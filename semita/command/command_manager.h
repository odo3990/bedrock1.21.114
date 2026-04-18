#pragma once

#include "command.h"
#include "minecraft/event/events/message_event.h"

#include <unordered_map>
#include <functional>

namespace semita {
    class command_manager {
    public:
        using callback_t = std::function<void(const std::vector<std::string_view>&)>;
        using map_t = std::unordered_map<std::string_view, callback_t>;

        command_manager();
        ~command_manager();

        template <typename commands_t, size_t... Is>
        void register_commands(std::index_sequence<Is...>) {
            (register_command<std::tuple_element_t<Is, commands_t>>(), ...);
        }

        template <is_command command_t>
        void register_command() {
            m_commands.try_emplace(command_t::details::name, [](const auto& args) {
                command_t::try_execute(args);
            });
        }

        void on_chat_message(message_event& event);

    private:
        map_t m_commands{};
    };
}
