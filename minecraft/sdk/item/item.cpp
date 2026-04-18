#include "item.h"

#include <libhat/Access.hpp>

#include "spdlog/logger.h"
#include "util/logger.h"
#include "util/memory.h"

namespace semita {
    std::string item::get_name() {
        return hat::member_at<std::string>(this, 0xD8);
    }

    float item::get_destroy_speed(const item_stack_base& stack, const block& b) {
        return memory::call_virtual<83, float>(this, stack, b);
    }

    bool item::can_destroy(const block& block) {
        return memory::call_virtual<32, bool>(this, block);
    }
}
