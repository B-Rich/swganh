// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#ifndef SWGANH_OBJECT_TANGIBLE_TANGIBLE_FACTORY_H_
#define SWGANH_OBJECT_TANGIBLE_TANGIBLE_FACTORY_H_

#include "swganh/object/object_factory.h"

#include <unordered_map>

namespace anh {
namespace database {
class DatabaseManagerInterface;
}} // anh::database

namespace sql {
class Statement;
}

namespace swganh {
namespace object {
namespace tangible {

    class Tangible;
    class TangibleFactory : public swganh::object::ObjectFactory
    {
    public:
        typedef Tangible ObjectType;

        TangibleFactory(anh::database::DatabaseManagerInterface* db_manager,
            anh::EventDispatcher* event_dispatcher);
        void LoadTemplates();

        bool HasTemplate(const std::string& template_name);

        uint32_t PersistObject(const std::shared_ptr<swganh::object::Object>& object);

        void DeleteObjectFromStorage(const std::shared_ptr<swganh::object::Object>& object);

        std::shared_ptr<swganh::object::Object> CreateObjectFromStorage(uint64_t object_id);
        void CreateTangible(const std::shared_ptr<Tangible>& tangible, const std::shared_ptr<sql::Statement>& statement);

        std::shared_ptr<swganh::object::Object> CreateObjectFromTemplate(const std::string& template_name);
        
        virtual void RegisterEventHandlers(){}
    private:
        std::unordered_map<std::string, std::shared_ptr<swganh::object::tangible::Tangible>>::iterator GetTemplateIter_(const std::string& template_name);
        std::unordered_map<std::string, std::shared_ptr<swganh::object::tangible::Tangible>> tangible_templates_;
    };

}}}  // namespace swganh::object::tangible

#endif  // SWGANH_OBJECT_TANGIBLE_TANGIBLE_FACTORY_H_
