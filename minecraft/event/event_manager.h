#pragma once

#include "event.h"
#include "event_priority.h"

#include <functional>
#include <array>
#include <unordered_map>
#include <ranges>

#if defined(_MSC_VER)
    #define FUNC_SIGNATURE __FUNCSIG__
#else
    #define FUNC_SIGNATURE __PRETTY_FUNCTION__
#endif

namespace semita {
    namespace detail {
        constexpr std::size_t fnv1a(const std::string_view str) {
            std::size_t hash = 1469598103934665603ull;
            for (const char c : str) {
                hash = (hash ^ static_cast<unsigned char>(c)) * 1099511628211ull;
            }

            return hash;
        }

        template <auto function>
        constexpr size_t function_hash() {
            constexpr auto sig = FUNC_SIGNATURE;
            return fnv1a(sig);
        }
    }

    template <typename event_t>
    class listener_container {
    public:
        using callback_t = std::function<void(event_t&)>;
        using event_map = std::unordered_map<size_t, callback_t>;
        using map_container = std::array<event_map, priority_count>;

        void insert(const size_t key, callback_t callback, event_priority priority) {
            m_listeners[static_cast<int>(priority)][key] = std::move(callback);
        }

        void remove(const size_t key) {
            for (auto& map : m_listeners) {
                map.erase(key);
            }
        }

        void call(event_t& event) {
            for (const auto& map : m_listeners) {
                for (const auto& func : map | std::views::values) {
                    func(event);
                }
            }
        }

    private:
        map_container m_listeners{};
    };

    template <typename event_t>
    class event_handler {
    public:
        template <auto function, typename class_t>
        void listen(class_t* instance, event_priority priority) {
            const auto key = detail::function_hash<function>();
            const auto trigger_func = [=](event_t& event) {
                (instance->*function)(event);
            };

            m_listener.insert(key, trigger_func, priority);
        }

        template <auto function>
        void listen(event_priority priority) {
            const auto key = detail::function_hash<function>();
            m_listener.insert(key, [](event_t& event) {
                function(event);
            }, priority);
        }

        template <auto function>
        void mute() {
            m_listener.remove(detail::function_hash<function>());
        }

        void call(event_t& event) {
            m_listener.call(event);
        }

    private:
        listener_container<event_t> m_listener;
    };

    class event_manager {
    public:
        template <is_event event_t, auto function, typename class_t>
        void listen(class_t* instance, event_priority priority = event_priority::medium) {
            auto& handler = get_handler<event_t>();
            handler.template listen<function>(instance, priority);
        }

        template <is_event event_t, auto function>
        void listen(event_priority priority = event_priority::medium) {
            auto& handler = get_handler<event_t>();
            handler.template listen<function>(priority);
        }

        template <is_event event_t, auto function>
        void mute() {
            auto& handler = get_handler<event_t>();
            handler.template mute<function>();
        }

        template<is_event event_t>
        void call(event_t& event) {
            auto& handler = get_handler<event_t>();
            handler.call(event);
        }

        static event_manager& get() {
            static event_manager instance;
            return instance;
        }

    private:
        template <typename event_t>
        [[nodiscard]] event_handler<event_t>& get_handler() {
            static event_handler<event_t> handler;
            return handler;
        }
    };
}