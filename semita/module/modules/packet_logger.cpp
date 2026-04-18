#include "packet_logger.h"

#include "minecraft/event/event_manager.h"
#include "util/logger.h"
#include "util/mc/game.h"
#include "util/mc/text_format.h"

namespace semita {
    packet_logger::packet_logger()
    : module("PacketLogger", "Logs packet traffic to the console for testing hooks and events.", key_type::i) {}

    void packet_logger::on_enable() {
        event_manager::get().listen<packet_event, &packet_logger::on_packet>(this);
        game::display_message("{}Enabled {}{}", text_format::green, name(), text_format::reset);
    }

    void packet_logger::on_disable() {
        event_manager::get().mute<packet_event, &packet_logger::on_packet>();
        game::display_message("{}Disabled {}{}", text_format::red, name(), text_format::reset);
    }

    void packet_logger::on_packet(packet_event& event) {

    }
}
