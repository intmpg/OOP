#include "stdafx.h"
#include "HttpUrl.h"


void CHttpUrl::ParsingUrl(std::string const & url)
{
	std::string tempUrl(url);
	if (!TakeProtocol(tempUrl))
	{
		throw CUrlParsingError("Invalid Protckol");
	}
	if (!TakeWebSite(tempUrl))
	{
		throw CUrlParsingError("Domain not found");
	}
	if (!CheckDomainOnCorrect())
	{
		throw CUrlParsingError("Invalid domain");
	}
	if (!TakePort(tempUrl))
	{
		throw CUrlParsingError("Invalid port");
	}
	TakeDocument(tempUrl);
}

bool CHttpUrl::TakeProtocol(std::string & url)
{
	if (url.substr(0, 4) == HTTP_PORT)
	{
		m_protocol = HTTP;
		url.erase(0, 4);
		if (url[0] == 's')
		{
			m_protocol = HTTPS;
			url.erase(0, 1);
		}

		if (url.substr(0, 3) == "://")
		{
			url.erase(0, 3);
			return true;
		}
	}
	return false;
}

bool CHttpUrl::TakeWebSite(std::string & url)
{
	std::string tempStr;
	while ((url[0] != '/' && url[0] != ':') && 0 < url.size())
	{
		tempStr += url[0];
		url.erase(0, 1);
	}
	if (tempStr.size() == 0)
	{
		return false;
	}
	m_domain = std::move(tempStr);
	return true;
}

const std::set<char> WrongSymbols = { '\t', ' ', '/', '\\' };

bool CHttpUrl::CheckDomainOnCorrect()
{
	auto check = [](char const& arg) { return WrongSymbols.find(arg) != WrongSymbols.end(); };
	if (std::any_of(m_domain.begin(), m_domain.end(), check))
	{
		return false;
	}
	return true;
}

const std::set<char> Digits = { '0',  '1', '2', '3', '4', '5', '6', '7', '8', '9'};

bool CHttpUrl::TakePort(std::string & url)
{
	if (url[0] == '/')
	{
		SetDefoultPort();
		url.erase(0, 1);
		return true;
	}
	else if (url[0] == ':')
	{
		url.erase(0, 1);
		std::string tempStr;
		while (url[0] != '/' && 0 < url.size())
		{
			tempStr += url[0];
			url.erase(0, 1);
		}

		auto notDigit = [](char const& ch) { return Digits.find(ch) == Digits.end(); };

		if (tempStr.size() > 3 || std::any_of(tempStr.begin(), tempStr.end(), notDigit))
		{
			return false;
		}
		if (tempStr.size() == 0)
		{
			SetDefoultPort();
			return true;
		}
		m_port = std::atoi(tempStr.c_str());
		return true;
	}
	return false;
}

void CHttpUrl::TakeDocument(std::string & url)
{
	std::string doc;
	if (url[0] != '/')
	{
		doc += '/';
	}
	doc += url;
	m_document = doc;
}

void CHttpUrl::SetDefoultPort()
{
	switch (m_protocol)
	{
	case HTTP: m_port = 80; break;
	case HTTPS: m_port = 443; break;
	}
}

CHttpUrl::CHttpUrl(std::string const & url)
{
	ParsingUrl(url);
}

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol, unsigned short port)
	: m_port(port)
	, m_protocol(protocol)
	, m_document(document)
	, m_domain(domain)
{
	if (!CheckDomainOnCorrect())
	{
		throw CUrlParsingError("Invalid domain");
	}
}

std::string CHttpUrl::GetURL() const
{
	std::string url = (m_protocol == HTTP ? "http://" : "https://");
	url += m_domain;
	if (m_protocol == HTTP && m_port != 80)
	{
		url += ":" + std::to_string(m_port);
	}
	else if (m_protocol == HTTPS && m_port != 443)
	{
		url += ":" + std::to_string(m_port);
	}
	url += m_document;
	return url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}
