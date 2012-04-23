// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#ifndef ANH_NETWORK_SOE_DECOMPRESSION_FILTER_H_
#define ANH_NETWORK_SOE_DECOMPRESSION_FILTER_H_

#include <cstdint>
#include <memory>
#include <vector>

#include <zlib.h>

namespace anh {

    class ByteBuffer;

namespace network {
namespace soe {

    class Session;

namespace filters {

    /**
     * @brief Decompresses packet data that is flagged as compressed.
     */
    class DecompressionFilter {
    public:
        /**
         * @param max_receive_size Maximum allowed size of incoming messages.
         */
        explicit DecompressionFilter(uint32_t max_message_size);
    
        void operator()(Session* session, ByteBuffer* message);
    
    private:
        DecompressionFilter();
    
    	void Decompress_(anh::ByteBuffer* buffer);
        
        uint32_t max_message_size_;
        
        z_stream zstream_;
        std::vector<uint8_t> decompression_output_;
    };

}}}} // namespace anh::network::soe::filters

#endif // ANH_NETWORK_SOE_DECOMPRESSION_FILTER_H_
