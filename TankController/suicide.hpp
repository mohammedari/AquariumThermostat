#pragma once

#include <machine.h>
#include "buzzer.hpp"
#include "wait.hpp"

namespace tank_controller
{

void suicide()
{
    buzzer b;
    
    for(int i = 0; i < 3; i++)
    {
        b.on();
        wait(500);
        b.off();
    }
    
    sleep();
}

}