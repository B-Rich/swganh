
#ifndef SWGANH_OBJECT_OBJECT_MESSAGE_BUILDER_H_
#define SWGANH_OBJECT_OBJECT_MESSAGE_BUILDER_H_

#include <memory>
#include <boost/optional.hpp>

#include "anh/event_dispatcher.h"

namespace swganh {
namespace messages {
    struct BaselinesMessage;
    class DeltasMessage;
}} // swganh::messages

namespace swganh {
namespace object {

    class Object;
    class ObjectController;
    class ObjectMessageBuilder
    {
    public:
        ObjectMessageBuilder(anh::EventDispatcher* event_dispatcher_)
            : event_dispatcher(event_dispatcher_)
        {
            RegisterEventHandlers();
        }
        virtual void RegisterEventHandlers();
        virtual void SendEndBaselines(std::shared_ptr<Object> object, std::shared_ptr<ObjectController> controller);
        static void BuildComplexityDelta(std::shared_ptr<Object> object);
        static void BuildStfNameDelta(std::shared_ptr<Object> object);
        static void BuildCustomNameDelta(std::shared_ptr<Object> object);
        static void BuildVolumeDelta(std::shared_ptr<Object> object);
        // delta 6
        static void BuildServerIDDelta(std::shared_ptr<Object> object);

        static swganh::messages::BaselinesMessage CreateBaselinesMessage(std::shared_ptr<Object> object, uint8_t view_type, uint16_t opcount = 0) ;

        static swganh::messages::DeltasMessage CreateDeltasMessage(std::shared_ptr<Object> object, uint8_t view_type, uint16_t update_type, uint16_t update_count = 1) ;

        static swganh::messages::BaselinesMessage BuildBaseline3(std::shared_ptr<Object> object);
        static swganh::messages::BaselinesMessage BuildBaseline6(std::shared_ptr<Object> object);
        typedef anh::ValueEvent<std::shared_ptr<Object>> ObjectEvent;
    protected:
        anh::EventDispatcher* event_dispatcher;        
	};

}}  // swganh::object

#endif  // SWGANH_OBJECT_OBJECT_MESSAGE_BUILDER_H_
