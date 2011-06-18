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

#include <list>
#include <tuple>
#include <gtest/gtest.h>
#include "anh/network/soe/packet_utilities.h"
#include "anh/byte_buffer.h"
#include "anh/utilities.h"

using namespace anh;
using namespace network::soe;
using namespace std;

namespace {

class PacketUtilitiesTests : public testing::Test {
protected:
    void SetUp() {}
    void TearDown() {}

    // Returns a tuple containing a list of swg message buffers that are all under
    // 255 bytes long and the expected multi data channel message when packed.
    tuple<list<shared_ptr<ByteBuffer>>, ByteBuffer> generateSmallMultiMessageData();

    // Returns a tuple containing a list of swg message buffers that are all over
    // 255 bytes long and the expected multi data channel message when packed.
    tuple<list<shared_ptr<ByteBuffer>>, ByteBuffer> generateLargeMultiMessageData();

    const static string long_string;
};

/// This test verifies that a proper data channel header can be constructed from a sequence id.
TEST_F(PacketUtilitiesTests, CanBuildDataChannelHeader) {
    ByteBuffer reference_header;
    reference_header.write<uint16_t>(anh::hostToBig<uint16_t>(0x09));
    reference_header.write<uint16_t>(anh::hostToBig<uint16_t>(0x01));

    ByteBuffer built_header = BuildDataChannelHeader(1);

    EXPECT_EQ(reference_header, built_header);
}

/// This test ensures that when packing only a single swg message no modifications are made
TEST_F(PacketUtilitiesTests, PackingSingleMessageDoesNotModifyIt) {
    auto small_buffer = make_shared<ByteBuffer>();
    small_buffer->write<uint32_t>(500);
    
    list<shared_ptr<ByteBuffer>> buffer_list(1, small_buffer); // Create a list of only 1 buffer
    
    ByteBuffer out_buffer = PackDataChannelMessages(buffer_list);

    // Expect that the output buffer has the same value in it as the input.
    EXPECT_EQ(500, out_buffer.read<int>());
}

/// This test ensures that when packing multiple swg messages together that they produce a
/// single buffer with a 0x0019 header.
TEST_F(PacketUtilitiesTests, PackingMultipleMessagesAddsMultiMessageHeader) {
    auto small_buffer = make_shared<ByteBuffer>();
    small_buffer->write<uint32_t>(500);
    
    list<shared_ptr<ByteBuffer>> buffer_list(2, small_buffer); // Create a list with more than 1 buffer

    ByteBuffer out_buffer = PackDataChannelMessages(buffer_list);

    EXPECT_EQ(anh::bigToHost<uint16_t>(0x19), out_buffer.read<uint16_t>());
}


/// This test ensures that when packing multiple swg messages that any of the messages with
/// a length smaller than 255 has an uint8_t size prefixed to them.
TEST_F(PacketUtilitiesTests, SmallSwgMessagesHave8ByteSizePrefix) {
    list<shared_ptr<ByteBuffer>> buffer_list;
    ByteBuffer expected_buffer;

    tie(buffer_list, expected_buffer) = generateSmallMultiMessageData();

    ByteBuffer out_buffer = PackDataChannelMessages(buffer_list);
    
    EXPECT_EQ(expected_buffer.read<uint16_t>(), out_buffer.read<uint16_t>());

    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(expected_buffer.read<uint8_t>(), out_buffer.read<uint8_t>()); // size
        EXPECT_EQ(expected_buffer.read<uint32_t>(), out_buffer.read<uint32_t>()); // data
    }
}

/// This test ensures that when packing multiple swg messages that any of the messages exceeding
/// a 255 length have a uint16_t size prefixed to them.
TEST_F(PacketUtilitiesTests, LargeSwgMessagesHaveBytePlus16ByteSizePrefix) {
    list<shared_ptr<ByteBuffer>> buffer_list;
    ByteBuffer expected_buffer;

    tie(buffer_list, expected_buffer) = generateLargeMultiMessageData();

    ByteBuffer out_buffer = PackDataChannelMessages(buffer_list);
    
    EXPECT_EQ(expected_buffer.read<uint16_t>(), out_buffer.read<uint16_t>());

    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(expected_buffer.read<uint8_t>(), out_buffer.read<uint8_t>()); // size
        EXPECT_EQ(expected_buffer.read<uint16_t>(), out_buffer.read<uint16_t>()); // size
        EXPECT_EQ(expected_buffer.read<string>(), out_buffer.read<string>()); // data
    }
}


// Implementation of the PacketUtilitiesTests's helper members

const string PacketUtilitiesTests::long_string = // This string is 300 bytes long
        "2d8h3941y88gpcu633t7a0o9j0p3658fpnxwlmcxgv9buxy8x2"
        "2d8h3941y88gpcu633t7a0o9j0p3658fpnxwlmcxgv9buxy8x2"
        "2d8h3941y88gpcu633t7a0o9j0p3658fpnxwlmcxgv9buxy8x2"
        "2d8h3941y88gpcu633t7a0o9j0p3658fpnxwlmcxgv9buxy8x2"
        "2d8h3941y88gpcu633t7a0o9j0p3658fpnxwlmcxgv9buxy8x2"
        "2d8h3941y88gpcu633t7a0o9j0p3658fpnxwlmcxgv9buxy8x2";

tuple<list<shared_ptr<ByteBuffer>>, ByteBuffer> PacketUtilitiesTests::generateSmallMultiMessageData() {
    // Create a small buffer with a single data value that is less than 255 bytes long
    auto small_buffer = make_shared<ByteBuffer>();
    small_buffer->write<uint32_t>(500); // This int is only 4 bytes long
    
    // Create a list of 3 of the previous buffers to simulate 3 swg messages being packed.
    list<shared_ptr<ByteBuffer>> buffer_list(3, small_buffer);

    // Create a buffer that holds the expected output from packing the above data.
    ByteBuffer expected_buffer;
    
    expected_buffer.write<uint16_t>(hostToBig<uint16_t>(0x19)); // header
    expected_buffer.write<uint8_t>(4); // size
    expected_buffer.write<int32_t>(500); // value
    expected_buffer.write<uint8_t>(4); // size
    expected_buffer.write<int32_t>(500); // value
    expected_buffer.write<uint8_t>(4); // size
    expected_buffer.write<int32_t>(500); // value

    // Return a tuple of the list of simulated swg messages and the expected buffer.
    return make_tuple(buffer_list, expected_buffer);
}

tuple<list<shared_ptr<ByteBuffer>>, ByteBuffer> PacketUtilitiesTests::generateLargeMultiMessageData() {
    // Create a large buffer with a length of 304 bytes (300 byte string + 4 byte string length)
    auto large_buffer = make_shared<ByteBuffer>();
    large_buffer->write<string>(long_string); // This int is only 4 bytes long
    
    // Create a list of 3 of the previous buffers to simulate 3 swg messages being packed.
    list<shared_ptr<ByteBuffer>> buffer_list(3, large_buffer);

    // Create a buffer that holds the expected output from packing the above data.
    ByteBuffer expected_buffer;
    
    expected_buffer.write<uint16_t>(hostToBig<uint16_t>(0x19)); // header
    expected_buffer.write<uint8_t>(0xFF); // large message byte
    expected_buffer.write<uint16_t>(hostToBig<uint16_t>(302)); // str length 300 + 2 byte size
    expected_buffer.write<string>(long_string); // value
    expected_buffer.write<uint8_t>(0xFF); // large message byte
    expected_buffer.write<uint16_t>(hostToBig<uint16_t>(302)); // str length 300 + 2 byte size
    expected_buffer.write<string>(long_string); // value
    expected_buffer.write<uint8_t>(0xFF); // large message byte
    expected_buffer.write<uint16_t>(hostToBig<uint16_t>(302)); // str length 300 + 2 byte size
    expected_buffer.write<string>(long_string); // value

    // Return a tuple of the list of simulated swg messages and the expected buffer.
    return make_tuple(buffer_list, expected_buffer);
}

}  // namespace
