// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include <swganh/travel/travel_service_interface.h>

#include <glm/glm.hpp>

#include <swganh/app/swganh_kernel.h>
#include <swganh/connection/connection_client_interface.h>

namespace swganh {
namespace connection {
	class ConnectionClientInterface;
} // namespace swganh::connection 

namespace simulation {
	class SimulationService;
} // namespace swganh::simulation

namespace messages {
	struct PlanetTravelPointListRequest;
} // namespace swganh::messages

namespace travel {

	struct TravelPoint
	{
		uint32_t taxes;
		uint8_t port_type;
		std::string descriptor;
		uint32_t scene_id;
		glm::vec3 position;
		glm::vec3 spawn_position;
	};

	class TravelService : public TravelServiceInterface
	{
	public:
		TravelService(swganh::app::SwganhKernel* kernel);
		~TravelService();

		void Startup();

		swganh::service::ServiceDescription GetServiceDescription();

		virtual void BeginTicketTransaction(std::shared_ptr<swganh::object::Object> object);

	private:

		void HandlePlanetTravelPointListRequest(const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client, swganh::messages::PlanetTravelPointListRequest* message);

		void LoadStaticTravelPoints();
		void LoadDynamicTravelPoints();

		std::vector<TravelPoint> travel_points_;

		swganh::app::SwganhKernel* kernel_;
		swganh::simulation::SimulationService* simulation_;
	};
}} // namespace swganh::travel