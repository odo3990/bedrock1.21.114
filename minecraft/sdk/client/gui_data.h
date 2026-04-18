#pragma once

#include <glm/vec2.hpp>
#include <string>

namespace semita {
    class gui_data {
    public:
        [[nodiscard]] const glm::vec2& get_window_size() const;
        [[nodiscard]] const glm::vec2& get_game_size() const;

        void display_client_message(const std::string& message);
    };
}
