cmake_minimum_required(VERSION 3.5)

project(fun)

set(CMAKE_CXX_STANDARD 23)

add_executable(
    fun
    src/main.cpp
    src/editor.cpp
    src/text_buffer.cpp
    src/row.cpp
    src/renderer.cpp
)
target_link_libraries(fun ncurses)
