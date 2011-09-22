#include <string>
#include "iodefine.h"
#include "command_manager.hpp"
#include "list.hpp"
#include "command_base.hpp"
#include "wait.hpp"
#include "serial_communication.hpp"
#include "stddef.h"

namespace util
{

void command_manager::parse_command(serial_communication& s, const string& line)
{
    int index = line.find_first_of(_separator);
    string command_str = line.substr(0, index);
    string parameter_str("");
    if(line.npos != index)
        string parameter_str = line.substr(index + 1);

    for(list<command_base*>::iterator i = _command_list.begin(); i != _command_list.end(); ++i)
        if((*i)->is_match(command_str))
        {
            (*i)->execute(s, parameter_str);
            break;
        }
}

bool command_manager::add_received_character(char c)
{
    //多すぎたら読み捨て
    if(_line.size() + 1 > _line.max_size())
        return false;

    _line += c;
    return true;
}

void command_manager::remove_one_character()
{
    size_t s = _line.size();
    if(0 < s)
        _line.resize(s - 1);
}

void command_manager::on_received(serial_communication& s, char c)
{    
    if(!serial_communication::is_control_character(c))
    {
        if(add_received_character(c))
            s.putc(c);
            
        return;
    }
    
    //制御コード受信
    if(serial_communication::is_new_line(c))
    {
        s.putc(c);
        parse_command(s, _line);
        clear_received_character();
        
        show_command_request_character(s);
    }
    else if(serial_communication::is_back_space(c))
    {
        if(0 < _line.size())
        {
            remove_one_character();
            s.putc(c); s.putc(' '); s.putc(c);  //戻って上書きして戻る
        }
    }
}
    
}
