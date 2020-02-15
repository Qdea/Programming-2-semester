#include <iostream>
#include "Set.h"

using namespace std;

int main() {
	int n;
	int x;
	Set a, b;
	std::cout << "***********" << std::endl;
	std::cout << "***Lab 3***" << std::endl;
	std::cout << "***********" << std::endl;

	cout << "SET A. Input count of elements: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Input element #" << i << ": ";
		cin >> x;
		a += x;
	}
	cout << "SET A: " << a << endl;

	cout << "SET B. Input count of elements: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Input element #" << i << ": ";
		cin >> x;
		b += x;
	}
	cout << "SET B: " << b << endl;

	Set c = a + b;
	cout << "SET C = UNION A + B: " << c << endl;

	cout << "DELETE ELEMENTS FROM C. Input count of delete operations: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Input element #" << i << ": ";
		cin >> x;
		c -= x;
	}
	cout << "SET A: " << a << endl;
	cout << "SET B: " << b << endl;
	cout << "SET C: " << c << endl;

	cout << "SET C == A? " << ((c == a) ? "YES" : "NO") << endl;
	cout << "SET C != B? " << ((c != b) ? "YES" : "NO") << endl;
}
