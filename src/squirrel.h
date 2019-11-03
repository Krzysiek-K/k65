// ---------------- Library -- generated on 28.10.2017  20:32 ----------------



#pragma once

// ******************************** xsquirrel.h ********************************

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

