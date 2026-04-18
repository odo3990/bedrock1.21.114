#pragma once

#include "semita/client/client.h"
#include "semita/command/command.h"
#include "util/mc/game.h"
#include "util/mc/text_format.h"

namespace semita {
    template <>
    struct command_traits<struct eject_command> {
        using arguments_type = std::tuple<>;

        static constexpr auto name = std::string_view{ "eject" };
        static constexpr auto description = std::string_view{ "Eject Semita Client from your game." };
        static constexpr auto usage = std::string_view{ "Usage: .eject" };
    };

    struct eject_command : command<eject_command> {
        static void execute([[maybe_unused]] const parsed_arguments& args) {
            game::display_message("{}Ejecting...", text_format::red);
            client::get().eject();
        }
    };
}
