// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "swganh/object/weapon/weapon.h"

#include "swganh_core/messages/deltas_message.h"

using namespace std;
using namespace swganh::messages;
using namespace swganh::object;
using namespace swganh::object::weapon;

uint32_t Weapon::GetType() const 
{ 
	return Weapon::type; 
}