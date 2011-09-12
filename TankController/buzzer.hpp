#include "ssr.hpp"

#pragma once

namespace tank_controller
{

class buzzer : public ssr
{
    public:
    buzzer() : ssr(0x80) { }    
};

}