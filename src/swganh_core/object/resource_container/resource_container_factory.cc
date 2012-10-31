// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "resource_container_factory.h"
#include "resource_container.h"

using namespace std;
using namespace swganh::object;
using namespace swganh::object;

ResourceContainerFactory::ResourceContainerFactory(swganh::app::SwganhKernel* kernel)
	: TangibleFactory(kernel)
{
}

uint32_t ResourceContainerFactory::PersistObject(const shared_ptr<Object>& object, bool persist_inherited)
{
	uint32_t counter = 1;
	return counter;
}

void ResourceContainerFactory::DeleteObjectFromStorage(const shared_ptr<Object>& object)
{
	ObjectFactory::DeleteObjectFromStorage(object);
}

shared_ptr<Object> ResourceContainerFactory::CreateObjectFromStorage(uint64_t object_id)
{
    return make_shared<ResourceContainer>();
}

shared_ptr<Object> ResourceContainerFactory::CreateObject()
{
    return make_shared<ResourceContainer>();
}
