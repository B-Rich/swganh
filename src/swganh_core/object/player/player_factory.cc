// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "player_factory.h"

#include <sstream>

#include <cppconn/exception.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/sqlstring.h>
#include "swganh/logger.h"

#include "swganh/crc.h"
#include "swganh/database/database_manager.h"
#include "swganh_core/object/player/player.h"
#include "player_events.h"

#include "swganh_core/object/exception.h"
#include "swganh_core/simulation/simulation_service_interface.h"

using namespace std;
using namespace swganh::database;
using namespace swganh::object;
using namespace swganh::object;
using namespace swganh::simulation;

PlayerFactory::PlayerFactory(swganh::app::SwganhKernel* kernel)
    : IntangibleFactory(kernel)
{}

void PlayerFactory::LoadFromStorage(const std::shared_ptr<sql::Connection>& connection, const std::shared_ptr<Object>& object)
{
    IntangibleFactory::LoadFromStorage(connection, object);

    auto player = std::dynamic_pointer_cast<Player>(object);
    if(!player)
    {
        throw InvalidObject("Object requested for loading is not Intangible");
    }

    auto statement = std::unique_ptr<sql::PreparedStatement>
        (connection->prepareStatement("CALL sp_GetPlayer(?);"));
    
    statement->setUInt64(1, player->GetObjectId());
  
    auto result = std::unique_ptr<sql::ResultSet>(statement->executeQuery());

    do
    { 
        while (result->next())
        {
            // Player specific start
            player->SetProfessionTag(result->getString("profession_tag"));
            player->SetBornDate(result->getUInt("born_date"));
            player->SetTotalPlayTime(result->getUInt("total_playtime"));
            player->SetAdminTag(result->getUInt("csr_tag"));
            player->SetCurrentForcePower(result->getUInt("current_force"));
            player->SetMaxForcePower(result->getUInt("max_force"));
            player->SetExperimentationFlag(result->getUInt("experimentation_enabled"));
            player->SetCraftingStage(result->getUInt("crafting_stage"));
            player->SetNearestCraftingStation(result->getUInt64("nearest_crafting_station"));
            player->AddExperimentationPoints(result->getUInt("experimentation_points"));
            player->ResetAccomplishmentCounter(result->getUInt("accomplishment_counter"));
            player->SetLanguage(result->getUInt("current_language"));
            player->ResetCurrentStomach(result->getUInt("current_stomach"));
            player->ResetMaxStomach(result->getUInt("max_stomach"));
            player->ResetCurrentDrink(result->getUInt("current_drink"));
            player->ResetMaxDrink(result->getUInt("max_drink"));
            player->SetJediState(result->getUInt("jedi_state"));
        }
    } while(statement->getMoreResults());
    
    LoadStatusFlags_(connection, player);
    LoadProfileFlags_(connection, player);
    LoadBadges_(connection, player);
    LoadDraftSchematics_(connection, player);
    LoadFriends_(connection, player);
    LoadForceSensitiveQuests_(connection, player);
    LoadIgnoredList_(connection, player);
    LoadQuestJournal_(connection, player);
    LoadWaypoints_(connection, player);
    LoadXP_(connection, player);
}

void PlayerFactory::RegisterEventHandlers()
{
    GetEventDispatcher()->Subscribe("Player::StatusBitmask", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));
    GetEventDispatcher()->Subscribe("Player::ProfileFlag", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));
    GetEventDispatcher()->Subscribe("Player::ProfessionTag", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));
    GetEventDispatcher()->Subscribe("Player::BornDate", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));
	GetEventDispatcher()->Subscribe("Player::TotalPlayTime", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));
	GetEventDispatcher()->Subscribe("Player::AdminTag", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));
	GetEventDispatcher()->Subscribe("Player::Experience", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));
	GetEventDispatcher()->Subscribe("Player::Waypoint", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));
	GetEventDispatcher()->Subscribe("Player::ForcePower", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));
	GetEventDispatcher()->Subscribe("Player::MaxForcePower", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::ForceSensitiveQuests", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::CompletedForceSensitiveQuests", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::QuestJournal", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::ExperimentationFlag", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::CraftingStage", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::NearestCraftingStation", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::DraftSchematic", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::ExperimentationPoints", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::AccomplishmentCounter", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::Friend", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::RemoveFriend", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::IgnorePlayer", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::RemoveIgnoredPlayer", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::Language", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::CurrentStomach", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::MaxStomach", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::CurrentDrink", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::MaxDrink", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));	
	GetEventDispatcher()->Subscribe("Player::JediState", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));
	GetEventDispatcher()->Subscribe("Player::Badges", std::bind(&PlayerFactory::PersistHandler, this, std::placeholders::_1));
}

void PlayerFactory::PersistChangedObjects()
{
	std::set<shared_ptr<Object>> persisted;
	{
		boost::lock_guard<boost::mutex> lg(persisted_objects_mutex_);
		persisted = move(persisted_objects_);
	}
	for (auto& object : persisted)
	{
		if(object->IsDatabasePersisted())
			PersistObject(object);
	}
}

uint32_t PlayerFactory::PersistObject(const shared_ptr<Object>& object, bool persist_inherited)
{
	uint32_t counter = 1;
	
    IntangibleFactory::PersistObject(object, persist_inherited);

    try 
    {
        auto conn = GetDatabaseManager()->getConnection("galaxy");
        auto statement = shared_ptr<sql::PreparedStatement>
			(conn->prepareStatement("CALL sp_PersistPlayer(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);"));
        
		auto player = static_pointer_cast<Player>(object);
		statement->setUInt64(counter++, player->GetObjectId());
		statement->setString(counter++, player->GetProfessionTag());
		statement->setUInt64(counter++, player->GetTotalPlayTime());
		statement->setUInt(counter++, player->GetAdminTag());
		statement->setUInt(counter++, player->GetMaxForcePower());
		statement->setUInt(counter++, player->GetExperimentationFlag());
		statement->setUInt(counter++, player->GetCraftingStage());
		statement->setUInt64(counter++, player->GetNearestCraftingStation());
		statement->setUInt(counter++, player->GetExperimentationPoints());
		statement->setUInt(counter++, player->GetAccomplishmentCounter());
		statement->setUInt(counter++, player->GetLanguage());
		statement->setUInt(counter++, player->GetCurrentStomach());
		statement->setUInt(counter++, player->GetMaxStomach());
		statement->setUInt(counter++, player->GetCurrentDrink());
		statement->setUInt(counter++, player->GetMaxDrink());
		statement->setUInt(counter++, player->GetJediState());

        statement->executeUpdate();

        PersistFriends_(player);
        PersistIgnoredList_(player);
        PersistXP_(player);
        PersistDraftSchematics_(player);
        PersistForceSensitiveQuests_(player);
        PersistQuestJournal_(player);
		PersistBadges_(player);
    }
    catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
	return counter;
}

void PlayerFactory::DeleteObjectFromStorage(const shared_ptr<Object>& object)
{
    ObjectFactory::DeleteObjectFromStorage(object);
}

shared_ptr<Object> PlayerFactory::CreateObject()
{
	//@TODO: Create me with help from db
	return make_shared<Player>();
}

void PlayerFactory::PersistXP_(const shared_ptr<Player>& player)
{
    try 
    {
        auto conn = GetDatabaseManager()->getConnection("galaxy");
        auto xp = player->GetXp();
        for(auto& xpData : xp)
        {
            auto statement = conn->prepareStatement("CALL sp_UpdateExperience(?,?);");
            statement->setString(1,xpData.first);
            statement->setUInt(2,xpData.second.value);
            auto result = unique_ptr<sql::ResultSet>(statement->executeQuery());
        };
    }
        catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}

void PlayerFactory::PersistBadges_(const shared_ptr<Player>& player)
{
	try
	{
		auto conn = GetDatabaseManager()->getConnection("galaxy");
		auto badges = player->GetBadgesSyncQueue();

		while(badges.size())
		{
			auto queue_item = badges.front();

			switch(queue_item.first)
			{
			case 0: // Remove
				{
					auto statement = conn->prepareStatement("CALL sp_RemoveBadge(?, ?);");
					statement->setUInt64(1, player->GetObjectId());
					statement->setUInt(2, queue_item.second);
					auto result = unique_ptr<sql::ResultSet>(statement->executeQuery());
					break;
				}

			case 1: // Add
				{
					auto statement = conn->prepareStatement("CALL sp_UpdateBadges(?, ?);");
					statement->setUInt64(1, player->GetObjectId());
					statement->setUInt(2, queue_item.second);
					auto result = unique_ptr<sql::ResultSet>(statement->executeQuery());
					break;
				}
			}

			badges.pop();
		}

		//for(auto& badge_id : badges)
		//{
		//	auto statement = conn->prepareStatement("CALL sp_UpdateBadges(?, ?);");
		//	statement->setUInt64(1, player->GetObjectId());
		//	statement->setUInt(2, badge_id);
		//	auto result = unique_ptr<sql::ResultSet>(statement->executeQuery());
		//};
	}
    catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}

void PlayerFactory::PersistDraftSchematics_(const shared_ptr<Player>& player)
{
    try 
    {
        auto conn = GetDatabaseManager()->getConnection("galaxy");
        auto draft_schematics = player->GetDraftSchematics();
        for(auto& schematic : draft_schematics)
        {
            auto statement = conn->prepareStatement("CALL sp_UpdateDraftSchematic(?,?,?);");
            statement->setUInt64(1, player->GetObjectId());
            statement->setUInt(2,schematic.schematic_id);
            statement->setUInt(3, schematic.schematic_crc);
            auto result = unique_ptr<sql::ResultSet>(statement->executeQuery());
        };
    }
        catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}

void PlayerFactory::PersistQuestJournal_(const shared_ptr<Player>& player)
{
    try 
    {
        auto conn = GetDatabaseManager()->getConnection("galaxy");
        auto quests = player->GetQuests();
        
        for(auto& quest : quests)
        {
            auto statement = conn->prepareStatement("CALL sp_UpdateQuestJournal(?,?,?,?,?,?);");
            statement->setUInt64(1, player->GetObjectId());
            statement->setUInt64(2, quest.second.owner_id);
            statement->setUInt(3, quest.second.quest_crc);
            statement->setUInt(4, quest.second.active_step_bitmask);
            statement->setUInt(5, quest.second.completed_step_bitmask);
            statement->setUInt(6, quest.second.completed_flag);
            
            auto result = unique_ptr<sql::ResultSet>(statement->executeQuery());
        };
    }
        catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}

void PlayerFactory::PersistForceSensitiveQuests_(const shared_ptr<Player>& player)
{
    try 
    {
        auto conn = GetDatabaseManager()->getConnection("galaxy");
        auto statement = conn->prepareStatement("CALL sp_UpdateFSQuests(?,?,?);");
        statement->setUInt64(1, player->GetObjectId());
        statement->setUInt(2, player->GetCurrentForceSensitiveQuests());
        statement->setUInt(3, player->GetCompletedForceSensitiveQuests());

        auto result = unique_ptr<sql::ResultSet>(statement->executeQuery());
    }
        catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}
void PlayerFactory::RemoveFriend_(const std::shared_ptr<Player>& player, uint64_t friend_id)
{
    try 
    {
        auto conn = GetDatabaseManager()->getConnection("galaxy");
        
        auto statement = conn->prepareStatement("CALL sp_RemoveFriend(?,?);");
        statement->setUInt64(1, player->GetObjectId());
        statement->setUInt64(2, friend_id);

        statement->execute();
        }
    catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}
void PlayerFactory::PersistFriends_(const shared_ptr<Player>& player)
{
    try 
    {
        auto conn = GetDatabaseManager()->getConnection("galaxy");
        auto friends = player->GetFriends();
        
        for(auto& friend_name : friends)
        {
            auto statement = conn->prepareStatement("CALL sp_UpdateFriends(?,?);");
            statement->setUInt64(1, player->GetObjectId());
            statement->setUInt64(2, friend_name.id);
            auto result = unique_ptr<sql::ResultSet>(statement->executeQuery());
        };
    }
        catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}

void PlayerFactory::PersistIgnoredList_(const shared_ptr<Player>& player)
{
    try 
    {
        auto conn = GetDatabaseManager()->getConnection("galaxy");
        auto ignored_players = player->GetIgnoredPlayers();
        
        for(auto& player_name : ignored_players)
        {
            auto statement = conn->prepareStatement("CALL sp_UpdateIgnoreList(?,?);");
            statement->setUInt64(1, player->GetObjectId());
            statement->setUInt64(2, player_name.id);
            auto result = unique_ptr<sql::ResultSet>(statement->executeQuery());
        };
    }
        catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}
void PlayerFactory::RemoveFromIgnoredList_(const shared_ptr<Player>& player, uint64_t ignore_player_id)
{
    try 
    {
        auto conn = GetDatabaseManager()->getConnection("galaxy");
        
        auto statement = conn->prepareStatement("CALL sp_RemoveIgnoredPlayer(?,?);");
        statement->setUInt64(1, player->GetObjectId());
        statement->setUInt64(2, ignore_player_id);

        statement->execute();
        }
    catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}

void PlayerFactory::LoadStatusFlags_(const std::shared_ptr<sql::Connection>& connection, const std::shared_ptr<Player>& player)
{
    auto statement = std::shared_ptr<sql::PreparedStatement>
        (connection->prepareStatement("CALL sp_GetPlayerStatusFlags(?);"));
    
    statement->setUInt64(1, player->GetObjectId());

    auto result = std::unique_ptr<sql::ResultSet>(statement->executeQuery());
    do
    {
        while (result->next())
        {
            player->AddStatusFlag(static_cast<StatusFlags>(result->getUInt("flag")));
        }
    } while(statement->getMoreResults());
}

void PlayerFactory::LoadProfileFlags_(const std::shared_ptr<sql::Connection>& connection, const std::shared_ptr<Player>& player)
{
    auto statement = std::shared_ptr<sql::PreparedStatement>
        (connection->prepareStatement("CALL sp_GetPlayerProfileFlags(?);"));
    
    statement->setUInt64(1, player->GetObjectId());

    auto result = std::unique_ptr<sql::ResultSet>(statement->executeQuery());
    do
    { 
        while (result->next())
        {
            player->AddProfileFlag(static_cast<ProfileFlags>(result->getUInt("flag")));
        }
    } while(statement->getMoreResults());
}

void PlayerFactory::LoadBadges_(const std::shared_ptr<sql::Connection>& connection, const std::shared_ptr<Player>& player)
{
    auto statement = std::shared_ptr<sql::PreparedStatement>
        (connection->prepareStatement("CALL sp_GetPlayerBadges(?);"));
    
    statement->setUInt64(1, player->GetObjectId());

    auto result = std::unique_ptr<sql::ResultSet>(statement->executeQuery());  
    do
    {  
        while (result->next())
        {
            player->AddBadge(result->getUInt("badge"));
        }
    } while(statement->getMoreResults());
}

void PlayerFactory::LoadDraftSchematics_(const std::shared_ptr<sql::Connection>& connection, const std::shared_ptr<Player>& player)
{
    auto statement = std::shared_ptr<sql::PreparedStatement>
        (connection->prepareStatement("CALL sp_GetPlayerDraftSchematics(?);"));
    
    statement->setUInt64(1, player->GetObjectId());

    auto result = std::unique_ptr<sql::ResultSet>(statement->executeQuery());
    do
    {
        while (result->next())
        {
            DraftSchematicData data;
            data.schematic_id = result->getUInt("id");
            data.schematic_crc = result->getUInt("schematic_id");
            // didn't move here because you can't get faster than copying 2 ints
            player->AddDraftSchematic(data);
        }
    } while(statement->getMoreResults());
}

void PlayerFactory::LoadFriends_(const std::shared_ptr<sql::Connection>& connection, const std::shared_ptr<Player>& player)
{
    auto statement = std::shared_ptr<sql::PreparedStatement>
        (connection->prepareStatement("CALL sp_GetFriends(?);"));
    
    statement->setUInt64(1, player->GetObjectId());

    auto result = std::unique_ptr<sql::ResultSet>(statement->executeQuery());
    do
    {
        while (result->next())
        {
            player->AddFriend(result->getString("custom_name"), result->getUInt64("id"));
        }
    } while(statement->getMoreResults());
}

void PlayerFactory::LoadForceSensitiveQuests_(const std::shared_ptr<sql::Connection>& connection, const std::shared_ptr<Player>& player)
{
    auto statement = std::shared_ptr<sql::PreparedStatement>
        (connection->prepareStatement("CALL sp_GetFSQuestList(?);"));
    
    statement->setUInt64(1, player->GetObjectId());

    auto result = std::unique_ptr<sql::ResultSet>(statement->executeQuery());
    do
    {  
        while (result->next())
        {
            if (result->getUInt("completed") == 1)
            {
                player->AddCompletedForceSensitiveQuest(result->getUInt("quest_mask"));
            }
            else
            {
                player->AddCurrentForceSensitiveQuest(result->getUInt("quest_mask"));
            }
        }
    } while(statement->getMoreResults());
}

void PlayerFactory::LoadIgnoredList_(const std::shared_ptr<sql::Connection>& connection, const std::shared_ptr<Player>& player)
{
    auto statement = std::shared_ptr<sql::PreparedStatement>
        (connection->prepareStatement("CALL sp_GetIgnoredList(?);"));
    
    statement->setUInt64(1, player->GetObjectId());

    auto result = std::unique_ptr<sql::ResultSet>(statement->executeQuery());
    do
    {  
        while (result->next())
        {
            player->IgnorePlayer(result->getString("custom_name"), result->getUInt64("id"));
        }
    } while(statement->getMoreResults());
}

void PlayerFactory::LoadQuestJournal_(const std::shared_ptr<sql::Connection>& connection, const std::shared_ptr<Player>& player)
{
    auto statement = std::shared_ptr<sql::PreparedStatement>
        (connection->prepareStatement("CALL sp_GetQuestJournal(?);"));
    
    statement->setUInt64(1, player->GetObjectId());

    auto result = std::unique_ptr<sql::ResultSet>(statement->executeQuery());
    do
    {
        while (result->next())
        {
            QuestJournalData data;
            data.owner_id = result->getUInt64("quest_owner_id");
            data.quest_crc = result->getUInt("quest_crc");
            data.active_step_bitmask = result->getUInt("active_step_bitmask");
            data.completed_step_bitmask = result->getUInt("completed_step_bitmask");
            data.completed_flag = result->getUInt("completed") == 1;
            player->AddQuest(std::move(data));
        }
    } while(statement->getMoreResults());
}

void PlayerFactory::LoadWaypoints_(const std::shared_ptr<sql::Connection>& connection, const std::shared_ptr<Player>& player)
{
    auto statement = std::shared_ptr<sql::PreparedStatement>
        (connection->prepareStatement("CALL sp_GetWaypoint(?);"));
    
    statement->setUInt64(1, player->GetObjectId());

    auto result = std::unique_ptr<sql::ResultSet>(statement->executeQuery());
    do
    {   
        while (result->next())
        {
            //auto result = shared_ptr<sql::ResultSet>(statement->getResultSet());
            //GetEventDispatcher()->Dispatch(make_shared<WaypointEvent>("LoadWaypoints", player, result));
        }
    } while(statement->getMoreResults());
}

void PlayerFactory::LoadXP_(const std::shared_ptr<sql::Connection>& connection, const std::shared_ptr<Player>& player)
{
    auto statement = std::shared_ptr<sql::PreparedStatement>
        (connection->prepareStatement("CALL sp_GetExperienceList(?);"));
    
    statement->setUInt64(1, player->GetObjectId());

    auto result = std::unique_ptr<sql::ResultSet>(statement->executeQuery());
    do
    { 
        while (result->next())
        {
            player->AddExperience(XpData(result->getString("name"), result->getUInt("value")));
        }
    } while(statement->getMoreResults());
}
