#include <iostream>
#include <vector>
#include <algorithm>
#include "CircBuf.h"
using namespace std;
int main()
{
	int size;
	cout << "Enter size of ring buffer, please: "  << endl;
	cin >> size;
	CircBuf<int> buffer(size);
	string command;
	cout << "To start enter command 'insert-start' and enter your value";
	while (command != "stop")
	{
		cout << endl << "Enter the command:" << endl;
		cin >> command;
		if (command == "insert-end")
		{
			int x;
			cin >> x;
			buffer.insert_end(x);
			cout << "Total buffer: ";
			for (int i = 0; i < buffer.size(); i++)
				cout << buffer[i] << " ";
		}
		else if (command == "delete-end")
		{
			buffer.delete_end();
			cout << "Total buffer: ";
			for (int i = 0; i < buffer.size(); i++)
				cout << buffer[i] << " ";
		}
		else if (command == "insert-start")
		{
			int x;
			cin >> x;
			buffer.insert_start(x);
			cout << "Total buffer: ";
			for (int i = 0; i < buffer.size(); i++)
				cout << buffer[i] << " ";
		}
		else if (command == "delete-start")
		{
			buffer.delete_start();
			cout << "Total buffer: ";
			for (int i = 0; i < buffer.size(); i++)
				cout << buffer[i] << " ";
		}
		else if (command == "insert-it")
		{
			int index;
			int value;
			cout << "Enter the index and value:" << endl;
			cin >> index >> value;
			buffer.insert_it(buffer.begin() + index, value);
			cout << "Total buffer: ";
			for (int i = 0; i < buffer.size(); i++)
				cout << buffer[i] << " ";
		}
		else if (command == "delete-it")
		{
			int x;
			cout << "Enter value to delete:" << endl;
			cin >> x;
			buffer.delete_it(find(buffer.begin(), buffer.end(), x));
			cout << "Total buffer: ";
			for (int i = 0; i < buffer.size(); i++)
				cout << buffer[i] << " ";
		}
		else if (command == "find-start")
		{
			cout << buffer[0];
		}
		else if (command == "find-end") {
			cout << buffer[size - 1];
		}
		else if (command == "find-id")
		{
			int id;
			cin >> id;
			cout << "Your element whith id=" << id << ": ";
			cout << buffer[id];
		}
		else if (command == "resize")
		{
			int _size;
			cout << "Enter new size:" << endl;
			cin >> _size;
			size = _size;
			buffer.resize(_size);
			cout << "Total buffer: ";
			for (int i = 0; i < buffer.size(); i++)
				cout << buffer[i] << " ";
		}
		else if (command == "print")
		{
			cout << "Total buffer: ";
			for (int i = 0; i < buffer.size(); i++)
				cout << buffer[i] << " ";
		}
		else if (command == "print-it")
		{
			for (auto it = buffer.begin() + 1; it != buffer.end(); it++)
				cout << *it << " ";
		}
		else if (command == "stop") {
			cout <<endl << "Good bye";
			exit(0);
		}
		else
		{
			cout << "Commands: " << endl;
			cout << "1)insert-end, delete-end" << endl;
			cout << "2)insert-start, delete-start" << endl;
			cout << "3)insert-it, delete-it" << endl;
			cout << "4)find-start, find-end " << endl;
			cout << "5)find-id" << endl;
			cout << "6) resize" << endl; 
			cout << "7) print" << endl; 
			cout << "8) print-it" << endl;
			cout << "9) stop" << endl;
			cout << "To start enter command insert-start and enter your value";
		}
	}
}
