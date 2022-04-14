#include "DecodeHtmlFunctions.h"

int main()
{
	std::string encodedHtml;

	std::cout << "decoding html string:" << std::endl;

	while (getline(std::cin, encodedHtml))
	{
		if (encodedHtml.empty())
		{
			std::cout << "Input string is empty" << std::endl;
		}
		std::string decodedHtml = HtmlDecode(encodedHtml);
		std::cout << decodedHtml << std::endl;
	}

	return 0;
}
