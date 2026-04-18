#pragma once

#include "gamemode.h"
#include "actor.h"

#include "minecraft/sdk/container/player_inventory.h"
#include "minecraft/sdk/tick.h"

namespace semita {
    class player : public mob {
    public:
        player_inventory* get_player_inventory();
        gamemode* get_gamemode();
    };

    class local_player : public player {
    public:
        void apply_turn_delta(const glm::vec2& delta);
        void jump_from_ground();
        void tick_world(const tick& current_tick);
    };
}
