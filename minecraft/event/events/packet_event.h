#pragma once

#include "minecraft/event/event.h"
#include "minecraft/sdk/network/loopback_packet_sender.h"

#include <cstdint>

namespace semita {
    enum class packet_direction : uint8_t {
        send,
        receive
    };

    class packet_event : public cancellable_event {
    public:
        packet_event(
            const packet_direction direction,
            packet* pkt,
            loopback_packet_sender* sender = nullptr,
            void* handler = nullptr,
            void* network_identifier = nullptr,
            void* context = nullptr
        )
        : m_direction(direction),
          m_packet(pkt),
          m_sender(sender),
          m_handler(handler),
          m_network_identifier(network_identifier),
          m_context(context) {}

        [[nodiscard]] packet_direction direction() const {
            return m_direction;
        }

        [[nodiscard]] bool incoming() const {
            return m_direction == packet_direction::receive;
        }

        [[nodiscard]] bool outgoing() const {
            return m_direction == packet_direction::send;
        }

        [[nodiscard]] loopback_packet_sender* get_sender() const {
            return m_sender;
        }

        [[nodiscard]] void* get_handler() const {
            return m_handler;
        }

        [[nodiscard]] void* get_network_identifier() const {
            return m_network_identifier;
        }

        [[nodiscard]] void* get_context() const {
            return m_context;
        }

        [[nodiscard]] packet* get_packet() const {
            return m_packet;
        }

    private:
        packet_direction m_direction;
        packet* m_packet{ nullptr };
        loopback_packet_sender* m_sender{ nullptr };
        void* m_handler{ nullptr };
        void* m_network_identifier{ nullptr };
        void* m_context{ nullptr };
    };
}
