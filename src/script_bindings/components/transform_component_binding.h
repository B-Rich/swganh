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
#ifndef ZONE_TRANSFORM_COMPONENT_BINDING__H_
#define ZONE_TRANSFORM_COMPONENT_BINDING__H_

#include "base_component_binding.h"
#include <zone/components/transform_component.h>

using namespace zone::components;
using namespace std;
// This creates an opaque pointer. It can be extended to expose members of any objects, 
// or used as is to return opaque references to objects. For opaque references, the module 
// must still be imported by the Python app. If anh_python.pyd is in a package directory, 
// importing it in the __init__.py file in that directory seems to be a simple, workable solution.
namespace boost {
namespace python {
        template <class T> struct pointee< shared_ptr<T> > {
            typedef T type; 
        };
} // namespace python
} // namespace boost

namespace anh_python { namespace components {

class TransformComponentBinding : public TransformComponent, public wrapper<TransformComponent>
{
    public:
    TransformComponentBinding(const ObjectId& id) : TransformComponent(id) {}
    TransformComponentBinding(const ObjectId& id, const glm::vec3& position, const glm::quat& rotation, const float speed)
        : TransformComponent(id, position, rotation, speed) {}
};
void define_class_transform_component() {
    
    // overloads
    const ObjectId      (TransformComponent::*get_parent_id)(void)              = &TransformComponent::parent_id; 
    void                (TransformComponent::*set_parent_id)(const ObjectId)    = &TransformComponent::parent_id;
    const glm::vec3&    (TransformComponent::*get_pos)(void)                    = &TransformComponent::position;
    void                (TransformComponent::*set_pos)(const glm::vec3&)        = &TransformComponent::position;
    void (TransformComponent::*set_pos3)(const float, const float, const float) = &TransformComponent::position;
    const glm::quat&    (TransformComponent::*get_rot)(void)                    = &TransformComponent::rotation;
    void                (TransformComponent::*set_rot)(const glm::quat&)        = &TransformComponent::rotation;
    void (TransformComponent::*set_rot4)(const float, const float, const float, const float) = &TransformComponent::rotation;
    const float         (TransformComponent::*get_speed)(void)                  = &TransformComponent::speed;
    void                (TransformComponent::*set_speed)(const float)           = &TransformComponent::speed;
    
    // TODO: add way to get internal TransformComponent based on id
    class_<TransformComponent, boost::noncopyable>("TransformComponent",
        "A component controlling everything about an entities position in the world. \n"
        "@note: It is almost always prefered to get this object from an existing entity Id. "
        "Components use the ObjectManager to get a shared_ptr reference to the existing TransformComponent "
        "which relates to the specific ID.",
        init<const ObjectId>())
        .def(init< const ObjectId, const glm::vec3&, const glm::quat&, const float >())
        .def("object_id", &TransformComponent::object_id, return_value_policy<copy_const_reference>())
        .def("parent_id", get_parent_id)
        .def("parent_id", set_parent_id)
        .def("position", get_pos, return_internal_reference<>(),
        "Gets a L{glm::vec3} of the current position, @returns internal reference.")
        .def("position", set_pos)
        .def("position", set_pos3,
        "Sets position L{glm::vec3} by passing in 3 floats representing x,y,z coordinates of the entity")
        .def("rotation", get_rot, return_internal_reference<>(),
            "Gets a L{glm::quat} of the current entities rotation, @returns internal reference.")
        .def("rotation", set_rot)
        .def("rotation", set_rot4,
            "Sets entities rotation L{glm::quat} by passing in 4 floats representing w,x,y,z rotation of the entity")
        .def("speed", get_speed)
        .def("speed", set_speed)
        .def("rotate", &TransformComponent::rotate)
        .def("rotate_left", &TransformComponent::rotate_left)
        .def("rotate_right", &TransformComponent::rotate_right)
        .def("face", &TransformComponent::face)
        .def("move", &TransformComponent::move)
        .def("move_forward", &TransformComponent::move_forward)
        .def("move_back", &TransformComponent::move_back)
        .def("rotation_angle", &TransformComponent::rotation_angle)
        .def("HandleMessage", &TransformComponent::HandleMessage)
        ;
}
void define_class_transform_message()
{
    class_<shared_ptr<TransformMessage> >("TransformMessagePtr", no_init)
        .def("init", &TransformMessage::createTransformMessage);

    class_<TransformMessage >("TransformMessage", no_init)
        .def("init", &TransformMessage::createTransformMessage)
        .staticmethod("init")
        .def("parent_id", &TransformMessage::parent_id)
        .def("position", &TransformMessage::position, return_value_policy<copy_const_reference>())
        .def("rotation", &TransformMessage::rotation, return_value_policy<copy_const_reference>())
        .def("speed", &TransformMessage::speed)
        ;
}
} // components
} // anh_python
#endif // ZONE_TRANSFORM_COMPONENT_BINDING__H_