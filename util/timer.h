#pragma once

#include <chrono>
#include "logger.h"

namespace semita {
    class timer {
    public:
        using timestamp_t = std::chrono::time_point<std::chrono::high_resolution_clock>;
        using duration_t = std::chrono::duration<double, std::milli>;

        timer() : m_start(std::chrono::high_resolution_clock::now()) {}

        void restart() {
            m_start = std::chrono::high_resolution_clock::now();
        }

        [[nodiscard]] duration_t duration() const {
            return std::chrono::high_resolution_clock::now() - m_start;
        }

        [[nodiscard]] double count() const {
            return duration().count();
        }

        [[nodiscard]] bool exceeds(const double ms) const {
            return count() > ms;
        }

        [[nodiscard]] timestamp_t start() const {
            return m_start;
        }

    protected:
        timestamp_t m_start{ };
    };

    class scoped_timer : public timer {
    public:
        explicit scoped_timer(std::string_view name) : m_name(name) {}

        ~scoped_timer() {
            logger::get()->debug("{} took {:.3f} ms", m_name, count());
        }

    private:
        std::string_view m_name;
    };
}