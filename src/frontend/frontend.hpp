#pragma once

#include "tokens.hpp"

#include <cstddef>
#include <span>
#include <string_view>
#include <vector>

namespace zink {

class Lexer {
public:
    Lexer(std::string_view source_code);
    [[nodiscard]]
    std::span<const Token> tokenize();

private:
    std::string_view _source_code;
    std::vector<Token> _tokens;
    std::size_t _idx { };
};

}
