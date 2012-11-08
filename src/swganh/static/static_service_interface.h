// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "swganh/service/service_interface.h"

namespace swganh
{
namespace object
{
	class Object;
	class Creature;
}

namespace statics
{
	struct ElevatorData
	{
		uint64_t dst_cell;
		glm::quat dst_orientation;
		glm::vec3 dst_position;
		uint32_t effect_id;
		bool going_down;
	};

	struct CloneData
	{
		std::string city;
		uint32_t scene_id;
		uint64_t parent_id;
		glm::vec3 vec;
		glm::quat quat;
	};

	class StaticServiceInterface : public swganh::service::ServiceInterface
	{
	public:

		//Returns the elevator data for a particular terminal.
		virtual std::vector<std::shared_ptr<ElevatorData>> GetElevatorDataForObject(uint64_t terminal_id) = 0;

		/*
		 * @brief Gets a given skill mod and any affected Attributes if exist
		 * @return a pair of base, modifier
		 */
		virtual std::pair<uint32_t, uint32_t> GetSkillMod(const std::shared_ptr<swganh::object::Creature>& creature, const std::string& skill_mod_name) = 0;
		
		/*
		 * @brief Gets All SkillMods that are applicable for this creature.
		 * @return a map of pairs of base, modifier
		 */
		virtual std::map<std::string, std::pair<uint32_t, uint32_t>> GetSkillMods(const std::shared_ptr<swganh::object::Creature>& creature) = 0;


		 /*
		 * @brief get CloneData for a given clone_id
		 */
		virtual std::shared_ptr<CloneData> GetCloneData(uint32_t clone_id) = 0;		
		/*
		 * @brief Gets the clone id based on the current object id
		 */ 
		virtual int32_t GetCloneId(const std::shared_ptr<swganh::object::Object> obj) = 0;		

	};
}
}