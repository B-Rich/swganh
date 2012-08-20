#ifndef SWGANH_TERRAIN_SERVICE_H_
#define SWGANH_TERRAIN_SERVICE_H_

#include "swganh/terrain/terrain_service_interface.h"
#include "swganh/app/swganh_kernel.h"
#include <map>
#include <list>
#include <memory>

namespace swganh
{
namespace tre
{
	class TerrainVisitor;
	class LayerVisitor;
	class Fractal;

	class ContainerLayer;
}
}


namespace swganh_core
{


namespace terrain
{
	struct LayerEntry
	{
		std::shared_ptr<swganh::tre::LayerVisitor> layer_visitor_;
		float offset_x, offset_z;
	};

	struct SceneEntry
	{
		std::shared_ptr<swganh::tre::TerrainVisitor> terrain_visitor_;
		std::list<LayerEntry> layers_;
	};

	typedef std::map<uint32_t, SceneEntry> SceneMap;

	class TerrainService : public swganh::terrain::TerrainServiceInterface
	{
	public:

		TerrainService(swganh::app::SwganhKernel* kernel);

		virtual float GetHeight(uint32_t scene_id, float x, float z, bool raw=false);

		virtual bool IsWater(uint32_t scene_id, float x, float z, bool raw=false);

		anh::service::ServiceDescription GetServiceDescription();
        

	private:

		float processLayerHeight(swganh::tre::ContainerLayer* layer, float x, float z, float& base_value, float affector_transform, std::map<uint32_t, swganh::tre::Fractal*>& fractals);
		float calculateFeathering(float value, int featheringType);

		SceneMap scenes_;
		swganh::app::SwganhKernel* kernel_;
	};
}
}

#endif;