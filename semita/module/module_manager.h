#pragma once

#include "module.h"
#include "minecraft/event/events/keyboard_event.h"

#include <memory>
#include <string_view>
#include <utility>
#include <vector>

namespace semita {
    class module_manager {
    public:
        module_manager();

        template <typename module_t, typename... args_t>
        module_t& register_module(args_t&&... args) {
            auto module = std::make_unique<module_t>(std::forward<args_t>(args)...);
            auto* result = module.get();

            m_modules.emplace_back(std::move(module));
            return *result;
        }

        void on_keyboard(const keyboard_event& event) const;

        [[nodiscard]] const std::vector<std::unique_ptr<module>>& get_modules() const;
        [[nodiscard]] module* find_module(std::string_view name) const;
        [[nodiscard]] module* module_by_keybind(key_type key) const;

        bool enable_module(std::string_view name) const;
        bool disable_module(std::string_view name) const;
        bool toggle_module(std::string_view name) const;

    private:
        std::vector<std::unique_ptr<module>> m_modules{};
    };
}
