#pragma once

#include "container_type.h"
#include "minecraft/sdk/world/block_source.h"

namespace semita {
    class item_stack;

    class container {
    public:
        [[nodiscard]]  container_type get_container_type();

        [[nodiscard]] int empty_slot_count();

        [[nodiscard]] int first_empty_slot();

        [[nodiscard]] int first_item_slot();

        [[nodiscard]] bool is_empty();

        void drop_slot_content(block_source& region, const block_pos& pos, bool random_direction, int slot);
    };
}
