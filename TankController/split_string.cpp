#include "split_string.hpp"
#include <string>

namespace util
{
    
void split_string(const string& source, char separator, string& left, string& right)
{
    int index = source.find_first_of(separator);
    
    if(string::npos == index || source.size() - 1 == index) //�܂܂�Ȃ����E�[
    {
        left = source;
        right = "";
    }
    else if(0 == index) //���[
    {
        left = "";
        right = source;
    }
    else
    {
        left = source.substr(0, index);
        right = source.substr(index + 1);
    }
}

}