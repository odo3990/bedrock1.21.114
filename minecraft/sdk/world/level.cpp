#include "level.h"

#include <libhat/Access.hpp>

namespace semita {
    hit_result* level::get_hit_result() {
        return hat::member_at<hit_result*>(this, 0x1E8);
    }
}
