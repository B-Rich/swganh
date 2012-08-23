// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "swganh/object/installation/harvester_installation_factory.h"

#include "swganh/object/installation/harvester_installation.h"

using namespace std;
using namespace swganh::object;
using namespace swganh::object::installation;

uint32_t HarvesterInstallationFactory::PersistObject(const shared_ptr<Object>& object)
{
	uint32_t counter = 1;
	
	return counter;
}

void HarvesterInstallationFactory::DeleteObjectFromStorage(const shared_ptr<Object>& object)
{}

shared_ptr<Object> HarvesterInstallationFactory::CreateObjectFromStorage(uint64_t object_id)
{
    return make_shared<Installation>();
}

shared_ptr<Object> HarvesterInstallationFactory::CreateObjectFromTemplate(const string& template_name, bool db_persisted, bool db_initialized)
{
    return make_shared<Installation>();
}
