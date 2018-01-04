#pragma once
class Token
{
public:
	//Token();
	Token(char kind = '7', double value = 0.0) : kind(kind) , value(value){}
	/*Token(char kind, double value = 0.0)
	{
		this->kind = kind;
		this->value = value;
	}*/
	/*{
		this->kind = kind;
	}*/
	~Token();
public:
	char kind;
	double value;
};

