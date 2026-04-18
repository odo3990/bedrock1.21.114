#include "game_manager.h"

#include "event/event_manager.h"

namespace semita {
    game_manager::game_manager() {
        event_manager::get().listen<tick_event, &game_manager::on_tick>(this);
        event_manager::get().listen<render_event, &game_manager::on_render>(this);
    }

    game_manager::~game_manager() {
        event_manager::get().mute<tick_event, &game_manager::on_tick>();
        event_manager::get().mute<render_event, &game_manager::on_render>();
    }

    void game_manager::on_tick(const tick_event& event) {
        m_context.update(event.get_client_instance());
    }

    void game_manager::on_render(const render_event& event) {
        m_context.update(event.get_render_context());
    }

    const game_context& game_manager::get_context() const {
        return m_context;
    }
}
