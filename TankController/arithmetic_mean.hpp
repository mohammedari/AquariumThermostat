#pragma once

#include "stddef.h"
#include "array.hpp"

namespace util
{

//内部にリングバッファを持つ
//pushでデータを追加、averageで加算平均
template<class T, size_t N>
class arithmetic_mean
{
	private:
	size_t _num;
	size_t _index;
	array<T, N> _arr;
	
	public:
	arithmetic_mean() : _num(0), _index(0) { }
	void push(const T& data);
	T average();
};

template<class T, size_t N>
void arithmetic_mean<T, N>::push(const T& data)
{
	if(N < _index)
		_index = 0;
		
	_arr[_index] = data;
	++_index;
	
	if(_num < N)
		++_num;
}

template<class T, size_t N>
T arithmetic_mean<T, N>::average()
{
	T sum;
	for(size_t i = 0; i < N; ++i)
		sum += _arr[i];
	
	return sum / _num;
}
	
}