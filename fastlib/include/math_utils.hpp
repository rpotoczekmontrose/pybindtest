#pragma once
#include <type_traits>
#include <limits>
#include <concepts>

namespace fastlib
{

    // integral overload
    template <std::integral T>
    T safe_divide(T a, T b)
    {
        if (b == 0)
            throw std::runtime_error("Division by zero");
        return a / b;
    }

    // floating-point overload
    template <std::floating_point T>
    T safe_divide(T a, T b)
    {
        if (b == T{0})
            return std::numeric_limits<T>::infinity();
        return a / b;
    }

    // legacy enable_if example
    template <typename T>
    std::enable_if_t<std::is_floating_point_v<T>, T>
    reciprocal_or_zero(T x)
    {
        if (x == T{0})
            return T{0};
        return T{1} / x;
    }

} // namespace fastlib