
#include "swganh/object/object_controller.h"

#include "swganh/messages/obj_controller_message.h"
#include "swganh/network/remote_client.h"
#include "swganh/object/object.h"

using namespace std;
using namespace swganh::messages;
using namespace swganh::network;
using namespace swganh::object;

ObjectController::ObjectController(
    const ObjControllerHandlerMap& handlers,
    shared_ptr<Object> object,
    shared_ptr<RemoteClient> client)
    : handlers_(handlers)
    , object_(object)
    , client_(client)
{
    object_->SetController(shared_from_this());
}

ObjectController::~ObjectController()
{
    object_->ClearController();
}

const shared_ptr<Object>& ObjectController::GetObject() const
{
    return object_;
}

const shared_ptr<RemoteClient>& ObjectController::GetRemoteClient() const
{
    return client_;
}

void ObjectController::HandleControllerMessage(const ObjControllerMessage& message)
{
    auto find_iter = handlers_.find(message.header);
    
    if (find_iter == handlers_.end())
    {
        throw InvalidControllerMessage("No handler registered to process the given message.");
    }
    
    find_iter->second(object_, move(message));
}

void ObjectController::Notify(const anh::ByteBuffer& message)
{
    client_->Send(message);
}
