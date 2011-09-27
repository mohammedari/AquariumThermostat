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
	
	WDT.TCSRWD.BYTE = a + 0x10;	//書き込み許可
	WDT.TCSRWD.BYTE = b + 0x04;	//WDTスタート
	WDT.TCSRWD.BYTE = a;			//書込み禁止
}

void watch_dog::watch()
{
	unsigned char b = WDT.TCSRWD.BYTE & 0x3F;
	
	WDT.TCSRWD.BYTE = b + 0x40;	//書きこみ許可
	WDT.TCWD = _write_value;
	WDT.TCSRWD.BYTE = b;			//書き込み禁止
}

}