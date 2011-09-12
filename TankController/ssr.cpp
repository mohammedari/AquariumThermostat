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
    TW.TIOR0.BIT.IOA = 0x00;
    TW.TIOR0.BIT.IOB = 0x00;
    TW.TIOR1.BIT.IOC = 0x00;
    TW.TIOR1.BIT.IOD = 0x00;    //タイマOFF
    IO.PDR8.BYTE = 0x00;
    IO.PCR8      = 0xFF;        //全部出力
}

void ssr::on()
{
    _is_on = true;
    IO.PDR8.BYTE |= _mask;
}

void ssr::off()
{
    _is_on = false;
    IO.PDR8.BYTE &= !_mask;
}
    
}