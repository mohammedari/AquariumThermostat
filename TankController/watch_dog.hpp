#pragma once

namespace tank_controller
{

class watch_dog
{
    private:
    bool _error_occured_in_previous_execution;
    
    public:
    watch_dog();
    bool check();
    void watch();
};

}