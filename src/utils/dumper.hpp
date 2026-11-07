#pragma once

#include "frontend/ast.hpp"
#include "frontend/tokens.hpp"

#include <span>

namespace zink::dump {

void tokens(std::span<const Token> tokens);
void ast(std::span<const ASTNode> ast_tree);

}
