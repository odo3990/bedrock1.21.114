#include "inventory.h"

#include "util/memory.h"

namespace semita {
    item_stack* inventory::get_item(const int slot)  {
        return memory::call_virtual_copy<7, item_stack*>(this, slot);
    }
}