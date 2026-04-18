#include "player.h"

#include "component/jump_from_ground_request_component.h"
#include "minecraft/signature/signature_result.h"
#include <libhat/Access.hpp>

namespace semita {
    player_inventory* player::get_player_inventory() {
        return hat::member_at<player_inventory*>(this, 0x5B8);
    }

    gamemode* player::get_gamemode() {
        return hat::member_at<gamemode*>(this, 0xA78);
    }

    void local_player::apply_turn_delta(const glm::vec2& delta) {
        using func_t = void(__fastcall*)(local_player*, const glm::vec2&);
        static auto fn = signature_value<&local_player::apply_turn_delta, func_t>();
        fn(this, delta);
    }

    void local_player::jump_from_ground() {
        auto& entity_ctx = get_entity_context();
        entity_ctx.add_component<jump_found_ground_request_component>();
    }
}
