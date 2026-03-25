cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(parser)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(parser
    ./src/main.cpp
    ./src/lexer.cpp
    ./src/parser.cpp
)


target_compile_options(parser PRIVATE -Wall -Wextra -Wconversion -Wpedantic -Wimplicit-fallthrough)
