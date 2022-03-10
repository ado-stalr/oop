#include <fstream>
#include <iostream>
#include <optional>
#include <string>

#define MATRIX_SIZE 3

typedef float Matrix3x3[MATRIX_SIZE][MATRIX_SIZE];
struct WrappedMatrix3x3
{
	Matrix3x3 items;
};

struct Args
{
	std::string inputFirstFileName;
	std::string inputSecondFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "Usage: multmatrix.exe <matrix file1> <matrix file2>\n";
		return std::nullopt;
	}

	Args args;
	args.inputFirstFileName = argv[1];
	args.inputSecondFileName = argv[2];

	return args;
}

std::optional<WrappedMatrix3x3> ReadSquareMatrix(const std::string& fileName)
{
	std::ifstream matrixFile(fileName);
	if (!matrixFile.is_open())
	{
		std::cout << "Failed to open matrix file for reading\n";
		return std::nullopt;
	}

	WrappedMatrix3x3 matrix = {};

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (!(matrixFile >> matrix.items[j][i]))
			{
				std::cout << "Incorrect matrix file format. Matrix should be 3 x 3\n";
				return std::nullopt;
			}
		}
	}

	if (matrixFile.bad() || !matrixFile.eof())
	{
		std::cout << "Incorrect matrix file format. Matrix should be 3 x 3\n";
		return std::nullopt;
	}

	return matrix;
}

void PrintSquareMatrix(WrappedMatrix3x3 matrix)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			std::cout.width(15);
			std::cout.setf(std::ios::fixed);
			std::cout.precision(3);
			std::cout << matrix.items[j][i];
		}
		std::cout << std::endl;
	}
}

//принимать входные матрицы по константной ссылке
WrappedMatrix3x3 MultiplyMatrix(WrappedMatrix3x3 matrix1, WrappedMatrix3x3 matrix2)
{
	WrappedMatrix3x3 multipliedMatrix = {};

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			for (int k = 0; k < MATRIX_SIZE; k++)
			{
				multipliedMatrix.items[j][i] += matrix1.items[k][i] * matrix2.items[j][k];
			}
		}
	}
	return multipliedMatrix;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	auto matrix1 = ReadSquareMatrix(args->inputFirstFileName);
	if (!matrix1)
	{
		return 1;
	}

	auto matrix2 = ReadSquareMatrix(args->inputSecondFileName);
	if (!matrix2)
	{
		return 1;
	}

	PrintSquareMatrix(MultiplyMatrix(*matrix1, *matrix2));

	return 0;
}
