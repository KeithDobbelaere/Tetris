cmake_minimum_required(VERSION 3.5)
project(Tetris
    VERSION 0.0.1
    DESCRIPTION "Tetris built with raylib."
    LANGUAGES CXX)

file(GLOB SOURCES "src/*.cpp")
add_executable(Tetris ${SOURCES})
target_link_libraries(Tetris raylib)
set_target_properties(Tetris PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})