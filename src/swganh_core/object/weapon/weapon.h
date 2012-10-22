// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include "swganh_core/object/tangible/tangible.h"

namespace swganh {
namespace object {

class WeaponFactory;
class WeaponMessageBuilder;
enum WeaponType {
	MELEE = 0,
	RANGED
};
class Weapon : public swganh::object::Tangible
{
public:
	typedef WeaponFactory FactoryType;
    typedef WeaponMessageBuilder MessageBuilderType;
    Weapon();
	WeaponType GetWeaponType() { return weapon_type_; }
	// WEAO
    virtual uint32_t GetType() const;
    const static uint32_t type = 0x6AAC0CFE;    
private:
	WeaponType weapon_type_;
	
	virtual std::shared_ptr<Object> Clone();
	void Clone(std::shared_ptr<Weapon> other);
};
    
}}  // namespace swganh::object
