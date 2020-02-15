#include <iostream>
#include "Header.h"

void Change(int* a, int* b) {
	if ((*a) > (*b)) {
		(*a) = (*a) % (*b);
	}
	else if ((*a) < (*b)) {
		(*b) = (*b) % (*a);
	}
	else {
		std::cout << "They are equal" << std::endl;
	}
}
void Change(int& a, int& b) {
	if (a > b) {
		a = a % b;
	}
	else if (a < b) {
		b = b % a;
	}
	else {
		std::cout << "They are equal" << std::endl;
	}
}

void Round(double& a) {
	a = int(a + 0.5);
}

void Round(double* a) {
	*a = int(*a + 0.5);
}

void Transp(int(&a)[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 3; j++) {
			int tmp = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = tmp;
		}
	}
}

void Transp(int(*a)[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 3; j++) {
			int tmp = (*a)[i][j];
			(*a)[i][j] = (*a)[j][i];
			(*a)[j][i] = tmp;
		}
	}
}

void Print(int a[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << a[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void RadiusReduction(circle* obj, double* a) {
		obj->r -=*a;
}

void RadiusReduction(circle& obj, double& a) {
		obj.r -= a;
}
