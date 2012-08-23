// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "weapon_attribute_template.h"

#include <sstream>

#include "anh/event_dispatcher.h"
#include "swganh/object/tangible/tangible.h"

using namespace std;
using namespace anh;
using namespace swganh::object;
using namespace swganh::messages;
using namespace swganh_core::attributes;

WeaponAttributeTemplate::WeaponAttributeTemplate(anh::EventDispatcher* dispatcher)
	: BaseAttributeTemplate(dispatcher)
{
	RegisterEventHandlers();
}

swganh::messages::AttributeListMessage WeaponAttributeTemplate::BuildAttributeTemplate(shared_ptr<Object> object)
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
    attribue_list.push_back(Attribute("@obj_attr_n:weapon_cert_status", object->GetAttributeAsString("weapon_cert_status")));
	attribue_list.push_back(Attribute("@obj_attr_n:condition", condition));
	attribue_list.push_back(Attribute("@obj_attr_n:volume", object->GetAttributeAsString("volume")));
	attribue_list.push_back(Attribute("@obj_attr_n:crafter", object->GetAttributeAsString("crafter")));
	attribue_list.push_back(Attribute("@obj_attr_n:serial_number", object->GetAttributeAsString("serial_number")));
    attribue_list.push_back(Attribute("@obj_attr_n:wpn_armor_pierce_rating", object->GetAttributeAsString("wpn_armor_pierce_rating")));
    attribue_list.push_back(Attribute("@obj_attr_n:wpn_attack_speed", object->GetAttributeAsString("wpn_attack_speed")));
    attribue_list.push_back(Attribute("cat_wpn_damage.@obj_attr_n:cat_wpn_damage", object->GetAttributeAsString("cat_wpn_damage.wpn_damage_type")));
    attribue_list.push_back(Attribute("cat_wpn_damage.@obj_attr_n:wpn_damage_min", object->GetAttributeAsString("cat_wpn_damage.wpn_damage_min")));
    attribue_list.push_back(Attribute("cat_wpn_damage.@obj_attr_n:wpn_damage_max", object->GetAttributeAsString("cat_wpn_damage.wpn_damage_max")));
    attribue_list.push_back(Attribute("cat_wpn_damage.@obj_attr_n:wpn_wound_chance", object->GetAttributeAsString("cat_wpn_damage.wpn_wound_chance")));
    attribue_list.push_back(Attribute("cat_wpn_rangemods.@obj_attr_n:wpn_range_zero", object->GetAttributeAsString("cat_wpn_rangemods.wpn_range_zero")));
    attribue_list.push_back(Attribute("cat_wpn_rangemods.@obj_attr_n:wpn_range_mid", object->GetAttributeAsString("cat_wpn_rangemods.wpn_range_mid")));
    attribue_list.push_back(Attribute("cat_wpn_rangemods.@obj_attr_n:wpn_range_max", object->GetAttributeAsString("cat_wpn_rangemods.wpn_range_max")));
    attribue_list.push_back(Attribute("cat_wpn_attack_cost.@obj_attr_n:wpn_attack_cost_health", object->GetAttributeAsString("cat_wpn_attack_cost.wpn_attack_cost_health")));
    attribue_list.push_back(Attribute("cat_wpn_attack_cost.@obj_attr_n:wpn_attack_cost_action", object->GetAttributeAsString("cat_wpn_attack_cost.wpn_attack_cost_action")));
    attribue_list.push_back(Attribute("cat_wpn_attack_cost.@obj_attr_n:wpn_attack_cost_mind", object->GetAttributeAsString("cat_wpn_attack_cost.wpn_attack_cost_mind")));
	attribute_list_message.attributes = move(attribue_list);

	object_attribute_list_messages_[object_id] = move(attribute_list_message);
	return attribute_list_message;
}

