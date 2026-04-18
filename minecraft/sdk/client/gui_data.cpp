#include "gui_data.h"

#include "minecraft/signature/signature_result.h"

#include <libhat/Access.hpp>
#include <optional>

namespace semita {
    const glm::vec2& gui_data::get_window_size() const {
        return hat::member_at<glm::vec2>(this, 0x40);
    }

    const glm::vec2& gui_data::get_game_size() const {
        return hat::member_at<glm::vec2>(this, 0x50);
    }

    void gui_data::display_client_message(const std::string& message) {
        using function_t = void(__fastcall*)(gui_data*, const std::string&, std::optional<std::string>, bool);
        static const auto fn = signature_value<&gui_data::display_client_message, function_t>();
        fn(this, message, std::nullopt, false);
    }
}
