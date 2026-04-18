#include "item_stack_base.h"

#include <libhat/Access.hpp>

namespace semita {
    item* item_stack_base::get_item() {
        const auto i = hat::member_at<item**>(this, 0x8); // WeakPtr<item>
        return i ? *i : nullptr;
    }

    block* item_stack_base::get_block() {
        return hat::member_at<block*>(this, 0x18);
    }

    uint8_t item_stack_base::get_count() {
        return hat::member_at<uint8_t>(this, 0x22);
    }
}