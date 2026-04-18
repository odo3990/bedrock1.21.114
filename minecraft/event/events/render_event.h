#pragma once

#include "minecraft/event/event.h"
#include "minecraft/sdk/render/render_context.h"
#include "minecraft/sdk/render/screen_view.h"

namespace semita {
    class render_event : public event {
    public:
        render_event(screen_view* view, minecraft_ui_render_ctx* ctx)
        : m_view(view), m_ctx(ctx) {}

        [[nodiscard]] screen_view* get_screen_view() const {
            return m_view;
        }

        [[nodiscard]] minecraft_ui_render_ctx* get_render_context() const {
            return m_ctx;
        }

    private:
        screen_view* m_view;
        minecraft_ui_render_ctx* m_ctx;
    };
}