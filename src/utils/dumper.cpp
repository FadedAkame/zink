#include "dumper.hpp"
#include "frontend/ast.hpp"
#include "frontend/tokens.hpp"
#include "logger.hpp"
#include "sentinel.hpp"

namespace zink::dump {

#define CASE(v) \
    case (v):   \
        return #v;

void tokens(std::span<const Token> tokens) {
    auto enum2str = [](TokenTag tag) {
        using token = zink::TokenTag;

        switch (tag) {
            CASE(token::Var);
            CASE(token::Identifier);
            CASE(token::IntLiteral);
            CASE(token::Semicolon);
            CASE(token::Equals);
            CASE(token::Eof);
        default:
            PANIC("Unknown: check if ALL lexer tokens are cased in dumper!");
        }
    };

    std::size_t counter { };
    RELEASE_ZLOG(log::info, "--- Lexer Output Tokens ---");
    RELEASE_ZLOG(log::info, "[TOKEN_TAG OFFSET:LENGTH] : INDICE");
    for (const auto& tok : tokens) {
        RELEASE_ZLOG(log::info, "  [{} {}:{}] : {}",
            enum2str(tok.tag),
            (tok.offset == sentinel::na ? "NA" : std::to_string(tok.offset)),
            (tok.len == sentinel::na ? "NA" : std::to_string(tok.len)),
            counter);
        ++counter;
    }
}

void ast(std::span<const ASTNode> ast_tree) {
    auto enum2str = [](ASTTag tag) {
        using ast = zink::ASTTag;

        switch (tag) {
            CASE(ast::VarDecl);
            CASE(ast::Number);
            CASE(ast::Symbol);
        default:
            PANIC("Unknown: check if ALL ASTTags are cased in dumper!");
        }
    };

    std::size_t counter { };
    RELEASE_ZLOG(log::info, "--- AST Tree ---");
    RELEASE_ZLOG(log::info, "[implementation defined] : INDICE");
    for (const auto& node : ast_tree) {
        RELEASE_ZLOG(log::info, "  [{} Token({}) {}:{}] : {}",
            enum2str(node.tag),
            node.main_token,
            (node.lhs == sentinel::na ? "NA" : std::to_string(node.lhs)),
            (node.rhs == sentinel::na ? "NA" : std::to_string(node.rhs)),
            counter);
        ++counter;
    }
}

#undef CASE

}
