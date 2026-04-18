#pragma once

namespace semita {
    enum class event_priority {
        very_high,
        high,
        medium,
        low,
        very_low,
        count
    };

    static inline constexpr size_t priority_count = static_cast<size_t>(event_priority::count);
}