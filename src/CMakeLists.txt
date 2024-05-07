add_executable(json_parser
    main.cpp
    lexer.cpp
)

target_include_directories(json_parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

