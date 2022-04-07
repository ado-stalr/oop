#include "VectorFunctions.h"

std::vector<float> ReadArrayFromStream(std::istream& input)
{
	return std::vector<float>(std::istream_iterator<float>{ input }, std::istream_iterator<float>{});
}

bool DivideByHalfMax(std::vector<float>& numbers)
{
	//обработать ситуацию когда намберс пустой
	if (numbers.empty())
	{
		return true;
	}


	float maxEl = *std::max_element(numbers.begin(), numbers.end());
	float halfMaxEl = maxEl / 2;

	if (halfMaxEl == 0)
	{
		// никакого вывода не должно быть
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
