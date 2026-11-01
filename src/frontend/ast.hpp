#pragma once

#include <cstdint>

namespace zink {

enum class ASTTag : std::uint8_t {
    VarDecl,
};

struct ASTNode {
    using TokenIndex = std::uint32_t;
    using Index = std::uint32_t;

    ASTTag tag;
    TokenIndex main_token;
    Index lhs;
    Index rhs;
};

}
