#pragma once

#include <array>
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include <chrono>

namespace semita::math {
    using duration_t = std::chrono::duration<double, std::milli>;

    static constexpr std::array cardinal_directions {
        glm::ivec3{ 1, 0, 0 },
        glm::ivec3{ -1, 0, 0 },
        glm::ivec3{ 0, 0, 1 },
        glm::ivec3{ 0, 0, -1 }
    };

    static constexpr std::array diagonal_directions {
        glm::ivec3{ 1, 0, 1 },
        glm::ivec3{ 1, 0, -1 },
        glm::ivec3{ -1, 0, 1 },
        glm::ivec3{ -1, 0, -1 }
    };

    inline glm::vec3 direction_vector(const float yaw, const float pitch) {
        const float yaw_radians = glm::radians(yaw);
        const float pitch_radians = glm::radians(pitch);
        const float m = cosf(pitch_radians);

        return glm::vec3{
            -m * sinf(yaw_radians),
            -sinf(pitch_radians),
            m * cosf(yaw_radians)
        };
    }
}
