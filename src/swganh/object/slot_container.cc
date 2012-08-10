#include "slot_container.h"
#include "object.h"

using namespace swganh::object;

std::shared_ptr<swganh::object::Object> SlotContainer::insert_object(std::shared_ptr<swganh::object::Object> insertObject)
{
	held_objects_.insert(insertObject);
	return nullptr;
}

void SlotContainer::remove_object(std::shared_ptr<swganh::object::Object> removeObject)
{
	auto itr = held_objects_.find(removeObject);
	if(itr != held_objects_.end())
	{
		held_objects_.erase(itr);
	}
}

void SlotContainer::view_objects(std::function<void(std::shared_ptr<swganh::object::Object>&)> walkerFunction)
{
	for_each(held_objects_.begin(), held_objects_.end(), walkerFunction);
}