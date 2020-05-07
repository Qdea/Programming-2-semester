#pragma once
#include <iterator>
#define rait random_access_iterator_tag
#define difty difference_type
#define pos _position
template <typename T>
class CircIter : public std::iterator<std::rait, T>
{
private:
	T* _data;
	int pos;
	int _start;
	int _end;
	size_t _cap;
public:
	using difty = typename std::iterator<std::rait, T>::difty;
	typename CircIter::reference operator*() const
	{
		return _data[pos % _cap];
	}
	CircIter() {}
	CircIter(T* buf, size_t& N, int& start, int& end, int position);
	CircIter operator+(const int& _pos) const;
	CircIter operator-(const int& _pos) const;
	bool operator!=(CircIter const& additer) const;
	CircIter operator++(int);
};
#include "CircIter.tpp"
