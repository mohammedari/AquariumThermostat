#pragma once

namespace tank_controller
{

class watch_dog
{
    private:
    bool _is_error_occured_in_previous_execution;
    
    public:
    watch_dog();
    bool is_error_occured_in_previous_execution() const { return _is_error_occured_in_previous_execution; }
    void watch();
};

}