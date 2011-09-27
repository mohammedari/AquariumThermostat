#pragma once

#include "temperature.hpp"
#include "adc.hpp"

namespace tank_controller
{

class thermometer
{
	private:
	util::adc _adc;	//AN1
	static const double _conversion_gain;
	
    public:
	thermometer() : _adc(0x01) { }
    temperature measure() const;
};

}