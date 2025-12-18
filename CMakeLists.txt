cmake_minimum_required(VERSION 3.5)

project(fun)

set(CMAKE_CXX_STANDARD 20)

add_executable(
    fun
    src/main.cpp
    src/Editor.cpp
    src/TextBuffer.cpp
    src/Row.cpp

)
target_link_libraries(fun ncurses)
