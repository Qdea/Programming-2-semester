#include "Stack.h"
#include <iostream>
#include <cstdlib>

using namespace std;
const int DEFAULT_DEPTH = 1000;

Stack::Stack()
{
	this->_count = 0;
	this->_depth = DEFAULT_DEPTH;
	this->_data = (int*)malloc(sizeof(int) * this->_depth);
}
Stack::Stack(const Stack& x)
{
	this->_count = 0;
	this->_depth = x.getDepth();
	if (this->_data = (int*)malloc(sizeof(int) * this->_depth)) {
		memcpy(this->_data, x.getData(), sizeof(int) * this->_depth);
	}
}
Stack::Stack(int depth)
{
	this->_count = 0;
	this->_depth = depth;
	this->_data = (int*)malloc(sizeof(int) * this->_depth);
}
Stack& Stack::operator=(const Stack& x)
{
	if (this->_data) {
		free(this->_data);
	}
	this->_count = 0;
	this->_depth = x.getDepth();
	if (this->_data = (int*)malloc(sizeof(int) * this->_depth)) {
		memcpy(this->_data, x.getData(), sizeof(int) * this->_depth);
	}
	
	return *this;
}
Stack::~Stack()
{
	free(this->_data);
}
int Stack::getDepth() const
{
	return this->_depth;
}
int* Stack::getData() const
{
	return this->_data;
}
int Stack::getCount() const
{
	return this->_count;
}
void Stack::push(int x)
{
	if (this->_count == this->_depth) {
		throw "Stack is full. Push is impossible!";
	}
	this->_data[this->_count] = x;
	this->_count++;
}
int Stack::pop()
{
	if (this->isEmpty()) {
		throw "Stack is empty. Pop is impossible!";
	}
	this->_count--;
	return this->_data[this->_count];
}
int Stack::lookup() const
{
	if (this->isEmpty()) {
		throw "Stack is empty. Lookup is impossible!";
	}
	return this->_data[this->_count - 1];
}
bool Stack::isEmpty() const
{
	return this->_count == 0;
}
istream& operator>>(istream& stream, Stack& x)
{
	int depth;

	cout << "Input depth of stack: ";
	stream >> depth;
	cout << endl;
	x = Stack(depth);

	return stream;
}

ostream& operator<<(ostream& stream, const Stack& x)
{
	int* data = x.getData();
	int n = x.getCount();
	for (int i = 0; i < n; i++) {
		if (i > 0) stream << " ";
		stream << data[i];
	}
	stream << endl;

	return stream;
}
