/*
 This file is part of SWGANH. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2012 The SWG:ANH Team

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "node.h"

#include <swganh/object/object.h>

namespace quadtree
{

Node::Node(NodeQuadrant quadrant, Region region, uint32_t level, uint32_t max_level)
	: quadrant_(quadrant)
	, region_(region)
	, level_(level)
	, max_level_(max_level)
	, state_(LEAF)
{
	// If this is the root node, we need to do a manual split.
	if(quadrant_ == ROOT)
		Split();
}

Node::~Node(void)
{
}

void Node::InsertObject(std::shared_ptr<swganh::object::Object> obj)
{
	if(objects_.size() >= 1 && level_ < max_level_ && state_ == LEAF)
	{
		Split();
	}

	bool success = false;

	if(state_ == BRANCH)
	{
		std::for_each(leaf_nodes_.begin(), leaf_nodes_.end(), [=, &obj, &success](std::shared_ptr<Node> node){
			if(boost::geometry::within( Point(obj->GetPosition().x, obj->GetPosition().y) , node->GetRegion()))
			{
				node->InsertObject(obj);
				success = true;
				return;
			}
		});
	}

	if(success)
		return;

	objects_.push_back(obj);
}

void Node::RemoveObject(std::shared_ptr<swganh::object::Object> obj)
{
	for(auto i = objects_.begin(); i != objects_.end(); )
	{
		if(obj->GetObjectId() == (*i)->GetObjectId())
		{
			i = objects_.erase(i);
			return;
		}
		i++;
	}

	if(state_ == BRANCH)
	{
		Point obj_point(obj->GetPosition().x, obj->GetPosition().y);
		for(std::shared_ptr<Node> node : leaf_nodes_)
		{
			if(boost::geometry::within(obj_point, node->GetRegion()))
			{
				node->RemoveObject(obj);
				return;
			}
		}
	}

}

void Node::Split()
{
	if(state_ == BRANCH)
		return;

	state_ = BRANCH;

	Point center((region_.min_corner().x() + region_.max_corner().x()) / 2, (region_.min_corner().y() + region_.max_corner().y()) / 2);
	Point upper_center((region_.min_corner().x() + region_.max_corner().x()) / 2, region_.min_corner().y());
	Point left_center(region_.min_corner().x(), (region_.min_corner().y() + region_.max_corner().y()) / 2);
	Point right_center(region_.max_corner().x(), (region_.min_corner().y() + region_.max_corner().y()) / 2);
	Point bottom_center((region_.min_corner().x() + region_.max_corner().x()) / 2, region_.max_corner().y());

	leaf_nodes_[NW_QUADRANT] = std::make_shared<Node>(NW_QUADRANT, Region(region_.min_corner(), center), level_ + 1, max_level_);
	leaf_nodes_[NE_QUADRANT] = std::make_shared<Node>(NE_QUADRANT, Region(upper_center, right_center), level_ + 1, max_level_);
	leaf_nodes_[SW_QUADRANT] = std::make_shared<Node>(SW_QUADRANT, Region(left_center, bottom_center), level_ + 1, max_level_);
	leaf_nodes_[SE_QUADRANT] = std::make_shared<Node>(SE_QUADRANT, Region(center, region_.max_corner()), level_ + 1, max_level_);

	for(auto i = objects_.begin(); i != objects_.end();)
	{
		auto obj = (*i);
		bool success = false;
		for(std::shared_ptr<Node> node : leaf_nodes_)
		{
			//std::cout << "Trying to move!" << std::endl;
			//std::cout << "Node Level: " << node->GetLevel() << std::endl;
			//std::cout << "Object " << obj->GetObjectId() << " @ " << obj->GetPosition().x << "," << obj->GetPosition().y << std::endl;
			//std::cout << "Region: (" << node->GetRegion().min_corner().x() << "," << node->GetRegion().min_corner().y() << ") (" << node->GetRegion().max_corner().x() << "," << node->GetRegion().max_corner().y() << ")" << std::endl;
			//std::cout << "Within: " << boost::geometry::within(Point(obj->GetPosition().x, obj->GetPosition().y) , node->GetRegion()) << std::endl;
			if(boost::geometry::within(Point(obj->GetPosition().x, obj->GetPosition().y) , node->GetRegion()))
			{
				i = objects_.erase(i);
				node->InsertObject(std::move(obj));
				success = true;
				break;
			}
		}

		if(!success)
			i++;
	}
}

std::vector<std::shared_ptr<swganh::object::Object>> Node::Query(QueryBox query_box)
{
	std::vector<std::shared_ptr<swganh::object::Object>> return_list;

	std::for_each(objects_.begin(), objects_.end(), [=,& return_list](std::shared_ptr<swganh::object::Object> obj) {
		if(boost::geometry::within(Point(obj->GetPosition().x, obj->GetPosition().y), query_box))
			return_list.push_back(obj);
	});

	if(state_ == BRANCH)
	{
		for(std::shared_ptr<Node> node : leaf_nodes_)
		{
			// Node is within Query Box.
			if(boost::geometry::within(node->GetRegion(), query_box))
			{
				auto contained_objects = node->GetContainedObjects();
				return_list.insert( return_list.end(), contained_objects.begin(), contained_objects.end() );
				continue;
			}
			
			// Query Box is within node.
			if(boost::geometry::within(query_box, node->GetRegion()))
			{
				std::vector<std::shared_ptr<swganh::object::Object>> list = node->Query(query_box);
				return_list.insert( return_list.end(), list.begin(), list.end() );
				break;
			}

			// Query Box intersects with node.
			if(boost::geometry::intersects(query_box, node->GetRegion()))
			{
				std::vector<std::shared_ptr<swganh::object::Object>> list = node->Query(query_box);
				return_list.insert( return_list.end(), list.begin(), list.end() );
			}
		}
	}

	return return_list;
}

const std::vector<std::shared_ptr<swganh::object::Object>> Node::GetContainedObjects(void)
{
	std::vector<std::shared_ptr<swganh::object::Object>> objs;

	objs.insert(objs.end(), objects_.begin(), objects_.end());

	if(state_ == BRANCH)
	{
		for(const std::shared_ptr<Node> node : leaf_nodes_)
		{
			std::vector<std::shared_ptr<swganh::object::Object>> objs2 = node->GetContainedObjects();
			objs.insert(objs.end(), objs2.begin(), objs2.end());
		}
	}

	return objs;
}

} // namespace quadtree