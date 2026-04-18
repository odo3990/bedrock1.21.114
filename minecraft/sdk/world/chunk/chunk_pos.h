#pragma once

namespace semita {
    class chunk_pos {
    public:
        explicit constexpr chunk_pos(const int x = 0, const int z = 0)
        : m_x(x >> 4), m_z(z >> 4) {}

        [[nodiscard]] constexpr int x() const {
            return m_x;
        }

        [[nodiscard]] constexpr int z() const {
            return m_z;
        }

    private:
        int m_x;
        int m_z;
    };
}