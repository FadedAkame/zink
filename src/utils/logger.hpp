#pragma once

#include <cstdint>
#include <format>
#include <iostream>
#include <utility>

#ifndef DNDEBUG
    /* General log macro for Zink, supports [info, warn, err] as log levels. */
    #define ZLOG(level, ...) \
        zink::detail::log::write<(level)>(__VA_ARGS__)

    /* Expect the [expr] to be true, if not then panic, gets removed in release. */
    #define DEBUG_EXPECT(expr, ...)                    \
        do {                                           \
            if (!(expr))                               \
                zink::detail::log::panic(__VA_ARGS__); \
        } while (0)
#endif

/* General log macro for Zink BUT lasts outside of debug, should only be used for
 * dumpers or similar */
#define RELEASE_ZLOG(level, ...) \
    zink::detail::log::write<(level)>(__VA_ARGS__)

/* Expect the [expr] to be true, if not then panic, doesn't get removed in release. */
#define RELEASE_EXPECT(expr, ...)                  \
    do {                                           \
        if (!(expr))                               \
            zink::detail::log::panic(__VA_ARGS__); \
    } while (0)

/* This should ONLY be called in absolute unrecoverable errors. */
#define PANIC(...) \
    zink::detail::log::panic(__VA_ARGS__)

namespace zink::log {

inline constexpr std::uint8_t info { 0 };
inline constexpr std::uint8_t warn { 1 };
inline constexpr std::uint8_t err { 2 };

}

namespace zink::detail::log {

consteval auto level_to_char(std::uint8_t level) {
    switch (level) {
    case zink::log::info:
        return "[I] ";
    case zink::log::warn:
        return "[W] ";
    case zink::log::err:
        return "[E] ";
    default:
        return "[?] ";
    }
}

template <std::uint8_t Level, typename... Args>
inline void write(std::format_string<Args...> msg, Args&&... args) {
    static constexpr auto& out { Level == zink::log::err ? std::cerr : std::clog };
    out << level_to_char(Level) << std::format(msg, std::forward<Args>(args)...) << '\n';
}
template <std::uint8_t Level>
inline void write(const char* msg) {
    static constexpr auto& out { Level == zink::log::err ? std::cerr : std::clog };
    out << level_to_char(Level) << msg << '\n';
}

template <typename... Args>
[[noreturn]]
inline void panic(std::format_string<Args...> msg, Args&&... args) {
    std::cerr << "unrecoverable error occured: " << std::format(msg, std::forward<Args>(args)...) << '\n';
    std::terminate();
}
[[noreturn]]
inline void panic(const char* msg) {
    std::cerr << "unrecoverable error occured: " << msg << '\n';
    std::terminate();
}

}
