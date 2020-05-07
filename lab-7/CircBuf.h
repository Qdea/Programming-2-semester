#pragma once
#include <exception>
#include <iterator>
#include <string>
#include "CircIter.h"

template <typename T>
class CircBuf
{
public:
	explicit CircBuf(size_t N);
	~CircBuf();
	CircIter<T> begin();
	CircIter<T> end();
	CircIter<T> insert_it(const CircIter<T>& iter, const T& value);
	CircIter<T> delete_it(const CircIter<T>& iter);
	void insert_end(const T& val);
	void insert_start(const T& val);
	void delete_end();
	void delete_start();
	void resize(const size_t& N);
	size_t size() const;
	T& operator[](const size_t& i) const;
private:
	size_t _cap;
	size_t _count;
	int _start;
	int _end;
	T* _arr;
};
#include "CircBuf.tpp"
