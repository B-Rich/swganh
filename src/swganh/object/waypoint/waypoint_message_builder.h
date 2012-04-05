
#ifndef SWGANH_OBJECT_WAYPOINT_WAYPOINT_MESSAGE_BUILDER_H_
#define SWGANH_OBJECT_WAYPOINT_WAYPOINT_MESSAGE_BUILDER_H_

#include "swganh/object/object_message_builder.h"

namespace swganh {
namespace messages {
    struct BaselinesMessage;
}} // swganh::messages

namespace swganh {
namespace object {
namespace waypoint {

    class Waypoint;

    class WaypointMessageBuilder : public ObjectMessageBuilder
    {
    public:
        WaypointMessageBuilder(anh::EventDispatcher* dispatcher) : 
            ObjectMessageBuilder(dispatcher)
        {
            RegisterEventHandlers();
        }
        virtual void RegisterEventHandlers();
		static void BuildUsesDelta(std::shared_ptr<Waypoint> object);
		static void BuildActivateDelta(std::shared_ptr<Waypoint> object);
		static void BuildPlanetDelta(std::shared_ptr<Waypoint> object);
		static void BuildCoordinatesDelta(std::shared_ptr<Waypoint> object);
		static void BuildColor(std::shared_ptr<Waypoint> object);
        static boost::optional<swganh::messages::BaselinesMessage> BuildBaseline3(std::shared_ptr<Waypoint> object);
    };

}}}  // swganh::object::waypoint

#endif  // SWGANH_OBJECT_WAYPOINT_WAYPOINT_MESSAGE_BUILDER_H_
