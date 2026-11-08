#include "ast.hpp"
#include "frontend.hpp"
#include "tokens.hpp"
#include "translation_unit.hpp"
#include "utils/logger.hpp"
#include "utils/sentinel.hpp"

#include <vector>

namespace zink {

/* --- Helpers ---------------------------------- */
constexpr bool Parser::at_end() const {
    return _tokens[_token_idx].tag == TokenTag::Eof
        || _token_idx + 1 >= _tokens.size();
}
constexpr Token Parser::current() const { return _tokens[_token_idx]; }
constexpr Token Parser::peek() const { return _tokens[_token_idx + 1]; }
constexpr Token Parser::consume() { return _tokens[++_token_idx]; }
constexpr void Parser::push_node(ASTTag tag,
    ASTNode::TokenIndex main_token,
    ASTNode::ASTIndex lhs,
    ASTNode::ASTIndex rhs) {
    _nodes.emplace_back(tag, main_token, lhs, rhs);
}

/* --- Parser ----------------------------------- */
Parser::Parser(TranslationUnit& ctx)
    : _tokens(ctx.tokens)
    , _nodes(ctx.ast) {
    /* Preallocate AST, avoids many reallocations */
    _nodes.reserve(_tokens.size());
}

void Parser::parse() {
    while (!at_end()) {
        declaration();
        consume();
    }
}

/* --- Declaration parsers --- */
void Parser::declaration() {
    switch (current().tag) {
    case TokenTag::Var:
        variable_decl();
        break;
    default:
        PANIC("Token parsed as declaration couldn't be resolved as a declaration");
        break;
    }
}

void Parser::variable_decl() {
    RELEASE_EXPECT(consume().tag == TokenTag::Identifier,
        "Expected a symbol for variable declaration");
    const auto symbol { _token_idx };

    push_node(ASTTag::VarDecl, symbol, static_cast<ASTNode::ASTIndex>(_nodes.size()) + 1, sentinel::na);
    RELEASE_EXPECT(consume().tag == TokenTag::Equals,
        "Variable must be assigned at declaration");
    expression();

    RELEASE_EXPECT(consume().tag == TokenTag::Semicolon,
        "Expected semicolon after expression");
}

/* --- Expression parsers --- */
void Parser::expression() {
    switch (consume().tag) {
    case TokenTag::IntLiteral:
        push_node(ASTTag::Number, _token_idx, sentinel::na, sentinel::na);
        break;
    case TokenTag::Identifier:
        push_node(ASTTag::Symbol, _token_idx, sentinel::na, sentinel::na);
        break;
    default:
        PANIC("Expression couldn't be resolved as an expression");
        break;
    }
}

}
