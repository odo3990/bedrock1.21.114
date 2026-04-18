#pragma once

#include "packet_id_list.h"

namespace semita {
    enum class packet_id : int {
        #define SEMITA_PACKET_ID_ENTRY(name, value) name = value,
        SEMITA_PACKET_ID_LIST(SEMITA_PACKET_ID_ENTRY)
        #undef SEMITA_PACKET_ID_ENTRY
    };
}
