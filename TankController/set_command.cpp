#include "set_command.hpp"
#include <string>
#include "array.hpp"
#include "temperature.hpp"
#include "split_string.hpp"

using namespace util;

namespace tank_controller {
namespace commands {
    
void set_command::execute(const serial_communication& s, const string& parameter)
{
    string command, value;
    split_string(parameter, ' ', command, value);
    
    if("time" == command)
    {   
        array<unsigned char, 3> arr;
        
        for(int i = 0; i < 3; i++)
        {
            string l, r;
            split_string(value, ':', l, r);
                    
            arr[i] = atoi(l.c_str());
            if(0 >= arr[i])
            {
                s.write_line("Invalid value was entered. Format is \"xx:xx:xx\".");
                return;
            }   
            
            value = r;
        }
        
        _clock.set(time(arr[0], arr[1], arr[2]));
    }
    if("temperature" == command)
    {
        float f = atof(value.c_str());
        if(0 == f)
        {
            s.write_line("Invalid value was entered. Please enter float value after \"temperature\".");
            return;
        }
        
        _status.setting_temperature = temperature(f);
    }
    else
        s.write_line("Invalid parameter was entered. Please check \"help get\".");
}

}}