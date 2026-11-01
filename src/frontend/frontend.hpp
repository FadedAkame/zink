#pragma once

#include "translation_unit.hpp"

#include <cstddef>

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
    TranslationUnit& _ctx;
    std::size_t _idx { };
};

}
