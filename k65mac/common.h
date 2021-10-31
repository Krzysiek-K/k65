
#pragma once


#define K65_VERSION_MAJOR		0
#define K65_VERSION_MINOR		2
#define K65_VERSION_REVISION	1


#define ___str(x)				#x
#define __str(x)				___str(x)
#define K65_VERSION_TEXT()		__str(K65_VERSION_MAJOR) "." __str(K65_VERSION_MINOR) "." __str(K65_VERSION_REVISION)


class IErrorHandler {
public:
	virtual void   Error(const char *e)		{ static string _e; _e=e;	throw _e.c_str();	}
	virtual void   Warn(const char *e)		{ printf("Warning: %s\n",e);					}

	void   Error(const string &e)	{ Error(e.c_str());	}
	void   Warn(const string &e)	{ Warn(e.c_str());	}
};



#include "asm.h"
//#include "linker.h"
#include "imager.h"
#include "eval.h"
#include "compiler.h"
#include "comstate.h"
#include "sqlinker.h"








// sqapi.cpp

extern IErrorHandler *sqapi_errorhandler;

extern SqVM vm;
extern string current_script_path;
extern string current_exe_path;

int execute(const char *str);


// main.cpp

string fixpath(const char *path);
inline string fixpath(const string &path)	{ return fixpath(path.c_str()); }
