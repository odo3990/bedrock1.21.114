#pragma once

#include "packet_id.h"

#include <string>
#include <chrono>

namespace semita {
    enum class packet_priority : uint32_t {
        immediate = 0,
        high = 1,
        medium = 2,
        low = 3,
    };

    enum class reliability : uint32_t {
        reliable = 0,
        reliable_ordered = 1,
        unreliable = 2,
        unreliable_sequenced = 3,
    };

    enum class compressibility : uint64_t {
        compressible = 0,
        uncompressible = 1,
    };

    class packet {
    public:
        packet_priority m_priority;
        reliability m_reliability;
        uint8_t m_client_sub_id;
        bool m_is_handled;
        std::chrono::steady_clock::time_point m_received;
        class packet_handler_dispatcher* m_packet_handler_dispatcher;
        int m_compressibility;

        virtual ~packet() = default;
        virtual packet_id get_id();
        virtual std::string get_name();
    };
}
