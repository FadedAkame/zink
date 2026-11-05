#pragma once

#include "translation_unit.hpp"

#include <cstddef>
#include <span>
#include <string_view>
#include <vector>

namespace zink {

class Lexer {
public:
    Lexer(TranslationUnit& ctx);
    void tokenize();

private:
    constexpr bool at_end() const;
    constexpr char current() const;
    constexpr char peek() const;
    constexpr char consume();

private:
    std::string_view _source_code;
    std::vector<Token>& _tokens;
    std::size_t _idx { };
};

class Parser {
public:
    Parser(TranslationUnit& ctx);
    void parse();

private:
    constexpr bool at_end() const;
    constexpr Token current() const;
    constexpr Token peek() const;
    constexpr Token consume();
    constexpr void push_node(ASTTag tag,
        ASTNode::TokenIndex main_token,
        ASTNode::ASTIndex lhs,
        ASTNode::ASTIndex rhs);

    void declaration();
    void expression();

    void variable_decl();

private:
    std::span<const Token> _tokens;
    std::vector<ASTNode>& _nodes;
    Token::SrcCodeOffset _token_idx { };
    ASTNode::ASTIndex _ast_idx { };
};

}
