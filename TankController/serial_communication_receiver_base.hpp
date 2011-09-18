#pragma once

//‘ŠŒİQÆ
namespace util
{
class serial_communication;
}


namespace util
{
    
class serial_communication_receiver_base
{
    public:
    virtual void on_received(serial_communication& s, char c) = 0;    
};

}