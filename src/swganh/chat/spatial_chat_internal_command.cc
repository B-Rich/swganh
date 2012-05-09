// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "spatial_chat_internal_command.h"

#ifdef WIN32
#include <regex>
#else
#include <boost/regex.hpp>
#endif

#include "anh/logger.h"
#include "anh/service/service_manager.h"

#include "swganh/object/creature/creature.h"
#include "swganh/object/tangible/tangible.h"

#include "chat_service.h"

using swganh::chat::ChatService;
using swganh::chat::SpatialChatInternalCommand;
using swganh::command::BaseSwgCommand;
using swganh::command::CommandProperties;
using swganh::messages::controllers::CommandQueueEnqueue;
using swganh::object::creature::Creature;
using swganh::object::tangible::Tangible;

#ifdef WIN32
using std::wregex;
using std::wsmatch;
using std::regex_match;
#else
using boost::wregex;
using boost::wsmatch;
using boost::regex_match;
#endif

SpatialChatInternalCommand::SpatialChatInternalCommand(
    swganh::app::SwganhKernel* kernel,
    const CommandProperties& properties,
    const std::shared_ptr<swganh::object::creature::Creature>& actor,
    const std::shared_ptr<swganh::object::tangible::Tangible>& target,
    const swganh::messages::controllers::CommandQueueEnqueue& command)
    : BaseSwgCommand(kernel, properties, actor, target, command)
{
    chat_service_ = kernel->GetServiceManager()->GetService<ChatService>("ChatService");
}

SpatialChatInternalCommand::~SpatialChatInternalCommand()
{}

void SpatialChatInternalCommand::Setup()
{}

bool SpatialChatInternalCommand::Validate()
{
    return true;
}

void SpatialChatInternalCommand::Run()
{
    // This regular expression searches for 5 numbers separated by spaces
    // followed by a string text message.
    const wregex p(L"(\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (.*)");
    wsmatch m;

    if (! regex_match(GetCommandString(), m, p)) {
        LOG(error) << "Invalid spatial chat message format";
        return; // We suffered an unrecoverable error, bail out now.
    }
    
    chat_service_->SendSpatialChat(
        GetActor(), 
        GetTarget(), 
        m[6].str().substr(0, 256), // Use a max of 255 characters and discard the rest.
        std::stoi(m[2].str()), // Convert the string to an integer 
        std::stoi(m[3].str()));
}
