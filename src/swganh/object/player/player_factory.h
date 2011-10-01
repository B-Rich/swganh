
#ifndef SWGANH_OBJECT_PLAYER_PLAYER_FACTORY_H_
#define SWGANH_OBJECT_PLAYER_PLAYER_FACTORY_H_

#include "swganh/object/object_factory_interface.h"
#include <unordered_map>

namespace anh {
namespace database {
class DatabaseManagerInterface;
}} // anh::database

namespace swganh {
namespace object {
namespace player {
    
    class Player;
    class PlayerFactory : public swganh::object::ObjectFactoryInterface
    {
    public:
        PlayerFactory(const std::shared_ptr<anh::database::DatabaseManagerInterface>& db_manager);

        void LoadTemplates();

        bool HasTemplate(const std::string& template_name);

        void PersistObject(const std::shared_ptr<swganh::object::Object>& object);

        void DeleteObjectFromStorage(const std::shared_ptr<swganh::object::Object>& object);

        std::shared_ptr<swganh::object::Object> CreateObjectFromStorage(uint64_t object_id);

        std::shared_ptr<swganh::object::Object> CreateObjectFromTemplate(const std::string& template_name);
    private:
        PlayerFactory(){}
        // Helpers
        void LoadXP_(std::shared_ptr<Player> player);
        void PersistXP_(const std::shared_ptr<Player>& player);
        void LoadWaypoints_(std::shared_ptr<Player> player);
        void PersistWaypoints_(const std::shared_ptr<Player>& player);
        void LoadDraftSchematics_(std::shared_ptr<Player> player);
        void PersistDraftSchematics_(const std::shared_ptr<Player>& player);
        void LoadQuestJournal_(std::shared_ptr<Player> player);
        void PersistQuestJournal_(const std::shared_ptr<Player>& player);
        void LoadAbilities_(std::shared_ptr<Player> player);
        void PersistAbilities_(const std::shared_ptr<Player>& player);
        void LoadFriends_(std::shared_ptr<Player> player);
        void PersistFriends_(const std::shared_ptr<Player>& player);
        void LoadIgnoredList_(std::shared_ptr<Player> player);
        void PersistIgnoredList_(const std::shared_ptr<Player>& player);

        std::shared_ptr<anh::database::DatabaseManagerInterface> db_manager_;
        std::unordered_map<std::string, std::shared_ptr<Player>>::iterator GetTemplateIter_(const std::string& template_name);
        std::unordered_map<std::string, std::shared_ptr<Player>> player_templates_;
    };

}}}  // namespace swganh::object::player

#endif  // SWGANH_OBJECT_PLAYER_PLAYER_FACTORY_H_
