#pragma once
#include <glm/vec2.hpp>

namespace semita {
    struct rect {
        float left, right, top, bottom;

        explicit rect(const float left = 0, const float right = 0, const float top = 0, const float bottom = 0)
        : left(left), right(right), top(top), bottom(bottom) {}

        [[nodiscard]] float width() const {
            return right - left;
        }

        [[nodiscard]] float height() const {
            return bottom - top;
        }

        [[nodiscard]] glm::vec2 center() const {
            return { (left + right) * 0.5f, (top + bottom) * 0.5f };
        }
    };
}
