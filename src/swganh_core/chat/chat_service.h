// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <boost/thread/mutex.hpp>

#include "swganh_core/chat/chat_service_interface.h"
#include "swganh_core/command/command_service_interface.h"
#include "swganh_core/simulation/simulation_service_interface.h"
#include "swganh_core/equipment/equipment_service_interface.h"

#include "swganh/app/swganh_kernel.h"
#include "swganh_core/messages/controllers/command_queue_enqueue.h"

namespace swganh {
namespace connection {
    class ConnectionClientInterface;
}

namespace object {
	class Object;
}

namespace messages
{
	//Tell Related
	struct ChatInstantMessageToCharacter;
	
	//Mail Related
	struct ChatPersistentMessageToServer;
	struct ChatRequestPersistentMessage;
	struct ChatDeletePersistentMessage;

	//Chat Room Related
	struct ChatRequestRoomList;
	struct ChatQueryRoom;
	struct ChatSendToRoom;
	struct ChatJoinRoom;
	struct ChatPartRoom;

	//Chat Room Management
	struct ChatCreateRoom;
	struct ChatDestroyRoom;

	//class Room User Management
	struct ChatBanAvatarFromRoom;
	struct ChatUnbanAvatarFromRoom;
	struct ChatInviteAvatarToRoom;
	struct ChatUninviteAvatarToRoom;
	struct ChatAddModToRoom;
	struct ChatRemoveModFromRoom;

	//Chat Room Ownership Management
}

namespace chat {

class ChatRoomProviderInterface;
class ChatUserProviderInterface;

/*
* The chat service handles chat related functions
*/
class ChatService: public swganh::chat::ChatServiceInterface
{
public:
	/**
	* Creates a new instance
	*/
    explicit ChatService(swganh::app::SwganhKernel* kernel);
    virtual ~ChatService();

    bool SendPersistentMessage(
        const std::string& recipient,
        const std::string& sender, 
        const std::string& sender_game, 
        const std::string& sender_galaxy, 
        const std::wstring& subject, 
        const std::wstring& message, 
        const std::vector<char>& attachments);
    
    bool SendPersistentMessage(
        const std::string& recipient,
        const std::string& sender,
        const std::wstring& subject, 
        const std::wstring& message);
		
	/**
	* Sends a spatial chat message
	* @param actor the speaker
	* @param target the target
	* @param chat_message the message
	* @param chat_type the type of chat
	* @param mood the mood used
	*/
    void SendSpatialChat(
		const std::shared_ptr<swganh::object::Object>& actor, // creature object
		const std::shared_ptr<swganh::object::Object>& target,	// target object
        std::wstring chat_message,
        uint16_t chat_type,
        uint16_t mood);

	void Initialize();
    void Startup();

    uint64_t GetObjectIdByCustomName(const std::string& custom_name);

private:
    swganh::database::DatabaseManager* db_manager_;
	swganh::command::CommandServiceInterface* command_service_;
    swganh::simulation::SimulationServiceInterface* simulation_service_;
	swganh::equipment::EquipmentServiceInterface* equipment_service_;


    swganh::app::SwganhKernel* kernel_;
	std::shared_ptr<ChatRoomProviderInterface> room_provider_;
	std::shared_ptr<ChatUserProviderInterface> user_provider_;

	std::string galaxy_name_;

	std::map<uint64_t, std::set<std::shared_ptr<swganh::observer::ObserverInterface>>> player_observers_;
	std::map<uint64_t, std::shared_ptr<swganh::observer::ObserverInterface>> online_players_;

    void SendChatPersistentMessageToClient(
        const std::shared_ptr<swganh::observer::ObserverInterface>& receiver, 
        const std::string& sender_name, 
        const std::string& sender_game, 
        const std::string& sender_galaxy, 
        const std::wstring& subject, 
        const std::wstring& message, 
        uint32_t message_id,
        uint8_t status,
        const std::vector<char>& attachments, 
        uint32_t timestamp);

    void SendChatPersistentMessageToClient(
        const std::shared_ptr<swganh::observer::ObserverInterface>& receiver, 
        const std::string& sender_name, 
        const std::string& sender_game, 
        const std::string& sender_galaxy, 
        const std::wstring& subject,
        uint32_t message_id,
        uint8_t status,
        uint32_t timestamp);
    
    void SendChatPersistentMessageToClient(
        const std::shared_ptr<swganh::observer::ObserverInterface>& receiver, 
        const std::string& sender_name, 
        const std::string& sender_game, 
        const std::string& sender_galaxy, 
        const std::wstring& subject, 
        const std::wstring& message, 
        uint32_t message_id,
        uint8_t status,
        const std::vector<char>& attachments, 
        uint32_t timestamp,
        uint8_t header_only);

    void SendChatOnSendInstantMessage(
        const std::shared_ptr<swganh::observer::ObserverInterface>& receiver,
        uint32_t message_id,
        uint32_t recieved_status);

    void SendChatOnSendPersistentMessage(
        const std::shared_ptr<swganh::observer::ObserverInterface>& receiver,
        uint32_t message_id,
        uint32_t recieved_status);

    void SendChatInstantMessageToClient(
        const std::shared_ptr<swganh::observer::ObserverInterface>& receiver, 
        const std::string& sender_name, 
        const std::string& sender_game, 
        const std::string& sender_galaxy, 
        const std::wstring& message);
		
    uint32_t StorePersistentMessage(
        uint64_t recipient_id,
        const std::string& sender_name, 
        const std::string& sender_game, 
        const std::string& sender_galaxy, 
        const std::wstring& subject, 
        const std::wstring& message, 
        const std::vector<char>& attachments,
        uint8_t status,
        uint32_t timestamp);

    void LoadMessageHeaders(const std::shared_ptr<swganh::object::Creature>& receiver);
	void HandleFriendsList(const std::shared_ptr<swganh::object::Creature>& receiver, uint8_t operation);
    std::wstring FilterMessage(const std::wstring& message);

	//Tell Related
	void _handleInstantMessageToCharacter(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatInstantMessageToCharacter* message);
	
	//Mail Related
	void _handlePersistentMessageToServer(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatPersistentMessageToServer* message);

	void _handleRequestPersistentMessage(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatRequestPersistentMessage* message);

	void _handleDeletePersistentMessage(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatDeletePersistentMessage* message);

	//Chat Room Related
	void _handleRequestRoomList(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatRequestRoomList* message);

	void _handleQueryRoom(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatQueryRoom* message);

	void _handleSendToRoom(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatSendToRoom* message);

	void _handleJoinRoom(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatJoinRoom* message);

	void _handlePartRoom(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatPartRoom* message);

	//Chat Room Management
	void _handleCreateRoom(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatCreateRoom* message);

	void _handleDestroyRoom(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatDestroyRoom* message);


	//class Room User Management
	void _handleBanAvatarFromRoom(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatBanAvatarFromRoom* message);

	void _handleUnbanAvatarFromRoom(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatUnbanAvatarFromRoom* message);

	void _handleInviteAvatarToRoom(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatInviteAvatarToRoom* message);

	void _handleUninviteAvatarToRoom(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatUninviteAvatarToRoom* message);

	void _handleAddModToRoom(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatAddModToRoom* message);

	void _handleRemoveModFromRoom(
		const std::shared_ptr<swganh::connection::ConnectionClientInterface>& client,
		swganh::messages::ChatRemoveModFromRoom* message);

};

}}  // namespace swganh::chat
