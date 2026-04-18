#pragma once

#include <tuple>

namespace semita {
    template <typename tuple_t, typename function_t>
    static void tuple_for_each(tuple_t&& tuple, function_t function) {
        static constexpr auto size = std::tuple_size_v<std::remove_reference_t<tuple_t>>;
        tuple_for_each_impl(std::forward<tuple_t>(tuple), function, std::make_index_sequence<size>{});
    }

    template <typename tuple_t, typename function_t, std::size_t... Is>
    static void tuple_for_each_impl(tuple_t&& tuple, function_t function, std::index_sequence<Is...>) {
        (function(std::get<Is>(tuple)), ...);
    }
}