#pragma once
#include <iterator>
#define rait random_access_iterator_tag
#define difty difference_type
#define pos _position
template <typename CB>
class CircIter : public std::iterator<std::rait, CB>
{
private:
	CB* _data;
	int pos;
	int _start;
	int _end;
	size_t _cap;
public:
	using difty = typename std::iterator<std::rait, CB>::difty;
	typename CircIter::reference operator*() const
	{
		return _data[pos % _cap];
	}
	CircIter() {}
	CircIter(CB* buf, size_t& N, int& start, int& end, int position);
	difty operator-(const CircIter& it) const;
	difty operator+(const CircIter& it) const;
	CircIter operator+(const int& _pos) const;
	CircIter operator-(const int& _pos) const;
	bool operator!=(CircIter const& additer) const;
	bool operator==(CircIter const& additer) const;
	bool operator>(const CircIter& rai) const;
	bool operator<(const CircIter& rai) const;
	bool operator>=(const CircIter& rai) const;
	bool operator<=(const CircIter& rai) const;
	CircIter operator++();
	CircIter operator++(int);
	CircIter operator--();
	CircIter operator--(int);
};

template <typename CB>
CircIter<CB>::CircIter(CB* buf, size_t& N, int& start, int& end, int position) : 
_data(buf), _cap(N), _start(start), _end(end), pos(position) {}

template <typename CB>
typename CircIter<CB>::difty CircIter<CB>::operator-(const CircIter& it) const
{
	CircIter iter = *this;
	iter.pos -= it.pos;
	return *iter;
}

template <typename CB>
typename CircIter<CB>::difty CircIter<CB>::operator+(const CircIter& it) const
{
	CircIter iter = *this;
	iter.pos += it.pos;
	return *iter;
}

template <typename CB>
typename CircIter<CB> CircIter<CB>::operator+(const int& _pos) const
{
	CircIter iter = *this;
	iter.pos = (pos + _pos) % _cap;
	return iter;
}

template <typename CB>
typename CircIter<CB> CircIter<CB>::operator-(const int& _pos) const
{
	CircIter iter = *this;
	iter.pos = (pos + _cap - _pos) % _cap;
	return iter;
}

template <typename CB>
bool CircIter<CB>::operator!=(CircIter const& additer) const
{
	return this->pos % _cap != additer.pos % _cap;
}

template <typename CB>
bool CircIter<CB>::operator==(CircIter const& additer) const
{
	return this->pos % _cap == additer.pos % _cap;
}

template <typename CB>
bool CircIter<CB>::operator>(const CircIter& rai) const
{
	if (_start > _end)
	{
		if (pos < _cap && rai.pos < _cap)
			return pos > rai.pos;
		else if (pos < _cap)
			return false;
		else if (rai.pos < _cap)
			return true;
		else
			return pos > rai.pos;
	}
	else
		return pos > rai.pos;
}

template <typename CB>
bool CircIter<CB>::operator<(const CircIter& rai) const
{
	if (_start > _end)
	{
		if (pos < _cap && rai.pos < _cap)
			return pos < rai.pos;
		else if (pos < _cap)
			return true;
		else if (rai.pos < _cap)
			return false;
		else
			return pos < rai.pos;
	}
	else
		return pos < rai.pos;
}

template <typename CB>
bool CircIter<CB>::operator>=(const CircIter& rai) const
{
	if (_start > _end)
	{
		if (pos < _cap && rai.pos < _cap)
			return pos >= rai.pos;
		else if (pos < _cap)
			return false;
		else if (rai.pos < _cap)
			return true;
		else
			return pos >= rai.pos;
	}
	else
		return pos >= rai.pos;
}

template <typename CB>
bool CircIter<CB>::operator<=(const CircIter& rai) const
{
	if (_start > _end)
	{
		if (pos < _cap && rai.pos < _cap)
			return pos <= rai.pos;
		else if (pos < _cap)
			return true;
		else if (rai.pos < _cap)
			return false;
		else
			return pos <= rai.pos;
	}
	else
		return pos <= rai.pos;
}

template <typename CB>
typename CircIter<CB> CircIter<CB>::operator++()
{
	this->pos++;
	return *this;
}

template <typename CB>
typename CircIter<CB> CircIter<CB>::operator++(int)
{
	CircIter t(*this);
	operator++();
	return t;
}

template <typename CB>
typename CircIter<CB> CircIter<CB>::operator--()
{
	this->pos--;
	return *this;
}

template <typename CB>
typename CircIter<CB> CircIter<CB>::operator--(int)
{
	CircIter t(*this);
	operator--();
	return t;
}
