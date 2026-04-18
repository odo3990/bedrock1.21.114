#pragma once

#include "hooks/keyboard_hook.h"
#include "hooks/local_player_tick_world_hook.h"
#include "hooks/packet_hook.h"
#include "hooks/receive_hook.h"
#include "hooks/render_hook.h"
#include "hooks/tick_hook.h"
#include "util/logger.h"
#include "minecraft/signature/signature_result.h"
#include "minecraft/signature/registry/signature_registry.h"

#include <tuple>

namespace semita {
    using hook_types = std::tuple<
        render_hook,
        tick_hook,
        local_player_tick_world_hook,
        packet_hook,
        keyboard_hook
    >;

    using standalone_hook_types = std::tuple<
        receive_hook
    >;

    class hook_manager {
    public:
        hook_manager();
        ~hook_manager();

        template <is_hook hook_t>
        void initialize(hook_t& hook) {
            initialize_hook_lifecycle<hook_t>();
            patch(hook);
        }

        template <is_hook hook_t>
        void patch(hook_t& hook) {
            const auto target = signature_value<&hook_t::callback, LPVOID>();
            if (const auto addr = patch_impl<hook_t>(target)) {
                hook.set_target(addr);
            }
        }

        template <is_hook hook_t>
        static void shutdown(hook_t& hook) {
            hook.shutdown();
            shutdown_hook_lifecycle<hook_t>();
        }

    private:
        template <typename tuple_t, size_t... Is>
        static void initialize_standalone_hooks(std::index_sequence<Is...>) {
            (initialize_hook_lifecycle<std::tuple_element_t<Is, tuple_t>>(), ...);
        }

        template <typename tuple_t, size_t... Is>
        static void shutdown_standalone_hooks(std::index_sequence<Is...>) {
            (shutdown_hook_lifecycle<std::tuple_element_t<Is, tuple_t>>(), ...);
        }

        template <is_hook hook_t>
        LPVOID patch_impl(auto target) {
            constexpr auto name = signature<&hook_t::callback>::name.to_view();
            const auto original = reinterpret_cast<LPVOID*>(&hook_t::original);
            const auto callback = reinterpret_cast<LPVOID>(&hook_t::callback);

            if (const auto status = MH_CreateHook(target, callback, original); status != MH_OK) {
                logger::get()->error("failed to create hook {}: {}", name , MH_StatusToString(status));
                return nullptr;
            }

            MH_EnableHook(target);
            logger::get()->info("created hook: {}", name);

            return target;
        }

        hook_types m_hooks;
    };
}
