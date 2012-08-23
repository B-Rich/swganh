// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "armor_attribute_template.h"

#include <sstream>

#include "anh/event_dispatcher.h"
#include "swganh/object/tangible/tangible.h"

using namespace std;
using namespace anh;
using namespace swganh::object;
using namespace swganh::messages;
using namespace swganh_core::attributes;

ArmorAttributeTemplate::ArmorAttributeTemplate(anh::EventDispatcher* dispatcher)
	: AttributeTemplateInterface(dispatcher)
{
	RegisterEventHandlers();
}
void ArmorAttributeTemplate::RegisterEventHandlers()
{
	event_dispatcher_->Subscribe("Object::UpdateAttribute", [this](const shared_ptr<EventInterface>& incoming_event)
	{
		const auto& object = static_pointer_cast<ObjectEvent>(incoming_event)->Get();
		
		// Clear out attributes if they have been updated
		if (HasAttributeListMessage(object->GetObjectId()))
			object_attribute_list_messages_[object->GetObjectId()].attributes.clear();
	});
}
bool ArmorAttributeTemplate::HasAttributeListMessage(uint64_t object_id)
{
	bool hasMessage = false;
	auto found = find_if(object_attribute_list_messages_.begin(), object_attribute_list_messages_.end(),[object_id](ObjectMapAttributeListMessages::value_type entry)
	{
		return entry.first == object_id;
	});
	if (found != object_attribute_list_messages_.end())
	{
		if (found->second.attributes.size() > 0)
		{
			hasMessage = true;
		}
	}
	return hasMessage;
}
swganh::messages::AttributeListMessage ArmorAttributeTemplate::BuildAttributeTemplate(shared_ptr<Object> object)
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

	attribue_list.push_back(Attribute("original_name", object->GetAttributeAsString("original_name")));
	attribue_list.push_back(Attribute("condition", condition));
	attribue_list.push_back(Attribute("volume", object->GetAttributeAsString("volume")));
	attribue_list.push_back(Attribute("sockets", object->GetAttributeAsString("sockets")));
	attribue_list.push_back(Attribute("armor_rating", object->GetAttributeAsString("armor_rating")));
	attribue_list.push_back(Attribute("cat_armor_special_protection", L""));
	attribue_list.push_back(Attribute("armor_eff_kinetic", object->GetAttributeAsString("cat_armor_special_protection.armor_eff_kinetic")));
	attribue_list.push_back(Attribute("armor_eff_energy", object->GetAttributeAsString("cat_armor_special_protection.armor_eff_energy")));
	attribue_list.push_back(Attribute("armor_eff_blast", object->GetAttributeAsString("cat_armor_special_protection.armor_eff_blast")));
	attribue_list.push_back(Attribute("armor_eff_stun", object->GetAttributeAsString("cat_armor_special_protection.armor_eff_stun")));
	attribue_list.push_back(Attribute("armor_eff_elemental_heat", object->GetAttributeAsString("cat_armor_special_protection.armor_eff_elemental_heat")));
	attribue_list.push_back(Attribute("armor_eff_elemental_cold", object->GetAttributeAsString("cat_armor_special_protection.armor_eff_elemental_cold")));
	attribue_list.push_back(Attribute("armor_eff_elemental_acid", object->GetAttributeAsString("cat_armor_special_protection.armor_eff_elemental_acid")));
	attribue_list.push_back(Attribute("armor_eff_elemental_electrical", object->GetAttributeAsString("cat_armor_special_protection.armor_eff_elemental_electrical")));
	attribue_list.push_back(Attribute("armor_eff_restraint", object->GetAttributeAsString("cat_armor_special_protection.armor_eff_restraint")));
	attribue_list.push_back(Attribute("cat_armor_effectiveness", L""));
	attribue_list.push_back(Attribute("armor_eff_kinetic", object->GetAttributeAsString("cat_armor_effectiveness.armor_eff_kinetic")));
	attribue_list.push_back(Attribute("armor_eff_energy", object->GetAttributeAsString("cat_armor_effectiveness.armor_eff_energy")));
	attribue_list.push_back(Attribute("armor_eff_blast", object->GetAttributeAsString("cat_armor_effectiveness.armor_eff_blast")));
	attribue_list.push_back(Attribute("armor_eff_stun", object->GetAttributeAsString("cat_armor_effectiveness.armor_eff_stun")));
	attribue_list.push_back(Attribute("armor_eff_elemental_heat", object->GetAttributeAsString("cat_armor_effectiveness.armor_eff_elemental_heat")));
	attribue_list.push_back(Attribute("armor_eff_elemental_cold", object->GetAttributeAsString("cat_armor_effectiveness.armor_eff_elemental_cold")));
	attribue_list.push_back(Attribute("armor_eff_elemental_acid", object->GetAttributeAsString("cat_armor_effectiveness.armor_eff_elemental_acid")));
	attribue_list.push_back(Attribute("armor_eff_elemental_electrical", object->GetAttributeAsString("cat_armor_effectiveness.armor_eff_elemental_electrical")));
	attribue_list.push_back(Attribute("armor_eff_restraint", object->GetAttributeAsString("cat_armor_effectiveness.armor_eff_restraint")));
	attribue_list.push_back(Attribute("cat_armor_effectiveness", L""));
	attribue_list.push_back(Attribute("armor_eff_kinetic", object->GetAttributeAsString("cat_armor_vulnerability.armor_eff_kinetic")));
	attribue_list.push_back(Attribute("armor_eff_energy", object->GetAttributeAsString("cat_armor_vulnerability.armor_eff_energy")));
	attribue_list.push_back(Attribute("armor_eff_blast", object->GetAttributeAsString("cat_armor_vulnerability.armor_eff_blast")));
	attribue_list.push_back(Attribute("armor_eff_stun", object->GetAttributeAsString("cat_armor_vulnerability.armor_eff_stun")));
	attribue_list.push_back(Attribute("armor_eff_elemental_heat", object->GetAttributeAsString("cat_armor_vulnerability.armor_eff_elemental_heat")));
	attribue_list.push_back(Attribute("armor_eff_elemental_cold", object->GetAttributeAsString("cat_armor_vulnerability.armor_eff_elemental_cold")));
	attribue_list.push_back(Attribute("armor_eff_elemental_acid", object->GetAttributeAsString("cat_armor_vulnerability.armor_eff_elemental_acid")));
	attribue_list.push_back(Attribute("armor_eff_elemental_electrical", object->GetAttributeAsString("cat_armor_vulnerability.armor_eff_elemental_electrical")));
	attribue_list.push_back(Attribute("armor_eff_restraint", object->GetAttributeAsString("cat_armor_vulnerability.armor_eff_restraint")));
	attribue_list.push_back(Attribute("cat_armor_encumbrance", L""));
	attribue_list.push_back(Attribute("armor_health_encumbrance", object->GetAttributeAsString("cat_armor_encumbrance.armor_action_encumbrance")));
	attribue_list.push_back(Attribute("armor_action_encumbrance", object->GetAttributeAsString("cat_armor_encumbrance.armor_action_encumbrance")));
	attribue_list.push_back(Attribute("armor_mind_encumbrance", object->GetAttributeAsString("cat_armor_encumbrance.armor_mind_encumbrance")));
	attribue_list.push_back(Attribute("crafter", object->GetAttributeAsString("crafter")));
	attribue_list.push_back(Attribute("serial_number", object->GetAttributeAsString("serial_number")));
	attribute_list_message.attributes = move(attribue_list);

	object_attribute_list_messages_[object_id] = move(attribute_list_message);
	return attribute_list_message;
}

