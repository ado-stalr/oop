#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

struct Args
{
	std::vector<std::string> inputFileNames;
	std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: join.exe <input file 1> ... <input file N> <output file>\n";
		return std::nullopt;
	}

	Args args;
	for (int i = 1; i < argc - 1; i++)
	{
		args.inputFileNames.push_back(argv[i]);
	}
	args.outputFileName = argv[argc - 1];

	return args;
}

void ClearFile(const std::string& fileName)
{
	std::fstream clear_file(fileName, std::ios::out);
	clear_file.close();
}

void CopyFile(std::istream& input, std::ostream& output) //переименовать
{
	char ch;
	while (input.get(ch))
	{
		if (!output.put(ch))
		{
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	std::ofstream output(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open " << args->outputFileName << " for writing\n";
		return 1;
	}

	//выделить функцию inputs[] output
	for (int i = 0; i < args->inputFileNames.size(); i++)
	{
		std::ifstream input(args->inputFileNames[i]);
		if (!input.is_open())
		{
			std::cout << "Failed to open " << args->inputFileNames[i] << " for reading\n";

			//удадить очистку

			output.close();
			ClearFile(std::string(args->outputFileName));
			return 1;
		}

		CopyFile(input, output);

		if (input.bad())
		{
			std::cout << "Failed to read data from input file\n";
			return 1;
		}

	}

	if (!output.flush())
	{
		std::cout << "Failed to copy text to output file\n";
		return 1;
	}

	return 0;
}
