#include "parseUrlFunctions.h"

#include <iostream>
#include <string>
#include <regex>

const std::string HOST_TEXT = "HOST: ";
const std::string PORT_TEXT = "PORT: ";
const std::string DOC_TEXT = "DOCUMENT: ";

const int MAX_PORT = 65535;

Protocol GetProtocol(const std::string& protocolStr)
{
	if (protocolStr == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocolStr == "https")
	{
		return Protocol::HTTPS;
	}
	else if (protocolStr == "ftp")
	{
		return Protocol::FTP;
	}
	else
	{
		return Protocol::WITHOUT_PROTOCOL;
	}
}

int GetPortFromProtocol(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return 80;
	case Protocol::HTTPS:
		return 443;
	case Protocol::FTP:
		return 21;
	default:
		return 0;
	}
}

bool ParseUrl(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::string lowerUrl;
	lowerUrl.resize(url.length());
	transform(url.begin(), url.end(), lowerUrl.begin(), [](char ch) {return tolower(ch); });
	std::cmatch matchedUrl;
	std::regex regex("(http|https|ftp)://([a-zA-Z0-9._-]+)(:[0-9]+)?(/.+)?");
	if (regex_match(lowerUrl.c_str(), matchedUrl, regex))
	{
		protocol = GetProtocol(matchedUrl[1]);
		host = matchedUrl[2];
		if (matchedUrl[3] == "")
		{
			port = GetPortFromProtocol(protocol);
		}
		else
		{
			std::string portStr = matchedUrl[3];
			portStr.erase(0, 1);
			if (!(stoi(portStr) < 1 || stoi(portStr) > 65535))
			{
				port = stoi(portStr);
			}
			else
			{
				return false;
			}
		}
		if (!(matchedUrl[4] == ""))
		{
			std::string documentStr = matchedUrl[4].str();
			std::copy(documentStr.begin() + 1, documentStr.end(), std::back_inserter(document));
		}
		else
		{
			document = matchedUrl[4];
		}
		return true;
	}
	return false;
}

void PrintParsedUrl(int port, const std::string& host, const std::string& document)
{
	std::cout << HOST_TEXT;
	std::cout << host << std::endl;
	std::cout << PORT_TEXT;
	std::cout << port << std::endl;
	std::cout << DOC_TEXT;
	std::cout << document;
	std::cout << std::endl;
}