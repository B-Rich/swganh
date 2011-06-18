/*
 This file is part of MMOServer. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2010 The SWG:ANH Team

 MMOServer is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 MMOServer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with MMOServer.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ANH_NETWORK_SOE_PACKET_UTILITIES_H_
#define ANH_NETWORK_SOE_PACKET_UTILITIES_H_

#include <cstdint>
#include <list>
#include "anh/byte_buffer.h"

namespace anh {
namespace network {
namespace soe {

/**
 * Builds a data channel message header with the provided sequence.
 *
 * @param sequence The sequence of the data channel message header being created.
 * @return A byte buffer containing the fully constructed data channel message header.
 */
anh::ByteBuffer BuildDataChannelHeader(uint16_t sequence);

/**
 * Packs a list of game messages into a single message body.
 *
 * @param data_list A list of game messages to pack.
 * @return A single data channel message containing 1 or more game messages.
 */
anh::ByteBuffer PackDataChannelMessages(std::list<anh::ByteBuffer>& data_list);

}}}  // namespace anh::network::soe

#endif // ANH_NETWORK_SOE_PACKET_UTILITIES_H_
