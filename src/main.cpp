#include "frontend/frontend.hpp"
#include "utils/dumper.hpp"
#include "utils/logger.hpp"

#include <fstream>
#include <iterator>

constexpr auto filename { "tests/var.zn" };

int main() {
    std::fstream source_stream { filename };
    RELEASE_EXPECT(source_stream.is_open(), "couldn't open file '{}'", filename);
    std::string translation_unit { std::istreambuf_iterator<char> { source_stream }, { } };

    zink::Lexer lexer { translation_unit };
    [[maybe_unused]]
    auto tokens { lexer.tokenize() };

    zink::dumper::tokens(tokens);
}
