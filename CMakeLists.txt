cmake_minimum_required(VERSION 3.29)

project(Minesweeper)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/utils)
add_subdirectory(lib/graphics)
add_subdirectory(lib/logic)
add_subdirectory(lib/playfield)

add_executable(Minesweeper main.cpp window.h window.cpp)
target_link_libraries(Minesweeper PRIVATE playfield logic)
