// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "swganh/object/harvester_installation/harvester_installation.h"

using namespace swganh::object::harvester_installation;

HarvesterInstallation::HarvesterInstallation()
	: Installation()
{
}

uint32_t HarvesterInstallation::GetType() const
{ 
    return HarvesterInstallation::type; 
}
