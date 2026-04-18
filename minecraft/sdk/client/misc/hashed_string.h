#pragma once

#include <cstdint>
#include <string>

namespace semita {
    class hashed_string {
    public:
        explicit hashed_string(std::string text) : m_text(std::move(text)) {
            compute_hash();
        }

        void compute_hash() {
            m_hash = 0xCBF29CE484222325ULL;
            if (m_text.empty())
                return;

            const char* textP = m_text.c_str();
            auto c = *textP;

            do {
                m_hash = c ^ 0x100000001B3ULL * m_hash;
                c = *++textP;
            } while (*textP);
        }

    private:
        uint64_t m_hash = 0;
        std::string m_text{};
    };
}