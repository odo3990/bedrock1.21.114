#pragma once

namespace semita {
    template <typename T>
    concept is_signature = requires {
        { T::fixed_pattern };
        { T::name };
    };

    template <auto function>
    struct signature { };

    template <typename T>
    struct signature_func { };

    template <auto function>
    struct signature_func<signature<function>> {
        static constexpr auto value = function;
    };

    template <typename signature_t>
    static constexpr auto signature_func_v = signature_func<signature_t>::value;
}
