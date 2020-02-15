#include "Set.h"
Set::Set() 
{
	this->_set = 0;
}
Set::~Set() = default;
int Set::set() const
{
	return this->_set;
}
Set& Set::operator+(Set& a) 
{
	Set b;
	b._set = this->_set | a.set();
	return b;
}
Set& Set::operator+=(int& a) 
{
	this->_set |= (1 << a);
	return *this;
}
Set& Set::operator-=(int& a) 
{
	this->_set ^= this->_set & (1 << a);
	return *this;
}
bool Set::operator==(Set& a)
{
	return this->_set == a.set();
}
bool Set::operator!=(Set& a)
{
	return this->_set != a.set();
}
std::ostream& operator<<(std::ostream& stream, const Set& a)
{
	for (int i = 0; i < 10; i++) {
		if (a._set & (1 << i)) {
			stream << i << " ";
		}
	}
	return stream;
}
