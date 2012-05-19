// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "swganh/galaxy/galaxy_service.h"

#include <boost/asio/placeholders.hpp>

#include "anh/event_dispatcher.h"
#include "anh/plugin/plugin_manager.h"
#include "anh/service/service_directory_interface.h"
#include "anh/service/service_manager.h"

#include "swganh/app/swganh_kernel.h"
#include "swganh/galaxy/providers/galaxy_provider_interface.h"

using namespace anh;
using namespace app;
using namespace service;
using namespace swganh::app;
using namespace swganh::galaxy;
using namespace std;

GalaxyService::GalaxyService(SwganhKernel* kernel)
    : kernel_(kernel)
{
	galaxy_provider_ = kernel->GetPluginManager()->CreateObject<providers::GalaxyProviderInterface>("GalaxyService::GalaxyProvider");
}

GalaxyService::~GalaxyService()
{
    galaxy_timer_.reset();
}

ServiceDescription GalaxyService::GetServiceDescription()
{
	ServiceDescription service_description(        
		"ANH Galaxy Service",
        "galaxy",
        "0.1",
        "127.0.0.1", 
        0,
        0, 
        0);
	return service_description;
}

uint32_t GalaxyService::GetPopulation()
{
	return galaxy_provider_->GetPopulation();
}

void GalaxyService::Startup()
{
    galaxy_timer_ = std::make_shared<boost::asio::deadline_timer>(kernel_->GetIoService(), boost::posix_time::seconds(10));

    galaxy_timer_->async_wait(boost::bind(&GalaxyService::GalaxyStatusTimerHandler_, this, boost::asio::placeholders::error, 10));
}

void GalaxyService::GalaxyStatusTimerHandler_(const boost::system::error_code& e, int delay_in_secs)
{
    if (!e)
    {
        kernel_->GetServiceDirectory()->updateGalaxyStatus();        
        kernel_->GetEventDispatcher()->Dispatch(std::make_shared<BaseEvent>("UpdateGalaxyStatus"));
        

        if (this && galaxy_timer_)
        {
            galaxy_timer_->expires_from_now(boost::posix_time::seconds(delay_in_secs));    
            galaxy_timer_->async_wait(std::bind(&GalaxyService::GalaxyStatusTimerHandler_, this, std::placeholders::_1, delay_in_secs));
        }
    }
}