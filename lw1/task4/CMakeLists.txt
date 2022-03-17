cmake_minimum_required(VERSION 3.21)
project(rle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

# добавление флага для беззнакового char
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -funsigned-char")

add_executable(rle main.cpp)
