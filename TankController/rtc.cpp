#include "rtc.hpp"
#include "time.hpp"
#include "i2c.hpp"
#include "array.hpp"

using namespace util;

namespace tank_controller
{
    
const unsigned char rtc::_control_address = 0x00;
const unsigned char rtc::_seconds_address = 0x02;

rtc::rtc(i2c& com) : _i2c(com)
{
    //コントロールレジスタを初期化
    _i2c.start(_address & 0xFE);    //書き込みモード
    _i2c.write((const unsigned char*)&_control_address, sizeof(unsigned char));
    unsigned char data[] = { 0x00, 0x00 };
    _i2c.write(data, 2);
    _i2c.stop();
}

void rtc::set(const time& t)
{
    array<unsigned char, 3> data;
    data[0] = _convert_to_bcd(t.second);
    data[1] = _convert_to_bcd(t.minute);
    data[2] = _convert_to_bcd(t.hour);
    
    _i2c.start(_address & 0xFE);    //書き込みモード
    _i2c.write((const unsigned char*)&_seconds_address, sizeof(unsigned char));
    _i2c.write(data, data.size());
    _i2c.stop();
}

time rtc::get()
{
    array<unsigned char, 3> buf;
    
    _i2c.start(_address & 0xFE);    //書き込みモード
    _i2c.write((const unsigned char*)&_seconds_address, sizeof(unsigned char));
    _i2c.start(_address | 0x01);    //読み出しモード
    _i2c.read(buf, buf.size());
    _i2c.stop();
    
    return time(_convert_from_bcd(buf[2]), 
                _convert_from_bcd(buf[1]), 
                _convert_from_bcd(buf[0])); 
}

unsigned char rtc::_convert_to_bcd(unsigned char integer)
{
    unsigned char high = integer / 10;
    unsigned char low = integer % 10;
    
    return (high << 4) + low;
}

unsigned char rtc::_convert_from_bcd(unsigned char bcd)
{
    unsigned char high = bcd >> 4;
    unsigned char low = bcd & 0x0F;
    
    return high * 10 + low;
}
    
}