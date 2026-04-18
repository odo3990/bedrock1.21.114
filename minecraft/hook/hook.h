#pragma once

#include <MinHook.h>

namespace semita {
    class hook {
    public:
        void shutdown() {
            if (m_target) {
                MH_DisableHook(m_target);
                MH_RemoveHook(m_target);
                m_target = nullptr;
            }
        }

        void set_target(LPVOID target) {
            m_target = target;
        }

        [[nodiscard]] LPVOID target() const {
            return m_target;
        }

    private:
        LPVOID m_target{ nullptr };
    };

    template <typename T>
    concept is_hook = requires {
        { T::callback };
        { T::original };
    };

    template <typename T>
    concept has_hook_init = requires {
        T::init();
    };

    template <typename T>
    concept has_hook_static_shutdown = requires {
        T::shutdown();
    };

    template <typename hook_t>
    void initialize_hook_lifecycle() {
        if constexpr (has_hook_init<hook_t>) {
            hook_t::init();
        }
    }

    template <typename hook_t>
    void shutdown_hook_lifecycle() {
        if constexpr (has_hook_static_shutdown<hook_t>) {
            hook_t::shutdown();
        }
    }
}
