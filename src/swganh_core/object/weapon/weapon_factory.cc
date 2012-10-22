// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "weapon_factory.h"

#include "swganh_core/object/weapon/weapon.h"

using namespace std;
using namespace swganh::object;
using namespace swganh::object;

WeaponFactory::WeaponFactory(swganh::app::SwganhKernel* kernel)
	: TangibleFactory(kernel)
{
}

void WeaponFactory::PersistChangedObjects()
{
	std::set<shared_ptr<Object>> persisted;
	{
		boost::lock_guard<boost::mutex> lg(persisted_objects_mutex_);
		persisted = move(persisted_objects_);
	}
	for (auto& object : persisted)
	{
		if(object->IsDatabasePersisted())
			PersistObject(object);
	}
}

uint32_t WeaponFactory::PersistObject(const shared_ptr<Object>& object)
{
	return 1;
}

void WeaponFactory::DeleteObjectFromStorage(const shared_ptr<Object>& object)
{
	ObjectFactory::DeleteObjectFromStorage(object);
}

shared_ptr<Object> WeaponFactory::CreateObjectFromStorage(uint64_t object_id)
{
    return make_shared<Weapon>();
}

shared_ptr<Object> WeaponFactory::CreateObject()
{
    return make_shared<Weapon>();
}
