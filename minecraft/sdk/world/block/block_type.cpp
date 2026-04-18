#include "block_type.h"

#include <libhat/Access.hpp>

namespace semita {
    std::string block_type::get_name() {
        return hat::member_at<std::string>(this, 0x98);
    }

    std::string block_type::get_item_group() {
        return hat::member_at<std::string>(this, 0x170);
    }

    material* block_type::get_material() {
        return hat::member_at<material*>(this, 0x158);
    }
}
