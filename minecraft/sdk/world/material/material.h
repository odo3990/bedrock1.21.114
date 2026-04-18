#pragma once

#include "material_type.h"

namespace semita {
    struct material {
        material_type m_type;
        bool          m_never_buildable;
        bool          m_liquid;
        bool          m_blocks_motion;
        bool          m_blocks_precipitation;
        bool          m_solid;
        bool          m_super_hot;
    };
}