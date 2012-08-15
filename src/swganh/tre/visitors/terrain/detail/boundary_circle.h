#ifndef BOUNDARY_CIRCLE_H_
#define BOUNDARY_CIRCLE_H_

#include "boundary_layer.h"

namespace swganh
{
namespace tre
{

	class BoundaryCircle : public BoundaryLayer
	{
	public:

		virtual bool IsContained(float px, float pz);
		virtual float Process(float px, float pz);
		
	protected:
		float x;
		float z;
		float rad;
	};

}
}


#endif