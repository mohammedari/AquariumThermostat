#include "i2c.hpp"
#include "array.hpp"
#include "stddef.h"
#include "iodefine.h"

namespace util
{

i2c* i2c::_instance = NULL;

i2c& i2c::get_instance()
{
    if(NULL == _instance)
        _instance = new i2c();
        
    return *_instance;
}

void i2c::delete_instance()
{
    if(NULL != _instance)
        delete _instance;
        
    _instance = NULL;
}
    
i2c::i2c()
{
    IIC2.ICCR1.BIT.ICE = 1;
    IIC2.ICCR1.BIT.CKS = 0x0D;  //1101 100kHz
    IIC2.ICMR.BIT.MLS = 0;      //MSBファースト
    IIC2.ICMR.BIT.WAIT = 1;     //送信時ウェイト挿入
    IIC2.ICIER.BYTE = 0x00;     //割り込み禁止、ACK無視、送信ACK=0
    IIC2.SAR.BIT.FS = 0;        //I2Cフォーマット
}

bool i2c::start(unsigned char control) const
{
    IIC2.ICCR1.BIT.MST = 1; //マスタ
    IIC2.ICCR1.BIT.TRS = 1; //送信
    
    send_start_bit();
    
    while(!IIC2.ICSR.BIT.TDRE);
    
    IIC2.ICDRT = control;
    
    while(!IIC2.ICSR.BIT.TEND);
    
    if(IIC2.ICIER.BIT.ACKBR)
    {
        stop();
        return false;
    }
    
    return true;
}

void i2c::stop() const
{
    IIC2.ICSR.BIT.TEND = 0;     //送信の後始末

    IIC2.ICSR.BIT.STOP = 0;    
    send_stop_bit();
    
    while(!IIC2.ICSR.BIT.STOP);
    
    volatile unsigned char dummy = IIC2.ICDRR;
    IIC2.ICCR1.BIT.RCVD = 0;    //
    IIC2.ICIER.BIT.ACKBT = 0;   //受信の後始末
    
    IIC2.ICCR1.BIT.MST = 0; //スレーブ
    IIC2.ICCR1.BIT.TRS = 0; //受信
}

void i2c::write(const unsigned char* data, size_t size) const
{
    for(size_t i = 0; i < size; ++i)
    {
        while(!IIC2.ICSR.BIT.TDRE);
        IIC2.ICDRT = data[i];
    }
    
    while(!IIC2.ICSR.BIT.TEND);
}

void i2c::read(unsigned char* buff, size_t size) const
{
    IIC2.ICSR.BIT.TEND = 0; //
    IIC2.ICCR1.BIT.TRS = 0; //
    IIC2.ICSR.BIT.TDRE = 0; //受信モードに切り替え
    
    volatile unsigned char dummy = IIC2.ICDRR; //受信開始
    
    for(size_t i = 0; i < size; ++i)
    {
        while(!IIC2.ICSR.BIT.RDRF);
        
        //最終フレーム
        if(i == size - 1)
        {
            IIC2.ICCR1.BIT.RCVD = 1;    //次受信禁止
            IIC2.ICIER.BIT.ACKBT = 1;   //NACK送信
        }
                    
        buff[i] = IIC2.ICDRR;
    }
}

}