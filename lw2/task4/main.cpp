#include "PrimeNumbersFunctions.h"

int main(int argc, char* argv[])
{
    const std::optional<int> upperLimit = ParseProgramArgs(argc, argv);
    if (!upperLimit)
    {
        return 1;
    }

    std::set<int> primeNumbers = GeneratePrimeNumbersSet(*upperLimit);

    PrintSet(primeNumbers);

    return 0;
}