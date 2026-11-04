#pragma once

#include <concepts>
#include <limits>

namespace zink::sentinel {

/* Proxy object that adapts to integral unsigned types given enough context.
 * size_t x = sentinel::na; // x == std::numeric_limits<size_t>::max()
 * uint8_t y = sentinel::na; // y == std::numeric_limits<uint8_t>::max() */
struct SentinelValue {
    template <std::unsigned_integral T>
    constexpr operator T() const noexcept {
        return std::numeric_limits<T>::max();
    }

    template <std::unsigned_integral T>
    friend constexpr bool operator==(T x, SentinelValue) {
        return x == std::numeric_limits<T>::max();
    }
    template <std::unsigned_integral T>
    friend constexpr bool operator==(SentinelValue, T x) {
        return x == std::numeric_limits<T>::max();
    }
};

inline constexpr SentinelValue na { }; /* No index applicable */

}
