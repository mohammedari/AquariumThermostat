#include "display.hpp"
#include "lcd.hpp"
#include "tank_status.hpp"

using namespace util;

namespace tank_controller
{
	
bool display::_initialized = false;
	
display::display()
{
	if(_initialized)
		return;
		
	_initialized = true;
	
	//PORT1 0,1,2�v���A�b�v�Ȃ��S�ėp�o��
	IO.PMR1.BIT.TMOW = 0;
	IO.PUCR1.BYTE &= ~(0x07);
	IO.PCR1       |= 0x07;
	IO.PDR1.BYTE  &= ~(0x07);
		
	//PORT5 0,1,2,3�v���A�b�v�Ȃ��S�ėp�o��
    IO.PMR5.BYTE  &= ~(0x0F);
	IO.PUCR5.BYTE &= ~(0x0F);
	IO.PCR5       |= 0x0F;
	IO.PDR5.BYTE  &= ~(0x0F);
	
	//LCD�̏�����
	reset();
}

void display::update(const tank_status& state)
{
}
	
}