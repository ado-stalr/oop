#include "VectorFunctions.h"

int main()
{
	std::vector<float> numbers = ReadArrayFromStream(std::cin);

	if (!DivideByHalfMax(numbers))
	{
		return 1;
	}

	SortVector(numbers);
	WriteVectorToStream(numbers, std::cout);

	return 0;
}