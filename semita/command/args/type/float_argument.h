#pragma once

#include <charconv>

#include "semita/command/args/argument.h"
#include <optional>

namespace semita {
    struct float_argument : argument_base<float> {
        static optional_t parse(const std::string_view arg) {
            float value;
            const auto [ptr, ec] = std::from_chars(arg.data(), arg.data() + arg.size(), value);
            if (ec != std::errc{} || ptr != arg.data() + arg.size()) {
                return std::nullopt;
            }

            return value;
        }
    };
}