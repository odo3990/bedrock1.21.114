#pragma once

#include <compare>
#include <cstdint>

namespace semita {
    struct tick {
        uint64_t tick_id;

        [[nodiscard]] constexpr bool operator==(const tick& other) const noexcept = default;

        [[nodiscard]] constexpr std::strong_ordering operator<=>(const tick& other) const noexcept {
            return tick_id <=> other.tick_id;
        }
    };
}
