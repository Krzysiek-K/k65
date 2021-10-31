
#include "stdafx.h"
#include "common.h"
#include "coltab_pal.h"
//TBC #include "coltab/ntsc.inc"


struct EvOp {
	int	id;
	const char *name;
};

static const EvOp EV_OPS[] = {
#include "gen/compiler_evops.inl"
	{0,NULL}
};



static Compiler *_context;



void EvalAny::Error(const char *s)
{
	_context->Error(format("[eval] %s",s));
}

string EvalAny::GetString() const
{
	if(type==ET_NUMBER) return format("%lf",value_f);
	if(type==ET_STRING) return value_s;
	if(type==ET_SECTION) return state.GetSectionName(value_i);
	return "";
}

string EvalAny::ToString() const
{
	if(type==ET_NUMBER) return format("number %lf",value_f);
	if(type==ET_STRING) return format("string \"%s\"",value_s.c_str());
	if(type==ET_SECTION) return format("section %s",state.GetSectionName(value_i).c_str());
	return "invalid type (internal error)";
}

double EvalAny::ToNumber() const
{
	if(type==ET_NUMBER) return value_f;
	Error(format("Can't convert %s to a number",ToString().c_str()));
	return 0;
}

AsmSection *EvalAny::ToSection() const
{
	if(type!=ET_SECTION) Error(format("Can't convert %s to a section",ToString().c_str()));
	AsmSection *sec = state.GetSection(value_i);
	if(!sec) Error("Value is invalid section index");
	return sec;
}


bool EvalAny::IsTrue() const
{
	if(type==ET_NUMBER) return (value_f!=0);
	if(type==ET_STRING) return (value_s.size()>0);
	return true;	// any other type is non-empty
}







float Compiler::make_color(float rf,float gf,float bf)
{
	int r = (int)max(0.f,min(255.f,rf*255));
	int g = (int)max(0.f,min(255.f,gf*255));
	int b = (int)max(0.f,min(255.f,bf*255));
	int best = 0;
	int berr = 1000000000;
	for(int i=0;i<128;i++)
	{
		int er = ((PAL[i]>>16)&0xFF)-r;
		int eg = ((PAL[i]>> 8)&0xFF)-g;
		int eb = ((PAL[i]    )&0xFF)-b;
		if(er<0) er=-er;
		if(eg<0) eg=-eg;
		if(eb<0) eb=-eb;
		if(er+eg+eb<berr)
		{
			berr=er+eg+eb;
			best = i<<1;
		}
	}
	return (float)best;
}



void Compiler::Eval_Precompile(Evaluator &ev,const char *code)
{
	map<string,int> names_map;
	map<double,int> values_map;
	vector<pair<int,string> > fix_jumps;
	map<string,int> fix_labels;

	ev.Clear();

	_context = this;

	//printf("> %s\n",code);

	while(1)
	{
		ParseWhitespace(code);
		const char *_begin = code;
		bool is_string = (*code=='"');
		string cmd = ParseString(code);
		if(cmd.size()<=0) break;

		if( is_string )
		{
			if( code-_begin>=2 && cmd.size()==(code-_begin)-2 && code[-1]=='"' )
			{
				ev.ops.push_back( (7<<24) | ev.names.size() );
				ev.names.push_back(cmd);
			}
			else
				Error(format("[internal] Invalid string '%s'",cmd.c_str()));
		}
		else if( cmd[0]=='@' && cmd.size()>=3 )
		{
			if(cmd[1]=='=' || cmd[1]=='?')
			{
				int id = 0;
				map<string, int>::iterator p = names_map.find(cmd.c_str()+2);
				if(p==names_map.end())
				{
					id = ev.names.size();
					ev.names.push_back(cmd.c_str()+2);
					names_map[cmd.c_str()+1] = id;
				}
				else
					id = p->second;
				id |= (cmd[1]=='=' ? 3 : 2)<<24;
				ev.ops.push_back(id);
			}
			else
				Error(format("[internal] Unknown evaluator operation '%s'",cmd.c_str()));
		}
		else if( cmd[0]=='J' && cmd.size()>=3 )
		{
			if(cmd[1]=='a' || cmd[1]=='z')
			{
				fix_jumps.push_back( pair<int,string>( ev.ops.size(), cmd.c_str()+2 ) );
				ev.ops.push_back( (cmd[1]=='a' ? 5 : 6)<<24 );
			}
			else
				Error(format("[internal] Unknown evaluator operation '%s'",cmd.c_str()));
		}
		else if( cmd[0]==':' && cmd.size()>=2 )
		{
			fix_labels[ cmd.c_str()+1 ] = ev.ops.size();
		}
		else if(cmd[0]=='#')
		{
			const char *s = cmd.c_str()+1;
			double f = 0;
			if(s[0]=='0' && (s[1]=='x' || s[1]=='b'))
				f = ParseInt(s);
			else
				f = ParseFloat(s);	// TBD: parse double

			int id = 0;
			map<double, int>::iterator p = values_map.find(f);
			if(p==values_map.end())
			{
				id = ev.values.size();
				ev.values.push_back(f);
				values_map[f] = id;
			}
			else
				id = p->second;
			id |= 1<<24;
			ev.ops.push_back(id);
		}
		else
		{
			// generic commands
			bool found = false;
			for(int i=0;EV_OPS[i].name;i++)
				if(EV_OPS[i].name==cmd)
				{
					ev.ops.push_back(EV_OPS[i].id);
					found = true;
					break;
				}
			if(!found)
			{
				// try finding in user functions
				map<string, Evaluator>::iterator pfn = eval_functions.find(cmd);
				if(pfn!=eval_functions.end())
				{
					ev.ops.push_back( pfn->second.user_id | (4<<24) );
					found = true;
				}
			}
			if(!found)
			{
				const char *s = cmd.c_str();
				int args = 0;
				if(*s=='!') s++;
				while(*s=='.') s++, args++;
				Error(format("Unknown evaluator function '%s' or function doesn't take %d arguments",s,args));
			}
		}
	}

	// fix jumps
	for(int i=0;i<(int)fix_jumps.size();i++)
	{
		pair<int, string> &j = fix_jumps[i];
		map<string, int>::iterator p = fix_labels.find(j.second);
		if(p==fix_labels.end())
			Error(format("[internal] Missing evaluator label '%s'",j.second.c_str()));
		ev.ops[j.first] |= p->second;
	}
}

string &Compiler::Eval_FixLocals(const string &code,const string &locals,int *local_count)
{
	static string buff;
	static map<string,string> replace;
	static vector<string> local_list;
	static vector<string> local_replaced;
	string tmp;

	_context = this;
	
	buff.clear();
	replace.clear();
	local_list.clear();
	local_replaced.clear();

	// parse locals
	const char *p = locals.c_str();
	while(1)
	{
		ParseString(p,tmp);
		if(tmp.size()<=0) break;
		local_list.push_back(tmp);
	}
	if(local_count!=NULL)
		*local_count = local_list.size();

	// allocate replacements
	local_replaced.resize(local_list.size());
	for(int i=0;i<(int)local_list.size();i++)
	{
		local_replaced[i] = format("__local_%d",eval_local_alloc++);

		// add replacements
		string &prev = local_list[i];
		string &repl = local_replaced[i];
		replace["@?"+prev] = "@?"+repl;
		replace["@="+prev] = "@="+repl;
	}

	// build local loading code
	for(int i=local_list.size()-1;i>=0;i--)
	{
		if(buff.size()>0)
			buff+=" ";
		buff += "@=";
		buff += local_replaced[i];
		buff += " ,";
	}

	// append code with replacement
	const char *s = code.c_str();
	while(1)
	{
		// parse
		ParseString(s,tmp);
		if(tmp.size()<=0) break;

		// find/replace
		map<string, string>::iterator found = replace.find(tmp);
		if(found!=replace.end())
			tmp = found->second;
		
		// append
		if(buff.size()>0)
			buff+=" ";
		buff += tmp;
	}

	return buff;
}

void Compiler::Eval_AddFunction(const string &name,const string &locals,const string &_code)
{
	static string code;
	static string fname;
	int num_locals = 0;

	_context = this;

	//printf("Function %s(%s):\n  %s\n",name.c_str(),locals.c_str(),_code.c_str());
	
	code = Eval_FixLocals(_code,locals,&num_locals);
	//printf("Function %s(%s):\n  %s\n",name.c_str(),locals.c_str(),code.c_str());

	fname = "!";
	for(int i=0;i<num_locals;i++)
		fname.push_back('.');
	fname += name;

	// check if we aren't shadowing something
	int error = 0;
	for(int i=0;EV_OPS[i].name;i++)
		if(EV_OPS[i].name==fname)
		{
			error = 1;	// found in system
			break;
		}
	if(!error && eval_functions.find(fname)!=eval_functions.end())
		error = 2;	// found in user functions
	if(error)
	{
		const char *s = fname.c_str();
		int args = 0;
		if(*s=='!') s++;
		while(*s=='.') s++, args++;
		if(error==1)	Error(format("Evaluator function '%s' with %d arguments is already predefined in the system",s,args));
		else			Error(format("Evaluator function '%s' with %d arguments is already defined",s,args));
	}

	// compile and add the function
	Evaluator &eval = eval_functions[fname];
	Eval_Precompile( eval, code.c_str() );
	eval.user_id = eval_fn_table.size();
	eval_fn_table.push_back( eval_functions.find(fname) );
}



EvalAny	Compiler::Eval_Index_1D(const EvalAny &arr,const EvalAny &index)
{
	AsmSection *tab = arr.ToSection();
	if(!tab->BuildRawTable()) Error(format("Section '%s' can't be converted to raw bytes yet",tab->name.c_str()));

	int addr = index.ToInt();
	if( addr>=0 && addr<(int)tab->raw_table.size() )
		return EvalAny(tab->raw_table[addr]);
	return EvalAny(0);
}

EvalAny	Compiler::Eval_Index_2D(const EvalAny &arr,const EvalAny &ix,const EvalAny &iy)
{
	AsmSection *tab = arr.ToSection();
	if(!tab->BuildRawTable()) Error(format("Section '%s' can't be converted to raw bytes yet",tab->name.c_str()));
	if(!tab->img_width || !tab->img_height) Error(format("Section '%s' doesn't specify 2D dimensions",tab->name.c_str()));

	int xp = ix.ToInt();
	int yp = iy.ToInt();
	int addr = -1;
	if( xp>=0 && xp<tab->img_width && yp>=0 && yp<tab->img_height)
		addr = xp + yp*tab->img_width;

	if( addr>=0 && addr<(int)tab->raw_table.size() )
		return EvalAny(tab->raw_table[addr]);
	return EvalAny(0);
}


void Compiler::Eval_RunVM(const Evaluator &ev)
{
#define SPOP			if(eval_stack.size()<1) Error("[internal] Eval stack underrun"); eval_stack.pop_back();
#define S(x)			( eval_stack.size()<=(x) ? Error("[internal] Eval stack underrun"),0 : 0, eval_stack[eval_stack.size()-1-(x)] )
#define BINARY(op)		S(1)=S(1) op S(0); SPOP
#define BITBINARY(op)	S(1)=S(1).ToInt() op S(0).ToInt(); SPOP
#define LOGBINARY(op)	S(1)=(S(1).ToNumber()!=0) op (S(0).ToNumber()!=0); SPOP
#define NUMFUNC1(fn)	S(0)=fn(S(0).ToNumber());
#define NUMFUNC2(fn)	S(1)=fn(S(1).ToNumber(),S(0).ToNumber()); SPOP
#define NUMFUNC3(fn)	S(2)=fn(S(2).ToNumber(),S(1).ToNumber(),S(0).ToNumber()); SPOP SPOP

	int pos = 0;
	_context = this;

	while(pos<(int)ev.ops.size())
	{
		int op = ev.ops[pos++];
		if( (op>>24)==1 )	// load value
		{
			op&=0xFFFFFF;
			if(op>=(int)ev.values.size())
				Error(format("[internal] Invalid evaluator value index %d",op));
			eval_stack.resize(eval_stack.size()+1);
			eval_stack[eval_stack.size()-1].SetF(ev.values[op]);
		}
		else if( (op>>24)==2 )	// get variable
		{
			op&=0xFFFFFF;
			if(op>=(int)ev.names.size())
				Error(format("[internal] Invalid evaluator name index %d (get)",op));
			eval_stack.push_back(getevalvar(ev.names[op].c_str()));
		}
		else if( (op>>24)==3 )	// set variable
		{
			op&=0xFFFFFF;
			if(op>=(int)ev.names.size())
				Error(format("[internal] Invalid evaluator name index %d (set)",op));
			setevalvar(ev.names[op].c_str(),S(0));
		}
		else if( (op>>24)==4 )	// call function
		{
			op&=0xFFFFFF;
			if(op>=(int)eval_fn_table.size())
				Error(format("[internal] Invalid evaluator function index %d (set)",op));
			Eval_RunVM( eval_fn_table[op]->second );
		}
		else if( (op>>24)==5 )	// jump always
		{
			op&=0xFFFFFF;
			if(op>(int)ev.ops.size())
				Error("[internal] Jump target outside code range");
			pos = op;
		}
		else if( (op>>24)==6 )	// pop and jump if zero
		{
			op&=0xFFFFFF;
			if(op>(int)ev.ops.size())
				Error("[internal] Jump target outside code range");
			if( S(0).IsTrue() == false )
				pos = op;
			SPOP
		}
		else if( (op>>24)==7 )	// load string to stack (from names)
		{
			op&=0xFFFFFF;
			if(op>=(int)ev.names.size())
				Error("[internal] String index outside range");
			eval_stack.push_back( EvalAny(ev.names[op]) );
		}
		else //if( (op>>24)==0 )
		{
			switch(op)
			{
			case 1:	//	,		pop one value
				SPOP break;
			case 2:	//	?:		ternary operation (3->1)
				S(2)=( S(2).IsTrue() ? S(1) : S(0) ); SPOP SPOP break;
			case 3://	!..max (a,b)	Maximum
				S(1)=( S(1)>S(0) ? S(1) : S(0) ); SPOP break;
			case 4://	!..min (a,b)	Minimum
				S(1)=( S(1)<S(0) ? S(1) : S(0) ); SPOP break;
			case 5://	|		bitwise or
				BITBINARY(|); break;
			case 6://	^		bitwise xor
				BITBINARY(^); break;
			case 7://	&		bitwise and
				BITBINARY(&); break;
			case 8://	<
				BINARY(<); break;
			case 9://	>
				BINARY(>); break;
			case 10://	>=
				BINARY(>=); break;
			case 11://	<=
				BINARY(<=); break;
			case 12://	==
				BINARY(==); break;
			case 13://	!=
				BINARY(!=); break;
			case 14://	+
				BINARY(+); break;
			case 15://	-
				BINARY(-); break;
			case 16://	*
				BINARY(*); break;
			case 17://	/
				BINARY(/); break;
			case 18://	%		modulo
				S(1)=fmod( fmod(S(1).ToNumber(),S(0).ToNumber()) + S(0).ToNumber(), S(0).ToNumber() ); SPOP break;
			case 19://	~-		negate topmost value
				S(0)=-S(0); break;
			case 20://	!.floor (x)		Round down to nearest integer
				NUMFUNC1(floor) break;
			case 21://	!.ceil ( x )	Round up to nearest integer
				NUMFUNC1(ceil) break;
			case 22://	!.round ( x )	Round to nearest integer
				S(0)=floor(S(0).ToNumber()+.5f); break;
			case 23://	!.frac ( x )	Get fractional part ( ''x-floor(x)'' )
				S(0)=S(0).ToNumber()-floor(S(0).ToNumber()); break;
			case 24://	!.sin ( x )		Sinus
				NUMFUNC1(sin); break;
			case 25://	!.cos ( x )		Cosinus
				NUMFUNC1(cos); break;
			case 26://	!rnd ( )			Random value ''0 <= x < 1''
				eval_stack.push_back(float(rand())/0x8000); break;
			case 27://	!...clamp ( x , min, max )		Clamp ''x'' to range ''min'' to ''max''
				if(S(2)>S(0)) S(2)=S(0);
				if(S(2)<S(1)) S(2)=S(1);
				SPOP SPOP
				break;
			case 28://	!...color ( r, g, b)	Return palette index for nearest color to color (''r'',''g'',''b'')
				S(2)=make_color((float)S(2).ToNumber(),(float)S(1).ToNumber(),(float)S(0).ToNumber());
				SPOP SPOP
				break;
			case 29://	!.sqrt ( x )			Square root
				NUMFUNC1(sqrt); break;
			case 30://	!..pow ( x, y )			Power function
				NUMFUNC2(pow); break;
			case 31://	!.acos ( x )			Arcus cosinus
				NUMFUNC1(acos); break;
			case 32://	!.asin ( x )			Arcus sinus
				NUMFUNC1(asin); break;
			case 33://	~		bitwise topmost value
				S(0)=~S(0).ToInt(); break;
			case 34://	!.color ( x )			Return  palette index for nearest color specified in format ''0xRRGGBB''
				{
					vec3 col = vec3::from_rgb(S(0).ToInt());
					S(0)=make_color(col.x,col.y,col.z);
				}
				break;
			case 35://	!..index ( tab , x )	1-dimensional indexing operator ( same as ''tab''[''x''] )
				S(1)=Eval_Index_1D(S(1),S(0));
				SPOP
				break;
			case 36://	!...index ( tab, x, y )		2-dimensional indexing operator ( same as ''tab''[''x'',''y''] )
				S(2)=Eval_Index_2D(S(2),S(1),S(0));
				SPOP SPOP
				break;
			case 37://	!..addbyte ( sec, b )		Add byte ''b'' to section ''sec''
				S(1).ToSection()->Assemble(format("    .byte   #$%02X",S(0).ToInt()&0xFF));
				S(1)=S(0); SPOP
				break;
			case 38://	!.size ( sec )				Current size of section ''sec''
				{
					AsmSection *sec = S(0).ToSection();
					if(!sec->BuildRawTable())
						Error(format("Section '%s' can't be converted to raw bytes yet",sec->name.c_str()));
					S(0) = EvalAny( sec->raw_table.size() );
				}
				break;
			case 39://	!.print ( msg )				Print message ''msg''
				printf("%s\n",S(0).GetString().c_str());
				break;
			case 40://	!.error ( err )				Print error message ''err'' ane terminate compilation
				Error(S(0).GetString().c_str());
				break;
			case 41://	~!		logical not
				S(0)=(S(0).ToNumber()==0 ? 1.f : 0.f); break;
			case 42://	>>		bit shift right
				BITBINARY(>>); break;
			case 43://	<<		bit shift left
				BITBINARY(<<); break;
			case 44://	||
				LOGBINARY(||); break;
			case 45://	&&
				LOGBINARY(&&); break;

			default:
				Error(format("[internal] Invalid evaluator opcode %d:%d",op>>24,op&0xFFFFFF));
				break;
			}
		}
	}
}

float Compiler::Eval_Exec(const Evaluator &ev,bool needs_value)
{
	_context = this;
	eval_stack.clear();

	Eval_RunVM(ev);

	if(eval_stack.size()!=1)
		Error(format("[internal] Invalid evaluator stack state after execution (size %d)",eval_stack.size()));

	return needs_value ? (float)S(0).ToNumber() : 0;
}
