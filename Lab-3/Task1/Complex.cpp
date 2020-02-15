#include "Complex.h"

Complex::Complex()
{
	this->_im = 0;
	this->_re = 0;
}
Complex& Complex::operator=(const Complex& a)
{
	if (this != &a)
	{
		this->_re = a.re();
		this->_im = a.im();
	}
	return *this;
}
Complex::~Complex() = default;

double Complex::re() const
{
	return this->_re;
}
double Complex::im() const
{
	return this->_im;
}
Complex::operator double() const
{
	return sqrt(pow(this->re(), 2) + pow(this->im(), 2));
}

std::istream& operator>>(std::istream & stream, Complex & a)
{
	stream >> a._re >> a._im;
	return stream;
}
std::ostream& operator<<(std::ostream & stream, const Complex & a)
{
	stream << a.re() << (a.im() >= 0 ? "+" : "") << a.im() << 'i';
	return stream;
}

Complex& Complex::operator*(const double& a)
{
	this->_re *= a;
	this->_im *= a;
	return *this;
}
Complex& Complex::operator+(const Complex & a)
{
	this->_re += a.re();
	this->_im += a.im();
	return *this;
}
Complex& Complex::operator*(const Complex & a)
{
	double re = this->_re * a.re() - this->_im * a.im();
	double im = this->_re * a.im() + this->_im * a.re();
	this->_re = re;
	this->_im = im;
	return *this;
}
