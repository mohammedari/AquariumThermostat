#pragma once

#include "command_base.hpp"

namespace tank_controller
{
    
class command_manager
{
    private:
    static const size_t _size = 5;
    command_base* _command_list[_size];
    static command_manager* _current_instance;
    
    public:
    command_manager();
    void register_commnad(command_base& command);
    
    public:
    void hook_receive_intrrupt();
    static void receive_intrrupt();
};

}