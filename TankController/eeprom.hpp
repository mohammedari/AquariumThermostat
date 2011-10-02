#pragma once

#include "i2c.hpp"
#include "wait.hpp"
#include "stddef.h"

namespace tank_controller
{
    
class eeprom
{
    private:
    static const unsigned char _address = 0xA0; //1010 0000
    static const size_t _page_size = 32;
    static const unsigned char _write_cycle_ms = 5;
    util::i2c& _i2c;

    public:
    eeprom(util::i2c& com) : _i2c(com) { }

    template<class T>
    void save(unsigned int address, const T& t)
    {
        write(address, (const unsigned char*)&t, sizeof(T));
    }
    
    template<class T>
    T load(unsigned int address)
    {
        array<unsigned char, sizeof(T)> t;
        
        while(_i2c.is_busy());
    
        _i2c.start(_address & 0xFE);    //�������݃��[�h
        _i2c.write((const unsigned char*)&address, sizeof(unsigned int));
        _i2c.start(_address | 0x01);    //�ǂݍ��݃��[�h
        _i2c.read(t, t.size());
        _i2c.stop();
    
        return reinterpret_cast<T&>(t);
    }
    
    private:

    bool check_page_overflow(unsigned int address, size_t size)
    {
        //�擪�A�h���X�Ɩ��[�A�h���X�������y�[�W�ɂ��邩�ǂ����`�F�b�N
        return address / _page_size == ( address + size - 1 ) / _page_size;
    }
    
    void write(unsigned int address, const unsigned char* data, size_t size)
    {
        if(check_page_overflow(address, size))  //�y�[�W���E�`�F�b�N
        {
            while(_i2c.is_busy());
        
            _i2c.start(_address & 0xFE);    //�������݃��[�h
            _i2c.write((const unsigned char*)&address, sizeof(unsigned int));
            _i2c.write(data, size);
            _i2c.stop();
    
            util::wait(_write_cycle_ms);    //�������ݑ҂�
        }
        else
        {
            size_t s = _page_size - address % _page_size;   //�擪�A�h���X�̃y�[�W�ɏ������߂�傫��
            write(address, data, s);
            write(address + s + 1, data + s + 1, size - s);
        }
    }
};
    
}