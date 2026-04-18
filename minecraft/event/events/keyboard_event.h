#pragma once

#include "minecraft/event/event.h"
#include "util/keyboard.h"

namespace semita {
    class keyboard_event : public cancellable_event {
    public:
        keyboard_event(const key_type key, const key_state action)
        : m_key(key), m_action(action) {}

        [[nodiscard]] key_type key() const {
            return m_key;
        }

        [[nodiscard]] key_state action() const {
            return m_action;
        }

    private:
        key_type m_key;
        key_state m_action;
    };
}