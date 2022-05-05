#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../parseUrlFunctions.h"

SCENARIO("ParseUrl: empty url")
{
	std::string url = "";
	std::string host, document;
	Protocol protocol;

	int port;
	bool result = ParseUrl(url, protocol, port, host, document);
	REQUIRE(result == false);
}

SCENARIO("ParseUrl: incorrect protocol")
{
	std::string url = "httpss://www.google.com/docs/document1.html?page=30&lang=en#title";
	std::string host, document;
	Protocol protocol;
	int port;

	bool result = ParseUrl(url, protocol, port, host, document);
	REQUIRE(result == false);
}

SCENARIO("ParseUrl: without port - get port from protocol: http")
{
	std::string url = "http://www.google.com/docs/document1.html?page=30&lang=en#title";
	std::string host, document;
	Protocol protocol;
	int port;

	bool result = ParseUrl(url, protocol, port, host, document);
	REQUIRE((result && host == "www.google.com" && port == 80 && document == "docs/document1.html?page=30&lang=en#title" && protocol == Protocol::HTTP));
}

SCENARIO("ParseUrl: without port - get port from protocol: ftp")
{
	std::string url = "ftp://www.creado.info/docs/document1.html?page=30&lang=en#title";
	std::string host, document;
	Protocol protocol;
	int port;

	bool result = ParseUrl(url, protocol, port, host, document);
	REQUIRE((result && host == "www.creado.info" && port == 21 && document == "docs/document1.html?page=30&lang=en#title" && protocol == Protocol::FTP));
}

SCENARIO("ParseUrl: without port - get port from protocol: https")
{
	std::string url = "https://www.google.com/docs/document1.html?page=30&lang=en#title";
	std::string host, document;
	Protocol protocol;
	int port;

	bool result = ParseUrl(url, protocol, port, host, document);
	REQUIRE((result && host == "www.google.com" && port == 443 && document == "docs/document1.html?page=30&lang=en#title" && protocol == Protocol::HTTPS));
}

SCENARIO("ParseUrl: with port")
{
	std::string url = "http://www.ya.com:59/docs/document1.html?page=30&lang=en#title";
	std::string host, document;
	Protocol protocol;
	int port;

	bool result = ParseUrl(url, protocol, port, host, document);
	REQUIRE((result && host == "www.ya.com" && port == 59 && document == "docs/document1.html?page=30&lang=en#title" && protocol == Protocol::HTTP));
}


// в тестах надо проверять оба значения вблизи границ
// добавить тесты с разным регистром схемы
SCENARIO("ParseUrl: port is more limitation")
{
	std::string url = "http://www.ya.com:65536/docs/document1.html?page=30&lang=en#title";
	std::string host, document;
	Protocol protocol;
	int port;

	bool result = ParseUrl(url, protocol, port, host, document);
	REQUIRE(result == false);
}

SCENARIO("ParseUrl: without document")
{
	std::string url = "http://ya.ru";
	std::string host, document;
	Protocol protocol;
	int port;

	bool result = ParseUrl(url, protocol, port, host, document);
	REQUIRE((result && host == "ya.ru" && port == 80 && document.empty() && protocol == Protocol::HTTP));
}

SCENARIO("ParseUrl: localhost with post 3000")
{
	std::string url = "http://localhost:3000/index.html";
	std::string host, document;
	Protocol protocol;
	int port;

	bool result = ParseUrl(url, protocol, port, host, document);
	REQUIRE((result && host == "localhost" && port == 3000 && document == "index.html" && protocol == Protocol::HTTP));
}

SCENARIO("ParseUrl: host with document")
{
	std::string url = "http://host/:12345abc";
	std::string host, document;
	Protocol protocol;
	int port;

	bool result = ParseUrl(url, protocol, port, host, document);
	REQUIRE((result && host == "host" && port == 80 && document == ":12345abc" && protocol == Protocol::HTTP));
}
