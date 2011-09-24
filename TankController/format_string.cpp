#include "format_string.hpp"
#include "stdio.h"
#include "stdarg.h"
#include <string>

namespace util
{

string format_string(const char* format, ...)    
{
	char buf[default_buf_size];
	
	va_list ap;
	va_start(ap, format);
	vsprintf(buf, format, ap);
	va_end(ap);
	
	return string(buf);
}

}