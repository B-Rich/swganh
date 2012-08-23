// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "crafting_tool_attribute_template.h"

#include <sstream>

#include "anh/event_dispatcher.h"
#include "swganh/object/tangible/tangible.h"

using namespace std;
using namespace anh;
using namespace swganh::object;
using namespace swganh::messages;
using namespace swganh_core::attributes;

CraftingToolAttributeTemplate::CraftingToolAttributeTemplate(anh::EventDispatcher* dispatcher)
	: BaseAttributeTemplate(dispatcher)
{
	RegisterEventHandlers();
}

swganh::messages::AttributeListMessage CraftingToolAttributeTemplate::BuildAttributeTemplate(shared_ptr<Object> object)
{
	uint64_t object_id = object->GetObjectId();
	if (HasAttributeListMessage(object_id))
		return object_attribute_list_messages_[object_id];

	swganh::messages::AttributeListMessage attribute_list_message;
	
	std::vector<Attribute> attribue_list;
	attribute_list_message.object_id = object->GetObjectId();

	// condition is special
	auto tano = static_pointer_cast<tangible::Tangible>(object);
	std::wstring condition = object->GetAttributeAsString("condition");
	wstringstream ss;
	if (tano)
	{
		ss << tano->GetCondition() << L"/" << tano->GetMaxCondition();
		condition = ss.str();
		object->SetAttribute<wstring>("condition", condition);
	}
    
	attribue_list.push_back(Attribute("@obj_attr_n:original_name", object->GetAttributeAsString("original_name")));
	attribue_list.push_back(Attribute("@obj_attr_n:condition", condition));
	attribue_list.push_back(Attribute("@obj_attr_n:volume", object->GetAttributeAsString("volume")));
    attribue_list.push_back(Attribute("@obj_attr_n:craft_tool_effectiveness", object->GetAttributeAsString("craft_tool_effectiveness")));
    attribue_list.push_back(Attribute("@obj_attr_n:craft_tool_status", object->GetAttributeAsString("craft_tool_status")));
    attribue_list.push_back(Attribute("@obj_attr_n:crafter", object->GetAttributeAsString("crafter")));
	attribue_list.push_back(Attribute("@obj_attr_n:serial_number", object->GetAttributeAsString("serial_number")));
	attribute_list_message.attributes = move(attribue_list);

	object_attribute_list_messages_[object_id] = move(attribute_list_message);
	return attribute_list_message;
}

