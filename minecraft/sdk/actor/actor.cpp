#include "actor.h"

#include "minecraft/signature/signature_result.h"
#include "minecraft/signature/registry/signature_registry.h"
#include <libhat/Access.hpp>

namespace semita {
    level* actor::get_level() {
        return hat::member_at<level*>(this, 0x1D8);
    }

    built_in_actor_components& actor::get_built_in_actor_components() {
        return hat::member_at<built_in_actor_components>(this, 0x218);
    }

    const glm::vec3& actor::get_position() {
        return get_built_in_actor_components().m_state_vector_component->m_position;
    }

    entity_context& actor::get_entity_context() {
        return hat::member_at<entity_context>(this, 0x8);
    }

    void actor::move(const glm::vec3& delta) {
        using func_t = void(__fastcall*)(actor*, const glm::vec3&);
        static auto fn = signature_value<&actor::move, func_t>();
        fn(this, delta);
    }
}
