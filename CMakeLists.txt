cmake_minimum_required(VERSION 2.8)

PROJECT(TextMining CXX)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++14 -pedantic -Wall -Wextra -Werror -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")

ADD_CUSTOM_TARGET (doc doxygen ./doc/doc.conf)

include_directories(src)

set(SRCBASE
    $<TARGET_OBJECTS:node_obj>
    $<TARGET_OBJECTS:trie_obj>)

set(SRC_COMPILE
    ${SRCBASE}
    src/compiler.cc
)

set(TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_executable(TextMiningCompiler ${SRC_COMPILE})
