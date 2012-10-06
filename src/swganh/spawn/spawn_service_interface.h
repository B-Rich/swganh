#ifndef SWGANH_SPAWN_SERVICE_INTERFACE_H_
#define SWGANH_SPAWN_SERVICE_INTERFACE_H_

#include <swganh/service/service_interface.h>

namespace swganh
{
namespace object
{
	class Object;
}

namespace spawn
{
	class SpawnServiceInterface : public swganh::service::ServiceInterface
	{
	public:
		virtual void StartManagingObject(std::shared_ptr<swganh::object::Object> object, std::wstring machine) = 0;
		virtual void StopManagingObject(std::shared_ptr<swganh::object::Object> object) = 0;
	};
}
}

#endif