#include "stdafx.h"
#include "Rational.h"
#include <map>



CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{}

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (m_denominator == 0)
	{
		throw std::invalid_argument("the denominator is 0. Can not divide by zero");
	}
	if (m_denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return double(m_numerator) / m_denominator;
}


void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}
unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int wholeNumber = m_numerator / m_denominator;
	int numerator = m_numerator - (wholeNumber * m_denominator);

	return std::pair<int, CRational>(wholeNumber, CRational(numerator, m_denominator));
}

// task 1 unary + and -
CRational const CRational::operator -()const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const CRational::operator +()const
{
	return *this;
}

// task 4 +=
CRational & CRational::operator +=(const CRational & secNumber)
{
	*this = (*this + secNumber);
	Normalize();
	return *this;
}

// task 5 -=
CRational & CRational::operator -=(const CRational & secNumber)
{
	*this = (*this - secNumber);
	Normalize();
	return *this;
}

// task 8 *=
CRational & CRational::operator *=(const CRational & secNumber)
{
	*this = (*this * secNumber);
	return *this;
}

// task 9 /=
CRational & CRational::operator /=(const CRational & secNumber)
{
	*this = (*this / secNumber);
	return *this;
}

// task 2 binary +
CRational const operator +(const CRational & firstNumber, const CRational & secNumber)
{
	int numerator = (firstNumber.GetNumerator() * secNumber.GetDenominator())
		+ (secNumber.GetNumerator() * firstNumber.GetDenominator());
	int denominator = firstNumber.GetDenominator() * secNumber.GetDenominator();
	return CRational(numerator, denominator);
}

// task 3 binary -
CRational const operator -(const CRational & firstNumber, const CRational & secNumber)
{
	int numerator = (firstNumber.GetNumerator() * secNumber.GetDenominator())
		- (secNumber.GetNumerator() * firstNumber.GetDenominator());
	int denominator = firstNumber.GetDenominator() * secNumber.GetDenominator();
	return CRational(numerator, denominator);
}

// task 6 *
CRational const operator *(const CRational & firstNumber, const CRational & secNumber)
{
	int numerator = firstNumber.GetNumerator() * secNumber.GetNumerator();
	int denominator = firstNumber.GetDenominator() * secNumber.GetDenominator();
	return CRational(numerator, denominator);
}

// task 7 /
CRational const operator /(const CRational & firstNumber, const CRational & secNumber)
{
	int numerator = firstNumber.GetNumerator() * secNumber.GetDenominator();
	int denominator = firstNumber.GetDenominator() * secNumber.GetNumerator();
	return CRational(numerator, denominator);
}

// task 10 == and !=
bool const operator ==(const CRational & firstNumber, const CRational & secNumber)
{
	return ((firstNumber.GetNumerator() == secNumber.GetNumerator())
		&& (firstNumber.GetDenominator() == secNumber.GetDenominator()));
}

bool const operator !=(const CRational & firstNumber, const CRational & secNumber)
{
	return !(firstNumber == secNumber);
}

// task 11 <, <=, >, >=
bool const operator <(const CRational & firstNumber, const CRational & secNumber)
{
	return ((firstNumber - secNumber).GetNumerator() < (secNumber - firstNumber).GetNumerator());
}

bool const operator <=(const CRational & firstNumber, const CRational & secNumber)
{
	return ((firstNumber < secNumber) || (firstNumber == secNumber));
}

bool const operator >(const CRational & firstNumber, const CRational & secNumber)
{
	return !(firstNumber < secNumber);
}

bool const operator >=(const CRational & firstNumber, const CRational & secNumber)
{
	return ((firstNumber > secNumber) || (firstNumber == secNumber));
}


// task 13 output
std::ostream & operator <<(std::ostream & strm, const CRational & rational)
{
	strm << rational.GetNumerator() << '/' << rational.GetDenominator();
	return strm;
}

// task 14 input
std::istream & operator >> (std::istream & strm, CRational & rational)
{
	std::streamoff startPos = strm.tellg();
	int numerator = 0;
	int denominator = 0;
	if ((strm >> numerator) && (strm.get() == '/') && (strm >> denominator))
	{
		rational = CRational(numerator, denominator);
		return strm;
	}
	strm.seekg(startPos);
	return strm;
}
