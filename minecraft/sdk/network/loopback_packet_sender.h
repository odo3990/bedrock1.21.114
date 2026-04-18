#pragma once

#include "packet/packet.h"

namespace semita {
    class loopback_packet_sender {
    public:
        void send(packet* pkt);
    };
}
