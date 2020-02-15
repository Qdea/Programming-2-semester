#pragma once
#include <fstream>
class Set
{
private:
	int _set;
public:
	Set();
	int set() const;
	Set& operator+(Set&);
	Set& operator+=(int&);
	Set& operator-=(int&);
	bool operator==(Set&);
	bool operator!=(Set&);
	friend std::ostream& operator<<(std::ostream&, const Set&);
	~Set();
 };
