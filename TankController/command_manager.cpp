#include <string>
#include "iodefine.h"
#include "command_manager.hpp"
#include "linked_list.hpp"
#include "command_base.hpp"
#include "wait.hpp"
#include "serial_communication.hpp"
#include "stddef.h"

#include "alert.hpp"

namespace util
{

void command_manager::parse_command(serial_communication& s, const string& line)
{
    int index = line.find_first_of(_separator);
    string command_str = line.substr(0, index);
    string parameter_str("");
    if(line.npos != index)
        string parameter_str = line.substr(index + 1);

    for(linked_list<command_base*>::iterator i = _command_list.begin(); i != _command_list.end(); ++i)
        if((*i)->is_match(command_str))
        {
            (*i)->execute(s, parameter_str);
            break;
        }
}

void command_manager::echo_back(serial_communication& s, char c) const
{
    s.write(string(1, c));
}

void command_manager::remove_one_character()
{
    size_t s = _line.size();
    if(0 < s)
        _line.resize(s - 1);
}

void command_manager::on_received(serial_communication& s, char c)
{
    //test
    //tank_controller::alert();
    
    if(!serial_communication::is_control_character(c))
    {
        echo_back(s, c);
        add_received_character(c);
        return;
    }
    
    //制御コード受信
    if(serial_communication::is_new_line(c))
    {
        echo_back(s, c);
        parse_command(s, _line);
        clear_received_character();
    }
    else if(serial_communication::is_back_space(c))
    {
        remove_one_character();
        
        char str[3];
        str[0] = c;
        str[1] = ' ';   //スペースを使って明示的に消す
        str[2] = c;
        s.write(string(str, 3));
    }
}
    
}
