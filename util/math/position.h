#pragma once

#include <glm/vec3.hpp>
#include <cmath>
#include <string>

namespace semita {
    using block_position = glm::ivec3;
    using block_pos = block_position;

    struct position_utils {
        static glm::ivec3 floor(const glm::vec3 vec) {
            return glm::ivec3{
                static_cast<int>(std::floor(vec.x)),
                static_cast<int>(std::floor(vec.y)),
                static_cast<int>(std::floor(vec.z))
            };
        }
    };

    struct block_pos_hash {
        size_t operator()(const block_pos& pos) const {
            const size_t h1 = std::hash<int>()(pos.x);
            const size_t h2 = std::hash<int>()(pos.y);
            const size_t h3 = std::hash<int>()(pos.z);

            size_t seed = h1;
            seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };
}
