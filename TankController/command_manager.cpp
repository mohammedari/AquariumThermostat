#include <string>
#include "iodefine.h"
#include "command_manager.hpp"
#include "linked_list.hpp"
#include "command_base.hpp"
#include "wait.hpp"

namespace tank_controller
{

void command_manager::register_command(command_base& command)
{
    _command_list.add(command);
}

void command_manager::parse_command(string& line)
{
    int index = line.find_first_of(_separator);
    string command_str = line.substr(0, index);
    string parameter_str("");
    if(line.npos != index)
        string parameter_str = line.substr(index + 1);

    for(linked_list<command_base>::iterator i = _command_list.begin(); i != _command_list.end(); i++)
        if((*i).is_match(command_str))
        {
            (*i).execute(parameter_str);
            break;
        }
}

void command_manager::on_received(char c)
{
    //改行コード受信
    if(_new_line == c)
    {
        parse_command(_line);
        clear_received_character();
        return;
    }

    add_received_character(c);
}
    
}
