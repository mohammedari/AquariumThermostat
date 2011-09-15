#pragma once

namespace util
{
    
class serial_communication_receiver_base
{
    public:
    virtual void on_received(char c) = 0;    
};

}