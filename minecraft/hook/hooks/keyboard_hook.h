#pragma once

#include "minecraft/hook/hook.h"
#include "minecraft/event/events/keyboard_event.h"
#include "minecraft/event/event_manager.h"
#include "minecraft/sdk/network/minecraft_packets.h"
#include <util/logger.h>

namespace semita {
    struct keyboard_hook : hook {
        using original_t = void(__fastcall*)(int, bool);

        static void init() {}

        static void callback(const int key, const bool state) {
            keyboard_event event(static_cast<key_type>(key), static_cast<key_state>(state));
            event_manager::get().call(event);

            if (event.cancelled()) {
               return;
            }

            return original(key, state);
        }

        static void feed(const key_type key, const key_state state) {
            original(static_cast<__int64>(key), static_cast<int>(state));
        }

        static inline original_t original{ nullptr };
    };
}
