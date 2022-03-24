#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::vector<float> ReadArrayFromStream(std::istream& input)
{
	return std::vector<float>(std::istream_iterator<float>{ input }, std::istream_iterator<float>{});
}

bool DivideByHalfMax(std::vector<float>& numbers)
{
	float maxEl = *std::max_element(numbers.begin(), numbers.end());
	float halfMaxEl = maxEl / 2;

	if (halfMaxEl == 0)
	{
		std::cout << "Divide by zero is not allowed" << std::endl;
		return false;
	}

	for (float& number : numbers)
	{
		number /= halfMaxEl;
	}

	return true;
}

void SortVector(std::vector<float>& arr)
{
	sort(arr.begin(), arr.end());
}

void WriteVectorToStream(std::vector<float>& arr, std::ostream& output)
{
	copy(arr.begin(), arr.end(), std::ostream_iterator<float>(output << std::setprecision(3) << std::fixed, ", "));
}

int main()
{
	std::vector<float> numbers = ReadArrayFromStream(std::cin);
	if (numbers.empty())
	{
		std::cout << "Input does not contain numbers" << std::endl;
		return 1;
	}

	if (!DivideByHalfMax(numbers))
	{
		return 1;
	}

	SortVector(numbers);
	WriteVectorToStream(numbers, std::cout);

	return 0;
}