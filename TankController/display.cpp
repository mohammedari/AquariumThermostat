#include "display.hpp"
#include "lcd.hpp"
#include "tank_state.hpp"

using namespace util;

namespace tank_controller
{
	
bool display::_initialized = false;
	
display::display()
{
	if(_initialized)
		return;
		
	_initialized = true;
	
	//PORT1 0,1,2プルアップなし全汎用出力
	IO.PMR1.BYTE &= !(0x07);
	IO.PUCR1.BYTE = !(0x07);
	IO.PCR1      |= 0x07;
	IO.PDR1.BYTE &= !(0x07);
		
	//PORT5IIC残してプルアップなし全汎用出力
	IO.PUCR5.BYTE = !(0x0F);
	IO.PCR5      |= 0x0F;
	IO.PDR5.BYTE &= !(0x0F);
	
	//LCDの初期化
	reset();
}

void display::update(const tank_state& state)
{
}
	
}