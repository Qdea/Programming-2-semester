#pragma once
#ifndef Header_h
#define Header_h

void Change(int&, int&);
void Change(int*, int*);

void Round(double&);
void Round(double*);

void Transp(int(&a)[3][3]);
void Transp(int(*a)[3][3]);

void Print(int a[3][3]);

struct circle {
	double x;
	double y;
	double r;
};
void RadiusReduction(circle*, double const *a);
void RadiusReduction(circle&, double const &a);
#endif Header_h
