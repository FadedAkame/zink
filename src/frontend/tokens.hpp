#pragma once

#include <array>
#include <cstdint>
#include <string_view>
#include <utility>

namespace zink {

/* clang-format off */
/* All lexical tokens collected from the source code */
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

/* Keep keywords in order as they are declared in the enum for lookups,
 * comparisons, and ease of converting string -> enum */
inline constexpr std::array<std::pair<std::string_view, TokenTag>, 1> keyword_table = {{
    {"var", TokenTag::Var},
}};
/* clang-format on */

struct Token {
    using SrcCodeOffset = std::uint32_t;
    using TokenLength = std::uint16_t;

    SrcCodeOffset offset; /* Offset into the src code */
    TokenLength len; /* Length of token from offset */
    TokenTag tag; /* Token representation */
};

/* Programs have LOTS of tokens so keeping tokens small enough for cache
 * friendlyness is better for less reads and overall faster fetching */
static_assert(sizeof(Token) == 8);
static_assert(sizeof(TokenTag) == 1);

}
