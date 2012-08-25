// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include <memory>
#include <boost/asio/deadline_timer.hpp>

#include "anh/service/service_interface.h"

#include "swganh/app/swganh_kernel.h"
#include "swganh/galaxy/providers/galaxy_provider_interface.h"

namespace anh {
    class EventDispatcherInterface;
namespace app {
class KernelInterface;
}}  // namespace anh::app


namespace swganh {
namespace galaxy {

    class GalaxyServiceInterface : public anh::service::ServiceInterface
    {
    public:    

    	virtual uint32_t GetPopulation() = 0;
		
		virtual uint64_t GetGalaxyTimeInMilliseconds() = 0;

    	virtual anh::service::ServiceDescription GetServiceDescription() = 0;
        
        virtual void Startup() = 0;

    };

}}  // swganh::galaxy
