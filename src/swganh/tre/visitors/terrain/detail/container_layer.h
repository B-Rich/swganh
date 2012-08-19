#ifndef CONTAINER_LAYER_H_
#define CONTAINER_LAYER_H_

#include "layer.h"
#include <vector>

namespace swganh
{
namespace tre
{
	class BoundaryLayer;
	class FilterLayer;
	class HeightLayer;

	class ContainerLayer : public Layer
	{
	public:

		virtual void Deserialize(anh::ByteBuffer& buffer)
		{
		}

		virtual LayerType GetType() { return LAYER_TYPE_CONTAINER; }

		void InsertLayer(Layer* layer)
		{
			switch(layer->GetType())
			{
			case LAYER_TYPE_CONTAINER:
				children.push_back((ContainerLayer*)layer);
				break;
			case LAYER_TYPE_BOUNDARY:
				boundaries.push_back((BoundaryLayer*)layer);
				break;
			case LAYER_TYPE_HEIGHT:
				heights.push_back((HeightLayer*)layer);
				break;
			case LAYER_TYPE_FILTER:
				filters.push_back((FilterLayer*)layer);
			}
		}

		std::vector<ContainerLayer*> children;
		std::vector<BoundaryLayer*> boundaries;
		std::vector<FilterLayer*> filters;
		std::vector<HeightLayer*> heights;

	private:
	};

}
}


#endif