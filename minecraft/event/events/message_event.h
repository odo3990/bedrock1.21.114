#pragma once

#include "minecraft/event/event.h"
#include "minecraft/sdk/network/packet/type/text_packet.h"

namespace semita {
    class message_event : public cancellable_event {
    public:
        explicit message_event(text_packet* pkt) : m_packet(pkt) {}

        text_packet* get_packet() const {
            return m_packet;
        }

    private:
        text_packet* m_packet{ nullptr };
    };
}
