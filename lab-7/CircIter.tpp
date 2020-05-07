#include "CircIter.h"

template <typename T>
CircIter<T>::CircIter(T* buf, size_t& N, int& start, int& end, int position) : 
_data(buf), _cap(N), _start(start), _end(end), pos(position) {}

template <typename T>
typename CircIter<T> CircIter<T>::operator+(const int& _pos) const
{
	CircIter iter = *this;
	iter.pos = (pos + _pos) % _cap;
	return iter;
}

template <typename T>
typename CircIter<T> CircIter<T>::operator-(const int& _pos) const
{
	CircIter iter = *this;
	iter.pos = (pos + _cap - _pos) % _cap;
	return iter;
}

template <typename T>
bool CircIter<T>::operator!=(CircIter const& additer) const
{
	return this->pos % _cap != additer.pos % _cap;
}

template <typename T>
typename CircIter<T> CircIter<T>::operator++(int)
{
	CircIter t(*this);
	this->pos++;
	return t;
}
