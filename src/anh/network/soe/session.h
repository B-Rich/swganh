/*
---------------------------------------------------------------------------------------
This source file is part of SWG:ANH (Star Wars Galaxies - A New Hope - Server Emulator)

For more information, visit http://www.swganh.com

Copyright (c) 2006 - 2010 The SWG:ANH Team
---------------------------------------------------------------------------------------
Use of this source code is governed by the GPL v3 license that can be found
in the COPYING file or at http://www.gnu.org/licenses/gpl-3.0.html

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
---------------------------------------------------------------------------------------
*/

#ifndef ANH_NETWORK_SOE_SESSION_H_
#define ANH_NETWORK_SOE_SESSION_H_

#include <array>
#include <list>
#include <memory>
#include <vector>

#include <tbb/atomic.h>
#include <tbb/concurrent_queue.h>
#include <boost/asio.hpp>

#include "anh/network/soe/protocol_packets.h"
#include "anh/network/soe/socket.h"

namespace anh {

// FORWARD DECLARATIONS
class ByteBuffer;
namespace event_dispatcher { class EventInterface; }

namespace network {
namespace soe {

// FORWARD DECLARATION
class Service;
class SoeProtocolFilter;
class SessionRequestFilter;

/**
 * @brief An estabilished connection between a SOE Client and a SOE Service.
 */
class Session : public std::enable_shared_from_this<Session> {
public:
    /**
     * Adds itself to the Session Manager.
     */
    Session(boost::asio::ip::udp::endpoint& remote_endpoint, Service* service);
    ~Session(void);

    /**
    * @return The current send sequence for the server.
    */
    uint16_t server_sequence() const;

    /**
    * Sends a data channel message to the remote client.
    *
    * Increases the server sequence count by 1 for each individual packet sent to the 
    * remote end. This call can result in multiple packets being generated depending on 
    * the size of the payload and whether or not it needs to be fragmented.
    *
    * @param data_channel_payload The payload to send in the data channel message(s).
    */
    void sendDataChannelMessage(anh::ByteBuffer data_channel_payload);

    std::vector<std::shared_ptr<anh::ByteBuffer>> getUnacknowledgedOutgoingMessages() const;

    /**
     * 
     */
    void SendMessage(std::shared_ptr<anh::event_dispatcher::EventInterface> message);

    /**
     * Clears each message pump.
     */
    void Update(void);

    /**
     * Closes the Session.
     */
    void Close(void);

    bool connected() { return connected_; }

    uint32_t connection_id() { return connection_id_; }

    boost::asio::ip::udp::endpoint& remote_endpoint() { return remote_endpoint_; }

    friend class SoeProtocolFilter;
    friend class SessionRequestFilter;
    friend class SessionTest;
private:
    typedef	std::map<uint16_t, std::shared_ptr<anh::ByteBuffer>>				SequencedMessageMap;
    typedef std::map<uint16_t, std::shared_ptr<anh::ByteBuffer>>::iterator		SequencedMessageMapIterator;

    void HandleSoeMessage(anh::ByteBuffer& message);
    void handleSessionRequest_(SessionRequest& packet);
    void handleMultiPacket_(MultiPacket& packet);
    void handleDisconnect_(Disconnect& packet);
    void handlePing_(Ping& packet);
    void handleNetStatsClient_(NetStatsClient& packet);
    void handleChildDataA_(ChildDataA& packet);
    void handleDataFragA_(DataFragA& packet);
    void handleAckA_(AckA& packet);
    void handleOutOfOrderA_(OutOfOrderA& packet);

    void SendSoePacket(std::shared_ptr<anh::ByteBuffer> message);

    bool SequenceIsValid_(const uint16_t& sequence);
    void AcknowledgeSequence_(const uint16_t& sequence);

    boost::asio::ip::udp::endpoint		remote_endpoint_; // ip_address
    Service*							service_; // owner

    SequencedMessageMap												sent_messages_;

    bool								connected_;

    // SOE Session Variables
    uint32_t							connection_id_;
    uint32_t							recv_buffer_size_;
    uint32_t							crc_length_;

    // Sequences
    uint16_t							last_acknowledged_sequence_;
    uint16_t							next_client_sequence_;
    uint16_t							current_client_sequence_;
    tbb::atomic<uint16_t>				server_sequence_;

    uint32_t							next_frag_size_;

    // Net Stats
    NetStatsServer						server_net_stats_;

    ChildDataA							outgoing_data_message_;
    
    tbb::concurrent_queue<anh::ByteBuffer> outgoing_data_messages_;

    std::list<anh::ByteBuffer>			incoming_fragmented_messages_;
    uint16_t							incoming_fragmented_total_len_;
    uint16_t							incoming_fragmented_curr_len_;
};

} // namespace soe
} // namespace network
} // namespace anh

#endif