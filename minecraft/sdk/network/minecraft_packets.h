#pragma once

#include <memory>

#include "packet/packet.h"

namespace semita {
    class minecraft_packets {
    public:
        static std::shared_ptr<packet> create_packet(packet_id id);
    };
}
