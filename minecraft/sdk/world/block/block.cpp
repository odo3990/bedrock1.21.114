#include "block.h"

#include <libhat/access.hpp>

namespace semita {
    block_type* block::get_block_type() const {
        return hat::member_at<block_type*>(this, 0x78);
    }

    float block::get_destroy_speed() const {
        return hat::member_at<float>(this, 0xD4);
    }
}