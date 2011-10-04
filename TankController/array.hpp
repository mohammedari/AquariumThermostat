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
	size_t size() const { return N; }
	
	public:
	operator T*() { return _array; }
	
    public:
	typedef T* iterator;
	
    iterator begin() const { return iterator(_array); }
    iterator end() const { return iterator(_array + N); }
};

}