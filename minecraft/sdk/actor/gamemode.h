#pragma once
#include "actor.h"
#include "minecraft/sdk/item/item_stack.h"
#include "util/math/position.h"

namespace semita {
    struct interaction_result {
        enum class result : int {
            fail = 0,
            success = 1,
            swing = 2
        };

        result m_result;
    };

    class gamemode {
    public:
        virtual ~gamemode() = default;

        virtual bool start_destroy_block(const block_pos& pos, int face, bool& has_destroyed);
        virtual bool destroy_block(const block_pos& pos, int face);
        virtual bool continue_destroy_block(const block_pos& pos, int face, const glm::vec3& player_pos, bool& has_destroyed);
        virtual void stop_destroy_block(const block_pos& pos);

        virtual void start_build_block(const block_pos& pos, int face);
        virtual void build_block(const block_pos& pos, int face, bool);
        virtual bool continue_build_block(const block_pos& pos, int face);
        virtual void stop_build_block();

        virtual void tick();

        virtual float pick_range(const class input_mode& current_input);

        virtual bool use_item(item_stack& stack);
        virtual bool use_item_attack(item_stack& item);
        virtual interaction_result use_item_on(item_stack& stack, const block_pos& pos, int face, const glm::vec3& hit, const block* target, bool);

        virtual bool attack(actor& target);

        virtual void release_using_item();
    };
}
