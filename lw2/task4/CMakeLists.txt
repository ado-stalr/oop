cmake_minimum_required(VERSION 3.21)
project(generatePrimeNumbers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")


add_executable(generatePrimeNumbers main.cpp PrimeNumbersFunctions.cpp PrimeNumbersFunctions.h)

# Tests
add_subdirectory(tests)
