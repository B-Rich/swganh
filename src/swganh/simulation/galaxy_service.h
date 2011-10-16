
#ifndef SWGANH_SIMULATION_GALAXY_SERVICE_H_
#define SWGANH_SIMULATION_GALAXY_SERVICE_H_

#include <cstdint>
#include <map>
#include <memory>

#include "swganh/base/base_service.h"
#include "swganh/object/object_controller.h"

namespace swganh {
namespace network {
    class RemoteClient;
}}  // namespace swganh::network

namespace swganh {
namespace object {
    class Object;
}}  // namespace swganh::object

namespace swganh {
namespace simulation {
    
    class GalaxyServiceImpl;

    class GalaxyService : public swganh::base::BaseService
    {
    public:
        explicit GalaxyService(std::shared_ptr<anh::app::KernelInterface> kernel);
    
        ~GalaxyService();

        anh::service::ServiceDescription GetServiceDescription();

        void StartScene(const std::string& scene_label);
        void StopScene(const std::string& scene_label);

		void RegisterObjectFactories(std::shared_ptr<anh::app::KernelInterface> kernel);
        
        std::shared_ptr<swganh::object::Object> LoadObjectById(uint64_t object_id);
        
        const std::shared_ptr<swganh::object::Object>& GetObjectById(uint64_t object_id);

        template<typename T>
        const std::shared_ptr<T>& GetObjectById(uint64_t object_id)
        {
            std::shared_ptr<Object> object = GetObjectById(object_id);

#if _DEBUG
            return std::dynamic_pointer_cast<T>(object);
#else
            return std::static_pointer_cast<T>(object);
#endif
        }

        /**
         * Removes the requested object from the simulation.
         */
        void RemoveObjectById(uint64_t object_id);
        
        std::shared_ptr<swganh::object::ObjectController> StartControllingObject(
            const std::shared_ptr<swganh::object::Object>& object,
            std::shared_ptr<swganh::network::RemoteClient> client);

        void StopControllingObject(const std::shared_ptr<swganh::object::Object>& object);

        void RegisterControllerHandler(uint32_t handler_id, swganh::object::ObjControllerHandler&& handler);

        void UnregisterControllerHandler(uint32_t handler_id);

    private:

        void onStart();

        std::unique_ptr<GalaxyServiceImpl> impl_;
    };

}}  // namespace swganh::simulation

#endif  // SWGANH_SIMULATION_GALAXY_SERVICE_H_
