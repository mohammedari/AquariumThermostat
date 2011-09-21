#include "ssr.hpp"
#include "iodefine.h"

namespace tank_controller
{
    
bool ssr::_initialized = false;

ssr::ssr(unsigned char mask)
{
    _mask = mask;
    
    if(_initialized)
        return;
        
    _initialized = true;
    
    //ポート初期化
    TW.TIOR0.BIT.IOB = 0x00;
    TW.TIOR1.BIT.IOC = 0x00;
    TW.TIOR1.BIT.IOD = 0x00;    //タイマOFF
    IO.PCR8      |= 0x4E;       
    IO.PDR8.BYTE &= !(0x4E);	//2,3,4,7出力
}

void ssr::on() const
{
    IO.PDR8.BYTE |= _mask;
}

void ssr::off() const
{
    IO.PDR8.BYTE &= !_mask;
}

bool ssr::is_on() const
{
	return 0 != (IO.PDR8.BYTE & _mask);
}

bool ssr::is_off() const
{
	return 0 == (IO.PDR8.BYTE & _mask);
}
    
}