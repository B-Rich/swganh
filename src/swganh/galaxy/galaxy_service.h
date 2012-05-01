// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#ifndef SWGANH_GALAXY_GALAXY_SERVICE_H_
#define SWGANH_GALAXY_GALAXY_SERVICE_H_

#include "anh/service/service_interface.h"

#include "swganh/app/swganh_kernel.h"
#include "swganh/galaxy/providers/galaxy_provider_interface.h"

namespace anh {
namespace app {
class KernelInterface;
}}  // namespace anh::app


namespace swganh {
namespace galaxy {

    class GalaxyService : public anh::service::ServiceInterface
    {
    public:    
        explicit GalaxyService(swganh::app::SwganhKernel* kernel);
    	uint32_t GetPopulation();
    	anh::service::ServiceDescription GetServiceDescription();
        
    private:
        GalaxyService();
    	std::shared_ptr<providers::GalaxyProviderInterface> galaxy_provider_;
        swganh::app::SwganhKernel* kernel_;
    };

}}  // swganh::galaxy

#endif // SWGANH_GALAXY_GALAXY_SERVICE_H_
