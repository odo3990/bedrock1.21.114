#pragma once

#include "../math/position.h"
#include "minecraft/sdk/world/block/block.h"
#include "minecraft/sdk/item/item_stack.h"
#include "minecraft/sdk/world/hit_result.h"

namespace semita {
    struct world {
        [[nodiscard]] static block* block_at(const block_pos& pos);
        [[nodiscard]] static block* block_at(int x, int y, int z);
        [[nodiscard]] static block* block_at(const block_pos& pos, facing dir);
        [[nodiscard]] static block* landing_block_at(const block_pos& pos);

        [[nodiscard]] static bool is_landing_safe(const block_pos& pos);
        [[nodiscard]] static bool is_air(const block* b);
        [[nodiscard]] static bool is_solid(const block* b);
        [[nodiscard]] static bool is_walkable(const block* b);
        [[nodiscard]] static bool is_breakable(const block* b);
        [[nodiscard]] static bool is_liquid(const block* b);

        [[nodiscard]] static float destroy_duration(item_stack* stack, const block* block);
    };
}