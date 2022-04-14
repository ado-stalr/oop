#ifndef PARSEURL_PARSEURLFUNCTIONS_H
#define PARSEURL_PARSEURLFUNCTIONS_H
#endif // PARSEURL_PARSEURLFUNCTIONS_H

#include <string>
#include <regex>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
	WITHOUT_PROTOCOL
};

Protocol GetProtocol(const std::string& str_protocol);
int GetPortFromProtocol(Protocol protocol);
bool ParseUrl(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);
void PrintParsedUrl(int port, const std::string& host, const std::string& document);