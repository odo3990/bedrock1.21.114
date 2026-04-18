#include "player_inventory.h"

#include "minecraft/sdk/item/item.h"
#include "minecraft/sdk/item/item_stack.h"

#include  <libhat/Access.hpp>

namespace semita {
    int& player_inventory::selected_slot() {
        return hat::member_at<int>(this, 0x10);
    }

    inventory* player_inventory::get_inventory() {
        return hat::member_at<inventory*>(this, 0xB8);
    }

    item_stack* player_inventory::get_held_item_stack() {
        const auto inv = get_inventory();
        return inv ? inv->get_item(selected_slot()) : nullptr;
    }

    item* player_inventory::get_held_item() {
        const auto stack = get_held_item_stack();
        return stack ? stack->get_item() : nullptr;
    }

    void player_inventory::set_selected_slot(const int slot) {
        selected_slot() = slot;
    }
}
