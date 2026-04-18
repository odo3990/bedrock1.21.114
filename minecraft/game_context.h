#pragma once

#include "sdk/client/client_instance.h"
#include "sdk/world/block_source.h"
#include "sdk/render/render_context.h"

namespace semita {
    class game_context {
    public:
        game_context() = default;

        [[nodiscard]] client_instance* get_client_instance() const;
        [[nodiscard]] local_player* local_player() const;
        [[nodiscard]] block_source* region() const;
        [[nodiscard]] level* level() const;
        [[nodiscard]] gamemode* game_mode() const;
        [[nodiscard]] glm::vec3 player_position(bool feet = false) const;

        void update(client_instance* instance);
        void update(minecraft_ui_render_ctx* ctx);

    private:
        class client_instance* m_client_instance = nullptr;
        class local_player* m_local_player = nullptr;
        minecraft_ui_render_ctx* m_render_ctx = nullptr;
    };
}
