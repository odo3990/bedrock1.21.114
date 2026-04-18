#pragma once

#include <cstddef>

namespace semita {
    template <auto function>
    struct signature_result {
        static inline std::byte* value{ nullptr };
    };

    template <auto function, typename result_t = std::byte*>
    static result_t signature_value() {
        using signature_result_t = signature_result<function>;
        return reinterpret_cast<result_t>(signature_result_t::value);
    }
}
