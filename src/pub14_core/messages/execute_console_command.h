// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include <cstdint>
#include <string>
#include "anh/byte_buffer.h"
#include "base_swg_message.h"

namespace swganh {
namespace messages {

    struct ExecuteConsoleCommand : public BaseSwgMessage<ExecuteConsoleCommand>
    {
    	static uint16_t Opcount() { return 2; }
    	static uint32_t Opcode() { return 0xB1CFCE1C; }
    
    	std::string command;
    
    	void OnSerialize(anh::ByteBuffer& buffer) const {
    		buffer.write(command);
    	}
    
    	void OnDeserialize(anh::ByteBuffer buffer) {
    		command = buffer.read<std::string>();
    	}
    };

}} // namespace swganh::messages
