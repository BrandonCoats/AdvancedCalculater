#include "Calculator.h"
#include <iostream>
#include <vector>
#include <assert.h>
#include <math.h>
#include <iomanip>
/*Brandon coats 
Grammar def.......
Term def:
term = expression 
term +primary 
term - primary
...................
Primary def: 
numbers 
or ( and )
absolute number []
...................
Expession 
the actual expression
...................
Func 
The primary 
func ^
func ~

*/
/*
			Operator Precedence & Associativity Table
	Operators on the same row have the same precedence & associativity

Precedence-------Operators-------Binary / Unary-------Associativity-------Names
Lowest	-----------+, - ----------Binary-----------------Left---------Addition,Subtraction

------------------*, /, %	------Binary-----------------Left---------Multiplication, Division, Modulo
-------------------+, -	----------Unary		-------------   ---------Unary plus (does nothing), Unary negation
--------------------^	----------Binary-----------------Right	-------Exponentiation 
--------------------!, L----------Unary------------------    ---------Factorial, Logarithm base 10
Highest-------------(), []--------------------------------------------
Grouping, Absolute Value

*/
Calculator::Calculator()
{
}


Calculator::~Calculator()
{
}

void Calculator::Execute01()
{
	std::cout << "Calculator v1.00V ready.....\n";
	std::cout << "enter an expression (use +, -): \n";
	int lval = 0;
	int rval = 0;
	char op = '?';
	int result = 0;
	std::cin >> lval >> op >> rval;
	if (op == '+')
	{
		result = lval + rval;
	}
	else if (op == '-')
	{
		result = lval - rval;
	}
	std::cout << "Result: " << result << "\n";
	std::cout << "Calculator Done!" <<"\n";
}
void Calculator::Execute02()
{
	std::cout << "Calculator v2.00 ready.....\n";
	std::cout << "enter an expression (use +, -, *, /): \n";
	int lval = 0;
	int rval = 0;
	char op = '?';
	int result = 0;
	std::cin >> lval >> op >> rval;

	switch (op)
	{
	case '+': result = lval + rval;
		break;
	case '-': result = lval - rval;
		break;
	case '*': result = lval * rval;
		break;
	case '/': result = lval / rval;
		break;
	default:
		std::cout << "Error unknown operator";
	}
	std::cout << "Result: " << result << "\n";
	std::cout << "Calculator Done!" << "\n";

}
void Calculator::Execute03()
{
}
void Calculator::Execute04()
{
	Token t{'+'};
	std::cout << t.value << std::endl;
	std::cout << "Calculator v4.00 ready.....\n";
	std::cout << "enter an expression (use +, -, *, /, ^, enter x to quit): \n";
	double lval = 0;
	double rval = 0;
	//bool done = false;
	//while (done == false)
	//{
		
		std::cin >> lval;
		if (!std::cin) {
			std::cout << "Error no first operand\n";
		}
		for (char op; std::cin >> op;)
		{
			
			if (op != '=') std::cin >> rval;
			if (!std::cin) std::cout << "Error no second operand\n";
		
			switch (op)
			{
			case '+': lval += rval;
				break;
			case '-': lval -= rval;
				break;
			case '*': lval *= rval;
				break;
			case '^':lval = pow(lval, rval);
				
				break;
			case '/':
				if (rval == 0)
				{
					std::cout << "Illegal right operand, division by zero, Please try again" << 0 << std::endl;
				}
				else {
					lval /= rval;
				}

				break;
				case '=': 
					std::cout << "Result: " << lval << "\n";
					std::cout << "Calculator Done!" << "\n";
					std::cin >> lval;
					rval = 0;
					break;
				case 'x':
				return;
			default:
				std::cout << "Error unknown operator";

			}
		
		}
	//}
	
//1.order of operations 
//2. power ^ : yes  check
//3./0 fix : yes  :Check
//4.Parentheses
//5.change to double : Yes :Check
//6.continue for anothe operation : yes 
//7.store into a variable 
//8.use x to exit
}

void Calculator::Execute05()
{
	std::cout << "Calculator v6.00 ready.....\n";
	std::cout << "Enter an expression (use +, -, *, /, ^,(),[], %, ~, and L\n  and use = to return an answer when done enter q to quit): \n";
	Calculate5();
	std::cout << "Calculator Done!" << "\n";
}

bool Calculator::Calculate5()
{
	while (ProcessExpression())
	{

	}
	return false;
}
bool Calculator::ProcessExpression()
{
	static double result = 0.0;
	Token t = GetToken();
	switch (t.kind)
	{
	case 'q': 
		if (!Tokens.empty())
		
			ShowResults(result);
		
		return false;
	case '=': 
		ShowResults(result); 
		result = 0.0; 
		ClearStorage();
		break;
		
			
		
	default: PutTokenBack(t);


	}
	if (!Tokens.empty())
	{
		ShowResults(result,"=?>");
	}
	result = Expression();
	return true;
}
void Calculator::ShowResults(double result, char *str)
{
	std::cout << str;
		
	std::cout << std::setw(10) << result << " : ";
		for (unsigned h = 0; h < Tokens.size(); ++h)
		{ 
			if (Tokens.at(h).kind == '7')
			{
				std::cout <<  Tokens.at(h).value;
			}
			else
			{
				std::cout << Tokens.at(h).kind;
			}
		
		} 
	std::cout << "\n";
	//add the answers in the format = (10 space) answer:   calculation
}

double Calculator::Expression()
{
	double left = Term();
	for (;;)
	{
		Token t = GetToken();
		switch (t.kind)
		{
		case '+':Store(t); left += Term();
			
			break;
			
		case '-':Store(t);  left -= Term();
			
			break;

		default: PutTokenBack(t); return left;

		}
	}
	//return 0.0;
}



Token Calculator::GetToken()
{

	return tokenStream.GetToken();
}

void Calculator::PutTokenBack(Token t)
{
	tokenStream.PutTokenBack(t);
}

double Calculator::Primary()
{
	Token t = GetToken();
	switch (t.kind)
	{
	case '7': 
	{
		Store(t);
		Token c = GetToken();// peek character
		double d = 0;
		if (c.kind == '!')
		{
			Store(c);
			d = Factorial(t.value);
		
			return d;
		}
		else if (c.kind == 'L')
		{
			Store(c);
			d = log10(t.value);
			
			return d;
		}
	
			PutTokenBack(c);
		
		
		return t.value;
	}
	case '+':Store(t); return Primary();
	case '-': Store(t); return -Primary();
	case '[':
	{
		Store(t);
		double d = Expression();
		t = GetToken();
		
		if (t.kind != ']')
		{
			std::cout << "ERROR: expected right bracket.";
			assert(false);
			return 0;
		}
		else {
			Store(t);
		}
		if (d < 0)
		{
			d = d*-1;
		}
		return d;
	}
	case '(':
	{
		Store(t);
		double d = Expression();
		t = GetToken();
		
		if (t.kind != ')')
		{
			std::cout << "ERROR: expected right perentheses.";
				assert(false);
				return 0;
		}
		else
		{
			Store(t);
		}
		
			return d;
	}
	default: 
		PutTokenBack(t);
		break;
		
	
	}
	return 0.0;
	//not
}
double Calculator::Term()
{


	double left = Func();
	for (;;)
	{
		Token t = GetToken();
		switch (t.kind)
		{
		case '*':
			Store(t);
			left *= Func();
			
			break;
		case'%':
			Store(t);
			left = (int)left % (int)Func();
			
			break;
			
		case '/':
			Store(t);
			left /= Func(); 
			break;

		default:PutTokenBack(t); return left;

		}
	}
	//return 0.0;
}
double Calculator::Func()
{
	double left = Primary();
	for (;;)
	{
		Token t = GetToken();
		switch (t.kind)
		{
		case '^':
			Store(t);
			left = pow(left, Primary());
			break;
		case'~':
			Store(t);
			left = Roots(left, Primary());
			break;

		default:PutTokenBack(t); return left;

		}
	}
	//return 0.0;
}
double  Calculator::Roots(double num, double root)
{
	double totalRoot;
	totalRoot = pow(num, 1 / root);
	return totalRoot;
	
}

double Calculator::Factorial(double n)
{
	int fullfactorial = (int)n;
	while (n > 0)
	{
		if (n > 1)
		{
			--n;
			fullfactorial *= (int)n;
		}
		else
		{

			fullfactorial *= (int)n;
			--n;
		}
		
		
		
	}
	return fullfactorial;
}

void Calculator::Store(Token t)
{
	Tokens.push_back(t);
}

void Calculator::ClearStorage()
{
	
		Tokens.clear();
}

Token Calculator::PostOpCheck(Token t)
{
	
	return t;
}
	

//X cube root is equal to x *(1/3)
//x ~ y = root 
//x%y = modulus
//X ^ y = power 
//Factorial is in primary
//modulus lives in trem with * and /
//something between term and primary called func  
//can be a  a primary term has to call func change primary to func and call primary in func
/*func order 
primary 
func ^ primary
funct ~ primary*/
//absolute value is brackets 
//absoliute value Lives in the primary
//Method for root and factorial as well as log
//L for log and 
//Log(5) / log (2)
// primary contains log it's represented as L 
// Rename printing to statement
// add new prints for the line and its calculations
//3.9 drop the fraction part for factorials





