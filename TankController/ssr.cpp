#include "ssr.hpp"
#include "iodefine.h"

namespace tank_controller
{
    
bool ssr::_initialized = false;

ssr::ssr()
{
    if(_initialized)
        return;
    
    //�|�[�g������
    TW.TIOR0.BIT.IOA = 0x00;
    TW.TIOR0.BIT.IOB = 0x00;
    TW.TIOR1.BIT.IOC = 0x00;
    TW.TIOR1.BIT.IOD = 0x00;    //�^�C�}OFF
    IO.PDR8.BYTE = 0x00;
    IO.PCR8      = 0xFF;        //�S���o��
}

void ssr::on()
{
    _is_on = true;
    IO.PDR8.BYTE |= get_mask();
}

void ssr::off()
{
    _is_on = false;
    IO.PDR8.BYTE &= !get_mask();
}
    
}