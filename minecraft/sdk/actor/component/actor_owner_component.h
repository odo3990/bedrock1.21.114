#pragma once

#include "../actor.h"

namespace semita {
    struct actor_owner_component : entity_component {
        static constexpr hat::fixed_string type_name = "class ActorOwnerComponent";
        std::unique_ptr<actor> m_actor;
    };
}
