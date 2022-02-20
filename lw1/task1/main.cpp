#include <iostream>
#include <fstream>
#include <string>

void clearFile(const std::string& fileName)
{
	std::fstream clear_file(fileName, std::ios::out);
	clear_file.close();
}


int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: join.exe <input file 1> ... <input file N> <output file>\n";
		return 1;
	}

	std::ofstream output(argv[argc - 1]);
	if (!output.is_open())
	{
		std::cout << "Failed to open " << argv[argc - 1] << " for writing\n";
		return 1;
	}

	for (int i = 1; i < argc - 1; i++)
	{
		std::ifstream input(argv[i]);
		if (!input.is_open())
		{
			std::cout << "Failed to open " << argv[1] << " for reading\n";
			output.close();
			clearFile(std::string(argv[argc - 1]));
			return 1;
		}

		char ch;
		while (input.get(ch))
		{
			if (!output.put(ch))
			{
				std::cout << "Failed to save data on disk\n";
				return 1;
			}
		}
	}

	return 0;
}
