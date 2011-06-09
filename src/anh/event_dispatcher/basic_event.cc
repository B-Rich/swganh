/*
 This file is part of MMOServer. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2010 The SWG:ANH Team

 MMOServer is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 MMOServer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with MMOServer.  If not, see <http://www.gnu.org/licenses/>.
*/
 
#include "basic_event.h"
 
using namespace anh::event_dispatcher;
 
SimpleEvent anh::event_dispatcher::make_event(EventType type) {
    SimpleEvent created_event = make_event(type, NullEventData());
    return created_event;
}

std::shared_ptr<SimpleEvent> anh::event_dispatcher::make_shared_event(EventType type) {
    auto created_event = std::allocate_shared<SimpleEvent>(
        tbb::scalable_allocator<SimpleEvent>(), 
        type
    );

    return created_event;
}
