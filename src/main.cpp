#include <fstream>
#include <iostream>
#include <iterator>

constexpr auto filename { "tests/var.fe" };

int main() {
    std::fstream source_stream { filename };
    std::string translation_unit { std::istreambuf_iterator<char> { source_stream }, { } };

    std::cout << translation_unit;
}
