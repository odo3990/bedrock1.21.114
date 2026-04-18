#pragma once

#include "minecraft/sdk/world/material/material.h"

#include <string>

namespace semita {
    class block_type {
    public:
        std::string get_name();
        std::string get_item_group();
        material* get_material();
    };
}