#pragma once

#include <glm/vec3.hpp>

#include "util/math/position.h"

namespace semita {
    enum class hit_type {
        block,
        actor,
        far_actor,
        none
    };

    enum class facing : int {
        down = 0,
        up = 1,
        north = 2,
        south = 3,
        west = 4,
        east = 5,
    };

    inline glm::ivec3 facing_to_direction(const facing face) {
        switch (face) {
            case facing::down: return {0, -1, 0};
            case facing::up: return {0, 1, 0};
            case facing::north: return {0, 0, -1};
            case facing::south: return {0, 0, 1};
            case facing::west: return {-1, 0, 0};
            case facing::east: return {1, 0, 0};
            default: return {0, 0, 0};
        }
    }

    struct weak_entity_storage {
        char pad[0x10];
        uint32_t id;
        char pad2[0x4];
    };

    struct hit_result {
        glm::vec3 m_start_position;
        glm::vec3 m_direction;
        hit_type m_type;
        facing m_facing;
        block_pos m_block_position;
        glm::vec3 m_position;
        weak_entity_storage m_entity;
        bool m_liquid_hit;
        facing m_liquid_facing;
        glm::vec3 m_liquid_position;
        bool m_idk;
    };
}
