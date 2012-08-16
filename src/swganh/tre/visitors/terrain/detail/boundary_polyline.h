#ifndef BOUNDARY_POLYLINE_H_
#define BOUNDARY_POLYLINE_H_

#include "boundary_layer.h"
#include <glm/glm.hpp>

namespace swganh
{
namespace tre
{

	class BoundaryPolyline : public BoundaryLayer
	{
	public:

		virtual void Deserialize(anh::ByteBuffer buffer);
		virtual bool IsContained(float px, float pz);
		virtual float Process(float px, float pz);
		
	protected:
		std::vector<glm::vec2> verts;
		float line_width;
		float max_x, max_z, min_x, min_z;
	};

}
}


#endif