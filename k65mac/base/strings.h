
#ifndef _BASE_STRINGS_H
#define _BASE_STRINGS_H


#include <stdio.h>
#include <stdarg.h>


namespace base
{


std::string format(const char *fmt, ...);
std::string vformat(const char *fmt, va_list arg);

void sprintf(std::string &out,const char *fmt, ...);
void vsprintf(std::string &out,const char *fmt, va_list arg);


}


#endif
