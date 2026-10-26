#pragma once

#include <array>
#include <cstdint>
#include <string_view>
#include <utility>

namespace zink {

/* clang-format off */
enum class TokenTag : std::uint8_t {
    /* Keywords */
    Var = 0,

    /* Literals */
    Identifier, IntLiteral,

    /* Grammar */
    Semicolon,

    /* Operators */
    Equals,

    Eof
};

/* Keywords MUST be in order in the table & at the top
 * of the TokenTag enum class to properly index into the table*/
inline constexpr std::array<std::pair<std::string_view, TokenTag>, 1> keyword_table = {{
    {"var", TokenTag::Var},
}};
/* clang-format on */

/* More memory efficient (8 bytes) than a tag
 * and a string_view (24 bytes) & more cache
 * friendly. Although a SoA's *might* be better. */
struct Token {
    std::uint32_t offset; /* Offset into the src code */
    std::uint16_t len; /* Length of token from offset */
    TokenTag tag; /* TokenTag of what the token is */
};

static_assert(sizeof(Token) == 8);
static_assert(sizeof(TokenTag) == 1);

}
