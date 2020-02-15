#include <iostream>
#include "StackMenu.h"
using namespace std;
int main() {
	cout << "***********" << endl; 
	cout << "*  LAB 2  *" << endl;
	cout << "***********" << endl;

	StackMenu menu;
	while (menu.isRunning()) {
		cout << menu;
		cin >> menu;
		menu.doAction();
	}
}
