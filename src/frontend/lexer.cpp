#include "frontend.hpp"
#include "tokens.hpp"
#include "translation_unit.hpp"
#include "utils/logger.hpp"
#include "utils/sentinel.hpp"

#include <algorithm>

namespace zink {

/* --- Helpers ---------------------------------- */
static constexpr bool is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}
static constexpr bool is_numeric(char c) {
    return c >= '0' && c <= '9';
}
static constexpr bool is_alpha_numeric(char c) {
    return is_numeric(c) || is_alpha(c);
}

static constexpr TokenTag find_keyword(std::string_view keyword) {
    for (const auto& key : keyword_table)
        if (key.first == keyword)
            return key.second;

    return TokenTag::Identifier;
}

/* --- Lexer ------------------------------------ */
Lexer::Lexer(TranslationUnit& ctx)
    : _source_code(ctx.source_code)
    , _tokens(ctx.tokens) {
    /* Preallocate token stream, avoids many reallocations */
    const auto count { static_cast<std::size_t>(std::ranges::count(_source_code, ';')) };
    _tokens.reserve(count * 6);
}

void Lexer::tokenize() {
    while (!at_end()) {
        switch (current()) {
        /* Whitespace */
        case ' ':
        case '\n':
        case '\t':
        case '\v':
        case '\r':
            break;

        /* Grammar */
        case ';':
            _tokens.emplace_back(sentinel::na, sentinel::na, TokenTag::Semicolon);
            break;

        /* Operators */
        case '=':
            _tokens.emplace_back(sentinel::na, sentinel::na, TokenTag::Equals);
            break;

        default:
            if (is_numeric(current())) {
                /* Tokenize literals */
                const auto start_pos { _idx };
                while (!at_end() && is_numeric(peek()))
                    consume();

                const auto end_pos { (_idx + 1) - start_pos };
                _tokens.emplace_back(start_pos, end_pos, TokenTag::IntLiteral);
            } else if (is_alpha(current())) {
                /* Tokenize identifiers */
                const auto start_pos { _idx };
                while (!at_end() && is_alpha_numeric(peek()))
                    consume();

                const auto end_pos { (_idx + 1) - start_pos };
                const auto tag { find_keyword(_source_code.substr(start_pos, end_pos)) };
                _tokens.emplace_back(start_pos, end_pos, tag);
            } else {
                /* Nothing detected */
                ZLOG(log::err, "unknown character found '{}'", current());
            }
            break;
        }

        consume();
    }

    _tokens.emplace_back(sentinel::na, sentinel::na, TokenTag::Eof);
}

constexpr bool Lexer::at_end() const { return _idx + 1 >= _source_code.length(); }
constexpr char Lexer::current() const { return _source_code.at(_idx); }
constexpr char Lexer::peek() const { return _source_code.at(_idx + 1); }
constexpr char Lexer::consume() { return _source_code.at(++_idx); }

}
