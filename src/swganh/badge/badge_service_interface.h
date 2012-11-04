// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include <swganh/service/service_interface.h>

namespace swganh {

namespace object {
	class Object;
} // namespace swganh::object

namespace badge {

	/**
	 * Manages players badges.
	 */
	class BadgeServiceInterface : public swganh::service::ServiceInterface
	{
	public:

		/**
		 * Awards player with the target badge.
		 *
		 * @param player Target player.
		 * @param name The name of the badge begin awarded. (i.e. "exp_tat_bens_hut", see database `swganh_static.badges`.)
		 */
		virtual void GiveBadge(std::shared_ptr<swganh::object::Object> player, std::string name)=0;

		/**
		 * Awards player with the target badge.
		 *
		 * @param player Target player.
		 * @param id The id of the badge begin awarded. (See database `swganh_static.badges`.)
		 */
		virtual void GiveBadge(std::shared_ptr<swganh::object::Object> player, uint32_t id)=0;

		/**
		 * Verfies if a player has target badge.
		 *
		 * @param player Target player.
		 * @param name The name of the badge being verified. (i.e. "exp_tat_bens_hut", see database `swganh_static.badges`.)
		 */
		virtual bool HasBadge(std::shared_ptr<swganh::object::Object> object, std::string name)=0;

		/**
		 * Verfies if a player has target badge.
		 *
		 * @param player Target player.
		 * @param id The id of the badge being verified. (See database `swganh_static.badges`.)
		 */
		virtual bool HasBadge(std::shared_ptr<swganh::object::Object> object, uint32_t id)=0;
	};
}} // namespace swganh::badge