#pragma once

#include "minecraft/game_manager.h"
#include "minecraft/hook/hook_manager.h"
#include "semita/command/command_manager.h"
#include "semita/module/module_manager.h"

#include <tuple>

namespace semita {
    class client {
    public:
        client(const client&) = delete;
        client& operator=(const client&) = delete;
        client(client&&) = delete;
        client& operator=(client&&) = delete;

        template <typename system_t>
        constexpr system_t& get_system() {
            return std::get<system_t>(m_systems);
        }

        void eject();
        [[nodiscard]] bool running() const;
        [[nodiscard]] static client& get();

    private:
        using systems_t = std::tuple<
            hook_manager,
            game_manager,
            module_manager,
            command_manager
        >;

        client() = default;
        ~client() = default;

        systems_t m_systems{};
        bool m_running{ true };
    };

    template <typename system_t>
    constexpr system_t& get() {
        return client::get().get_system<system_t>();
    }
}
