#pragma once

#include "inventory.h"

namespace semita {
    class item;

    class player_inventory {
    public:
        [[nodiscard]] int& selected_slot();
        [[nodiscard]] inventory* get_inventory();

        [[nodiscard]] item_stack* get_held_item_stack();
        [[nodiscard]] item* get_held_item();

        void set_selected_slot(int slot);
    };
}