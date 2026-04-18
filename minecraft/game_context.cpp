#include "game_context.h"

namespace semita {
    client_instance* game_context::get_client_instance() const {
        return m_client_instance;
    }

    local_player* game_context::local_player() const {
        return m_local_player;
    }

    block_source* game_context::region() const {
        return get_client_instance() ? get_client_instance()->get_region() : nullptr;
    }

    level* game_context::level() const {
        const auto player = this->local_player();
        return player ? player->get_level() : nullptr;
    }

    gamemode* game_context::game_mode() const {
        return local_player() ? local_player()->get_gamemode() : nullptr;
    }

    glm::vec3 game_context::player_position(const bool feet) const {
        const auto player = local_player();
        if (!player) {
            return glm::vec3{0.0f, 0.0f, 0.0f};
        }

        auto position = player->get_built_in_actor_components().m_state_vector_component->m_position;
        if (feet) {
            position.y -= 1.62f;
        }

        return position;
    }

    void game_context::update(client_instance* instance) {
        m_client_instance = instance;
        m_local_player = instance ? instance->get_local_player() : nullptr;
    }

    void game_context::update(minecraft_ui_render_ctx* ctx) {
        m_render_ctx = ctx;
        update(ctx ? ctx->m_client_instance : nullptr);
    }
}
