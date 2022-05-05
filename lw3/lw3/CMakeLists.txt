cmake_minimum_required(VERSION 3.21)
project(task1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(task1 main.cpp Car.cpp Car.h CarController.cpp CarController.h)

# Tests
add_subdirectory(tests)