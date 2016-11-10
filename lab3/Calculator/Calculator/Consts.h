#pragma once
#include "stdafx.h"

static std::set<std::string> SIGNS = { "-", "+", "*", "/" };

enum class Operators { plus, minus, division, multiply };

static const std::map <std::string, Operators> OPERATORS = 
{
	{"-", Operators::minus},
	{"+", Operators::plus},
	{"*", Operators::multiply},
	{"/", Operators::division}
};

static const std::map <unsigned, std::string> ERRORS = 
{
	{ 1, "The syntax is as follows: Var <id1>" },
	{ 2, "The syntax is as follows: Let <id1> = <id2> or Let <id1> = <double>" },
	{ 3, "The syntax is as follows: Fn <id1> = <id2> or Fn <id1> = <id2> operator <id3> (operators: +,-,*,/)" },
	{ 4, "The syntax is as follows: Print <id>" },
	{ 5, "The syntax is as follows: Printvars" },
	{ 6, "The syntax is as follows: Printfns" },
	{ 7, "This variables Name is already in use" },
	{ 8, "Unknown variable" },
	{ 9, "Name of variable cant began at number"},
	{ 10, "Unknown operator"},
	{11, "Unknown command"}
};

