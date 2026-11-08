#pragma once

#include <cstdint>

namespace zink {

/* Just another enum but for AST related representations, similar to Zigs way.
 * Each enum entry can change the meaning for 3 fields (lhs, rhs, main_token)
 * in ASTNode.
 * So, each entry will have a comment showing what each field represents,
 * for example
 *
 * main_token = symbol name (index into token stream to the token for its symbol)
 * lhs = index into beginning of expression (index meaning into the ASTNode array)
 * rhs = NA (NA or sentinel::na means the value has no meaning aka 'NULL')
 */
enum class ASTTag : std::uint8_t {
    /* main_token = symbol name.
     * lhs = index into beginning of expression.
     * rhs = NA. */
    VarDecl,

    /* Expressions */
    /* main_token = number.
     * lhs = NA.
     * rhs = NA. */
    Number,
    /* main_token = symbol.
     * lhs = NA.
     * rhs = NA. */
    Symbol,
};

struct ASTNode {
    using TokenIndex = std::uint32_t;
    using ASTIndex = std::uint32_t;

    ASTTag tag;
    TokenIndex main_token; /* Refer to 'tag' for representation */
    ASTIndex lhs; /* Refer to 'tag' for representation */
    ASTIndex rhs; /* Refer to 'tag' for representation */
};

}
