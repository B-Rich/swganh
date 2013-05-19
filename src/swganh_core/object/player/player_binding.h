// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#pragma once

#include "swganh_core/object/player/player.h"
#include "swganh_core/object/creature/creature_binding.h"

#include <boost/python.hpp>

using namespace boost::python;
using namespace std;
using namespace swganh::object;

void exportPlayer()
{
	enum_<Gender>("GENDER", "The gender of the :class:`.Player`")
		.value("FEMALE", FEMALE)
		.value("MALE", MALE)
		;
	enum_<StatusFlags>("STATUS_FLAGS", "Status of the :class:`.Player` they can be in multiple of these")
		.value("CLEAR", CLEAR)
		.value("LFG", LFG)
		.value("HELPER", HELPER)
		.value("ROLEPLAYER", ROLEPLAYER)
		.value("AFK", AFK)
		.value("LD", LD)
		.value("FACTION_RANK", FACTION_RANK)
		//.value("ANONYMOUS", ANONYMOUS)
		;
    
    //@TODO: Discover Profile Flags
    enum_<ProfileFlags>("PROFILE_FLAGS", "Flags that describe a :class:`.Player` profile.")
        ;
	
    enum_<AdminTag>("ADMIN_TAG", "Admin tag that the :class:`.Player` has.")
		.value("CSR", CSR)
		.value("DEVELOPER", DEVELOPER)
		;

	class_<XpData>("XpData")
		//.def_readwrite("type", &XpData.type)
		//.def_readwrite("value", &XpData.value)
		//.def("__eq__", &XpData.operator==)
		;
	class_<QuestJournalData>("QuestJournalData", "Describes the Quest Journal of the :class:`.Player`")
		.def_readwrite("quest_crc", &QuestJournalData::quest_crc)
		.def_readwrite("owner_id", &QuestJournalData::owner_id)
		.def_readwrite("active_step_bitmask", &QuestJournalData::active_step_bitmask)
		.def_readwrite("completed_step_bitmask", &QuestJournalData::completed_step_bitmask)
		.def_readwrite("completed_flag", &QuestJournalData::completed_flag)
		.def_readwrite("counter", &QuestJournalData::counter)
		;
	class_<DraftSchematicData>("DraftSchematicData", "Describes a single Draft Schematic", init<uint32_t, uint32_t>())
		.def_readwrite("schematic_id", &DraftSchematicData::schematic_id)
		.def_readwrite("schematic_crc", &DraftSchematicData::schematic_crc)
		;
	class_<PlayerWaypointSerializer>("PlayerWaypointSerializer", "Describes a single Waypoint", init<std::shared_ptr<Waypoint>>())
		.def_readwrite("waypoint", &PlayerWaypointSerializer::waypoint)
		;

	class_<Player, bases<Intangible>, std::shared_ptr<Player>, boost::noncopyable>("Player", "The :class:`.Player` is a child of :class:`.Object` and describes actions specific to a Player Character.")
		.def("addStatusFlag", (void(Player::*)(StatusFlags,StatusIndex)) &Player::AddStatusFlag, "adds a status flag to the existing :class:`.STATUS_FLAGS`")
		.def("removeStatusFlag", (void(Player::*)(StatusFlags,StatusIndex)) &Player::RemoveStatusFlag, "remove status flag from existing :class:`.STATUS_FLAGS`")
		.def("clearStatusFlags", (void(Player::*)()) &Player::ClearStatusFlags, "clears all status :class:`.STATUS_FLAGS`")
		.def("addProfileFlag", (void(Player::*)(ProfileFlags,StatusIndex)) &Player::AddProfileFlag, "adds a profile flag to the existing :class:`.PROFILE_FLAGS`")
		.def("removeProfileFlag", (void(Player::*)(ProfileFlags,StatusIndex)) &Player::RemoveProfileFlag, "remove profile flag from existing :class:`.PROFILE_FLAGS`")
		.def("clearProfileFlags", (void(Player::*)()) &Player::ClearProfileFlags, "clears all :class:`.PROFILE_FLAGS`")
		.add_property("profession_tag", (std::string(Player::*)()) &Player::GetProfessionTag,  (void(Player::*)(std::string))&Player::SetProfessionTag, "Gets and Sets the profession tag")
		.add_property("born_date", (uint32_t(Player::*)()) &Player::GetBornDate,  (void(Player::*)(uint32_t)) &Player::SetBornDate, "Gets and Sets the born date")
		.add_property("play_time", (uint32_t(Player::*)()) &Player::GetTotalPlayTime, (void(Player::*)(uint32_t)) &Player::SetTotalPlayTime, "Gets and Sets Total Play Time")
		.add_property("admin_flag", (uint8_t(Player::*)()) &Player::GetAdminTag, (void(Player::*)(uint8_t)) &Player::SetAdminTag, "Gets and Sets the admin tag of the player")
		.def("addXp", (void(Player::*)(XpData)) &Player::AddExperience, "adds experience via :class:`.XpData`")
		.def("deductXp", (void(Player::*)(XpData)) &Player::DeductXp, "deducts experience via :class:`.XpData`")
		.def("clearXp", (void(Player::*)(std::string)) &Player::ClearXpType, "clears all experience of the type given")
		.def("clearAllXp", (void(Player::*)()) &Player::ClearAllXp, "clears all experience of all types")
		.def("addWaypoint", (void(Player::*)(PlayerWaypointSerializer)) &Player::AddWaypoint, "adds a :class:`.Waypoint` to the player")
		.def("removeWaypoint", (void(Player::*)(uint64_t)) &Player::RemoveWaypoint, "removes a :class:`.Waypoint` from the player")
		.def("modifyWaypoint", (void(Player::*)(PlayerWaypointSerializer)) &Player::ModifyWaypoint, "modifys an existing :class:`.Waypoint`")
		.def("clearAllWaypoints", (void(Player::*)()) &Player::ClearAllWaypoints, "clears all :class:`.Waypoint`")
		.add_property("forcePower", (int32_t(Player::*)()) &Player::GetCurrentForcePower, (void(Player::*)(int32_t)) &Player::SetCurrentForcePower, "Gets and Sets the current force power")
		.def("addForcePower", (void(Player::*)(int32_t)) &Player::IncrementForcePower, "increments the current force power by x amount")
		.add_property("maxForcePower", (int32_t(Player::*)()) &Player::GetMaxForcePower, (void(Player::*)(int32_t)) &Player::SetMaxForcePower, "Gets and set the max force power")
		.def("getCurrentFsQuests", (uint32_t(Player::*)()) &Player::GetCurrentForceSensitiveQuests, "Gets the players current force sensitive quests in crc form")
		.def("addFsQuest", (void(Player::*)(uint32_t)) &Player::AddCurrentForceSensitiveQuest, "Adds a fs quest to the players current force sensitive quests")
		.def("removeFsQuest", (void(Player::*)(uint32_t)) &Player::RemoveCurrentForceSensitiveQuest, "Removes a fs quest from the player's force sensitive quests")
		.def("clearFsQuests", (void(Player::*)()) &Player::ClearCurrentForceSensitiveQuests, "Clear current force sensitive quests")
		.def("getCompletedFsQuests", (uint32_t(Player::*)()) &Player::GetCompletedForceSensitiveQuests, "Gets the players completed force sensitive quests in crc form")
		.def("completeFsQuest", (void(Player::*)(uint32_t)) &Player::AddCompletedForceSensitiveQuest, "Adds a fs quest to the players completed force sensitive quests")
		.def("clearCompletedFsQuests", (void(Player::*)()) &Player::ClearCompletedForceSensitiveQuests, "Clear completed force sensitive quests")
		.def("addQuest", (void(Player::*)(QuestJournalData)) &Player::AddQuest, "Adds a quest to the players :class:`.QuestJournal`")
		.def("removeQuest", (void(Player::*)(QuestJournalData)) &Player::RemoveQuest, "Removes quest from the players :class:`.QuestJournal`")
		.def("updateQuest", (void(Player::*)(QuestJournalData)) &Player::UpdateQuest, "Updates an existing quest in the players :class:`.QuestJournal`")
		.def("clearQuests", (void(Player::*)()) &Player::ClearAllQuests, "Clears all quests from a players :class:`.QuestJournal`")
		.add_property("experimentation_flag", (uint32_t(Player::*)()) &Player::GetExperimentationFlag, (void(Player::*)(uint32_t)) &Player::SetExperimentationFlag, "Gets and Sets the player experimentation flag")
		.add_property("crafting_stage", (uint32_t(Player::*)()) &Player::GetCraftingStage, (void(Player::*)(uint32_t)) &Player::SetCraftingStage, "Gets and Sets the players current crafting stage")
		.add_property("nearest_crafting_station", (uint64_t(Player::*)()) &Player::GetNearestCraftingStation, (void(Player::*)(uint64_t)) &Player::SetNearestCraftingStation, "Gets and Sets the nearest crafting station for the player")
		.def("addDraftSchematic", (void(Player::*)(DraftSchematicData)) &Player::AddDraftSchematic, "Adds a :class:`.DraftSchematicData` to the player")
		.def("removeDraftSchematic", (void(Player::*)(uint32_t)) &Player::RemoveDraftSchematic, "Removes a :class:`.DraftSchematicData` from the player")
		.def("clearDraftSchematics", (void(Player::*)()) &Player::ClearDraftSchematics, "Clears all :class:`.DraftSchematicData`  from player")
		.add_property("experimentation_points", (uint32_t(Player::*)()) &Player::GetExperimentationPoints, (void(Player::*)(uint32_t)) &Player::ResetExperimentationPoints, "Gets and Resets the experimentation points of the player")
		.def("addExperimentationPoints", (void(Player::*)(uint32_t)) &Player::AddExperimentationPoints, "Adds experimentations points to the player")
		.def("removeExperimentationPoints", (void(Player::*)(uint32_t)) &Player::RemoveExperimentationPoints, "Removes experimentation points from the player")
		.def("incrementAccomplishments", (void(Player::*)()) &Player::IncrementAccomplishmentCounter, "increments the accomplishment counter of the player")
		.add_property("accomplishment_counter", (uint32_t(Player::*)()) &Player::GetAccomplishmentCounter, (void(Player::*)(uint32_t)) &Player::ResetAccomplishmentCounter, "Gets and Resets the accomplishment counter of the player")
		.def("addFriend", (void(Player::*)(std::string, uint64_t)) &Player::AddFriend, "Adds a friend to the players friends list")
		.def("removeFriend", (void(Player::*)(std::string)) &Player::RemoveFriend, "Removes a friend from the players friends list")
		.def("clearFriends", (void(Player::*)()) &Player::ClearFriends, "Clears all friends from the players friends list")
        .def("isFriend", (bool(Player::*)(std::string)) &Player::IsFriend, "Checks to see if the name is currently a friend of the player")
        .def("isIgnored", (bool(Player::*)(std::string)) &Player::IsIgnored, "Checks to see if the name is currently being ignored by the player")
		.def("ignorePlayer", (void(Player::*)(std::string, uint64_t)) &Player::IgnorePlayer, "Adds a player to the ignore list")
		.def("removeIgnore", (void(Player::*)(std::string)) &Player::StopIgnoringPlayer, "Stops ignoring a player, removes them from the ignore list")
		.def("clearIgnorePlayers", (void(Player::*)()) &Player::ClearIgnored, "Clears the ignore player list")
		.add_property("language", (uint32_t(Player::*)()) &Player::GetLanguage, (void(Player::*)(uint32_t)) &Player::SetLanguage, "Gets and Sets the players spoken language")
		.add_property("stomach", (uint32_t(Player::*)()) &Player::GetCurrentStomach, (void(Player::*)(uint32_t)) &Player::ResetCurrentStomach, "Gets and resets the players stomach level")
		.def("increaseStomach", (void(Player::*)(uint32_t)) &Player::IncreaseCurrentStomach, "adds to the players current stomach level")
		.def("decreaseStomach", (void(Player::*)(uint32_t)) &Player::DecreaseCurrentStomach, "decreases from the players current stomach level")
		.add_property("max_stomach", (uint32_t(Player::*)()) &Player::GetMaxStomach, (void(Player::*)(uint32_t)) &Player::ResetMaxStomach, "Gets and resets the players MAX stomach level")
		.add_property("drink", (uint32_t(Player::*)()) &Player::GetCurrentDrink, (void(Player::*)(uint32_t)) &Player::ResetCurrentDrink, "Gets and resets the players drink level")
		.def("increaseDrink", (void(Player::*)(uint32_t)) &Player::IncreaseCurrentDrink, "adds to the players current drink level")
		.def("decreaseDrink", (void(Player::*)(uint32_t)) &Player::DecreaseCurrentDrink, "decreases from the players current drink level")
		.add_property("max_drink", (uint32_t(Player::*)()) &Player::GetMaxDrink, (void(Player::*)(uint32_t)) &Player::ResetMaxDrink, "Gets and resets the players MAX drink level")
		.add_property("jedi_state", (uint32_t(Player::*)()) &Player::GetJediState, (void(Player::*)(uint32_t)) &Player::SetJediState, "Gets and set the jedi state")
		.add_property("gender", (Gender(Player::*)()) &Player::GetGender, (void(Player::*)(Gender)) &Player::SetGender, "Gets and Sets the players :class:`.GENDER` ")
		;

	implicitly_convertible<std::shared_ptr<Player>, std::shared_ptr<Object>>();
	implicitly_convertible<std::shared_ptr<Player>, std::shared_ptr<ContainerInterface>>();
}