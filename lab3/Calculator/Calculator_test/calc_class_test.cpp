#include "stdafx.h"
#include "../Calculator/Calculator.h"

using namespace std;

struct calc
{
	CCalculator myCalc;

};

BOOST_FIXTURE_TEST_SUITE(calculator_testing, calc);

	BOOST_AUTO_TEST_CASE(calculator_must_be_empty)
	{
		BOOST_CHECK_EQUAL(myCalc.GetFnsCount(), 0);
		BOOST_CHECK_EQUAL(myCalc.GetVarsCount(), 0);
	}

	BOOST_AUTO_TEST_CASE(calculator_can_add_var)
	{
		myCalc.RunTheCommand("Var u");
		BOOST_CHECK(myCalc.isNAN("u"));
		BOOST_CHECK_EQUAL(myCalc.GetVarsCount(), 1);
	}
	BOOST_AUTO_TEST_CASE(calculator_can_add_var_with_value)
	{
		myCalc.RunTheCommand("Let u = 9.0");
		BOOST_CHECK(!myCalc.isNAN("u"));
		BOOST_CHECK_EQUAL(myCalc.GetVarsCount(), 1);
		BOOST_CHECK_EQUAL(myCalc.GetVarValueAtName("u"), 9);
	}
	BOOST_AUTO_TEST_CASE(calculator_can_add_fn_with_value)
	{
		myCalc.RunTheCommand("Let b = 3.0");
		myCalc.RunTheCommand("Fn u = b");
		BOOST_CHECK(!myCalc.isNAN("u"));
		BOOST_CHECK_EQUAL(myCalc.GetFnsCount(), 1);
		BOOST_CHECK_EQUAL(myCalc.GetFnValueAtName("u"),3);
	}

	struct CalcWithVars : calc
	{
		CalcWithVars()
		{
			myCalc.RunTheCommand("Var a");
			myCalc.RunTheCommand("Let b = 3.0");
			myCalc.RunTheCommand("Let c = 2.0");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(testing_calcs_functions, CalcWithVars);

		BOOST_AUTO_TEST_CASE(calculator_can_sum_two_vars)
		{
			myCalc.RunTheCommand("Fn u = b + c");
			BOOST_CHECK(!myCalc.isNAN("u"));
			BOOST_CHECK_EQUAL(myCalc.GetFnsCount(), 1);
			BOOST_CHECK_EQUAL(myCalc.GetFnValueAtName("u"), 5);
		}

		BOOST_AUTO_TEST_CASE(calculator_can_work_with_NAN_var)
		{
			myCalc.RunTheCommand("Fn u = a + b");
			BOOST_CHECK(myCalc.isNAN("u"));
			BOOST_CHECK_EQUAL(myCalc.GetFnsCount(), 1);
			BOOST_CHECK_EQUAL(myCalc.GetVarsCount(), 3);
			BOOST_CHECK_EQUAL(myCalc.GetFnValueAtName("u"), 0);
		}

		BOOST_AUTO_TEST_CASE(calculator_can_multiply_two_vars)
		{
			myCalc.RunTheCommand("Fn u = b * c");
			BOOST_CHECK(!myCalc.isNAN("u"));
			BOOST_CHECK_EQUAL(myCalc.GetFnsCount(), 1);
			BOOST_CHECK_EQUAL(myCalc.GetFnValueAtName("u"), 6);
		}

		BOOST_AUTO_TEST_CASE(calculator_can_sub_two_vars)
		{
			myCalc.RunTheCommand("Fn u = b - c");
			BOOST_CHECK(!myCalc.isNAN("u"));
			BOOST_CHECK_EQUAL(myCalc.GetFnsCount(), 1);
			BOOST_CHECK_EQUAL(myCalc.GetFnValueAtName("u"), 1);
		}

		BOOST_AUTO_TEST_CASE(calculator_can_div_two_vars)
		{
			myCalc.RunTheCommand("Fn u = c / c");
			BOOST_CHECK(!myCalc.isNAN("u"));
			BOOST_CHECK_EQUAL(myCalc.GetFnsCount(), 1);
			BOOST_CHECK_EQUAL(myCalc.GetFnValueAtName("u"), 1);
		}

	BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();