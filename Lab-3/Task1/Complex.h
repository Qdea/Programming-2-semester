#pragma once
#include <fstream>

class Complex
{
private:
	double _re;
	double _im;
public:
	Complex();
	Complex& operator=(const Complex&);
	Complex& operator*(const double&);
	Complex& operator+(const Complex&);
	Complex& operator*(const Complex&);
	operator double() const;
	~Complex();

	friend std::istream& operator>>(std::istream&, Complex&);
	friend std::ostream& operator<<(std::ostream&, const Complex&);
	double re() const;
	double im() const;
};
