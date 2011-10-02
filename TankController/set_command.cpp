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
        array<int, 3> arr;
        
        for(int i = 0; i < 3; i++)
        {
            string l, r;
            split_string(value, ':', l, r);
                                
            arr[i] = atoi(l.c_str());
            if(0 > arr[i])
            {
                s.write_line("Invalid value was entered. Format is \"xx:xx:xx\".");
                return;
            }   
            
            value = r;
        }
        
        time t = time(arr[0], arr[1], arr[2]);
        _clock.set(t);
        s.write_line("Time was set to " + t.str());
    }
    else if("temperature" == command)
    {
        float f = atof(value.c_str());
        if(0 > f)
        {
            s.write_line("Invalid value was entered.");
            s.write_line("Please enter positive float value.");
            return;
        }
        
        _status.setting_temperature = temperature(f);
        s.write_line("Temperature was set to " + _status.setting_temperature.str());
    }
    else if("light" == command)
    {
        string hour, sw;
        split_string(value, ' ', hour, sw);
        int h = atoi(hour.c_str());
        
        if(h < 0 && 23 < h)
        {
            s.write_line("Invalid hour was selected.");
            s.write_line("Please enter 0-23 value after \"light\".");
            return;
        }
        
        if("on" == sw)
            _status.light_seq.set_on(h);
        else if("off" == sw)
            _status.light_seq.set_off(h);
        else
        {
            s.write_line("Invalid switch was entered.");
            s.write_line("Please enter \"on\" or \"off\" after hour number.");
            return;
        }
        
        //s.write_line("Light swiches " + sw + " at " + hour + ".");
        s.write("Light switches ");
        s.write(sw);
        s.write(" at ");
        s.write(hour);
        s.write_line(".");
    }
    else
        s.write_line("Invalid parameter was entered. Please check \"help set\".");
}

}}