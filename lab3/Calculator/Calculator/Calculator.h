#pragma once
#include "Consts.h"

class CCalculator
{
public:
	CCalculator();
	void RunTheCommand(std::string const& commandLine);

	double GetFnValueAtName(std::string const& fnName);
	double GetVarValueAtName(std::string const& fnName);
	bool isNAN(std::string const& varName);

	int GetFnsCount();
	int GetVarsCount();

private:
	// TODO: add enum constants
	const std::map<std::string, unsigned> m_commandsMap = {
		{"Var", 1},
		{"Let", 2},
		{"Fn", 3},
		{"Print", 4},
		{"Printvars", 5},
		{"Printfns", 6},
	};
	std::vector<std::string> ParseCommand(std::string const& commandLine);

	bool isItName(std::string const& varName);
	bool isInitVar(std::string const& varName);
	bool isNumber(std::string const& number);

	void NotifyAnError(unsigned const& errorCode);
	void RemoveFromUndefined(std::string const& varName);
	void SetValue(std::string const& varName, std::string const & valueName);

	double GetValue(std::string const& varName);
	double FromStringToDouble(std::string const& number);
	double GetFnResult(double const& val1, double const& val2, Operators const& sign);

	unsigned RecognizeTheCommand(std::string const & commandName);

	unsigned CheckTheVarSyntax(std::vector<std::string> const& command);
	unsigned Var(std::vector<std::string> const& command); // TODO: rename to DoVarCommand

	unsigned  CheckTheLetSyntax(std::vector<std::string> const& command);
	unsigned Let(std::vector<std::string> const& command); // TODO: rename to DoLetCommand

	unsigned CheckTheFnSyntax(std::vector<std::string> const& command);
	unsigned Fn(std::vector<std::string> const& command);

	unsigned CheckThePrintSyntax(std::vector<std::string> const& command);
	unsigned Print(std::vector<std::string> const& command);

	unsigned PrintVars(std::vector<std::string> const& command);
	unsigned PrintFns(std::vector<std::string> const & command);

	std::map<std::string, double> m_vars;
	std::map<std::string, double> m_fns;

	std::set<std::string> m_undefinedVars;
};

