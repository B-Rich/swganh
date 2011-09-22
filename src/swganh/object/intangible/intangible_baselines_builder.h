
#ifndef SWGANH_OBJECT_INTANGIBLE_INTANGIBLE_BASELINES_BUILDER_H_
#define SWGANH_OBJECT_INTANGIBLE_INTANGIBLE_BASELINES_BUILDER_H_

#include <memory>

namespace swganh {
namespace object {
namespace intangible {

    class Intangible;

    class IntangibleBaselinesBuilder
    {
    public:
        static void BuildStfDetailDelta(Intangible* object);
    };

}}}  // swganh::object::intangible

#endif  // SWGANH_OBJECT_INTANGIBLE_INTANGIBLE_BASELINES_BUILDER_H_
