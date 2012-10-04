// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#ifndef WIN32
#include <Python.h>
#endif

#include "swganh_core/object/object.h"
#include "swganh/object/object_controller_binding.h"
#include "swganh/object/permissions/container_permissions_interface.h"

#include <boost/python.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "swganh/sui/radial_binding.h"

#include "swganh_core/messages/system_message.h"

#include "swganh_core/messages/update_transform_message.h"
#include "swganh_core/messages/update_transform_with_parent_message.h"

using namespace boost::python;
using namespace std;
using namespace swganh::object;

boost::python::tuple AddObject(std::shared_ptr<Object> requester, std::shared_ptr<Object> newObject, int32_t arrangement_id=-2)
{
	return boost::python::make_tuple(newObject, requester, arrangement_id);
}

boost::python::tuple TransferObject(std::shared_ptr<Object> requester, std::shared_ptr<Object> object, std::shared_ptr<ContainerInterface> newContainer, int32_t arrangement_id=-2)
{
	return boost::python::make_tuple(requester, object, newContainer, arrangement_id);
}

void SendSystemMessage1(std::shared_ptr<Object> requester, std::string filename, std::string label)
{
	SystemMessage::Send(requester, filename, label);
}
void SendSystemMessage2(std::shared_ptr<Object> requester, std::wstring& custom_message, bool chatbox_only, bool send_to_inrange)
{
	SystemMessage::Send(requester, custom_message, chatbox_only, send_to_inrange);
}
void SendSystemMessage3(std::shared_ptr<Object> requester, swganh::messages::OutOfBand& out_of_band, bool chatbox_only, bool send_to_inrange)
{
	SystemMessage::Send(requester, out_of_band, chatbox_only, send_to_inrange);
}
void SendSystemMessage4(std::shared_ptr<Object> requester, std::wstring custom_message, swganh::messages::OutOfBand& out_of_band, bool chatbox_only, bool send_to_inrange)
{
	SystemMessage::Send(requester, custom_message, out_of_band, chatbox_only, send_to_inrange);
}
void SendFlyText(std::shared_ptr<Object> requester, const std::string& fly_text, controllers::FlyTextColor color)
{
	SystemMessage::FlyText(requester, fly_text, color);
}

void UpdatePosition(std::shared_ptr<Object> object, glm::vec3 pos)
{
	object->SetPosition(pos);
	if(object->GetContainer()->GetObjectId() == 0)
	{
		UpdateTransformMessage transform_update;
		transform_update.object_id = object->GetObjectId();
		transform_update.heading = static_cast<uint8_t>(object->GetHeading());
		transform_update.position = pos;
		object->NotifyObservers(&transform_update);
	}
	else
	{
		UpdateTransformWithParentMessage transform_update;
		transform_update.object_id = object->GetObjectId();
		transform_update.heading = static_cast<uint8_t>(object->GetHeading());
		transform_update.position = pos;
		transform_update.cell_id = object->GetContainer()->GetObjectId();
		object->NotifyObservers(&transform_update);
	}
}
void UpdateOrientation(std::shared_ptr<Object> object, glm::quat orientation)
{
	object->SetOrientation(orientation);

	if(object->GetContainer()->GetObjectId() == 0) {
		UpdateTransformMessage transform_update;
		transform_update.object_id = object->GetObjectId();
		transform_update.heading = static_cast<uint8_t>(object->GetHeading());
		transform_update.position = object->GetPosition();
		object->NotifyObservers(&transform_update);
	}
	else
	{
		UpdateTransformWithParentMessage transform_update;
		transform_update.object_id = object->GetObjectId();
		transform_update.heading = static_cast<uint8_t>(object->GetHeading());
		transform_update.position = object->GetPosition();
		transform_update.cell_id = object->GetContainer()->GetObjectId();
		object->NotifyObservers(&transform_update);
	}
}

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(addObjectOverload, AddObject, 2, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(transferObjectOverload, TransferObject, 3, 4)

struct ProsePackageWrapper : ProsePackage, wrapper<ProsePackage>
{
    ProsePackageWrapper() : ProsePackage(){}
};

void exportOutOfBand()
{
    enum_<ProseType>("ProseType", "Prose type of the :class:`.OutOfBand` Message")
        .value("TU", TU)
        .value("TT", TT)
        .value("TO", TO)
        .value("DI", DI)
        .value("DF", DF)
        ;
    class_<OutOfBand, boost::noncopyable>("OutOfBand","object that is used in the help with sending system stf messages")
        .def(init<std::string, std::string, ProseType, uint64_t>())
        .def(init<std::string, std::string, ProseType, std::wstring>())
        .def(init<std::string, std::string>())
    ;
}

void exportObject()
{
	enum_<controllers::FlyTextColor>("FlyTextColor", "Object that describes the different colors Fly Text Can be")
    .value("RED", controllers::RED)
    .value("GREEN", controllers::GREEN)
    .value("BLUE", controllers::BLUE)
    .value("WHITE", controllers::WHITE)
    .value("MIX", controllers::MIX)
    ;
	void (ContainerInterface::*RemoveObject)(shared_ptr<Object>, shared_ptr<Object>) = &ContainerInterface::RemoveObject;

	class_<ContainerInterface, std::shared_ptr<ContainerInterface>, boost::noncopyable>("ContainerInterface", "Container interface", no_init)
		.def("add", &ContainerInterface::AddObject, addObjectOverload(args("requester", "newObject", "arrangement_id"), "Adds an object to the current object"))
		.def("remove", RemoveObject, "Removes an object fomr the current object")
		.def("transfer", &ContainerInterface::TransferObject, transferObjectOverload(args("object", "newContainer", "arrangement_id"), "Transfer an object to a different object"))
		.def("swapSlots", &Object::SwapSlots, "Change an objects current arrangement")	
		.def("container", &Object::GetContainer, "Gets the :class:`ContainerInterface` object of the current object")
		.def_readonly("id", &ContainerInterface::GetObjectId, "Gets the object id of the container")
		;
	
    class_<Object, bases<ContainerInterface>, std::shared_ptr<Object>, boost::noncopyable>("Object", "The Base SWG Object that all Objects inherit from")
		.add_property("id", &Object::GetObjectId, &Object::SetObjectId, "Gets or sets The id of the object")
		.add_property("scene_id", &Object::GetSceneId, "Gets the scene id the object is in")
		.add_property("type", &Object::GetType, "Gets the type of the object")
		.add_property("position", &Object::GetPosition, UpdatePosition, "Gets and Sets the position of the object, using :class:`.Vec3`")
		.add_property("heading", &Object::GetHeading, "Gets the heading as an int of the object")
		.add_property("orientation", &Object::GetOrientation, UpdateOrientation, "Property to get or set the orientation of the object")
		.add_property("template", &Object::GetTemplate, &Object::SetTemplate, "the .iff file associated with this object"					)
		.add_property("volume", &Object::GetVolume, &Object::SetVolume, "Property to get or set the volume of the object (how much it can store)")
		.add_property("stf_name_file", &Object::GetStfNameFile, "gets the stf name file of the object")
		.add_property("stf_name_string", &Object::GetStfNameString, "gets the stf name file of the object")
		.def("stfName", &Object::SetStfName, "sets the full stf name, takes stf_name_file and stf_name_string as parameters")
		.add_property("custom_name", &Object::GetCustomName, &Object::SetCustomName, "Property to get and set the custom name")
        .def("controller", &Object::GetController, "Get the :class:`.ObjectController` of the object")
        .def("hasFlag", &Object::HasFlag, "Checks if the object has a specific flag set on it")
        .def("setFlag", &Object::SetFlag, "Sets a flag on the object")
        .def("removeFlag", &Object::RemoveFlag, "Removes a flag from the object")
		.def("hasAttribute", &Object::HasAttribute, "Returns true if the object has the given attribute.")
		.def("getFloatAttribute", &Object::GetAttribute<float>, "Gets the float attribute value")
		.def("setFloatAttribute", &Object::SetAttribute<float>, "Sets the float attribute value")
		.def("getIntAttribute", &Object::GetAttribute<int32_t>, "Gets the int attribute value")
		.def("setIntAttribute", &Object::SetAttribute<int32_t>, "Sets the int attribute value")
		.def("getStringAttribute", &Object::GetAttribute<wstring>, "Gets the string attribute value")
		.def("setStringAttribute", &Object::SetAttribute<wstring>, "sets the string attribute value")
		.add_property("attribute_template_id", &Object::GetAttributeTemplateId, &Object::SetAttributeTemplateId, "Gets and Sets the attribute template_id")
		.def("eventDispatcher", &Object::SetEventDispatcher, "Sets the event dispatcher pointer")
		.def("sendSystemMessage", SendSystemMessage1, "Send a system message to the requester, see :class:`")
		.def("sendSystemMessage", SendSystemMessage2, "Send a system message to the requester")
		.def("sendSystemMessage", SendSystemMessage3, "Send a system message to the requester")
		.def("sendSystemMessage", SendSystemMessage4, "Send a system message to the requester")
		.def("sendFlyText", SendFlyText, "Sends Fly Text to the player, see :class:`.FlyTextColor`")
		.def("updatePosition", &Object::UpdatePosition, "Updates the position and sends an update to the player")
		;

	implicitly_convertible<std::shared_ptr<Object>, std::shared_ptr<ContainerInterface>>();
}
