#include "iodefine.h"
#include "serial_communication.hpp"
#include "wait.hpp"

namespace util
{

bool serial_communication::_initialized = false;
linked_list<serial_communication*> serial_communication::_instances;

serial_communication::serial_communication()
{
    if(_initialized)
        return;
        
    _initialized = true;
    
    //シリアルポート初期化
    SCI3.SCR3.BYTE = 0x00;
    SCI3.SMR.BYTE = 0x00;   //ストップビット1、偶数パリティ
    SCI3.BRR = _baud_rate;
    
    wait(1);
    
    SCI3.SCR3.BIT.TE = 1;
    SCI3.SCR3.BIT.RE = 1;
    
    SCI3.SCR3.BIT.RIE = 1;
}

}