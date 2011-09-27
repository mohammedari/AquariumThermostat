#include "watch_dog.hpp"
#include "iodefine.h"

namespace util
{
	
watch_dog::watch_dog()
{
	_is_error_occured_in_previous_execution = WDT.TCSRWD.BIT.WRST;
	
	WDT.TMWD.BIT.CKS = _clock_source;
	unsigned char a = WDT.TCSRWD.BYTE & 0xCF;
	unsigned char b = WDT.TCSRWD.BYTE & 0xF3;
	
	WDT.TCSRWD.BYTE = a + 0x10;	//�������݋���
	WDT.TCSRWD.BYTE = b + 0x04;	//WDT�X�^�[�g
	WDT.TCSRWD.BYTE = a;			//�����݋֎~
}

void watch_dog::watch()
{
	unsigned char b = WDT.TCSRWD.BYTE & 0x3F;
	
	WDT.TCSRWD.BYTE = b + 0x40;	//�������݋���
	WDT.TCWD = _write_value;
	WDT.TCSRWD.BYTE = b;			//�������݋֎~
}

}