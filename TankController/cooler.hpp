#include "ssr.hpp"

#pragma once

namespace tank_controller
{

class cooler : public ssr
{
    public:
    cooler() : ssr(0x08) { }        
};

}