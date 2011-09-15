#pragma once

#include <machine.h>
#include "define.hpp"

namespace util
{
    
const size_t nop_per_milisec = 20e+6 / 10000;   //‚È‚ñ‚©‚í‚©‚ç‚ñ‚¯‚Ç‚±‚ñ‚®‚ç‚¢

inline void wait(size_t milisec)
{
    for(size_t i = 0; i < milisec; ++i)
        for(size_t j = 0; j < nop_per_milisec; ++j)
            nop();
}

}