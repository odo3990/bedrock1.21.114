#pragma once

#include "block_type.h"

namespace semita {
    class block {
    public:
        [[nodiscard]] block_type* get_block_type() const;
        [[nodiscard]] float get_destroy_speed() const;
    };
}
