#pragma once
#include <string>
#include <iostream>
#include "Stack.h"

class StackMenu
{
private:
	int _option;
	int _count;
	Stack _stack;
	const char* _actions[100];
public:
	StackMenu();
	~StackMenu();

	int getCount();
	void setOption(int option);
	const char** getActions();
	void doAction();
	void addAction(const char* message);
	bool isRunning();
	void createStack();

	friend std::istream& operator>>(std::istream& stream, StackMenu& x);
	friend std::ostream& operator<<(std::ostream& stream, StackMenu& x);
};
