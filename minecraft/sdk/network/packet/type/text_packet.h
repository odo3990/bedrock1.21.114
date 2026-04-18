#pragma once

#include <optional>
#include <string>
#include <vector>

#include "minecraft/sdk/network/packet/packet.h"

namespace semita {
    enum class text_packet_type : uint8_t {
        raw = 0,
        chat = 1,
        translate = 2,
        popup = 3,
        jukebox_popup = 4,
        tip = 5,
        system = 6,
        whisper = 7,
        announcement = 8,
        text_obj_whisper = 9,
        text_obj = 10,
        text_obj_announcement = 11
    };

    class text_packet final : public packet {
    public:
        text_packet_type m_type;
        std::string m_author;
        std::string m_message;
        std::optional<std::string> m_filtered;
        std::vector<std::string> m_parameters;
        bool m_localized;
        std::string m_xuid;
        std::string m_platform_id;
    };
}
