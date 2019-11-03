
#include "base.h"

using namespace std;




namespace base
{



string format(const char *fmt, ...)
{
	string tmp;
	va_list arg;
	va_start(arg,fmt);
	vsprintf(tmp,fmt,arg);
	va_end(arg);
	return tmp;
}


string vformat(const char *fmt, va_list arg)
{
	string tmp;
	vsprintf(tmp,fmt,arg);
	return tmp;
}


void sprintf(string &out,const char *fmt, ...)
{
	va_list arg;
	va_start(arg,fmt);
	vsprintf(out,fmt,arg);
	va_end(arg);
}


void vsprintf(string &out,const char *fmt, va_list arg)
{
	va_list start = arg;
	int len = vsnprintf(NULL,0,fmt,arg) + 1;
	out.resize(len);
	vsnprintf((char*)out.data(),len,fmt,start);
	out.resize(len-1);
}



}
