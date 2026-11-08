#include "frontend/frontend.hpp"
#include "translation_unit.hpp"
#include "utils/arg_parser.hpp"
#include "utils/dumper.hpp"

using namespace zink;

int main(int argc, char** argv) {
    TranslationUnit ctx;
    parse_args(argc, argv, ctx);

    Lexer lexer { ctx };
    lexer.tokenize();
    if (ctx.dump_tokens)
        dump::tokens(ctx.tokens);

    Parser parser { ctx };
    parser.parse();
    if (ctx.dump_ast)
        dump::ast(ctx.ast);

    return EXIT_SUCCESS;
}
