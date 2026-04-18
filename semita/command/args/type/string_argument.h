#pragma once

#include "semita/command/args/argument.h"

#include <string>

namespace semita {
    struct string_argument : argument_base<std::string> {
        static optional_t parse(const std::string_view arg) {
            return std::string(arg);
        }
    };
}
