// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "swganh/object/static/static.h"

using namespace std;
using namespace swganh::object;
using namespace swganh::object::static_object;

uint32_t Static::GetType() const
{ 
    return Static::type; 
}
