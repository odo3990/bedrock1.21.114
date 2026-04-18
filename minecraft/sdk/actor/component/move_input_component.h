#pragma once

#include "minecraft/sdk/actor/entity_context.h"

#include <libhat/fixed_string.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace semita {
    struct move_input_state {
        std::byte pad[0x6];
        bool m_jump_down;
        std::byte pad2[0x21];
    };

    struct move_input_component : entity_component {
        static constexpr hat::fixed_string type_name = "struct MoveInputComponent";

        move_input_state m_input_state;
        move_input_state m_raw_input_state;
        std::byte pad[0x8];
        glm::vec2 m_move;
        glm::vec2 m_look_delta;
        glm::vec2 m_interact_direction;
        glm::vec3 m_displacement;
        glm::vec3 m_displacement_delta;
        glm::vec3 m_camera_orientation;
        bool m_sneaking;
        bool m_sprinting;
        bool m_up;
        bool m_down;
        bool m_jumping;
        bool m_jumping_in_water;
        bool m_locked_state;
        bool m_sneak;
        bool m_auto_jump;
        std::byte pad2[0x2];

        void set_jumping(const bool jumping = true) {
            m_jumping = jumping;
            m_input_state.m_jump_down = jumping;
            m_raw_input_state.m_jump_down = jumping;
        }
    };
}
