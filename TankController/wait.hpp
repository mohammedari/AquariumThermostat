#pragma once

#include <machine.h>

namespace tank_controller
{
    
const size_t nop_per_milisec = 20e+6 / 1000;

void wait(size_t milisec)
{
    for(size_t i = 0; i < milisec; i++)
        for(size_t j = 0; j < nop_per_milisec; j++)
            nop();
}

}