#ifndef VECTORS_VECTORFUNCTIONS_H
#define VECTORS_VECTORFUNCTIONS_H

#endif // VECTORS_VECTORFUNCTIONS_H

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::vector<float> ReadArrayFromStream(std::istream& input);
bool DivideByHalfMax(std::vector<float>& numbers);
void SortVector(std::vector<float>& arr);
void WriteVectorToStream(std::vector<float>& arr, std::ostream& output);