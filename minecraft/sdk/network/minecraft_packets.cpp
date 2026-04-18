#include "minecraft_packets.h"

#include "minecraft/signature/signature_result.h"

namespace semita {
    std::shared_ptr<packet> minecraft_packets::create_packet(packet_id id) {
        using func_t = std::shared_ptr<packet>(__fastcall*)(int);
        static auto fn = signature_value<&minecraft_packets::create_packet, func_t>();
        return fn(static_cast<int>(id));
    }
}
