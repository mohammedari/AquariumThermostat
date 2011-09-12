#include "ssr.hpp"

#pragma once

namespace tank_controller
{

class heater : public ssr
{
    public:
    heater() : ssr(0x10) { }
};

}