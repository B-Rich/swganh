// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include "spawn_region.h"

#include <boost/geometry/geometries/point_xy.hpp>

namespace swganh
{
namespace terrain
{
	class TerrainServiceInterface;
}

namespace spawn
{

typedef boost::geometry::model::d2::point_xy<double> Point;

class CircleSpawnRegion : public SpawnRegion
{
public:
	
	CircleSpawnRegion(std::shared_ptr<swganh::terrain::TerrainServiceInterface> terrain, 
		std::shared_ptr<LootGroup> loot_group, uint32_t density, uint32_t timeout, float rarity,
		float x, float y, float radius, SpawnFactory type);
	
	std::shared_ptr<swganh::object::Object> Spawn(swganh::app::SwganhKernel* kernel);
	
	bool NeedsSpawn(swganh::app::SwganhKernel* kernel);
	
	glm::vec3 NextSpawnLocation(swganh::app::SwganhKernel* kernel);
	
private:
	std::shared_ptr<swganh::terrain::TerrainServiceInterface> terrain_;
	SpawnFactory factory_;
	Point center_;
};

}}