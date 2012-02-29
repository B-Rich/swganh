#ifndef SWGANH_OBJECT_OBJECT_CONTROLLER_H_
#define SWGANH_OBJECT_OBJECT_CONTROLLER_H_

#include "swganh/object/object_controller.h"
#include "swganh/messages/controllers/show_fly_text.h"
#include "swganh/messages/out_of_band.h"

#include <boost/python.hpp>

using namespace boost::python;
using namespace std;
using namespace swganh::object;
using namespace swganh::messages;

struct ProsePackageWrapper : ProsePackage, wrapper<ProsePackage>
{
    ProsePackageWrapper() : ProsePackage(){}
};

void exportOutOfBand()
{
    enum_<ProseType>("ProseType")
        .value("TU", TU)
        .value("TT", TT)
        .value("TO", TO)
        .value("DI", DI)
        .value("DF", DF)
        ;
    class_<OutOfBand, boost::noncopyable>("OutOfBand","object that is used in the help with sending system stf messages")
        .def(init<std::string, std::string, ProseType, uint64_t>())
    ;
}

struct ObjectControllerWrapper : ObjectController, wrapper<ObjectController>
{
};

void exportObjectController()
{
    enum_<controllers::FlyTextColor>("FlyTextColor")
        .value("RED", controllers::RED)
        .value("GREEN", controllers::GREEN)
        .value("BLUE", controllers::BLUE)
        .value("MIX", controllers::MIX)
        ;

    bool (ObjectController::*SendSystemMessageStr)(const std::string&) = &ObjectController::SendSystemMessage;
    bool (ObjectController::*SendSystemMessageOutOfBand)(const OutOfBand&, bool, bool) = &ObjectController::SendSystemMessage;
    bool (ObjectController::*SendSystemMessageString)(const std::wstring&, bool, bool) = &ObjectController::SendSystemMessage;

    void (ObjectController::*SendFlyText)(const std::string&, controllers::FlyTextColor) = &ObjectController::SendFlyText;

    class_<ObjectControllerWrapper, std::shared_ptr<ObjectController>, boost::noncopyable>("ObjectController", no_init)
        .def("SendSystemMessage", SendSystemMessageOutOfBand, "Sends the specified system message to the player with an out of band object attached")
        .def("SendSystemMessage", SendSystemMessageString, "Sends System Message to the player, taking a string as the message and boolean for chatbox only and another boolean to send to in range")
        .def("SendSystemMessage", SendSystemMessageStr, "Sends System Message to the player, taking a string as the message")
        .def("SendFlyText", SendFlyText, "Sends Fly Text to the player, see @FlyTextColor")
        .def("Notify", &ObjectControllerWrapper::Notify, "Notifies the controller whent he object has been updated")
    ;
}

#endif //  SWGANH_OBJECT_OBJECT_CONTROLLER_H_