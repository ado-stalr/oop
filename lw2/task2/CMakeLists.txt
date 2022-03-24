cmake_minimum_required(VERSION 3.21)
project(decodeHtml)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(decodeHtml main.cpp)