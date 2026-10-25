#include "frontend.hpp"

#include <algorithm>
#include <span>
#include <string_view>

namespace zink {

Lexer::Lexer(std::string_view source_code)
    : _source_code(source_code) {
    auto count { static_cast<std::size_t>(std::ranges::count(_source_code, ';')) };
    _tokens.reserve(count * 6);
}

std::span<const Token> Lexer::tokenize() {
    return _tokens;
}

}
