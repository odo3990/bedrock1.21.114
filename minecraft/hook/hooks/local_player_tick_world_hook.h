#pragma once

#include "minecraft/event/event_manager.h"
#include "minecraft/event/events/world_tick_event.h"
#include "minecraft/hook/hook.h"
#include "minecraft/sdk/actor/player.h"
#include "minecraft/sdk/tick.h"

namespace semita {
    struct local_player_tick_world_hook : hook {
        using original_t = void(__fastcall*)(local_player*, const tick&);

        static void init() {}

        static void callback(local_player* this_, const tick& current_tick) {
            world_tick_event event(current_tick);
            event_manager::get().call(event);

            return original(this_, current_tick);
        }

        static inline original_t original{ nullptr };
    };
}
