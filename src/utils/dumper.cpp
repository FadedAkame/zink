#include "dumper.hpp"
#include "frontend/ast.hpp"
#include "frontend/tokens.hpp"
#include "logger.hpp"
#include "sentinel.hpp"

#include <iostream>

namespace zink::dump {

void tokens(std::span<const Token> tokens) {
#define CASE(v) \
    case (v):   \
        return #v;
    auto get_str = [](TokenTag tag) {
        switch (tag) {
            CASE(TokenTag::Var);
            CASE(TokenTag::Identifier);
            CASE(TokenTag::IntLiteral);
            CASE(TokenTag::Semicolon);
            CASE(TokenTag::Equals);
            CASE(TokenTag::Eof);
        default:
            return "Unknown: check if ALL lexer tokens are cased in dumper!";
        }
    };
#undef CASE

    ZLOG(log::info, "--- Lexer Output Tokens ---");
    ZLOG(log::info, "[TOKEN_TAG OFFSET:LENGTH]");
    for (const auto& tok : tokens) {
        std::clog << '[' << get_str(tok.tag)
                  << ' '
                  << (tok.offset == sentinel::na ? "NA" : std::to_string(tok.offset))
                  << ':'
                  << (tok.len == sentinel::na ? "NA" : std::to_string(tok.len))
                  << "]\n";
    }
}

void ast(std::span<const ASTNode> ast) {
#define CASE(v) \
    case (v):   \
        return #v;
    auto get_str = [](ASTTag tag) {
        switch (tag) {
            CASE(ASTTag::VarDecl);
            CASE(ASTTag::NumLiteral);
            CASE(ASTTag::Symbol);
        default:
            return "Unknown: check if ALL lexer tokens are cased in dumper!";
        }
    };
#undef CASE

    ZLOG(log::info, "--- AST Tree ---");
    ZLOG(log::info, "'ast.hpp' for more info on the structure.");
    for (const auto& node : ast) {
        std::clog << '[' << get_str(node.tag)
                  << ' '
                  << "Token(" << node.main_token << ") "
                  << (node.lhs == sentinel::na ? "NA" : std::to_string(node.lhs))
                  << ':'
                  << (node.rhs == sentinel::na ? "NA" : std::to_string(node.rhs))
                  << "]\n";
    }
}

}
