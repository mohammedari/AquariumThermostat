#include "adc.hpp"
#include "iodefine.h"

namespace util
{
	
bool adc::_initialized = false;
	
adc::adc(unsigned char channel) : _channel(channel)
{
	if(_initialized)
		return;
	
	AD.ADCSR.BYTE &= 0x07;	//割り込み禁止、単一モード、134ステートキャプチャ
	AD.ADCR.BIT.TRGE = 0;	//外部トリガは使用しない
		
	_initialized = true;
}

unsigned int adc::scan() const
{
	AD.ADCSR.BIT.CH = _channel;

	AD.ADCSR.BIT.ADST = 1;	//変換開始
	
	while(!AD.ADCSR.BIT.ADF);
	AD.ADCSR.BIT.ADF = 0;
	
	switch(_channel)
	{
		case 0x00:
		case 0x04:
			return AD.ADDRA >> 6;	//下位ビットに寄せる
		case 0x01:
		case 0x05:
			return AD.ADDRB >> 6;
		case 0x02:
		case 0x06:
			return AD.ADDRC >> 6;
		case 0x03:
		case 0x07:
			return AD.ADDRD >> 6;
	}
	
	return 0;
}
	
}