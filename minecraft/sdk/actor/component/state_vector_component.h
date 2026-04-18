#pragma once

#include <glm/vec3.hpp>

#include "minecraft/sdk/actor/entity_context.h"
#include <libhat/fixed_string.hpp>

namespace semita {
    struct state_vector_component : entity_component {
        static constexpr hat::fixed_string type_name = "struct StateVectorComponent";

        glm::vec3 m_position;
        glm::vec3 m_previous_position;
        glm::vec3 m_position_delta;
    };

    static_assert(sizeof(state_vector_component) == 0x24);
}
