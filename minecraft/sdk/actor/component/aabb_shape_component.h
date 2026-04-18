#pragma once

#include "util/math/aabb.h"

#include <glm/vec2.hpp>


namespace semita {
    struct aabb_shape_component {
        aabb m_aabb;
        glm::vec2 m_dimension;
    };
}
