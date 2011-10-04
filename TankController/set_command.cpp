#include "set_command.hpp"
#include <string>
#include "array.hpp"
#include "temperature.hpp"
#include "split_string.hpp"
#include "format_string.hpp"

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
                s.write("Invalid value was entered.");
                s.write_line(" Format is \"xx:xx:xx\".");
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
        if(temperature::min > f || temperature::max < f)
        {
            s.write_line("Invalid value was entered.");
            s.write("Please enter float value from");
            s.write_line(format_string(" %4.1f to %4.1f.", temperature::min, temperature::max));
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
        
        if(h < 0 || 23 < h)
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
            s.write("Please enter \"on\" or");
            s.write_line(" \"off\" after hour number.");
            return;
        }
        
        s.write("Light switches ");
        s.write(sw);
        s.write(" at ");
        s.write(hour);
        s.write_line(".");
    }
    else
    {
        s.write("Invalid parameter was entered.");
        s.write_line(" Please check \"help set\".");
    }
}

}}