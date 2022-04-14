#include "DecodeHtmlFunctions.h"

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

// Дать подходящее название
void JoinDecodedHtml(std::string& encodedHtml, const std::string& encodedValue)
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
	// Tests
	std::string decodedHtml;
	size_t startPosition;
	bool isBuffering = false;

	// size_t
	for (size_t i = 0; i < html.length(); i++)
	{
		// непонятное название
		if (isBuffering)
		{
			if (html[i] == '&')
			{
				// аппенд метод
				decodedHtml.append(html, startPosition, i - startPosition);
				startPosition = i;
				continue;
			}
			if (html[i] == ';')
			{
				std::string encodedValue(&html[startPosition], i - startPosition + 1);
				JoinDecodedHtml(decodedHtml, encodedValue);
				isBuffering = false;
			}
			continue;
		}
		if (html[i] != '&')
		{
			decodedHtml.push_back(html[i]);
			continue;
		}
		startPosition = i;
		isBuffering = true;
	}

	// Терялись символы
	if(isBuffering)
	{
		decodedHtml.append(html, startPosition, html.length() - startPosition);
	}

	return decodedHtml;
}
