#include <iostream>
#include "Complex.h"

void ComplexMultiplyingByNumber() {
	std::cout << "Action number 1" << std::endl;
	std::cout << "Enter complex number:";
	Complex X;
	std::cin >> X;
	std::cout << "Enter real number:";
	double Y;
	std::cin >> Y;
	std::cout << "Multiply a complex number on real number:" << X.operator*(Y) << std::endl;
}
void ComplexSum() {
	std::cout << std::endl;
	std::cout << "Action number 2" << std::endl;
	std::cout << "Enter complex number:";
	Complex X;
	std::cin >> X;
	std::cout << "Enter complex number:";
	Complex Y;
	std::cin >> Y;
	std::cout << "Sum of two complex numbers:" << X.operator+(Y) << std::endl;
}
void ComplexMultiplication() {
	std::cout << std::endl;
	std::cout << "Action number 3" << std::endl;
	std::cout << "Enter complex number:";
	Complex X;
	std::cin >> X;
	std::cout << "Enter complex number:";
	Complex Y;
	std::cin >> Y;
	std::cout << "Multiply of two complex numbers:" << X.operator*(Y) << std::endl;
}
void ComplexLenght() {
	std::cout << std::endl;
	std::cout << "Action number 4" << std::endl;
	std::cout << "Enter complex number:";
	Complex X;
	std::cin >> X;
	std::cout << "Lengt of complex number:" << (double)X << std::endl;
}

int main() {
	std::cout << "***********" << std::endl;
	std::cout << "***Lab 3***" << std::endl; 
	std::cout << "***********" << std::endl;
	ComplexMultiplyingByNumber();
	ComplexSum();
	ComplexMultiplication();
	ComplexLenght();
}
