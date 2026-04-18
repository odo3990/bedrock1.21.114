#pragma once

#include <algorithm>
#include <glm/common.hpp>
#include <glm/vec3.hpp>

namespace semita {
    struct aabb {
        glm::vec3 m_min;
        glm::vec3 m_max;

        [[nodiscard]] glm::vec3 closest_point(const glm::vec3& point) const {
            return {
                std::max(m_min.x, std::min(point.x, m_max.x)),
                std::max(m_min.y, std::min(point.y, m_max.y)),
                std::max(m_min.z, std::min(point.z, m_max.z))
            };
        }
    };
}
