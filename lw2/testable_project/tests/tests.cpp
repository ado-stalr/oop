#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Reverse.h"

//TEST_CASE("example test") {
//	REQUIRE(2 + 2 == 4);
//}

SCENARIO("Reversing of empty string gives an empty string")
{
	REQUIRE(Reverse("").empty());
}

SCENARIO("Reversing of 1 char string is the string itself")
{
	REQUIRE(Reverse("a") == "a");
}

SCENARIO("Revers of string longer then 1 char")
{
	REQUIRE(Reverse("abcd") == "dcba");
}