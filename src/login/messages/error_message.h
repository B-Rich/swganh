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

#ifndef LOGIN_MESSAGES_ERROR_MESSAGE_H_
#define LOGIN_MESSAGES_ERROR_MESSAGE_H_

#include <cstdint>
#include <string>
#include "anh/byte_buffer.h"
#include "swganh/base/swg_message.h"

namespace login {
namespace messages {
    
struct ErrorMessage : public swganh::base::SwgMessage<ErrorMessage> {
    static const uint16_t opcount = 3;
    static const uint32_t opcode = 0xB5ABF91A;
    
    std::string type;
    std::string message;
    bool force_fatal;
    
    void onSerialize(anh::ByteBuffer& buffer) const {
        buffer.write(type);
        buffer.write(message);
        buffer.write(force_fatal);
    }
    
    void onDeserialize(anh::ByteBuffer buffer) {
        type = buffer.read<std::string>();
        message = buffer.read<std::string>();
        force_fatal = buffer.read<bool>();
    }    
};

}}  // namespace login::messages

#endif  // LOGIN_MESSAGES_ERROR_MESSAGE_H_
