#include "format_string.hpp"
#include "stdarg.h"
#include <string>

namespace util
{

string _toa(unsigned int i, unsigned char base, unsigned char padding)
{
	string s;

	do{
		s.insert((size_t)0, 1, "0123456789ABCDEF"[i % base]);
		i /= base;
	}while(0 != i);

	if(padding > s.size())
		s.insert((size_t)0, padding - s.size(), '0');

	return s;
}

inline string btoa(unsigned int i, unsigned char padding = 0 ){ return _toa(i, 2, padding); }
inline string otoa(unsigned int i, unsigned char padding = 0 ){ return _toa(i, 8, padding); }
inline string xtoa(unsigned int i, unsigned char padding = 0 ){ return _toa(i, 16, padding); }
string dtoa(int i, unsigned char padding = 0 )
{
	string s;
	if(0 > i)
	{
		i = -i;
		s += '-';
	}
	return s + _toa((unsigned int)i, 10, padding);
}

string ftoa(float f, unsigned char precision = 1, unsigned char padding = 0)
{
	string s;
	bool minus = false;
	if(0 > f)
	{
		f = -f;
		minus = true;
	}

	//整数部
	int i = (int)f;
	do{
		s.insert((size_t)0, 1, "0123456789"[i % 10]);
		i /= 10;
	}while(0 != i);

	//小数点以下
	i = (int)f;	//ごめんなさい再利用…
	if(precision > 0)
	{
		s += '.';
		float g = f - i;
		for(int p = 0; p < precision; p++)
		{
			g *= 10;
			int g_ = (int)g;

			s += "0123456789"[g_];
			g -= g_;
		}
	}

	if(padding > s.size())
		s.insert((size_t)0, padding - s.size(), '0');

	if(minus)
		s.insert((size_t)0, 1, '-');

	return s;
}

//%1b, %2o, %3x, %4.5f, %6d, %c, %sに対応
string format_string(const char* format, ...)
{
	string s;

	va_list args;
	va_start(args, format);

	for(const char* p = format; '\0' != *p; ++p)
	{
		if('%' == *p)
		{
			++p;
			unsigned char pad = 0;
			unsigned char pre = 1;

			//パディング
			if((*p >= '1') && (*p <= '9')) {
                pad = *p++ - '0';
                while ((*p >= '0') && (*p <= '9')) pad = pad * 10 + (*p++ - '0');
            }
			//精度
			if('.' == *p)
			{
				++p;
				if((*p >= '1') && (*p <= '9')) {
					pre = *p++ - '0';
					while ((*p >= '0') && (*p <= '9')) pre = pre * 10 + (*p++ - '0');
				}
			}

			switch(*p)
			{
				case 'b':
					s += btoa((unsigned int)va_arg(args, unsigned int), pad);
				break;
				case 'o':
					s += otoa((unsigned int)va_arg(args, unsigned int), pad);
				break;
				case 'x':
					s += xtoa((unsigned int)va_arg(args, unsigned int), pad);
				break;
				case 'f':
					s += ftoa((double)va_arg(args, double), pre, pad);
				break;
				case 'd':
					s += dtoa((int)va_arg(args, int), pad);
				break;
				case 'c':
					s += (char)va_arg(args, char);
				break;
				case 's':
					s += (char*)va_arg(args, char*);
				break;
				default:
				break;
			}
		}
		else
		{
			s += *p;
		}
	}

	va_end(args);

	return s;
}


}