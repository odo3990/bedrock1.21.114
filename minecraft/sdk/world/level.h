#pragma once

#include "hit_result.h"

namespace semita {
    class level {
    public:
        [[nodiscard]] hit_result* get_hit_result();
    };
}
