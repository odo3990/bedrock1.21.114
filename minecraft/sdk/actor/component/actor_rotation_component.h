#pragma once

#include <glm/vec2.hpp>
#include <libhat/fixed_string.hpp>

namespace semita {
    struct actor_rotation_component {
        static constexpr hat::fixed_string type_name = "struct ActorRotationComponent";

        glm::vec2 m_rotation;
        glm::vec2 m_prev_rotation;
    };

    static_assert(sizeof(actor_rotation_component) == 0x10);
}
