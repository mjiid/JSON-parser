cmake_minimum_required(VERSION 3.10)
project(JSONParser)

# Set the source files and include directories
set(SOURCES
    src/main.cpp
    src/lexer.cpp
)

# Include directories for header files
include_directories(include)

# Create the executable from source files
add_executable(json_parser ${SOURCES})

