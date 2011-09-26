#pragma once

//ëäå›éQè∆
namespace util
{
class serial_communication;
}


namespace util
{
    
class serial_communication_receiver_base
{
    public:
	virtual ~serial_communication_receiver_base() { };
    virtual void on_received(serial_communication& s, char c) = 0;    
};

}