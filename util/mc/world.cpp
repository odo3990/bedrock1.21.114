#include "world.h"

#include "semita/client/client.h"
#include "minecraft/game_manager.h"

namespace semita {
    block* world::block_at(const block_pos& pos) {
        const auto region = get<game_manager>().get_context().region();
        if (!region) {
            return nullptr;
        }

        return region->get_block(pos);
    }

    block* world::block_at(const block_pos& pos, const facing dir) {
        return block_at(pos + facing_to_direction(dir));
    }

    block* world::block_at(const int x, const int y, const int z) {
        return block_at(block_pos{ x, y, z });
    }

    bool world::is_landing_safe(const block_pos& pos) {
        const auto b = block_at(pos, facing::down);
        return b && is_walkable(b);
    }

    bool world::is_air(const block* b) {
        return !b || b->get_block_type()->get_material()->m_type == material_type::air;
    }

    bool world::is_solid(const block* b) {
        return b && b->get_block_type()->get_material()->m_solid;
    }

    bool world::is_liquid(const block* b) {
        return b && b->get_block_type()->get_material()->m_liquid;
    }

    bool world::is_walkable(const block* b) {
        return is_solid(b) && !is_liquid(b) && !is_air(b);
    }

    bool world::is_breakable(const block* b) {
        return b && b->get_destroy_speed() > 0.0f && !is_air(b) && !is_liquid(b);
    }

    float world::destroy_duration(item_stack* stack, const block* block) {
        if (!stack || !block)
            return -1.0f;

        const auto item = stack->get_item();
        const float speed = item ? item->get_destroy_speed(*stack, *block) : 1.0f;
        const float hardness = block->get_destroy_speed();

        if (hardness <= 0.0f || speed <= 0.0f)
            return -1.0f;

        const float scale = item ? (item->can_destroy(*block) ? 0.033333335f : 0.01f) : 0.033333335f;
        const float progress_per_tick = (speed / hardness) * scale;

        if (progress_per_tick <= 0.0f)
            return -1.0f;

        return (1.0f / progress_per_tick) / 20.0f;
    }
}
