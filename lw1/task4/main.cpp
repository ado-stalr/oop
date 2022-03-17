#include <cstring>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

enum Operation
{
	UNKNOWN,
	PACK,
	UNPACK
};

struct Args
{
	Operation operation;
	std::string inputFileName;
	std::string outputFileName;
};
//добавить тест на пустой
struct RLEChunk
{
	char ch = 0;
	uint8_t counter = 0;
};

std::optional<RLEChunk> TryReadChunk(std::istream& strm);
void WriteChunk(RLEChunk chunk, std::ostream& strm);
void CompressChar(char ch, RLEChunk& chunk, std::ostream& strm);


Operation ParseOperation(char* arg)
{
	if (strcasecmp(arg, "PACK") == 0)
	{
		return PACK;
	}
	else if (strcasecmp(arg, "UNPACK") == 0)
	{
		return UNPACK;
	}

	return UNKNOWN;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid arguments count\n"
				  << "Usage: rle.exe <pack / unpack> <input file> <output file>\n";
		return std::nullopt;
	}

	Args args;

	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	args.operation = ParseOperation(argv[1]);
	if (!args.operation)
	{
		std::cout << "Invalid <pack / unpack> argument\n"
				  << "Usage: rle.exe <pack / unpack> <input file> <output file>\n";
		return std::nullopt;
	}

	return args;
}

// переделать на uint 8
void printRepeatingChar(char ch, char count, std::ostream& output)
{
	for (char i = 0; i < count; i++)
	{
		if (!output.put(ch))
		{
			break;
		}
	}
}

void printPackedChar(char ch, char count, std::ostream& output)
{
	output.put(ch);
	output.put(count);
}

int pack(std::istream& input, std::ostream& output)
{
	char ch, currentCh;
	char counter = 0;
	while (input.get(ch))
	{
		if (!counter)
		{
			currentCh = ch;
			counter++;
			continue;
		}

		if (currentCh != ch)
		{
			printPackedChar(currentCh, counter, output);
			currentCh = ch;
			counter = 1;
		}
		else
		{
			if (char(counter + 1) == 0)
			{
				printPackedChar(currentCh, counter, output);
				counter = 0;
			}

			counter++;
		}
	}

	if (counter)
	{
		printPackedChar(currentCh, counter, output);
	}

	if (!output.flush())
	{
		std::cout << "Failed to write to output file\n";
		return 1;
	}

	return 0;
}

// не соблюдаются именования
// возращать тру при успехе и наоборот
int unpack(std::istream& input, std::ostream& output)
{
	char ch, counter;
	while (input.get(ch))
	{
		if (!input.get(counter) || counter == 0)
		{
			std::cout << "Incorrect packed data\n";
			return 1;
		}
		printRepeatingChar(ch, counter, output);
	}

	if (!output.flush())
	{
		std::cout << "Failed to write to output file\n";
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	std::ifstream input(args->inputFileName, std::ios_base::binary);
	if (!input.is_open())
	{
		std::cout << "Failed to open input file for reading\n";
		return 1;
	}

	std::ofstream output(args->outputFileName, std::ios_base::binary);
	if (!output.is_open())
	{
		std::cout << "Failed to open output file for writing\n";
		return 1;
	}

	switch (args->operation)
	{
	case PACK:
		return pack(input, output);
	case UNPACK:
		return unpack(input, output);
	default:
		return 1;
	}
}