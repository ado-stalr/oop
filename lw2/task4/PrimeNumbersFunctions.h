#ifndef GENERATEPRIMENUMBERS_PRIMENUMBERSFUNCTIONS_H
#define GENERATEPRIMENUMBERS_PRIMENUMBERSFUNCTIONS_H
#endif // GENERATEPRIMENUMBERS_PRIMENUMBERSFUNCTIONS_H

#include <optional>
#include <set>
#include <vector>
#include <iostream>

constexpr int MAX_NUMBER = 100000000;

std::optional<int> ParseProgramArgs(int argc, char* argv[]);
std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintSet(const std::set<int> &set);

