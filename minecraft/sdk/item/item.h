#pragma once

#include <string>

namespace semita {
    class block;
    class item_stack_base;

    class item {
    public:
        [[nodiscard]] std::string get_name();
        [[nodiscard]] float get_destroy_speed(const item_stack_base& stack, const block& block);
        [[nodiscard]] bool can_destroy(const block& block);
    };
}