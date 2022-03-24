#include <iostream>
#include <optional>
#include <string>

struct HTMLElement
{
	char decodeValue;
	std::string encodedValue;
};

std::optional<char> GetDecodedHtmlElement(const std::string& encodedValue)
{
	HTMLElement htmlElements[5] = {
		{ '"', "&quot;" },
		{ '\'', "&apos;" },
		{ '<', "&lt;" },
		{ '>', "&gt;" },
		{ '&', "&amp;" },
	};

	for (HTMLElement& item : htmlElements)
	{
		if (item.encodedValue == encodedValue)
		{
			return item.decodeValue;
		}
	}
	return std::nullopt;
}

void ReplaceHtmlElement(std::string& encodedHtml, const std::string& encodedValue)
{
	std::optional<char> htmlElement = GetDecodedHtmlElement(encodedValue);
	if (htmlElement)
	{
		encodedHtml += *htmlElement;
	}
	else
	{
		encodedHtml += encodedValue;
	}
}

std::string HtmlDecode(std::string& html)
{
	std::string decodedHtml;
	int startPosition;
	bool copyToBuffer = false;

	for (int i = 0; i < html.size(); i++)
	{
		if (copyToBuffer)
		{
			if (html[i] == '&')
			{
				decodedHtml += html.substr(startPosition, i - startPosition);
				startPosition = i;
				continue;
			}
			if (html[i] == ';')
			{
				std::string encodedValue(&html[startPosition], i - startPosition + 1);
				ReplaceHtmlElement(decodedHtml, encodedValue);
				copyToBuffer = false;
			}
			continue;
		}
		if (html[i] != '&')
		{
			decodedHtml.push_back(html[i]);
			continue;
		}
		startPosition = i;
		copyToBuffer = true;
	}

	return decodedHtml;
}

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
