// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include "swganh_core/object/tangible/tangible_factory.h"

namespace swganh {
namespace object {


	class Installation;
    class InstallationFactory : public swganh::object::TangibleFactory
    {
    public:
		typedef Installation ObjectType;

        InstallationFactory(swganh::app::SwganhKernel* kernel);

        virtual uint32_t PersistObject(const std::shared_ptr<swganh::object::Object>& object);
		virtual void PersistChangedObjects();
        void DeleteObjectFromStorage(const std::shared_ptr<swganh::object::Object>& object);
		std::shared_ptr<swganh::object::Object> CreateObjectFromStorage(uint64_t object_id);

        std::shared_ptr<swganh::object::Object> CreateObject();

		virtual void RegisterEventHandlers();
    };

}}  // namespace swganh::object
