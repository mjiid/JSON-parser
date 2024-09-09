cmake_minimum_required(VERSION 3.10)
project(JsonParser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(json_parser
    src/JsonValue.cpp
    src/Tokenizer.cpp
    src/Parser.cpp
)

add_executable(json_parser_test test/main.cpp)
target_link_libraries(json_parser_test json_parser)