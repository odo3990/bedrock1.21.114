#include "filling_container.h"

#include "util/memory.h"

namespace semita {
    void filling_container::swap_slots(int from, int to) {
        return memory::call_virtual<45, void>(this, from, to);
    }

    int filling_container::get_size() {
        return memory::call_virtual<20, int>(this);
    }
}