#ifndef HEIGHT_CONSTANT_H_
#define HEIGHT_CONSTANT_H_

#include "height_layer.h"

namespace swganh
{
namespace tre
{
	class HeightConstant : public HeightLayer
	{
	public:

		virtual void Deserialize(anh::ByteBuffer& buffer);
		
		virtual void GetBaseHeight(float x, float z, float transform_value, float& base_value, std::map<uint32_t,Fractal*>& fractals);

	private:
		int   fractal_id;
		int   transform_type;
		float height_val;
	};

}
}


#endif