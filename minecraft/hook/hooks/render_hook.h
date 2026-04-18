#pragma once

#include "minecraft/hook/hook.h"
#include "minecraft/sdk/render/render_context.h"
#include "minecraft/sdk/render/screen_view.h"
#include "minecraft/event/event_manager.h"
#include "minecraft/event/events/render_event.h"

namespace semita {
    struct render_hook : hook {
        using original_t = __int64(__fastcall*)(screen_view*, minecraft_ui_render_ctx&);

        static void init() {}

        static __int64 callback(screen_view* this_, minecraft_ui_render_ctx& ctx) {
            render_event ev(this_, &ctx);
            event_manager::get().call(ev);

            return original(this_, ctx);
        }

        static inline original_t original{ nullptr };
    };
}
