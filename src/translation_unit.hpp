#pragma once

#include "frontend/ast.hpp"
#include "frontend/tokens.hpp"

#include <string>
#include <vector>

namespace zink {

struct TranslationUnit {
    std::string source_code;
    std::vector<Token> tokens;
    std::vector<ASTNode> ast;

    bool dump_tokens : 1 { false };
    bool dump_ast : 1 { false };
};

}
