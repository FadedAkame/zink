#pragma once

#include "frontend/tokens.hpp"

#include <span>

namespace zink::dump {

void tokens(std::span<const Token> tokens);

}
