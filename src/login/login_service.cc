/*
 This file is part of SWGANH. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2011 The SWG:ANH Team

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "login/login_service.h"

#include <glog/logging.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "anh/app/kernel_interface.h"

#include "anh/database/database_manager.h"

#include "anh/event_dispatcher/basic_event.h"
#include "anh/event_dispatcher/event_dispatcher_interface.h"

#include "anh/network/soe/packet.h"
#include "anh/network/soe/session.h"
#include "anh/network/soe/server.h"

#include "anh/service/service_manager.h"

#include "swganh/base/swg_message_handler.h"

#include "login/messages/delete_character_reply_message.h"
#include "login/messages/enumerate_character_id.h"
#include "login/messages/login_client_token.h"
#include "login/messages/login_cluster_status.h"
#include "login/messages/login_enum_cluster.h"

#include "login/authentication_manager.h"
#include "login/login_client.h"
#include "login/encoders/sha512_encoder.h"
#include "login/providers/mysql_account_provider.h"

using namespace anh;
using namespace app;
using namespace login;
using namespace messages;
using namespace swganh::login;
using namespace swganh::base;
using namespace swganh::character;
using namespace database;
using namespace event_dispatcher;
using namespace std;

LoginService::LoginService(shared_ptr<KernelInterface> kernel) 
    : LoginServiceInterface(kernel)
    , galaxy_status_timer_(kernel->GetIoService())
    , listen_port_(0)
    , packet_router_(clients_) {
    soe_server_.reset(new network::soe::Server(kernel->GetIoService(), swganh::base::SwgMessageHandler(kernel->GetEventDispatcher())));
    soe_server_->event_dispatcher(kernel->GetEventDispatcher());
    
    auto encoder = make_shared<encoders::Sha512Encoder>(kernel->GetDatabaseManager());

    authentication_manager_ = make_shared<AuthenticationManager>(encoder);
    account_provider_ = make_shared<providers::MysqlAccountProvider>(kernel->GetDatabaseManager());
}

LoginService::~LoginService() {}

service::ServiceDescription LoginService::GetServiceDescription() {
    service::ServiceDescription service_description(
        "ANH Login Service",
        "login",
        "0.1",
        listen_address_, 
        0, 
        listen_port_, 
        0);

    return service_description;
}

void LoginService::DescribeConfigOptions(boost::program_options::options_description& description) {
    description.add_options()
        ("service.login.udp_port", boost::program_options::value<uint16_t>(&listen_port_),
            "The port the login service will listen for incoming client connections on")
        ("service.login.address", boost::program_options::value<string>(&listen_address_),
            "The public address the login service will listen for incoming client connections on")
        ("service.login.status_check_duration_secs", boost::program_options::value<int>(&galaxy_status_check_duration_secs_),
            "The amount of time between checks for updated galaxy status")
    ;
}

void LoginService::onStart() {
    character_service_ = static_pointer_cast<BaseCharacterService>(kernel()->GetServiceManager()->GetService("CharacterService"));

    soe_server_->Start(listen_port_);
    galaxy_status_ = GetGalaxyStatus_();
    
    UpdateGalaxyStatus_();
}

void LoginService::onStop() {
    soe_server_->Shutdown();
}

void LoginService::subscribe() {
    auto event_dispatcher = kernel()->GetEventDispatcher();
   
    event_dispatcher->subscribe("LoginClientId", [this] (shared_ptr<EventInterface> incoming_event) {
        return HandleLoginClientId_(incoming_event);
    });

    event_dispatcher->subscribe("DeleteCharacterMessage", [this] (shared_ptr<EventInterface> incoming_event) {
        return packet_router_.RoutePacket<DeleteCharacterMessage>(incoming_event, bind(&LoginService::HandleDeleteCharacterMessage_, this, placeholders::_1, placeholders::_2));
    });
    
    event_dispatcher->subscribe("NetworkSessionRemoved", [this] (shared_ptr<EventInterface> incoming_event) -> bool {
        auto session_removed = std::static_pointer_cast<anh::event_dispatcher::BasicEvent<anh::network::soe::SessionData>>(incoming_event);
        
        // Message was triggered from our server so process it.
        if (session_removed->session->server() == soe_server_.get()) {
            RemoveClient_(session_removed->session);
        }

        return true;
    });
}

std::shared_ptr<LoginClient> LoginService::AddClient_(std::shared_ptr<anh::network::soe::Session> session) {
    std::shared_ptr<LoginClient> client = nullptr;

    auto find_it = clients_.find(session->remote_endpoint());

    if (find_it == clients_.end()) {
        DLOG(WARNING) << "Adding login client";

        client = make_shared<LoginClient>();
        client->session = session;

        clients_.insert(make_pair(session->remote_endpoint(), client));
    }

    DLOG(WARNING) << "Login service currently has ("<< clients_.size() << ") clients";
    return client;
}

void LoginService::RemoveClient_(std::shared_ptr<anh::network::soe::Session> session) {
    active().Send([=] () {
        auto find_it = clients_.find(session->remote_endpoint());

        if (find_it != clients_.end()) {
            DLOG(WARNING) << "Removing disconnected client";
            clients_.erase(find_it);
        }

        DLOG(WARNING) << "Login service currently has ("<< clients_.size() << ") clients";
    });
}

void LoginService::UpdateGalaxyStatus_() {    
    active().SendRepeated(boost::posix_time::seconds(galaxy_status_check_duration_secs_), [this] (const boost::system::error_code & error) {
        DLOG(INFO) << "Updating galaxy status";

        galaxy_status_ = GetGalaxyStatus_();
        
        const vector<GalaxyStatus>& status = galaxy_status_;

        std::for_each(clients_.begin(), clients_.end(), [&status] (std::map<boost::asio::ip::udp::endpoint, std::shared_ptr<LoginClient>>::value_type& client_entry) {
            if (client_entry.second) {                
                client_entry.second->session->SendMessage(
                    BuildLoginClusterStatus(status));
            }
        });
    });
}

std::vector<GalaxyStatus> LoginService::GetGalaxyStatus_() {
    std::vector<GalaxyStatus> galaxy_status;
    
    auto service_directory = this->service_directory();

    auto galaxy_list = service_directory->getGalaxySnapshot();

    std::for_each(galaxy_list.begin(), galaxy_list.end(), [this, &galaxy_status, &service_directory] (anh::service::Galaxy& galaxy) {
        auto service_list = service_directory->getServiceSnapshot(std::make_shared<anh::service::Galaxy>(galaxy));

        auto it = std::find_if(service_list.begin(), service_list.end(), [] (anh::service::ServiceDescription& service) {
            return service.type().compare("connection") == 0;
        });

        if (it != service_list.end()) {
            GalaxyStatus status;
            status.address = it->address();
            status.connection_port = it->udp_port();
            status.distance = 0xffff8f80;
            status.galaxy_id = galaxy.id();
            status.max_characters = 2;
            status.max_population = 0x00000cb2;
            status.name = galaxy.name();
            status.ping_port = it->ping_port();
            status.server_population = 10;
            status.status = service_directory->galaxy()->status();

            galaxy_status.push_back(std::move(status));
        }
    });

    return galaxy_status;
}

bool LoginService::HandleLoginClientId_(std::shared_ptr<anh::event_dispatcher::EventInterface> incoming_event) {
    auto remote_event = std::static_pointer_cast<anh::event_dispatcher::BasicEvent<anh::network::soe::Packet>>(incoming_event);

    auto login_client = AddClient_(remote_event->session());

    LoginClientId message;
    message.deserialize(*remote_event->message());

    login_client->username = message.username;
    login_client->password = message.password;
    login_client->version = message.client_version;

    auto account = account_provider_->FindByUsername(login_client->username);

    if (! account) {
        DLOG(WARNING) << "Login request for invalid user: " << login_client->username;
        return true;
    }

    if (! authentication_manager_->Authenticate(login_client, account)) {
        DLOG(WARNING) << "Failed login attempt for user: " << login_client->username;
        return true;
    }

    login_client->account = account;
    clients_.insert(make_pair(login_client->session->remote_endpoint(), login_client));
    
    // create account session
    string account_session = boost::posix_time::to_simple_string(boost::posix_time::microsec_clock::local_time())
        + boost::lexical_cast<string>(remote_event->session()->remote_endpoint().address());

    account_provider_->CreateAccountSession(account->account_id(), account_session);
    login_client->session->SendMessage(
        messages::BuildLoginClientToken(login_client, account_session));
    
    login_client->session->SendMessage(
        messages::BuildLoginEnumCluster(login_client, galaxy_status_));
    
    login_client->session->SendMessage(
        messages::BuildLoginClusterStatus(galaxy_status_));
    
    auto characters = character_service_->GetCharactersForAccount(login_client->account->account_id());

    login_client->session->SendMessage(
        messages::BuildEnumerateCharacterId(characters));

    return true;
}
void LoginService::HandleDeleteCharacterMessage_(std::shared_ptr<LoginClient> login_client, const DeleteCharacterMessage& message) {
    DeleteCharacterReplyMessage reply_message;
    reply_message.failure_flag = 1;

    if (character_service_->DeleteCharacter(message.character_id)) {
        reply_message.failure_flag = 0;
    }

    login_client->session->SendMessage(reply_message);
}

uint32_t LoginService::GetAccountBySessionKey(const string& session_key) {
    return account_provider_->FindBySessionKey(session_key);
}