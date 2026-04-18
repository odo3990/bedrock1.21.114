#pragma once

#include "semita/client/client.h"
#include "semita/command/command.h"
#include "semita/module/module_manager.h"

namespace semita {
    template <>
    struct command_traits<struct disable_command> {
        using arguments_type = std::tuple<string_argument>;

        static constexpr auto name = std::string_view{ "disable" };
        static constexpr auto description = std::string_view{ "Disable a module." };
        static constexpr auto usage = std::string_view{ ".disable <module>" };
    };

    struct disable_command : command<disable_command> {
        static void execute(const parsed_arguments& args) {
            const auto& module_name = args.get<0>();
            auto& manager = get<module_manager>();

            const auto module = manager.find_module(module_name);
            if (!module) {
                game::display_message("{}Unknown module: {}{}", text_format::red, module_name, text_format::reset);
                return;
            }

            if (manager.disable_module(module_name)) {
                game::display_message("{}Disabled {}{}", text_format::red, module->name(), text_format::reset);
                return;
            }

            game::display_message("{}{} is already disabled{}", text_format::yellow, module->name(), text_format::reset);
        }
    };
}
