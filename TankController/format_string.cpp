#include "format_string.hpp"
#include <string>
#include "stdarg.h"
#include "stdio.h"

namespace util
{
	
static const size_t format_buf_size = 20;
	
string format_string(const char* format, ...)
{
	char buf[format_buf_size];
	
	va_list ap;
	va_start(ap, format);
	vsprintf(buf, format, ap);
	va_end(ap);
	
	return string(buf);
}
	
}