#include "StackMenu.h"
using namespace std;

StackMenu::StackMenu()
{
	this->_option = -1;
	this->_count = 0;
	this->addAction("1. Create stack");
	this->addAction("2. Push element");
	this->addAction("3. Pop element");
	this->addAction("4. Count of elements");
	this->addAction("5. Is stack empty");
	this->addAction("6. Lookup top element");
	this->addAction("7. Display stack");
	this->addAction("0. Exit programm");
}

StackMenu::~StackMenu() = default;

void StackMenu::createStack()
{
	cin >> this->_stack;
	cout << "Stack was created" << endl << endl;
}

void StackMenu::doAction()
{
	try {
		switch (this->_option) {
		case 1: {
			this->createStack();
			break;
		}
		case 2: {
			int x;
			cout << "Push your element: ";
			cin >> x;
			cout << endl << endl;
			this->_stack.push(x);
			break;
		}
		case 3: {
			cout << "Popped element is: " << this->_stack.pop() << endl << endl;
			break;
		}
		case 4: {
			cout << "Count of elements is: " << this->_stack.getCount() << endl << endl;
			break;
		}
		case 5: {
			cout << "Is stack empty? " << (this->_stack.isEmpty() ? "YES" : "NO") << endl << endl;
			break;
		}
		case 6: {
			cout << "Top element is: " << this->_stack.lookup() << endl << endl;
			break;
		}
		case 7: {
			cout << "Stack contains elements: " << this->_stack << endl << endl;
			break;
		}

		}
	}
	catch (const char* err) {
		cout << err << endl << endl;
	}
}

void StackMenu::addAction(const char* message)
{
	this->_actions[this->_count] = message;
	this->_count++;
}

int StackMenu::getCount()
{
	return this->_count;
}

void StackMenu::setOption(int option)
{
	this->_option = option;
}

const char** StackMenu::getActions()
{
	return this->_actions;
}

bool StackMenu::isRunning()
{
	return this->_option != 0;
}

istream& operator>>(istream& stream, StackMenu& x)
{
	int option;

	cout << "Input your action number: ";
	stream >> option;
	cout << endl;
	x.setOption(option);

	return stream;
}

ostream& operator<<(ostream& stream, StackMenu& x)
{
	int n = x.getCount();
	const char** actions = x.getActions();
	for (int i = 0; i < n; i++) {
		stream << actions[i] << endl;
	}
	return stream;
}
