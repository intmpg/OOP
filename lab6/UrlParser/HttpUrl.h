#pragma once
#include "UrlParsingError.h"

enum Protocol
{
	HTTP,
	HTTPS
};

const std::string HTTP_PORT = "http";

class CHttpUrl
{
public:
	// выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
	// выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
	CHttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
	ѕри недопустимости входных параметров выбрасывает исключение
	std::invalid_argument
	≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = HTTP,
		unsigned short port = 80);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = HTTP);
	// возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
	// выбранного протокола (80 дл€ http и 443 дл€ https) в URL не должен включатьс€
	std::string GetURL()const;

	// возвращает доменное им€
	std::string GetDomain()const;

	/*
	¬озвращает им€ документа. ѕримеры:
	/
	/index.html
	/images/photo.jpg
	*/
	std::string GetDocument()const;

	// возвращает тип протокола
	Protocol GetProtocol()const;

	// возвращает номер порта
	unsigned short GetPort()const;

private:
	void ParsingUrl(std::string const& url);
	bool TakeProtocol(std::string & url);
	bool TakeWebSite(std::string & url);
	bool CheckDomainOnCorrect();
	bool TakePort(std::string & url);
	void TakeDocument(std::string & url);
	void SetDefoultPort();

	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	unsigned short m_port;
};

