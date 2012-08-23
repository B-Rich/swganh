// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#ifndef SWGANH_OBJECT_BUILDING_BUILDING_FACTORY_H_
#define SWGANH_OBJECT_BUILDING_BUILDING_FACTORY_H_

#include "swganh/object/tangible/tangible_factory.h"

namespace swganh {
namespace object {

	class ObjectManager;

namespace building {

	class Building;

    class BuildingFactory : public swganh::object::tangible::TangibleFactory
    {
    public:
        BuildingFactory(anh::database::DatabaseManagerInterface* db_manager,
            anh::EventDispatcher* event_dispatcher);
		
		void LoadTemplates();

        bool HasTemplate(const std::string& template_name);

        uint32_t PersistObject(const std::shared_ptr<swganh::object::Object>& object);

        void DeleteObjectFromStorage(const std::shared_ptr<swganh::object::Object>& object);

        std::shared_ptr<swganh::object::Object> CreateObjectFromStorage(uint64_t object_id);

        std::shared_ptr<swganh::object::Object> CreateObjectFromTemplate(const std::string& template_name);

		virtual void RegisterEventHandlers(){}
    };

}}}  // namespace swganh::object::building

#endif  // SWGANH_OBJECT_BUILDING_BUILDING_FACTORY_H_
