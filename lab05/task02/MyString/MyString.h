#pragma once
#include "stdafx.h"

class CMyString
{
public:
	// ����������� �� ���������
	CMyString();

	// �����������, ���������������� ������ ������� ������
	// � ����������� ������� ��������
	CMyString(const char * pString);

	// �����������, ���������������� ������ ������� �� 
	// ����������� ������� �������� �����
	CMyString(const char * pString, size_t length);

	// ����������� �����������
	CMyString(CMyString const& other);

	// ������������ ����������� (��� ������������, ����������� � C++11)
	//  ����������� ��������� � ������������ ���������� ������������ 
	CMyString(CMyString && other);

	// �����������, ���������������� ������ ������� �� 
	// ������ ����������� ���������� C++
	CMyString(std::string const& stlString);

	// ���������� ������ - ����������� ������, ���������� ��������� ������
	~CMyString();

	// ���������� ����� ������ (��� ����� ������������ �������� �������)
	size_t GetLength()const;

	// ���������� ��������� �� ������ �������� ������.
	// � ����� ������� ����������� ������ ���� ����������� ������� ������
	// ���� ���� ������ ������ 
	const char* GetStringData()const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	CMyString const SubString(size_t start, size_t length = SIZE_MAX)const;

	// ������� ������ (������ ���������� ����� ������� �����)
	void Clear();

	// operators
	CMyString & operator =(const CMyString & str);
	CMyString & operator +=(const CMyString & str);
	const char & operator[](size_t index) const;
private:

	//TODO: CMyString(...) // impl

	size_t m_length = 0;

	//TODO: unique_ptr
	char* m_string;
};

CMyString operator +(CMyString const &str1, CMyString const &str2);
CMyString operator +(std::string const &str1, CMyString const &str2);
CMyString operator +(const char* str1, CMyString const &str2);

bool operator ==(const CMyString &str1, const CMyString &str2);
bool operator !=(const CMyString &str1, const CMyString &str2);
bool operator <(const CMyString &str1, const CMyString &str2);
bool operator >(const CMyString &str1, const CMyString &str2);
bool operator <=(const CMyString &str1, const CMyString &str2);
bool operator >=(const CMyString &str1, const CMyString &str2);

std::ostream & operator <<(std::ostream & strm, CMyString const & string);
std::istream & operator >> (std::istream & strm, CMyString & string);