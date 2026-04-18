#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "minecraft/sdk/network/packet/packet.h"

namespace semita {
    class set_actor_motion_packet final : public packet {
    public:
        int64_t m_id;
        glm::vec3 m_motion;
    };
}