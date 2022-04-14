#include <iostream>
#include "Reverse.h"

int main() {

	std::string line;
	while (std::getline(std::cin, line))
	{
		std::cout << Copy(line) << std::endl;
	}
	std::cout << "Copy(line)" << std::endl;

    return 0;
}
