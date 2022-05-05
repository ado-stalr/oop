#include <iostream>
#include <string>
#include "parseUrlFunctions.h"

const std::string EXIT_TEXT = "exit";
const std::string WELCOME_TEXT = "Please enter URL. Enter \"" + EXIT_TEXT + "\" to stop the parsing process.\n";
const std::string ERROR_URL_TEXT = "This URL doesn\'t correct\n";

int main()
{
	std::cout << WELCOME_TEXT << std::endl;
	std::string url;
	while (getline(std::cin, url) && url != EXIT_TEXT)
	{
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		if (ParseUrl(url, protocol, port, host, document))
		{
			PrintParsedUrl(port, host, document);
		}
		else
		{
			std::cout << ERROR_URL_TEXT << std::endl;
		}
	}
	return 0;
}