#pragma once

#include "parse_result.h"

#include <expected>
#include <vector>

namespace semita {
    enum class parse_error {
        invalid_argument_type,
        invalid_argument_count,
    };

    class argument_parser {
    public:
        template <typename argument_tuple>
        using result_t = parse_result<argument_tuple>;

        template <typename argument_tuple>
        using expected_t = std::expected<result_t<argument_tuple>, parse_error>;

        template <typename argument_tuple>
        static expected_t<argument_tuple> parse(const std::vector<std::string_view>& args) {
            static constexpr auto size = std::tuple_size_v<std::remove_reference_t<argument_tuple>>;

            if (args.size() != size) {
                return std::unexpected(parse_error::invalid_argument_count);
            }

            if constexpr (size == 0) {
                return expected_t<argument_tuple>(result_t<argument_tuple>{});
            }

            return parse_tuple_args<argument_tuple>(args, std::make_index_sequence<size>{});
        }

    private:
        template <size_t I, typename argument_tuple>
        static bool try_parse_arguments(std::string_view to_parse, result_t<argument_tuple>& out_result) {
            using argument_type = std::tuple_element_t<I, argument_tuple>;
            const auto parsed = argument_type::parse(to_parse);

            if (parsed) {
                out_result[I] = std::move(*parsed);
                return true;
            }

            return false;
        }

        template <typename argument_tuple, size_t ...Is>
        static expected_t<argument_tuple> parse_tuple_args(const std::vector<std::string_view>& args, std::index_sequence<Is...>) {
            result_t<argument_tuple> result;

            if (const bool success = (try_parse_arguments<Is, argument_tuple>(args[Is], result) && ...); !success) {
                return std::unexpected(parse_error::invalid_argument_type);
            }

            return expected_t<argument_tuple>(std::move(result));
        }
    };
}
