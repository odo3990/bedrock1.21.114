#pragma once

#include <type_traits>

namespace semita {
    class event { };

    class cancellable_event : public event {
    public:
        void set_cancelled(const bool cancelled) {
            m_cancelled = cancelled;
        }

        void cancel() {
            set_cancelled(true);
        }

        void resume() {
            set_cancelled(false);
        }

        [[nodiscard]] bool cancelled() const {
            return m_cancelled;
        }

    private:
        bool m_cancelled{ false };
    };

    template <typename T>
    concept is_event = std::is_base_of_v<event, T>;
}
