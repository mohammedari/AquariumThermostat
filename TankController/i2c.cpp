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
    IIC2.ICMR.BIT.MLS = 0;      //MSB�t�@�[�X�g
    IIC2.ICMR.BIT.WAIT = 1;     //���M���E�F�C�g�}��
    IIC2.ICIER.BYTE = 0x00;     //���荞�݋֎~�AACK�����A���MACK=0
    IIC2.SAR.BIT.FS = 0;        //I2C�t�H�[�}�b�g
}

bool i2c::start(unsigned char control) const
{
    IIC2.ICCR1.BIT.MST = 1; //�}�X�^
    IIC2.ICCR1.BIT.TRS = 1; //���M
    
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
    IIC2.ICSR.BIT.TEND = 0;     //���M�̌�n��

    IIC2.ICSR.BIT.STOP = 0;    
    send_stop_bit();
    
    while(!IIC2.ICSR.BIT.STOP);
    
    volatile unsigned char dummy = IIC2.ICDRR;
    IIC2.ICCR1.BIT.RCVD = 0;    //
    IIC2.ICIER.BIT.ACKBT = 0;   //��M�̌�n��
    
    IIC2.ICCR1.BIT.MST = 0; //�X���[�u
    IIC2.ICCR1.BIT.TRS = 0; //��M
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
    IIC2.ICSR.BIT.TDRE = 0; //��M���[�h�ɐ؂�ւ�
    
    volatile unsigned char dummy = IIC2.ICDRR; //��M�J�n
    
    for(size_t i = 0; i < size; ++i)
    {
        while(!IIC2.ICSR.BIT.RDRF);
        
        //�ŏI�t���[��
        if(i == size - 1)
        {
            IIC2.ICCR1.BIT.RCVD = 1;    //����M�֎~
            IIC2.ICIER.BIT.ACKBT = 1;   //NACK���M
        }
                    
        buff[i] = IIC2.ICDRR;
    }
}

}