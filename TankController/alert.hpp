#pragma once

#include "buzzer.hpp"
#include "wait.hpp"

namespace tank_controller
{
    
inline void alert()
{
    buzzer b;
    
    for(int i = 0; i < 2; ++i)
    {
        b.on();
        util::wait(100);
        b.off();
        util::wait(100);
    }
    
    util::wait(200);
}

}