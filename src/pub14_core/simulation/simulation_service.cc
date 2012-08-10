// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "simulation_service.h"

#include <boost/algorithm/string.hpp>

#include "anh/byte_buffer.h"
#include "anh/crc.h"
#include "anh/event_dispatcher.h"
#include "anh/service/service_manager.h"
#include "anh/database/database_manager.h"
#include "anh/network/soe/server_interface.h"
#include "anh/plugin/plugin_manager.h"

#include "swganh/app/swganh_kernel.h"

#include "swganh/command/command_interface.h"
#include "swganh/command/command_service_interface.h"
#include "swganh/command/python_command_creator.h"

#include "swganh/connection/connection_client_interface.h"
#include "swganh/connection/connection_service_interface.h"

#include "swganh/messages/select_character.h"

#include "swganh/object/object.h"
#include "swganh/object/object_controller.h"
#include "swganh/object/object_manager.h"

// factories
#include "swganh/object/creature/creature_factory.h"
#include "swganh/object/creature/creature.h"
#include "swganh/object/tangible/tangible_factory.h"
#include "swganh/object/tangible/tangible.h"
#include "swganh/object/intangible/intangible_factory.h"
#include "swganh/object/intangible/intangible.h"
#include "swganh/object/player/player_factory.h"
#include "swganh/object/player/player.h"

// message builders
#include "swganh/object/creature/creature_message_builder.h"
#include "swganh/object/intangible/intangible_message_builder.h"
#include "swganh/object/tangible/tangible_message_builder.h"
#include "swganh/object/player/player_message_builder.h"

#include "swganh/simulation/scene_manager_interface.h"
#include "swganh/simulation/spatial_provider_interface.h"
#include "swganh/simulation/scene_interface.h"
#include "swganh/messages/cmd_start_scene.h"
#include "swganh/messages/cmd_scene_ready.h"
#include "swganh/messages/obj_controller_message.h"
#include "swganh/messages/update_containment_message.h"

#include "swganh/tre/resource_manager.h"
#include "swganh/tre/visitors/objects/object_visitor.h"

#include "movement_manager.h"
#include "scene_manager.h"
#include "swganh/simulation/movement_manager_interface.h"

using namespace anh;
using namespace std;
using namespace swganh::connection;
using namespace swganh::messages;
using namespace swganh::network;
using namespace swganh::object;
using namespace swganh::simulation;
using namespace swganh_core::simulation;

using namespace swganh::tre;

using anh::network::soe::ServerInterface;
using anh::network::soe::Session;
using anh::service::ServiceDescription;
using swganh::app::SwganhKernel;

namespace swganh_core {
namespace simulation {

class SimulationServiceImpl {
public:
    SimulationServiceImpl(SwganhKernel* kernel)
        : kernel_(kernel)
    {
		spatial_provider_ = kernel->GetPluginManager()->CreateObject<SpatialProviderInterface>("Simulation::SpatialProvider");
    }

    const shared_ptr<ObjectManager>& GetObjectManager()
    {
        if (!object_manager_)
        {
            object_manager_ = make_shared<ObjectManager>(kernel_);
        }

        return object_manager_;
    }

    const shared_ptr<SceneManagerInterface>& GetSceneManager()
    {
        if (!scene_manager_)
        {
            scene_manager_ = kernel_->GetPluginManager()->CreateObject<SceneManager>("Simulation::SceneManager");
        }

        return scene_manager_;
    }

    MovementManagerInterface* GetMovementManager()
    {
        if (!movement_manager_)
        {
			movement_manager_ = kernel_->GetPluginManager()->CreateObject<MovementManager>("Simulation::MovementManager");
			movement_manager_->SetSpatialProvider(spatial_provider_.get());
		}

        return movement_manager_.get();
    }
	
    void PersistObject(uint64_t object_id)
    {
        object_manager_->PersistObject(object_id);
    }
	void PersistRelatedObjects(uint64_t parent_object_id)
	{
        object_manager_->PersistRelatedObjects(parent_object_id);
	}

    shared_ptr<Object> LoadObjectById(uint64_t object_id)
    {
        auto object = object_manager_->LoadObjectById(object_id);

		spatial_provider_->AddObject(object); // Add object to spatial indexing.
        
        return object;
    }

    shared_ptr<Object> LoadObjectById(uint64_t object_id, uint32_t type)
    {
        auto object = object_manager_->LoadObjectById(object_id, type);

		spatial_provider_->AddObject(object); // Add object to spatial indexing.

        return object;
    }

    shared_ptr<Object> GetObjectById(uint64_t object_id)
    {
        return object_manager_->GetObjectById(object_id);
    }

    void RemoveObjectById(uint64_t object_id)
    {
        auto object = object_manager_->GetObjectById(object_id);
        if (object)
        {
            RemoveObject(object);
        }
    }

    void RemoveObject(const shared_ptr<Object>& object)
    {
        auto scene = scene_manager_->GetScene(object->GetSceneId());
        if (scene)
        {
            scene->RemoveObject(object);
        }

		spatial_provider_->RemoveObject(object); // Remove the object from spatial indexing.

        StopControllingObject(object);

        object_manager_->RemoveObject(object);
        
        auto contained_objects = object->GetContainedObjects();
        for_each(
            begin(contained_objects),
            end(contained_objects),
            [this] (const Object::ObjectMap::value_type& item)
        {
            RemoveObject(item.second);
        });
    }

	shared_ptr<Object> GetObjectByCustomName(const wstring& custom_name)
	{
        return object_manager_->GetObjectByCustomName(custom_name);
	}

	void TransferObjectToSceneWithPosition(uint64_t object_id, const string& scene, float x, float y, float z)
	{
		auto obj = TransferObjectToScene(object_id, scene);
		obj->SetPosition(glm::vec3(x,y,z));
	}
	void TransferObjectToSceneWithPosition(shared_ptr<Object> obj, const string& scene, float x, float y, float z)
	{
		TransferObjectToScene(obj, scene);
		obj->SetPosition(glm::vec3(x,y,z));
	}
	void TransferObjectToScene(shared_ptr<Object> obj, const string& scene)
	{
		// Get Next Scene
		auto scene_obj = scene_manager_->GetScene(scene);

        if (!scene_obj)
        {
            throw std::runtime_error("Requested transfer to an invalid scene: " + scene);
        }

		// Remove from existing scene
		scene_manager_->GetScene(obj->GetSceneId())->RemoveObject(obj);

		// Add to new scene
		// CmdStartScene
        CmdStartScene start_scene;
        start_scene.ignore_layout = 0;
        start_scene.character_id = obj->GetObjectId();

        start_scene.terrain_map = scene_obj->GetTerrainMap();
        start_scene.position = obj->GetPosition();
        start_scene.shared_race_template = obj->GetTemplate();
        start_scene.galaxy_time = 0;
        obj->GetController()->GetRemoteClient()->SendTo(start_scene);

        // Add object to scene and send baselines
        scene_obj->AddObject(obj);
	}

	shared_ptr<Object> TransferObjectToScene(uint64_t object_id, const string& scene)
	{
		// Get Object
		auto obj = GetObjectById(object_id);

		TransferObjectToScene(obj, scene);

		return obj;
	}
	
    shared_ptr<ObjectController> StartControllingObject(const shared_ptr<Object>& object, shared_ptr<ConnectionClientInterface> client)
    {
        shared_ptr<ObjectController> controller = nullptr;

        // If a controller already exists update it, otherwise create a new controller record.
        auto find_iter = controlled_objects_.find(object->GetObjectId());
        if (find_iter != controlled_objects_.end())
        {
            controller = find_iter->second;
            controller->SetRemoteClient(client);
        }
        else
        {
            controller = make_shared<ObjectController>(object, client);
            object->SetController(controller);

            controlled_objects_.insert(make_pair(object->GetObjectId(), controller));
        }

        auto connection_client = std::static_pointer_cast<ConnectionClientInterface>(client);
        connection_client->SetController(controller);

        return controller;
    }

    void StopControllingObject(const shared_ptr<Object>& object)
    {
        auto find_iter = controlled_objects_.find(object->GetObjectId());

        if (find_iter == controlled_objects_.end())
        {
            return;
        }

        controlled_objects_.unsafe_erase(find_iter);
    }

    void RegisterControllerHandler(uint32_t handler_id, swganh::object::ObjControllerHandler&& handler)
    {
        auto find_iter = controller_handlers_.find(handler_id);

        if (find_iter != controller_handlers_.end())
        {
            // just return, we already have the handler registered
            return;
            //throw std::runtime_error("ObjControllerHandler already exists");
        }

        controller_handlers_.insert(make_pair(handler_id, move(handler)));
    }

    void UnregisterControllerHandler(uint32_t handler_id)
    {
        auto find_iter = controller_handlers_.find(handler_id);

        if (find_iter == controller_handlers_.end())
        {
            throw std::runtime_error("ObjControllerHandler does not exist");
        }

        controller_handlers_.unsafe_erase(find_iter);
    }

    void HandleObjControllerMessage(
        const shared_ptr<ConnectionClientInterface>& client,
        ObjControllerMessage message)
    {
        auto find_iter = controller_handlers_.find(message.message_type);

        if (find_iter == controller_handlers_.end())
        {
            DLOG(warning) << "No handler registered to process the given message. " << message.data;
            return;
        }

        find_iter->second(client->GetController(), move(message));
    }

    void HandleSelectCharacter(
        const shared_ptr<ConnectionClientInterface>& client,
        SelectCharacter message)
    {
        auto object = GetObjectById(message.character_id);

        if (!object)
        {
            object = LoadObjectById(message.character_id, creature::Creature::type);
        }

        auto event_dispatcher = kernel_->GetEventDispatcher();
        auto contained = object->GetContainedObjects();
		
        for_each(
            begin(contained),
            end(contained),
            [event_dispatcher] (Object::ObjectMap::value_type& object_entry)
        {
			if (object_entry.second->GetType() == player::Player::type)
			{
				auto player = static_pointer_cast<player::Player>(object_entry.second);
				if (player)
				{
					event_dispatcher->Dispatch(
						make_shared<ValueEvent<shared_ptr<player::Player>>>("Simulation::PlayerSelected", player));
				}
			}
        });
        
        StartControllingObject(object, client);

        auto scene = scene_manager_->GetScene(object->GetSceneId());

        if (!scene)
        {
            throw std::runtime_error("Invalid scene selected for object");
        }

        // CmdStartScene
        CmdStartScene start_scene;
        start_scene.ignore_layout = 0;
        start_scene.character_id = object->GetObjectId();

        start_scene.terrain_map = scene->GetTerrainMap();
        start_scene.position = object->GetPosition();
        start_scene.shared_race_template = object->GetTemplate();
        start_scene.galaxy_time = 0;
        client->SendTo(start_scene);

        // Add object to scene and send baselines
        scene->AddObject(object);

		////////// TESTING ///////////
		////////// TESTING ///////////

		auto object_template = std::static_pointer_cast<ObjectVisitor>(
			kernel_->GetResourceManager()->getResourceByName(
			"object/tangible/wearables/armor/marine/shared_armor_marine_backpack.iff", 
			OIFF_VISITOR));
		object_template->load_aggregate_data(kernel_->GetResourceManager());
		object_template->load_referenced_files(kernel_->GetResourceManager());

		////////// TESTING ///////////
		////////// TESTING ///////////
    }

	void SendToAll(ByteBuffer message)
	{
		for_each(begin(controlled_objects_), end(controlled_objects_), [=] (const pair<uint64_t, shared_ptr<ObjectController>>& pair) {
            auto controller = pair.second;
            controller->GetRemoteClient()->SendTo(message);
        });
	}

    void SendToAllInScene(ByteBuffer message, uint32_t scene_id)
    {
        for_each(begin(controlled_objects_), end(controlled_objects_), [=] (const pair<uint64_t, shared_ptr<ObjectController>>& pair) {
            auto controller = pair.second;
            if (controller->GetObject()->GetSceneId() == scene_id)
                controller->GetRemoteClient()->SendTo(message);
        });
    }

private:
    shared_ptr<ObjectManager> object_manager_;
    shared_ptr<SceneManagerInterface> scene_manager_;
    shared_ptr<MovementManagerInterface> movement_manager_;
    SwganhKernel* kernel_;
	ServerInterface* server_;
	shared_ptr<SpatialProviderInterface> spatial_provider_;

    ObjControllerHandlerMap controller_handlers_;

    Concurrency::concurrent_unordered_map<uint64_t, shared_ptr<ObjectController>> controlled_objects_;
};

}}  // namespace swganh_core::simulation

SimulationService::SimulationService(SwganhKernel* kernel)
    : impl_(new SimulationServiceImpl(kernel))
    , kernel_(kernel)
{
    impl_->GetSceneManager()->LoadSceneDescriptionsFromDatabase(kernel_->GetDatabaseManager()->getConnection("galaxy"));
    RegisterObjectFactories();
}

SimulationService::~SimulationService()
{}

ServiceDescription SimulationService::GetServiceDescription()
{
    ServiceDescription service_description(
        "SimulationService",
        "simulation",
        "0.1",
        "127.0.0.1",
        0,
        0,
        0);

    return service_description;
}

void SimulationService::StartScene(const std::string& scene_label)
{
    impl_->GetSceneManager()->StartScene(scene_label);
}

void SimulationService::StopScene(const std::string& scene_label)
{
    impl_->GetSceneManager()->StopScene(scene_label);
}
void SimulationService::RegisterObjectFactories()
{
    auto object_manager = impl_->GetObjectManager();

    object_manager->RegisterObjectType<Object>();
    object_manager->RegisterObjectType<tangible::Tangible>();
    object_manager->RegisterObjectType<intangible::Intangible>();
    object_manager->RegisterObjectType<creature::Creature>();
    object_manager->RegisterObjectType<player::Player>();
}

void SimulationService::PersistObject(uint64_t object_id)
{
    impl_->PersistObject(object_id);
}
void SimulationService::PersistRelatedObjects(uint64_t parent_object_id)
{
	impl_->PersistRelatedObjects(parent_object_id);
}
shared_ptr<Object> SimulationService::LoadObjectById(uint64_t object_id)
{
    return impl_->LoadObjectById(object_id);
}
shared_ptr<Object> SimulationService::LoadObjectById(uint64_t object_id, uint32_t type)
{
    return impl_->LoadObjectById(object_id, type);
}

shared_ptr<Object> SimulationService::GetObjectById(uint64_t object_id)
{
    return impl_->GetObjectById(object_id);
}

void SimulationService::RemoveObjectById(uint64_t object_id)
{
    impl_->RemoveObjectById(object_id);
}

void SimulationService::RemoveObject(const shared_ptr<Object>& object)
{
    impl_->RemoveObject(object);
}

shared_ptr<Object> SimulationService::GetObjectByCustomName(const string& custom_name)
{
	return GetObjectByCustomName(wstring(begin(custom_name), end(custom_name)));
}

shared_ptr<Object> SimulationService::GetObjectByCustomName(const wstring& custom_name)
{
	return impl_->GetObjectByCustomName(custom_name);
}

void SimulationService::TransferObjectToScene(uint64_t object_id, const string& scene)
{
	impl_->TransferObjectToScene(object_id, scene);
}
void SimulationService::TransferObjectToScene(uint64_t object_id, const std::string& scene, float x, float y, float z)
{
	impl_->TransferObjectToSceneWithPosition(object_id, scene, x, y ,z);
}
void SimulationService::TransferObjectToScene(std::shared_ptr<swganh::object::Object> object, const std::string& scene)
{
	impl_->TransferObjectToScene(object, scene);
}
void SimulationService::TransferObjectToScene(std::shared_ptr<swganh::object::Object> object, const std::string& scene, float x, float y, float z)
{
	impl_->TransferObjectToSceneWithPosition(object, scene, x, y, z);
}
shared_ptr<ObjectController> SimulationService::StartControllingObject(
    const shared_ptr<Object>& object,
    shared_ptr<ConnectionClientInterface> client)
{
    return impl_->StartControllingObject(object, client);
}

void SimulationService::StopControllingObject(const shared_ptr<Object>& object)
{
    impl_->StopControllingObject(object);
}

void SimulationService::RegisterControllerHandler(
    uint32_t handler_id,
    swganh::object::ObjControllerHandler&& handler)
{
    impl_->RegisterControllerHandler(handler_id, move(handler));
}

void SimulationService::UnregisterControllerHandler(uint32_t handler_id)
{
    impl_->UnregisterControllerHandler(handler_id);
}

void SimulationService::SendToAll(ByteBuffer message)
{
    impl_->SendToAll(message);
}

void SimulationService::SendToAllInScene(ByteBuffer message, uint32_t scene_id)
{
    impl_->SendToAllInScene(message, scene_id);
}

void SimulationService::Startup()
{
	auto connection_service = kernel_->GetServiceManager()->GetService<ConnectionServiceInterface>("ConnectionService");

    connection_service->RegisterMessageHandler(
        &SimulationServiceImpl::HandleSelectCharacter, impl_.get());

    connection_service->RegisterMessageHandler(
        &SimulationServiceImpl::HandleObjControllerMessage, impl_.get());

    SimulationServiceInterface::RegisterControllerHandler(
        &MovementManagerInterface::HandleDataTransform, impl_->GetMovementManager());

    SimulationServiceInterface::RegisterControllerHandler(
        &MovementManagerInterface::HandleDataTransformWithParent, impl_->GetMovementManager());

    
	auto command_service = kernel_->GetServiceManager()->GetService<swganh::command::CommandServiceInterface>("CommandService");

    command_service->AddCommandCreator("burstrun", swganh::command::PythonCommandCreator("commands.burstrun", "BurstRunCommand"));
	command_service->AddCommandCreator("addfriend", swganh::command::PythonCommandCreator("commands.addfriend", "AddFriendCommand"));
	command_service->AddCommandCreator("removefriend", swganh::command::PythonCommandCreator("commands.removefriend", "RemoveFriendCommand"));
	command_service->AddCommandCreator("setmoodinternal", swganh::command::PythonCommandCreator("commands.setmoodinternal", "SetMoodInternalCommand"));

}
