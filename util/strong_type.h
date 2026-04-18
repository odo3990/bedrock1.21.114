#pragma once

#include <concepts>

namespace semita {
    template <typename T>
    concept strong_arithmetic_compatible = requires(T a, T b) {
        { a + b };
        { a - b };
        { a * b };
        { a / b };
        { a == b };
    };

    template <typename T>
    concept strong_arithmetic_assign = requires(T a, T b) {
        { a += b };
        { a -= b };
    };

    template <typename T>
    struct strong_type {
        constexpr strong_type()
        requires std::is_default_constructible_v<T>
        : m_value(T{}) {}

        constexpr strong_type(T value)
        : m_value(value) {}

        template <typename U>
        explicit strong_type(U) requires(!std::same_as<std::decay_t<U>, T>) = delete;

        explicit operator T() const {
            return m_value;
        }

        constexpr const T& get() const {
            return m_value;
        }

        constexpr strong_type operator+(const strong_type& other) const
        requires strong_arithmetic_compatible<T> {
            return strong_type(other.m_value + m_value);
        }

        constexpr strong_type operator-(const strong_type& other) const
        requires strong_arithmetic_compatible<T> {
            return strong_type(m_value - other.m_value);
        }

        constexpr strong_type operator*(const strong_type& other) const
        requires strong_arithmetic_compatible<T>{
            return strong_type(m_value * other.m_value);
        }

        constexpr strong_type operator/(const strong_type& other) const
        requires strong_arithmetic_compatible<T> {
            return strong_type(m_value / other.m_value);
        }

        bool operator==(const strong_type& cost) const
        requires strong_arithmetic_compatible<T> {
            return m_value == cost.m_value;
        }

        constexpr strong_type& operator+=(const strong_type& other)
        requires strong_arithmetic_assign<T> {
            m_value += other.m_value;
            return *this;
        }

        constexpr strong_type& operator-=(const strong_type& other)
        requires strong_arithmetic_assign<T> {
            m_value -= other.m_value;
            return *this;
        }

        auto operator<=>(const strong_type& cost) const {
            return m_value <=> cost.m_value;
        }

    private:
        T m_value;
    };
}