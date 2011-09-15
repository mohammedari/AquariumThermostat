#pragma once

#include <machine.h>
#include "buzzer.hpp"
#include "wait.hpp"

using namespace util;
    
namespace tank_controller
{

inline void suicide()
{
    buzzer b;
    
    for(int i = 0; i < 3; ++i)
    {
        b.on();
        wait(500);
        b.off();
        wait(500);
    }
    
    sleep();
}

}