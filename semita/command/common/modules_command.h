#pragma once

#include "semita/client/client.h"
#include "semita/command/command.h"
#include "semita/module/module_manager.h"

namespace semita {
    template <>
    struct command_traits<struct modules_command> {
        using arguments_type = std::tuple<>;

        static constexpr auto name = std::string_view{ "modules" };
        static constexpr auto description = std::string_view{ "List registered modules." };
        static constexpr auto usage = std::string_view{ ".modules" };
    };

    struct modules_command : command<modules_command> {
        static void execute([[maybe_unused]] const parsed_arguments& args) {
            const auto& modules = get<module_manager>().get_modules();
            if (modules.empty()) {
                game::display_message("{}No modules registered{}", text_format::yellow, text_format::reset);
                return;
            }

            std::string message = "Modules: ";
            for (size_t i = 0; i < modules.size(); ++i) {
                const auto& module = modules[i];
                message += std::format(
                    "{}{}{}",
                    module->enabled() ? text_format::green : text_format::red,
                    module->name(),
                    text_format::reset
                );

                if (i + 1 < modules.size()) {
                    message += ", ";
                }
            }

            game::display_message(message);
        }
    };
}
