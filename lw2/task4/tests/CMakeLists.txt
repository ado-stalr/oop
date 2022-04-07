# FROM TUTORIAL
#add_executable(Catch_tests_run ConverterTests.cpp AbsoluteDateTest.cpp)
#target_link_libraries(Catch_tests_run DateConverter_lib)

set(TEST_FILES tests.cpp)
set(TESTING_FILES ../PrimeNumbersFunctions.cpp ../PrimeNumbersFunctions.h)

add_executable(tests ${TEST_FILES} ../../../catch2/catch.hpp ${TESTING_FILES})