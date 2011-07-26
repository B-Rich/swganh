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

#ifndef CONNECTION_MESSAGES_SELECT_CHARACTER_MESSAGE_H_
#define CONNECTION_MESSAGES_SELECT_CHARACTER_MESSAGE_H_

#include <cstdint>
#include "anh/byte_buffer.h"
#include "swganh/base/swg_message.h"

namespace connection {
namespace messages {
    
struct SelectCharacter : public swganh::base::SwgMessage<SelectCharacter> {
    static const uint16_t opcount = 2;
    static const uint32_t opcode = 0xB5098D76;    
    
    uint64_t character_id;

    void onSerialize(anh::ByteBuffer& buffer) const {
        buffer.write(character_id);	
    }

    void onDeserialize(anh::ByteBuffer buffer) {
    	character_id = buffer.read<uint64_t>();
    }
};

}}  // namespace connection::messages

#endif  // CONNECTION_MESSAGES_SELECT_CHARACTER_MESSAGE_H_
