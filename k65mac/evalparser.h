
#pragma once




class EvalParser {
public:
	enum vartype_t {
		VT_NONE = 0,
		VT_ITERATOR,
		VT_LOCAL,
		VT_CONST,
	};

	struct Var {
		vartype_t	type;
		float		value;

		Var() : type(VT_NONE), value(0) {}
	};

	struct Func {
		struct Arg {
			string	name;
			bool	is_ref;
		};

		vector<Arg>	args;
		string		code;
	};

	map<string,float>	vars;

	void Clear() { vars.clear(); names.clear(); name_search.clear(); }
    float Parse(const char *s);

	static float make_color(float rf,float gf,float bf);

private:

	typedef float symb_t;

    const char          *src;
    vector<string>      names;
    map<string,int>     name_search;
	
	float getnum(const char *s);
    float getvar(const char *s);
    int   string2id(const char *s);
    const char *id2string(int id);

    int    GetChar();
    void   Error(const char *e);
    symb_t RunParser();


};
