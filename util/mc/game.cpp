#include "game.h"

#include "semita/client/client.h"

namespace semita {
    void game::display_message(const std::string& message) {
        if (const auto ci = get<game_manager>().get_context().get_client_instance()) {
            ci->get_gui_data()->display_client_message(message);
        }
    }

    void game::look_at(const glm::vec3& position) {
        const auto player = get<game_manager>().get_context().local_player();
        if (!player) {
            return;
        }

        const auto& components = player->get_built_in_actor_components();
        const auto player_pos = components.m_state_vector_component->m_position;
        const auto player_rot = components.m_actor_rotation_component->m_rotation;

        const auto position_delta = position - player_pos;
        const float target_yaw = glm::degrees(std::atan2(-position_delta.x, position_delta.z));
        const float horizontal_dist = std::sqrt(position_delta.x * position_delta.x + position_delta.z * position_delta.z);
        const float target_pitch = glm::degrees(-std::atan2(position_delta.y, horizontal_dist));

        float delta_yaw = std::fmod((target_yaw - player_rot.y + 540.0f), 360.0f) - 180.0f;
        float delta_pitch = target_pitch - player_rot.x;

        player->apply_turn_delta({ delta_pitch, delta_yaw });
    }

    void game::select_slot(const uint8_t slot) {
        if (const auto player = get<game_manager>().get_context().local_player()) {
            player->get_player_inventory()->set_selected_slot(slot);
        }
    }
}
