#pragma once

namespace util
{

//単一モードのみ
class adc
{
    private:
    static bool _initialized;
    unsigned char _channel;
    
    public:
	//channelは000-111のでAN0～AN7を選択
    adc(unsigned char channel);
    unsigned int scan() const;
};
    
}