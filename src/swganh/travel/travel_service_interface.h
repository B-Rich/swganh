// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include <swganh/service/service_interface.h>

namespace swganh {
namespace object {
	class Object;
} // namespace swganh::object

namespace travel {
	class TravelServiceInterface : public swganh::service::ServiceInterface
	{
	public:

		/**
		 * Begins the ticket transaction processes by opening the ticket purchasing window.
		 * 
		 * @param object Target player.
		 */
		virtual void BeginTicketTransaction(std::shared_ptr<swganh::object::Object> object)=0;
	};
}} // namespace swganh::travel