#pragma once

#include "semita/command/args/argument.h"
#include "float_argument.h"
#include "integer_argument.h"
#include <glm/vec3.hpp>

#include "util/logger.h"

namespace semita {
    template <typename T>
    concept valid_position_type = std::same_as<T, glm::vec3> || std::same_as<T, glm::ivec3>;

    template <valid_position_type vec_type>
    struct position_argument : argument_base<vec_type> {
        static typename position_argument::optional_t parse(const std::string_view arg) {
            vec_type result;
            size_t start = 0;

            for (size_t i{ 0 }; i < 2; ++i) {
                const auto it = arg.find(':', start);
                if (it == std::string::npos) {
                    return std::nullopt;
                }

                if (!parse_substr(arg.substr(start, it - start), i, result)) {
                    return std::nullopt;
                }

                start = it + 1;
            }

            if (!parse_substr(arg.substr(start), 2, result)) {
                return std::nullopt;
            }

            return result;
        }

    private:
        static bool parse_substr(const std::string_view str, const size_t index, vec_type& out) {
            using target_type = std::conditional_t<std::is_same_v<vec_type, glm::ivec3>, int, float>;
            std::optional<target_type> parsed;

            if constexpr(std::is_same_v<target_type, int>) {
                parsed = integer_argument::parse(str);
            } else {
                parsed = float_argument::parse(str);
            }

            if (!parsed) {
                return false;
            }

            out[index] = *parsed;
            return true;
        }
    };
}
