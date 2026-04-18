#pragma once

#include "args/argument_parser.h"
#include "util/mc/game.h"
#include "util/mc/text_format.h"

namespace semita {
    template <typename command_t>
    struct command_traits {
        using arguments_type = std::tuple<>;

        static constexpr std::string_view name{ "name" };
        static constexpr std::string_view description{ "description" };
        static constexpr std::string_view usage{ "usage" };
    };

    template <typename command_t>
    struct command {
        using details = command_traits<command_t>;
        using arguments_type = typename details::arguments_type;
        using parsed_arguments = parse_result<arguments_type>;

        static void try_execute(const std::vector<std::string_view>& args) {
            const auto parse_result = argument_parser::parse<arguments_type>(args);
            if (parse_result.has_value()) {
                command_t::execute(*parse_result);
                return;
            }

            send_failure(parse_result.error());
        }

        static void send_failure(parse_error error) {
            send_usage(); // todo
        }

        static void send_usage() {
            game::display_message("{}Usage: {}", text_format::red, details::usage);
        }
    };

    template <typename T>
    concept is_command = requires (const typename T::parsed_arguments& args) {
        { T::execute(args) } -> std::convertible_to<void>;
    };
}
