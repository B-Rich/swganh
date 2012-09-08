#include "spawn_service.h"

#include <algorithm>
#include <memory>

#include "anh/logger.h"

#include "anh/service/service_manager.h"

#include "pub14_core/simulation/simulation_service.h"
#include "pub14_core/simulation/scene_events.h"

#include "swganh/object/permissions/permission_type.h"
#include "swganh/object/object_manager.h"
#include "swganh/object/object.h"

#include "swganh/tre/resource_manager.h"
#include "swganh/tre/visitors/snapshot/ws_visitor.h"
#include "swganh/tre/visitors/objects/object_visitor.h"

// Temp
#include "swganh/object/regions/badge/badge_region.h"
#include "swganh/object/permissions/world_permission.h"

using namespace anh::service;
using namespace swganh::app;
using namespace swganh::simulation;
using namespace swganh::object;
using namespace swganh::tre;

using namespace swganh_core::spawn;
using namespace swganh_core::simulation;

SpawnService::SpawnService(SwganhKernel* kernel) : kernel_(kernel)
{
	kernel_->GetEventDispatcher()->Subscribe("SceneManager:NewScene", [&] (const std::shared_ptr<anh::EventInterface>& newEvent)
	{
		auto real_event = std::static_pointer_cast<swganh_core::simulation::NewSceneEvent>(newEvent);
		
		auto simulation_service = kernel_->GetServiceManager()->GetService<SimulationServiceInterface>("SimulationService");
		
		LOG(info) << "SpawnService: Loading static objects for planet: " << real_event->scene_label;

		//Temp
		std::shared_ptr<swganh::object::regions::BadgeRegion> badge_region = std::make_shared<swganh::object::regions::BadgeRegion>();
		badge_region->SetEventDispatcher(kernel_->GetEventDispatcher());
		badge_region->SetPosition(glm::vec3(1084, 0, 4176));
		badge_region->SetSceneId(real_event->scene_id);
		badge_region->SetObjectId(0xDEADBABE);
		badge_region->SetInSnapshot(true);
		badge_region->SetPermissions(std::make_shared<swganh::object::WorldPermission>());
		simulation_service->TransferObjectToScene(badge_region, real_event->scene_label);

		//Load objects from snapshot	
		std::string snapshot_filename = "snapshot/"+real_event->scene_label+".ws";
		auto snapshot_visitor = kernel_->GetResourceManager()->GetResourceByName<WsVisitor>(snapshot_filename, false);

		auto chunks = snapshot_visitor->chunks();
		simulation_service->PrepareToAccomodate(chunks.size());
		for(auto& chunk : chunks) 
		{
			auto filename = snapshot_visitor->name(chunk.name_id);
			auto object = simulation_service->CreateObjectFromTemplate(filename, 
				FindProperPermission_(filename), false, false, chunk.id);
				
			if(object)
			{
				object->SetPosition(chunk.location);
				object->SetOrientation(chunk.orientation);
				object->SetSceneId(real_event->scene_id);
				object->SetInSnapshot(true);
				object->SetDatabasePersisted(false);
					
				//@Todo: Set scale
				
				if(chunk.parent_id == 0)
				{
					//Put it into the scene
					simulation_service->TransferObjectToScene(object, real_event->scene_label);
				}
				else
				{
					//It has a parent, so get it's parent and put it into that
					auto parent = simulation_service->GetObjectById(chunk.parent_id);
					if(parent != nullptr)
					{
						parent->AddObject(nullptr, object);
					}
				}
			}
		}
	});

	/* Dont need this now, but we might later.
	
	kernel_->GetEventDispatcher()->Subscribe("SceneManager:DestroyScene", [&] (const std::shared_ptr<anh::EventInterface>& newEvent)
	{
		auto real_event = std::static_pointer_cast<swganh_core::simulation::DestroySceneEvent>(newEvent);
		
	});*/
}

SpawnService::~SpawnService()
{
}

ServiceDescription SpawnService::GetServiceDescription()
{
    ServiceDescription service_description(
        "SpawnService",
        "spawn",
        "0.1",
        "127.0.0.1",
        0,
        0,
        0);

    return service_description;
}

PermissionType SpawnService::FindProperPermission_(const std::string& iff_name)
{
	if(iff_name.compare("object/cell/shared_cell.iff") == 0)
	{
		return WORLD_CELL_PERMISSION;
	}
	return STATIC_CONTAINER_PERMISSION;
}