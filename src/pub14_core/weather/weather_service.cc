// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "weather_service.h"

#include <algorithm>
#include <ctime>
#include "anh/logger.h"
#include "anh/event_dispatcher.h"
#include "anh/plugin/plugin_manager.h"
#include "anh/service/service_manager.h"
#include "anh/service/service_directory_interface.h"
#include "pub14_core/messages/server_weather_message.h"
#include "swganh/app/swganh_kernel.h"
#include "swganh/messages/out_of_band.h"
#include "swganh/simulation/simulation_service_interface.h"
#include "swganh/object/player/player.h"
#include "swganh/object/object_controller.h"
#include "swganh/connection/connection_client.h"
#include "swganh/object/object.h"

using namespace std;
using namespace anh;
using namespace anh::service;
using namespace anh::plugin;
using namespace swganh::messages;
using namespace swganh::simulation;
using namespace swganh_core::weather;
using namespace swganh::object::player;
using namespace swganh::object;
using namespace swganh::weather;
using namespace swganh::galaxy;
using namespace swganh::scripting;

using anh::app::KernelInterface;
using anh::service::ServiceDescription;
using swganh::app::SwganhKernel;
using swganh::simulation::SimulationServiceInterface;


WeatherService::WeatherService(SwganhKernel* kernel)
	: kernel_(kernel), script_(kernel_->GetAppConfig().script_directory + "/weather/weather.py")
{
	player_selected_callback_ = kernel_->GetEventDispatcher()->Subscribe(
		"ObjectReadyEvent",
		[this] (shared_ptr<anh::EventInterface> incoming_event)
		{
			const auto& player_obj = static_pointer_cast<ValueEvent<shared_ptr<Object>>>(incoming_event)->Get();
			OnPlayerEnter(player_obj);
		});
}

WeatherService::~WeatherService(){
}

void WeatherService::OnPlayerEnter(shared_ptr<Object> player_obj)
{
	//On object ready event, send player current scene weather message
	uint32_t playerScene = player_obj->GetSceneId();
	if(sceneLookup_.count(playerScene))
	{
		SendServerWeatherMessagePlayer_(sceneLookup_[playerScene].weatherSequence_[(sceneLookup_[playerScene].sequenceCount_)-1], player_obj->GetController());
	}
	else
	{
	}
}

ServiceDescription WeatherService::GetServiceDescription()
{
    ServiceDescription service_description(
        "WeatherService",
        "weather",
        "0.1",
        "127.0.0.1",
        0,
        0,
        0);

    return service_description;
}

Weather WeatherService::GetSceneWeather(uint32_t scene_id)
{
	if(sceneLookup_.count(scene_id))
	{
		return sceneLookup_[scene_id].weatherSequence_[sceneLookup_[scene_id].sequenceCount_].GetWeatherType();
	}
	else
		return Weather::NOSTORM;
}
void WeatherService::SetSceneWeather(uint32_t scene_id, std::vector<WeatherEvent> weather_sequence_)
{
	boost::lock_guard<boost::mutex> lock(weather_mutex_);
	if(!sceneLookup_.count(scene_id))
	{
		sceneLookup_[scene_id].scene_=Scene(scene_id);
		sceneLookup_[scene_id].weatherSequence_=weather_sequence_;
		sceneLookup_[scene_id].updateGalaxyTickTime_=0;
		sceneLookup_[scene_id].sequenceCount_=0;
	}
	else
		LOG(info) << "Scene: " << scene_id << " currently has a weather event";
}

void WeatherService::SendServerWeatherMessagePlayer_(
	WeatherEvent weatherdata_,
	std::shared_ptr<swganh::object::ObjectController> obj_controller)
{
	ServerWeatherMessage server_weather_message;
	server_weather_message.weather_id = weatherdata_.GetWeatherType();
	server_weather_message.cloud_vector = weatherdata_.GetCloudVector();
	obj_controller->GetRemoteClient()->SendTo(server_weather_message);
			
}

void WeatherService::SendServerWeatherMessageAll_(
	Weather weather_type,
	glm::vec3 cloud_vector,
    uint32_t scene_id)
{
	ServerWeatherMessage server_weather_message;
	server_weather_message.weather_id = weather_type;
	server_weather_message.cloud_vector = cloud_vector;

	simulation_service_ = kernel_->GetServiceManager()->GetService<SimulationServiceInterface>("SimulationService");
	simulation_service_->SendToAllInScene(server_weather_message, scene_id);
}

void WeatherService::tickPlanetWeather_()
{
	bool removeWeather = false;
	uint32_t removeWeatherScene;
	uint64_t galaxyTime = galaxy_service_->GetGalaxyTimeInMilliseconds()/1000;

	//Loop through each weather scene and check if its time to run weather sequence
	std::for_each(sceneLookup_.begin(), sceneLookup_.end(), [this, &galaxyTime, &removeWeather, &removeWeatherScene] (std::pair<const uint32_t, PlanetWeather>& planetWeather_) {
		if(planetWeather_.second.updateGalaxyTickTime_ <= galaxyTime)
		{
			uint32_t planetSequenceCount = planetWeather_.second.sequenceCount_;
				if(planetWeather_.second.weatherSequence_.size()>planetSequenceCount)
				{
					LOG(info)<< "Setting weather on scene "<<Scene(planetWeather_.second.scene_);
					SendServerWeatherMessageAll_(planetWeather_.second.weatherSequence_.at(planetSequenceCount).GetWeatherType(),planetWeather_.second.weatherSequence_.at(planetSequenceCount).GetCloudVector(),planetWeather_.second.scene_);
					planetWeather_.second.updateGalaxyTickTime_ = galaxyTime + (planetWeather_.second.weatherSequence_.at(planetSequenceCount).GetDuration()*60);
					planetWeather_.second.sequenceCount_++;
				}
				//If weather sequence has finished, remove scene map
				if(planetWeather_.second.weatherSequence_.size()==planetSequenceCount)
				{
					removeWeather =true;
					removeWeatherScene=planetWeather_.second.scene_;
				}
		}
	});
	if(removeWeather)
		sceneLookup_.erase(removeWeatherScene);

	if(weatherScriptTimer< galaxyTime)
		{
			//Execute weather script every 5 mins
			WeatherScript();
			weatherScriptTimer = galaxyTime + 1800;
		}
}
void WeatherService::RunWeatherSequence()
{		
	weather_timer_ = std::make_shared<boost::asio::deadline_timer>(kernel_->GetIoService(), boost::posix_time::seconds(10));
	weather_timer_->async_wait(boost::bind(&WeatherService::RunWeatherSequenceTimer, this, boost::asio::placeholders::error, 10 ));
}

void WeatherService::RunWeatherSequenceTimer(
	const boost::system::error_code& e, uint32_t count)
{
	tickPlanetWeather_();
	weather_timer_->expires_at(weather_timer_->expires_at() + boost::posix_time::seconds(10));
	weather_timer_->async_wait(boost::bind(&WeatherService::RunWeatherSequenceTimer, this, boost::asio::placeholders::error, 10 ));
}

void WeatherService::WeatherScript()
{
	try
    {
        script_.SetContext("kernel", boost::python::ptr(kernel_));
        script_.Run();
    }
    catch (std::exception& e)
	{
        LOG(fatal) << e.what();
	}
}

void WeatherService::Startup() 
{
	galaxy_service_  = kernel_->GetServiceManager()->GetService<GalaxyService>("GalaxyService");
	weatherScriptTimer=0;
	RunWeatherSequence();
}

