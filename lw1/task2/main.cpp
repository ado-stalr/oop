#include <cstring>
#include <iostream>
#include <optional>

struct Args
{
	int number;
	int shiftsAmount;
	int direction; // 0 - Left;  1 - Right
};

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
		int direction;

		if (number > 255)
		{
			throw std::invalid_argument("Invalid argument <byte>\n");
		}

		if (!strcmp(argv[3], "L"))
		{
			direction = 0;
		}
		else if (!strcmp(argv[3], "R"))
		{
			direction = 1;
		}
		else
		{
			throw std::invalid_argument("Invalid argument <L / R>\n");
		}

		args.number = number;
		args.shiftsAmount = shiftsAmount;
		args.direction = direction;
	}
	catch (std::invalid_argument e)
	{
		std::cout << "Invalid arguments\n"
				  << "Usage: rotatebyte.exe <byte> <number of bits> <L / R>\n";
		return std::nullopt;
	}

	return args;
}

int RotateByte(int number, int shiftsAmount, int direction)
{
	int resultNumber = number;
	for (int i = 0; i < shiftsAmount; i++)
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
