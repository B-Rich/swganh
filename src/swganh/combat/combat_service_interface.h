// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#ifndef WIN32
#include <Python.h>
#endif

#include <cstdint>
#include <memory>
#include <string>
#include <tuple>

#include <boost/asio/deadline_timer.hpp>
#include <boost/python.hpp>

#include "swganh/active_object.h"
#include "swganh/random_generator.h"
#include "swganh/service/service_interface.h"

#include "swganh/app/swganh_kernel.h"
#include "swganh/command/command_properties.h"
#include "pub14_core/messages/controllers/command_queue_enqueue.h"


namespace swganh {
namespace simulation {
class SimulationServiceInterface;
}
namespace command {
class CommandServiceInterface; 
}
namespace object {
    class Object;
    class ObjectController;
namespace tangible {
    class Tangible;
}
namespace creature {
	class Creature;
}}}  // namespace swganh::object::creature;


namespace swganh {
namespace command {    
    class BaseCombatCommand;
}
    
namespace combat {

    class CombatServiceInterface : public anh::service::ServiceInterface
    {
    public:
        virtual void SetIncapacitated(const std::shared_ptr<swganh::object::creature::Creature>& attacker, const std::shared_ptr<swganh::object::creature::Creature>& target) = 0;
        
        virtual void SetDead(const std::shared_ptr<swganh::object::creature::Creature>& attacker, const std::shared_ptr<swganh::object::creature::Creature>& target) = 0;

        virtual void EndDuel(const std::shared_ptr<swganh::object::creature::Creature>& attacker, const std::shared_ptr<swganh::object::creature::Creature>& target) = 0;
        virtual void EndCombat(const std::shared_ptr<swganh::object::creature::Creature>& attacker, const std::shared_ptr<swganh::object::creature::Creature>& target) = 0;
        
		virtual void Startup() = 0;

        virtual void SendCombatAction(swganh::command::BaseCombatCommand* command) = 0;
    };

}}  // namespace swganh::combat
