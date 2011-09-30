#pragma once

#include "i2c.hpp"
#include "wait.hpp"

namespace tank_controller
{
    
class eeprom
{
    private:
    static const unsigned char _address = 0xA0; //1010 0000
    util::i2c& _i2c;

    public:
    eeprom(util::i2c& com) : _i2c(com) { }

    template<class T>
    void save(unsigned int address, const T& t)
    {
        while(_i2c.is_busy());
        
        _i2c.start(_address & 0xFE);    //書き込みモード
        _i2c.write((const unsigned char*)&address, sizeof(unsigned int));
        _i2c.write((const unsigned char*)&t, sizeof(T));
        _i2c.stop();
    
        wait(5);    //書き込み待ち
    }
    
    template<class T>
    T load(unsigned int address)
    {
        array<unsigned char, sizeof(T)> t;
        
        while(_i2c.is_busy());
    
        _i2c.start(_address & 0xFE);    //書き込みモード
        _i2c.write((const unsigned char*)&address, sizeof(unsigned int));
        _i2c.start(_address | 0x01);    //読み込みモード
        _i2c.read(t, t.size());
        _i2c.stop();
    
        return reinterpret_cast<T&>(t);
    }
};
    
}