#pragma once

#include "frontend/ast.hpp"
#include "frontend/tokens.hpp"

#include <string>
#include <vector>

namespace zink {

struct TranslationUnit {
    std::string source_code;
    std::vector<Token> tokens;
    std::vector<ASTNode> nodes;
};

}
