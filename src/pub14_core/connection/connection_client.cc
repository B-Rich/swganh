// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "connection_client.h"
#include "swganh/object/object_controller.h"
#include "swganh/object/object.h"
#include "swganh/object/player/player.h"

using namespace anh::network::soe;
using namespace std;
using namespace swganh_core::connection;
using namespace swganh::object;

ConnectionClient::ConnectionClient(ServerInterface* server, boost::asio::io_service& io_service, boost::asio::ip::udp::endpoint remote_endpoint)
    : ConnectionClientInterface(server, io_service, remote_endpoint)
{}

ConnectionClient::State ConnectionClient::GetState() const
{
    return state_;
}

uint32_t ConnectionClient::GetAccountId() const
{
    return account_id_;
}

uint64_t ConnectionClient::GetPlayerId() const
{
    return player_id_;
}

void ConnectionClient::Connect(uint32_t account_id, uint64_t player_id)
{
    account_id_ = account_id;
    player_id_ = player_id;

    state_ = CONNECTED;
}

void ConnectionClient::OnClose()
{
    state_ = DISCONNECTING;
}

const shared_ptr<ObjectController>& ConnectionClient::GetController() const
{
    return controller_;
}

void ConnectionClient::SetController(const shared_ptr<ObjectController>& controller)
{
    controller_ = controller;
}
