#include "iodefine.h"
#include "serial_communication.hpp"
#include "wait.hpp"
#include <string>

namespace util
{

bool serial_communication::_initialized = false;
list<serial_communication*> serial_communication::_instances;

serial_communication::serial_communication()
{
    _instances.push_back(this);
    
    if(_initialized)
        return;
        
    _initialized = true;
    
    //シリアルポート初期化
    SCI3.SCR3.BYTE = 0x00;
    SCI3.SMR.BYTE = 0x00;   //ストップビット1、偶数パリティ
    SCI3.BRR = _baud_rate;
    
    wait(1);
    
    IO.PMR1.BIT.TXD = 1;
    SCI3.SCR3.BIT.TE = 1;
    SCI3.SCR3.BIT.RE = 1;
    
    SCI3.SCR3.BIT.RIE = 1;
}

void serial_communication::putc(char c) const
{
    while(!SCI3.SSR.BIT.TDRE)
        ;
    SCI3.TDR = c;
}

void serial_communication::write(const string& str) const
{
    for(string::const_iterator it = str.begin(); it != str.end(); ++it)
        putc(*it);
    
    while(!SCI3.SSR.BIT.TEND)
        ;
}

void serial_communication::write_line(const string& str) const
{
    for(string::const_iterator it = str.begin(); it != str.end(); ++it)
        putc(*it);
        
    putc(new_line);
    
    while(!SCI3.SSR.BIT.TEND)
        ;
}

}