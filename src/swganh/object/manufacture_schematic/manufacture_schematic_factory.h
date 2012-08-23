// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#ifndef SWGANH_OBJECT_MANUFACTURE_SCHEMATIC_MANUFACTURE_SCHEMATIC_FACTORY_H_
#define SWGANH_OBJECT_MANUFACTURE_SCHEMATIC_MANUFACTURE_SCHEMATIC_FACTORY_H_

#include "swganh/object/object_factory_interface.h"

namespace swganh {
namespace object {
namespace manufacture_schematic {

    class ManufactureSchematicFactory : public swganh::object::ObjectFactoryInterface
    {
    public:
        void LoadTemplates();

        bool HasTemplate(const std::string& template_name);

        uint32_t PersistObject(const std::shared_ptr<swganh::object::Object>& object);

        void DeleteObjectFromStorage(const std::shared_ptr<swganh::object::Object>& object);

        std::shared_ptr<swganh::object::Object> CreateObjectFromStorage(uint64_t object_id);

        std::shared_ptr<swganh::object::Object> CreateObjectFromTemplate(const std::string& template_name, bool db_persisted=true, bool db_initialized=true);
    };

}}}  // namespace swganh::object::manufacture_schematic

#endif  // SWGANH_OBJECT_MANUFACTURE_SCHEMATIC_MANUFACTURE_SCHEMATIC_FACTORY_H_
