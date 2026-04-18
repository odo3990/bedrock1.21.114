#pragma once

#include "argument.h"
#include "type/string_argument.h"
#include "type/position_argument.h"
#include "type/float_argument.h"
#include "type/integer_argument.h"
#include "util/math/position.h"

#include <array>

namespace semita {
    using all_arguments = argument_types<
        integer_argument,
        float_argument,
        string_argument,
        position_argument<block_pos>,
        position_argument<glm::vec3>
    >;

    using argument_variant = all_arguments::value_variant;

    // wrapper for std::array to make it easier to access argument_variant values
    template <typename argument_tuple>
    class parse_result {
    public:
        template <size_t I>
        using argument_type = typename std::tuple_element_t<I, argument_tuple>::type;

        template <size_t I>
        argument_type<I> get() const {
            return std::get<argument_type<I>>(values[I]);
        }

        constexpr auto& operator[](size_t index) { return values[index]; }
        constexpr const auto& operator[](size_t index) const { return values[index]; }

    private:
        using array_t = std::array<
            argument_variant,
            std::tuple_size_v<std::remove_reference_t<argument_tuple>>
        >;

        array_t values{};
    };
}
