#pragma once

#include "minecraft/sdk/world/block/block.h"
#include "item.h"

namespace semita {
    class block;

    class item_stack_base {
    public:
        [[nodiscard]] item* get_item();
        [[nodiscard]] block* get_block();
        [[nodiscard]] uint8_t get_count();
    };
}
