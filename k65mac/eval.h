
#pragma once


#include <math.h>



enum {
	ET_NUMBER,
	ET_STRING,
	ET_SECTION,		// value_i: index
};

struct EvalAny {
	int		type;
	double	value_f;
	string	value_s;
	int		value_i;

	static void Error(const char *s);
	static void Error(const string &s)										{ Error(s.c_str()); }
	static void Error(const char *s,const EvalAny &a)						{ Error(format(s,a.ToString().c_str())); }
	static void Error(const char *s,const EvalAny &a,const EvalAny &b)		{ Error(format(s,a.ToString().c_str(),b.ToString().c_str())); }
	string GetString() const;
	string ToString() const;
	double ToNumber() const;
	int ToInt() const { return int(floor(ToNumber())+.5f); }
	AsmSection *ToSection() const;
	bool IsTrue() const;

	EvalAny() : type(ET_NUMBER), value_f(0), value_i(0) {}
	EvalAny(double v) : type(ET_NUMBER), value_f(v), value_i(0) {}
	EvalAny(const string &v) : type(ET_STRING), value_f(0), value_i(0), value_s(v) {}

	void SetF(double v) { type=ET_NUMBER; value_f=v; }

#include "compiler_evany.h"

};


class Evaluator {
public:
	// ops highest byte is command
	//	0 - run command
	//	1 - load value to stack
	//	2 - load var to stack
	//	3 - pop stack to var
	//	4 - function call
	//	5 - jump always
	//	6 - pop and jump if zero
	//	7 - load string to stack (from names)
	vector<int>		ops;
	vector<string>	names;
	vector<double>	values;
	int				user_id;

	void Clear()
	{
		ops.clear();
		names.clear();
		values.clear();
		user_id = 0;
	}

	bool IsReady()
	{
		return ops.size()>0;
	}

	// moved to Compiler class
	//void Precompile(const char *code);
	//float Exec();
};
