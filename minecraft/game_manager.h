#pragma once

#include "game_context.h"
#include "event/events/keyboard_event.h"
#include "event/events/render_event.h"
#include "event/events/tick_event.h"

namespace semita {
    class game_manager {
    public:
        game_manager();
        ~game_manager();

        void on_tick(const tick_event& event);
        void on_render(const render_event& event);

        [[nodiscard]] const game_context& get_context() const;

    private:
        game_context m_context{};
    };
}
