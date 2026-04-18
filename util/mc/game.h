#pragma once

#include <string>
#include <format>
#include <glm/vec3.hpp>

namespace semita {
    struct game {
        static void display_message(const std::string& message);

        template <typename... args_t>
        static void display_message(std::format_string<args_t...> fmt, args_t&&... args) {
            const auto msg = std::format(fmt, std::forward<args_t>(args)...);
            display_message(msg);
        }

        static void look_at(const glm::vec3& position);

        static void select_slot(uint8_t slot);
    };
}
