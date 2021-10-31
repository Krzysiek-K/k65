
#pragma once



enum addrmode_t {
	AM_NONE,
	AM_ACC,
	AM_X,
	AM_Y,
	AM_S,
	AM_VAR,
	AM_IMM,
	AM_OFS_LO,
	AM_OFS_HI,
	AM_VAR_X,
	AM_VAR_Y,
	AM_IND,
	AM_IND_X,
	AM_IND_Y,
	NUM_ADDR_MODES
};

#define INVALID_VALUE		(int(0x80000000))



// -------------------------------- AndedStack --------------------------------


// stack of binary values that knows AND result of its contents
class AndedStack {
public:
	AndedStack() : stack_size(0), bottom_ones_count(0) {}

	void clear()				{ stack_size=0; bottom_ones_count=0; }
	bool get_and()				{ return (bottom_ones_count==stack_size); }
	void push(bool value) {
		if(value && bottom_ones_count==stack_size) bottom_ones_count++;
		stack_size++;
	}
	bool pop() {
		if(stack_size<=0) return false;
		stack_size--;
		if(bottom_ones_count>stack_size) bottom_ones_count=stack_size;
		return true;
	}
	bool set_top(bool value) {
		if(stack_size<=0) return false;
			 if( value && bottom_ones_count==stack_size-1) bottom_ones_count++;
		else if(!value && bottom_ones_count==stack_size  ) bottom_ones_count--;
		return true;
	}

private:
	int	stack_size;
	int	bottom_ones_count;
};






// -------------------------------- Compiler --------------------------------


class Compiler : public IErrorHandler {
public:

	Compiler() : code(NULL) {}
	~Compiler() { delete code; }
    
	void InitCompile();
	void SetBank(const char *bank);
	void SetVar(const char *name,double value)		{ setevalvar(name,value); }
	const char *Compile(const char *codetext);

	//string SectionName(int index);

private:
	friend struct EvalAny;
    typedef string	symb_t;

	struct Arg {
		int		mode;
		int		var_id;
		int		value;
	};

    enum {
        VT_UNKNOWN,
        VT_VAR,
        VT_CONST,
		VT_LABEL,
		VT_EVAL_VAR,
		VT_RESERVED,
		VT_IMAGE,
		VT_BINARY
    };

	struct Var {
        int     type;
		string	name;
		bool	has_value;
		int		value;
		EvalAny	value_eval;
		int		size;

        Var() : type(VT_UNKNOWN), has_value(false), value(-1), size(0) {}
	};

	struct Repeat {
		string					op;
		AsmSection::Location	loc;
		int						line;
	};

	enum {
		PREPROC_DEFAULT,
		PREPROC_IF_TAKEN,
		PREPROC_IF_NOT_TAKEN,
		PREPROC_ELSE_TAKEN,
		PREPROC_ELSE_NOT_TAKEN,
		PREPROC_ELIF_DO_NOT_TAKE,
	};

	const char				*src;
	int						line;
	int						label_id_gen;
	int						var_addr;
    string					error;
	vector<Var>				vars;
	vector<string>			comms;
	vector<string>			break_labels;
	vector<Repeat>			delayed_repeats;
	string					cur_bank;
	string					charset;
	Evaluator				evaluator;
	string					movmap[NUM_ADDR_MODES][NUM_ADDR_MODES];
    Imager					img;
	vector<uint8_t>			binary;
	AndedStack				parser_enabled;
	vector<int>				preproc_state_stack;
	int						preproc_state;
	map<string,Evaluator>	eval_functions;
	vector<map<string,Evaluator>::iterator>	eval_fn_table;
	vector<EvalAny>			eval_stack;
	int						eval_local_alloc;
	Evaluator				tmp_eval;
	int						local_index;


public:
	// affected from scripts
	AsmSection				*code;

private:

    int num(const string &s) { return getnum(s.c_str()); }

	string arg(int mode,const string &arg="");
	string argto(int mode,const string &arg);
	string argaddr(const string &arg);
	int    ident2value(const string &var,bool &found,Var **pvar=NULL);
	int    ident2value(const string &var);
	string ident2arg(const string &var,const string &offs,bool negate_offs);
	int   getnum(const char *s);
	int   getvar(const char *s,int &offs,bool is_label);
	const EvalAny &getevalvar(const char *s);
	void setevalvar(const char *s,const EvalAny &val);
	void setevalvar(const char *s,double val)				{ EvalAny v; v.SetF(val); setevalvar(s,v); }
	Arg  getarg(const char *s);
	Var *find_var(const string &name,bool allow_create);
	string doeval(const string &s,bool needs_value);
	void settmpeval(const string &s);
	string dotmpeval(bool needs_value);
	void var(const string &name,const string &addr,bool is_const,int size,bool verbose=false);
	void init_section(const string &name);
	void datavalue(const string &v);
	void datastr(const string &v);
	void addop(const char *s,const Arg &a);
	void opsimp(const string &cmd);
	void opnop(int wait);
	void opunary(const string &cmd,const Arg &a);
	void opunary(const string &cmd,const string &arg);
	void oparith(const string &cmd,const string &arg,char acc);
	void opmov(const Arg &da,const Arg &sa);
	void opmov(const string &dst,const string &src);
    void opmov3(const string &a1,const string &a2,const string &a3);
	void opmovseq(const string &movseq);
	string invert_branch(const string &cmd);
	void opbranch(const string &cmd,const string &lab);
	void opbranch_repeat(const string &cmd,const string &lab,AsmSection::Location loc);
	void oplabel(const string &lab);
	string genlabel();
	string flag2jump(const string &flag,bool flag_state);
	void opend();
	void op_delayed_repeat(const string &cmd);
	void check_loop_jumps();
	void flush_loop_jumps(const string &br2_multi_data);
	void makesection(const string &name,const string &type);
	void makeimagesection(const string &name, string path);
	void makebinarysection(const string &name,string path);
	void setalign(int a,int offs=0);
	void setaddress(int addr);
	void dofunction(const string &id, bool farcall);
	void dofarjump(const string &id);
	void pulltile();
	void loadbinary(const char *path);
	void pullbinary();

	string make_multi(const string &a1,int a2) { return format("%s %d",a1.c_str(),a2); }
	string make_multi(const string &a1,int a2,int a3) { return format("%s %d %d",a1.c_str(),a2,a3); }
	string multi_get_1(const string &m) { const char *s = m.c_str(); return ParseString(s); }
	string multi_get_2(const string &m) { const char *s = m.c_str(); ParseString(s); return ParseString(s); }
	int    multi_get_2i(const string &m) { const char *s = m.c_str(); ParseString(s); return ParseInt(s); }

	string unquote(const string &s)
	{
		if(s.size()>=2 && s[0]=='"' && s[s.size()-1]=='"')
			return string(s.begin()+1,s.end()-1);
		return s;
	}

	void pp_if(bool result);
	void pp_else();
	void pp_elif(bool result);
	void pp_endif();



    void   LineStart(const char *s);
    int    GetChar();

	AsmSection &GetCode() {
		if( !code ) Error("[internal] No active section");
		return *code;
	}

public:
    virtual void Error(const char *e);
    virtual void Warn(const char *e);
	void   Error(const string &e)	{ Error(e.c_str());	}
	void   Warn(const string &e)	{ Warn(e.c_str());	}

private:
	symb_t RunParser();
	void   RunLinker();

	// evaluator
public:
	float  make_color(float rf,float gf,float bf);

private:
	void	Eval_Precompile(Evaluator &ev,const char *code);
	string	&Eval_FixLocals(const string &code,const string &locals,int *local_count=NULL);
	void	Eval_AddFunction(const string &name,const string &locals,const string &code);
	EvalAny	Eval_Index_1D(const EvalAny &arr,const EvalAny &index);
	EvalAny	Eval_Index_2D(const EvalAny &arr,const EvalAny &ix,const EvalAny &iy);
	void	Eval_RunVM(const Evaluator &ev);
	float	Eval_Exec(const Evaluator &ev,bool needs_value);


};

extern Compiler cmp;
