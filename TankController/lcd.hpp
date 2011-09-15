#pragma once

#include <string>
#include "tank_state.hpp"

namespace tank_controller
{

class lcd
{
    public:
    lcd();
    void update(const tank_state&);
};
    
}