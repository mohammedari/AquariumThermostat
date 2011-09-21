#pragma once

#include <machine.h>
#include "stddef.h"

namespace util
{

//êÖèª20MHz, H8 3694ê›íË
const size_t nop_per_milisec = 20e+6 / 10000;   //Ç»ÇÒÇ©ÇÌÇ©ÇÁÇÒÇØÇ«Ç±ÇÒÇÆÇÁÇ¢
const size_t nop_per_usec = 20e+6 / 10000000;	//Ç±ÇÒÇÆÇÁÇ¢ÅH

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