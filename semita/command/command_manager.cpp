#include "command_manager.h"

#include "common/disable_command.h"
#include "minecraft/event/event_manager.h"
#include "common/enable_command.h"
#include "common/eject_command.h"
#include "common/modules_command.h"
#include "common/toggle_command.h"
#include "util/string.h"

namespace semita {
    using command_list = std::tuple<
        eject_command,
        modules_command,
        enable_command,
        disable_command,
        toggle_command
    >;

    command_manager::command_manager() {
        event_manager::get().listen<message_event, &command_manager::on_chat_message>(this);

        constexpr auto size = std::tuple_size_v<command_list>;
        m_commands.reserve(size);
        register_commands<command_list>(std::make_index_sequence<size>{});
    }

    command_manager::~command_manager() {
        event_manager::get().mute<message_event, &command_manager::on_chat_message>();
        m_commands.clear();
    }

    void command_manager::on_chat_message(message_event& event) {
        const auto& message = event.get_packet()->m_message;
        auto split = string::split_sv(message, ' ');

        if (split.empty()) {
            return;
        }

        auto& prefix_part = split.at(0);
        if (!prefix_part.starts_with('.')) {
            return;
        }

        prefix_part.remove_prefix(1);
        const auto it = m_commands.find(prefix_part);
        if (it == m_commands.end()) {
            return;
        }

        split.erase(split.begin());
        it->second(split);
        event.cancel();
    }
}
