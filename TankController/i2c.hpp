#pragma once
#include "array.hpp"
#include "iodefine.h"

namespace util
{

//�}�X�^���[�h��p
class i2c
{
    private:
    static i2c* _instance;
    
    private:
    i2c();
    i2c(const i2c& i) { }
    
    public:
    static i2c& get_instance();
    static void delete_instance();
    
    public:
    //�X���[�u�A�h���X7bit + R/W, �X���[�u��������Ȃ��ꍇ��false��Ԃ�
    bool start(unsigned char control) const;    //busy�`�F�b�N�͂��Ȃ�
    bool is_busy() const { return IIC2.ICCR2.BIT.BBSY; }
    void stop() const;
    void write(const unsigned char* data, size_t size) const;
    void read(unsigned char* buff, size_t size) const;
    
    private:
    void send_start_bit() const { IIC2.ICCR2.BYTE = (IIC2.ICCR2.BYTE | 0x80) & 0xBF; }  //BBSY = 1, SCP = 0
    void send_stop_bit() const { IIC2.ICCR2.BYTE &= 0x3F; } //BBSY = 0, SCP = 0
};

}