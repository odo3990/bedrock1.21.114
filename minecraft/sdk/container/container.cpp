#include "container.h"

#include <libhat/Access.hpp>

#include "util/memory.h"

namespace semita {
    container_type container::get_container_type() {
        return hat::member_at<container_type>(this, 0x8);
    }

    void container::drop_slot_content(block_source& region, const block_pos& pos, bool random_direction, int slot) {
        memory::call_virtual<18, void>(this, region, pos, random_direction, slot);
    }

    int container::empty_slot_count() {
        return memory::call_virtual<26, int>(this);
    }

    int container::first_empty_slot() {
        return memory::call_virtual<28, int>(this);
    }

    int container::first_item_slot() {
        return memory::call_virtual<29, int>(this);
    }

    bool container::is_empty() {
        return memory::call_virtual<42, bool>(this);
    }
}
