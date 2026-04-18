#pragma once

#include "level.h"
#include "block/block.h"
#include "util/math/position.h"

namespace semita {
    class dimension;
    class level_chunk;
    class chunk_pos;

    class block_source {
    public:
        [[nodiscard]] level* get_level();
        [[nodiscard]] dimension* get_dimension();

        [[nodiscard]] level_chunk* get_chunk(int x, int z);
        [[nodiscard]] level_chunk* get_chunk(const chunk_pos& pos);
        [[nodiscard]] level_chunk* get_chunk_at(const block_pos& pos);

        [[nodiscard]] short get_max_height();
        [[nodiscard]] short get_min_height();

        [[nodiscard]] block* get_block(const block_pos& pos);
        [[nodiscard]] bool has_block(const block_pos& pos);

        [[nodiscard]] bool is_solid_blocking_block(const block_pos& pos);
    };
}