#pragma once

#include <libhat/fixed_string.hpp>

#include "../signature.h"
#include "minecraft/hook/hooks/keyboard_hook.h"
#include "minecraft/hook/hooks/local_player_tick_world_hook.h"
#include "minecraft/hook/hooks/render_hook.h"
#include "minecraft/hook/hooks/packet_hook.h"
#include "minecraft/sdk/actor/actor.h"
#include "minecraft/sdk/client/gui_data.h"
#include "minecraft/hook/hooks/tick_hook.h"
#include "minecraft/sdk/actor/player.h"
#include "minecraft/sdk/network/minecraft_packets.h"

namespace semita {
    template <>
    struct signature<&render_hook::callback> {
        static constexpr auto name = hat::fixed_string{ "screen_view::setup_and_render" };
        static constexpr auto fixed_pattern = hat::fixed_string{
            "48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 "
            "48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 "
            "? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA "
            "48 89 55"
        };
    };

    template <>
    struct signature<&packet_hook::callback> {
        static constexpr auto name = hat::fixed_string{ "loopback_packet_sender::send" };
        static constexpr auto fixed_pattern = hat::fixed_string{
            "48 83 EC ? 48 0F BE 41 ? 48 83 C0 ? 74 ? 48 83 F8 ? 48 8B 01"
        };
    };

    template <>
    struct signature<&gui_data::display_client_message> {
        static constexpr auto name = hat::fixed_string{ "gui_data::display_client_message" };
        static constexpr auto fixed_pattern = hat::fixed_string {
            "40 55 53 56 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? "
            "48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 41 0F B6 F9"
        };
    };

    template <>
    struct signature<&actor::move> {
        static constexpr auto name = hat::fixed_string{ "actor::move" };
        static constexpr auto fixed_pattern = hat::fixed_string {
            "4c 8b dc 49 89 5b ? 49 89 73 ? 57 48 83 ec ? 48 8b fa 48 8b d9"
        };
    };

    template <>
    struct signature<&keyboard_hook::callback> {
        static constexpr auto name = hat::fixed_string{ "keyboard::feed" };
        static constexpr auto fixed_pattern = hat::fixed_string {
            "48 83 EC ? 0F B6 C1 4C 8D 05"
        };
    };

    template <>
    struct signature<&tick_hook::callback> {
        static constexpr auto name = hat::fixed_string{ "client_instance::update" };
        static constexpr auto fixed_pattern = hat::fixed_string {
            "48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D AC 24 "
            "? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? "
            "? 44 0F B6 FA 48 8B F9 33 DB"
        };

    };

    template <>
    struct signature<&local_player_tick_world_hook::callback> {
        static constexpr auto name = hat::fixed_string{ "local_player::tick_world" };
        static constexpr auto fixed_pattern = hat::fixed_string {
            "40 53 48 83 EC ? 8B 41 ? 48 8B D9 48 8B 49"
        };
    };

    template <>
    struct signature<&local_player::apply_turn_delta> {
        static constexpr auto name = hat::fixed_string{ "local_player::apply_turn_delta" };
        static constexpr auto fixed_pattern = hat::fixed_string {
            "48 8B C4 48 89 58 ? 48 89 70 ? 55 57 41 54 41 56 41 57 48 8D 68 "
            "? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 "
            "48 ? 44 0F 29 50 ? 44 0F 29 98 ? ? ? ? 48 8B 05"
        };
    };

    template <>
    struct signature<&minecraft_packets::create_packet> {
        static constexpr auto name = hat::fixed_string{ "minecraft_packets::create_packet" };
        static constexpr auto fixed_pattern = hat::fixed_string {
            "48 89 5C 24 10 48 89 6C 24 18 48 89 74 24 20 57 48 83 EC 60 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 58 48 8B F9 48 89 4C 24 38"
        };
    };

    using signature_list = std::tuple<
        signature<&render_hook::callback>,
        signature<&packet_hook::callback>,
        signature<&keyboard_hook::callback>,
        signature<&tick_hook::callback>,
        signature<&local_player_tick_world_hook::callback>,
        signature<&gui_data::display_client_message>,
        signature<&actor::move>,
        signature<&local_player::apply_turn_delta>,
        signature<&minecraft_packets::create_packet>
    >;
}
