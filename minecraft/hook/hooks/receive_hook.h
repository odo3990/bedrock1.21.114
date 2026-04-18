#pragma once

#include "minecraft/event/event_manager.h"
#include "minecraft/event/events/packet_event.h"
#include "minecraft/sdk/network/minecraft_packets.h"
#include "minecraft/sdk/network/packet/packet_id_list.h"
#include "util/logger.h"

#include <MinHook.h>
#include <memory>
#include <array>
#include <unordered_map>

namespace semita {
    struct receive_hook {
        using original_t = void(*)(void*, void*, void*, const std::shared_ptr<packet>&);

        struct hook_entry {
            LPVOID target{ nullptr };
            original_t original{ nullptr };
        };

        static void init() {
            for (const auto id : listened_packet_ids) {
                if (id == packet_id::keep_alive) {
                    continue;
                }

                create_dispatch_hook(id);
            }

            logger::get()->info(
                "created {} receive hooks across {} packet listeners",
                m_originals_by_target.size(),
                m_hooks.size()
            );
        }

        static void shutdown() {
            for (const auto& [target, original] : m_originals_by_target) {
                if (!target) {
                    continue;
                }

                MH_DisableHook(target);
                MH_RemoveHook(target);
            }

            m_hooks.clear();
            m_originals_by_target.clear();
        }

        static void callback(void* handler, void* network_identifier, void* context, const std::shared_ptr<packet>& pkt) {
            if (!pkt) {
                return;
            }

            packet_event event(packet_direction::receive, pkt.get(), nullptr, handler, network_identifier, context);
            event_manager::get().call(event);
            if (event.cancelled()) {
                return;
            }

            const auto it = m_hooks.find(static_cast<int>(pkt->get_id()));
            if (it == m_hooks.end() || !it->second.original) {
                return;
            }

            return it->second.original(handler, network_identifier, context, pkt);
        }

    private:
        static void create_dispatch_hook(const packet_id id) {
            const auto pkt = minecraft_packets::create_packet(id);
            if (!pkt || !pkt->m_packet_handler_dispatcher) {
                return;
            }

            auto** vtable = *reinterpret_cast<void***>(pkt->m_packet_handler_dispatcher);
            if (!vtable || !vtable[1]) {
                return;
            }

            const auto target = vtable[1];
            const auto key = static_cast<int>(id);

            if (const auto it = m_originals_by_target.find(target); it != m_originals_by_target.end()) {
                m_hooks.insert_or_assign(key, hook_entry{ target, it->second });
                return;
            }

            original_t original = nullptr;
            if (const auto status = MH_CreateHook(target, reinterpret_cast<LPVOID>(&receive_hook::callback), reinterpret_cast<LPVOID*>(&original)); status != MH_OK) {
                logger::get()->error("failed to create receive hook for packet {}: {}", key, MH_StatusToString(status));
                return;
            }

            if (const auto status = MH_EnableHook(target); status != MH_OK) {
                logger::get()->error("failed to enable receive hook for packet {}: {}", key, MH_StatusToString(status));
                MH_RemoveHook(target);
                return;
            }

            m_originals_by_target.insert_or_assign(target, original);
            m_hooks.insert_or_assign(key, hook_entry{ target, original });
        }

        static inline constexpr auto listened_packet_ids = std::array{
            #define SEMITA_PACKET_ID_VALUE(name, value) packet_id::name,
            SEMITA_PACKET_ID_LIST(SEMITA_PACKET_ID_VALUE)
            #undef SEMITA_PACKET_ID_VALUE
        };

        static inline std::unordered_map<int, hook_entry> m_hooks{};
        static inline std::unordered_map<LPVOID, original_t> m_originals_by_target{};
    };
}
