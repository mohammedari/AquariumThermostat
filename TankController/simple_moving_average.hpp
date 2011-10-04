#pragma once

#include "stddef.h"
#include "array.hpp"

namespace util
{

//内部にリングバッファを持つ
//pushでデータを追加、averageで移動平均
template<class T, size_t N>
class simple_moving_average
{
	private:
	size_t _num;
	size_t _index;
	array<T, N> _arr;
	
	public:
	simple_moving_average() : _num(0), _index(0) { }
	void push(const T& data);
	T average();
};

template<class T, size_t N>
void simple_moving_average<T, N>::push(const T& data)
{
	if(N < _index)
		_index = 0;
		
	_arr[_index] = data;
	++_index;
	
	if(_num < N)
		++_num;
}

template<class T, size_t N>
T simple_moving_average<T, N>::average()
{
	T sum;
	for(size_t i = 0; i < N; ++i)
		sum += _arr[i];
	
	return sum / _num;
}
	
}