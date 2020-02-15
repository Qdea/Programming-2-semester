#pragma once
#include <iostream>

class Stack 
{
private:
	int _depth;
	int _count;
	int* _data;
public:
	Stack();
	Stack(const Stack&);
	explicit Stack(int depth);
	Stack& operator=(const Stack&);
	friend std::istream& operator>>(std::istream&, Stack&);
	friend std::ostream& operator<<(std::ostream& stream, const Stack& x);
	~Stack();
	
	int getDepth() const;
	int* getData() const;
	int getCount() const;
	void push(int x);
	int pop();
	int lookup() const;
	bool isEmpty() const;
};
