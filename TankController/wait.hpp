#pragma once

#include <machine.h>
#include "stddef.h"

namespace util
{

//����20MHz, H8 3694�ݒ�
const size_t nop_per_milisec = 20e+6 / 10000;   //�Ȃ񂩂킩��񂯂ǂ��񂮂炢
const size_t nop_per_usec = 20e+6 / 10000000;	//���񂮂炢�H

inline void wait(size_t milisec)
{
    for(size_t i = 0; i < milisec; ++i)
        for(size_t j = 0; j < nop_per_milisec; ++j)
            nop();
}

inline void wait_usec(size_t microsec)
{
	for(size_t i = 0; i < microsec; ++i)
		for(size_t j = 0; j < nop_per_usec; ++j)
			nop();
}

}