#pragma once
#include "Token.h"
#include "TokenStream.h"
#include <vector>
class Calculator
{
public:
	Calculator();
	~Calculator();
public:
	void Execute01();
	void Execute02();
	void Execute03();
	void Execute04();
	void Execute05();
private: 
	bool Calculate5();
	double Expression();
	double Term();
	Token GetToken();
	void PutTokenBack(Token t);
	double Primary();
	double Func();
	bool ProcessExpression();
	void ShowResults(double result, char *str = "==>");
	double Roots(double num, double root);
	double Factorial(double n);
	void Store(Token t);
	void ClearStorage();
	Token PostOpCheck(Token t);
private: 
	TokenStream tokenStream;
	std::vector<Token>Tokens;
};


