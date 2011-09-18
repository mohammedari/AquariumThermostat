#pragma once

#include <machine.h>
#include "buzzer.hpp"
#include "wait.hpp"

namespace tank_controller
{

inline void suicide()
{
    buzzer b;
    
    for(int i = 0; i < 3; ++i)
    {
        b.on();
        util::wait(500);
        b.off();
        util::wait(500);
    }
    
    sleep();
}

}