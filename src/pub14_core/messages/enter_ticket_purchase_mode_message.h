// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include <cstdint>
#include <string>
#include "anh/byte_buffer.h"
#include "base_swg_message.h"

namespace swganh {
namespace messages {

    struct EnterTicketPurchaseModeMessage : public BaseSwgMessage<EnterTicketPurchaseModeMessage>
    {
    	static uint16_t Opcount() { return 4; }
    	static uint32_t Opcode() { return 0x904DAE1A; }
    
    	std::string planet_name; // planet on which the terminal is located
    	std::string city_name; // city in which the terminal is located
    
    	void OnSerialize(anh::ByteBuffer& buffer) const
    	{
    		buffer.write(planet_name);
    		buffer.write(city_name);
    	}
    
    	void OnDeserialize(anh::ByteBuffer buffer)
    	{
    		planet_name = buffer.read<std::string>();
    		city_name = buffer.read<std::string>();
    	}
    };

}} // namespace swganh::messages
