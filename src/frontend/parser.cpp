#include "frontend.hpp"
#include "utils/logger.hpp"

namespace zink {

Parser::Parser(TranslationUnit& ctx)
    : _ctx(ctx) {
    /* Preallocate AST */
    _ctx.nodes.reserve(_ctx.tokens.size());
}

void Parser::parse() {
    LOG(log::info, "Hello, from the Parser!");
}

}
