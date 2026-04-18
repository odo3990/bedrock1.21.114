#pragma once

#include "filling_container.h"

namespace semita {
    class inventory : public filling_container {
    public:
        [[nodiscard]] item_stack* get_item(int slot);
    };
}