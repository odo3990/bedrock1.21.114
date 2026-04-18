#pragma once

#include <vector>

#include "container.h"

namespace semita {
    class filling_container : public container {
    public:
        void swap_slots(int from, int to);
        [[nodiscard]] int get_size();

        [[nodiscard]] std::vector<item_stack>* get_items();
    };
}