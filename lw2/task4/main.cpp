#include <optional>
#include <set>
#include <vector>
#include <iostream>

constexpr int MAX_NUMBER = 100000000;

std::optional<int> ParseProgramArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Incorrect program arguments" << std::endl;
        std::cout << "Usage: generatePrimeNumbers.exe < Upper_Limit >" << std::endl;
        return std::nullopt;
    }

    int upperLimit = 0;
    upperLimit = std::stoi(argv[1]);
    if (!upperLimit)
    {
        std::cout << "Incorrect <Upper_Limit> argument" << std::endl;
        std::cout << "Usage: generatePrimeNumbers.exe < Upper_Limit >" << std::endl;
        return std::nullopt;
    }
    else if (upperLimit > MAX_NUMBER)
    {
        std::cout << "Incorrect <Upper_Limit> argument" << std::endl;
        std::cout << "Upper_Limit should be less 100 000 000" << std::endl;
        return std::nullopt;
    }

    return upperLimit;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::set<int> primeNumbers;
    if (upperBound < 0)
    {
        return primeNumbers;
    }
    std::vector<bool> array(upperBound + 1, true);
    int count;
    for (count = 2; count * count <= upperBound; count++)
    {
        if (array[count])
        {
            primeNumbers.insert(primeNumbers.end(), count);
            for (int j = count * count; j <= upperBound; j += count)
            {
                array[j] = false;
            }
        }
    }

    for (; count < upperBound + 1; count++)
    {
        if (array[count])
        {
            primeNumbers.insert(primeNumbers.end(), count);
        }
    }
    return primeNumbers;
}

void PrintSet(const std::set<int> &set)
{
    int count = 0;
    for (int item : set)
    {
        count++;
        std::cout << item;
        if (count != set.size())
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

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