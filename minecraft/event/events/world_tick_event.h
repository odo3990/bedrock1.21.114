#pragma once

#include "minecraft/event/event.h"
#include "minecraft/sdk/tick.h"

namespace semita {
    class world_tick_event : public event {
    public:
        explicit world_tick_event(const tick& current_tick)
        : m_tick(current_tick) {}

        [[nodiscard]] const tick& current_tick() const {
            return m_tick;
        }

    private:
        tick m_tick;
    };
}
