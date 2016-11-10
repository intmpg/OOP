#pragma once
#include "stdafx.h"
#include <map>
#include <sstream>

#include <stdexcept>
#include <istream>
#include <iosfwd>


class CRational
{
public:
	// ������������ ������������ �����, ������ ���� (0/1)
	CRational();

	// ������������ ������������ �����, ������ value (value/1)
	CRational(int value);

	// ������������ ������������ �����, ������ numerator/denominator
	// ������������ ����� ������ ��������� � ��������������� ����:
	//	����������� ������������� (��������� ����� ���� �������������)
	//	��������� � ����������� �� ����� ����� ��������� (6/8 => 3/4 � �.�.)
	// ���� ����������� ����� ����, ������ ����������������� ������������ �����, ������ ����
	CRational(int numerator, int denominator);

	// ���������� ���������
	int GetNumerator() const;

	// ���������� ����������� (����������� �����)
	int GetDenominator() const;

	// ���������� ��������� ��������� � ����������� � ���� ����� double
	double ToDouble() const;

	// ���������� ������������� ������������� ����� � ���� ��������� �����
	std::pair<int, CRational> ToCompoundFraction()const;

	CRational const operator-() const;
	CRational const operator+() const;

	// task 4 +=
	CRational & operator +=(const CRational & secNumber);
	// task 5 -=
	CRational & operator -=(const CRational & secNumber);

	// task 8 *=
	CRational & operator *=(const CRational & secNumber);
	// task 9 /=
	CRational & operator /=(const CRational & secNumber);

private:
	int m_numerator;
	int m_denominator;

	// ����������� ������������ �����
	void Normalize();


};

unsigned GCD(unsigned a, unsigned b);

// task 2 binary +
CRational const operator +(const CRational & firstNumber, const CRational & secNumber);

// task 3 binary -
CRational const operator -(const CRational & firstNumber, const CRational & secNumber);

// task 6 *
CRational const operator *(const CRational & firstNumber, const CRational & secNumber);

// task 7 /
CRational const operator /(const CRational & firstNumber, const CRational & secNumber);

// task 10 == and !=
bool const operator ==(const CRational & firstNumber, const CRational & secNumber);
bool const operator !=(const CRational & firstNumber, const CRational & secNumber);

// task 11 <, <=, >, >=
bool const operator <(const CRational & firstNumber, const CRational & secNumber);
bool const operator <=(const CRational & firstNumber, const CRational & secNumber);
bool const operator >(const CRational & firstNumber, const CRational & secNumber);
bool const operator >=(const CRational & firstNumber, const CRational & secNumber);

// task 13 ostream
std::ostream & operator <<(std::ostream & strm, const CRational & rational);

// task 14 istream
std::istream & operator >> (std::istream & strm, CRational & rational);