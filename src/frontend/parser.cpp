#include "frontend.hpp"
#include "utils/logger.hpp"

namespace zink {

Parser::Parser(TranslationUnit& ctx)
    : _tokens(ctx.tokens)
    , _nodes(ctx.nodes) {
    /* Preallocate AST */
    _nodes.reserve(_tokens.size());
}

void Parser::parse() {
    LOG(log::info, "Hello, from the Parser!");
}

}
