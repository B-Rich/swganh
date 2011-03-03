/*
---------------------------------------------------------------------------------------
This source file is part of SWG:ANH (Star Wars Galaxies - A New Hope - Server Emulator)

For more information, visit http://www.swganh.com

Copyright (c) 2006 - 2011 The SWG:ANH Team
---------------------------------------------------------------------------------------
Use of this source code is governed by the GPL v3 license that can be found
in the COPYING file or at http://www.gnu.org/licenses/gpl-3.0.html

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,a
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
---------------------------------------------------------------------------------------
*/
#include <iostream>
#include "transform_component.h"

using namespace std;
namespace zone { namespace components {

// statics
std::shared_ptr<NullTransformComponent> TransformComponentInterface::NullComponent = std::shared_ptr<NullTransformComponent>(new NullTransformComponent());
ComponentInfo NullTransformComponent::component_info_ = ComponentInfo(ComponentType("NullTransformComponent"), false);
ComponentInfo TransformComponent::component_info_ = ComponentInfo(ComponentType("TransformComponent"), true);

TransformComponent::TransformComponent(const ObjectId& id)
: TransformComponentInterface(id)
{}
void TransformComponent::Init(boost::property_tree::ptree& pt) {
    // initial default values
    parent_id_ = pt.get<ObjectId>("parent_id", 0); 
	position_.x = pt.get<float>("position.x", 0.0f);
	position_.y = pt.get<float>("position.y", 0.0f);
	position_.z = pt.get<float>("position.z", 0.0f);
	rotation_.x = pt.get<float>("rotation.x", 0.0f);
	rotation_.y = pt.get<float>("rotation.y", 0.0f);
	rotation_.z = pt.get<float>("rotation.z", 0.0f);
	rotation_.w = pt.get<float>("rotation.w", 1.0f);

}

void TransformComponent::HandleMessage(const Message message) {
    std::shared_ptr<TransformMessage> transform = std::dynamic_pointer_cast<TransformMessage>(message);
    
    parent_id(transform->parent_id());
    position(transform->position());
    rotation(transform->rotation());
    speed(transform->speed());
}
} // namespace zone
} // namespace components