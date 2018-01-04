#pragma once
#include "Token.h"

class TokenStream
{
public:
	TokenStream();
	~TokenStream();
public:
	Token GetToken();
	bool PutTokenBack(Token t);

private:
	Token buffer;
	bool isFull{ false };
};

