cmake_minimum_required(VERSION 3.21)
project(rotatebyte)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(rotatebyte main.cpp)
