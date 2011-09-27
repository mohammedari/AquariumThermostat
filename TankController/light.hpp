#include "ssr.hpp"

#pragma once

namespace tank_controller
{

class light : public ssr
{
	public:
    light() : ssr(0x04) { } 
};

}