// Calculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Calculator.h"


int main()
{
	CCalculator calc;
	std::string str;
	while (std::cin && !std::cin.fail())
	{
		std::cout << "> ";
		std::getline(std::cin, str);
		calc.RunTheCommand(str);
	}
    return 0;
}

