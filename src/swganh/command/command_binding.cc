// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "command_binding.h"

#include "anh/python_shared_ptr.h"
#include <boost/python.hpp>

#include "swganh/app/swganh_kernel.h"
#include "swganh/object/creature/creature.h"
#include "swganh/object/tangible/tangible.h"
#include "swganh/scripting/utilities.h"

#include "base_swg_command.h"
#include "command_interface.h"

namespace bp = boost::python;
using swganh::command::BaseSwgCommand;
using swganh::command::CommandCallback;
using swganh::command::CommandInterface;
using swganh::command::CommandProperties;
using swganh::object::ObjectController;
using swganh::scripting::ScopedGilLock;

struct BaseSwgCommandWrapper : BaseSwgCommand, bp::wrapper<BaseSwgCommand>
{
    BaseSwgCommandWrapper(
        PyObject* obj,
        swganh::app::SwganhKernel* kernel,
        const CommandProperties& properties,
        const std::shared_ptr<ObjectController>& controller,
        const swganh::messages::controllers::CommandQueueEnqueue& command_request)
        : BaseSwgCommand(kernel, properties, controller, command_request)
    {
        ScopedGilLock lock;
        bp::detail::initialize_wrapper(obj, this);
    }

    const std::shared_ptr<ObjectController>& GetController() const
    {
        {
            ScopedGilLock lock;
            try 
            {
                bp::override get_controller = this->get_override("GetController");
                if (get_controller)
                {
                    return get_controller().as<const std::shared_ptr<ObjectController>&>();
                }
            }
            catch(bp::error_already_set& /*e*/)
            {
                PyErr_Print();
            }
        }

        return this->BaseSwgCommand::GetController();
    }

    void Setup()
    {
        ScopedGilLock lock;
        try 
        {
            this->get_override("Setup")();
        }
        catch(bp::error_already_set& /*e*/)
        {
            PyErr_Print();
        }
    }

    bool Validate()
    {
        bool validated = false;

        ScopedGilLock lock;
        try 
        {
            validated = this->get_override("Validate")();
        }
        catch(bp::error_already_set& /*e*/)
        {
            PyErr_Print();
        }

        return validated;
    }

    boost::optional<std::shared_ptr<CommandCallback>> Run()
    {
        boost::optional<std::shared_ptr<CommandCallback>> callback;

        ScopedGilLock lock;
        try 
        {
            bp::object result = this->get_override("Run")();

            CommandCallback* obj_pointer = bp::extract<CommandCallback*>(result);
            callback.reset(std::shared_ptr<CommandCallback>(obj_pointer, [result] (CommandCallback*) {}));
        }
        catch(bp::error_already_set& /*e*/)
        {
            PyErr_Print();
        }

        return callback;
    }
};

class CommandCallbackWrapper : public CommandCallback, bp::wrapper<CommandCallback>
{
public:
    CommandCallbackWrapper(
        PyObject* obj,
        boost::python::object function,
        uint64_t delay_timer)
        : CommandCallback([function] () -> boost::optional<std::shared_ptr<CommandCallback>>
    {
        ScopedGilLock lock;
        
        boost::optional<std::shared_ptr<CommandCallback>> callback;

        try 
        {
            bp::object result = function();
            
            CommandCallback* obj_pointer = bp::extract<CommandCallback*>(result);
            callback.reset(std::shared_ptr<CommandCallback>(obj_pointer, [result] (CommandCallback*) {}));
        }
        catch(bp::error_already_set& /*e*/)
        {
            PyErr_Print();
        }

        return callback;
    }, delay_timer)
    {    
        ScopedGilLock lock;
        bp::detail::initialize_wrapper(obj, this);
    }

    CommandCallbackWrapper(
        PyObject* obj,
        boost::python::object function,
        boost::python::object instance,
        uint64_t delay_timer)
        : CommandCallback([function, instance] () -> boost::optional<std::shared_ptr<CommandCallback>>
    {
        ScopedGilLock lock;
        boost::optional<std::shared_ptr<CommandCallback>> callback;
        
        try 
        {
            bp::object result = function();
            CommandCallback* obj_pointer = bp::extract<CommandCallback*>(result);
            callback.reset(std::shared_ptr<CommandCallback>(obj_pointer, [result] (CommandCallback*) {}));
        }
        catch(bp::error_already_set& /*e*/)
        {
            PyErr_Print();
        }

        return callback;
    }, delay_timer)
    {
        ScopedGilLock lock;
        bp::detail::initialize_wrapper(obj, this);
    }
};

void swganh::command::ExportCommand()
{
    bp::class_<CommandCallback, std::shared_ptr<CommandCallbackWrapper>, boost::noncopyable>
        ("Callback", bp::init<bp::object, uint64_t>())
        .def(bp::init<bp::object, bp::object, uint64_t>())
        .def("GetDelayTimeInMs", &CommandCallbackWrapper::GetDelayTimeInMs)
        .def("Execute", &CommandCallbackWrapper::operator())
    ;

    bp::class_<CommandInterface, boost::noncopyable>("CommandInterface", bp::no_init)
        .def("GetController", bp::pure_virtual(&CommandInterface::GetController), bp::return_internal_reference<>())
        .def("Setup", bp::pure_virtual(&CommandInterface::Setup))
        .def("Validate", bp::pure_virtual(&CommandInterface::Validate))
        .def("Run", bp::pure_virtual(&CommandInterface::Run))
    ;
    
    bp::class_<BaseSwgCommand, BaseSwgCommandWrapper, bp::bases<CommandInterface>, boost::noncopyable>
        ("BaseSwgCommand", bp::init<swganh::app::SwganhKernel*, const CommandProperties&, const std::shared_ptr<object::ObjectController>&, const swganh::messages::controllers::CommandQueueEnqueue&>())
        .def("GetController", &BaseSwgCommandWrapper::GetController, bp::return_value_policy<bp::copy_const_reference>())
        .def("GetKernel", &BaseSwgCommandWrapper::GetKernel, bp::return_internal_reference<>())
        .def("GetCommandName", &BaseSwgCommandWrapper::GetCommandName)
        .def("GetActionCounter", &BaseSwgCommandWrapper::GetActionCounter)
        .def("GetPriority", &BaseSwgCommandWrapper::GetPriority)
        .def("GetCommandGroup", &BaseSwgCommandWrapper::GetCommandGroup)
        .def("GetTargetRequiredType", &BaseSwgCommandWrapper::GetTargetRequiredType)
        .def("GetMaxRangeToTarget", &BaseSwgCommandWrapper::GetMaxRangeToTarget)
        .def("GetDefaultTime", &BaseSwgCommandWrapper::GetDefaultTime)
        .def("GetRequiredAbility", &BaseSwgCommandWrapper::GetRequiredAbility)
        .def("IsQueuedCommand", &BaseSwgCommandWrapper::IsQueuedCommand)
        .def("GetActor", &BaseSwgCommandWrapper::GetActor, bp::return_value_policy<bp::copy_const_reference>())
        .def("GetTarget", &BaseSwgCommandWrapper::GetTarget, bp::return_value_policy<bp::copy_const_reference>())
    ;
}
