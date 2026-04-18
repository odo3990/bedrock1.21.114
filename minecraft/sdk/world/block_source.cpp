#include "block_source.h"

#include "util/memory.h"

namespace semita {
    level* block_source::get_level() {
        return memory::call_virtual<41, level*>(this);
    }

    dimension* block_source::get_dimension() {
        return memory::call_virtual<36, dimension*>(this);
    }

    level_chunk* block_source::get_chunk(int x, int z) {
        return memory::call_virtual<40, level_chunk*>(this, x, z);
    }

    level_chunk* block_source::get_chunk(const chunk_pos& pos) {
        return memory::call_virtual<39, level_chunk*>(this, pos);
    }

    level_chunk* block_source::get_chunk_at(const block_pos& pos) {
        return memory::call_virtual<38, level_chunk*>(this, pos);
    }

    short block_source::get_max_height() {
        return memory::call_virtual<34, short>(this);
    }

    short block_source::get_min_height() {
        return memory::call_virtual<33, short>(this);
    }

    block* block_source::get_block(const block_pos& pos) {
        return memory::call_virtual<2, block*>(this, pos);
    }

    bool block_source::has_block(const block_pos& pos) {
        return memory::call_virtual<6, bool>(this, pos);
    }

    bool block_source::is_solid_blocking_block(const block_pos& pos) {
        return memory::call_virtual<52, bool>(this, pos);
    }
}
