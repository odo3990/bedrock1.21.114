#pragma once

#include "semita/command/args/argument.h"

#include <optional>

#include "util/logger.h"

namespace semita {
    struct integer_argument : argument_base<int> {
        static optional_t parse(const std::string_view arg) {
            int value;
            const auto [ptr, ec] = std::from_chars(arg.data(), arg.data() + arg.size(), value);
            if (ec == std::errc() && ptr == arg.data() + arg.size()) {
                return value;
            }

            return std::nullopt;
        }
    };
}
