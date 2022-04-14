#include "Reverse.h"
#include <iterator>
#include <algorithm>

std::string Reverse(const std::string& str)
{
	int i = 2;
	std::string reversed;
	reversed.reserve(str.length());

	std::reverse_copy(str.begin(), str.end(), std::back_inserter(reversed));

	return reversed;
}


std::string Copy(const std::string& str)
{
	return str;
}