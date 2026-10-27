#include "dumper.hpp"
#include "sentinel.hpp"

#include <iostream>

namespace zink::dumper {

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
            return "Unknown: you shouldn't see this";
        }
    };
#undef CASE

    for (const auto& tok : tokens) {
        std::clog << '[' << get_str(tok.tag)
                  << ' '
                  << (tok.offset == sentinel::na ? "NA" : std::to_string(tok.offset))
                  << ':'
                  << (tok.len == sentinel::na ? "NA" : std::to_string(tok.len))
                  << "]\n";
    }
}

}
