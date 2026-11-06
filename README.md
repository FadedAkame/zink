# Zink

Zink is a general purpose low-level compiled programming language

---
## Philosophy
Zink takes lots of inspiration from C and C++, combining C's explicitness and simplicity with C++'s zero cost abstractions and compile time capabilities. The goal is to provide low-level control without sacrificing the developers sanity and convenience.

Zink aims to keep its language design dead simple, its standard library lightweight and its abstractions predictable without unnessesary complexity nor bloat.

Zink is NOT trying to be a replacement of any language, its simply a overly ambitious learning project.

---
## Example
*"Hello, World!" example program in Zink*
```
import("print");

fn main() u8 {
    std.println("Hello, {}", "World!");
    return 0;
}
```
*NOTE: This is the planned future syntax example in Zink*

---
## Status
*See ```ROADMAP.md``` for details on the active progression.*

Zink is currently still in active development.

Features and syntax are subject to change as the compiler matures and evolves.

---
## Requirements
*Developed & Tested on Arch Linux*
- **OS:** Linux
- **Compiler:** GCC w/ C++20 support
- **Build System:** CMake + GNU Make

---
## Building
Zink doesn't depend on third party vendors, a git clone will suffice.
```
git clone https://github.com/FadedAkame/zink.git
```
Then configure and build the project.
```
cmake -B build
cmake --build build -j$(nproc)
```

---
## License
Licensed under MIT.
See ```LICENSE.md``` for details.
