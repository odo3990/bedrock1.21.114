#pragma once

#include "aabb_shape_component.h"
#include "actor_rotation_component.h"
#include "state_vector_component.h"

namespace semita {
    struct built_in_actor_components {
        state_vector_component* m_state_vector_component;
        aabb_shape_component*   m_aabb_shape_component;
        actor_rotation_component* m_actor_rotation_component;
        void* m_walk_animation_component;
    };
}
