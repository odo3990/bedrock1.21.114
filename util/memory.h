#pragma once

#include <utility>

namespace semita {
    struct memory {
        template <size_t I, typename return_t, typename... args_t>
        static return_t call_virtual(void* instance, args_t&&... args) {
            using func_t = return_t(__thiscall*)(void*, args_t...);
            const auto vtable = *static_cast<func_t**>(instance);
            const auto func = vtable[I];

            return func(instance, std::forward<args_t>(args)...);
        }

        template<size_t I, typename return_t, typename... args_t>
        static return_t call_virtual_copy(void* instance, args_t... args) {
            using func_t = return_t(__thiscall*)(void*, args_t...);
            const auto vtable = *static_cast<func_t**>(instance);
            const auto func = vtable[I];
            return func(instance, args...);
        }

        template <typename return_t, typename... args_t>
        static return_t call_fastcall(void* func, args_t&&... args) {
            using func_t = return_t(__fastcall*)(args_t...);
            return reinterpret_cast<func_t>(func)(std::forward<args_t>(args)...);
        }
    };
}
