#pragma once

#include "gui_data.h"
#include "../world/block_source.h"
#include "minecraft/sdk/actor/player.h"

namespace semita {
    class client_instance {
    public:
        [[nodiscard]] block_source* get_region();
        [[nodiscard]] local_player* get_local_player();
        [[nodiscard]] gui_data* get_gui_data();
    };
}
