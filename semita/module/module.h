#pragma once

#include <string>
#include <utility>

#include "util/keyboard.h"

namespace semita {
    class module {
    public:
        module(std::string name, std::string description, const key_type keybind)
        : m_name(std::move(name)), m_description(std::move(description)), m_keybind(keybind) {}

        virtual ~module() = default;

        [[nodiscard]] const std::string& name() const {
            return m_name;
        }

        [[nodiscard]] const std::string& description() const {
            return m_description;
        }

        [[nodiscard]] key_type keybind() const {
            return m_keybind;
        }

        [[nodiscard]] bool enabled() const {
            return m_enabled;
        }

        bool set_enabled(const bool enabled) {
            if (m_enabled == enabled) {
                return false;
            }

            m_enabled = enabled;
            if (m_enabled) {
                on_enable();
            } else {
                on_disable();
            }

            return true;
        }

        bool toggle() {
            return set_enabled(!m_enabled);
        }

        virtual void on_enable() {}
        virtual void on_disable() {}

    private:
        std::string m_name;
        std::string m_description;
        key_type m_keybind{ };
        bool m_enabled{ false };
    };
}
