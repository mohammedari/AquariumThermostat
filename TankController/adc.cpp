#include "adc.hpp"
#include "iodefine.h"

namespace util
{
	
bool adc::_initialized = false;
	
adc::adc(unsigned char channel) : _channel(channel)
{
	if(_initialized)
		return;
	
	AD.ADCSR.BYTE &= 0x07;	//���荞�݋֎~�A�P�ꃂ�[�h�A134�X�e�[�g�L���v�`��
	AD.ADCR.BIT.TRGE = 0;	//�O���g���K�͎g�p���Ȃ�
		
	_initialized = true;
}

unsigned int adc::scan() const
{
	AD.ADCSR.BIT.CH = _channel;

	AD.ADCSR.BIT.ADST = 1;	//�ϊ��J�n
	
	while(!AD.ADCSR.BIT.ADF);
	AD.ADCSR.BIT.ADF = 0;
	
	switch(_channel)
	{
		case 0x00:
		case 0x04:
			return AD.ADDRA >> 6;	//���ʃr�b�g�Ɋ񂹂�
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