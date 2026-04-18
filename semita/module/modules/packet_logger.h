#pragma once

#include "minecraft/event/events/packet_event.h"
#include "semita/module/module.h"

namespace semita {
    class packet_logger final : public module {
    public:
        packet_logger();

        void on_enable() override;
        void on_disable() override;

    private:
        void on_packet(packet_event& event);
    };
}
