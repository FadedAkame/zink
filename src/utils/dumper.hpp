#pragma once

#include "frontend/tokens.hpp"

#include <span>

namespace zink::dumper {

void tokens(std::span<const Token> tokens);

}
