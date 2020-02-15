#include <iostream>
#include "Header.h"

void Changes() {
	int x;
	int y;
	std::cout << "---Task1---" << std::endl;
	std::cout << "Input two vars:" << std::endl;
	std::cin >> x;
	std::cin >> y;
	Change(x, y);
	std::cout << "Fist change: " << x << std::endl;
	std::cout << "Fist change: " << y << "\n" << std::endl;
	if (((x > y)& (y != 0)) || ((x < y) & (x != 0))) {
		Change(&x, &y);
		std::cout << "Second change: " << x << std::endl;
		std::cout << "Second change: " << y << "\n" << std::endl;
	}
	else {
		std::cout << "Error. Second change is impossible" << "\n";
		std::cout << "\n";
	}
}
void RoundReal() {
	double x;
	std::cout << "---Task2_1---" << std::endl;
	std::cout << "Input real: " << std::endl;
	std::cin >> x;
	Round(x);
	std::cout << "Fist round: " << x << "\n" << std::endl;

	std::cout << "---Task2_2---" << std::endl;
	std::cout << "Input real: " << std::endl;
	std::cin >> x;
	Round(&x);
	std::cout << "Second round: " << x << "\n" << std::endl;
}
void Transparation() {
	int matrix[3][3];
	std::cout << "---Task4_1---" << std::endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix[i][j] = 2 * i + j * 3;
		}
	}
	std::cout << "Normal: " << std::endl;
	Print(matrix);
	Transp(matrix);
	std::cout << "Transpared: " << std::endl;
	Print(matrix);
	std::cout << "\n";

	std::cout << "---Task4_2---" << std::endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix[i][j] = 3 * i + j * 2;
		}
	}
	std::cout << "Normal: " << std::endl;
	Print(matrix);
	Transp(&matrix);
	std::cout << "Transpared: " << std::endl;
	Print(matrix);
}
void RadiusReduction() {
	double a;
	circle obj;
	std::cout << "---Task3_1---" << std::endl;
	std::cout << "Input parametrs of circle: " << std::endl;
	std::cin >> obj.x >> obj.y >> obj.r;
	std::cout << "Decrease radius by: " << std::endl;
	std::cin >> a;
	if (obj.r > a) {
	RadiusReduction(obj, a);
		std::cout << "Coordinates of center: "<<"("<< obj.x <<","<< obj.y <<")"<< std::endl;
		std::cout << "Result radius = " << obj.r << std::endl;
	}
	else { 
		std::cout << "Error. Wrong reductor of radius. Reductor must be less then radius or equivalent to it." << std::endl;
		std::cout << std::endl;
	}

	std::cout << "---Task3_2---" << std::endl;
	std::cout << "Input parametrs of circle: " << std::endl;
	std::cin >> obj.x >> obj.y >> obj.r;
	std::cout << "Decrease radius by: " << std::endl;
	std::cin >> a;
	if (obj.r > a) {
		RadiusReduction(&obj, &a);
		std::cout << "Coordinates of center: " << "(" << obj.x << "," << obj.y << ")" << std::endl;
		std::cout << "Result radius = " << obj.r << std::endl;
	}
	else {
		std::cout << "Error. Wrong reductor of radius. Reductor must be less then radius or equivalent to it." << std::endl;
		std::cout<<std::endl;
	}
}
int main(int argc, const char* argv[]) {
	Changes();
	RoundReal();
	RadiusReduction();
	Transparation();
	return 0;
}
