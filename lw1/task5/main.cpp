#include <fstream>
#include <iostream>
#include <optional>
#include <queue>

#define FIELD_SIZE 100
#define START_FILLING_POINT_CHAR 'O'
#define FILLING_POINT_CHAR '.'

typedef char Field[FIELD_SIZE][FIELD_SIZE];

struct Point
{
	int x;
	int y;
};

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: fill.exe <input file> <output file>\n";
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	return args;
}

void FillPoint(Point point, Field* field, std::queue<Point>* fillingPoints)
{
	if (point.x >= 0 && point.x < FIELD_SIZE
		&& point.y >= 0 && point.y < FIELD_SIZE
		&& ((*field)[point.y][point.x] == ' ' || (*field)[point.y][point.x] == 0))
	{
		(*field)[point.y][point.x] = FILLING_POINT_CHAR;
		fillingPoints->push({ point.x, point.y });
	}
}

void FillField(Field* field, std::queue<Point>* fillingPoints)
{
	while (!fillingPoints->empty())
	{
		Point point = fillingPoints->front();

		FillPoint({ point.x, point.y + 1 }, field, fillingPoints);
		FillPoint({ point.x + 1, point.y }, field, fillingPoints);
		FillPoint({ point.x, point.y - 1 }, field, fillingPoints);
		FillPoint({ point.x - 1, point.y }, field, fillingPoints);

		fillingPoints->pop();
	}
}

void ReadField(Field* field, std::istream* input, std::queue<Point>* fillingPoints)
{
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		std::string line;
		std::getline(*input, line);
		if (input->bad() || input->eof())
		{
			return;
		}
		for (int j = 0; j < line.length() && j < FIELD_SIZE; j++)
		{
			(*field)[j][i] = line[j];
			if (line[j] == START_FILLING_POINT_CHAR)
			{
				fillingPoints->push({ i, j });
			}
		}
	}
}

void PrintField(Field field, std::ostream* output)
{
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if (field[j][i] != 0)
			{
				*output << field[j][i];
			}
		}
		*output << std::endl;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	std::ifstream input(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open input file for reading\n";
		return 1;
	}

	std::ofstream output(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open output file for writing\n";
		return 1;
	}

	Field field = { 0 };
	std::queue<Point> fillingPoints;

	ReadField(&field, &input, &fillingPoints);

	FillField(&field, &fillingPoints);

	PrintField(field, &output);

	return 0;
}
