#ifndef DECODEHTML_DECODEHTMLFUNCTIONS_H
#define DECODEHTML_DECODEHTMLFUNCTIONS_H
#endif // DECODEHTML_DECODEHTMLFUNCTIONS_H

#include <iostream>
#include <string>
#include <optional>

struct HTMLElement
{
	char decodeValue;
	std::string encodedValue;
};

std::optional<char> GetDecodedHtmlElement(const std::string& encodedValue);
void JoinDecodedHtml(std::string& encodedHtml, const std::string& encodedValue);
std::string HtmlDecode(std::string& html);
