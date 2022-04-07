#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../VectorFunctions.h"

SCENARIO("Test with empty vector")
{
	std::vector<float> initalVector (0);
	std::vector<float> expectedVector (0);
	bool result = DivideByHalfMax(initalVector);
	REQUIRE(result == true);
	REQUIRE(initalVector == expectedVector);
}

SCENARIO("Test with one number")
{
	std::vector<float> initalVector = { 20 };
	std::vector<float> expectedVector = { 2 };
	bool result = DivideByHalfMax(initalVector);
	REQUIRE(result == true);
	REQUIRE(initalVector == expectedVector);
}

SCENARIO("Test with simple vector")
{
	std::vector<float> initalVector = { 20, 10, 5 };
	std::vector<float> expectedVector = { 2, 1, 0.5 };
	bool result = DivideByHalfMax(initalVector);
	REQUIRE(result == true);
	REQUIRE(initalVector == expectedVector);
}

SCENARIO("Test with dividing zero")
{
	std::vector<float> initalVector = { -20, -10, 0 };
	bool result = DivideByHalfMax(initalVector);
	REQUIRE(result == false);
}

SCENARIO("Test with negative numbers")
{
	std::vector<float> initalVector = { -1, -20, -5 };
	std::vector<float> expectedVector = { 2, 40, 10 };
	bool result = DivideByHalfMax(initalVector);
	REQUIRE(result == true);
	REQUIRE(initalVector == expectedVector);
}

SCENARIO("Test sorting numbers")
{
	std::vector<float> initalVector = { 20, -10, 5};
	SortVector(initalVector);
	std::vector<float> expectedVector = { -10, 5, 20 };
	REQUIRE(initalVector == expectedVector);
}
