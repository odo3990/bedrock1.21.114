#pragma once

#include "minecraft/event/event_manager.h"
#include "minecraft/event/events/message_event.h"
#include "minecraft/event/events/packet_event.h"
#include "minecraft/hook/hook.h"
#include "minecraft/sdk/network/loopback_packet_sender.h"
#include "minecraft/sdk/network/packet/packet.h"
#include "minecraft/sdk/network/packet/type/login_packet.h"
#include "minecraft/sdk/network/packet/type/text_packet.h"
#include "util/logger.h"

#include <string>

namespace semita {
    struct packet_hook : hook {
        using original_t = void(__fastcall*)(loopback_packet_sender*, packet*);

        static void init() {}

        static void handle_login(const login_packet* pkt) {
            if (!pkt) {
                return;
            }

            const auto parsed = parse_login_client_data(*pkt);
            if (!parsed) {
                logger::get()->info(
                    "login: protocol={}, connection_request={} bytes, client data parse failed",
                    pkt->m_protocol_version,
                    pkt->m_connection_request.size()
                );
                return;
            }

            const auto optional_int = [](const std::optional<int32_t>& value) -> std::string {
                return value ? std::to_string(*value) : "n/a";
            };

            const auto game_version = parsed->m_game_version.value_or("n/a");

            logger::get()->info(
                "login: protocol={}, current_input_mode={}, default_input_mode={}, device_os={}, ui_profile={}, game_version={}",
                pkt->m_protocol_version,
                optional_int(parsed->m_current_input_mode),
                optional_int(parsed->m_default_input_mode),
                optional_int(parsed->m_device_os),
                optional_int(parsed->m_ui_profile),
                game_version
            );
        }

        static void callback(loopback_packet_sender* this_, packet* pkt) {
            if (!pkt) {
                return original(this_, pkt);
            }

            packet_event ev(packet_direction::send, pkt, this_);
            event_manager::get().call(ev);
            if (ev.cancelled()) {
                return;
            }

            if (pkt->get_id() == packet_id::login) {
                handle_login(reinterpret_cast<login_packet*>(pkt));
            } else if (pkt->get_id() == packet_id::text) {
                message_event event(reinterpret_cast<text_packet*>(pkt));
                event_manager::get().call(event);

                if (event.cancelled()) {
                    return;
                }
            }

            return original(this_, pkt);
        }

        static inline original_t original{ nullptr };
    };
}
