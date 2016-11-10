#include "stdafx.h"
#include "Calculator.h"

CCalculator::CCalculator()
{
}

std::vector<std::string> CCalculator::ParseCommand(std::string const& commandLine)
{
	std::vector<std::string> commandElements;
	std::istringstream command(commandLine);
	std::string element;
	while (command)
	{
		command >> element;
		commandElements.push_back(element);
	}
	commandElements.pop_back();
	return commandElements;
}

void CCalculator::RunTheCommand(std::string const & commandLine)
{
	auto command = ParseCommand(commandLine);
	switch (RecognizeTheCommand(command[0]))
	{
	case 0: NotifyAnError(11); break;
	case 1: NotifyAnError(Var(command)); break;
	case 2: NotifyAnError(Let(command)); break;
	case 3: NotifyAnError(Fn(command)); break;
	case 4: NotifyAnError(Print(command)); break;
	case 5: NotifyAnError(PrintVars(command)); break;
	case 6: NotifyAnError(PrintFns(command)); break;
	}
}

double CCalculator::GetFnValueAtName(std::string const & fnName)
{
	if (m_fns.find(fnName) != m_fns.end())
	{
		return m_fns.find(fnName)->second;
	}
	return 0.0;
}

double CCalculator::GetVarValueAtName(std::string const & fnName)
{
	if (m_vars.find(fnName) != m_vars.end())
	{
		return m_vars.find(fnName)->second;
	}
	return 0.0;
}

bool CCalculator::isNAN(std::string const & varName)
{
	return m_undefinedVars.find(varName) != m_undefinedVars.end();
}

int CCalculator::GetFnsCount()
{
	return int(m_fns.size());
}

int CCalculator::GetVarsCount()
{
	return int(m_vars.size());
}

bool CCalculator::isItName(std::string const & varName)
{
	return !(varName[0] <= '9' && varName[0] >= '0');
}

void CCalculator::NotifyAnError(unsigned const & errorCode)
{
	if (errorCode != 0)
	{
		std::cout << ERRORS.find(errorCode)->second << std::endl;
	}
}

unsigned CCalculator::RecognizeTheCommand(std::string const & commandName)
{
	if (m_commandsMap.find(commandName) == m_commandsMap.end())
		return 0;
	return m_commandsMap.find(commandName)->second;
}

void CCalculator::RemoveFromUndefined(std::string const & varName)
{
	m_undefinedVars.erase(varName);
}

bool CCalculator::isInitVar(std::string const & varName)
{
	return m_vars.find(varName) != m_vars.end() || m_fns.find(varName) != m_fns.end();
}

bool CCalculator::isNumber(std::string const & number)
{
	// TODO: fix for numbers and cover with test cases:
	//   999999999999999999999999999
	//   99.9
	// don't use any_of
	return std::any_of(number.begin(), number.end(), [](auto &it) {return (it >= '0' && it <= '9'); });
}

void CCalculator::SetValue(std::string const & varName, std::string const & valueName)
{
	if (!isInitVar(varName))
	{
		m_vars.insert({ varName , 0.0 });
	}
	auto var = m_vars.find(varName);

	RemoveFromUndefined(varName);
	if (isNumber(valueName))
	{
		var->second = FromStringToDouble(valueName);
	}
	else
	{
		var->second = GetValue(valueName);
		if (isNAN(valueName))
		{
			m_undefinedVars.insert(varName);
		}
	}
}

double CCalculator::GetValue(std::string const & varName)
{
	// TODO: use std::numeric_limits instead of m_undefinedVars
#if 0
	std::numeric_limits<double>::infinity();
	std::numeric_limits<double>::max();
	std::numeric_limits<double>::quiet_NaN();
#endif

	if (m_vars.find(varName) != m_vars.end())
	{
		return m_vars.find(varName)->second;
	}
	else if (m_fns.find(varName) != m_fns.end())
	{
		return m_fns.find(varName)->second;
	}
	return 0.0;
}

double CCalculator::FromStringToDouble(std::string const & number)
{
	std::istringstream tempS(number);
	double num;
	tempS >> num;
	return num;
}

double CCalculator::GetFnResult(double const & val1, double const & val2, Operators const & sign)
{
	switch (sign)
	{
	case Operators::plus: return val1 + val2; break;
	case Operators::minus: return val1 - val2; break;
	case Operators::division: return val1 / val2; break;
	case Operators::multiply: return val1 * val2; break;
	}
	return 0.0;
}

unsigned CCalculator::CheckTheVarSyntax(std::vector<std::string> const & command)
{
	if (command.size() != 2)
	{
		return 1;
	}
	if (!isItName(command[1]))
	{
		return 9;
	}
	if (isInitVar(command[1]))
	{
		return 7;
	}
	return 0;
}

unsigned CCalculator::Var(std::vector<std::string> const & command)
{
	auto errorCode = CheckTheVarSyntax(command);
	if (errorCode != 0)
		return errorCode;
	m_vars.insert({ command[1], 0 });
	m_undefinedVars.insert(command[1]);
	return 0;
}

unsigned CCalculator::CheckTheLetSyntax(std::vector<std::string> const & command)
{
	if (command.size() != 4)
	{
		return 2;
	}
	if (!isItName(command[1]))
	{
		return 9;
	}
	if (!isItName(command[3]) && !isNumber(command[3]))
	{
		return 9;
	}
	if (!isNumber(command[3]) && !isInitVar(command[3]))
	{
		return 8;
	}
	if (command[2] != "=")
	{
		return 10;
	}
	return 0;
}

unsigned CCalculator::Let(std::vector<std::string> const & command)
{
	auto errorCode = CheckTheLetSyntax(command);
	if (errorCode != 0)
		return errorCode;


	SetValue(command[1], command[3]);
	return 0;

}

unsigned CCalculator::CheckTheFnSyntax(std::vector<std::string> const & command)
{
	if (command.size() == 4 || command.size() == 6)
	{
		if (isInitVar(command[1]))
		{
			return 7;
		}
		if (!isItName(command[1]))
		{
			return 9;
		}
		if (!isItName(command[3]) || !isInitVar(command[3]))
		{
			return 8;
		}
		if (command[2] != "=")
		{
			return 10;
		}
		if (command.size() == 6)
		{
			if (SIGNS.find(command[4]) == SIGNS.end())
			{
				return 10;
			}
			if (!isItName(command[5]) || !isInitVar(command[5]))
			{
				return 8;
			}
		}
		return 0;
	}

	return 3;
}

unsigned CCalculator::Fn(std::vector<std::string> const & command)
{
	auto errorCode = CheckTheFnSyntax(command);
	if (errorCode != 0)
		return errorCode;

	if (command.size() == 4)
	{
		if (isNAN(command[3]))
		{
			m_undefinedVars.insert(command[1]);
			m_fns.insert({ command[1], 0.0 });
		}
		else
		{
			m_fns.insert({ command[1], GetValue(command[3])});
		}
	}
	else
	{
		if (isNAN(command[3]) || isNAN(command[5]))
		{
			m_undefinedVars.insert(command[1]);
			m_fns.insert({ command[1], 0.0 });
		}
		else
		{
			m_fns.insert({ command[1], GetFnResult(GetValue(command[3]),  GetValue(command[5]), OPERATORS.find(command[4])->second) });
		}
	}
	
	return 0;
}

unsigned CCalculator::CheckThePrintSyntax(std::vector<std::string> const & command)
{
	if (!isInitVar(command[1]))
	{
		return 4;
	}
	return 0;
}

unsigned CCalculator::Print(std::vector<std::string> const & command)
{
	auto errorCode = CheckThePrintSyntax(command);
	if (errorCode != 0)
		return errorCode;

	// TODO: use IsNAN
	if (m_undefinedVars.find(command[1]) == m_undefinedVars.end())
	{
		std::cout << command[1] << ": " << GetValue(command[1]) << std::endl;
	}
	else
	{
		std::cout << command[1] << ": NAN" << std::endl;

	}
	return 0;
}

unsigned CCalculator::PrintVars(std::vector<std::string> const & command)
{
	if (command.size() != 1)
	{
		return 5;
	}
	for (auto &it : m_vars)
	{
		if (m_undefinedVars.find(it.first) == m_undefinedVars.end())
		{
			std::cout << it.first << ": " << it.second << std::endl;
		}
		else
		{
			std::cout << it.first << ": NAN" << std::endl;

		}
		
	}
	return 0;
}

unsigned CCalculator::PrintFns(std::vector<std::string> const & command)
{
	if (command.size() != 1)
	{
		return 6;
	}
	for (auto &it : m_fns)
	{
		if (m_undefinedVars.find(it.first) == m_undefinedVars.end())
		{
			std::cout << it.first << ": " << it.second << std::endl;
		}
		else
		{
			std::cout << it.first << ": NAN" << std::endl;

		}

	}
	return 0;
}
