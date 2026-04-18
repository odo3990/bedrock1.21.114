#pragma once

#include "minecraft/sdk/actor/entity_context.h"

#include <libhat/fixed_string.hpp>

namespace semita {
    struct runtime_id_component : entity_component {
        static constexpr hat::fixed_string type_name = "struct RuntimeIDComponent";
        int64_t m_id;
    };
}