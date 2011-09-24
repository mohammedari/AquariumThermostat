#include "lcd.hpp"
#include <string>
#include "tank_state.hpp"
#include "wait.hpp" 

namespace util
{

void lcd::reset()
{
	set_register_select(false);
	set_read_write(false);
	set_enable(false);
	set_upper_order_bit(0x00);
	
	//LCD�̏������҂�
	wait(30);
	
	//��ʁA���ʃr�b�g�̃R�}���h������Ă���\���ɔ�����
	set_register_select(false);
	set_upper_order_bit(0x02);
	enable_signal();
	
	//4bit�A2���C���A5x7�h�b�g
	write(false, 0x20);
	wait_usec(39);
	
	//�\��ON�A�J�[�\��OFF�A�_��OFF
	write(false, 0x0C);
	wait_usec(39);
	
	//�f�B�X�v���C�N���A
	write(false, 0x01);
	wait(2);
	
	//�G���g���[���[�h�Z�b�g
	write(false, 0x06);
}

void lcd::write_line(unsigned char line, const string& str)
{
	switch(line)
	{
		case 0:
			write(false, 0x80);
		break;
		case 1:
			write(false, 0xC0);
		break;
		default:
			return;
	}
	
	string s(str);
	s.resize(_display_length, 'a');
	
	for(string::const_iterator it = s.begin(); it != s.end(); ++it)
		write(true, *it);
}

void lcd::enable_signal()
{
	set_enable(true);
	wait_usec(1);
	set_enable(false);
    wait_usec(1);
}

void lcd::write(bool register_select, unsigned char data)
{
	set_register_select(register_select);
	set_read_write(false);
	set_upper_order_bit(data >> 4);
	enable_signal();
	set_upper_order_bit(0x0F & data);
	enable_signal();
}

void lcd::set_upper_order_bit(unsigned char data)
{
	set_b4(data & 0x01);
	set_b5(data & 0x02);
	set_b6(data & 0x04);
	set_b7(data & 0x08);
}
    
}