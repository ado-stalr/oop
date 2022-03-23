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
void WriteUncompressedChunk(RLEChunk chunk, std::ostream& strm);
void CompressChar(char ch, RLEChunk& chunk, std::ostream& strm);
void WriteCompressedChar(RLEChunk chunk, std::ostream& output);

void CompressChar(char ch, RLEChunk& chunk, std::ostream& output)
{
	if (!chunk.counter)
	{
		chunk.ch = ch;
		chunk.counter++;
		return;
	}

	if (chunk.ch != ch)
	{
		WriteCompressedChar(chunk, output);
		chunk.ch = ch;
		chunk.counter = 1;
	}
	else
	{
		if (uint8_t (chunk.counter + 1) == 0)
		{
			WriteCompressedChar(chunk, output);
			chunk.counter = 0;
		}

		chunk.counter++;
	}
}

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

void WriteUncompressedChunk(RLEChunk chunk, std::ostream& output)
{
	for (uint8_t i = 0; i < chunk.counter; i++)
	{
		if (!output.put(chunk.ch))
		{
			break;
		}
	}
}

// исключение
// enum class ReadChunkResult{ OK, EoF, Error };
// [[nodiscard]] ReadChunkResult ReadChunk(RLEChunk& chunk);
// вариант
/*
std::optional<std::variant<std::monostate, RLEChunk>>;
 */
std::optional<RLEChunk> TryReadChunk(std::istream& input)
{
	RLEChunk chunk;
	input.get(chunk.ch);

	char counterChar = 0;
	if (!input.get(counterChar) || counterChar == 0)
	{
		chunk.counter = (uint8_t)(counterChar);
		std::cout << "Incorrect packed data\n";
		return std::nullopt;
	}
	return chunk;
}

void WriteCompressedChar(RLEChunk chunk, std::ostream& output)
{
	output.put(chunk.ch);
	output.put(chunk.counter);
}

bool Pack(std::istream& input, std::ostream& output)
{
	char ch;
	RLEChunk chunk;

	while (input.get(ch))
	{
		CompressChar(ch, chunk, output);
	}

	if (chunk.counter)
	{
		WriteCompressedChar(chunk, output);
	}

	if (!output.flush())
	{
		std::cout << "Failed to write to output file\n";
		return false;
	}

	return true;
}

bool Unpack(std::istream& input, std::ostream& output)
{
	RLEChunk chunk;
	while (input.get(chunk.ch))
	{
		char counterChar = 0;
		if (!input.get(counterChar) || counterChar == 0)
		{
			std::cout << "Incorrect packed data\n";
			return false;
		}
		chunk.counter = (uint8_t)(counterChar);
		WriteUncompressedChunk(chunk, output);
	}

	if (!output.flush())
	{
		std::cout << "Failed to write to output file\n";
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}
	// выделить функцию которая запаковывает по имени файла
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
		return Pack(input, output) ? 0 : 1;
	case UNPACK:
		return Unpack(input, output) ? 0 : 1;
	default:
		return 1;
	}
}