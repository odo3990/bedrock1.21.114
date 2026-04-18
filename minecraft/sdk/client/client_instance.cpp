#include "client_instance.h"

#include "util/memory.h"
#include <libhat/access.hpp>

namespace semita {
    block_source* client_instance::get_region() {
        return memory::call_virtual_copy<30, block_source*>(this);
    }

    local_player* client_instance::get_local_player() {
        return memory::call_virtual<31, local_player*>(this);
    }

    gui_data* client_instance::get_gui_data() {
        return hat::member_at<gui_data*>(this, 0x578);
    }
}
