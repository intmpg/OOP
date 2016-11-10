#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

void TranslationFromDecimalToBinary(int dec)
{
	if (dec > 0 )
	{
		dec2bin(dec >> 1);
		cout << (dec &1);
	}
}

int main(int argc, char * argv[])
{
	if (argc == 2)
	{
		int dec = atoi(argv[1]);
		TranslationFromDecimalToBinary(dec);
	}	
	else
	{
		cout <<"you should enter 2 argumånts: bin2dec.exe <the number in the decimal system>";
	}
	return 0;
}

