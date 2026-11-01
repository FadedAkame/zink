#include "frontend/frontend.hpp"
#include "translation_unit.hpp"
#include "utils/dumper.hpp"
#include "utils/logger.hpp"

#include <fstream>
#include <iterator>

using namespace zink;

constexpr auto filename { "tests/var.zn" };

int main() {
    std::fstream source_stream { filename };
    RELEASE_EXPECT(source_stream.is_open(), "couldn't open file '{}'", filename);

    TranslationUnit ctx;
    ctx.source_code = std::string(std::istreambuf_iterator<char> { source_stream }, { });

    Lexer lexer { ctx };
    Parser parser { ctx };
    lexer.tokenize();
    parser.parse();

    dumper::tokens(ctx.tokens);
}
