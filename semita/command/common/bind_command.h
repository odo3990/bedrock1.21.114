#pragma once

#include "semita/client/client.h"
#include "semita/command/command.h"
#include "semita/module/module_manager.h"

namespace semita {
    template <>
    struct command_traits<struct disable_command> {
        using arguments_type = std::tuple<string_argument>;

        static constexpr auto name = std::string_view{ "bind" };
        static constexpr auto description = std::string_view{ "Bind a module." };
        static constexpr auto usage = std::string_view{ ".bind <module> <key>" };
    };

    struct bind_command : command<bind_command> {
        static void execute(const parsed_arguments& args) {
        }
    };
}
