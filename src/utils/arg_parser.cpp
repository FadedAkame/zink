#include "arg_parser.hpp"
#include "logger.hpp"
#include "translation_unit.hpp"

#include <cstring>
#include <fstream>
#include <iterator>

namespace zink {

constexpr static auto help_output = "usage: zink {OPTIONS} {SOURCE_FILE(S)}\n"
                                    "  options:\n"
                                    "    --dump-tokens (Dumps the source file(s) lexical tokens)\n"
                                    "    --dump-ast (Dumps the source file(s) abstract syntax tree)\n";

void parse_args(int argc, char** argv, TranslationUnit& ctx) {
    RELEASE_EXPECT(argc > 1, "Nothing to do. '--help' for more info on arguments");

    for (auto i { 1 }; i < argc; ++i) {
        if (std::strcmp(argv[i], "--help") == 0)
            RELEASE_ZLOG(log::display, help_output);
        else if (std::strcmp(argv[i], "--dump-tokens") == 0)
            ctx.dump_tokens = true;
        else if (std::strcmp(argv[i], "--dump-ast") == 0)
            ctx.dump_ast = true;
        else {
            std::fstream source_stream { argv[i] };
            RELEASE_EXPECT(source_stream.is_open(), "couldn't open file '{}'", argv[i]);
            ctx.source_code = std::string(std::istreambuf_iterator<char> { source_stream }, { });
        }
    }

    /* Prevents compiling nothing */
    if (ctx.source_code.length() == 0)
        std::exit(EXIT_SUCCESS);
}

}
