// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include <cstdint>
#include "anh/byte_buffer.h"
#include "base_swg_message.h"

namespace swganh {
namespace messages {

    struct ClientInactivityMessage : public BaseSwgMessage<ClientInactivityMessage>
    {
    	static uint16_t Opcount() { return 2; }
    	static uint32_t Opcode() { return 0x0F5D5325; }

    	uint8_t inactivity_flag; // 0 = active, 1 = inactive
    	
    	void OnSerialize(anh::ByteBuffer& buffer) const
    	{
    		buffer.write(inactivity_flag);
    	}

    	void OnDeserialize(anh::ByteBuffer buffer)
    	{
    		inactivity_flag = buffer.read<uint8_t>();
    	}
    };

}} // namespace swganh::messages
