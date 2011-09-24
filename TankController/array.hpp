#pragma once
#include "stddef.h"

namespace util
{
	
template<class T, size_t N>
class array
{
	private:
	T _array[N];
	
	public:
	size_t size() { return N; }
	
	public:
	T& operator[](size_t n) { return _array[n]; }
	operator T*() { return _array; }
	
    public:
	typedef T* iterator;
	
    iterator begin() { return iterator(_array); }
    iterator end() { return iterator(_array + N); }
};

}