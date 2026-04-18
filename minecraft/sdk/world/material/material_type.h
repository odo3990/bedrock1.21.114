#pragma once

#include <cstdint>

namespace semita {
    enum class material_type : uint32_t {
        air                         = 0,
        dirt                        = 1,
        wood                        = 2,
        metal                       = 3,
        grate                       = 4,
        water                       = 5,
        lava                        = 6,
        leaves                      = 7,
        plant                       = 8,
        solid_plant                 = 9,
        fire                        = 10,
        glass                       = 11,
        explosive                   = 12,
        ice                         = 13,
        powder_snow                 = 14,
        cactus                      = 15,
        portal                      = 16,
        stone_decoration            = 17,
        bubble                      = 18,
        barrier                     = 19,
        decoration_solid            = 20,
        client_request_placeholder  = 21,
        structure_void              = 22,
        solid                       = 23,
        non_solid                   = 24,
        any                         = 25,
    };

}
