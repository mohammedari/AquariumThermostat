#pragma once
#include "array.hpp"

namespace util
{

//マスタモード専用
class i2c
{
    public:
    i2c();
    
    void start(unsigned char address);
    void end();
    template<size_t N> void write(const array<unsigned char, N>& data)
    {
    }
    template<size_t N> size_t read(const array<unsigned char, N>& data)
    {
    }
};

}