#ifndef ANH_PACKETS_LOGINENUMCLUSTER_H
#define ANH_PACKETS_LOGINENUMCLUSTER_H

#include <cstdint>
#include <algorithm>
#include <list>
#include <string>
#include "anh/byte_buffer.h"
#include "packets/base_swg_packet.h"

// Originates on Server
// http://wiki.swganh.org/index.php/LoginEnumCluster
namespace packets {

struct Cluster {
    uint32_t server_id;
    std::string server_name;
    // D = 3600 * GMTOffset
    int32_t distance;
};

struct LoginEnumCluster : public BaseSwgPacket<LoginEnumCluster> {
    static const uint16_t opcount = 3;
    static const uint32_t opcode = 0xC11C63B9;

    std::list<Cluster> servers;
    uint32_t max_account_chars;
    
    void onSerialize(anh::ByteBuffer& buffer) const {
        buffer.write<uint32_t>(servers.size());
        std::for_each(servers.begin(), servers.end(), [&buffer] (Cluster cluster){
            buffer.write<int32_t>(cluster.server_id);
            buffer.write<std::string>(cluster.server_name);
            buffer.write<int32_t>(cluster.distance);
        });
        buffer.write<uint32_t>(max_account_chars);
    }

    void onDeserialize(anh::ByteBuffer buffer) {
        server_count = buffer.read<uint32_t>();
        for(uint32_t i = 0; i < server_count; i++)
        {
            Cluster cluster;
            cluster.server_id = buffer.read<int32_t>();
            cluster.server_name = buffer.read<std::string>();
            cluster.distance = buffer.read<int32_t>();
            servers.push_back(cluster);
        }
        max_account_chars = buffer.read<uint32_t>();
    }
};

} // packets

#endif // ANH_PACKETS_LOGINENUMCLUSTER_H