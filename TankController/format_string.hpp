#pragma once

#include "stdio.h"
#include "stdarg.h"
#include <string>

namespace util
{

template<size_t BUF_SIZE>
string format_string(const char* format, ...)
{
	char buf[BUF_SIZE];
	
	va_list ap;
	va_start(ap, format);
	vsprintf(buf, format, ap);
	va_end(ap);
	
	return string(buf);
}
	
}