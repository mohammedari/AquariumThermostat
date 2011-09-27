#include "thermometer.hpp"
#include "temperature.hpp"
#include "adc.hpp"

using namespace util;

namespace tank_controller
{
	
//5/(2^10)[volt/bit]A10mV‚Å1
const double thermometer::_conversion_gain = 5.0 / 0x3FF * 100;
	
temperature thermometer::measure() const
{
	unsigned int ad = _adc.scan();
	
	return temperature(ad * _conversion_gain);
}
	
}