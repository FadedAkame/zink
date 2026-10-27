cmake_minimum_required(VERSION 3.5)

project(zink LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_DEBUG "Build in debug mode" ON)
option(ENABLE_ASAN  "Enable AddressSanitizer + UBSan" ON)

if(ENABLE_DEBUG)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
else()
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

set(SOURCE_FILES
    src/main.cpp
    src/utils/dumper.cpp
    src/frontend/lexer.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_compile_options(${PROJECT_NAME} 
    PRIVATE -Werror -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow
)

if(ENABLE_ASAN)
    set(SAN_FLAGS -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_compile_options(${PROJECT_NAME} PRIVATE ${SAN_FLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${SAN_FLAGS})
endif()
