#include "CircBuf.h"
#include <exception>
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

template <typename T>
void CircBuf<T>::insert_end(const T& val)
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

template <typename T>
void CircBuf<T>::insert_start(const T& val)
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

template <typename T>
typename CircIter<T> CircBuf<T>::insert_it(const CircIter<T>& iter, const T& value)
{
	if (!(iter != begin()))
	{
		insert_start(value);
		return begin();
	}
	else if (!(iter != end()))
	{
		insert_end(value);
		return end() - 1;
	}
	else
	{
		T* buf = new T[_cap];
		int Nmax = 0;
		int posT = -1;
		int i = 0;
		for (auto it = begin(); it != end(), i <= _count; it++, i++)
		{
			if (!(it != iter))
			{
				posT = i;
				buf[i] = value;
				Nmax++;
				i++;
			}
			buf[i] = *it;
			Nmax++;
		}
		delete[] _arr;
		_arr = new T[_cap];
		for (int i = 0; i <= Nmax; i++)
			_arr[i] = buf[i];
		_start = 0;
		_end = Nmax;
		_count = Nmax;
		delete[] buf;
		return begin() + posT;
	}
}

template <typename T>
typename CircIter<T> CircBuf<T>::delete_it(const CircIter<T>& iter)
{
	if (!(iter != begin()))
	{
		delete_start();
		return begin();
	}
	else if (!(iter != end() - 1))
	{
		delete_end();
		return end() - 1;
	}
	else
	{
		T* buf = new T[_cap];
		int Nmax = 0;
		int posT = -1;
		int i = 0;
		for (auto it = begin(); it != end(); it+1, i+1)
		{
			if (!(it != iter))
			{
				posT = i;
				it+1;
			}
			buf[i] = *it;
			Nmax = i;
		}
		delete[] _arr;
		_arr = new T[_cap];
		for (int i = 0; i <= Nmax; i++)
			_arr[i] = buf[i];
		_start = 0;
		_end = Nmax + 1;
		_count = Nmax + 1;
		delete[] buf;
		return begin() + posT;
	}
}

template <typename T>
typename CircIter<T> CircBuf<T>::begin()
{
	CircIter<T> iter(_arr, _cap, _start, _end, _start);
	return iter;
}

template <typename T>
typename CircIter<T> CircBuf<T>::end()
{
	CircIter<T> iter(_arr, _cap, _start, _end, _end);
	return iter;
}

template <typename T>
T& CircBuf<T>::operator[](const size_t& i) const
{
	return _arr[(_start + i) % _cap];
}

template <typename T>
void CircBuf<T>::resize(const size_t& N)
{
	T* buf = new T[_cap];
	int Nmax = 0;
	for (int i = 0; i < N; i++)
	{
		if (i == _count)
			break;
		buf[i] = operator[](i);
		Nmax++;
	}
	delete[] _arr;
	_arr = new T[N + 1];
	for (int i = 0; i < Nmax; i++)
		_arr[i] = buf[i];
	_count = Nmax;
	_cap = N + 1;
	_start = 0;
	_end = _count;
	delete[] buf;
}

template <typename T>
size_t CircBuf<T>::size() const
{
	return _count;
}

template<typename It, typename T>
It Go(It first, It last, const T& value)
{
	for (; first != last; first + 1) {
		if (*first == value) {
			return first;
		}
	}
	return last;
}
