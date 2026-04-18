#pragma once

#include "minecraft/event/event_manager.h"
#include "minecraft/event/events/tick_event.h"
#include "minecraft/hook/hook.h"
#include "minecraft/sdk/client/client_instance.h"

namespace semita {
    struct tick_hook : hook {
        using original_t = __int64(__fastcall*)(client_instance*, bool);

        static void init() {}

        static __int64 callback(client_instance* this_, const bool is_initialized) {
            tick_event ev(this_);
            event_manager::get().call(ev);

            return original(this_, is_initialized);
        }

        static inline original_t original{ nullptr };
    };
}
