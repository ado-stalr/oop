cmake_minimum_required(VERSION 3.21)
project(testable_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(testable_project main.cpp Reverse.cpp Reverse.h)

# Tests
add_subdirectory(tests)