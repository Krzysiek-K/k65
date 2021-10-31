// ---------------- Library -- generated on 28.10.2017  20:32 ----------------



// ******************************** _xsquirrel.cpp ********************************

#ifndef _XSQUIRREL_CPP_DONE
#define _XSQUIRREL_CPP_DONE



#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef SQBIND_STATIC
#define SQBIND_STATIC
#endif



#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <vector>
using namespace std;


// ---- #include "xsquirrel.h"
// ---> including xsquirrel.h

#ifndef _XSQUIRREL_H
#define _XSQUIRREL_H


#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef SQBIND_STATIC
#define SQBIND_STATIC
#endif


#include <string.h>
#include <string>
#include <vector>


#if !defined(__clang__)
	#define __has_feature(x)	0
#endif

#if defined(__GNUC__)
	#define SQBIND_BEGIN_MULTILINE_MACRO()	do {
	#define SQBIND_END_MULTILINE_MACRO()	} while(0)
#endif

#define SQBIND_CPP0X_NULLPTR_SUPPORTED	0


// ---- #include "squirrel/squirrel.h"
// ---> including squirrel.h
/*
Copyright (c) 2003-2012 Alberto Demichelis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef _SQUIRREL_H_
#define _SQUIRREL_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SQUIRREL_API
#define SQUIRREL_API extern
#endif

#if (defined(_WIN64) || defined(_LP64))
#ifndef _SQ64
#define _SQ64
#endif
#endif

#ifdef _SQ64

#ifdef _MSC_VER
typedef __int64 SQInteger;
typedef unsigned __int64 SQUnsignedInteger;
typedef unsigned __int64 SQHash; /*should be the same size of a pointer*/
#else
typedef long long SQInteger;
typedef unsigned long long SQUnsignedInteger;
typedef unsigned long long SQHash; /*should be the same size of a pointer*/
#endif
typedef int SQInt32; 
typedef unsigned int SQUnsignedInteger32;
#else 
typedef int SQInteger;
typedef int SQInt32; /*must be 32 bits(also on 64bits processors)*/
typedef unsigned int SQUnsignedInteger32; /*must be 32 bits(also on 64bits processors)*/
typedef unsigned int SQUnsignedInteger;
typedef unsigned int SQHash; /*should be the same size of a pointer*/
#endif


#ifdef SQUSEDOUBLE
typedef double SQFloat;
#else
typedef float SQFloat;
#endif

#if defined(SQUSEDOUBLE) && !defined(_SQ64) || !defined(SQUSEDOUBLE) && defined(_SQ64)
#ifdef _MSC_VER
typedef __int64 SQRawObjectVal; //must be 64bits
#else
typedef long long SQRawObjectVal; //must be 64bits
#endif
#define SQ_OBJECT_RAWINIT() { _unVal.raw = 0; }
#else
typedef SQUnsignedInteger SQRawObjectVal; //is 32 bits on 32 bits builds and 64 bits otherwise
#define SQ_OBJECT_RAWINIT()
#endif

#ifndef SQ_ALIGNMENT // SQ_ALIGNMENT shall be less than or equal to SQ_MALLOC alignments, and its value shall be power of 2.
#if defined(SQUSEDOUBLE) || defined(_SQ64)
#define SQ_ALIGNMENT 8
#else
#define SQ_ALIGNMENT 4
#endif
#endif

typedef void* SQUserPointer;
typedef SQUnsignedInteger SQBool;
typedef SQInteger SQRESULT;

#define SQTrue	(1)
#define SQFalse	(0)

struct SQVM;
struct SQTable;
struct SQArray;
struct SQString;
struct SQClosure;
struct SQGenerator;
struct SQNativeClosure;
struct SQUserData;
struct SQFunctionProto;
struct SQRefCounted;
struct SQClass;
struct SQInstance;
struct SQDelegable;
struct SQOuter;

#ifdef _UNICODE
#define SQUNICODE
#endif

#ifdef SQUNICODE
#if (defined(_MSC_VER) && _MSC_VER >= 1400) // 1400 = VS8

#if !defined(_NATIVE_WCHAR_T_DEFINED) //this is if the compiler considers wchar_t as native type
#define wchar_t unsigned short
#endif

#else
typedef unsigned short wchar_t;
#endif

typedef wchar_t SQChar;
#define _SC(a) L##a
#define	scstrcmp	wcscmp
#define scsprintf	swprintf
#define scstrlen	wcslen
#define scstrtod	wcstod
#ifdef _SQ64
#define scstrtol	_wcstoi64
#else
#define scstrtol	wcstol
#endif
#define scatoi		_wtoi
#define scstrtoul	wcstoul
#define scvsprintf	vswprintf
#define scstrstr	wcsstr
#define scisspace	iswspace
#define scisdigit	iswdigit
#define scisxdigit	iswxdigit
#define scisalpha	iswalpha
#define sciscntrl	iswcntrl
#define scisalnum	iswalnum
#define scprintf	wprintf
#define MAX_CHAR 0xFFFF
#else
typedef char SQChar;
#define _SC(a) a
#define	scstrcmp	strcmp
#define scsprintf	sprintf
#define scstrlen	strlen
#define scstrtod	strtod
#ifdef _SQ64
#ifdef _MSC_VER
#define scstrtol	_strtoi64
#else
#define scstrtol	strtoll
#endif
#else
#define scstrtol	strtol
#endif
#define scatoi		atoi
#define scstrtoul	strtoul
#define scvsprintf	vsprintf
#define scstrstr	strstr
#define scisspace	isspace
#define scisdigit	isdigit
#define scisxdigit	isxdigit
#define sciscntrl	iscntrl
#define scisalpha	isalpha
#define scisalnum	isalnum
#define scprintf	printf
#define MAX_CHAR 0xFF
#endif

#ifdef _SQ64
#define _PRINT_INT_PREC _SC("ll")
#define _PRINT_INT_FMT _SC("%lld")
#else
#define _PRINT_INT_FMT _SC("%d")
#endif

#define SQUIRREL_VERSION	_SC("Squirrel 3.0.3 stable")
#define SQUIRREL_COPYRIGHT	_SC("Copyright (C) 2003-2012 Alberto Demichelis")
#define SQUIRREL_AUTHOR		_SC("Alberto Demichelis")
#define SQUIRREL_VERSION_NUMBER	303

#define SQ_VMSTATE_IDLE			0
#define SQ_VMSTATE_RUNNING		1
#define SQ_VMSTATE_SUSPENDED	2

#define SQUIRREL_EOB 0
#define SQ_BYTECODE_STREAM_TAG	0xFAFA

#define SQOBJECT_REF_COUNTED	0x08000000
#define SQOBJECT_NUMERIC		0x04000000
#define SQOBJECT_DELEGABLE		0x02000000
#define SQOBJECT_CANBEFALSE		0x01000000

#define SQ_MATCHTYPEMASKSTRING (-99999)

#define _RT_MASK 0x00FFFFFF
#define _RAW_TYPE(type) (type&_RT_MASK)

#define _RT_NULL			0x00000001
#define _RT_INTEGER			0x00000002
#define _RT_FLOAT			0x00000004
#define _RT_BOOL			0x00000008
#define _RT_STRING			0x00000010
#define _RT_TABLE			0x00000020
#define _RT_ARRAY			0x00000040
#define _RT_USERDATA		0x00000080
#define _RT_CLOSURE			0x00000100
#define _RT_NATIVECLOSURE	0x00000200
#define _RT_GENERATOR		0x00000400
#define _RT_USERPOINTER		0x00000800
#define _RT_THREAD			0x00001000
#define _RT_FUNCPROTO		0x00002000
#define _RT_CLASS			0x00004000
#define _RT_INSTANCE		0x00008000
#define _RT_WEAKREF			0x00010000
#define _RT_OUTER			0x00020000

typedef enum tagSQObjectType{
	OT_NULL =			(_RT_NULL|SQOBJECT_CANBEFALSE),
	OT_INTEGER =		(_RT_INTEGER|SQOBJECT_NUMERIC|SQOBJECT_CANBEFALSE),
	OT_FLOAT =			(_RT_FLOAT|SQOBJECT_NUMERIC|SQOBJECT_CANBEFALSE),
	OT_BOOL =			(_RT_BOOL|SQOBJECT_CANBEFALSE),
	OT_STRING =			(_RT_STRING|SQOBJECT_REF_COUNTED),
	OT_TABLE =			(_RT_TABLE|SQOBJECT_REF_COUNTED|SQOBJECT_DELEGABLE),
	OT_ARRAY =			(_RT_ARRAY|SQOBJECT_REF_COUNTED),
	OT_USERDATA =		(_RT_USERDATA|SQOBJECT_REF_COUNTED|SQOBJECT_DELEGABLE),
	OT_CLOSURE =		(_RT_CLOSURE|SQOBJECT_REF_COUNTED),
	OT_NATIVECLOSURE =	(_RT_NATIVECLOSURE|SQOBJECT_REF_COUNTED),
	OT_GENERATOR =		(_RT_GENERATOR|SQOBJECT_REF_COUNTED),
	OT_USERPOINTER =	_RT_USERPOINTER,
	OT_THREAD =			(_RT_THREAD|SQOBJECT_REF_COUNTED) ,
	OT_FUNCPROTO =		(_RT_FUNCPROTO|SQOBJECT_REF_COUNTED), //internal usage only
	OT_CLASS =			(_RT_CLASS|SQOBJECT_REF_COUNTED),
	OT_INSTANCE =		(_RT_INSTANCE|SQOBJECT_REF_COUNTED|SQOBJECT_DELEGABLE),
	OT_WEAKREF =		(_RT_WEAKREF|SQOBJECT_REF_COUNTED),
	OT_OUTER =			(_RT_OUTER|SQOBJECT_REF_COUNTED) //internal usage only
}SQObjectType;

#define ISREFCOUNTED(t) (t&SQOBJECT_REF_COUNTED)


typedef union tagSQObjectValue
{
	struct SQTable *pTable;
	struct SQArray *pArray;
	struct SQClosure *pClosure;
	struct SQOuter *pOuter;
	struct SQGenerator *pGenerator;
	struct SQNativeClosure *pNativeClosure;
	struct SQString *pString;
	struct SQUserData *pUserData;
	SQInteger nInteger;
	SQFloat fFloat;
	SQUserPointer pUserPointer;
	struct SQFunctionProto *pFunctionProto;
	struct SQRefCounted *pRefCounted;
	struct SQDelegable *pDelegable;
	struct SQVM *pThread;
	struct SQClass *pClass;
	struct SQInstance *pInstance;
	struct SQWeakRef *pWeakRef;
	SQRawObjectVal raw;
}SQObjectValue;


typedef struct tagSQObject
{
	SQObjectType _type;
	SQObjectValue _unVal;
}SQObject;

typedef struct  tagSQMemberHandle{
	SQBool _static;
	SQInteger _index;
}SQMemberHandle;

typedef struct tagSQStackInfos{
	const SQChar* funcname;
	const SQChar* source;
	SQInteger line;
}SQStackInfos;

typedef struct SQVM* HSQUIRRELVM;
typedef SQObject HSQOBJECT;
typedef SQMemberHandle HSQMEMBERHANDLE;
typedef SQInteger (*SQFUNCTION)(HSQUIRRELVM);
typedef SQInteger (*SQRELEASEHOOK)(SQUserPointer,SQInteger size);
typedef void (*SQCOMPILERERROR)(HSQUIRRELVM,const SQChar * /*desc*/,const SQChar * /*source*/,SQInteger /*line*/,SQInteger /*column*/);
typedef void (*SQPRINTFUNCTION)(HSQUIRRELVM,const SQChar * ,...);
typedef void (*SQDEBUGHOOK)(HSQUIRRELVM /*v*/, SQInteger /*type*/, const SQChar * /*sourcename*/, SQInteger /*line*/, const SQChar * /*funcname*/);
typedef SQInteger (*SQWRITEFUNC)(SQUserPointer,SQUserPointer,SQInteger);
typedef SQInteger (*SQREADFUNC)(SQUserPointer,SQUserPointer,SQInteger);

typedef SQInteger (*SQLEXREADFUNC)(SQUserPointer);

typedef struct tagSQRegFunction{
	const SQChar *name;
	SQFUNCTION f;
	SQInteger nparamscheck;
	const SQChar *typemask;
}SQRegFunction;

typedef struct tagSQFunctionInfo {
	SQUserPointer funcid;
	const SQChar *name;
	const SQChar *source;
}SQFunctionInfo;

/*vm*/
SQUIRREL_API HSQUIRRELVM sq_open(SQInteger initialstacksize);
SQUIRREL_API HSQUIRRELVM sq_newthread(HSQUIRRELVM friendvm, SQInteger initialstacksize);
SQUIRREL_API void sq_seterrorhandler(HSQUIRRELVM v);
SQUIRREL_API void sq_close(HSQUIRRELVM v);
SQUIRREL_API void sq_setforeignptr(HSQUIRRELVM v,SQUserPointer p);
SQUIRREL_API SQUserPointer sq_getforeignptr(HSQUIRRELVM v);
SQUIRREL_API void sq_setprintfunc(HSQUIRRELVM v, SQPRINTFUNCTION printfunc,SQPRINTFUNCTION errfunc);
SQUIRREL_API SQPRINTFUNCTION sq_getprintfunc(HSQUIRRELVM v);
SQUIRREL_API SQPRINTFUNCTION sq_geterrorfunc(HSQUIRRELVM v);
SQUIRREL_API SQRESULT sq_suspendvm(HSQUIRRELVM v);
SQUIRREL_API SQRESULT sq_wakeupvm(HSQUIRRELVM v,SQBool resumedret,SQBool retval,SQBool raiseerror,SQBool throwerror);
SQUIRREL_API SQInteger sq_getvmstate(HSQUIRRELVM v);
SQUIRREL_API SQInteger sq_getversion();

/*compiler*/
SQUIRREL_API SQRESULT sq_compile(HSQUIRRELVM v,SQLEXREADFUNC read,SQUserPointer p,const SQChar *sourcename,SQBool raiseerror);
SQUIRREL_API SQRESULT sq_compilebuffer(HSQUIRRELVM v,const SQChar *s,SQInteger size,const SQChar *sourcename,SQBool raiseerror);
SQUIRREL_API void sq_enabledebuginfo(HSQUIRRELVM v, SQBool enable);
SQUIRREL_API void sq_notifyallexceptions(HSQUIRRELVM v, SQBool enable);
SQUIRREL_API void sq_setcompilererrorhandler(HSQUIRRELVM v,SQCOMPILERERROR f);

/*stack operations*/
SQUIRREL_API void sq_push(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API void sq_pop(HSQUIRRELVM v,SQInteger nelemstopop);
SQUIRREL_API void sq_poptop(HSQUIRRELVM v);
SQUIRREL_API void sq_remove(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQInteger sq_gettop(HSQUIRRELVM v);
SQUIRREL_API void sq_settop(HSQUIRRELVM v,SQInteger newtop);
SQUIRREL_API SQRESULT sq_reservestack(HSQUIRRELVM v,SQInteger nsize);
SQUIRREL_API SQInteger sq_cmp(HSQUIRRELVM v);
SQUIRREL_API void sq_move(HSQUIRRELVM dest,HSQUIRRELVM src,SQInteger idx);

/*object creation handling*/
SQUIRREL_API SQUserPointer sq_newuserdata(HSQUIRRELVM v,SQUnsignedInteger size);
SQUIRREL_API void sq_newtable(HSQUIRRELVM v);
SQUIRREL_API void sq_newtableex(HSQUIRRELVM v,SQInteger initialcapacity);
SQUIRREL_API void sq_newarray(HSQUIRRELVM v,SQInteger size);
SQUIRREL_API void sq_newclosure(HSQUIRRELVM v,SQFUNCTION func,SQUnsignedInteger nfreevars);
SQUIRREL_API SQRESULT sq_setparamscheck(HSQUIRRELVM v,SQInteger nparamscheck,const SQChar *typemask);
SQUIRREL_API SQRESULT sq_bindenv(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API void sq_pushstring(HSQUIRRELVM v,const SQChar *s,SQInteger len);
SQUIRREL_API void sq_pushfloat(HSQUIRRELVM v,SQFloat f);
SQUIRREL_API void sq_pushinteger(HSQUIRRELVM v,SQInteger n);
SQUIRREL_API void sq_pushbool(HSQUIRRELVM v,SQBool b);
SQUIRREL_API void sq_pushuserpointer(HSQUIRRELVM v,SQUserPointer p);
SQUIRREL_API void sq_pushnull(HSQUIRRELVM v);
SQUIRREL_API SQObjectType sq_gettype(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_typeof(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQInteger sq_getsize(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQHash sq_gethash(HSQUIRRELVM v, SQInteger idx);
SQUIRREL_API SQRESULT sq_getbase(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQBool sq_instanceof(HSQUIRRELVM v);
SQUIRREL_API SQRESULT sq_tostring(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API void sq_tobool(HSQUIRRELVM v, SQInteger idx, SQBool *b);
SQUIRREL_API SQRESULT sq_getstring(HSQUIRRELVM v,SQInteger idx,const SQChar **c);
SQUIRREL_API SQRESULT sq_getinteger(HSQUIRRELVM v,SQInteger idx,SQInteger *i);
SQUIRREL_API SQRESULT sq_getfloat(HSQUIRRELVM v,SQInteger idx,SQFloat *f);
SQUIRREL_API SQRESULT sq_getbool(HSQUIRRELVM v,SQInteger idx,SQBool *b);
SQUIRREL_API SQRESULT sq_getthread(HSQUIRRELVM v,SQInteger idx,HSQUIRRELVM *thread);
SQUIRREL_API SQRESULT sq_getuserpointer(HSQUIRRELVM v,SQInteger idx,SQUserPointer *p);
SQUIRREL_API SQRESULT sq_getuserdata(HSQUIRRELVM v,SQInteger idx,SQUserPointer *p,SQUserPointer *typetag);
SQUIRREL_API SQRESULT sq_settypetag(HSQUIRRELVM v,SQInteger idx,SQUserPointer typetag);
SQUIRREL_API SQRESULT sq_gettypetag(HSQUIRRELVM v,SQInteger idx,SQUserPointer *typetag);
SQUIRREL_API void sq_setreleasehook(HSQUIRRELVM v,SQInteger idx,SQRELEASEHOOK hook);
SQUIRREL_API SQChar *sq_getscratchpad(HSQUIRRELVM v,SQInteger minsize);
SQUIRREL_API SQRESULT sq_getfunctioninfo(HSQUIRRELVM v,SQInteger level,SQFunctionInfo *fi);
SQUIRREL_API SQRESULT sq_getclosureinfo(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger *nparams,SQUnsignedInteger *nfreevars);
SQUIRREL_API SQRESULT sq_getclosurename(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_setnativeclosurename(HSQUIRRELVM v,SQInteger idx,const SQChar *name);
SQUIRREL_API SQRESULT sq_setinstanceup(HSQUIRRELVM v, SQInteger idx, SQUserPointer p);
SQUIRREL_API SQRESULT sq_getinstanceup(HSQUIRRELVM v, SQInteger idx, SQUserPointer *p,SQUserPointer typetag);
SQUIRREL_API SQRESULT sq_setclassudsize(HSQUIRRELVM v, SQInteger idx, SQInteger udsize);
SQUIRREL_API SQRESULT sq_newclass(HSQUIRRELVM v,SQBool hasbase);
SQUIRREL_API SQRESULT sq_createinstance(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_setattributes(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_getattributes(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_getclass(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API void sq_weakref(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_getdefaultdelegate(HSQUIRRELVM v,SQObjectType t);
SQUIRREL_API SQRESULT sq_getmemberhandle(HSQUIRRELVM v,SQInteger idx,HSQMEMBERHANDLE *handle);
SQUIRREL_API SQRESULT sq_getbyhandle(HSQUIRRELVM v,SQInteger idx,const HSQMEMBERHANDLE *handle);
SQUIRREL_API SQRESULT sq_setbyhandle(HSQUIRRELVM v,SQInteger idx,const HSQMEMBERHANDLE *handle);

/*object manipulation*/
SQUIRREL_API void sq_pushroottable(HSQUIRRELVM v);
SQUIRREL_API void sq_pushregistrytable(HSQUIRRELVM v);
SQUIRREL_API void sq_pushconsttable(HSQUIRRELVM v);
SQUIRREL_API SQRESULT sq_setroottable(HSQUIRRELVM v);
SQUIRREL_API SQRESULT sq_setconsttable(HSQUIRRELVM v);
SQUIRREL_API SQRESULT sq_newslot(HSQUIRRELVM v, SQInteger idx, SQBool bstatic);
SQUIRREL_API SQRESULT sq_deleteslot(HSQUIRRELVM v,SQInteger idx,SQBool pushval);
SQUIRREL_API SQRESULT sq_set(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_get(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_rawget(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_rawset(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_rawdeleteslot(HSQUIRRELVM v,SQInteger idx,SQBool pushval);
SQUIRREL_API SQRESULT sq_newmember(HSQUIRRELVM v,SQInteger idx,SQBool bstatic);
SQUIRREL_API SQRESULT sq_rawnewmember(HSQUIRRELVM v,SQInteger idx,SQBool bstatic);
SQUIRREL_API SQRESULT sq_arrayappend(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_arraypop(HSQUIRRELVM v,SQInteger idx,SQBool pushval); 
SQUIRREL_API SQRESULT sq_arrayresize(HSQUIRRELVM v,SQInteger idx,SQInteger newsize); 
SQUIRREL_API SQRESULT sq_arrayreverse(HSQUIRRELVM v,SQInteger idx); 
SQUIRREL_API SQRESULT sq_arrayremove(HSQUIRRELVM v,SQInteger idx,SQInteger itemidx);
SQUIRREL_API SQRESULT sq_arrayinsert(HSQUIRRELVM v,SQInteger idx,SQInteger destpos);
SQUIRREL_API SQRESULT sq_setdelegate(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_getdelegate(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_clone(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_setfreevariable(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger nval);
SQUIRREL_API SQRESULT sq_next(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_getweakrefval(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_clear(HSQUIRRELVM v,SQInteger idx);

/*calls*/
SQUIRREL_API SQRESULT sq_call(HSQUIRRELVM v,SQInteger params,SQBool retval,SQBool raiseerror);
SQUIRREL_API SQRESULT sq_resume(HSQUIRRELVM v,SQBool retval,SQBool raiseerror);
SQUIRREL_API const SQChar *sq_getlocal(HSQUIRRELVM v,SQUnsignedInteger level,SQUnsignedInteger idx);
SQUIRREL_API SQRESULT sq_getcallee(HSQUIRRELVM v);
SQUIRREL_API const SQChar *sq_getfreevariable(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger nval);
SQUIRREL_API SQRESULT sq_throwerror(HSQUIRRELVM v,const SQChar *err);
SQUIRREL_API SQRESULT sq_throwobject(HSQUIRRELVM v);
SQUIRREL_API void sq_reseterror(HSQUIRRELVM v);
SQUIRREL_API void sq_getlasterror(HSQUIRRELVM v);

/*raw object handling*/
SQUIRREL_API SQRESULT sq_getstackobj(HSQUIRRELVM v,SQInteger idx,HSQOBJECT *po);
SQUIRREL_API void sq_pushobject(HSQUIRRELVM v,HSQOBJECT obj);
SQUIRREL_API void sq_addref(HSQUIRRELVM v,HSQOBJECT *po);
SQUIRREL_API SQBool sq_release(HSQUIRRELVM v,HSQOBJECT *po);
SQUIRREL_API SQUnsignedInteger sq_getrefcount(HSQUIRRELVM v,HSQOBJECT *po);
SQUIRREL_API void sq_resetobject(HSQOBJECT *po);
SQUIRREL_API const SQChar *sq_objtostring(const HSQOBJECT *o);
SQUIRREL_API SQBool sq_objtobool(const HSQOBJECT *o);
SQUIRREL_API SQInteger sq_objtointeger(const HSQOBJECT *o);
SQUIRREL_API SQFloat sq_objtofloat(const HSQOBJECT *o);
SQUIRREL_API SQUserPointer sq_objtouserpointer(const HSQOBJECT *o);
SQUIRREL_API SQRESULT sq_getobjtypetag(const HSQOBJECT *o,SQUserPointer * typetag);

/*GC*/
SQUIRREL_API SQInteger sq_collectgarbage(HSQUIRRELVM v);
SQUIRREL_API SQRESULT sq_resurrectunreachable(HSQUIRRELVM v);

/*serialization*/
SQUIRREL_API SQRESULT sq_writeclosure(HSQUIRRELVM vm,SQWRITEFUNC writef,SQUserPointer up);
SQUIRREL_API SQRESULT sq_readclosure(HSQUIRRELVM vm,SQREADFUNC readf,SQUserPointer up);

/*mem allocation*/
SQUIRREL_API void *sq_malloc(SQUnsignedInteger size);
SQUIRREL_API void *sq_realloc(void* p,SQUnsignedInteger oldsize,SQUnsignedInteger newsize);
SQUIRREL_API void sq_free(void *p,SQUnsignedInteger size);

/*debug*/
SQUIRREL_API SQRESULT sq_stackinfos(HSQUIRRELVM v,SQInteger level,SQStackInfos *si);
SQUIRREL_API void sq_setdebughook(HSQUIRRELVM v);
SQUIRREL_API void sq_setnativedebughook(HSQUIRRELVM v,SQDEBUGHOOK hook);

/*UTILITY MACRO*/
#define sq_isnumeric(o) ((o)._type&SQOBJECT_NUMERIC)
#define sq_istable(o) ((o)._type==OT_TABLE)
#define sq_isarray(o) ((o)._type==OT_ARRAY)
#define sq_isfunction(o) ((o)._type==OT_FUNCPROTO)
#define sq_isclosure(o) ((o)._type==OT_CLOSURE)
#define sq_isgenerator(o) ((o)._type==OT_GENERATOR)
#define sq_isnativeclosure(o) ((o)._type==OT_NATIVECLOSURE)
#define sq_isstring(o) ((o)._type==OT_STRING)
#define sq_isinteger(o) ((o)._type==OT_INTEGER)
#define sq_isfloat(o) ((o)._type==OT_FLOAT)
#define sq_isuserpointer(o) ((o)._type==OT_USERPOINTER)
#define sq_isuserdata(o) ((o)._type==OT_USERDATA)
#define sq_isthread(o) ((o)._type==OT_THREAD)
#define sq_isnull(o) ((o)._type==OT_NULL)
#define sq_isclass(o) ((o)._type==OT_CLASS)
#define sq_isinstance(o) ((o)._type==OT_INSTANCE)
#define sq_isbool(o) ((o)._type==OT_BOOL)
#define sq_isweakref(o) ((o)._type==OT_WEAKREF)
#define sq_type(o) ((o)._type)

/* deprecated */
#define sq_createslot(v,n) sq_newslot(v,n,SQFalse)

#define SQ_OK (0)
#define SQ_ERROR (-1)

#define SQ_FAILED(res) (res<0)
#define SQ_SUCCEEDED(res) (res>=0)

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_SQUIRREL_H_*/

// <--- back to xsquirrel.h


// Implemented on user side
void xsq_print( const char *msg );
void xsq_error( const char *err );
bool xsq_getfile( const char *path, std::vector<unsigned char> &data );
unsigned long long xsq_getfiletime( const char *path );




#define XSQ_STRUCT(name,sqname,st)							\
	struct name {											\
		st													\
		static const char *_name() { return #name; }		\
		static const char *_name_sq() { return sqname; }	\
		static const char *_member_list() { return #st; }	\
	}; \
	namespace sqb \
	{ \
		template<> struct TypeInfo<name> \
		{ \
			enum \
			{ \
				kTypeID = kScriptVarTypeObject, \
				kTypeSize = sizeof(name), \
				kTypeMask = '.', \
				kTypeIsInstance = SQFalse, \
			}; \
			const SQChar *m_typeName; \
			inline TypeInfo() : m_typeName(_SC(sqname)) \
			{ \
			} \
			inline operator ScriptVarType() const \
			{ \
				return static_cast<ScriptVarType>(kTypeID); \
			} \
		}; \
		template<> inline bool Match<name>(TypeWrapper<name>, HSQUIRRELVM vm, SQInteger idx)					{ return true; } \
		template<> inline bool Match<name &>(TypeWrapper<name &>, HSQUIRRELVM vm, SQInteger idx)				{ return true; } \
		template<> inline bool Match<const name &>(TypeWrapper<const name &>, HSQUIRRELVM vm, SQInteger idx)	{ return true; } \
		template<> inline name &Get<name>(TypeWrapper<name>, HSQUIRRELVM vm, SQInteger idx) \
		{ \
			SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm); \
			static name value; \
			value = name(); \
			sqvm.xsq_struct_get(&value,#st,idx); \
			return value; \
		} \
		template<> inline SQRESULT Push<name>(HSQUIRRELVM vm, name &value) \
		{ \
			SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm); \
			return sqvm._sq_push(value); \
		} \
		template<> inline SQRESULT Push<name>(HSQUIRRELVM vm, const name &value) \
		{ \
			SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm); \
			return sqvm._sq_push(value); \
		} \
	}




// ---------------- register internals ----------------

class __xsq_register {
public:
	static std::vector<void (*)(HSQUIRRELVM)> &regs()
	{
		static std::vector<void (*)(HSQUIRRELVM)> _regs;
		return _regs;
	}

	static void add(void (*fn)(HSQUIRRELVM))
	{
		regs().push_back(fn);
	}
};



class SqRef;




class SqVM {
public:
	enum {
		LIB_BLOB	= (1<<0),
		LIB_IO		= (1<<1),
		LIB_MATH	= (1<<2),
		LIB_STRING	= (1<<3),
		LIB_SYSTEM	= (1<<4),

		CHECK_RUN_MODIFIED				= 0,
		CHECK_RUN_ALL					= 1,
		CHECK_RUN_MODIFIED_AND_LATER	= 2,
	};


	SqVM() : vm(NULL), first_free_handle(NULL), first_busy_handle(NULL), last_stack_size(1024) {}
	~SqVM() { DeInit(); }

	void Init(int stack_size = 1024,int libflags=LIB_BLOB|LIB_MATH|LIB_STRING);
	void DeInit();
	void Reset();

	bool DoFile(const char *path);
	bool DoString(const char *code);

	bool AddFile(const char *path);
	int  CheckFiles(int check_mode=CHECK_RUN_MODIFIED);

	void RunGC()	{ sq_collectgarbage(vm); }

	HSQUIRRELVM operator ()() { return vm; }



	template<class T>
	T Get(const char *name)
	{
		T out = T();
		int top = sq_gettop(vm);
		sq_pushroottable(vm);
		sq_pushstring(vm,name,-1);
		if(SQ_SUCCEEDED(sq_get(vm,-2)))
			_sq_get(out,-1);
		sq_settop(vm,top);
		return out;
	}

	template<class T>
	bool Get(const char *name,T &out)
	{
		bool ok = false;
		int top = sq_gettop(vm);
		sq_pushroottable(vm);
		sq_pushstring(vm,name,-1);
		if(SQ_SUCCEEDED(sq_get(vm,-2)))
			ok = _sq_get(out,-1);
		else
			out = out();
		sq_settop(vm,top);
		return ok;
	}

	int			GetInt(const char *name)	{ return Get<int>(name); }
	float		GetFloat(const char *name)	{ return Get<float>(name); }
	std::string	GetString(const char *name)	{ return Get<std::string>(name); }
	SqRef		GetObj(const char *name);


	template<class T>
	bool Set(const char *name,const T v)
	{
		bool ok = false;
		int top = sq_gettop(vm);
		sq_pushroottable(vm);
		sq_pushstring(vm,name,-1);
		if(_sq_push(v)==1 && SQ_SUCCEEDED(sq_newslot(vm,-3,false)))
			ok = true;
		sq_settop(vm,top);
		return ok;
	}

	template<class T> SqRef ToObject(const T v);
	SqRef NewTable();


	//template<class A1>
	//bool Run(const char *fn,A1 a1)
	//{
	//	int top = sq_gettop(vm);
	//	sq_pushroottable(vm);
	//	sq_pushstring(vm,fn,-1);
	//	if(SQ_SUCCEEDED(sq_get(vm,-2)))
	//	{
	//		sq_pushroottable(vm); //push the 'this' (in this case is the global table)
	//		sq_pushinteger(vm,n); 
	//		sq_pushfloat(vm,f);
	//		sq_pushstring(vm,s,-1);
	//		sq_call(vm,4,0,0);
	//	}
	//	sq_settop(vm,top); //restores the original stack size
	//}
#define T		template<
#define C(n)	class T##n
#define FN		bool Run(const char *fn
#define A(n)	,const T##n a##n
#define CODE	) { int args=1, top=sq_gettop(vm); bool ok=false; sq_pushroottable(vm); sq_pushstring(vm,fn,-1); if(SQ_SUCCEEDED(sq_get(vm,-2))) { sq_pushroottable(vm);
#define P(n)	args+=_sq_push(a##n);
#define END		ok=SQ_SUCCEEDED(sq_call(vm,args,false,true)); } sq_settop(vm,top); return ok; }
	FN CODE END
	T C(1) > FN A(1) CODE P(1) END
	T C(1),C(2) > FN A(1) A(2) CODE P(1) P(2) END
	T C(1),C(2),C(3) > FN A(1) A(2) A(3) CODE P(1) P(2) P(3) END
	T C(1),C(2),C(3),C(4) > FN A(1) A(2) A(3) A(4) CODE P(1) P(2) P(3) P(4) END
	T C(1),C(2),C(3),C(4),C(5) > FN A(1) A(2) A(3) A(4) A(5) CODE P(1) P(2) P(3) P(4) P(5) END
#undef T
#undef C
#undef FN	
#undef A
#undef CODE	
#undef P
#undef END	

#define T		template<class R
#define C(n)	class T##n
#define FN		R RunRet(const char *fn
#define A(n)	,const T##n a##n
#define CODE	) { int args=1, top=sq_gettop(vm); sq_pushroottable(vm); sq_pushstring(vm,fn,-1); if(SQ_SUCCEEDED(sq_get(vm,-2))) { sq_pushroottable(vm);
#define P(n)	args+=_sq_push(a##n);
#define END		sq_call(vm,args,true,true); R ret = R(); _sq_get(ret,-1); sq_settop(vm,top); return ret; } sq_settop(vm,top); return R(); }
	T > FN CODE END
	T ,C(1) > FN A(1) CODE P(1) END
	T ,C(1),C(2) > FN A(1) A(2) CODE P(1) P(2) END
	T ,C(1),C(2),C(3) > FN A(1) A(2) A(3) CODE P(1) P(2) P(3) END
	T ,C(1),C(2),C(3),C(4) > FN A(1) A(2) A(3) A(4) CODE P(1) P(2) P(3) P(4) END
	T ,C(1),C(2),C(3),C(4),C(5) > FN A(1) A(2) A(3) A(4) A(5) CODE P(1) P(2) P(3) P(4) P(5) END
#undef T
#undef C
#undef FN	
#undef A
#undef CODE	
#undef P
#undef END	

private:
	friend class SqRef;
	friend class ObjectHandle;
	friend SqRef &__xsqbind_sqref_get(SQVM *vm,int index);


	class ObjectHandle {
	public:
		SqVM			*vm;
		int				refcount;
		HSQOBJECT		hobj;
		ObjectHandle	*next;
		ObjectHandle	*prev;

		ObjectHandle(SqVM &_vm);

	private:
		friend class SqVM;
		friend class SqRef;

		void Free();	// called after losing last reference

		ObjectHandle();							// disabled
		ObjectHandle(const ObjectHandle &);		// disabled
		void operator =(const ObjectHandle &);	// disabled
	};

	struct ScriptFile {
		std::string			path;
		unsigned long long	timestamp;
	};

	HSQUIRRELVM				vm;
	ObjectHandle			*first_free_handle;
	ObjectHandle			*first_busy_handle;
	std::vector<ScriptFile>	script_files;
	int						last_stack_size;


	static void print_callback(HSQUIRRELVM vm, const SQChar *format, ...);
	static void print_error_callback(HSQUIRRELVM vm, const SQChar *format, ...);
	static void print_stack_trace(HSQUIRRELVM vm);
	static SQInteger print_runtime_error(HSQUIRRELVM vm);
	static void print_compile_error(HSQUIRRELVM vm, const SQChar* description, const SQChar* file, SQInteger line, SQInteger column);

	bool getstackobj(SqRef &out,int index);

public:
	template<class T>	int _sq_push(T a)					{ return xsq_struct_push(&a,T::_member_list()); }
	template<class T>	bool _sq_get(T &out,int depth)		{ return xsq_struct_get(&out,T::_member_list(),depth); }

	int xsq_struct_push(const void *st,const char *members);
	bool xsq_struct_get(void *st,const char *members,int depth);

private:

	SqVM(const SqVM &);				// disabled
	void operator =(const SqVM &);	// disabled
};




class SqRef {
public:
	SqRef() : handle(NULL) { }
	SqRef(const SqRef &r) : handle(r.handle) { if(handle) handle->refcount++; }

	void operator =(const SqRef &r)
	{
		if(handle && !--(handle->refcount))
			handle->Free();
		handle = r.handle;
		if(handle) handle->refcount++;
	}

	bool operator ==(const SqRef &r) const	{ return handle==r.handle; }
	bool operator !() const					{ return !handle; }

	void clear_ref()
	{
		if(handle && !--(handle->refcount))
			handle->Free();
		handle = NULL;
	}

	void *GetPointer()
	{
		if(!handle) return NULL;
		if(handle->hobj._type==OT_NULL) return NULL;
		return handle->hobj._unVal.pTable;
	}

	template<class T>
	T Get(const char *name)
	{
		int top = _get_base(name);
		if(top==int(0x8000000))
			return T();
		T out = T();
		handle->vm->_sq_get(out,-1);
		sq_settop(handle->vm->vm,top);
		return out;
	}

	template<class T>
	bool Get(const char *name,T &out)
	{
		int top = _get_base(name);
		if(top==int(0x8000000))
		{
			out = T();
			return false;
		}
		handle->vm->_sq_get(out,-1);
		sq_settop(handle->vm->vm,top);
		return true;
	}

	int			GetInt(const char *name)	{ return Get<int>(name); }
	float		GetFloat(const char *name)	{ return Get<float>(name); }
	std::string	GetString(const char *name)	{ return Get<std::string>(name); }
	SqRef		GetObj(const char *name)	{ return Get<SqRef>(name); }

	template<class T>
	bool Set(const char *name,const T v)
	{
		int top = _set_base(name);
		if(top==int(0x8000000))
			return false;
		bool ok = false;
		if(handle->vm->_sq_push(v)==1 && SQ_SUCCEEDED(sq_newslot(handle->vm->vm,-3,false)))
			ok = true;
		sq_settop(handle->vm->vm,top);
		return ok;
	}

	//template<class A1>
	//bool Run(const char *fn,A1 a1)
	//{
	//	int top = sq_gettop(vm);
	//	sq_pushroottable(vm);
	//	sq_pushstring(vm,fn,-1);
	//	if(SQ_SUCCEEDED(sq_get(vm,-2)))
	//	{
	//		sq_pushroottable(vm); //push the 'this' (in this case is the global table)
	//		sq_pushinteger(vm,n); 
	//		sq_pushfloat(vm,f);
	//		sq_pushstring(vm,s,-1);
	//		sq_call(vm,4,0,0);
	//	}
	//	sq_settop(vm,top); //restores the original stack size
	//}
#define T		template<
#define C(n)	class T##n
#define FN		bool Run(const char *fn
#define A(n)	,const T##n a##n
#define CODE	) { if(!handle || !handle->vm) return false;	\
					HSQUIRRELVM vm = handle->vm->vm;			\
					int args=1, top=sq_gettop(vm);				\
					bool ok=false; sq_pushobject(vm,handle->hobj); sq_pushstring(vm,fn,-1); if(SQ_SUCCEEDED(sq_get(vm,-2))) { sq_pushobject(vm,handle->hobj);
#define P(n)	args+=handle->vm->_sq_push(a##n);
#define END		ok=SQ_SUCCEEDED(sq_call(vm,args,false,true)); } sq_settop(vm,top); return ok; }
	FN CODE END
	T C(1) > FN A(1) CODE P(1) END
	T C(1),C(2) > FN A(1) A(2) CODE P(1) P(2) END
	T C(1),C(2),C(3) > FN A(1) A(2) A(3) CODE P(1) P(2) P(3) END
	T C(1),C(2),C(3),C(4) > FN A(1) A(2) A(3) A(4) CODE P(1) P(2) P(3) P(4) END
	T C(1),C(2),C(3),C(4),C(5) > FN A(1) A(2) A(3) A(4) A(5) CODE P(1) P(2) P(3) P(4) P(5) END
#undef T
#undef C
#undef FN	
#undef A
#undef CODE	
#undef P
#undef END	

#define T		template<class R
#define C(n)	class T##n
#define FN		R RunRet(const char *fn
#define A(n)	,const T##n a##n
#define CODE	) { if(!handle || !handle->vm) return R();		\
					HSQUIRRELVM vm = handle->vm->vm;			\
					int args=1, top=sq_gettop(vm);				\
					bool ok=false; sq_pushobject(vm,handle->hobj); sq_pushstring(vm,fn,-1); if(SQ_SUCCEEDED(sq_get(vm,-2))) { sq_pushobject(vm,handle->hobj);
#define P(n)	args+=handle->vm->_sq_push(a##n);
#define END		sq_call(vm,args,true,true); R ret = R(); handle->vm->_sq_get(ret,-1); sq_settop(vm,top); return ret; } sq_settop(vm,top); return R(); }
	T > FN CODE END
	T ,C(1) > FN A(1) CODE P(1) END
	T ,C(1),C(2) > FN A(1) A(2) CODE P(1) P(2) END
	T ,C(1),C(2),C(3) > FN A(1) A(2) A(3) CODE P(1) P(2) P(3) END
	T ,C(1),C(2),C(3),C(4) > FN A(1) A(2) A(3) A(4) CODE P(1) P(2) P(3) P(4) END
	T ,C(1),C(2),C(3),C(4),C(5) > FN A(1) A(2) A(3) A(4) A(5) CODE P(1) P(2) P(3) P(4) P(5) END
#undef T
#undef C
#undef FN	
#undef A
#undef CODE	
#undef P
#undef END	


private:
	friend class SqVM;
	friend int __xsqbind_sqref_push(SQVM *vm,SqRef &ref);

	SqVM::ObjectHandle	*handle;

	int _get_base(const char *name);
	int _set_base(const char *name);

	void set_ref(SqVM::ObjectHandle *h)
	{
		if(handle && !--(handle->refcount))
			handle->Free();
		handle = h;
		if(handle) handle->refcount++;
	}
};



inline SqRef SqVM::GetObj(const char *name) { return Get<SqRef>(name); }

template<class T>
SqRef SqVM::ToObject(const T v)
{
	bool ok = false;
	SqRef ref;
	int top = sq_gettop(vm);
	if(_sq_push(v)==1 && getstackobj(ref,-1))
		ok = true;
	sq_settop(vm,top);
	return ref;
}

inline SqRef SqVM::NewTable()
{
	SqRef ref;
	int top = sq_gettop(vm);
	sq_newtable(vm);
	getstackobj(ref,-1);
	sq_settop(vm,top);
	return ref;
}



template<>	inline		int SqVM::_sq_push(const int a)			{ sq_pushinteger(vm,a);				return 1; }
template<>	inline		int SqVM::_sq_push(const float a)		{ sq_pushfloat(vm,a);				return 1; }
template<>	inline		int SqVM::_sq_push(const char *a)		{ sq_pushstring(vm,a,-1);			return 1; }
template<>	inline		int SqVM::_sq_push(const std::string a)	{ sq_pushstring(vm,a.c_str(),-1);	return 1; }
template<>	inline		int SqVM::_sq_push(std::string *a)		{ sq_pushstring(vm,a->c_str(),-1);	return 1; }
template<>	inline		int SqVM::_sq_push(SqRef a)				{ if(a.handle) sq_pushobject(vm,a.handle->hobj); else sq_pushnull(vm);	return 1; }

template<>	inline		bool SqVM::_sq_get(int &out,int depth) {
							SQInteger i;
							if(SQ_FAILED(sq_getinteger(vm,depth,&i)))	{ out=0; return false; }
							out = i;
							return true;
						}
template<>	inline		bool SqVM::_sq_get(float &out,int depth)		{ if(SQ_FAILED(sq_getfloat(vm,depth,&out)))	{ out=0; return false; } return true; }
template<>				bool SqVM::_sq_get(std::string &out,int depth);
template<>	inline		bool SqVM::_sq_get(SqRef &out,int depth)		{ return getstackobj(out,depth); }


#ifdef XSQ_VEC2
template<> inline int SqVM::_sq_push(XSQ_VEC2 v)
{
	int top=sq_gettop(vm);
	bool ok=false;
	sq_pushroottable(vm);
	sq_pushstring(vm, "vec2", -1);
	if( SQ_SUCCEEDED(sq_get(vm, -2)) )
	{
		sq_pushroottable(vm);
		_sq_push(v.x);
		_sq_push(v.y);
		if( SQ_SUCCEEDED(sq_call(vm, 3, true, true)) )
		{
								// roottable, closure, value
			sq_remove(vm,-2);	// roottable, value
			sq_remove(vm,-2);	// value
			ok = true;
		}
	}
	if(!ok)
		sq_settop( vm, top );
	return ok ? 1 : 0;
}
#endif

#ifdef XSQ_VEC3
template<> inline int SqVM::_sq_push(XSQ_VEC3 v)
{
	int top=sq_gettop(vm);
	bool ok=false;
	sq_pushroottable(vm);
	sq_pushstring(vm, "vec3", -1);
	if( SQ_SUCCEEDED(sq_get(vm, -2)) )
	{
		sq_pushroottable(vm);
		_sq_push(v.x);
		_sq_push(v.y);
		_sq_push(v.z);
		if( SQ_SUCCEEDED(sq_call(vm, 4, true, true)) )
		{
								// roottable, closure, value
			sq_remove(vm,-2);	// roottable, value
			sq_remove(vm,-2);	// value
			ok = true;
		}
	}
	if(!ok)
		sq_settop( vm, top );
	return ok ? 1 : 0;
}
#endif

#ifdef XSQ_VEC2
template<> inline bool SqVM::_sq_get(XSQ_VEC2 &out,int depth)
{
	int top = sq_gettop(vm);
	if(depth<0) depth = top + depth + 1;

	do {
	
		sq_pushstring(vm, "___immutable_x", -1);
		if( SQ_FAILED(sq_get(vm, depth)) ) break;
		if( SQ_FAILED(sq_getfloat(vm,-1,&out.x))) break;

		sq_pushstring(vm, "___immutable_y", -1);
		if( SQ_FAILED(sq_get(vm, depth)) ) break;
		if( SQ_FAILED(sq_getfloat(vm,-1,&out.y))) break;

		sq_settop( vm, top );
		return true;

	} while(0);

	out.x = out.y = 0;

	sq_settop( vm, top );
	return false;
}
#endif

#ifdef XSQ_VEC3
template<> inline bool SqVM::_sq_get(XSQ_VEC3 &out,int depth)
{
	int top = sq_gettop(vm);
	int d0 = depth;
	if(depth<0) depth = top + depth + 1;

	do {
	
		sq_pushstring(vm, "___immutable_x", -1);
		if( SQ_FAILED(sq_get(vm, depth)) ) break;
		if( SQ_FAILED(sq_getfloat(vm,-1,&out.x))) break;

		sq_pushstring(vm, "___immutable_y", -1);
		if( SQ_FAILED(sq_get(vm, depth)) ) break;
		if( SQ_FAILED(sq_getfloat(vm,-1,&out.y))) break;

		sq_pushstring(vm, "___immutable_z", -1);
		if( SQ_FAILED(sq_get(vm, depth)) ) break;
		if( SQ_FAILED(sq_getfloat(vm,-1,&out.z))) break;

		sq_settop( vm, top );
		return true;

	} while(0);

	out.x = out.y = out.z = 0;

	sq_settop( vm, top );
	return false;
}
#endif



#endif

// <--- back to _xsquirrel.cpp
// ---- #include "sqstdio.h"
// ---> including sqstdio.h
/*	see copyright notice in squirrel.h */
#ifndef _SQSTDIO_H_
#define _SQSTDIO_H_

#ifdef __cplusplus

#define SQSTD_STREAM_TYPE_TAG 0x80000000

struct SQStream {
	virtual SQInteger Read(void *buffer, SQInteger size) = 0;
	virtual SQInteger Write(void *buffer, SQInteger size) = 0;
	virtual SQInteger Flush() = 0;
	virtual SQInteger Tell() = 0;
	virtual SQInteger Len() = 0;
	virtual SQInteger Seek(SQInteger offset, SQInteger origin) = 0;
	virtual bool IsValid() = 0;
	virtual bool EOS() = 0;
};

extern "C" {
#endif

#define SQ_SEEK_CUR 0
#define SQ_SEEK_END 1
#define SQ_SEEK_SET 2

typedef void* SQFILE;

SQUIRREL_API SQFILE sqstd_fopen(const SQChar *,const SQChar *);
SQUIRREL_API SQInteger sqstd_fread(SQUserPointer, SQInteger, SQInteger, SQFILE);
SQUIRREL_API SQInteger sqstd_fwrite(const SQUserPointer, SQInteger, SQInteger, SQFILE);
SQUIRREL_API SQInteger sqstd_fseek(SQFILE , SQInteger , SQInteger);
SQUIRREL_API SQInteger sqstd_ftell(SQFILE);
SQUIRREL_API SQInteger sqstd_fflush(SQFILE);
SQUIRREL_API SQInteger sqstd_fclose(SQFILE);
SQUIRREL_API SQInteger sqstd_feof(SQFILE);

SQUIRREL_API SQRESULT sqstd_createfile(HSQUIRRELVM v, SQFILE file,SQBool own);
SQUIRREL_API SQRESULT sqstd_getfile(HSQUIRRELVM v, SQInteger idx, SQFILE *file);

//compiler helpers
SQUIRREL_API SQRESULT sqstd_loadfile(HSQUIRRELVM v,const SQChar *filename,SQBool printerror);
SQUIRREL_API SQRESULT sqstd_dofile(HSQUIRRELVM v,const SQChar *filename,SQBool retval,SQBool printerror);
SQUIRREL_API SQRESULT sqstd_writeclosuretofile(HSQUIRRELVM v,const SQChar *filename);

SQUIRREL_API SQRESULT sqstd_register_iolib(HSQUIRRELVM v);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_SQSTDIO_H_*/


// <--- back to _xsquirrel.cpp
// ---- #include "sqstdmath.h"
// ---> including sqstdmath.h
/*	see copyright notice in squirrel.h */
#ifndef _SQSTD_MATH_H_
#define _SQSTD_MATH_H_

#ifdef __cplusplus
extern "C" {
#endif

SQUIRREL_API SQRESULT sqstd_register_mathlib(HSQUIRRELVM v);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_SQSTD_MATH_H_*/

// <--- back to _xsquirrel.cpp
// ---- #include "sqstdstring.h"
// ---> including sqstdstring.h
/*	see copyright notice in squirrel.h */
#ifndef _SQSTD_STRING_H_
#define _SQSTD_STRING_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int SQRexBool;
typedef struct SQRex SQRex;

typedef struct {
	const SQChar *begin;
	SQInteger len;
} SQRexMatch;

SQUIRREL_API SQRex *sqstd_rex_compile(const SQChar *pattern,const SQChar **error);
SQUIRREL_API void sqstd_rex_free(SQRex *exp);
SQUIRREL_API SQBool sqstd_rex_match(SQRex* exp,const SQChar* text);
SQUIRREL_API SQBool sqstd_rex_search(SQRex* exp,const SQChar* text, const SQChar** out_begin, const SQChar** out_end);
SQUIRREL_API SQBool sqstd_rex_searchrange(SQRex* exp,const SQChar* text_begin,const SQChar* text_end,const SQChar** out_begin, const SQChar** out_end);
SQUIRREL_API SQInteger sqstd_rex_getsubexpcount(SQRex* exp);
SQUIRREL_API SQBool sqstd_rex_getsubexp(SQRex* exp, SQInteger n, SQRexMatch *subexp);

SQUIRREL_API SQRESULT sqstd_format(HSQUIRRELVM v,SQInteger nformatstringidx,SQInteger *outlen,SQChar **output);

SQUIRREL_API SQRESULT sqstd_register_stringlib(HSQUIRRELVM v);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_SQSTD_STRING_H_*/

// <--- back to _xsquirrel.cpp
// ---- #include "sqstdblob.h"
// ---> including sqstdblob.h
/*	see copyright notice in squirrel.h */
#ifndef _SQSTDBLOB_H_
#define _SQSTDBLOB_H_

#ifdef __cplusplus
extern "C" {
#endif

SQUIRREL_API SQUserPointer sqstd_createblob(HSQUIRRELVM v, SQInteger size);
SQUIRREL_API SQRESULT sqstd_getblob(HSQUIRRELVM v,SQInteger idx,SQUserPointer *ptr);
SQUIRREL_API SQInteger sqstd_getblobsize(HSQUIRRELVM v,SQInteger idx);

SQUIRREL_API SQRESULT sqstd_register_bloblib(HSQUIRRELVM v);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_SQSTDBLOB_H_*/


// <--- back to _xsquirrel.cpp
// ---- #include "sqstdsystem.h"
// ---> including sqstdsystem.h
/*	see copyright notice in squirrel.h */
#ifndef _SQSTD_SYSTEMLIB_H_
#define _SQSTD_SYSTEMLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

SQUIRREL_API SQInteger sqstd_register_systemlib(HSQUIRRELVM v);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* _SQSTD_SYSTEMLIB_H_ */

// <--- back to _xsquirrel.cpp


// -------------------------------- helper macros --------------------------------


#define __IS_RANGE(x,a,b)		( (x)>=(a) && (x)<=(b) )
#define __IS_ALPHA(x)			( __IS_RANGE((x),'a','z') || __IS_RANGE((x),'A','Z') )
#define __IS_NUM(x)				__IS_RANGE((x),'0','9')
#define __IS_IDENT_START(x)		( __IS_ALPHA(x) || ((x)=='_') )
#define __IS_IDENT_CHAR(x)		( __IS_ALPHA(x) || __IS_NUM(x) || ((x)=='_') )




// -------------------------------- helper functions --------------------------------


static void _parse_white(const char *&s)
{
	while(*s==' ' || *s=='\t' || *s=='\n' || *s=='\r') s++;
}


static bool _parse_ident(const char *&s,string &out)
{
	_parse_white(s);
	if(!__IS_IDENT_START(*s))
	{
		out.clear();
		return false;
	}
	const char *b = s++;
	while(__IS_IDENT_CHAR(*s)) s++;
	out.assign(b,s);
	return true;
}



// -------------------------------- _sq_get/_sq_push template specializations --------------------------------


template<> bool SqVM::_sq_get(std::string &out,int depth)
{
	if(SQ_FAILED(sq_tostring(vm,depth)))
	{
		out.clear();
		return false;
	}
	const char *s=NULL;
	if(SQ_FAILED(sq_getstring(vm,-1,&s)) || !s)
	{
		out.clear();
		sq_remove(vm,-1);
		return false;
	}
	out=s;
	sq_remove(vm,-1);
	return true;
}







// -------------------------------- SqRef --------------------------------


int SqRef::_get_base(const char *name)
{
	if(!handle || !handle->vm)
		return int(0x8000000);
	HSQUIRRELVM vm = handle->vm->vm;
	int top = sq_gettop(vm);
	sq_pushobject(vm,handle->hobj);
	sq_pushstring(vm,name,-1);
	if(SQ_SUCCEEDED(sq_get(vm,-2)))
		return top;
	sq_settop(vm,top);
	return int(0x8000000);
}

int SqRef::_set_base(const char *name)
{
	if(!handle || !handle->vm)
		return int(0x8000000);
	HSQUIRRELVM vm = handle->vm->vm;
	int top = sq_gettop(vm);
	sq_pushobject(vm,handle->hobj);
	sq_pushstring(vm,name,-1);
	return top;
}




// -------------------------------- ObjectHandle --------------------------------


SqVM::ObjectHandle::ObjectHandle(SqVM &_vm) : vm(&_vm), refcount(0)
{
	sq_resetobject(&hobj);

	next = vm->first_free_handle;
	prev = NULL;
	vm->first_free_handle = this;
}

void SqVM::ObjectHandle::Free()
{
	if(vm)
	{
		sq_release(vm->vm,&hobj);

		// just to be sure
		sq_resetobject(&hobj);
		refcount = 0;
	}

	// unbind from the busy list
	if(next)	next->prev = prev;
	if(prev)	prev->next = next;
	else if(vm)	vm->first_busy_handle = next;

	// bind to free list (delete self if VM no longer exists)
	if(!vm)
	{
		delete this;
		return;
	}
	next = vm->first_free_handle;
	prev = NULL;
	vm->first_free_handle = this;
}






// -------------------------------- SqVM --------------------------------


void SqVM::print_callback(HSQUIRRELVM vm, const SQChar *fmt, ...)
{
	std::string out;

	va_list arg;
	
	va_start(arg,fmt);
	int len = vsnprintf(NULL,0,fmt,arg) + 1;
	out.resize(len);
	va_end(arg);
	
	va_start(arg,fmt);
	vsnprintf((char*)out.data(),len,fmt,arg);
	out.resize(len-1);

	va_end(arg);

	xsq_print(out.c_str());
}

void SqVM::print_error_callback(HSQUIRRELVM vm, const SQChar *fmt, ...)
{
	std::string out;

	va_list arg;
	
	va_start(arg,fmt);
	int len = vsnprintf(NULL,0,fmt,arg) + 1;
	out.resize(len);
	va_end(arg);
	
	va_start(arg,fmt);
	vsnprintf((char*)out.data(),len,fmt,arg);
	out.resize(len-1);
	va_end(arg);

	xsq_error(out.c_str());
}


void SqVM::print_stack_trace(HSQUIRRELVM vm)
{
    SQStackInfos stack_info;
    SQInteger stack_depth = 1;
 
    print_error_callback(vm,"  Stack Dump:\n");
    while( SQ_SUCCEEDED(sq_stackinfos(vm,stack_depth,&stack_info)) )
	{
        const SQChar *func_name = (stack_info.funcname) ? stack_info.funcname : "???";
        const SQChar *source_file = (stack_info.source) ? stack_info.source : "???";
        print_error_callback(vm,"    %2d: %s (%s:%d)\n", stack_depth, func_name, source_file, stack_info.line);
        stack_depth++;
    }
}
 
SQInteger SqVM::print_runtime_error(HSQUIRRELVM vm)
{
    const SQChar* error_message = NULL;
    if(sq_gettop(vm) >= 1)
	{
        if(SQ_SUCCEEDED(sq_getstring(vm,2,&error_message)))
            print_error_callback(vm,"Script runtime error: %s.\n", error_message);
        print_stack_trace(vm);
    }
    return 0;
}
 
void SqVM::print_compile_error(HSQUIRRELVM vm, const SQChar* description, const SQChar* file, SQInteger line, SQInteger column)
{
    print_error_callback(vm,"Script compile error: %s:%d:%d : %s.\n", file, line, column, description);
}




void SqVM::Init(int stack_size,int libflags)
{
	last_stack_size = stack_size;

	DeInit();
	if(vm) sq_close(vm);

    vm = sq_open(stack_size);
	sq_setforeignptr(vm,this);

    sq_setprintfunc(vm, print_callback, print_error_callback);
    sq_setcompilererrorhandler(vm, print_compile_error);
    sq_newclosure(vm, print_runtime_error, 0);
    sq_seterrorhandler(vm);

	if( libflags & LIB_MATH		)	{ sq_pushroottable(vm);		sqstd_register_mathlib(vm);		}
	if( libflags & LIB_STRING	)	{ sq_pushroottable(vm);		sqstd_register_stringlib(vm);	}
	if( libflags & LIB_BLOB		)	{ sq_pushroottable(vm);		sqstd_register_bloblib(vm);		}
	if( libflags & LIB_IO		)	{ sq_pushroottable(vm);		sqstd_register_iolib(vm);		}
	if( libflags & LIB_SYSTEM	)	{ sq_pushroottable(vm);		sqstd_register_systemlib(vm);	}

	for(int i=0;i<(int)__xsq_register::regs().size();i++)
		__xsq_register::regs()[i](vm);
}

void SqVM::DeInit()
{
	// delete free handles
	ObjectHandle *h = first_free_handle;
	while(h)
	{
		ObjectHandle *n = h->next;
		delete h;
		h = n;
	}
	first_free_handle = NULL;

	// unbind busy handles
	h = first_busy_handle;
	while(h)
	{
		h->vm = NULL;
		h = h->next;
	}
	first_busy_handle = NULL;

	// close VM
	if(vm) sq_close(vm);
	vm = 0;

	script_files.clear();
}

void SqVM::Reset()
{
	vector<ScriptFile> files = script_files;

	Init(last_stack_size);
	for(int i=0;i<(int)files.size();i++)
		AddFile(files[i].path.c_str());
}



bool SqVM::DoFile(const char *path)
{
    sq_pushroottable(vm);
    if(SQ_FAILED(sqstd_dofile(vm, path, 0, 1)))
    {
		sq_pop(vm,1);
		return false;
    }
    sq_pop(vm,1);
	return true;
}

bool SqVM::DoString(const char *code)
{
    if(SQ_FAILED(sq_compilebuffer(vm, code, sizeof(SQChar)*strlen(code), "script", SQTrue)))
        return false;
 
    sq_pushroottable(vm);
    if (SQ_FAILED(sq_call(vm, 1, SQFalse, SQTrue)))
    {
		sq_pop(vm,1);
		return false;
    }
    sq_pop(vm,1);
	return true;
}

bool SqVM::AddFile(const char *path)
{
	ScriptFile sf;
	sf.path = path;
	sf.timestamp = xsq_getfiletime(path);
	for(int i=0;i<(int)script_files.size();i++)
		if(sf.path==script_files[i].path)
		{
			script_files[i].timestamp = sf.timestamp;
			sf.path.clear();
			break;
		}

	bool retval = DoFile(path);

	// add file after executing it, so files included will go before it
	if(sf.path.size()>0)
		script_files.push_back(sf);

	return retval;
}

int SqVM::CheckFiles(int check_mode)
{
	int n = 0;
	for(int i=0;i<(int)script_files.size();i++)
	{
		ScriptFile &sf = script_files[i];
		unsigned long long t = xsq_getfiletime(sf.path.c_str());
		if(t!=sf.timestamp)
		{
			if( check_mode!=CHECK_RUN_ALL )
				DoFile(sf.path.c_str());
			sf.timestamp = t;
			n++;
		}
		else if( n>0 && check_mode==CHECK_RUN_MODIFIED_AND_LATER )
		{
			DoFile(sf.path.c_str());	// run because earlier was ran
		}
	}

	if( n>0 && check_mode==CHECK_RUN_ALL )
	{
		for(int i=0;i<(int)script_files.size();i++)
			DoFile(script_files[i].path.c_str());
	}

	return n;
}



bool SqVM::getstackobj(SqRef &out,int index)
{
	HSQOBJECT hobj;
	if(SQ_FAILED(sq_getstackobj(vm,index,&hobj)))
	{
		out.clear_ref();
		return false;
	}

	// make sure there is free handle ready
	if(!first_free_handle)
		new ObjectHandle(*this);	// this should add itself to the free list

	// get target ObjectHandle
	ObjectHandle *target = first_free_handle;

	// remove from free list
	first_free_handle = first_free_handle->next;
	if(first_free_handle)
		first_free_handle->prev = NULL;

	// add to busy list
	target->next = first_busy_handle;
	target->prev = NULL;
	if(first_busy_handle)
		first_busy_handle->prev = target;

	// set object
	target->hobj = hobj;
	out.set_ref(target);
	sq_addref(vm,&hobj);

	return true;
}


int SqVM::xsq_struct_push(const void *st,const char *members)
{
	string type, name;

	if(!st || !members)
	{
		sq_pushnull(vm);
		return 1;
	}


	// create table
	sq_newtable(vm);
	
	const char *s = members;
	const char *src = (const char*)st;
	while(1)
	{
		if(!_parse_ident(s,type))
		{
			if(*s) print_error_callback(vm,"ERROR parsing structure: \"%s\"\n   at: %s\n",members,s);
			break;
		}
		if(!_parse_ident(s,name))
		{
			print_error_callback(vm,"ERROR parsing structure: \"%s\"\n   at: %s\n",members,s);
			break;
		}
		sq_pushstring(vm,name.c_str(),-1);
			 if(type=="int"		) { sq_pushinteger(vm,*(int*)src);					src+=sizeof(int);		}
		else if(type=="float"	) { sq_pushfloat(vm,*(float*)src);					src+=sizeof(float);		}
		else if(type=="string"	) { sq_pushstring(vm,((string*)src)->c_str(),-1);	src+=sizeof(string);	}
		else
		{
			print_error_callback(vm,"ERROR bad type '%s' in structure: \"%s\"\n",type.c_str(),members);
			sq_poptop(vm);	// remove name
			break;
		}

		if(!SQ_SUCCEEDED(sq_newslot(vm,-3,false)))
			print_error_callback(vm,"ERROR setting member '%s' in structure: \"%s\"\n",name.c_str(),members);

		_parse_white(s);
		if(*s!=';')
		{
			print_error_callback(vm,"ERROR parsing structure: \"%s\"\n   at: %s\n",members,s);
			break;
		}
		s++;
	}

	return 1;
}


bool SqVM::xsq_struct_get(void *st,const char *members,int depth)
{
	string type, name;

	if(!st || !members)
		return false;


	// gen elments
	int top = sq_gettop(vm);
	if(depth<0) depth = top + depth + 1;
	
	const char *s = members;
	const char *src = (const char*)st;
	while(1)
	{
		if(!_parse_ident(s,type))
		{
			if(*s) print_error_callback(vm,"ERROR parsing structure: \"%s\"\n   at: %s\n",members,s);
			return false;
		}
		if(!_parse_ident(s,name))
		{
			print_error_callback(vm,"ERROR parsing structure: \"%s\"\n   at: %s\n",members,s);
			return false;
		}
		sq_pushstring(vm,name.c_str(),-1);
		if(SQ_SUCCEEDED(sq_get(vm,depth)))
		{
				 if(type=="int"		) { _sq_get(*(int*)src,-1);			src+=sizeof(int);		}
			else if(type=="float"	) { _sq_get(*(float*)src,-1);		src+=sizeof(float);		}
			else if(type=="string"	) { _sq_get(*(string*)src,-1);		src+=sizeof(string);	}
			else
			{
				print_error_callback(vm,"ERROR bad type '%s' in structure: \"%s\"\n",type.c_str(),members);
				sq_poptop(vm);	// remove value
				return false;
			}
			sq_poptop(vm);	// remove value
		}
		else
		{
				 if(type=="int"		) { *(int*)src = 0;				src+=sizeof(int);		}
			else if(type=="float"	) { *(float*)src = 0;			src+=sizeof(float);		}
			else if(type=="string"	) { ((string*)src)->clear();	src+=sizeof(string);	}
			else
			{
				print_error_callback(vm,"ERROR bad type '%s' in structure: \"%s\"\n",type.c_str(),members);
				return false;
			}
		}


		_parse_white(s);
		if(*s!=';')
		{
			print_error_callback(vm,"ERROR parsing structure: \"%s\"\n   at: %s\n",members,s);
			return false;
		}
		s++;
	}

	return true;
}



#endif

// ******************************** _xsqio.cpp ********************************

#ifndef _XSQIO_CPP_DONE
#define _XSQIO_CPP_DONE



#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef SQBIND_STATIC
#define SQBIND_STATIC
#endif



#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <vector>
using namespace std;


// ---- #include "xsquirrel.h"
// ---> including xsquirrel.h
// <--- back to _xsqio.cpp
// ---- #include "sqstdio.h"
// ---> including sqstdio.h
// <--- back to _xsqio.cpp
// ---- #include "sqstdmath.h"
// ---> including sqstdmath.h
// <--- back to _xsqio.cpp
// ---- #include "sqstdstring.h"
// ---> including sqstdstring.h
// <--- back to _xsqio.cpp
// ---- #include "sqstdblob.h"
// ---> including sqstdblob.h
// <--- back to _xsqio.cpp



// internal file frapper
typedef void *XSQ_FILE;
struct XSqFile {
	vector<unsigned char> data;
	int fpos;
	bool eof;
	bool error;

	XSqFile() : fpos(0), eof(false), error(false) {}
};


SQFILE sqstd_fopen(const SQChar *filename ,const SQChar *mode)
{
#ifdef SQUNICODE
	#error Unicode not supported
#endif

	bool md_read = false;
	bool md_write = false;
	bool md_append= false;
	bool md_text = false;
	bool md_plus = false;

	while(*mode)
	{
		if(*mode=='r') md_read = true;
		if(*mode=='w') md_write = true;
		if(*mode=='a') md_append = true;
		if(*mode=='t') md_text = true;
		if(*mode=='+') md_plus = true;
		mode++;
	}

	// only pure read supported (with optional text mode)
	if(md_write || md_append || md_plus || !md_read) return NULL;

	XSqFile *f = new XSqFile();
	if(!xsq_getfile(filename,f->data))
	{
		delete f;
		return NULL;
	}

	// text mode read - remove all '\r'
	if(md_text)
	{
		int d = 0;
		for(int i=0;i<(int)f->data.size();i++)
			if(f->data[i]!='\r')
				f->data[d++] = f->data[i];
		f->data.resize(d);
	}

	return (SQFILE*)f;
}

SQInteger sqstd_fread(void* buffer, SQInteger size, SQInteger count, SQFILE fp)
{
	if(!fp) return 0;
	XSqFile *f = (XSqFile*)fp;

	int len = f->data.size() - f->fpos;
	if( len >= size*count )
		len = size*count;
	else
		f->eof = true;

	if(len>0)
	{
		memcpy(buffer,&f->data[f->fpos],len);
		f->fpos += len;
	}

	return len / size;
}

SQInteger sqstd_fwrite(const SQUserPointer buffer, SQInteger size, SQInteger count, SQFILE fp)
{
	return 0;	// TBD: unsupported
}

SQInteger sqstd_fseek(SQFILE fp, SQInteger offset, SQInteger origin)
{
	if(!fp) return 1;
	XSqFile *f = (XSqFile*)fp;
	long int newpos = -1;
	if(origin==SQ_SEEK_SET) newpos = offset;
	if(origin==SQ_SEEK_CUR) newpos = f->fpos + offset;
	if(origin==SQ_SEEK_END) newpos = f->data.size() + offset;
	if(newpos<0 || newpos>(int)f->data.size())
		return 1;
	f->fpos = newpos;
	f->eof = false;
	// ungetc character should be dropped, but none suported
	return 0;
}

SQInteger sqstd_ftell(SQFILE fp)
{
	if(!fp) return -1L;
	return ((XSqFile*)fp)->fpos;
}

SQInteger sqstd_fflush(SQFILE fp)
{
	return 0;	// TBD
}

SQInteger sqstd_fclose(SQFILE fp)
{
	if(!fp) return EOF;
	delete (XSqFile*)fp;
	return 0;
}

SQInteger sqstd_feof(SQFILE fp)
{
	if(!fp) return 0;
	return ((XSqFile*)fp)->eof ? 1 : 0;
}




#endif

// ******************************** sqstdaux.cpp ********************************
/* see copyright notice in squirrel.h */
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqstdaux.cpp
// ---- #include <sqstdaux.h>
// ---> including sqstdaux.h
/*	see copyright notice in squirrel.h */
#ifndef _SQSTD_AUXLIB_H_
#define _SQSTD_AUXLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

SQUIRREL_API void sqstd_seterrorhandlers(HSQUIRRELVM v);
SQUIRREL_API void sqstd_printcallstack(HSQUIRRELVM v);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* _SQSTD_AUXLIB_H_ */

// <--- back to sqstdaux.cpp
#include <assert.h>

void sqstd_printcallstack(HSQUIRRELVM v)
{
	SQPRINTFUNCTION pf = sq_geterrorfunc(v);
	if(pf) {
		SQStackInfos si;
		SQInteger i;
		SQFloat f;
		const SQChar *s;
		SQInteger level=1; //1 is to skip this function that is level 0
		const SQChar *name=0; 
		SQInteger seq=0;
		pf(v,_SC("\nCALLSTACK\n"));
		while(SQ_SUCCEEDED(sq_stackinfos(v,level,&si)))
		{
			const SQChar *fn=_SC("unknown");
			const SQChar *src=_SC("unknown");
			if(si.funcname)fn=si.funcname;
			if(si.source)src=si.source;
			pf(v,_SC("*FUNCTION [%s()] %s line [%d]\n"),fn,src,si.line);
			level++;
		}
		level=0;
		pf(v,_SC("\nLOCALS\n"));

		for(level=0;level<10;level++){
			seq=0;
			while((name = sq_getlocal(v,level,seq)))
			{
				seq++;
				switch(sq_gettype(v,-1))
				{
				case OT_NULL:
					pf(v,_SC("[%s] NULL\n"),name);
					break;
				case OT_INTEGER:
					sq_getinteger(v,-1,&i);
					pf(v,_SC("[%s] %d\n"),name,i);
					break;
				case OT_FLOAT:
					sq_getfloat(v,-1,&f);
					pf(v,_SC("[%s] %.14g\n"),name,f);
					break;
				case OT_USERPOINTER:
					pf(v,_SC("[%s] USERPOINTER\n"),name);
					break;
				case OT_STRING:
					sq_getstring(v,-1,&s);
					pf(v,_SC("[%s] \"%s\"\n"),name,s);
					break;
				case OT_TABLE:
					pf(v,_SC("[%s] TABLE\n"),name);
					break;
				case OT_ARRAY:
					pf(v,_SC("[%s] ARRAY\n"),name);
					break;
				case OT_CLOSURE:
					pf(v,_SC("[%s] CLOSURE\n"),name);
					break;
				case OT_NATIVECLOSURE:
					pf(v,_SC("[%s] NATIVECLOSURE\n"),name);
					break;
				case OT_GENERATOR:
					pf(v,_SC("[%s] GENERATOR\n"),name);
					break;
				case OT_USERDATA:
					pf(v,_SC("[%s] USERDATA\n"),name);
					break;
				case OT_THREAD:
					pf(v,_SC("[%s] THREAD\n"),name);
					break;
				case OT_CLASS:
					pf(v,_SC("[%s] CLASS\n"),name);
					break;
				case OT_INSTANCE:
					pf(v,_SC("[%s] INSTANCE\n"),name);
					break;
				case OT_WEAKREF:
					pf(v,_SC("[%s] WEAKREF\n"),name);
					break;
				case OT_BOOL:{
					sq_getinteger(v,-1,&i);
					pf(v,_SC("[%s] %s\n"),name,i?_SC("true"):_SC("false"));
							 }
					break;
				default: assert(0); break;
				}
				sq_pop(v,1);
			}
		}
	}
}

static SQInteger _sqstd_aux_printerror(HSQUIRRELVM v)
{
	SQPRINTFUNCTION pf = sq_geterrorfunc(v);
	if(pf) {
		const SQChar *sErr = 0;
		if(sq_gettop(v)>=1) {
			if(SQ_SUCCEEDED(sq_getstring(v,2,&sErr)))	{
				pf(v,_SC("\nAN ERROR HAS OCCURED [%s]\n"),sErr);
			}
			else{
				pf(v,_SC("\nAN ERROR HAS OCCURED [unknown]\n"));
			}
			sqstd_printcallstack(v);
		}
	}
	return 0;
}

void _sqstd_compiler_error(HSQUIRRELVM v,const SQChar *sErr,const SQChar *sSource,SQInteger line,SQInteger column)
{
	SQPRINTFUNCTION pf = sq_geterrorfunc(v);
	if(pf) {
		pf(v,_SC("%s line = (%d) column = (%d) : error %s\n"),sSource,line,column,sErr);
	}
}

void sqstd_seterrorhandlers(HSQUIRRELVM v)
{
	sq_setcompilererrorhandler(v,_sqstd_compiler_error);
	sq_newclosure(v,_sqstd_aux_printerror,0);
	sq_seterrorhandler(v);
}

// ******************************** sqstdblob.cpp ********************************
/* see copyright notice in squirrel.h */
#include <new>
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqstdblob.cpp
// ---- #include <sqstdio.h>
// ---> including sqstdio.h
// <--- back to sqstdblob.cpp
#include <string.h>
// ---- #include <sqstdblob.h>
// ---> including sqstdblob.h
// <--- back to sqstdblob.cpp
// ---- #include "sqstdstream.h"
// ---> including sqstdstream.h
/*	see copyright notice in squirrel.h */
#ifndef _SQSTD_STREAM_H_
#define _SQSTD_STREAM_H_

SQInteger _stream_readblob(HSQUIRRELVM v);
SQInteger _stream_readline(HSQUIRRELVM v);
SQInteger _stream_readn(HSQUIRRELVM v);
SQInteger _stream_writeblob(HSQUIRRELVM v);
SQInteger _stream_writen(HSQUIRRELVM v);
SQInteger _stream_seek(HSQUIRRELVM v);
SQInteger _stream_tell(HSQUIRRELVM v);
SQInteger _stream_len(HSQUIRRELVM v);
SQInteger _stream_eos(HSQUIRRELVM v);
SQInteger _stream_flush(HSQUIRRELVM v);

#define _DECL_STREAM_FUNC(name,nparams,typecheck) {_SC(#name),_stream_##name,nparams,typecheck}
SQRESULT declare_stream(HSQUIRRELVM v,const SQChar* name,SQUserPointer typetag,const SQChar* reg_name,SQRegFunction *methods,SQRegFunction *globals);
#endif /*_SQSTD_STREAM_H_*/

// <--- back to sqstdblob.cpp
// ---- #include "sqstdblobimpl.h"
// ---> including sqstdblobimpl.h
/*	see copyright notice in squirrel.h */
#ifndef _SQSTD_BLOBIMPL_H_
#define _SQSTD_BLOBIMPL_H_

struct SQBlob : public SQStream
{
	SQBlob(SQInteger size) {
		_size = size;
		_allocated = size;
		_buf = (unsigned char *)sq_malloc(size);
		memset(_buf, 0, _size);
		_ptr = 0;
		_owns = true;
	}
	virtual ~SQBlob() {
		sq_free(_buf, _allocated);
	}
	SQInteger Write(void *buffer, SQInteger size) {
		if(!CanAdvance(size)) {
			GrowBufOf(_ptr + size - _size);
		}
		memcpy(&_buf[_ptr], buffer, size);
		_ptr += size;
		return size;
	}
	SQInteger Read(void *buffer,SQInteger size) {
		SQInteger n = size;
		if(!CanAdvance(size)) {
			if((_size - _ptr) > 0)
				n = _size - _ptr;
			else return 0;
		}
		memcpy(buffer, &_buf[_ptr], n);
		_ptr += n;
		return n;
	}
	bool Resize(SQInteger n) {
		if(!_owns) return false;
		if(n != _allocated) {
			unsigned char *newbuf = (unsigned char *)sq_malloc(n);
			memset(newbuf,0,n);
			if(_size > n)
				memcpy(newbuf,_buf,n);
			else
				memcpy(newbuf,_buf,_size);
			sq_free(_buf,_allocated);
			_buf=newbuf;
			_allocated = n;
			if(_size > _allocated)
				_size = _allocated;
			if(_ptr > _allocated)
				_ptr = _allocated;
		}
		return true;
	}
	bool GrowBufOf(SQInteger n)
	{
		bool ret = true;
		if(_size + n > _allocated) {
			if(_size + n > _size * 2)
				ret = Resize(_size + n);
			else
				ret = Resize(_size * 2);
		}
		_size = _size + n;
		return ret;
	}
	bool CanAdvance(SQInteger n) {
		if(_ptr+n>_size)return false;
		return true;
	}
	SQInteger Seek(SQInteger offset, SQInteger origin) {
		switch(origin) {
			case SQ_SEEK_SET:
				if(offset > _size || offset < 0) return -1;
				_ptr = offset;
				break;
			case SQ_SEEK_CUR:
				if(_ptr + offset > _size || _ptr + offset < 0) return -1;
				_ptr += offset;
				break;
			case SQ_SEEK_END:
				if(_size + offset > _size || _size + offset < 0) return -1;
				_ptr = _size + offset;
				break;
			default: return -1;
		}
		return 0;
	}
	bool IsValid() {
		return _buf?true:false;
	}
	bool EOS() {
		return _ptr == _size;
	}
	SQInteger Flush() { return 0; }
	SQInteger Tell() { return _ptr; }
	SQInteger Len() { return _size; }
	SQUserPointer GetBuf(){ return _buf; }
private:
	SQInteger _size;
	SQInteger _allocated;
	SQInteger _ptr;
	unsigned char *_buf;
	bool _owns;
};

#endif //_SQSTD_BLOBIMPL_H_

// <--- back to sqstdblob.cpp

#define SQSTD_BLOB_TYPE_TAG (SQSTD_STREAM_TYPE_TAG | 0x00000002)

//Blob


#define SETUP_BLOB(v) \
	SQBlob *self = NULL; \
	{ if(SQ_FAILED(sq_getinstanceup(v,1,(SQUserPointer*)&self,(SQUserPointer)SQSTD_BLOB_TYPE_TAG))) \
		return sq_throwerror(v,_SC("invalid type tag"));  } \
	if(!self || !self->IsValid())  \
		return sq_throwerror(v,_SC("the blob is invalid"));


static SQInteger _blob_resize(HSQUIRRELVM v)
{
	SETUP_BLOB(v);
	SQInteger size;
	sq_getinteger(v,2,&size);
	if(!self->Resize(size))
		return sq_throwerror(v,_SC("resize failed"));
	return 0;
}

static void __swap_dword(unsigned int *n)
{
	*n=(unsigned int)(((*n&0xFF000000)>>24)  |
			((*n&0x00FF0000)>>8)  |
			((*n&0x0000FF00)<<8)  |
			((*n&0x000000FF)<<24));
}

static void __swap_word(unsigned short *n)
{
	*n=(unsigned short)((*n>>8)&0x00FF)| ((*n<<8)&0xFF00);
}

static SQInteger _blob_swap4(HSQUIRRELVM v)
{
	SETUP_BLOB(v);
	SQInteger num=(self->Len()-(self->Len()%4))>>2;
	unsigned int *t=(unsigned int *)self->GetBuf();
	for(SQInteger i = 0; i < num; i++) {
		__swap_dword(&t[i]);
	}
	return 0;
}

static SQInteger _blob_swap2(HSQUIRRELVM v)
{
	SETUP_BLOB(v);
	SQInteger num=(self->Len()-(self->Len()%2))>>1;
	unsigned short *t = (unsigned short *)self->GetBuf();
	for(SQInteger i = 0; i < num; i++) {
		__swap_word(&t[i]);
	}
	return 0;
}

static SQInteger _blob__set(HSQUIRRELVM v)
{
	SETUP_BLOB(v);
	SQInteger idx,val;
	sq_getinteger(v,2,&idx);
	sq_getinteger(v,3,&val);
	if(idx < 0 || idx >= self->Len())
		return sq_throwerror(v,_SC("index out of range"));
	((unsigned char *)self->GetBuf())[idx] = (unsigned char) val;
	sq_push(v,3);
	return 1;
}

static SQInteger _blob__get(HSQUIRRELVM v)
{
	SETUP_BLOB(v);
	SQInteger idx;
	sq_getinteger(v,2,&idx);
	if(idx < 0 || idx >= self->Len())
		return sq_throwerror(v,_SC("index out of range"));
	sq_pushinteger(v,((unsigned char *)self->GetBuf())[idx]);
	return 1;
}

static SQInteger _blob__nexti(HSQUIRRELVM v)
{
	SETUP_BLOB(v);
	if(sq_gettype(v,2) == OT_NULL) {
		sq_pushinteger(v, 0);
		return 1;
	}
	SQInteger idx;
	if(SQ_SUCCEEDED(sq_getinteger(v, 2, &idx))) {
		if(idx+1 < self->Len()) {
			sq_pushinteger(v, idx+1);
			return 1;
		}
		sq_pushnull(v);
		return 1;
	}
	return sq_throwerror(v,_SC("internal error (_nexti) wrong argument type"));
}

static SQInteger _blob__typeof(HSQUIRRELVM v)
{
	sq_pushstring(v,_SC("blob"),-1);
	return 1;
}

static SQInteger _blob_releasehook(SQUserPointer p, SQInteger size)
{
	SQBlob *self = (SQBlob*)p;
	self->~SQBlob();
	sq_free(self,sizeof(SQBlob));
	return 1;
}

static SQInteger _blob_constructor(HSQUIRRELVM v)
{
	SQInteger nparam = sq_gettop(v);
	SQInteger size = 0;
	if(nparam == 2) {
		sq_getinteger(v, 2, &size);
	}
	if(size < 0) return sq_throwerror(v, _SC("cannot create blob with negative size"));
	//SQBlob *b = new SQBlob(size);

	SQBlob *b = new (sq_malloc(sizeof(SQBlob)))SQBlob(size);
	if(SQ_FAILED(sq_setinstanceup(v,1,b))) {
		b->~SQBlob();
		sq_free(b,sizeof(SQBlob));
		return sq_throwerror(v, _SC("cannot create blob"));
	}
	sq_setreleasehook(v,1,_blob_releasehook);
	return 0;
}

static SQInteger _blob__cloned(HSQUIRRELVM v)
{
	SQBlob *other = NULL;
	{ 
		if(SQ_FAILED(sq_getinstanceup(v,2,(SQUserPointer*)&other,(SQUserPointer)SQSTD_BLOB_TYPE_TAG)))
			return SQ_ERROR; 
	}
	//SQBlob *thisone = new SQBlob(other->Len());
	SQBlob *thisone = new (sq_malloc(sizeof(SQBlob)))SQBlob(other->Len());
	memcpy(thisone->GetBuf(),other->GetBuf(),thisone->Len());
	if(SQ_FAILED(sq_setinstanceup(v,1,thisone))) {
		thisone->~SQBlob();
		sq_free(thisone,sizeof(SQBlob));
		return sq_throwerror(v, _SC("cannot clone blob"));
	}
	sq_setreleasehook(v,1,_blob_releasehook);
	return 0;
}

#define _DECL_BLOB_FUNC(name,nparams,typecheck) {_SC(#name),_blob_##name,nparams,typecheck}
static SQRegFunction _blob_methods[] = {
	_DECL_BLOB_FUNC(constructor,-1,_SC("xn")),
	_DECL_BLOB_FUNC(resize,2,_SC("xn")),
	_DECL_BLOB_FUNC(swap2,1,_SC("x")),
	_DECL_BLOB_FUNC(swap4,1,_SC("x")),
	_DECL_BLOB_FUNC(_set,3,_SC("xnn")),
	_DECL_BLOB_FUNC(_get,2,_SC("xn")),
	_DECL_BLOB_FUNC(_typeof,1,_SC("x")),
	_DECL_BLOB_FUNC(_nexti,2,_SC("x")),
	_DECL_BLOB_FUNC(_cloned,2,_SC("xx")),
	{0,0,0,0}
};



//GLOBAL FUNCTIONS

static SQInteger _g_blob_casti2f(HSQUIRRELVM v)
{
	SQInteger i;
	sq_getinteger(v,2,&i);
	sq_pushfloat(v,*((SQFloat *)&i));
	return 1;
}

static SQInteger _g_blob_castf2i(HSQUIRRELVM v)
{
	SQFloat f;
	sq_getfloat(v,2,&f);
	sq_pushinteger(v,*((SQInteger *)&f));
	return 1;
}

static SQInteger _g_blob_swap2(HSQUIRRELVM v)
{
	SQInteger i;
	sq_getinteger(v,2,&i);
	short s=(short)i;
	sq_pushinteger(v,(s<<8)|((s>>8)&0x00FF));
	return 1;
}

static SQInteger _g_blob_swap4(HSQUIRRELVM v)
{
	SQInteger i;
	sq_getinteger(v,2,&i);
	unsigned int t4 = (unsigned int)i;
	__swap_dword(&t4);
	sq_pushinteger(v,(SQInteger)t4);
	return 1;
}

static SQInteger _g_blob_swapfloat(HSQUIRRELVM v)
{
	SQFloat f;
	sq_getfloat(v,2,&f);
	__swap_dword((unsigned int *)&f);
	sq_pushfloat(v,f);
	return 1;
}

#define _DECL_GLOBALBLOB_FUNC(name,nparams,typecheck) {_SC(#name),_g_blob_##name,nparams,typecheck}
static SQRegFunction bloblib_funcs[]={
	_DECL_GLOBALBLOB_FUNC(casti2f,2,_SC(".n")),
	_DECL_GLOBALBLOB_FUNC(castf2i,2,_SC(".n")),
	_DECL_GLOBALBLOB_FUNC(swap2,2,_SC(".n")),
	_DECL_GLOBALBLOB_FUNC(swap4,2,_SC(".n")),
	_DECL_GLOBALBLOB_FUNC(swapfloat,2,_SC(".n")),
	{0,0}
};

SQRESULT sqstd_getblob(HSQUIRRELVM v,SQInteger idx,SQUserPointer *ptr)
{
	SQBlob *blob;
	if(SQ_FAILED(sq_getinstanceup(v,idx,(SQUserPointer *)&blob,(SQUserPointer)SQSTD_BLOB_TYPE_TAG)))
		return -1;
	*ptr = blob->GetBuf();
	return SQ_OK;
}

SQInteger sqstd_getblobsize(HSQUIRRELVM v,SQInteger idx)
{
	SQBlob *blob;
	if(SQ_FAILED(sq_getinstanceup(v,idx,(SQUserPointer *)&blob,(SQUserPointer)SQSTD_BLOB_TYPE_TAG)))
		return -1;
	return blob->Len();
}

SQUserPointer sqstd_createblob(HSQUIRRELVM v, SQInteger size)
{
	SQInteger top = sq_gettop(v);
	sq_pushregistrytable(v);
	sq_pushstring(v,_SC("std_blob"),-1);
	if(SQ_SUCCEEDED(sq_get(v,-2))) {
		sq_remove(v,-2); //removes the registry
		sq_push(v,1); // push the this
		sq_pushinteger(v,size); //size
		SQBlob *blob = NULL;
		if(SQ_SUCCEEDED(sq_call(v,2,SQTrue,SQFalse))
			&& SQ_SUCCEEDED(sq_getinstanceup(v,-1,(SQUserPointer *)&blob,(SQUserPointer)SQSTD_BLOB_TYPE_TAG))) {
			sq_remove(v,-2);
			return blob->GetBuf();
		}
	}
	sq_settop(v,top);
	return NULL;
}

SQRESULT sqstd_register_bloblib(HSQUIRRELVM v)
{
	return declare_stream(v,_SC("blob"),(SQUserPointer)SQSTD_BLOB_TYPE_TAG,_SC("std_blob"),_blob_methods,bloblib_funcs);
}


// ******************************** sqstdio.cpp ********************************
/* see copyright notice in squirrel.h */
#include <new>
#include <stdio.h>
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqstdio.cpp
// ---- #include <sqstdio.h>
// ---> including sqstdio.h
// <--- back to sqstdio.cpp
// ---- #include "sqstdstream.h"
// ---> including sqstdstream.h
// <--- back to sqstdio.cpp

#define SQSTD_FILE_TYPE_TAG (SQSTD_STREAM_TYPE_TAG | 0x00000001)
//basic API
//SQFILE sqstd_fopen(const SQChar *filename ,const SQChar *mode)
//{
//#ifndef SQUNICODE
//	return (SQFILE)fopen(filename,mode);
//#else
//	return (SQFILE)_wfopen(filename,mode);
//#endif
//}
//
//SQInteger sqstd_fread(void* buffer, SQInteger size, SQInteger count, SQFILE file)
//{
//	return (SQInteger)fread(buffer,size,count,(FILE *)file);
//}
//
//SQInteger sqstd_fwrite(const SQUserPointer buffer, SQInteger size, SQInteger count, SQFILE file)
//{
//	return (SQInteger)fwrite(buffer,size,count,(FILE *)file);
//}
//
//SQInteger sqstd_fseek(SQFILE file, SQInteger offset, SQInteger origin)
//{
//	SQInteger realorigin;
//	switch(origin) {
//		case SQ_SEEK_CUR: realorigin = SEEK_CUR; break;
//		case SQ_SEEK_END: realorigin = SEEK_END; break;
//		case SQ_SEEK_SET: realorigin = SEEK_SET; break;
//		default: return -1; //failed
//	}
//	return fseek((FILE *)file,(long)offset,(int)realorigin);
//}
//
//SQInteger sqstd_ftell(SQFILE file)
//{
//	return ftell((FILE *)file);
//}
//
//SQInteger sqstd_fflush(SQFILE file)
//{
//	return fflush((FILE *)file);
//}
//
//SQInteger sqstd_fclose(SQFILE file)
//{
//	return fclose((FILE *)file);
//}
//
//SQInteger sqstd_feof(SQFILE file)
//{
//	return feof((FILE *)file);
//}

//File
struct SQFile : public SQStream {
	SQFile() { _handle = NULL; _owns = false;}
	SQFile(SQFILE file, bool owns) { _handle = file; _owns = owns;}
	virtual ~SQFile() { Close(); }
	bool Open(const SQChar *filename ,const SQChar *mode) {
		Close();
		if( (_handle = sqstd_fopen(filename,mode)) ) {
			_owns = true;
			return true;
		}
		return false;
	}
	void Close() {
		if(_handle && _owns) { 
			sqstd_fclose(_handle);
			_handle = NULL;
			_owns = false;
		}
	}
	SQInteger Read(void *buffer,SQInteger size) {
		return sqstd_fread(buffer,1,size,_handle);
	}
	SQInteger Write(void *buffer,SQInteger size) {
		return sqstd_fwrite(buffer,1,size,_handle);
	}
	SQInteger Flush() {
		return sqstd_fflush(_handle);
	}
	SQInteger Tell() {
		return sqstd_ftell(_handle);
	}
	SQInteger Len() {
		SQInteger prevpos=Tell();
		Seek(0,SQ_SEEK_END);
		SQInteger size=Tell();
		Seek(prevpos,SQ_SEEK_SET);
		return size;
	}
	SQInteger Seek(SQInteger offset, SQInteger origin)	{
		return sqstd_fseek(_handle,offset,origin);
	}
	bool IsValid() { return _handle?true:false; }
	bool EOS() { return Tell()==Len()?true:false;}
	SQFILE GetHandle() {return _handle;}
private:
	SQFILE _handle;
	bool _owns;
};

static SQInteger _file__typeof(HSQUIRRELVM v)
{
	sq_pushstring(v,_SC("file"),-1);
	return 1;
}

static SQInteger _file_releasehook(SQUserPointer p, SQInteger size)
{
	SQFile *self = (SQFile*)p;
	self->~SQFile();
	sq_free(self,sizeof(SQFile));
	return 1;
}

static SQInteger _file_constructor(HSQUIRRELVM v)
{
	const SQChar *filename,*mode;
	bool owns = true;
	SQFile *f;
	SQFILE newf;
	if(sq_gettype(v,2) == OT_STRING && sq_gettype(v,3) == OT_STRING) {
		sq_getstring(v, 2, &filename);
		sq_getstring(v, 3, &mode);
		newf = sqstd_fopen(filename, mode);
		if(!newf) return sq_throwerror(v, _SC("cannot open file"));
	} else if(sq_gettype(v,2) == OT_USERPOINTER) {
		owns = !(sq_gettype(v,3) == OT_NULL);
		sq_getuserpointer(v,2,&newf);
	} else {
		return sq_throwerror(v,_SC("wrong parameter"));
	}
	
	f = new (sq_malloc(sizeof(SQFile)))SQFile(newf,owns);
	if(SQ_FAILED(sq_setinstanceup(v,1,f))) {
		f->~SQFile();
		sq_free(f,sizeof(SQFile));
		return sq_throwerror(v, _SC("cannot create blob with negative size"));
	}
	sq_setreleasehook(v,1,_file_releasehook);
	return 0;
}

static SQInteger _file_close(HSQUIRRELVM v)
{
	SQFile *self = NULL;
	if(SQ_SUCCEEDED(sq_getinstanceup(v,1,(SQUserPointer*)&self,(SQUserPointer)SQSTD_FILE_TYPE_TAG))
		&& self != NULL)
	{
		self->Close();
	}
	return 0;
}

//bindings
#define _DECL_FILE_FUNC(name,nparams,typecheck) {_SC(#name),_file_##name,nparams,typecheck}
static SQRegFunction _file_methods[] = {
	_DECL_FILE_FUNC(constructor,3,_SC("x")),
	_DECL_FILE_FUNC(_typeof,1,_SC("x")),
	_DECL_FILE_FUNC(close,1,_SC("x")),
	{0,0,0,0},
};



SQRESULT sqstd_createfile(HSQUIRRELVM v, SQFILE file,SQBool own)
{
	SQInteger top = sq_gettop(v);
	sq_pushregistrytable(v);
	sq_pushstring(v,_SC("std_file"),-1);
	if(SQ_SUCCEEDED(sq_get(v,-2))) {
		sq_remove(v,-2); //removes the registry
		sq_pushroottable(v); // push the this
		sq_pushuserpointer(v,file); //file
		if(own){
			sq_pushinteger(v,1); //true
		}
		else{
			sq_pushnull(v); //false
		}
		if(SQ_SUCCEEDED( sq_call(v,3,SQTrue,SQFalse) )) {
			sq_remove(v,-2);
			return SQ_OK;
		}
	}
	sq_settop(v,top);
	return SQ_OK;
}

SQRESULT sqstd_getfile(HSQUIRRELVM v, SQInteger idx, SQFILE *file)
{
	SQFile *fileobj = NULL;
	if(SQ_SUCCEEDED(sq_getinstanceup(v,idx,(SQUserPointer*)&fileobj,(SQUserPointer)SQSTD_FILE_TYPE_TAG))) {
		*file = fileobj->GetHandle();
		return SQ_OK;
	}
	return sq_throwerror(v,_SC("not a file"));
}



static SQInteger _io_file_lexfeed_PLAIN(SQUserPointer file)
{
	SQInteger ret;
	char c;
	if( ( ret=sqstd_fread(&c,sizeof(c),1,(FILE *)file )>0) )
		return c;
	return 0;
}

#ifdef SQUNICODE
static SQInteger _io_file_lexfeed_UTF8(SQUserPointer file)
{
#define READ() \
	if(sqstd_fread(&inchar,sizeof(inchar),1,(FILE *)file) != 1) \
		return 0;

	static const SQInteger utf8_lengths[16] =
	{
		1,1,1,1,1,1,1,1,        /* 0000 to 0111 : 1 byte (plain ASCII) */
		0,0,0,0,                /* 1000 to 1011 : not valid */
		2,2,                    /* 1100, 1101 : 2 bytes */
		3,                      /* 1110 : 3 bytes */
		4                       /* 1111 :4 bytes */
	};
	static unsigned char byte_masks[5] = {0,0,0x1f,0x0f,0x07};
	unsigned char inchar;
	SQInteger c = 0;
	READ();
	c = inchar;
	//
	if(c >= 0x80) {
		SQInteger tmp;
		SQInteger codelen = utf8_lengths[c>>4];
		if(codelen == 0) 
			return 0;
			//"invalid UTF-8 stream";
		tmp = c&byte_masks[codelen];
		for(SQInteger n = 0; n < codelen-1; n++) {
			tmp<<=6;
			READ();
			tmp |= inchar & 0x3F;
		}
		c = tmp;
	}
	return c;
}
#endif

static SQInteger _io_file_lexfeed_UCS2_LE(SQUserPointer file)
{
	SQInteger ret;
	wchar_t c;
	if( ( ret=sqstd_fread(&c,sizeof(c),1,(FILE *)file )>0) )
		return (SQChar)c;
	return 0;
}

static SQInteger _io_file_lexfeed_UCS2_BE(SQUserPointer file)
{
	SQInteger ret;
	unsigned short c;
	if( ( ret=sqstd_fread(&c,sizeof(c),1,(FILE *)file )>0) ) {
		c = ((c>>8)&0x00FF)| ((c<<8)&0xFF00);
		return (SQChar)c;
	}
	return 0;
}

SQInteger file_read(SQUserPointer file,SQUserPointer buf,SQInteger size)
{
	SQInteger ret;
	if( ( ret = sqstd_fread(buf,1,size,(SQFILE)file ))!=0 )return ret;
	return -1;
}

SQInteger file_write(SQUserPointer file,SQUserPointer p,SQInteger size)
{
	return sqstd_fwrite(p,1,size,(SQFILE)file);
}

SQRESULT sqstd_loadfile(HSQUIRRELVM v,const SQChar *filename,SQBool printerror)
{
	SQFILE file = sqstd_fopen(filename,_SC("rb"));
	SQInteger ret;
	unsigned short us;
	unsigned char uc;
	SQLEXREADFUNC func = _io_file_lexfeed_PLAIN;
	if(file){
		ret = sqstd_fread(&us,1,2,file);
		if(ret != 2) {
			//probably an empty file
			us = 0;
		}
		if(us == SQ_BYTECODE_STREAM_TAG) { //BYTECODE
			sqstd_fseek(file,0,SQ_SEEK_SET);
			if(SQ_SUCCEEDED(sq_readclosure(v,file_read,file))) {
				sqstd_fclose(file);
				return SQ_OK;
			}
		}
		else { //SCRIPT
			switch(us)
			{
				//gotta swap the next 2 lines on BIG endian machines
				case 0xFFFE: func = _io_file_lexfeed_UCS2_BE; break;//UTF-16 little endian;
				case 0xFEFF: func = _io_file_lexfeed_UCS2_LE; break;//UTF-16 big endian;
				case 0xBBEF: 
					if(sqstd_fread(&uc,1,sizeof(uc),file) == 0) { 
						sqstd_fclose(file); 
						return sq_throwerror(v,_SC("io error")); 
					}
					if(uc != 0xBF) { 
						sqstd_fclose(file); 
						return sq_throwerror(v,_SC("Unrecognozed ecoding")); 
					}
#ifdef SQUNICODE
					func = _io_file_lexfeed_UTF8;
#else
					func = _io_file_lexfeed_PLAIN;
#endif
					break;//UTF-8 ;
				default: sqstd_fseek(file,0,SQ_SEEK_SET); break; // ascii
			}

			if(SQ_SUCCEEDED(sq_compile(v,func,file,filename,printerror))){
				sqstd_fclose(file);
				return SQ_OK;
			}
		}
		sqstd_fclose(file);
		return SQ_ERROR;
	}
	return sq_throwerror(v,_SC("cannot open the file"));
}

SQRESULT sqstd_dofile(HSQUIRRELVM v,const SQChar *filename,SQBool retval,SQBool printerror)
{
	if(SQ_SUCCEEDED(sqstd_loadfile(v,filename,printerror))) {
		sq_push(v,-2);
		if(SQ_SUCCEEDED(sq_call(v,1,retval,SQTrue))) {
			sq_remove(v,retval?-2:-1); //removes the closure
			return 1;
		}
		sq_pop(v,1); //removes the closure
	}
	return SQ_ERROR;
}

SQRESULT sqstd_writeclosuretofile(HSQUIRRELVM v,const SQChar *filename)
{
	SQFILE file = sqstd_fopen(filename,_SC("wb+"));
	if(!file) return sq_throwerror(v,_SC("cannot open the file"));
	if(SQ_SUCCEEDED(sq_writeclosure(v,file_write,file))) {
		sqstd_fclose(file);
		return SQ_OK;
	}
	sqstd_fclose(file);
	return SQ_ERROR; //forward the error
}

SQInteger _g_io_loadfile(HSQUIRRELVM v)
{
	const SQChar *filename;
	SQBool printerror = SQFalse;
	sq_getstring(v,2,&filename);
	if(sq_gettop(v) >= 3) {
		sq_getbool(v,3,&printerror);
	}
	if(SQ_SUCCEEDED(sqstd_loadfile(v,filename,printerror)))
		return 1;
	return SQ_ERROR; //propagates the error
}

SQInteger _g_io_writeclosuretofile(HSQUIRRELVM v)
{
	const SQChar *filename;
	sq_getstring(v,2,&filename);
	if(SQ_SUCCEEDED(sqstd_writeclosuretofile(v,filename)))
		return 1;
	return SQ_ERROR; //propagates the error
}

SQInteger _g_io_dofile(HSQUIRRELVM v)
{
	const SQChar *filename;
	SQBool printerror = SQFalse;
	sq_getstring(v,2,&filename);
	if(sq_gettop(v) >= 3) {
		sq_getbool(v,3,&printerror);
	}
	sq_push(v,1); //repush the this
	if(SQ_SUCCEEDED(sqstd_dofile(v,filename,SQTrue,printerror)))
		return 1;
	return SQ_ERROR; //propagates the error
}

#define _DECL_GLOBALIO_FUNC(name,nparams,typecheck) {_SC(#name),_g_io_##name,nparams,typecheck}
static SQRegFunction iolib_funcs[]={
	_DECL_GLOBALIO_FUNC(loadfile,-2,_SC(".sb")),
	_DECL_GLOBALIO_FUNC(dofile,-2,_SC(".sb")),
	_DECL_GLOBALIO_FUNC(writeclosuretofile,3,_SC(".sc")),
	{0,0}
};

SQRESULT sqstd_register_iolib(HSQUIRRELVM v)
{
	SQInteger top = sq_gettop(v);
	//create delegate
	declare_stream(v,_SC("file"),(SQUserPointer)SQSTD_FILE_TYPE_TAG,_SC("std_file"),_file_methods,iolib_funcs);
	sq_pushstring(v,_SC("stdout"),-1);
	sqstd_createfile(v,stdout,SQFalse);
	sq_newslot(v,-3,SQFalse);
	sq_pushstring(v,_SC("stdin"),-1);
	sqstd_createfile(v,stdin,SQFalse);
	sq_newslot(v,-3,SQFalse);
	sq_pushstring(v,_SC("stderr"),-1);
	sqstd_createfile(v,stderr,SQFalse);
	sq_newslot(v,-3,SQFalse);
	sq_settop(v,top);
	return SQ_OK;
}

// ******************************** sqstdmath.cpp ********************************
/* see copyright notice in squirrel.h */
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqstdmath.cpp
#include <math.h>
#include <stdlib.h>
// ---- #include <sqstdmath.h>
// ---> including sqstdmath.h
// <--- back to sqstdmath.cpp

#define SINGLE_ARG_FUNC(_funcname) static SQInteger math_##_funcname(HSQUIRRELVM v){ \
	SQFloat f; \
	sq_getfloat(v,2,&f); \
	sq_pushfloat(v,(SQFloat)_funcname(f)); \
	return 1; \
}

#define TWO_ARGS_FUNC(_funcname) static SQInteger math_##_funcname(HSQUIRRELVM v){ \
	SQFloat p1,p2; \
	sq_getfloat(v,2,&p1); \
	sq_getfloat(v,3,&p2); \
	sq_pushfloat(v,(SQFloat)_funcname(p1,p2)); \
	return 1; \
}

static SQInteger math_srand(HSQUIRRELVM v)
{
	SQInteger i;
	if(SQ_FAILED(sq_getinteger(v,2,&i)))
		return sq_throwerror(v,_SC("invalid param"));
	srand((unsigned int)i);
	return 0;
}

static SQInteger math_rand(HSQUIRRELVM v)
{
	sq_pushinteger(v,rand());
	return 1;
}

static SQInteger math_abs(HSQUIRRELVM v)
{
	SQInteger n;
	sq_getinteger(v,2,&n);
	sq_pushinteger(v,(SQInteger)abs((int)n)); 
	return 1; 
}

SINGLE_ARG_FUNC(sqrt)
SINGLE_ARG_FUNC(fabs)
SINGLE_ARG_FUNC(sin)
SINGLE_ARG_FUNC(cos)
SINGLE_ARG_FUNC(asin)
SINGLE_ARG_FUNC(acos)
SINGLE_ARG_FUNC(log)
SINGLE_ARG_FUNC(log10)
SINGLE_ARG_FUNC(tan)
SINGLE_ARG_FUNC(atan)
TWO_ARGS_FUNC(atan2)
TWO_ARGS_FUNC(pow)
SINGLE_ARG_FUNC(floor)
SINGLE_ARG_FUNC(ceil)
SINGLE_ARG_FUNC(exp)

#define _DECL_FUNC(name,nparams,tycheck) {_SC(#name),math_##name,nparams,tycheck}
static SQRegFunction mathlib_funcs[] = {
	_DECL_FUNC(sqrt,2,_SC(".n")),
	_DECL_FUNC(sin,2,_SC(".n")),
	_DECL_FUNC(cos,2,_SC(".n")),
	_DECL_FUNC(asin,2,_SC(".n")),
	_DECL_FUNC(acos,2,_SC(".n")),
	_DECL_FUNC(log,2,_SC(".n")),
	_DECL_FUNC(log10,2,_SC(".n")),
	_DECL_FUNC(tan,2,_SC(".n")),
	_DECL_FUNC(atan,2,_SC(".n")),
	_DECL_FUNC(atan2,3,_SC(".nn")),
	_DECL_FUNC(pow,3,_SC(".nn")),
	_DECL_FUNC(floor,2,_SC(".n")),
	_DECL_FUNC(ceil,2,_SC(".n")),
	_DECL_FUNC(exp,2,_SC(".n")),
	_DECL_FUNC(srand,2,_SC(".n")),
	_DECL_FUNC(rand,1,NULL),
	_DECL_FUNC(fabs,2,_SC(".n")),
	_DECL_FUNC(abs,2,_SC(".n")),
	{0,0},
};
#undef _DECL_FUNC

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

SQRESULT sqstd_register_mathlib(HSQUIRRELVM v)
{
	SQInteger i=0;
	while(mathlib_funcs[i].name!=0)	{
		sq_pushstring(v,mathlib_funcs[i].name,-1);
		sq_newclosure(v,mathlib_funcs[i].f,0);
		sq_setparamscheck(v,mathlib_funcs[i].nparamscheck,mathlib_funcs[i].typemask);
		sq_setnativeclosurename(v,-1,mathlib_funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}
	sq_pushstring(v,_SC("RAND_MAX"),-1);
	sq_pushinteger(v,RAND_MAX);
	sq_newslot(v,-3,SQFalse);
	sq_pushstring(v,_SC("PI"),-1);
	sq_pushfloat(v,(SQFloat)M_PI);
	sq_newslot(v,-3,SQFalse);
	return SQ_OK;
}

// ******************************** sqstdrex.cpp ********************************
/* see copyright notice in squirrel.h */
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqstdrex.cpp
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
// ---- #include <sqstdstring.h>
// ---> including sqstdstring.h
// <--- back to sqstdrex.cpp

#ifdef _UINCODE
#define scisprint iswprint
#else
#define scisprint isprint
#endif

#ifdef _DEBUG
#include <stdio.h>

static const SQChar *g_nnames[] =
{
	_SC("NONE"),_SC("OP_GREEDY"),	_SC("OP_OR"),
	_SC("OP_EXPR"),_SC("OP_NOCAPEXPR"),_SC("OP_DOT"),	_SC("OP_CLASS"),
	_SC("OP_CCLASS"),_SC("OP_NCLASS"),_SC("OP_RANGE"),_SC("OP_CHAR"),
	_SC("OP_EOL"),_SC("OP_BOL"),_SC("OP_WB")
};

#endif

#define OP_GREEDY		(MAX_CHAR+1) // * + ? {n}
#define OP_OR			(MAX_CHAR+2)
#define OP_EXPR			(MAX_CHAR+3) //parentesis ()
#define OP_NOCAPEXPR	(MAX_CHAR+4) //parentesis (?:)
#define OP_DOT			(MAX_CHAR+5)
#define OP_CLASS		(MAX_CHAR+6)
#define OP_CCLASS		(MAX_CHAR+7)
#define OP_NCLASS		(MAX_CHAR+8) //negates class the [^
#define OP_RANGE		(MAX_CHAR+9)
#define OP_CHAR			(MAX_CHAR+10)
#define OP_EOL			(MAX_CHAR+11)
#define OP_BOL			(MAX_CHAR+12)
#define OP_WB			(MAX_CHAR+13)

#define SQREX_SYMBOL_ANY_CHAR ('.')
#define SQREX_SYMBOL_GREEDY_ONE_OR_MORE ('+')
#define SQREX_SYMBOL_GREEDY_ZERO_OR_MORE ('*')
#define SQREX_SYMBOL_GREEDY_ZERO_OR_ONE ('?')
#define SQREX_SYMBOL_BRANCH ('|')
#define SQREX_SYMBOL_END_OF_STRING ('$')
#define SQREX_SYMBOL_BEGINNING_OF_STRING ('^')
#define SQREX_SYMBOL_ESCAPE_CHAR ('\\')


typedef int SQRexNodeType;

typedef struct tagSQRexNode{
	SQRexNodeType type;
	SQInteger left;
	SQInteger right;
	SQInteger next;
}SQRexNode;

struct SQRex{
	const SQChar *_eol;
	const SQChar *_bol;
	const SQChar *_p;
	SQInteger _first;
	SQInteger _op;
	SQRexNode *_nodes;
	SQInteger _nallocated;
	SQInteger _nsize;
	SQInteger _nsubexpr;
	SQRexMatch *_matches;
	SQInteger _currsubexp;
	void *_jmpbuf;
	const SQChar **_error;
};

static SQInteger sqstd_rex_list(SQRex *exp);

static SQInteger sqstd_rex_newnode(SQRex *exp, SQRexNodeType type)
{
	SQRexNode n;
	n.type = type;
	n.next = n.right = n.left = -1;
	if(type == OP_EXPR)
		n.right = exp->_nsubexpr++;
	if(exp->_nallocated < (exp->_nsize + 1)) {
		SQInteger oldsize = exp->_nallocated;
		exp->_nallocated *= 2;
		exp->_nodes = (SQRexNode *)sq_realloc(exp->_nodes, oldsize * sizeof(SQRexNode) ,exp->_nallocated * sizeof(SQRexNode));
	}
	exp->_nodes[exp->_nsize++] = n;
	SQInteger newid = exp->_nsize - 1;
	return (SQInteger)newid;
}

static void sqstd_rex_error(SQRex *exp,const SQChar *error)
{
	if(exp->_error) *exp->_error = error;
	longjmp(*((jmp_buf*)exp->_jmpbuf),-1);
}

static void sqstd_rex_expect(SQRex *exp, SQInteger n){
	if((*exp->_p) != n) 
		sqstd_rex_error(exp, _SC("expected paren"));
	exp->_p++;
}

static SQChar sqstd_rex_escapechar(SQRex *exp)
{
	if(*exp->_p == SQREX_SYMBOL_ESCAPE_CHAR){
		exp->_p++;
		switch(*exp->_p) {
		case 'v': exp->_p++; return '\v';
		case 'n': exp->_p++; return '\n';
		case 't': exp->_p++; return '\t';
		case 'r': exp->_p++; return '\r';
		case 'f': exp->_p++; return '\f';
		default: return (*exp->_p++);
		}
	} else if(!scisprint(*exp->_p)) sqstd_rex_error(exp,_SC("letter expected"));
	return (*exp->_p++);
}

static SQInteger sqstd_rex_charclass(SQRex *exp,SQInteger classid)
{
	SQInteger n = sqstd_rex_newnode(exp,OP_CCLASS);
	exp->_nodes[n].left = classid;
	return n;
}

static SQInteger sqstd_rex_charnode(SQRex *exp,SQBool isclass)
{
	SQChar t;
	if(*exp->_p == SQREX_SYMBOL_ESCAPE_CHAR) {
		exp->_p++;
		switch(*exp->_p) {
			case 'n': exp->_p++; return sqstd_rex_newnode(exp,'\n');
			case 't': exp->_p++; return sqstd_rex_newnode(exp,'\t');
			case 'r': exp->_p++; return sqstd_rex_newnode(exp,'\r');
			case 'f': exp->_p++; return sqstd_rex_newnode(exp,'\f');
			case 'v': exp->_p++; return sqstd_rex_newnode(exp,'\v');
			case 'a': case 'A': case 'w': case 'W': case 's': case 'S': 
			case 'd': case 'D': case 'x': case 'X': case 'c': case 'C': 
			case 'p': case 'P': case 'l': case 'u': 
				{
				t = *exp->_p; exp->_p++; 
				return sqstd_rex_charclass(exp,t);
				}
			case 'b': 
			case 'B':
				if(!isclass) {
					SQInteger node = sqstd_rex_newnode(exp,OP_WB);
					exp->_nodes[node].left = *exp->_p;
					exp->_p++; 
					return node;
				} //else default
			default: 
				t = *exp->_p; exp->_p++; 
				return sqstd_rex_newnode(exp,t);
		}
	}
	else if(!scisprint(*exp->_p)) {
		
		sqstd_rex_error(exp,_SC("letter expected"));
	}
	t = *exp->_p; exp->_p++; 
	return sqstd_rex_newnode(exp,t);
}
static SQInteger sqstd_rex_class(SQRex *exp)
{
	SQInteger ret = -1;
	SQInteger first = -1,chain;
	if(*exp->_p == SQREX_SYMBOL_BEGINNING_OF_STRING){
		ret = sqstd_rex_newnode(exp,OP_NCLASS);
		exp->_p++;
	}else ret = sqstd_rex_newnode(exp,OP_CLASS);
	
	if(*exp->_p == ']') sqstd_rex_error(exp,_SC("empty class"));
	chain = ret;
	while(*exp->_p != ']' && exp->_p != exp->_eol) {
		if(*exp->_p == '-' && first != -1){ 
			SQInteger r;
			if(*exp->_p++ == ']') sqstd_rex_error(exp,_SC("unfinished range"));
			r = sqstd_rex_newnode(exp,OP_RANGE);
			if(exp->_nodes[first].type>*exp->_p) sqstd_rex_error(exp,_SC("invalid range"));
			if(exp->_nodes[first].type == OP_CCLASS) sqstd_rex_error(exp,_SC("cannot use character classes in ranges"));
			exp->_nodes[r].left = exp->_nodes[first].type;
			SQInteger t = sqstd_rex_escapechar(exp);
			exp->_nodes[r].right = t;
            exp->_nodes[chain].next = r;
			chain = r;
			first = -1;
		}
		else{
			if(first!=-1){
				SQInteger c = first;
				exp->_nodes[chain].next = c;
				chain = c;
				first = sqstd_rex_charnode(exp,SQTrue);
			}
			else{
				first = sqstd_rex_charnode(exp,SQTrue);
			}
		}
	}
	if(first!=-1){
		SQInteger c = first;
		exp->_nodes[chain].next = c;
		chain = c;
		first = -1;
	}
	/* hack? */
	exp->_nodes[ret].left = exp->_nodes[ret].next;
	exp->_nodes[ret].next = -1;
	return ret;
}

static SQInteger sqstd_rex_parsenumber(SQRex *exp)
{
	SQInteger ret = *exp->_p-'0';
	SQInteger positions = 10;
	exp->_p++;
	while(isdigit(*exp->_p)) {
		ret = ret*10+(*exp->_p++-'0');
		if(positions==1000000000) sqstd_rex_error(exp,_SC("overflow in numeric constant"));
		positions *= 10;
	};
	return ret;
}

static SQInteger sqstd_rex_element(SQRex *exp)
{
	SQInteger ret = -1;
	switch(*exp->_p)
	{
	case '(': {
		SQInteger expr;
		exp->_p++;


		if(*exp->_p =='?') {
			exp->_p++;
			sqstd_rex_expect(exp,':');
			expr = sqstd_rex_newnode(exp,OP_NOCAPEXPR);
		}
		else
			expr = sqstd_rex_newnode(exp,OP_EXPR);
		SQInteger newn = sqstd_rex_list(exp);
		exp->_nodes[expr].left = newn;
		ret = expr;
		sqstd_rex_expect(exp,')');
			  }
			  break;
	case '[':
		exp->_p++;
		ret = sqstd_rex_class(exp);
		sqstd_rex_expect(exp,']');
		break;
	case SQREX_SYMBOL_END_OF_STRING: exp->_p++; ret = sqstd_rex_newnode(exp,OP_EOL);break;
	case SQREX_SYMBOL_ANY_CHAR: exp->_p++; ret = sqstd_rex_newnode(exp,OP_DOT);break;
	default:
		ret = sqstd_rex_charnode(exp,SQFalse);
		break;
	}


	SQInteger op;
	SQBool isgreedy = SQFalse;
	unsigned short p0 = 0, p1 = 0;
	switch(*exp->_p){
		case SQREX_SYMBOL_GREEDY_ZERO_OR_MORE: p0 = 0; p1 = 0xFFFF; exp->_p++; isgreedy = SQTrue; break;
		case SQREX_SYMBOL_GREEDY_ONE_OR_MORE: p0 = 1; p1 = 0xFFFF; exp->_p++; isgreedy = SQTrue; break;
		case SQREX_SYMBOL_GREEDY_ZERO_OR_ONE: p0 = 0; p1 = 1; exp->_p++; isgreedy = SQTrue; break;
		case '{':
			exp->_p++;
			if(!isdigit(*exp->_p)) sqstd_rex_error(exp,_SC("number expected"));
			p0 = (unsigned short)sqstd_rex_parsenumber(exp);
			/*******************************/
			switch(*exp->_p) {
		case '}':
			p1 = p0; exp->_p++;
			break;
		case ',':
			exp->_p++;
			p1 = 0xFFFF;
			if(isdigit(*exp->_p)){
				p1 = (unsigned short)sqstd_rex_parsenumber(exp);
			}
			sqstd_rex_expect(exp,'}');
			break;
		default:
			sqstd_rex_error(exp,_SC(", or } expected"));
			}
			/*******************************/
			isgreedy = SQTrue; 
			break;

	}
	if(isgreedy) {
		SQInteger nnode = sqstd_rex_newnode(exp,OP_GREEDY);
		op = OP_GREEDY;
		exp->_nodes[nnode].left = ret;
		exp->_nodes[nnode].right = ((p0)<<16)|p1;
		ret = nnode;
	}

	if((*exp->_p != SQREX_SYMBOL_BRANCH) && (*exp->_p != ')') && (*exp->_p != SQREX_SYMBOL_GREEDY_ZERO_OR_MORE) && (*exp->_p != SQREX_SYMBOL_GREEDY_ONE_OR_MORE) && (*exp->_p != '\0')) {
		SQInteger nnode = sqstd_rex_element(exp);
		exp->_nodes[ret].next = nnode;
	}

	return ret;
}

static SQInteger sqstd_rex_list(SQRex *exp)
{
	SQInteger ret=-1,e;
	if(*exp->_p == SQREX_SYMBOL_BEGINNING_OF_STRING) {
		exp->_p++;
		ret = sqstd_rex_newnode(exp,OP_BOL);
	}
	e = sqstd_rex_element(exp);
	if(ret != -1) {
		exp->_nodes[ret].next = e;
	}
	else ret = e;

	if(*exp->_p == SQREX_SYMBOL_BRANCH) {
		SQInteger temp,tright;
		exp->_p++;
		temp = sqstd_rex_newnode(exp,OP_OR);
		exp->_nodes[temp].left = ret;
		tright = sqstd_rex_list(exp);
		exp->_nodes[temp].right = tright;
		ret = temp;
	}
	return ret;
}

static SQBool sqstd_rex_matchcclass(SQInteger cclass,SQChar c)
{
	switch(cclass) {
	case 'a': return isalpha(c)?SQTrue:SQFalse;
	case 'A': return !isalpha(c)?SQTrue:SQFalse;
	case 'w': return (isalnum(c) || c == '_')?SQTrue:SQFalse;
	case 'W': return (!isalnum(c) && c != '_')?SQTrue:SQFalse;
	case 's': return isspace(c)?SQTrue:SQFalse;
	case 'S': return !isspace(c)?SQTrue:SQFalse;
	case 'd': return isdigit(c)?SQTrue:SQFalse;
	case 'D': return !isdigit(c)?SQTrue:SQFalse;
	case 'x': return isxdigit(c)?SQTrue:SQFalse;
	case 'X': return !isxdigit(c)?SQTrue:SQFalse;
	case 'c': return iscntrl(c)?SQTrue:SQFalse;
	case 'C': return !iscntrl(c)?SQTrue:SQFalse;
	case 'p': return ispunct(c)?SQTrue:SQFalse;
	case 'P': return !ispunct(c)?SQTrue:SQFalse;
	case 'l': return islower(c)?SQTrue:SQFalse;
	case 'u': return isupper(c)?SQTrue:SQFalse;
	}
	return SQFalse; /*cannot happen*/
}

static SQBool sqstd_rex_matchclass(SQRex* exp,SQRexNode *node,SQChar c)
{
	do {
		switch(node->type) {
			case OP_RANGE:
				if(c >= node->left && c <= node->right) return SQTrue;
				break;
			case OP_CCLASS:
				if(sqstd_rex_matchcclass(node->left,c)) return SQTrue;
				break;
			default:
				if(c == node->type)return SQTrue;
		}
	} while((node->next != -1) && (node = &exp->_nodes[node->next]));
	return SQFalse;
}

static const SQChar *sqstd_rex_matchnode(SQRex* exp,SQRexNode *node,const SQChar *str,SQRexNode *next)
{
	
	SQRexNodeType type = node->type;
	switch(type) {
	case OP_GREEDY: {
		//SQRexNode *greedystop = (node->next != -1) ? &exp->_nodes[node->next] : NULL;
		SQRexNode *greedystop = NULL;
		SQInteger p0 = (node->right >> 16)&0x0000FFFF, p1 = node->right&0x0000FFFF, nmaches = 0;
		const SQChar *s=str, *good = str;

		if(node->next != -1) {
			greedystop = &exp->_nodes[node->next];
		}
		else {
			greedystop = next;
		}

		while((nmaches == 0xFFFF || nmaches < p1)) {

			const SQChar *stop;
			if(!(s = sqstd_rex_matchnode(exp,&exp->_nodes[node->left],s,greedystop)))
				break;
			nmaches++;
			good=s;
			if(greedystop) {
				//checks that 0 matches satisfy the expression(if so skips)
				//if not would always stop(for instance if is a '?')
				if(greedystop->type != OP_GREEDY ||
				(greedystop->type == OP_GREEDY && ((greedystop->right >> 16)&0x0000FFFF) != 0))
				{
					SQRexNode *gnext = NULL;
					if(greedystop->next != -1) {
						gnext = &exp->_nodes[greedystop->next];
					}else if(next && next->next != -1){
						gnext = &exp->_nodes[next->next];
					}
					stop = sqstd_rex_matchnode(exp,greedystop,s,gnext);
					if(stop) {
						//if satisfied stop it
						if(p0 == p1 && p0 == nmaches) break;
						else if(nmaches >= p0 && p1 == 0xFFFF) break;
						else if(nmaches >= p0 && nmaches <= p1) break;
					}
				}
			}
			
			if(s >= exp->_eol)
				break;
		}
		if(p0 == p1 && p0 == nmaches) return good;
		else if(nmaches >= p0 && p1 == 0xFFFF) return good;
		else if(nmaches >= p0 && nmaches <= p1) return good;
		return NULL;
	}
	case OP_OR: {
			const SQChar *asd = str;
			SQRexNode *temp=&exp->_nodes[node->left];
			while( (asd = sqstd_rex_matchnode(exp,temp,asd,NULL)) ) {
				if(temp->next != -1)
					temp = &exp->_nodes[temp->next];
				else
					return asd;
			}
			asd = str;
			temp = &exp->_nodes[node->right];
			while( (asd = sqstd_rex_matchnode(exp,temp,asd,NULL)) ) {
				if(temp->next != -1)
					temp = &exp->_nodes[temp->next];
				else
					return asd;
			}
			return NULL;
			break;
	}
	case OP_EXPR:
	case OP_NOCAPEXPR:{
			SQRexNode *n = &exp->_nodes[node->left];
			const SQChar *cur = str;
			SQInteger capture = -1;
			if(node->type != OP_NOCAPEXPR && node->right == exp->_currsubexp) {
				capture = exp->_currsubexp;
				exp->_matches[capture].begin = cur;
				exp->_currsubexp++;
			}
			int tempcap = exp->_currsubexp;
			do {
				SQRexNode *subnext = NULL;
				if(n->next != -1) {
					subnext = &exp->_nodes[n->next];
				}else {
					subnext = next;
				}
				if(!(cur = sqstd_rex_matchnode(exp,n,cur,subnext))) {
					if(capture != -1){
						exp->_matches[capture].begin = 0;
						exp->_matches[capture].len = 0;
					}
					return NULL;
				}
			} while((n->next != -1) && (n = &exp->_nodes[n->next]));

			exp->_currsubexp = tempcap;
			if(capture != -1) 
				exp->_matches[capture].len = cur - exp->_matches[capture].begin;
			return cur;
	}				 
	case OP_WB:
		if((str == exp->_bol && !isspace(*str))
		 || (str == exp->_eol && !isspace(*(str-1)))
		 || (!isspace(*str) && isspace(*(str+1)))
		 || (isspace(*str) && !isspace(*(str+1))) ) {
			return (node->left == 'b')?str:NULL;
		}
		return (node->left == 'b')?NULL:str;
	case OP_BOL:
		if(str == exp->_bol) return str;
		return NULL;
	case OP_EOL:
		if(str == exp->_eol) return str;
		return NULL;
	case OP_DOT:{
		str++;
				}
		return str;
	case OP_NCLASS:
	case OP_CLASS:
		if(sqstd_rex_matchclass(exp,&exp->_nodes[node->left],*str)?(type == OP_CLASS?SQTrue:SQFalse):(type == OP_NCLASS?SQTrue:SQFalse)) {
			str++;
			return str;
		}
		return NULL;
	case OP_CCLASS:
		if(sqstd_rex_matchcclass(node->left,*str)) {
			str++;
			return str;
		}
		return NULL;
	default: /* char */
		if(*str != node->type) return NULL;
		str++;
		return str;
	}
	return NULL;
}

/* public api */
SQRex *sqstd_rex_compile(const SQChar *pattern,const SQChar **error)
{
	SQRex *exp = (SQRex *)sq_malloc(sizeof(SQRex));
	exp->_eol = exp->_bol = NULL;
	exp->_p = pattern;
	exp->_nallocated = (SQInteger)scstrlen(pattern) * sizeof(SQChar);
	exp->_nodes = (SQRexNode *)sq_malloc(exp->_nallocated * sizeof(SQRexNode));
	exp->_nsize = 0;
	exp->_matches = 0;
	exp->_nsubexpr = 0;
	exp->_first = sqstd_rex_newnode(exp,OP_EXPR);
	exp->_error = error;
	exp->_jmpbuf = sq_malloc(sizeof(jmp_buf));
	if(setjmp(*((jmp_buf*)exp->_jmpbuf)) == 0) {
		SQInteger res = sqstd_rex_list(exp);
		exp->_nodes[exp->_first].left = res;
		if(*exp->_p!='\0')
			sqstd_rex_error(exp,_SC("unexpected character"));
#ifdef _DEBUG
		{
			SQInteger nsize,i;
			SQRexNode *t;
			nsize = exp->_nsize;
			t = &exp->_nodes[0];
			scprintf(_SC("\n"));
			for(i = 0;i < nsize; i++) {
				if(exp->_nodes[i].type>MAX_CHAR)
					scprintf(_SC("[%02d] %10s "),i,g_nnames[exp->_nodes[i].type-MAX_CHAR]);
				else
					scprintf(_SC("[%02d] %10c "),i,exp->_nodes[i].type);
				scprintf(_SC("left %02d right %02d next %02d\n"),exp->_nodes[i].left,exp->_nodes[i].right,exp->_nodes[i].next);
			}
			scprintf(_SC("\n"));
		}
#endif
		exp->_matches = (SQRexMatch *) sq_malloc(exp->_nsubexpr * sizeof(SQRexMatch));
		memset(exp->_matches,0,exp->_nsubexpr * sizeof(SQRexMatch));
	}
	else{
		sqstd_rex_free(exp);
		return NULL;
	}
	return exp;
}

void sqstd_rex_free(SQRex *exp)
{
	if(exp)	{
		if(exp->_nodes) sq_free(exp->_nodes,exp->_nallocated * sizeof(SQRexNode));
		if(exp->_jmpbuf) sq_free(exp->_jmpbuf,sizeof(jmp_buf));
		if(exp->_matches) sq_free(exp->_matches,exp->_nsubexpr * sizeof(SQRexMatch));
		sq_free(exp,sizeof(SQRex));
	}
}

SQBool sqstd_rex_match(SQRex* exp,const SQChar* text)
{
	const SQChar* res = NULL;
	exp->_bol = text;
	exp->_eol = text + scstrlen(text);
	exp->_currsubexp = 0;
	res = sqstd_rex_matchnode(exp,exp->_nodes,text,NULL);
	if(res == NULL || res != exp->_eol)
		return SQFalse;
	return SQTrue;
}

SQBool sqstd_rex_searchrange(SQRex* exp,const SQChar* text_begin,const SQChar* text_end,const SQChar** out_begin, const SQChar** out_end)
{
	const SQChar *cur = NULL;
	SQInteger node = exp->_first;
	if(text_begin >= text_end) return SQFalse;
	exp->_bol = text_begin;
	exp->_eol = text_end;
	do {
		cur = text_begin;
		while(node != -1) {
			exp->_currsubexp = 0;
			cur = sqstd_rex_matchnode(exp,&exp->_nodes[node],cur,NULL);
			if(!cur)
				break;
			node = exp->_nodes[node].next;
		}
		text_begin++;
	} while(cur == NULL && text_begin != text_end);

	if(cur == NULL)
		return SQFalse;

	--text_begin;

	if(out_begin) *out_begin = text_begin;
	if(out_end) *out_end = cur;
	return SQTrue;
}

SQBool sqstd_rex_search(SQRex* exp,const SQChar* text, const SQChar** out_begin, const SQChar** out_end)
{
	return sqstd_rex_searchrange(exp,text,text + scstrlen(text),out_begin,out_end);
}

SQInteger sqstd_rex_getsubexpcount(SQRex* exp)
{
	return exp->_nsubexpr;
}

SQBool sqstd_rex_getsubexp(SQRex* exp, SQInteger n, SQRexMatch *subexp)
{
	if( n<0 || n >= exp->_nsubexpr) return SQFalse;
	*subexp = exp->_matches[n];
	return SQTrue;
}


// ******************************** sqstdstream.cpp ********************************
/* see copyright notice in squirrel.h */
#include <new>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqstdstream.cpp
// ---- #include <sqstdio.h>
// ---> including sqstdio.h
// <--- back to sqstdstream.cpp
// ---- #include <sqstdblob.h>
// ---> including sqstdblob.h
// <--- back to sqstdstream.cpp
// ---- #include "sqstdstream.h"
// ---> including sqstdstream.h
// <--- back to sqstdstream.cpp
// ---- #include "sqstdblobimpl.h"
// ---> including sqstdblobimpl.h
// <--- back to sqstdstream.cpp

#define SETUP_STREAM(v) \
	SQStream *self = NULL; \
	if(SQ_FAILED(sq_getinstanceup(v,1,(SQUserPointer*)&self,(SQUserPointer)SQSTD_STREAM_TYPE_TAG))) \
		return sq_throwerror(v,_SC("invalid type tag")); \
	if(!self || !self->IsValid())  \
		return sq_throwerror(v,_SC("the stream is invalid"));

SQInteger _stream_readblob(HSQUIRRELVM v)
{
	SETUP_STREAM(v);
	SQUserPointer data,blobp;
	SQInteger size,res;
	sq_getinteger(v,2,&size);
	if(size > self->Len()) {
		size = self->Len();
	}
	data = sq_getscratchpad(v,size);
	res = self->Read(data,size);
	if(res <= 0)
		return sq_throwerror(v,_SC("no data left to read"));
	blobp = sqstd_createblob(v,res);
	memcpy(blobp,data,res);
	return 1;
}

#define SAFE_READN(ptr,len) { \
	if(self->Read(ptr,len) != len) return sq_throwerror(v,_SC("io error")); \
	}
SQInteger _stream_readn(HSQUIRRELVM v)
{
	SETUP_STREAM(v);
	SQInteger format;
	sq_getinteger(v, 2, &format);
	switch(format) {
	case 'l': {
		SQInteger i;
		SAFE_READN(&i, sizeof(i));
		sq_pushinteger(v, i);
			  }
		break;
	case 'i': {
		SQInt32 i;
		SAFE_READN(&i, sizeof(i));
		sq_pushinteger(v, i);
			  }
		break;
	case 's': {
		short s;
		SAFE_READN(&s, sizeof(short));
		sq_pushinteger(v, s);
			  }
		break;
	case 'w': {
		unsigned short w;
		SAFE_READN(&w, sizeof(unsigned short));
		sq_pushinteger(v, w);
			  }
		break;
	case 'c': {
		char c;
		SAFE_READN(&c, sizeof(char));
		sq_pushinteger(v, c);
			  }
		break;
	case 'b': {
		unsigned char c;
		SAFE_READN(&c, sizeof(unsigned char));
		sq_pushinteger(v, c);
			  }
		break;
	case 'f': {
		float f;
		SAFE_READN(&f, sizeof(float));
		sq_pushfloat(v, f);
			  }
		break;
	case 'd': {
		double d;
		SAFE_READN(&d, sizeof(double));
		sq_pushfloat(v, (SQFloat)d);
			  }
		break;
	default:
		return sq_throwerror(v, _SC("invalid format"));
	}
	return 1;
}

SQInteger _stream_writeblob(HSQUIRRELVM v)
{
	SQUserPointer data;
	SQInteger size;
	SETUP_STREAM(v);
	if(SQ_FAILED(sqstd_getblob(v,2,&data)))
		return sq_throwerror(v,_SC("invalid parameter"));
	size = sqstd_getblobsize(v,2);
	if(self->Write(data,size) != size)
		return sq_throwerror(v,_SC("io error"));
	sq_pushinteger(v,size);
	return 1;
}

SQInteger _stream_writen(HSQUIRRELVM v)
{
	SETUP_STREAM(v);
	SQInteger format, ti;
	SQFloat tf;
	sq_getinteger(v, 3, &format);
	switch(format) {
	case 'l': {
		SQInteger i;
		sq_getinteger(v, 2, &ti);
		i = ti;
		self->Write(&i, sizeof(SQInteger));
			  }
		break;
	case 'i': {
		SQInt32 i;
		sq_getinteger(v, 2, &ti);
		i = (SQInt32)ti;
		self->Write(&i, sizeof(SQInt32));
			  }
		break;
	case 's': {
		short s;
		sq_getinteger(v, 2, &ti);
		s = (short)ti;
		self->Write(&s, sizeof(short));
			  }
		break;
	case 'w': {
		unsigned short w;
		sq_getinteger(v, 2, &ti);
		w = (unsigned short)ti;
		self->Write(&w, sizeof(unsigned short));
			  }
		break;
	case 'c': {
		char c;
		sq_getinteger(v, 2, &ti);
		c = (char)ti;
		self->Write(&c, sizeof(char));
				  }
		break;
	case 'b': {
		unsigned char b;
		sq_getinteger(v, 2, &ti);
		b = (unsigned char)ti;
		self->Write(&b, sizeof(unsigned char));
			  }
		break;
	case 'f': {
		float f;
		sq_getfloat(v, 2, &tf);
		f = (float)tf;
		self->Write(&f, sizeof(float));
			  }
		break;
	case 'd': {
		double d;
		sq_getfloat(v, 2, &tf);
		d = tf;
		self->Write(&d, sizeof(double));
			  }
		break;
	default:
		return sq_throwerror(v, _SC("invalid format"));
	}
	return 0;
}

SQInteger _stream_seek(HSQUIRRELVM v)
{
	SETUP_STREAM(v);
	SQInteger offset, origin = SQ_SEEK_SET;
	sq_getinteger(v, 2, &offset);
	if(sq_gettop(v) > 2) {
		SQInteger t;
		sq_getinteger(v, 3, &t);
		switch(t) {
			case 'b': origin = SQ_SEEK_SET; break;
			case 'c': origin = SQ_SEEK_CUR; break;
			case 'e': origin = SQ_SEEK_END; break;
			default: return sq_throwerror(v,_SC("invalid origin"));
		}
	}
	sq_pushinteger(v, self->Seek(offset, origin));
	return 1;
}

SQInteger _stream_tell(HSQUIRRELVM v)
{
	SETUP_STREAM(v);
	sq_pushinteger(v, self->Tell());
	return 1;
}

SQInteger _stream_len(HSQUIRRELVM v)
{
	SETUP_STREAM(v);
	sq_pushinteger(v, self->Len());
	return 1;
}

SQInteger _stream_flush(HSQUIRRELVM v)
{
	SETUP_STREAM(v);
	if(!self->Flush())
		sq_pushinteger(v, 1);
	else
		sq_pushnull(v);
	return 1;
}

SQInteger _stream_eos(HSQUIRRELVM v)
{
	SETUP_STREAM(v);
	if(self->EOS())
		sq_pushinteger(v, 1);
	else
		sq_pushnull(v);
	return 1;
}

 SQInteger _stream__cloned(HSQUIRRELVM v)
 {
	 return sq_throwerror(v,_SC("this object cannot be cloned"));
 }

static SQRegFunction _stream_methods[] = {
	_DECL_STREAM_FUNC(readblob,2,_SC("xn")),
	_DECL_STREAM_FUNC(readn,2,_SC("xn")),
	_DECL_STREAM_FUNC(writeblob,-2,_SC("xx")),
	_DECL_STREAM_FUNC(writen,3,_SC("xnn")),
	_DECL_STREAM_FUNC(seek,-2,_SC("xnn")),
	_DECL_STREAM_FUNC(tell,1,_SC("x")),
	_DECL_STREAM_FUNC(len,1,_SC("x")),
	_DECL_STREAM_FUNC(eos,1,_SC("x")),
	_DECL_STREAM_FUNC(flush,1,_SC("x")),
	_DECL_STREAM_FUNC(_cloned,0,NULL),
	{0,0}
};

void init_streamclass(HSQUIRRELVM v)
{
	sq_pushregistrytable(v);
	sq_pushstring(v,_SC("std_stream"),-1);
	if(SQ_FAILED(sq_get(v,-2))) {
		sq_pushstring(v,_SC("std_stream"),-1);
		sq_newclass(v,SQFalse);
		sq_settypetag(v,-1,(SQUserPointer)SQSTD_STREAM_TYPE_TAG);
		SQInteger i = 0;
		while(_stream_methods[i].name != 0) {
			SQRegFunction &f = _stream_methods[i];
			sq_pushstring(v,f.name,-1);
			sq_newclosure(v,f.f,0);
			sq_setparamscheck(v,f.nparamscheck,f.typemask);
			sq_newslot(v,-3,SQFalse);
			i++;
		}
		sq_newslot(v,-3,SQFalse);
		sq_pushroottable(v);
		sq_pushstring(v,_SC("stream"),-1);
		sq_pushstring(v,_SC("std_stream"),-1);
		sq_get(v,-4);
		sq_newslot(v,-3,SQFalse);
		sq_pop(v,1);
	}
	else {
		sq_pop(v,1); //result
	}
	sq_pop(v,1);
}

SQRESULT declare_stream(HSQUIRRELVM v,const SQChar* name,SQUserPointer typetag,const SQChar* reg_name,SQRegFunction *methods,SQRegFunction *globals)
{
	if(sq_gettype(v,-1) != OT_TABLE)
		return sq_throwerror(v,_SC("table expected"));
	SQInteger top = sq_gettop(v);
	//create delegate
    init_streamclass(v);
	sq_pushregistrytable(v);
	sq_pushstring(v,reg_name,-1);
	sq_pushstring(v,_SC("std_stream"),-1);
	if(SQ_SUCCEEDED(sq_get(v,-3))) {
		sq_newclass(v,SQTrue);
		sq_settypetag(v,-1,typetag);
		SQInteger i = 0;
		while(methods[i].name != 0) {
			SQRegFunction &f = methods[i];
			sq_pushstring(v,f.name,-1);
			sq_newclosure(v,f.f,0);
			sq_setparamscheck(v,f.nparamscheck,f.typemask);
			sq_setnativeclosurename(v,-1,f.name);
			sq_newslot(v,-3,SQFalse);
			i++;
		}
		sq_newslot(v,-3,SQFalse);
		sq_pop(v,1);
		
		i = 0;
		while(globals[i].name!=0)
		{
			SQRegFunction &f = globals[i];
			sq_pushstring(v,f.name,-1);
			sq_newclosure(v,f.f,0);
			sq_setparamscheck(v,f.nparamscheck,f.typemask);
			sq_setnativeclosurename(v,-1,f.name);
			sq_newslot(v,-3,SQFalse);
			i++;
		}
		//register the class in the target table
		sq_pushstring(v,name,-1);
		sq_pushregistrytable(v);
		sq_pushstring(v,reg_name,-1);
		sq_get(v,-2);
		sq_remove(v,-2);
		sq_newslot(v,-3,SQFalse);

		sq_settop(v,top);
		return SQ_OK;
	}
	sq_settop(v,top);
	return SQ_ERROR;
}

// ******************************** sqstdstring.cpp ********************************
/* see copyright notice in squirrel.h */
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqstdstring.cpp
// ---- #include <sqstdstring.h>
// ---> including sqstdstring.h
// <--- back to sqstdstring.cpp
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#ifdef SQUNICODE
#define scstrchr wcschr
#define scsnprintf wsnprintf
#define scatoi _wtoi
#define scstrtok wcstok
#else
#define scstrchr strchr
#define scsnprintf snprintf
#define scatoi atoi
#define scstrtok strtok
#endif
#define MAX_FORMAT_LEN	20
#define MAX_WFORMAT_LEN	3
#define ADDITIONAL_FORMAT_SPACE (100*sizeof(SQChar))

static SQInteger validate_format(HSQUIRRELVM v, SQChar *fmt, const SQChar *src, SQInteger n,SQInteger &width)
{
	SQChar swidth[MAX_WFORMAT_LEN];
	SQInteger wc = 0;
	SQInteger start = n;
	fmt[0] = '%';
	while (scstrchr(_SC("-+ #0"), src[n])) n++;
	while (scisdigit(src[n])) {
		swidth[wc] = src[n];
		n++;
		wc++;
		if(wc>=MAX_WFORMAT_LEN)
			return sq_throwerror(v,_SC("width format too long"));
	}
	swidth[wc] = '\0';
	if(wc > 0) {
		width = scatoi(swidth);
	}
	else
		width = 0;
	if (src[n] == '.') {
	    n++;
    	
		wc = 0;
		while (scisdigit(src[n])) {
			swidth[wc] = src[n];
			n++;
			wc++;
			if(wc>=MAX_WFORMAT_LEN)
				return sq_throwerror(v,_SC("precision format too long"));
		}
		swidth[wc] = '\0';
		if(wc > 0) {
			width += scatoi(swidth);
		}
	}
	if (n-start > MAX_FORMAT_LEN )
		return sq_throwerror(v,_SC("format too long"));
	memcpy(&fmt[1],&src[start],((n-start)+1)*sizeof(SQChar));
	fmt[(n-start)+2] = '\0';
	return n;
}

SQRESULT sqstd_format(HSQUIRRELVM v,SQInteger nformatstringidx,SQInteger *outlen,SQChar **output)
{
	const SQChar *format;
	SQChar *dest;
	SQChar fmt[MAX_FORMAT_LEN];
	sq_getstring(v,nformatstringidx,&format);
	SQInteger allocated = (sq_getsize(v,nformatstringidx)+2)*sizeof(SQChar);
	dest = sq_getscratchpad(v,allocated);
	SQInteger n = 0,i = 0, nparam = nformatstringidx+1, w = 0;
	while(format[n] != '\0') {
		if(format[n] != '%') {
			assert(i < allocated);
			dest[i++] = format[n];
			n++;
		}
		else if(format[n+1] == '%') { //handles %%
				dest[i++] = '%';
				n += 2; 
		}
		else {
			n++;
			if( nparam > sq_gettop(v) )
				return sq_throwerror(v,_SC("not enough paramters for the given format string"));
			n = validate_format(v,fmt,format,n,w);
			if(n < 0) return -1;
			SQInteger addlen = 0;
			SQInteger valtype = 0;
			const SQChar *ts;
			SQInteger ti;
			SQFloat tf;
			switch(format[n]) {
			case 's':
				if(SQ_FAILED(sq_getstring(v,nparam,&ts))) 
					return sq_throwerror(v,_SC("string expected for the specified format"));
				addlen = (sq_getsize(v,nparam)*sizeof(SQChar))+((w+1)*sizeof(SQChar));
				valtype = 's';
				break;
			case 'i': case 'd': case 'o': case 'u':  case 'x':  case 'X':
#ifdef _SQ64
				{
				size_t flen = scstrlen(fmt);
				SQInteger fpos = flen - 1;
				SQChar f = fmt[fpos];
				SQChar *prec = (SQChar *)_PRINT_INT_PREC;
				while(*prec != _SC('\0')) {
					fmt[fpos++] = *prec++;
				}
				fmt[fpos++] = f;
				fmt[fpos++] = _SC('\0');
				}
#endif
			case 'c':
				if(SQ_FAILED(sq_getinteger(v,nparam,&ti))) 
					return sq_throwerror(v,_SC("integer expected for the specified format"));
				addlen = (ADDITIONAL_FORMAT_SPACE)+((w+1)*sizeof(SQChar));
				valtype = 'i';
				break;
			case 'f': case 'g': case 'G': case 'e':  case 'E':
				if(SQ_FAILED(sq_getfloat(v,nparam,&tf))) 
					return sq_throwerror(v,_SC("float expected for the specified format"));
				addlen = (ADDITIONAL_FORMAT_SPACE)+((w+1)*sizeof(SQChar));
				valtype = 'f';
				break;
			default:
				return sq_throwerror(v,_SC("invalid format"));
			}
			n++;
			allocated += addlen + sizeof(SQChar);
			dest = sq_getscratchpad(v,allocated);
			switch(valtype) {
			case 's': i += scsprintf(&dest[i],fmt,ts); break;
			case 'i': i += scsprintf(&dest[i],fmt,ti); break;
			case 'f': i += scsprintf(&dest[i],fmt,tf); break;
			};
			nparam ++;
		}
	}
	*outlen = i;
	dest[i] = '\0';
	*output = dest;
	return SQ_OK;
}

static SQInteger _string_format(HSQUIRRELVM v)
{
	SQChar *dest = NULL;
	SQInteger length = 0;
	if(SQ_FAILED(sqstd_format(v,2,&length,&dest)))
		return -1;
	sq_pushstring(v,dest,length);
	return 1;
}

static void __strip_l(const SQChar *str,const SQChar **start)
{
	const SQChar *t = str;
	while(((*t) != '\0') && scisspace(*t)){ t++; }
	*start = t;
}

static void __strip_r(const SQChar *str,SQInteger len,const SQChar **end)
{
	if(len == 0) {
		*end = str;
		return;
	}
	const SQChar *t = &str[len-1];
	while(t != str && scisspace(*t)) { t--; }
	*end = t+1;
}

static SQInteger _string_strip(HSQUIRRELVM v)
{
	const SQChar *str,*start,*end;
	sq_getstring(v,2,&str);
	SQInteger len = sq_getsize(v,2);
	__strip_l(str,&start);
	__strip_r(str,len,&end);
	sq_pushstring(v,start,end - start);
	return 1;
}

static SQInteger _string_lstrip(HSQUIRRELVM v)
{
	const SQChar *str,*start;
	sq_getstring(v,2,&str);
	__strip_l(str,&start);
	sq_pushstring(v,start,-1);
	return 1;
}

static SQInteger _string_rstrip(HSQUIRRELVM v)
{
	const SQChar *str,*end;
	sq_getstring(v,2,&str);
	SQInteger len = sq_getsize(v,2);
	__strip_r(str,len,&end);
	sq_pushstring(v,str,end - str);
	return 1;
}

static SQInteger _string_split(HSQUIRRELVM v)
{
	const SQChar *str,*seps;
	SQChar *stemp,*tok;
	sq_getstring(v,2,&str);
	sq_getstring(v,3,&seps);
	if(sq_getsize(v,3) == 0) return sq_throwerror(v,_SC("empty separators string"));
	SQInteger memsize = (sq_getsize(v,2)+1)*sizeof(SQChar);
	stemp = sq_getscratchpad(v,memsize);
	memcpy(stemp,str,memsize);
	tok = scstrtok(stemp,seps);
	sq_newarray(v,0);
	while( tok != NULL ) {
		sq_pushstring(v,tok,-1);
		sq_arrayappend(v,-2);
		tok = scstrtok( NULL, seps );
	}
	return 1;
}

#define SETUP_REX(v) \
	SQRex *self = NULL; \
	sq_getinstanceup(v,1,(SQUserPointer *)&self,0); 

static SQInteger _rexobj_releasehook(SQUserPointer p, SQInteger size)
{
	SQRex *self = ((SQRex *)p);
	sqstd_rex_free(self);
	return 1;
}

static SQInteger _regexp_match(HSQUIRRELVM v)
{
	SETUP_REX(v);
	const SQChar *str;
	sq_getstring(v,2,&str);
	if(sqstd_rex_match(self,str) == SQTrue)
	{
		sq_pushbool(v,SQTrue);
		return 1;
	}
	sq_pushbool(v,SQFalse);
	return 1;
}

static void _addrexmatch(HSQUIRRELVM v,const SQChar *str,const SQChar *begin,const SQChar *end)
{
	sq_newtable(v);
	sq_pushstring(v,_SC("begin"),-1);
	sq_pushinteger(v,begin - str);
	sq_rawset(v,-3);
	sq_pushstring(v,_SC("end"),-1);
	sq_pushinteger(v,end - str);
	sq_rawset(v,-3);
}

static SQInteger _regexp_search(HSQUIRRELVM v)
{
	SETUP_REX(v);
	const SQChar *str,*begin,*end;
	SQInteger start = 0;
	sq_getstring(v,2,&str);
	if(sq_gettop(v) > 2) sq_getinteger(v,3,&start);
	if(sqstd_rex_search(self,str+start,&begin,&end) == SQTrue) {
		_addrexmatch(v,str,begin,end);
		return 1;
	}
	return 0;
}

static SQInteger _regexp_capture(HSQUIRRELVM v)
{
	SETUP_REX(v);
	const SQChar *str,*begin,*end;
	SQInteger start = 0;
	sq_getstring(v,2,&str);
	if(sq_gettop(v) > 2) sq_getinteger(v,3,&start);
	if(sqstd_rex_search(self,str+start,&begin,&end) == SQTrue) {
		SQInteger n = sqstd_rex_getsubexpcount(self);
		SQRexMatch match;
		sq_newarray(v,0);
		for(SQInteger i = 0;i < n; i++) {
			sqstd_rex_getsubexp(self,i,&match);
			if(match.len > 0)
				_addrexmatch(v,str,match.begin,match.begin+match.len);
			else
				_addrexmatch(v,str,str,str); //empty match
			sq_arrayappend(v,-2);
		}
		return 1;
	}
	return 0;
}

static SQInteger _regexp_subexpcount(HSQUIRRELVM v)
{
	SETUP_REX(v);
	sq_pushinteger(v,sqstd_rex_getsubexpcount(self));
	return 1;
}

static SQInteger _regexp_constructor(HSQUIRRELVM v)
{
	const SQChar *error,*pattern;
	sq_getstring(v,2,&pattern);
	SQRex *rex = sqstd_rex_compile(pattern,&error);
	if(!rex) return sq_throwerror(v,error);
	sq_setinstanceup(v,1,rex);
	sq_setreleasehook(v,1,_rexobj_releasehook);
	return 0;
}

static SQInteger _regexp__typeof(HSQUIRRELVM v)
{
	sq_pushstring(v,_SC("regexp"),-1);
	return 1;
}

#define _DECL_REX_FUNC(name,nparams,pmask) {_SC(#name),_regexp_##name,nparams,pmask}
static SQRegFunction rexobj_funcs[]={
	_DECL_REX_FUNC(constructor,2,_SC(".s")),
	_DECL_REX_FUNC(search,-2,_SC("xsn")),
	_DECL_REX_FUNC(match,2,_SC("xs")),
	_DECL_REX_FUNC(capture,-2,_SC("xsn")),
	_DECL_REX_FUNC(subexpcount,1,_SC("x")),
	_DECL_REX_FUNC(_typeof,1,_SC("x")),
	{0,0}
};
#undef _DECL_REX_FUNC

#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),_string_##name,nparams,pmask}
static SQRegFunction stringlib_funcs[]={
	_DECL_FUNC(format,-2,_SC(".s")),
	_DECL_FUNC(strip,2,_SC(".s")),
	_DECL_FUNC(lstrip,2,_SC(".s")),
	_DECL_FUNC(rstrip,2,_SC(".s")),
	_DECL_FUNC(split,3,_SC(".ss")),
	{0,0}
};
#undef _DECL_FUNC


SQInteger sqstd_register_stringlib(HSQUIRRELVM v)
{
	sq_pushstring(v,_SC("regexp"),-1);
	sq_newclass(v,SQFalse);
	SQInteger i = 0;
	while(rexobj_funcs[i].name != 0) {
		SQRegFunction &f = rexobj_funcs[i];
		sq_pushstring(v,f.name,-1);
		sq_newclosure(v,f.f,0);
		sq_setparamscheck(v,f.nparamscheck,f.typemask);
		sq_setnativeclosurename(v,-1,f.name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}
	sq_newslot(v,-3,SQFalse);

	i = 0;
	while(stringlib_funcs[i].name!=0)
	{
		sq_pushstring(v,stringlib_funcs[i].name,-1);
		sq_newclosure(v,stringlib_funcs[i].f,0);
		sq_setparamscheck(v,stringlib_funcs[i].nparamscheck,stringlib_funcs[i].typemask);
		sq_setnativeclosurename(v,-1,stringlib_funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}
	return 1;
}

// ******************************** sqstdsystem.cpp ********************************
/* see copyright notice in squirrel.h */
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqstdsystem.cpp
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
// ---- #include <sqstdsystem.h>
// ---> including sqstdsystem.h
// <--- back to sqstdsystem.cpp

#ifdef SQUNICODE
#include <wchar.h>
#define scgetenv _wgetenv
#define scsystem _wsystem
#define scasctime _wasctime
#define scremove _wremove
#define screname _wrename
#else
#define scgetenv getenv
#define scsystem system
#define scasctime asctime
#define scremove remove
#define screname rename
#endif

static SQInteger _system_getenv(HSQUIRRELVM v)
{
	const SQChar *s;
	if(SQ_SUCCEEDED(sq_getstring(v,2,&s))){
        sq_pushstring(v,scgetenv(s),-1);
		return 1;
	}
	return 0;
}


static SQInteger _system_system(HSQUIRRELVM v)
{
	const SQChar *s;
	if(SQ_SUCCEEDED(sq_getstring(v,2,&s))){
		sq_pushinteger(v,scsystem(s));
		return 1;
	}
	return sq_throwerror(v,_SC("wrong param"));
}


static SQInteger _system_clock(HSQUIRRELVM v)
{
	sq_pushfloat(v,((SQFloat)clock())/(SQFloat)CLOCKS_PER_SEC);
	return 1;
}

static SQInteger _system_time(HSQUIRRELVM v)
{
	time_t t;
	time(&t);
	sq_pushinteger(v,*((SQInteger *)&t));
	return 1;
}

static SQInteger _system_remove(HSQUIRRELVM v)
{
	const SQChar *s;
	sq_getstring(v,2,&s);
	if(scremove(s)==-1)
		return sq_throwerror(v,_SC("remove() failed"));
	return 0;
}

static SQInteger _system_rename(HSQUIRRELVM v)
{
	const SQChar *oldn,*newn;
	sq_getstring(v,2,&oldn);
	sq_getstring(v,3,&newn);
	if(screname(oldn,newn)==-1)
		return sq_throwerror(v,_SC("rename() failed"));
	return 0;
}

static void _set_integer_slot(HSQUIRRELVM v,const SQChar *name,SQInteger val)
{
	sq_pushstring(v,name,-1);
	sq_pushinteger(v,val);
	sq_rawset(v,-3);
}

static SQInteger _system_date(HSQUIRRELVM v)
{
	time_t t;
	SQInteger it;
	SQInteger format = 'l';
	if(sq_gettop(v) > 1) {
		sq_getinteger(v,2,&it);
		t = it;
		if(sq_gettop(v) > 2) {
			sq_getinteger(v,3,(SQInteger*)&format);
		}
	}
	else {
		time(&t);
	}
	tm *date;
    if(format == 'u')
		date = gmtime(&t);
	else
		date = localtime(&t);
	if(!date)
		return sq_throwerror(v,_SC("crt api failure"));
	sq_newtable(v);
	_set_integer_slot(v, _SC("sec"), date->tm_sec);
    _set_integer_slot(v, _SC("min"), date->tm_min);
    _set_integer_slot(v, _SC("hour"), date->tm_hour);
    _set_integer_slot(v, _SC("day"), date->tm_mday);
    _set_integer_slot(v, _SC("month"), date->tm_mon);
    _set_integer_slot(v, _SC("year"), date->tm_year+1900);
    _set_integer_slot(v, _SC("wday"), date->tm_wday);
    _set_integer_slot(v, _SC("yday"), date->tm_yday);
	return 1;
}



#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),_system_##name,nparams,pmask}
static SQRegFunction systemlib_funcs[]={
	_DECL_FUNC(getenv,2,_SC(".s")),
	_DECL_FUNC(system,2,_SC(".s")),
	_DECL_FUNC(clock,0,NULL),
	_DECL_FUNC(time,1,NULL),
	_DECL_FUNC(date,-1,_SC(".nn")),
	_DECL_FUNC(remove,2,_SC(".s")),
	_DECL_FUNC(rename,3,_SC(".ss")),
	{0,0}
};
#undef _DECL_FUNC

SQInteger sqstd_register_systemlib(HSQUIRRELVM v)
{
	SQInteger i=0;
	while(systemlib_funcs[i].name!=0)
	{
		sq_pushstring(v,systemlib_funcs[i].name,-1);
		sq_newclosure(v,systemlib_funcs[i].f,0);
		sq_setparamscheck(v,systemlib_funcs[i].nparamscheck,systemlib_funcs[i].typemask);
		sq_setnativeclosurename(v,-1,systemlib_funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}
	return 1;
}

// ******************************** sqapi.cpp ********************************
/*
	see copyright notice in squirrel.h
*/
// ---- #include "sqpcheader.h"
// ---> including sqpcheader.h
/*	see copyright notice in squirrel.h */
#ifndef _SQPCHEADER_H_
#define _SQPCHEADER_H_

#if defined(_MSC_VER) && defined(_DEBUG)
#include <crtdbg.h>
#endif 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <new>
//squirrel stuff
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqpcheader.h
// ---- #include "sqobject.h"
// ---> including sqobject.h
/*	see copyright notice in squirrel.h */
#ifndef _SQOBJECT_H_
#define _SQOBJECT_H_

// ---- #include "squtils.h"
// ---> including squtils.h
/*	see copyright notice in squirrel.h */
#ifndef _SQUTILS_H_
#define _SQUTILS_H_

void *sq_vm_malloc(SQUnsignedInteger size);
void *sq_vm_realloc(void *p,SQUnsignedInteger oldsize,SQUnsignedInteger size);
void sq_vm_free(void *p,SQUnsignedInteger size);

#define sq_new(__ptr,__type) {__ptr=(__type *)sq_vm_malloc(sizeof(__type));new (__ptr) __type;}
#define sq_delete(__ptr,__type) {__ptr->~__type();sq_vm_free(__ptr,sizeof(__type));}
#define SQ_MALLOC(__size) sq_vm_malloc((__size));
#define SQ_FREE(__ptr,__size) sq_vm_free((__ptr),(__size));
#define SQ_REALLOC(__ptr,__oldsize,__size) sq_vm_realloc((__ptr),(__oldsize),(__size));

#define sq_aligning(v) (((size_t)(v) + (SQ_ALIGNMENT-1)) & (~(SQ_ALIGNMENT-1)))

//sqvector mini vector class, supports objects by value
template<typename T> class sqvector
{
public:
	sqvector()
	{
		_vals = NULL;
		_size = 0;
		_allocated = 0;
	}
	sqvector(const sqvector<T>& v)
	{
		copy(v);
	}
	void copy(const sqvector<T>& v)
	{
		if(_size) {
			resize(0); //destroys all previous stuff
		}
		//resize(v._size);
		if(v._size > _allocated) {
			_realloc(v._size);
		}
		for(SQUnsignedInteger i = 0; i < v._size; i++) {
			new ((void *)&_vals[i]) T(v._vals[i]);
		}
		_size = v._size;
	}
	~sqvector()
	{
		if(_allocated) {
			for(SQUnsignedInteger i = 0; i < _size; i++)
				_vals[i].~T();
			SQ_FREE(_vals, (_allocated * sizeof(T)));
		}
	}
	void reserve(SQUnsignedInteger newsize) { _realloc(newsize); }
	void resize(SQUnsignedInteger newsize, const T& fill = T())
	{
		if(newsize > _allocated)
			_realloc(newsize);
		if(newsize > _size) {
			while(_size < newsize) {
				new ((void *)&_vals[_size]) T(fill);
				_size++;
			}
		}
		else{
			for(SQUnsignedInteger i = newsize; i < _size; i++) {
				_vals[i].~T();
			}
			_size = newsize;
		}
	}
	void shrinktofit() { if(_size > 4) { _realloc(_size); } }
	T& top() const { return _vals[_size - 1]; }
	inline SQUnsignedInteger size() const { return _size; }
	bool empty() const { return (_size <= 0); }
	inline T &push_back(const T& val = T())
	{
		if(_allocated <= _size)
			_realloc(_size * 2);
		return *(new ((void *)&_vals[_size++]) T(val));
	}
	inline void pop_back()
	{
		_size--; _vals[_size].~T();
	}
	void insert(SQUnsignedInteger idx, const T& val)
	{
		resize(_size + 1);
		for(SQUnsignedInteger i = _size - 1; i > idx; i--) {
			_vals[i] = _vals[i - 1];
		}
    	_vals[idx] = val;
	}
	void remove(SQUnsignedInteger idx)
	{
		_vals[idx].~T();
		if(idx < (_size - 1)) {
			memmove(&_vals[idx], &_vals[idx+1], sizeof(T) * (_size - idx - 1));
		}
		_size--;
	}
	SQUnsignedInteger capacity() { return _allocated; }
	inline T &back() const { return _vals[_size - 1]; }
	inline T& operator[](SQUnsignedInteger pos) const{ return _vals[pos]; }
	T* _vals;
private:
	void _realloc(SQUnsignedInteger newsize)
	{
		newsize = (newsize > 0)?newsize:4;
		_vals = (T*)SQ_REALLOC(_vals, _allocated * sizeof(T), newsize * sizeof(T));
		_allocated = newsize;
	}
	SQUnsignedInteger _size;
	SQUnsignedInteger _allocated;
};

#endif //_SQUTILS_H_

// <--- back to sqobject.h

#ifdef _SQ64
#define UINT_MINUS_ONE (0xFFFFFFFFFFFFFFFF)
#else
#define UINT_MINUS_ONE (0xFFFFFFFF)
#endif

#define SQ_CLOSURESTREAM_HEAD (('S'<<24)|('Q'<<16)|('I'<<8)|('R'))
#define SQ_CLOSURESTREAM_PART (('P'<<24)|('A'<<16)|('R'<<8)|('T'))
#define SQ_CLOSURESTREAM_TAIL (('T'<<24)|('A'<<16)|('I'<<8)|('L'))

struct SQSharedState;

enum SQMetaMethod{
	MT_ADD=0,
	MT_SUB=1,
	MT_MUL=2,
	MT_DIV=3,
	MT_UNM=4,
	MT_MODULO=5,
	MT_SET=6,
	MT_GET=7,
	MT_TYPEOF=8,
	MT_NEXTI=9,
	MT_CMP=10,
	MT_CALL=11,
	MT_CLONED=12,
	MT_NEWSLOT=13,
	MT_DELSLOT=14,
	MT_TOSTRING=15,
	MT_NEWMEMBER=16,
	MT_INHERITED=17,
	MT_LAST = 18
};

#define MM_ADD		_SC("_add")
#define MM_SUB		_SC("_sub")
#define MM_MUL		_SC("_mul")
#define MM_DIV		_SC("_div")
#define MM_UNM		_SC("_unm")
#define MM_MODULO	_SC("_modulo")
#define MM_SET		_SC("_set")
#define MM_GET		_SC("_get")
#define MM_TYPEOF	_SC("_typeof")
#define MM_NEXTI	_SC("_nexti")
#define MM_CMP		_SC("_cmp")
#define MM_CALL		_SC("_call")
#define MM_CLONED	_SC("_cloned")
#define MM_NEWSLOT	_SC("_newslot")
#define MM_DELSLOT	_SC("_delslot")
#define MM_TOSTRING	_SC("_tostring")
#define MM_NEWMEMBER _SC("_newmember")
#define MM_INHERITED _SC("_inherited")


#define _CONSTRUCT_VECTOR(type,size,ptr) { \
	for(SQInteger n = 0; n < ((SQInteger)size); n++) { \
			new (&ptr[n]) type(); \
		} \
}

#define _DESTRUCT_VECTOR(type,size,ptr) { \
	for(SQInteger nl = 0; nl < ((SQInteger)size); nl++) { \
			ptr[nl].~type(); \
	} \
}

#define _COPY_VECTOR(dest,src,size) { \
	for(SQInteger _n_ = 0; _n_ < ((SQInteger)size); _n_++) { \
		dest[_n_] = src[_n_]; \
	} \
}

#define _NULL_SQOBJECT_VECTOR(vec,size) { \
	for(SQInteger _n_ = 0; _n_ < ((SQInteger)size); _n_++) { \
		vec[_n_].Null(); \
	} \
}

#define MINPOWER2 4

struct SQRefCounted
{
	SQUnsignedInteger _uiRef;
	struct SQWeakRef *_weakref;
	SQRefCounted() { _uiRef = 0; _weakref = NULL; }
	virtual ~SQRefCounted();
	SQWeakRef *GetWeakRef(SQObjectType type);
	virtual void Release()=0;
	
};

struct SQWeakRef : SQRefCounted
{
	void Release();
	SQObject _obj;
};

#define _realval(o) (type((o)) != OT_WEAKREF?(SQObject)o:_weakref(o)->_obj)

struct SQObjectPtr;

#define __AddRef(type,unval) if(ISREFCOUNTED(type))	\
		{ \
			unval.pRefCounted->_uiRef++; \
		}  

#define __Release(type,unval) if(ISREFCOUNTED(type) && ((--unval.pRefCounted->_uiRef)==0))	\
		{	\
			unval.pRefCounted->Release();	\
		}

#define __ObjRelease(obj) { \
	if((obj)) {	\
		(obj)->_uiRef--; \
		if((obj)->_uiRef == 0) \
			(obj)->Release(); \
		(obj) = NULL;	\
	} \
}

#define __ObjAddRef(obj) { \
	(obj)->_uiRef++; \
}

#define type(obj) ((obj)._type)
#define is_delegable(t) (type(t)&SQOBJECT_DELEGABLE)
#define raw_type(obj) _RAW_TYPE((obj)._type)

#define _integer(obj) ((obj)._unVal.nInteger)
#define _float(obj) ((obj)._unVal.fFloat)
#define _string(obj) ((obj)._unVal.pString)
#define _table(obj) ((obj)._unVal.pTable)
#define _array(obj) ((obj)._unVal.pArray)
#define _closure(obj) ((obj)._unVal.pClosure)
#define _generator(obj) ((obj)._unVal.pGenerator)
#define _nativeclosure(obj) ((obj)._unVal.pNativeClosure)
#define _userdata(obj) ((obj)._unVal.pUserData)
#define _userpointer(obj) ((obj)._unVal.pUserPointer)
#define _thread(obj) ((obj)._unVal.pThread)
#define _funcproto(obj) ((obj)._unVal.pFunctionProto)
#define _class(obj) ((obj)._unVal.pClass)
#define _instance(obj) ((obj)._unVal.pInstance)
#define _delegable(obj) ((SQDelegable *)(obj)._unVal.pDelegable)
#define _weakref(obj) ((obj)._unVal.pWeakRef)
#define _outer(obj) ((obj)._unVal.pOuter)
#define _refcounted(obj) ((obj)._unVal.pRefCounted)
#define _rawval(obj) ((obj)._unVal.raw)

#define _stringval(obj) (obj)._unVal.pString->_val
#define _userdataval(obj) ((SQUserPointer)sq_aligning((obj)._unVal.pUserData + 1))

#define tofloat(num) ((type(num)==OT_INTEGER)?(SQFloat)_integer(num):_float(num))
#define tointeger(num) ((type(num)==OT_FLOAT)?(SQInteger)_float(num):_integer(num))
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#if defined(SQUSEDOUBLE) && !defined(_SQ64) || !defined(SQUSEDOUBLE) && defined(_SQ64)
#define SQ_REFOBJECT_INIT()	SQ_OBJECT_RAWINIT()
#else
#define SQ_REFOBJECT_INIT()
#endif

#define _REF_TYPE_DECL(type,_class,sym) \
	SQObjectPtr(_class * x) \
	{ \
		SQ_OBJECT_RAWINIT() \
		_type=type; \
		_unVal.sym = x; \
		assert(_unVal.pTable); \
		_unVal.pRefCounted->_uiRef++; \
	} \
	inline SQObjectPtr& operator=(_class *x) \
	{  \
		SQObjectType tOldType; \
		SQObjectValue unOldVal; \
		tOldType=_type; \
		unOldVal=_unVal; \
		_type = type; \
		SQ_REFOBJECT_INIT() \
		_unVal.sym = x; \
		_unVal.pRefCounted->_uiRef++; \
		__Release(tOldType,unOldVal); \
		return *this; \
	}

#define _SCALAR_TYPE_DECL(type,_class,sym) \
	SQObjectPtr(_class x) \
	{ \
		SQ_OBJECT_RAWINIT() \
		_type=type; \
		_unVal.sym = x; \
	} \
	inline SQObjectPtr& operator=(_class x) \
	{  \
		__Release(_type,_unVal); \
		_type = type; \
		SQ_OBJECT_RAWINIT() \
		_unVal.sym = x; \
		return *this; \
	}
struct SQObjectPtr : public SQObject
{
	SQObjectPtr()
	{
		SQ_OBJECT_RAWINIT()
		_type=OT_NULL;
		_unVal.pUserPointer=NULL;
	}
	SQObjectPtr(const SQObjectPtr &o)
	{
		_type = o._type;
		_unVal = o._unVal;
		__AddRef(_type,_unVal);
	}
	SQObjectPtr(const SQObject &o)
	{
		_type = o._type;
		_unVal = o._unVal;
		__AddRef(_type,_unVal);
	}
	_REF_TYPE_DECL(OT_TABLE,SQTable,pTable)
	_REF_TYPE_DECL(OT_CLASS,SQClass,pClass)
	_REF_TYPE_DECL(OT_INSTANCE,SQInstance,pInstance)
	_REF_TYPE_DECL(OT_ARRAY,SQArray,pArray)
	_REF_TYPE_DECL(OT_CLOSURE,SQClosure,pClosure)
	_REF_TYPE_DECL(OT_NATIVECLOSURE,SQNativeClosure,pNativeClosure)
	_REF_TYPE_DECL(OT_OUTER,SQOuter,pOuter)
	_REF_TYPE_DECL(OT_GENERATOR,SQGenerator,pGenerator)
	_REF_TYPE_DECL(OT_STRING,SQString,pString)
	_REF_TYPE_DECL(OT_USERDATA,SQUserData,pUserData)
	_REF_TYPE_DECL(OT_WEAKREF,SQWeakRef,pWeakRef)
	_REF_TYPE_DECL(OT_THREAD,SQVM,pThread)
	_REF_TYPE_DECL(OT_FUNCPROTO,SQFunctionProto,pFunctionProto)
	
	_SCALAR_TYPE_DECL(OT_INTEGER,SQInteger,nInteger)
	_SCALAR_TYPE_DECL(OT_FLOAT,SQFloat,fFloat)
	_SCALAR_TYPE_DECL(OT_USERPOINTER,SQUserPointer,pUserPointer)

	SQObjectPtr(bool bBool)
	{
		SQ_OBJECT_RAWINIT()
		_type = OT_BOOL;
		_unVal.nInteger = bBool?1:0;
	}
	inline SQObjectPtr& operator=(bool b)
	{ 
		__Release(_type,_unVal);
		SQ_OBJECT_RAWINIT()
		_type = OT_BOOL;
		_unVal.nInteger = b?1:0;
		return *this;
	}

	~SQObjectPtr()
	{
		__Release(_type,_unVal);
	}
			
	inline SQObjectPtr& operator=(const SQObjectPtr& obj)
	{ 
		SQObjectType tOldType;
		SQObjectValue unOldVal;
		tOldType=_type;
		unOldVal=_unVal;
		_unVal = obj._unVal;
		_type = obj._type;
		__AddRef(_type,_unVal);
		__Release(tOldType,unOldVal);
		return *this;
	}
	inline SQObjectPtr& operator=(const SQObject& obj)
	{ 
		SQObjectType tOldType;
		SQObjectValue unOldVal;
		tOldType=_type;
		unOldVal=_unVal;
		_unVal = obj._unVal;
		_type = obj._type;
		__AddRef(_type,_unVal);
		__Release(tOldType,unOldVal);
		return *this;
	}
	inline void Null()
	{
		SQObjectType tOldType = _type;
		SQObjectValue unOldVal = _unVal;
		_type = OT_NULL;
		_unVal.raw = (SQRawObjectVal)NULL;
		__Release(tOldType ,unOldVal);
	}
	private:
		SQObjectPtr(const SQChar *){} //safety
};


inline void _Swap(SQObject &a,SQObject &b)
{
	SQObjectType tOldType = a._type;
	SQObjectValue unOldVal = a._unVal;
	a._type = b._type;
	a._unVal = b._unVal;
	b._type = tOldType;
	b._unVal = unOldVal;
}

/////////////////////////////////////////////////////////////////////////////////////
#ifndef NO_GARBAGE_COLLECTOR
#define MARK_FLAG 0x80000000
struct SQCollectable : public SQRefCounted {
	SQCollectable *_next;
	SQCollectable *_prev;
	SQSharedState *_sharedstate;
	virtual SQObjectType GetType()=0;
	virtual void Release()=0;
	virtual void Mark(SQCollectable **chain)=0;
	void UnMark();
	virtual void Finalize()=0;
	static void AddToChain(SQCollectable **chain,SQCollectable *c);
	static void RemoveFromChain(SQCollectable **chain,SQCollectable *c);
};


#define ADD_TO_CHAIN(chain,obj) AddToChain(chain,obj)
#define REMOVE_FROM_CHAIN(chain,obj) {if(!(_uiRef&MARK_FLAG))RemoveFromChain(chain,obj);}
#define CHAINABLE_OBJ SQCollectable
#define INIT_CHAIN() {_next=NULL;_prev=NULL;_sharedstate=ss;}
#else

#define ADD_TO_CHAIN(chain,obj) ((void)0)
#define REMOVE_FROM_CHAIN(chain,obj) ((void)0)
#define CHAINABLE_OBJ SQRefCounted
#define INIT_CHAIN() ((void)0)
#endif

struct SQDelegable : public CHAINABLE_OBJ {
	bool SetDelegate(SQTable *m);
	virtual bool GetMetaMethod(SQVM *v,SQMetaMethod mm,SQObjectPtr &res);
	SQTable *_delegate;
};

SQUnsignedInteger TranslateIndex(const SQObjectPtr &idx);
typedef sqvector<SQObjectPtr> SQObjectPtrVec;
typedef sqvector<SQInteger> SQIntVec;
const SQChar *GetTypeName(const SQObjectPtr &obj1);
const SQChar *IdType2Name(SQObjectType type);



#endif //_SQOBJECT_H_

// <--- back to sqpcheader.h
// ---- #include "sqstate.h"
// ---> including sqstate.h
/*	see copyright notice in squirrel.h */
#ifndef _SQSTATE_H_
#define _SQSTATE_H_

// ---- #include "squtils.h"
// ---> including squtils.h
// <--- back to sqstate.h
// ---- #include "sqobject.h"
// ---> including sqobject.h
// <--- back to sqstate.h
struct SQString;
struct SQTable;
//max number of character for a printed number
#define NUMBER_MAX_CHAR 50

struct SQStringTable
{
	SQStringTable(SQSharedState*ss);
	~SQStringTable();
	SQString *Add(const SQChar *,SQInteger len);
	void Remove(SQString *);
private:
	void Resize(SQInteger size);
	void AllocNodes(SQInteger size);
	SQString **_strings;
	SQUnsignedInteger _numofslots;
	SQUnsignedInteger _slotused;
	SQSharedState *_sharedstate;
};

struct RefTable {
	struct RefNode {
		SQObjectPtr obj;
		SQUnsignedInteger refs;
		struct RefNode *next;
	};
	RefTable();
	~RefTable();
	void AddRef(SQObject &obj);
	SQBool Release(SQObject &obj);
	SQUnsignedInteger GetRefCount(SQObject &obj);
#ifndef NO_GARBAGE_COLLECTOR
	void Mark(SQCollectable **chain);
#endif
	void Finalize();
private:
	RefNode *Get(SQObject &obj,SQHash &mainpos,RefNode **prev,bool add);
	RefNode *Add(SQHash mainpos,SQObject &obj);
	void Resize(SQUnsignedInteger size);
	void AllocNodes(SQUnsignedInteger size);
	SQUnsignedInteger _numofslots;
	SQUnsignedInteger _slotused;
	RefNode *_nodes;
	RefNode *_freelist;
	RefNode **_buckets;
};

#define ADD_STRING(ss,str,len) ss->_stringtable->Add(str,len)
#define REMOVE_STRING(ss,bstr) ss->_stringtable->Remove(bstr)

struct SQObjectPtr;

struct SQSharedState
{
	SQSharedState();
	~SQSharedState();
	void Init();
public:
	SQChar* GetScratchPad(SQInteger size);
	SQInteger GetMetaMethodIdxByName(const SQObjectPtr &name);
#ifndef NO_GARBAGE_COLLECTOR
	SQInteger CollectGarbage(SQVM *vm);
	void RunMark(SQVM *vm,SQCollectable **tchain);
	SQInteger ResurrectUnreachable(SQVM *vm);
	static void MarkObject(SQObjectPtr &o,SQCollectable **chain);
#endif
	SQObjectPtrVec *_metamethods;
	SQObjectPtr _metamethodsmap;
	SQObjectPtrVec *_systemstrings;
	SQObjectPtrVec *_types;
	SQStringTable *_stringtable;
	RefTable _refs_table;
	SQObjectPtr _registry;
	SQObjectPtr _consts;
	SQObjectPtr _constructoridx;
#ifndef NO_GARBAGE_COLLECTOR
	SQCollectable *_gc_chain;
#endif
	SQObjectPtr _root_vm;
	SQObjectPtr _table_default_delegate;
	static SQRegFunction _table_default_delegate_funcz[];
	SQObjectPtr _array_default_delegate;
	static SQRegFunction _array_default_delegate_funcz[];
	SQObjectPtr _string_default_delegate;
	static SQRegFunction _string_default_delegate_funcz[];
	SQObjectPtr _number_default_delegate;
	static SQRegFunction _number_default_delegate_funcz[];
	SQObjectPtr _generator_default_delegate;
	static SQRegFunction _generator_default_delegate_funcz[];
	SQObjectPtr _closure_default_delegate;
	static SQRegFunction _closure_default_delegate_funcz[];
	SQObjectPtr _thread_default_delegate;
	static SQRegFunction _thread_default_delegate_funcz[];
	SQObjectPtr _class_default_delegate;
	static SQRegFunction _class_default_delegate_funcz[];
	SQObjectPtr _instance_default_delegate;
	static SQRegFunction _instance_default_delegate_funcz[];
	SQObjectPtr _weakref_default_delegate;
	static SQRegFunction _weakref_default_delegate_funcz[];
	
	SQCOMPILERERROR _compilererrorhandler;
	SQPRINTFUNCTION _printfunc;
	SQPRINTFUNCTION _errorfunc;
	bool _debuginfo;
	bool _notifyallexceptions;
private:
	SQChar *_scratchpad;
	SQInteger _scratchpadsize;
};

#define _sp(s) (_sharedstate->GetScratchPad(s))
#define _spval (_sharedstate->GetScratchPad(-1))

#define _table_ddel		_table(_sharedstate->_table_default_delegate) 
#define _array_ddel		_table(_sharedstate->_array_default_delegate) 
#define _string_ddel	_table(_sharedstate->_string_default_delegate) 
#define _number_ddel	_table(_sharedstate->_number_default_delegate) 
#define _generator_ddel	_table(_sharedstate->_generator_default_delegate) 
#define _closure_ddel	_table(_sharedstate->_closure_default_delegate) 
#define _thread_ddel	_table(_sharedstate->_thread_default_delegate) 
#define _class_ddel		_table(_sharedstate->_class_default_delegate) 
#define _instance_ddel	_table(_sharedstate->_instance_default_delegate) 
#define _weakref_ddel	_table(_sharedstate->_weakref_default_delegate) 

#ifdef SQUNICODE //rsl REAL STRING LEN
#define rsl(l) ((l)<<1)
#else
#define rsl(l) (l)
#endif

//extern SQObjectPtr _null_;

bool CompileTypemask(SQIntVec &res,const SQChar *typemask);


#endif //_SQSTATE_H_

// <--- back to sqpcheader.h

#endif //_SQPCHEADER_H_

// <--- back to sqapi.cpp
// ---- #include "sqvm.h"
// ---> including sqvm.h
/*	see copyright notice in squirrel.h */
#ifndef _SQVM_H_
#define _SQVM_H_

// ---- #include "sqopcodes.h"
// ---> including sqopcodes.h
/*	see copyright notice in squirrel.h */
#ifndef _SQOPCODES_H_
#define _SQOPCODES_H_

#define MAX_FUNC_STACKSIZE 0xFF
#define MAX_LITERALS ((SQInteger)0x7FFFFFFF)

enum BitWiseOP {
	BW_AND = 0,
	BW_OR = 2,	
	BW_XOR = 3,
	BW_SHIFTL = 4,
	BW_SHIFTR = 5,
	BW_USHIFTR = 6
};

enum CmpOP {
	CMP_G = 0,
	CMP_GE = 2,	
	CMP_L = 3,
	CMP_LE = 4,
	CMP_3W = 5
};

enum NewObjectType {
	NOT_TABLE = 0,
	NOT_ARRAY = 1,
	NOT_CLASS = 2
};

enum AppendArrayType {
	AAT_STACK = 0,
	AAT_LITERAL = 1,
	AAT_INT = 2,
	AAT_FLOAT = 3,
	AAT_BOOL = 4
};

enum SQOpcode
{
	_OP_LINE=				0x00,	
	_OP_LOAD=				0x01,
	_OP_LOADINT=			0x02,
	_OP_LOADFLOAT=			0x03,
	_OP_DLOAD=				0x04,
	_OP_TAILCALL=			0x05,	
	_OP_CALL=				0x06,	
	_OP_PREPCALL=			0x07,	
	_OP_PREPCALLK=			0x08,	
	_OP_GETK=				0x09,	
	_OP_MOVE=				0x0A,	
	_OP_NEWSLOT=			0x0B,	
	_OP_DELETE=				0x0C,	
	_OP_SET=				0x0D,	
	_OP_GET=				0x0E,
	_OP_EQ=					0x0F,
	_OP_NE=					0x10,
	_OP_ADD=				0x11,
	_OP_SUB=				0x12,
	_OP_MUL=				0x13,
	_OP_DIV=				0x14,
	_OP_MOD=				0x15,
	_OP_BITW=				0x16,
	_OP_RETURN=				0x17,	
	_OP_LOADNULLS=			0x18,	
	_OP_LOADROOT=			0x19,
	_OP_LOADBOOL=			0x1A,
	_OP_DMOVE=				0x1B,	
	_OP_JMP=				0x1C,	
	//_OP_JNZ=				0x1D,
	_OP_JCMP=				0x1D,
	_OP_JZ=					0x1E,	
	_OP_SETOUTER=			0x1F,	
	_OP_GETOUTER=			0x20,	
	_OP_NEWOBJ=				0x21,
	_OP_APPENDARRAY=		0x22,	
	_OP_COMPARITH=			0x23,	
	_OP_INC=				0x24,	
	_OP_INCL=				0x25,	
	_OP_PINC=				0x26,	
	_OP_PINCL=				0x27,	
	_OP_CMP=				0x28,
	_OP_EXISTS=				0x29,	
	_OP_INSTANCEOF=			0x2A,
	_OP_AND=				0x2B,
	_OP_OR=					0x2C,
	_OP_NEG=				0x2D,
	_OP_NOT=				0x2E,
	_OP_BWNOT=				0x2F,	
	_OP_CLOSURE=			0x30,	
	_OP_YIELD=				0x31,	
	_OP_RESUME=				0x32,
	_OP_FOREACH=			0x33,
	_OP_POSTFOREACH=		0x34,
	_OP_CLONE=				0x35,
	_OP_TYPEOF=				0x36,
	_OP_PUSHTRAP=			0x37,
	_OP_POPTRAP=			0x38,
	_OP_THROW=				0x39,
	_OP_NEWSLOTA=			0x3A,
	_OP_GETBASE=			0x3B,
	_OP_CLOSE=				0x3C,
};							  

struct SQInstructionDesc {	  
	const SQChar *name;		  
};							  

struct SQInstruction 
{
	SQInstruction(){};
	SQInstruction(SQOpcode _op,SQInteger a0=0,SQInteger a1=0,SQInteger a2=0,SQInteger a3=0)
	{	op = _op;
		_arg0 = (unsigned char)a0;_arg1 = (SQInt32)a1;
		_arg2 = (unsigned char)a2;_arg3 = (unsigned char)a3;
	}
    
	
	SQInt32 _arg1;
	unsigned char op;
	unsigned char _arg0;
	unsigned char _arg2;
	unsigned char _arg3;
};

// ---- #include "squtils.h"
// ---> including squtils.h
// <--- back to sqopcodes.h
typedef sqvector<SQInstruction> SQInstructionVec;

#define NEW_SLOT_ATTRIBUTES_FLAG	0x01
#define NEW_SLOT_STATIC_FLAG		0x02

#endif // _SQOPCODES_H_

// <--- back to sqvm.h
// ---- #include "sqobject.h"
// ---> including sqobject.h
// <--- back to sqvm.h
#define MAX_NATIVE_CALLS 100
#define MIN_STACK_OVERHEAD 15

#define SQ_SUSPEND_FLAG -666
#define DONT_FALL_BACK 666
//base lib
void sq_base_register(HSQUIRRELVM v);

struct SQExceptionTrap{
	SQExceptionTrap() {}
	SQExceptionTrap(SQInteger ss, SQInteger stackbase,SQInstruction *ip, SQInteger ex_target){ _stacksize = ss; _stackbase = stackbase; _ip = ip; _extarget = ex_target;}
	SQExceptionTrap(const SQExceptionTrap &et) { (*this) = et;	}
	SQInteger _stackbase;
	SQInteger _stacksize;
	SQInstruction *_ip;
	SQInteger _extarget;
};

#define _INLINE 

#define STK(a) _stack._vals[_stackbase+(a)]
#define TARGET _stack._vals[_stackbase+arg0]

typedef sqvector<SQExceptionTrap> ExceptionsTraps;

struct SQVM : public CHAINABLE_OBJ
{
	struct CallInfo{
		//CallInfo() { _generator = NULL;}
		SQInstruction *_ip;
		SQObjectPtr *_literals;
		SQObjectPtr _closure;
		SQGenerator *_generator;
		SQInt32 _etraps;
		SQInt32 _prevstkbase;
		SQInt32 _prevtop;
		SQInt32 _target;
		SQInt32 _ncalls;
		SQBool _root;
	};
	
typedef sqvector<CallInfo> CallInfoVec;
public:
	void DebugHookProxy(SQInteger type, const SQChar * sourcename, SQInteger line, const SQChar * funcname);
	static void _DebugHookProxy(HSQUIRRELVM v, SQInteger type, const SQChar * sourcename, SQInteger line, const SQChar * funcname);
	enum ExecutionType { ET_CALL, ET_RESUME_GENERATOR, ET_RESUME_VM,ET_RESUME_THROW_VM };
	SQVM(SQSharedState *ss);
	~SQVM();
	bool Init(SQVM *friendvm, SQInteger stacksize);
	bool Execute(SQObjectPtr &func, SQInteger nargs, SQInteger stackbase, SQObjectPtr &outres, SQBool raiseerror, ExecutionType et = ET_CALL);
	//starts a native call return when the NATIVE closure returns
	bool CallNative(SQNativeClosure *nclosure, SQInteger nargs, SQInteger newbase, SQObjectPtr &retval,bool &suspend);
	//starts a SQUIRREL call in the same "Execution loop"
	bool StartCall(SQClosure *closure, SQInteger target, SQInteger nargs, SQInteger stackbase, bool tailcall);
	bool CreateClassInstance(SQClass *theclass, SQObjectPtr &inst, SQObjectPtr &constructor);
	//call a generic closure pure SQUIRREL or NATIVE
	bool Call(SQObjectPtr &closure, SQInteger nparams, SQInteger stackbase, SQObjectPtr &outres,SQBool raiseerror);
	SQRESULT Suspend();

	void CallDebugHook(SQInteger type,SQInteger forcedline=0);
	void CallErrorHandler(SQObjectPtr &e);
	bool Get(const SQObjectPtr &self, const SQObjectPtr &key, SQObjectPtr &dest, bool raw, SQInteger selfidx);
	SQInteger FallBackGet(const SQObjectPtr &self,const SQObjectPtr &key,SQObjectPtr &dest);
	bool InvokeDefaultDelegate(const SQObjectPtr &self,const SQObjectPtr &key,SQObjectPtr &dest);
	bool Set(const SQObjectPtr &self, const SQObjectPtr &key, const SQObjectPtr &val, SQInteger selfidx);
	SQInteger FallBackSet(const SQObjectPtr &self,const SQObjectPtr &key,const SQObjectPtr &val);
	bool NewSlot(const SQObjectPtr &self, const SQObjectPtr &key, const SQObjectPtr &val,bool bstatic);
	bool NewSlotA(const SQObjectPtr &self,const SQObjectPtr &key,const SQObjectPtr &val,const SQObjectPtr &attrs,bool bstatic,bool raw);
	bool DeleteSlot(const SQObjectPtr &self, const SQObjectPtr &key, SQObjectPtr &res);
	bool Clone(const SQObjectPtr &self, SQObjectPtr &target);
	bool ObjCmp(const SQObjectPtr &o1, const SQObjectPtr &o2,SQInteger &res);
	bool StringCat(const SQObjectPtr &str, const SQObjectPtr &obj, SQObjectPtr &dest);
	static bool IsEqual(const SQObjectPtr &o1,const SQObjectPtr &o2,bool &res);
	bool ToString(const SQObjectPtr &o,SQObjectPtr &res);
	SQString *PrintObjVal(const SQObjectPtr &o);

 
	void Raise_Error(const SQChar *s, ...);
	void Raise_Error(const SQObjectPtr &desc);
	void Raise_IdxError(const SQObjectPtr &o);
	void Raise_CompareError(const SQObject &o1, const SQObject &o2);
	void Raise_ParamTypeError(SQInteger nparam,SQInteger typemask,SQInteger type);

	void FindOuter(SQObjectPtr &target, SQObjectPtr *stackindex);
	void RelocateOuters();
	void CloseOuters(SQObjectPtr *stackindex);

	bool TypeOf(const SQObjectPtr &obj1, SQObjectPtr &dest);
	bool CallMetaMethod(SQObjectPtr &closure, SQMetaMethod mm, SQInteger nparams, SQObjectPtr &outres);
	bool ArithMetaMethod(SQInteger op, const SQObjectPtr &o1, const SQObjectPtr &o2, SQObjectPtr &dest);
	bool Return(SQInteger _arg0, SQInteger _arg1, SQObjectPtr &retval);
	//new stuff
	_INLINE bool ARITH_OP(SQUnsignedInteger op,SQObjectPtr &trg,const SQObjectPtr &o1,const SQObjectPtr &o2);
	_INLINE bool BW_OP(SQUnsignedInteger op,SQObjectPtr &trg,const SQObjectPtr &o1,const SQObjectPtr &o2);
	_INLINE bool NEG_OP(SQObjectPtr &trg,const SQObjectPtr &o1);
	_INLINE bool CMP_OP(CmpOP op, const SQObjectPtr &o1,const SQObjectPtr &o2,SQObjectPtr &res);
	bool CLOSURE_OP(SQObjectPtr &target, SQFunctionProto *func);
	bool CLASS_OP(SQObjectPtr &target,SQInteger base,SQInteger attrs);
	//return true if the loop is finished
	bool FOREACH_OP(SQObjectPtr &o1,SQObjectPtr &o2,SQObjectPtr &o3,SQObjectPtr &o4,SQInteger arg_2,int exitpos,int &jump);
	//_INLINE bool LOCAL_INC(SQInteger op,SQObjectPtr &target, SQObjectPtr &a, SQObjectPtr &incr);
	_INLINE bool PLOCAL_INC(SQInteger op,SQObjectPtr &target, SQObjectPtr &a, SQObjectPtr &incr);
	_INLINE bool DerefInc(SQInteger op,SQObjectPtr &target, SQObjectPtr &self, SQObjectPtr &key, SQObjectPtr &incr, bool postfix,SQInteger arg0);
#ifdef _DEBUG_DUMP
	void dumpstack(SQInteger stackbase=-1, bool dumpall = false);
#endif

#ifndef NO_GARBAGE_COLLECTOR
	void Mark(SQCollectable **chain);
	SQObjectType GetType() {return OT_THREAD;}
#endif
	void Finalize();
	void GrowCallStack() {
		SQInteger newsize = _alloccallsstacksize*2;
		_callstackdata.resize(newsize);
		_callsstack = &_callstackdata[0];
		_alloccallsstacksize = newsize;
	}
	bool EnterFrame(SQInteger newbase, SQInteger newtop, bool tailcall);
	void LeaveFrame();
	void Release(){ sq_delete(this,SQVM); }
////////////////////////////////////////////////////////////////////////////
	//stack functions for the api
	void Remove(SQInteger n);

	static bool IsFalse(SQObjectPtr &o);
	
	void Pop();
	void Pop(SQInteger n);
	void Push(const SQObjectPtr &o);
	void PushNull();
	SQObjectPtr &Top();
	SQObjectPtr &PopGet();
	SQObjectPtr &GetUp(SQInteger n);
	SQObjectPtr &GetAt(SQInteger n);

	SQObjectPtrVec _stack;

	SQInteger _top;
	SQInteger _stackbase;
	SQOuter	*_openouters;
	SQObjectPtr _roottable;
	SQObjectPtr _lasterror;
	SQObjectPtr _errorhandler;

	bool _debughook;
	SQDEBUGHOOK _debughook_native;
	SQObjectPtr _debughook_closure;

	SQObjectPtr temp_reg;
	

	CallInfo* _callsstack;
	SQInteger _callsstacksize;
	SQInteger _alloccallsstacksize;
	sqvector<CallInfo>  _callstackdata;

	ExceptionsTraps _etraps;
	CallInfo *ci;
	void *_foreignptr;
	//VMs sharing the same state
	SQSharedState *_sharedstate;
	SQInteger _nnativecalls;
	SQInteger _nmetamethodscall;
	//suspend infos
	SQBool _suspended;
	SQBool _suspended_root;
	SQInteger _suspended_target;
	SQInteger _suspended_traps;
};

struct AutoDec{
	AutoDec(SQInteger *n) { _n = n; }
	~AutoDec() { (*_n)--; }
	SQInteger *_n;
};

inline SQObjectPtr &stack_get(HSQUIRRELVM v,SQInteger idx){return ((idx>=0)?(v->GetAt(idx+v->_stackbase-1)):(v->GetUp(idx)));}

#define _ss(_vm_) (_vm_)->_sharedstate

#ifndef NO_GARBAGE_COLLECTOR
#define _opt_ss(_vm_) (_vm_)->_sharedstate
#else
#define _opt_ss(_vm_) NULL
#endif

#define PUSH_CALLINFO(v,nci){ \
	SQInteger css = v->_callsstacksize; \
	if(css == v->_alloccallsstacksize) { \
		v->GrowCallStack(); \
	} \
	v->ci = &v->_callsstack[css]; \
	*(v->ci) = nci; \
	v->_callsstacksize++; \
}

#define POP_CALLINFO(v){ \
	SQInteger css = --v->_callsstacksize; \
	v->ci->_closure.Null(); \
	v->ci = css?&v->_callsstack[css-1]:NULL;	\
}
#endif //_SQVM_H_

// <--- back to sqapi.cpp
// ---- #include "sqstring.h"
// ---> including sqstring.h
/*	see copyright notice in squirrel.h */
#ifndef _SQSTRING_H_
#define _SQSTRING_H_

inline SQHash _hashstr (const SQChar *s, size_t l)
{
		SQHash h = (SQHash)l;  /* seed */
		size_t step = (l>>5)|1;  /* if string is too long, don't hash all its chars */
		for (; l>=step; l-=step)
			h = h ^ ((h<<5)+(h>>2)+(unsigned short)*(s++));
		return h;
}

struct SQString : public SQRefCounted
{
	SQString(){}
	~SQString(){}
public:
	static SQString *Create(SQSharedState *ss, const SQChar *, SQInteger len = -1 );
	SQInteger Next(const SQObjectPtr &refpos, SQObjectPtr &outkey, SQObjectPtr &outval);
	void Release();
	SQSharedState *_sharedstate;
	SQString *_next; //chain for the string table
	SQInteger _len;
	SQHash _hash;
	SQChar _val[1];
};



#endif //_SQSTRING_H_

// <--- back to sqapi.cpp
// ---- #include "sqtable.h"
// ---> including sqtable.h
/*	see copyright notice in squirrel.h */
#ifndef _SQTABLE_H_
#define _SQTABLE_H_
/*
* The following code is based on Lua 4.0 (Copyright 1994-2002 Tecgraf, PUC-Rio.)
* http://www.lua.org/copyright.html#4
* http://www.lua.org/source/4.0.1/src_ltable.c.html
*/

// ---- #include "sqstring.h"
// ---> including sqstring.h
// <--- back to sqtable.h


#define hashptr(p)  ((SQHash)(((SQInteger)p) >> 3))

inline SQHash HashObj(const SQObjectPtr &key)
{
	switch(type(key)) {
		case OT_STRING:		return _string(key)->_hash;
		case OT_FLOAT:		return (SQHash)((SQInteger)_float(key));
		case OT_BOOL: case OT_INTEGER:	return (SQHash)((SQInteger)_integer(key));
		default:			return hashptr(key._unVal.pRefCounted);
	}
}

struct SQTable : public SQDelegable 
{
private:
	struct _HashNode
	{
		_HashNode() { next = NULL; }
		SQObjectPtr val;
		SQObjectPtr key;
		_HashNode *next;
	};
	_HashNode *_firstfree;
	_HashNode *_nodes;
	SQInteger _numofnodes;
	SQInteger _usednodes;
	
///////////////////////////
	void AllocNodes(SQInteger nSize);
	void Rehash(bool force);
	SQTable(SQSharedState *ss, SQInteger nInitialSize);
	void _ClearNodes();
public:
	static SQTable* Create(SQSharedState *ss,SQInteger nInitialSize)
	{
		SQTable *newtable = (SQTable*)SQ_MALLOC(sizeof(SQTable));
		new (newtable) SQTable(ss, nInitialSize);
		newtable->_delegate = NULL;
		return newtable;
	}
	void Finalize();
	SQTable *Clone();
	~SQTable()
	{
		SetDelegate(NULL);
		REMOVE_FROM_CHAIN(&_sharedstate->_gc_chain, this);
		for (SQInteger i = 0; i < _numofnodes; i++) _nodes[i].~_HashNode();
		SQ_FREE(_nodes, _numofnodes * sizeof(_HashNode));
	}
#ifndef NO_GARBAGE_COLLECTOR 
	void Mark(SQCollectable **chain);
	SQObjectType GetType() {return OT_TABLE;}
#endif
	inline _HashNode *_Get(const SQObjectPtr &key,SQHash hash)
	{
		_HashNode *n = &_nodes[hash];
		do{
			if(_rawval(n->key) == _rawval(key) && type(n->key) == type(key)){
				return n;
			}
		}while((n = n->next));
		return NULL;
	}
	bool Get(const SQObjectPtr &key,SQObjectPtr &val);
	void Remove(const SQObjectPtr &key);
	bool Set(const SQObjectPtr &key, const SQObjectPtr &val);
	//returns true if a new slot has been created false if it was already present
	bool NewSlot(const SQObjectPtr &key,const SQObjectPtr &val);
	SQInteger Next(bool getweakrefs,const SQObjectPtr &refpos, SQObjectPtr &outkey, SQObjectPtr &outval);
	
	SQInteger CountUsed(){ return _usednodes;}
	void Clear();
	void Release()
	{
		sq_delete(this, SQTable);
	}
	
};

#endif //_SQTABLE_H_

// <--- back to sqapi.cpp
// ---- #include "sqarray.h"
// ---> including sqarray.h
/*	see copyright notice in squirrel.h */
#ifndef _SQARRAY_H_
#define _SQARRAY_H_

struct SQArray : public CHAINABLE_OBJ
{
private:
	SQArray(SQSharedState *ss,SQInteger nsize){_values.resize(nsize); INIT_CHAIN();ADD_TO_CHAIN(&_ss(this)->_gc_chain,this);}
	~SQArray()
	{
		REMOVE_FROM_CHAIN(&_ss(this)->_gc_chain,this);
	}
public:
	static SQArray* Create(SQSharedState *ss,SQInteger nInitialSize){
		SQArray *newarray=(SQArray*)SQ_MALLOC(sizeof(SQArray));
		new (newarray) SQArray(ss,nInitialSize);
		return newarray;
	}
#ifndef NO_GARBAGE_COLLECTOR
	void Mark(SQCollectable **chain);
	SQObjectType GetType() {return OT_ARRAY;}
#endif
	void Finalize(){
		_values.resize(0);
	}
	bool Get(const SQInteger nidx,SQObjectPtr &val)
	{
		if(nidx>=0 && nidx<(SQInteger)_values.size()){
			SQObjectPtr &o = _values[nidx];
			val = _realval(o);
			return true;
		}
		else return false;
	}
	bool Set(const SQInteger nidx,const SQObjectPtr &val)
	{
		if(nidx>=0 && nidx<(SQInteger)_values.size()){
			_values[nidx]=val;
			return true;
		}
		else return false;
	}
	SQInteger Next(const SQObjectPtr &refpos,SQObjectPtr &outkey,SQObjectPtr &outval)
	{
		SQUnsignedInteger idx=TranslateIndex(refpos);
		while(idx<_values.size()){
			//first found
			outkey=(SQInteger)idx;
			SQObjectPtr &o = _values[idx];
			outval = _realval(o);
			//return idx for the next iteration
			return ++idx;
		}
		//nothing to iterate anymore
		return -1;
	}
	SQArray *Clone(){SQArray *anew=Create(_opt_ss(this),0); anew->_values.copy(_values); return anew; }
	SQInteger Size() const {return _values.size();}
	void Resize(SQInteger size)
	{
		SQObjectPtr _null;
		Resize(size,_null);
	}
	void Resize(SQInteger size,SQObjectPtr &fill) { _values.resize(size,fill); ShrinkIfNeeded(); }
	void Reserve(SQInteger size) { _values.reserve(size); }
	void Append(const SQObject &o){_values.push_back(o);}
	void Extend(const SQArray *a);
	SQObjectPtr &Top(){return _values.top();}
	void Pop(){_values.pop_back(); ShrinkIfNeeded(); }
	bool Insert(SQInteger idx,const SQObject &val){
		if(idx < 0 || idx > (SQInteger)_values.size())
			return false;
		_values.insert(idx,val);
		return true;
	}
	void ShrinkIfNeeded() {
		if(_values.size() <= _values.capacity()>>2) //shrink the array
			_values.shrinktofit();
	}
	bool Remove(SQInteger idx){
		if(idx < 0 || idx >= (SQInteger)_values.size())
			return false;
		_values.remove(idx);
		ShrinkIfNeeded();
		return true;
	}
	void Release()
	{
		sq_delete(this,SQArray);
	}
	
	SQObjectPtrVec _values;
};
#endif //_SQARRAY_H_

// <--- back to sqapi.cpp
// ---- #include "sqfuncproto.h"
// ---> including sqfuncproto.h
/*	see copyright notice in squirrel.h */
#ifndef _SQFUNCTION_H_
#define _SQFUNCTION_H_

// ---- #include "sqopcodes.h"
// ---> including sqopcodes.h
// <--- back to sqfuncproto.h

enum SQOuterType {
	otLOCAL = 0,
	otOUTER = 1
};

struct SQOuterVar
{
	
	SQOuterVar(){}
	SQOuterVar(const SQObjectPtr &name,const SQObjectPtr &src,SQOuterType t)
	{
		_name = name;
		_src=src;
		_type=t;
	}
	SQOuterVar(const SQOuterVar &ov)
	{
		_type=ov._type;
		_src=ov._src;
		_name=ov._name;
	}
	SQOuterType _type;
	SQObjectPtr _name;
	SQObjectPtr _src;
};

struct SQLocalVarInfo
{
	SQLocalVarInfo():_start_op(0),_end_op(0),_pos(0){}
	SQLocalVarInfo(const SQLocalVarInfo &lvi)
	{
		_name=lvi._name;
		_start_op=lvi._start_op;
		_end_op=lvi._end_op;
		_pos=lvi._pos;
	}
	SQObjectPtr _name;
	SQUnsignedInteger _start_op;
	SQUnsignedInteger _end_op;
	SQUnsignedInteger _pos;
};

struct SQLineInfo { SQInteger _line;SQInteger _op; };

typedef sqvector<SQOuterVar> SQOuterVarVec;
typedef sqvector<SQLocalVarInfo> SQLocalVarInfoVec;
typedef sqvector<SQLineInfo> SQLineInfoVec;

#define _FUNC_SIZE(ni,nl,nparams,nfuncs,nouters,nlineinf,localinf,defparams) (sizeof(SQFunctionProto) \
		+((ni-1)*sizeof(SQInstruction))+(nl*sizeof(SQObjectPtr)) \
		+(nparams*sizeof(SQObjectPtr))+(nfuncs*sizeof(SQObjectPtr)) \
		+(nouters*sizeof(SQOuterVar))+(nlineinf*sizeof(SQLineInfo)) \
		+(localinf*sizeof(SQLocalVarInfo))+(defparams*sizeof(SQInteger)))


struct SQFunctionProto : public CHAINABLE_OBJ
{
private:
	SQFunctionProto(SQSharedState *ss);
	~SQFunctionProto();
	
public:
	static SQFunctionProto *Create(SQSharedState *ss,SQInteger ninstructions,
		SQInteger nliterals,SQInteger nparameters,
		SQInteger nfunctions,SQInteger noutervalues,
		SQInteger nlineinfos,SQInteger nlocalvarinfos,SQInteger ndefaultparams)
	{
		SQFunctionProto *f;
		//I compact the whole class and members in a single memory allocation
		f = (SQFunctionProto *)sq_vm_malloc(_FUNC_SIZE(ninstructions,nliterals,nparameters,nfunctions,noutervalues,nlineinfos,nlocalvarinfos,ndefaultparams));
		new (f) SQFunctionProto(ss);
		f->_ninstructions = ninstructions;
		f->_literals = (SQObjectPtr*)&f->_instructions[ninstructions];
		f->_nliterals = nliterals;
		f->_parameters = (SQObjectPtr*)&f->_literals[nliterals];
		f->_nparameters = nparameters;
		f->_functions = (SQObjectPtr*)&f->_parameters[nparameters];
		f->_nfunctions = nfunctions;
		f->_outervalues = (SQOuterVar*)&f->_functions[nfunctions];
		f->_noutervalues = noutervalues;
		f->_lineinfos = (SQLineInfo *)&f->_outervalues[noutervalues];
		f->_nlineinfos = nlineinfos;
		f->_localvarinfos = (SQLocalVarInfo *)&f->_lineinfos[nlineinfos];
		f->_nlocalvarinfos = nlocalvarinfos;
		f->_defaultparams = (SQInteger *)&f->_localvarinfos[nlocalvarinfos];
		f->_ndefaultparams = ndefaultparams;

		_CONSTRUCT_VECTOR(SQObjectPtr,f->_nliterals,f->_literals);
		_CONSTRUCT_VECTOR(SQObjectPtr,f->_nparameters,f->_parameters);
		_CONSTRUCT_VECTOR(SQObjectPtr,f->_nfunctions,f->_functions);
		_CONSTRUCT_VECTOR(SQOuterVar,f->_noutervalues,f->_outervalues);
		//_CONSTRUCT_VECTOR(SQLineInfo,f->_nlineinfos,f->_lineinfos); //not required are 2 integers
		_CONSTRUCT_VECTOR(SQLocalVarInfo,f->_nlocalvarinfos,f->_localvarinfos);
		return f;
	}
	void Release(){ 
		_DESTRUCT_VECTOR(SQObjectPtr,_nliterals,_literals);
		_DESTRUCT_VECTOR(SQObjectPtr,_nparameters,_parameters);
		_DESTRUCT_VECTOR(SQObjectPtr,_nfunctions,_functions);
		_DESTRUCT_VECTOR(SQOuterVar,_noutervalues,_outervalues);
		//_DESTRUCT_VECTOR(SQLineInfo,_nlineinfos,_lineinfos); //not required are 2 integers
		_DESTRUCT_VECTOR(SQLocalVarInfo,_nlocalvarinfos,_localvarinfos);
		SQInteger size = _FUNC_SIZE(_ninstructions,_nliterals,_nparameters,_nfunctions,_noutervalues,_nlineinfos,_nlocalvarinfos,_ndefaultparams);
		this->~SQFunctionProto();
		sq_vm_free(this,size);
	}
	
	const SQChar* GetLocal(SQVM *v,SQUnsignedInteger stackbase,SQUnsignedInteger nseq,SQUnsignedInteger nop);
	SQInteger GetLine(SQInstruction *curr);
	bool Save(SQVM *v,SQUserPointer up,SQWRITEFUNC write);
	static bool Load(SQVM *v,SQUserPointer up,SQREADFUNC read,SQObjectPtr &ret);
#ifndef NO_GARBAGE_COLLECTOR
	void Mark(SQCollectable **chain);
	void Finalize(){ _NULL_SQOBJECT_VECTOR(_literals,_nliterals); }
	SQObjectType GetType() {return OT_FUNCPROTO;}
#endif
	SQObjectPtr _sourcename;
	SQObjectPtr _name;
    SQInteger _stacksize;
	bool _bgenerator;
	SQInteger _varparams;

	SQInteger _nlocalvarinfos;
	SQLocalVarInfo *_localvarinfos;

	SQInteger _nlineinfos;
	SQLineInfo *_lineinfos;

	SQInteger _nliterals;
	SQObjectPtr *_literals;

	SQInteger _nparameters;
	SQObjectPtr *_parameters;
	
	SQInteger _nfunctions;
	SQObjectPtr *_functions;

	SQInteger _noutervalues;
	SQOuterVar *_outervalues;

	SQInteger _ndefaultparams;
	SQInteger *_defaultparams;
	
	SQInteger _ninstructions;
	SQInstruction _instructions[1];
};

#endif //_SQFUNCTION_H_

// <--- back to sqapi.cpp
// ---- #include "sqclosure.h"
// ---> including sqclosure.h
/*	see copyright notice in squirrel.h */
#ifndef _SQCLOSURE_H_
#define _SQCLOSURE_H_


#define _CALC_CLOSURE_SIZE(func) (sizeof(SQClosure) + (func->_noutervalues*sizeof(SQObjectPtr)) + (func->_ndefaultparams*sizeof(SQObjectPtr)))

struct SQFunctionProto;
struct SQClass;
struct SQClosure : public CHAINABLE_OBJ
{
private:
	SQClosure(SQSharedState *ss,SQFunctionProto *func){_function = func; __ObjAddRef(_function); _base = NULL; INIT_CHAIN();ADD_TO_CHAIN(&_ss(this)->_gc_chain,this); _env = NULL;}
public:
	static SQClosure *Create(SQSharedState *ss,SQFunctionProto *func){
		SQInteger size = _CALC_CLOSURE_SIZE(func);
		SQClosure *nc=(SQClosure*)SQ_MALLOC(size);
		new (nc) SQClosure(ss,func);
		nc->_outervalues = (SQObjectPtr *)(nc + 1);
		nc->_defaultparams = &nc->_outervalues[func->_noutervalues];
		_CONSTRUCT_VECTOR(SQObjectPtr,func->_noutervalues,nc->_outervalues);
		_CONSTRUCT_VECTOR(SQObjectPtr,func->_ndefaultparams,nc->_defaultparams);
		return nc;
	}
	void Release(){
		SQFunctionProto *f = _function;
		SQInteger size = _CALC_CLOSURE_SIZE(f);
		_DESTRUCT_VECTOR(SQObjectPtr,f->_noutervalues,_outervalues);
		_DESTRUCT_VECTOR(SQObjectPtr,f->_ndefaultparams,_defaultparams);
		__ObjRelease(_function);
		this->~SQClosure();
		sq_vm_free(this,size);
	}
	
	SQClosure *Clone()
	{
		SQFunctionProto *f = _function;
		SQClosure * ret = SQClosure::Create(_opt_ss(this),f);
		ret->_env = _env;
		if(ret->_env) __ObjAddRef(ret->_env);
		_COPY_VECTOR(ret->_outervalues,_outervalues,f->_noutervalues);
		_COPY_VECTOR(ret->_defaultparams,_defaultparams,f->_ndefaultparams);
		return ret;
	}
	~SQClosure();
	
	bool Save(SQVM *v,SQUserPointer up,SQWRITEFUNC write);
	static bool Load(SQVM *v,SQUserPointer up,SQREADFUNC read,SQObjectPtr &ret);
#ifndef NO_GARBAGE_COLLECTOR
	void Mark(SQCollectable **chain);
	void Finalize(){
		SQFunctionProto *f = _function;
		_NULL_SQOBJECT_VECTOR(_outervalues,f->_noutervalues);
		_NULL_SQOBJECT_VECTOR(_defaultparams,f->_ndefaultparams);
	}
	SQObjectType GetType() {return OT_CLOSURE;}
#endif
	SQWeakRef *_env;
	SQClass *_base;
	SQFunctionProto *_function;
	SQObjectPtr *_outervalues;
	SQObjectPtr *_defaultparams;
};

//////////////////////////////////////////////
struct SQOuter : public CHAINABLE_OBJ
{

private:
	SQOuter(SQSharedState *ss, SQObjectPtr *outer){_valptr = outer; _next = NULL; INIT_CHAIN(); ADD_TO_CHAIN(&_ss(this)->_gc_chain,this); }

public:
	static SQOuter *Create(SQSharedState *ss, SQObjectPtr *outer)
	{
		SQOuter *nc  = (SQOuter*)SQ_MALLOC(sizeof(SQOuter));
		new (nc) SQOuter(ss, outer);
		return nc;
	}
	~SQOuter() { REMOVE_FROM_CHAIN(&_ss(this)->_gc_chain,this); }

	void Release()
	{
		this->~SQOuter();
		sq_vm_free(this,sizeof(SQOuter));
	}
	
#ifndef NO_GARBAGE_COLLECTOR
	void Mark(SQCollectable **chain);
	void Finalize() { _value.Null(); }
	SQObjectType GetType() {return OT_OUTER;}
#endif

	SQObjectPtr *_valptr;  /* pointer to value on stack, or _value below */
	SQInteger    _idx;     /* idx in stack array, for relocation */
	SQObjectPtr  _value;   /* value of outer after stack frame is closed */
	SQOuter     *_next;    /* pointer to next outer when frame is open   */
};

//////////////////////////////////////////////
struct SQGenerator : public CHAINABLE_OBJ 
{
	enum SQGeneratorState{eRunning,eSuspended,eDead};
private:
	SQGenerator(SQSharedState *ss,SQClosure *closure){_closure=closure;_state=eRunning;_ci._generator=NULL;INIT_CHAIN();ADD_TO_CHAIN(&_ss(this)->_gc_chain,this);}
public:
	static SQGenerator *Create(SQSharedState *ss,SQClosure *closure){
		SQGenerator *nc=(SQGenerator*)SQ_MALLOC(sizeof(SQGenerator));
		new (nc) SQGenerator(ss,closure);
		return nc;
	}
	~SQGenerator()
	{
		REMOVE_FROM_CHAIN(&_ss(this)->_gc_chain,this);
	}
    void Kill(){
		_state=eDead;
		_stack.resize(0);
		_closure.Null();}
	void Release(){
		sq_delete(this,SQGenerator);
	}
	
	bool Yield(SQVM *v,SQInteger target);
	bool Resume(SQVM *v,SQObjectPtr &dest);
#ifndef NO_GARBAGE_COLLECTOR
	void Mark(SQCollectable **chain);
	void Finalize(){_stack.resize(0);_closure.Null();}
	SQObjectType GetType() {return OT_GENERATOR;}
#endif
	SQObjectPtr _closure;
	SQObjectPtrVec _stack;
	SQVM::CallInfo _ci;
	ExceptionsTraps _etraps;
	SQGeneratorState _state;
};

#define _CALC_NATVIVECLOSURE_SIZE(noutervalues) (sizeof(SQNativeClosure) + (noutervalues*sizeof(SQObjectPtr)))

struct SQNativeClosure : public CHAINABLE_OBJ
{
private:
	SQNativeClosure(SQSharedState *ss,SQFUNCTION func){_function=func;INIT_CHAIN();ADD_TO_CHAIN(&_ss(this)->_gc_chain,this); _env = NULL;}
public:
	static SQNativeClosure *Create(SQSharedState *ss,SQFUNCTION func,SQInteger nouters)
	{
		SQInteger size = _CALC_NATVIVECLOSURE_SIZE(nouters);
		SQNativeClosure *nc=(SQNativeClosure*)SQ_MALLOC(size);
		new (nc) SQNativeClosure(ss,func);
		nc->_outervalues = (SQObjectPtr *)(nc + 1);
		nc->_noutervalues = nouters;
		_CONSTRUCT_VECTOR(SQObjectPtr,nc->_noutervalues,nc->_outervalues);
		return nc;
	}
	SQNativeClosure *Clone()
	{
		SQNativeClosure * ret = SQNativeClosure::Create(_opt_ss(this),_function,_noutervalues);
		ret->_env = _env;
		if(ret->_env) __ObjAddRef(ret->_env);
		ret->_name = _name;
		_COPY_VECTOR(ret->_outervalues,_outervalues,_noutervalues);
		ret->_typecheck.copy(_typecheck);
		ret->_nparamscheck = _nparamscheck;
		return ret;
	}
	~SQNativeClosure()
	{
		__ObjRelease(_env);
		REMOVE_FROM_CHAIN(&_ss(this)->_gc_chain,this);
	}
	void Release(){
		SQInteger size = _CALC_NATVIVECLOSURE_SIZE(_noutervalues);
		_DESTRUCT_VECTOR(SQObjectPtr,_noutervalues,_outervalues);
		this->~SQNativeClosure();
		sq_free(this,size);
	}
	
#ifndef NO_GARBAGE_COLLECTOR
	void Mark(SQCollectable **chain);
	void Finalize() { _NULL_SQOBJECT_VECTOR(_outervalues,_noutervalues); }
	SQObjectType GetType() {return OT_NATIVECLOSURE;}
#endif
	SQInteger _nparamscheck;
	SQIntVec _typecheck;
	SQObjectPtr *_outervalues;
	SQUnsignedInteger _noutervalues;
	SQWeakRef *_env;
	SQFUNCTION _function;
	SQObjectPtr _name;
};



#endif //_SQCLOSURE_H_

// <--- back to sqapi.cpp
// ---- #include "squserdata.h"
// ---> including squserdata.h
/*	see copyright notice in squirrel.h */
#ifndef _SQUSERDATA_H_
#define _SQUSERDATA_H_

struct SQUserData : SQDelegable
{
	SQUserData(SQSharedState *ss){ _delegate = 0; _hook = NULL; INIT_CHAIN(); ADD_TO_CHAIN(&_ss(this)->_gc_chain, this); }
	~SQUserData()
	{
		REMOVE_FROM_CHAIN(&_ss(this)->_gc_chain, this);
		SetDelegate(NULL);
	}
	static SQUserData* Create(SQSharedState *ss, SQInteger size)
	{
		SQUserData* ud = (SQUserData*)SQ_MALLOC(sq_aligning(sizeof(SQUserData))+size);
		new (ud) SQUserData(ss);
		ud->_size = size;
		ud->_typetag = 0;
		return ud;
	}
#ifndef NO_GARBAGE_COLLECTOR
	void Mark(SQCollectable **chain);
	void Finalize(){SetDelegate(NULL);}
	SQObjectType GetType(){ return OT_USERDATA;}
#endif
	void Release() {
		if (_hook) _hook((SQUserPointer)sq_aligning(this + 1),_size);
		SQInteger tsize = _size;
		this->~SQUserData();
		SQ_FREE(this, sq_aligning(sizeof(SQUserData)) + tsize);
	}
	
		
	SQInteger _size;
	SQRELEASEHOOK _hook;
	SQUserPointer _typetag;
	//SQChar _val[1];
};

#endif //_SQUSERDATA_H_

// <--- back to sqapi.cpp
// ---- #include "sqcompiler.h"
// ---> including sqcompiler.h
/*	see copyright notice in squirrel.h */
#ifndef _SQCOMPILER_H_
#define _SQCOMPILER_H_

struct SQVM;

#define	TK_IDENTIFIER	258
#define	TK_STRING_LITERAL	259
#define	TK_INTEGER	260
#define	TK_FLOAT	261
#define	TK_BASE	262
#define	TK_DELETE	263
#define	TK_EQ	264
#define	TK_NE	265
#define	TK_LE	266
#define	TK_GE	267
#define	TK_SWITCH	268
#define	TK_ARROW	269
#define	TK_AND	270
#define	TK_OR	271
#define	TK_IF	272
#define	TK_ELSE	273
#define	TK_WHILE	274
#define	TK_BREAK	275
#define	TK_FOR	276
#define	TK_DO	277
#define	TK_NULL	278
#define	TK_FOREACH	279
#define	TK_IN	280
#define	TK_NEWSLOT	281
#define	TK_MODULO	282
#define	TK_LOCAL	283
#define	TK_CLONE	284
#define	TK_FUNCTION	285
#define	TK_RETURN	286
#define	TK_TYPEOF	287
#define	TK_UMINUS	288
#define	TK_PLUSEQ	289
#define	TK_MINUSEQ	290
#define	TK_CONTINUE	291
#define TK_YIELD 292
#define TK_TRY 293
#define TK_CATCH 294
#define TK_THROW 295
#define TK_SHIFTL 296
#define TK_SHIFTR 297
#define TK_RESUME 298
#define TK_DOUBLE_COLON 299
#define TK_CASE 300
#define TK_DEFAULT 301
#define TK_THIS 302
#define TK_PLUSPLUS 303
#define TK_MINUSMINUS 304
#define TK_3WAYSCMP 305
#define TK_USHIFTR 306
#define TK_CLASS 307
#define TK_EXTENDS 308
#define TK_CONSTRUCTOR 310
#define TK_INSTANCEOF 311
#define TK_VARPARAMS 312
//#define TK_VARGC 313
//#define TK_VARGV 314
#define TK_TRUE 315
#define TK_FALSE 316
#define TK_MULEQ 317
#define TK_DIVEQ 318
#define TK_MODEQ 319
#define TK_ATTR_OPEN 320
#define TK_ATTR_CLOSE 321
#define TK_STATIC 322
#define TK_ENUM 323
#define TK_CONST 324


typedef void(*CompilerErrorFunc)(void *ud, const SQChar *s);
bool Compile(SQVM *vm, SQLEXREADFUNC rg, SQUserPointer up, const SQChar *sourcename, SQObjectPtr &out, bool raiseerror, bool lineinfo);
#endif //_SQCOMPILER_H_

// <--- back to sqapi.cpp
// ---- #include "sqfuncstate.h"
// ---> including sqfuncstate.h
/*	see copyright notice in squirrel.h */
#ifndef _SQFUNCSTATE_H_
#define _SQFUNCSTATE_H_
///////////////////////////////////
// ---- #include "squtils.h"
// ---> including squtils.h
// <--- back to sqfuncstate.h

struct SQFuncState
{
	SQFuncState(SQSharedState *ss,SQFuncState *parent,CompilerErrorFunc efunc,void *ed);
	~SQFuncState();
#ifdef _DEBUG_DUMP
	void Dump(SQFunctionProto *func);
#endif
	void Error(const SQChar *err);
	SQFuncState *PushChildState(SQSharedState *ss);
	void PopChildState();
	void AddInstruction(SQOpcode _op,SQInteger arg0=0,SQInteger arg1=0,SQInteger arg2=0,SQInteger arg3=0){SQInstruction i(_op,arg0,arg1,arg2,arg3);AddInstruction(i);}
	void AddInstruction(SQInstruction &i);
	void SetIntructionParams(SQInteger pos,SQInteger arg0,SQInteger arg1,SQInteger arg2=0,SQInteger arg3=0);
	void SetIntructionParam(SQInteger pos,SQInteger arg,SQInteger val);
	SQInstruction &GetInstruction(SQInteger pos){return _instructions[pos];}
	void PopInstructions(SQInteger size){for(SQInteger i=0;i<size;i++)_instructions.pop_back();}
	void SetStackSize(SQInteger n);
	SQInteger CountOuters(SQInteger stacksize);
	void SnoozeOpt(){_optimization=false;}
	void AddDefaultParam(SQInteger trg) { _defaultparams.push_back(trg); }
	SQInteger GetDefaultParamCount() { return _defaultparams.size(); }
	SQInteger GetCurrentPos(){return _instructions.size()-1;}
	SQInteger GetNumericConstant(const SQInteger cons);
	SQInteger GetNumericConstant(const SQFloat cons);
	SQInteger PushLocalVariable(const SQObject &name);
	void AddParameter(const SQObject &name);
	//void AddOuterValue(const SQObject &name);
	SQInteger GetLocalVariable(const SQObject &name);
	void MarkLocalAsOuter(SQInteger pos);
	SQInteger GetOuterVariable(const SQObject &name);
	SQInteger GenerateCode();
	SQInteger GetStackSize();
	SQInteger CalcStackFrameSize();
	void AddLineInfos(SQInteger line,bool lineop,bool force=false);
	SQFunctionProto *BuildProto();
	SQInteger AllocStackPos();
	SQInteger PushTarget(SQInteger n=-1);
	SQInteger PopTarget();
	SQInteger TopTarget();
	SQInteger GetUpTarget(SQInteger n);
	void DiscardTarget();
	bool IsLocal(SQUnsignedInteger stkpos);
	SQObject CreateString(const SQChar *s,SQInteger len = -1);
	SQObject CreateTable();
	bool IsConstant(const SQObject &name,SQObject &e);
	SQInteger _returnexp;
	SQLocalVarInfoVec _vlocals;
	SQIntVec _targetstack;
	SQInteger _stacksize;
	bool _varparams;
	bool _bgenerator;
	SQIntVec _unresolvedbreaks;
	SQIntVec _unresolvedcontinues;
	SQObjectPtrVec _functions;
	SQObjectPtrVec _parameters;
	SQOuterVarVec _outervalues;
	SQInstructionVec _instructions;
	SQLocalVarInfoVec _localvarinfos;
	SQObjectPtr _literals;
	SQObjectPtr _strings;
	SQObjectPtr _name;
	SQObjectPtr _sourcename;
	SQInteger _nliterals;
	SQLineInfoVec _lineinfos;
	SQFuncState *_parent;
	SQIntVec _scope_blocks;
	SQIntVec _breaktargets;
	SQIntVec _continuetargets;
	SQIntVec _defaultparams;
	SQInteger _lastline;
	SQInteger _traps; //contains number of nested exception traps
	SQInteger _outers;
	bool _optimization;
	SQSharedState *_sharedstate;
	sqvector<SQFuncState*> _childstates;
	SQInteger GetConstant(const SQObject &cons);
private:
	CompilerErrorFunc _errfunc;
	void *_errtarget;
	SQSharedState *_ss;
};


#endif //_SQFUNCSTATE_H_


// <--- back to sqapi.cpp
// ---- #include "sqclass.h"
// ---> including sqclass.h
/*	see copyright notice in squirrel.h */
#ifndef _SQCLASS_H_
#define _SQCLASS_H_

struct SQInstance;

struct SQClassMember {
	SQObjectPtr val;
	SQObjectPtr attrs;
};

typedef sqvector<SQClassMember> SQClassMemberVec;

#define MEMBER_TYPE_METHOD 0x01000000
#define MEMBER_TYPE_FIELD 0x02000000

#define _ismethod(o) (_integer(o)&MEMBER_TYPE_METHOD)
#define _isfield(o) (_integer(o)&MEMBER_TYPE_FIELD)
#define _make_method_idx(i) ((SQInteger)(MEMBER_TYPE_METHOD|i))
#define _make_field_idx(i) ((SQInteger)(MEMBER_TYPE_FIELD|i))
#define _member_type(o) (_integer(o)&0xFF000000)
#define _member_idx(o) (_integer(o)&0x00FFFFFF)

struct SQClass : public CHAINABLE_OBJ
{
	SQClass(SQSharedState *ss,SQClass *base);
public:
	static SQClass* Create(SQSharedState *ss,SQClass *base) {
		SQClass *newclass = (SQClass *)SQ_MALLOC(sizeof(SQClass));
		new (newclass) SQClass(ss, base);
		return newclass;
	}
	~SQClass();
	bool NewSlot(SQSharedState *ss, const SQObjectPtr &key,const SQObjectPtr &val,bool bstatic);
	bool Get(const SQObjectPtr &key,SQObjectPtr &val) {
		if(_members->Get(key,val)) {
			if(_isfield(val)) {
				SQObjectPtr &o = _defaultvalues[_member_idx(val)].val;
				val = _realval(o);
			}
			else {
				val = _methods[_member_idx(val)].val;
			}
			return true;
		}
		return false;
	}
	bool GetConstructor(SQObjectPtr &ctor)
	{
		if(_constructoridx != -1) {
			ctor = _methods[_constructoridx].val;
			return true;
		}
		return false;
	}
	bool SetAttributes(const SQObjectPtr &key,const SQObjectPtr &val);
	bool GetAttributes(const SQObjectPtr &key,SQObjectPtr &outval);
	void Lock() { _locked = true; if(_base) _base->Lock(); }
	void Release() { 
		if (_hook) { _hook(_typetag,0);}
		sq_delete(this, SQClass);	
	}
	void Finalize();
#ifndef NO_GARBAGE_COLLECTOR
	void Mark(SQCollectable ** );
	SQObjectType GetType() {return OT_CLASS;}
#endif
	SQInteger Next(const SQObjectPtr &refpos, SQObjectPtr &outkey, SQObjectPtr &outval);
	SQInstance *CreateInstance();
	SQTable *_members;
	SQClass *_base;
	SQClassMemberVec _defaultvalues;
	SQClassMemberVec _methods;
	SQObjectPtr _metamethods[MT_LAST];
	SQObjectPtr _attributes;
	SQUserPointer _typetag;
	SQRELEASEHOOK _hook;
	bool _locked;
	SQInteger _constructoridx;
	SQInteger _udsize;
};

#define calcinstancesize(_theclass_) \
	(_theclass_->_udsize + sq_aligning(sizeof(SQInstance) +  (sizeof(SQObjectPtr)*(_theclass_->_defaultvalues.size()>0?_theclass_->_defaultvalues.size()-1:0))))

struct SQInstance : public SQDelegable 
{
	void Init(SQSharedState *ss);
	SQInstance(SQSharedState *ss, SQClass *c, SQInteger memsize);
	SQInstance(SQSharedState *ss, SQInstance *c, SQInteger memsize);
public:
	static SQInstance* Create(SQSharedState *ss,SQClass *theclass) {
		
		SQInteger size = calcinstancesize(theclass);
		SQInstance *newinst = (SQInstance *)SQ_MALLOC(size);
		new (newinst) SQInstance(ss, theclass,size);
		if(theclass->_udsize) {
			newinst->_userpointer = ((unsigned char *)newinst) + (size - theclass->_udsize);
		}
		return newinst;
	}
	SQInstance *Clone(SQSharedState *ss)
	{
		SQInteger size = calcinstancesize(_class);
		SQInstance *newinst = (SQInstance *)SQ_MALLOC(size);
		new (newinst) SQInstance(ss, this,size);
		if(_class->_udsize) {
			newinst->_userpointer = ((unsigned char *)newinst) + (size - _class->_udsize);
		}
		return newinst;
	}
	~SQInstance();
	bool Get(const SQObjectPtr &key,SQObjectPtr &val)  {
		if(_class->_members->Get(key,val)) {
			if(_isfield(val)) {
				SQObjectPtr &o = _values[_member_idx(val)];
				val = _realval(o);
			}
			else {
				val = _class->_methods[_member_idx(val)].val;
			}
			return true;
		}
		return false;
	}
	bool Set(const SQObjectPtr &key,const SQObjectPtr &val) {
		SQObjectPtr idx;
		if(_class->_members->Get(key,idx) && _isfield(idx)) {
            _values[_member_idx(idx)] = val;
			return true;
		}
		return false;
	}
	void Release() {
		_uiRef++;
		if (_hook) { _hook(_userpointer,0);}
		_uiRef--;
		if(_uiRef > 0) return;
		SQInteger size = _memsize;
		this->~SQInstance();
		SQ_FREE(this, size);
	}
	void Finalize();
#ifndef NO_GARBAGE_COLLECTOR 
	void Mark(SQCollectable ** );
	SQObjectType GetType() {return OT_INSTANCE;}
#endif
	bool InstanceOf(SQClass *trg);
	bool GetMetaMethod(SQVM *v,SQMetaMethod mm,SQObjectPtr &res);

	SQClass *_class;
	SQUserPointer _userpointer;
	SQRELEASEHOOK _hook;
	SQInteger _memsize;
	SQObjectPtr _values[1];
};

#endif //_SQCLASS_H_

// <--- back to sqapi.cpp

bool sq_aux_gettypedarg(HSQUIRRELVM v,SQInteger idx,SQObjectType type,SQObjectPtr **o)
{
	*o = &stack_get(v,idx);
	if(type(**o) != type){
		SQObjectPtr oval = v->PrintObjVal(**o);
		v->Raise_Error(_SC("wrong argument type, expected '%s' got '%.50s'"),IdType2Name(type),_stringval(oval));
		return false;
	}
	return true;
}

#define _GETSAFE_OBJ(v,idx,type,o) { if(!sq_aux_gettypedarg(v,idx,type,&o)) return SQ_ERROR; }

#define sq_aux_paramscheck(v,count) \
{ \
	if(sq_gettop(v) < count){ v->Raise_Error(_SC("not enough params in the stack")); return SQ_ERROR; }\
}		


SQInteger sq_aux_invalidtype(HSQUIRRELVM v,SQObjectType type)
{
	scsprintf(_ss(v)->GetScratchPad(100), _SC("unexpected type %s"), IdType2Name(type));
	return sq_throwerror(v, _ss(v)->GetScratchPad(-1));
}

HSQUIRRELVM sq_open(SQInteger initialstacksize)
{
	SQSharedState *ss;
	SQVM *v;
	sq_new(ss, SQSharedState);
	ss->Init();
	v = (SQVM *)SQ_MALLOC(sizeof(SQVM));
	new (v) SQVM(ss);
	ss->_root_vm = v;
	if(v->Init(NULL, initialstacksize)) {
		return v;
	} else {
		sq_delete(v, SQVM);
		return NULL;
	}
	return v;
}

HSQUIRRELVM sq_newthread(HSQUIRRELVM friendvm, SQInteger initialstacksize)
{
	SQSharedState *ss;
	SQVM *v;
	ss=_ss(friendvm);
	
	v= (SQVM *)SQ_MALLOC(sizeof(SQVM));
	new (v) SQVM(ss);
	
	if(v->Init(friendvm, initialstacksize)) {
		friendvm->Push(v);
		return v;
	} else {
		sq_delete(v, SQVM);
		return NULL;
	}
}

SQInteger sq_getvmstate(HSQUIRRELVM v)
{
	if(v->_suspended)
		return SQ_VMSTATE_SUSPENDED;
	else { 
		if(v->_callsstacksize != 0) return SQ_VMSTATE_RUNNING;
		else return SQ_VMSTATE_IDLE;
	}
}

void sq_seterrorhandler(HSQUIRRELVM v)
{
	SQObject o = stack_get(v, -1);
	if(sq_isclosure(o) || sq_isnativeclosure(o) || sq_isnull(o)) {
		v->_errorhandler = o;
		v->Pop();
	}
}

void sq_setnativedebughook(HSQUIRRELVM v,SQDEBUGHOOK hook)
{
	v->_debughook_native = hook;
	v->_debughook_closure.Null();
	v->_debughook = hook?true:false;
}

void sq_setdebughook(HSQUIRRELVM v)
{
	SQObject o = stack_get(v,-1);
	if(sq_isclosure(o) || sq_isnativeclosure(o) || sq_isnull(o)) {
		v->_debughook_closure = o;
		v->_debughook_native = NULL;
		v->_debughook = !sq_isnull(o);
		v->Pop();
	}
}

void sq_close(HSQUIRRELVM v)
{
	SQSharedState *ss = _ss(v);
	_thread(ss->_root_vm)->Finalize();
	sq_delete(ss, SQSharedState);
}

SQInteger sq_getversion()
{
	return SQUIRREL_VERSION_NUMBER;
}

SQRESULT sq_compile(HSQUIRRELVM v,SQLEXREADFUNC read,SQUserPointer p,const SQChar *sourcename,SQBool raiseerror)
{
	SQObjectPtr o;
#ifndef NO_COMPILER
	if(Compile(v, read, p, sourcename, o, raiseerror?true:false, _ss(v)->_debuginfo)) {
		v->Push(SQClosure::Create(_ss(v), _funcproto(o)));
		return SQ_OK;
	}
	return SQ_ERROR;
#else
	return sq_throwerror(v,_SC("this is a no compiler build"));
#endif
}

void sq_enabledebuginfo(HSQUIRRELVM v, SQBool enable)
{
	_ss(v)->_debuginfo = enable?true:false;
}

void sq_notifyallexceptions(HSQUIRRELVM v, SQBool enable)
{
	_ss(v)->_notifyallexceptions = enable?true:false;
}

void sq_addref(HSQUIRRELVM v,HSQOBJECT *po)
{
	if(!ISREFCOUNTED(type(*po))) return;
#ifdef NO_GARBAGE_COLLECTOR
	__AddRef(po->_type,po->_unVal);
#else
	_ss(v)->_refs_table.AddRef(*po);
#endif
}

SQUnsignedInteger sq_getrefcount(HSQUIRRELVM v,HSQOBJECT *po)
{
	if(!ISREFCOUNTED(type(*po))) return 0;
#ifdef NO_GARBAGE_COLLECTOR
   return po->_unVal.pRefCounted->_uiRef; 
#else
   return _ss(v)->_refs_table.GetRefCount(*po); 
#endif 
}

SQBool sq_release(HSQUIRRELVM v,HSQOBJECT *po)
{
	if(!ISREFCOUNTED(type(*po))) return SQTrue;
#ifdef NO_GARBAGE_COLLECTOR
	bool ret = (po->_unVal.pRefCounted->_uiRef <= 1) ? SQTrue : SQFalse;
	__Release(po->_type,po->_unVal);
	return ret; //the ret val doesn't work(and cannot be fixed)
#else
	return _ss(v)->_refs_table.Release(*po);
#endif
}

const SQChar *sq_objtostring(const HSQOBJECT *o) 
{
	if(sq_type(*o) == OT_STRING) {
		return _stringval(*o);
	}
	return NULL;
}

SQInteger sq_objtointeger(const HSQOBJECT *o) 
{
	if(sq_isnumeric(*o)) {
		return tointeger(*o);
	}
	return 0;
}

SQFloat sq_objtofloat(const HSQOBJECT *o) 
{
	if(sq_isnumeric(*o)) {
		return tofloat(*o);
	}
	return 0;
}

SQBool sq_objtobool(const HSQOBJECT *o) 
{
	if(sq_isbool(*o)) {
		return _integer(*o);
	}
	return SQFalse;
}

SQUserPointer sq_objtouserpointer(const HSQOBJECT *o)
{
	if(sq_isuserpointer(*o)) {
		return _userpointer(*o);
	}
	return 0;
}

void sq_pushnull(HSQUIRRELVM v)
{
	v->PushNull();
}

void sq_pushstring(HSQUIRRELVM v,const SQChar *s,SQInteger len)
{
	if(s)
		v->Push(SQObjectPtr(SQString::Create(_ss(v), s, len)));
	else v->PushNull();
}

void sq_pushinteger(HSQUIRRELVM v,SQInteger n)
{
	v->Push(n);
}

void sq_pushbool(HSQUIRRELVM v,SQBool b)
{
	v->Push(b?true:false);
}

void sq_pushfloat(HSQUIRRELVM v,SQFloat n)
{
	v->Push(n);
}

void sq_pushuserpointer(HSQUIRRELVM v,SQUserPointer p)
{
	v->Push(p);
}

SQUserPointer sq_newuserdata(HSQUIRRELVM v,SQUnsignedInteger size)
{
	SQUserData *ud = SQUserData::Create(_ss(v), size);
	v->Push(ud);
	return (SQUserPointer)sq_aligning(ud + 1);
}

void sq_newtable(HSQUIRRELVM v)
{
	v->Push(SQTable::Create(_ss(v), 0));	
}

void sq_newtableex(HSQUIRRELVM v,SQInteger initialcapacity)
{
	v->Push(SQTable::Create(_ss(v), initialcapacity));	
}

void sq_newarray(HSQUIRRELVM v,SQInteger size)
{
	v->Push(SQArray::Create(_ss(v), size));	
}

SQRESULT sq_newclass(HSQUIRRELVM v,SQBool hasbase)
{
	SQClass *baseclass = NULL;
	if(hasbase) {
		SQObjectPtr &base = stack_get(v,-1);
		if(type(base) != OT_CLASS)
			return sq_throwerror(v,_SC("invalid base type"));
		baseclass = _class(base);
	}
	SQClass *newclass = SQClass::Create(_ss(v), baseclass);
	if(baseclass) v->Pop();
	v->Push(newclass);	
	return SQ_OK;
}

SQBool sq_instanceof(HSQUIRRELVM v)
{
	SQObjectPtr &inst = stack_get(v,-1);
	SQObjectPtr &cl = stack_get(v,-2);
	if(type(inst) != OT_INSTANCE || type(cl) != OT_CLASS)
		return sq_throwerror(v,_SC("invalid param type"));
	return _instance(inst)->InstanceOf(_class(cl))?SQTrue:SQFalse;
}

SQRESULT sq_arrayappend(HSQUIRRELVM v,SQInteger idx)
{
	sq_aux_paramscheck(v,2);
	SQObjectPtr *arr;
	_GETSAFE_OBJ(v, idx, OT_ARRAY,arr);
	_array(*arr)->Append(v->GetUp(-1));
	v->Pop();
	return SQ_OK;
}

SQRESULT sq_arraypop(HSQUIRRELVM v,SQInteger idx,SQBool pushval)
{
	sq_aux_paramscheck(v, 1);
	SQObjectPtr *arr;
	_GETSAFE_OBJ(v, idx, OT_ARRAY,arr);
	if(_array(*arr)->Size() > 0) {
        if(pushval != 0){ v->Push(_array(*arr)->Top()); }
		_array(*arr)->Pop();
		return SQ_OK;
	}
	return sq_throwerror(v, _SC("empty array"));
}

SQRESULT sq_arrayresize(HSQUIRRELVM v,SQInteger idx,SQInteger newsize)
{
	sq_aux_paramscheck(v,1);
	SQObjectPtr *arr;
	_GETSAFE_OBJ(v, idx, OT_ARRAY,arr);
	if(newsize >= 0) {
		_array(*arr)->Resize(newsize);
		return SQ_OK;
	}
	return sq_throwerror(v,_SC("negative size"));
}


SQRESULT sq_arrayreverse(HSQUIRRELVM v,SQInteger idx)
{
	sq_aux_paramscheck(v, 1);
	SQObjectPtr *o;
	_GETSAFE_OBJ(v, idx, OT_ARRAY,o);
	SQArray *arr = _array(*o);
	if(arr->Size() > 0) {
		SQObjectPtr t;
		SQInteger size = arr->Size();
		SQInteger n = size >> 1; size -= 1;
		for(SQInteger i = 0; i < n; i++) {
			t = arr->_values[i];
			arr->_values[i] = arr->_values[size-i];
			arr->_values[size-i] = t;
		}
		return SQ_OK;
	}
	return SQ_OK;
}

SQRESULT sq_arrayremove(HSQUIRRELVM v,SQInteger idx,SQInteger itemidx)
{
	sq_aux_paramscheck(v, 1); 
	SQObjectPtr *arr;
	_GETSAFE_OBJ(v, idx, OT_ARRAY,arr); 
	return _array(*arr)->Remove(itemidx) ? SQ_OK : sq_throwerror(v,_SC("index out of range")); 
}

SQRESULT sq_arrayinsert(HSQUIRRELVM v,SQInteger idx,SQInteger destpos)
{
	sq_aux_paramscheck(v, 1); 
	SQObjectPtr *arr;
	_GETSAFE_OBJ(v, idx, OT_ARRAY,arr);
	SQRESULT ret = _array(*arr)->Insert(destpos, v->GetUp(-1)) ? SQ_OK : sq_throwerror(v,_SC("index out of range"));
	v->Pop();
	return ret;
}

void sq_newclosure(HSQUIRRELVM v,SQFUNCTION func,SQUnsignedInteger nfreevars)
{
	SQNativeClosure *nc = SQNativeClosure::Create(_ss(v), func,nfreevars);
	nc->_nparamscheck = 0;
	for(SQUnsignedInteger i = 0; i < nfreevars; i++) {
		nc->_outervalues[i] = v->Top();
		v->Pop();
	}
	v->Push(SQObjectPtr(nc));	
}

SQRESULT sq_getclosureinfo(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger *nparams,SQUnsignedInteger *nfreevars)
{
	SQObject o = stack_get(v, idx);
	if(type(o) == OT_CLOSURE) {
		SQClosure *c = _closure(o);
		SQFunctionProto *proto = c->_function;
		*nparams = (SQUnsignedInteger)proto->_nparameters;
		*nfreevars = (SQUnsignedInteger)proto->_noutervalues;
		return SQ_OK;
	}
	else if(type(o) == OT_NATIVECLOSURE)
	{
		SQNativeClosure *c = _nativeclosure(o);
		*nparams = (SQUnsignedInteger)c->_nparamscheck;
		*nfreevars = c->_noutervalues;
		return SQ_OK;
	}
	return sq_throwerror(v,_SC("the object is not a closure"));
}

SQRESULT sq_setnativeclosurename(HSQUIRRELVM v,SQInteger idx,const SQChar *name)
{
	SQObject o = stack_get(v, idx);
	if(sq_isnativeclosure(o)) {
		SQNativeClosure *nc = _nativeclosure(o);
		nc->_name = SQString::Create(_ss(v),name);
		return SQ_OK;
	}
	return sq_throwerror(v,_SC("the object is not a nativeclosure"));
}

SQRESULT sq_setparamscheck(HSQUIRRELVM v,SQInteger nparamscheck,const SQChar *typemask)
{
	SQObject o = stack_get(v, -1);
	if(!sq_isnativeclosure(o))
		return sq_throwerror(v, _SC("native closure expected"));
	SQNativeClosure *nc = _nativeclosure(o);
	nc->_nparamscheck = nparamscheck;
	if(typemask) {
		SQIntVec res;
		if(!CompileTypemask(res, typemask))
			return sq_throwerror(v, _SC("invalid typemask"));
		nc->_typecheck.copy(res);
	}
	else {
		nc->_typecheck.resize(0);
	}
	if(nparamscheck == SQ_MATCHTYPEMASKSTRING) {
		nc->_nparamscheck = nc->_typecheck.size();
	}
	return SQ_OK;
}

SQRESULT sq_bindenv(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr &o = stack_get(v,idx);
	if(!sq_isnativeclosure(o) &&
		!sq_isclosure(o))
		return sq_throwerror(v,_SC("the target is not a closure"));
    SQObjectPtr &env = stack_get(v,-1);
	if(!sq_istable(env) &&
		!sq_isclass(env) &&
		!sq_isinstance(env))
		return sq_throwerror(v,_SC("invalid environment"));
	SQWeakRef *w = _refcounted(env)->GetWeakRef(type(env));
	SQObjectPtr ret;
	if(sq_isclosure(o)) {
		SQClosure *c = _closure(o)->Clone();
		__ObjRelease(c->_env);
		c->_env = w;
		__ObjAddRef(c->_env);
		if(_closure(o)->_base) {
			c->_base = _closure(o)->_base;
			__ObjAddRef(c->_base);
		}
		ret = c;
	}
	else { //then must be a native closure
		SQNativeClosure *c = _nativeclosure(o)->Clone();
		__ObjRelease(c->_env);
		c->_env = w;
		__ObjAddRef(c->_env);
		ret = c;
	}
	v->Pop();
	v->Push(ret);
	return SQ_OK;
}

SQRESULT sq_getclosurename(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr &o = stack_get(v,idx);
	if(!sq_isnativeclosure(o) &&
		!sq_isclosure(o))
		return sq_throwerror(v,_SC("the target is not a closure"));
	if(sq_isnativeclosure(o))
	{
		v->Push(_nativeclosure(o)->_name);
	}
	else { //closure
		v->Push(_closure(o)->_function->_name);
	}
	return SQ_OK;
}

SQRESULT sq_clear(HSQUIRRELVM v,SQInteger idx)
{
	SQObject &o=stack_get(v,idx);
	switch(type(o)) {
		case OT_TABLE: _table(o)->Clear();	break;
		case OT_ARRAY: _array(o)->Resize(0); break;
		default:
			return sq_throwerror(v, _SC("clear only works on table and array"));
		break;

	}
	return SQ_OK;
}

void sq_pushroottable(HSQUIRRELVM v)
{
	v->Push(v->_roottable);
}

void sq_pushregistrytable(HSQUIRRELVM v)
{
	v->Push(_ss(v)->_registry);
}

void sq_pushconsttable(HSQUIRRELVM v)
{
	v->Push(_ss(v)->_consts);
}

SQRESULT sq_setroottable(HSQUIRRELVM v)
{
	SQObject o = stack_get(v, -1);
	if(sq_istable(o) || sq_isnull(o)) {
		v->_roottable = o;
		v->Pop();
		return SQ_OK;
	}
	return sq_throwerror(v, _SC("ivalid type"));
}

SQRESULT sq_setconsttable(HSQUIRRELVM v)
{
	SQObject o = stack_get(v, -1);
	if(sq_istable(o)) {
		_ss(v)->_consts = o;
		v->Pop();
		return SQ_OK;
	}
	return sq_throwerror(v, _SC("ivalid type, expected table"));
}

void sq_setforeignptr(HSQUIRRELVM v,SQUserPointer p)
{
	v->_foreignptr = p;
}

SQUserPointer sq_getforeignptr(HSQUIRRELVM v)
{
	return v->_foreignptr;
}

void sq_push(HSQUIRRELVM v,SQInteger idx)
{
	v->Push(stack_get(v, idx));
}

SQObjectType sq_gettype(HSQUIRRELVM v,SQInteger idx)
{
	return type(stack_get(v, idx));
}

SQRESULT sq_typeof(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr &o = stack_get(v, idx);
	SQObjectPtr res;
	if(!v->TypeOf(o,res)) {
		return SQ_ERROR;
	}
	v->Push(res);
	return SQ_OK;
}

SQRESULT sq_tostring(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr &o = stack_get(v, idx);
	SQObjectPtr res;
	if(!v->ToString(o,res)) {
		return SQ_ERROR;
	}
	v->Push(res);
	return SQ_OK;
}

void sq_tobool(HSQUIRRELVM v, SQInteger idx, SQBool *b)
{
	SQObjectPtr &o = stack_get(v, idx);
	*b = SQVM::IsFalse(o)?SQFalse:SQTrue;
}

SQRESULT sq_getinteger(HSQUIRRELVM v,SQInteger idx,SQInteger *i)
{
	SQObjectPtr &o = stack_get(v, idx);
	if(sq_isnumeric(o)) {
		*i = tointeger(o);
		return SQ_OK;
	}
	return SQ_ERROR;
}

SQRESULT sq_getfloat(HSQUIRRELVM v,SQInteger idx,SQFloat *f)
{
	SQObjectPtr &o = stack_get(v, idx);
	if(sq_isnumeric(o)) {
		*f = tofloat(o);
		return SQ_OK;
	}
	return SQ_ERROR;
}

SQRESULT sq_getbool(HSQUIRRELVM v,SQInteger idx,SQBool *b)
{
	SQObjectPtr &o = stack_get(v, idx);
	if(sq_isbool(o)) {
		*b = _integer(o);
		return SQ_OK;
	}
	return SQ_ERROR;
}

SQRESULT sq_getstring(HSQUIRRELVM v,SQInteger idx,const SQChar **c)
{
	SQObjectPtr *o = NULL;
	_GETSAFE_OBJ(v, idx, OT_STRING,o);
	*c = _stringval(*o);
	return SQ_OK;
}

SQRESULT sq_getthread(HSQUIRRELVM v,SQInteger idx,HSQUIRRELVM *thread)
{
	SQObjectPtr *o = NULL;
	_GETSAFE_OBJ(v, idx, OT_THREAD,o);
	*thread = _thread(*o);
	return SQ_OK;
}

SQRESULT sq_clone(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr &o = stack_get(v,idx);
	v->PushNull();
	if(!v->Clone(o, stack_get(v, -1))){
		v->Pop();
		return SQ_ERROR;
	}
	return SQ_OK;
}

SQInteger sq_getsize(HSQUIRRELVM v, SQInteger idx)
{
	SQObjectPtr &o = stack_get(v, idx);
	SQObjectType type = type(o);
	switch(type) {
	case OT_STRING:		return _string(o)->_len;
	case OT_TABLE:		return _table(o)->CountUsed();
	case OT_ARRAY:		return _array(o)->Size();
	case OT_USERDATA:	return _userdata(o)->_size;
	case OT_INSTANCE:	return _instance(o)->_class->_udsize;
	case OT_CLASS:		return _class(o)->_udsize;
	default:
		return sq_aux_invalidtype(v, type);
	}
}

SQHash sq_gethash(HSQUIRRELVM v, SQInteger idx)
{
	SQObjectPtr &o = stack_get(v, idx);
	return HashObj(o);
}

SQRESULT sq_getuserdata(HSQUIRRELVM v,SQInteger idx,SQUserPointer *p,SQUserPointer *typetag)
{
	SQObjectPtr *o = NULL;
	_GETSAFE_OBJ(v, idx, OT_USERDATA,o);
	(*p) = _userdataval(*o);
	if(typetag) *typetag = _userdata(*o)->_typetag;
	return SQ_OK;
}

SQRESULT sq_settypetag(HSQUIRRELVM v,SQInteger idx,SQUserPointer typetag)
{
	SQObjectPtr &o = stack_get(v,idx);
	switch(type(o)) {
		case OT_USERDATA:	_userdata(o)->_typetag = typetag;	break;
		case OT_CLASS:		_class(o)->_typetag = typetag;		break;
		default:			return sq_throwerror(v,_SC("invalid object type"));
	}
	return SQ_OK;
}

SQRESULT sq_getobjtypetag(const HSQOBJECT *o,SQUserPointer * typetag)
{
  switch(type(*o)) {
    case OT_INSTANCE: *typetag = _instance(*o)->_class->_typetag; break;
    case OT_USERDATA: *typetag = _userdata(*o)->_typetag; break;
    case OT_CLASS:    *typetag = _class(*o)->_typetag; break;
    default: return SQ_ERROR;
  }
  return SQ_OK;
}

SQRESULT sq_gettypetag(HSQUIRRELVM v,SQInteger idx,SQUserPointer *typetag)
{
	SQObjectPtr &o = stack_get(v,idx);
	if(SQ_FAILED(sq_getobjtypetag(&o,typetag)))
		return sq_throwerror(v,_SC("invalid object type"));
	return SQ_OK;
}

SQRESULT sq_getuserpointer(HSQUIRRELVM v, SQInteger idx, SQUserPointer *p)
{
	SQObjectPtr *o = NULL;
	_GETSAFE_OBJ(v, idx, OT_USERPOINTER,o);
	(*p) = _userpointer(*o);
	return SQ_OK;
}

SQRESULT sq_setinstanceup(HSQUIRRELVM v, SQInteger idx, SQUserPointer p)
{
	SQObjectPtr &o = stack_get(v,idx);
	if(type(o) != OT_INSTANCE) return sq_throwerror(v,_SC("the object is not a class instance"));
	_instance(o)->_userpointer = p;
	return SQ_OK;
}

SQRESULT sq_setclassudsize(HSQUIRRELVM v, SQInteger idx, SQInteger udsize)
{
	SQObjectPtr &o = stack_get(v,idx);
	if(type(o) != OT_CLASS) return sq_throwerror(v,_SC("the object is not a class"));
	if(_class(o)->_locked) return sq_throwerror(v,_SC("the class is locked"));
	_class(o)->_udsize = udsize;
	return SQ_OK;
}


SQRESULT sq_getinstanceup(HSQUIRRELVM v, SQInteger idx, SQUserPointer *p,SQUserPointer typetag)
{
	SQObjectPtr &o = stack_get(v,idx);
	if(type(o) != OT_INSTANCE) return sq_throwerror(v,_SC("the object is not a class instance"));
	(*p) = _instance(o)->_userpointer;
	if(typetag != 0) {
		SQClass *cl = _instance(o)->_class;
		do{
			if(cl->_typetag == typetag)
				return SQ_OK;
			cl = cl->_base;
		}while(cl != NULL);
		return sq_throwerror(v,_SC("invalid type tag"));
	}
	return SQ_OK;
}

SQInteger sq_gettop(HSQUIRRELVM v)
{
	return (v->_top) - v->_stackbase;
}

void sq_settop(HSQUIRRELVM v, SQInteger newtop)
{
	SQInteger top = sq_gettop(v);
	if(top > newtop)
		sq_pop(v, top - newtop);
	else
		while(top++ < newtop) sq_pushnull(v);
}

void sq_pop(HSQUIRRELVM v, SQInteger nelemstopop)
{
	assert(v->_top >= nelemstopop);
	v->Pop(nelemstopop);
}

void sq_poptop(HSQUIRRELVM v)
{
	assert(v->_top >= 1);
    v->Pop();
}


void sq_remove(HSQUIRRELVM v, SQInteger idx)
{
	v->Remove(idx);
}

SQInteger sq_cmp(HSQUIRRELVM v)
{
	SQInteger res;
	v->ObjCmp(stack_get(v, -1), stack_get(v, -2),res);
	return res;
}

SQRESULT sq_newslot(HSQUIRRELVM v, SQInteger idx, SQBool bstatic)
{
	sq_aux_paramscheck(v, 3);
	SQObjectPtr &self = stack_get(v, idx);
	if(type(self) == OT_TABLE || type(self) == OT_CLASS) {
		SQObjectPtr &key = v->GetUp(-2);
		if(type(key) == OT_NULL) return sq_throwerror(v, _SC("null is not a valid key"));
		v->NewSlot(self, key, v->GetUp(-1),bstatic?true:false);
		v->Pop(2);
	}
	return SQ_OK;
}

SQRESULT sq_deleteslot(HSQUIRRELVM v,SQInteger idx,SQBool pushval)
{
	sq_aux_paramscheck(v, 2);
	SQObjectPtr *self;
	_GETSAFE_OBJ(v, idx, OT_TABLE,self);
	SQObjectPtr &key = v->GetUp(-1);
	if(type(key) == OT_NULL) return sq_throwerror(v, _SC("null is not a valid key"));
	SQObjectPtr res;
	if(!v->DeleteSlot(*self, key, res)){
		return SQ_ERROR;
	}
	if(pushval)	v->GetUp(-1) = res;
	else v->Pop();
	return SQ_OK;
}

SQRESULT sq_set(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr &self = stack_get(v, idx);
	if(v->Set(self, v->GetUp(-2), v->GetUp(-1),DONT_FALL_BACK)) {
		v->Pop(2);
		return SQ_OK;
	}
	return SQ_ERROR;
}

SQRESULT sq_rawset(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr &self = stack_get(v, idx);
	if(type(v->GetUp(-2)) == OT_NULL) {
		v->Pop(2);
		return sq_throwerror(v, _SC("null key"));
	}
	switch(type(self)) {
	case OT_TABLE:
		_table(self)->NewSlot(v->GetUp(-2), v->GetUp(-1));
		v->Pop(2);
		return SQ_OK;
	break;
	case OT_CLASS:
		_class(self)->NewSlot(_ss(v), v->GetUp(-2), v->GetUp(-1),false);
		v->Pop(2);
		return SQ_OK;
	break;
	case OT_INSTANCE:
		if(_instance(self)->Set(v->GetUp(-2), v->GetUp(-1))) {
			v->Pop(2);
			return SQ_OK;
		}
	break;
	case OT_ARRAY:
		if(v->Set(self, v->GetUp(-2), v->GetUp(-1),false)) {
			v->Pop(2);
			return SQ_OK;
		}
	break;
	default:
		v->Pop(2);
		return sq_throwerror(v, _SC("rawset works only on array/table/class and instance"));
	}
	v->Raise_IdxError(v->GetUp(-2));return SQ_ERROR;
}

SQRESULT sq_newmember(HSQUIRRELVM v,SQInteger idx,SQBool bstatic)
{
	SQObjectPtr &self = stack_get(v, idx);
	if(type(self) != OT_CLASS) return sq_throwerror(v, _SC("new member only works with classes"));
	if(type(v->GetUp(-3)) == OT_NULL) return sq_throwerror(v, _SC("null key"));
	if(!v->NewSlotA(self,v->GetUp(-3),v->GetUp(-2),v->GetUp(-1),bstatic?true:false,false))
		return SQ_ERROR;
	return SQ_OK; 
}

SQRESULT sq_rawnewmember(HSQUIRRELVM v,SQInteger idx,SQBool bstatic)
{
	SQObjectPtr &self = stack_get(v, idx);
	if(type(self) != OT_CLASS) return sq_throwerror(v, _SC("new member only works with classes"));
	if(type(v->GetUp(-3)) == OT_NULL) return sq_throwerror(v, _SC("null key"));
	if(!v->NewSlotA(self,v->GetUp(-3),v->GetUp(-2),v->GetUp(-1),bstatic?true:false,true))
		return SQ_ERROR;
	return SQ_OK; 
}

SQRESULT sq_setdelegate(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr &self = stack_get(v, idx);
	SQObjectPtr &mt = v->GetUp(-1);
	SQObjectType type = type(self);
	switch(type) {
	case OT_TABLE:
		if(type(mt) == OT_TABLE) {
			if(!_table(self)->SetDelegate(_table(mt))) return sq_throwerror(v, _SC("delagate cycle")); v->Pop();}
		else if(type(mt)==OT_NULL) {
			_table(self)->SetDelegate(NULL); v->Pop(); }
		else return sq_aux_invalidtype(v,type);
		break;
	case OT_USERDATA:
		if(type(mt)==OT_TABLE) {
			_userdata(self)->SetDelegate(_table(mt)); v->Pop(); }
		else if(type(mt)==OT_NULL) {
			_userdata(self)->SetDelegate(NULL); v->Pop(); }
		else return sq_aux_invalidtype(v, type);
		break;
	default:
			return sq_aux_invalidtype(v, type);
		break;
	}
	return SQ_OK;
}

SQRESULT sq_rawdeleteslot(HSQUIRRELVM v,SQInteger idx,SQBool pushval)
{
	sq_aux_paramscheck(v, 2);
	SQObjectPtr *self;
	_GETSAFE_OBJ(v, idx, OT_TABLE,self);
	SQObjectPtr &key = v->GetUp(-1);
	SQObjectPtr t;
	if(_table(*self)->Get(key,t)) {
		_table(*self)->Remove(key);
	}
	if(pushval != 0)
		v->GetUp(-1) = t;
	else
		v->Pop();
	return SQ_OK;
}

SQRESULT sq_getdelegate(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr &self=stack_get(v,idx);
	switch(type(self)){
	case OT_TABLE:
	case OT_USERDATA:
		if(!_delegable(self)->_delegate){
			v->PushNull();
			break;
		}
		v->Push(SQObjectPtr(_delegable(self)->_delegate));
		break;
	default: return sq_throwerror(v,_SC("wrong type")); break;
	}
	return SQ_OK;
	
}

SQRESULT sq_get(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr &self=stack_get(v,idx);
	if(v->Get(self,v->GetUp(-1),v->GetUp(-1),false,DONT_FALL_BACK))
		return SQ_OK;
	v->Pop();
	return SQ_ERROR;
}

SQRESULT sq_rawget(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr &self=stack_get(v,idx);
	switch(type(self)) {
	case OT_TABLE:
		if(_table(self)->Get(v->GetUp(-1),v->GetUp(-1)))
			return SQ_OK;
		break;
	case OT_CLASS:
		if(_class(self)->Get(v->GetUp(-1),v->GetUp(-1)))
			return SQ_OK;
		break;
	case OT_INSTANCE:
		if(_instance(self)->Get(v->GetUp(-1),v->GetUp(-1)))
			return SQ_OK;
		break;
	case OT_ARRAY:{
		SQObjectPtr& key = v->GetUp(-1);
		if(sq_isnumeric(key)){
			if(_array(self)->Get(tointeger(key),v->GetUp(-1))) {
				return SQ_OK;
			}
		}
		else {
			v->Pop();
			return sq_throwerror(v,_SC("invalid index type for an array"));
		}
				  }
		break;
	default:
		v->Pop();
		return sq_throwerror(v,_SC("rawget works only on array/table/instance and class"));
	}	
	v->Pop();
	return sq_throwerror(v,_SC("the index doesn't exist"));
}

SQRESULT sq_getstackobj(HSQUIRRELVM v,SQInteger idx,HSQOBJECT *po)
{
	*po=stack_get(v,idx);
	return SQ_OK;
}

const SQChar *sq_getlocal(HSQUIRRELVM v,SQUnsignedInteger level,SQUnsignedInteger idx)
{
	SQUnsignedInteger cstksize=v->_callsstacksize;
	SQUnsignedInteger lvl=(cstksize-level)-1;
	SQInteger stackbase=v->_stackbase;
	if(lvl<cstksize){
		for(SQUnsignedInteger i=0;i<level;i++){
			SQVM::CallInfo &ci=v->_callsstack[(cstksize-i)-1];
			stackbase-=ci._prevstkbase;
		}
		SQVM::CallInfo &ci=v->_callsstack[lvl];
		if(type(ci._closure)!=OT_CLOSURE)
			return NULL;
		SQClosure *c=_closure(ci._closure);
		SQFunctionProto *func=c->_function;
		if(func->_noutervalues > (SQInteger)idx) {
			v->Push(*_outer(c->_outervalues[idx])->_valptr);
			return _stringval(func->_outervalues[idx]._name);
		}
		idx -= func->_noutervalues;
		return func->GetLocal(v,stackbase,idx,(SQInteger)(ci._ip-func->_instructions)-1);
	}
	return NULL;
}

void sq_pushobject(HSQUIRRELVM v,HSQOBJECT obj)
{
	v->Push(SQObjectPtr(obj));
}

void sq_resetobject(HSQOBJECT *po)
{
	po->_unVal.pUserPointer=NULL;po->_type=OT_NULL;
}

SQRESULT sq_throwerror(HSQUIRRELVM v,const SQChar *err)
{
	v->_lasterror=SQString::Create(_ss(v),err);
	return SQ_ERROR;
}

SQRESULT sq_throwobject(HSQUIRRELVM v)
{
	v->_lasterror = v->GetUp(-1);
	v->Pop();
	return SQ_ERROR;
}


void sq_reseterror(HSQUIRRELVM v)
{
	v->_lasterror.Null();
}

void sq_getlasterror(HSQUIRRELVM v)
{
	v->Push(v->_lasterror);
}

SQRESULT sq_reservestack(HSQUIRRELVM v,SQInteger nsize)
{
	if (((SQUnsignedInteger)v->_top + nsize) > v->_stack.size()) {
		if(v->_nmetamethodscall) {
			return sq_throwerror(v,_SC("cannot resize stack while in  a metamethod"));
		}
		v->_stack.resize(v->_stack.size() + ((v->_top + nsize) - v->_stack.size()));
	}
	return SQ_OK;
}

SQRESULT sq_resume(HSQUIRRELVM v,SQBool retval,SQBool raiseerror)
{
	if(type(v->GetUp(-1))==OT_GENERATOR){
		v->PushNull(); //retval
		if(!v->Execute(v->GetUp(-2),0,v->_top,v->GetUp(-1),raiseerror,SQVM::ET_RESUME_GENERATOR))
		{v->Raise_Error(v->_lasterror); return SQ_ERROR;}
		if(!retval)
			v->Pop();
		return SQ_OK;
	}
	return sq_throwerror(v,_SC("only generators can be resumed"));
}

SQRESULT sq_call(HSQUIRRELVM v,SQInteger params,SQBool retval,SQBool raiseerror)
{
	SQObjectPtr res;
	if(v->Call(v->GetUp(-(params+1)),params,v->_top-params,res,raiseerror?true:false)){

		if(!v->_suspended) {
			v->Pop(params);//pop closure and args
		}
		if(retval){
			v->Push(res); return SQ_OK;
		}
		return SQ_OK;
	}
	else {
		v->Pop(params);
		return SQ_ERROR;
	}
	if(!v->_suspended)
		v->Pop(params);
	return sq_throwerror(v,_SC("call failed"));
}

SQRESULT sq_suspendvm(HSQUIRRELVM v)
{
	return v->Suspend();
}

SQRESULT sq_wakeupvm(HSQUIRRELVM v,SQBool wakeupret,SQBool retval,SQBool raiseerror,SQBool throwerror)
{
	SQObjectPtr ret;
	if(!v->_suspended)
		return sq_throwerror(v,_SC("cannot resume a vm that is not running any code"));
	SQInteger target = v->_suspended_target;
	if(wakeupret) {
		if(target != -1) {
			v->GetAt(v->_stackbase+v->_suspended_target)=v->GetUp(-1); //retval
		}
		v->Pop();
	} else if(target != -1) { v->GetAt(v->_stackbase+v->_suspended_target).Null(); }
	SQObjectPtr dummy;
	if(!v->Execute(dummy,-1,-1,ret,raiseerror,throwerror?SQVM::ET_RESUME_THROW_VM : SQVM::ET_RESUME_VM)) {
		return SQ_ERROR;
	}
	if(retval)
		v->Push(ret);
	return SQ_OK;
}

void sq_setreleasehook(HSQUIRRELVM v,SQInteger idx,SQRELEASEHOOK hook)
{
	if(sq_gettop(v) >= 1){
		SQObjectPtr &ud=stack_get(v,idx);
		switch( type(ud) ) {
		case OT_USERDATA:	_userdata(ud)->_hook = hook;	break;
		case OT_INSTANCE:	_instance(ud)->_hook = hook;	break;
		case OT_CLASS:		_class(ud)->_hook = hook;		break;
		default: break; //shutup compiler
		}
	}
}

void sq_setcompilererrorhandler(HSQUIRRELVM v,SQCOMPILERERROR f)
{
	_ss(v)->_compilererrorhandler = f;
}

SQRESULT sq_writeclosure(HSQUIRRELVM v,SQWRITEFUNC w,SQUserPointer up)
{
	SQObjectPtr *o = NULL;
	_GETSAFE_OBJ(v, -1, OT_CLOSURE,o);
	unsigned short tag = SQ_BYTECODE_STREAM_TAG;
	if(w(up,&tag,2) != 2)
		return sq_throwerror(v,_SC("io error"));
	if(!_closure(*o)->Save(v,up,w))
		return SQ_ERROR;
	return SQ_OK;
}

SQRESULT sq_readclosure(HSQUIRRELVM v,SQREADFUNC r,SQUserPointer up)
{
	SQObjectPtr closure;
	
	unsigned short tag;
	if(r(up,&tag,2) != 2)
		return sq_throwerror(v,_SC("io error"));
	if(tag != SQ_BYTECODE_STREAM_TAG)
		return sq_throwerror(v,_SC("invalid stream"));
	if(!SQClosure::Load(v,up,r,closure))
		return SQ_ERROR;
	v->Push(closure);
	return SQ_OK;
}

SQChar *sq_getscratchpad(HSQUIRRELVM v,SQInteger minsize)
{
	return _ss(v)->GetScratchPad(minsize);
}

SQRESULT sq_resurrectunreachable(HSQUIRRELVM v)
{
#ifndef NO_GARBAGE_COLLECTOR
	_ss(v)->ResurrectUnreachable(v);
	return SQ_OK;
#else
	return sq_throwerror(v,_SC("sq_resurrectunreachable requires a garbage collector build"));
#endif
}

SQInteger sq_collectgarbage(HSQUIRRELVM v)
{
#ifndef NO_GARBAGE_COLLECTOR
	return _ss(v)->CollectGarbage(v);
#else
	return -1;
#endif
}

SQRESULT sq_getcallee(HSQUIRRELVM v)
{
	if(v->_callsstacksize > 1)
	{
		v->Push(v->_callsstack[v->_callsstacksize - 2]._closure);
		return SQ_OK;
	}
	return sq_throwerror(v,_SC("no closure in the calls stack"));
}

const SQChar *sq_getfreevariable(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger nval)
{
	SQObjectPtr &self=stack_get(v,idx);
	const SQChar *name = NULL;
	switch(type(self))
	{
	case OT_CLOSURE:{
		SQClosure *clo = _closure(self);
		SQFunctionProto *fp = clo->_function;
		if(((SQUnsignedInteger)fp->_noutervalues) > nval) {
			v->Push(*(_outer(clo->_outervalues[nval])->_valptr));
			SQOuterVar &ov = fp->_outervalues[nval];
			name = _stringval(ov._name);
		}
					}
		break;
	case OT_NATIVECLOSURE:{
		SQNativeClosure *clo = _nativeclosure(self);
		if(clo->_noutervalues > nval) {
			v->Push(clo->_outervalues[nval]);
			name = _SC("@NATIVE");
		}
						  }
		break;
	default: break; //shutup compiler
	}
	return name;
}

SQRESULT sq_setfreevariable(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger nval)
{
	SQObjectPtr &self=stack_get(v,idx);
	switch(type(self))
	{
	case OT_CLOSURE:{
		SQFunctionProto *fp = _closure(self)->_function;
		if(((SQUnsignedInteger)fp->_noutervalues) > nval){
			*(_outer(_closure(self)->_outervalues[nval])->_valptr) = stack_get(v,-1);
		}
		else return sq_throwerror(v,_SC("invalid free var index"));
					}
		break;
	case OT_NATIVECLOSURE:
		if(_nativeclosure(self)->_noutervalues > nval){
			_nativeclosure(self)->_outervalues[nval] = stack_get(v,-1);
		}
		else return sq_throwerror(v,_SC("invalid free var index"));
		break;
	default:
		return sq_aux_invalidtype(v,type(self));
	}
	v->Pop();
	return SQ_OK;
}

SQRESULT sq_setattributes(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr *o = NULL;
	_GETSAFE_OBJ(v, idx, OT_CLASS,o);
	SQObjectPtr &key = stack_get(v,-2);
	SQObjectPtr &val = stack_get(v,-1);
	SQObjectPtr attrs;
	if(type(key) == OT_NULL) {
		attrs = _class(*o)->_attributes;
		_class(*o)->_attributes = val;
		v->Pop(2);
		v->Push(attrs);
		return SQ_OK;
	}else if(_class(*o)->GetAttributes(key,attrs)) {
		_class(*o)->SetAttributes(key,val);
		v->Pop(2);
		v->Push(attrs);
		return SQ_OK;
	}
	return sq_throwerror(v,_SC("wrong index"));
}

SQRESULT sq_getattributes(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr *o = NULL;
	_GETSAFE_OBJ(v, idx, OT_CLASS,o);
	SQObjectPtr &key = stack_get(v,-1);
	SQObjectPtr attrs;
	if(type(key) == OT_NULL) {
		attrs = _class(*o)->_attributes;
		v->Pop();
		v->Push(attrs); 
		return SQ_OK;
	}
	else if(_class(*o)->GetAttributes(key,attrs)) {
		v->Pop();
		v->Push(attrs);
		return SQ_OK;
	}
	return sq_throwerror(v,_SC("wrong index"));
}

SQRESULT sq_getmemberhandle(HSQUIRRELVM v,SQInteger idx,HSQMEMBERHANDLE *handle)
{
	SQObjectPtr *o = NULL;
	_GETSAFE_OBJ(v, idx, OT_CLASS,o);
	SQObjectPtr &key = stack_get(v,-1);
	SQTable *m = _class(*o)->_members;
	SQObjectPtr val;
	if(m->Get(key,val)) {
		handle->_static = _isfield(val) ? SQFalse : SQTrue;
		handle->_index = _member_idx(val);
		v->Pop();
		return SQ_OK;
	}
	return sq_throwerror(v,_SC("wrong index"));
}

SQRESULT _getmemberbyhandle(HSQUIRRELVM v,SQObjectPtr &self,const HSQMEMBERHANDLE *handle,SQObjectPtr *&val)
{
	switch(type(self)) {
		case OT_INSTANCE: {
				SQInstance *i = _instance(self);
				if(handle->_static) {
					SQClass *c = i->_class;
					val = &c->_methods[handle->_index].val;
				}
				else {
					val = &i->_values[handle->_index];
					
				}
			}
			break;
		case OT_CLASS: {
				SQClass *c = _class(self);
				if(handle->_static) {
					val = &c->_methods[handle->_index].val;
				}
				else {
					val = &c->_defaultvalues[handle->_index].val;
				}
			}
			break;
		default:
			return sq_throwerror(v,_SC("wrong type(expected class or instance)"));
	}
	return SQ_OK;
}

SQRESULT sq_getbyhandle(HSQUIRRELVM v,SQInteger idx,const HSQMEMBERHANDLE *handle)
{
	SQObjectPtr &self = stack_get(v,idx);
	SQObjectPtr *val = NULL;
	if(SQ_FAILED(_getmemberbyhandle(v,self,handle,val))) {
		return SQ_ERROR;
	}
	v->Push(_realval(*val));
	return SQ_OK;
}

SQRESULT sq_setbyhandle(HSQUIRRELVM v,SQInteger idx,const HSQMEMBERHANDLE *handle)
{
	SQObjectPtr &self = stack_get(v,idx);
	SQObjectPtr &newval = stack_get(v,-1);
	SQObjectPtr *val = NULL;
	if(SQ_FAILED(_getmemberbyhandle(v,self,handle,val))) {
		return SQ_ERROR;
	}
	*val = newval;
	v->Pop();
	return SQ_OK;
}

SQRESULT sq_getbase(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr *o = NULL;
	_GETSAFE_OBJ(v, idx, OT_CLASS,o);
	if(_class(*o)->_base)
		v->Push(SQObjectPtr(_class(*o)->_base));
	else
		v->PushNull();
	return SQ_OK;
}

SQRESULT sq_getclass(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr *o = NULL;
	_GETSAFE_OBJ(v, idx, OT_INSTANCE,o);
	v->Push(SQObjectPtr(_instance(*o)->_class));
	return SQ_OK;
}

SQRESULT sq_createinstance(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr *o = NULL;
	_GETSAFE_OBJ(v, idx, OT_CLASS,o);
	v->Push(_class(*o)->CreateInstance());
	return SQ_OK;
}

void sq_weakref(HSQUIRRELVM v,SQInteger idx)
{
	SQObject &o=stack_get(v,idx);
	if(ISREFCOUNTED(type(o))) {
		v->Push(_refcounted(o)->GetWeakRef(type(o)));
		return;
	}
	v->Push(o);
}

SQRESULT sq_getweakrefval(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr &o = stack_get(v,idx);
	if(type(o) != OT_WEAKREF) {
		return sq_throwerror(v,_SC("the object must be a weakref"));
	}
	v->Push(_weakref(o)->_obj);
	return SQ_OK;
}

SQRESULT sq_getdefaultdelegate(HSQUIRRELVM v,SQObjectType t)
{
	SQSharedState *ss = _ss(v);
	switch(t) {
	case OT_TABLE: v->Push(ss->_table_default_delegate); break;
	case OT_ARRAY: v->Push(ss->_array_default_delegate); break;
	case OT_STRING: v->Push(ss->_string_default_delegate); break;
	case OT_INTEGER: case OT_FLOAT: v->Push(ss->_number_default_delegate); break;
	case OT_GENERATOR: v->Push(ss->_generator_default_delegate); break;
	case OT_CLOSURE: case OT_NATIVECLOSURE: v->Push(ss->_closure_default_delegate); break;
	case OT_THREAD: v->Push(ss->_thread_default_delegate); break;
	case OT_CLASS: v->Push(ss->_class_default_delegate); break;
	case OT_INSTANCE: v->Push(ss->_instance_default_delegate); break;
	case OT_WEAKREF: v->Push(ss->_weakref_default_delegate); break;
	default: return sq_throwerror(v,_SC("the type doesn't have a default delegate"));
	}
	return SQ_OK;
}

SQRESULT sq_next(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr o=stack_get(v,idx),&refpos = stack_get(v,-1),realkey,val;
	if(type(o) == OT_GENERATOR) {
		return sq_throwerror(v,_SC("cannot iterate a generator"));
	}
	int faketojump;
	if(!v->FOREACH_OP(o,realkey,val,refpos,0,666,faketojump))
		return SQ_ERROR;
	if(faketojump != 666) {
		v->Push(realkey);
		v->Push(val);
		return SQ_OK;
	}
	return SQ_ERROR;
}

struct BufState{
	const SQChar *buf;
	SQInteger ptr;
	SQInteger size;
};

SQInteger buf_lexfeed(SQUserPointer file)
{
	BufState *buf=(BufState*)file;
	if(buf->size<(buf->ptr+1))
		return 0;
	return buf->buf[buf->ptr++];
}

SQRESULT sq_compilebuffer(HSQUIRRELVM v,const SQChar *s,SQInteger size,const SQChar *sourcename,SQBool raiseerror) {
	BufState buf;
	buf.buf = s;
	buf.size = size;
	buf.ptr = 0;
	return sq_compile(v, buf_lexfeed, &buf, sourcename, raiseerror);
}

void sq_move(HSQUIRRELVM dest,HSQUIRRELVM src,SQInteger idx)
{
	dest->Push(stack_get(src,idx));
}

void sq_setprintfunc(HSQUIRRELVM v, SQPRINTFUNCTION printfunc,SQPRINTFUNCTION errfunc)
{
	_ss(v)->_printfunc = printfunc;
	_ss(v)->_errorfunc = errfunc;
}

SQPRINTFUNCTION sq_getprintfunc(HSQUIRRELVM v)
{
	return _ss(v)->_printfunc;
}

SQPRINTFUNCTION sq_geterrorfunc(HSQUIRRELVM v)
{
	return _ss(v)->_errorfunc;
}

void *sq_malloc(SQUnsignedInteger size)
{
	return SQ_MALLOC(size);
}

void *sq_realloc(void* p,SQUnsignedInteger oldsize,SQUnsignedInteger newsize)
{
	return SQ_REALLOC(p,oldsize,newsize);
}

void sq_free(void *p,SQUnsignedInteger size)
{
	SQ_FREE(p,size);
}

// ******************************** sqbaselib.cpp ********************************
/*
	see copyright notice in squirrel.h
*/
// ---- #include "sqpcheader.h"
// ---> including sqpcheader.h
// <--- back to sqbaselib.cpp
// ---- #include "sqvm.h"
// ---> including sqvm.h
// <--- back to sqbaselib.cpp
// ---- #include "sqstring.h"
// ---> including sqstring.h
// <--- back to sqbaselib.cpp
// ---- #include "sqtable.h"
// ---> including sqtable.h
// <--- back to sqbaselib.cpp
// ---- #include "sqarray.h"
// ---> including sqarray.h
// <--- back to sqbaselib.cpp
// ---- #include "sqfuncproto.h"
// ---> including sqfuncproto.h
// <--- back to sqbaselib.cpp
// ---- #include "sqclosure.h"
// ---> including sqclosure.h
// <--- back to sqbaselib.cpp
// ---- #include "sqclass.h"
// ---> including sqclass.h
// <--- back to sqbaselib.cpp
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

bool str2num(const SQChar *s,SQObjectPtr &res)
{
	SQChar *end;
	const SQChar *e = s;
	SQBool isfloat = SQFalse;
	SQChar c;
	while((c = *e) != _SC('\0'))
	{
		if(c == _SC('.') || c == _SC('E')|| c == _SC('e')) { //e and E is for scientific notation
			isfloat = SQTrue;
			break;
		}
		e++;
	}
	if(isfloat){
		SQFloat r = SQFloat(scstrtod(s,&end));
		if(s == end) return false;
		res = r;
	}
	else{
		SQInteger r = SQInteger(scstrtol(s,&end,10));
		if(s == end) return false;
		res = r;
	}
	return true;
}

static SQInteger base_dummy(HSQUIRRELVM v)
{
	return 0;
}

#ifndef NO_GARBAGE_COLLECTOR
static SQInteger base_collectgarbage(HSQUIRRELVM v)
{
	sq_pushinteger(v, sq_collectgarbage(v));
	return 1;
}
static SQInteger base_resurectureachable(HSQUIRRELVM v)
{
	sq_resurrectunreachable(v);
	return 1;
}
#endif

static SQInteger base_getroottable(HSQUIRRELVM v)
{
	v->Push(v->_roottable);
	return 1;
}

static SQInteger base_getconsttable(HSQUIRRELVM v)
{
	v->Push(_ss(v)->_consts);
	return 1;
}


static SQInteger base_setroottable(HSQUIRRELVM v)
{
	SQObjectPtr o = v->_roottable;
	if(SQ_FAILED(sq_setroottable(v))) return SQ_ERROR;
	v->Push(o);
	return 1;
}

static SQInteger base_setconsttable(HSQUIRRELVM v)
{
	SQObjectPtr o = _ss(v)->_consts;
	if(SQ_FAILED(sq_setconsttable(v))) return SQ_ERROR;
	v->Push(o);
	return 1;
}

static SQInteger base_seterrorhandler(HSQUIRRELVM v)
{
	sq_seterrorhandler(v);
	return 0;
}

static SQInteger base_setdebughook(HSQUIRRELVM v)
{
	sq_setdebughook(v);
	return 0;
}

static SQInteger base_enabledebuginfo(HSQUIRRELVM v)
{
	SQObjectPtr &o=stack_get(v,2);
	
	sq_enabledebuginfo(v,SQVM::IsFalse(o)?SQFalse:SQTrue);
	return 0;
}

static SQInteger __getcallstackinfos(HSQUIRRELVM v,SQInteger level)
{
	SQStackInfos si;
	SQInteger seq = 0;
	const SQChar *name = NULL;
	
	if (SQ_SUCCEEDED(sq_stackinfos(v, level, &si)))
	{
		const SQChar *fn = _SC("unknown");
		const SQChar *src = _SC("unknown");
		if(si.funcname)fn = si.funcname;
		if(si.source)src = si.source;
		sq_newtable(v);
		sq_pushstring(v, _SC("func"), -1);
		sq_pushstring(v, fn, -1);
		sq_newslot(v, -3, SQFalse);
		sq_pushstring(v, _SC("src"), -1);
		sq_pushstring(v, src, -1);
		sq_newslot(v, -3, SQFalse);
		sq_pushstring(v, _SC("line"), -1);
		sq_pushinteger(v, si.line);
		sq_newslot(v, -3, SQFalse);
		sq_pushstring(v, _SC("locals"), -1);
		sq_newtable(v);
		seq=0;
		while ((name = sq_getlocal(v, level, seq))) {
			sq_pushstring(v, name, -1);
			sq_push(v, -2);
			sq_newslot(v, -4, SQFalse);
			sq_pop(v, 1);
			seq++;
		}
		sq_newslot(v, -3, SQFalse);
		return 1;
	}

	return 0;
}
static SQInteger base_getstackinfos(HSQUIRRELVM v)
{
	SQInteger level;
	sq_getinteger(v, -1, &level);
	return __getcallstackinfos(v,level);
}

static SQInteger base_assert(HSQUIRRELVM v)
{
	if(SQVM::IsFalse(stack_get(v,2))){
		return sq_throwerror(v,_SC("assertion failed"));
	}
	return 0;
}

static SQInteger get_slice_params(HSQUIRRELVM v,SQInteger &sidx,SQInteger &eidx,SQObjectPtr &o)
{
	SQInteger top = sq_gettop(v);
	sidx=0;
	eidx=0;
	o=stack_get(v,1);
	SQObjectPtr &start=stack_get(v,2);
	if(type(start)!=OT_NULL && sq_isnumeric(start)){
		sidx=tointeger(start);
	}
	if(top>2){
		SQObjectPtr &end=stack_get(v,3);
		if(sq_isnumeric(end)){
			eidx=tointeger(end);
		}
	}
	else {
		eidx = sq_getsize(v,1);
	}
	return 1;
}

static SQInteger base_print(HSQUIRRELVM v)
{
	const SQChar *str;
	sq_tostring(v,2);
	sq_getstring(v,-1,&str);
	if(_ss(v)->_printfunc) _ss(v)->_printfunc(v,_SC("%s"),str);
	return 0;
}

static SQInteger base_error(HSQUIRRELVM v)
{
	const SQChar *str;
	sq_tostring(v,2);
	sq_getstring(v,-1,&str);
	if(_ss(v)->_errorfunc) _ss(v)->_errorfunc(v,_SC("%s"),str);
	return 0;
}

static SQInteger base_compilestring(HSQUIRRELVM v)
{
	SQInteger nargs=sq_gettop(v);
	const SQChar *src=NULL,*name=_SC("unnamedbuffer");
	SQInteger size;
	sq_getstring(v,2,&src);
	size=sq_getsize(v,2);
	if(nargs>2){
		sq_getstring(v,3,&name);
	}
	if(SQ_SUCCEEDED(sq_compilebuffer(v,src,size,name,SQFalse)))
		return 1;
	else
		return SQ_ERROR;
}

static SQInteger base_newthread(HSQUIRRELVM v)
{
	SQObjectPtr &func = stack_get(v,2);
	SQInteger stksize = (_closure(func)->_function->_stacksize << 1) +2;
	HSQUIRRELVM newv = sq_newthread(v, (stksize < MIN_STACK_OVERHEAD + 2)? MIN_STACK_OVERHEAD + 2 : stksize);
	sq_move(newv,v,-2);
	return 1;
}

static SQInteger base_suspend(HSQUIRRELVM v)
{
	return sq_suspendvm(v);
}

static SQInteger base_array(HSQUIRRELVM v)
{
	SQArray *a;
	SQObject &size = stack_get(v,2);
	if(sq_gettop(v) > 2) {
		a = SQArray::Create(_ss(v),0);
		a->Resize(tointeger(size),stack_get(v,3));
	}
	else {
		a = SQArray::Create(_ss(v),tointeger(size));
	}
	v->Push(a);
	return 1;
}

static SQInteger base_type(HSQUIRRELVM v)
{
	SQObjectPtr &o = stack_get(v,2);
	v->Push(SQString::Create(_ss(v),GetTypeName(o),-1));
	return 1;
}

static SQInteger base_callee(HSQUIRRELVM v)
{
	if(v->_callsstacksize > 1)
	{
		v->Push(v->_callsstack[v->_callsstacksize - 2]._closure);
		return 1;
	}
	return sq_throwerror(v,_SC("no closure in the calls stack"));
}

static SQRegFunction base_funcs[]={
	//generic
	{_SC("seterrorhandler"),base_seterrorhandler,2, NULL},
	{_SC("setdebughook"),base_setdebughook,2, NULL},
	{_SC("enabledebuginfo"),base_enabledebuginfo,2, NULL},
	{_SC("getstackinfos"),base_getstackinfos,2, _SC(".n")},
	{_SC("getroottable"),base_getroottable,1, NULL},
	{_SC("setroottable"),base_setroottable,2, NULL},
	{_SC("getconsttable"),base_getconsttable,1, NULL},
	{_SC("setconsttable"),base_setconsttable,2, NULL},
	{_SC("assert"),base_assert,2, NULL},
	{_SC("print"),base_print,2, NULL},
	{_SC("error"),base_error,2, NULL},
	{_SC("compilestring"),base_compilestring,-2, _SC(".ss")},
	{_SC("newthread"),base_newthread,2, _SC(".c")},
	{_SC("suspend"),base_suspend,-1, NULL},
	{_SC("array"),base_array,-2, _SC(".n")},
	{_SC("type"),base_type,2, NULL},
	{_SC("callee"),base_callee,0,NULL},
	{_SC("dummy"),base_dummy,0,NULL},
#ifndef NO_GARBAGE_COLLECTOR
	{_SC("collectgarbage"),base_collectgarbage,0, NULL},
	{_SC("resurrectunreachable"),base_resurectureachable,0, NULL},
#endif
	{0,0}
};

void sq_base_register(HSQUIRRELVM v)
{
	SQInteger i=0;
	sq_pushroottable(v);
	while(base_funcs[i].name!=0) {
		sq_pushstring(v,base_funcs[i].name,-1);
		sq_newclosure(v,base_funcs[i].f,0);
		sq_setnativeclosurename(v,-1,base_funcs[i].name);
		sq_setparamscheck(v,base_funcs[i].nparamscheck,base_funcs[i].typemask);
		sq_newslot(v,-3, SQFalse);
		i++;
	}
	
	sq_pushstring(v,_SC("_versionnumber_"),-1);
	sq_pushinteger(v,SQUIRREL_VERSION_NUMBER);
	sq_newslot(v,-3, SQFalse);
	sq_pushstring(v,_SC("_version_"),-1);
	sq_pushstring(v,SQUIRREL_VERSION,-1);
	sq_newslot(v,-3, SQFalse);
	sq_pushstring(v,_SC("_charsize_"),-1);
	sq_pushinteger(v,sizeof(SQChar));
	sq_newslot(v,-3, SQFalse);
	sq_pushstring(v,_SC("_intsize_"),-1);
	sq_pushinteger(v,sizeof(SQInteger));
	sq_newslot(v,-3, SQFalse);
	sq_pushstring(v,_SC("_floatsize_"),-1);
	sq_pushinteger(v,sizeof(SQFloat));
	sq_newslot(v,-3, SQFalse);
	sq_pop(v,1);
}

static SQInteger default_delegate_len(HSQUIRRELVM v)
{
	v->Push(SQInteger(sq_getsize(v,1)));
	return 1;
}

static SQInteger default_delegate_tofloat(HSQUIRRELVM v)
{
	SQObjectPtr &o=stack_get(v,1);
	switch(type(o)){
	case OT_STRING:{
		SQObjectPtr res;
		if(str2num(_stringval(o),res)){
			v->Push(SQObjectPtr(tofloat(res)));
			break;
		}}
		return sq_throwerror(v, _SC("cannot convert the string"));
		break;
	case OT_INTEGER:case OT_FLOAT:
		v->Push(SQObjectPtr(tofloat(o)));
		break;
	case OT_BOOL:
		v->Push(SQObjectPtr((SQFloat)(_integer(o)?1:0)));
		break;
	default:
		v->PushNull();
		break;
	}
	return 1;
}

static SQInteger default_delegate_tointeger(HSQUIRRELVM v)
{
	SQObjectPtr &o=stack_get(v,1);
	switch(type(o)){
	case OT_STRING:{
		SQObjectPtr res;
		if(str2num(_stringval(o),res)){
			v->Push(SQObjectPtr(tointeger(res)));
			break;
		}}
		return sq_throwerror(v, _SC("cannot convert the string"));
		break;
	case OT_INTEGER:case OT_FLOAT:
		v->Push(SQObjectPtr(tointeger(o)));
		break;
	case OT_BOOL:
		v->Push(SQObjectPtr(_integer(o)?(SQInteger)1:(SQInteger)0));
		break;
	default:
		v->PushNull();
		break;
	}
	return 1;
}

static SQInteger default_delegate_tostring(HSQUIRRELVM v)
{
	sq_tostring(v,1);
	return 1;
}

static SQInteger obj_delegate_weakref(HSQUIRRELVM v)
{
	sq_weakref(v,1);
	return 1;
}

static SQInteger obj_clear(HSQUIRRELVM v)
{
	return sq_clear(v,-1);
}


static SQInteger number_delegate_tochar(HSQUIRRELVM v)
{
	SQObject &o=stack_get(v,1);
	SQChar c = (SQChar)tointeger(o);
	v->Push(SQString::Create(_ss(v),(const SQChar *)&c,1));
	return 1;
}



/////////////////////////////////////////////////////////////////
//TABLE DEFAULT DELEGATE

static SQInteger table_rawdelete(HSQUIRRELVM v)
{
	if(SQ_FAILED(sq_rawdeleteslot(v,1,SQTrue)))
		return SQ_ERROR;
	return 1;
}


static SQInteger container_rawexists(HSQUIRRELVM v)
{
	if(SQ_SUCCEEDED(sq_rawget(v,-2))) {
		sq_pushbool(v,SQTrue);
		return 1;
	}
	sq_pushbool(v,SQFalse);
	return 1;
}

static SQInteger container_rawset(HSQUIRRELVM v)
{
	return sq_rawset(v,-3);
}


static SQInteger container_rawget(HSQUIRRELVM v)
{
	return SQ_SUCCEEDED(sq_rawget(v,-2))?1:SQ_ERROR;
}

static SQInteger table_setdelegate(HSQUIRRELVM v)
{
	if(SQ_FAILED(sq_setdelegate(v,-2)))
		return SQ_ERROR;
	sq_push(v,-1); // -1 because sq_setdelegate pops 1
	return 1;
}

static SQInteger table_getdelegate(HSQUIRRELVM v)
{
	return SQ_SUCCEEDED(sq_getdelegate(v,-1))?1:SQ_ERROR;
}

SQRegFunction SQSharedState::_table_default_delegate_funcz[]={
	{_SC("len"),default_delegate_len,1, _SC("t")},
	{_SC("rawget"),container_rawget,2, _SC("t")},
	{_SC("rawset"),container_rawset,3, _SC("t")},
	{_SC("rawdelete"),table_rawdelete,2, _SC("t")},
	{_SC("rawin"),container_rawexists,2, _SC("t")},
	{_SC("weakref"),obj_delegate_weakref,1, NULL },
	{_SC("tostring"),default_delegate_tostring,1, _SC(".")},
	{_SC("clear"),obj_clear,1, _SC(".")},
	{_SC("setdelegate"),table_setdelegate,2, _SC(".t|o")},
	{_SC("getdelegate"),table_getdelegate,1, _SC(".")},
	{0,0}
};

//ARRAY DEFAULT DELEGATE///////////////////////////////////////

static SQInteger array_append(HSQUIRRELVM v)
{
	return sq_arrayappend(v,-2);
}

static SQInteger array_extend(HSQUIRRELVM v)
{
	_array(stack_get(v,1))->Extend(_array(stack_get(v,2)));
	return 0;
}

static SQInteger array_reverse(HSQUIRRELVM v)
{
	return sq_arrayreverse(v,-1);
}

static SQInteger array_pop(HSQUIRRELVM v)
{
	return SQ_SUCCEEDED(sq_arraypop(v,1,SQTrue))?1:SQ_ERROR;
}

static SQInteger array_top(HSQUIRRELVM v)
{
	SQObject &o=stack_get(v,1);
	if(_array(o)->Size()>0){
		v->Push(_array(o)->Top());
		return 1;
	}
	else return sq_throwerror(v,_SC("top() on a empty array"));
}

static SQInteger array_insert(HSQUIRRELVM v)
{
	SQObject &o=stack_get(v,1);
	SQObject &idx=stack_get(v,2);
	SQObject &val=stack_get(v,3);
	if(!_array(o)->Insert(tointeger(idx),val))
		return sq_throwerror(v,_SC("index out of range"));
	return 0;
}

static SQInteger array_remove(HSQUIRRELVM v)
{
	SQObject &o = stack_get(v, 1);
	SQObject &idx = stack_get(v, 2);
	if(!sq_isnumeric(idx)) return sq_throwerror(v, _SC("wrong type"));
	SQObjectPtr val;
	if(_array(o)->Get(tointeger(idx), val)) {
		_array(o)->Remove(tointeger(idx));
		v->Push(val);
		return 1;
	}
	return sq_throwerror(v, _SC("idx out of range"));
}

static SQInteger array_resize(HSQUIRRELVM v)
{
	SQObject &o = stack_get(v, 1);
	SQObject &nsize = stack_get(v, 2);
	SQObjectPtr fill;
	if(sq_isnumeric(nsize)) {
		if(sq_gettop(v) > 2)
			fill = stack_get(v, 3);
		_array(o)->Resize(tointeger(nsize),fill);
		return 0;
	}
	return sq_throwerror(v, _SC("size must be a number"));
}

static SQInteger __map_array(SQArray *dest,SQArray *src,HSQUIRRELVM v) {
	SQObjectPtr temp;
	SQInteger size = src->Size();
	for(SQInteger n = 0; n < size; n++) {
		src->Get(n,temp);
		v->Push(src);
		v->Push(temp);
		if(SQ_FAILED(sq_call(v,2,SQTrue,SQFalse))) {
			return SQ_ERROR;
		}
		dest->Set(n,v->GetUp(-1));
		v->Pop();
	}
	return 0;
}

static SQInteger array_map(HSQUIRRELVM v)
{
	SQObject &o = stack_get(v,1);
	SQInteger size = _array(o)->Size();
	SQObjectPtr ret = SQArray::Create(_ss(v),size);
	if(SQ_FAILED(__map_array(_array(ret),_array(o),v)))
		return SQ_ERROR;
	v->Push(ret);
	return 1;
}

static SQInteger array_apply(HSQUIRRELVM v)
{
	SQObject &o = stack_get(v,1);
	if(SQ_FAILED(__map_array(_array(o),_array(o),v)))
		return SQ_ERROR;
	return 0;
}

static SQInteger array_reduce(HSQUIRRELVM v)
{
	SQObject &o = stack_get(v,1);
	SQArray *a = _array(o);
	SQInteger size = a->Size();
	if(size == 0) {
		return 0;
	}
	SQObjectPtr res;
	a->Get(0,res);
	if(size > 1) {
		SQObjectPtr other;
		for(SQInteger n = 1; n < size; n++) {
			a->Get(n,other);
			v->Push(o);
			v->Push(res);
			v->Push(other);
			if(SQ_FAILED(sq_call(v,3,SQTrue,SQFalse))) {
				return SQ_ERROR;
			}
			res = v->GetUp(-1);
			v->Pop();
		}
	}
	v->Push(res);
	return 1;
}

static SQInteger array_filter(HSQUIRRELVM v)
{
	SQObject &o = stack_get(v,1);
	SQArray *a = _array(o);
	SQObjectPtr ret = SQArray::Create(_ss(v),0);
	SQInteger size = a->Size();
	SQObjectPtr val;
	for(SQInteger n = 0; n < size; n++) {
		a->Get(n,val);
		v->Push(o);
		v->Push(n);
		v->Push(val);
		if(SQ_FAILED(sq_call(v,3,SQTrue,SQFalse))) {
			return SQ_ERROR;
		}
		if(!SQVM::IsFalse(v->GetUp(-1))) {
			_array(ret)->Append(val);
		}
		v->Pop();
	}
	v->Push(ret);
	return 1;
}

static SQInteger array_find(HSQUIRRELVM v)
{
	SQObject &o = stack_get(v,1);
	SQObjectPtr &val = stack_get(v,2);
	SQArray *a = _array(o);
	SQInteger size = a->Size();
	SQObjectPtr temp;
	for(SQInteger n = 0; n < size; n++) {
		bool res = false;
		a->Get(n,temp);
		if(SQVM::IsEqual(temp,val,res) && res) {
			v->Push(n);
			return 1;
		}
	}
	return 0;
}


bool _sort_compare(HSQUIRRELVM v,SQObjectPtr &a,SQObjectPtr &b,SQInteger func,SQInteger &ret)
{
	if(func < 0) {
		if(!v->ObjCmp(a,b,ret)) return false;
	}
	else {
		SQInteger top = sq_gettop(v);
		sq_push(v, func);
		sq_pushroottable(v);
		v->Push(a);
		v->Push(b);
		if(SQ_FAILED(sq_call(v, 3, SQTrue, SQFalse))) {
			if(!sq_isstring( v->_lasterror)) 
				v->Raise_Error(_SC("compare func failed"));
			return false;
		}
		if(SQ_FAILED(sq_getinteger(v, -1, &ret))) {
			v->Raise_Error(_SC("numeric value expected as return value of the compare function"));
			return false;
		}
		sq_settop(v, top);
		return true;
	}
	return true;
}

bool _hsort_sift_down(HSQUIRRELVM v,SQArray *arr, SQInteger root, SQInteger bottom, SQInteger func)
{
	SQInteger maxChild;
	SQInteger done = 0;
	SQInteger ret;
	SQInteger root2;
	while (((root2 = root * 2) <= bottom) && (!done))
	{
		if (root2 == bottom) {
			maxChild = root2;
		}
		else {
			if(!_sort_compare(v,arr->_values[root2],arr->_values[root2 + 1],func,ret))
				return false;
			if (ret > 0) {
				maxChild = root2;
			}
			else {
				maxChild = root2 + 1;
			}
		}

		if(!_sort_compare(v,arr->_values[root],arr->_values[maxChild],func,ret))
			return false;
		if (ret < 0) {
			if (root == maxChild) {
                v->Raise_Error(_SC("inconsistent compare function"));
                return false; // We'd be swapping ourselve. The compare function is incorrect
            }

			_Swap(arr->_values[root],arr->_values[maxChild]);
			root = maxChild;
		}
		else {
			done = 1;
		}
	}
	return true;
}

bool _hsort(HSQUIRRELVM v,SQObjectPtr &arr, SQInteger l, SQInteger r,SQInteger func)
{
	SQArray *a = _array(arr);
	SQInteger i;
	SQInteger array_size = a->Size();
	for (i = (array_size / 2); i >= 0; i--) {
		if(!_hsort_sift_down(v,a, i, array_size - 1,func)) return false;
	}

	for (i = array_size-1; i >= 1; i--)
	{
		_Swap(a->_values[0],a->_values[i]);
		if(!_hsort_sift_down(v,a, 0, i-1,func)) return false;
	}
	return true;
}

static SQInteger array_sort(HSQUIRRELVM v)
{
	SQInteger func = -1;
	SQObjectPtr &o = stack_get(v,1);
	if(_array(o)->Size() > 1) {
		if(sq_gettop(v) == 2) func = 2;
		if(!_hsort(v, o, 0, _array(o)->Size()-1, func))
			return SQ_ERROR;

	}
	return 0;
}

static SQInteger array_slice(HSQUIRRELVM v)
{
	SQInteger sidx,eidx;
	SQObjectPtr o;
	if(get_slice_params(v,sidx,eidx,o)==-1)return -1;
	SQInteger alen = _array(o)->Size();
	if(sidx < 0)sidx = alen + sidx;
	if(eidx < 0)eidx = alen + eidx;
	if(eidx < sidx)return sq_throwerror(v,_SC("wrong indexes"));
	if(eidx > alen)return sq_throwerror(v,_SC("slice out of range"));
	SQArray *arr=SQArray::Create(_ss(v),eidx-sidx);
	SQObjectPtr t;
	SQInteger count=0;
	for(SQInteger i=sidx;i<eidx;i++){
		_array(o)->Get(i,t);
		arr->Set(count++,t);
	}
	v->Push(arr);
	return 1;
	
}

SQRegFunction SQSharedState::_array_default_delegate_funcz[]={
	{_SC("len"),default_delegate_len,1, _SC("a")},
	{_SC("append"),array_append,2, _SC("a")},
	{_SC("extend"),array_extend,2, _SC("aa")},
	{_SC("push"),array_append,2, _SC("a")},
	{_SC("pop"),array_pop,1, _SC("a")},
	{_SC("top"),array_top,1, _SC("a")},
	{_SC("insert"),array_insert,3, _SC("an")},
	{_SC("remove"),array_remove,2, _SC("an")},
	{_SC("resize"),array_resize,-2, _SC("an")},
	{_SC("reverse"),array_reverse,1, _SC("a")},
	{_SC("sort"),array_sort,-1, _SC("ac")},
	{_SC("slice"),array_slice,-1, _SC("ann")},
	{_SC("weakref"),obj_delegate_weakref,1, NULL },
	{_SC("tostring"),default_delegate_tostring,1, _SC(".")},
	{_SC("clear"),obj_clear,1, _SC(".")},
	{_SC("map"),array_map,2, _SC("ac")}, 
	{_SC("apply"),array_apply,2, _SC("ac")}, 
	{_SC("reduce"),array_reduce,2, _SC("ac")}, 
	{_SC("filter"),array_filter,2, _SC("ac")},
	{_SC("find"),array_find,2, _SC("a.")},
	{0,0}
};

//STRING DEFAULT DELEGATE//////////////////////////
static SQInteger string_slice(HSQUIRRELVM v)
{
	SQInteger sidx,eidx;
	SQObjectPtr o;
	if(SQ_FAILED(get_slice_params(v,sidx,eidx,o)))return -1;
	SQInteger slen = _string(o)->_len;
	if(sidx < 0)sidx = slen + sidx;
	if(eidx < 0)eidx = slen + eidx;
	if(eidx < sidx)	return sq_throwerror(v,_SC("wrong indexes"));
	if(eidx > slen)	return sq_throwerror(v,_SC("slice out of range"));
	v->Push(SQString::Create(_ss(v),&_stringval(o)[sidx],eidx-sidx));
	return 1;
}

static SQInteger string_find(HSQUIRRELVM v)
{
	SQInteger top,start_idx=0;
	const SQChar *str,*substr,*ret;
	if(((top=sq_gettop(v))>1) && SQ_SUCCEEDED(sq_getstring(v,1,&str)) && SQ_SUCCEEDED(sq_getstring(v,2,&substr))){
		if(top>2)sq_getinteger(v,3,&start_idx);
		if((sq_getsize(v,1)>start_idx) && (start_idx>=0)){
			ret=scstrstr(&str[start_idx],substr);
			if(ret){
				sq_pushinteger(v,(SQInteger)(ret-str));
				return 1;
			}
		}
		return 0;
	}
	return sq_throwerror(v,_SC("invalid param"));
}

#define STRING_TOFUNCZ(func) static SQInteger string_##func(HSQUIRRELVM v) \
{ \
	SQObject str=stack_get(v,1); \
	SQInteger len=_string(str)->_len; \
	const SQChar *sThis=_stringval(str); \
	SQChar *sNew=(_ss(v)->GetScratchPad(rsl(len))); \
	for(SQInteger i=0;i<len;i++) sNew[i]=func(sThis[i]); \
	v->Push(SQString::Create(_ss(v),sNew,len)); \
	return 1; \
}


STRING_TOFUNCZ(tolower)
STRING_TOFUNCZ(toupper)

SQRegFunction SQSharedState::_string_default_delegate_funcz[]={
	{_SC("len"),default_delegate_len,1, _SC("s")},
	{_SC("tointeger"),default_delegate_tointeger,1, _SC("s")},
	{_SC("tofloat"),default_delegate_tofloat,1, _SC("s")},
	{_SC("tostring"),default_delegate_tostring,1, _SC(".")},
	{_SC("slice"),string_slice,-1, _SC(" s n  n")},
	{_SC("find"),string_find,-2, _SC("s s n ")},
	{_SC("tolower"),string_tolower,1, _SC("s")},
	{_SC("toupper"),string_toupper,1, _SC("s")},
	{_SC("weakref"),obj_delegate_weakref,1, NULL },
	{0,0}
};

//INTEGER DEFAULT DELEGATE//////////////////////////
SQRegFunction SQSharedState::_number_default_delegate_funcz[]={
	{_SC("tointeger"),default_delegate_tointeger,1, _SC("n|b")},
	{_SC("tofloat"),default_delegate_tofloat,1, _SC("n|b")},
	{_SC("tostring"),default_delegate_tostring,1, _SC(".")},
	{_SC("tochar"),number_delegate_tochar,1, _SC("n|b")},
	{_SC("weakref"),obj_delegate_weakref,1, NULL },
	{0,0}
};

//CLOSURE DEFAULT DELEGATE//////////////////////////
static SQInteger closure_pcall(HSQUIRRELVM v)
{
	return SQ_SUCCEEDED(sq_call(v,sq_gettop(v)-1,SQTrue,SQFalse))?1:SQ_ERROR;
}

static SQInteger closure_call(HSQUIRRELVM v)
{
	return SQ_SUCCEEDED(sq_call(v,sq_gettop(v)-1,SQTrue,SQTrue))?1:SQ_ERROR;
}

static SQInteger _closure_acall(HSQUIRRELVM v,SQBool raiseerror)
{
	SQArray *aparams=_array(stack_get(v,2));
	SQInteger nparams=aparams->Size();
	v->Push(stack_get(v,1));
	for(SQInteger i=0;i<nparams;i++)v->Push(aparams->_values[i]);
	return SQ_SUCCEEDED(sq_call(v,nparams,SQTrue,raiseerror))?1:SQ_ERROR;
}

static SQInteger closure_acall(HSQUIRRELVM v)
{
	return _closure_acall(v,SQTrue);
}

static SQInteger closure_pacall(HSQUIRRELVM v)
{
	return _closure_acall(v,SQFalse);
}

static SQInteger closure_bindenv(HSQUIRRELVM v)
{
	if(SQ_FAILED(sq_bindenv(v,1)))
		return SQ_ERROR;
	return 1;
}

static SQInteger closure_getinfos(HSQUIRRELVM v) {
	SQObject o = stack_get(v,1);
	SQTable *res = SQTable::Create(_ss(v),4);
	if(type(o) == OT_CLOSURE) {
		SQFunctionProto *f = _closure(o)->_function;
		SQInteger nparams = f->_nparameters + (f->_varparams?1:0);
		SQObjectPtr params = SQArray::Create(_ss(v),nparams);
    SQObjectPtr defparams = SQArray::Create(_ss(v),f->_ndefaultparams);
		for(SQInteger n = 0; n<f->_nparameters; n++) {
			_array(params)->Set((SQInteger)n,f->_parameters[n]);
		}
    for(SQInteger j = 0; j<f->_ndefaultparams; j++) {
			_array(defparams)->Set((SQInteger)j,_closure(o)->_defaultparams[j]);
		}
		if(f->_varparams) {
			_array(params)->Set(nparams-1,SQString::Create(_ss(v),_SC("..."),-1));
		}
		res->NewSlot(SQString::Create(_ss(v),_SC("native"),-1),false);
		res->NewSlot(SQString::Create(_ss(v),_SC("name"),-1),f->_name);
		res->NewSlot(SQString::Create(_ss(v),_SC("src"),-1),f->_sourcename);
		res->NewSlot(SQString::Create(_ss(v),_SC("parameters"),-1),params);
		res->NewSlot(SQString::Create(_ss(v),_SC("varargs"),-1),f->_varparams);
    res->NewSlot(SQString::Create(_ss(v),_SC("defparams"),-1),defparams);
	}
	else { //OT_NATIVECLOSURE 
		SQNativeClosure *nc = _nativeclosure(o);
		res->NewSlot(SQString::Create(_ss(v),_SC("native"),-1),true);
		res->NewSlot(SQString::Create(_ss(v),_SC("name"),-1),nc->_name);
		res->NewSlot(SQString::Create(_ss(v),_SC("paramscheck"),-1),nc->_nparamscheck);
		SQObjectPtr typecheck;
		if(nc->_typecheck.size() > 0) {
			typecheck =
				SQArray::Create(_ss(v), nc->_typecheck.size());
			for(SQUnsignedInteger n = 0; n<nc->_typecheck.size(); n++) {
					_array(typecheck)->Set((SQInteger)n,nc->_typecheck[n]);
			}
		}
		res->NewSlot(SQString::Create(_ss(v),_SC("typecheck"),-1),typecheck);
	}
	v->Push(res);
	return 1;
}



SQRegFunction SQSharedState::_closure_default_delegate_funcz[]={
	{_SC("call"),closure_call,-1, _SC("c")},
	{_SC("pcall"),closure_pcall,-1, _SC("c")},
	{_SC("acall"),closure_acall,2, _SC("ca")},
	{_SC("pacall"),closure_pacall,2, _SC("ca")},
	{_SC("weakref"),obj_delegate_weakref,1, NULL },
	{_SC("tostring"),default_delegate_tostring,1, _SC(".")},
	{_SC("bindenv"),closure_bindenv,2, _SC("c x|y|t")},
	{_SC("getinfos"),closure_getinfos,1, _SC("c")},
	{0,0}
};

//GENERATOR DEFAULT DELEGATE
static SQInteger generator_getstatus(HSQUIRRELVM v)
{
	SQObject &o=stack_get(v,1);
	switch(_generator(o)->_state){
		case SQGenerator::eSuspended:v->Push(SQString::Create(_ss(v),_SC("suspended")));break;
		case SQGenerator::eRunning:v->Push(SQString::Create(_ss(v),_SC("running")));break;
		case SQGenerator::eDead:v->Push(SQString::Create(_ss(v),_SC("dead")));break;
	}
	return 1;
}

SQRegFunction SQSharedState::_generator_default_delegate_funcz[]={
	{_SC("getstatus"),generator_getstatus,1, _SC("g")},
	{_SC("weakref"),obj_delegate_weakref,1, NULL },
	{_SC("tostring"),default_delegate_tostring,1, _SC(".")},
	{0,0}
};

//THREAD DEFAULT DELEGATE
static SQInteger thread_call(HSQUIRRELVM v)
{
	SQObjectPtr o = stack_get(v,1);
	if(type(o) == OT_THREAD) {
		SQInteger nparams = sq_gettop(v);
		_thread(o)->Push(_thread(o)->_roottable);
		for(SQInteger i = 2; i<(nparams+1); i++)
			sq_move(_thread(o),v,i);
		if(SQ_SUCCEEDED(sq_call(_thread(o),nparams,SQTrue,SQFalse))) {
			sq_move(v,_thread(o),-1);
			sq_pop(_thread(o),1);
			return 1;
		}
		v->_lasterror = _thread(o)->_lasterror;
		return SQ_ERROR;
	}
	return sq_throwerror(v,_SC("wrong parameter"));
}

static SQInteger thread_wakeup(HSQUIRRELVM v)
{
	SQObjectPtr o = stack_get(v,1);
	if(type(o) == OT_THREAD) {
		SQVM *thread = _thread(o);
		SQInteger state = sq_getvmstate(thread);
		if(state != SQ_VMSTATE_SUSPENDED) {
			switch(state) {
				case SQ_VMSTATE_IDLE:
					return sq_throwerror(v,_SC("cannot wakeup a idle thread"));
				break;
				case SQ_VMSTATE_RUNNING:
					return sq_throwerror(v,_SC("cannot wakeup a running thread"));
				break;
			}
		}
			
		SQInteger wakeupret = sq_gettop(v)>1?1:0;
		if(wakeupret) {
			sq_move(thread,v,2);
		}
		if(SQ_SUCCEEDED(sq_wakeupvm(thread,wakeupret,SQTrue,SQTrue,SQFalse))) {
			sq_move(v,thread,-1);
			sq_pop(thread,1); //pop retval
			if(sq_getvmstate(thread) == SQ_VMSTATE_IDLE) {
				sq_settop(thread,1); //pop roottable
			}
			return 1;
		}
		sq_settop(thread,1);
		v->_lasterror = thread->_lasterror;
		return SQ_ERROR;
	}
	return sq_throwerror(v,_SC("wrong parameter"));
}

static SQInteger thread_getstatus(HSQUIRRELVM v)
{
	SQObjectPtr &o = stack_get(v,1);
	switch(sq_getvmstate(_thread(o))) {
		case SQ_VMSTATE_IDLE:
			sq_pushstring(v,_SC("idle"),-1);
		break;
		case SQ_VMSTATE_RUNNING:
			sq_pushstring(v,_SC("running"),-1);
		break;
		case SQ_VMSTATE_SUSPENDED:
			sq_pushstring(v,_SC("suspended"),-1);
		break;
		default:
			return sq_throwerror(v,_SC("internal VM error"));
	}
	return 1;
}

static SQInteger thread_getstackinfos(HSQUIRRELVM v)
{
	SQObjectPtr o = stack_get(v,1);
	if(type(o) == OT_THREAD) {
		SQVM *thread = _thread(o);
		SQInteger threadtop = sq_gettop(thread);
		SQInteger level;
		sq_getinteger(v,-1,&level);
		SQRESULT res = __getcallstackinfos(thread,level);
		if(SQ_FAILED(res))
		{
			sq_settop(thread,threadtop);
			if(type(thread->_lasterror) == OT_STRING) {
				sq_throwerror(v,_stringval(thread->_lasterror));
			}
			else {
				sq_throwerror(v,_SC("unknown error"));
			}
		}
		if(res > 0) {
			//some result
			sq_move(v,thread,-1);
			sq_settop(thread,threadtop);
			return 1;
		}
		//no result
		sq_settop(thread,threadtop);
		return 0;
		
	}
	return sq_throwerror(v,_SC("wrong parameter"));
}

SQRegFunction SQSharedState::_thread_default_delegate_funcz[] = {
	{_SC("call"), thread_call, -1, _SC("v")},
	{_SC("wakeup"), thread_wakeup, -1, _SC("v")},
	{_SC("getstatus"), thread_getstatus, 1, _SC("v")},
	{_SC("weakref"),obj_delegate_weakref,1, NULL },
	{_SC("getstackinfos"),thread_getstackinfos,2, _SC("vn")},
	{_SC("tostring"),default_delegate_tostring,1, _SC(".")},
	{0,0},
};

static SQInteger class_getattributes(HSQUIRRELVM v)
{
	return SQ_SUCCEEDED(sq_getattributes(v,-2))?1:SQ_ERROR;
}

static SQInteger class_setattributes(HSQUIRRELVM v)
{
	return SQ_SUCCEEDED(sq_setattributes(v,-3))?1:SQ_ERROR;
}

static SQInteger class_instance(HSQUIRRELVM v)
{
	return SQ_SUCCEEDED(sq_createinstance(v,-1))?1:SQ_ERROR;
}

static SQInteger class_getbase(HSQUIRRELVM v)
{
	return SQ_SUCCEEDED(sq_getbase(v,-1))?1:SQ_ERROR;
}

static SQInteger class_newmember(HSQUIRRELVM v)
{
	SQInteger top = sq_gettop(v);
	SQBool bstatic = SQFalse;
	if(top == 5)
	{
		sq_tobool(v,-1,&bstatic);
		sq_pop(v,1);
	}

	if(top < 4) {
		sq_pushnull(v);
	}
	return SQ_SUCCEEDED(sq_newmember(v,-4,bstatic))?1:SQ_ERROR;
}

static SQInteger class_rawnewmember(HSQUIRRELVM v)
{
	SQInteger top = sq_gettop(v);
	SQBool bstatic = SQFalse;
	if(top == 5)
	{
		sq_tobool(v,-1,&bstatic);
		sq_pop(v,1);
	}

	if(top < 4) {
		sq_pushnull(v);
	}
	return SQ_SUCCEEDED(sq_rawnewmember(v,-4,bstatic))?1:SQ_ERROR;
}

SQRegFunction SQSharedState::_class_default_delegate_funcz[] = {
	{_SC("getattributes"), class_getattributes, 2, _SC("y.")},
	{_SC("setattributes"), class_setattributes, 3, _SC("y..")},
	{_SC("rawget"),container_rawget,2, _SC("y")},
	{_SC("rawset"),container_rawset,3, _SC("y")},
	{_SC("rawin"),container_rawexists,2, _SC("y")},
	{_SC("weakref"),obj_delegate_weakref,1, NULL },
	{_SC("tostring"),default_delegate_tostring,1, _SC(".")},
	{_SC("instance"),class_instance,1, _SC("y")},
	{_SC("getbase"),class_getbase,1, _SC("y")},
	{_SC("newmember"),class_newmember,-3, _SC("y")},
	{_SC("rawnewmember"),class_rawnewmember,-3, _SC("y")},
	{0,0}
};


static SQInteger instance_getclass(HSQUIRRELVM v)
{
	if(SQ_SUCCEEDED(sq_getclass(v,1)))
		return 1;
	return SQ_ERROR;
}

SQRegFunction SQSharedState::_instance_default_delegate_funcz[] = {
	{_SC("getclass"), instance_getclass, 1, _SC("x")},
	{_SC("rawget"),container_rawget,2, _SC("x")},
	{_SC("rawset"),container_rawset,3, _SC("x")},
	{_SC("rawin"),container_rawexists,2, _SC("x")},
	{_SC("weakref"),obj_delegate_weakref,1, NULL },
	{_SC("tostring"),default_delegate_tostring,1, _SC(".")},
	{0,0}
};

static SQInteger weakref_ref(HSQUIRRELVM v)
{
	if(SQ_FAILED(sq_getweakrefval(v,1)))
		return SQ_ERROR;
	return 1;
}

SQRegFunction SQSharedState::_weakref_default_delegate_funcz[] = {
	{_SC("ref"),weakref_ref,1, _SC("r")},
	{_SC("weakref"),obj_delegate_weakref,1, NULL },
	{_SC("tostring"),default_delegate_tostring,1, _SC(".")},
	{0,0}
};


// ******************************** sqclass.cpp ********************************
/*
	see copyright notice in squirrel.h
*/
// ---- #include "sqpcheader.h"
// ---> including sqpcheader.h
// <--- back to sqclass.cpp
// ---- #include "sqvm.h"
// ---> including sqvm.h
// <--- back to sqclass.cpp
// ---- #include "sqtable.h"
// ---> including sqtable.h
// <--- back to sqclass.cpp
// ---- #include "sqclass.h"
// ---> including sqclass.h
// <--- back to sqclass.cpp
// ---- #include "sqfuncproto.h"
// ---> including sqfuncproto.h
// <--- back to sqclass.cpp
// ---- #include "sqclosure.h"
// ---> including sqclosure.h
// <--- back to sqclass.cpp



SQClass::SQClass(SQSharedState *ss,SQClass *base)
{
	_base = base;
	_typetag = 0;
	_hook = NULL;
	_udsize = 0;
	_locked = false;
	_constructoridx = -1;
	if(_base) {
		_constructoridx = _base->_constructoridx;
		_udsize = _base->_udsize;
		_defaultvalues.copy(base->_defaultvalues);
		_methods.copy(base->_methods);
		_COPY_VECTOR(_metamethods,base->_metamethods,MT_LAST);
		__ObjAddRef(_base);
	}
	_members = base?base->_members->Clone() : SQTable::Create(ss,0);
	__ObjAddRef(_members);
	
	INIT_CHAIN();
	ADD_TO_CHAIN(&_sharedstate->_gc_chain, this);
}

void SQClass::Finalize() { 
	_attributes.Null();
	_defaultvalues.resize(0);
	_methods.resize(0);
	_NULL_SQOBJECT_VECTOR(_metamethods,MT_LAST);
	__ObjRelease(_members);
	if(_base) {
		__ObjRelease(_base);
	}
}

SQClass::~SQClass()
{
	REMOVE_FROM_CHAIN(&_sharedstate->_gc_chain, this);
	Finalize();
}

bool SQClass::NewSlot(SQSharedState *ss,const SQObjectPtr &key,const SQObjectPtr &val,bool bstatic)
{
	SQObjectPtr temp;
	bool belongs_to_static_table = type(val) == OT_CLOSURE || type(val) == OT_NATIVECLOSURE || bstatic;
	if(_locked && !belongs_to_static_table) 
		return false; //the class already has an instance so cannot be modified
	if(_members->Get(key,temp) && _isfield(temp)) //overrides the default value
	{
		_defaultvalues[_member_idx(temp)].val = val;
		return true;
	}
	if(belongs_to_static_table) {
		SQInteger mmidx;
		if((type(val) == OT_CLOSURE || type(val) == OT_NATIVECLOSURE) && 
			(mmidx = ss->GetMetaMethodIdxByName(key)) != -1) {
			_metamethods[mmidx] = val;
		} 
		else {
			SQObjectPtr theval = val;
			if(_base && type(val) == OT_CLOSURE) {
				theval = _closure(val)->Clone();
				_closure(theval)->_base = _base;
				__ObjAddRef(_base); //ref for the closure
			}
			if(type(temp) == OT_NULL) {
				bool isconstructor;
				SQVM::IsEqual(ss->_constructoridx, key, isconstructor);
				if(isconstructor) {
					_constructoridx = (SQInteger)_methods.size();
				}
				SQClassMember m;
				m.val = theval;
				_members->NewSlot(key,SQObjectPtr(_make_method_idx(_methods.size())));
				_methods.push_back(m);
			}
			else {
				_methods[_member_idx(temp)].val = theval;
			}
		}
		return true;
	}
	SQClassMember m;
	m.val = val;
	_members->NewSlot(key,SQObjectPtr(_make_field_idx(_defaultvalues.size())));
	_defaultvalues.push_back(m);
	return true;
}

SQInstance *SQClass::CreateInstance()
{
	if(!_locked) Lock();
	return SQInstance::Create(_opt_ss(this),this);
}

SQInteger SQClass::Next(const SQObjectPtr &refpos, SQObjectPtr &outkey, SQObjectPtr &outval)
{
	SQObjectPtr oval;
	SQInteger idx = _members->Next(false,refpos,outkey,oval);
	if(idx != -1) {
		if(_ismethod(oval)) {
			outval = _methods[_member_idx(oval)].val;
		}
		else {
			SQObjectPtr &o = _defaultvalues[_member_idx(oval)].val;
			outval = _realval(o);
		}
	}
	return idx;
}

bool SQClass::SetAttributes(const SQObjectPtr &key,const SQObjectPtr &val)
{
	SQObjectPtr idx;
	if(_members->Get(key,idx)) {
		if(_isfield(idx))
			_defaultvalues[_member_idx(idx)].attrs = val;
		else
			_methods[_member_idx(idx)].attrs = val;
		return true;
	}
	return false;
}

bool SQClass::GetAttributes(const SQObjectPtr &key,SQObjectPtr &outval)
{
	SQObjectPtr idx;
	if(_members->Get(key,idx)) {
		outval = (_isfield(idx)?_defaultvalues[_member_idx(idx)].attrs:_methods[_member_idx(idx)].attrs);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////
void SQInstance::Init(SQSharedState *ss)
{
	_userpointer = NULL;
	_hook = NULL;
	__ObjAddRef(_class);
	_delegate = _class->_members;
	INIT_CHAIN();
	ADD_TO_CHAIN(&_sharedstate->_gc_chain, this);
}

SQInstance::SQInstance(SQSharedState *ss, SQClass *c, SQInteger memsize)
{
	_memsize = memsize;
	_class = c;
	SQUnsignedInteger nvalues = _class->_defaultvalues.size();
	for(SQUnsignedInteger n = 0; n < nvalues; n++) {
		new (&_values[n]) SQObjectPtr(_class->_defaultvalues[n].val);
	}
	Init(ss);
}

SQInstance::SQInstance(SQSharedState *ss, SQInstance *i, SQInteger memsize)
{
	_memsize = memsize;
	_class = i->_class;
	SQUnsignedInteger nvalues = _class->_defaultvalues.size();
	for(SQUnsignedInteger n = 0; n < nvalues; n++) {
		new (&_values[n]) SQObjectPtr(i->_values[n]);
	}
	Init(ss);
}

void SQInstance::Finalize() 
{
	SQUnsignedInteger nvalues = _class->_defaultvalues.size();
	__ObjRelease(_class);
	_NULL_SQOBJECT_VECTOR(_values,nvalues);
	//for(SQUnsignedInteger i = 0; i < nvalues; i++) {
//		_values[i].Null();
//	}
}

SQInstance::~SQInstance()
{
	REMOVE_FROM_CHAIN(&_sharedstate->_gc_chain, this);
	if(_class){ Finalize(); } //if _class is null it was already finalized by the GC
}

bool SQInstance::GetMetaMethod(SQVM *v,SQMetaMethod mm,SQObjectPtr &res)
{
	if(type(_class->_metamethods[mm]) != OT_NULL) {
		res = _class->_metamethods[mm];
		return true;
	}
	return false;
}

bool SQInstance::InstanceOf(SQClass *trg)
{
	SQClass *parent = _class;
	while(parent != NULL) {
		if(parent == trg)
			return true;
		parent = parent->_base;
	}
	return false;
}

// ******************************** sqcompiler.cpp ********************************
/*
	see copyright notice in squirrel.h
*/
// ---- #include "sqpcheader.h"
// ---> including sqpcheader.h
// <--- back to sqcompiler.cpp
#ifndef NO_COMPILER
#include <stdarg.h>
#include <setjmp.h>
// ---- #include "sqopcodes.h"
// ---> including sqopcodes.h
// <--- back to sqcompiler.cpp
// ---- #include "sqstring.h"
// ---> including sqstring.h
// <--- back to sqcompiler.cpp
// ---- #include "sqfuncproto.h"
// ---> including sqfuncproto.h
// <--- back to sqcompiler.cpp
// ---- #include "sqcompiler.h"
// ---> including sqcompiler.h
// <--- back to sqcompiler.cpp
// ---- #include "sqfuncstate.h"
// ---> including sqfuncstate.h
// <--- back to sqcompiler.cpp
// ---- #include "sqlexer.h"
// ---> including sqlexer.h
/*	see copyright notice in squirrel.h */
#ifndef _SQLEXER_H_
#define _SQLEXER_H_

#ifdef SQUNICODE
typedef SQChar LexChar;
#else
typedef	unsigned char LexChar;
#endif

struct SQLexer
{
	SQLexer();
	~SQLexer();
	void Init(SQSharedState *ss,SQLEXREADFUNC rg,SQUserPointer up,CompilerErrorFunc efunc,void *ed);
	void Error(const SQChar *err);
	SQInteger Lex();
	const SQChar *Tok2Str(SQInteger tok);
private:
	SQInteger GetIDType(SQChar *s);
	SQInteger ReadString(SQInteger ndelim,bool verbatim);
	SQInteger ReadNumber();
	void LexBlockComment();
	void LexLineComment();
	SQInteger ReadID();
	void Next();
	SQInteger _curtoken;
	SQTable *_keywords;
	SQBool _reached_eof;
public:
	SQInteger _prevtoken;
	SQInteger _currentline;
	SQInteger _lasttokenline;
	SQInteger _currentcolumn;
	const SQChar *_svalue;
	SQInteger _nvalue;
	SQFloat _fvalue;
	SQLEXREADFUNC _readf;
	SQUserPointer _up;
	LexChar _currdata;
	SQSharedState *_sharedstate;
	sqvector<SQChar> _longstr;
	CompilerErrorFunc _errfunc;
	void *_errtarget;
};

#endif

// <--- back to sqcompiler.cpp
// ---- #include "sqvm.h"
// ---> including sqvm.h
// <--- back to sqcompiler.cpp
// ---- #include "sqtable.h"
// ---> including sqtable.h
// <--- back to sqcompiler.cpp

#define EXPR   1
#define OBJECT 2
#define BASE   3
#define LOCAL  4
#define OUTER  5

struct SQExpState {
  SQInteger  etype;       /* expr. type; one of EXPR, OBJECT, BASE, OUTER or LOCAL */
  SQInteger  epos;        /* expr. location on stack; -1 for OBJECT and BASE */
  bool       donot_get;   /* signal not to deref the next value */
};

struct SQScope {
	SQInteger outers;
	SQInteger stacksize;
};

#define BEGIN_SCOPE() SQScope __oldscope__ = _scope; \
					 _scope.outers = _fs->_outers; \
					 _scope.stacksize = _fs->GetStackSize();

#define RESOLVE_OUTERS() if(_fs->GetStackSize() != _scope.stacksize) { \
							if(_fs->CountOuters(_scope.stacksize)) { \
								_fs->AddInstruction(_OP_CLOSE,0,_scope.stacksize); \
							} \
						}

#define END_SCOPE_NO_CLOSE() {	if(_fs->GetStackSize() != _scope.stacksize) { \
							_fs->SetStackSize(_scope.stacksize); \
						} \
						_scope = __oldscope__; \
					}

#define END_SCOPE() {	SQInteger oldouters = _fs->_outers;\
						if(_fs->GetStackSize() != _scope.stacksize) { \
							_fs->SetStackSize(_scope.stacksize); \
							if(oldouters != _fs->_outers) { \
								_fs->AddInstruction(_OP_CLOSE,0,_scope.stacksize); \
							} \
						} \
						_scope = __oldscope__; \
					}

#define BEGIN_BREAKBLE_BLOCK()	SQInteger __nbreaks__=_fs->_unresolvedbreaks.size(); \
							SQInteger __ncontinues__=_fs->_unresolvedcontinues.size(); \
							_fs->_breaktargets.push_back(0);_fs->_continuetargets.push_back(0);

#define END_BREAKBLE_BLOCK(continue_target) {__nbreaks__=_fs->_unresolvedbreaks.size()-__nbreaks__; \
					__ncontinues__=_fs->_unresolvedcontinues.size()-__ncontinues__; \
					if(__ncontinues__>0)ResolveContinues(_fs,__ncontinues__,continue_target); \
					if(__nbreaks__>0)ResolveBreaks(_fs,__nbreaks__); \
					_fs->_breaktargets.pop_back();_fs->_continuetargets.pop_back();}

class SQCompiler
{
public:
	SQCompiler(SQVM *v, SQLEXREADFUNC rg, SQUserPointer up, const SQChar* sourcename, bool raiseerror, bool lineinfo)
	{
		_vm=v;
		_lex.Init(_ss(v), rg, up,ThrowError,this);
		_sourcename = SQString::Create(_ss(v), sourcename);
		_lineinfo = lineinfo;_raiseerror = raiseerror;
		_scope.outers = 0;
		_scope.stacksize = 0;
		compilererror = NULL;
	}
	static void ThrowError(void *ud, const SQChar *s) {
		SQCompiler *c = (SQCompiler *)ud;
		c->Error(s);
	}
	void Error(const SQChar *s, ...)
	{
		static SQChar temp[256];
		va_list vl;
		va_start(vl, s);
		scvsprintf(temp, s, vl);
		va_end(vl);
		compilererror = temp;
		longjmp(_errorjmp,1);
	}
	void Lex(){	_token = _lex.Lex();}
	SQObject Expect(SQInteger tok)
	{
		
		if(_token != tok) {
			if(_token == TK_CONSTRUCTOR && tok == TK_IDENTIFIER) {
				//do nothing
			}
			else {
				const SQChar *etypename;
				if(tok > 255) {
					switch(tok)
					{
					case TK_IDENTIFIER:
						etypename = _SC("IDENTIFIER");
						break;
					case TK_STRING_LITERAL:
						etypename = _SC("STRING_LITERAL");
						break;
					case TK_INTEGER:
						etypename = _SC("INTEGER");
						break;
					case TK_FLOAT:
						etypename = _SC("FLOAT");
						break;
					default:
						etypename = _lex.Tok2Str(tok);
					}
					Error(_SC("expected '%s'"), etypename);
				}
				Error(_SC("expected '%c'"), tok);
			}
		}
		SQObjectPtr ret;
		switch(tok)
		{
		case TK_IDENTIFIER:
			ret = _fs->CreateString(_lex._svalue);
			break;
		case TK_STRING_LITERAL:
			ret = _fs->CreateString(_lex._svalue,_lex._longstr.size()-1);
			break;
		case TK_INTEGER:
			ret = SQObjectPtr(_lex._nvalue);
			break;
		case TK_FLOAT:
			ret = SQObjectPtr(_lex._fvalue);
			break;
		}
		Lex();
		return ret;
	}
	bool IsEndOfStatement() { return ((_lex._prevtoken == _SC('\n')) || (_token == SQUIRREL_EOB) || (_token == _SC('}')) || (_token == _SC(';'))); }
	void OptionalSemicolon()
	{
		if(_token == _SC(';')) { Lex(); return; }
		if(!IsEndOfStatement()) {
			Error(_SC("end of statement expected (; or lf)"));
		}
	}
	void MoveIfCurrentTargetIsLocal() {
		SQInteger trg = _fs->TopTarget();
		if(_fs->IsLocal(trg)) {
			trg = _fs->PopTarget(); //no pops the target and move it
			_fs->AddInstruction(_OP_MOVE, _fs->PushTarget(), trg);
		}
	}
	bool Compile(SQObjectPtr &o)
	{
		_debugline = 1;
		_debugop = 0;

		SQFuncState funcstate(_ss(_vm), NULL,ThrowError,this);
		funcstate._name = SQString::Create(_ss(_vm), _SC("main"));
		_fs = &funcstate;
		_fs->AddParameter(_fs->CreateString(_SC("this")));
		_fs->AddParameter(_fs->CreateString(_SC("vargv")));
		_fs->_varparams = true;
		_fs->_sourcename = _sourcename;
		SQInteger stacksize = _fs->GetStackSize();
		if(setjmp(_errorjmp) == 0) {
			Lex();
			while(_token > 0){
				Statement();
				if(_lex._prevtoken != _SC('}') && _lex._prevtoken != _SC(';')) OptionalSemicolon();
			}
			_fs->SetStackSize(stacksize);
			_fs->AddLineInfos(_lex._currentline, _lineinfo, true);
			_fs->AddInstruction(_OP_RETURN, 0xFF);
			_fs->SetStackSize(0);
			o =_fs->BuildProto();
#ifdef _DEBUG_DUMP
			_fs->Dump(_funcproto(o));
#endif
		}
		else {
			if(_raiseerror && _ss(_vm)->_compilererrorhandler) {
				_ss(_vm)->_compilererrorhandler(_vm, compilererror, type(_sourcename) == OT_STRING?_stringval(_sourcename):_SC("unknown"),
					_lex._currentline, _lex._currentcolumn);
			}
			_vm->_lasterror = SQString::Create(_ss(_vm), compilererror, -1);
			return false;
		}
		return true;
	}
	void Statements()
	{
		while(_token != _SC('}') && _token != TK_DEFAULT && _token != TK_CASE) {
			Statement();
			if(_lex._prevtoken != _SC('}') && _lex._prevtoken != _SC(';')) OptionalSemicolon();
		}
	}
	void Statement(bool closeframe = true)
	{
		_fs->AddLineInfos(_lex._currentline, _lineinfo);
		switch(_token){
		case _SC(';'):	Lex();					break;
		case TK_IF:		IfStatement();			break;
		case TK_WHILE:		WhileStatement();		break;
		case TK_DO:		DoWhileStatement();		break;
		case TK_FOR:		ForStatement();			break;
		case TK_FOREACH:	ForEachStatement();		break;
		case TK_SWITCH:	SwitchStatement();		break;
		case TK_LOCAL:		LocalDeclStatement();	break;
		case TK_RETURN:
		case TK_YIELD: {
			SQOpcode op;
			if(_token == TK_RETURN) {
				op = _OP_RETURN;
			}
			else {
				op = _OP_YIELD;
				_fs->_bgenerator = true;
			}
			Lex();
			if(!IsEndOfStatement()) {
				SQInteger retexp = _fs->GetCurrentPos()+1;
				CommaExpr();
				if(op == _OP_RETURN && _fs->_traps > 0)
					_fs->AddInstruction(_OP_POPTRAP, _fs->_traps, 0);
				_fs->_returnexp = retexp;
				_fs->AddInstruction(op, 1, _fs->PopTarget(),_fs->GetStackSize());
			}
			else{ 
				if(op == _OP_RETURN && _fs->_traps > 0)
					_fs->AddInstruction(_OP_POPTRAP, _fs->_traps ,0);
				_fs->_returnexp = -1;
				_fs->AddInstruction(op, 0xFF,0,_fs->GetStackSize()); 
			}
			break;}
		case TK_BREAK:
			if(_fs->_breaktargets.size() <= 0)Error(_SC("'break' has to be in a loop block"));
			if(_fs->_breaktargets.top() > 0){
				_fs->AddInstruction(_OP_POPTRAP, _fs->_breaktargets.top(), 0);
			}
			RESOLVE_OUTERS();
			_fs->AddInstruction(_OP_JMP, 0, -1234);
			_fs->_unresolvedbreaks.push_back(_fs->GetCurrentPos());
			Lex();
			break;
		case TK_CONTINUE:
			if(_fs->_continuetargets.size() <= 0)Error(_SC("'continue' has to be in a loop block"));
			if(_fs->_continuetargets.top() > 0) {
				_fs->AddInstruction(_OP_POPTRAP, _fs->_continuetargets.top(), 0);
			}
			RESOLVE_OUTERS();
			_fs->AddInstruction(_OP_JMP, 0, -1234);
			_fs->_unresolvedcontinues.push_back(_fs->GetCurrentPos());
			Lex();
			break;
		case TK_FUNCTION:
			FunctionStatement();
			break;
		case TK_CLASS:
			ClassStatement();
			break;
		case TK_ENUM:
			EnumStatement();
			break;
		case _SC('{'):{
				BEGIN_SCOPE();
				Lex();
				Statements();
				Expect(_SC('}'));
				if(closeframe) {
					END_SCOPE();
				}
				else {
					END_SCOPE_NO_CLOSE();
				}
			}
			break;
		case TK_TRY:
			TryCatchStatement();
			break;
		case TK_THROW:
			Lex();
			CommaExpr();
			_fs->AddInstruction(_OP_THROW, _fs->PopTarget());
			break;
		case TK_CONST:
			{
			Lex();
			SQObject id = Expect(TK_IDENTIFIER);
			Expect('=');
			SQObject val = ExpectScalar();
			OptionalSemicolon();
			SQTable *enums = _table(_ss(_vm)->_consts);
			SQObjectPtr strongid = id; 
			enums->NewSlot(strongid,SQObjectPtr(val));
			strongid.Null();
			}
			break;
		default:
			CommaExpr();
			_fs->DiscardTarget();
			//_fs->PopTarget();
			break;
		}
		_fs->SnoozeOpt();
	}
	void EmitDerefOp(SQOpcode op)
	{
		SQInteger val = _fs->PopTarget();
		SQInteger key = _fs->PopTarget();
		SQInteger src = _fs->PopTarget();
        _fs->AddInstruction(op,_fs->PushTarget(),src,key,val);
	}
	void Emit2ArgsOP(SQOpcode op, SQInteger p3 = 0)
	{
		SQInteger p2 = _fs->PopTarget(); //src in OP_GET
		SQInteger p1 = _fs->PopTarget(); //key in OP_GET
		_fs->AddInstruction(op,_fs->PushTarget(), p1, p2, p3);
	}
	void EmitCompoundArith(SQInteger tok, SQInteger etype, SQInteger pos)
	{
		/* Generate code depending on the expression type */
		switch(etype) {
		case LOCAL:{
			SQInteger p2 = _fs->PopTarget(); //src in OP_GET
			SQInteger p1 = _fs->PopTarget(); //key in OP_GET
			_fs->PushTarget(p1);
			//EmitCompArithLocal(tok, p1, p1, p2);
			_fs->AddInstruction(ChooseArithOpByToken(tok),p1, p2, p1, 0);
				   }
			break;
		case OBJECT:
		case BASE:
			{
				SQInteger val = _fs->PopTarget();
				SQInteger key = _fs->PopTarget();
				SQInteger src = _fs->PopTarget();
				/* _OP_COMPARITH mixes dest obj and source val in the arg1 */
				_fs->AddInstruction(_OP_COMPARITH, _fs->PushTarget(), (src<<16)|val, key, ChooseCompArithCharByToken(tok));
			}
			break;
		case OUTER:
			{
				SQInteger val = _fs->TopTarget();
				SQInteger tmp = _fs->PushTarget();
				_fs->AddInstruction(_OP_GETOUTER,   tmp, pos);
				_fs->AddInstruction(ChooseArithOpByToken(tok), tmp, val, tmp, 0);
				_fs->AddInstruction(_OP_SETOUTER, tmp, pos, tmp);
			}
			break;
		}
	}
	void CommaExpr()
	{
		for(Expression();_token == ',';_fs->PopTarget(), Lex(), CommaExpr());
	}
	void Expression()
	{
		 SQExpState es = _es;
		_es.etype     = EXPR;
		_es.epos      = -1;
		_es.donot_get = false;
		LogicalOrExp();
		switch(_token)  {
		case _SC('='):
		case TK_NEWSLOT:
		case TK_MINUSEQ:
		case TK_PLUSEQ:
		case TK_MULEQ:
		case TK_DIVEQ:
		case TK_MODEQ:{
			SQInteger op = _token;
			SQInteger ds = _es.etype;
			SQInteger pos = _es.epos;
			if(ds == EXPR) Error(_SC("can't assign expression"));
			Lex(); Expression();

			switch(op){
			case TK_NEWSLOT:
				if(ds == OBJECT || ds == BASE)
					EmitDerefOp(_OP_NEWSLOT);
				else //if _derefstate != DEREF_NO_DEREF && DEREF_FIELD so is the index of a local
					Error(_SC("can't 'create' a local slot"));
				break;
			case _SC('='): //ASSIGN
				switch(ds) {
				case LOCAL:
					{
						SQInteger src = _fs->PopTarget();
						SQInteger dst = _fs->TopTarget();
						_fs->AddInstruction(_OP_MOVE, dst, src);
					}
					break;
				case OBJECT:
				case BASE:
					EmitDerefOp(_OP_SET);
					break;
				case OUTER:
					{
						SQInteger src = _fs->PopTarget();
						SQInteger dst = _fs->PushTarget();
						_fs->AddInstruction(_OP_SETOUTER, dst, pos, src);
					}
				}
				break;
			case TK_MINUSEQ:
			case TK_PLUSEQ:
			case TK_MULEQ:
			case TK_DIVEQ:
			case TK_MODEQ:
				EmitCompoundArith(op, ds, pos);
				break;
			}
			}
			break;
		case _SC('?'): {
			Lex();
			_fs->AddInstruction(_OP_JZ, _fs->PopTarget());
			SQInteger jzpos = _fs->GetCurrentPos();
			SQInteger trg = _fs->PushTarget();
			Expression();
			SQInteger first_exp = _fs->PopTarget();
			if(trg != first_exp) _fs->AddInstruction(_OP_MOVE, trg, first_exp);
			SQInteger endfirstexp = _fs->GetCurrentPos();
			_fs->AddInstruction(_OP_JMP, 0, 0);
			Expect(_SC(':'));
			SQInteger jmppos = _fs->GetCurrentPos();
			Expression();
			SQInteger second_exp = _fs->PopTarget();
			if(trg != second_exp) _fs->AddInstruction(_OP_MOVE, trg, second_exp);
			_fs->SetIntructionParam(jmppos, 1, _fs->GetCurrentPos() - jmppos);
			_fs->SetIntructionParam(jzpos, 1, endfirstexp - jzpos + 1);
			_fs->SnoozeOpt();
			}
			break;
		}
		_es = es;
	}
	template<typename T> void BIN_EXP(SQOpcode op, T f,SQInteger op3 = 0)
	{
		Lex(); (this->*f)();
		SQInteger op1 = _fs->PopTarget();SQInteger op2 = _fs->PopTarget();
		_fs->AddInstruction(op, _fs->PushTarget(), op1, op2, op3);
	}
	void LogicalOrExp()
	{
		LogicalAndExp();
		for(;;) if(_token == TK_OR) {
			SQInteger first_exp = _fs->PopTarget();
			SQInteger trg = _fs->PushTarget();
			_fs->AddInstruction(_OP_OR, trg, 0, first_exp, 0);
			SQInteger jpos = _fs->GetCurrentPos();
			if(trg != first_exp) _fs->AddInstruction(_OP_MOVE, trg, first_exp);
			Lex(); LogicalOrExp();
			_fs->SnoozeOpt();
			SQInteger second_exp = _fs->PopTarget();
			if(trg != second_exp) _fs->AddInstruction(_OP_MOVE, trg, second_exp);
			_fs->SnoozeOpt();
			_fs->SetIntructionParam(jpos, 1, (_fs->GetCurrentPos() - jpos));
			break;
		}else return;
	}
	void LogicalAndExp()
	{
		BitwiseOrExp();
		for(;;) switch(_token) {
		case TK_AND: {
			SQInteger first_exp = _fs->PopTarget();
			SQInteger trg = _fs->PushTarget();
			_fs->AddInstruction(_OP_AND, trg, 0, first_exp, 0);
			SQInteger jpos = _fs->GetCurrentPos();
			if(trg != first_exp) _fs->AddInstruction(_OP_MOVE, trg, first_exp);
			Lex(); LogicalAndExp();
			_fs->SnoozeOpt();
			SQInteger second_exp = _fs->PopTarget();
			if(trg != second_exp) _fs->AddInstruction(_OP_MOVE, trg, second_exp);
			_fs->SnoozeOpt();
			_fs->SetIntructionParam(jpos, 1, (_fs->GetCurrentPos() - jpos));
			break;
			}
		case TK_IN: BIN_EXP(_OP_EXISTS, &SQCompiler::BitwiseOrExp); break;
		case TK_INSTANCEOF: BIN_EXP(_OP_INSTANCEOF, &SQCompiler::BitwiseOrExp); break;
		default:
			return;
		}
	}
	void BitwiseOrExp()
	{
		BitwiseXorExp();
		for(;;) if(_token == _SC('|'))
		{BIN_EXP(_OP_BITW, &SQCompiler::BitwiseXorExp,BW_OR);
		}else return;
	}
	void BitwiseXorExp()
	{
		BitwiseAndExp();
		for(;;) if(_token == _SC('^'))
		{BIN_EXP(_OP_BITW, &SQCompiler::BitwiseAndExp,BW_XOR);
		}else return;
	}
	void BitwiseAndExp()
	{
		EqExp();
		for(;;) if(_token == _SC('&'))
		{BIN_EXP(_OP_BITW, &SQCompiler::EqExp,BW_AND);
		}else return;
	}
	void EqExp()
	{
		CompExp();
		for(;;) switch(_token) {
		case TK_EQ: BIN_EXP(_OP_EQ, &SQCompiler::CompExp); break;
		case TK_NE: BIN_EXP(_OP_NE, &SQCompiler::CompExp); break;
		case TK_3WAYSCMP: BIN_EXP(_OP_CMP, &SQCompiler::CompExp,CMP_3W); break;
		default: return;	
		}
	}
	void CompExp()
	{
		ShiftExp();
		for(;;) switch(_token) {
		case _SC('>'): BIN_EXP(_OP_CMP, &SQCompiler::ShiftExp,CMP_G); break;
		case _SC('<'): BIN_EXP(_OP_CMP, &SQCompiler::ShiftExp,CMP_L); break;
		case TK_GE: BIN_EXP(_OP_CMP, &SQCompiler::ShiftExp,CMP_GE); break;
		case TK_LE: BIN_EXP(_OP_CMP, &SQCompiler::ShiftExp,CMP_LE); break;
		default: return;	
		}
	}
	void ShiftExp()
	{
		PlusExp();
		for(;;) switch(_token) {
		case TK_USHIFTR: BIN_EXP(_OP_BITW, &SQCompiler::PlusExp,BW_USHIFTR); break;
		case TK_SHIFTL: BIN_EXP(_OP_BITW, &SQCompiler::PlusExp,BW_SHIFTL); break;
		case TK_SHIFTR: BIN_EXP(_OP_BITW, &SQCompiler::PlusExp,BW_SHIFTR); break;
		default: return;	
		}
	}
	SQOpcode ChooseArithOpByToken(SQInteger tok)
	{
		switch(tok) {
			case TK_PLUSEQ: case '+': return _OP_ADD;
			case TK_MINUSEQ: case '-': return _OP_SUB;
			case TK_MULEQ: case '*': return _OP_MUL;
			case TK_DIVEQ: case '/': return _OP_DIV;
			case TK_MODEQ: case '%': return _OP_MOD;
			default: assert(0);
		}
		return _OP_ADD;
	}
	SQInteger ChooseCompArithCharByToken(SQInteger tok)
	{
		SQInteger oper;
		switch(tok){
		case TK_MINUSEQ: oper = '-'; break;
		case TK_PLUSEQ: oper = '+'; break;
		case TK_MULEQ: oper = '*'; break;
		case TK_DIVEQ: oper = '/'; break;
		case TK_MODEQ: oper = '%'; break;
		default: oper = 0; //shut up compiler
			assert(0); break;
		};
		return oper;
	}
	void PlusExp()
	{
		MultExp();
		for(;;) switch(_token) {
		case _SC('+'): case _SC('-'):
			BIN_EXP(ChooseArithOpByToken(_token), &SQCompiler::MultExp); break;
		default: return;
		}
	}
	
	void MultExp()
	{
		PrefixedExpr();
		for(;;) switch(_token) {
		case _SC('*'): case _SC('/'): case _SC('%'):
			BIN_EXP(ChooseArithOpByToken(_token), &SQCompiler::PrefixedExpr); break;
		default: return;
		}
	}
	//if 'pos' != -1 the previous variable is a local variable
	void PrefixedExpr()
	{
		SQInteger pos = Factor();
		for(;;) {
			switch(_token) {
			case _SC('.'):
				pos = -1;
				Lex(); 

				_fs->AddInstruction(_OP_LOAD, _fs->PushTarget(), _fs->GetConstant(Expect(TK_IDENTIFIER)));
				if(_es.etype==BASE) {
					Emit2ArgsOP(_OP_GET);
					pos = _fs->TopTarget();
					_es.etype = EXPR;
					_es.epos   = pos;
				}
				else {
					if(NeedGet()) {
						Emit2ArgsOP(_OP_GET);
					}
					_es.etype = OBJECT;
				}
				break;
			case _SC('['):
				if(_lex._prevtoken == _SC('\n')) Error(_SC("cannot brake deref/or comma needed after [exp]=exp slot declaration"));
				Lex(); Expression(); Expect(_SC(']')); 
				pos = -1;
				if(_es.etype==BASE) {
					Emit2ArgsOP(_OP_GET);
					pos = _fs->TopTarget();
					_es.etype = EXPR;
					_es.epos   = pos;
				}
				else {
					if(NeedGet()) {
						Emit2ArgsOP(_OP_GET);
					}
					_es.etype = OBJECT;
				}
				break;
			case TK_MINUSMINUS:
			case TK_PLUSPLUS:
				{
					if(IsEndOfStatement()) return;
					SQInteger diff = (_token==TK_MINUSMINUS) ? -1 : 1;
					Lex();
					switch(_es.etype)
					{
						case EXPR: Error(_SC("can't '++' or '--' an expression")); break;
						case OBJECT:
						case BASE:
							Emit2ArgsOP(_OP_PINC, diff);
							break;
						case LOCAL: {
							SQInteger src = _fs->PopTarget();
							_fs->AddInstruction(_OP_PINCL, _fs->PushTarget(), src, 0, diff);
									}
							break;
						case OUTER: {
							SQInteger tmp1 = _fs->PushTarget();
							SQInteger tmp2 = _fs->PushTarget();
							_fs->AddInstruction(_OP_GETOUTER, tmp2, _es.epos);
							_fs->AddInstruction(_OP_PINCL,    tmp1, tmp2, 0, diff);
							_fs->AddInstruction(_OP_SETOUTER, tmp2, _es.epos, tmp2);
							_fs->PopTarget();
						}
					}
				}
				return;
				break;	
			case _SC('('): 
				switch(_es.etype) {
					case OBJECT: {
						SQInteger key     = _fs->PopTarget();  /* location of the key */
						SQInteger table   = _fs->PopTarget();  /* location of the object */
						SQInteger closure = _fs->PushTarget(); /* location for the closure */
						SQInteger ttarget = _fs->PushTarget(); /* location for 'this' pointer */
						_fs->AddInstruction(_OP_PREPCALL, closure, key, table, ttarget);
						}
						break;
					case BASE:
						//Emit2ArgsOP(_OP_GET);
						_fs->AddInstruction(_OP_MOVE, _fs->PushTarget(), 0);
						break;
					case OUTER:
						_fs->AddInstruction(_OP_GETOUTER, _fs->PushTarget(), _es.epos);
						_fs->AddInstruction(_OP_MOVE,     _fs->PushTarget(), 0);
						break;
					default:
						_fs->AddInstruction(_OP_MOVE, _fs->PushTarget(), 0);
				}
				_es.etype = EXPR;
				Lex();
				FunctionCallArgs();
				break;
			default: return;
			}
		}
	}
	SQInteger Factor()
	{
		_es.etype = EXPR;
		switch(_token)
		{
		case TK_STRING_LITERAL:
			_fs->AddInstruction(_OP_LOAD, _fs->PushTarget(), _fs->GetConstant(_fs->CreateString(_lex._svalue,_lex._longstr.size()-1)));
			Lex(); 
			break;
		case TK_BASE:
			Lex();
			_fs->AddInstruction(_OP_GETBASE, _fs->PushTarget());
			_es.etype  = BASE;
			_es.epos   = _fs->TopTarget();
			return (_es.epos);
			break;
		case TK_IDENTIFIER:
		case TK_CONSTRUCTOR:
		case TK_THIS:{
				SQObject id;
				SQObject constant;

				switch(_token) {
					case TK_IDENTIFIER:  id = _fs->CreateString(_lex._svalue);       break;
					case TK_THIS:        id = _fs->CreateString(_SC("this"));        break;
					case TK_CONSTRUCTOR: id = _fs->CreateString(_SC("constructor")); break;
				}

				SQInteger pos = -1;
				Lex();
				if((pos = _fs->GetLocalVariable(id)) != -1) {
					/* Handle a local variable (includes 'this') */
					_fs->PushTarget(pos);
					_es.etype  = LOCAL;
					_es.epos   = pos;
				}

				else if((pos = _fs->GetOuterVariable(id)) != -1) {
					/* Handle a free var */
					if(NeedGet()) {
						_es.epos  = _fs->PushTarget();
						_fs->AddInstruction(_OP_GETOUTER, _es.epos, pos);	
						/* _es.etype = EXPR; already default value */
					}
					else {
						_es.etype = OUTER;
						_es.epos  = pos;
					}
				}

				else if(_fs->IsConstant(id, constant)) {
					/* Handle named constant */
					SQObjectPtr constval;
					SQObject    constid;
					if(type(constant) == OT_TABLE) {
						Expect('.');
						constid = Expect(TK_IDENTIFIER);
						if(!_table(constant)->Get(constid, constval)) {
							constval.Null();
							Error(_SC("invalid constant [%s.%s]"), _stringval(id), _stringval(constid));
						}
					}
					else {
						constval = constant;
					}
					_es.epos = _fs->PushTarget();

					/* generate direct or literal function depending on size */
					SQObjectType ctype = type(constval);
					switch(ctype) {
						case OT_INTEGER: EmitLoadConstInt(_integer(constval),_es.epos); break;
						case OT_FLOAT: EmitLoadConstFloat(_float(constval),_es.epos); break;
						default: _fs->AddInstruction(_OP_LOAD,_es.epos,_fs->GetConstant(constval)); break;
					}
					_es.etype = EXPR;
				}
				else {
					/* Handle a non-local variable, aka a field. Push the 'this' pointer on
					* the virtual stack (always found in offset 0, so no instruction needs to
					* be generated), and push the key next. Generate an _OP_LOAD instruction
					* for the latter. If we are not using the variable as a dref expr, generate
					* the _OP_GET instruction.
					*/
					_fs->PushTarget(0);
					_fs->AddInstruction(_OP_LOAD, _fs->PushTarget(), _fs->GetConstant(id));
					if(NeedGet()) {
						Emit2ArgsOP(_OP_GET);
					}
					_es.etype = OBJECT;
				}
				return _es.epos;
			}
			break;
		case TK_DOUBLE_COLON:  // "::"
			_fs->AddInstruction(_OP_LOADROOT, _fs->PushTarget());
			_es.etype = OBJECT;
			_token = _SC('.'); /* hack: drop into PrefixExpr, case '.'*/
			_es.epos = -1;
			return _es.epos;
			break;
		case TK_NULL: 
			_fs->AddInstruction(_OP_LOADNULLS, _fs->PushTarget(),1);
			Lex();
			break;
		case TK_INTEGER: EmitLoadConstInt(_lex._nvalue,-1); Lex();	break;
		case TK_FLOAT: EmitLoadConstFloat(_lex._fvalue,-1); Lex(); break;
		case TK_TRUE: case TK_FALSE:
			_fs->AddInstruction(_OP_LOADBOOL, _fs->PushTarget(),_token == TK_TRUE?1:0);
			Lex();
			break;
		case _SC('['): {
				_fs->AddInstruction(_OP_NEWOBJ, _fs->PushTarget(),0,0,NOT_ARRAY);
				SQInteger apos = _fs->GetCurrentPos(),key = 0;
				Lex();
				while(_token != _SC(']')) {
                    Expression(); 
					if(_token == _SC(',')) Lex();
					SQInteger val = _fs->PopTarget();
					SQInteger array = _fs->TopTarget();
					_fs->AddInstruction(_OP_APPENDARRAY, array, val, AAT_STACK);
					key++;
				}
				_fs->SetIntructionParam(apos, 1, key);
				Lex();
			}
			break;
		case _SC('{'):
			_fs->AddInstruction(_OP_NEWOBJ, _fs->PushTarget(),0,NOT_TABLE);
			Lex();ParseTableOrClass(_SC(','),_SC('}'));
			break;
		case TK_FUNCTION: FunctionExp(_token);break;
		case _SC('@'): FunctionExp(_token,true);break;
		case TK_CLASS: Lex(); ClassExp();break;
		case _SC('-'): 
			Lex(); 
			switch(_token) {
			case TK_INTEGER: EmitLoadConstInt(-_lex._nvalue,-1); Lex(); break;
			case TK_FLOAT: EmitLoadConstFloat(-_lex._fvalue,-1); Lex(); break;
			default: UnaryOP(_OP_NEG);
			}
			break;
		case _SC('!'): Lex(); UnaryOP(_OP_NOT); break;
		case _SC('~'): 
			Lex(); 
			if(_token == TK_INTEGER)  { EmitLoadConstInt(~_lex._nvalue,-1); Lex(); break; }
			UnaryOP(_OP_BWNOT); 
			break;
		case TK_TYPEOF : Lex() ;UnaryOP(_OP_TYPEOF); break;
		case TK_RESUME : Lex(); UnaryOP(_OP_RESUME); break;
		case TK_CLONE : Lex(); UnaryOP(_OP_CLONE); break;
		case TK_MINUSMINUS : 
		case TK_PLUSPLUS :PrefixIncDec(_token); break;
		case TK_DELETE : DeleteExpr(); break;
		case _SC('('): Lex(); CommaExpr(); Expect(_SC(')'));
			break;
		default: Error(_SC("expression expected"));
		}
		return -1;
	}
	void EmitLoadConstInt(SQInteger value,SQInteger target)
	{
		if(target < 0) {
			target = _fs->PushTarget();
		}
		if((value & (~((SQInteger)0xFFFFFFFF))) == 0) { //does it fit in 32 bits?
			_fs->AddInstruction(_OP_LOADINT, target,value);
		}
		else {
			_fs->AddInstruction(_OP_LOAD, target, _fs->GetNumericConstant(value));
		}
	}
	void EmitLoadConstFloat(SQFloat value,SQInteger target)
	{
		if(target < 0) {
			target = _fs->PushTarget();
		}
		if(sizeof(SQFloat) == sizeof(SQInt32)) {
			_fs->AddInstruction(_OP_LOADFLOAT, target,*((SQInt32 *)&value));
		}
		else {
			_fs->AddInstruction(_OP_LOAD, target, _fs->GetNumericConstant(value));
		}
	}
	void UnaryOP(SQOpcode op)
	{
		PrefixedExpr();
		SQInteger src = _fs->PopTarget();
		_fs->AddInstruction(op, _fs->PushTarget(), src);
	}
	bool NeedGet()
	{
		switch(_token) {
		case _SC('='): case _SC('('): case TK_NEWSLOT: case TK_MODEQ: case TK_MULEQ:
	    case TK_DIVEQ: case TK_MINUSEQ: case TK_PLUSEQ: case TK_PLUSPLUS: case TK_MINUSMINUS:
			return false;
		}
		return (!_es.donot_get || ( _es.donot_get && (_token == _SC('.') || _token == _SC('['))));
	}
	void FunctionCallArgs()
	{
		SQInteger nargs = 1;//this
		 while(_token != _SC(')')) {
			 Expression();
			 MoveIfCurrentTargetIsLocal();
			 nargs++; 
			 if(_token == _SC(',')){ 
				 Lex(); 
				 if(_token == ')') Error(_SC("expression expected, found ')'"));
			 }
		 }
		 Lex();
		 for(SQInteger i = 0; i < (nargs - 1); i++) _fs->PopTarget();
		 SQInteger stackbase = _fs->PopTarget();
		 SQInteger closure = _fs->PopTarget();
         _fs->AddInstruction(_OP_CALL, _fs->PushTarget(), closure, stackbase, nargs);
	}
	void ParseTableOrClass(SQInteger separator,SQInteger terminator)
	{
		SQInteger tpos = _fs->GetCurrentPos(),nkeys = 0;
		while(_token != terminator) {
			bool hasattrs = false;
			bool isstatic = false;
			//check if is an attribute
			if(separator == ';') {
				if(_token == TK_ATTR_OPEN) {
					_fs->AddInstruction(_OP_NEWOBJ, _fs->PushTarget(),0,NOT_TABLE); Lex();
					ParseTableOrClass(',',TK_ATTR_CLOSE);
					hasattrs = true;
				}
				if(_token == TK_STATIC) {
					isstatic = true;
					Lex();
				}
			}
			switch(_token) {
			case TK_FUNCTION:
			case TK_CONSTRUCTOR:{
				SQInteger tk = _token;
				Lex();
				SQObject id = tk == TK_FUNCTION ? Expect(TK_IDENTIFIER) : _fs->CreateString(_SC("constructor"));
				Expect(_SC('('));
				_fs->AddInstruction(_OP_LOAD, _fs->PushTarget(), _fs->GetConstant(id));
				CreateFunction(id);
				_fs->AddInstruction(_OP_CLOSURE, _fs->PushTarget(), _fs->_functions.size() - 1, 0);
								}
								break;
			case _SC('['):
				Lex(); CommaExpr(); Expect(_SC(']'));
				Expect(_SC('=')); Expression();
				break;
			case TK_STRING_LITERAL: //JSON
				if(separator == ',') { //only works for tables
					_fs->AddInstruction(_OP_LOAD, _fs->PushTarget(), _fs->GetConstant(Expect(TK_STRING_LITERAL)));
					Expect(_SC(':')); Expression();
					break;
				}
			default :
				_fs->AddInstruction(_OP_LOAD, _fs->PushTarget(), _fs->GetConstant(Expect(TK_IDENTIFIER)));
				Expect(_SC('=')); Expression();
			}
			if(_token == separator) Lex();//optional comma/semicolon
			nkeys++;
			SQInteger val = _fs->PopTarget();
			SQInteger key = _fs->PopTarget();
			SQInteger attrs = hasattrs ? _fs->PopTarget():-1;
			assert((hasattrs && (attrs == key-1)) || !hasattrs);
			unsigned char flags = (hasattrs?NEW_SLOT_ATTRIBUTES_FLAG:0)|(isstatic?NEW_SLOT_STATIC_FLAG:0);
			SQInteger table = _fs->TopTarget(); //<<BECAUSE OF THIS NO COMMON EMIT FUNC IS POSSIBLE
			if(separator == _SC(',')) { //hack recognizes a table from the separator
				_fs->AddInstruction(_OP_NEWSLOT, 0xFF, table, key, val);
			}
			else {
				_fs->AddInstruction(_OP_NEWSLOTA, flags, table, key, val); //this for classes only as it invokes _newmember
			}
		}
		if(separator == _SC(',')) //hack recognizes a table from the separator
			_fs->SetIntructionParam(tpos, 1, nkeys);
		Lex();
	}
	void LocalDeclStatement()
	{
		SQObject varname;
		Lex();
		if( _token == TK_FUNCTION) {
			Lex();
			varname = Expect(TK_IDENTIFIER);
			Expect(_SC('('));
			CreateFunction(varname,false);
			_fs->AddInstruction(_OP_CLOSURE, _fs->PushTarget(), _fs->_functions.size() - 1, 0);
			_fs->PopTarget();
			_fs->PushLocalVariable(varname);
			return;
		}

		do {
			varname = Expect(TK_IDENTIFIER);
			if(_token == _SC('=')) {
				Lex(); Expression();
				SQInteger src = _fs->PopTarget();
				SQInteger dest = _fs->PushTarget();
				if(dest != src) _fs->AddInstruction(_OP_MOVE, dest, src);
			}
			else{
				_fs->AddInstruction(_OP_LOADNULLS, _fs->PushTarget(),1);
			}
			_fs->PopTarget();
			_fs->PushLocalVariable(varname);
			if(_token == _SC(',')) Lex(); else break;
		} while(1);
	}
	void IfStatement()
	{
		SQInteger jmppos;
		bool haselse = false;
		Lex(); Expect(_SC('(')); CommaExpr(); Expect(_SC(')'));
		_fs->AddInstruction(_OP_JZ, _fs->PopTarget());
		SQInteger jnepos = _fs->GetCurrentPos();
		BEGIN_SCOPE();
		
		Statement();
		//
		if(_token != _SC('}') && _token != TK_ELSE) OptionalSemicolon();
		
		END_SCOPE();
		SQInteger endifblock = _fs->GetCurrentPos();
		if(_token == TK_ELSE){
			haselse = true;
			BEGIN_SCOPE();
			_fs->AddInstruction(_OP_JMP);
			jmppos = _fs->GetCurrentPos();
			Lex();
			Statement(); OptionalSemicolon();
			END_SCOPE();
			_fs->SetIntructionParam(jmppos, 1, _fs->GetCurrentPos() - jmppos);
		}
		_fs->SetIntructionParam(jnepos, 1, endifblock - jnepos + (haselse?1:0));
	}
	void WhileStatement()
	{
		SQInteger jzpos, jmppos;
		jmppos = _fs->GetCurrentPos();
		Lex(); Expect(_SC('(')); CommaExpr(); Expect(_SC(')'));
		
		BEGIN_BREAKBLE_BLOCK();
		_fs->AddInstruction(_OP_JZ, _fs->PopTarget());
		jzpos = _fs->GetCurrentPos();
		BEGIN_SCOPE();
		
		Statement();
		
		END_SCOPE();
		_fs->AddInstruction(_OP_JMP, 0, jmppos - _fs->GetCurrentPos() - 1);
		_fs->SetIntructionParam(jzpos, 1, _fs->GetCurrentPos() - jzpos);
		
		END_BREAKBLE_BLOCK(jmppos);
	}
	void DoWhileStatement()
	{
		Lex();
		SQInteger jmptrg = _fs->GetCurrentPos();
		BEGIN_BREAKBLE_BLOCK()
		BEGIN_SCOPE();
		Statement();
		END_SCOPE();
		Expect(TK_WHILE);
		SQInteger continuetrg = _fs->GetCurrentPos();
		Expect(_SC('(')); CommaExpr(); Expect(_SC(')'));
		_fs->AddInstruction(_OP_JZ, _fs->PopTarget(), 1);
		_fs->AddInstruction(_OP_JMP, 0, jmptrg - _fs->GetCurrentPos() - 1);
		END_BREAKBLE_BLOCK(continuetrg);
	}
	void ForStatement()
	{
		Lex();
		BEGIN_SCOPE();
		Expect(_SC('('));
		if(_token == TK_LOCAL) LocalDeclStatement();
		else if(_token != _SC(';')){
			CommaExpr();
			_fs->PopTarget();
		}
		Expect(_SC(';'));
		_fs->SnoozeOpt();
		SQInteger jmppos = _fs->GetCurrentPos();
		SQInteger jzpos = -1;
		if(_token != _SC(';')) { CommaExpr(); _fs->AddInstruction(_OP_JZ, _fs->PopTarget()); jzpos = _fs->GetCurrentPos(); }
		Expect(_SC(';'));
		_fs->SnoozeOpt();
		SQInteger expstart = _fs->GetCurrentPos() + 1;
		if(_token != _SC(')')) {
			CommaExpr();
			_fs->PopTarget();
		}
		Expect(_SC(')'));
		_fs->SnoozeOpt();
		SQInteger expend = _fs->GetCurrentPos();
		SQInteger expsize = (expend - expstart) + 1;
		SQInstructionVec exp;
		if(expsize > 0) {
			for(SQInteger i = 0; i < expsize; i++)
				exp.push_back(_fs->GetInstruction(expstart + i));
			_fs->PopInstructions(expsize);
		}
		BEGIN_BREAKBLE_BLOCK()
		Statement();
		SQInteger continuetrg = _fs->GetCurrentPos();
		if(expsize > 0) {
			for(SQInteger i = 0; i < expsize; i++)
				_fs->AddInstruction(exp[i]);
		}
		_fs->AddInstruction(_OP_JMP, 0, jmppos - _fs->GetCurrentPos() - 1, 0);
		if(jzpos>  0) _fs->SetIntructionParam(jzpos, 1, _fs->GetCurrentPos() - jzpos);
		END_SCOPE();
		
		END_BREAKBLE_BLOCK(continuetrg);
	}
	void ForEachStatement()
	{
		SQObject idxname, valname;
		Lex(); Expect(_SC('(')); valname = Expect(TK_IDENTIFIER);
		if(_token == _SC(',')) {
			idxname = valname;
			Lex(); valname = Expect(TK_IDENTIFIER);
		}
		else{
			idxname = _fs->CreateString(_SC("@INDEX@"));
		}
		Expect(TK_IN);
		
		//save the stack size
		BEGIN_SCOPE();
		//put the table in the stack(evaluate the table expression)
		Expression(); Expect(_SC(')'));
		SQInteger container = _fs->TopTarget();
		//push the index local var
		SQInteger indexpos = _fs->PushLocalVariable(idxname);
		_fs->AddInstruction(_OP_LOADNULLS, indexpos,1);
		//push the value local var
		SQInteger valuepos = _fs->PushLocalVariable(valname);
		_fs->AddInstruction(_OP_LOADNULLS, valuepos,1);
		//push reference index
		SQInteger itrpos = _fs->PushLocalVariable(_fs->CreateString(_SC("@ITERATOR@"))); //use invalid id to make it inaccessible
		_fs->AddInstruction(_OP_LOADNULLS, itrpos,1);
		SQInteger jmppos = _fs->GetCurrentPos();
		_fs->AddInstruction(_OP_FOREACH, container, 0, indexpos);
		SQInteger foreachpos = _fs->GetCurrentPos();
		_fs->AddInstruction(_OP_POSTFOREACH, container, 0, indexpos);
		//generate the statement code
		BEGIN_BREAKBLE_BLOCK()
		Statement();
		_fs->AddInstruction(_OP_JMP, 0, jmppos - _fs->GetCurrentPos() - 1);
		_fs->SetIntructionParam(foreachpos, 1, _fs->GetCurrentPos() - foreachpos);
		_fs->SetIntructionParam(foreachpos + 1, 1, _fs->GetCurrentPos() - foreachpos);
		END_BREAKBLE_BLOCK(foreachpos - 1);
		//restore the local variable stack(remove index,val and ref idx)
		_fs->PopTarget();
		END_SCOPE();
	}
	void SwitchStatement()
	{
		Lex(); Expect(_SC('(')); CommaExpr(); Expect(_SC(')'));
		Expect(_SC('{'));
		SQInteger expr = _fs->TopTarget();
		bool bfirst = true;
		SQInteger tonextcondjmp = -1;
		SQInteger skipcondjmp = -1;
		SQInteger __nbreaks__ = _fs->_unresolvedbreaks.size();
		_fs->_breaktargets.push_back(0);
		while(_token == TK_CASE) {
			if(!bfirst) {
				_fs->AddInstruction(_OP_JMP, 0, 0);
				skipcondjmp = _fs->GetCurrentPos();
				_fs->SetIntructionParam(tonextcondjmp, 1, _fs->GetCurrentPos() - tonextcondjmp);
			}
			//condition
			Lex(); Expression(); Expect(_SC(':'));
			SQInteger trg = _fs->PopTarget();
			_fs->AddInstruction(_OP_EQ, trg, trg, expr);
			_fs->AddInstruction(_OP_JZ, trg, 0);
			//end condition
			if(skipcondjmp != -1) {
				_fs->SetIntructionParam(skipcondjmp, 1, (_fs->GetCurrentPos() - skipcondjmp));
			}
			tonextcondjmp = _fs->GetCurrentPos();
			BEGIN_SCOPE();
			Statements();
			END_SCOPE();
			bfirst = false;
		}
		if(tonextcondjmp != -1)
			_fs->SetIntructionParam(tonextcondjmp, 1, _fs->GetCurrentPos() - tonextcondjmp);
		if(_token == TK_DEFAULT) {
			Lex(); Expect(_SC(':'));
			BEGIN_SCOPE();
			Statements();
			END_SCOPE();
		}
		Expect(_SC('}'));
		_fs->PopTarget();
		__nbreaks__ = _fs->_unresolvedbreaks.size() - __nbreaks__;
		if(__nbreaks__ > 0)ResolveBreaks(_fs, __nbreaks__);
		_fs->_breaktargets.pop_back();
	}
	void FunctionStatement()
	{
		SQObject id;
		Lex(); id = Expect(TK_IDENTIFIER);
		_fs->PushTarget(0);
		_fs->AddInstruction(_OP_LOAD, _fs->PushTarget(), _fs->GetConstant(id));
		if(_token == TK_DOUBLE_COLON) Emit2ArgsOP(_OP_GET);
		
		while(_token == TK_DOUBLE_COLON) {
			Lex();
			id = Expect(TK_IDENTIFIER);
			_fs->AddInstruction(_OP_LOAD, _fs->PushTarget(), _fs->GetConstant(id));
			if(_token == TK_DOUBLE_COLON) Emit2ArgsOP(_OP_GET);
		}
		Expect(_SC('('));
		CreateFunction(id);
		_fs->AddInstruction(_OP_CLOSURE, _fs->PushTarget(), _fs->_functions.size() - 1, 0);
		EmitDerefOp(_OP_NEWSLOT);
		_fs->PopTarget();
	}
	void ClassStatement()
	{
		SQExpState es;
		Lex();
		es = _es;
		_es.donot_get = true;
		PrefixedExpr();
		if(_es.etype == EXPR) {
			Error(_SC("invalid class name"));
		}
		else if(_es.etype == OBJECT || _es.etype == BASE) {
			ClassExp();
			EmitDerefOp(_OP_NEWSLOT);
			_fs->PopTarget();
		}
		else {
			Error(_SC("cannot create a class in a local with the syntax(class <local>)"));
		}
		_es = es;
	}
	SQObject ExpectScalar()
	{
		SQObject val;
		val._type = OT_NULL; val._unVal.nInteger = 0; //shut up GCC 4.x
		switch(_token) {
			case TK_INTEGER:
				val._type = OT_INTEGER;
				val._unVal.nInteger = _lex._nvalue;
				break;
			case TK_FLOAT:
				val._type = OT_FLOAT;
				val._unVal.fFloat = _lex._fvalue;
				break;
			case TK_STRING_LITERAL:
				val = _fs->CreateString(_lex._svalue,_lex._longstr.size()-1);
				break;
			case '-':
				Lex();
				switch(_token)
				{
				case TK_INTEGER:
					val._type = OT_INTEGER;
					val._unVal.nInteger = -_lex._nvalue;
				break;
				case TK_FLOAT:
					val._type = OT_FLOAT;
					val._unVal.fFloat = -_lex._fvalue;
				break;
				default:
					Error(_SC("scalar expected : integer,float"));
				}
				break;
			default:
				Error(_SC("scalar expected : integer,float or string"));
		}
		Lex();
		return val;
	}
	void EnumStatement()
	{
		Lex(); 
		SQObject id = Expect(TK_IDENTIFIER);
		Expect(_SC('{'));
		
		SQObject table = _fs->CreateTable();
		SQInteger nval = 0;
		while(_token != _SC('}')) {
			SQObject key = Expect(TK_IDENTIFIER);
			SQObject val;
			if(_token == _SC('=')) {
				Lex();
				val = ExpectScalar();
			}
			else {
				val._type = OT_INTEGER;
				val._unVal.nInteger = nval++;
			}
			_table(table)->NewSlot(SQObjectPtr(key),SQObjectPtr(val));
			if(_token == ',') Lex();
		}
		SQTable *enums = _table(_ss(_vm)->_consts);
		SQObjectPtr strongid = id; 
		enums->NewSlot(SQObjectPtr(strongid),SQObjectPtr(table));
		strongid.Null();
		Lex();
	}
	void TryCatchStatement()
	{
		SQObject exid;
		Lex();
		_fs->AddInstruction(_OP_PUSHTRAP,0,0);
		_fs->_traps++;
		if(_fs->_breaktargets.size()) _fs->_breaktargets.top()++;
		if(_fs->_continuetargets.size()) _fs->_continuetargets.top()++;
		SQInteger trappos = _fs->GetCurrentPos();
		{
			BEGIN_SCOPE();
			Statement();
			END_SCOPE();
		}
		_fs->_traps--;
		_fs->AddInstruction(_OP_POPTRAP, 1, 0);
		if(_fs->_breaktargets.size()) _fs->_breaktargets.top()--;
		if(_fs->_continuetargets.size()) _fs->_continuetargets.top()--;
		_fs->AddInstruction(_OP_JMP, 0, 0);
		SQInteger jmppos = _fs->GetCurrentPos();
		_fs->SetIntructionParam(trappos, 1, (_fs->GetCurrentPos() - trappos));
		Expect(TK_CATCH); Expect(_SC('(')); exid = Expect(TK_IDENTIFIER); Expect(_SC(')'));
		{
			BEGIN_SCOPE();
			SQInteger ex_target = _fs->PushLocalVariable(exid);
			_fs->SetIntructionParam(trappos, 0, ex_target);
			Statement();
			_fs->SetIntructionParams(jmppos, 0, (_fs->GetCurrentPos() - jmppos), 0);
			END_SCOPE();
		}
	}
	void FunctionExp(SQInteger ftype,bool lambda = false)
	{
		Lex(); Expect(_SC('('));
		SQObjectPtr dummy;
		CreateFunction(dummy,lambda);
		_fs->AddInstruction(_OP_CLOSURE, _fs->PushTarget(), _fs->_functions.size() - 1, ftype == TK_FUNCTION?0:1);
	}
	void ClassExp()
	{
		SQInteger base = -1;
		SQInteger attrs = -1;
		if(_token == TK_EXTENDS) {
			Lex(); Expression();
			base = _fs->TopTarget();
		}
		if(_token == TK_ATTR_OPEN) {
			Lex();
			_fs->AddInstruction(_OP_NEWOBJ, _fs->PushTarget(),0,NOT_TABLE);
			ParseTableOrClass(_SC(','),TK_ATTR_CLOSE);
			attrs = _fs->TopTarget();
		}
		Expect(_SC('{'));
		if(attrs != -1) _fs->PopTarget();
		if(base != -1) _fs->PopTarget();
		_fs->AddInstruction(_OP_NEWOBJ, _fs->PushTarget(), base, attrs,NOT_CLASS);
		ParseTableOrClass(_SC(';'),_SC('}'));
	}
	void DeleteExpr()
	{
		SQExpState es;
		Lex();
		es = _es;
		_es.donot_get = true;
		PrefixedExpr();
		if(_es.etype==EXPR) Error(_SC("can't delete an expression"));
		if(_es.etype==OBJECT || _es.etype==BASE) {
			Emit2ArgsOP(_OP_DELETE);
		}
		else {
			Error(_SC("cannot delete an (outer) local"));
		}
		_es = es;
	}
	void PrefixIncDec(SQInteger token)
	{
		SQExpState  es;
		SQInteger diff = (token==TK_MINUSMINUS) ? -1 : 1;
		Lex();
		es = _es;
		_es.donot_get = true;
		PrefixedExpr();
		if(_es.etype==EXPR) {
			Error(_SC("can't '++' or '--' an expression"));
		}
		else if(_es.etype==OBJECT || _es.etype==BASE) {
			Emit2ArgsOP(_OP_INC, diff);
		}
		else if(_es.etype==LOCAL) {
			SQInteger src = _fs->TopTarget();
			_fs->AddInstruction(_OP_INCL, src, src, 0, diff);
			
		}
		else if(_es.etype==OUTER) {
			SQInteger tmp = _fs->PushTarget();
			_fs->AddInstruction(_OP_GETOUTER, tmp, _es.epos);
			_fs->AddInstruction(_OP_INCL,     tmp, tmp, 0, diff);
			_fs->AddInstruction(_OP_SETOUTER, tmp, _es.epos, tmp);
		}
		_es = es;
	}
	void CreateFunction(SQObject &name,bool lambda = false)
	{
		SQFuncState *funcstate = _fs->PushChildState(_ss(_vm));
		funcstate->_name = name;
		SQObject paramname;
		funcstate->AddParameter(_fs->CreateString(_SC("this")));
		funcstate->_sourcename = _sourcename;
		SQInteger defparams = 0;
		while(_token!=_SC(')')) {
			if(_token == TK_VARPARAMS) {
				if(defparams > 0) Error(_SC("function with default parameters cannot have variable number of parameters"));
				funcstate->AddParameter(_fs->CreateString(_SC("vargv")));
				funcstate->_varparams = true;
				Lex();
				if(_token != _SC(')')) Error(_SC("expected ')'"));
				break;
			}
			else {
				paramname = Expect(TK_IDENTIFIER);
				funcstate->AddParameter(paramname);
				if(_token == _SC('=')) { 
					Lex();
					Expression();
					funcstate->AddDefaultParam(_fs->TopTarget());
					defparams++;
				}
				else {
					if(defparams > 0) Error(_SC("expected '='"));
				}
				if(_token == _SC(',')) Lex();
				else if(_token != _SC(')')) Error(_SC("expected ')' or ','"));
			}
		}
		Expect(_SC(')'));
		for(SQInteger n = 0; n < defparams; n++) {
			_fs->PopTarget();
		}
				
		SQFuncState *currchunk = _fs;
		_fs = funcstate;
		if(lambda) { 
			Expression(); 
			_fs->AddInstruction(_OP_RETURN, 1, _fs->PopTarget());}
		else { 
			Statement(false); 
		}
		funcstate->AddLineInfos(_lex._prevtoken == _SC('\n')?_lex._lasttokenline:_lex._currentline, _lineinfo, true);
        funcstate->AddInstruction(_OP_RETURN, -1);
		funcstate->SetStackSize(0);

		SQFunctionProto *func = funcstate->BuildProto();
#ifdef _DEBUG_DUMP
		funcstate->Dump(func);
#endif
		_fs = currchunk;
		_fs->_functions.push_back(func);
		_fs->PopChildState();
	}
	void ResolveBreaks(SQFuncState *funcstate, SQInteger ntoresolve)
	{
		while(ntoresolve > 0) {
			SQInteger pos = funcstate->_unresolvedbreaks.back();
			funcstate->_unresolvedbreaks.pop_back();
			//set the jmp instruction
			funcstate->SetIntructionParams(pos, 0, funcstate->GetCurrentPos() - pos, 0);
			ntoresolve--;
		}
	}
	void ResolveContinues(SQFuncState *funcstate, SQInteger ntoresolve, SQInteger targetpos)
	{
		while(ntoresolve > 0) {
			SQInteger pos = funcstate->_unresolvedcontinues.back();
			funcstate->_unresolvedcontinues.pop_back();
			//set the jmp instruction
			funcstate->SetIntructionParams(pos, 0, targetpos - pos, 0);
			ntoresolve--;
		}
	}
private:
	SQInteger _token;
	SQFuncState *_fs;
	SQObjectPtr _sourcename;
	SQLexer _lex;
	bool _lineinfo;
	bool _raiseerror;
	SQInteger _debugline;
	SQInteger _debugop;
	SQExpState   _es;
	SQScope _scope;
	SQChar *compilererror;
	jmp_buf _errorjmp;
	SQVM *_vm;
};

bool Compile(SQVM *vm,SQLEXREADFUNC rg, SQUserPointer up, const SQChar *sourcename, SQObjectPtr &out, bool raiseerror, bool lineinfo)
{
	SQCompiler p(vm, rg, up, sourcename, raiseerror, lineinfo);
	return p.Compile(out);
}

#endif

// ******************************** sqdebug.cpp ********************************
/*
	see copyright notice in squirrel.h
*/
// ---- #include "sqpcheader.h"
// ---> including sqpcheader.h
// <--- back to sqdebug.cpp
#include <stdarg.h>
// ---- #include "sqvm.h"
// ---> including sqvm.h
// <--- back to sqdebug.cpp
// ---- #include "sqfuncproto.h"
// ---> including sqfuncproto.h
// <--- back to sqdebug.cpp
// ---- #include "sqclosure.h"
// ---> including sqclosure.h
// <--- back to sqdebug.cpp
// ---- #include "sqstring.h"
// ---> including sqstring.h
// <--- back to sqdebug.cpp

SQRESULT sq_getfunctioninfo(HSQUIRRELVM v,SQInteger level,SQFunctionInfo *fi)
{
	SQInteger cssize = v->_callsstacksize;
	if (cssize > level) {
		SQVM::CallInfo &ci = v->_callsstack[cssize-level-1];
		if(sq_isclosure(ci._closure)) {
			SQClosure *c = _closure(ci._closure);
			SQFunctionProto *proto = c->_function;
			fi->funcid = proto;
			fi->name = type(proto->_name) == OT_STRING?_stringval(proto->_name):_SC("unknown");
			fi->source = type(proto->_name) == OT_STRING?_stringval(proto->_sourcename):_SC("unknown");
			return SQ_OK;
		}
	}
	return sq_throwerror(v,_SC("the object is not a closure"));
}

SQRESULT sq_stackinfos(HSQUIRRELVM v, SQInteger level, SQStackInfos *si)
{
	SQInteger cssize = v->_callsstacksize;
	if (cssize > level) {
		memset(si, 0, sizeof(SQStackInfos));
		SQVM::CallInfo &ci = v->_callsstack[cssize-level-1];
		switch (type(ci._closure)) {
		case OT_CLOSURE:{
			SQFunctionProto *func = _closure(ci._closure)->_function;
			if (type(func->_name) == OT_STRING)
				si->funcname = _stringval(func->_name);
			if (type(func->_sourcename) == OT_STRING)
				si->source = _stringval(func->_sourcename);
			si->line = func->GetLine(ci._ip);
						}
			break;
		case OT_NATIVECLOSURE:
			si->source = _SC("NATIVE");
			si->funcname = _SC("unknown");
			if(type(_nativeclosure(ci._closure)->_name) == OT_STRING)
				si->funcname = _stringval(_nativeclosure(ci._closure)->_name);
			si->line = -1;
			break;
		default: break; //shutup compiler
		}
		return SQ_OK;
	}
	return SQ_ERROR;
}

void SQVM::Raise_Error(const SQChar *s, ...)
{
	va_list vl;
	va_start(vl, s);
	scvsprintf(_sp(rsl((SQInteger)scstrlen(s)+(NUMBER_MAX_CHAR*2))), s, vl);
	va_end(vl);
	_lasterror = SQString::Create(_ss(this),_spval,-1);
}

void SQVM::Raise_Error(const SQObjectPtr &desc)
{
	_lasterror = desc;
}

SQString *SQVM::PrintObjVal(const SQObjectPtr &o)
{
	switch(type(o)) {
	case OT_STRING: return _string(o);
	case OT_INTEGER:
		scsprintf(_sp(rsl(NUMBER_MAX_CHAR+1)), _PRINT_INT_FMT, _integer(o));
		return SQString::Create(_ss(this), _spval);
		break;
	case OT_FLOAT:
		scsprintf(_sp(rsl(NUMBER_MAX_CHAR+1)), _SC("%.14g"), _float(o));
		return SQString::Create(_ss(this), _spval);
		break;
	default:
		return SQString::Create(_ss(this), GetTypeName(o));
	}
}

void SQVM::Raise_IdxError(const SQObjectPtr &o)
{
	SQObjectPtr oval = PrintObjVal(o);
	Raise_Error(_SC("the index '%.50s' does not exist"), _stringval(oval));
}

void SQVM::Raise_CompareError(const SQObject &o1, const SQObject &o2)
{
	SQObjectPtr oval1 = PrintObjVal(o1), oval2 = PrintObjVal(o2);
	Raise_Error(_SC("comparison between '%.50s' and '%.50s'"), _stringval(oval1), _stringval(oval2));
}


void SQVM::Raise_ParamTypeError(SQInteger nparam,SQInteger typemask,SQInteger type)
{
	SQObjectPtr exptypes = SQString::Create(_ss(this), _SC(""), -1);
	SQInteger found = 0;	
	for(SQInteger i=0; i<16; i++)
	{
		SQInteger mask = 0x00000001 << i;
		if(typemask & (mask)) {
			if(found>0) StringCat(exptypes,SQString::Create(_ss(this), _SC("|"), -1), exptypes);
			found ++;
			StringCat(exptypes,SQString::Create(_ss(this), IdType2Name((SQObjectType)mask), -1), exptypes);
		}
	}
	Raise_Error(_SC("parameter %d has an invalid type '%s' ; expected: '%s'"), nparam, IdType2Name((SQObjectType)type), _stringval(exptypes));
}

// ******************************** sqfuncstate.cpp ********************************
/*
	see copyright notice in squirrel.h
*/
// ---- #include "sqpcheader.h"
// ---> including sqpcheader.h
// <--- back to sqfuncstate.cpp
#ifndef NO_COMPILER
// ---- #include "sqcompiler.h"
// ---> including sqcompiler.h
// <--- back to sqfuncstate.cpp
// ---- #include "sqstring.h"
// ---> including sqstring.h
// <--- back to sqfuncstate.cpp
// ---- #include "sqfuncproto.h"
// ---> including sqfuncproto.h
// <--- back to sqfuncstate.cpp
// ---- #include "sqtable.h"
// ---> including sqtable.h
// <--- back to sqfuncstate.cpp
// ---- #include "sqopcodes.h"
// ---> including sqopcodes.h
// <--- back to sqfuncstate.cpp
// ---- #include "sqfuncstate.h"
// ---> including sqfuncstate.h
// <--- back to sqfuncstate.cpp

#ifdef _DEBUG_DUMP
SQInstructionDesc g_InstrDesc[]={
	{_SC("_OP_LINE")},
	{_SC("_OP_LOAD")},
	{_SC("_OP_LOADINT")},
	{_SC("_OP_LOADFLOAT")},
	{_SC("_OP_DLOAD")},
	{_SC("_OP_TAILCALL")},
	{_SC("_OP_CALL")},
	{_SC("_OP_PREPCALL")},
	{_SC("_OP_PREPCALLK")},
	{_SC("_OP_GETK")},
	{_SC("_OP_MOVE")},
	{_SC("_OP_NEWSLOT")},
	{_SC("_OP_DELETE")},
	{_SC("_OP_SET")},
	{_SC("_OP_GET")},
	{_SC("_OP_EQ")},
	{_SC("_OP_NE")},
	{_SC("_OP_ADD")},
	{_SC("_OP_SUB")},
	{_SC("_OP_MUL")},
	{_SC("_OP_DIV")},
	{_SC("_OP_MOD")},
	{_SC("_OP_BITW")},
	{_SC("_OP_RETURN")},
	{_SC("_OP_LOADNULLS")},
	{_SC("_OP_LOADROOT")},
	{_SC("_OP_LOADBOOL")},
	{_SC("_OP_DMOVE")},
	{_SC("_OP_JMP")},
	{_SC("_OP_JCMP")},
	{_SC("_OP_JZ")},
	{_SC("_OP_SETOUTER")},
	{_SC("_OP_GETOUTER")},
	{_SC("_OP_NEWOBJ")},
	{_SC("_OP_APPENDARRAY")},
	{_SC("_OP_COMPARITH")},
	{_SC("_OP_INC")},
	{_SC("_OP_INCL")},
	{_SC("_OP_PINC")},
	{_SC("_OP_PINCL")},
	{_SC("_OP_CMP")},
	{_SC("_OP_EXISTS")},
	{_SC("_OP_INSTANCEOF")},
	{_SC("_OP_AND")},
	{_SC("_OP_OR")},
	{_SC("_OP_NEG")},
	{_SC("_OP_NOT")},
	{_SC("_OP_BWNOT")},
	{_SC("_OP_CLOSURE")},
	{_SC("_OP_YIELD")},
	{_SC("_OP_RESUME")},
	{_SC("_OP_FOREACH")},
	{_SC("_OP_POSTFOREACH")},
	{_SC("_OP_CLONE")},
	{_SC("_OP_TYPEOF")},
	{_SC("_OP_PUSHTRAP")},
	{_SC("_OP_POPTRAP")},
	{_SC("_OP_THROW")},
	{_SC("_OP_NEWSLOTA")},
	{_SC("_OP_GETBASE")},
	{_SC("_OP_CLOSE")},
	{_SC("_OP_JCMP")}
};
#endif
void DumpLiteral(SQObjectPtr &o)
{
	switch(type(o)){
		case OT_STRING:	scprintf(_SC("\"%s\""),_stringval(o));break;
		case OT_FLOAT: scprintf(_SC("{%f}"),_float(o));break;
		case OT_INTEGER: scprintf(_SC("{") _PRINT_INT_FMT _SC("}"),_integer(o));break;
		case OT_BOOL: scprintf(_SC("%s"),_integer(o)?_SC("true"):_SC("false"));break;
		default: scprintf(_SC("(%s %p)"),GetTypeName(o),(void*)_rawval(o));break; break; //shut up compiler
	}
}

SQFuncState::SQFuncState(SQSharedState *ss,SQFuncState *parent,CompilerErrorFunc efunc,void *ed)
{
		_nliterals = 0;
		_literals = SQTable::Create(ss,0);
		_strings =  SQTable::Create(ss,0);
		_sharedstate = ss;
		_lastline = 0;
		_optimization = true;
		_parent = parent;
		_stacksize = 0;
		_traps = 0;
		_returnexp = 0;
		_varparams = false;
		_errfunc = efunc;
		_errtarget = ed;
		_bgenerator = false;
		_outers = 0;
		_ss = ss;

}

void SQFuncState::Error(const SQChar *err)
{
	_errfunc(_errtarget,err);
}

#ifdef _DEBUG_DUMP
void SQFuncState::Dump(SQFunctionProto *func)
{
	SQUnsignedInteger n=0,i;
	SQInteger si;
	scprintf(_SC("SQInstruction sizeof %d\n"),sizeof(SQInstruction));
	scprintf(_SC("SQObject sizeof %d\n"),sizeof(SQObject));
	scprintf(_SC("--------------------------------------------------------------------\n"));
	scprintf(_SC("*****FUNCTION [%s]\n"),type(func->_name)==OT_STRING?_stringval(func->_name):_SC("unknown"));
	scprintf(_SC("-----LITERALS\n"));
	SQObjectPtr refidx,key,val;
	SQInteger idx;
	SQObjectPtrVec templiterals;
	templiterals.resize(_nliterals);
	while((idx=_table(_literals)->Next(false,refidx,key,val))!=-1) {
		refidx=idx;
		templiterals[_integer(val)]=key;
	}
	for(i=0;i<templiterals.size();i++){
		scprintf(_SC("[%d] "),n);
		DumpLiteral(templiterals[i]);
		scprintf(_SC("\n"));
		n++;
	}
	scprintf(_SC("-----PARAMS\n"));
	if(_varparams)
		scprintf(_SC("<<VARPARAMS>>\n"));
	n=0;
	for(i=0;i<_parameters.size();i++){
		scprintf(_SC("[%d] "),n);
		DumpLiteral(_parameters[i]);
		scprintf(_SC("\n"));
		n++;
	}
	scprintf(_SC("-----LOCALS\n"));
	for(si=0;si<func->_nlocalvarinfos;si++){
		SQLocalVarInfo lvi=func->_localvarinfos[si];
		scprintf(_SC("[%d] %s \t%d %d\n"),lvi._pos,_stringval(lvi._name),lvi._start_op,lvi._end_op);
		n++;
	}
	scprintf(_SC("-----LINE INFO\n"));
	for(i=0;i<_lineinfos.size();i++){
		SQLineInfo li=_lineinfos[i];
		scprintf(_SC("op [%d] line [%d] \n"),li._op,li._line);
		n++;
	}
	scprintf(_SC("-----dump\n"));
	n=0;
	for(i=0;i<_instructions.size();i++){
		SQInstruction &inst=_instructions[i];
		if(inst.op==_OP_LOAD || inst.op==_OP_DLOAD || inst.op==_OP_PREPCALLK || inst.op==_OP_GETK ){
			
			SQInteger lidx = inst._arg1;
			scprintf(_SC("[%03d] %15s %d "),n,g_InstrDesc[inst.op].name,inst._arg0);
			if(lidx >= 0xFFFFFFFF)
				scprintf(_SC("null"));
			else {
				SQInteger refidx;
				SQObjectPtr val,key,refo;
				while(((refidx=_table(_literals)->Next(false,refo,key,val))!= -1) && (_integer(val) != lidx)) {
					refo = refidx;	
				}
				DumpLiteral(key);
			}
			if(inst.op != _OP_DLOAD) {
				scprintf(_SC(" %d %d \n"),inst._arg2,inst._arg3);
			}
			else {
				scprintf(_SC(" %d "),inst._arg2);
				lidx = inst._arg3;
				if(lidx >= 0xFFFFFFFF)
					scprintf(_SC("null"));
				else {
					SQInteger refidx;
					SQObjectPtr val,key,refo;
					while(((refidx=_table(_literals)->Next(false,refo,key,val))!= -1) && (_integer(val) != lidx)) {
						refo = refidx;	
				}
				DumpLiteral(key);
				scprintf(_SC("\n"));
			}
			}
		}
		else if(inst.op==_OP_LOADFLOAT) {
			scprintf(_SC("[%03d] %15s %d %f %d %d\n"),n,g_InstrDesc[inst.op].name,inst._arg0,*((SQFloat*)&inst._arg1),inst._arg2,inst._arg3);
		}
	/*	else if(inst.op==_OP_ARITH){
			scprintf(_SC("[%03d] %15s %d %d %d %c\n"),n,g_InstrDesc[inst.op].name,inst._arg0,inst._arg1,inst._arg2,inst._arg3);
		}*/
		else {
			scprintf(_SC("[%03d] %15s %d %d %d %d\n"),n,g_InstrDesc[inst.op].name,inst._arg0,inst._arg1,inst._arg2,inst._arg3);
		}
		n++;
	}
	scprintf(_SC("-----\n"));
	scprintf(_SC("stack size[%d]\n"),func->_stacksize);
	scprintf(_SC("--------------------------------------------------------------------\n\n"));
}
#endif

SQInteger SQFuncState::GetNumericConstant(const SQInteger cons)
{
	return GetConstant(SQObjectPtr(cons));
}

SQInteger SQFuncState::GetNumericConstant(const SQFloat cons)
{
	return GetConstant(SQObjectPtr(cons));
}

SQInteger SQFuncState::GetConstant(const SQObject &cons)
{
	SQObjectPtr val;
	if(!_table(_literals)->Get(cons,val))
	{
		val = _nliterals;
		_table(_literals)->NewSlot(cons,val);
		_nliterals++;
		if(_nliterals > MAX_LITERALS) {
			val.Null();
			Error(_SC("internal compiler error: too many literals"));
		}
	}
	return _integer(val);
}

void SQFuncState::SetIntructionParams(SQInteger pos,SQInteger arg0,SQInteger arg1,SQInteger arg2,SQInteger arg3)
{
	_instructions[pos]._arg0=(unsigned char)*((SQUnsignedInteger *)&arg0);
	_instructions[pos]._arg1=(SQInt32)*((SQUnsignedInteger *)&arg1);
	_instructions[pos]._arg2=(unsigned char)*((SQUnsignedInteger *)&arg2);
	_instructions[pos]._arg3=(unsigned char)*((SQUnsignedInteger *)&arg3);
}

void SQFuncState::SetIntructionParam(SQInteger pos,SQInteger arg,SQInteger val)
{
	switch(arg){
		case 0:_instructions[pos]._arg0=(unsigned char)*((SQUnsignedInteger *)&val);break;
		case 1:case 4:_instructions[pos]._arg1=(SQInt32)*((SQUnsignedInteger *)&val);break;
		case 2:_instructions[pos]._arg2=(unsigned char)*((SQUnsignedInteger *)&val);break;
		case 3:_instructions[pos]._arg3=(unsigned char)*((SQUnsignedInteger *)&val);break;
	};
}

SQInteger SQFuncState::AllocStackPos()
{
	SQInteger npos=_vlocals.size();
	_vlocals.push_back(SQLocalVarInfo());
	if(_vlocals.size()>((SQUnsignedInteger)_stacksize)) {
		if(_stacksize>MAX_FUNC_STACKSIZE) Error(_SC("internal compiler error: too many locals"));
		_stacksize=_vlocals.size();
	}
	return npos;
}

SQInteger SQFuncState::PushTarget(SQInteger n)
{
	if(n!=-1){
		_targetstack.push_back(n);
		return n;
	}
	n=AllocStackPos();
	_targetstack.push_back(n);
	return n;
}

SQInteger SQFuncState::GetUpTarget(SQInteger n){
	return _targetstack[((_targetstack.size()-1)-n)];
}

SQInteger SQFuncState::TopTarget(){
	return _targetstack.back();
}
SQInteger SQFuncState::PopTarget()
{
	SQUnsignedInteger npos=_targetstack.back();
	assert(npos < _vlocals.size());
	SQLocalVarInfo &t = _vlocals[npos];
	if(type(t._name)==OT_NULL){
		_vlocals.pop_back();
	}
	_targetstack.pop_back();
	return npos;
}

SQInteger SQFuncState::GetStackSize()
{
	return _vlocals.size();
}

SQInteger SQFuncState::CountOuters(SQInteger stacksize)
{
	SQInteger outers = 0;
	SQInteger k = _vlocals.size() - 1;
	while(k >= stacksize) {
		SQLocalVarInfo &lvi = _vlocals[k];
		k--;
		if(lvi._end_op == UINT_MINUS_ONE) { //this means is an outer
			outers++;
		}
	}
	return outers;
}

void SQFuncState::SetStackSize(SQInteger n)
{
	SQInteger size=_vlocals.size();
	while(size>n){
		size--;
		SQLocalVarInfo lvi = _vlocals.back();
		if(type(lvi._name)!=OT_NULL){
			if(lvi._end_op == UINT_MINUS_ONE) { //this means is an outer
				_outers--;
			}
			lvi._end_op = GetCurrentPos();
			_localvarinfos.push_back(lvi);
		}
		_vlocals.pop_back();
	}
}

bool SQFuncState::IsConstant(const SQObject &name,SQObject &e)
{
	SQObjectPtr val;
	if(_table(_sharedstate->_consts)->Get(name,val)) {
		e = val;
		return true;
	}
	return false;
}

bool SQFuncState::IsLocal(SQUnsignedInteger stkpos)
{
	if(stkpos>=_vlocals.size())return false;
	else if(type(_vlocals[stkpos]._name)!=OT_NULL)return true;
	return false;
}

SQInteger SQFuncState::PushLocalVariable(const SQObject &name)
{
	SQInteger pos=_vlocals.size();
	SQLocalVarInfo lvi;
	lvi._name=name;
	lvi._start_op=GetCurrentPos()+1;
	lvi._pos=_vlocals.size();
	_vlocals.push_back(lvi);
	if(_vlocals.size()>((SQUnsignedInteger)_stacksize))_stacksize=_vlocals.size();
	return pos;
}



SQInteger SQFuncState::GetLocalVariable(const SQObject &name)
{
	SQInteger locals=_vlocals.size();
	while(locals>=1){
		SQLocalVarInfo &lvi = _vlocals[locals-1];
		if(type(lvi._name)==OT_STRING && _string(lvi._name)==_string(name)){
			return locals-1;
		}
		locals--;
	}
	return -1;
}

void SQFuncState::MarkLocalAsOuter(SQInteger pos)
{
	SQLocalVarInfo &lvi = _vlocals[pos];
	lvi._end_op = UINT_MINUS_ONE;
	_outers++;
}

SQInteger SQFuncState::GetOuterVariable(const SQObject &name)
{
	SQInteger outers = _outervalues.size();
	for(SQInteger i = 0; i<outers; i++) {
		if(_string(_outervalues[i]._name) == _string(name))
			return i;
	}
	SQInteger pos=-1;
	if(_parent) { 
		pos = _parent->GetLocalVariable(name);
		if(pos == -1) {
			pos = _parent->GetOuterVariable(name);
			if(pos != -1) {
				_outervalues.push_back(SQOuterVar(name,SQObjectPtr(SQInteger(pos)),otOUTER)); //local
				return _outervalues.size() - 1;	
			}
		}
		else {
			_parent->MarkLocalAsOuter(pos);
			_outervalues.push_back(SQOuterVar(name,SQObjectPtr(SQInteger(pos)),otLOCAL)); //local
			return _outervalues.size() - 1;
			
			
		}
	}
	return -1;
}

void SQFuncState::AddParameter(const SQObject &name)
{
	PushLocalVariable(name);
	_parameters.push_back(name);
}

void SQFuncState::AddLineInfos(SQInteger line,bool lineop,bool force)
{
	if(_lastline!=line || force){
		SQLineInfo li;
		li._line=line;li._op=(GetCurrentPos()+1);
		if(lineop)AddInstruction(_OP_LINE,0,line);
		if(_lastline!=line) {
			_lineinfos.push_back(li);
		}
		_lastline=line;
	}
}

void SQFuncState::DiscardTarget()
{
	SQInteger discardedtarget = PopTarget();
	SQInteger size = _instructions.size();
	if(size > 0 && _optimization){
		SQInstruction &pi = _instructions[size-1];//previous instruction
		switch(pi.op) {
		case _OP_SET:case _OP_NEWSLOT:case _OP_SETOUTER:case _OP_CALL:
			if(pi._arg0 == discardedtarget) {
				pi._arg0 = 0xFF;
			}
		}
	}
}

void SQFuncState::AddInstruction(SQInstruction &i)
{
	SQInteger size = _instructions.size();
	if(size > 0 && _optimization){ //simple optimizer
		SQInstruction &pi = _instructions[size-1];//previous instruction
		switch(i.op) {
		case _OP_JZ:
			if( pi.op == _OP_CMP && pi._arg1 < 0xFF) {
				pi.op = _OP_JCMP;
				pi._arg0 = (unsigned char)pi._arg1;
				pi._arg1 = i._arg1;
				return;
			}
		case _OP_SET:
		case _OP_NEWSLOT:
			if(i._arg0 == i._arg3) {
				i._arg0 = 0xFF;
			}
			break;
		case _OP_SETOUTER:
			if(i._arg0 == i._arg2) {
				i._arg0 = 0xFF;
			}
			break;
		case _OP_RETURN:
			if( _parent && i._arg0 != MAX_FUNC_STACKSIZE && pi.op == _OP_CALL && _returnexp < size-1) {
				pi.op = _OP_TAILCALL;
			} else if(pi.op == _OP_CLOSE){
				pi = i;
				return;
			}
		break;
		case _OP_GET:
			if( pi.op == _OP_LOAD && pi._arg0 == i._arg2 && (!IsLocal(pi._arg0))){
				pi._arg1 = pi._arg1;
				pi._arg2 = (unsigned char)i._arg1;
				pi.op = _OP_GETK;
				pi._arg0 = i._arg0;
				
				return;
			}
		break;
		case _OP_PREPCALL:
			if( pi.op == _OP_LOAD  && pi._arg0 == i._arg1 && (!IsLocal(pi._arg0))){
				pi.op = _OP_PREPCALLK;
				pi._arg0 = i._arg0;
				pi._arg1 = pi._arg1;
				pi._arg2 = i._arg2;
				pi._arg3 = i._arg3;
				return;
			}
			break;
		case _OP_APPENDARRAY: {
			SQInteger aat = -1;
			switch(pi.op) {
			case _OP_LOAD: aat = AAT_LITERAL; break;
			case _OP_LOADINT: aat = AAT_INT; break;
			case _OP_LOADBOOL: aat = AAT_BOOL; break;
			case _OP_LOADFLOAT: aat = AAT_FLOAT; break;
			default: break;
			}
			if(aat != -1 && pi._arg0 == i._arg1 && (!IsLocal(pi._arg0))){
				pi.op = _OP_APPENDARRAY;
				pi._arg0 = i._arg0;
				pi._arg1 = pi._arg1;
				pi._arg2 = (unsigned char)aat;
				pi._arg3 = MAX_FUNC_STACKSIZE;
				return;
			}
							  }
			break;
		case _OP_MOVE:
			switch(pi.op) {
			case _OP_GET: case _OP_ADD: case _OP_SUB: case _OP_MUL: case _OP_DIV: case _OP_MOD: case _OP_BITW:
			case _OP_LOADINT: case _OP_LOADFLOAT: case _OP_LOADBOOL: case _OP_LOAD:

				if(pi._arg0 == i._arg1)
				{
					pi._arg0 = i._arg0;
					_optimization = false;
					//_result_elimination = false;
					return;
				}
			}

			if(pi.op == _OP_MOVE)
			{
				pi.op = _OP_DMOVE;
				pi._arg2 = i._arg0;
				pi._arg3 = (unsigned char)i._arg1;
				return;
			}
			break;
		case _OP_LOAD:
			if(pi.op == _OP_LOAD && i._arg1 < 256) {
				pi.op = _OP_DLOAD;
				pi._arg2 = i._arg0;
				pi._arg3 = (unsigned char)i._arg1;
				return;
			}
			break;
		case _OP_EQ:case _OP_NE:
			if(pi.op == _OP_LOAD && pi._arg0 == i._arg1 && (!IsLocal(pi._arg0) ))
			{
				pi.op = i.op;
				pi._arg0 = i._arg0;
				pi._arg1 = pi._arg1;
				pi._arg2 = i._arg2;
				pi._arg3 = MAX_FUNC_STACKSIZE;
				return;
			}
			break;
		case _OP_LOADNULLS:
			if((pi.op == _OP_LOADNULLS && pi._arg0+pi._arg1 == i._arg0)) {
				
				pi._arg1 = pi._arg1 + 1;
				pi.op = _OP_LOADNULLS;
				return;
			}
            break;
		case _OP_LINE:
			if(pi.op == _OP_LINE) {
				_instructions.pop_back();
				_lineinfos.pop_back();
			}
			break;
		}
	}
	_optimization = true;
	_instructions.push_back(i);
}

SQObject SQFuncState::CreateString(const SQChar *s,SQInteger len)
{
	SQObjectPtr ns(SQString::Create(_sharedstate,s,len));
	_table(_strings)->NewSlot(ns,(SQInteger)1);
	return ns;
}

SQObject SQFuncState::CreateTable()
{
	SQObjectPtr nt(SQTable::Create(_sharedstate,0));
	_table(_strings)->NewSlot(nt,(SQInteger)1);
	return nt;
}

SQFunctionProto *SQFuncState::BuildProto()
{
	
	SQFunctionProto *f=SQFunctionProto::Create(_ss,_instructions.size(),
		_nliterals,_parameters.size(),_functions.size(),_outervalues.size(),
		_lineinfos.size(),_localvarinfos.size(),_defaultparams.size());

	SQObjectPtr refidx,key,val;
	SQInteger idx;

	f->_stacksize = _stacksize;
	f->_sourcename = _sourcename;
	f->_bgenerator = _bgenerator;
	f->_name = _name;

	while((idx=_table(_literals)->Next(false,refidx,key,val))!=-1) {
		f->_literals[_integer(val)]=key;
		refidx=idx;
	}

	for(SQUnsignedInteger nf = 0; nf < _functions.size(); nf++) f->_functions[nf] = _functions[nf];
	for(SQUnsignedInteger np = 0; np < _parameters.size(); np++) f->_parameters[np] = _parameters[np];
	for(SQUnsignedInteger no = 0; no < _outervalues.size(); no++) f->_outervalues[no] = _outervalues[no];
	for(SQUnsignedInteger nl = 0; nl < _localvarinfos.size(); nl++) f->_localvarinfos[nl] = _localvarinfos[nl];
	for(SQUnsignedInteger ni = 0; ni < _lineinfos.size(); ni++) f->_lineinfos[ni] = _lineinfos[ni];
	for(SQUnsignedInteger nd = 0; nd < _defaultparams.size(); nd++) f->_defaultparams[nd] = _defaultparams[nd];

	memcpy(f->_instructions,&_instructions[0],_instructions.size()*sizeof(SQInstruction));

	f->_varparams = _varparams;

	return f;
}

SQFuncState *SQFuncState::PushChildState(SQSharedState *ss)
{
	SQFuncState *child = (SQFuncState *)sq_malloc(sizeof(SQFuncState));
	new (child) SQFuncState(ss,this,_errfunc,_errtarget);
	_childstates.push_back(child);
	return child;
}

void SQFuncState::PopChildState()
{
	SQFuncState *child = _childstates.back();
	sq_delete(child,SQFuncState);
	_childstates.pop_back();
}

SQFuncState::~SQFuncState()
{
	while(_childstates.size() > 0)
	{
		PopChildState();
	}
}

#endif

// ******************************** sqlexer.cpp ********************************
/*
	see copyright notice in squirrel.h
*/
// ---- #include "sqpcheader.h"
// ---> including sqpcheader.h
// <--- back to sqlexer.cpp
#include <ctype.h>
#include <stdlib.h>
// ---- #include "sqtable.h"
// ---> including sqtable.h
// <--- back to sqlexer.cpp
// ---- #include "sqstring.h"
// ---> including sqstring.h
// <--- back to sqlexer.cpp
// ---- #include "sqcompiler.h"
// ---> including sqcompiler.h
// <--- back to sqlexer.cpp
// ---- #include "sqlexer.h"
// ---> including sqlexer.h
// <--- back to sqlexer.cpp

#define CUR_CHAR (_currdata)
#define RETURN_TOKEN(t) { _prevtoken = _curtoken; _curtoken = t; return t;}
#define IS_EOB() (CUR_CHAR <= SQUIRREL_EOB)
#define NEXT() {Next();_currentcolumn++;}
#define INIT_TEMP_STRING() { _longstr.resize(0);}
#define APPEND_CHAR(c) { _longstr.push_back(c);}
#define TERMINATE_BUFFER() {_longstr.push_back(_SC('\0'));}
#define ADD_KEYWORD(key,id) _keywords->NewSlot( SQString::Create(ss, _SC(#key)) ,SQInteger(id))

SQLexer::SQLexer(){}
SQLexer::~SQLexer()
{
	_keywords->Release();
}

void SQLexer::Init(SQSharedState *ss, SQLEXREADFUNC rg, SQUserPointer up,CompilerErrorFunc efunc,void *ed)
{
	_errfunc = efunc;
	_errtarget = ed;
	_sharedstate = ss;
	_keywords = SQTable::Create(ss, 26);
	ADD_KEYWORD(while, TK_WHILE);
	ADD_KEYWORD(do, TK_DO);
	ADD_KEYWORD(if, TK_IF);
	ADD_KEYWORD(else, TK_ELSE);
	ADD_KEYWORD(break, TK_BREAK);
	ADD_KEYWORD(continue, TK_CONTINUE);
	ADD_KEYWORD(return, TK_RETURN);
	ADD_KEYWORD(null, TK_NULL);
	ADD_KEYWORD(function, TK_FUNCTION);
	ADD_KEYWORD(local, TK_LOCAL);
	ADD_KEYWORD(for, TK_FOR);
	ADD_KEYWORD(foreach, TK_FOREACH);
	ADD_KEYWORD(in, TK_IN);
	ADD_KEYWORD(typeof, TK_TYPEOF);
	ADD_KEYWORD(base, TK_BASE);
	ADD_KEYWORD(delete, TK_DELETE);
	ADD_KEYWORD(try, TK_TRY);
	ADD_KEYWORD(catch, TK_CATCH);
	ADD_KEYWORD(throw, TK_THROW);
	ADD_KEYWORD(clone, TK_CLONE);
	ADD_KEYWORD(yield, TK_YIELD);
	ADD_KEYWORD(resume, TK_RESUME);
	ADD_KEYWORD(switch, TK_SWITCH);
	ADD_KEYWORD(case, TK_CASE);
	ADD_KEYWORD(default, TK_DEFAULT);
	ADD_KEYWORD(this, TK_THIS);
	ADD_KEYWORD(class,TK_CLASS);
	ADD_KEYWORD(extends,TK_EXTENDS);
	ADD_KEYWORD(constructor,TK_CONSTRUCTOR);
	ADD_KEYWORD(instanceof,TK_INSTANCEOF);
	ADD_KEYWORD(true,TK_TRUE);
	ADD_KEYWORD(false,TK_FALSE);
	ADD_KEYWORD(static,TK_STATIC);
	ADD_KEYWORD(enum,TK_ENUM);
	ADD_KEYWORD(const,TK_CONST);

	_readf = rg;
	_up = up;
	_lasttokenline = _currentline = 1;
	_currentcolumn = 0;
	_prevtoken = -1;
	_reached_eof = SQFalse;
	Next();
}

void SQLexer::Error(const SQChar *err)
{
	_errfunc(_errtarget,err);
}

void SQLexer::Next()
{
	SQInteger t = _readf(_up);
	if(t > MAX_CHAR) Error(_SC("Invalid character"));
	if(t != 0) {
		_currdata = (LexChar)t;
		return;
	}
	_currdata = SQUIRREL_EOB;
	_reached_eof = SQTrue;
}

const SQChar *SQLexer::Tok2Str(SQInteger tok)
{
	SQObjectPtr itr, key, val;
	SQInteger nitr;
	while((nitr = _keywords->Next(false,itr, key, val)) != -1) {
		itr = (SQInteger)nitr;
		if(((SQInteger)_integer(val)) == tok)
			return _stringval(key);
	}
	return NULL;
}

void SQLexer::LexBlockComment()
{
	bool done = false;
	while(!done) {
		switch(CUR_CHAR) {
			case _SC('*'): { NEXT(); if(CUR_CHAR == _SC('/')) { done = true; NEXT(); }}; continue;
			case _SC('\n'): _currentline++; NEXT(); continue;
			case SQUIRREL_EOB: Error(_SC("missing \"*/\" in comment"));
			default: NEXT();
		}
	}
}
void SQLexer::LexLineComment()
{
	do { NEXT(); } while (CUR_CHAR != _SC('\n') && (!IS_EOB()));
}

SQInteger SQLexer::Lex()
{
	_lasttokenline = _currentline;
	while(CUR_CHAR != SQUIRREL_EOB) {
		switch(CUR_CHAR){
		case _SC('\t'): case _SC('\r'): case _SC(' '): NEXT(); continue;
		case _SC('\n'):
			_currentline++;
			_prevtoken=_curtoken;
			_curtoken=_SC('\n');
			NEXT();
			_currentcolumn=1;
			continue;
		case _SC('#'): LexLineComment(); continue;
		case _SC('/'):
			NEXT();
			switch(CUR_CHAR){
			case _SC('*'):
				NEXT();
				LexBlockComment();
				continue;	
			case _SC('/'):
				LexLineComment();
				continue;
			case _SC('='):
				NEXT();
				RETURN_TOKEN(TK_DIVEQ);
				continue;
			case _SC('>'):
				NEXT();
				RETURN_TOKEN(TK_ATTR_CLOSE);
				continue;
			default:
				RETURN_TOKEN('/');
			}
		case _SC('='):
			NEXT();
			if (CUR_CHAR != _SC('=')){ RETURN_TOKEN('=') }
			else { NEXT(); RETURN_TOKEN(TK_EQ); }
		case _SC('<'):
			NEXT();
			switch(CUR_CHAR) {
			case _SC('='):
				NEXT(); 
				if(CUR_CHAR == _SC('>')) {
					NEXT();
					RETURN_TOKEN(TK_3WAYSCMP); 
				}
				RETURN_TOKEN(TK_LE) 
				break;
			case _SC('-'): NEXT(); RETURN_TOKEN(TK_NEWSLOT); break;
			case _SC('<'): NEXT(); RETURN_TOKEN(TK_SHIFTL); break;
			case _SC('/'): NEXT(); RETURN_TOKEN(TK_ATTR_OPEN); break;
			}
			RETURN_TOKEN('<');
		case _SC('>'):
			NEXT();
			if (CUR_CHAR == _SC('=')){ NEXT(); RETURN_TOKEN(TK_GE);}
			else if(CUR_CHAR == _SC('>')){ 
				NEXT(); 
				if(CUR_CHAR == _SC('>')){
					NEXT();
					RETURN_TOKEN(TK_USHIFTR);
				}
				RETURN_TOKEN(TK_SHIFTR);
			}
			else { RETURN_TOKEN('>') }
		case _SC('!'):
			NEXT();
			if (CUR_CHAR != _SC('=')){ RETURN_TOKEN('!')}
			else { NEXT(); RETURN_TOKEN(TK_NE); }
		case _SC('@'): {
			SQInteger stype;
			NEXT();
			if(CUR_CHAR != _SC('"')) {
				RETURN_TOKEN('@');
			}
			if((stype=ReadString('"',true))!=-1) {
				RETURN_TOKEN(stype);
			}
			Error(_SC("error parsing the string"));
					   }
		case _SC('"'):
		case _SC('\''): {
			SQInteger stype;
			if((stype=ReadString(CUR_CHAR,false))!=-1){
				RETURN_TOKEN(stype);
			}
			Error(_SC("error parsing the string"));
			}
		case _SC('{'): case _SC('}'): case _SC('('): case _SC(')'): case _SC('['): case _SC(']'):
		case _SC(';'): case _SC(','): case _SC('?'): case _SC('^'): case _SC('~'):
			{SQInteger ret = CUR_CHAR;
			NEXT(); RETURN_TOKEN(ret); }
		case _SC('.'):
			NEXT();
			if (CUR_CHAR != _SC('.')){ RETURN_TOKEN('.') }
			NEXT();
			if (CUR_CHAR != _SC('.')){ Error(_SC("invalid token '..'")); }
			NEXT();
			RETURN_TOKEN(TK_VARPARAMS);
		case _SC('&'):
			NEXT();
			if (CUR_CHAR != _SC('&')){ RETURN_TOKEN('&') }
			else { NEXT(); RETURN_TOKEN(TK_AND); }
		case _SC('|'):
			NEXT();
			if (CUR_CHAR != _SC('|')){ RETURN_TOKEN('|') }
			else { NEXT(); RETURN_TOKEN(TK_OR); }
		case _SC(':'):
			NEXT();
			if (CUR_CHAR != _SC(':')){ RETURN_TOKEN(':') }
			else { NEXT(); RETURN_TOKEN(TK_DOUBLE_COLON); }
		case _SC('*'):
			NEXT();
			if (CUR_CHAR == _SC('=')){ NEXT(); RETURN_TOKEN(TK_MULEQ);}
			else RETURN_TOKEN('*');
		case _SC('%'):
			NEXT();
			if (CUR_CHAR == _SC('=')){ NEXT(); RETURN_TOKEN(TK_MODEQ);}
			else RETURN_TOKEN('%');
		case _SC('-'):
			NEXT();
			if (CUR_CHAR == _SC('=')){ NEXT(); RETURN_TOKEN(TK_MINUSEQ);}
			else if  (CUR_CHAR == _SC('-')){ NEXT(); RETURN_TOKEN(TK_MINUSMINUS);}
			else RETURN_TOKEN('-');
		case _SC('+'):
			NEXT();
			if (CUR_CHAR == _SC('=')){ NEXT(); RETURN_TOKEN(TK_PLUSEQ);}
			else if (CUR_CHAR == _SC('+')){ NEXT(); RETURN_TOKEN(TK_PLUSPLUS);}
			else RETURN_TOKEN('+');
		case SQUIRREL_EOB:
			return 0;
		default:{
				if (scisdigit(CUR_CHAR)) {
					SQInteger ret = ReadNumber();
					RETURN_TOKEN(ret);
				}
				else if (scisalpha(CUR_CHAR) || CUR_CHAR == _SC('_')) {
					SQInteger t = ReadID();
					RETURN_TOKEN(t);
				}
				else {
					SQInteger c = CUR_CHAR;
					if (sciscntrl((int)c)) Error(_SC("unexpected character(control)"));
					NEXT();
					RETURN_TOKEN(c);  
				}
				RETURN_TOKEN(0);
			}
		}
	}
	return 0;    
}
	
SQInteger SQLexer::GetIDType(SQChar *s)
{
	SQObjectPtr t;
	if(_keywords->Get(SQString::Create(_sharedstate, s), t)) {
		return SQInteger(_integer(t));
	}
	return TK_IDENTIFIER;
}


SQInteger SQLexer::ReadString(SQInteger ndelim,bool verbatim)
{
	INIT_TEMP_STRING();
	NEXT();
	if(IS_EOB()) return -1;
	for(;;) {
		while(CUR_CHAR != ndelim) {
			switch(CUR_CHAR) {
			case SQUIRREL_EOB:
				Error(_SC("unfinished string"));
				return -1;
			case _SC('\n'): 
				if(!verbatim) Error(_SC("newline in a constant")); 
				APPEND_CHAR(CUR_CHAR); NEXT(); 
				_currentline++;
				break;
			case _SC('\\'):
				if(verbatim) {
					APPEND_CHAR('\\'); NEXT(); 
				}
				else {
					NEXT();
					switch(CUR_CHAR) {
					case _SC('x'): NEXT(); {
						if(!isxdigit(CUR_CHAR)) Error(_SC("hexadecimal number expected")); 
						const SQInteger maxdigits = 4;
						SQChar temp[maxdigits+1];
						SQInteger n = 0;
						while(isxdigit(CUR_CHAR) && n < maxdigits) {
							temp[n] = CUR_CHAR;
							n++;
							NEXT();
						}
						temp[n] = 0;
						SQChar *sTemp;
						APPEND_CHAR((SQChar)scstrtoul(temp,&sTemp,16));
					}
				    break;
					case _SC('t'): APPEND_CHAR(_SC('\t')); NEXT(); break;
					case _SC('a'): APPEND_CHAR(_SC('\a')); NEXT(); break;
					case _SC('b'): APPEND_CHAR(_SC('\b')); NEXT(); break;
					case _SC('n'): APPEND_CHAR(_SC('\n')); NEXT(); break;
					case _SC('r'): APPEND_CHAR(_SC('\r')); NEXT(); break;
					case _SC('v'): APPEND_CHAR(_SC('\v')); NEXT(); break;
					case _SC('f'): APPEND_CHAR(_SC('\f')); NEXT(); break;
					case _SC('0'): APPEND_CHAR(_SC('\0')); NEXT(); break;
					case _SC('\\'): APPEND_CHAR(_SC('\\')); NEXT(); break;
					case _SC('"'): APPEND_CHAR(_SC('"')); NEXT(); break;
					case _SC('\''): APPEND_CHAR(_SC('\'')); NEXT(); break;
					default:
						Error(_SC("unrecognised escaper char"));
					break;
					}
				}
				break;
			default:
				APPEND_CHAR(CUR_CHAR);
				NEXT();
			}
		}
		NEXT();
		if(verbatim && CUR_CHAR == '"') { //double quotation
			APPEND_CHAR(CUR_CHAR);
			NEXT();
		}
		else {
			break;
		}
	}
	TERMINATE_BUFFER();
	SQInteger len = _longstr.size()-1;
	if(ndelim == _SC('\'')) {
		if(len == 0) Error(_SC("empty constant"));
		if(len > 1) Error(_SC("constant too long"));
		_nvalue = _longstr[0];
		return TK_INTEGER;
	}
	_svalue = &_longstr[0];
	return TK_STRING_LITERAL;
}

void LexHexadecimal(const SQChar *s,SQUnsignedInteger *res)
{
	*res = 0;
	while(*s != 0)
	{
		if(scisdigit(*s)) *res = (*res)*16+((*s++)-'0');
		else if(scisxdigit(*s)) *res = (*res)*16+(toupper(*s++)-'A'+10);
		else { assert(0); }
	}
}

void LexInteger(const SQChar *s,SQUnsignedInteger *res)
{
	*res = 0;
	while(*s != 0)
	{
		*res = (*res)*10+((*s++)-'0');
	}
}

SQInteger scisodigit(SQInteger c) { return c >= _SC('0') && c <= _SC('7'); }

void LexOctal(const SQChar *s,SQUnsignedInteger *res)
{
	*res = 0;
	while(*s != 0)
	{
		if(scisodigit(*s)) *res = (*res)*8+((*s++)-'0');
		else { assert(0); }
	}
}

SQInteger isexponent(SQInteger c) { return c == 'e' || c=='E'; }


#define MAX_HEX_DIGITS (sizeof(SQInteger)*2)
SQInteger SQLexer::ReadNumber()
{
#define TINT 1
#define TFLOAT 2
#define THEX 3
#define TSCIENTIFIC 4
#define TOCTAL 5
	SQInteger type = TINT, firstchar = CUR_CHAR;
	SQChar *sTemp;
	INIT_TEMP_STRING();
	NEXT();
	if(firstchar == _SC('0') && (toupper(CUR_CHAR) == _SC('X') || scisodigit(CUR_CHAR)) ) {
		if(scisodigit(CUR_CHAR)) {
			type = TOCTAL;
			while(scisodigit(CUR_CHAR)) {
				APPEND_CHAR(CUR_CHAR);
				NEXT();
			}
			if(scisdigit(CUR_CHAR)) Error(_SC("invalid octal number"));
		}
		else {
			NEXT();
			type = THEX;
			while(isxdigit(CUR_CHAR)) {
				APPEND_CHAR(CUR_CHAR);
				NEXT();
			}
			if(_longstr.size() > MAX_HEX_DIGITS) Error(_SC("too many digits for an Hex number"));
		}
	}
	else {
		APPEND_CHAR((int)firstchar);
		while (CUR_CHAR == _SC('.') || scisdigit(CUR_CHAR) || isexponent(CUR_CHAR)) {
            if(CUR_CHAR == _SC('.') || isexponent(CUR_CHAR)) type = TFLOAT;
			if(isexponent(CUR_CHAR)) {
				if(type != TFLOAT) Error(_SC("invalid numeric format"));
				type = TSCIENTIFIC;
				APPEND_CHAR(CUR_CHAR);
				NEXT();
				if(CUR_CHAR == '+' || CUR_CHAR == '-'){
					APPEND_CHAR(CUR_CHAR);
					NEXT();
				}
				if(!scisdigit(CUR_CHAR)) Error(_SC("exponent expected"));
			}
			
			APPEND_CHAR(CUR_CHAR);
			NEXT();
		}
	}
	TERMINATE_BUFFER();
	switch(type) {
	case TSCIENTIFIC:
	case TFLOAT:
		_fvalue = (SQFloat)scstrtod(&_longstr[0],&sTemp);
		return TK_FLOAT;
	case TINT:
		LexInteger(&_longstr[0],(SQUnsignedInteger *)&_nvalue);
		return TK_INTEGER;
	case THEX:
		LexHexadecimal(&_longstr[0],(SQUnsignedInteger *)&_nvalue);
		return TK_INTEGER;
	case TOCTAL:
		LexOctal(&_longstr[0],(SQUnsignedInteger *)&_nvalue);
		return TK_INTEGER;
	}
	return 0;
}

SQInteger SQLexer::ReadID()
{
	SQInteger res;
	INIT_TEMP_STRING();
	do {
		APPEND_CHAR(CUR_CHAR);
		NEXT();
	} while(scisalnum(CUR_CHAR) || CUR_CHAR == _SC('_'));
	TERMINATE_BUFFER();
	res = GetIDType(&_longstr[0]);
	if(res == TK_IDENTIFIER || res == TK_CONSTRUCTOR) {
		_svalue = &_longstr[0];
	}
	return res;
}

// ******************************** sqmem.cpp ********************************
/*
	see copyright notice in squirrel.h
*/
// ---- #include "sqpcheader.h"
// ---> including sqpcheader.h
// <--- back to sqmem.cpp
void *sq_vm_malloc(SQUnsignedInteger size){	return malloc(size); }

void *sq_vm_realloc(void *p, SQUnsignedInteger oldsize, SQUnsignedInteger size){ return realloc(p, size); }

void sq_vm_free(void *p, SQUnsignedInteger size){	free(p); }

// ******************************** sqobject.cpp ********************************
/*
	see copyright notice in squirrel.h
*/
// ---- #include "sqpcheader.h"
// ---> including sqpcheader.h
// <--- back to sqobject.cpp
// ---- #include "sqvm.h"
// ---> including sqvm.h
// <--- back to sqobject.cpp
// ---- #include "sqstring.h"
// ---> including sqstring.h
// <--- back to sqobject.cpp
// ---- #include "sqarray.h"
// ---> including sqarray.h
// <--- back to sqobject.cpp
// ---- #include "sqtable.h"
// ---> including sqtable.h
// <--- back to sqobject.cpp
// ---- #include "squserdata.h"
// ---> including squserdata.h
// <--- back to sqobject.cpp
// ---- #include "sqfuncproto.h"
// ---> including sqfuncproto.h
// <--- back to sqobject.cpp
// ---- #include "sqclass.h"
// ---> including sqclass.h
// <--- back to sqobject.cpp
// ---- #include "sqclosure.h"
// ---> including sqclosure.h
// <--- back to sqobject.cpp


const SQChar *IdType2Name(SQObjectType type)
{
	switch(_RAW_TYPE(type))
	{
	case _RT_NULL:return _SC("null");
	case _RT_INTEGER:return _SC("integer");
	case _RT_FLOAT:return _SC("float");
	case _RT_BOOL:return _SC("bool");
	case _RT_STRING:return _SC("string");
	case _RT_TABLE:return _SC("table");
	case _RT_ARRAY:return _SC("array");
	case _RT_GENERATOR:return _SC("generator");
	case _RT_CLOSURE:
	case _RT_NATIVECLOSURE:
		return _SC("function");
	case _RT_USERDATA:
	case _RT_USERPOINTER:
		return _SC("userdata");
	case _RT_THREAD: return _SC("thread");
	case _RT_FUNCPROTO: return _SC("function");
	case _RT_CLASS: return _SC("class");
	case _RT_INSTANCE: return _SC("instance");
	case _RT_WEAKREF: return _SC("weakref");
	case _RT_OUTER: return _SC("outer");
	default:
		return NULL;
	}
}

const SQChar *GetTypeName(const SQObjectPtr &obj1)
{
	return IdType2Name(type(obj1));	
}

SQString *SQString::Create(SQSharedState *ss,const SQChar *s,SQInteger len)
{
	SQString *str=ADD_STRING(ss,s,len);
	return str;
}

void SQString::Release()
{
	REMOVE_STRING(_sharedstate,this);
}

SQInteger SQString::Next(const SQObjectPtr &refpos, SQObjectPtr &outkey, SQObjectPtr &outval)
{
	SQInteger idx = (SQInteger)TranslateIndex(refpos);
	while(idx < _len){
		outkey = (SQInteger)idx;
		outval = (SQInteger)((SQUnsignedInteger)_val[idx]);
		//return idx for the next iteration
		return ++idx;
	}
	//nothing to iterate anymore
	return -1;
}

SQUnsignedInteger TranslateIndex(const SQObjectPtr &idx)
{
	switch(type(idx)){
		case OT_NULL:
			return 0;
		case OT_INTEGER:
			return (SQUnsignedInteger)_integer(idx);
		default: assert(0); break;
	}
	return 0;
}

SQWeakRef *SQRefCounted::GetWeakRef(SQObjectType type)
{
	if(!_weakref) {
		sq_new(_weakref,SQWeakRef);
		_weakref->_obj._type = type;
		_weakref->_obj._unVal.pRefCounted = this;
	}
	return _weakref;
}

SQRefCounted::~SQRefCounted()
{
	if(_weakref) {
		_weakref->_obj._type = OT_NULL;
		_weakref->_obj._unVal.pRefCounted = NULL;
	}
}

void SQWeakRef::Release() { 
	if(ISREFCOUNTED(_obj._type)) { 
		_obj._unVal.pRefCounted->_weakref = NULL;
	} 
	sq_delete(this,SQWeakRef);
}

bool SQDelegable::GetMetaMethod(SQVM *v,SQMetaMethod mm,SQObjectPtr &res) {
	if(_delegate) {
		return _delegate->Get((*_ss(v)->_metamethods)[mm],res);
	}
	return false;
}

bool SQDelegable::SetDelegate(SQTable *mt)
{
	SQTable *temp = mt;
	if(temp == this) return false;
	while (temp) {
		if (temp->_delegate == this) return false; //cycle detected
		temp = temp->_delegate;
	}
	if (mt)	__ObjAddRef(mt);
	__ObjRelease(_delegate);
	_delegate = mt;
	return true;
}

bool SQGenerator::Yield(SQVM *v,SQInteger target)
{
	if(_state==eSuspended) { v->Raise_Error(_SC("internal vm error, yielding dead generator"));  return false;}
	if(_state==eDead) { v->Raise_Error(_SC("internal vm error, yielding a dead generator")); return false; }
	SQInteger size = v->_top-v->_stackbase;
	
	_stack.resize(size);
	SQObject _this = v->_stack[v->_stackbase];
	_stack._vals[0] = ISREFCOUNTED(type(_this)) ? SQObjectPtr(_refcounted(_this)->GetWeakRef(type(_this))) : _this;
	for(SQInteger n =1; n<target; n++) {
		_stack._vals[n] = v->_stack[v->_stackbase+n];
	}
	for(SQInteger j =0; j < size; j++)
	{
		v->_stack[v->_stackbase+j].Null();
	}

	_ci = *v->ci;
	_ci._generator=NULL;
	for(SQInteger i=0;i<_ci._etraps;i++) {
		_etraps.push_back(v->_etraps.top());
		v->_etraps.pop_back();
	}
	_state=eSuspended;
	return true;
}

bool SQGenerator::Resume(SQVM *v,SQObjectPtr &dest)
{
	if(_state==eDead){ v->Raise_Error(_SC("resuming dead generator")); return false; }
	if(_state==eRunning){ v->Raise_Error(_SC("resuming active generator")); return false; }
	SQInteger size = _stack.size();
	SQInteger target = &dest - &(v->_stack._vals[v->_stackbase]);
	assert(target>=0 && target<=255);
	if(!v->EnterFrame(v->_top, v->_top + size, false)) 
		return false;
	v->ci->_generator   = this;
	v->ci->_target      = (SQInt32)target;
	v->ci->_closure     = _ci._closure;
	v->ci->_ip          = _ci._ip;
	v->ci->_literals    = _ci._literals;
	v->ci->_ncalls      = _ci._ncalls;
	v->ci->_etraps      = _ci._etraps;
	v->ci->_root        = _ci._root;


	for(SQInteger i=0;i<_ci._etraps;i++) {
		v->_etraps.push_back(_etraps.top());
		_etraps.pop_back();
	}
	SQObject _this = _stack._vals[0];
	v->_stack[v->_stackbase] = type(_this) == OT_WEAKREF ? _weakref(_this)->_obj : _this;

	for(SQInteger n = 1; n<size; n++) {
		v->_stack[v->_stackbase+n] = _stack._vals[n];
		_stack._vals[n].Null();
	}

	_state=eRunning;
	if (v->_debughook)
		v->CallDebugHook(_SC('c'));

	return true;
}

void SQArray::Extend(const SQArray *a){
	SQInteger xlen;
	if((xlen=a->Size()))
		for(SQInteger i=0;i<xlen;i++)
			Append(a->_values[i]);
}

const SQChar* SQFunctionProto::GetLocal(SQVM *vm,SQUnsignedInteger stackbase,SQUnsignedInteger nseq,SQUnsignedInteger nop)
{
	SQUnsignedInteger nvars=_nlocalvarinfos;
	const SQChar *res=NULL; 
	if(nvars>=nseq){
 		for(SQUnsignedInteger i=0;i<nvars;i++){
			if(_localvarinfos[i]._start_op<=nop && _localvarinfos[i]._end_op>=nop)
			{
				if(nseq==0){
					vm->Push(vm->_stack[stackbase+_localvarinfos[i]._pos]);
					res=_stringval(_localvarinfos[i]._name);
					break;
				}
				nseq--;
			}
		}
	}
	return res;
}


SQInteger SQFunctionProto::GetLine(SQInstruction *curr)
{
	SQInteger op = (SQInteger)(curr-_instructions);
	SQInteger line=_lineinfos[0]._line;
	SQInteger low = 0;
	SQInteger high = _nlineinfos - 1;
	SQInteger mid = 0;
	while(low <= high)
	{
		mid = low + ((high - low) >> 1);
		SQInteger curop = _lineinfos[mid]._op;
		if(curop > op)
		{
			high = mid - 1;
		}
		else if(curop < op) {
			if(mid < (_nlineinfos - 1) 
				&& _lineinfos[mid + 1]._op >= op) {
				break;
			}
			low = mid + 1;
		}
		else { //equal
			break;
		}
	}

	line = _lineinfos[mid]._line;
	return line;
}

SQClosure::~SQClosure()
{
	__ObjRelease(_env);
	__ObjRelease(_base);
	REMOVE_FROM_CHAIN(&_ss(this)->_gc_chain,this);
}

#define _CHECK_IO(exp)  { if(!exp)return false; }
bool SafeWrite(HSQUIRRELVM v,SQWRITEFUNC write,SQUserPointer up,SQUserPointer dest,SQInteger size)
{
	if(write(up,dest,size) != size) {
		v->Raise_Error(_SC("io error (write function failure)"));
		return false;
	}
	return true;
}

bool SafeRead(HSQUIRRELVM v,SQWRITEFUNC read,SQUserPointer up,SQUserPointer dest,SQInteger size)
{
	if(size && read(up,dest,size) != size) {
		v->Raise_Error(_SC("io error, read function failure, the origin stream could be corrupted/trucated"));
		return false;
	}
	return true;
}

bool WriteTag(HSQUIRRELVM v,SQWRITEFUNC write,SQUserPointer up,SQUnsignedInteger32 tag)
{
	return SafeWrite(v,write,up,&tag,sizeof(tag));
}

bool CheckTag(HSQUIRRELVM v,SQWRITEFUNC read,SQUserPointer up,SQUnsignedInteger32 tag)
{
	SQUnsignedInteger32 t;
	_CHECK_IO(SafeRead(v,read,up,&t,sizeof(t)));
	if(t != tag){
		v->Raise_Error(_SC("invalid or corrupted closure stream"));
		return false;
	}
	return true;
}

bool WriteObject(HSQUIRRELVM v,SQUserPointer up,SQWRITEFUNC write,SQObjectPtr &o)
{
	SQUnsignedInteger32 _type = (SQUnsignedInteger32)type(o);
	_CHECK_IO(SafeWrite(v,write,up,&_type,sizeof(_type)));
	switch(type(o)){
	case OT_STRING:
		_CHECK_IO(SafeWrite(v,write,up,&_string(o)->_len,sizeof(SQInteger)));
		_CHECK_IO(SafeWrite(v,write,up,_stringval(o),rsl(_string(o)->_len)));
		break;
	case OT_INTEGER:
		_CHECK_IO(SafeWrite(v,write,up,&_integer(o),sizeof(SQInteger)));break;
	case OT_FLOAT:
		_CHECK_IO(SafeWrite(v,write,up,&_float(o),sizeof(SQFloat)));break;
	case OT_NULL:
		break;
	default:
		v->Raise_Error(_SC("cannot serialize a %s"),GetTypeName(o));
		return false;
	}
	return true;
}

bool ReadObject(HSQUIRRELVM v,SQUserPointer up,SQREADFUNC read,SQObjectPtr &o)
{
	SQUnsignedInteger32 _type;
	_CHECK_IO(SafeRead(v,read,up,&_type,sizeof(_type)));
	SQObjectType t = (SQObjectType)_type;
	switch(t){
	case OT_STRING:{
		SQInteger len;
		_CHECK_IO(SafeRead(v,read,up,&len,sizeof(SQInteger)));
		_CHECK_IO(SafeRead(v,read,up,_ss(v)->GetScratchPad(rsl(len)),rsl(len)));
		o=SQString::Create(_ss(v),_ss(v)->GetScratchPad(-1),len);
				   }
		break;
	case OT_INTEGER:{
		SQInteger i;
		_CHECK_IO(SafeRead(v,read,up,&i,sizeof(SQInteger))); o = i; break;
					}
	case OT_FLOAT:{
		SQFloat f;
		_CHECK_IO(SafeRead(v,read,up,&f,sizeof(SQFloat))); o = f; break;
				  }
	case OT_NULL:
		o.Null();
		break;
	default:
		v->Raise_Error(_SC("cannot serialize a %s"),IdType2Name(t));
		return false;
	}
	return true;
}

bool SQClosure::Save(SQVM *v,SQUserPointer up,SQWRITEFUNC write)
{
	_CHECK_IO(WriteTag(v,write,up,SQ_CLOSURESTREAM_HEAD));
	_CHECK_IO(WriteTag(v,write,up,sizeof(SQChar)));
	_CHECK_IO(WriteTag(v,write,up,sizeof(SQInteger)));
	_CHECK_IO(WriteTag(v,write,up,sizeof(SQFloat)));
	_CHECK_IO(_function->Save(v,up,write));
	_CHECK_IO(WriteTag(v,write,up,SQ_CLOSURESTREAM_TAIL));
	return true;
}

bool SQClosure::Load(SQVM *v,SQUserPointer up,SQREADFUNC read,SQObjectPtr &ret)
{
	_CHECK_IO(CheckTag(v,read,up,SQ_CLOSURESTREAM_HEAD));
	_CHECK_IO(CheckTag(v,read,up,sizeof(SQChar)));
	_CHECK_IO(CheckTag(v,read,up,sizeof(SQInteger)));
	_CHECK_IO(CheckTag(v,read,up,sizeof(SQFloat)));
	SQObjectPtr func;
	_CHECK_IO(SQFunctionProto::Load(v,up,read,func));
	_CHECK_IO(CheckTag(v,read,up,SQ_CLOSURESTREAM_TAIL));
	ret = SQClosure::Create(_ss(v),_funcproto(func));
	return true;
}

SQFunctionProto::SQFunctionProto(SQSharedState *ss)
{
	_stacksize=0;
	_bgenerator=false;
	INIT_CHAIN();ADD_TO_CHAIN(&_ss(this)->_gc_chain,this);
}

SQFunctionProto::~SQFunctionProto()
{
	REMOVE_FROM_CHAIN(&_ss(this)->_gc_chain,this);
}

bool SQFunctionProto::Save(SQVM *v,SQUserPointer up,SQWRITEFUNC write)
{
	SQInteger i,nliterals = _nliterals,nparameters = _nparameters;
	SQInteger noutervalues = _noutervalues,nlocalvarinfos = _nlocalvarinfos;
	SQInteger nlineinfos=_nlineinfos,ninstructions = _ninstructions,nfunctions=_nfunctions;
	SQInteger ndefaultparams = _ndefaultparams;
	_CHECK_IO(WriteTag(v,write,up,SQ_CLOSURESTREAM_PART));
	_CHECK_IO(WriteObject(v,up,write,_sourcename));
	_CHECK_IO(WriteObject(v,up,write,_name));
	_CHECK_IO(WriteTag(v,write,up,SQ_CLOSURESTREAM_PART));
	_CHECK_IO(SafeWrite(v,write,up,&nliterals,sizeof(nliterals)));
	_CHECK_IO(SafeWrite(v,write,up,&nparameters,sizeof(nparameters)));
	_CHECK_IO(SafeWrite(v,write,up,&noutervalues,sizeof(noutervalues)));
	_CHECK_IO(SafeWrite(v,write,up,&nlocalvarinfos,sizeof(nlocalvarinfos)));
	_CHECK_IO(SafeWrite(v,write,up,&nlineinfos,sizeof(nlineinfos)));
	_CHECK_IO(SafeWrite(v,write,up,&ndefaultparams,sizeof(ndefaultparams)));
	_CHECK_IO(SafeWrite(v,write,up,&ninstructions,sizeof(ninstructions)));
	_CHECK_IO(SafeWrite(v,write,up,&nfunctions,sizeof(nfunctions)));
	_CHECK_IO(WriteTag(v,write,up,SQ_CLOSURESTREAM_PART));
	for(i=0;i<nliterals;i++){
		_CHECK_IO(WriteObject(v,up,write,_literals[i]));
	}

	_CHECK_IO(WriteTag(v,write,up,SQ_CLOSURESTREAM_PART));
	for(i=0;i<nparameters;i++){
		_CHECK_IO(WriteObject(v,up,write,_parameters[i]));
	}

	_CHECK_IO(WriteTag(v,write,up,SQ_CLOSURESTREAM_PART));
	for(i=0;i<noutervalues;i++){
		_CHECK_IO(SafeWrite(v,write,up,&_outervalues[i]._type,sizeof(SQUnsignedInteger)));
		_CHECK_IO(WriteObject(v,up,write,_outervalues[i]._src));
		_CHECK_IO(WriteObject(v,up,write,_outervalues[i]._name));
	}

	_CHECK_IO(WriteTag(v,write,up,SQ_CLOSURESTREAM_PART));
	for(i=0;i<nlocalvarinfos;i++){
		SQLocalVarInfo &lvi=_localvarinfos[i];
		_CHECK_IO(WriteObject(v,up,write,lvi._name));
		_CHECK_IO(SafeWrite(v,write,up,&lvi._pos,sizeof(SQUnsignedInteger)));
		_CHECK_IO(SafeWrite(v,write,up,&lvi._start_op,sizeof(SQUnsignedInteger)));
		_CHECK_IO(SafeWrite(v,write,up,&lvi._end_op,sizeof(SQUnsignedInteger)));
	}

	_CHECK_IO(WriteTag(v,write,up,SQ_CLOSURESTREAM_PART));
	_CHECK_IO(SafeWrite(v,write,up,_lineinfos,sizeof(SQLineInfo)*nlineinfos));

	_CHECK_IO(WriteTag(v,write,up,SQ_CLOSURESTREAM_PART));
	_CHECK_IO(SafeWrite(v,write,up,_defaultparams,sizeof(SQInteger)*ndefaultparams));

	_CHECK_IO(WriteTag(v,write,up,SQ_CLOSURESTREAM_PART));
	_CHECK_IO(SafeWrite(v,write,up,_instructions,sizeof(SQInstruction)*ninstructions));

	_CHECK_IO(WriteTag(v,write,up,SQ_CLOSURESTREAM_PART));
	for(i=0;i<nfunctions;i++){
		_CHECK_IO(_funcproto(_functions[i])->Save(v,up,write));
	}
	_CHECK_IO(SafeWrite(v,write,up,&_stacksize,sizeof(_stacksize)));
	_CHECK_IO(SafeWrite(v,write,up,&_bgenerator,sizeof(_bgenerator)));
	_CHECK_IO(SafeWrite(v,write,up,&_varparams,sizeof(_varparams)));
	return true;
}

bool SQFunctionProto::Load(SQVM *v,SQUserPointer up,SQREADFUNC read,SQObjectPtr &ret)
{
	SQInteger i, nliterals,nparameters;
	SQInteger noutervalues ,nlocalvarinfos ;
	SQInteger nlineinfos,ninstructions ,nfunctions,ndefaultparams ;
	SQObjectPtr sourcename, name;
	SQObjectPtr o;
	_CHECK_IO(CheckTag(v,read,up,SQ_CLOSURESTREAM_PART));
	_CHECK_IO(ReadObject(v, up, read, sourcename));
	_CHECK_IO(ReadObject(v, up, read, name));
	
	_CHECK_IO(CheckTag(v,read,up,SQ_CLOSURESTREAM_PART));
	_CHECK_IO(SafeRead(v,read,up, &nliterals, sizeof(nliterals)));
	_CHECK_IO(SafeRead(v,read,up, &nparameters, sizeof(nparameters)));
	_CHECK_IO(SafeRead(v,read,up, &noutervalues, sizeof(noutervalues)));
	_CHECK_IO(SafeRead(v,read,up, &nlocalvarinfos, sizeof(nlocalvarinfos)));
	_CHECK_IO(SafeRead(v,read,up, &nlineinfos, sizeof(nlineinfos)));
	_CHECK_IO(SafeRead(v,read,up, &ndefaultparams, sizeof(ndefaultparams)));
	_CHECK_IO(SafeRead(v,read,up, &ninstructions, sizeof(ninstructions)));
	_CHECK_IO(SafeRead(v,read,up, &nfunctions, sizeof(nfunctions)));
	

	SQFunctionProto *f = SQFunctionProto::Create(_opt_ss(v),ninstructions,nliterals,nparameters,
			nfunctions,noutervalues,nlineinfos,nlocalvarinfos,ndefaultparams);
	SQObjectPtr proto = f; //gets a ref in case of failure
	f->_sourcename = sourcename;
	f->_name = name;

	_CHECK_IO(CheckTag(v,read,up,SQ_CLOSURESTREAM_PART));

	for(i = 0;i < nliterals; i++){
		_CHECK_IO(ReadObject(v, up, read, o));
		f->_literals[i] = o;
	}
	_CHECK_IO(CheckTag(v,read,up,SQ_CLOSURESTREAM_PART));

	for(i = 0; i < nparameters; i++){
		_CHECK_IO(ReadObject(v, up, read, o));
		f->_parameters[i] = o;
	}
	_CHECK_IO(CheckTag(v,read,up,SQ_CLOSURESTREAM_PART));

	for(i = 0; i < noutervalues; i++){
		SQUnsignedInteger type;
		SQObjectPtr name;
		_CHECK_IO(SafeRead(v,read,up, &type, sizeof(SQUnsignedInteger)));
		_CHECK_IO(ReadObject(v, up, read, o));
		_CHECK_IO(ReadObject(v, up, read, name));
		f->_outervalues[i] = SQOuterVar(name,o, (SQOuterType)type);
	}
	_CHECK_IO(CheckTag(v,read,up,SQ_CLOSURESTREAM_PART));

	for(i = 0; i < nlocalvarinfos; i++){
		SQLocalVarInfo lvi;
		_CHECK_IO(ReadObject(v, up, read, lvi._name));
		_CHECK_IO(SafeRead(v,read,up, &lvi._pos, sizeof(SQUnsignedInteger)));
		_CHECK_IO(SafeRead(v,read,up, &lvi._start_op, sizeof(SQUnsignedInteger)));
		_CHECK_IO(SafeRead(v,read,up, &lvi._end_op, sizeof(SQUnsignedInteger)));
		f->_localvarinfos[i] = lvi;
	}
	_CHECK_IO(CheckTag(v,read,up,SQ_CLOSURESTREAM_PART));
	_CHECK_IO(SafeRead(v,read,up, f->_lineinfos, sizeof(SQLineInfo)*nlineinfos));

	_CHECK_IO(CheckTag(v,read,up,SQ_CLOSURESTREAM_PART));
	_CHECK_IO(SafeRead(v,read,up, f->_defaultparams, sizeof(SQInteger)*ndefaultparams));

	_CHECK_IO(CheckTag(v,read,up,SQ_CLOSURESTREAM_PART));
	_CHECK_IO(SafeRead(v,read,up, f->_instructions, sizeof(SQInstruction)*ninstructions));

	_CHECK_IO(CheckTag(v,read,up,SQ_CLOSURESTREAM_PART));
	for(i = 0; i < nfunctions; i++){
		_CHECK_IO(_funcproto(o)->Load(v, up, read, o));
		f->_functions[i] = o;
	}
	_CHECK_IO(SafeRead(v,read,up, &f->_stacksize, sizeof(f->_stacksize)));
	_CHECK_IO(SafeRead(v,read,up, &f->_bgenerator, sizeof(f->_bgenerator)));
	_CHECK_IO(SafeRead(v,read,up, &f->_varparams, sizeof(f->_varparams)));
	
	ret = f;
	return true;
}

#ifndef NO_GARBAGE_COLLECTOR

#define START_MARK() 	if(!(_uiRef&MARK_FLAG)){ \
		_uiRef|=MARK_FLAG;

#define END_MARK() RemoveFromChain(&_sharedstate->_gc_chain, this); \
		AddToChain(chain, this); }

void SQVM::Mark(SQCollectable **chain)
{
	START_MARK()
		SQSharedState::MarkObject(_lasterror,chain);
		SQSharedState::MarkObject(_errorhandler,chain);
		SQSharedState::MarkObject(_debughook_closure,chain);
		SQSharedState::MarkObject(_roottable, chain);
		SQSharedState::MarkObject(temp_reg, chain);
		for(SQUnsignedInteger i = 0; i < _stack.size(); i++) SQSharedState::MarkObject(_stack[i], chain);
		for(SQInteger k = 0; k < _callsstacksize; k++) SQSharedState::MarkObject(_callsstack[k]._closure, chain);
	END_MARK()
}

void SQArray::Mark(SQCollectable **chain)
{
	START_MARK()
		SQInteger len = _values.size();
		for(SQInteger i = 0;i < len; i++) SQSharedState::MarkObject(_values[i], chain);
	END_MARK()
}
void SQTable::Mark(SQCollectable **chain)
{
	START_MARK()
		if(_delegate) _delegate->Mark(chain);
		SQInteger len = _numofnodes;
		for(SQInteger i = 0; i < len; i++){
			SQSharedState::MarkObject(_nodes[i].key, chain);
			SQSharedState::MarkObject(_nodes[i].val, chain);
		}
	END_MARK()
}

void SQClass::Mark(SQCollectable **chain)
{
	START_MARK()
		_members->Mark(chain);
		if(_base) _base->Mark(chain);
		SQSharedState::MarkObject(_attributes, chain);
		for(SQUnsignedInteger i =0; i< _defaultvalues.size(); i++) {
			SQSharedState::MarkObject(_defaultvalues[i].val, chain);
			SQSharedState::MarkObject(_defaultvalues[i].attrs, chain);
		}
		for(SQUnsignedInteger j =0; j< _methods.size(); j++) {
			SQSharedState::MarkObject(_methods[j].val, chain);
			SQSharedState::MarkObject(_methods[j].attrs, chain);
		}
		for(SQUnsignedInteger k =0; k< MT_LAST; k++) {
			SQSharedState::MarkObject(_metamethods[k], chain);
		}
	END_MARK()
}

void SQInstance::Mark(SQCollectable **chain)
{
	START_MARK()
		_class->Mark(chain);
		SQUnsignedInteger nvalues = _class->_defaultvalues.size();
		for(SQUnsignedInteger i =0; i< nvalues; i++) {
			SQSharedState::MarkObject(_values[i], chain);
		}
	END_MARK()
}

void SQGenerator::Mark(SQCollectable **chain)
{
	START_MARK()
		for(SQUnsignedInteger i = 0; i < _stack.size(); i++) SQSharedState::MarkObject(_stack[i], chain);
		SQSharedState::MarkObject(_closure, chain);
	END_MARK()
}

void SQFunctionProto::Mark(SQCollectable **chain)
{
	START_MARK()
		for(SQInteger i = 0; i < _nliterals; i++) SQSharedState::MarkObject(_literals[i], chain);
		for(SQInteger k = 0; k < _nfunctions; k++) SQSharedState::MarkObject(_functions[k], chain);
	END_MARK()
}

void SQClosure::Mark(SQCollectable **chain)
{
	START_MARK()
		if(_base) _base->Mark(chain);
		SQFunctionProto *fp = _function;
		fp->Mark(chain);
		for(SQInteger i = 0; i < fp->_noutervalues; i++) SQSharedState::MarkObject(_outervalues[i], chain);
		for(SQInteger k = 0; k < fp->_ndefaultparams; k++) SQSharedState::MarkObject(_defaultparams[k], chain);
	END_MARK()
}

void SQNativeClosure::Mark(SQCollectable **chain)
{
	START_MARK()
		for(SQUnsignedInteger i = 0; i < _noutervalues; i++) SQSharedState::MarkObject(_outervalues[i], chain);
	END_MARK()
}

void SQOuter::Mark(SQCollectable **chain)
{
	START_MARK()
    /* If the valptr points to a closed value, that value is alive */
    if(_valptr == &_value) {
      SQSharedState::MarkObject(_value, chain);
    }
	END_MARK()
}

void SQUserData::Mark(SQCollectable **chain){
	START_MARK()
		if(_delegate) _delegate->Mark(chain);
	END_MARK()
}

void SQCollectable::UnMark() { _uiRef&=~MARK_FLAG; }

#endif


// ******************************** sqstate.cpp ********************************
/*
	see copyright notice in squirrel.h
*/
// ---- #include "sqpcheader.h"
// ---> including sqpcheader.h
// <--- back to sqstate.cpp
// ---- #include "sqopcodes.h"
// ---> including sqopcodes.h
// <--- back to sqstate.cpp
// ---- #include "sqvm.h"
// ---> including sqvm.h
// <--- back to sqstate.cpp
// ---- #include "sqfuncproto.h"
// ---> including sqfuncproto.h
// <--- back to sqstate.cpp
// ---- #include "sqclosure.h"
// ---> including sqclosure.h
// <--- back to sqstate.cpp
// ---- #include "sqstring.h"
// ---> including sqstring.h
// <--- back to sqstate.cpp
// ---- #include "sqtable.h"
// ---> including sqtable.h
// <--- back to sqstate.cpp
// ---- #include "sqarray.h"
// ---> including sqarray.h
// <--- back to sqstate.cpp
// ---- #include "squserdata.h"
// ---> including squserdata.h
// <--- back to sqstate.cpp
// ---- #include "sqclass.h"
// ---> including sqclass.h
// <--- back to sqstate.cpp

//SQObjectPtr _null_;
//SQObjectPtr _true_(true);
//SQObjectPtr _false_(false);
//SQObjectPtr _one_((SQInteger)1);
//SQObjectPtr _minusone_((SQInteger)-1);

SQSharedState::SQSharedState()
{
	_compilererrorhandler = NULL;
	_printfunc = NULL;
	_errorfunc = NULL;
	_debuginfo = false;
	_notifyallexceptions = false;
}

#define newsysstring(s) {	\
	_systemstrings->push_back(SQString::Create(this,s));	\
	}

#define newmetamethod(s) {	\
	_metamethods->push_back(SQString::Create(this,s));	\
	_table(_metamethodsmap)->NewSlot(_metamethods->back(),(SQInteger)(_metamethods->size()-1)); \
	}

bool CompileTypemask(SQIntVec &res,const SQChar *typemask)
{
	SQInteger i = 0;
	
	SQInteger mask = 0;
	while(typemask[i] != 0) {
		
		switch(typemask[i]){
				case 'o': mask |= _RT_NULL; break;
				case 'i': mask |= _RT_INTEGER; break;
				case 'f': mask |= _RT_FLOAT; break;
				case 'n': mask |= (_RT_FLOAT | _RT_INTEGER); break;
				case 's': mask |= _RT_STRING; break;
				case 't': mask |= _RT_TABLE; break;
				case 'a': mask |= _RT_ARRAY; break;
				case 'u': mask |= _RT_USERDATA; break;
				case 'c': mask |= (_RT_CLOSURE | _RT_NATIVECLOSURE); break;
				case 'b': mask |= _RT_BOOL; break;
				case 'g': mask |= _RT_GENERATOR; break;
				case 'p': mask |= _RT_USERPOINTER; break;
				case 'v': mask |= _RT_THREAD; break;
				case 'x': mask |= _RT_INSTANCE; break;
				case 'y': mask |= _RT_CLASS; break;
				case 'r': mask |= _RT_WEAKREF; break;
				case '.': mask = -1; res.push_back(mask); i++; mask = 0; continue;
				case ' ': i++; continue; //ignores spaces
				default:
					return false;
		}
		i++;
		if(typemask[i] == '|') { 
			i++; 
			if(typemask[i] == 0)
				return false;
			continue; 
		}
		res.push_back(mask);
		mask = 0;
		
	}
	return true;
}

SQTable *CreateDefaultDelegate(SQSharedState *ss,SQRegFunction *funcz)
{
	SQInteger i=0;
	SQTable *t=SQTable::Create(ss,0);
	while(funcz[i].name!=0){
		SQNativeClosure *nc = SQNativeClosure::Create(ss,funcz[i].f,0);
		nc->_nparamscheck = funcz[i].nparamscheck;
		nc->_name = SQString::Create(ss,funcz[i].name);
		if(funcz[i].typemask && !CompileTypemask(nc->_typecheck,funcz[i].typemask))
			return NULL;
		t->NewSlot(SQString::Create(ss,funcz[i].name),nc);
		i++;
	}
	return t;
}

void SQSharedState::Init()
{	
	_scratchpad=NULL;
	_scratchpadsize=0;
#ifndef NO_GARBAGE_COLLECTOR
	_gc_chain=NULL;
#endif
	_stringtable = (SQStringTable*)SQ_MALLOC(sizeof(SQStringTable));
	new (_stringtable) SQStringTable(this);
	sq_new(_metamethods,SQObjectPtrVec);
	sq_new(_systemstrings,SQObjectPtrVec);
	sq_new(_types,SQObjectPtrVec);
	_metamethodsmap = SQTable::Create(this,MT_LAST-1);
	//adding type strings to avoid memory trashing
	//types names
	newsysstring(_SC("null"));
	newsysstring(_SC("table"));
	newsysstring(_SC("array"));
	newsysstring(_SC("closure"));
	newsysstring(_SC("string"));
	newsysstring(_SC("userdata"));
	newsysstring(_SC("integer"));
	newsysstring(_SC("float"));
	newsysstring(_SC("userpointer"));
	newsysstring(_SC("function"));
	newsysstring(_SC("generator"));
	newsysstring(_SC("thread"));
	newsysstring(_SC("class"));
	newsysstring(_SC("instance"));
	newsysstring(_SC("bool"));
	//meta methods
	newmetamethod(MM_ADD);
	newmetamethod(MM_SUB);
	newmetamethod(MM_MUL);
	newmetamethod(MM_DIV);
	newmetamethod(MM_UNM);
	newmetamethod(MM_MODULO);
	newmetamethod(MM_SET);
	newmetamethod(MM_GET);
	newmetamethod(MM_TYPEOF);
	newmetamethod(MM_NEXTI);
	newmetamethod(MM_CMP);
	newmetamethod(MM_CALL);
	newmetamethod(MM_CLONED);
	newmetamethod(MM_NEWSLOT);
	newmetamethod(MM_DELSLOT);
	newmetamethod(MM_TOSTRING);
	newmetamethod(MM_NEWMEMBER);
	newmetamethod(MM_INHERITED);

	_constructoridx = SQString::Create(this,_SC("constructor"));
	_registry = SQTable::Create(this,0);
	_consts = SQTable::Create(this,0);
	_table_default_delegate = CreateDefaultDelegate(this,_table_default_delegate_funcz);
	_array_default_delegate = CreateDefaultDelegate(this,_array_default_delegate_funcz);
	_string_default_delegate = CreateDefaultDelegate(this,_string_default_delegate_funcz);
	_number_default_delegate = CreateDefaultDelegate(this,_number_default_delegate_funcz);
	_closure_default_delegate = CreateDefaultDelegate(this,_closure_default_delegate_funcz);
	_generator_default_delegate = CreateDefaultDelegate(this,_generator_default_delegate_funcz);
	_thread_default_delegate = CreateDefaultDelegate(this,_thread_default_delegate_funcz);
	_class_default_delegate = CreateDefaultDelegate(this,_class_default_delegate_funcz);
	_instance_default_delegate = CreateDefaultDelegate(this,_instance_default_delegate_funcz);
	_weakref_default_delegate = CreateDefaultDelegate(this,_weakref_default_delegate_funcz);

}

SQSharedState::~SQSharedState()
{
	_constructoridx.Null();
	_table(_registry)->Finalize();
	_table(_consts)->Finalize();
	_table(_metamethodsmap)->Finalize();
	_registry.Null();
	_consts.Null();
	_metamethodsmap.Null();
	while(!_systemstrings->empty()) {
		_systemstrings->back().Null();
		_systemstrings->pop_back();
	}
	_thread(_root_vm)->Finalize();
	_root_vm.Null();
	_table_default_delegate.Null();
	_array_default_delegate.Null();
	_string_default_delegate.Null();
	_number_default_delegate.Null();
	_closure_default_delegate.Null();
	_generator_default_delegate.Null();
	_thread_default_delegate.Null();
	_class_default_delegate.Null();
	_instance_default_delegate.Null();
	_weakref_default_delegate.Null();
	_refs_table.Finalize();
#ifndef NO_GARBAGE_COLLECTOR
	SQCollectable *t = _gc_chain;
	SQCollectable *nx = NULL;
	if(t) {
		t->_uiRef++;
		while(t) {
			t->Finalize();
			nx = t->_next;
			if(nx) nx->_uiRef++;
			if(--t->_uiRef == 0)
				t->Release();
			t = nx;
		}
	}
	assert(_gc_chain==NULL); //just to proove a theory
	while(_gc_chain){
		_gc_chain->_uiRef++;
		_gc_chain->Release();
	}
#endif

	sq_delete(_types,SQObjectPtrVec);
	sq_delete(_systemstrings,SQObjectPtrVec);
	sq_delete(_metamethods,SQObjectPtrVec);
	sq_delete(_stringtable,SQStringTable);
	if(_scratchpad)SQ_FREE(_scratchpad,_scratchpadsize);
}


SQInteger SQSharedState::GetMetaMethodIdxByName(const SQObjectPtr &name)
{
	if(type(name) != OT_STRING)
		return -1;
	SQObjectPtr ret;
	if(_table(_metamethodsmap)->Get(name,ret)) {
		return _integer(ret);
	}
	return -1;
}

#ifndef NO_GARBAGE_COLLECTOR

void SQSharedState::MarkObject(SQObjectPtr &o,SQCollectable **chain)
{
	switch(type(o)){
	case OT_TABLE:_table(o)->Mark(chain);break;
	case OT_ARRAY:_array(o)->Mark(chain);break;
	case OT_USERDATA:_userdata(o)->Mark(chain);break;
	case OT_CLOSURE:_closure(o)->Mark(chain);break;
	case OT_NATIVECLOSURE:_nativeclosure(o)->Mark(chain);break;
	case OT_GENERATOR:_generator(o)->Mark(chain);break;
	case OT_THREAD:_thread(o)->Mark(chain);break;
	case OT_CLASS:_class(o)->Mark(chain);break;
	case OT_INSTANCE:_instance(o)->Mark(chain);break;
	case OT_OUTER:_outer(o)->Mark(chain);break;
	case OT_FUNCPROTO:_funcproto(o)->Mark(chain);break;
	default: break; //shutup compiler
	}
}


void SQSharedState::RunMark(SQVM *vm,SQCollectable **tchain)
{
	SQVM *vms = _thread(_root_vm);
	
	vms->Mark(tchain);
	
	_refs_table.Mark(tchain);
	MarkObject(_registry,tchain);
	MarkObject(_consts,tchain);
	MarkObject(_metamethodsmap,tchain);
	MarkObject(_table_default_delegate,tchain);
	MarkObject(_array_default_delegate,tchain);
	MarkObject(_string_default_delegate,tchain);
	MarkObject(_number_default_delegate,tchain);
	MarkObject(_generator_default_delegate,tchain);
	MarkObject(_thread_default_delegate,tchain);
	MarkObject(_closure_default_delegate,tchain);
	MarkObject(_class_default_delegate,tchain);
	MarkObject(_instance_default_delegate,tchain);
	MarkObject(_weakref_default_delegate,tchain);

}

SQInteger SQSharedState::ResurrectUnreachable(SQVM *vm)
{
	SQInteger n=0;
	SQCollectable *tchain=NULL;

	RunMark(vm,&tchain);

	SQCollectable *resurrected = _gc_chain;
	SQCollectable *t = resurrected;
	//SQCollectable *nx = NULL;

	_gc_chain = tchain;

	SQArray *ret = NULL;
	if(resurrected) {
		ret = SQArray::Create(this,0);
		SQCollectable *rlast = NULL;
		while(t) {
			rlast = t;
			SQObjectType type = t->GetType();
			if(type != OT_FUNCPROTO && type != OT_OUTER) {
				SQObject sqo;
				sqo._type = type;
				sqo._unVal.pRefCounted = t;
				ret->Append(sqo);
			}
			t = t->_next;
			n++;
		}

		assert(rlast->_next == NULL);
		rlast->_next = _gc_chain;
		if(_gc_chain)
		{
			_gc_chain->_prev = rlast;
		}
		_gc_chain = resurrected;
	}

	t = _gc_chain;
	while(t) {
		t->UnMark();
		t = t->_next;
	}

	if(ret) {
		SQObjectPtr temp = ret;
		vm->Push(temp);
	}
	else {
		vm->PushNull();
	}
	return n;
}

SQInteger SQSharedState::CollectGarbage(SQVM *vm)
{
	SQInteger n = 0;
	SQCollectable *tchain = NULL;

	RunMark(vm,&tchain);

	SQCollectable *t = _gc_chain;
	SQCollectable *nx = NULL;
	if(t) {
		t->_uiRef++;
		while(t) {
			t->Finalize();
			nx = t->_next;
			if(nx) nx->_uiRef++;
			if(--t->_uiRef == 0)
				t->Release();
			t = nx;
			n++;
		}
	}

	t = tchain;
	while(t) {
		t->UnMark();
		t = t->_next;
	}
	_gc_chain = tchain;
	
	return n;
}
#endif

#ifndef NO_GARBAGE_COLLECTOR
void SQCollectable::AddToChain(SQCollectable **chain,SQCollectable *c)
{
    c->_prev = NULL;
	c->_next = *chain;
	if(*chain) (*chain)->_prev = c;
	*chain = c;
}

void SQCollectable::RemoveFromChain(SQCollectable **chain,SQCollectable *c)
{
	if(c->_prev) c->_prev->_next = c->_next;
	else *chain = c->_next;
	if(c->_next)
		c->_next->_prev = c->_prev;
	c->_next = NULL;
	c->_prev = NULL;
}
#endif

SQChar* SQSharedState::GetScratchPad(SQInteger size)
{
	SQInteger newsize;
	if(size>0) {
		if(_scratchpadsize < size) {
			newsize = size + (size>>1);
			_scratchpad = (SQChar *)SQ_REALLOC(_scratchpad,_scratchpadsize,newsize);
			_scratchpadsize = newsize;

		}else if(_scratchpadsize >= (size<<5)) {
			newsize = _scratchpadsize >> 1;
			_scratchpad = (SQChar *)SQ_REALLOC(_scratchpad,_scratchpadsize,newsize);
			_scratchpadsize = newsize;
		}
	}
	return _scratchpad;
}

RefTable::RefTable()
{
	AllocNodes(4);
}

void RefTable::Finalize()
{
	RefNode *nodes = _nodes;
	for(SQUnsignedInteger n = 0; n < _numofslots; n++) {
		nodes->obj.Null();
		nodes++;
	}
}

RefTable::~RefTable()
{
	SQ_FREE(_buckets,(_numofslots * sizeof(RefNode *)) + (_numofslots * sizeof(RefNode)));
}

#ifndef NO_GARBAGE_COLLECTOR
void RefTable::Mark(SQCollectable **chain)
{
	RefNode *nodes = (RefNode *)_nodes;
	for(SQUnsignedInteger n = 0; n < _numofslots; n++) {
		if(type(nodes->obj) != OT_NULL) {
			SQSharedState::MarkObject(nodes->obj,chain);
		}
		nodes++;
	}
}
#endif

void RefTable::AddRef(SQObject &obj)
{
	SQHash mainpos;
	RefNode *prev;
	RefNode *ref = Get(obj,mainpos,&prev,true);
	ref->refs++;
}

SQUnsignedInteger RefTable::GetRefCount(SQObject &obj)
{
     SQHash mainpos;
     RefNode *prev;
     RefNode *ref = Get(obj,mainpos,&prev,true);
     return ref->refs;
}


SQBool RefTable::Release(SQObject &obj)
{
	SQHash mainpos;
	RefNode *prev;
	RefNode *ref = Get(obj,mainpos,&prev,false);
	if(ref) {
		if(--ref->refs == 0) {
			SQObjectPtr o = ref->obj;
			if(prev) {
				prev->next = ref->next;
			}
			else {
				_buckets[mainpos] = ref->next;
			}
			ref->next = _freelist;
			_freelist = ref;
			_slotused--;
			ref->obj.Null();
			//<<FIXME>>test for shrink?
			return SQTrue;
		}
	}
	else {
		assert(0);
	}
	return SQFalse;
}

void RefTable::Resize(SQUnsignedInteger size)
{
	RefNode **oldbucks = _buckets;
	RefNode *t = _nodes;
	SQUnsignedInteger oldnumofslots = _numofslots;
	AllocNodes(size);
	//rehash
	SQUnsignedInteger nfound = 0;
	for(SQUnsignedInteger n = 0; n < oldnumofslots; n++) {
		if(type(t->obj) != OT_NULL) {
			//add back;
			assert(t->refs != 0);
			RefNode *nn = Add(::HashObj(t->obj)&(_numofslots-1),t->obj);
			nn->refs = t->refs; 
			t->obj.Null();
			nfound++;
		}
		t++;
	}
	assert(nfound == oldnumofslots);
	SQ_FREE(oldbucks,(oldnumofslots * sizeof(RefNode *)) + (oldnumofslots * sizeof(RefNode)));
}

RefTable::RefNode *RefTable::Add(SQHash mainpos,SQObject &obj)
{
	RefNode *t = _buckets[mainpos];
	RefNode *newnode = _freelist;
	newnode->obj = obj;
	_buckets[mainpos] = newnode;
	_freelist = _freelist->next;
	newnode->next = t;
	assert(newnode->refs == 0);
	_slotused++;
	return newnode;
}

RefTable::RefNode *RefTable::Get(SQObject &obj,SQHash &mainpos,RefNode **prev,bool add)
{
	RefNode *ref;
	mainpos = ::HashObj(obj)&(_numofslots-1);
	*prev = NULL;
	for (ref = _buckets[mainpos]; ref; ) {
		if(_rawval(ref->obj) == _rawval(obj) && type(ref->obj) == type(obj))
			break;
		*prev = ref;
		ref = ref->next;
	}
	if(ref == NULL && add) {
		if(_numofslots == _slotused) {
			assert(_freelist == 0);
			Resize(_numofslots*2);
			mainpos = ::HashObj(obj)&(_numofslots-1);
		}
		ref = Add(mainpos,obj);
	}
	return ref;
}

void RefTable::AllocNodes(SQUnsignedInteger size)
{
	RefNode **bucks;
	RefNode *nodes;
	bucks = (RefNode **)SQ_MALLOC((size * sizeof(RefNode *)) + (size * sizeof(RefNode)));
	nodes = (RefNode *)&bucks[size];
	RefNode *temp = nodes;
	SQUnsignedInteger n;
	for(n = 0; n < size - 1; n++) {
		bucks[n] = NULL;
		temp->refs = 0;
		new (&temp->obj) SQObjectPtr;
		temp->next = temp+1;
		temp++;
	}
	bucks[n] = NULL;
	temp->refs = 0;
	new (&temp->obj) SQObjectPtr;
	temp->next = NULL;
	_freelist = nodes;
	_nodes = nodes;
	_buckets = bucks;
	_slotused = 0;
	_numofslots = size;
}
//////////////////////////////////////////////////////////////////////////
//SQStringTable
/*
* The following code is based on Lua 4.0 (Copyright 1994-2002 Tecgraf, PUC-Rio.)
* http://www.lua.org/copyright.html#4
* http://www.lua.org/source/4.0.1/src_lstring.c.html
*/

SQStringTable::SQStringTable(SQSharedState *ss)
{
	_sharedstate = ss;
	AllocNodes(4);
	_slotused = 0;
}

SQStringTable::~SQStringTable()
{
	SQ_FREE(_strings,sizeof(SQString*)*_numofslots);
	_strings = NULL;
}

void SQStringTable::AllocNodes(SQInteger size)
{
	_numofslots = size;
	_strings = (SQString**)SQ_MALLOC(sizeof(SQString*)*_numofslots);
	memset(_strings,0,sizeof(SQString*)*_numofslots);
}

SQString *SQStringTable::Add(const SQChar *news,SQInteger len)
{
	if(len<0)
		len = (SQInteger)scstrlen(news);
	SQHash newhash = ::_hashstr(news,len);
	SQHash h = newhash&(_numofslots-1);
	SQString *s;
	for (s = _strings[h]; s; s = s->_next){
		if(s->_len == len && (!memcmp(news,s->_val,rsl(len))))
			return s; //found
	}

	SQString *t = (SQString *)SQ_MALLOC(rsl(len)+sizeof(SQString));
	new (t) SQString;
	t->_sharedstate = _sharedstate;
	memcpy(t->_val,news,rsl(len));
	t->_val[len] = _SC('\0');
	t->_len = len;
	t->_hash = newhash;
	t->_next = _strings[h];
	_strings[h] = t;
	_slotused++;
	if (_slotused > _numofslots)  /* too crowded? */
		Resize(_numofslots*2);
	return t;
}

void SQStringTable::Resize(SQInteger size)
{
	SQInteger oldsize=_numofslots;
	SQString **oldtable=_strings;
	AllocNodes(size);
	for (SQInteger i=0; i<oldsize; i++){
		SQString *p = oldtable[i];
		while(p){
			SQString *next = p->_next;
			SQHash h = p->_hash&(_numofslots-1);
			p->_next = _strings[h];
			_strings[h] = p;
			p = next;
		}
	}
	SQ_FREE(oldtable,oldsize*sizeof(SQString*));
}

void SQStringTable::Remove(SQString *bs)
{
	SQString *s;
	SQString *prev=NULL;
	SQHash h = bs->_hash&(_numofslots - 1);
	
	for (s = _strings[h]; s; ){
		if(s == bs){
			if(prev)
				prev->_next = s->_next;
			else
				_strings[h] = s->_next;
			_slotused--;
			SQInteger slen = s->_len;
			s->~SQString();
			SQ_FREE(s,sizeof(SQString) + rsl(slen));
			return;
		}
		prev = s;
		s = s->_next;
	}
	assert(0);//if this fail something is wrong
}

// ******************************** sqtable.cpp ********************************
/*
see copyright notice in squirrel.h
*/
// ---- #include "sqpcheader.h"
// ---> including sqpcheader.h
// <--- back to sqtable.cpp
// ---- #include "sqvm.h"
// ---> including sqvm.h
// <--- back to sqtable.cpp
// ---- #include "sqtable.h"
// ---> including sqtable.h
// <--- back to sqtable.cpp
// ---- #include "sqfuncproto.h"
// ---> including sqfuncproto.h
// <--- back to sqtable.cpp
// ---- #include "sqclosure.h"
// ---> including sqclosure.h
// <--- back to sqtable.cpp

SQTable::SQTable(SQSharedState *ss,SQInteger nInitialSize)
{
	SQInteger pow2size=MINPOWER2;
	while(nInitialSize>pow2size)pow2size=pow2size<<1;
	AllocNodes(pow2size);
	_usednodes = 0;
	_delegate = NULL;
	INIT_CHAIN();
	ADD_TO_CHAIN(&_sharedstate->_gc_chain,this);
}

void SQTable::Remove(const SQObjectPtr &key)
{
	
	_HashNode *n = _Get(key, HashObj(key) & (_numofnodes - 1));
	if (n) {
		n->val.Null();
		n->key.Null();
		_usednodes--;
		Rehash(false);
	}
}

void SQTable::AllocNodes(SQInteger nSize)
{
	_HashNode *nodes=(_HashNode *)SQ_MALLOC(sizeof(_HashNode)*nSize);
	for(SQInteger i=0;i<nSize;i++){
		_HashNode &n = nodes[i];
		new (&n) _HashNode;
		n.next=NULL;
	}
	_numofnodes=nSize;
	_nodes=nodes;
	_firstfree=&_nodes[_numofnodes-1];
}

void SQTable::Rehash(bool force)
{
	SQInteger oldsize=_numofnodes;
	//prevent problems with the integer division
	if(oldsize<4)oldsize=4;
	_HashNode *nold=_nodes;
	SQInteger nelems=CountUsed();
	if (nelems >= oldsize-oldsize/4)  /* using more than 3/4? */
		AllocNodes(oldsize*2);
	else if (nelems <= oldsize/4 &&  /* less than 1/4? */
		oldsize > MINPOWER2)
		AllocNodes(oldsize/2);
	else if(force)
		AllocNodes(oldsize);
	else
		return;
	_usednodes = 0;
	for (SQInteger i=0; i<oldsize; i++) {
		_HashNode *old = nold+i;
		if (type(old->key) != OT_NULL)
			NewSlot(old->key,old->val);
	}
	for(SQInteger k=0;k<oldsize;k++) 
		nold[k].~_HashNode();
	SQ_FREE(nold,oldsize*sizeof(_HashNode));
}

SQTable *SQTable::Clone()
{
	SQTable *nt=Create(_opt_ss(this),_numofnodes);
#ifdef _FAST_CLONE
	_HashNode *basesrc = _nodes;
	_HashNode *basedst = nt->_nodes;
	_HashNode *src = _nodes;
	_HashNode *dst = nt->_nodes;
	SQInteger n = 0;
	for(n = 0; n < _numofnodes; n++) {
		dst->key = src->key;
		dst->val = src->val;
		if(src->next) {
			assert(src->next > basesrc);
			dst->next = basedst + (src->next - basesrc);
			assert(dst != dst->next);
		}
		dst++;
		src++;
	}
	assert(_firstfree > basesrc);
	assert(_firstfree != NULL);
	nt->_firstfree = basedst + (_firstfree - basesrc);
	nt->_usednodes = _usednodes;
#else
	SQInteger ridx=0;
	SQObjectPtr key,val;
	while((ridx=Next(true,ridx,key,val))!=-1){
		nt->NewSlot(key,val);
	}
#endif
	nt->SetDelegate(_delegate);
	return nt;
}

bool SQTable::Get(const SQObjectPtr &key,SQObjectPtr &val)
{
	if(type(key) == OT_NULL)
		return false;
	_HashNode *n = _Get(key, HashObj(key) & (_numofnodes - 1));
	if (n) {
		val = _realval(n->val);
		return true;
	}
	return false;
}
bool SQTable::NewSlot(const SQObjectPtr &key,const SQObjectPtr &val)
{
	assert(type(key) != OT_NULL);
	SQHash h = HashObj(key) & (_numofnodes - 1);
	_HashNode *n = _Get(key, h);
	if (n) {
		n->val = val;
		return false;
	}
	_HashNode *mp = &_nodes[h];
	n = mp;


	//key not found I'll insert it
	//main pos is not free

	if(type(mp->key) != OT_NULL) {
		n = _firstfree;  /* get a free place */
		SQHash mph = HashObj(mp->key) & (_numofnodes - 1);
		_HashNode *othern;  /* main position of colliding node */
		
		if (mp > n && (othern = &_nodes[mph]) != mp){
			/* yes; move colliding node into free position */
			while (othern->next != mp){
				assert(othern->next != NULL);
				othern = othern->next;  /* find previous */
			}
			othern->next = n;  /* redo the chain with `n' in place of `mp' */
			n->key = mp->key;
			n->val = mp->val;/* copy colliding node into free pos. (mp->next also goes) */
			n->next = mp->next;
			mp->key.Null();
			mp->val.Null();
			mp->next = NULL;  /* now `mp' is free */
		}
		else{
			/* new node will go into free position */
			n->next = mp->next;  /* chain new position */
			mp->next = n;
			mp = n;
		}
	}
	mp->key = key;

	for (;;) {  /* correct `firstfree' */
		if (type(_firstfree->key) == OT_NULL && _firstfree->next == NULL) {
			mp->val = val;
			_usednodes++;
			return true;  /* OK; table still has a free place */
		}
		else if (_firstfree == _nodes) break;  /* cannot decrement from here */
		else (_firstfree)--;
	}
	Rehash(true);
	return NewSlot(key, val);
}

SQInteger SQTable::Next(bool getweakrefs,const SQObjectPtr &refpos, SQObjectPtr &outkey, SQObjectPtr &outval)
{
	SQInteger idx = (SQInteger)TranslateIndex(refpos);
	while (idx < _numofnodes) {
		if(type(_nodes[idx].key) != OT_NULL) {
			//first found
			_HashNode &n = _nodes[idx];
			outkey = n.key;
			outval = getweakrefs?(SQObject)n.val:_realval(n.val);
			//return idx for the next iteration
			return ++idx;
		}
		++idx;
	}
	//nothing to iterate anymore
	return -1;
}


bool SQTable::Set(const SQObjectPtr &key, const SQObjectPtr &val)
{
	_HashNode *n = _Get(key, HashObj(key) & (_numofnodes - 1));
	if (n) {
		n->val = val;
		return true;
	}
	return false;
}

void SQTable::_ClearNodes()
{
	for(SQInteger i = 0;i < _numofnodes; i++) { _HashNode &n = _nodes[i]; n.key.Null(); n.val.Null(); }
}

void SQTable::Finalize()
{
	_ClearNodes();
	SetDelegate(NULL);
}

void SQTable::Clear()
{
	_ClearNodes();
	_usednodes = 0;
	Rehash(true);
}

// ******************************** sqvm.cpp ********************************
/*
	see copyright notice in squirrel.h
*/
// ---- #include "sqpcheader.h"
// ---> including sqpcheader.h
// <--- back to sqvm.cpp
#include <math.h>
#include <stdlib.h>
// ---- #include "sqopcodes.h"
// ---> including sqopcodes.h
// <--- back to sqvm.cpp
// ---- #include "sqvm.h"
// ---> including sqvm.h
// <--- back to sqvm.cpp
// ---- #include "sqfuncproto.h"
// ---> including sqfuncproto.h
// <--- back to sqvm.cpp
// ---- #include "sqclosure.h"
// ---> including sqclosure.h
// <--- back to sqvm.cpp
// ---- #include "sqstring.h"
// ---> including sqstring.h
// <--- back to sqvm.cpp
// ---- #include "sqtable.h"
// ---> including sqtable.h
// <--- back to sqvm.cpp
// ---- #include "squserdata.h"
// ---> including squserdata.h
// <--- back to sqvm.cpp
// ---- #include "sqarray.h"
// ---> including sqarray.h
// <--- back to sqvm.cpp
// ---- #include "sqclass.h"
// ---> including sqclass.h
// <--- back to sqvm.cpp

#define TOP() (_stack._vals[_top-1])

bool SQVM::BW_OP(SQUnsignedInteger op,SQObjectPtr &trg,const SQObjectPtr &o1,const SQObjectPtr &o2)
{
	SQInteger res;
	if((type(o1)|type(o2)) == OT_INTEGER)
	{
		SQInteger i1 = _integer(o1), i2 = _integer(o2);
		switch(op) {
			case BW_AND:	res = i1 & i2; break;
			case BW_OR:		res = i1 | i2; break;
			case BW_XOR:	res = i1 ^ i2; break;
			case BW_SHIFTL:	res = i1 << i2; break;
			case BW_SHIFTR:	res = i1 >> i2; break;
			case BW_USHIFTR:res = (SQInteger)(*((SQUnsignedInteger*)&i1) >> i2); break;
			default: { Raise_Error(_SC("internal vm error bitwise op failed")); return false; }
		}
	} 
	else { Raise_Error(_SC("bitwise op between '%s' and '%s'"),GetTypeName(o1),GetTypeName(o2)); return false;}
	trg = res;
	return true;
}

#define _ARITH_(op,trg,o1,o2) \
{ \
	SQInteger tmask = type(o1)|type(o2); \
	switch(tmask) { \
		case OT_INTEGER: trg = _integer(o1) op _integer(o2);break; \
		case (OT_FLOAT|OT_INTEGER): \
		case (OT_FLOAT): trg = tofloat(o1) op tofloat(o2); break;\
		default: _GUARD(ARITH_OP((#op)[0],trg,o1,o2)); break;\
	} \
}

#define _ARITH_NOZERO(op,trg,o1,o2,err) \
{ \
	SQInteger tmask = type(o1)|type(o2); \
	switch(tmask) { \
		case OT_INTEGER: { SQInteger i2 = _integer(o2); if(i2 == 0) { Raise_Error(err); SQ_THROW(); } trg = _integer(o1) op i2; } break;\
		case (OT_FLOAT|OT_INTEGER): \
		case (OT_FLOAT): trg = tofloat(o1) op tofloat(o2); break;\
		default: _GUARD(ARITH_OP((#op)[0],trg,o1,o2)); break;\
	} \
}

bool SQVM::ARITH_OP(SQUnsignedInteger op,SQObjectPtr &trg,const SQObjectPtr &o1,const SQObjectPtr &o2)
{
	SQInteger tmask = type(o1)|type(o2);
	switch(tmask) {
		case OT_INTEGER:{
			SQInteger res, i1 = _integer(o1), i2 = _integer(o2);
			switch(op) {
			case '+': res = i1 + i2; break;
			case '-': res = i1 - i2; break;
			case '/': if(i2 == 0) { Raise_Error(_SC("division by zero")); return false; }
					res = i1 / i2; 
					break;
			case '*': res = i1 * i2; break;
			case '%': if(i2 == 0) { Raise_Error(_SC("modulo by zero")); return false; }
					res = i1 % i2; 
					break;
			default: res = 0xDEADBEEF;
			}
			trg = res; }
			break;
		case (OT_FLOAT|OT_INTEGER):
		case (OT_FLOAT):{
			SQFloat res, f1 = tofloat(o1), f2 = tofloat(o2);
			switch(op) {
			case '+': res = f1 + f2; break;
			case '-': res = f1 - f2; break;
			case '/': res = f1 / f2; break;
			case '*': res = f1 * f2; break;
			case '%': res = SQFloat(fmod((double)f1,(double)f2)); break;
			default: res = 0x0f;
			}
			trg = res; }
			break;
		default:
			if(op == '+' &&	(tmask & _RT_STRING)){
				if(!StringCat(o1, o2, trg)) return false;
			}
			else if(!ArithMetaMethod(op,o1,o2,trg)) { 
				return false; 
			}
	}
	return true;
}

SQVM::SQVM(SQSharedState *ss)
{
	_sharedstate=ss;
	_suspended = SQFalse;
	_suspended_target = -1;
	_suspended_root = SQFalse;
	_suspended_traps = -1;
	_foreignptr = NULL;
	_nnativecalls = 0;
	_nmetamethodscall = 0;
	_lasterror.Null();
	_errorhandler.Null();
	_debughook = false;
	_debughook_native = NULL;
	_debughook_closure.Null();
	_openouters = NULL;
	ci = NULL;
	INIT_CHAIN();ADD_TO_CHAIN(&_ss(this)->_gc_chain,this);
}

void SQVM::Finalize()
{
	if(_openouters) CloseOuters(&_stack._vals[0]);
	_roottable.Null();
	_lasterror.Null();
	_errorhandler.Null();
	_debughook = false;
	_debughook_native = NULL;
	_debughook_closure.Null();
	temp_reg.Null();
	_callstackdata.resize(0);
	SQInteger size=_stack.size();
	for(SQInteger i=0;i<size;i++)
		_stack[i].Null();
}

SQVM::~SQVM()
{
	Finalize();
	REMOVE_FROM_CHAIN(&_ss(this)->_gc_chain,this);
}

bool SQVM::ArithMetaMethod(SQInteger op,const SQObjectPtr &o1,const SQObjectPtr &o2,SQObjectPtr &dest)
{
	SQMetaMethod mm;
	switch(op){
		case _SC('+'): mm=MT_ADD; break;
		case _SC('-'): mm=MT_SUB; break;
		case _SC('/'): mm=MT_DIV; break;
		case _SC('*'): mm=MT_MUL; break;
		case _SC('%'): mm=MT_MODULO; break;
		default: mm = MT_ADD; assert(0); break; //shutup compiler
	}
	if(is_delegable(o1) && _delegable(o1)->_delegate) {
		
		SQObjectPtr closure;
		if(_delegable(o1)->GetMetaMethod(this, mm, closure)) {
			Push(o1);Push(o2);
			return CallMetaMethod(closure,mm,2,dest);
		}
	}
	Raise_Error(_SC("arith op %c on between '%s' and '%s'"),op,GetTypeName(o1),GetTypeName(o2)); 
	return false;
}

bool SQVM::NEG_OP(SQObjectPtr &trg,const SQObjectPtr &o)
{
	
	switch(type(o)) {
	case OT_INTEGER:
		trg = -_integer(o);
		return true;
	case OT_FLOAT:
		trg = -_float(o);
		return true;
	case OT_TABLE:
	case OT_USERDATA:
	case OT_INSTANCE:
		if(_delegable(o)->_delegate) {
			SQObjectPtr closure;
			if(_delegable(o)->GetMetaMethod(this, MT_UNM, closure)) {
				Push(o);
				if(!CallMetaMethod(closure, MT_UNM, 1, temp_reg)) return false;
				_Swap(trg,temp_reg);
				return true;

			}
		}
	default:break; //shutup compiler
	}
	Raise_Error(_SC("attempt to negate a %s"), GetTypeName(o));
	return false;
}

#define _RET_SUCCEED(exp) { result = (exp); return true; } 
bool SQVM::ObjCmp(const SQObjectPtr &o1,const SQObjectPtr &o2,SQInteger &result)
{
	SQObjectType t1 = type(o1), t2 = type(o2);
	if(t1 == t2) {
		if(_rawval(o1) == _rawval(o2))_RET_SUCCEED(0);
		SQObjectPtr res;
		switch(t1){
		case OT_STRING:
			_RET_SUCCEED(scstrcmp(_stringval(o1),_stringval(o2)));
		case OT_INTEGER:
			_RET_SUCCEED((_integer(o1)<_integer(o2))?-1:1);
		case OT_FLOAT:
			_RET_SUCCEED((_float(o1)<_float(o2))?-1:1);
		case OT_TABLE:
		case OT_USERDATA:
		case OT_INSTANCE:
			if(_delegable(o1)->_delegate) {
				SQObjectPtr closure;
				if(_delegable(o1)->GetMetaMethod(this, MT_CMP, closure)) {
					Push(o1);Push(o2);
					if(CallMetaMethod(closure,MT_CMP,2,res)) {
						if(type(res) != OT_INTEGER) {
							Raise_Error(_SC("_cmp must return an integer"));
							return false;
						}
						_RET_SUCCEED(_integer(res))
					}
					return false;
				}
			}
			//continues through (no break needed)
		default: 
			_RET_SUCCEED( _userpointer(o1) < _userpointer(o2)?-1:1 );
		}
		assert(0);
		//if(type(res)!=OT_INTEGER) { Raise_CompareError(o1,o2); return false; }
		//	_RET_SUCCEED(_integer(res));
		
	}
	else{
		if(sq_isnumeric(o1) && sq_isnumeric(o2)){
			if((t1==OT_INTEGER) && (t2==OT_FLOAT)) { 
				if( _integer(o1)==_float(o2) ) { _RET_SUCCEED(0); }
				else if( _integer(o1)<_float(o2) ) { _RET_SUCCEED(-1); }
				_RET_SUCCEED(1);
			}
			else{
				if( _float(o1)==_integer(o2) ) { _RET_SUCCEED(0); }
				else if( _float(o1)<_integer(o2) ) { _RET_SUCCEED(-1); }
				_RET_SUCCEED(1);
			}
		}
		else if(t1==OT_NULL) {_RET_SUCCEED(-1);}
		else if(t2==OT_NULL) {_RET_SUCCEED(1);}
		else { Raise_CompareError(o1,o2); return false; }
		
	}
	assert(0);
	_RET_SUCCEED(0); //cannot happen
}

bool SQVM::CMP_OP(CmpOP op, const SQObjectPtr &o1,const SQObjectPtr &o2,SQObjectPtr &res)
{
	SQInteger r;
	if(ObjCmp(o1,o2,r)) {
		switch(op) {
			case CMP_G: res = (r > 0); return true;
			case CMP_GE: res = (r >= 0); return true;
			case CMP_L: res = (r < 0); return true;
			case CMP_LE: res = (r <= 0); return true;
			case CMP_3W: res = r; return true;
		}
		assert(0);
	}
	return false;
}

bool SQVM::ToString(const SQObjectPtr &o,SQObjectPtr &res)
{
	switch(type(o)) {
	case OT_STRING:
		res = o;
		return true;
	case OT_FLOAT:
		scsprintf(_sp(rsl(NUMBER_MAX_CHAR+1)),_SC("%g"),_float(o));
		break;
	case OT_INTEGER:
		scsprintf(_sp(rsl(NUMBER_MAX_CHAR+1)),_PRINT_INT_FMT,_integer(o));
		break;
	case OT_BOOL:
		scsprintf(_sp(rsl(6)),_integer(o)?_SC("true"):_SC("false"));
		break;
	case OT_TABLE:
	case OT_USERDATA:
	case OT_INSTANCE:
		if(_delegable(o)->_delegate) {
			SQObjectPtr closure;
			if(_delegable(o)->GetMetaMethod(this, MT_TOSTRING, closure)) {
				Push(o);
				if(CallMetaMethod(closure,MT_TOSTRING,1,res)) {;
					if(type(res) == OT_STRING)
						return true;
				} 
				else {
					return false;
				}
			}
		}
	default:
		scsprintf(_sp(rsl(sizeof(void*)+20)),_SC("(%s : 0x%p)"),GetTypeName(o),(void*)_rawval(o));
	}
	res = SQString::Create(_ss(this),_spval);
	return true;
}


bool SQVM::StringCat(const SQObjectPtr &str,const SQObjectPtr &obj,SQObjectPtr &dest)
{
	SQObjectPtr a, b;
	if(!ToString(str, a)) return false;
	if(!ToString(obj, b)) return false;
	SQInteger l = _string(a)->_len , ol = _string(b)->_len;
	SQChar *s = _sp(rsl(l + ol + 1));
	memcpy(s, _stringval(a), rsl(l)); 
	memcpy(s + l, _stringval(b), rsl(ol));
	dest = SQString::Create(_ss(this), _spval, l + ol);
	return true;
}

bool SQVM::TypeOf(const SQObjectPtr &obj1,SQObjectPtr &dest)
{
	if(is_delegable(obj1) && _delegable(obj1)->_delegate) {
		SQObjectPtr closure;
		if(_delegable(obj1)->GetMetaMethod(this, MT_TYPEOF, closure)) {
			Push(obj1);
			return CallMetaMethod(closure,MT_TYPEOF,1,dest);
		}
	}
	dest = SQString::Create(_ss(this),GetTypeName(obj1));
	return true;
}

bool SQVM::Init(SQVM *friendvm, SQInteger stacksize)
{
	_stack.resize(stacksize);
	_alloccallsstacksize = 4;
	_callstackdata.resize(_alloccallsstacksize);
	_callsstacksize = 0;
	_callsstack = &_callstackdata[0];
	_stackbase = 0;
	_top = 0;
	if(!friendvm) 
		_roottable = SQTable::Create(_ss(this), 0);
	else {
		_roottable = friendvm->_roottable;
		_errorhandler = friendvm->_errorhandler;
		_debughook = friendvm->_debughook;
		_debughook_native = friendvm->_debughook_native;
		_debughook_closure = friendvm->_debughook_closure;
	}
	
	sq_base_register(this);
	return true;
}


bool SQVM::StartCall(SQClosure *closure,SQInteger target,SQInteger args,SQInteger stackbase,bool tailcall)
{
	SQFunctionProto *func = closure->_function;

	SQInteger paramssize = func->_nparameters;
	const SQInteger newtop = stackbase + func->_stacksize;
	SQInteger nargs = args;
	if(func->_varparams)
	{
		paramssize--;
		if (nargs < paramssize) {
			Raise_Error(_SC("wrong number of parameters"));
			return false;
		}

		//dumpstack(stackbase);
		SQInteger nvargs = nargs - paramssize;
		SQArray *arr = SQArray::Create(_ss(this),nvargs);
		SQInteger pbase = stackbase+paramssize;
		for(SQInteger n = 0; n < nvargs; n++) {
			arr->_values[n] = _stack._vals[pbase];
			_stack._vals[pbase].Null();
			pbase++;

		}
		_stack._vals[stackbase+paramssize] = arr;
		//dumpstack(stackbase);
	}
	else if (paramssize != nargs) {
		SQInteger ndef = func->_ndefaultparams;
		SQInteger diff;
		if(ndef && nargs < paramssize && (diff = paramssize - nargs) <= ndef) {
			for(SQInteger n = ndef - diff; n < ndef; n++) {
				_stack._vals[stackbase + (nargs++)] = closure->_defaultparams[n];
			}
		}
		else {
			Raise_Error(_SC("wrong number of parameters"));
			return false;
		}
	}

	if(closure->_env) {
		_stack._vals[stackbase] = closure->_env->_obj;
	}

	if(!EnterFrame(stackbase, newtop, tailcall)) return false;

	ci->_closure  = closure;
	ci->_literals = func->_literals;
	ci->_ip       = func->_instructions;
	ci->_target   = (SQInt32)target;

	if (_debughook) {
		CallDebugHook(_SC('c'));
	}

	if (closure->_function->_bgenerator) {
		SQFunctionProto *f = closure->_function;
		SQGenerator *gen = SQGenerator::Create(_ss(this), closure);
		if(!gen->Yield(this,f->_stacksize))
			return false;
		SQObjectPtr temp;
		Return(1, target, temp);
		STK(target) = gen;
	}


	return true;
}

bool SQVM::Return(SQInteger _arg0, SQInteger _arg1, SQObjectPtr &retval)
{
	SQBool    _isroot      = ci->_root;
	SQInteger callerbase   = _stackbase - ci->_prevstkbase;

	if (_debughook) {
		for(SQInteger i=0; i<ci->_ncalls; i++) {
			CallDebugHook(_SC('r'));
		}
	}

	SQObjectPtr *dest;
	if (_isroot) {
		dest = &(retval);
	} else if (ci->_target == -1) {
		dest = NULL;
	} else {
		dest = &_stack._vals[callerbase + ci->_target];
	}
	if (dest) {
		if(_arg0 != 0xFF) {
			*dest = _stack._vals[_stackbase+_arg1];
		}
		else {
			dest->Null();
		}
		//*dest = (_arg0 != 0xFF) ? _stack._vals[_stackbase+_arg1] : _null_;
	}
	LeaveFrame();
	return _isroot ? true : false;
}

#define _RET_ON_FAIL(exp) { if(!exp) return false; }

bool SQVM::PLOCAL_INC(SQInteger op,SQObjectPtr &target, SQObjectPtr &a, SQObjectPtr &incr)
{
 	SQObjectPtr trg;
	_RET_ON_FAIL(ARITH_OP( op , trg, a, incr));
	target = a;
	a = trg;
	return true;
}

bool SQVM::DerefInc(SQInteger op,SQObjectPtr &target, SQObjectPtr &self, SQObjectPtr &key, SQObjectPtr &incr, bool postfix,SQInteger selfidx)
{
	SQObjectPtr tmp, tself = self, tkey = key;
	if (!Get(tself, tkey, tmp, false, selfidx)) { return false; }
	_RET_ON_FAIL(ARITH_OP( op , target, tmp, incr))
	if (!Set(tself, tkey, target,selfidx)) { return false; }
	if (postfix) target = tmp;
	return true;
}

#define arg0 (_i_._arg0)
#define sarg0 ((SQInteger)*((signed char *)&_i_._arg0))
#define arg1 (_i_._arg1)
#define sarg1 (*((SQInt32 *)&_i_._arg1))
#define arg2 (_i_._arg2)
#define arg3 (_i_._arg3)
#define sarg3 ((SQInteger)*((signed char *)&_i_._arg3))

SQRESULT SQVM::Suspend()
{
	if (_suspended)
		return sq_throwerror(this, _SC("cannot suspend an already suspended vm"));
	if (_nnativecalls!=2)
		return sq_throwerror(this, _SC("cannot suspend through native calls/metamethods"));
	return SQ_SUSPEND_FLAG;
}


#define _FINISH(howmuchtojump) {jump = howmuchtojump; return true; }
bool SQVM::FOREACH_OP(SQObjectPtr &o1,SQObjectPtr &o2,SQObjectPtr 
&o3,SQObjectPtr &o4,SQInteger arg_2,int exitpos,int &jump)
{
	SQInteger nrefidx;
	switch(type(o1)) {
	case OT_TABLE:
		if((nrefidx = _table(o1)->Next(false,o4, o2, o3)) == -1) _FINISH(exitpos);
		o4 = (SQInteger)nrefidx; _FINISH(1);
	case OT_ARRAY:
		if((nrefidx = _array(o1)->Next(o4, o2, o3)) == -1) _FINISH(exitpos);
		o4 = (SQInteger) nrefidx; _FINISH(1);
	case OT_STRING:
		if((nrefidx = _string(o1)->Next(o4, o2, o3)) == -1)_FINISH(exitpos);
		o4 = (SQInteger)nrefidx; _FINISH(1);
	case OT_CLASS:
		if((nrefidx = _class(o1)->Next(o4, o2, o3)) == -1)_FINISH(exitpos);
		o4 = (SQInteger)nrefidx; _FINISH(1);
	case OT_USERDATA:
	case OT_INSTANCE:
		if(_delegable(o1)->_delegate) {
			SQObjectPtr itr;
			SQObjectPtr closure;
			if(_delegable(o1)->GetMetaMethod(this, MT_NEXTI, closure)) {
				Push(o1);
				Push(o4);
				if(CallMetaMethod(closure, MT_NEXTI, 2, itr)) {
					o4 = o2 = itr;
					if(type(itr) == OT_NULL) _FINISH(exitpos);
					if(!Get(o1, itr, o3, false, DONT_FALL_BACK)) {
						Raise_Error(_SC("_nexti returned an invalid idx")); // cloud be changed
						return false;
					}
					_FINISH(1);
				}
				else {
					return false;
				}
			}
			Raise_Error(_SC("_nexti failed"));
			return false;
		}
		break;
	case OT_GENERATOR:
		if(_generator(o1)->_state == SQGenerator::eDead) _FINISH(exitpos);
		if(_generator(o1)->_state == SQGenerator::eSuspended) {
			SQInteger idx = 0;
			if(type(o4) == OT_INTEGER) {
				idx = _integer(o4) + 1;
			}
			o2 = idx;
			o4 = idx;
			_generator(o1)->Resume(this, o3);
			_FINISH(0);
		}
	default: 
		Raise_Error(_SC("cannot iterate %s"), GetTypeName(o1));
	}
	return false; //cannot be hit(just to avoid warnings)
}

#define COND_LITERAL (arg3!=0?ci->_literals[arg1]:STK(arg1))

#define SQ_THROW() { goto exception_trap; }

#define _GUARD(exp) { if(!exp) { SQ_THROW();} }

bool SQVM::CLOSURE_OP(SQObjectPtr &target, SQFunctionProto *func)
{
	SQInteger nouters;
	SQClosure *closure = SQClosure::Create(_ss(this), func);
	if((nouters = func->_noutervalues)) {
		for(SQInteger i = 0; i<nouters; i++) {
			SQOuterVar &v = func->_outervalues[i];
			switch(v._type){
			case otLOCAL:
				FindOuter(closure->_outervalues[i], &STK(_integer(v._src)));
				break;
			case otOUTER:
				closure->_outervalues[i] = _closure(ci->_closure)->_outervalues[_integer(v._src)];
				break;
			}
		}
	}
	SQInteger ndefparams;
	if((ndefparams = func->_ndefaultparams)) {
		for(SQInteger i = 0; i < ndefparams; i++) {
			SQInteger spos = func->_defaultparams[i];
			closure->_defaultparams[i] = _stack._vals[_stackbase + spos];
		}
	}
	target = closure;
	return true;

}


bool SQVM::CLASS_OP(SQObjectPtr &target,SQInteger baseclass,SQInteger attributes)
{
	SQClass *base = NULL;
	SQObjectPtr attrs;
	if(baseclass != -1) {
		if(type(_stack._vals[_stackbase+baseclass]) != OT_CLASS) { Raise_Error(_SC("trying to inherit from a %s"),GetTypeName(_stack._vals[_stackbase+baseclass])); return false; }
		base = _class(_stack._vals[_stackbase + baseclass]);
	}
	if(attributes != MAX_FUNC_STACKSIZE) {
		attrs = _stack._vals[_stackbase+attributes];
	}
	target = SQClass::Create(_ss(this),base);
	if(type(_class(target)->_metamethods[MT_INHERITED]) != OT_NULL) {
		int nparams = 2;
		SQObjectPtr ret;
		Push(target); Push(attrs);
		Call(_class(target)->_metamethods[MT_INHERITED],nparams,_top - nparams, ret, false);
		Pop(nparams);
	}
	_class(target)->_attributes = attrs;
	return true;
}

bool SQVM::IsEqual(const SQObjectPtr &o1,const SQObjectPtr &o2,bool &res)
{
	if(type(o1) == type(o2)) {
		res = (_rawval(o1) == _rawval(o2));
	}
	else {
		if(sq_isnumeric(o1) && sq_isnumeric(o2)) {
			res = (tofloat(o1) == tofloat(o2));
		}
		else {
			res = false;
		}
	}
	return true;
}

bool SQVM::IsFalse(SQObjectPtr &o)
{
	if(((type(o) & SQOBJECT_CANBEFALSE) 
		&& ( ((type(o) == OT_FLOAT) && (_float(o) == SQFloat(0.0))) ))
#if !defined(SQUSEDOUBLE) || (defined(SQUSEDOUBLE) && defined(_SQ64))
		|| (_integer(o) == 0) )  //OT_NULL|OT_INTEGER|OT_BOOL
#else
		|| (((type(o) != OT_FLOAT) && (_integer(o) == 0))) )  //OT_NULL|OT_INTEGER|OT_BOOL
#endif
	{
		return true;
	}
	return false;
}

bool SQVM::Execute(SQObjectPtr &closure, SQInteger nargs, SQInteger stackbase,SQObjectPtr &outres, SQBool raiseerror,ExecutionType et)
{
	if ((_nnativecalls + 1) > MAX_NATIVE_CALLS) { Raise_Error(_SC("Native stack overflow")); return false; }
	_nnativecalls++;
	AutoDec ad(&_nnativecalls);
	SQInteger traps = 0;
	CallInfo *prevci = ci;
		
	switch(et) {
		case ET_CALL: {
			temp_reg = closure;
			if(!StartCall(_closure(temp_reg), _top - nargs, nargs, stackbase, false)) { 
				//call the handler if there are no calls in the stack, if not relies on the previous node
				if(ci == NULL) CallErrorHandler(_lasterror);
				return false;
			}
			if(ci == prevci) {
				outres = STK(_top-nargs);
				return true;
			}
			ci->_root = SQTrue;
					  }
			break;
		case ET_RESUME_GENERATOR: _generator(closure)->Resume(this, outres); ci->_root = SQTrue; traps += ci->_etraps; break;
		case ET_RESUME_VM:
		case ET_RESUME_THROW_VM:
			traps = _suspended_traps;
			ci->_root = _suspended_root;
			_suspended = SQFalse;
			if(et  == ET_RESUME_THROW_VM) { SQ_THROW(); }
			break;
	}
	
exception_restore:
	//
	{
		for(;;)
		{
			const SQInstruction &_i_ = *ci->_ip++;
			//dumpstack(_stackbase);
			//scprintf("\n[%d] %s %d %d %d %d\n",ci->_ip-ci->_iv->_vals,g_InstrDesc[_i_.op].name,arg0,arg1,arg2,arg3);
			switch(_i_.op)
			{
			case _OP_LINE: if (_debughook) CallDebugHook(_SC('l'),arg1); continue;
			case _OP_LOAD: TARGET = ci->_literals[arg1]; continue;
			case _OP_LOADINT: 
#ifndef _SQ64
				TARGET = (SQInteger)arg1; continue;
#else
				TARGET = (SQInteger)((SQUnsignedInteger32)arg1); continue;
#endif
			case _OP_LOADFLOAT: TARGET = *((SQFloat *)&arg1); continue;
			case _OP_DLOAD: TARGET = ci->_literals[arg1]; STK(arg2) = ci->_literals[arg3];continue;
			case _OP_TAILCALL:{
				SQObjectPtr &t = STK(arg1);
				if (type(t) == OT_CLOSURE 
					&& (!_closure(t)->_function->_bgenerator)){
					SQObjectPtr clo = t;
					if(_openouters) CloseOuters(&(_stack._vals[_stackbase]));
					for (SQInteger i = 0; i < arg3; i++) STK(i) = STK(arg2 + i);
					_GUARD(StartCall(_closure(clo), ci->_target, arg3, _stackbase, true));
					continue;
				}
							  }
			case _OP_CALL: {
					SQObjectPtr clo = STK(arg1);
					switch (type(clo)) {
					case OT_CLOSURE:
						_GUARD(StartCall(_closure(clo), sarg0, arg3, _stackbase+arg2, false));
						continue;
					case OT_NATIVECLOSURE: {
						bool suspend;
						_GUARD(CallNative(_nativeclosure(clo), arg3, _stackbase+arg2, clo,suspend));
						if(suspend){
							_suspended = SQTrue;
							_suspended_target = sarg0;
							_suspended_root = ci->_root;
							_suspended_traps = traps;
							outres = clo;
							return true;
						}
						if(sarg0 != -1) {
							STK(arg0) = clo;
						}
										   }
						continue;
					case OT_CLASS:{
						SQObjectPtr inst;
						_GUARD(CreateClassInstance(_class(clo),inst,clo));
						if(sarg0 != -1) {
							STK(arg0) = inst;
						}
						SQInteger stkbase;
						switch(type(clo)) {
							case OT_CLOSURE:
								stkbase = _stackbase+arg2;
								_stack._vals[stkbase] = inst;
								_GUARD(StartCall(_closure(clo), -1, arg3, stkbase, false));
								break;
							case OT_NATIVECLOSURE:
								bool suspend;
								stkbase = _stackbase+arg2;
								_stack._vals[stkbase] = inst;
								_GUARD(CallNative(_nativeclosure(clo), arg3, stkbase, clo,suspend));
								break;
							default: break; //shutup GCC 4.x
						}
						}
						break;
					case OT_TABLE:
					case OT_USERDATA:
					case OT_INSTANCE:{
						SQObjectPtr closure;
						if(_delegable(clo)->_delegate && _delegable(clo)->GetMetaMethod(this,MT_CALL,closure)) {
							Push(clo);
							for (SQInteger i = 0; i < arg3; i++) Push(STK(arg2 + i));
							if(!CallMetaMethod(closure, MT_CALL, arg3+1, clo)) SQ_THROW();
							if(sarg0 != -1) {
								STK(arg0) = clo;
							}
							break;
						}
									 
						//Raise_Error(_SC("attempt to call '%s'"), GetTypeName(clo));
						//SQ_THROW();
					  }
					default:
						Raise_Error(_SC("attempt to call '%s'"), GetTypeName(clo));
						SQ_THROW();
					}
				}
				  continue;
			case _OP_PREPCALL:
			case _OP_PREPCALLK:	{
					SQObjectPtr &key = _i_.op == _OP_PREPCALLK?(ci->_literals)[arg1]:STK(arg1);
					SQObjectPtr &o = STK(arg2);
					if (!Get(o, key, temp_reg,false,arg2)) {
						SQ_THROW();
					}
					STK(arg3) = o;
					_Swap(TARGET,temp_reg);//TARGET = temp_reg;
				}
				continue;
			case _OP_GETK:
				if (!Get(STK(arg2), ci->_literals[arg1], temp_reg, false,arg2)) { SQ_THROW();}
				_Swap(TARGET,temp_reg);//TARGET = temp_reg;
				continue;
			case _OP_MOVE: TARGET = STK(arg1); continue;
			case _OP_NEWSLOT:
				_GUARD(NewSlot(STK(arg1), STK(arg2), STK(arg3),false));
				if(arg0 != 0xFF) TARGET = STK(arg3);
				continue;
			case _OP_DELETE: _GUARD(DeleteSlot(STK(arg1), STK(arg2), TARGET)); continue;
			case _OP_SET:
				if (!Set(STK(arg1), STK(arg2), STK(arg3),arg1)) { SQ_THROW(); }
				if (arg0 != 0xFF) TARGET = STK(arg3);
				continue;
			case _OP_GET:
				if (!Get(STK(arg1), STK(arg2), temp_reg, false,arg1)) { SQ_THROW(); }
				_Swap(TARGET,temp_reg);//TARGET = temp_reg;
				continue;
			case _OP_EQ:{
				bool res;
				if(!IsEqual(STK(arg2),COND_LITERAL,res)) { SQ_THROW(); }
				TARGET = res?true:false;
				}continue;
			case _OP_NE:{ 
				bool res;
				if(!IsEqual(STK(arg2),COND_LITERAL,res)) { SQ_THROW(); }
				TARGET = (!res)?true:false;
				} continue;
			case _OP_ADD: _ARITH_(+,TARGET,STK(arg2),STK(arg1)); continue;
			case _OP_SUB: _ARITH_(-,TARGET,STK(arg2),STK(arg1)); continue;
			case _OP_MUL: _ARITH_(*,TARGET,STK(arg2),STK(arg1)); continue;
			case _OP_DIV: _ARITH_NOZERO(/,TARGET,STK(arg2),STK(arg1),_SC("division by zero")); continue;
			case _OP_MOD: ARITH_OP('%',TARGET,STK(arg2),STK(arg1)); continue;
			case _OP_BITW:	_GUARD(BW_OP( arg3,TARGET,STK(arg2),STK(arg1))); continue;
			case _OP_RETURN:
				if((ci)->_generator) {
					(ci)->_generator->Kill();
				}
				if(Return(arg0, arg1, temp_reg)){
					assert(traps==0);
					//outres = temp_reg;
					_Swap(outres,temp_reg);
					return true;
				}
				continue;
			case _OP_LOADNULLS:{ for(SQInt32 n=0; n < arg1; n++) STK(arg0+n).Null(); }continue;
			case _OP_LOADROOT:	TARGET = _roottable; continue;
			case _OP_LOADBOOL: TARGET = arg1?true:false; continue;
			case _OP_DMOVE: STK(arg0) = STK(arg1); STK(arg2) = STK(arg3); continue;
			case _OP_JMP: ci->_ip += (sarg1); continue;
			//case _OP_JNZ: if(!IsFalse(STK(arg0))) ci->_ip+=(sarg1); continue;
			case _OP_JCMP: 
				_GUARD(CMP_OP((CmpOP)arg3,STK(arg2),STK(arg0),temp_reg));
				if(IsFalse(temp_reg)) ci->_ip+=(sarg1);
				continue;
			case _OP_JZ: if(IsFalse(STK(arg0))) ci->_ip+=(sarg1); continue;
			case _OP_GETOUTER: {
				SQClosure *cur_cls = _closure(ci->_closure);
				SQOuter *otr = _outer(cur_cls->_outervalues[arg1]);
				TARGET = *(otr->_valptr);
				}
			continue;
			case _OP_SETOUTER: {
				SQClosure *cur_cls = _closure(ci->_closure);
				SQOuter   *otr = _outer(cur_cls->_outervalues[arg1]);
				*(otr->_valptr) = STK(arg2);
				if(arg0 != 0xFF) {
					TARGET = STK(arg2);
				}
				}
			continue;
			case _OP_NEWOBJ: 
				switch(arg3) {
					case NOT_TABLE: TARGET = SQTable::Create(_ss(this), arg1); continue;
					case NOT_ARRAY: TARGET = SQArray::Create(_ss(this), 0); _array(TARGET)->Reserve(arg1); continue;
					case NOT_CLASS: _GUARD(CLASS_OP(TARGET,arg1,arg2)); continue;
					default: assert(0); continue;
				}
			case _OP_APPENDARRAY: 
				{
					SQObject val;
					val._unVal.raw = 0;
				switch(arg2) {
				case AAT_STACK:
					val = STK(arg1); break;
				case AAT_LITERAL:
					val = ci->_literals[arg1]; break;
				case AAT_INT:
					val._type = OT_INTEGER;
#ifndef _SQ64
					val._unVal.nInteger = (SQInteger)arg1; 
#else
					val._unVal.nInteger = (SQInteger)((SQUnsignedInteger32)arg1);
#endif
					break;
				case AAT_FLOAT:
					val._type = OT_FLOAT;
					val._unVal.fFloat = *((SQFloat *)&arg1);
					break;
				case AAT_BOOL:
					val._type = OT_BOOL;
					val._unVal.nInteger = arg1;
					break;
				default: assert(0); break;

				}
				_array(STK(arg0))->Append(val);	continue;
				}
			case _OP_COMPARITH: {
				SQInteger selfidx = (((SQUnsignedInteger)arg1&0xFFFF0000)>>16);
				_GUARD(DerefInc(arg3, TARGET, STK(selfidx), STK(arg2), STK(arg1&0x0000FFFF), false, selfidx)); 
								}
				continue;
			case _OP_INC: {SQObjectPtr o(sarg3); _GUARD(DerefInc('+',TARGET, STK(arg1), STK(arg2), o, false, arg1));} continue;
			case _OP_INCL: {
				SQObjectPtr &a = STK(arg1);
				if(type(a) == OT_INTEGER) {
					a._unVal.nInteger = _integer(a) + sarg3;
				}
				else {
					SQObjectPtr o(sarg3); //_GUARD(LOCAL_INC('+',TARGET, STK(arg1), o));
					_ARITH_(+,a,a,o);
				}
						   } continue;
			case _OP_PINC: {SQObjectPtr o(sarg3); _GUARD(DerefInc('+',TARGET, STK(arg1), STK(arg2), o, true, arg1));} continue;
			case _OP_PINCL:	{
				SQObjectPtr &a = STK(arg1);
				if(type(a) == OT_INTEGER) {
					TARGET = a;
					a._unVal.nInteger = _integer(a) + sarg3;
				}
				else {
					SQObjectPtr o(sarg3); _GUARD(PLOCAL_INC('+',TARGET, STK(arg1), o));
				}
				
						} continue;
			case _OP_CMP:	_GUARD(CMP_OP((CmpOP)arg3,STK(arg2),STK(arg1),TARGET))	continue;
			case _OP_EXISTS: TARGET = Get(STK(arg1), STK(arg2), temp_reg, true,DONT_FALL_BACK)?true:false;continue;
			case _OP_INSTANCEOF: 
				if(type(STK(arg1)) != OT_CLASS)
				{Raise_Error(_SC("cannot apply instanceof between a %s and a %s"),GetTypeName(STK(arg1)),GetTypeName(STK(arg2))); SQ_THROW();}
				TARGET = (type(STK(arg2)) == OT_INSTANCE) ? (_instance(STK(arg2))->InstanceOf(_class(STK(arg1)))?true:false) : false;
				continue;
			case _OP_AND: 
				if(IsFalse(STK(arg2))) {
					TARGET = STK(arg2);
					ci->_ip += (sarg1);
				}
				continue;
			case _OP_OR:
				if(!IsFalse(STK(arg2))) {
					TARGET = STK(arg2);
					ci->_ip += (sarg1);
				}
				continue;
			case _OP_NEG: _GUARD(NEG_OP(TARGET,STK(arg1))); continue;
			case _OP_NOT: TARGET = IsFalse(STK(arg1)); continue;
			case _OP_BWNOT:
				if(type(STK(arg1)) == OT_INTEGER) {
					SQInteger t = _integer(STK(arg1));
					TARGET = SQInteger(~t);
					continue;
				}
				Raise_Error(_SC("attempt to perform a bitwise op on a %s"), GetTypeName(STK(arg1)));
				SQ_THROW();
			case _OP_CLOSURE: {
				SQClosure *c = ci->_closure._unVal.pClosure;
				SQFunctionProto *fp = c->_function;
				if(!CLOSURE_OP(TARGET,fp->_functions[arg1]._unVal.pFunctionProto)) { SQ_THROW(); }
				continue;
			}
			case _OP_YIELD:{
				if(ci->_generator) {
					if(sarg1 != MAX_FUNC_STACKSIZE) temp_reg = STK(arg1);
					_GUARD(ci->_generator->Yield(this,arg2));
					traps -= ci->_etraps;
					if(sarg1 != MAX_FUNC_STACKSIZE) _Swap(STK(arg1),temp_reg);//STK(arg1) = temp_reg;
				}
				else { Raise_Error(_SC("trying to yield a '%s',only genenerator can be yielded"), GetTypeName(ci->_generator)); SQ_THROW();}
				if(Return(arg0, arg1, temp_reg)){
					assert(traps == 0);
					outres = temp_reg;
					return true;
				}
					
				}
				continue;
			case _OP_RESUME:
				if(type(STK(arg1)) != OT_GENERATOR){ Raise_Error(_SC("trying to resume a '%s',only genenerator can be resumed"), GetTypeName(STK(arg1))); SQ_THROW();}
				_GUARD(_generator(STK(arg1))->Resume(this, TARGET));
				traps += ci->_etraps;
                continue;
			case _OP_FOREACH:{ int tojump;
				_GUARD(FOREACH_OP(STK(arg0),STK(arg2),STK(arg2+1),STK(arg2+2),arg2,sarg1,tojump));
				ci->_ip += tojump; }
				continue;
			case _OP_POSTFOREACH:
				assert(type(STK(arg0)) == OT_GENERATOR);
				if(_generator(STK(arg0))->_state == SQGenerator::eDead) 
					ci->_ip += (sarg1 - 1);
				continue;
			case _OP_CLONE: _GUARD(Clone(STK(arg1), TARGET)); continue;
			case _OP_TYPEOF: _GUARD(TypeOf(STK(arg1), TARGET)) continue;
			case _OP_PUSHTRAP:{
				SQInstruction *_iv = _closure(ci->_closure)->_function->_instructions;
				_etraps.push_back(SQExceptionTrap(_top,_stackbase, &_iv[(ci->_ip-_iv)+arg1], arg0)); traps++;
				ci->_etraps++;
							  }
				continue;
			case _OP_POPTRAP: {
				for(SQInteger i = 0; i < arg0; i++) {
					_etraps.pop_back(); traps--;
					ci->_etraps--;
				}
							  }
				continue;
			case _OP_THROW:	Raise_Error(TARGET); SQ_THROW(); continue;
			case _OP_NEWSLOTA:
				_GUARD(NewSlotA(STK(arg1),STK(arg2),STK(arg3),(arg0&NEW_SLOT_ATTRIBUTES_FLAG) ? STK(arg2-1) : SQObjectPtr(),(arg0&NEW_SLOT_STATIC_FLAG)?true:false,false));
				continue;
			case _OP_GETBASE:{
				SQClosure *clo = _closure(ci->_closure);
				if(clo->_base) {
					TARGET = clo->_base;
				}
				else {
					TARGET.Null();
				}
				continue;
			}
			case _OP_CLOSE:
				if(_openouters) CloseOuters(&(STK(arg1)));
				continue;
			}
			
		}
	}
exception_trap:
	{
		SQObjectPtr currerror = _lasterror;
//		dumpstack(_stackbase);
//		SQInteger n = 0;
		SQInteger last_top = _top;
		
		if(_ss(this)->_notifyallexceptions || (!traps && raiseerror)) CallErrorHandler(currerror);

		while( ci ) {
			if(ci->_etraps > 0) {
				SQExceptionTrap &et = _etraps.top();
				ci->_ip = et._ip;
				_top = et._stacksize;
				_stackbase = et._stackbase;
				_stack._vals[_stackbase + et._extarget] = currerror;
				_etraps.pop_back(); traps--; ci->_etraps--;
				while(last_top >= _top) _stack._vals[last_top--].Null();
				goto exception_restore;
			}
			else if (_debughook) { 
					//notify debugger of a "return"
					//even if it really an exception unwinding the stack
					for(SQInteger i = 0; i < ci->_ncalls; i++) {
						CallDebugHook(_SC('r'));
					}
			}
			if(ci->_generator) ci->_generator->Kill();
			bool mustbreak = ci && ci->_root;
			LeaveFrame();
			if(mustbreak) break;
		}
						
		_lasterror = currerror;
		return false;
	}
	assert(0);
}

bool SQVM::CreateClassInstance(SQClass *theclass, SQObjectPtr &inst, SQObjectPtr &constructor)
{
	inst = theclass->CreateInstance();
	if(!theclass->GetConstructor(constructor)) {
		constructor.Null();
	}
	return true;
}

void SQVM::CallErrorHandler(SQObjectPtr &error)
{
	if(type(_errorhandler) != OT_NULL) {
		SQObjectPtr out;
		Push(_roottable); Push(error);
		Call(_errorhandler, 2, _top-2, out,SQFalse);
		Pop(2);
	}
}


void SQVM::CallDebugHook(SQInteger type,SQInteger forcedline)
{
	_debughook = false;
	SQFunctionProto *func=_closure(ci->_closure)->_function;
	if(_debughook_native) {
		const SQChar *src = type(func->_sourcename) == OT_STRING?_stringval(func->_sourcename):NULL;
		const SQChar *fname = type(func->_name) == OT_STRING?_stringval(func->_name):NULL;
		SQInteger line = forcedline?forcedline:func->GetLine(ci->_ip);
		_debughook_native(this,type,src,line,fname);
	}
	else {
		SQObjectPtr temp_reg;
		SQInteger nparams=5;
		Push(_roottable); Push(type); Push(func->_sourcename); Push(forcedline?forcedline:func->GetLine(ci->_ip)); Push(func->_name);
		Call(_debughook_closure,nparams,_top-nparams,temp_reg,SQFalse);
		Pop(nparams);
	}
	_debughook = true;
}

bool SQVM::CallNative(SQNativeClosure *nclosure, SQInteger nargs, SQInteger newbase, SQObjectPtr &retval, bool &suspend)
{
	SQInteger nparamscheck = nclosure->_nparamscheck;
	SQInteger newtop = newbase + nargs + nclosure->_noutervalues;
	
	if (_nnativecalls + 1 > MAX_NATIVE_CALLS) {
		Raise_Error(_SC("Native stack overflow"));
		return false;
	}

	if(nparamscheck && (((nparamscheck > 0) && (nparamscheck != nargs)) ||
		((nparamscheck < 0) && (nargs < (-nparamscheck)))))
	{
		Raise_Error(_SC("wrong number of parameters"));
		return false;
	}

	SQInteger tcs;
	SQIntVec &tc = nclosure->_typecheck;
	if((tcs = tc.size())) {
		for(SQInteger i = 0; i < nargs && i < tcs; i++) {
			if((tc._vals[i] != -1) && !(type(_stack._vals[newbase+i]) & tc._vals[i])) {
				Raise_ParamTypeError(i,tc._vals[i],type(_stack._vals[newbase+i]));
				return false;
			}
		}
	}

	if(!EnterFrame(newbase, newtop, false)) return false;
	ci->_closure  = nclosure;

	SQInteger outers = nclosure->_noutervalues;
	for (SQInteger i = 0; i < outers; i++) {
		_stack._vals[newbase+nargs+i] = nclosure->_outervalues[i];
	}
	if(nclosure->_env) {
		_stack._vals[newbase] = nclosure->_env->_obj;
	}

	_nnativecalls++;
	SQInteger ret = (nclosure->_function)(this);
	_nnativecalls--;

	suspend = false;
	if (ret == SQ_SUSPEND_FLAG) {
		suspend = true;
	}
	else if (ret < 0) {
		LeaveFrame();
		Raise_Error(_lasterror);
		return false;
	}
	if(ret) {
		retval = _stack._vals[_top-1];
	}
	else {
		retval.Null();
	}
	//retval = ret ? _stack._vals[_top-1] : _null_;
	LeaveFrame();
	return true;
}

#define FALLBACK_OK			0
#define FALLBACK_NO_MATCH	1
#define FALLBACK_ERROR		2

bool SQVM::Get(const SQObjectPtr &self,const SQObjectPtr &key,SQObjectPtr &dest,bool raw, SQInteger selfidx)
{
	switch(type(self)){
	case OT_TABLE:
		if(_table(self)->Get(key,dest))return true;
		break;
	case OT_ARRAY:
		if(sq_isnumeric(key)) { if(_array(self)->Get(tointeger(key),dest)) { return true; } Raise_IdxError(key); return false; }
		break;
	case OT_INSTANCE:
		if(_instance(self)->Get(key,dest)) return true;
		break;
	case OT_CLASS: 
		if(_class(self)->Get(key,dest)) return true;
		break;
	case OT_STRING:
		if(sq_isnumeric(key)){
			SQInteger n = tointeger(key);
			if(abs((int)n) < _string(self)->_len) {
				if(n < 0) n = _string(self)->_len - n;
				dest = SQInteger(_stringval(self)[n]);
				return true;
			}
			Raise_IdxError(key);
			return false;
		}
		break;
	default:break; //shut up compiler
	}
	if(!raw) {
		switch(FallBackGet(self,key,dest)) {
			case FALLBACK_OK: return true; //okie
			case FALLBACK_NO_MATCH: break; //keep falling back
			case FALLBACK_ERROR: return false; // the metamethod failed
		}
		if(InvokeDefaultDelegate(self,key,dest)) {
			return true;
		}
	}
//#ifdef ROOT_FALLBACK
	if(selfidx == 0) {
		if(_table(_roottable)->Get(key,dest)) return true;
	}
//#endif
	Raise_IdxError(key);
	return false;
}

bool SQVM::InvokeDefaultDelegate(const SQObjectPtr &self,const SQObjectPtr &key,SQObjectPtr &dest)
{
	SQTable *ddel = NULL;
	switch(type(self)) {
		case OT_CLASS: ddel = _class_ddel; break;
		case OT_TABLE: ddel = _table_ddel; break;
		case OT_ARRAY: ddel = _array_ddel; break;
		case OT_STRING: ddel = _string_ddel; break;
		case OT_INSTANCE: ddel = _instance_ddel; break;
		case OT_INTEGER:case OT_FLOAT:case OT_BOOL: ddel = _number_ddel; break;
		case OT_GENERATOR: ddel = _generator_ddel; break;
		case OT_CLOSURE: case OT_NATIVECLOSURE:	ddel = _closure_ddel; break;
		case OT_THREAD: ddel = _thread_ddel; break;
		case OT_WEAKREF: ddel = _weakref_ddel; break;
		default: return false;
	}
	return  ddel->Get(key,dest);
}


SQInteger SQVM::FallBackGet(const SQObjectPtr &self,const SQObjectPtr &key,SQObjectPtr &dest)
{
	switch(type(self)){
	case OT_TABLE:
	case OT_USERDATA:
        //delegation
		if(_delegable(self)->_delegate) {
			if(Get(SQObjectPtr(_delegable(self)->_delegate),key,dest,false,DONT_FALL_BACK)) return FALLBACK_OK;	
		}
		else {
			return FALLBACK_NO_MATCH;
		}
		//go through
	case OT_INSTANCE: {
		SQObjectPtr closure;
		if(_delegable(self)->GetMetaMethod(this, MT_GET, closure)) {
			Push(self);Push(key);
			_nmetamethodscall++;
			AutoDec ad(&_nmetamethodscall);
			if(Call(closure, 2, _top - 2, dest, SQFalse)) {
				Pop(2);
				return FALLBACK_OK;
			}
			else {
				if(type(_lasterror) != OT_NULL) { //NULL means "clean failure" (not found)
					//error
					Pop(2);
					return FALLBACK_ERROR;
				}
			}
		}
					  }
		break;
	default: break;//shutup GCC 4.x
	}
	// no metamethod or no fallback type
	return FALLBACK_NO_MATCH;
}

bool SQVM::Set(const SQObjectPtr &self,const SQObjectPtr &key,const SQObjectPtr &val,SQInteger selfidx)
{
	switch(type(self)){
	case OT_TABLE:
		if(_table(self)->Set(key,val)) return true;
		break;
	case OT_INSTANCE:
		if(_instance(self)->Set(key,val)) return true;
		break;
	case OT_ARRAY:
		if(!sq_isnumeric(key)) { Raise_Error(_SC("indexing %s with %s"),GetTypeName(self),GetTypeName(key)); return false; }
		if(!_array(self)->Set(tointeger(key),val)) {
			Raise_IdxError(key);
			return false;
		}
		return true;
	default:
		Raise_Error(_SC("trying to set '%s'"),GetTypeName(self));
		return false;
	}

	switch(FallBackSet(self,key,val)) {
		case FALLBACK_OK: return true; //okie
		case FALLBACK_NO_MATCH: break; //keep falling back
		case FALLBACK_ERROR: return false; // the metamethod failed
	}
	if(selfidx == 0) {
		if(_table(_roottable)->Set(key,val))
			return true;
	}
	Raise_IdxError(key);
	return false;
}

SQInteger SQVM::FallBackSet(const SQObjectPtr &self,const SQObjectPtr &key,const SQObjectPtr &val)
{
	switch(type(self)) {
	case OT_TABLE:
		if(_table(self)->_delegate) {
			if(Set(_table(self)->_delegate,key,val,DONT_FALL_BACK))	return FALLBACK_OK;
		}
		//keps on going
	case OT_INSTANCE:
	case OT_USERDATA:{
		SQObjectPtr closure;
		SQObjectPtr t;
		if(_delegable(self)->GetMetaMethod(this, MT_SET, closure)) {
			Push(self);Push(key);Push(val);
			_nmetamethodscall++;
			AutoDec ad(&_nmetamethodscall);
			if(Call(closure, 3, _top - 3, t, SQFalse)) {
				Pop(3);
				return FALLBACK_OK;
			}
			else {
				if(type(_lasterror) != OT_NULL) { //NULL means "clean failure" (not found)
					//error
					Pop(3);
					return FALLBACK_ERROR;
				}
			}
		}
					 }
		break;
		default: break;//shutup GCC 4.x
	}
	// no metamethod or no fallback type
	return FALLBACK_NO_MATCH;
}

bool SQVM::Clone(const SQObjectPtr &self,SQObjectPtr &target)
{
	SQObjectPtr temp_reg;
	SQObjectPtr newobj;
	switch(type(self)){
	case OT_TABLE:
		newobj = _table(self)->Clone();
		goto cloned_mt;
	case OT_INSTANCE: {
		newobj = _instance(self)->Clone(_ss(this));
cloned_mt:
		SQObjectPtr closure;
		if(_delegable(newobj)->_delegate && _delegable(newobj)->GetMetaMethod(this,MT_CLONED,closure)) {
			Push(newobj);
			Push(self);
			if(!CallMetaMethod(closure,MT_CLONED,2,temp_reg))
				return false;
		}
		}
		target = newobj;
		return true;
	case OT_ARRAY: 
		target = _array(self)->Clone();
		return true;
	default: 
		Raise_Error(_SC("cloning a %s"), GetTypeName(self));
		return false;
	}
}

bool SQVM::NewSlotA(const SQObjectPtr &self,const SQObjectPtr &key,const SQObjectPtr &val,const SQObjectPtr &attrs,bool bstatic,bool raw)
{
	if(type(self) != OT_CLASS) {
		Raise_Error(_SC("object must be a class"));
		return false;
	}
	SQClass *c = _class(self);
	if(!raw) {
		SQObjectPtr &mm = c->_metamethods[MT_NEWMEMBER];
		if(type(mm) != OT_NULL ) {
			Push(self); Push(key); Push(val);
			Push(attrs);
			Push(bstatic);
			return CallMetaMethod(mm,MT_NEWMEMBER,5,temp_reg);
		}
	}
	if(!NewSlot(self, key, val,bstatic))
		return false;
	if(type(attrs) != OT_NULL) {
		c->SetAttributes(key,attrs);
	}
	return true;
}

bool SQVM::NewSlot(const SQObjectPtr &self,const SQObjectPtr &key,const SQObjectPtr &val,bool bstatic)
{
	if(type(key) == OT_NULL) { Raise_Error(_SC("null cannot be used as index")); return false; }
	switch(type(self)) {
	case OT_TABLE: {
		bool rawcall = true;
		if(_table(self)->_delegate) {
			SQObjectPtr res;
			if(!_table(self)->Get(key,res)) {
				SQObjectPtr closure;
				if(_delegable(self)->_delegate && _delegable(self)->GetMetaMethod(this,MT_NEWSLOT,closure)) {
					Push(self);Push(key);Push(val);
					if(!CallMetaMethod(closure,MT_NEWSLOT,3,res)) {
						return false;
					}
					rawcall = false;
				}
				else {
					rawcall = true;
				}
			}
		}
		if(rawcall) _table(self)->NewSlot(key,val); //cannot fail
		
		break;}
	case OT_INSTANCE: {
		SQObjectPtr res;
		SQObjectPtr closure;
		if(_delegable(self)->_delegate && _delegable(self)->GetMetaMethod(this,MT_NEWSLOT,closure)) {
			Push(self);Push(key);Push(val);
			if(!CallMetaMethod(closure,MT_NEWSLOT,3,res)) {
				return false;
			}
			break;
		}
		Raise_Error(_SC("class instances do not support the new slot operator"));
		return false;
		break;}
	case OT_CLASS: 
		if(!_class(self)->NewSlot(_ss(this),key,val,bstatic)) {
			if(_class(self)->_locked) {
				Raise_Error(_SC("trying to modify a class that has already been instantiated"));
				return false;
			}
			else {
				SQObjectPtr oval = PrintObjVal(key);
				Raise_Error(_SC("the property '%s' already exists"),_stringval(oval));
				return false;
			}
		}
		break;
	default:
		Raise_Error(_SC("indexing %s with %s"),GetTypeName(self),GetTypeName(key));
		return false;
		break;
	}
	return true;
}



bool SQVM::DeleteSlot(const SQObjectPtr &self,const SQObjectPtr &key,SQObjectPtr &res)
{
	switch(type(self)) {
	case OT_TABLE:
	case OT_INSTANCE:
	case OT_USERDATA: {
		SQObjectPtr t;
		//bool handled = false;
		SQObjectPtr closure;
		if(_delegable(self)->_delegate && _delegable(self)->GetMetaMethod(this,MT_DELSLOT,closure)) {
			Push(self);Push(key);
			return CallMetaMethod(closure,MT_DELSLOT,2,res);
		}
		else {
			if(type(self) == OT_TABLE) {
				if(_table(self)->Get(key,t)) {
					_table(self)->Remove(key);
				}
				else {
					Raise_IdxError((SQObject &)key);
					return false;
				}
			}
			else {
				Raise_Error(_SC("cannot delete a slot from %s"),GetTypeName(self));
				return false;
			}
		}
		res = t;
				}
		break;
	default:
		Raise_Error(_SC("attempt to delete a slot from a %s"),GetTypeName(self));
		return false;
	}
	return true;
}

bool SQVM::Call(SQObjectPtr &closure,SQInteger nparams,SQInteger stackbase,SQObjectPtr &outres,SQBool raiseerror)
{
#ifdef _DEBUG
SQInteger prevstackbase = _stackbase;
#endif
	switch(type(closure)) {
	case OT_CLOSURE:
		return Execute(closure, nparams, stackbase, outres, raiseerror);
		break;
	case OT_NATIVECLOSURE:{
		bool suspend;
		return CallNative(_nativeclosure(closure), nparams, stackbase, outres,suspend);
		
						  }
		break;
	case OT_CLASS: {
		SQObjectPtr constr;
		SQObjectPtr temp;
		CreateClassInstance(_class(closure),outres,constr);
		if(type(constr) != OT_NULL) {
			_stack[stackbase] = outres;
			return Call(constr,nparams,stackbase,temp,raiseerror);
		}
		return true;
				   }
		break;
	default:
		return false;
	}
#ifdef _DEBUG
	if(!_suspended) {
		assert(_stackbase == prevstackbase);
	}
#endif
	return true;
}

bool SQVM::CallMetaMethod(SQObjectPtr &closure,SQMetaMethod mm,SQInteger nparams,SQObjectPtr &outres)
{
	//SQObjectPtr closure;
	
	_nmetamethodscall++;
	if(Call(closure, nparams, _top - nparams, outres, SQFalse)) {
		_nmetamethodscall--;
		Pop(nparams);
		return true;
	}
	_nmetamethodscall--;
	//}
	Pop(nparams);
	return false;
}

void SQVM::FindOuter(SQObjectPtr &target, SQObjectPtr *stackindex)
{
	SQOuter **pp = &_openouters;
	SQOuter *p;
	SQOuter *otr;

	while ((p = *pp) != NULL && p->_valptr >= stackindex) {
		if (p->_valptr == stackindex) {
			target = SQObjectPtr(p);
			return;
		}
		pp = &p->_next;
	}
	otr = SQOuter::Create(_ss(this), stackindex);
	otr->_next = *pp;
	otr->_idx  = (stackindex - _stack._vals);
	__ObjAddRef(otr);
	*pp = otr;
	target = SQObjectPtr(otr);
}

bool SQVM::EnterFrame(SQInteger newbase, SQInteger newtop, bool tailcall)
{
	if( !tailcall ) {
		if( _callsstacksize == _alloccallsstacksize ) {
			GrowCallStack();
		}
		ci = &_callsstack[_callsstacksize++];
		ci->_prevstkbase = (SQInt32)(newbase - _stackbase);
		ci->_prevtop = (SQInt32)(_top - _stackbase);
		ci->_etraps = 0;
		ci->_ncalls = 1;
		ci->_generator = NULL;
		ci->_root = SQFalse;
	}
	else {
		ci->_ncalls++;
	}

	_stackbase = newbase;
	_top = newtop;
	if(newtop + MIN_STACK_OVERHEAD > (SQInteger)_stack.size()) {
		if(_nmetamethodscall) {
			Raise_Error(_SC("stack overflow, cannot resize stack while in  a metamethod"));
			return false;
		}
		_stack.resize(_stack.size() + (MIN_STACK_OVERHEAD << 2));
		RelocateOuters();
	}
	return true;
}

void SQVM::LeaveFrame() {
	SQInteger last_top = _top;
	SQInteger last_stackbase = _stackbase;
	SQInteger css = --_callsstacksize;

	/* First clean out the call stack frame */
	ci->_closure.Null();
	_stackbase -= ci->_prevstkbase;
	_top = _stackbase + ci->_prevtop;
	ci = (css) ? &_callsstack[css-1] : NULL;

	if(_openouters) CloseOuters(&(_stack._vals[last_stackbase]));
	while (last_top >= _top) {
		_stack._vals[last_top--].Null();
	}
}

void SQVM::RelocateOuters()
{
	SQOuter *p = _openouters;
	while (p) {
		p->_valptr = _stack._vals + p->_idx;
		p = p->_next;
	}
}

void SQVM::CloseOuters(SQObjectPtr *stackindex) {
  SQOuter *p;
  while ((p = _openouters) != NULL && p->_valptr >= stackindex) {
    p->_value = *(p->_valptr);
    p->_valptr = &p->_value;
    _openouters = p->_next;
  	__ObjRelease(p);
  }
}

void SQVM::Remove(SQInteger n) {
	n = (n >= 0)?n + _stackbase - 1:_top + n;
	for(SQInteger i = n; i < _top; i++){
		_stack[i] = _stack[i+1];
	}
	_stack[_top].Null();
	_top--;
}

void SQVM::Pop() {
	_stack[--_top].Null();
}

void SQVM::Pop(SQInteger n) {
	for(SQInteger i = 0; i < n; i++){
		_stack[--_top].Null();
	}
}

void SQVM::PushNull() { _stack[_top++].Null(); }
void SQVM::Push(const SQObjectPtr &o) { _stack[_top++] = o; }
SQObjectPtr &SQVM::Top() { return _stack[_top-1]; }
SQObjectPtr &SQVM::PopGet() { return _stack[--_top]; }
SQObjectPtr &SQVM::GetUp(SQInteger n) { return _stack[_top+n]; }
SQObjectPtr &SQVM::GetAt(SQInteger n) { return _stack[n]; }

#ifdef _DEBUG_DUMP
void SQVM::dumpstack(SQInteger stackbase,bool dumpall)
{
	SQInteger size=dumpall?_stack.size():_top;
	SQInteger n=0;
	scprintf(_SC("\n>>>>stack dump<<<<\n"));
	CallInfo &ci=_callsstack[_callsstacksize-1];
	scprintf(_SC("IP: %p\n"),ci._ip);
	scprintf(_SC("prev stack base: %d\n"),ci._prevstkbase);
	scprintf(_SC("prev top: %d\n"),ci._prevtop);
	for(SQInteger i=0;i<size;i++){
		SQObjectPtr &obj=_stack[i];	
		if(stackbase==i)scprintf(_SC(">"));else scprintf(_SC(" "));
		scprintf(_SC("[%d]:"),n);
		switch(type(obj)){
		case OT_FLOAT:			scprintf(_SC("FLOAT %.3f"),_float(obj));break;
		case OT_INTEGER:		scprintf(_SC("INTEGER %d"),_integer(obj));break;
		case OT_BOOL:			scprintf(_SC("BOOL %s"),_integer(obj)?"true":"false");break;
		case OT_STRING:			scprintf(_SC("STRING %s"),_stringval(obj));break;
		case OT_NULL:			scprintf(_SC("NULL"));	break;
		case OT_TABLE:			scprintf(_SC("TABLE %p[%p]"),_table(obj),_table(obj)->_delegate);break;
		case OT_ARRAY:			scprintf(_SC("ARRAY %p"),_array(obj));break;
		case OT_CLOSURE:		scprintf(_SC("CLOSURE [%p]"),_closure(obj));break;
		case OT_NATIVECLOSURE:	scprintf(_SC("NATIVECLOSURE"));break;
		case OT_USERDATA:		scprintf(_SC("USERDATA %p[%p]"),_userdataval(obj),_userdata(obj)->_delegate);break;
		case OT_GENERATOR:		scprintf(_SC("GENERATOR %p"),_generator(obj));break;
		case OT_THREAD:			scprintf(_SC("THREAD [%p]"),_thread(obj));break;
		case OT_USERPOINTER:	scprintf(_SC("USERPOINTER %p"),_userpointer(obj));break;
		case OT_CLASS:			scprintf(_SC("CLASS %p"),_class(obj));break;
		case OT_INSTANCE:		scprintf(_SC("INSTANCE %p"),_instance(obj));break;
		case OT_WEAKREF:		scprintf(_SC("WEAKERF %p"),_weakref(obj));break;
		default:
			assert(0);
			break;
		};
		scprintf(_SC("\n"));
		++n;
	}
}



#endif

