#include "utils/logger.hpp"

#include <fstream>
#include <iostream>
#include <iterator>

constexpr auto filename { "tests/var.zn" };

int main() {
    std::fstream source_stream { filename };
    RELEASE_EXPECT(source_stream.is_open(), "couldn't open file '{}'", filename);
    std::string translation_unit { std::istreambuf_iterator<char> { source_stream }, { } };

    std::cout << translation_unit;
}
