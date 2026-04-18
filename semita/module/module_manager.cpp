#include "module_manager.h"

#include "modules/auto_web.h"
#include "modules/packet_logger.h"
#include "util/string.h"

#include <ranges>

#include "minecraft/event/event_manager.h"

namespace semita {
    module_manager::module_manager() {
        m_modules.reserve(8);
        register_module<packet_logger>();
        event_manager::get().listen<keyboard_event, &module_manager::on_keyboard>(this);
    }

    void module_manager::on_keyboard(const keyboard_event& event) const {
        if (event.action() != key_state::pressed) {
            return;
        }

        if (const auto module = module_by_keybind(event.key())) {
            module->toggle();
        }
    }

    const std::vector<std::unique_ptr<module>>& module_manager::get_modules() const {
        return m_modules;
    }

    module* module_manager::find_module(const std::string_view name) const {
        const auto it = std::ranges::find_if(m_modules, [&](const auto& module) {
            return string::iequals(module->name(), name);
        });

        return it != m_modules.end() ? it->get() : nullptr;
    }

    module* module_manager::module_by_keybind(key_type key) const {
        const auto it = std::ranges::find_if(m_modules, [&](const auto& module) {
            return module->keybind() == key;
        });

        return it != m_modules.end() ? it->get() : nullptr;
    }

    bool module_manager::enable_module(const std::string_view name) const {
        if (const auto module = find_module(name)) {
            return module->set_enabled(true);
        }

        return false;
    }

    bool module_manager::disable_module(const std::string_view name) const {
        if (const auto module = find_module(name)) {
            return module->set_enabled(false);
        }

        return false;
    }

    bool module_manager::toggle_module(const std::string_view name) const {
        if (const auto module = find_module(name)) {
            return module->toggle();
        }

        return false;
    }
}
