#pragma once

#include "semita/client/client.h"
#include "semita/command/command.h"
#include "semita/module/module_manager.h"

namespace semita {
    template <>
    struct command_traits<struct enable_command> {
        using arguments_type = std::tuple<string_argument>;

        static constexpr auto name = std::string_view{ "enable" };
        static constexpr auto description = std::string_view{ "Enable a module." };
        static constexpr auto usage = std::string_view{ ".enable <module>" };
    };

    struct enable_command : command<enable_command> {
        static void execute(const parsed_arguments& args) {
            const auto& module_name = args.get<0>();
            auto& manager = get<module_manager>();

            const auto module = manager.find_module(module_name);
            if (!module) {
                game::display_message("{}Unknown module: {}{}", text_format::red, module_name, text_format::reset);
                return;
            }

            if (manager.enable_module(module_name)) {
                game::display_message("{}Enabled {}{}", text_format::green, module->name(), text_format::reset);
                return;
            }

            game::display_message("{}{} is already enabled{}", text_format::yellow, module->name(), text_format::reset);
        }
    };
}
