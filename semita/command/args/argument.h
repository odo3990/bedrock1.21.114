#pragma once

#include <variant>
#include <string>
#include <optional>

namespace semita {
    template <typename underlying_type>
    struct argument_base {
        using type = underlying_type;
        using optional_t = std::optional<type>;
    };

    template <typename T>
    concept is_argument = requires (std::string_view arg) {
        { T::parse(arg) } -> std::same_as<typename T::optional_t>;
    };

    template <is_argument ...args_t>
    struct argument_types {
        using value_variant = std::variant<typename args_t::type...>;
    };
}
