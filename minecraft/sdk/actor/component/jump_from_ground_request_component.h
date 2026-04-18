#pragma once

#include "minecraft/sdk/actor/entity_context.h"

#include <libhat/fixed_string.hpp>

namespace semita {
    struct jump_found_ground_request_component : entity_component {
        static constexpr hat::fixed_string type_name = "struct JumpFromGroundRequestComponent";
    };

    struct on_ground_flag_component : entity_component {
        static constexpr hat::fixed_string type_name = "struct OnGroundFlagComponent";
    };
}