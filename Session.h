#pragma once
#include "Commands.h"

class Session
{
private: 
	Commands command;
	String current;
	bool doesEnd = false;
public:
	void session();
	bool isNumber()const;
};

