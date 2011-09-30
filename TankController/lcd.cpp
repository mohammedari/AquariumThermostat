#include "lcd.hpp"
#include <string>
#include "tank_status.hpp"
#include "wait.hpp" 

#include "iodefine.h"
#include "serial_communication.hpp"
#include "format_string.hpp"

namespace util
{

void lcd::reset()
{
	set_register_select(false);
	set_read_write(false);
	set_enable(false);
	
	//LCDの初期化待ち
	wait(15);
	
    //よくわかんないけど3回 0011
	set_register_select(false);
	set_upper_order_bit(0x03);
	enable_signal();
    wait(5);
	set_upper_order_bit(0x03);
	enable_signal();
    wait_usec(100);
	set_upper_order_bit(0x03);
	enable_signal();
    wait_usec(100);
	
    //4bit
	set_upper_order_bit(0x03);
	enable_signal();
    wait_usec(40);
    
	//2ライン、5x7ドット
	write(false, 0x28); //00101000
	wait_usec(40);
	
	//表示ON、カーソルOFF、点滅OFF
	write(false, 0x0C); //00001100
	wait_usec(40);
	
	//ディスプレイクリア
	write(false, 0x01); //00000001
	wait(2);
	
	//エントリーモードセット
	write(false, 0x06); //00000110
    wait_usec(40);
}

void lcd::write_line(unsigned char line, const string& str)
{
	switch(line)
	{
		case 0:
			write(false, 0x80); //10000000
            wait_usec(40);
		break;
		case 1:
			write(false, 0xC0); //11000000
            wait_usec(40);
		break;
		default:
			return;
	}
	
	for(string::const_iterator it = str.begin(); it != str.end(); ++it)
    {
		write(true, *it);
        wait_usec(40);
    }
    
    for(int i = _display_length - str.size(); 0 < i; --i)
    {
        write(true, ' ');
        wait_usec(40);
    }
}

void lcd::enable_signal()
{
	wait_usec(1);
	set_enable(true);
	wait_usec(1);
	set_enable(false);
    wait_usec(1);
}

void lcd::write(bool register_select, unsigned char data)
{
    serial_communication& s = serial_communication::get_instance();
    
	set_register_select(register_select);
	set_read_write(false);
    
    s.write(format_string("%1d%1d", IO.PDR1.BIT.B1, IO.PDR1.BIT.B0));
    
	set_upper_order_bit(data >> 4);        
	enable_signal();
    
    s.write(format_string("%1d%1d%1d%1d", IO.PDR5.BIT.B0, IO.PDR5.BIT.B2, IO.PDR5.BIT.B1, IO.PDR5.BIT.B3));
    
	set_upper_order_bit(0x0F & data);
	enable_signal();
    
    s.write_line(format_string("%1d%1d%1d%1d", IO.PDR5.BIT.B0, IO.PDR5.BIT.B2, IO.PDR5.BIT.B1, IO.PDR5.BIT.B3));
}

void lcd::set_upper_order_bit(unsigned char data)
{
	set_b4(data & 0x01);
	set_b5(data & 0x02);
	set_b6(data & 0x04);
	set_b7(data & 0x08);
}
    
}