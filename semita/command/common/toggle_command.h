#pragma once

#include "semita/client/client.h"
#include "semita/command/command.h"
#include "semita/module/module_manager.h"

namespace semita {
    template <>
    struct command_traits<struct toggle_command> {
        using arguments_type = std::tuple<string_argument>;

        static constexpr auto name = std::string_view{ "toggle" };
        static constexpr auto description = std::string_view{ "Toggle a module." };
        static constexpr auto usage = std::string_view{ ".toggle <module>" };
    };

    struct toggle_command : command<toggle_command> {
        static void execute(const parsed_arguments& args) {
            const auto& module_name = args.get<0>();
            auto& manager = get<module_manager>();

            const auto module = manager.find_module(module_name);
            if (!module) {
                game::display_message("{}Unknown module: {}{}", text_format::red, module_name, text_format::reset);
                return;
            }

            manager.toggle_module(module_name);
            game::display_message(
                "{}{} {}{}",
                module->enabled() ? text_format::green : text_format::red,
                module->name(),
                module->enabled() ? "enabled" : "disabled",
                text_format::reset
            );
        }
    };
}
