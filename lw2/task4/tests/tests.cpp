#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../PrimeNumbersFunctions.h"

SCENARIO("Test with upperBound < 0")
{
	int upperBound = -100;
	std::set<int>set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.empty());
}

SCENARIO("Test with upperBound = 0")
{
	int upperBound = 0;
	std::set<int>set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.empty());
}

SCENARIO("Test with upperBound = 1")
{
	int upperBound = 1;
	std::set<int>set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.empty());
}

SCENARIO("Test with upperBound = 2")
{
	int upperBound = 2;
	std::set<int> expectingSet{ 2 };
	std::set<int>set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.size() == 1);
	REQUIRE(set == expectingSet);
}

SCENARIO("Test with upperBound = 20")
{
	int upperBound = 20;
	std::set<int> expectingSet{ 2, 3, 5, 7, 11, 13, 17, 19 };
	std::set<int>set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set == expectingSet);
}

SCENARIO("Test with upperBound = 100000000")
{
	int upperBound = 100000000;
	std::set<int>set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.size() == 5761455);
}

SCENARIO("Test with upperBound > 100000000")
{
	int upperBound = 100000001;
	std::set<int>set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.empty());
}