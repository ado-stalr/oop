#include <cstring>
#include <iostream>
#include <optional>

enum Direction
{
	UNDEFINED,
	LEFT,
	RIGHT
};

struct Args
{
	uint8_t number;
	int shiftsAmount;
	Direction direction;
};

Direction ParseDirection(char* arg)
{
	if (strcasecmp(arg, "L") == 0)
	{
		return LEFT;
	}
	else if (strcasecmp(arg, "R") == 0)
	{
		return RIGHT;
	}

	return UNDEFINED;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: rotatebyte.exe <byte> <number of bits> <L / R>\n";
		return std::nullopt;
	}

	Args args;
	try
	{
		unsigned int number = std::stoi(argv[1]);
		unsigned int shiftsAmount = std::stoi(argv[2]);

		if (number > 255)
		{
			throw std::invalid_argument("Invalid argument <byte>\n");
		}

		args.direction = ParseDirection(argv[3]);
		if (!args.direction)
		{
			throw std::invalid_argument("Invalid argument <L / R>\n");
		}

		args.number = number;
		args.shiftsAmount = shiftsAmount;
	}
	catch (std::invalid_argument e)
	{
		std::cout << "Invalid arguments\n"
				  << "Usage: rotatebyte.exe <byte> <number of bits> <L / R>\n";
		return std::nullopt;
	}

	return args;
}

//Оптимизировать без цикла
// RotateByte(uint8_t byte, int shifts, Direction dir)
int RotateByte(int number, int shifts, int direction)
{
	int resultNumber = number;
	for (int i = 0; i < shifts; i++)
	{
		if (direction)
		{
			resultNumber = (resultNumber >> 1) | ((resultNumber & 0b01) << 7);
		}
		else
		{
			resultNumber = (resultNumber << 1) | ((resultNumber & 0b10000000) >> 7);
		}
	}
	return resultNumber & 0b11111111;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}


	std::cout << RotateByte(args->number, args->shiftsAmount % 8, args->direction) << std::endl;

	return 0;
}
