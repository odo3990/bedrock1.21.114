#pragma once

#include <entt/entt.hpp>

struct entity_id {
    std::uint32_t rawId;

    [[nodiscard]] constexpr bool operator==(const entity_id& other) const = default;

    [[nodiscard]] constexpr operator std::uint32_t() const {
        return rawId;
    }
};

struct entity_id_traits {
    using value_type = entity_id;

    using entity_type  = uint32_t;
    using version_type = uint16_t;

    static constexpr entity_type entity_mask  = 0x3FFFF;
    static constexpr entity_type version_mask = 0x3FFF;
};

template <>
struct entt::entt_traits<entity_id> : basic_entt_traits<entity_id_traits> {
    static constexpr entity_type page_size = 2048;
};

struct entity_component {};

template<std::derived_from<entity_component> T>
struct entt::component_traits<T> {
    using type = T;
    static constexpr bool in_place_delete = true;
    static constexpr std::size_t page_size = 128 * !std::is_empty_v<T>;
};

template<typename T>
struct entt::storage_type<T, entity_id> {
    using type = basic_storage<T, entity_id>;
};

class entity_registry : public std::enable_shared_from_this<entity_registry> {
public:
    std::string name;
    entt::basic_registry<entity_id> ownedRegistry;
    uint32_t id;
};

class entity_context {
public:
    entity_registry& registry;
    entt::basic_registry<entity_id>& entt_registry;
    entity_id entity;

    template<std::derived_from<entity_component> T>
    [[nodiscard]] T* try_get() {
        return entt_registry.try_get<T>(entity);
    }

    template<std::derived_from<entity_component> T>
    [[nodiscard]] const T* try_get() const {
        return entt_registry.try_get<T>(entity);
    }

    template<std::derived_from<entity_component> T>
    [[nodiscard]] bool has_component() const {
        return entt_registry.all_of<T>(entity);
    }

    template <std::derived_from<entity_component> T>
    void add_component() const {
        entt_registry.emplace_or_replace<T>(entity);
    }
};

template<std::derived_from<entity_component> T>
struct entt::type_hash<T> {
    [[nodiscard]] static consteval id_type value() noexcept {
        constexpr auto name = T::type_name;
        return hashed_string::value(name.data(), name.size());
    }

    [[nodiscard]] consteval operator id_type() const noexcept {
        return value();
    }
};