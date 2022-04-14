cmake_minimum_required(VERSION 3.21)
project(parseUrl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(parseUrl main.cpp parseUrlFunctions.cpp parseUrlFunctions.h)

# Tests
add_subdirectory(tests)