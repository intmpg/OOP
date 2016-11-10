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
	// ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
	// ���������� ���������� CUrlParsingError, ���������� ��������� �������� ������
	CHttpUrl(std::string const& url);

	/* �������������� URL �� ������ ���������� ����������.
	��� �������������� ������� ���������� ����������� ����������
	std::invalid_argument
	���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
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
	// ���������� ��������� ������������� URL-�. ����, ���������� ����������� ���
	// ���������� ��������� (80 ��� http � 443 ��� https) � URL �� ������ ����������
	std::string GetURL()const;

	// ���������� �������� ���
	std::string GetDomain()const;

	/*
	���������� ��� ���������. �������:
	/
	/index.html
	/images/photo.jpg
	*/
	std::string GetDocument()const;

	// ���������� ��� ���������
	Protocol GetProtocol()const;

	// ���������� ����� �����
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

