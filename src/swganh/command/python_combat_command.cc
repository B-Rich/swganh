// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "python_combat_command.h"
#include "swganh/app/swganh_kernel.h"

#include "swganh/object/creature/creature.h"
#include "swganh/object/tangible/tangible.h"

using namespace boost::python;
using namespace std;
using namespace swganh::command;
using namespace swganh::scripting;
using namespace swganh::object;
using namespace swganh::object::creature;
using namespace swganh::object::tangible;

PythonCombatCommand::PythonCombatCommand(std::string script)
: script_(script)
{
}

boost::python::object PythonCombatCommand::operator()(swganh::app::SwganhKernel* kernel, shared_ptr<Creature> actor, shared_ptr<Tangible> target, const swganh::messages::controllers::CommandQueueEnqueue& command_queue_message)
{
    shared_ptr<Creature> creature = nullptr;
    if (target && target->GetType() == Creature::type)
        creature = static_pointer_cast<Creature>(target);
    
    script_.SetContext("kernel", boost::python::ptr(kernel));
	script_.SetContext("actor", actor);
    script_.SetContext("target", target);
    script_.SetContext("creature_target", creature);
    script_.SetContext("command_string", command_queue_message.command_options);
	
	script_.Run();

    return script_.GetGlobals();
}