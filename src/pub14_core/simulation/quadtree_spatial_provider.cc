// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "quadtree_spatial_provider.h"

#include "anh/logger.h"

#include "swganh/object/object.h"

using std::shared_ptr;

using namespace anh::observer;
using namespace swganh::object;
using namespace swganh_core::simulation;
using namespace quadtree;

QuadtreeSpatialProvider::QuadtreeSpatialProvider()
	: root_node_(ROOT, Region(Point(-8300.0f, -8300.0f), Point(8300.0f, 8300.0f)), 0, 9, nullptr)
{
}

QuadtreeSpatialProvider::~QuadtreeSpatialProvider(void)
{
	__this.reset();
}

struct comp
{
	bool operator() (const std::shared_ptr<ObserverInterface>& lhs, const std::shared_ptr<ObserverInterface>& rhs)
	{ 
		return lhs->GetId() < rhs->GetId(); 
	}
};

void QuadtreeSpatialProvider::AddObject(shared_ptr<Object> object)
{
	LOG(warning) << "QUADTREE AddObject " << object->GetObjectId();
	root_node_.InsertObject(object);
	object->SetContainer(__this);
	
	// Make objects aware
	ViewObjects(0, true, [&](shared_ptr<Object> found_object){
		found_object->AddAwareObject(object->GetController());
		object->AddAwareObject(found_object->GetController());
	}, object);
}

void QuadtreeSpatialProvider::RemoveObject(shared_ptr<Object> object)
{
	LOG(warning) << "QUADTREE RemoveObject " << object->GetObjectId();
	root_node_.RemoveObject(object);
	object->SetContainer(nullptr);

    ViewObjects(0, false, [&](shared_ptr<Object> found_object){
		found_object->RemoveAwareObject(object->GetController());
		object->RemoveAwareObject(found_object->GetController());
	}, object);
}

void QuadtreeSpatialProvider::UpdateObject(shared_ptr<Object> obj, glm::vec3 old_position, glm::vec3 new_position)
{
	LOG(warning) << "QUADTREE UpdateObject " << obj->GetObjectId();
	root_node_.UpdateObject(obj, old_position, new_position);
}

void QuadtreeSpatialProvider::TransferObject(std::shared_ptr<Object> object, std::shared_ptr<ContainerInterface> newContainer)
{
	LOG(warning) << "QUADTREE TRANSFER " << object->GetObjectId() << " FROM " << this->GetObjectId() << " TO " << newContainer->GetObjectId();
	//Perform the transfer
	if (object != newContainer)
	{
		root_node_.RemoveObject(object);
		newContainer->__InternalInsert(object);

		//Split into 3 groups -- only ours, only new, and both ours and new
		std::set<std::shared_ptr<ObserverInterface>, comp> oldObservers, newObservers, bothObservers;

		object->ViewAwareObjects([&] (std::shared_ptr<ObserverInterface>& observer) {
			oldObservers.insert(observer);
		});

		newContainer->ViewAwareObjects([&] (std::shared_ptr<ObserverInterface>& observer) {
			auto itr = oldObservers.find(observer);
			if(itr == oldObservers.end()) {
				oldObservers.erase(itr);
				bothObservers.insert(observer);
			} else {
				newObservers.insert(observer);
			}
		});

		//Send Creates to only new
		for(auto& observer : newObservers) {
			object->AddAwareObject(observer);
		}

		//Send updates to both
		for(auto& observer : bothObservers) {
			object->SendUpdateContainmentMessage(observer);
		}

		//Send destroys to only ours
		for(auto& observer : oldObservers) {
			object->RemoveAwareObject(observer);
		}
	}
}

void QuadtreeSpatialProvider::ViewObjects(uint32_t max_depth, bool topDown, std::function<void(std::shared_ptr<Object>)> func, std::shared_ptr<Object> hint)
{
	LOG(warning) << "QUADTREE VIEW OBJECTS ";
	std::vector<std::shared_ptr<Object>> contained_objects;
	if (hint)
	{
		contained_objects = root_node_.Query(GetQueryBoxViewRange(hint));
	}
	else
	{
		contained_objects = root_node_.GetContainedObjects();
	}

	for (auto& object : contained_objects)
	{
		if (topDown)
			func(object);

		if (max_depth != 1)
			object->ViewObjects((max_depth == 0 ? 0 : max_depth - 1), topDown, func);

		if (!topDown)
			func(object);
	}
}

void QuadtreeSpatialProvider::__InternalInsert(std::shared_ptr<Object> object)
{
	LOG(warning) << "QUADTREE __InternalInsert " << object->GetObjectId();

	root_node_.InsertObject(object);
	object->SetContainer(__this);
}

QueryBox QuadtreeSpatialProvider::GetQueryBoxViewRange(std::shared_ptr<Object> object)
{
	auto position = object->GetPosition();
	return QueryBox(Point(position.x - 256, position.y + 256), Point(position.x + 256, position.y - 256));
}