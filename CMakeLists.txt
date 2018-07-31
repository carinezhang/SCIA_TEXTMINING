cmake_minimum_required(VERSION 2.8)

PROJECT(TextMining CXX)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++14 -pedantic -Wall -Wextra -Werror -O0 -g")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")

add_custom_target(doc
    COMMAND doxygen doc.conf
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doc)

include_directories(src)

set(SRC_COMPILE
    src/compiler.cc
    src/node.cc
    src/trie.cc
    src/search.cc
)

set(SRC_APP
    src/app.cc
    src/node.cc
    src/trie.cc
    src/search.cc
)

set(TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_executable(TextMiningCompiler ${SRC_COMPILE})
add_executable(TextMiningApp ${SRC_COMPILE})
