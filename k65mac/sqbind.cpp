// ---------------- Library -- generated on 28.10.2017  20:32 ----------------



// ******************************** _xsqbind.cpp ********************************

#ifndef _XSQBIND_CPP_DONE
#define _XSQBIND_CPP_DONE



#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef SQBIND_STATIC
#define SQBIND_STATIC
#endif

// ---- #include "xsqbind.h"
// ---> including xsqbind.h
#ifndef _XSQBIND_H
#define _XSQBIND_H

// ---- #pragma once



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

// <--- back to xsqbind.h

// ---- #include "sqbind/sqbStackUtils.h"
// ---> including sqbStackUtils.h
#ifndef _SQBSTACKUTILS_H
#define _SQBSTACKUTILS_H

// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbAssert.h>
// ---> including sqbAssert.h
#ifndef _SQBASSERT_H
#define _SQBASSERT_H

// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
#include <cassert>
#include <cstdlib>
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbBaseHeader.h>
// ---> including sqbBaseHeader.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqbBaseHeader.h
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_COMPILER_CLANG
/// \def SQBIND_COMPILER_MSVC
/// \def SQBIND_COMPILER_GCC
/// \def SQBIND_COMPILER_VERSION
//----------------------------------------------------------------------------------------------------------------------
#if defined(__clang__)
# define SQBIND_COMPILER_CLANG
# define SQBIND_COMPILER_VERSION (__clang_major__ * 10000) + (__clang_minor__ * 100) + __clang_patchlevel__
#elif defined(_MSC_VER)
# define SQBIND_COMPILER_MSVC
# define SQBIND_COMPILER_VERSION _MSC_VER
#elif defined(__GNUC__)
# define SQBIND_COMPILER_GCC
# define SQBIND_COMPILER_VERSION (__GNUC__ * 10000) + (__GNUC_MINOR__ * 100) + __GNUC_PATCHLEVEL__
#endif

//----------------------------------------------------------------------------------------------------------------------
/// \cond NO_DOXYGEN
#if defined(_MSC_VER) && defined(__clang__)
# undef _HAS_CHAR16_T_LANGUAGE_SUPPORT
# define _HAS_CHAR16_T_LANGUAGE_SUPPORT 0
#endif

#if defined(_MSC_VER)
// visual studio doesn't define std int types.
typedef signed __int8     int8_t;
typedef unsigned __int8   uint8_t;
typedef signed __int16    int16_t;
typedef unsigned __int16  uint16_t;
typedef signed __int32    int32_t;
typedef unsigned __int32  uint32_t;
typedef signed __int64    int64_t;
typedef unsigned __int64  uint64_t;
#else
# include <stdint.h>
# include <stddef.h>
#endif

// enable the use of nullptr for all compilers.
#if !defined(SQBIND_CPP0X_NULLPTR_SUPPORTED)
# if (defined(SQBIND_COMPILER_MSVC) && (SQBIND_COMPILER_VERSION >= 1600))
#  define SQBIND_CPP0X_NULLPTR_SUPPORTED 1
# elif (defined(SQBIND_COMPILER_GCC) && (SQBIND_COMPILER_VERSION >= 40600))
#  define SQBIND_CPP0X_NULLPTR_SUPPORTED 1
# elif (defined(SQBIND_COMPILER_CLANG) && __has_feature(cxx_nullptr))
#  define SQBIND_CPP0X_NULLPTR_SUPPORTED 1
# else
#  define SQBIND_CPP0X_NULLPTR_SUPPORTED 0
# endif
#endif

#if !SQBIND_CPP0X_NULLPTR_SUPPORTED
# if !defined nullptr
#  define nullptr 0
# endif
#endif
/// \endcond
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_MAJOR_VERSION
/// \brief The major version number of sqbind.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_MAJOR_VERSION 1

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_MINOR_VERSION
/// \brief The minor version number of sqbind.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_MINOR_VERSION 20

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_VERSION_NUMBER
/// \brief The combined version number of sqbind, of the form 1000.
/// The number will be (SQBIND_MAJOR_VERSION * 1000) + SQBIND_MINOR_VERSION
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_VERSION_NUMBER ((SQBIND_MAJOR_VERSION * 1000) + SQBIND_MINOR_VERSION)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_STRINGIFY_INTERNAL
/// \brief Used by SQBIND_STRINGIFY to turn macro values in to strings, never call this directly.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_STRINGIFY_INTERNAL(SQBIND_VALUE) _SC(#SQBIND_VALUE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_STRINGIFY
/// \brief Converts a value to a string.
/// \code
/// #define NUMBER 1.0
/// // str will be _SC("1.0")
/// //
/// const SQChar* str = SQBIND_STRINGIFY(NUMBER);
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_STRINGIFY(SQBIND_VALUE) SQBIND_STRINGIFY_INTERNAL(SQBIND_VALUE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_VERSION_STRING
/// \brief The string version number of sqbind of the form sqbind-SQBIND_MAJOR_VERSION.SQBIND_MINOR_VERSION
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_VERSION_STRING _SC("sqbind-") SQBIND_STRINGIFY(SQBIND_MAJOR_VERSION) _SC(".") SQBIND_STRINGIFY(SQBIND_MINOR_VERSION)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_OVERRIDE
/// \brief
/// \code
/// class Base
/// {
/// public:
///   virtual Func();
/// };
///
/// class Derived : public Base
/// {
/// public:
///   SQBIND_BEGIN_NONSTANDARD_EXTENSION_BLOCK();
///   virtual Func() SQBIND_OVERRIDE;
///   SQBIND_END_NONSTANDARD_EXTENSION_BLOCK();
/// };
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
#if _MSC_VER >= 1400
# define SQBIND_OVERRIDE override
#else
# define SQBIND_OVERRIDE
#endif

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_BEGIN_NONSTANDARD_EXTENSION_BLOCK
/// \brief
//----------------------------------------------------------------------------------------------------------------------
#if _MSC_VER >= 1400
# define SQBIND_BEGIN_NONSTANDARD_EXTENSION_BLOCK() \
  __pragma(warning(push)) \
  __pragma(warning(disable: 4481))
#else
# define SQBIND_BEGIN_NONSTANDARD_EXTENSION_BLOCK()
#endif

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_END_NONSTANDARD_EXTENSION_BLOCK
/// \brief
//----------------------------------------------------------------------------------------------------------------------
#if _MSC_VER >= 1400
# define SQBIND_END_NONSTANDARD_EXTENSION_BLOCK() \
  __pragma(warning(pop))
#else
# define SQBIND_END_NONSTANDARD_EXTENSION_BLOCK()
#endif

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_UNUSED
/// \brief Used to mark a function parameter as unused
/// \code
/// void func(int SQBIND_UNUSED(blah))
/// {
/// }
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_UNUSED(X)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_TEST_COVERAGE_OFF
/// \brief Disables coverage instrumentation for all code following this call. Only works in coverage builds.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_TEST_COVERAGE_OFF)
# if defined(__COVERAGESCANNER__)
#  define SQBIND_TEST_COVERAGE_OFF() __pragma(CoverageScanner(cov-off))
# else // defined(__COVERAGESCANNER__)
#  define SQBIND_TEST_COVERAGE_OFF()
# endif // defined(__COVERAGESCANNER__)
#endif // !defined(SQBIND_TEST_COVERAGE_OFF)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_TEST_COVERAGE_ON
/// \brief Pops last coverage instrumentation command resetting it to normal. Only works in coverage builds.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_TEST_COVERAGE_ON)
# if defined(__COVERAGESCANNER__)
#  define SQBIND_TEST_COVERAGE_ON() __pragma(CoverageScanner(cov-on))
# else // defined(__COVERAGESCANNER__)
#  define SQBIND_TEST_COVERAGE_ON()
# endif // defined(__COVERAGESCANNER__)
#endif // !defined(SQBIND_TEST_COVERAGE_ON)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_API
/// \brief Used to mark objects for export when compiling sqbind as a dll.
//----------------------------------------------------------------------------------------------------------------------
#ifndef SQBIND_API
# ifdef WIN32
#  ifndef SQBIND_STATIC
#   ifdef SQBIND_EXPORTS
#    define SQBIND_API __declspec(dllexport)
#   else
#    define SQBIND_API __declspec(dllimport)
#   endif
#  else
#   define SQBIND_API
#  endif
# else
#  define SQBIND_API
# endif
#endif

// <--- back to sqbAssert.h
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERTS_ENABLED
/// \brief Define this to enable asserts, by default it is defined if _DEBUG is enabled.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERTS_ENABLED)
# if defined(_DEBUG)
#  define SQBIND_ASSERTS_ENABLED 1
# else
#  define SQBIND_ASSERTS_ENABLED 0
# endif // defined(_DEBUG)
#endif // !defined(SQBIND_ASSERTS_ENABLED)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_BREAK()
/// \brief Use this to break program execution
/// \code
/// int i = 0;
/// SQBIND_BREAK(); // program execution will halt here
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_BREAK)
# if defined(SQBIND_COMPILER_MSVC) && (SQBIND_COMPILER_VERSION >= 1300)
#  define SQBIND_BREAK() __debugbreak()
# elif defined(SQBIND_COMPILER_GCC)
#  define SQBIND_BREAK() __builtin_trap()
# else
#  define SQBIND_BREAK() assert(false)
# endif // defined(SQBIND_COMPILER_MSVC) && (SQBIND_COMPILER_VERSION >= 1300)
#endif // !defined(SQBIND_BREAK)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_EXIT(RETURN_CODE)
/// \brief Use this to exit program execution
/// \code
/// int i = 0;
/// SQBIND_EXIT(10); // program will exit returning 10 here
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_EXIT)
# define SQBIND_EXIT(__SQBIND_RETURN_CODE__) exit(__SQBIND_RETURN_CODE__)
#endif

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_BEGIN_MULTILINE_MACRO
/// \brief Helper function for wrapping multi line macros in a do while loop
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_BEGIN_MULTILINE_MACRO)
# if defined(SQBIND_COMPILER_MSVC)
# define SQBIND_BEGIN_MULTILINE_MACRO() \
  __pragma(warning(push)) \
  __pragma(warning(disable:4127)) \
  do \
  {
# elif defined(SQBIND_COMPILER_GCC) && (SQBIND_COMPILER_VERSION > 40400)
# define SQBIND_BEGIN_MULTILINE_MACRO() \
  _Pragma("GCC diagnostic push") \
  _Pragma("GCC diagnostic ignored \"-Wno-unused-values\"") \
  do \
  {
# else // defined(SQBIND_COMPILER_MSVC)
# define SQBIND_BEGIN_MULTILINE_MACRO() \
  do \
  {
# endif // defined(SQBIND_COMPILER_MSVC)
#endif // !defined(SQBIND_BEGIN_MULTILINE_MACRO)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_END_MULTILINE_MACRO
/// \brief Helper function for wrapping multi line macros in a do while loop, required to stop msvc warnings
/// about constant conditionals (warning C4127).
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_END_MULTILINE_MACRO)
# if defined(SQBIND_COMPILER_MSVC)
# define SQBIND_END_MULTILINE_MACRO() \
  } while(0) \
  __pragma(warning(pop))
# elif defined(SQBIND_COMPILER_GCC) && (SQBIND_COMPILER_VERSION > 40400)
# define SQBIND_END_MULTILINE_MACRO() \
  } while(0) \
  _Pragma("GCC diagnostic pop")
# else // defined(defined(SQBIND_COMPILER_MSVC)
# define SQBIND_END_MULTILINE_MACRO() \
  } while(0)
# endif // defined(SQBIND_COMPILER_MSVC)
#endif // !defined(SQBIND_END_MULTILINE_MACRO)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_INTERNAL
/// \brief For internal use by other assert macros only, do not call this directly.
/// If SQBIND_ASSERTS_ENABLED is not defined this macro results in a no-op but still references the condition so there
/// are no unreferenced variable compiler errors or warnings in release code. 
/// \code
/// int result = func();
/// SQBIND_ASSERT(result); // result would be unreferenced without the sizeof code
/// \endcode
/// \note This assert is based on the article Stupid C++ Tricks: Adventures in Assert found
/// http://cnicholson.net/2009/02/stupid-c-tricks-adventures-in-assert/.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_INTERNAL)
# if SQBIND_ASSERTS_ENABLED != 0
#  define SQBIND_ASSERT_INTERNAL(__SQBIND_ASSERT_CONDITION__, __SQBIND_ASSERT_MESSAGE__) \
  SQBIND_BEGIN_MULTILINE_MACRO(); \
    sqb::AssertFailOp _fail_op = sqb::kAssertFailContinue; \
    if (!(__SQBIND_ASSERT_CONDITION__)) \
    { \
      _fail_op = sqb::AssertionFailure(__FILE__, __LINE__, __SQBIND_ASSERT_MESSAGE__); \
    } \
    switch (_fail_op) \
    { \
    default: \
    case sqb::kAssertFailHalt: \
      SQBIND_BREAK(); \
      break; \
    case sqb::kAssertFailExit: \
      SQBIND_EXIT(-1); \
    case sqb::kAssertFailContinue: \
      break; \
    } \
  SQBIND_END_MULTILINE_MACRO()
# else // SQBIND_ASSERTS_ENABLED != 0
// visual studio 2010 no longer treats sizeof as referencing a variable so we have to rely
// on if (false) and the optimiser taking care of the rest.
// same is true for gcc 4.4
// C4127 is conditional expression is constant warning.
#  if (defined(SQBIND_COMPILER_MSVC) && (SQBIND_COMPILER_VERSION >= 1600)) || (defined(SQBIND_COMPILER_GCC) && (SQBIND_COMPILER_VERSION < 40500))
#   define SQBIND_ASSERT_INTERNAL(__SQBIND_ASSERT_CONDITION__, __SQBIND_ASSERT_MESSAGE__) \
  SQBIND_TEST_COVERAGE_OFF(); \
  SQBIND_BEGIN_MULTILINE_MACRO(); \
  if (false) \
  { \
    (void)(__SQBIND_ASSERT_CONDITION__); \
  } \
  SQBIND_END_MULTILINE_MACRO(); \
  SQBIND_TEST_COVERAGE_ON()
#  else // (defined(SQBIND_COMPILER_MSVC) && (SQBIND_COMPILER_VERSION >= 1600))
#   define SQBIND_ASSERT_INTERNAL(__SQBIND_ASSERT_CONDITION__, __SQBIND_ASSERT_MESSAGE__) \
  SQBIND_TEST_COVERAGE_OFF(); \
  SQBIND_BEGIN_MULTILINE_MACRO(); \
    sizeof(__SQBIND_ASSERT_CONDITION__); \
  SQBIND_END_MULTILINE_MACRO(); \
  SQBIND_TEST_COVERAGE_ON()
#  endif // (defined(SQBIND_COMPILER_MSVC) && (SQBIND_COMPILER_VERSION >= 1600))
# endif // SQBIND_ASSERTS_ENABLED != 0
#endif // !defined(SQBIND_ASSERT_INTERNAL)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT(ASSERT_CONDITION)
/// \brief Use this to assert a condition is true. If asserts are enabled and SQBIND_ASSERT has not been
/// overridden externally when the condition is false this will call sqb::AssertionFailure. Depending on the
/// return value of sqb::AssertionFailure program execution can either halt, exit or continue as normal. By
/// default it will halt, to change the behaviour set the assert handler by calling sqb::SetAssertionFailureFunction
/// to something other than sqb::AssertionFailureFunctionDefault.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT)
# define SQBIND_ASSERT(__SQBIND_ASSERT_CONDITION__) \
  SQBIND_ASSERT_INTERNAL(__SQBIND_ASSERT_CONDITION__, "SQBIND_ASSERT(" #__SQBIND_ASSERT_CONDITION__ ")")
#endif // !defined(SQBIND_ASSERT)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_MSG
/// \brief Assert a condition is true also logging a message on failure.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_MSG)
# define SQBIND_ASSERT_MSG(__SQBIND_ASSERT_CONDITION__, __SQBIND_ASSERT_MESSAGE__) \
  SQBIND_ASSERT_INTERNAL(__SQBIND_ASSERT_CONDITION__, "SQBIND_ASSERT(" #__SQBIND_ASSERT_CONDITION__ ") : " __SQBIND_ASSERT_MESSAGE__)
#endif // !defined(SQBIND_ASSERT)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_FAIL()
/// \brief Always does the current assert fail operation. Use this for always halting program execution or to make sure
/// certain code paths are never called.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_FAIL)
# define SQBIND_ASSERT_FAIL() \
  SQBIND_ASSERT_INTERNAL(false, "SQBIND_ASSERT_FAIL()")
#endif // !defined(SQBIND_ASSERT_FAIL)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_FAIL_MSG
/// \brief Perform the current assert fail op logging an additional message.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_FAIL_MSG)
# define SQBIND_ASSERT_FAIL_MSG(__SQBIND_ASSERT_MESSAGE__) \
  SQBIND_ASSERT_INTERNAL(false, "SQBIND_ASSERT_FAIL_MSG() : " __SQBIND_ASSERT_MESSAGE__)
#endif // !defined(SQBIND_ASSERT)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_SUCCEEDED
/// \brief Shorter and neater way of writing #SQBIND_ASSERT(SQ_SUCCEEDED(sqresult));
/// Never call a function that returns an SQRESULT inside this macro as it will not be called in release code.
/// \code
/// SQBIND_ASSERT_SUCCEEDED(sq_getinteger(vm, index, &value)); // NEVER DO THIS
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_SUCCEEDED)
# define SQBIND_ASSERT_SUCCEEDED(__SQ_RESULT__) \
  SQBIND_ASSERT_INTERNAL(SQ_SUCCEEDED(__SQ_RESULT__), "SQBIND_ASSERT_SUCCEEDED(" #__SQ_RESULT__ ")")
#endif // !defined(SQBIND_ASSERT_SUCCEEDED)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_SUCCEEDED_MSG
/// \brief Assert that an SQRESULT was successful logging an additional message.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_SUCCEEDED_MSG)
# define SQBIND_ASSERT_SUCCEEDED_MSG(__SQ_RESULT__, __SQBIND_ASSERT_MESSAGE__) \
  SQBIND_ASSERT_INTERNAL(SQ_SUCCEEDED(__SQ_RESULT__), "SQBIND_ASSERT_SUCCEEDED(" #__SQ_RESULT__ ") : " __SQBIND_ASSERT_MESSAGE__)
#endif // !defined(SQBIND_ASSERT_SUCCEEDED_MSG)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_FAILED
/// \brief Shorter and neater way of writing #SQBIND_ASSERT(SQ_FAILED(sqresult));
/// Never call a function that returns an SQRESULT inside this macro as it will not be called in release code.
/// \code
/// SQBIND_ASSERT_FAILED(sq_getinteger(vm, index, &value)); // NEVER DO THIS
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_FAILED)
# define SQBIND_ASSERT_FAILED(__SQ_RESULT__) \
  SQBIND_ASSERT_INTERNAL(SQ_FAILED(__SQ_RESULT__), "SQBIND_ASSERT_FAILED(" #__SQ_RESULT__ ")")
#endif // !defined(SQBIND_ASSERT_FAILED)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_FAILED_MSG
/// \brief Assert that an SQRESULT was unsuccessful logging an additional message.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_FAILED_MSG)
# define SQBIND_ASSERT_FAILED_MSG(__SQ_RESULT__, __SQBIND_ASSERT_MESSAGE__) \
  SQBIND_ASSERT_INTERNAL(SQ_FAILED(__SQ_RESULT__), "SQBIND_ASSERT_FAILED(" #__SQ_RESULT__ ") : " __SQBIND_ASSERT_MESSAGE__)
#endif // !defined(SQBIND_ASSERT_FAILED_MSG)

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
enum AssertFailOp
{
  kAssertFailHalt,      ///< Assertion failure will halt execution.
  kAssertFailExit,      ///< Assertion failure will exit the program.
  kAssertFailContinue,  ///< Assertion failure will let the program execution continue.
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief The function signature for custom assert handler functions. Custom assert handler functions must match
/// this signature.
//----------------------------------------------------------------------------------------------------------------------
typedef AssertFailOp (*AssertFailHandlerFunction)(const char *file, size_t line, const char *message, void *userdata);

//----------------------------------------------------------------------------------------------------------------------
/// \brief Get the current assertion failure function.
//----------------------------------------------------------------------------------------------------------------------
SQBIND_API void GetAssertionFailureFunction(AssertFailHandlerFunction *handler, void **userData);

//----------------------------------------------------------------------------------------------------------------------
/// \brief Set the current assert handler function. By default this is set to sqb::AssertionFailureFunctionDefault
/// with a null user data.
//----------------------------------------------------------------------------------------------------------------------
SQBIND_API void SetAssertionFailureFunction(AssertFailHandlerFunction handler, void *userData);

//----------------------------------------------------------------------------------------------------------------------
/// \brief This function internally calls the current assert handler function and returns the desired fail operation.
/// If the current assert handler is null or SQBIND_ASSERTS_ENABLED is false then this will return kAssertFailContinue.
//----------------------------------------------------------------------------------------------------------------------
SQBIND_API AssertFailOp AssertionFailure(const char *file, size_t line, const char *message);

//----------------------------------------------------------------------------------------------------------------------
/// \brief This assertion failure handler which prints the file line and assert condition to stderr and
/// returns sqb::kAssertFailHalt.
/// \code
/// void EnableAsserts()
/// {
///   sqb::SetAssertionFailureFunction(&sqb::AssertionFailureFunctionBreak, nullptr);
/// }
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
SQBIND_API AssertFailOp AssertionFailureFunctionBreak(const char *file, size_t line, const char *message, void *userData);

//----------------------------------------------------------------------------------------------------------------------
/// \brief This assertion failure handler which prints the file line and assert condition to stderr and
/// returns sqb::kAssertFailExit.
/// \code
/// void EnableAsserts()
/// {
///   sqb::SetAssertionFailureFunction(&sqb::AssertionFailureFunctionExit, nullptr);
/// }
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
SQBIND_API AssertFailOp AssertionFailureFunctionExit(const char *file, size_t line, const char *message, void *userData);

//----------------------------------------------------------------------------------------------------------------------
/// \brief This assertion failure handler which always returns sqb::kAssertFailContinue.
/// To make sure asserts have no affect then define SQBIND_ASSERTS_ENABLED 0. This should only be used to temporarily
/// disable asserts while running.
/// \code
/// void DisableAsserts()
/// {
///   sqb::SetAssertionFailureFunction(&sqb::AssertionFailureFunctionContinue, nullptr);
/// }
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
SQBIND_API AssertFailOp AssertionFailureFunctionContinue(const char *file, size_t line, const char *message, void *userData);

} // namespace sqb

#endif

// <--- back to sqbStackUtils.h
//----------------------------------------------------------------------------------------------------------------------
#include <new>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief Class for passing around types.
//----------------------------------------------------------------------------------------------------------------------
template<class T>
struct TypeWrapper { };

/// \brief Pushes a value onto the stack, there is no default implementation of the template versions
/// of this function. Specialisations are declared when the \link CLASS_DECLARATION instance binding macros \endlink
/// are used.
template<typename T>
SQRESULT Push(HSQUIRRELVM vm, T *value);

/// \overload
template<typename T>
SQRESULT Push(HSQUIRRELVM vm, T &value);

/// \overload
template<typename T>
SQRESULT Push(HSQUIRRELVM vm, const T *value);

/// \overload
template<typename T>
SQRESULT Push(HSQUIRRELVM vm, const T &value);

/// \brief Checks that an object on the stack is of a particular type.
template<typename T>
bool Match(TypeWrapper<T>, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
bool Match(TypeWrapper<T *>, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
bool Match(TypeWrapper<T &> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
bool Match(TypeWrapper<const T *> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
bool Match(TypeWrapper<const T &> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \brief Gets a typed value from the stack at the index specified. If the value is
/// a reference then it will be invalid when it is removed from the stack.
/// Get should be used in conjunction with Match as no type checking is done.
template<typename T>
T& Get(TypeWrapper<T> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
T *Get(TypeWrapper<T*> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
T &Get(TypeWrapper<T&> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
const T *Get(TypeWrapper<const T *>, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
const T &Get(TypeWrapper<const T &>, HSQUIRRELVM vm, SQInteger index);

/// \overload
SQRESULT Push(HSQUIRRELVM vm, bool value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, char value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, int8_t value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, uint8_t value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, int16_t value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, uint16_t value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, int32_t value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, uint32_t value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, float value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, const SQChar *value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, SQUserPointer value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, HSQOBJECT value);

/// \overload
bool Match(TypeWrapper<bool> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<char> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<int16_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<uint16_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<int16_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<uint16_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<int32_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<uint32_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<float> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<const SQChar*> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<SQUserPointer> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<HSQOBJECT> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \overload
bool          Get(TypeWrapper<bool> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
char          Get(TypeWrapper<char> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
int8_t        Get(TypeWrapper<int8_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
uint8_t       Get(TypeWrapper<uint8_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
int16_t       Get(TypeWrapper<int16_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
uint16_t      Get(TypeWrapper<uint16_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
int32_t       Get(TypeWrapper<int32_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
uint32_t      Get(TypeWrapper<uint32_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
float         Get(TypeWrapper<float> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
const SQChar *Get(TypeWrapper<const SQChar *> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
SQUserPointer Get(TypeWrapper<SQUserPointer> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
HSQOBJECT     Get(TypeWrapper<HSQOBJECT> wrapper, HSQUIRRELVM vm, SQInteger index);

#if defined(_SQ64)
/// \overload
SQRESULT  Push(HSQUIRRELVM vm, int64_t value);
/// \overload
SQRESULT  Push(HSQUIRRELVM vm, uint64_t value);
/// \overload
bool      Match(TypeWrapper<int64_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool      Match(TypeWrapper<uint64_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
int64_t   Get(TypeWrapper<int64_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
uint64_t  Get(TypeWrapper<uint64_t> wrapper, HSQUIRRELVM vm, SQInteger index);
#endif // defined(_SQ64)

#if defined(SQUSEDOUBLE)
/// \overload
SQRESULT  Push(HSQUIRRELVM vm, double value);
/// \overload
bool      Match(TypeWrapper<double> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
double    Get(TypeWrapper<double> wrapper, HSQUIRRELVM vm, SQInteger index);
#endif // defined(SQUSEDOUBLE)

} // namespace sqb

// ---- #include <sqbind/sqbStackUtils.inl>
// ---> including sqbStackUtils.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// Push
//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, bool value)
{
  sq_pushbool(vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, char value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, int8_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, uint8_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, int16_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, uint16_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, int32_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, uint32_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, float value)
{
  sq_pushfloat(vm, static_cast<SQFloat>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, const SQChar *value)
{
  sq_pushstring(vm, value, -1);
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, SQUserPointer value)
{
  sq_pushuserpointer(vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, HSQOBJECT value)
{
  sq_pushobject(vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
/// Match
//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<bool> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return sq_gettype(vm, index) == OT_BOOL;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<char> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<int8_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<uint8_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<int16_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<uint16_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<int32_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<uint32_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<float> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<const SQChar*> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return sq_gettype(vm, index) == OT_STRING;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<SQUserPointer> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return sq_gettype(vm, index) == OT_USERPOINTER;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<HSQOBJECT> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
/// Get
//----------------------------------------------------------------------------------------------------------------------
inline bool Get(TypeWrapper<bool> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQBool value;
  SQRESULT result = sq_getbool(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value == SQTrue;
}

//----------------------------------------------------------------------------------------------------------------------
inline char Get(TypeWrapper<char> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value = 0;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<char>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline int8_t Get(TypeWrapper<int8_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value = 0;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<int8_t>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline uint8_t Get(TypeWrapper<uint8_t>, HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value = 0;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<uint8_t>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline int16_t Get(TypeWrapper<int16_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value = 0;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<int16_t>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline uint16_t Get(TypeWrapper<uint16_t>, HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value = 0;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<uint16_t>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline int32_t Get(TypeWrapper<int32_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<int32_t>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline uint32_t Get(TypeWrapper<uint32_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<uint32_t>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline float Get(TypeWrapper<float> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQFloat value;
  SQRESULT result = sq_getfloat(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<float>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline const SQChar *Get(TypeWrapper<const SQChar*> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  const SQChar *value;
  SQRESULT result = sq_getstring(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQUserPointer Get(TypeWrapper<SQUserPointer> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQUserPointer value;
  SQRESULT result = sq_getuserpointer(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline HSQOBJECT Get(TypeWrapper<HSQOBJECT> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQBIND_ASSERT(index != 0);
  SQBIND_ASSERT(-sq_gettop(vm) <= index);
  SQBIND_ASSERT(index <= sq_gettop(vm));

  HSQOBJECT value;
  // sq_getstackobj always returns SQ_OK so no need to test the result
  //
  sq_getstackobj(vm, index, &value);
  return value;
}

#if defined(_SQ64)

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, int64_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, uint64_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<int64_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<uint64_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline int64_t Get(TypeWrapper<int64_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<int64_t>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline uint64_t Get(TypeWrapper<uint64_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<uint64_t>(value);
}

#endif // defined(_SQ64)

#if defined(SQUSEDOUBLE)

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, double value)
{
  sq_pushfloat(vm, static_cast<SQFloat>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<double> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline double Get(TypeWrapper<double> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQFloat value;
  SQRESULT result = sq_getfloat(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<double>(value);
}

#endif // defined(SQUSEDOUBLE)

} // namespace sqb

// <--- back to sqbStackUtils.h


#endif

// <--- back to xsqbind.h
// ---- #include "sqbind/sqbTypeInfo.h"
// ---> including sqbTypeInfo.h
#ifndef _SQBTYPEINFO_H
#define _SQBTYPEINFO_H

// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbBaseHeader.h>
// ---> including sqbBaseHeader.h
// <--- back to sqbTypeInfo.h
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_TYPEINFO(TYPE, NAME)
/// \brief Declares the sqb::TypeInfo struct for a type. This is required for binding a type as a variable.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_TYPEINFO(TYPE, NAME) \
  namespace sqb \
  { \
  template<> \
  struct TypeInfo<TYPE> \
  { \
    enum \
    { \
      kTypeID = kScriptVarTypeInstance, \
      kTypeSize = sizeof(TYPE), \
      kTypeMask = 'x', \
      kTypeIsInstance = SQTrue, \
    }; \
    const SQChar *m_typeName; \
    inline TypeInfo() \
    : m_typeName(_SC(#NAME)) \
    { \
    } \
    inline operator ScriptVarType() const \
    { \
      return static_cast<ScriptVarType>(kTypeID); \
    } \
  }; \
  }

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief Converts from a SQObjectType to a string.
/// \code
/// // prints out "string"
/// scprintf(RawTypeToTypeName(OT_STRING));
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
inline const SQChar *RawTypeToTypeName(SQObjectType type);

//----------------------------------------------------------------------------------------------------------------------
/// \brief List of basic types that are supported.
//----------------------------------------------------------------------------------------------------------------------
enum ScriptVarType
{
  kScriptVarTypeNone = -1,
  kScriptVarTypeBool = 0,
  kScriptVarTypeChar,
  kScriptVarTypeInt8,
  kScriptVarTypeUInt8,
  kScriptVarTypeInt16,
  kScriptVarTypeUInt16,
  kScriptVarTypeInt32,
  kScriptVarTypeUInt32,
  kScriptVarTypeFloat,
  kScriptVarTypeString,
  kScriptVarTypeUserPointer,
  kScriptVarTypeInstance,
  kScriptVarTypeObject,
#if defined(_SQ64)
  kScriptVarTypeInt64,
  kScriptVarTypeUInt64,
#endif // defined(_SQ64)
#if defined(SQUSEDOUBLE)
  kScriptVarTypeDouble,
#endif // defined(SQUSEDOUBLE)
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief Template class for gaining info about a bound script type. Specialisation of TypeInfo
/// is done automatically when a type is declared using #SQBIND_DECLARE_TYPEINFO or any of the other
/// macros that call it.
//----------------------------------------------------------------------------------------------------------------------
template<typename T>
struct TypeInfo
{
  enum
  {
    kTypeID = kScriptVarTypeNone,
    kTypeSize = sizeof(T),
    kTypeMask = '?',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
/// \cond NO_DOXYGEN
template<>
struct TypeInfo<bool>
{
  enum
  {
    kTypeID = kScriptVarTypeBool,
    kTypeSize = sizeof(bool),
    kTypeMask = 'b',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<char>
{
  enum
  {
    kTypeID = kScriptVarTypeChar,
    kTypeSize = sizeof(char),
    kTypeMask = 'i',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<int8_t>
{
  enum
  {
    kTypeID = kScriptVarTypeInt8,
    kTypeSize = sizeof(int8_t),
    kTypeMask = 'i',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<uint8_t>
{
  enum
  {
    kTypeID = kScriptVarTypeUInt8,
    kTypeSize = sizeof(uint8_t),
    kTypeMask = 'i',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<int16_t>
{
  enum
  {
    kTypeID = kScriptVarTypeInt16,
    kTypeSize = sizeof(int16_t),
    kTypeMask = 'i',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<uint16_t>
{
  enum
  {
    kTypeID = kScriptVarTypeUInt16,
    kTypeSize = sizeof(uint16_t),
    kTypeMask = 'i',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<int32_t>
{
  enum
  {
    kTypeID = kScriptVarTypeInt32,
    kTypeSize = sizeof(int32_t),
    kTypeMask = 'n',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<uint32_t>
{
  enum
  {
    kTypeID = kScriptVarTypeUInt32,
    kTypeSize = sizeof(uint32_t),
    kTypeMask = 'n',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<float>
{
  enum
  {
    kTypeID = kScriptVarTypeFloat,
    kTypeSize = sizeof(float),
    kTypeMask = 'n',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<const SQChar*>
{
  enum
  {
    kTypeID = kScriptVarTypeString,
    kTypeSize = sizeof(const SQChar*),
    kTypeMask = 's',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<SQUserPointer>
{
  enum
  {
    kTypeID = kScriptVarTypeUserPointer,
    kTypeSize = sizeof(SQUserPointer),
    kTypeMask = 'p',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<HSQOBJECT>
{
  enum
  {
    kTypeID = kScriptVarTypeObject,
    kTypeSize = sizeof(HSQOBJECT),
    kTypeMask = '.',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

#if defined(_SQ64)

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<int64_t>
{
  enum
  {
    kTypeID = kScriptVarTypeInt64,
    kTypeSize = sizeof(int64_t),
    kTypeMask = 'n',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<uint64_t>
{
  enum
  {
    kTypeID = kScriptVarTypeUInt64,
    kTypeSize = sizeof(uint64_t),
    kTypeMask = 'n',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

#endif // defined(_SQ64)

#if defined(SQUSEDOUBLE)

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<double>
{
  enum
  {
    kTypeID = kScriptVarTypeDouble,
    kTypeSize = sizeof(double),
    kTypeMask = 'n',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

#endif // defined(SQUSEDOUBLE)
/// \endcond

} // namespace sqb

// ---- #include <sqbind/sqbTypeInfo.inl>
// ---> including sqbTypeInfo.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
inline const SQChar *RawTypeToTypeName(SQObjectType type)
{
  switch(_RAW_TYPE(type))
  {
  case _RT_NULL:
    return _SC("null");
  case _RT_INTEGER:
    return _SC("integer");
  case _RT_FLOAT:
    return _SC("float");
  case _RT_BOOL:
    return _SC("bool");
  case _RT_STRING:
    return _SC("string");
  case _RT_TABLE:
    return _SC("table");
  case _RT_ARRAY:
    return _SC("array");
  case _RT_GENERATOR:
    return _SC("generator");
  case _RT_CLOSURE:
  case _RT_NATIVECLOSURE:
    return _SC("function");
  case _RT_USERDATA:
  case _RT_USERPOINTER:
    return _SC("userdata");
  case _RT_THREAD:
    return _SC("thread");
  case _RT_CLASS:
    return _SC("class");
  case _RT_INSTANCE:
    return _SC("instance");
  case _RT_WEAKREF:
    return _SC("weakref");
  default:
    break;
  }
  return _SC("");
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<bool>
//----------------------------------------------------------------------------------------------------------------------
template<typename T>
inline TypeInfo<T>::TypeInfo()
: m_typeName(_SC(""))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<bool>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<bool>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_BOOL))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<char>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<char>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<int8_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<int8_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<uint8_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<uint8_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<int16_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<int16_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<uint16_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<uint16_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<int32_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<int32_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<uint32_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<uint32_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<float>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<float>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_FLOAT))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<const SQChar*>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<const SQChar*>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_STRING))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<SQUserPointer>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<SQUserPointer>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_USERPOINTER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<HSQOBJECT>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<HSQOBJECT>::TypeInfo()
: m_typeName(_SC("object"))
{
}

#if defined(_SQ64)

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<int64_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<int64_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<uint64_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<uint64_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

#endif

#if defined(SQUSEDOUBLE)

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<double>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<double>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_FLOAT))
{
}

#endif

} // namespace sqb

// <--- back to sqbTypeInfo.h

#endif

// <--- back to xsqbind.h


#include <vector>
#include <string>



namespace sqb {

	//template<typename T>
	//T Get(TypeWrapper<T> wrapper, HSQUIRRELVM vm, SQInteger index);

	template<>
	struct TypeInfo<SqRef>
	{
	  enum
	  {
		kTypeID = kScriptVarTypeObject,
		kTypeSize = sizeof(SqRef),
		kTypeMask = '.',
		kTypeIsInstance = SQFalse,
	  };
	  const SQChar *m_typeName;
	  TypeInfo() : m_typeName(_SC("SqRef")) {}
	};

	template<>
	struct TypeInfo<std::string>
	{
	  enum
	  {
		kTypeID = kScriptVarTypeObject,
		kTypeSize = sizeof(std::string),
		kTypeMask = 's',
		kTypeIsInstance = SQFalse,
	  };
	  const SQChar *m_typeName;
	  TypeInfo() : m_typeName(_SC("string")) {}
	};


	// ---- vec2 ----
#ifdef XSQ_VEC2
	template<> struct TypeInfo<XSQ_VEC2>
	{
		enum
		{
			kTypeID = kScriptVarTypeInstance,
			kTypeSize = sizeof(XSQ_VEC2),
			kTypeMask = 'x',
			kTypeIsInstance = SQTrue,
		};
		const SQChar *m_typeName;
		inline TypeInfo() : m_typeName(_SC("vec2"))
		{
		}
		inline operator ScriptVarType() const
		{
			return static_cast<ScriptVarType>(kTypeID);
		}
	}; \
	template<> inline bool Match<XSQ_VEC2>(TypeWrapper<XSQ_VEC2>, HSQUIRRELVM vm, SQInteger idx)					{ return true; }
	template<> inline bool Match<XSQ_VEC2 &>(TypeWrapper<XSQ_VEC2 &>, HSQUIRRELVM vm, SQInteger idx)				{ return true; }
	template<> inline bool Match<const XSQ_VEC2 &>(TypeWrapper<const XSQ_VEC2 &>, HSQUIRRELVM vm, SQInteger idx)	{ return true; }
	inline XSQ_VEC2 Get(TypeWrapper<XSQ_VEC2>, HSQUIRRELVM vm, SQInteger idx)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		XSQ_VEC2 value = XSQ_VEC2(0,0);
		sqvm._sq_get(value,idx);
		return value;
	}
	inline XSQ_VEC2 Get(TypeWrapper<XSQ_VEC2&>, HSQUIRRELVM vm, SQInteger idx)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		XSQ_VEC2 value = XSQ_VEC2(0, 0);
		sqvm._sq_get(value, idx);
		return value;
	}
	inline XSQ_VEC2 Get(TypeWrapper<const XSQ_VEC2 &>, HSQUIRRELVM vm, SQInteger idx)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		XSQ_VEC2 value = XSQ_VEC2(0, 0);
		sqvm._sq_get(value, idx);
		return value;
	}
	template<> inline SQRESULT Push<XSQ_VEC2>(HSQUIRRELVM vm, XSQ_VEC2 &value)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		return sqvm._sq_push(value);
	}
	template<> inline SQRESULT Push<XSQ_VEC2>(HSQUIRRELVM vm, const XSQ_VEC2 &value)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		return sqvm._sq_push(value);
	}
#endif

	// ---- vec3 ----
#ifdef XSQ_VEC3
	template<> struct TypeInfo<XSQ_VEC3>
	{
		enum
		{
			kTypeID = kScriptVarTypeInstance,
			kTypeSize = sizeof(XSQ_VEC3),
			kTypeMask = 'x',
			kTypeIsInstance = SQTrue,
		};
		const SQChar *m_typeName;
		inline TypeInfo() : m_typeName(_SC("vec3"))
		{
		}
		inline operator ScriptVarType() const
		{
			return static_cast<ScriptVarType>(kTypeID);
		}
	};
	template<> inline bool Match<XSQ_VEC3>(TypeWrapper<XSQ_VEC3>, HSQUIRRELVM vm, SQInteger idx)					{ return true; }
	template<> inline bool Match<XSQ_VEC3 &>(TypeWrapper<XSQ_VEC3 &>, HSQUIRRELVM vm, SQInteger idx)				{ return true; }
	template<> inline bool Match<const XSQ_VEC3 &>(TypeWrapper<const XSQ_VEC3 &>, HSQUIRRELVM vm, SQInteger idx)	{ return true; }
	inline XSQ_VEC3 Get(TypeWrapper<XSQ_VEC3>, HSQUIRRELVM vm, SQInteger idx)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		XSQ_VEC3 value = XSQ_VEC3(0, 0, 0);
		sqvm._sq_get(value, idx);
		return value;
	}
	inline XSQ_VEC3 Get(TypeWrapper<XSQ_VEC3&>, HSQUIRRELVM vm, SQInteger idx)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		XSQ_VEC3 value = XSQ_VEC3(0, 0, 0);
		sqvm._sq_get(value, idx);
		return value;
	}
	inline XSQ_VEC3 Get(TypeWrapper<const XSQ_VEC3 &>, HSQUIRRELVM vm, SQInteger idx)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		XSQ_VEC3 value = XSQ_VEC3(0, 0, 0);
		sqvm._sq_get(value, idx);
		return value;
	}
	template<> inline SQRESULT Push<XSQ_VEC3>(HSQUIRRELVM vm, XSQ_VEC3 &value)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		return sqvm._sq_push(value);
	}
	template<> inline SQRESULT Push<XSQ_VEC3>(HSQUIRRELVM vm, const XSQ_VEC3 &value)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		return sqvm._sq_push(value);
	}
#endif
}


#define XSQ_REGISTER_FN(fn)		\
	static void __xsq_register_##fn(HSQUIRRELVM vm) {	\
		sq_pushroottable(vm);							\
		sqb::Bind::BindFunction(vm, -1, &fn, #fn);		\
		sq_poptop(vm);									\
	}													\
	static char __xsq_register_trigger_##fn = (__xsq_register::add(__xsq_register_##fn), 0);



// ---- #include "sqbind/SquirrelBind.h"
// ---> including SquirrelBind.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the 'Software'), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbAssert.h>
// ---> including sqbAssert.h
// <--- back to SquirrelBind.h
// ---- #include <sqbind/sqbBind.h>
// ---> including sqbBind.h
#ifndef _SQBIND_H
#define _SQBIND_H

// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
#include <cstring>
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/autogen/sqbCall.h>
// ---> including sqbCall.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the 'Software'), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbind/autogen/sqbReturnSpecialisation.h"
// ---> including sqbReturnSpecialisation.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the 'Software'), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbind/sqbStackHandler.h"
// ---> including sqbStackHandler.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbAssert.h>
// ---> including sqbAssert.h
// <--- back to sqbStackHandler.h
// ---- #include <sqbind/sqbClassHelpers.h>
// ---> including sqbClassHelpers.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbTypeInfo.h>
// ---> including sqbTypeInfo.h
// <--- back to sqbClassHelpers.h
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief Default function used as _typeof metamethod func of classes bound with #RegisterClassType.
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
SQInteger TypeOf(HSQUIRRELVM vm);

//----------------------------------------------------------------------------------------------------------------------
/// \brief Creates an instance of classObject and set its release hook without invoking the constructor.
/// Resulting instance is left on the top of the stack. The function will fail if classObject is not of
/// type OT_CLASS or the call to sq_createinstance fails. If the call to sq_createinstance fails then
/// the error can be retrieved by getting the last error for the vm.
//----------------------------------------------------------------------------------------------------------------------
SQBIND_API bool CreateNativeClassInstance(HSQUIRRELVM vm, HSQOBJECT classObject, SQRELEASEHOOK hook);

}

// ---- #include <sqbind/sqbClassHelpers.inl>
// ---> including sqbClassHelpers.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
SQInteger TypeOf(HSQUIRRELVM v)
{
  sq_pushstring(v, TypeInfo<ClassType>().m_typeName, -1);
  return 1;
}

} // namespace sqb

// <--- back to sqbClassHelpers.h

// <--- back to sqbStackHandler.h
// ---- #include <sqbind/sqbClassTypeTag.h>
// ---> including sqbClassTypeTag.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
#include <cstdio>
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbAssert.h>
// ---> including sqbAssert.h
// <--- back to sqbClassTypeTag.h
// ---- #include <sqbind/sqbTypeInfo.h>
// ---> including sqbTypeInfo.h
// <--- back to sqbClassTypeTag.h
// ---- #include <sqbind/sqbTypeTraits.h>
// ---> including sqbTypeTraits.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqbTypeTraits.h
//----------------------------------------------------------------------------------------------------------------------

/// \defgroup typetraits Class type traits
//@{

namespace sqb
{
namespace traits
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief This helper struct defines whether a class is a pod type. When an instance of a bound pod class is
/// released there is no need to call its destructor. For classes bound using ClassUserDataClassDef this means
/// there is no need for a release hook at all. For classes bound using SqMallocClassDef there is only a need
/// to call sq_free. There is no way to automatically check if a class is a pod type so classes must be declared
/// as such using DECLARE_TYPE_POD.
//----------------------------------------------------------------------------------------------------------------------
template<typename T>
struct IsPod { enum { kValue = false }; };

//----------------------------------------------------------------------------------------------------------------------
/// \brief Used to query whether a type is copyable. To make a type non-copyable specialise this class
/// or use the macros #SQBIND_DECLARE_NON_COPYABLE_CLASS_NAME or #SQBIND_DECLARE_NON_COPYABLE_CLASS.
/// Copyable types will use the assignment operator to copy them, non-copyable types by default will use
/// memcpy and sizeof(T). To change the copy operation of a type specialise ClassTypeCopyImpl before
/// declaring the type.
//----------------------------------------------------------------------------------------------------------------------
template<typename T>
struct IsCopyable { enum { kValue = true }; };

//----------------------------------------------------------------------------------------------------------------------
/// \brief This helper struct defines whether a class is aligned or not.
//----------------------------------------------------------------------------------------------------------------------
template<typename T>
struct IsAligned { enum { kIsAligned = false, kAlignment = 4, }; };

//----------------------------------------------------------------------------------------------------------------------
/// \brief Used to remove const, pointer and reference qualifiers from a given type. Used when querying
/// information about a type with TypeInfo and other traits classes.
//----------------------------------------------------------------------------------------------------------------------
template<typename Type>
struct RemoveQualifiers { typedef Type kType; };

} // namespace traits

} // namespace sqb

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_TYPE_POD(TYPE)
/// \brief Informs sqbind a class is a pod type, this means the binding code can optimise the class by simplifying
/// or in some cases removing each instances release hook. This does not affect the behaviour of Push so if the release
/// hook is set manually using ClassType::SetReleaseHook it will still be set for each instance of classes created with
/// Push(const MyClass&).
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_TYPE_POD(TYPE) \
  namespace sqb \
  { \
  namespace traits \
  { \
  template<> \
  struct IsPod<TYPE> { enum { kValue = true }; }; \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_TYPE_NON_COPYABLE(TYPE)
/// \brief 
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_TYPE_NON_COPYABLE(TYPE) \
  namespace sqb \
  { \
  namespace traits \
  { \
  template<> \
  struct IsCopyable<TYPE> { enum { kValue = false }; }; \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_TYPE_ALIGNED(TYPE, ALIGNMENT)
/// \brief Declares a class type to be aligned.
/// \note Alignment currently only works with classes declared with SQBIND_DECLARE_CLASS and ClassDefinition or
///   SQBIND_DECLARE_CLASSUD_CLASS and ClassUserDataClassDefinition. Instances bound with the other macros/class
///   definitions will not be aligned.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_TYPE_ALIGNED(TYPE, ALIGNMENT) \
  namespace sqb \
  { \
  namespace traits \
  { \
  template<> \
  struct IsAligned<TYPE> { enum { kIsAligned = true, kAlignment = ALIGNMENT, }; }; \
  } \
  }

//@}

// ---- #include <sqbind/sqbTypeTraits.inl>
// ---> including sqbTypeTraits.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
namespace traits
{
//----------------------------------------------------------------------------------------------------------------------
// RemoveQualifiers specialisations.
//----------------------------------------------------------------------------------------------------------------------
template<typename Type>
struct RemoveQualifiers<const Type> { typedef Type kType; };

//----------------------------------------------------------------------------------------------------------------------
template<typename Type>
struct RemoveQualifiers<Type &> { typedef Type kType; };

//----------------------------------------------------------------------------------------------------------------------
template<typename Type>
struct RemoveQualifiers<Type *> { typedef Type kType; };

//----------------------------------------------------------------------------------------------------------------------
template<typename Type>
struct RemoveQualifiers<const Type &> { typedef Type kType; };

//----------------------------------------------------------------------------------------------------------------------
template<typename Type>
struct RemoveQualifiers<const Type *> { typedef Type kType; };

//----------------------------------------------------------------------------------------------------------------------
template<typename Type>
struct RemoveQualifiers<Type *&> { typedef Type kType; };

//----------------------------------------------------------------------------------------------------------------------
template<typename Type>
struct RemoveQualifiers<const Type *&> { typedef Type kType; };

//----------------------------------------------------------------------------------------------------------------------
// specialisation for strings so they are correctly identified when using
// RemoveQualifiers combined with TypeInfo.
template<>
struct RemoveQualifiers<const SQChar *> { typedef const SQChar *kType; };

} // namespace traits

} // namespace sqb

// <--- back to sqbTypeTraits.h

// <--- back to sqbClassTypeTag.h
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief For binding classes that have no base class.
//----------------------------------------------------------------------------------------------------------------------
class NoBaseClass { };

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
typedef void (*CopyInstanceFunction)(void *dst, void *src);

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API ClassTypeTagBase
{
public:
  ClassTypeTagBase();
  virtual ~ClassTypeTagBase();

  /// \brief As this class is used as a type tag it will be cast to void pointers and back again, this check
  /// should ensure that other typetags cast from void pointers are not incorrectly used as this.
  bool IsValid() const;

  /// \brief Many types cannot have offset, since "this" is the same for all base classes of
  /// an instance. Detect this, to avoid sum up base offsets all the time.
  bool MayHaveOffset() const;
  /// \brief Gets the offset to this class from the base class pointer.
  ptrdiff_t GetOffsetTo(const ClassTypeTagBase *pbase) const;

  /// \brief Get the script name of the type
  const SQChar *GetTypeName() const;

  /// \brief Sets the release hook for the class.
  /// \note Always use the instance returned by the static Get function to call this func.
  void SetReleaseHook(SQRELEASEHOOK releaseHook);
  /// \brief Get the release hook for this class.
  /// \note Always use the instance returned by the static Get function to call this func.
  SQRELEASEHOOK GetReleaseHook() const;

  /// \brief Stores the class in the vm's registry table.
  void SetClassObject(HSQUIRRELVM vm, HSQOBJECT classObject);
  /// \brief Retrieves the class from the vm's registry table. The returned object handle is not a strong
  /// reference to the class object, make sure to call sq_addref if a strong reference is needed.
  HSQOBJECT GetClassObject(HSQUIRRELVM vm) const;

  /// \brief Checks that a class userdata is exactly equal to a specific size.
  /// \note Class user data is set using sq_setclassudsize or ClassDefBase::SetUserDataSize.
  bool CheckClassUserDataSize(HSQUIRRELVM vm, SQInteger expectedSize) const;

  virtual CopyInstanceFunction GetCopyFunction() const = 0;

protected:
  /// \brief Name of type.
  const SQChar *m_name;
  /// \brief Sets the release hook for the class.
  SQRELEASEHOOK m_releaseHook;
  /// \brief pointer to base class type.
  ClassTypeTagBase *m_baseType;
  /// \brief Adjustment of this pointer between this type and its base class.
  ptrdiff_t m_offset;
  /// \brief Set to 0 for types that cannot possibly have offset.
  mutable int8_t m_mayHaveOffset;

private:
  static const int32_t m_expectedValidityCheck;
  const int32_t m_validityCheck;

  // disable copy construction
  //
  ClassTypeTagBase(const ClassTypeTagBase&);
  const ClassTypeTagBase& operator = (const ClassTypeTagBase&);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief This level handles instance copying in different ways
//----------------------------------------------------------------------------------------------------------------------
template<typename T, bool copyable>
class ClassTypeTagCopyImpl;

//----------------------------------------------------------------------------------------------------------------------
/// \brief Base class to do copying using the assignment operator.
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
class ClassTypeTagCopyImpl<ClassType, true> : public ClassTypeTagBase
{
protected:
  /// \brief this works for types with assignment operator
  static void CopyInstance(ClassType *dst, ClassType *src);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief Base class to do copying with memcpy
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
class ClassTypeTagCopyImpl<ClassType, false> : public ClassTypeTagBase
{
protected:
  /// \brief This will assert if possible or do nothing.
  static void CopyInstance(ClassType *dst, ClassType *src);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief Used to get info about types.
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
class ClassTypeTag : public ClassTypeTagCopyImpl<ClassType, traits::IsCopyable<ClassType>::kValue>
{
public:
  typedef ClassTypeTagCopyImpl<ClassType, traits::IsCopyable<ClassType>::kValue> ThisBaseType;

  // helps resolve unqualified names to members of the dependent base class.
  using ThisBaseType::m_baseType;
  using ThisBaseType::m_name;
  using ThisBaseType::m_offset;

#if defined(SQBIND_COMPILER_MSVC)
#pragma warning(push)
// nonstandard extension used: override specifier 'override'
#pragma warning(disable: 4481)
#endif

  /// \brief Override from ClassTypeTagBase
  CopyInstanceFunction GetCopyFunction() const SQBIND_OVERRIDE;

#if defined(SQBIND_COMPILER_MSVC)
#pragma warning(pop)
#endif

  /// \brief Sets the base class type for this type.
  /// \note Always use the instance returned by the static Get function to call this func.
  ///   Have to pass a dummy pointer to the class type to help gcc out.
  template<typename BaseClassType>
  void SetBaseClass(BaseClassType *);

  /// \brief Gets an instance of ClassType<T> to save many being created.
  static ClassTypeTag<ClassType> *Get();

protected:
  ClassTypeTag();

private:
  static ClassTypeTag m_instance;

  // copy construction and assignment are disabled
  ClassTypeTag(const ClassTypeTag &rhs);
  const ClassTypeTag &operator = (const ClassTypeTag &rhs);
};

}

// ---- #include <sqbind/sqbClassTypeTag.inl>
// ---> including sqbClassTypeTag.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// ClassTypeTagBase functions.
//----------------------------------------------------------------------------------------------------------------------
inline bool ClassTypeTagBase::IsValid() const
{
  return m_validityCheck == m_expectedValidityCheck;
}

//----------------------------------------------------------------------------------------------------------------------
inline const SQChar *ClassTypeTagBase::GetTypeName() const
{
  return m_name;
}

//----------------------------------------------------------------------------------------------------------------------
inline void ClassTypeTagBase::SetReleaseHook(SQRELEASEHOOK releaseHook)
{
  m_releaseHook = releaseHook;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRELEASEHOOK ClassTypeTagBase::GetReleaseHook() const
{
  return m_releaseHook;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline void ClassTypeTagCopyImpl<ClassType, true>::CopyInstance(ClassType *dst, ClassType *src)
{
  *dst = *src;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline void ClassTypeTagCopyImpl<ClassType, false>::CopyInstance(
  ClassType *SQBIND_UNUSED(dst),
  ClassType *SQBIND_UNUSED(src))
{
  SQBIND_ASSERT_FAIL();
}

//----------------------------------------------------------------------------------------------------------------------
/// ClassTypeTag<ClassType>
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
ClassTypeTag<ClassType> ClassTypeTag<ClassType>::m_instance;

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline CopyInstanceFunction ClassTypeTag<ClassType>::GetCopyFunction() const
{
  return reinterpret_cast<CopyInstanceFunction>(&ThisBaseType::CopyInstance);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
template<typename BaseClassType>
void ClassTypeTag<ClassType>::SetBaseClass(BaseClassType *)
{
  m_baseType = ClassTypeTag<BaseClassType>::Get();

  // get the this pointer as the type ClassType (could be anything instead of this other than nullptr)
  //
  const ClassType *pt = reinterpret_cast<ClassType *>(this);
  // subtract the type pointer from the same pointer cast to the base type
  // the cast to base type offsets the pointer if there is any offset between types BC and T
  // subtracting T* from BC* for the same instance will result in the offset.
  //
  m_offset = reinterpret_cast<const char *>(pt) - reinterpret_cast<const char *>(static_cast<const BaseClassType *>(pt));
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline ClassTypeTag<ClassType> *ClassTypeTag<ClassType>::Get()
{
  return &m_instance;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
inline ClassTypeTag<NoBaseClass> *ClassTypeTag<NoBaseClass>::Get()
{
  return nullptr;
}

// as all ClassTypeTagBase are static instances this destructor is hit after the test coverage scanning has finished
//
SQBIND_TEST_COVERAGE_OFF()
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline ClassTypeTag<ClassType>::ClassTypeTag()
{
  m_name = TypeInfo<ClassType>().m_typeName;
}
SQBIND_TEST_COVERAGE_ON()

} // namespace sqb

// <--- back to sqbClassTypeTag.h

// <--- back to sqbStackHandler.h
// ---- #include <sqbind/sqbStackUtils.h>
// ---> including sqbStackUtils.h
// <--- back to sqbStackHandler.h
// ---- #include <sqbind/sqbTypeInfo.h>
// ---> including sqbTypeInfo.h
// <--- back to sqbStackHandler.h
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief
/// Wraps common functionality for handling the squirrel stack passed into a native closure.
//----------------------------------------------------------------------------------------------------------------------
class StackHandler
{
public:
  /// \brief Initialises the stack handler with a \link #HSQUIRRELVM vm\endlink.
  StackHandler(HSQUIRRELVM vm);

  /// \brief Gets the virtual machine the stack belongs to.
  HSQUIRRELVM GetVMPtr() const;

  /// \brief Gets the number of arguments on the stack.
  SQInteger GetParamCount() const;

  /// \brief Gets the type of the object at the specified index.
  SQObjectType GetType(SQInteger index) const;

  /// \brief Gets the type name of the object at the specified index.
  /// Will generate the same result as calling typeof(obj) in squirrel.
  const SQChar *GetTypeName(SQInteger index) const;

  /// \brief Same as GetType(index) == OT_INTEGER || GetType(index) == OT_FLOAT
  bool IsNumber(SQInteger index) const;

  /// \brief Convenience function same as calling GetType(index) == OT_STRING.
  bool IsString(SQInteger index) const;

  /// \brief Convenience function same as calling GetType(index) == OT_INSTANCE.
  bool IsInstance(SQInteger index) const;

  /// \brief Checks if the object at stack index index is an instance of a particular bound class type.
  /// \code
  /// sqb::StackHandler stack(vm);
  /// ...
  /// if (stack.IsInstanceOfType<MyClass>(1))
  /// {
  ///   MyClass *ptr = stack.GetInstance<MyClass>();
  /// }
  /// \endcode
  template<typename ClassType>
  bool IsInstanceOfType(SQInteger index) const;

  /// \brief Gets an integer from the stack at the specified index. If the object at that index
  /// is not an integer then 0 is returned.
  SQInteger GetInteger(SQInteger index);
  /// \brief Gets a float from the stack at the specified index. If the object at that index is
  /// not a float then 0.0f is returned.
  SQFloat GetFloat(SQInteger index);
  /// \brief Gets a number from the stack. If the object at that index is not a number then 0 is returned.
  /// \code
  /// sqb::StackHandler sh(vm);
  /// float value = sh.GetNumber<float>(1);
  /// \endcode
  template<typename NumberType>
  NumberType GetNumber(SQInteger index);

  /// \brief Gets a boolean from the stack at the specified index. If the object at that index
  /// is not a boolean then the function returns false.
  bool GetBool(SQInteger index);

  /// \brief Gets a string from the stack at the specified index. If the object at that index is
  /// not a string then null is returned.
  const SQChar *GetString(SQInteger index);

  /// \brief Gets a user data from the stack at the specified index.
  SQUserPointer GetUserData(SQInteger index);
  /// \brief Gets a user data from the stack at the specified index also returning an optional typetag.
  SQUserPointer GetUserDataAndTypeTag(SQInteger index, SQUserPointer *typetag);

  /// \brief Gets a user pointer from the stack at the specified index.
  SQUserPointer GetUserPointer(SQInteger index);

  /// \brief Gets an instance user pointer from the stack without checking the typetag.
  SQUserPointer GetInstance(SQInteger index);
  /// \brief Gets an instance of a class from the stack without checking it's type. Use in conjunction
  /// with IsInstanceOfType.
  /// \code
  /// sqb::StackHandler stack(vm);
  /// if (!stack.IsInstanceOfType<MyClass>(1))
  /// {
  ///   return stack.ThrowParamError(1, sqb::TypeInfo<MyClass>().m_typeName);
  /// }
  /// MyClass *_this = stack.GetInstance<MyClass>();
  /// \endcode
  /// \note MyClass must already be bound using SQBIND_DECLARE_CLASS(MyClass); and sqb::ClassDef<MyClass>.
  template<typename ClassType>
  ClassType* GetInstance(SQInteger index);
  /// \brief Gets an instance user pointer from the stack at the specified index checking the typetag, null
  /// typetag means no type check.
  SQUserPointer GetInstanceMatchTypeTag(SQInteger index, SQUserPointer typetag);
  /// \brief Gets a class instance from the stack using ClassType<T>::Get() as the typetag check.
  /// If the object at index is not an instance or does not have the correct typetag then it will
  /// return null otherwise it will return a pointer to the class instance.
  /// \code
  /// sqb::StackHandler stack(vm);
  /// MyClass* instance = stack.GetInstanceAsType<MyClass>(1);
  /// if (instance == nullptr)
  /// {
  ///   return stack.ThrowParamError(1, sqb::TypeInfo<MyClass>().m_typeName);
  /// }
  /// \endcode
  /// \note MyClass must already be bound using SQBIND_DECLARE_CLASS(MyClass); and sqb::ClassDef<MyClass>.
  template<typename ClassType>
  ClassType* GetInstanceAsType(SQInteger index);

  /// \brief Throws a null squirrel exception. This indicates that a set/get metamethod index was not found
  /// allowing squirrel to differentiate between this and a runtime error.
  SQInteger ThrowNull();

  /// \brief Throws a squirrel exception. Must be the returned by the native closure.
  /// \code
  /// StackHandler stack(vm);
  /// return stack.ThrowError(_SC("error message"));
  /// \endcode
  SQInteger ThrowError(const SQChar *format, ...);

  /// \brief Throws a squirrel exception with an error message specific for a call with the wrong
  /// number of parameters.
  SQInteger ThrowParamCountError(SQInteger expectedParamCount);

  /// \brief Throws a squirrel exception with an error message specific for a call with the wrong
  /// number of parameters.
  SQInteger ThrowParamCountError(SQInteger minParamCount, SQInteger maxParamCount);

  /// \brief Throws a squirrel exception with an error message specific for wrong parameter arguments.
  /// \code
  /// // squirrel code
  /// testfunc("blah")
  ///
  /// // c++ code inside testfunc
  /// StackHandler stack(vm);
  /// return stack.ThrowParamError(2, _SC("integer"));
  /// \endcode
  /// Generates the error message "parameter 1 has an invalid type 'string' ; expected: 'integer'".
  /// \note index is the index on the stack not the parameter argument number so a stack index of 2 would be
  /// the first parameter to the function. Stack index 1 is the hidden parameter 0 passed to all functions.
  SQInteger ThrowParamError(SQInteger index, const SQChar *expectedType);

  /// \brief Throws a squirrel exception with an error message specific for wrong parameter arguments.
  /// \code
  /// // squirrel code
  /// testfunc("blah")
  ///
  /// // c++ code inside testfunc
  /// StackHandler stack(vm);
  /// return stack.ThrowParamError(2, OT_INTEGER);
  /// \endcode
  /// Generates the error message "parameter 1 has an invalid type 'string' ; expected: 'integer'".
  /// \note index is the index on the stack not the parameter argument number so a stack index of 2 would be
  /// the first parameter to the function. Stack index 1 is the hidden parameter 0 passed to all functions.
  SQInteger ThrowParamError(SQInteger index, SQObjectType expectedType);

  /// \brief Used to returns nothing from a native closure, must be returned by the native closure.
  /// \return The number of arguments the closure returns.
  /// \code
  /// StackHandler sa(vm);
  ///   ...
  /// return sa.Return();
  /// \endcode
  SQInteger Return();
  /// \overload
  /// Makes the native closure return a bool.
  SQInteger Return(bool b);
  /// \overload
  /// Makes the native closure return an integer.
  SQInteger Return(SQInteger i);
  /// \overload
  /// Makes the native closure return a float.
  SQInteger Return(SQFloat f);
  /// \overload
  /// Makes the native closure return a string
  SQInteger Return(const SQChar *s, SQInteger length = -1);
  /// \overload
  /// Makes the native closure return a user pointer
  SQInteger Return(SQUserPointer p);
  /// \overload
  /// Makes the native closure return a HSQOBJECT.
  SQInteger Return(HSQOBJECT object);
  /// \overload
  /// Returns a bound class instance from a closure.
  template<typename ClassType>
  SQInteger Return(ClassType *instance);
  /// \overload
  /// Returns a bound class instance from a closure.
  template<typename ClassType>
  SQInteger Return(ClassType &instance);
  /// \overload
  /// Returns a bound class instance from a closure.
  template<typename ClassType>
  SQInteger Return(const ClassType *instance);
  /// \overload
  /// Returns a bound class instance from a closure.
  template<typename ClassType>
  SQInteger Return(const ClassType &instance);

  /// \overload
  /// In some cases can be quicker than the other templated return functions as it removes
  /// the need for an extra copy constructor and also removes some extra function calls.
  /// \code
  /// MyClass func();
  ///
  /// SQInteger sqfunc_standard(HSQUIRRELVM vm)
  /// {
  ///   return stack.Return(func());
  /// }
  ///
  /// SQInteger sqfunc_fast(HSQUIRRELVM vm)
  /// {
  ///   void *memory = sq_malloc(sizeof(MyClass));
  ///   MyClass *copy = new (memory) MyClass(func());
  ///   return stack.Return(copy, &sqb::DefaultReleaseHook<sqb::IsPodType<MyClass>::kValue>::SqFree<MyClass>);
  /// }
  /// \endcode
  template<typename ClassType>
  SQInteger Return(const ClassType *instance, SQRELEASEHOOK hook);

  /// \brief Suspends the execution of the vm must be returned by a c function.
  SQInteger SuspendVM();

private:
/// \cond NO_DOXYGEN
  HSQUIRRELVM m_vm;

  // disabled constructors and assignment operators
  StackHandler();
  StackHandler(const StackHandler &rhs);
  const StackHandler &operator = (const StackHandler &rhs);
/// \endcond
};

}

// ---- #include <sqbind/sqbStackHandler.inl>
// ---> including sqbStackHandler.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
inline StackHandler::StackHandler(HSQUIRRELVM vm)
: m_vm(vm)
{
}

//----------------------------------------------------------------------------------------------------------------------
inline HSQUIRRELVM StackHandler::GetVMPtr() const
{
  return m_vm;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::GetParamCount() const
{
  return sq_gettop(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType StackHandler::GetType(SQInteger index) const
{
  return sq_gettype(m_vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool StackHandler::IsNumber(SQInteger index) const
{
  return (sq_gettype(m_vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool StackHandler::IsString(SQInteger index) const
{
  return sq_gettype(m_vm, index) == OT_STRING;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool StackHandler::IsInstance(SQInteger index) const
{
  return sq_gettype(m_vm, index) == OT_INSTANCE;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline bool StackHandler::IsInstanceOfType(SQInteger index) const
{
  SQUserPointer up;
  SQUserPointer typetag = ClassTypeTag<ClassType>::Get();
  SQRESULT result = sq_getinstanceup(m_vm, index, &up, typetag);
  return SQ_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::GetInteger(SQInteger index)
{
  SQInteger value = 0;
  SQRESULT result = sq_getinteger(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQFloat StackHandler::GetFloat(SQInteger index)
{
  SQFloat value = static_cast<SQFloat>(0.0);
  SQRESULT result = sq_getfloat(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename NumberType>
inline NumberType StackHandler::GetNumber(SQInteger index)
{
  SQInteger value = 0;
  SQRESULT result = sq_getinteger(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<NumberType>(value);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
inline float StackHandler::GetNumber(SQInteger index)
{
  SQFloat value = 0;
  SQRESULT result = sq_getfloat(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<float>(value);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
inline double StackHandler::GetNumber(SQInteger index)
{
  SQFloat value = 0;
  SQRESULT result = sq_getfloat(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<double>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool StackHandler::GetBool(SQInteger index)
{
  SQBool value = SQFalse;
  SQRESULT result = sq_getbool(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value == SQTrue;
}

//----------------------------------------------------------------------------------------------------------------------
inline const SQChar *StackHandler::GetString(SQInteger index)
{
  const SQChar *value = _SC("");
  SQRESULT result = sq_getstring(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQUserPointer StackHandler::GetUserData(SQInteger index)
{
  SQUserPointer value = nullptr;
  SQRESULT result = sq_getuserdata(m_vm, index, &value, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQUserPointer StackHandler::GetUserDataAndTypeTag(SQInteger index, SQUserPointer *typetag)
{
  SQUserPointer value = nullptr;
  SQRESULT result = sq_getuserdata(m_vm, index, &value, typetag);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQUserPointer StackHandler::GetUserPointer(SQInteger index)
{
  SQUserPointer value = nullptr;
  SQRESULT result = sq_getuserpointer(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQUserPointer StackHandler::GetInstance(SQInteger index)
{
  SQUserPointer value = nullptr;
  SQRESULT result = sq_getinstanceup(m_vm, index, &value, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline ClassType *StackHandler::GetInstance(SQInteger index)
{
  SQUserPointer value = nullptr;
  SQRESULT result = sq_getinstanceup(m_vm, index, &value, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<ClassType *>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQUserPointer StackHandler::GetInstanceMatchTypeTag(SQInteger index, SQUserPointer typetag)
{
  // it's not a fatal failure if the typetags don't match so don't assert on the result of sq_getinstanceup,
  // only assert if it's not an instance on the stack.
  //
  SQBIND_ASSERT(sq_gettype(m_vm, index) == OT_INSTANCE);

  SQUserPointer value;
  if (SQ_SUCCEEDED(sq_getinstanceup(m_vm, index, &value, typetag)))
  {
    return value;
  }
  return nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline ClassType *StackHandler::GetInstanceAsType(SQInteger index)
{
  // it's not a fatal failure if the typetags don't match so don't assert on the result of sq_getinstanceup,
  // only assert if it's not an instance on the stack.
  //
  SQBIND_ASSERT(sq_gettype(m_vm, index) == OT_INSTANCE);

  SQUserPointer value;
  SQUserPointer typetag = ClassTypeTag<ClassType>::Get();
  if (SQ_SUCCEEDED(sq_getinstanceup(m_vm, index, &value, typetag)))
  {
    return static_cast<ClassType *>(value);
  }
  return nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::ThrowParamCountError(SQInteger expectedParamCount)
{
  SQInteger paramCount = GetParamCount();
  return ThrowError(
    _SC("wrong number of parameters '%d' ; expected '%d'"),
    paramCount,
    expectedParamCount);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::ThrowParamCountError(SQInteger minParamCount, SQInteger maxParamCount)
{
  SQInteger paramCount = GetParamCount();
  if (paramCount < minParamCount)
  {
    return ThrowError(
      _SC("too few parameters '%d' ; expected at least '%d'"),
      paramCount,
      minParamCount);
  }
  else
  {
    return ThrowError(
      _SC("too many parameters '%d' ; expected at most '%d'"),
      paramCount,
      maxParamCount);
  }
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::ThrowParamError(SQInteger index, const SQChar *expectedType)
{
  return ThrowError(
    _SC("parameter %d has an invalid type '%s' ; expected: '%s'"),
    index - 1,
    GetTypeName(index),
    expectedType);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::ThrowParamError(SQInteger index, SQObjectType expectedType)
{
  return ThrowError(
    _SC("parameter %d has an invalid type '%s' ; expected: '%s'"),
    index - 1,
    GetTypeName(index),
    RawTypeToTypeName(expectedType));
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::Return()
{ 
  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::Return(bool value)
{
  sq_pushbool(m_vm, (value ? SQTrue : SQFalse));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::Return(SQInteger value)
{
  sq_pushinteger(m_vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::Return(SQFloat value)
{
  sq_pushfloat(m_vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::Return(const SQChar *value, SQInteger length)
{
  sq_pushstring(m_vm, value, length);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::Return(SQUserPointer value)
{
  sq_pushuserpointer(m_vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::Return(HSQOBJECT value)
{
  sq_pushobject(m_vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline SQInteger StackHandler::Return(ClassType *value)
{
  return Push<ClassType>(m_vm, value);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline SQInteger StackHandler::Return(ClassType &value)
{
  return Push<ClassType>(m_vm, value);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline SQInteger StackHandler::Return(const ClassType *value)
{
  return Push<ClassType>(m_vm, value);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline SQInteger StackHandler::Return(const ClassType &value)
{
  return Push<ClassType>(m_vm, value);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
SQInteger StackHandler::Return(const ClassType *value, SQRELEASEHOOK hook)
{
  if (value != nullptr)
  {
    ClassTypeTag<ClassType> *typeinfo = ClassTypeTag<ClassType>::Get();
    HSQOBJECT classObject = typeinfo->GetClassObject(m_vm);
    if (CreateNativeClassInstance(m_vm, classObject, hook))
    {
      sq_setinstanceup(m_vm, -1, const_cast<ClassType *>(value));
      return 1;
    }
    if (hook != nullptr)
    {
      hook(const_cast<ClassType *>(value), sizeof(ClassType));
    }
    return ThrowError(_SC("error returning instance of type '%s'"), TypeInfo<ClassType>().m_typeName);
  }

  sq_pushnull(m_vm);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::SuspendVM()
{
  return sq_suspendvm(m_vm);
}

} // namespace sqb

// <--- back to sqbStackHandler.h

// <--- back to sqbReturnSpecialisation.h
// ---- #include "sqbind/sqbStackUtils.h"
// ---> including sqbStackUtils.h
// <--- back to sqbReturnSpecialisation.h
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// THIS FILE IS AUTO GENERATED DO NOT EDIT.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
namespace autogen
{
//----------------------------------------------------------------------------------------------------------------------
// ReturnSpecialisation<ReturnType>
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
class ReturnSpecialisation
{
public:
  static SQRESULT Call(ReturnType (*function)(), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType>
  static SQRESULT Call(InstanceType &instance, ReturnType (InstanceType::*function)(), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType>
  static SQRESULT Call(const InstanceType &instance, ReturnType (InstanceType::*function)() const, HSQUIRRELVM vm, SQInteger index);
  template<typename ParameterType0>
  static SQRESULT Call(ReturnType (*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0>
  static SQRESULT Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0>
  static SQRESULT Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0) const, HSQUIRRELVM vm, SQInteger index);
  template<typename ParameterType0, typename ParameterType1>
  static SQRESULT Call(ReturnType (*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1>
  static SQRESULT Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1>
  static SQRESULT Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1) const, HSQUIRRELVM vm, SQInteger index);
  template<typename ParameterType0, typename ParameterType1, typename ParameterType2>
  static SQRESULT Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
  static SQRESULT Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
  static SQRESULT Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2) const, HSQUIRRELVM vm, SQInteger index);
  template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
  static SQRESULT Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
  static SQRESULT Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
  static SQRESULT Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3) const, HSQUIRRELVM vm, SQInteger index);
  template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
  static SQRESULT Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
  static SQRESULT Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
  static SQRESULT Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4) const, HSQUIRRELVM vm, SQInteger index);
  template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
  static SQRESULT Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
  static SQRESULT Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
  static SQRESULT Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5) const, HSQUIRRELVM vm, SQInteger index);
  template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
  static SQRESULT Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
  static SQRESULT Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
  static SQRESULT Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6) const, HSQUIRRELVM vm, SQInteger index);
  template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
  static SQRESULT Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
  static SQRESULT Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
  static SQRESULT Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7) const, HSQUIRRELVM vm, SQInteger index);
  template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
  static SQRESULT Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
  static SQRESULT Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
  static SQRESULT Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8) const, HSQUIRRELVM vm, SQInteger index);
  template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
  static SQRESULT Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
  static SQRESULT Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index);
  template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
  static SQRESULT Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9) const, HSQUIRRELVM vm, SQInteger index);
};

} // namespace autogen

} // namespace sqb

// ---- #include "sqbind/autogen/sqbReturnSpecialisation.inl"
// ---> including sqbReturnSpecialisation.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the 'Software'), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// THIS FILE IS AUTO GENERATED DO NOT EDIT.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
namespace autogen
{
//----------------------------------------------------------------------------------------------------------------------
// ReturnSpecialisation<ReturnType>
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(), HSQUIRRELVM vm, SQInteger)
{
  ReturnType result = function();

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(), HSQUIRRELVM, SQInteger)
{
  function();

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(), HSQUIRRELVM vm, SQInteger)
{
  ReturnType result = (instance.*function)();

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(), HSQUIRRELVM, SQInteger)
{
  (instance.*function)();

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)() const, HSQUIRRELVM vm, SQInteger)
{
  ReturnType result = (instance.*function)();

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)() const, HSQUIRRELVM, SQInteger)
{
  (instance.*function)();

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType9>(), vm, index + 9))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 9, sqb::TypeInfo<ParameterType9>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8),
    sqb::Get(sqb::TypeWrapper<ParameterType9>(), vm, index + 9)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType9>(), vm, index + 9))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 9, sqb::TypeInfo<ParameterType9>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8),
    sqb::Get(sqb::TypeWrapper<ParameterType9>(), vm, index + 9)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType9>(), vm, index + 9))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 9, sqb::TypeInfo<ParameterType9>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8),
    sqb::Get(sqb::TypeWrapper<ParameterType9>(), vm, index + 9)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType9>(), vm, index + 9))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 9, sqb::TypeInfo<ParameterType9>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8),
    sqb::Get(sqb::TypeWrapper<ParameterType9>(), vm, index + 9)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType9>(), vm, index + 9))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 9, sqb::TypeInfo<ParameterType9>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8),
    sqb::Get(sqb::TypeWrapper<ParameterType9>(), vm, index + 9)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType9>(), vm, index + 9))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 9, sqb::TypeInfo<ParameterType9>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8),
    sqb::Get(sqb::TypeWrapper<ParameterType9>(), vm, index + 9)
    );

  return 0;
}

} // namespace autogen

} // namespace sqb

// <--- back to sqbReturnSpecialisation.h

// <--- back to sqbCall.h
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// THIS FILE IS AUTO GENERATED DO NOT EDIT.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
namespace autogen
{
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
inline static SQInteger Call(ReturnType (*function)(), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType>
inline static SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType>
inline static SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)() const, HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0>
inline static SQInteger Call(ReturnType (*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0>
inline static SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0>
inline static SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0) const, HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1>
inline static SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1>
inline static SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1>
inline static SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1) const, HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline static SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline static SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline static SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2) const, HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline static SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline static SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline static SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3) const, HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline static SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline static SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline static SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4) const, HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline static SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline static SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline static SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5) const, HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline static SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline static SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline static SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6) const, HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline static SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline static SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline static SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7) const, HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline static SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline static SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline static SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8) const, HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline static SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline static SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index);

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline static SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9) const, HSQUIRRELVM vm, SQInteger index);

} // namespace autogen

} // namespace sqb

// ---- #include "sqbind/autogen/sqbCall.inl"
// ---> including sqbCall.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the 'Software'), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// THIS FILE IS AUTO GENERATED DO NOT EDIT.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
namespace autogen
{
//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
inline SQInteger Call(ReturnType (*function)(), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)() const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0>
inline SQInteger Call(ReturnType (*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

} // namespace autogen

} // namespace sqb

// <--- back to sqbCall.h

// <--- back to sqbBind.h
// ---- #include <sqbind/autogen/sqbParamCheckHelper.h>
// ---> including sqbParamCheckHelper.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the 'Software'), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbind/sqbTypeInfo.h"
// ---> including sqbTypeInfo.h
// <--- back to sqbParamCheckHelper.h
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// THIS FILE IS AUTO GENERATED DO NOT EDIT.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
namespace autogen
{
//----------------------------------------------------------------------------------------------------------------------
// ParamCheckHelper
//----------------------------------------------------------------------------------------------------------------------
class ParamCheckHelper
{
public:
  template<typename ReturnType>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)());
  template<typename InstanceType, typename ReturnType>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)());
  template<typename InstanceType, typename ReturnType>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)() const);
  template<typename ReturnType, typename ParameterType0>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0));
  template<typename InstanceType, typename ReturnType, typename ParameterType0>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0));
  template<typename InstanceType, typename ReturnType, typename ParameterType0>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9) const);
};

} // namespace autogen

} // namespace sqb

// ---- #include "sqbind/autogen/sqbParamCheckHelper.inl"
// ---> including sqbParamCheckHelper.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the 'Software'), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// THIS FILE IS AUTO GENERATED DO NOT EDIT.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
namespace autogen
{
//----------------------------------------------------------------------------------------------------------------------
// ParamCheckHelper
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)())
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 1, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)())
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 1, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)() const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 1, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 2, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 2, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 2, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 3, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 3, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 3, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 4, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 4, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 4, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 5, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 5, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 5, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 6, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 6, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 6, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 7, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 7, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 7, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 8, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 8, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 8, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 9, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 9, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 9, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType8>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 10, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType8>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 10, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType8>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 10, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType8>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType9>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 11, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType8>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType9>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 11, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType8>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType9>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 11, typemask);
}

} // namespace autogen

} // namespace sqb

// <--- back to sqbParamCheckHelper.h

// <--- back to sqbBind.h
// ---- #include <sqbind/sqbClassHelpers.h>
// ---> including sqbClassHelpers.h
// <--- back to sqbBind.h
// ---- #include <sqbind/sqbClassTypeTag.h>
// ---> including sqbClassTypeTag.h
// <--- back to sqbBind.h
// ---- #include <sqbind/sqbFunctionOptions.h>
// ---> including sqbFunctionOptions.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbBaseHeader.h>
// ---> including sqbBaseHeader.h
// <--- back to sqbFunctionOptions.h
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief Defines whether a squirrel function is static or not. Only applies to functions within a class.
//----------------------------------------------------------------------------------------------------------------------
enum FunctionStaticType
{
  kNonStaticFunctionType = SQFalse, ///< Non-static function, this applies to all non class functions as they can never
                                    ///  be static.
  kStaticFunctionType = SQTrue,     ///< Static function, this only applies to some class functions.
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief Helper class to set all the optional parameters when binding a new function.
/// \code
/// sqb::Bind::BindFunction(
///   vm,
///   -1,
///   &func,
///   SC("func"),
///   sqb::FunctionOptions()
///     .ParamCheckCount(2)
///     .TypeMask(SC(".."))
///   );
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API FunctionOptions
{
public:
  /// \brief The number of free variables the new function has, these must be on the stack when the
  /// call to create function is made. The default value is 0.
  /// \note Free variables are bound the last in the stack first so the last on the stack when binding
  /// will be the first free variable on the stack when accessing them within the function.
  SQUnsignedInteger m_freeVariableCount;

  /// \brief This defines the parameter number check policy. 0 disables checking,
  /// greater than 0 means the number of parameters must exactly match, less
  /// than 0 means the function must be called with at least the absolute
  /// value number of parameters (ie. -3 would be at least 3 parameters
  /// required). The default value is 0.
  SQInteger m_paramCheckCount;

  /// \brief Parameter check type mask string. A null string means no checking.
  /// The default value is a null string.
  const SQChar *m_typeMaskString;

  /// \brief Is the function a static function, only applies to functions added to a
  /// a class object. The default value is kNonStaticFunctionType.
  FunctionStaticType m_staticType;

  FunctionOptions();

  FunctionOptions &FreeVariables(SQUnsignedInteger count);
  FunctionOptions &ParamCheckCount(SQInteger paramCheckCount);
  FunctionOptions &TypeMask(const SQChar *typeMask);
  FunctionOptions &Static(FunctionStaticType staticType);
};

}

// ---- #include <sqbind/sqbFunctionOptions.inl>
// ---> including sqbFunctionOptions.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
inline FunctionOptions::FunctionOptions()
: m_freeVariableCount(0),
  m_paramCheckCount(0),
  m_typeMaskString(nullptr),
  m_staticType(kNonStaticFunctionType)
{
}

//----------------------------------------------------------------------------------------------------------------------
inline FunctionOptions &FunctionOptions::FreeVariables(SQUnsignedInteger count)
{
  m_freeVariableCount = count;
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
inline FunctionOptions &FunctionOptions::ParamCheckCount(SQInteger paramCheckCount)
{
  m_paramCheckCount = paramCheckCount;
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
inline FunctionOptions &FunctionOptions::TypeMask(const SQChar *typeMaskString)
{
  m_typeMaskString = typeMaskString;
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
inline FunctionOptions &FunctionOptions::Static(FunctionStaticType staticType)
{
  m_staticType = staticType;
  return *this;
}

} // namespace sqb

// <--- back to sqbFunctionOptions.h

// <--- back to sqbBind.h
// ---- #include <sqbind/sqbTypeInfo.h>
// ---> including sqbTypeInfo.h
// <--- back to sqbBind.h
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief 
//---------------------------------------------------------------------------------------------------------------------
class SQBIND_API Bind
{
public:

  /// \defgroup Classes Binding classes
  /// Methods for binding classes to squirrel.
  /// @{

  /// \brief Bind a c++ class as a squirrel class.
  ///
  /// \note Binds sqb::TypeOf as "_typeof" metamethod.
  template<typename ClassType, typename BaseClassType>
  static bool BindClass(HSQUIRRELVM vm, SQInteger objectIndex, const SQChar *name);
  /// @}

  /// \defgroup Functions Binding functions
  /// Methods for binding functions to a squirrel table or class object.
  /// @{

  /// \brief Bind a global or static function to the class or table at objectIndex in the stack.
  ///
  /// A simple example of binding a function to the root table: \include BindFunction.cpp
  template<typename FunctionType>
  static bool BindFunction(
    HSQUIRRELVM       vm,
    SQInteger         objectIndex,
    FunctionType      function,
    const SQChar     *name,
    FunctionOptions   options = FunctionOptions());

  /// \brief Bind a global or static native function to the class or table at objectIndex in the stack.
  ///
  /// The function will assert if the object at objectIndex is not of type OT_TABLE or OT_CLASS or if name is
  /// null or zero length. If asserts are disabled then the results are undefined.
  /// A native function is of the form: \code SQInteger function(HSQUIRRELVM vm); \endcode
  ///
  /// A simple example of binding a native function to the root table: \include BindNativeFunction.cpp
  ///
  /// The options parameter can be used to specify the parameter check type mask and type count, if any
  /// free variables should be bound and if the object at idx is of type OT_CLASS whether the bound function
  /// is static.
  ///
  /// Free variables are bound the last in the stack first so the last on the stack when binding
  /// will be the first free variable on the stack when accessing them within the function.
  ///
  /// A more advanced example of binding a native function with a free variable to the root table: \include BindNativeFunctionWithFreeVariable.cpp
  ///
  /// The type mask and the param check count are passed directly to the squirrel api function sq_setparamscheck
  /// so refer to the squirrel documentation for more information on valid type masks and param check counts.
  ///
  /// Another advanced example of binding a native function with a type checking to the root table: \include BindNativeFunctionWithTypeCheck.cpp
  static bool BindNativeFunction(
    HSQUIRRELVM       vm,
    SQInteger         objectIndex,
    SQFUNCTION        function,
    const SQChar     *name,
    FunctionOptions   options = FunctionOptions());

  /// \brief Bind a class member function to the class at objectIndex in the stack.
  ///
  /// The function will assert if the object at objectIndex is not of type OT_CLASS or if name is
  /// null or zero length. If asserts are disabled then the results are undefined.
  ///
  /// The function will always be bound as non static as an instance is required for a successful call.
  ///
  /// A simple example of binding a function to a class: \include BindClassFunction.cpp
  template<typename ClassType, typename FunctionType>
  static bool BindClassFunction(
    HSQUIRRELVM   vm,
    SQInteger     objectIndex,
    FunctionType  function,
    const SQChar *name);

  /// \brief Bind a native class function to the class at objectIndex in the stack.
  ///
  /// The function will assert if the object at objectIndex is not of type OT_TABLE or if name is
  /// null or zero length. If asserts are disabled then the results are undefined.
  /// A native class function is of the form: \code class Class { SQInteger function(HSQUIRRELVM vm); }; \endcode
  ///
  /// A simple example of binding a native class function to a class: \include BindNativeClassFunction.cpp
  template<typename ClassType>
  static bool BindNativeClassFunction(
    HSQUIRRELVM       vm,
    SQInteger         objectIndex,
    SQInteger         (ClassType:: *function)(HSQUIRRELVM),
    const SQChar     *name,
    FunctionOptions   options = FunctionOptions());

  /// \brief Bind a specific instance class member function to the class or table at objectIndex in the stack.
  ///
  /// The call will fail if the object at objectIndex is not of type OT_CLASS or OT_TABLE, if name is
  /// null or zero length or if instance is null.
  ///
  /// The function will always be bound as a static function.
  ///
  /// A simple example of binding a function to the root table: \include BindSingletonFunction.cpp
  template<typename ClassType, typename FunctionType>
  static bool BindSingletonFunction(
    HSQUIRRELVM   vm,
    SQInteger     objectIndex,
    ClassType    *instance,
    FunctionType  function,
    const SQChar *name);

  /// \brief Bind a specific instance native class function to the class or table at objectIndex in the stack.
  ///
  /// The function will assert if the object at objectIndex is not of type OT_TABLE or OT_CLASS, if name is
  /// null or zero length or if instance is null. If asserts are disabled then the results are undefined.
  /// A native singleton function is of the same form as a native class function, the only difference is that this
  /// function binds to a specific class instance:
  /// \code class Singleton { SQInteger function(HSQUIRRELVM vm); }; \endcode
  ///
  /// A simple example of binding a native class function to a class: \include BindNativeSingletonFunction.cpp
  template<typename ClassType>
  static bool BindNativeSingletonFunction(
    HSQUIRRELVM       vm,
    SQInteger         objectIndex,
    ClassType        *instance,
    SQInteger         (ClassType:: *function)(HSQUIRRELVM),
    const SQChar     *name,
    FunctionOptions   options = FunctionOptions());
  /// @}

  /// \defgroup Variables Binding variables
  /// Methods for binding variables to a squirrel table or class object.
  /// @{

  /// \brief Bind a global or static member variable to the object at idx in the stack.
  template<typename VariableType>
  static bool BindVariable(
    HSQUIRRELVM         vm,
    SQInteger           idx,
    VariableType       *variable,
    const SQChar       *name);

  /// \brief Register a class instance member variable to a class.
  template<typename InstanceType, typename VariableType>
  static bool BindInstanceVariable(
    HSQUIRRELVM                   vm,
    SQInteger                     idx,
    VariableType InstanceType::  *variable,
    const SQChar                 *name);
  /// @}

private:

  /// \brief This enum contains the keys for every element contained within the variable reference table.
  ///
  /// Each bound variable has a variable reference table within the vm registry table that contains all the
  /// information about the variable required to set and get it via squirrel.
  enum VariableReferenceTableKeys
  {
    kScriptVarTypeKey = 0,     ///< The script type of the bound variable, can be any of ScriptVarType.
    kOffsetOrAddressKey,       ///< The address of the variable or the offset of the variable from its owning
                               ///  class instance.
    kInstanceClassTypeKey,     ///< The type of the bound variables owning instance if any.
    kVariableClassTypeKey,     ///< The class type of the bound variable if its ScriptVarType is of type
                               ///  kScriptVarTypeInstance.
    kFlagsKey,                 ///< The additional VariableFlags set when the variable was bound. Can be any
                               ///  combination of VariableFlags.
    kStringReferencesTableKey, ///< The string references table holds a strong reference to bound string variables
                               ///  so if they have been set via squirrel but all other references to the string have
                               ///  been destroyed, the string is not cleared until the bound variable is no longer
                               ///  referencing the string also.
  };

  enum VariableFlags
  {
    kVariableNoFlags  = 0,      ///< A default bound variable.
    kVariableStatic   = 1 << 0, ///< The variable is static, only used when binding to a class object.
  };

  /// \brief The number of variables expected when calling the _get metamethod.
  static const SQInteger kGetMetaMethodParamCheckCount;
  /// \brief The number of variables expected when calling the _set metamethod.
  static const SQInteger kSetMetaMethodParamCheckCount;

  /// \brief The typemask of variables expected when calling the _get metamethod.
  static const SQChar *kGetMetaMethodTypeMask;
  /// \brief The typemask of variables expected when calling the _set metamethod.
  static const SQChar *kSetMetaMethodTypeMask;

  /// \brief The index of the owning object in the stack when calling the _set or _get metamethod.
  static const SQInteger kThisObjectStackIndex;

  /// \brief The index of the variable name in the stack when calling _set or _get metamethods.
  static const SQInteger kNameStackIndex;

  /// \brief The index of the object references table in the stack when calling the _get metamethod.
  static const SQInteger kGetObjectReferencesStackIndex;

  /// \brief The index of the new object value in the stack when calling the _set metamethod.
  static const SQInteger kSetValueStackIndex;
  /// \brief The index of the object references table in the stack when calling the _set metamethod.
  static const SQInteger kSetObjectReferencesStackIndex;

  /// \brief Helper class, provides specialisation when BaseClassType is NoBaseClass.
  template<typename BaseClassType>
  class SetBaseClass
  {
  public:
    template<typename ClassType>
    static bool ForClassTypeTag(sqb::ClassTypeTag<ClassType> *classType);
  };

  /// \brief
  template<typename BaseClassType>
  static bool PushBaseClassType(HSQUIRRELVM vm);

  /// \brief
  template<typename InstanceType>
  static void GetInstanceFromStack(HSQUIRRELVM vm, SQInteger idx, InstanceType **instance);

  /// \brief Used to dispatch a native squirrel call to a call to a global or static c++ function call.
  template<typename FunctionType>
  static SQInteger DispatchFunctionCall(HSQUIRRELVM vm);

  /// \brief
  template<typename ClassType, typename FunctionType>
  static SQInteger DispatchClassFunctionCall(HSQUIRRELVM vm);

  /// \brief
  template<typename ClassType>
  static SQInteger DispatchNativeClassFunctionCall(HSQUIRRELVM vm);

  /// \brief
  template<typename ClassType, typename FunctionType>
  static SQInteger DispatchSingletonFunctionCall(HSQUIRRELVM vm);

  /// \brief
  template<typename InstanceType>
  static SQInteger DispatchNativeSingletonFunctionCall(HSQUIRRELVM vm);

  /// \brief Gets the object references table for an object at objectIndex in vm's stack. objectType
  /// should be of type OT_TABLE or OT_CLASS. If the object references table does not exist it is created.
  ///
  /// The object references table is stored per table/class object and holds all the information
  /// about every bound variable type. Each bound variable will have a variable reference table in the
  /// object references table.
  /// \note A derived class' object references table will have its base class' object references table as its
  /// delegate. This ensures that getting the variable reference table for a base member from the derived class
  /// will still succeed.
  static void GetOrCreateObjectReferencesTable(HSQUIRRELVM vm, SQInteger objectIndex, SQObjectType objectType);
  /// \brief Gets the delegate of a table or userdata creating it if necessary.
  /// \note Assumes the object at idx is a table or userdata and that idx is an absolute index.
  static void GetOrCreateObjectDelegate(HSQUIRRELVM vm, SQInteger objectIndex);

  /// \brief Fills in a table at variableReferenceIndex in vm's stack with all the information needed to bind
  /// a variable.
  static bool CreateVariableReference(
    HSQUIRRELVM     vm,
    SQInteger       variableReferenceIndex,
    ScriptVarType   variableType,
    SQUserPointer   offsetOrAddress,
    ClassTypeTagBase  *instanceClassType,
    ClassTypeTagBase  *variableClassType,
    SQInteger       bindFlags);

  /// \brief Makes sure that the required _get metamethod is bound for the object at objectIndex in vm's stack.
  static void EnsureGetMetaMethodBound(
    HSQUIRRELVM   vm,
    SQInteger     objectIndex,
    SQObjectType  objectType,
    SQInteger     objectReferencesIndex);
  /// \brief Makes sure that the required _set metamethod is bound for the object at objectIndex in vm's stack.
  static void EnsureSetMetaMethodBound(
    HSQUIRRELVM   vm,
    SQInteger     objectIndex,
    SQObjectType  objectType,
    SQInteger     objectReferencesIndex);

  /// \brief Retrieves the type and absolute address of a bound variable using the variable reference table at
  /// variableReferenceIndex in vm's stack.
  /// \note This should only be used for global variables bound to tables.
  static void GetVariableReferenceTypeAndAddress(
    HSQUIRRELVM     vm,
    SQInteger       variableReferenceIndex,
    SQInteger      *variableType,
    SQUserPointer  *address);

  /// \brief Gets the class type of a bound variable using the variable reference table at variableReferenceIndex
  /// in vm's stack.
  static void GetVariableClassType(
    HSQUIRRELVM           vm,
    SQInteger             variableReferenceIndex,
    const ClassTypeTagBase **variableClassType);

  static void GetVariableStringReferencesTable(
    HSQUIRRELVM vm,
    SQInteger   variableReferenceIndex);

  /// \brief The _get metamethod when binding variables to tables or userdata.
  static SQInteger GetVariableReference(HSQUIRRELVM vm);
  /// \brief The _set metamethod when binding variables to tables or userdata.
  static SQInteger SetVariableReference(HSQUIRRELVM vm);

  /// \brief Retrieves the type and offset or address of a bound variable using the variable reference table at
  /// variableReferenceIndex in vm's stack. If the variable is non-static and the owning object is a class
  /// instance then the offset in the variable reference table will be combined with the address of the instance
  /// user pointer to get the absolute address of the value being set/got.
  static void GetInstanceVariableReferenceTypeAndAddress(
    HSQUIRRELVM     vm,
    SQInteger       variableReferenceIndex,
    SQInteger      *variableType,
    SQUserPointer  *address);

  /// \brief The _get metamethod when binding variables to classes.
  static SQInteger GetInstanceVariableReference(HSQUIRRELVM vm);
  /// \brief The _set metamethod when binding variables to classes.
  static SQInteger SetInstanceVariableReference(HSQUIRRELVM vm);

  /// \brief Gets the value of the bound variable at address pushing it in the stack.
  /// \note The return value must be the value returned by the bound native _get metamethod function.
  static SQInteger GetVariable(
    HSQUIRRELVM   vm,
    SQInteger     variableReferenceIndex,
    SQInteger     variableType,
    SQUserPointer address);

  /// \brief Sets the value of the bound variable at address.
  /// \note The return value must be the value returned by the bound native _set metamethod function.
  static SQInteger SetVariable(
    HSQUIRRELVM   vm,
    SQInteger     variableReferenceIndex,
    SQInteger     variableType,
    SQUserPointer address);
};

} // namespace sqb

// ---- #include <sqbind/sqbBind.inl>
// ---> including sqbBind.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// Bind
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
bool Bind::BindClass(HSQUIRRELVM vm, SQInteger objectIndex, const SQChar *name)
{
  SQObjectType objectType = sq_gettype(vm, objectIndex);
  if (objectType != OT_TABLE && objectType != OT_CLASS)
  {
    return false;
  }

  if (name == nullptr)
  {
    return false;
  }

  size_t nameLength = scstrlen(name);
  if (nameLength == 0)
  {
    return false;
  }

  // if the index was relative to the top convert to an absolute index before calls alter the stack.
  //
  if (objectIndex < 0)
  {
    SQInteger top = sq_gettop(vm);
    objectIndex = top + objectIndex + 1;
  }

  sqb::ClassTypeTag<ClassType> *classTypeTag = sqb::ClassTypeTag<ClassType>::Get();

  // sqb::ClassTypeTag::Get will return null for sqb::NoBaseClass, make sure it cannot be bound
  //
  if (classTypeTag == nullptr)
  {
    return false;
  }

  // push this read for binding the class in to a named slot in object
  //
  sq_pushstring(vm, name, nameLength);

  // create a new class and setup up the base class if there was one
  //
  if (SetBaseClass<BaseClassType>::ForClassTypeTag(classTypeTag))
  {
    if (!PushBaseClassType<BaseClassType>(vm))
    {
      sq_poptop(vm);
      return false;
    }

    SQRESULT result = sq_newclass(vm, SQTrue);
    SQBIND_ASSERT_SUCCEEDED(result);
  }
  else
  {
    SQRESULT result = sq_newclass(vm, SQFalse);
    SQBIND_ASSERT_SUCCEEDED(result);
  }

  // set the ClassType instance as the type tag for the new class
  //
  {
    SQRESULT result = sq_settypetag(vm, -1, classTypeTag);
    SQBIND_ASSERT_SUCCEEDED(result);
  }

  // ensure the class object can be retrieve using ClassType at any point
  //
  HSQOBJECT classObject;
  {
    SQRESULT result = sq_getstackobj(vm, -1, &classObject);
    SQBIND_ASSERT_SUCCEEDED(result);
  }

  classTypeTag->SetClassObject(vm, classObject);

  // setup _typeof metamethod
  //
  FunctionOptions options;
  options.ParamCheckCount(1);
  options.TypeMask(_SC("x"));
  {
    bool result = BindNativeFunction(vm, -1, &TypeOf<ClassType>, _SC("_typeof"), options);
    SQBIND_ASSERT(result);
  }

  // add the new class as a named slot in object
  //
  {
    SQRESULT result = sq_newslot(vm, objectIndex, SQTrue);
    SQBIND_ASSERT_SUCCEEDED(result);
  }

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename FunctionType>
bool Bind::BindFunction(
  HSQUIRRELVM       vm,
  SQInteger         objectIndex,
  FunctionType      function,
  const SQChar     *name,
  FunctionOptions   options)
{
  SQObjectType objectType = sq_gettype(vm, objectIndex);
  if (objectType != OT_CLASS && objectType != OT_TABLE)
  {
    return false;
  }

  if (name == nullptr)
  {
    return false;
  }

  size_t nameLength = scstrlen(name);
  if (nameLength == 0)
  {
    return false;
  }

  // if the index was relative to the top convert to an absolute index before calls alter the stack.
  //
  if (objectIndex < 0)
  {
    SQInteger top = sq_gettop(vm);
    objectIndex = top + objectIndex + 1;
  }

  // create a new squirrel closure using the templated dispatch function with the actual function
  // as a free variable
  //
  sq_pushuserpointer(vm, reinterpret_cast<SQUserPointer*>(function));
  sq_newclosure(vm, &DispatchFunctionCall<FunctionType>, 1);

  // set the param check count and typemask for the new function
  //
  SQRESULT result = autogen::ParamCheckHelper::SetParamsCheck(vm, function);
  SQBIND_ASSERT_SUCCEEDED_MSG(result, "check all parameter types have been bound with SQBIND_DECLARE_TYPEINFO macro.");

  // set the name used when debugging
  //
  result = sq_setnativeclosurename(vm, -1, name);
  SQBIND_ASSERT_SUCCEEDED(result);

  // create a named slot for the new function in the owning object
  //
  sq_pushstring(vm, name, nameLength);
  sq_push(vm, -2);
  result = sq_newslot(vm, objectIndex, options.m_staticType);
  SQBIND_ASSERT_SUCCEEDED(result);

  // remove the closure from the stack, the pushed copy was removed by sq_newslot.
  //
  sq_poptop(vm);
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename FunctionType>
inline bool Bind::BindClassFunction(
  HSQUIRRELVM   vm,
  SQInteger     objectIndex,
  FunctionType  function,
  const SQChar *name)
{
  if (sq_gettype(vm, objectIndex) != OT_CLASS)
  {
    return false;
  }

  if (name == nullptr)
  {
    return false;
  }

  size_t nameLength = scstrlen(name);
  if (nameLength == 0)
  {
    return false;
  }

  // if the index was relative to the top convert to an absolute index before calls alter the stack.
  //
  if (objectIndex < 0)
  {
    SQInteger top = sq_gettop(vm);
    objectIndex = top + objectIndex + 1;
  }

  // put the name on the stack first ready for creating the slot later
  //
  sq_pushstring(vm, name, nameLength);

  // push the the function pointer as a free variable to be used by the dispatch function.
  // note: has to be done as userdata not a userpointer as member functions can sometimes
  //       be bigger than sizeof(void*).
  //
  FunctionType* pointer = (FunctionType*)sq_newuserdata(vm, sizeof(FunctionType));
  *pointer = function;

  sq_newclosure(vm, &DispatchClassFunctionCall<ClassType, FunctionType>, 1);

  // set the param check count and typemask for the new function
  //
  SQRESULT result = autogen::ParamCheckHelper::SetParamsCheck(vm, function);
  SQBIND_ASSERT_SUCCEEDED_MSG(result, "check all parameter types have been bound with SQBIND_DECLARE_TYPEINFO macro.");

  // set the name used when debugging
  //
  result = sq_setnativeclosurename(vm, -1, name);
  SQBIND_ASSERT_SUCCEEDED(result);

  // create a named slot for the new function in the owning object
  //
  result = sq_newslot(vm, objectIndex, SQFalse);
  SQBIND_ASSERT_SUCCEEDED(result);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline bool Bind::BindNativeClassFunction(
  HSQUIRRELVM       vm,
  SQInteger         objectIndex,
  SQInteger         (ClassType:: *function)(HSQUIRRELVM),
  const SQChar     *name,
  FunctionOptions   options)
{
  typedef SQInteger (ClassType:: *FunctionType)(HSQUIRRELVM);

  if (sq_gettype(vm, objectIndex) != OT_CLASS)
  {
    return false;
  }

  if (name == nullptr)
  {
    return false;
  }

  size_t nameLength = scstrlen(name);
  if (nameLength == 0)
  {
    return false;
  }

  // if the index was relative to the top convert to an absolute index before calls alter the stack.
  //
  if (objectIndex < 0)
  {
    SQInteger top = sq_gettop(vm);
    objectIndex = top + objectIndex + 1;
  }

  // push the the function pointer as a free variable to be used by the dispatch function.
  // note: has to be done as userdata not a userpointer as member functions can sometimes
  //       be bigger than sizeof(void*).
  //
  FunctionType* pointer = (FunctionType*)sq_newuserdata(vm, sizeof(FunctionType));
  *pointer = function;

  sq_newclosure(vm, &DispatchNativeClassFunctionCall<ClassType>, options.m_freeVariableCount + 1);

  if (options.m_paramCheckCount != 0 && options.m_typeMaskString != nullptr)
  {
    if (SQ_FAILED(sq_setparamscheck(vm, options.m_paramCheckCount, options.m_typeMaskString)))
    {
      sq_poptop(vm);
      return false;
    }
  }

  // set the name used when debugging
  //
  SQRESULT result = sq_setnativeclosurename(vm, -1, name);
  SQBIND_ASSERT_SUCCEEDED(result);

  // create a named slot for the new function in the owning object
  //
  sq_pushstring(vm, name, nameLength);
  sq_push(vm, -2);
  result = sq_newslot(vm, objectIndex, SQFalse);
  SQBIND_ASSERT_SUCCEEDED(result);

  // remove the first closure from the stack, the pushed copy was removed by sq_newslot.
  //
  sq_poptop(vm);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename FunctionType>
inline bool Bind::BindSingletonFunction(
  HSQUIRRELVM   vm,
  SQInteger     objectIndex,
  ClassType    *instance,
  FunctionType  function,
  const SQChar *name)
{
  SQObjectType objectType = sq_gettype(vm, objectIndex);
  if (objectType != OT_CLASS && objectType != OT_TABLE)
  {
    return false;
  }

  if (name == nullptr)
  {
    return false;
  }

  size_t nameLength = scstrlen(name);
  if (nameLength == 0)
  {
    return false;
  }

  if (instance == nullptr)
  {
    return false;
  }

  // if the index was relative to the top convert to an absolute index before calls alter the stack.
  //
  if (objectIndex < 0)
  {
    SQInteger top = sq_gettop(vm);
    objectIndex = top + objectIndex + 1;
  }

  // put the name on the stack first ready for creating the slot later
  //
  sq_pushstring(vm, name, nameLength);

  // push the class instance and the function pointer as free variables to be used by the dispatch function.
  // note: function has to be done as userdata not a userpointer as member functions can sometimes
  //       be bigger than sizeof(void*).
  //
  FunctionType* pointer = (FunctionType*)sq_newuserdata(vm, sizeof(FunctionType));
  *pointer = function;
  sq_pushuserpointer(vm, reinterpret_cast<SQUserPointer*>(instance));

  sq_newclosure(vm, &DispatchSingletonFunctionCall<ClassType, FunctionType>, 2);

  // set the param check count and typemask for the new function
  //
  SQRESULT result = autogen::ParamCheckHelper::SetParamsCheck(vm, function);
  SQBIND_ASSERT_SUCCEEDED_MSG(result, "check all parameter types have been bound with SQBIND_DECLARE_TYPEINFO macro.");

  // set the name used when debugging
  //
  result = sq_setnativeclosurename(vm, -1, name);
  SQBIND_ASSERT_SUCCEEDED(result);

  // create a named slot for the new function in the owning object
  //
  result = sq_newslot(vm, objectIndex, SQTrue);
  SQBIND_ASSERT_SUCCEEDED(result);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline bool Bind::BindNativeSingletonFunction(
  HSQUIRRELVM       vm,
  SQInteger         objectIndex,
  ClassType        *instance,
  SQInteger         (ClassType:: *function)(HSQUIRRELVM),
  const SQChar     *name,
  FunctionOptions   options)
{
  typedef SQInteger (ClassType:: *FunctionType)(HSQUIRRELVM);

  SQObjectType objectType = sq_gettype(vm, objectIndex);
  if (objectType != OT_CLASS && objectType != OT_TABLE)
  {
    return false;
  }

  if (name == nullptr)
  {
    return false;
  }

  size_t nameLength = scstrlen(name);
  if (nameLength == 0)
  {
    return false;
  }

  if (instance == nullptr)
  {
    return false;
  }

  // if the index was relative to the top convert to an absolute index before calls alter the stack.
  //
  if (objectIndex < 0)
  {
    SQInteger top = sq_gettop(vm);
    objectIndex = top + objectIndex + 1;
  }

  // push the class instance and the function pointer as free variables to be used by the dispatch function.
  // note: function has to be done as userdata not a userpointer as member functions can sometimes
  //       be bigger than sizeof(void*).
  //
  FunctionType* pointer = (FunctionType*)sq_newuserdata(vm, sizeof(FunctionType));
  *pointer = function;
  sq_pushuserpointer(vm, *reinterpret_cast<SQUserPointer*>(&instance));

  sq_newclosure(vm, &DispatchNativeSingletonFunctionCall<ClassType>, options.m_freeVariableCount + 2);

  if (options.m_paramCheckCount != 0 && options.m_typeMaskString != nullptr)
  {
    if (SQ_FAILED(sq_setparamscheck(vm, options.m_paramCheckCount, options.m_typeMaskString)))
    {
      sq_poptop(vm);
      return false;
    }
  }

  // set the name used when debugging
  //
  SQRESULT result = sq_setnativeclosurename(vm, -1, name);
  SQBIND_ASSERT_SUCCEEDED(result);

  // create a named slot for the new function in the owning object
  //
  sq_pushstring(vm, name, nameLength);
  sq_push(vm, -2);
  result = sq_newslot(vm, objectIndex, SQFalse);
  SQBIND_ASSERT_SUCCEEDED(result);

  // remove the first closure from the stack, the pushed copy was removed by sq_newslot.
  //
  sq_poptop(vm);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename VariableType>
inline bool Bind::BindVariable(
  HSQUIRRELVM   vm,
  SQInteger     objectIndex,
  VariableType *variable,
  const SQChar *name)
{
  SQObjectType objectType = sq_gettype(vm, objectIndex);
  if (objectType != OT_CLASS && objectType != OT_TABLE)
  {
    return false;
  }

  if (variable == nullptr)
  {
    return false;
  }

  if (name == nullptr)
  {
    return false;
  }

  size_t nameLength = scstrlen(name);
  if (nameLength == 0)
  {
    return false;
  }

  SQInteger top = sq_gettop(vm);

  // if the index was relative to the top convert to an absolute index before calls alter the stack.
  //
  if (objectIndex < 0)
  {
    objectIndex = top + objectIndex + 1;
  }

  GetOrCreateObjectReferencesTable(vm, objectIndex, objectType);
  SQBIND_ASSERT(sq_gettype(vm, -1) == OT_TABLE);

  // now create the variable reference in the object references table.
  //
  sq_newtable(vm);

  sq_pushstring(vm, name, -1);
  sq_push(vm, -2);
  sq_rawset(vm, -4);

  ScriptVarType variableType = static_cast<ScriptVarType>(TypeInfo<VariableType>::kTypeID);
  ClassTypeTag<VariableType>* variableClassTypeTag = ClassTypeTag<VariableType>::Get();
  SQInteger flags = ((objectType == OT_CLASS) ? kVariableStatic : kVariableNoFlags);
  bool result = CreateVariableReference(
    vm,
    top + 2,
    variableType,
    reinterpret_cast<SQUserPointer>(variable),
    nullptr,
    variableClassTypeTag,
    flags);

  if (!result)
  {
    sq_pop(vm, 2);
    return false;
  }

  SQInteger referencesTableIndex = top + 1;

  EnsureGetMetaMethodBound(vm, objectIndex, objectType, referencesTableIndex);
  EnsureSetMetaMethodBound(vm, objectIndex, objectType, referencesTableIndex);

  // pop the registry table, the object references table and the variable references.
  //
  sq_pop(vm, 2);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename VariableType>
inline bool Bind::BindInstanceVariable(
  HSQUIRRELVM                   vm,
  SQInteger                     objectIndex,
  VariableType InstanceType::  *variable,
  const SQChar                 *name)
{
  SQObjectType objectType = sq_gettype(vm, objectIndex);
  if (objectType != OT_CLASS)
  {
    return false;
  }

  if (variable == nullptr)
  {
    return false;
  }

  if (name == nullptr)
  {
    return false;
  }

  size_t nameLength = scstrlen(name);
  if (nameLength == 0)
  {
    return false;
  }

  SQInteger top = sq_gettop(vm);

  // if the index was relative to the top convert to an absolute index before calls alter the stack.
  //
  if (objectIndex < 0)
  {
    objectIndex = top + objectIndex + 1;
  }

  GetOrCreateObjectReferencesTable(vm, objectIndex, objectType);
  SQBIND_ASSERT(sq_gettype(vm, -1) == OT_TABLE);

  // now create the variable reference in the object references table.
  //
  sq_newtable(vm);

  sq_pushstring(vm, name, -1);
  sq_push(vm, -2);
  sq_rawset(vm, -4);

  // c++ won't let you cast from a member variable pointer to a void * so this struct is used to help
  // cast it. By casting the struct to a void ** and then dereferencing back to void * the variable pointer
  // is effectively cast to a void *. This uses the fact that the CastHelper::variable is the first and
  // only member of the struct so a pointer to the helper will also point to helper::variable.
  //
  struct CastHelper
  {
    VariableType InstanceType:: *variable;
  };
  CastHelper helper;
  helper.variable = variable;
  SQUserPointer offset = *reinterpret_cast<void**>(&helper);

#if defined(_SQ64)
  // 64-bit member variable offsets have the higher 32 bits uninitialised so mask that away
  // ie 0xcccccccc00000000 -> 0x0000000000000000
  //
  offset = reinterpret_cast<SQUserPointer>(reinterpret_cast<ptrdiff_t>(offset) & 0xffffffff);
#endif

  ClassTypeTag<InstanceType>* instanceClassTypeTag = ClassTypeTag<InstanceType>::Get();
  ClassTypeTag<VariableType>* variableClassTypeTag = ClassTypeTag<VariableType>::Get();
  bool result = CreateVariableReference(
    vm,
    top + 2,
    static_cast<ScriptVarType>(TypeInfo<VariableType>::kTypeID),
    offset,
    instanceClassTypeTag,
    variableClassTypeTag,
    kVariableNoFlags);

  if (!result)
  {
    sq_pop(vm, 2);
    return false;
  }

  SQInteger referencesTableIndex = top + 1;

  EnsureGetMetaMethodBound(vm, objectIndex, objectType, referencesTableIndex);
  EnsureSetMetaMethodBound(vm, objectIndex, objectType, referencesTableIndex);

  // pop the registry table, the object references table and the variable references.
  //
  sq_pop(vm, 2);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename BaseClassType>
template<typename ClassType>
bool Bind::SetBaseClass<BaseClassType>::ForClassTypeTag(sqb::ClassTypeTag<ClassType> *classType)
{
  classType->SetBaseClass(static_cast<BaseClassType *>(nullptr));

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ClassType>
bool Bind::SetBaseClass<NoBaseClass>::ForClassTypeTag(sqb::ClassTypeTag<ClassType> *SQBIND_UNUSED(classType))
{
  return false;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename BaseClassType>
inline bool Bind::PushBaseClassType(HSQUIRRELVM vm)
{
  sqb::ClassTypeTag<BaseClassType> *baseClassTypeTag = sqb::ClassTypeTag<BaseClassType>::Get();

  HSQOBJECT baseClassObject = baseClassTypeTag->GetClassObject(vm);
  if (sq_type(baseClassObject) == OT_CLASS)
  {
    sq_pushobject(vm, baseClassObject);
    return true;
  }

  return false;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType>
void Bind::GetInstanceFromStack(HSQUIRRELVM vm, SQInteger objectIndex, InstanceType **instance)
{
  // get the instance which will be the first parameter in the stack
  //
  SQUserPointer pointer;
  SQRESULT result = sq_getinstanceup(vm, objectIndex, &pointer, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(pointer != nullptr);

  // if the instance bound is not of type InstanceType then the pointer may need to be offset
  //
  ClassTypeTagBase *actualTypeTag;
  // this call cannot fail if sq_getinstanceup passed
  //
  sq_gettypetag(vm, objectIndex, reinterpret_cast<SQUserPointer *>(&actualTypeTag));
  SQBIND_ASSERT(actualTypeTag != nullptr);
  SQBIND_ASSERT(actualTypeTag->IsValid());

  // adjust the pointer offset if necessary
  //
  ClassTypeTagBase *expectedTypeTag = ClassTypeTag<InstanceType>::Get();
  if (actualTypeTag != expectedTypeTag && actualTypeTag->MayHaveOffset())
  {
    // instance type is more derived than callee and there may be an offset, adjust pointer
    ptrdiff_t offset = actualTypeTag->GetOffsetTo(expectedTypeTag);
    pointer = static_cast<uint8_t *>(pointer) - offset;
  }

  *instance = static_cast<InstanceType *>(pointer);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename FuncType>
inline SQInteger Bind::DispatchFunctionCall(HSQUIRRELVM vm)
{
  SQInteger count = sq_gettop(vm);

  SQBIND_ASSERT(count >= 1);

  FuncType function;
  SQRESULT result = sq_getuserpointer(vm, count, reinterpret_cast<SQUserPointer *>(&function));
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(function != nullptr);

  return autogen::Call(function, vm, 2);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename FunctionType>
inline SQInteger Bind::DispatchClassFunctionCall(HSQUIRRELVM vm)
{
  // count is also the index of the last free variable of the function
  //
  SQInteger count = sq_gettop(vm);
  SQBIND_ASSERT(count >= 2);

  // get the instance which will be the first parameter in the stack
  //
  InstanceType *instance;
  GetInstanceFromStack(vm, 1, &instance);

  // get the function which is the last free variable on the stack
  //
  SQUserPointer pointer = nullptr;
  SQRESULT result = sq_getuserdata(vm, count, &pointer, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(pointer != nullptr);

  FunctionType function = *((FunctionType*)pointer);
  return autogen::Call(*instance, function, vm, 2);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType>
inline SQInteger Bind::DispatchNativeClassFunctionCall(HSQUIRRELVM vm)
{
  typedef SQInteger (InstanceType:: *FunctionType)(HSQUIRRELVM);
  // count is also the index of the last free variable of the function
  //
  SQInteger count = sq_gettop(vm);
  SQBIND_ASSERT(count >= 2);

  // get the instance which will be the first parameter in the stack
  //
  InstanceType *instance;
  GetInstanceFromStack(vm, 1, &instance);

  // get the function which is the last free variable on the stack
  //
  SQUserPointer pointer = nullptr;
  SQRESULT result = sq_getuserdata(vm, count, &pointer, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(pointer != nullptr);

  FunctionType function = *((FunctionType*)pointer);
  return (instance->*(function))(vm);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename FunctionType>
inline SQInteger Bind::DispatchSingletonFunctionCall(HSQUIRRELVM vm)
{
  SQInteger count = sq_gettop(vm);

  SQBIND_ASSERT(count >= 2);

  // get the instance which will be the second to last free variable on the stack
  //
  InstanceType *instance = nullptr;
  SQRESULT result = sq_getuserpointer(vm, count - 1, reinterpret_cast<SQUserPointer *>(&instance));
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(instance != nullptr);

  // get the function which is the last free variable on the stack
  //
  SQUserPointer pointer = nullptr;
  result = sq_getuserdata(vm, count, &pointer, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(pointer != nullptr);

  FunctionType function = *((FunctionType*)pointer);
  return autogen::Call(*instance, function, vm, 2);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType>
inline SQInteger Bind::DispatchNativeSingletonFunctionCall(HSQUIRRELVM vm)
{
  typedef SQInteger (InstanceType:: *FunctionType)(HSQUIRRELVM);
  SQInteger count = sq_gettop(vm);

  SQBIND_ASSERT(count >= 2);

  // get the instance which will be the second to last free variable on the stack
  //
  InstanceType *instance = nullptr;
  SQRESULT result = sq_getuserpointer(vm, count - 1, reinterpret_cast<SQUserPointer *>(&instance));
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(instance != nullptr);

  // get the function which is the last free variable on the stack
  //
  SQUserPointer pointer = nullptr;
  result = sq_getuserdata(vm, count, &pointer, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(pointer != nullptr);

  FunctionType function = *((FunctionType*)pointer);
  return (instance->*(function))(vm);
}

} // namespace sqb

// <--- back to sqbBind.h

#endif

// <--- back to SquirrelBind.h
// ---- #include <sqbind/sqbBindMacros.h>
// ---> including sqbBindMacros.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the 'Software'), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbClassHelpers.h>
// ---> including sqbClassHelpers.h
// <--- back to sqbBindMacros.h
// ---- #include <sqbind/sqbClassTypeTag.h>
// ---> including sqbClassTypeTag.h
// <--- back to sqbBindMacros.h
// ---- #include <sqbind/sqbStackHandler.h>
// ---> including sqbStackHandler.h
// <--- back to sqbBindMacros.h
// ---- #include <sqbind/sqbStackUtils.h>
// ---> including sqbStackUtils.h
// <--- back to sqbBindMacros.h
// ---- #include <sqbind/sqbTypeInfo.h>
// ---> including sqbTypeInfo.h
// <--- back to sqbBindMacros.h
//----------------------------------------------------------------------------------------------------------------------

/*lint -emacro(19,SQBIND_DECLARE_TYPEINFO)*/
/*lint -emacro(1576,SQBIND_DECLARE_TYPEINFO)*/
/*lint -emacro(1577,SQBIND_DECLARE_TYPEINFO)*/

/*lint -emacro(19,SQBIND_DECLARE_CLASS_BASE)*/
/*lint -emacro(1576,SQBIND_DECLARE_CLASS_BASE)*/
/*lint -emacro(1577,SQBIND_DECLARE_CLASS_BASE)*/

/*lint -emacro(19,SQBIND_DECLARE_CLASS_NAME)*/
/*lint -emacro(1576,SQBIND_DECLARE_CLASS_NAME)*/
/*lint -emacro(1577,SQBIND_DECLARE_CLASS_NAME)*/

/*lint -emacro(19,SQBIND_DECLARE_CUSTOM_CLASS_NAME)*/
/*lint -emacro(1576,SQBIND_DECLARE_CUSTOM_CLASS_NAME)*/
/*lint -emacro(1577,SQBIND_DECLARE_CUSTOM_CLASS_NAME)*/

/// \defgroup CLASS_DECLARATION Binding types
/// Macros for binding types to script.

/// @{

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CLASS_BASE(TYPE, NAME)
/// \brief Declares the Match and Get function specialisations for a class type so functions with TYPE as
/// arguments or returning TYPE can be automatically bound to script. Does not define any Push specialisations.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CLASS_BASE(TYPE, NAME) \
  SQBIND_DECLARE_TYPEINFO(TYPE, NAME); \
  namespace sqb \
  { \
  template<> \
  inline bool Match<TYPE>(TypeWrapper<TYPE>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQBIND_ASSERT(sq_gettop(vm) >= (idx < 0 ? -idx : idx)); \
    SQUserPointer up; \
    return (sq_getinstanceup(vm, idx, &up, ClassTypeTag<TYPE>::Get()) == SQ_OK); \
  } \
  template<> \
  inline bool Match<TYPE>(TypeWrapper<TYPE *>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQBIND_ASSERT(sq_gettop(vm) >= (idx < 0 ? -idx : idx)); \
    SQUserPointer up; \
    return ((sq_gettype(vm, idx) == OT_NULL) || (sq_getinstanceup(vm, idx, &up, ClassTypeTag<TYPE>::Get()) == SQ_OK)); \
  } \
  template<> \
  inline bool Match<TYPE>(TypeWrapper<TYPE &>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQBIND_ASSERT(sq_gettop(vm) >= (idx < 0 ? -idx : idx)); \
    SQUserPointer up; \
    return (sq_getinstanceup(vm, idx, &up, ClassTypeTag<TYPE>::Get()) == SQ_OK); \
  } \
  template<> \
  inline bool Match<TYPE>(TypeWrapper<const TYPE *>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQBIND_ASSERT(sq_gettop(vm) >= (idx < 0 ? -idx : idx)); \
    SQUserPointer up; \
    return ((sq_gettype(vm, idx) == OT_NULL) || (sq_getinstanceup(vm, idx, &up, ClassTypeTag<TYPE>::Get()) == SQ_OK)); \
  } \
  template<> \
  inline bool Match<TYPE>(TypeWrapper<const TYPE &>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQBIND_ASSERT(sq_gettop(vm) >= (idx < 0 ? -idx : idx)); \
    SQUserPointer up; \
    return (sq_getinstanceup(vm, idx, &up, ClassTypeTag<TYPE>::Get()) == SQ_OK); \
  } \
  template<> \
  inline TYPE &Get<TYPE>(TypeWrapper<TYPE>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQUserPointer up; \
    SQBIND_ASSERT(Match<TYPE>(TypeWrapper<TYPE>(), vm, idx)); \
    sq_getinstanceup(vm, idx, &up, nullptr); \
    return *reinterpret_cast<TYPE *>(up); \
  } \
  template<> \
  inline TYPE *Get<TYPE>(TypeWrapper<TYPE *>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQUserPointer up; \
    if (sq_gettype(vm, idx) == OT_NULL) \
    { \
      return 0; \
    } \
    SQBIND_ASSERT(Match<TYPE>(TypeWrapper<TYPE *>(), vm, idx)); \
    sq_getinstanceup(vm, idx, &up, nullptr); \
    return reinterpret_cast<TYPE *>(up); \
  } \
  template<> \
  inline TYPE &Get<TYPE>(TypeWrapper<TYPE &>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQUserPointer up; \
    SQBIND_ASSERT(Match<TYPE>(TypeWrapper<TYPE *>(), vm, idx)); \
    sq_getinstanceup(vm, idx, &up, nullptr); \
    return *reinterpret_cast<TYPE *>(up); \
  } \
  template<> \
  inline const TYPE *Get<TYPE>(TypeWrapper<const TYPE *>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQUserPointer up; \
    if (sq_gettype(vm, idx) == OT_NULL) \
    { \
      return 0; \
    } \
    SQBIND_ASSERT(Match<TYPE>(TypeWrapper<TYPE *>(), vm, idx)); \
    sq_getinstanceup(vm, idx, &up, nullptr); \
    return reinterpret_cast<const TYPE *>(up); \
  } \
  template<> \
  inline const TYPE &Get<TYPE>(TypeWrapper<const TYPE &>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQUserPointer up; \
    SQBIND_ASSERT(Match<TYPE>(TypeWrapper<TYPE *>(), vm, idx)); \
    sq_getinstanceup(vm, idx, &up, nullptr); \
    return *reinterpret_cast<const TYPE *>(up); \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CLASS_BASE2(TYPE, NAME)
/// \brief Calls SQBIND_DECLARE_CLASS_BASE and also defines two specialisations of Push for TYPE* and const TYPE* types.
/// These will be bound with no release hook as they are pointers and so have been created somewhere externally.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CLASS_BASE2(TYPE, NAME) \
  SQBIND_DECLARE_CLASS_BASE(TYPE, NAME); \
  namespace sqb \
  { \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE *value) \
  { \
    return internal::BaseClassStackHelper<false>::Push<TYPE>(vm, value); \
  } \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE *value) \
  { \
    return internal::BaseClassStackHelper<false>::Push<TYPE>(vm, value); \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CLASSUD_CLASS_NAME(TYPE, NAME)
/// \brief Calls SQBIND_DECLARE_CLASS_BASE2 and defines the remaining Push overloads for Type& and const Type&.
/// Should be used if a class is bound with ClassUserDataClassDef.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CLASSUD_CLASS_NAME(TYPE, NAME) \
  SQBIND_DECLARE_CLASS_BASE2(TYPE, NAME); \
  namespace sqb \
  { \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE &value) \
  { \
    return internal::ClassUserDataStackHelper<traits::IsCopyable<TYPE>::kValue>::Push<TYPE>(vm, value); \
  } \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE &value) \
  { \
    return internal::ClassUserDataStackHelper<traits::IsCopyable<TYPE>::kValue>::Push<TYPE>(vm, value); \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_SQMALLOC_CLASS_NAME(TYPE, NAME)
/// \brief Calls SQBIND_DECLARE_CLASS_BASE2 and defines the remaining Push overloads for Type& and const Type&.
/// Should be used if a class is bound with SqMallocClassDefinition.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_SQMALLOC_CLASS_NAME(TYPE, NAME) \
  SQBIND_DECLARE_CLASS_BASE2(TYPE, NAME) \
  namespace sqb \
  { \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE &value) \
  { \
    return internal::SqMallocStackHelper<traits::IsCopyable<TYPE>::kValue>::Push<TYPE>(vm, value); \
  } \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE &value) \
  { \
    return internal::SqMallocStackHelper<traits::IsCopyable<TYPE>::kValue>::Push<TYPE>(vm, value); \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_AUTO_RELEASE_CLASS_NAME(TYPE, NAME)
/// \brief Calls SQBIND_DECLARE_CLASS_BASE and defines all Push overloads. Pushing references types will fail,
///   pushing pointer types will be the same as the base type but with the release hook set.
/// Should be used if a class is bound with NonCopyableClassDef.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_AUTO_RELEASE_CLASS_NAME(TYPE, NAME) \
  SQBIND_TYPE_NON_COPYABLE(TYPE); \
  SQBIND_DECLARE_CLASS_BASE(TYPE, NAME); \
  namespace sqb \
  { \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE *value) \
  { \
  return internal::BaseClassStackHelper<true>::Push<TYPE>(vm, value); \
  } \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE *value) \
  { \
  return internal::BaseClassStackHelper<true>::Push<TYPE>(vm, value); \
  } \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE &SQBIND_UNUSED(value)) \
  { \
    SQBIND_ASSERT_FAIL(); \
    return sq_throwerror(vm, "cannot push copy of non copyable type"); \
  } \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE &SQBIND_UNUSED(value)) \
  { \
    SQBIND_ASSERT_FAIL(); \
    return sq_throwerror(vm, "cannot push copy of non copyable type"); \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_NON_COPYABLE_CLASS_NAME(TYPE, NAME)
/// \brief Calls SQBIND_DECLARE_CLASS_BASE2 and defines the remaining Push overloads for Type& and const Type&.
/// Should be used if a class is bound with NonCopyableClassDef.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_NON_COPYABLE_CLASS_NAME(TYPE, NAME) \
  SQBIND_TYPE_NON_COPYABLE(TYPE); \
  SQBIND_DECLARE_CLASS_BASE2(TYPE, NAME); \
  namespace sqb \
  { \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE &SQBIND_UNUSED(value)) \
  { \
    SQBIND_ASSERT_FAIL(); \
    return sq_throwerror(vm, "cannot push copy of non copyable type"); \
  } \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE &SQBIND_UNUSED(value)) \
  { \
    SQBIND_ASSERT_FAIL(); \
    return sq_throwerror(vm, "cannot push copy of non copyable type"); \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CUSTOM_CLASS_NAME(TYPE, NAME)
/// \brief Calls SQBIND_DECLARE_CLASS_BASE and only declares all Push overloads Type. A custom implementation for
/// all four overloads must be defined elsewhere within the program.
/// Should be used if a class is bound using a custom method.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CUSTOM_CLASS_NAME(TYPE, NAME) \
  SQBIND_DECLARE_CLASS_BASE(TYPE, NAME) \
  namespace sqb \
  { \
  template<> \
  SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE *value); \
  template<> \
  SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE &value); \
  template<> \
  SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE *value); \
  template<> \
  SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE &value); \
  }


//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CLASSUD_CLASS(TYPE)
/// \brief Calls SQBIND_DECLARE_CLASSUD_CLASS_NAME with TYPE as the name of the class.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CLASSUD_CLASS(TYPE) \
  SQBIND_DECLARE_CLASSUD_CLASS_NAME(TYPE, TYPE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_SQMALLOC_CLASS(TYPE)
/// \brief Calls SQBIND_DECLARE_SQMALLOC_CLASS_NAME with TYPE as the name of the class.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_SQMALLOC_CLASS(TYPE) \
  SQBIND_DECLARE_SQMALLOC_CLASS_NAME(TYPE, TYPE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CLASS_NAME(TYPE, NAME)
/// \brief Calls the recommended method of declaring a named class type. Currently SQBIND_DECLARE_CLASSUD_CLASS_NAME
/// though this is subject to change.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CLASS_NAME(TYPE, NAME) \
  SQBIND_DECLARE_CLASSUD_CLASS_NAME(TYPE, NAME)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CLASS(TYPE)
/// \brief Calls the recommended method of declaring a class type. Currently SQBIND_DECLARE_CLASSUD_CLASS
/// though this is subject to change.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CLASS(TYPE) \
  SQBIND_DECLARE_CLASSUD_CLASS_NAME(TYPE, TYPE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_AUTO_RELEASE_CLASS(TYPE)
/// \brief Calls SQBIND_DECLARE_AUTO_RELEASE_CLASS_NAME with TYPE as the name of the class.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_AUTO_RELEASE_CLASS(TYPE) \
  SQBIND_DECLARE_AUTO_RELEASE_CLASS_NAME(TYPE, TYPE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_NON_COPYABLE_CLASS(TYPE)
/// \brief Calls SQBIND_DECLARE_NON_COPYABLE_CLASS_NAME with TYPE as the name of the class.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_NON_COPYABLE_CLASS(TYPE) \
  SQBIND_DECLARE_NON_COPYABLE_CLASS_NAME(TYPE, TYPE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CUSTOM_CLASS(TYPE)
/// \brief Declare a type without specialising sqb#Push, the types name will be TYPE.
/// \note sqb#Push must be manually defined elsewhere.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CUSTOM_CLASS(TYPE) \
  SQBIND_DECLARE_CUSTOM_CLASS_NAME(TYPE, TYPE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_ENUM(TYPE)
/// \brief Declares an enum type by providing specialisations to sqb#Push, sqb#Match and sqb#Get.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_ENUM(TYPE) \
  namespace sqb \
  { \
  template<> \
  struct TypeInfo<TYPE> \
  { \
    enum \
    { \
      kTypeID = kScriptVarTypeInt32, \
      kTypeSize = sizeof(TYPE), \
      kTypeMask = 'n', \
      kTypeIsInstance = SQFalse, \
    }; \
    const SQChar *m_typeName; \
    inline TypeInfo() \
    : m_typeName(_SC("integer")) \
    { \
    } \
    inline operator ScriptVarType() const \
    { \
      return static_cast<ScriptVarType>(kTypeID); \
    } \
  }; \
  inline SQRESULT Push(HSQUIRRELVM vm, TYPE value) \
  { \
    sq_pushinteger(vm, static_cast<SQInteger>(value)); \
    return 1; \
  } \
  inline bool Match(TypeWrapper<TYPE>, HSQUIRRELVM vm, SQInteger index) \
  { \
    SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index)); \
    return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC); \
  } \
  inline TYPE Get(TypeWrapper<TYPE>, HSQUIRRELVM vm, SQInteger index) \
  { \
    SQInteger value = 0; \
    SQRESULT result = sq_getinteger(vm, index, &value); \
    SQBIND_ASSERT_SUCCEEDED(result); \
    return static_cast<TYPE>(value); \
  } \
  }

/// @}

/// \internal

namespace sqb
{
namespace internal
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
template<bool RequiresReleaseHook>
struct BaseClassStackHelper
{
  template<typename InstanceType>
  static SQRESULT Push(HSQUIRRELVM vm, InstanceType *value);

  template<typename InstanceType>
  static SQRESULT Push(HSQUIRRELVM vm, const InstanceType *value);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
template<bool IsCopyable>
struct ClassUserDataStackHelper
{
  template<typename InstanceType>
  static SQRESULT Push(HSQUIRRELVM vm, InstanceType &value);

  template<typename InstanceType>
  static SQRESULT Push(HSQUIRRELVM vm, const InstanceType &value);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
template<bool IsCopyable>
struct SqMallocStackHelper
{
  template<typename InstanceType>
  static SQRESULT Push(HSQUIRRELVM vm, InstanceType &value);

  template<typename InstanceType>
  static SQRESULT Push(HSQUIRRELVM vm, const InstanceType &value);
};

} // namespace internal

} // namespace sqb

/// \endinternal

// ---- #include <sqbind/sqbBindMacros.inl>
// ---> including sqbBindMacros.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
namespace internal
{
//----------------------------------------------------------------------------------------------------------------------
// BaseClassStackHelper
//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT BaseClassStackHelper<true>::Push(HSQUIRRELVM vm, InstanceType *value)
{
  if (value != nullptr)
  {
    const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
    HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
    SQBIND_ASSERT(sq_isclass(classObject));
    SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
    if (CreateNativeClassInstance(vm, classObject, hook))
    {
      sq_setinstanceup(vm, -1, value);
      return 1;
    }

    sqb::StackHandler sh(vm);
    return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
  }
  sq_pushnull(vm);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT BaseClassStackHelper<false>::Push(HSQUIRRELVM vm, InstanceType *value)
{
  if (value != nullptr)
  {
    const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
    HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
    SQBIND_ASSERT(sq_isclass(classObject));
    if (CreateNativeClassInstance(vm, classObject, nullptr))
    {
      sq_setinstanceup(vm, -1, value);
      return 1;
    }

    sqb::StackHandler sh(vm);
    return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
  }

  sq_pushnull(vm);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT BaseClassStackHelper<true>::Push(HSQUIRRELVM vm, const InstanceType *value)
{
  if (value != nullptr)
  {
    const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
    HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
    SQBIND_ASSERT(sq_isclass(classObject));
    SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
    if (CreateNativeClassInstance(vm, classObject, hook))
    {
      sq_setinstanceup(vm, -1, const_cast<InstanceType *>(value));
      return 1;
    }

    sqb::StackHandler sh(vm);
    return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
  }

  sq_pushnull(vm);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT BaseClassStackHelper<false>::Push(HSQUIRRELVM vm, const InstanceType *value)
{
  if (value != nullptr)
  {
    const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
    HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
    SQBIND_ASSERT(sq_isclass(classObject));
    if (CreateNativeClassInstance(vm, classObject, nullptr))
    {
      sq_setinstanceup(vm, -1, const_cast<InstanceType *>(value));
      return 1;
    }

    sqb::StackHandler sh(vm);
    return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
  }

  sq_pushnull(vm);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
// ClassUserDataStackHelper
//----------------------------------------------------------------------------------------------------------------------
template<bool IsCopyable>
template<typename InstanceType>
inline SQRESULT ClassUserDataStackHelper<IsCopyable>::Push(HSQUIRRELVM vm, InstanceType &value)
{
  const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
  HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
  SQBIND_ASSERT(sq_isclass(classObject));
  SQBIND_ASSERT(classTypeTag->CheckClassUserDataSize(vm, sizeof(InstanceType)));
  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  if (CreateNativeClassInstance(vm, classObject, hook))
  {
    SQUserPointer userPointer;
    sq_getinstanceup(vm, -1, &userPointer, 0);

    // align the instance if required
    //
#if defined(SQBIND_COMPILER_MSVC)
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif
    if (traits::IsAligned<InstanceType>::kIsAligned)
    {
      const ptrdiff_t pointer = reinterpret_cast<ptrdiff_t>(userPointer);
      const ptrdiff_t alignment = static_cast<ptrdiff_t>(traits::IsAligned<InstanceType>::kAlignment);
      userPointer = reinterpret_cast<SQUserPointer>((pointer + (alignment - 1)) & ~(alignment - 1));
      sq_setinstanceup(vm, 1, userPointer);
    }
#if defined(SQBIND_COMPILER_MSVC)
# pragma warning(pop)
#endif

    new (userPointer) InstanceType(value);
    return 1;
  }

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT ClassUserDataStackHelper<false>::Push(HSQUIRRELVM vm, InstanceType &SQBIND_UNUSED(value))
{
  SQBIND_ASSERT_FAIL();

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("cannot push copy of non copyable type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

//----------------------------------------------------------------------------------------------------------------------
template<bool IsCopyable>
template<typename InstanceType>
inline SQRESULT ClassUserDataStackHelper<IsCopyable>::Push(HSQUIRRELVM vm, const InstanceType &value)
{
  const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
  HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
  SQBIND_ASSERT(sq_isclass(classObject));
  SQBIND_ASSERT(classTypeTag->CheckClassUserDataSize(vm, sizeof(InstanceType)));
  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  if (CreateNativeClassInstance(vm, classObject, hook))
  {
    SQUserPointer userPointer;
    sq_getinstanceup(vm, -1, &userPointer, 0);

    // align the instance if required
    //
#if defined(SQBIND_COMPILER_MSVC)
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif
    if (traits::IsAligned<InstanceType>::kIsAligned)
    {
      const ptrdiff_t pointer = reinterpret_cast<ptrdiff_t>(userPointer);
      const ptrdiff_t alignment = static_cast<ptrdiff_t>(traits::IsAligned<InstanceType>::kAlignment);
      userPointer = reinterpret_cast<SQUserPointer>((pointer + (alignment - 1)) & ~(alignment - 1));
      sq_setinstanceup(vm, 1, userPointer);
    }
#if defined(SQBIND_COMPILER_MSVC)
# pragma warning(pop)
#endif

    new (userPointer) InstanceType(value);
    return 1;
  }

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT ClassUserDataStackHelper<false>::Push(HSQUIRRELVM vm, const InstanceType &SQBIND_UNUSED(value))
{
  SQBIND_ASSERT_FAIL();

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("cannot push copy of non copyable type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

//----------------------------------------------------------------------------------------------------------------------
// SqMallocStackHelper
//----------------------------------------------------------------------------------------------------------------------
template<bool IsCopyable>
template<typename InstanceType>
inline SQRESULT SqMallocStackHelper<IsCopyable>::Push(HSQUIRRELVM vm, InstanceType &value)
{
  const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
  HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
  SQBIND_ASSERT(sq_isclass(classObject));
  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  if (CreateNativeClassInstance(vm, classObject, hook))
  {
    void *memory = sq_malloc(sizeof(InstanceType));
    new (memory) InstanceType(value);
    sq_setinstanceup(vm, -1, memory);
    return 1;
  }

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT SqMallocStackHelper<false>::Push(HSQUIRRELVM vm, InstanceType &SQBIND_UNUSED(value))
{
  SQBIND_ASSERT_FAIL();

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("cannot push copy of non copyable type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

//----------------------------------------------------------------------------------------------------------------------
template<bool IsCopyable>
template<typename InstanceType>
inline SQRESULT SqMallocStackHelper<IsCopyable>::Push(HSQUIRRELVM vm, const InstanceType &value)
{
  const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
  HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
  SQBIND_ASSERT(sq_isclass(classObject));
  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  if (CreateNativeClassInstance(vm, classObject, hook))
  {
    void *memory = sq_malloc(sizeof(InstanceType));
    new (memory) InstanceType(value);
    sq_setinstanceup(vm, -1, memory);
    return 1;
  }

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT SqMallocStackHelper<false>::Push(HSQUIRRELVM vm, const InstanceType &SQBIND_UNUSED(value))
{
  SQBIND_ASSERT_FAIL();

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("cannot push copy of non copyable type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

} // namespace internal

} // namespace sqb

// <--- back to sqbBindMacros.h

// <--- back to SquirrelBind.h
// ---- #include <sqbind/sqbClassDefinition.h>
// ---> including sqbClassDefinition.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbBind.h>
// ---> including sqbBind.h
// <--- back to sqbClassDefinition.h
// ---- #include <sqbind/sqbTypeTraits.h>
// ---> including sqbTypeTraits.h
// <--- back to sqbClassDefinition.h
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief Wrapper class for binding squirrel class. This class cannot be used directly, use
/// sqb#ClassDefinition or sqb#NoConstructorClassDefinition.
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
class ClassDefinitionBase
{
public:
  /// \brief typedef for class method with variable arguments.
  typedef SQInteger (ClassType::*HSQMETHOD)(HSQUIRRELVM);

  /// \brief Get the object that defines this class being bound.
  HSQOBJECT GetClassObject() const;

  /// \brief Sets the user data size of the class. When an instance of the class is created
  /// an additional amount of memory of size is also allocated after the instance saving the need
  /// for another allocation. The instance user pointer will point at the start of this additional
  /// memory block. ClassUserDataClassDefinition uses this approach to save the need for an additional allocation
  /// with every instance which SqMallocClassDefinition requires.
  ClassDefinitionBase& SetUserDataSize(size_t size);

  /// \brief Set the release hook for this class, will override any existing release hook.
  /// \note ClassUserDataClassDefinition and SqMallocClassDefinition call this function internally so unless
  /// you need to override the default release hook there is no need to call this.
  ClassDefinitionBase& SetReleaseHook(SQRELEASEHOOK hook);

  /// \brief Set the constructor of this class type. This will override any existing constructor
  /// but leave the current release hook. Useful when a class has a constructor that accepts more
  /// than the arguments the default SqMallocConstructor and ClassUserDataConstructor functions provide.
  /// \code
  /// class Vector2
  /// {
  /// public:
  ///   Vector2();
  ///   Vector2(const Vector2& copy);
  ///   Vector2(float x, float y);
  /// }
  ///
  /// SQInteger Vector2Constructor(HSQUIRRELVM vm);
  ///
  /// // ClassUserDataClassDefinition constructor sets up a default constructor and release hook and then
  /// // the call to Constructor overrides the constructor but leaves the release hook.
  /// sqb::ClassUserDataClassDefinition(vm, "Vector2")
  ///   .Constructor(
  ///     &Vector2Constructor,
  ///     FunctionOptions()
  ///       .ParamCheckCount(-1)
  ///       .TypeMask(_SC("x x|n n"))
  ///     )
  ///   ;
  /// \endcode
  ClassDefinitionBase& Constructor(
    SQFUNCTION constructor,
    const FunctionOptions &options = FunctionOptions());

  /// \brief Bind a class method.
  /// \code
  /// class MyClass
  /// {
  /// public:
  ///   int Func(int p1, bool p2, float p3);
  /// };
  ///
  /// sqb::ClassDefinition<MyClass>(vm, _SC("MyClass")).ClassFunction(&MyClass::Func, _SC("function"));
  /// \endcode
  template<typename FuncType>
  ClassDefinitionBase& ClassFunction(FuncType function, const SQChar *name);

  /// \brief
  /// \code
  /// class MyClass
  /// {
  /// public:
  ///   void Func(HSQUIRRELVM vm);
  /// };
  ///
  /// sqb::ClassDefinition<MyClass>(vm, _SC("MyClass")).NativeClassFunction(&MyClass::Func, _SC("function"));
  /// \endcode
  ClassDefinitionBase& NativeClassFunction(
    HSQMETHOD function,
    const SQChar *name,
    const FunctionOptions &options = FunctionOptions());

  /// \brief Binds a static class function as a static squirrel function.
  /// \code
  /// class MyClass
  /// {
  /// public:
  ///   static void Func(int p1, float p2);
  /// }
  ///
  /// sqb::ClassDefinition<MyClass>(vm, _SC("MyClass")).Function(&MyClass::Func, _SC("function"));
  /// \endcode
  template<typename FuncType>
  ClassDefinitionBase& Function(FuncType function, const SQChar *name, FunctionOptions options = FunctionOptions());

  /// \brief Registers a standard SQFUNCTION as a non-static member function of this class.
  /// \note the Static in the name refers to the c++/c function being static not the squirrel
  /// class function.
  /// \code
  /// class MyClass
  /// {
  /// public:
  ///   static int example1(HSQUIRREL vm);
  /// }
  /// int example2(HSQUIRREL vm);
  ///
  /// sqb::ClassDefinition<MyClass>(vm, _SC("MyClass")).NativeFunction(&MyClass::example1, _SC("example1"));
  /// sqb::ClassDefinition<MyClass>(vm, _SC("MyClass")).NativeFunction(&example2, _SC("example2"));
  /// \endcode
  ClassDefinitionBase& NativeFunction(
    SQFUNCTION function,
    const SQChar *name,
    const FunctionOptions &options = FunctionOptions());

  /// \brief Bind a normal member function of a singleton class as a static function in squirrel.
  /// \code
  /// class Singleton
  /// {
  /// public:
  ///   static Singleton *GetInstance();
  ///   void Func();
  /// }
  ///
  /// sqb::NoConstructorClassDefinition(vm, _SC("Singleton"))
  ///   .SingletonFunction(Singleton::GetInstance(), &Singleton::Func, _SC("Func")
  ///   ;
  /// \endcode
  template<typename FuncType>
  ClassDefinitionBase& SingletonFunction(ClassType *instance, FuncType function, const SQChar *name);

  /// \brief Bind a variable argument member function of a singleton class as a static function in squirrel.
  /// \code
  /// class Singleton
  /// {
  /// public:
  ///   static Singleton *GetInstance();
  ///   SQInteger Func(HSQUIRRELVM vm);
  /// }
  ///
  /// sqb::NoConstructorClassDefinition(vm, _SC("Singleton"))
  ///   .NativeSingletonFunction(Singleton::GetInstance, &Singleton::Func, _SC("Func")
  ///   ;
  /// \endcode
  ClassDefinitionBase& NativeSingletonFunction(
    ClassType *instance,
    HSQMETHOD function,
    const SQChar *name,
    const FunctionOptions &options = FunctionOptions());

  /// \brief Binds a class member variable as a member variable of the squirrel class.
  /// \code
  /// struct Vector2
  /// {
  ///   float x;
  ///   float y;
  /// };
  ///
  /// sqb::ClassUserDataClassDefinition<Vector2>(vm, _SC("Vector2"))
  ///   .Variable(&Vector2::x, _SC("x"))
  ///   .Variable(&Vector2::y, _SC("y"))
  ///   ;
  /// \endcode
  template<typename VariableType>
  ClassDefinitionBase& Variable(VariableType ClassType:: *var, const SQChar *name);

  /// \brief Binds a class member variable as a member variable of type user pointer in the squirrel class.
  /// User pointers cannot be manipulated directly from squirrel but can be passed around and used as a
  /// function argument.
  /// \code
  /// struct Handle
  /// {
  ///   void *m_pointer;
  /// };
  ///
  /// sqb::ClassUserDataClassDefinition<Handle>(vm, _SC("Handle"))
  ///   .UserPointerVariable(&Handle::m_pointer, _SC("pointer"))
  ///   ;
  /// \endcode
  template<typename VariableType>
  ClassDefinitionBase& UserPointerVariable(VariableType ClassType:: *var, const SQChar *name);

  /// \brief Bind a variable as a static member of a class.
  /// Useful in conjunction with SingletonFunc for binding specific instance member variables 
  /// or normal variables. All static variables are const for fundamental squirrel types bound
  /// static variables will have the value at the time of binding.
  /// \code
  /// class Singleton
  /// {
  /// public:
  ///   static Singleton *GetInstance();
  ///   bool m_boolean;
  /// };
  /// static int m_integer;
  ///
  /// sqb::NoConstructorClassDefinition(vm, _SC("Singleton"))
  ///   .StaticVariable(GetInstance()->m_boolean, _SC("boolean"))
  ///   .StaticVariable(m_integer, _SC("integer"))
  ///   ;
  /// \endcode
  template<typename VariableType>
  ClassDefinitionBase& StaticVariable(const VariableType &var, const SQChar *name);

  /// \brief Bind an integer or enum value as a static int member of the class
  /// \code
  /// class Window
  /// {
  /// public:
  ///   enum CreationFlags
  ///   {
  ///     kCreateMaximised = 0,
  ///     kCreateResizable = 1
  ///   };
  ///   // other code
  /// };
  /// int kExternalCreateFlag = 2;
  ///
  /// sqb::ClassDefinition<Window>(vm, name)
  ///   .EnumEntry(Window::kCreateMaximised, _SC("kCreateMaximised"))
  ///   .EnumEntry(Window::kCreateResizable, _SC("kCreateResizable"))
  ///   .EnumEntry(kExternalCreateFlag, _SC("kExternalCreateFlag"))
  ///   ;
  /// \endcode
  ClassDefinitionBase& EnumEntry(SQInteger value, const SQChar *name);

protected:
  HSQUIRRELVM     m_vm;
  HSQOBJECT       m_classObject;

  ClassDefinitionBase(HSQUIRRELVM vm, SQInteger objectIndex, const SQChar *name);
  ~ClassDefinitionBase();

  /// \cond NO_DOXYGEN
  ClassDefinitionBase(const ClassDefinitionBase& rhs);
  const ClassDefinitionBase& operator = (const ClassDefinitionBase& rhs);
  /// \endcond
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief Binds a class with a default constructor and typeof function. The memory required for new class instances
/// will be allocated using squirrel's class user data functionality so only one allocation will be done for the
/// stack object and the instance itself, this is the most effective way of creating new class instances within
/// squirrel. For types declared with SQBIND_DECLARE_CLASS_POD this also means they need no release hook at all which
/// is also a minor speed up. Use in conjunction with SQBIND_DECLARE_CLASSUD_CLASS or SQBIND_DECLARE_CLASS.
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType = NoBaseClass>
class ClassUserDataClassDefinition : public ClassDefinitionBase<ClassType, BaseClassType>
{
public:
  /// \brief The default constructor for classes bound with this method, can be used as a fallback in
  ///   custom constructors.
  static SQInteger DefaultConstructor(HSQUIRRELVM vm);
  /// \brief The default release hook for classes bound with this method.
  /// \note If a class is a pod type then there is no need to ever use a release hook, calling this function
  /// will be a no-op.
  static SQInteger DefaultReleaseHook(SQUserPointer up, SQInteger size);

  /// \brief Bind a class to script. The parameter name is the name of the class
  /// in script and does not have to be the same as the actual class name.
  /// \code
  /// class MyClass
  /// {
  /// };
  ///
  /// sqb::ClassUserDataClassDefinition<MyClass>(vm, _SC("MyClass"));
  /// \endcode
  ClassUserDataClassDefinition(
    HSQUIRRELVM   vm,
    SQInteger     ownerIndex,
    const SQChar *name);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief Binds a class with a default constructor and typeof function. The memory required for new class instances
/// will be allocated and deallocated with calls to sq_malloc and sq_free. This will be additional to the allocation
/// squirrel will do internally for the stack object. Even if a class is declared with SQBIND_DECLARE_CLASS_POD a
/// release hook is required to ensure sq_free is called. Use in conjunction with SQBIND_DECLARE_SQMALLOC_CLASS.
/// \note This is really only provided as a reference of how other ClassDefinition types can be implemented, use
/// ClassUserDataClassDefinition instead.
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType = NoBaseClass>
class SqMallocClassDefinition : public ClassDefinitionBase<ClassType, BaseClassType>
{
public:
  /// \brief The default constructor for classes bound with this method, can be used as a fallback in
  ///   custom constructors.
  static SQInteger DefaultConstructor(HSQUIRRELVM vm);
  /// \brief The default release hook for classes bound with this method.
  static SQInteger DefaultReleaseHook(SQUserPointer up, SQInteger size);
  
  /// \brief Bind a class to script. The parameter name is the name of the class
  /// in script and does not have to be the same as the actual class name.
  /// \code
  /// namespace blah
  /// {
  /// class MyClass
  /// {
  /// };
  /// }
  ///
  /// sqb::SqMallocClassDefinition<blah::MyClass>(vm, _SC("ScriptClass"));
  /// \endcode
  SqMallocClassDefinition(
    HSQUIRRELVM   vm,
    SQInteger     ownerIndex,
    const SQChar *name);
    
protected:
  template<bool IsCopyableType>
  SQInteger InternalDefaultConstructor(HSQUIRRELVM vm);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief Binds a class with the typeof function overloaded. This class can be used if you wish to provide custom
/// methods for allocating/deallocating instance types or for classes that are purely created within c++ code and never
/// squirrel scripts. This can be used to expose singleton classes to script. Use in conjunction with
/// SQBIND_DECLARE_NON_COPYABLE_CLASS or SQBIND_DECLARE_CUSTOM_CLASS.
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType = NoBaseClass>
class NoConstructorClassDefinition : public ClassDefinitionBase<ClassType, BaseClassType>
{
public:
  /// \brief Bind a class to script.
  /// \code
  /// namespace blah
  /// {
  /// class MyClass
  /// {
  /// };
  /// }
  ///
  /// sqb::NoConstructorClassDefinition<blah::MyClass>(vm, _SC("MyClass"));
  /// \endcode
  NoConstructorClassDefinition(
    HSQUIRRELVM   vm,
    SQInteger     ownerIndex,
    const SQChar *name);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType = NoBaseClass>
class ClassDefinition : public ClassUserDataClassDefinition<ClassType, BaseClassType>
{
public:
  /// \brief Bind a class to script. The parameter name is the name of the class
  /// in script and does not have to be the same as the actual class name.
  /// \code
  /// class MyClass
  /// {
  /// };
  ///
  /// sqb::ClassDefinition<MyClass>(vm, _SC("MyClass"));
  /// \endcode
  ClassDefinition(
    HSQUIRRELVM   vm,
    SQInteger     ownerIndex,
    const SQChar *name);
};

/*Initializing the implicit object parameter 'Type' (a non-const reference) with a non-lvalue*/
/*lint -esym(1793,sqb::ClassDefinitionBase<*,*>)*/
/*Ignoring return value of function*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::Func)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::FuncVarArgs)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::GlobalMemberFunc)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::GlobalMemberFuncVarArgs)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::StaticFunc)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::StaticFuncVarArgs)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::Var)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::VarAsUserPointer)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::StaticVar)*/

}

// ---- #include <sqbind/sqbClassDefinition.inl>
// ---> including sqbClassDefinition.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

#if defined(SQBIND_COMPILER_MSVC)
#pragma warning(push)
// disable warning C4127: conditional expression is constant
// type traits kValue used as conditionals
#pragma warning(disable: 4127)
#endif

namespace sqb
{
namespace internal
{
//----------------------------------------------------------------------------------------------------------------------
// Specialisation based on if a type is copyable, required to work round template specialisation issues.
// Consider: template<typename X> class A { template<typename Y> class B{}; };
// It is not permitted to specialise class B without also specialising class A so this helper function is needed
// for the default constructors
//----------------------------------------------------------------------------------------------------------------------
template<bool IsCopyableType>
struct CopyableSpecialisation
{
  template<typename ClassType>
  static SQInteger ClassUserDataConstructor(HSQUIRRELVM vm);

  template<typename ClassType>
  static SQInteger SqMallocConstructor(HSQUIRRELVM vm);
};

} // namespace internal

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline HSQOBJECT ClassDefinitionBase<ClassType, BaseClassType>::GetClassObject() const
{
  return m_classObject;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::SetUserDataSize(size_t size)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sq_setclassudsize(m_vm, -1, size);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::SetReleaseHook(SQRELEASEHOOK hook)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sqb::ClassTypeTag<ClassType>* classTypeTag = sqb::ClassTypeTag<ClassType>::Get();
  classTypeTag->SetReleaseHook(hook);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::Constructor(
  SQFUNCTION constructor,
  const FunctionOptions& options)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindNativeFunction(m_vm, -1, constructor, _SC("constructor"), options);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
template<typename FuncType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::ClassFunction(
  FuncType function,
  const SQChar *name)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindClassFunction<ClassType>(m_vm, -1, function, name);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::NativeClassFunction(
  HSQMETHOD function,
  const SQChar *name,
  const FunctionOptions &options)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindNativeClassFunction<ClassType>(m_vm, -1, function, name, options);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
template<typename FuncType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::Function(
  FuncType function,
  const SQChar *name,
  FunctionOptions options)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindFunction(m_vm, -1, function, name, options);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::NativeFunction(
  SQFUNCTION function,
  const SQChar *name,
  const FunctionOptions &options)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindNativeFunction(m_vm, -1, function, name, options);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
template<typename FuncType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::SingletonFunction(
  ClassType *instance,
  FuncType function,
  const SQChar *name)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindSingletonFunction(m_vm, -1, instance, function, name);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::NativeSingletonFunction(
  ClassType *instance,
  HSQMETHOD function,
  const SQChar *name,
  const FunctionOptions &options)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindNativeSingletonFunction(m_vm, -1, instance, function, name, options);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
template<typename VariableType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::Variable(
  VariableType ClassType:: *variable,
  const SQChar             *name)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindInstanceVariable<ClassType>(m_vm, -1, variable, name);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
template<typename VariableType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::UserPointerVariable(
  VariableType ClassType:: *variable,
  const SQChar             *name)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindInstanceVariable<ClassType>(m_vm, -1, reinterpret_cast<SQUserPointer ClassType::*>(variable), name);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
template<typename VariableType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::StaticVariable(
  const VariableType &variable,
  const SQChar *name)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sq_pushstring(m_vm, name, -1);
  Push(m_vm, variable);
  sq_newslot(m_vm, -3, SQTrue);
  sq_poptop(m_vm);

  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::EnumEntry(
  SQInteger entry,
  const SQChar *name)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sq_pushstring(m_vm, name, -1);
  sq_pushinteger(m_vm, entry);
  sq_newslot(m_vm, -3, SQTrue);
  sq_poptop(m_vm);

  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
ClassDefinitionBase<ClassType, BaseClassType>::ClassDefinitionBase(
  HSQUIRRELVM   vm,
  SQInteger     ownerIndex,
  const SQChar *name)
: m_vm(vm)
{
  sq_resetobject(&m_classObject);

  if (!sqb::Bind::BindClass<ClassType, BaseClassType>(m_vm, ownerIndex, name))
  {
    return;
  }

  sqb::ClassTypeTag<ClassType>* classTypeTag = sqb::ClassTypeTag<ClassType>::Get();
  m_classObject = classTypeTag->GetClassObject(m_vm);
  sq_addref(m_vm, &m_classObject);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline ClassDefinitionBase<ClassType, BaseClassType>::~ClassDefinitionBase()
{
  sq_release(m_vm, &m_classObject);
}

//----------------------------------------------------------------------------------------------------------------------
// ClassUserDataClassDefinition
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline SQInteger ClassUserDataClassDefinition<ClassType, BaseClassType>::DefaultConstructor(HSQUIRRELVM vm)
{
  typedef internal::CopyableSpecialisation<traits::IsCopyable<ClassType>::kValue> CopyableSpecialisation;
  return CopyableSpecialisation::template ClassUserDataConstructor<ClassType>(vm);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline SQInteger ClassUserDataClassDefinition<ClassType, BaseClassType>::DefaultReleaseHook(
  SQUserPointer up,
  SQInteger     SQBIND_UNUSED(size))
{
  if (!traits::IsPod<ClassType>::kValue)
  {
    ClassType *instance = static_cast<ClassType *>(up);
    (void)instance; // line below isn't enough to make it think it is referenced.
    instance->~ClassType();
  }

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline ClassUserDataClassDefinition<ClassType, BaseClassType>::ClassUserDataClassDefinition(
  HSQUIRRELVM   vm,
  SQInteger     ownerIndex,
  const SQChar *name)
: ClassDefinitionBase<ClassType, BaseClassType>(vm, ownerIndex, name)
{
  size_t classUserDataSize = sizeof(ClassType);
  if (traits::IsAligned<ClassType>::kIsAligned)
  {
    // need to ensure there is room to align the instance if necessary
    //
    classUserDataSize += traits::IsAligned<ClassType>::kAlignment;
  }
  // needs to be fully qualified to prevent there are no arguments to 'SetUserDataSize' that depend
  // on a template parameter, so a declaration of 'SetUserDataSize' must be available
  //
  ClassDefinitionBase<ClassType, BaseClassType>::SetUserDataSize(classUserDataSize);

  if (!traits::IsPod<ClassType>::kValue)
  {
    sqb::ClassTypeTag<ClassType>* classTypeTag = sqb::ClassTypeTag<ClassType>::Get();
    classTypeTag->SetReleaseHook(&DefaultReleaseHook);
  }

  FunctionOptions options;
  if (traits::IsCopyable<ClassType>::kValue)
  {
    options.m_paramCheckCount = -1;
    options.m_typeMaskString = _SC("xx");
    
  }
  else
  {
    options.m_paramCheckCount = 1;
    options.m_typeMaskString = _SC("x");
  }
  ClassDefinitionBase<ClassType, BaseClassType>::Constructor(&DefaultConstructor, options);
}

//----------------------------------------------------------------------------------------------------------------------
// SqMallocClassDefinition
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline SQInteger SqMallocClassDefinition<ClassType, BaseClassType>::DefaultConstructor(HSQUIRRELVM vm)
{
  typedef internal::CopyableSpecialisation<traits::IsCopyable<ClassType>::kValue> CopyableSpecialisation;
  return CopyableSpecialisation::template SqMallocConstructor<ClassType>(vm);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline SQInteger SqMallocClassDefinition<ClassType, BaseClassType>::DefaultReleaseHook(
  SQUserPointer up,
  SQInteger     size)
{
  if (!traits::IsPod<ClassType>::kValue)
  {
    ClassType *instance = static_cast<ClassType *>(up);
    (void)instance; // line below isn't enough to make it think it is referenced.
    instance->~ClassType();
  }

  sq_free(up, size);

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline SqMallocClassDefinition<ClassType, BaseClassType>::SqMallocClassDefinition(
  HSQUIRRELVM   vm,
  SQInteger     ownerIndex,
  const SQChar *name)
: ClassDefinitionBase<ClassType, BaseClassType>(vm, ownerIndex, name)
{
  // Classes bound with SqMalloc currently do not support alignment
  //
  SQBIND_ASSERT(!traits::IsAligned<ClassType>::kIsAligned);

  if (!traits::IsPod<ClassType>::kValue)
  {
    sqb::ClassTypeTag<ClassType>* classTypeTag = sqb::ClassTypeTag<ClassType>::Get();
    classTypeTag->SetReleaseHook(&DefaultReleaseHook);
  }

  FunctionOptions options;
  if (traits::IsCopyable<ClassType>::kValue)
  {
    options.m_paramCheckCount = -1;
    options.m_typeMaskString = _SC("xx");
  }
  else
  {
    options.m_paramCheckCount = 1;
    options.m_typeMaskString = _SC("x");
  }
  ClassDefinitionBase<ClassType, BaseClassType>::Constructor(&DefaultConstructor, options);
}

//----------------------------------------------------------------------------------------------------------------------
// NoConstructorClassDefinition
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline NoConstructorClassDefinition<ClassType, BaseClassType>::NoConstructorClassDefinition(
  HSQUIRRELVM   vm,
  SQInteger     ownerIndex,
  const SQChar *name)
: ClassDefinitionBase<ClassType, BaseClassType>(vm, ownerIndex, name)
{
}

//----------------------------------------------------------------------------------------------------------------------
// ClassDefinition
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline ClassDefinition<ClassType, BaseClassType>::ClassDefinition(
  HSQUIRRELVM   vm,
  SQInteger     ownerIndex,
  const SQChar *name)
: ClassUserDataClassDefinition<ClassType, BaseClassType>(vm, ownerIndex, name)
{
}

//----------------------------------------------------------------------------------------------------------------------
// internal::CopyableSpecialisation
//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ClassType>
inline SQInteger internal::CopyableSpecialisation<true>::ClassUserDataConstructor(HSQUIRRELVM vm)
{
  StackHandler stack(vm);

  ClassTypeTag<ClassType>* classTypeTag = ClassTypeTag<ClassType>::Get();

  SQUserPointer userPointer;
  SQBIND_ASSERT(sq_gettype(vm, 1) == OT_INSTANCE);
  sq_getinstanceup(vm, 1, &userPointer, nullptr);
  SQBIND_ASSERT_MSG(userPointer != nullptr, "new instance user pointer was null, did you forget to call sq_setclassudsize?");

  // align the instance if required
  //
  if (traits::IsAligned<ClassType>::kIsAligned)
  {
    const ptrdiff_t pointer = reinterpret_cast<ptrdiff_t>(userPointer);
    const ptrdiff_t alignment = static_cast<ptrdiff_t>(traits::IsAligned<ClassType>::kAlignment);
    userPointer = reinterpret_cast<SQUserPointer>((pointer + (alignment - 1)) & ~(alignment - 1));
    sq_setinstanceup(vm, 1, userPointer);
  }

  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  sq_setreleasehook(vm, 1, hook);

  if (stack.GetParamCount() == 2)
  {
    const ClassType *original = static_cast<const ClassType *>(stack.GetInstanceMatchTypeTag(2, classTypeTag));
    if (original)
    {
      // instance is for inspecting with a debugger
      //
      ClassType *instance = new (userPointer) ClassType(*original);
      (void)instance;

      return 1;
    }

    return stack.ThrowParamError(2, sqb::TypeInfo<ClassType>().m_typeName);
  }

  // instance is for inspecting with a debugger
  //
  ClassType *instance = new (userPointer) ClassType;
  (void)instance;

  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ClassType>
inline SQInteger internal::CopyableSpecialisation<false>::ClassUserDataConstructor(
  HSQUIRRELVM vm)
{
  StackHandler stack(vm);

  ClassTypeTag<ClassType>* classTypeTag = ClassTypeTag<ClassType>::Get();

  SQUserPointer userPointer;
  SQBIND_ASSERT(sq_gettype(vm, 1) == OT_INSTANCE);
  sq_getinstanceup(vm, 1, &userPointer, nullptr);
  SQBIND_ASSERT_MSG(userPointer != nullptr, "new instance user pointer was null, did you forget to call sq_setclassudsize?");

  // align the instance if required
  //
  if (traits::IsAligned<ClassType>::kIsAligned)
  {
    const ptrdiff_t pointer = reinterpret_cast<ptrdiff_t>(userPointer);
    const ptrdiff_t alignment = static_cast<ptrdiff_t>(traits::IsAligned<ClassType>::kAlignment);
    userPointer = reinterpret_cast<SQUserPointer>((pointer + (alignment - 1)) & ~(alignment - 1));
    sq_setinstanceup(vm, 1, userPointer);
  }

  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  sq_setreleasehook(vm, 1, hook);

  // instance is for inspecting with a debugger
  //
  ClassType *instance = new (userPointer) ClassType;
  (void)instance;

  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ClassType>
inline SQInteger internal::CopyableSpecialisation<true>::SqMallocConstructor(HSQUIRRELVM vm)
{
  StackHandler stack(vm);

  ClassTypeTag<ClassType>* classTypeTag = ClassTypeTag<ClassType>::Get();

  SQBIND_ASSERT(sq_gettype(vm, 1) == OT_INSTANCE);
  void *memory = sq_malloc(sizeof(ClassType));

  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  sq_setreleasehook(vm, 1, hook);

  if (stack.GetParamCount() == 2)
  {
    const ClassType *original = static_cast<const ClassType *>(stack.GetInstanceMatchTypeTag(2, classTypeTag));
    if (original)
    {
      ClassType *instance = new (memory) ClassType(*original);
      sq_setinstanceup(vm, 1, instance);

      return 1;
    }

    // make sure we don't leak memory
    //
    sq_free(memory, sizeof(ClassType));
    sq_setinstanceup(vm, 1, nullptr);
    sq_setreleasehook(vm, 1, nullptr);

    return stack.ThrowParamError(2, sqb::TypeInfo<ClassType>().m_typeName);
  }

  ClassType *instance = new (memory) ClassType;
  sq_setinstanceup(vm, 1, instance);

  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ClassType>
inline SQInteger internal::CopyableSpecialisation<false>::SqMallocConstructor(HSQUIRRELVM vm)
{
  StackHandler stack(vm);

  ClassTypeTag<ClassType>* classTypeTag = ClassTypeTag<ClassType>::Get();

  SQBIND_ASSERT(sq_gettype(vm, 1) == OT_INSTANCE);
  void *memory = sq_malloc(sizeof(ClassType));

  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  sq_setreleasehook(vm, 1, hook);

  ClassType *instance = new (memory) ClassType;
  sq_setinstanceup(vm, 1, instance);

  return 1;
}

} // namespace sqb

#if defined(SQBIND_COMPILER_MSVC)
#pragma warning(pop)
#endif

// <--- back to sqbClassDefinition.h

// <--- back to SquirrelBind.h
// ---- #include <sqbind/sqbScopedArrayAccess.h>
// ---> including sqbScopedArrayAccess.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqbScopedArrayAccess.h
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbAssert.h>
// ---> including sqbAssert.h
// <--- back to sqbScopedArrayAccess.h
// ---- #include <sqbind/sqbClassTypeTag.h>
// ---> including sqbClassTypeTag.h
// <--- back to sqbScopedArrayAccess.h
// ---- #include <sqbind/sqbSquirrelObject.h>
// ---> including sqbSquirrelObject.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqbSquirrelObject.h
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbAssert.h>
// ---> including sqbAssert.h
// <--- back to sqbSquirrelObject.h
// ---- #include <sqbind/sqbStackUtils.h>
// ---> including sqbStackUtils.h
// <--- back to sqbSquirrelObject.h
// ---- #include <sqbind/sqbTypeInfo.h>
// ---> including sqbTypeInfo.h
// <--- back to sqbSquirrelObject.h
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief 
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API SquirrelObject
{
public:
  static SquirrelObject kNullObject;

  SquirrelObject();
  SquirrelObject(HSQUIRRELVM vm, SQInteger index);
  SquirrelObject(HSQUIRRELVM vm, HSQOBJECT object);
  SquirrelObject(const SquirrelObject& rhs);

  ~SquirrelObject();

  operator HSQOBJECT () const;

  const SquirrelObject &operator = (const SquirrelObject &rhs);

  HSQOBJECT GetObject() const;
  HSQUIRRELVM GetVM() const;

  void Reference(HSQUIRRELVM vm, SQInteger index);
  void Reference(HSQUIRRELVM vm, HSQOBJECT object);
  void Reference(const SquirrelObject &object);
  void Release();

  SQObjectType GetType() const;
  const SQChar *GetTypeName() const;

  bool IsBool() const;
  bool IsFloat() const;
  bool IsInteger() const;
  bool IsNull() const;
  bool IsString() const;
  bool IsTable() const;

  bool          AsBool() const;
  SQFloat       AsFloat() const;
  SQInteger     AsInteger() const;
  const SQChar *AsString() const;

protected:
  HSQUIRRELVM m_vm;
  HSQOBJECT   m_object;
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<SquirrelObject>
{
  enum
  {
    kTypeID = kScriptVarTypeObject,
    kTypeSize = sizeof(SquirrelObject),
    kTypeMask = '.',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

/// \brief Overload of Push stack utility function for SquirrelObject.
SQRESULT Push(HSQUIRRELVM vm, SquirrelObject value);

/// \brief Overload of Match stack utility function for SquirrelObject.
bool Match(TypeWrapper<SquirrelObject> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \brief Overload of Get stack utility function for SquirrelObject.
SquirrelObject Get(TypeWrapper<SquirrelObject> wrapper, HSQUIRRELVM vm, SQInteger index);

} // namespace sqb

// ---- #include <sqbind/sqbSquirrelObject.inl>
// ---> including sqbSquirrelObject.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// SquirrelObject
//----------------------------------------------------------------------------------------------------------------------
inline SquirrelObject::SquirrelObject()
: m_vm(nullptr)
{
  sq_resetobject(&m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelObject::SquirrelObject(HSQUIRRELVM vm, SQInteger index)
{
  m_vm = vm;
  SQRESULT result = sq_getstackobj(vm, index, &m_object);
  SQBIND_ASSERT_SUCCEEDED(result);
  sq_addref(m_vm, &m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelObject::SquirrelObject(HSQUIRRELVM vm, HSQOBJECT object)
{
  m_vm = vm;
  m_object = object;
  sq_addref(vm, &m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelObject::SquirrelObject(const SquirrelObject& rhs)
: m_vm(rhs.m_vm),
  m_object(rhs.m_object)
{
  if (m_vm)
  {
    sq_addref(m_vm, &m_object);
  }
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelObject::~SquirrelObject()
{
  // release the object reference
  //
  if (m_vm)
  {
    sq_release(m_vm, &m_object);
  }
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelObject::operator HSQOBJECT () const
{
  return m_object;
}

//----------------------------------------------------------------------------------------------------------------------
inline HSQOBJECT SquirrelObject::GetObject() const
{
  return m_object;
}

//----------------------------------------------------------------------------------------------------------------------
inline HSQUIRRELVM SquirrelObject::GetVM() const
{
  return m_vm;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType SquirrelObject::GetType() const
{
  return sq_type(m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline const SQChar *SquirrelObject::GetTypeName() const
{
  SQObjectType objectType = sq_type(m_object);
  return RawTypeToTypeName(objectType);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelObject::IsBool() const
{
  return sq_isbool(m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelObject::IsFloat() const
{
  return sq_isfloat(m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelObject::IsInteger() const
{
  return sq_isinteger(m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelObject::IsNull() const
{
  return sq_isnull(m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelObject::IsString() const
{
  return sq_isstring(m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelObject::IsTable() const
{
  return sq_istable(m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelObject::AsBool() const
{
  return (sq_objtobool(&m_object) == SQTrue);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQFloat SquirrelObject::AsFloat() const
{
  return sq_objtofloat(&m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger SquirrelObject::AsInteger() const
{
  return sq_objtointeger(&m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline const SQChar *SquirrelObject::AsString() const
{
  return sq_objtostring(&m_object);
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<SquirrelObject>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<SquirrelObject>::TypeInfo()
: m_typeName(_SC("object"))
{
}

//----------------------------------------------------------------------------------------------------------------------
// Push
//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, SquirrelObject value)
{
  sq_pushobject(vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
// Match
//----------------------------------------------------------------------------------------------------------------------
inline bool Match(
  TypeWrapper<SquirrelObject> SQBIND_UNUSED(wrapper),
  HSQUIRRELVM                 SQBIND_UNUSED(vm),
  SQInteger                   SQBIND_UNUSED(index))
{
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
// Get
//----------------------------------------------------------------------------------------------------------------------
inline SquirrelObject Get(TypeWrapper<SquirrelObject> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SquirrelObject value(vm, index);
  return value;
}

} // namespace sqb

// <--- back to sqbSquirrelObject.h

// <--- back to sqbScopedArrayAccess.h
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API ScopedArrayAccess
{
public:
  ScopedArrayAccess(HSQUIRRELVM vm, HSQOBJECT object);
  ScopedArrayAccess(const SquirrelObject &object);

  ~ScopedArrayAccess();

  /// \brief Return the size of the array.
  SQInteger GetSize() const;

  /// \brief Resize the array to size elements.
  void Resize(SQInteger size);

  /// \brief Clears the contents of the array.
  void Clear();

  /// \brief Get the type of the element at index.
  SQObjectType GetElementType(SQInteger index) const;

  template<typename InstanceType>
  bool IsElementInstanceOfType(SQInteger index) const;

  /// \brief Append a new element to the end of the array.
  template<typename ValueType>
  void AppendElement(ValueType value);

  /// \brief Insert a new element at position index of the array.
  template<typename ValueType>
  void InsertElement(SQInteger index, ValueType value);

  /// \brief Removes an element from the end of the array.
  void PopElement();

  /// \brief Removes an element from the end of the array returning the removed value.
  template<typename ValueType>
  const ValueType &PopElement();

  /// \brief Removes an element from the array at the index given.
  void RemoveElement(SQInteger index);

  /// \brief Get the element at the given index.
  template<typename ValueType>
  const ValueType &GetElement(SQInteger index) const;

  /// \brief Set the element at the given index.
  template<typename ValueType>
  void SetElement(SQInteger index, ValueType value);

protected:
  HSQUIRRELVM m_vm;
  HSQOBJECT   m_object;
};

} // namespace sqb

// ---- #include <sqbind/sqbScopedArrayAccess.inl>
// ---> including sqbScopedArrayAccess.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Assert to check that the object is on the top of the stack.
//----------------------------------------------------------------------------------------------------------------------
#if SQBIND_ASSERTS_ENABLED
# define SQBIND_ASSERT_ARRAY_SCOPE_VALID() \
  SQBIND_ASSERT(sq_gettype(m_vm, -1) == OT_ARRAY); \
  sq_pushobject(m_vm, m_object); \
  SQBIND_ASSERT(sq_cmp(m_vm) == 0); \
  sq_poptop(m_vm)
#else
# define SQBIND_ASSERT_ARRAY_SCOPE_VALID()
#endif

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// ScopedArrayAccess
//----------------------------------------------------------------------------------------------------------------------
inline ScopedArrayAccess::ScopedArrayAccess(HSQUIRRELVM vm, HSQOBJECT object)
: m_vm(vm),
  m_object(object)
{
  SQBIND_ASSERT(sq_type(m_object) == OT_ARRAY);
  sq_pushobject(m_vm, m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline ScopedArrayAccess::ScopedArrayAccess(const SquirrelObject &object)
: m_vm(object.GetVM()),
  m_object(object.GetObject())
{
  SQBIND_ASSERT(sq_type(m_object) == OT_ARRAY);
  sq_pushobject(m_vm, m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline ScopedArrayAccess::~ScopedArrayAccess()
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  sq_poptop(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger ScopedArrayAccess::GetSize() const
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  return sq_getsize(m_vm, -1);
}

//----------------------------------------------------------------------------------------------------------------------
inline void ScopedArrayAccess::Resize(SQInteger size)
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  SQRESULT result = sq_arrayresize(m_vm, -1, size);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
inline void ScopedArrayAccess::Clear()
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  SQRESULT result = sq_clear(m_vm, -1);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType ScopedArrayAccess::GetElementType(SQInteger index) const
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  sq_pushinteger(m_vm, index);
  SQRESULT result = sq_rawget(m_vm, -2);
  SQBIND_ASSERT_SUCCEEDED(result);
  SQObjectType type = sq_gettype(m_vm, -1);
  sq_poptop(m_vm);
  return type;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
bool ScopedArrayAccess::IsElementInstanceOfType(SQInteger index) const
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  sq_pushinteger(m_vm, index);
  SQRESULT result = sq_rawget(m_vm, -2);
  SQBIND_ASSERT_SUCCEEDED(result);

  SQUserPointer up;
  SQUserPointer typetag = ClassTypeTag<ClassType>::Get();
  result = sq_getinstanceup(m_vm, -1, &up, typetag);

  sq_poptop(m_vm);
  return SQ_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline void ScopedArrayAccess::AppendElement(ValueType value)
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  SQRESULT result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = sq_arrayappend(m_vm, -2);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline void ScopedArrayAccess::InsertElement(SQInteger index, ValueType value)
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  SQBIND_ASSERT(index >= 0);
  SQBIND_ASSERT(index <= sq_getsize(m_vm, -1));
  SQRESULT result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = sq_arrayinsert(m_vm, -2, index);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
inline void ScopedArrayAccess::PopElement()
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  SQRESULT result = sq_arraypop(m_vm, -2, SQFalse);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline const ValueType &ScopedArrayAccess::PopElement()
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  SQRESULT result = sq_arraypop(m_vm, -2, SQTrue);
  SQBIND_ASSERT_SUCCEEDED(result);
  const ValueType &value = Get(TypeWrapper<ValueType>(), m_vm, -1);
  sq_poptop(m_vm);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline void ScopedArrayAccess::RemoveElement(SQInteger index)
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  SQBIND_ASSERT(index >= 0);
  SQBIND_ASSERT(index < sq_getsize(m_vm, -1));
  SQRESULT result = sq_arrayremove(m_vm, -1, index);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline void ScopedArrayAccess::SetElement(SQInteger key, ValueType value)
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  sq_pushinteger(m_vm, key);
  SQRESULT result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = sq_rawset(m_vm, -3);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline const ValueType &ScopedArrayAccess::GetElement(SQInteger key) const
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  sq_pushinteger(m_vm, key);
  SQRESULT result = sq_rawget(m_vm, -2);
  SQBIND_ASSERT_SUCCEEDED(result);
  const ValueType &value = Get(TypeWrapper<ValueType>(), m_vm, -1);
  sq_poptop(m_vm);
  return value;
}

} // namespace sqb

// <--- back to sqbScopedArrayAccess.h

// <--- back to SquirrelBind.h
// ---- #include <sqbind/sqbScopedTableAccess.h>
// ---> including sqbScopedTableAccess.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqbScopedTableAccess.h
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbAssert.h>
// ---> including sqbAssert.h
// <--- back to sqbScopedTableAccess.h
// ---- #include <sqbind/sqbSquirrelObject.h>
// ---> including sqbSquirrelObject.h
// <--- back to sqbScopedTableAccess.h
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API ScopedTableAccess
{
public:
  ScopedTableAccess(HSQUIRRELVM vm, HSQOBJECT object);
  ScopedTableAccess(const SquirrelObject &object);

  ~ScopedTableAccess();

  /// \brief Return the size of the array.
  SQInteger GetSize() const;

  /// \brief Clears the contents of the array.
  void Clear();

  template<typename KeyType>
  bool SlotExists(KeyType key) const;
  bool SlotExists(const SQChar *key, SQInteger keyLength) const;

  template<typename KeyType>
  bool RawSlotExists(KeyType key) const;
  bool RawSlotExists(const SQChar *key, SQInteger keyLength) const;

  template<typename KeyType>
  SQObjectType GetSlotType(KeyType key) const;
  SQObjectType GetSlotType(const SQChar *key, SQInteger keyLength) const;

  template<typename KeyType>
  SQObjectType RawGetSlotType(KeyType key) const;
  SQObjectType RawGetSlotType(const SQChar *key, SQInteger keyLength) const;

  /// \brief .
  template<typename KeyType, typename ValueType>
  SQRESULT NewSlot(KeyType key, ValueType value);
  template<typename ValueType>
  SQRESULT NewSlot(const SQChar *key, SQInteger keyLength, ValueType value);

  template<typename KeyType>
  SQRESULT NewSlotNewArray(KeyType key, SQInteger arraySize);
  SQRESULT NewSlotNewArray(const SQChar *key, SQInteger keyLength, SQInteger arraySize);

  template<typename KeyType>
  SQRESULT NewSlotNewTable(KeyType key);
  SQRESULT NewSlotNewTable(const SQChar *key, SQInteger keyLength);

  /// \brief .
  template<typename KeyType>
  SQRESULT DeleteSlot(KeyType key);
  template<typename KeyType, typename ValueType>
  SQRESULT DeleteSlot(KeyType key, ValueType *value = nullptr);

  /// \brief .
  template<typename KeyType>
  SQRESULT RawDeleteSlot(KeyType key);
  template<typename KeyType, typename ValueType>
  SQRESULT RawDeleteSlot(KeyType key, ValueType *value);

  /// \brief Get the value at the given index, this will invoke the tables delegate if there is one.
  template<typename KeyType, typename ValueType>
  SQRESULT GetSlot(KeyType key, ValueType *value) const;
  template<typename ValueType>
  SQRESULT GetSlot(const SQChar *key, SQInteger keyLength, ValueType *value) const;

  /// \brief Get the value at the given index.
  template<typename KeyType, typename ValueType>
  SQRESULT RawGetSlot(KeyType key, ValueType *value) const;
  template<typename ValueType>
  SQRESULT RawGetSlot(const SQChar *key, SQInteger keyLength, ValueType *value) const;

  /// \brief Set the value at the given index, this will invoke the tables delegate if there is one.
  ///   If the slot does not exist then this call will fail.
  template<typename KeyType, typename ValueType>
  SQRESULT SetSlot(KeyType key, ValueType value);
  template<typename ValueType>
  SQRESULT SetSlot(const SQChar *key, SQInteger keyLength, ValueType value);

  template<typename KeyType>
  SQRESULT SetSlotNewArray(KeyType key, SQInteger arraySize);
  SQRESULT SetSlotNewArray(const SQChar *key, SQInteger keyLength, SQInteger arraySize);

  template<typename KeyType>
  SQRESULT SetSlotNewTable(KeyType key);
  SQRESULT SetSlotNewTable(const SQChar *key, SQInteger keyLength);

  /// \brief Set the value at the given index, this bypasses invoking the table delegate.
  ///   If the slot doesn't exist it will be created.
  template<typename KeyType, typename ValueType>
  SQRESULT RawSetSlot(KeyType key, ValueType value);
  template<typename ValueType>
  SQRESULT RawSetSlot(const SQChar *key, SQInteger keyLength, ValueType value);

  /// \brief Creates a new table for the given index, this bypasses invoking the table delegate.
  ///   If the slot doesn't exist it will be created.
  template<typename KeyType>
  SQRESULT RawSetSlotNewArray(KeyType key, SQInteger arrayLength);
  SQRESULT RawSetSlotNewArray(const SQChar *key, SQInteger keyLength, SQInteger arrayLength);

  /// \brief Creates a new table for the given index, this bypasses invoking the table delegate.
  ///   If the slot doesn't exist it will be created.
  template<typename KeyType>
  SQRESULT RawSetSlotNewTable(KeyType key);
  SQRESULT RawSetSlotNewTable(const SQChar *key, SQInteger keyLength);

protected:
  HSQUIRRELVM m_vm;
  HSQOBJECT   m_object;
};

} // namespace sqb

// ---- #include <sqbind/sqbScopedTableAccess.inl>
// ---> including sqbScopedTableAccess.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Assert to check that the object is on the top of the stack.
//----------------------------------------------------------------------------------------------------------------------
#if SQBIND_ASSERTS_ENABLED
# define SQBIND_ASSERT_TABLE_SCOPE_VALID() \
  SQBIND_ASSERT(sq_gettype(m_vm, -1) == OT_TABLE); \
  sq_pushobject(m_vm, m_object); \
  SQBIND_ASSERT(sq_cmp(m_vm) == 0); \
  sq_poptop(m_vm)
#else
# define SQBIND_ASSERT_TABLE_SCOPE_VALID()
#endif

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// ScopedTableAccess
//----------------------------------------------------------------------------------------------------------------------
inline ScopedTableAccess::ScopedTableAccess(HSQUIRRELVM vm, HSQOBJECT object)
: m_vm(vm),
  m_object(object)
{
  SQBIND_ASSERT(sq_type(m_object) == OT_TABLE);
  sq_pushobject(m_vm, m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline ScopedTableAccess::ScopedTableAccess(const SquirrelObject &object)
: m_vm(object.GetVM()),
  m_object(object.GetObject())
{
  SQBIND_ASSERT(sq_type(m_object) == OT_TABLE);
  sq_pushobject(m_vm, m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline ScopedTableAccess::~ScopedTableAccess()
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_poptop(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger ScopedTableAccess::GetSize() const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  return sq_getsize(m_vm, -1);
}

//----------------------------------------------------------------------------------------------------------------------
inline void ScopedTableAccess::Clear()
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = sq_clear(m_vm, -1);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline bool ScopedTableAccess::SlotExists(KeyType key) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  if (SQ_SUCCEEDED(sq_get(m_vm, -2)))
  {
    sq_poptop(m_vm);
    return true;
  }
  else
  {
    return false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
inline bool ScopedTableAccess::SlotExists(const SQChar *key, SQInteger keyLength) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  if (SQ_SUCCEEDED(sq_get(m_vm, -2)))
  {
    sq_poptop(m_vm);
    return true;
  }
  else
  {
    return false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline bool ScopedTableAccess::RawSlotExists(KeyType key) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  if (SQ_SUCCEEDED(sq_rawget(m_vm, -2)))
  {
    sq_poptop(m_vm);
    return true;
  }
  else
  {
    return false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
inline bool ScopedTableAccess::RawSlotExists(const SQChar *key, SQInteger keyLength) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  if (SQ_SUCCEEDED(sq_rawget(m_vm, -2)))
  {
    sq_poptop(m_vm);
    return true;
  }
  else
  {
    return false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQObjectType ScopedTableAccess::GetSlotType(KeyType key) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);

  if (SQ_SUCCEEDED(sq_get(m_vm, -2)))
  {
    SQObjectType type = sq_gettype(m_vm, -1);
    sq_poptop(m_vm);
    return type;
  }

  return OT_NULL;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType ScopedTableAccess::GetSlotType(const SQChar *key, SQInteger keyLength) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);

  if (SQ_SUCCEEDED(sq_get(m_vm, -2)))
  {
    SQObjectType type = sq_gettype(m_vm, -1);
    sq_poptop(m_vm);
    return type;
  }

  return OT_NULL;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQObjectType ScopedTableAccess::RawGetSlotType(KeyType key) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);

  if (SQ_SUCCEEDED(sq_rawget(m_vm, -2)))
  {
    SQObjectType type = sq_gettype(m_vm, -1);
    sq_poptop(m_vm);
    return type;
  }

  return OT_NULL;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType ScopedTableAccess::RawGetSlotType(const SQChar *key, SQInteger keyLength) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);

  if (SQ_SUCCEEDED(sq_rawget(m_vm, -2)))
  {
    SQObjectType type = sq_gettype(m_vm, -1);
    sq_poptop(m_vm);
    return type;
  }

  return OT_NULL;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType, typename ValueType>
inline SQRESULT ScopedTableAccess::NewSlot(KeyType key, ValueType value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return sq_newslot(m_vm, -3, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline SQRESULT ScopedTableAccess::NewSlot(const SQChar *key, SQInteger keyLength, ValueType value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  SQRESULT result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return sq_newslot(m_vm, -3, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::NewSlotNewArray(KeyType key, SQInteger arraySize)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  sq_newarray(m_vm, arraySize);
  return sq_newslot(m_vm, -3, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT ScopedTableAccess::NewSlotNewArray(const SQChar *key, SQInteger keyLength, SQInteger arraySize)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  sq_newarray(m_vm, arraySize);
  return sq_newslot(m_vm, -3, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::NewSlotNewTable(KeyType key)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  sq_newtable(m_vm);
  return sq_newslot(m_vm, -3, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT ScopedTableAccess::NewSlotNewTable(const SQChar *key, SQInteger keyLength)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  sq_newtable(m_vm);
  return sq_newslot(m_vm, -3, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::DeleteSlot(KeyType key)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  return sq_deleteslot(m_vm, -2, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType, typename ValueType>
inline SQRESULT ScopedTableAccess::DeleteSlot(KeyType key, ValueType *value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  if (value != nullptr)
  {
    result = sq_deleteslot(m_vm, -2, SQTrue);
    if (SQ_SUCCEEDED(result))
    {
      *value = Get(TypeWrapper<ValueType>(), m_vm, -1);
      sq_poptop(m_vm);
    }
  }
  else
  {
    result = sq_deleteslot(m_vm, -2, SQFalse);
  }

  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::RawDeleteSlot(KeyType key)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  return sq_deleteslot(m_vm, -2, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType, typename ValueType>
inline SQRESULT ScopedTableAccess::RawDeleteSlot(KeyType key, ValueType *value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);

  result = sq_deleteslot(m_vm, -2, SQTrue);
  if (SQ_SUCCEEDED(result))
  {
    *value = Get(TypeWrapper<ValueType>(), m_vm, -1);
    sq_poptop(m_vm);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType, typename ValueType>
inline SQRESULT ScopedTableAccess::GetSlot(KeyType key, ValueType *value) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = sq_get(m_vm, -2);
  if (SQ_SUCCEEDED(result))
  {
    *value = Get(TypeWrapper<ValueType>(), m_vm, -1);
    sq_poptop(m_vm);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline SQRESULT ScopedTableAccess::GetSlot(const SQChar *key, SQInteger keyLength, ValueType *value) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  SQRESULT result = sq_get(m_vm, -2);
  if (SQ_SUCCEEDED(result))
  {
    *value = Get(TypeWrapper<ValueType>(), m_vm, -1);
    sq_poptop(m_vm);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType, typename ValueType>
inline SQRESULT ScopedTableAccess::RawGetSlot(KeyType key, ValueType *value) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = sq_rawget(m_vm, -2);
  if (SQ_SUCCEEDED(result))
  {
    *value = Get(TypeWrapper<ValueType>(), m_vm, -1);
    sq_poptop(m_vm);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline SQRESULT ScopedTableAccess::RawGetSlot(const SQChar *key, SQInteger keyLength, ValueType *value) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  SQRESULT result = sq_rawget(m_vm, -2);
  if (SQ_SUCCEEDED(result))
  {
    *value = Get(TypeWrapper<ValueType>(), m_vm, -1);
    sq_poptop(m_vm);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType, typename ValueType>
inline SQRESULT ScopedTableAccess::SetSlot(KeyType key, ValueType value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = sq_set(m_vm, -3);
  if (SQ_FAILED(result))
  {
    sq_pop(m_vm, 2);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline SQRESULT ScopedTableAccess::SetSlot(const SQChar *key, SQInteger keyLength, ValueType value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  SQRESULT result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = sq_set(m_vm, -3);
  if (SQ_FAILED(result))
  {
    sq_pop(m_vm, 2);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::SetSlotNewArray(KeyType key, SQInteger arraySize)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  sq_newarray(m_vm, arraySize);
  result = sq_set(m_vm, -3);
  if (SQ_FAILED(result))
  {
    sq_pop(m_vm, 2);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT ScopedTableAccess::SetSlotNewArray(const SQChar *key, SQInteger keyLength, SQInteger arraySize)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  sq_newarray(m_vm, arraySize);
  SQRESULT result = sq_set(m_vm, -3);
  if (SQ_FAILED(result))
  {
    sq_pop(m_vm, 2);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::SetSlotNewTable(KeyType key)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  sq_newtable(m_vm);
  result = sq_set(m_vm, -3);
  if (SQ_FAILED(result))
  {
    sq_pop(m_vm, 2);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT ScopedTableAccess::SetSlotNewTable(const SQChar *key, SQInteger keyLength)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  sq_newtable(m_vm);
  SQRESULT result = sq_set(m_vm, -3);
  if (SQ_FAILED(result))
  {
    sq_pop(m_vm, 2);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType, typename ValueType>
inline SQRESULT ScopedTableAccess::RawSetSlot(KeyType key, ValueType value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return sq_rawset(m_vm, -3);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline SQRESULT ScopedTableAccess::RawSetSlot(const SQChar *key, SQInteger keyLength, ValueType value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  SQRESULT result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return sq_rawset(m_vm, -3);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::RawSetSlotNewArray(KeyType key, SQInteger arrayLength)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  sq_newarray(m_vm, arrayLength);
  return sq_rawset(m_vm, -3);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT ScopedTableAccess::RawSetSlotNewArray(const SQChar *key, SQInteger keyLength, SQInteger arrayLength)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  sq_newarray(m_vm, arrayLength);
  return sq_rawset(m_vm, -3);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::RawSetSlotNewTable(KeyType key)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  sq_newtable(m_vm);
  return sq_rawset(m_vm, -3);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT ScopedTableAccess::RawSetSlotNewTable(const SQChar *key, SQInteger keyLength)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  sq_newtable(m_vm);
  return sq_rawset(m_vm, -3);
}

} // namespace sqb

// <--- back to sqbScopedTableAccess.h

// <--- back to SquirrelBind.h
// ---- #include <sqbind/sqbSquirrelFunction.h>
// ---> including sqbSquirrelFunction.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqbSquirrelFunction.h
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbAssert.h>
// ---> including sqbAssert.h
// <--- back to sqbSquirrelFunction.h
// ---- #include <sqbind/sqbScopedArrayAccess.h>
// ---> including sqbScopedArrayAccess.h
// <--- back to sqbSquirrelFunction.h
// ---- #include <sqbind/sqbSquirrelObject.h>
// ---> including sqbSquirrelObject.h
// <--- back to sqbSquirrelFunction.h
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
struct ExecutionOptions;

//----------------------------------------------------------------------------------------------------------------------
/// \brief 
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API SquirrelFunction
{
public:
  SquirrelFunction(HSQUIRRELVM vm);
  SquirrelFunction(HSQUIRRELVM vm, SQInteger index);
  SquirrelFunction(HSQUIRRELVM vm, HSQOBJECT function);
  SquirrelFunction(const SquirrelObject &function);

  /// \brief returns the previously managed vm.
  HSQUIRRELVM SetVM(HSQUIRRELVM vm);
  /// \brief Get the vm.
  HSQUIRRELVM GetVM() const;

  /// \note Setting the function does not affect the environment or arguments array.
  void SetFunction(SQInteger index);
  void SetFunction(HSQOBJECT function);

  /// \brief Set the environment to use when calling this function. By default the
  ///   environment is the root table of the function's vm, you only need to call this
  ///   function if you would like to use a different environment.
  void SetEnvironment(SQInteger index);
  void SetEnvironment(HSQOBJECT environment);

  /// \brief Returns the current number of arguments bound to this function instance.
  SQInteger GetArgumentCount() const;

  /// \brief Clears all currently bound arguments.
  void ClearArguments();

  /// \brief Adds an argument to be passed to the function when called.
  template<typename ArgumentType>
  void AddArgument(ArgumentType argument);

  template<typename ArgumentType>
  void InsertArgument(SQInteger index, ArgumentType argument);

  /// \brief Overwrites an existing function argument. This will assert if you try an overwrite a
  ///   non-existant argument.
  template<typename ArgumentType>
  void OverwriteArgument(SQInteger index, ArgumentType argument);

  /// \brief Remove an existing function argument. This will assert if you try an remove a
  ///   non-existant argument.
  void RemoveArgument(SQInteger index);

  /// \brief Call the function with the chosen environment and arguments, this can be called repeatedly
  ///   without the need to reset the arguments.
  SQRESULT Call();
  SQRESULT Call(const ExecutionOptions &options);

  /// \brief Get the type of the value returned by the function. If the function returned nothing
  ///   this will return OT_NULL.
  SQObjectType GetReturnType() const;

  /// \brief Get the value returned by the last call. This will be replaced every time the function is called.
  template<typename ResultType>
  const ResultType& GetReturnValue() const;

protected:
  SquirrelObject  m_function;
  SquirrelObject  m_environment;
  SquirrelObject  m_arguments;
  SquirrelObject  m_returnValue;
  HSQUIRRELVM     m_vm;
};

} // namespace sqb

// ---- #include <sqbind/sqbSquirrelFunction.inl>
// ---> including sqbSquirrelFunction.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// SquirrelFunction
//----------------------------------------------------------------------------------------------------------------------
inline HSQUIRRELVM SquirrelFunction::SetVM(HSQUIRRELVM vm)
{
  HSQUIRRELVM result = m_vm;
  m_vm = vm;
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
inline HSQUIRRELVM SquirrelFunction::GetVM() const
{
  return m_vm;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger SquirrelFunction::GetArgumentCount() const
{
  ScopedArrayAccess access(m_arguments);
  return access.GetSize();
}

//----------------------------------------------------------------------------------------------------------------------
inline void SquirrelFunction::ClearArguments()
{
  ScopedArrayAccess access(m_arguments);
  access.Clear();
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ArgumentType>
inline void SquirrelFunction::AddArgument(ArgumentType argument)
{
  ScopedArrayAccess access(m_arguments);
  access.AppendElement(argument);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ArgumentType>
inline void SquirrelFunction::InsertArgument(SQInteger index, ArgumentType argument)
{
  ScopedArrayAccess access(m_arguments);
  access.InsertElement(index, argument);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ArgumentType>
inline void SquirrelFunction::OverwriteArgument(SQInteger index, ArgumentType argument)
{
  ScopedArrayAccess access(m_arguments);
  access.SetElement(index, argument);
}

//----------------------------------------------------------------------------------------------------------------------
inline void SquirrelFunction::RemoveArgument(SQInteger index)
{
  ScopedArrayAccess access(m_arguments);
  access.RemoveElement(index);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType SquirrelFunction::GetReturnType() const
{
  return m_returnValue.GetType();
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ResultType>
inline const ResultType& SquirrelFunction::GetReturnValue() const
{
  sq_pushobject(m_vm, m_returnValue);
  const ResultType& returnValue = Get(TypeWrapper<ResultType>(), m_vm, -1);
  sq_poptop(m_vm);
  return returnValue;
}

} // namespace sqb

// <--- back to sqbSquirrelFunction.h

// <--- back to SquirrelBind.h
// ---- #include <sqbind/sqbSquirrelObject.h>
// ---> including sqbSquirrelObject.h
// <--- back to SquirrelBind.h
// ---- #include <sqbind/sqbSquirrelVM.h>
// ---> including sqbSquirrelVM.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqbSquirrelVM.h
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbBaseHeader.h>
// ---> including sqbBaseHeader.h
// <--- back to sqbSquirrelVM.h
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
class SquirrelObject;

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
struct SQBIND_API InitialisationOptions
{
  enum
  {
    kRegisterNoStdLibs    = 0,
    kRegisterStdBlobLib   = 1 << 1,
    kRegisterStdIOLib     = 1 << 2,
    kRegisterStdMathLib   = 1 << 3,
    kRegisterStdStringLib = 1 << 4,
    kRegisterStdSystemLib = 1 << 5,
    kRegisterAllStdLibs   = kRegisterStdBlobLib | kRegisterStdIOLib | kRegisterStdMathLib | kRegisterStdStringLib | kRegisterStdSystemLib,
  };

  typedef uint8_t Flags;
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
struct SQBIND_API CompilationOptions
{
  /// \brief The name associated with the compiled script used to generate more meaningful runtime errors,
  ///   defaults to null.
  const SQChar *m_sourceName;

  /// \brief Should an error be printed if the compilation fails, defaults to true.
  bool m_printError;

  CompilationOptions();

  CompilationOptions &SourceName(const SQChar *sourceName);
  CompilationOptions &PrintError(bool printError);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
struct SQBIND_API ExecutionOptions
{
  /// \brief Should the execution raise an error if it fails, defaults to true.
  bool m_raiseError;

  ExecutionOptions();

  ExecutionOptions &RaiseError(bool raiseError);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API SquirrelVM
{
public:

  enum
  {
    kInitialStackSize = 1024,
  };

  /// \brief Initialises the vm to null.
  SquirrelVM();
  /// \brief Initialise the vm and register the specified standard libraries, this is the same as calling Initialise.
  SquirrelVM(InitialisationOptions::Flags flags);
  /// \brief Initialise with an external vm, you cannot call Initialise if this was called.
  SquirrelVM(HSQUIRRELVM vm);
  /// \brief This destructor does nothing in case the vm was externally managed, to shutdown a vm
  ///   call Shutdown.
  ~SquirrelVM();

  /// \brief Overload the type cast operator to all this to be passed to native squirrel functions.
  operator HSQUIRRELVM () const;

  /// \brief Set the squirrel vm this manages, returns the previously managed vm.
  HSQUIRRELVM SetVM(HSQUIRRELVM vm);
  /// \brief Get the squirrel vm this is managing.
  HSQUIRRELVM GetVM() const;

  /// \brief Perform some standard initialisation of a squirrel vm. Creates a vm, turns on debugging info,
  ///   sets up the compile and runtime error handlers to use the print function and registers the standard
  ///   libraries.
  bool Initialise(InitialisationOptions::Flags flags = InitialisationOptions::kRegisterAllStdLibs);

  /// \brief Has this instance been successfully initialised.
  bool IsInitialised() const;

  /// \brief Shutdown the vm managed by this class.
  bool Shutdown();

  /// \brief Sets the print and error functions.
  bool SetPrintFunction(SQPRINTFUNCTION printFunction);

  SquirrelObject GetRootTable() const;

  SquirrelObject GetConstTable() const;

  SquirrelObject CreateNewTable();
  SquirrelObject CreateNewTable(SQInteger initialCapacity);
  SquirrelObject CreateNewArray(SQInteger size);


  /// \brief Compile a script buffer.
  SquirrelObject CompileBuffer(
    const SQChar              *buffer,
    const CompilationOptions  &compilationOptions = CompilationOptions());

  /// \brief Compile a script file.
  SquirrelObject CompileScript(
    const SQChar              *filename,
    const CompilationOptions  &compilationOptions = CompilationOptions());

  /// \brief Compile and call a script buffer.
  SQRESULT ExecuteBuffer(
    const SQChar              *buffer,
    const CompilationOptions  &compilationOptions = CompilationOptions(),
    const ExecutionOptions    &executionOptions = ExecutionOptions(),
    SquirrelObject            *returnValue = nullptr);

  /// \brief Compile and call a script file.
  SQRESULT ExecuteScript(
    const SQChar              *filename,
    const CompilationOptions  &compilationOptions = CompilationOptions(),
    const ExecutionOptions    &executionOptions = ExecutionOptions(),
    SquirrelObject            *returnValue = nullptr);

protected:
  HSQUIRRELVM m_vm;
};

} // namespace sqb

// ---- #include <sqbind/sqbSquirrelVM.inl>
// ---> including sqbSquirrelVM.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// CompilationOptions
//----------------------------------------------------------------------------------------------------------------------
inline CompilationOptions::CompilationOptions()
: m_sourceName(nullptr),
  m_printError(true)
{
}

//----------------------------------------------------------------------------------------------------------------------
inline CompilationOptions &CompilationOptions::SourceName(const SQChar *sourceName)
{
  m_sourceName = sourceName;
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
inline CompilationOptions &CompilationOptions::PrintError(bool printError)
{
  m_printError = printError;
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
inline ExecutionOptions::ExecutionOptions()
: m_raiseError(true)
{
}

//----------------------------------------------------------------------------------------------------------------------
inline ExecutionOptions &ExecutionOptions::RaiseError(bool raiseError)
{
  m_raiseError = raiseError;
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
// SquirrelVM
//----------------------------------------------------------------------------------------------------------------------
inline SquirrelVM::SquirrelVM()
: m_vm(nullptr)
{
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelVM::SquirrelVM(InitialisationOptions::Flags flags)
: m_vm(nullptr)
{
  Initialise(flags);
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelVM::SquirrelVM(HSQUIRRELVM vm)
: m_vm(vm)
{
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelVM::~SquirrelVM()
{
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelVM::operator HSQUIRRELVM () const
{
  return m_vm;
}

//----------------------------------------------------------------------------------------------------------------------
inline HSQUIRRELVM SquirrelVM::SetVM(HSQUIRRELVM vm)
{
  HSQUIRRELVM result = m_vm;
  m_vm = vm;
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
inline HSQUIRRELVM SquirrelVM::GetVM() const
{
  return m_vm;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelVM::IsInitialised() const
{
  return m_vm != nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelVM::SetPrintFunction(SQPRINTFUNCTION printFunction)
{
  if (m_vm)
  {
    sq_setprintfunc(m_vm, printFunction, printFunction);
    return true;
  }

  return false;
}

} // namespace sqb

// <--- back to sqbSquirrelVM.h

// <--- back to SquirrelBind.h
// ---- #include <sqbind/sqbStackHandler.h>
// ---> including sqbStackHandler.h
// <--- back to SquirrelBind.h
// ---- #include <sqbind/sqbTableIterator.h>
// ---> including sqbTableIterator.h
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqbTableIterator.h
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbAssert.h>
// ---> including sqbAssert.h
// <--- back to sqbTableIterator.h
// ---- #include <sqbind/sqbClassTypeTag.h>
// ---> including sqbClassTypeTag.h
// <--- back to sqbTableIterator.h
// ---- #include <sqbind/sqbSquirrelObject.h>
// ---> including sqbSquirrelObject.h
// <--- back to sqbTableIterator.h
// ---- #include <sqbind/sqbStackUtils.h>
// ---> including sqbStackUtils.h
// <--- back to sqbTableIterator.h
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API TableIterator
{
public:
  TableIterator(HSQUIRRELVM vm, SQInteger tableIndex);
  TableIterator(HSQUIRRELVM vm, HSQOBJECT tableObject);
  TableIterator(const SquirrelObject& tableObject);
  ~TableIterator();

  /// \brief Rewinds the iterator back to the start
  void Reset();

  /// \brief Iterates to the next element of the table, returns false when the iterating is complete.
  bool Next();

  SQObjectType GetKeyType() const;

  template<typename ClassType>
  bool IsKeyInstanceOfType() const;

  template<typename KeyType>
  void GetKey(KeyType *key) const;

  SQObjectType GetValueType() const;

  template<typename ClassType>
  bool IsValueInstanceOfType() const;

  template<typename ValueType>
  void GetValue(ValueType *value) const;

protected:
  /// \brief Enum to describe the current state of the iterator.
  /// \note Enum is in this order so when they are in order in a switch kIterationNotStarted and
  ///   kIterationFinished are next to each other and can share the same code path.
  enum IterationState
  {
    kIterationNotStarted,
    kIterationFinished,
    kIterationInProgress,
  };

  HSQUIRRELVM     m_vm;
  HSQOBJECT       m_object;
  IterationState  m_state;
};

} // namespace sqb

// ---- #include <sqbind/sqbTableIterator.inl>
// ---> including sqbTableIterator.inl
// ---- #pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Assert to check that the object is on the top of the stack.
//----------------------------------------------------------------------------------------------------------------------
#if SQBIND_ASSERTS_ENABLED
# define SQBIND_ASSERT_ITERATOR_VALID(SQBIND_TABLE_INDEX, SQBIND_ITERATOR_INDEX) \
  SQBIND_ASSERT(sq_gettype(m_vm, SQBIND_ITERATOR_INDEX) == OT_NULL || sq_gettype(m_vm, SQBIND_ITERATOR_INDEX) == OT_INTEGER); \
  SQBIND_ASSERT(sq_gettype(m_vm, SQBIND_TABLE_INDEX) == OT_TABLE); \
  sq_push(m_vm, SQBIND_TABLE_INDEX); \
  sq_pushobject(m_vm, m_object); \
  SQBIND_ASSERT(sq_cmp(m_vm) == 0); \
  sq_pop(m_vm, 2)
#else
# define SQBIND_ASSERT_ITERATOR_VALID(SQBIND_TABLE_INDEX, SQBIND_ITERATOR_INDEX)
#endif

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// TableIterator
//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType TableIterator::GetKeyType() const
{
  SQBIND_ASSERT(m_state == kIterationInProgress);
  SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
  return sq_gettype(m_vm, -2);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline bool TableIterator::IsKeyInstanceOfType() const
{
  SQBIND_ASSERT(m_state == kIterationInProgress);
  SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
  SQUserPointer up;
  SQUserPointer typetag = ClassTypeTag<ClassType>::Get();
  SQRESULT result = sq_getinstanceup(m_vm, -2, &up, typetag);
  return SQ_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline void TableIterator::GetKey(KeyType *key) const
{
  SQBIND_ASSERT(key != nullptr);
  SQBIND_ASSERT(m_state == kIterationInProgress);
  SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
  *key = Get(TypeWrapper<KeyType>(), m_vm, -2);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType TableIterator::GetValueType() const
{
  SQBIND_ASSERT(m_state == kIterationInProgress);
  SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
  return sq_gettype(m_vm, -1);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline bool TableIterator::IsValueInstanceOfType() const
{
  SQBIND_ASSERT(m_state == kIterationInProgress);
  SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
  SQUserPointer up;
  SQUserPointer typetag = ClassTypeTag<ClassType>::Get();
  SQRESULT result = sq_getinstanceup(m_vm, -1, &up, typetag);
  return SQ_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline void TableIterator::GetValue(ValueType *value) const
{
  SQBIND_ASSERT(value != nullptr);
  SQBIND_ASSERT(m_state == kIterationInProgress);
  SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
  *value = Get(TypeWrapper<ValueType>(), m_vm, -1);
}

} // namespace sqb

// <--- back to sqbTableIterator.h

// <--- back to SquirrelBind.h
//----------------------------------------------------------------------------------------------------------------------

// <--- back to xsqbind.h

#endif

// <--- back to _xsqbind.cpp







SqRef &__xsqbind_sqref_get(SQVM *vm,int index)
{
	SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
	static SqRef r;
	r = SqRef();
	sqvm.getstackobj(r,index);
	return r;
}

int __xsqbind_sqref_push(SQVM *vm,SqRef &ref)
{
	if(!ref.handle || !ref.handle->vm)
		return 0;	// return null
	sq_pushobject(vm,ref.handle->hobj);
	return 1;
}



namespace sqb {
	template<>
	SqRef &Get<SqRef>(sqb::TypeWrapper<SqRef>,SQVM *vm,SQInteger index)
	{
		return __xsqbind_sqref_get(vm,index);
	}

	template<>
	bool Match<SqRef>(sqb::TypeWrapper<SqRef>,SQVM *vm,SQInteger index)
	{
		HSQOBJECT hobj;
		if(SQ_FAILED(sq_getstackobj(vm,index,&hobj)))
			return false;
		return sq_istable(hobj) || sq_isarray(hobj) || sq_isinstance(hobj) || sq_isclass(hobj);
	}

	template<>
	SQInteger Push<SqRef>(SQVM *vm,SqRef &ref)
	{
		return __xsqbind_sqref_push(vm,ref);
	}

	//template<>
	//int Push<std::string> (struct SQVM *vm,std::string &s)
	//{
	//	sq_pushstring(vm,s.c_str(),s.size());
	//	return SQ_OK;
	//}


	bool Match(TypeWrapper<const std::string>,HSQUIRRELVM v,int idx) {
		return sq_gettype(v,idx) == OT_STRING;
	}

	std::string Get(TypeWrapper<const std::string>,HSQUIRRELVM v,int idx)
	{
		const SQChar * s;
		sq_getstring(v,idx,&s);
		return std::string(s);

	}

	template<>
	SQInteger Push<std::string>(HSQUIRRELVM v,std::string &value) { sq_pushstring(v,value.c_str(),-1); return 1; }
}



#endif

// ******************************** sqbAssert.cpp ********************************
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbPrecompiled.h"
// ---> including sqbPrecompiled.h
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
#include <cstdio>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqbPrecompiled.h
//----------------------------------------------------------------------------------------------------------------------

// <--- back to sqbAssert.cpp
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbAssert.h>
// ---> including sqbAssert.h
// <--- back to sqbAssert.cpp
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
// Pointer to the current assertion failure handler function
AssertFailHandlerFunction g_assertHandler = &AssertionFailureFunctionBreak;
// The current assertion failure handler's userdata.
void *g_assertUserData = nullptr;

//----------------------------------------------------------------------------------------------------------------------
void GetAssertionFailureFunction(AssertFailHandlerFunction *handler, void **userData)
{
  *handler = g_assertHandler;
  *userData = g_assertUserData;
}

//----------------------------------------------------------------------------------------------------------------------
void SetAssertionFailureFunction(AssertFailHandlerFunction handler, void* userData)
{
  g_assertHandler = handler;
  g_assertUserData = userData;
}

//----------------------------------------------------------------------------------------------------------------------
AssertFailOp AssertionFailure(const char* file, size_t line, const char* message)
{
#if SQBIND_ASSERTS_ENABLED
  if (g_assertHandler)
  {
    return g_assertHandler(file, line, message, g_assertUserData);
  }

  return kAssertFailContinue;
#else
  (void)file;
  (void)line;
  (void)message;

  return kAssertFailContinue;
#endif
}

//----------------------------------------------------------------------------------------------------------------------
AssertFailOp AssertionFailureFunctionBreak(
  const char* file,
  size_t      line,
  const char* message,
  void*       SQBIND_UNUSED(userData))
{
  fprintf(stderr, "%s(%lu) : assertion failure '%s'.\n", file, static_cast<unsigned long>(line), message);
  return kAssertFailHalt;
}

//----------------------------------------------------------------------------------------------------------------------
AssertFailOp AssertionFailureFunctionExit(
  const char* file,
  size_t      line,
  const char* message,
  void*       SQBIND_UNUSED(userData))
{
  fprintf(stderr, "%s(%lu) : assertion failure '%s'.\n", file, static_cast<unsigned long>(line), message);
  return kAssertFailExit;
}

//----------------------------------------------------------------------------------------------------------------------
AssertFailOp AssertionFailureFunctionContinue(
  const char* file,
  size_t      line,
  const char* message,
  void*       SQBIND_UNUSED(userData))
{
  fprintf(stderr, "%s(%lu) : assertion failure '%s'.\n", file, static_cast<unsigned long>(line), message);
  return kAssertFailContinue;
}

} // namespace sqb

// ******************************** sqbBind.cpp ********************************
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbPrecompiled.h"
// ---> including sqbPrecompiled.h
// <--- back to sqbBind.cpp
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbBind.h>
// ---> including sqbBind.h
// <--- back to sqbBind.cpp
// ---- #include <sqbind/sqbStackHandler.h>
// ---> including sqbStackHandler.h
// <--- back to sqbBind.cpp
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
const SQInteger Bind::kGetMetaMethodParamCheckCount = 2;
const SQInteger Bind::kSetMetaMethodParamCheckCount = 3;

const SQChar *Bind::kGetMetaMethodTypeMask = _SC("x|t|u s");
const SQChar *Bind::kSetMetaMethodTypeMask = _SC("x|t|u s .");

const SQInteger Bind::kThisObjectStackIndex = 1;

const SQInteger Bind::kNameStackIndex = 2;

const SQInteger Bind::kGetObjectReferencesStackIndex = 3;

const SQInteger Bind::kSetValueStackIndex = 3;
const SQInteger Bind::kSetObjectReferencesStackIndex = 4;

//----------------------------------------------------------------------------------------------------------------------
bool Bind::BindNativeFunction(
  HSQUIRRELVM       vm,
  SQInteger         objectIndex,
  SQFUNCTION        function,
  const SQChar     *name,
  FunctionOptions   options)
{
  SQObjectType objectType = sq_gettype(vm, objectIndex);
  if (objectType != OT_CLASS && objectType != OT_TABLE)
  {
    return false;
  }

  if (name == nullptr)
  {
    return false;
  }

  size_t nameLength = scstrlen(name);
  if (nameLength == 0)
  {
    return false;
  }

  // if the index was relative to the top convert to an absolute index before calls alter the stack.
  //
  if (objectIndex < 0)
  {
    SQInteger top = sq_gettop(vm);
    objectIndex = top + objectIndex + 1;
  }

  sq_newclosure(vm, function, options.m_freeVariableCount);

  if (options.m_paramCheckCount != 0 && options.m_typeMaskString != nullptr)
  {
    if (SQ_FAILED(sq_setparamscheck(vm, options.m_paramCheckCount, options.m_typeMaskString)))
    {
      sq_poptop(vm);
      return false;
    }
  }

  // set the name used when debugging
  //
  SQRESULT result = sq_setnativeclosurename(vm, -1, name);
  SQBIND_ASSERT_SUCCEEDED(result);

  // create a named slot for the new function in the owning object
  //
  sq_pushstring(vm, name, nameLength);
  sq_push(vm, -2);
  result = sq_newslot(vm, objectIndex, options.m_staticType);
  SQBIND_ASSERT_SUCCEEDED(result);

  // remove the first closure from the stack, the pushed copy was removed by sq_newslot.
  //
  sq_poptop(vm);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
void Bind::GetOrCreateObjectReferencesTable(HSQUIRRELVM vm, SQInteger objectIndex, SQObjectType objectType)
{
  // get the table that holds all variable references for the object we're binding to from the registry table.
  // the key is the object itself
  //
  sq_pushregistrytable(vm);
  sq_push(vm, objectIndex);

  // if there is no table then create a slot with the object being bound as the key and a new table as the value.
  //
  if (SQ_FAILED(sq_rawget(vm, -2)))
  {
    sq_newtable(vm);

    sq_push(vm, objectIndex);
    sq_push(vm, -2);
    sq_rawset(vm, -4);

    // if object is a class the delegate of the object references table must be the object references table
    // of the base class if there is one otherwise getting a member bound to a base class will fail for instances
    // of a derived class.
    //
    if (objectType == OT_CLASS)
    {
      sq_getbase(vm, objectIndex);

      if (sq_gettype(vm, objectIndex + 3) == OT_CLASS)
      {
        // do this recursively up the inheritance hierarchy
        //
        GetOrCreateObjectReferencesTable(vm, objectIndex + 3, OT_CLASS);
        sq_setdelegate(vm, objectIndex + 2);
      }

      sq_poptop(vm);
    }
  }

  // remove the registry table
  //
  sq_remove(vm, -2);
}

//----------------------------------------------------------------------------------------------------------------------
void Bind::GetOrCreateObjectDelegate(HSQUIRRELVM vm, SQInteger objectIndex)
{
  // this function is only called by this class so there is no need to do any checking of arguments
  //
  SQRESULT result = sq_getdelegate(vm, objectIndex);
  SQBIND_ASSERT_SUCCEEDED(result);
  if (sq_gettype(vm, -1) == OT_NULL)
  {
    sq_poptop(vm);

    sq_newtable(vm);

    sq_push(vm, -1);
    sq_setdelegate(vm, objectIndex);
  }
}

//----------------------------------------------------------------------------------------------------------------------
bool Bind::CreateVariableReference(
  HSQUIRRELVM     vm,
  SQInteger       variableReferenceIndex,
  ScriptVarType   variableType,
  SQUserPointer   offsetOrAddress,
  ClassTypeTagBase  *instanceClassType,
  ClassTypeTagBase  *variableClassType,
  SQInteger       bindFlags)
{
  SQBIND_ASSERT(sq_gettype(vm, variableReferenceIndex) == OT_TABLE);

  // store the script type
  //
  if (variableType == kScriptVarTypeNone)
  {
    return false;
  }
  sq_pushinteger(vm, kScriptVarTypeKey);
  sq_pushinteger(vm, variableType);
  sq_rawset(vm, variableReferenceIndex);

  // store the offsetOrAddress
  //
  sq_pushinteger(vm, kOffsetOrAddressKey);
  sq_pushuserpointer(vm, offsetOrAddress);
  sq_rawset(vm, variableReferenceIndex);

  // if we're binding to a class instance then store the instance type
  //
  if (instanceClassType != nullptr)
  {
    SQBIND_ASSERT(instanceClassType->IsValid());

    sq_pushinteger(vm, kInstanceClassTypeKey);
    sq_pushuserpointer(vm, instanceClassType);
    sq_rawset(vm, variableReferenceIndex);
  }

  // if the variable being bound is a class then store the class type
  //
  if (variableType == kScriptVarTypeInstance)
  {
    SQBIND_ASSERT(variableClassType != nullptr);
    SQBIND_ASSERT(variableClassType->IsValid());

    sq_pushinteger(vm, kVariableClassTypeKey);
    sq_pushuserpointer(vm, variableClassType);
    sq_rawset(vm, variableReferenceIndex);
  }

  // if there were any flags then store them
  //
  if (bindFlags != kVariableNoFlags)
  {
    sq_pushinteger(vm, kFlagsKey);
    sq_pushinteger(vm, static_cast<SQInteger>(bindFlags));
    sq_rawset(vm, variableReferenceIndex);
  }

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
void Bind::EnsureGetMetaMethodBound(
  HSQUIRRELVM   vm,
  SQInteger     objectIndex,
  SQObjectType  type,
  SQInteger     objectReferencesIndex)
{
  // this function can only be called by other static functions of this class so the parameters
  // and objects in the stack are guaranteed to be correct.
  //
  if (type != OT_CLASS)
  {
    GetOrCreateObjectDelegate(vm, objectIndex);
    objectIndex = -2;
  }

  sq_pushstring(vm, _SC("_get"), 4);
  if (SQ_FAILED(sq_rawget(vm, objectIndex)))
  {
    // there is no _set metamethod so create one
    //
    FunctionOptions options;

    // set up the param checks
    //
    options.ParamCheckCount(kGetMetaMethodParamCheckCount);
    options.TypeMask(kGetMetaMethodTypeMask);

    // push the object references table to be bound as a free variable
    //
    options.FreeVariables(1);
    sq_push(vm, objectReferencesIndex);

    if (type == OT_CLASS)
    {
      BindNativeFunction(vm, objectIndex, &GetInstanceVariableReference, _SC("_get"), options);
    }
    else
    {
      BindNativeFunction(vm, objectIndex, &GetVariableReference, _SC("_get"), options);
    }
  }
  else
  {
    SQBIND_ASSERT(sq_gettype(vm, -1) == OT_NATIVECLOSURE);

    // pop the metamethod
    //
    sq_poptop(vm);
  }

  if (type != OT_CLASS)
  {
    // pop the delegate
    //
    sq_poptop(vm);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void Bind::EnsureSetMetaMethodBound(
  HSQUIRRELVM   vm,
  SQInteger     objectIndex,
  SQObjectType  type,
  SQInteger     objectReferencesIndex)
{
  // this function can only be called by other static functions of this class so the parameters
  // and objects in the stack are guaranteed to be correct.
  //
  if (type != OT_CLASS)
  {
    GetOrCreateObjectDelegate(vm, objectIndex);
    objectIndex = -2;
  }

  sq_pushstring(vm, _SC("_set"), 4);
  if (SQ_FAILED(sq_rawget(vm, objectIndex)))
  {
    // there is no _set metamethod so create one
    //
    FunctionOptions options;

    // set up the param checks
    //
    options.ParamCheckCount(kSetMetaMethodParamCheckCount);
    options.TypeMask(kSetMetaMethodTypeMask);

    // push the object references table to be bound as a free variable
    //
    options.FreeVariables(1);
    sq_push(vm, objectReferencesIndex);

    if (type == OT_CLASS)
    {
      BindNativeFunction(vm, objectIndex, &SetInstanceVariableReference, _SC("_set"), options);
    }
    else
    {
      BindNativeFunction(vm, objectIndex, &SetVariableReference, _SC("_set"), options);
    }
  }
  else
  {
    SQBIND_ASSERT(sq_gettype(vm, -1) == OT_NATIVECLOSURE);

    // pop the metamethod
    //
    sq_poptop(vm);
  }

  if (type != OT_CLASS)
  {
    // pop the delegate
    //
    sq_poptop(vm);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void Bind::GetVariableReferenceTypeAndAddress(
  HSQUIRRELVM     vm,
  SQInteger       variableReferenceIndex,
  SQInteger      *variableType,
  SQUserPointer  *address)
{
  sq_pushinteger(vm, kScriptVarTypeKey);
  sq_rawget(vm, variableReferenceIndex);
  sq_getinteger(vm, -1, variableType);
  sq_poptop(vm);

  sq_pushinteger(vm, kOffsetOrAddressKey);
  sq_rawget(vm, variableReferenceIndex);
  sq_getuserpointer(vm, -1, address);
  sq_poptop(vm);
}

//----------------------------------------------------------------------------------------------------------------------
void Bind::GetVariableClassType(
  HSQUIRRELVM           vm,
  SQInteger             variableReferenceIndex,
  const ClassTypeTagBase **variableClassType)
{
  // get the variable class type from the variable reference table
  //
  sq_pushinteger(vm, kVariableClassTypeKey);
  sq_rawget(vm, variableReferenceIndex);
  sq_getuserpointer(vm, -1, (SQUserPointer*)variableClassType);
  sq_poptop(vm);
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger Bind::GetVariableReference(HSQUIRRELVM vm)
{
  // the object references stack index is never popped by this native closure,
  // squirrel cleans up the stack when this call returns
  //
  sq_push(vm, kNameStackIndex);
  if (SQ_FAILED(sq_rawget(vm, kGetObjectReferencesStackIndex)))
  {
    // throwing null indicates no runtime error and a clean failure of 'index not found'.
    //
#if defined(SQUIRREL_VERSION_NUMBER) && (SQUIRREL_VERSION_NUMBER >= 301)
    sq_pushnull(vm);
    return sq_throwobject(vm);
#else
    sq_reseterror(vm);
    return SQ_ERROR;
#endif // defined(SQUIRREL_VERSION_NUMBER) && SQUIRREL_VERSION_NUMBER >= 301
  }

  SQInteger variableType;
  SQUserPointer address;
  GetVariableReferenceTypeAndAddress(vm, kGetObjectReferencesStackIndex + 1, &variableType, &address);
  return GetVariable(vm, kGetObjectReferencesStackIndex + 1, variableType, address);
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger Bind::SetVariableReference(HSQUIRRELVM vm)
{
  // the object references stack index is never popped by this native closure,
  // squirrel cleans up the stack when this call returns
  //
  sq_push(vm, kNameStackIndex);
  if (SQ_FAILED(sq_rawget(vm, kSetObjectReferencesStackIndex)))
  {
    // throwing null indicates no runtime error and a clean failure of 'index not found'.
    //
#if defined(SQUIRREL_VERSION_NUMBER) && (SQUIRREL_VERSION_NUMBER >= 301)
    sq_pushnull(vm);
    return sq_throwobject(vm);
#else
    sq_reseterror(vm);
    return SQ_ERROR;
#endif // defined(SQUIRREL_VERSION_NUMBER) && SQUIRREL_VERSION_NUMBER >= 301
  }

  SQInteger variableType;
  SQUserPointer address;
  GetVariableReferenceTypeAndAddress(vm, kSetObjectReferencesStackIndex + 1, &variableType, &address);
  return SetVariable(vm, kSetObjectReferencesStackIndex + 1, variableType, address);
}


//----------------------------------------------------------------------------------------------------------------------
void Bind::GetInstanceVariableReferenceTypeAndAddress(
  HSQUIRRELVM     vm,
  SQInteger       variableReferenceIndex,
  SQInteger      *variableType,
  SQUserPointer  *address)
{
  sq_pushinteger(vm, kScriptVarTypeKey);
  sq_rawget(vm, variableReferenceIndex);
  sq_getinteger(vm, -1, variableType);
  sq_poptop(vm);

  SQUserPointer offsetOrAddress;
  sq_pushinteger(vm, kOffsetOrAddressKey);
  sq_rawget(vm, variableReferenceIndex);
  sq_getuserpointer(vm, -1, &offsetOrAddress);
  sq_poptop(vm);

  SQInteger flags;
  sq_pushinteger(vm, kFlagsKey);
  if (SQ_SUCCEEDED(sq_rawget(vm, variableReferenceIndex)))
  {
    sq_getinteger(vm, -1, &flags);
    sq_poptop(vm);
  }
  else
  {
    flags = kVariableNoFlags;
  }

  // if the static flag isn't set then offsetOrAddress is an offset from the instance so it must be
  // adjusted to make an absolute address
  //
  if ((flags & kVariableStatic) == kVariableStatic)
  {
    *address = offsetOrAddress;
  }
  else
  {
    // get the bound class type from the variable reference table
    //
    const ClassTypeTagBase *boundInstanceType;
    sq_pushinteger(vm, kInstanceClassTypeKey);
    sq_rawget(vm, variableReferenceIndex);
    sq_getuserpointer(vm, -1, (SQUserPointer*)&boundInstanceType);
    sq_poptop(vm);

    // get the current instance and its class type, don't ask for a typetag match as the typetag
    // matching will be done by GetOffsetTo and there is no point doing it twice.
    //
    SQUserPointer thisInstance;
    sq_getinstanceup(vm, kThisObjectStackIndex, &thisInstance, nullptr);
    SQUserPointer typetag;
    sq_gettypetag(vm, kThisObjectStackIndex, &typetag);

    const ClassTypeTagBase *thisInstanceType = static_cast<const ClassTypeTagBase *>(typetag);

    // adjust for the current type potentially being a derived class type of the bound class type.
    // if the current instance class type is not the same or does not derive from the bound class type
    // this call will assert.
    //
    if (boundInstanceType != typetag && thisInstanceType->MayHaveOffset())
    {
      ptrdiff_t offset = thisInstanceType->GetOffsetTo(boundInstanceType);
      thisInstance = static_cast<uint8_t *>(thisInstance) - offset;
    }

    // finally apply the offset from the instance to the member variable
    //
    *address = static_cast<uint8_t *>(thisInstance) + reinterpret_cast<ptrdiff_t>(offsetOrAddress);
  }
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger Bind::GetInstanceVariableReference(HSQUIRRELVM vm)
{
  // the object references stack index is never popped by this native closure,
  // squirrel cleans up the stack when this call returns
  //
  sq_push(vm, kNameStackIndex);
  // note that sq_get is used instead of sq_rawget as the variable reference may be in a delegate
  // of the object references table if it is a member of a base class not the most derived class
  //
  if (SQ_FAILED(sq_get(vm, kGetObjectReferencesStackIndex)))
  {
    // throwing null indicates no runtime error and a clean failure of 'index not found'.
    //
#if defined(SQUIRREL_VERSION_NUMBER) && (SQUIRREL_VERSION_NUMBER >= 301)
    sq_reseterror(vm);
    return SQ_ERROR;
#else
    sq_reseterror(vm);
    return SQ_ERROR;
#endif // defined(SQUIRREL_VERSION_NUMBER) && SQUIRREL_VERSION_NUMBER >= 301
  }

  SQInteger variableType;
  SQUserPointer address;
  GetInstanceVariableReferenceTypeAndAddress(vm, kGetObjectReferencesStackIndex + 1, &variableType, &address);
  return GetVariable(vm, kGetObjectReferencesStackIndex + 1, variableType, address);
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger Bind::SetInstanceVariableReference(HSQUIRRELVM vm)
{
  // the object references stack index is never popped by this native closure,
  // squirrel cleans up the stack when this call returns
  //
  sq_push(vm, kNameStackIndex);
  // note that sq_get is used instead of sq_rawget as the variable reference may be in a delegate
  // of the object references table if it is a member of a base class not the most derived class
  //
  if (SQ_FAILED(sq_get(vm, kSetObjectReferencesStackIndex)))
  {
    // throwing null indicates no runtime error and a clean failure of 'index not found'.
    //
#if defined(SQUIRREL_VERSION_NUMBER) && (SQUIRREL_VERSION_NUMBER >= 301)
    sq_reseterror(vm);
    return SQ_ERROR;
#else
    sq_reseterror(vm);
    return SQ_ERROR;
#endif // defined(SQUIRREL_VERSION_NUMBER) && SQUIRREL_VERSION_NUMBER >= 301
  }

  SQInteger variableType;
  SQUserPointer address;
  GetInstanceVariableReferenceTypeAndAddress(vm, kSetObjectReferencesStackIndex + 1, &variableType, &address);
  return SetVariable(vm, kSetObjectReferencesStackIndex + 1, variableType, address);
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger Bind::GetVariable(
  HSQUIRRELVM   vm,
  SQInteger     variableReferenceIndex,
  SQInteger     variableType,
  SQUserPointer address)
{
  StackHandler sh(vm);
  switch (variableType)
  {
  case TypeInfo<bool>::kTypeID:
    {
      const bool *value = static_cast<const bool*>(address);
      return sh.Return(static_cast<bool>(*value));
    }
  case TypeInfo<char>::kTypeID:
    {
      const char *value = static_cast<const char*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<int8_t>::kTypeID:
    {
      const int8_t *value = static_cast<const int8_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<uint8_t>::kTypeID:
    {
      const uint8_t *value = static_cast<const uint8_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<int16_t>::kTypeID:
    {
      const int16_t *value = static_cast<const int16_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<uint16_t>::kTypeID:
    {
      const uint16_t *value = static_cast<const uint16_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<int32_t>::kTypeID:
    {
      const int32_t *value = static_cast<const int32_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<uint32_t>::kTypeID:
    {
      const uint32_t *value = static_cast<const uint32_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<float>::kTypeID:
    {
      const float *value = static_cast<const float*>(address);
      return sh.Return(static_cast<SQFloat>(*value));
    }
  case TypeInfo<const SQChar *>::kTypeID:
    {
      const SQChar *const *value = static_cast<const SQChar *const *>(address);
      return sh.Return(static_cast<const SQChar*>(*value));
    }
  case TypeInfo<SQUserPointer>::kTypeID:
    {
      SQUserPointer *value = static_cast<SQUserPointer*>(address);
      return sh.Return(*value);
    }
  case kScriptVarTypeInstance:
    {
      const ClassTypeTagBase *variableClassTypeTag = nullptr;
      GetVariableClassType(vm, variableReferenceIndex, &variableClassTypeTag);

      HSQOBJECT variableClassObject = variableClassTypeTag->GetClassObject(vm);
      sq_pushobject(vm, variableClassObject);
      if (SQ_SUCCEEDED(sq_createinstance(vm, -1)))
      {
        // remove variableClassObject from stack
        //
        sq_remove(vm, -2);
        SQUserPointer instance = static_cast<SQUserPointer>(address);
        sq_setinstanceup(vm, -1, instance);
        return 1;
      }
      // remove variableClassObject from stack
      //
      sq_poptop(vm);
      return sh.ThrowError(
        _SC("error getting variable '%s' ; check variable class type '%s' has been bound correctly"),
        sh.GetString(2),
        variableClassTypeTag->GetTypeName());
    }
#if defined(_SQ64)
  case TypeInfo<int64_t>::kTypeID:
    {
      const int64_t *value = static_cast<const int64_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<uint64_t>::kTypeID:
    {
      const uint64_t *value = static_cast<const uint64_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
#endif
#if defined(SQUSEDOUBLE)
  case TypeInfo<double>::kTypeID:
    {
      const double *value = static_cast<const double*>(address);
      return sh.Return(static_cast<SQFloat>(*value));
    }
#endif
  default:
    break;
  }

  // annoyingly has to be outside the switch for test coverage instrumentation to work
  //
  return sh.ThrowError(
    _SC("error getting variable '%s' ; unknown variable type id '%d'"),
    sh.GetString(2),
    variableType);
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger Bind::SetVariable(
  HSQUIRRELVM   vm,
  SQInteger     variableReferenceIndex,
  SQInteger     variableType,
  SQUserPointer address)
{
  StackHandler sh(vm);

  SQObjectType expectedType;
  switch (variableType)
  {
  case TypeInfo<bool>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_BOOL)
    {
      SQBool value;
      sq_getbool(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<bool*>(address) = (value == SQTrue) ? true : false;
      sq_pushbool(vm, value);
      return 1;
    }
    expectedType = OT_BOOL;
    break;
  case TypeInfo<char>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<char*>(address) = static_cast<char>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<int8_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<int8_t*>(address) = static_cast<int8_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<uint8_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<uint8_t*>(address) = static_cast<uint8_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<int16_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<int16_t*>(address) = static_cast<int16_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<uint16_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<uint16_t*>(address) = static_cast<uint16_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<int32_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<int32_t*>(address) = static_cast<int32_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<uint32_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<uint32_t*>(address) = static_cast<uint32_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<float>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_FLOAT)
    {
      SQFloat value;
      sq_getfloat(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<float*>(address) = static_cast<float>(value);
      sq_pushfloat(vm, value);
      return 1;
    }
    expectedType = OT_FLOAT;
    break;
  case TypeInfo<const SQChar *>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_STRING)
    {
      const SQChar *value;
      sq_getstring(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<const SQChar **>(address) = value;
      sq_pushstring(vm, value, -1);

      // get the string references table from the variable reference table
      // if sq_rawget fails then the table doesn't exist yet so create it
      //
      sq_pushinteger(vm, kStringReferencesTableKey);
      if (SQ_FAILED(sq_rawget(vm, variableReferenceIndex)))
      {
        sq_newtable(vm);

        // push the integer and then the new table as sq_rawset will pop the key and value from the stack
        // and we need the new table to be on the stack after the call to sq_rawset.
        //
        sq_pushinteger(vm, kStringReferencesTableKey);
        sq_push(vm, -2);
        sq_rawset(vm, variableReferenceIndex);
      }

      // create a reference to the string with this object as the key so there is always a reference
      // otherwise the string may be cleaned up when it is still required
      //
      sq_push(vm, kThisObjectStackIndex);
      sq_push(vm, -3);
      sq_rawset(vm, -3);

      // remove the string references table
      //
      sq_poptop(vm);

      return 1;
    }
    expectedType = OT_STRING;
    break;
  case TypeInfo<SQUserPointer>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_USERPOINTER)
    {
      SQUserPointer value;
      sq_getuserpointer(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<SQUserPointer *>(address) = value;
      sq_pushuserpointer(vm, value);
      return 1;
    }
    expectedType = OT_USERPOINTER;
    break;
  case kScriptVarTypeInstance:
    {
      const ClassTypeTagBase *variableClassTypeTag = nullptr;
      GetVariableClassType(vm, variableReferenceIndex, &variableClassTypeTag);

      SQUserPointer value;
      if (SQ_SUCCEEDED(sq_getinstanceup(vm, kSetValueStackIndex, &value, (SQUserPointer)variableClassTypeTag)))
      {
        CopyInstanceFunction copyFunction = variableClassTypeTag->GetCopyFunction();
        copyFunction(address, value);

        HSQOBJECT variableClassObject = variableClassTypeTag->GetClassObject(vm);
        sq_pushobject(vm, variableClassObject);
        if (SQ_SUCCEEDED(sq_createinstance(vm, -1)))
        {
          // remove variableClassObject from stack
          //
          sq_remove(vm, -2);
          SQUserPointer instance = static_cast<SQUserPointer>(address);
          sq_setinstanceup(vm, -1, instance);
          return 1;
        }

        // remove variableClassObject from stack
        //
        sq_poptop(vm);
        return sh.ThrowError(
          _SC("error setting variable '%s' ; check variable class type '%s' has been bound correctly"),
          sh.GetString(2),
          variableClassTypeTag->GetTypeName());
      }

      return sh.ThrowError(
        _SC("error setting variable '%s' ; expected '%s' got '%s'"),
        sh.GetString(2),
        variableClassTypeTag->GetTypeName(),
        sh.GetTypeName(3));
    }
    break;
#if defined(_SQ64)
  case TypeInfo<int64_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<int64_t*>(address) = static_cast<int64_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<uint64_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<uint64_t*>(address) = static_cast<uint64_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
#endif // defined(_SQ64)
#if defined(SQUSEDOUBLE)
  case TypeInfo<double>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_FLOAT)
    {
      SQFloat value;
      sq_getfloat(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<double*>(address) = static_cast<double>(value);
      sq_pushfloat(vm, value);
      return 1;
    }
    expectedType = OT_FLOAT;
    break;
#endif // defined(SQUSEDOUBLE)
  default:
    return sh.ThrowError(
      _SC("error setting variable '%s' ; unknown variable type id '%d'"),
      sh.GetString(2),
      variableType);
  }

  return sh.ThrowError(
    _SC("error setting variable '%s' ; expected '%s' got '%s'"),
    sh.GetString(2),
    RawTypeToTypeName(expectedType),
    sh.GetTypeName(3));
}

}

// ******************************** sqbClassHelpers.cpp ********************************
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbPrecompiled.h"
// ---> including sqbPrecompiled.h
// <--- back to sqbClassHelpers.cpp
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbClassHelpers.h>
// ---> including sqbClassHelpers.h
// <--- back to sqbClassHelpers.cpp
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
bool CreateNativeClassInstance(HSQUIRRELVM vm, HSQOBJECT classObject, SQRELEASEHOOK hook)
{
  sq_pushobject(vm, classObject);

  if (SQ_FAILED(sq_createinstance(vm, -1)))
  {
    // remove class object
    //
    sq_poptop(vm);
    return false;
  }

  // remove class
  //
  sq_remove(vm, -2);

  if (hook)
  {
    sq_setreleasehook(vm, -1, hook);
  }

  return true;
}

}

// ******************************** sqbClassTypeTag.cpp ********************************
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbPrecompiled.h"
// ---> including sqbPrecompiled.h
// <--- back to sqbClassTypeTag.cpp
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbClassTypeTag.h>
// ---> including sqbClassTypeTag.h
// <--- back to sqbClassTypeTag.cpp
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// ClassTypeTagBase functions
//----------------------------------------------------------------------------------------------------------------------
const int32_t ClassTypeTagBase::m_expectedValidityCheck = 0x0B57AC1E;

// as all ClassTypeTagBase are static instances this destructor is hit after the test coverage scanning has finished
//
SQBIND_TEST_COVERAGE_OFF()
//----------------------------------------------------------------------------------------------------------------------
ClassTypeTagBase::ClassTypeTagBase()
: m_name(_SC("")),
  m_releaseHook(nullptr),
  m_baseType(nullptr),
  m_offset(0),
  m_mayHaveOffset(-1),
  m_validityCheck(m_expectedValidityCheck)
{
}

//----------------------------------------------------------------------------------------------------------------------
ClassTypeTagBase::~ClassTypeTagBase()
{
}
SQBIND_TEST_COVERAGE_ON()

//----------------------------------------------------------------------------------------------------------------------
void ClassTypeTagBase::SetClassObject(HSQUIRRELVM vm, HSQOBJECT classObject)
{
  // add classObject to the registry table with this userpointer as the key
  // so classObject can easily be retrieved when creating instances.
  sq_pushregistrytable(vm);

  // push the key
  SQUserPointer key = static_cast<SQUserPointer>(this);
  sq_pushuserpointer(vm, key);
  // push the class object
  sq_pushobject(vm, classObject);
  // add it to the registry table
  sq_rawset(vm, -3);

  // pop the registry table
  sq_poptop(vm);
}

//----------------------------------------------------------------------------------------------------------------------
HSQOBJECT ClassTypeTagBase::GetClassObject(HSQUIRRELVM vm) const
{
  sq_pushregistrytable(vm);

  SQUserPointer key = static_cast<SQUserPointer>(const_cast<ClassTypeTagBase*>(this));
  sq_pushuserpointer(vm, key);

  HSQOBJECT classObject;
  if (SQ_SUCCEEDED(sq_rawget(vm, -2)))
  {
    sq_getstackobj(vm, -1, &classObject);
    // pop the class
    sq_poptop(vm);
  }
  else
  {
    sq_resetobject(&classObject);
  }

  // pop the registry table
  //
  sq_poptop(vm);

  return classObject;
}

//----------------------------------------------------------------------------------------------------------------------
bool ClassTypeTagBase::CheckClassUserDataSize(HSQUIRRELVM vm, SQInteger expectedSize) const
{
  // retrieve the class object from the registry table
  //
  sq_pushregistrytable(vm);

  SQUserPointer key = static_cast<SQUserPointer>(const_cast<ClassTypeTagBase*>(this));
  sq_pushuserpointer(vm, key);

  SQInteger udsize = -1;
  if (SQ_SUCCEEDED(sq_rawget(vm, -2)))
  {
    udsize = sq_getsize(vm, -1);
    SQBIND_ASSERT(udsize != -1);

    // pop the class
    //
    sq_poptop(vm);
  }

  // pop the registry table, sq_rawget always pops the key from the stack regardless of success/failure.
  //
  sq_poptop(vm);

  return udsize >= expectedSize;
}

//----------------------------------------------------------------------------------------------------------------------
bool ClassTypeTagBase::MayHaveOffset() const
{
  if (m_mayHaveOffset < 0)
  {
    // if m_mayHaveOffset is less than 0 then it needs initialising
    //
    if (m_offset != 0)
    {
      // if this type has an offset then there definitely is an offset
      //
      m_mayHaveOffset = 1;
    }
    else
    {
      // if this type has no offset recurse up the hierarchy to the base checking for an offset
      //
      m_mayHaveOffset = 0;

      ClassTypeTagBase *current = m_baseType;
      while (current != nullptr)
      {
        if (current->m_offset != 0)
        {
          // a base class of this type had an offset to there might be an offset
          //
          m_mayHaveOffset = 1;
          break;
        }

        current = current->m_baseType;
      }
    }
  }

  return (m_mayHaveOffset != 0);
}

//----------------------------------------------------------------------------------------------------------------------
ptrdiff_t ClassTypeTagBase::GetOffsetTo(const ClassTypeTagBase *pbase) const
{
  // if this fails then pbase is invalid
  //
  SQBIND_ASSERT(pbase != nullptr);

  // accumulate the offset(s) until we hit pbase
  //
  ptrdiff_t offset = 0;

  const ClassTypeTagBase *current = this;
  while (current != nullptr && current != pbase)
  {
    offset += current->m_offset;
    current = current->m_baseType;
  }

  // if this fails then it doesn't derive from pbase.
  //
  SQBIND_ASSERT(current == pbase);

  return offset;
}

}

// ******************************** sqbPrecompiled.cpp ********************************
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbPrecompiled.h"
// ---> including sqbPrecompiled.h
// <--- back to sqbPrecompiled.cpp
//----------------------------------------------------------------------------------------------------------------------

// ******************************** sqbScopedArrayAccess.cpp ********************************
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbPrecompiled.h"
// ---> including sqbPrecompiled.h
// <--- back to sqbScopedArrayAccess.cpp
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbScopedArrayAccess.h>
// ---> including sqbScopedArrayAccess.h
// <--- back to sqbScopedArrayAccess.cpp
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// ScopedArrayAccess
//----------------------------------------------------------------------------------------------------------------------

} // namespace sqb

// ******************************** sqbScopedTableAccess.cpp ********************************
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbPrecompiled.h"
// ---> including sqbPrecompiled.h
// <--- back to sqbScopedTableAccess.cpp
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbScopedTableAccess.h>
// ---> including sqbScopedTableAccess.h
// <--- back to sqbScopedTableAccess.cpp
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// ScopedTableAccess
//----------------------------------------------------------------------------------------------------------------------

} // namespace sqb

// ******************************** sqbSquirrelFunction.cpp ********************************
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbPrecompiled.h"
// ---> including sqbPrecompiled.h
// <--- back to sqbSquirrelFunction.cpp
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbSquirrelFunction.h>
// ---> including sqbSquirrelFunction.h
// <--- back to sqbSquirrelFunction.cpp
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbSquirrelVM.h>
// ---> including sqbSquirrelVM.h
// <--- back to sqbSquirrelFunction.cpp
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// SquirrelFunction
//----------------------------------------------------------------------------------------------------------------------
SquirrelFunction::SquirrelFunction(HSQUIRRELVM vm)
: m_vm(vm)
{
  sq_pushroottable(m_vm);
  m_environment.Reference(m_vm, -1);
  sq_poptop(m_vm);

  sq_newarray(m_vm, 0);
  m_arguments.Reference(m_vm, -1);
  sq_poptop(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelFunction::SquirrelFunction(HSQUIRRELVM vm, SQInteger index)
: m_vm(vm)
{
#if SQBIND_ASSERTS_ENABLED
  SQObjectType type = sq_gettype(m_vm, index);
  SQBIND_ASSERT(type == OT_CLOSURE || type == OT_NATIVECLOSURE || type == OT_GENERATOR);
#endif
  m_function.Reference(m_vm, index);

  sq_pushroottable(m_vm);
  m_environment.Reference(m_vm, -1);
  sq_poptop(m_vm);

  sq_newarray(m_vm, 0);
  m_arguments.Reference(m_vm, -1);
  sq_poptop(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelFunction::SquirrelFunction(HSQUIRRELVM vm, HSQOBJECT function)
: m_vm(vm)
{
  SQBIND_ASSERT(sq_type(function) == OT_CLOSURE || sq_type(function) == OT_NATIVECLOSURE || sq_type(function) == OT_GENERATOR);
  m_function.Reference(m_vm, function);

  sq_pushroottable(m_vm);
  m_environment.Reference(m_vm, -1);
  sq_poptop(m_vm);

  sq_newarray(m_vm, 0);
  m_arguments.Reference(m_vm, -1);
  sq_poptop(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelFunction::SquirrelFunction(const SquirrelObject &function)
: m_function(function)
{
  SQBIND_ASSERT(m_function.GetType() == OT_CLOSURE || m_function.GetType() == OT_NATIVECLOSURE || m_function.GetType() == OT_GENERATOR);
  m_vm = m_function.GetVM();

  sq_pushroottable(m_vm);
  m_environment.Reference(m_vm, -1);
  sq_poptop(m_vm);

  sq_newarray(m_vm, 0);
  m_arguments.Reference(m_vm, -1);
  sq_poptop(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelFunction::SetFunction(SQInteger index)
{
#if SQBIND_ASSERTS_ENABLED
  SQObjectType type = sq_gettype(m_vm, index);
  SQBIND_ASSERT(type == OT_CLOSURE || type == OT_NATIVECLOSURE || type == OT_GENERATOR);
#endif
  m_function.Reference(m_vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelFunction::SetFunction(HSQOBJECT function)
{
  SQBIND_ASSERT(sq_type(function) == OT_CLOSURE || sq_type(function) == OT_NATIVECLOSURE || sq_type(function) == OT_GENERATOR);
  m_function.Reference(m_vm, function);
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelFunction::SetEnvironment(SQInteger index)
{
  m_environment.Reference(m_vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelFunction::SetEnvironment(HSQOBJECT environment)
{
  m_environment.Reference(m_vm, environment);
}

//----------------------------------------------------------------------------------------------------------------------
SQRESULT SquirrelFunction::Call()
{
  ExecutionOptions options;
  SQRESULT result = Call(options);
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
SQRESULT SquirrelFunction::Call(const ExecutionOptions &options)
{
  // push the function and environment first
  //
  sq_pushobject(m_vm, m_function);
  sq_pushobject(m_vm, m_environment);

  // push the arguments array so we can push all the arguments
  //
  sq_pushobject(m_vm, m_arguments);
  SQInteger argumentCount = sq_getsize(m_vm, -1);
  for (SQInteger i = 0; i != argumentCount; ++i)
  {
    sq_pushinteger(m_vm, i);
    SQRESULT result = sq_rawget(m_vm, -i - 2);
    SQBIND_ASSERT_SUCCEEDED(result);
  }
  // remove the arguments array
  //
  sq_remove(m_vm, -argumentCount - 1);

  SQRESULT result = sq_call(m_vm, argumentCount + 1, SQTrue, options.m_raiseError);
  if (SQ_SUCCEEDED(result))
  {
    m_returnValue.Reference(m_vm, -1);
    // pop the return value
    //
    sq_poptop(m_vm);
  }

  // pop the function
  //
  sq_poptop(m_vm);

  return result;
}

} // namespace sqb

// ******************************** sqbSquirrelObject.cpp ********************************
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbPrecompiled.h"
// ---> including sqbPrecompiled.h
// <--- back to sqbSquirrelObject.cpp
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbSquirrelObject.h>
// ---> including sqbSquirrelObject.h
// <--- back to sqbSquirrelObject.cpp
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// SquirrelObject
//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelObject::kNullObject;

//----------------------------------------------------------------------------------------------------------------------
const SquirrelObject &SquirrelObject::operator = (const SquirrelObject &rhs)
{
  // release the current object reference
  //
  if (m_vm)
  {
    sq_release(m_vm, &m_object);
  }

  // reference the other object
  //
  if (rhs.m_vm)
  {
    m_vm = rhs.m_vm;
    m_object = rhs.m_object;
    sq_addref(m_vm, &m_object);
  }
  else
  {
    m_vm = nullptr;
    sq_resetobject(&m_object);
  }

  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelObject::Reference(HSQUIRRELVM vm, SQInteger index)
{
  // release the current object reference
  //
  if (m_vm)
  {
    sq_release(m_vm, &m_object);
  }

  // reference the object on the stack
  //
  if (vm)
  {
    SQRESULT result = sq_getstackobj(vm, index, &m_object);
    SQBIND_ASSERT_SUCCEEDED(result);
    m_vm = vm;
    sq_addref(m_vm, &m_object);
  }
  else
  {
    m_vm = nullptr;
    sq_resetobject(&m_object);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelObject::Reference(HSQUIRRELVM vm, HSQOBJECT object)
{
  // release the current object reference
  //
  if (m_vm)
  {
    sq_release(m_vm, &m_object);
  }

  // reference the new object
  //
  if (vm)
  {
    m_vm = vm;
    m_object = object;
    sq_addref(m_vm, &m_object);
  }
  else
  {
    m_vm = nullptr;
    sq_resetobject(&m_object);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelObject::Reference(const SquirrelObject &object)
{
  // release the current object reference
  //
  if (m_vm)
  {
    sq_release(m_vm, &m_object);
  }

  // reference the other object
  //
  if (object.m_vm)
  {
    m_vm = object.m_vm;
    m_object = object.m_object;
    sq_addref(m_vm, &m_object);
  }
  else
  {
    m_vm = nullptr;
    sq_resetobject(&m_object);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelObject::Release()
{
  if (m_vm)
  {
    sq_release(m_vm, &m_object);

    m_vm = nullptr;
    sq_resetobject(&m_object);
  }
}

} // namespace sqb

// ******************************** sqbSquirrelVM.cpp ********************************
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbPrecompiled.h"
// ---> including sqbPrecompiled.h
// <--- back to sqbSquirrelVM.cpp
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbSquirrelVM.h>
// ---> including sqbSquirrelVM.h
// <--- back to sqbSquirrelVM.cpp
//----------------------------------------------------------------------------------------------------------------------
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

// <--- back to sqbSquirrelVM.cpp
// ---- #include <sqstdblob.h>
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


// <--- back to sqbSquirrelVM.cpp
// ---- #include <sqstdio.h>
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


// <--- back to sqbSquirrelVM.cpp
// ---- #include <sqstdmath.h>
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

// <--- back to sqbSquirrelVM.cpp
// ---- #include <sqstdstring.h>
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

// <--- back to sqbSquirrelVM.cpp
// ---- #include <sqstdsystem.h>
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

// <--- back to sqbSquirrelVM.cpp
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbAssert.h>
// ---> including sqbAssert.h
// <--- back to sqbSquirrelVM.cpp
// ---- #include <sqbind/sqbSquirrelObject.h>
// ---> including sqbSquirrelObject.h
// <--- back to sqbSquirrelVM.cpp
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// SquirrelVM
//----------------------------------------------------------------------------------------------------------------------
bool SquirrelVM::Initialise(InitialisationOptions::Flags flags)
{
  if (m_vm != nullptr)
  {
    // vm is already initialised.
    //
    return false;
  }

  m_vm = sq_open(kInitialStackSize);
  SQBIND_ASSERT(m_vm != nullptr);

  // enable debug line number info for error reporting
  //
  sq_enabledebuginfo(m_vm, SQTrue);

  // setup the compiler and runtime error handlers to use the print function
  //
  sqstd_seterrorhandlers(m_vm);

  // initialise all the standard libs
  //
  if (flags != InitialisationOptions::kRegisterNoStdLibs)
  {
    sq_pushroottable(m_vm);

    if ((flags & InitialisationOptions::kRegisterStdBlobLib) == InitialisationOptions::kRegisterStdBlobLib)
    {
      SQRESULT result = sqstd_register_bloblib(m_vm);
      SQBIND_ASSERT_SUCCEEDED(result);
    }

    if ((flags & InitialisationOptions::kRegisterStdIOLib) == InitialisationOptions::kRegisterStdIOLib)
    {
      SQRESULT result = sqstd_register_iolib(m_vm);
      SQBIND_ASSERT_SUCCEEDED(result);
    }

    if ((flags & InitialisationOptions::kRegisterStdMathLib) == InitialisationOptions::kRegisterStdMathLib)
    {
      SQRESULT result = sqstd_register_mathlib(m_vm);
      SQBIND_ASSERT_SUCCEEDED(result);
    }

    if ((flags & InitialisationOptions::kRegisterStdStringLib) == InitialisationOptions::kRegisterStdStringLib)
    {
      SQRESULT result = sqstd_register_stringlib(m_vm);
      SQBIND_ASSERT_SUCCEEDED(result);
    }

    if ((flags & InitialisationOptions::kRegisterStdSystemLib) == InitialisationOptions::kRegisterStdSystemLib)
    {
      SQRESULT result = sqstd_register_systemlib(m_vm);
      SQBIND_ASSERT_SUCCEEDED(result);
    }

    // pop the root table
    //
    sq_poptop(m_vm);
  }

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
bool SquirrelVM::Shutdown()
{
  if (m_vm == nullptr)
  {
    // vm was never initialised
    //
    return false;
  }

  // shutdown the vm
  //
  sq_close(m_vm);
  m_vm = nullptr;

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelVM::GetRootTable() const
{
  sq_pushroottable(m_vm);
  SquirrelObject object(m_vm, -1);
  sq_poptop(m_vm);
  return object;
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelVM::GetConstTable() const
{
  sq_pushconsttable(m_vm);
  SquirrelObject object(m_vm, -1);
  sq_poptop(m_vm);
  return object;
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelVM::CreateNewTable()
{
  sq_newtable(m_vm);
  SquirrelObject result(m_vm, -1);
  sq_poptop(m_vm);
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelVM::CreateNewTable(SQInteger initialCapacity)
{
  sq_newtableex(m_vm, initialCapacity);
  SquirrelObject result(m_vm, -1);
  sq_poptop(m_vm);
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelVM::CreateNewArray(SQInteger size)
{
  sq_newarray(m_vm, size);
  SquirrelObject result(m_vm, -1);
  sq_poptop(m_vm);
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelVM::CompileBuffer(
  const SQChar              *buffer,
  const CompilationOptions  &compilationOptions)
{
  SquirrelObject compiledBuffer;

  if (m_vm == nullptr)
  {
    return compiledBuffer;
  }

  if (buffer == nullptr)
  {
    return compiledBuffer;
  }

  size_t bufferLength = scstrlen(buffer);
  if (bufferLength == 0)
  {
    return compiledBuffer;
  }

  // compile the buffer with the given compilation options
  //
  SQRESULT result = sq_compilebuffer(
    m_vm,
    buffer,
    bufferLength,
    compilationOptions.m_sourceName ? compilationOptions.m_sourceName : _SC("CompiledBuffer"),
    compilationOptions.m_printError ? SQTrue : SQFalse);

  if (SQ_SUCCEEDED(result))
  {
    compiledBuffer.Reference(m_vm, -1);
    sq_poptop(m_vm);
  }

  return compiledBuffer;
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelVM::CompileScript(
  const SQChar              *filename,
  const CompilationOptions  &compilationOptions)
{
  SquirrelObject compiledBuffer;

  if (m_vm == nullptr)
  {
    return compiledBuffer;
  }

  if (filename == nullptr)
  {
    return compiledBuffer;
  }

  size_t filenameLength = scstrlen(filename);
  if (filenameLength == 0)
  {
    return compiledBuffer;
  }

  // load and compile the script with the given compilation options
  //
  SQRESULT result = sqstd_loadfile(m_vm, filename, compilationOptions.m_printError ? SQTrue : SQFalse);

  if (SQ_SUCCEEDED(result))
  {
    compiledBuffer.Reference(m_vm, -1);
    sq_poptop(m_vm);
  }

  return compiledBuffer;
}

//----------------------------------------------------------------------------------------------------------------------
SQRESULT SquirrelVM::ExecuteBuffer(
  const SQChar              *buffer,
  const CompilationOptions  &compilationOptions,
  const ExecutionOptions    &executionOptions,
  SquirrelObject            *returnValue)
{
  if (m_vm == nullptr)
  {
    return SQ_ERROR;
  }

  if (buffer == nullptr)
  {
    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteBuffer() : argument 'buffer' was null."));
  }

  size_t bufferLength = scstrlen(buffer);
  if (bufferLength == 0)
  {
    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteBuffer() : argument 'buffer' was empty."));
  }

  // compile the buffer with the given compilation options
  //
  SQRESULT result = sq_compilebuffer(
    m_vm,
    buffer,
    bufferLength,
    compilationOptions.m_sourceName ? compilationOptions.m_sourceName : _SC("CompiledBuffer"),
    compilationOptions.m_printError ? SQTrue : SQFalse);

  if (SQ_FAILED(result))
  {
    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteBuffer() : compilation of buffer failed."));
  }

  // push the root table
  //
  sq_pushroottable(m_vm);

  // call the compiled buffer with the given execution options
  //
  result = sq_call(
    m_vm,
    1,
    (returnValue != nullptr) ? SQTrue : SQFalse,
    executionOptions.m_raiseError ? SQTrue : SQFalse);

  if (SQ_SUCCEEDED(result))
  {
    if (returnValue != nullptr)
    {
      returnValue->Reference(m_vm, -1);

      // remove the result and the compiled buffer
      //
      sq_pop(m_vm, 2);

      return 1;
    }
    else
    {
      // pop the compiled buffer
      //
      sq_poptop(m_vm);

      return 0;
    }
  }
  else
  {
    // pop the compiled buffer
    //
    sq_poptop(m_vm);

    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteBuffer() : execution of buffer failed."));
  }
}

//----------------------------------------------------------------------------------------------------------------------
SQRESULT SquirrelVM::ExecuteScript(
  const SQChar              *filename,
  const CompilationOptions  &compilationOptions,
  const ExecutionOptions    &executionOptions,
  SquirrelObject            *returnValue)
{
  if (m_vm == nullptr)
  {
    return SQ_ERROR;
  }

  if (filename == nullptr)
  {
    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteScript() : argument 'filename' was null."));
  }

  size_t filenameLength = scstrlen(filename);
  if (filenameLength == 0)
  {
    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteScript() : argument 'filename' was empty."));
  }

  // load and compile the script with the given compilation options
  //
  SQRESULT result = sqstd_loadfile(m_vm, filename, compilationOptions.m_printError ? SQTrue : SQFalse);

  if (SQ_FAILED(result))
  {
    // pop the root table
    //
    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteScript() : loading of 'filename' failed."));
  }

  // push the root table in anticipation of the call
  //
  sq_pushroottable(m_vm);

  // call the compiled script with the given execution options
  //
  result = sq_call(
    m_vm,
    1,
    (returnValue != nullptr) ? SQTrue : SQFalse,
    executionOptions.m_raiseError ? SQTrue : SQFalse);

  if (SQ_SUCCEEDED(result))
  {
    if (returnValue != nullptr)
    {
      returnValue->Reference(m_vm, -1);

      // remove the result and the compiled buffer
      //
      sq_pop(m_vm, 2);

      return 1;
    }
    else
    {
      // pop the compiled buffer
      //
      sq_poptop(m_vm);

      return 0;
    }
  }
  else
  {
    // pop the root table and compiled buffer
    //
    sq_pop(m_vm, 2);

    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteScript() : execution of buffer failed."));
  }
}

} // namespace sqb

// ******************************** sqbStackHandler.cpp ********************************
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbPrecompiled.h"
// ---> including sqbPrecompiled.h
// <--- back to sqbStackHandler.cpp
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbStackHandler.h>
// ---> including sqbStackHandler.h
// <--- back to sqbStackHandler.cpp
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbClassTypeTag.h>
// ---> including sqbClassTypeTag.h
// <--- back to sqbStackHandler.cpp
//----------------------------------------------------------------------------------------------------------------------

#if defined(_MSC_VER)
# if defined(SQUNICODE)
#  define scvscprintf _vscwprintf
#  define scvsnprintf _vsnwprintf_s
# else // defined(SQUNICODE)
#  define scvscprintf _vscprintf
#  define scvsnprintf vsnprintf_s
# endif // defined(SQUNICODE)
#else // defined(_MSC_VER)
# if defined(SQUNICODE)
#  define scvsnprintf vsnwprintf
# else // defined(SQUNICODE)
#  define scvsnprintf vsnprintf
# endif // defined(SQUNICODE)
#endif // defined(_MSC_VER)

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
const SQChar *StackHandler::GetTypeName(SQInteger idx) const
{
  SQObjectType type = sq_gettype(m_vm, idx);

  // if it is an instance bound by this library then use that bound type name
  //
  if (type == OT_INSTANCE)
  {
    SQUserPointer typetag;
    sq_gettypetag(m_vm, idx, &typetag);

    if (typetag != nullptr)
    {
      const ClassTypeTagBase *classTypeTag = static_cast<const ClassTypeTagBase*>(typetag);
      if (classTypeTag->IsValid())
      {
        return classTypeTag->GetTypeName();
      }
    }
  }

  // if the type isn't an instance or the type tag isn't valid then return the raw type.
  //
  return RawTypeToTypeName(type);
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger StackHandler::ThrowNull()
{
  sq_reseterror(m_vm);
  return -1;
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger StackHandler::ThrowError(const SQChar *format, ...)
{
  SQBIND_ASSERT(format != nullptr);

#if defined(_MSC_VER)
  va_list vargs;
  va_start(vargs, format);
  int length = scvscprintf(format, vargs) + 1;
  va_end(vargs);

  SQChar *buffer = sq_getscratchpad(m_vm, length);

  va_start(vargs, format);
  scvsnprintf(buffer, length, length - 1, format, vargs);
  va_end(vargs);
#elif defined(__GNUC__) && defined(__STRICT_ANSI__)
  // susceptible to buffer overrun but vsnprintf doesn't exist for ansi c
  //
  const SQInteger increment = 256;
  SQInteger size = ((scstrlen(format) / increment) + 1) * increment;
  SQChar *buffer = sq_getscratchpad(m_vm, size);

  va_list vargs;
  va_start(vargs, format);
  int length = scvsprintf(buffer, format, vargs);
  va_end(vargs);

  SQBIND_ASSERT(length < size);
#else
  const SQInteger increment = 256;
  SQInteger size = ((scstrlen(format) / increment) + 1) * increment;
  SQChar *buffer = sq_getscratchpad(m_vm, size);

  va_list vargs;
  va_start(vargs, format);
  int length = scvsnprintf(buffer, size, format, vargs);
  va_end(vargs);

  if (length >= size)
  {
    buffer = sq_getscratchpad(m_vm, length + 1);

    va_start(vargs, format);
    int length = scvsnprintf(buffer, size, format, vargs);
    va_end(vargs);
  }
#endif

  return sq_throwerror(m_vm, buffer);
}

}

// ******************************** sqbTableIterator.cpp ********************************
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// ---- #include "sqbPrecompiled.h"
// ---> including sqbPrecompiled.h
// <--- back to sqbTableIterator.cpp
//----------------------------------------------------------------------------------------------------------------------
// ---- #include <sqbind/sqbTableIterator.h>
// ---> including sqbTableIterator.h
// <--- back to sqbTableIterator.cpp
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// TableIterator
//----------------------------------------------------------------------------------------------------------------------
TableIterator::TableIterator(HSQUIRRELVM vm, SQInteger tableIndex)
: m_vm(vm),
  m_state(kIterationNotStarted)
{
  sq_getstackobj(m_vm, tableIndex, &m_object);
  SQBIND_ASSERT(sq_type(m_object) == OT_TABLE);
  sq_pushobject(m_vm, m_object);
  sq_pushnull(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
TableIterator::TableIterator(HSQUIRRELVM vm, HSQOBJECT tableObject)
: m_vm(vm),
  m_object(tableObject),
  m_state(kIterationNotStarted)
{
  SQBIND_ASSERT(sq_type(m_object) == OT_TABLE);
  sq_pushobject(m_vm, m_object);
  sq_pushnull(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
TableIterator::TableIterator(const SquirrelObject& tableObject)
: m_vm(tableObject.GetVM()),
  m_object(tableObject.GetObject()),
  m_state(kIterationNotStarted)
{
  SQBIND_ASSERT(sq_type(m_object) == OT_TABLE);
  sq_pushobject(m_vm, m_object);
  sq_pushnull(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
TableIterator::~TableIterator()
{
  // clean up the stack
  //
  switch (m_state)
  {
  case kIterationNotStarted:
  case kIterationFinished:
    SQBIND_ASSERT_ITERATOR_VALID(-2, -1);
    sq_pop(m_vm, 2);
    break;
  case kIterationInProgress:
    SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
    sq_pop(m_vm, 4);
    break;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void TableIterator::Reset()
{
  // get rid of the current iterator
  //
  switch (m_state)
  {
  case kIterationNotStarted:
  case kIterationFinished:
    SQBIND_ASSERT_ITERATOR_VALID(-2, -1);
    sq_poptop(m_vm);
    break;
  case kIterationInProgress:
    SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
    sq_pop(m_vm, 3);
    break;
  }

  // setup for first iteration
  //
  m_state = kIterationNotStarted;
  sq_pushnull(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
bool TableIterator::Next()
{
  // get rid of the current iterator
  //
  switch (m_state)
  {
  case kIterationNotStarted:
    SQBIND_ASSERT_ITERATOR_VALID(-2, -1);
    m_state = kIterationInProgress;
    break;
  case kIterationFinished:
    SQBIND_ASSERT_ITERATOR_VALID(-2, -1);
    // early out as we have already finished iterating
    //
    return false;
  case kIterationInProgress:
    SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
    // pop the previous key and value
    //
    sq_pop(m_vm, 2);
    break;
  }

  // iterate to the next slot
  //
  if (SQ_SUCCEEDED(sq_next(m_vm, -2)))
  {
    return true;
  }

  // mark iterator as finished
  //
  m_state = kIterationFinished;

  return false;
}

} // namespace sqb

