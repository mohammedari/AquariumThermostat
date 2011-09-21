#pragma once

#include "tank_state.hpp"
#include <string>

namespace util
{

//2行、4bitモードのLCDの利用クラス
//ピンに対する操作メソッドをオーバーライドして使う
//reset()を呼んでください…
class lcd
{
	private:
	static const unsigned char _display_length = 16;
	
    public:
    void reset();
	void update(unsigned char line, const string& str);	//lineには0か1を指定
	
	protected:
	virtual void set_register_select(bool bit) = 0;
	virtual void set_read_write(bool bit) = 0;
	virtual void set_enable(bool bit) = 0;
	virtual void set_b4(bool bit) = 0;
	virtual void set_b5(bool bit) = 0;
	virtual void set_b6(bool bit) = 0;
	virtual void set_b7(bool bit) = 0;
    
    private:
	void enable_signal();
	void write(bool register_select, unsigned char data);
	unsigned char read();
    void set_upper_order_bit(unsigned char data);
};
    
}