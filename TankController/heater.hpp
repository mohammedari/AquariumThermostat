#include "ssr.hpp"

#pragma once

namespace tank_controller
{

class heater : public ssr
{
    unsigned char get_mask() { return 0x10; }
};

}