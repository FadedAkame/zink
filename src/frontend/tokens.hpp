#pragma once

#include <cstdint>

namespace zink {

/* clang-format off */
enum class TokenTag : std::uint8_t {
    /* Literals */
    Identifier, IntLiteral,

    /* Grammar */
    Semicolon,

    /* Keywords */
    Var,

    /* Operators */
    Equals,

    Eof
};
/* clang-format on */

/* More memory efficient (8 bytes) than a tag
 * and a string_view (24 bytes) & more cache
 * friendly. Although a SoA's *might* be better. */
struct Token {
    std::uint32_t offset;
    std::uint16_t len;
    TokenTag tag;
};

static_assert(sizeof(Token) == 8);
static_assert(sizeof(TokenTag) == 1);

}
