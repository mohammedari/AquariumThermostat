#include "ssr.hpp"

#pragma once

namespace tank_controller
{

class cooler : public ssr
{
    unsigned char get_mask() { return 0x08; }        
};

}