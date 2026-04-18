#pragma once

#include "component/built_in_actor_components.h"
#include "minecraft/sdk/world/level.h"
#include "entity_context.h"

namespace semita {
    class actor {
    public:
        [[nodiscard]] level* get_level();
        [[nodiscard]] built_in_actor_components& get_built_in_actor_components();
        [[nodiscard]] const glm::vec3& get_position();
        [[nodiscard]] entity_context& get_entity_context();

        void move(const glm::vec3& delta);
    };

    class mob : public actor {

    };
}
