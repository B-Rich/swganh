
#include "swganh/simulation/galaxy_service.h"

#include "anh/service/service_manager.h"

#include "swganh/app/swganh_kernel.h"

#include "swganh/connection/connection_client.h"
#include "swganh/connection/connection_service.h"

#include "swganh/messages/select_character.h"

#include "swganh/network/remote_client.h"

#include "swganh/object/object.h"
#include "swganh/object/object_controller.h"
#include "swganh/object/object_manager.h"

#include "swganh/simulation/scene_manager.h"

using namespace std;
using namespace swganh::connection;
using namespace swganh::messages;
using namespace swganh::network;
using namespace swganh::object;
using namespace swganh::simulation;

using anh::app::KernelInterface;
using anh::service::ServiceDescription;
using swganh::base::BaseService;

namespace swganh {
namespace simulation {

class GalaxyServiceImpl {
public:
    const shared_ptr<ObjectManager>& GetObjectManager()
    {
        if (!object_manager_)
        {
            object_manager_ = make_shared<ObjectManager>();
        }

        return object_manager_;
    }

    const shared_ptr<SceneManager>& GetSceneManager()
    {
        if (!scene_manager_)
        {
            scene_manager_ = make_shared<SceneManager>();
        }

        return scene_manager_;
    }

    shared_ptr<Object> LoadObjectById(uint64_t object_id)
    {
        auto find_iter = loaded_objects_.find(object_id);

        if (find_iter != loaded_objects_.end())
        {
            throw swganh::object::InvalidObject("Requested object already loaded");
        }

        auto object = object_manager_->CreateObjectFromStorage(object_id);

        loaded_objects_.insert(make_pair(object_id, object));

        return object;
    }

    const shared_ptr<Object>& GetObjectById(uint64_t object_id)
    {
        auto find_iter = loaded_objects_.find(object_id);

        if (find_iter == loaded_objects_.end())
        {
            throw swganh::object::InvalidObject("Requested an invalid object");
        }

        return find_iter->second;
    }

    void RemoveObjectById(uint64_t object_id)
    {
        auto find_iter = loaded_objects_.find(object_id);

        if (find_iter == loaded_objects_.end())
        {
            throw swganh::object::InvalidObject("Requested an invalid object");
        }

        loaded_objects_.erase(find_iter);
    }

    shared_ptr<ObjectController> StartControllingObject(const shared_ptr<Object>& object, shared_ptr<RemoteClient> client)
    {
        auto find_iter = controlled_objects_.find(object->GetObjectId());

        if (find_iter != controlled_objects_.end())
        {
            throw swganh::object::InvalidObject("Object already has a controller");
        }
        
        auto controller = make_shared<ObjectController>(controller_handlers_, object, client);

        controlled_objects_.insert(make_pair(object->GetObjectId(), controller));

        return controller;
    }

    void StopControllingObject(const shared_ptr<Object>& object)
    {
        auto find_iter = controlled_objects_.find(object->GetObjectId());

        if (find_iter == controlled_objects_.end())
        {
            throw swganh::object::InvalidObject("Object has no controller");
        }
        
        controlled_objects_.erase(find_iter);
    }
        
    void RegisterControllerHandler(uint32_t handler_id, swganh::object::ObjControllerHandler&& handler)
    {
        auto find_iter = controller_handlers_.find(handler_id);

        if (find_iter != controller_handlers_.end())
        {
            throw std::runtime_error("ObjControllerHandler already exists");
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

        controller_handlers_.erase(find_iter);
    }
    
    void HandleSelectCharacter(
        shared_ptr<ConnectionClient> client, 
        const SelectCharacter& message)
    {
        auto object = LoadObjectById(message.character_id);
        StartControllingObject(object, client);
    }

private:
    shared_ptr<ObjectManager> object_manager_;
    shared_ptr<SceneManager> scene_manager_;

    ObjControllerHandlerMap controller_handlers_;

    map<uint64_t, shared_ptr<Object>> loaded_objects_;
    map<uint64_t, shared_ptr<ObjectController>> controlled_objects_;
};

}}  // namespace swganh::simulation

GalaxyService::GalaxyService(shared_ptr<KernelInterface> kernel)
    : BaseService(kernel) 
    , impl_(new GalaxyServiceImpl)
{}
    
GalaxyService::~GalaxyService()
{}

ServiceDescription GalaxyService::GetServiceDescription()
{
    ServiceDescription service_description(
        "GalaxyService",
        "galaxy",
        "0.1",
        "127.0.0.1", 
        0, 
        0, 
        0);

    return service_description;
}

void GalaxyService::StartScene(const std::string& scene_label)
{
    impl_->GetSceneManager()->StartScene(scene_label);
}

void GalaxyService::StopScene(const std::string& scene_label)
{
    impl_->GetSceneManager()->StopScene(scene_label);
}

shared_ptr<Object> GalaxyService::LoadObjectById(uint64_t object_id)
{
    return impl_->LoadObjectById(object_id);
}

const shared_ptr<Object>& GalaxyService::GetObjectById(uint64_t object_id)
{
    return impl_->GetObjectById(object_id);
}

void GalaxyService::RemoveObjectById(uint64_t object_id)
{
    impl_->RemoveObjectById(object_id);
}

shared_ptr<ObjectController> GalaxyService::StartControllingObject(
    const shared_ptr<Object>& object, 
    shared_ptr<RemoteClient> client)
{
    return impl_->StartControllingObject(object, client);
}

void GalaxyService::StopControllingObject(const shared_ptr<Object>& object)
{
    impl_->StopControllingObject(object);
}

void GalaxyService::RegisterControllerHandler(uint32_t handler_id, swganh::object::ObjControllerHandler&& handler)
{
    impl_->RegisterControllerHandler(handler_id, move(handler));
}

void GalaxyService::UnregisterControllerHandler(uint32_t handler_id)
{
    impl_->UnregisterControllerHandler(handler_id);
}

void GalaxyService::onStart()
{
    auto connection_service = std::static_pointer_cast<ConnectionService>(kernel()->GetServiceManager()->GetService("ConnectionService"));
        
    connection_service->RegisterMessageHandler<SelectCharacter>([=] (
        shared_ptr<ConnectionClient> client, 
        const SelectCharacter& message)
    {
        impl_->HandleSelectCharacter(client, message);
    });
}
