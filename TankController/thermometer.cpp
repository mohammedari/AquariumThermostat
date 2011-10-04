#include "thermometer.hpp"
#include "temperature.hpp"
#include "adc.hpp"

using namespace util;

namespace tank_controller
{
	
//�A���R�[���_���x�v�ōZ���A���`�ߎ�
//y = 0.6124x - 10.465
const double thermometer::_conversion_gain = 0.6124;
const double thermometer::_conversion_offset = -10.465;
	
temperature thermometer::measure() const
{
	unsigned int ad = _adc.scan();
	
	return temperature(ad * _conversion_gain + _conversion_offset);
}
	
}