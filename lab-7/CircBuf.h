#pragma once
#include <exception>
#include <iterator>
#include <string>
#include "CircIter.h"

template <typename CB>
class CircBuf
{
public:
	CircBuf(size_t N);
	~CircBuf();
	CircIter<CB> begin();
	CircIter<CB> end();
	CircIter<CB> insert_it(const CircIter<CB>& iter, const CB& value);
	CircIter<CB> delete_it(const CircIter<CB>& iter);
	void insert_end(const CB& val);
	void insert_start(const CB& val);
	void delete_end();
	void delete_start();
	void resize(const size_t& N);
	size_t size() const;
	CB& operator[](const size_t& i) const;
	void print();
private:
	size_t _cap;
	size_t _count;
	int _start;
	int _end;
	CB* _arr;
};

template <typename T>
CircBuf<T>::CircBuf(size_t N)
{
	_arr = new T[N + 1];
	_cap = N + 1;
	_start = 0;
	_end = 0;
	_count = 0;
}

template <typename T>
CircBuf<T>::~CircBuf()
{
	delete[] _arr;
}

template <typename CB>
void CircBuf<CB>::insert_end(const CB& val)
{
	if (_start % _cap - _end % _cap == 1)
		_start = (_start + 1) % _cap;
	else
		_count++;
	_arr[_end % _cap] = val;
	_end = (_end + 1) % _cap;
}

template <typename T>
void CircBuf<T>::delete_end()
{
	if (_start % _cap != _end % _cap)
		_end = (_end + _cap - 1) % _cap, _count--;
	else
		throw std::exception("Buffer is empty");
}

template <typename CB>
void CircBuf<CB>::insert_start(const CB& val)
{
	if (_end % _cap - _start % _cap == 1 || (_end == _cap - 1 && _start == 0))
	{
		_end = (_end + _cap - 1) % _cap;
	}
	else
		_count++;
	_start = (_start + _cap - 1) % _cap;
	_arr[_start % _cap] = val;
}


template <typename T>
void CircBuf<T>::delete_start()
{
	if (_start % _cap != _end % _cap)
		_start = (_start + 1) % _cap, _count--;
	else
		throw std::exception("Buffer is empty");
}

template <typename CB>
typename CircIter<CB> CircBuf<CB>::insert_it(const CircIter<CB>& iter, const CB& value)
{
	if (iter == begin())
	{
		insert_start(value);
		return begin();
	}
	else if (iter == end())
	{
		insert_end(value);
		return end() - 1;
	}
	else
	{
		CB* buf = new CB[_cap];
		int Nmax = 0;
		int posCB = -1;
		int i = 0;
		for (auto it = begin(); it != end(), i <= _count; it++, i++)
		{
			if (it == iter)
			{
				posCB = i;
				buf[i] = value;
				Nmax++;
				i++;
			}
			buf[i] = *it;
			Nmax++;
		}
		delete[] _arr;
		_arr = new CB[_cap];
		for (int i = 0; i <= Nmax; i++)
			_arr[i] = buf[i];
		_start = 0;
		_end = Nmax;
		_count = Nmax;
		delete[] buf;
		return begin() + posCB;
	}
}

template <typename CB>
typename CircIter<CB> CircBuf<CB>::delete_it(const CircIter<CB>& iter)
{
	if (iter == begin())
	{
		delete_start();
		return begin();
	}
	else if (iter == end() - 1)
	{
		delete_end();
		return end() - 1;
	}
	else
	{
		CB* buf = new CB[_cap];
		int Nmax = 0;
		int posCB = -1;
		int i = 0;
		for (auto it = begin(); it != end(); it++, i++)
		{
			if (it == iter)
			{
				posCB = i;
				it++;
			}
			buf[i] = *it;
			Nmax = i;
		}
		delete[] _arr;
		_arr = new CB[_cap];
		for (int i = 0; i <= Nmax; i++)
			_arr[i] = buf[i];
		_start = 0;
		_end = Nmax + 1;
		_count = Nmax + 1;
		delete[] buf;
		return begin() + posCB;
	}
}

template <typename CB>
typename CircIter<CB> CircBuf<CB>::begin()
{
	CircIter<CB> iter(_arr, _cap, _start, _end, _start);
	return iter;
}

template <typename CB>
typename CircIter<CB> CircBuf<CB>::end()
{
	CircIter<CB> iter(_arr, _cap, _start, _end, _end);
	return iter;
}

template <typename CB>
CB& CircBuf<CB>::operator[](const size_t& i) const
{
	return _arr[(_start + i) % _cap];
}

template <typename CB>
void CircBuf<CB>::resize(const size_t& N)
{
	CB* buf = new CB[_cap];
	int Nmax = 0;
	for (int i = 0; i < N; i++)
	{
		if (i == _count)
			break;
		buf[i] = operator[](i);
		Nmax++;
	}
	delete[] _arr;
	_arr = new CB[N + 1];
	for (int i = 0; i < Nmax; i++)
		_arr[i] = buf[i];
	_count = Nmax;
	_cap = N + 1;
	_start = 0;
	_end = _count;
	delete[] buf;
}

template <typename CB>
size_t CircBuf<CB>::size() const
{
	return _count;
}
