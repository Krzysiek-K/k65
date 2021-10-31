
#include "stdafx.h"
#include "common.h"



Compiler cmp;



//static const char *REGS[] = {
//"$0x0",
//"VSYNC",		// $00   0000 00x0   Vertical Sync Set-Clear
//"VBLANK",		// $01   xx00 00x0   Vertical Blank Set-Clear
//"WSYNC",		// $02   ---- ----   Wait for Horizontal Blank
//"RSYNC",		// $03   ---- ----   Reset Horizontal Sync Counter
//"NUSIZ0",		// $04   00xx 0xxx   Number-Size player/missle 0
//"NUSIZ1",		// $05   00xx 0xxx   Number-Size player/missle 1
//"COLUP0",		// $06   xxxx xxx0   Color-Luminance Player 0
//"COLUP1",       // $07   xxxx xxx0   Color-Luminance Player 1
//"COLUPF",       // $08   xxxx xxx0   Color-Luminance Playfield
//"COLUBK",       // $09   xxxx xxx0   Color-Luminance Background
//"CTRLPF",       // $0A   00xx 0xxx   Control Playfield, Ball, Collisions
//"REFP0",        // $0B   0000 x000   Reflection Player 0
//"REFP1",        // $0C   0000 x000   Reflection Player 1
//"PF0",          // $0D   xxxx 0000   Playfield Register Byte 0
//"PF1",          // $0E   xxxx xxxx   Playfield Register Byte 1
//"PF2",          // $0F   xxxx xxxx   Playfield Register Byte 2
//"RESP0",        // $10   ---- ----   Reset Player 0
//"RESP1",        // $11   ---- ----   Reset Player 1
//"RESM0",        // $12   ---- ----   Reset Missle 0
//"RESM1",        // $13   ---- ----   Reset Missle 1
//"RESBL",        // $14   ---- ----   Reset Ball
//"AUDC0",        // $15   0000 xxxx   Audio Control 0
//"AUDC1",        // $16   0000 xxxx   Audio Control 1
//"AUDF0",        // $17   000x xxxx   Audio Frequency 0
//"AUDF1",        // $18   000x xxxx   Audio Frequency 1
//"AUDV0",        // $19   0000 xxxx   Audio Volume 0
//"AUDV1",        // $1A   0000 xxxx   Audio Volume 1
//"GRP0",         // $1B   xxxx xxxx   Graphics Register Player 0
//"GRP1",         // $1C   xxxx xxxx   Graphics Register Player 1
//"ENAM0",        // $1D   0000 00x0   Graphics Enable Missle 0
//"ENAM1",        // $1E   0000 00x0   Graphics Enable Missle 1
//"ENABL",        // $1F   0000 00x0   Graphics Enable Ball
//"HMP0",         // $20   xxxx 0000   Horizontal Motion Player 0
//"HMP1",         // $21   xxxx 0000   Horizontal Motion Player 1
//"HMM0",         // $22   xxxx 0000   Horizontal Motion Missle 0
//"HMM1",         // $23   xxxx 0000   Horizontal Motion Missle 1
//"HMBL",         // $24   xxxx 0000   Horizontal Motion Ball
//"VDELP0",       // $25   0000 000x   Vertical Delay Player 0
//"VDELP1",       // $26   0000 000x   Vertical Delay Player 1
//"VDELBL",       // $27   0000 000x   Vertical Delay Ball
//"RESMP0",       // $28   0000 00x0   Reset Missle 0 to Player 0
//"RESMP1",       // $29   0000 00x0   Reset Missle 1 to Player 1
//"HMOVE",        // $2A   ---- ----   Apply Horizontal Motion
//"HMCLR",        // $2B   ---- ----   Clear Horizontal Move Registers
//"CXCLR",        // $2C   ---- ----   Clear Collision Latches
//
//"$0x0",
//"CXM0P",	    // $00  xx00 0000       Read Collision  M0-P1   M0-P0
//"CXM1P",		// $01  xx00 0000                       M1-P0   M1-P1
//"CXP0FB",		// $02  xx00 0000                       P0-PF   P0-BL
//"CXP1FB",		// $03  xx00 0000                       P1-PF   P1-BL
//"CXM0FB",		// $04  xx00 0000                       M0-PF   M0-BL
//"CXM1FB",		// $05  xx00 0000                       M1-PF   M1-BL
//"CXBLPF",		// $06  x000 0000                       BL-PF   -----
//"CXPPMM",		// $07  xx00 0000                       P0-P1   M0-M1
//"INPT0",		// $08  x000 0000       Read Pot Port 0
//"INPT1",		// $09  x000 0000       Read Pot Port 1
//"INPT2",		// $0A  x000 0000       Read Pot Port 2
//"INPT3",		// $0B  x000 0000       Read Pot Port 3
//"INPT4",		// $0C	x000 0000       Read Input (Trigger) 0
//"INPT5",		// $0D	x000 0000       Read Input (Trigger) 1
//
//"$0x280",
//"SWCHA",		// $280     Port A data register for joysticks:
//				//			Bits 4-7 for player 1.  Bits 0-3 for player 2.
//
//"SWACNT",       // $281     Port A data direction register (DDR)
//"SWCHB",        // $282		Port B data (console switches)
//"SWBCNT",       // $283     Port B DDR
//"INTIM",        // $284		Timer output
//		        
//"TIMINT",     	// $285
//		        
//"$0x294",
//"TIM1T",		// $294		set 1 clock interval
//"TIM8T",        // $295     set 8 clock interval
//"TIM64T",       // $296     set 64 clock interval
//"T1024T",       // $297     set 1024 clock interval
//NULL
//};



struct AddrMode {
	int mode;
	const char *op;
	int bytes;
	int	lda, sta, ldx, stx, ldy, sty;
	int c10, idc;
	int bit, cpx;
	// ari == lda
};

static AddrMode ADDRMODES[] = {
//						 len LDA STA LDX STX LDY STY 10  IDC BIT CPX
	{AM_NONE,	"?"},
	{AM_ACC,	"A"		,0	,0	,0	,0	,0	,0	,0	,1	,0	,0	,0	},
	{AM_X,		"X"},
	{AM_Y,		"Y"},
	{AM_S,		"S"},
	{AM_VAR,	"v"		,-1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,1	},
	{AM_IMM,	"#$h"	,1	,1	,0	,1	,0	,1	,0	,0	,0	,0	,1	},
	{AM_OFS_LO,	"#<(v)"	,1	,1	,0	,1	,0	,1	,0	,0	,0	,0	,1	},
	{AM_OFS_HI,	"#>(v)"	,1	,1	,0	,1	,0	,1	,0	,0	,0	,0	,1	},
	{AM_VAR_X,	"v,X"	,-1	,1	,1	,0	,0	,1	,1	,1	,1	,0	,0	},
	{AM_VAR_Y,	"v,Y"	,-1	,1	,1	,1	,1	,0	,0	,0	,0	,0	,0	},
	{AM_IND,	"(v)"	},
	{AM_IND_X,	"(v,X)"	,1	,1	,1	,0	,0	,0	,0	,0	,0	,0	,0	},
	{AM_IND_Y,	"(v),Y"	,1	,1	,1	,0	,0	,0	,0	,0	,0	,0	,0	},
	{0,NULL}
};


template<class T>
void append(vector<T> &dst,const vector<T> &src)
{
	dst.insert(dst.end(),src.begin(),src.end());
}

static bool _isnumber(const string &str)
{
	const char *s = str.c_str();
	if(*s=='-') s++;
	return (*s>='0' && *s<='9');
}



string Compiler::arg(int mode,const string &arg)
{
	return format("%c%s",mode+'a',arg.c_str());
}

string Compiler::argto(int mode,const string &arg)
{
	string tmp = arg;
	if(tmp.size()<0)
		Error(format("Empty string does not represent valid memory location"));
	if(tmp[0]!=(AM_VAR+'a'))
		Error(format("String '%s' does not represent valid memory location",tmp.c_str()+1));
	tmp[0] = mode+'a';
	return tmp;
}

string Compiler::argaddr(const string &arg)
{
	if(arg.size()<0)
		Error(format("Empty string does not represent valid memory location"));
	if(arg[0]!=(AM_VAR+'a'))
		Error(format("String '%s' does not represent valid memory location",arg.c_str()+1));
	return arg.c_str()+1;
}

int Compiler::ident2value(const string &var,bool &found,Var **pvar)
{
	if( _isnumber(var) )
	{
		found = true;
		if(pvar) *pvar = NULL;
		return getnum(var.c_str());
	}

	Var *v = find_var(var,true);
	if(pvar) *pvar = v;
//	if(!v) Error(format("Unknown variable '%s'",var.c_str()));
	if(v->type==VT_CONST)
	{
		if(!v->has_value) Error(format("Constant '%s' doesn't have value assigned",var.c_str()));
		found = true;
		return v->value;
	}
	else if(v->type==VT_EVAL_VAR)
	{
		if(!v->has_value) Error(format("Variale '%s' doesn't have value assigned",var.c_str()));
		if(v->value_eval.type!=ET_NUMBER) Error(format("Variale '%s' is not a number",var.c_str()));
		found = true;
		return int(floor(v->value_eval.value_f+.5f));
	}

	found = false;
	return INVALID_VALUE;
}

int Compiler::ident2value(const string &var)
{
	bool found = false;
	int val = ident2value(var,found,NULL);
	if(!found)
		Error(format("Identifier '%s' is of unknown or invalid type and can't be used as here",var.c_str()));

	return val;
}

string Compiler::ident2arg(const string &var,const string &offs,bool negate_offs)
{
	int offset_value = ident2value(offs);
	if(negate_offs)
		offset_value = -offset_value;

	bool found = false;
	Var *v = NULL;
	int imm = ident2value(var,found,&v);
	if(found)
		return arg(AM_IMM,format("%d",imm+offset_value));

	if(offset_value>0) return arg(AM_VAR,format("%s+%d",var.c_str(), offset_value));
	if(offset_value<0) return arg(AM_VAR,format("%s-%d",var.c_str(),-offset_value));
	return arg(AM_VAR,var.c_str());
}

int Compiler::getnum(const char *s)
{
	int base = 10;
	int v = 0;
	int sign = 1;
	const char *b = s;

	if(*s=='-') s++, sign=-1;

	if(*s=='0' && s[1])
	{
		s++;
		if(*s=='x') base=16, s++;
		else if(*s=='b') base=2, s++;
		else Error(format("String '%s' is not a number (invalid base)",b).c_str());
	}

	while(*s)
	{
		int d=-1;
			 if(*s>='0' && *s<='9') d = *s - '0';
		else if(*s>='a' && *s<='z') d = *s - 'a' + 10;
		else if(*s>='A' && *s<='Z') d = *s - 'A' + 10;
		else Error(format("String '%s' is not a number (invalid character)",b).c_str());

		if(d>=base)
			Error(format("String '%s' is not a number (digit exceeds base)",b).c_str());

		v = v*base + d;

		s++;
	}

	return v*sign;
}

int Compiler::getvar(const char *s,int &offs,bool is_label)
{
	const char *b = s;
	for(;*s;s++)
	{
		if(*s>='0' && *s<='9') continue;
		if(*s>='a' && *s<='z') continue;
		if(*s>='A' && *s<='Z') continue;
		if(*s=='_') continue;
		break;
	}
	string vn(b,s);

	Var *v = find_var(vn,false);
	if(!v && is_label)
		v = find_var(vn,true);
	if(!v)
		Error(format("Undeclared variable '%s'",vn.c_str()).c_str());

	offs = 0;
		 if(*s=='-') offs=-getnum(s+1);
	else if(*s=='+') offs= getnum(s+1);
	else if(!*s) {}
	else Error(format("Expression '%s' can't be used as variable address",b).c_str());

	int id = v - &vars[0];
	return id;
}

const EvalAny &Compiler::getevalvar(const char *s)
{
	Var *v = find_var(s,false);
	if(!v) Error(format("Undeclared eval variable '%s'",s));

	switch(v->type)
	{
	case VT_CONST:
		if(!v->has_value) Error(format("Variable '%s' doesn't have any value assigned",s));
		v->value_eval.SetF(v->value);
		return v->value_eval;
	case VT_EVAL_VAR:
		if(!v->has_value) Error(format("Variable '%s' doesn't have any value assigned",s));
		return v->value_eval;
	case VT_LABEL:	// section
	case VT_IMAGE:	// section
	case VT_BINARY:	// section
		{
			AsmSection *sec = state.FindSection(v->name.c_str());
			if(!sec) Error(format("Label '%s' doesn't represent a compiled section",s));
			v->value_eval.type = ET_SECTION;
			v->value_eval.value_i = state.GetSectionId(sec);
			if(v->value_eval.value_i==-1) Error(format("Label '%s' doesn't represent a compiled section",s));
			return v->value_eval;
		}
		
	default:
		Error(format("Incorrect type of eval variable '%s'",s));
	}
	Error("[internal] Unknown variable type");

	static EvalAny a;
	return a;
}

void Compiler::setevalvar(const char *s,const EvalAny &val)
{
	Var *v = find_var(s,true);
	if(v->type==VT_UNKNOWN)
		v->type=VT_EVAL_VAR;
	if(v->type!=VT_CONST && v->type!=VT_EVAL_VAR)
		Error(format("Incorrect type of eval variable '%s'",s));
	if(v->type==VT_CONST)
		Error(format("Can't assign value to const '%s'",s));
	v->has_value = true;
	v->value_eval = val;
}

Compiler::Arg Compiler::getarg(const char *s)
{
	Arg a;
	a.mode = *s ? *s++ - 'a' : AM_NONE;
	a.var_id = -1;
	a.value = 0;

	switch(a.mode)
	{
	case AM_VAR:
		a.var_id = getvar(s,a.value,false);
		if(vars[a.var_id].type == VT_CONST)
		{
			if(vars[a.var_id].has_value)
				a.value += vars[a.var_id].value;
			a.mode = AM_IMM;
		}
		else if(vars[a.var_id].type == VT_EVAL_VAR)
		{
			if(vars[a.var_id].has_value)
			{
				Var &v = vars[a.var_id];
				if(v.value_eval.type!=ET_NUMBER) Error(format("Variable '%s' is not a number",v.name.c_str()));
				a.value += int(floor(v.value_eval.value_f+.5f));
			}
			a.mode = AM_IMM;
		}
		break;

	case AM_VAR_X:
	case AM_VAR_Y:
	case AM_IND:
	case AM_IND_X:
	case AM_IND_Y:
	case AM_OFS_LO:
	case AM_OFS_HI:
		a.var_id = getvar(s,a.value,true);
        if(vars[a.var_id].type == VT_CONST)
			Error("Constant used as variable");
        if(vars[a.var_id].type == VT_EVAL_VAR)
			Error("Compile-time variable used as code variable");
		break;

	case AM_IMM:
		a.value = getnum(s);
		break;
	}

	return a;
}

string Compiler::doeval(const string &s,bool needs_value)
{
	int v = 0;
	Evaluator ev;
	Eval_Precompile(ev,s.c_str());
	v = int(floor(Eval_Exec(ev,needs_value)+.5f));

	return format("%d",v);
}

void Compiler::settmpeval(const string &s)
{
	Eval_Precompile(tmp_eval,s.c_str());
}

string Compiler::dotmpeval(bool needs_value)
{
	int v = int(floor(Eval_Exec(tmp_eval,needs_value)+.5f));
	return format("%d",v);
}


Compiler::Var *Compiler::find_var(const string &name,bool allow_create)
{
	for(int i=0;i<(int)vars.size();i++)
		if(vars[i].name==name)
			return &vars[i];
	if(!allow_create)
		return NULL;

	Var v;
	v.name = name;
	vars.push_back(v);
	return &vars[vars.size()-1];
}

void Compiler::var(const string &name,const string &addr,bool is_const,int size,bool verbose)
{
	Var *v = find_var(name,true);
	if(v->type!=VT_UNKNOWN || v->has_value || v->size)
		Error(format("Symbol '%s' redeclared",name.c_str()).c_str());
	v->name = name;
	v->size = size;
	if(addr.size()>0)
	{
		v->value = getnum(addr.c_str());
		v->has_value = true;
	}
	else if(!is_const)
	{
		// allocate right after previous var
		v->value = var_addr;
		v->has_value = true;
	}
	v->type = is_const ? VT_CONST : VT_VAR;

	if(v->type==VT_VAR && v->has_value)
	{
		state.AddLabel(v->name.c_str(), v->value, code, false, this);

		var_addr = v->value + v->size;
	}

	if(verbose && !is_const && v->has_value)
		if(v->size==1)
			printf("Variable '%s' located at $%02X\n",v->name.c_str(),v->value);
		else
			printf("Variable '%s' located at $%02X..$%02X\n",v->name.c_str(),v->value,v->value+v->size-1);
}

void Compiler::init_section(const string &name)
{
	charset.clear();
	evaluator.Clear();

	code = state.CreateSection();
	code->Clear();
	code->name = name;
	code->bank_list.push_back( cur_bank );
}

void Compiler::datavalue(const string &v)
{
	int n = getnum(v.c_str());
	if(evaluator.IsReady())
	{
		setevalvar("x",n);
		n = int(Eval_Exec(evaluator,true))&0xFF;
	}
	if( !code ) Error("[internal] No active section");
	code->Assemble(format("    .byte   #$%02X",n));
}

void Compiler::datastr(const string &v)
{
	if(v.size()<2 || v[0]!='"' || v[v.size()-1]!='"') Error("Bad string");
	
	string tmp;
	for(int i=1;i<(int)v.size()-1;i++)
	{
		int ch = 0;
		for(int j=0;j<(int)charset.size();j++)
			if(charset[j]==v[i])
			{
				ch = j;
				break;
			}

		if(evaluator.IsReady())
		{
			setevalvar("x",ch);
			ch = int(Eval_Exec(evaluator,true))&0xFF;
		}
		if( !code ) Error("[internal] No active section");
		code->Assemble(format("    .byte   #$%02X",ch));
	}
}



void Compiler::addop(const char *s,const Arg &a)
{
	string cmd = "    ";
	while(*s)
	{
		if(*s=='v')
		{
			if(a.var_id<0) Error("[internal] Missing variable");
			cmd += vars[a.var_id].name;
			if(a.value!=0) cmd += format("%+d",a.value);
		}
		else if(*s=='h') cmd += format("%02X",a.value);
		else if(*s=='?') {}
		else cmd.push_back(*s);
		s++;
	}

	try {
		if( !code ) Error("[internal] No active section");
		code->Assemble(cmd);
	}
	catch(const char *e)
	{
		Error(string(e));
	}
}

void Compiler::opsimp(const string &cmd)
{
	if( !code ) Error("[internal] No active section");
	code->Assemble(format("    %s",cmd.c_str()));
}

void Compiler::opnop(int wait)
{
	if(wait<0) Error(format("Negative wait value %d",wait).c_str());
	if(wait==1) Error("1-cycle NOP is not realizable");
	if(wait>256) Error(format("Wait value %d is more than 256",wait).c_str());
	if(wait&1) opsimp("NOP     $80"), wait-=3;
	while(wait>0)
		opsimp("NOP"), wait -= 2;
}

void Compiler::opunary(const string &cmd,const Arg &a)
{
	if(cmd=="INC" && a.mode==AM_X) { opsimp("INX"); return; }
	if(cmd=="DEC" && a.mode==AM_X) { opsimp("DEX"); return; }
	if(cmd=="INC" && a.mode==AM_Y) { opsimp("INY"); return; }
	if(cmd=="DEC" && a.mode==AM_Y) { opsimp("DEY"); return; }

	int flag = (cmd=="INC" || cmd=="DEC") ? ADDRMODES[a.mode].idc : ADDRMODES[a.mode].c10;
//	if(!flag)
//		Error(format("Unary operation %s doesn't work in mode %s",cmd.c_str(),ADDRMODES[a.mode].op).c_str());

	string tmp = cmd;
	if(a.mode!=AM_ACC)
	{
		tmp += "     ";
		tmp += ADDRMODES[a.mode].op;
	}
	addop(tmp.c_str(),a);
}

void Compiler::opunary(const string &cmd,const string &arg)
{
	Arg a=getarg(arg.c_str());
	opunary(cmd,a);
}

void Compiler::oparith(const string &_cmd,const string &arg,char acc)
{
	Arg a=getarg(arg.c_str());
	string cmd = _cmd;
	if(acc=='X' || acc=='Y')
	{
		if(cmd=="CMP") cmd = (acc=='X') ? "CPX" : "CPY";
		else Error("The only accumulator op compatible with X/Y is comparison");
	}

	int flag = ADDRMODES[a.mode].lda;
	if(cmd=="CPX" || cmd=="CPY") flag = ADDRMODES[a.mode].cpx;
	if(cmd=="BIT") flag = ADDRMODES[a.mode].bit;

//	if(!flag)
//		Error(format("Arith operation %s doesn't work in mode %s",cmd.c_str(),ADDRMODES[a.mode].op).c_str());

	string tmp = cmd;
	if(a.mode!=AM_ACC)
	{
		tmp += "     ";
		tmp += ADDRMODES[a.mode].op;
	}
	addop(tmp.c_str(),a);
}

void Compiler::opmov(const Arg &da,const Arg &sa)
{
	const char *s = movmap[da.mode][sa.mode].c_str();
	if(!*s)
		Error(format("No opcode for data mov:  %s <- %s",ADDRMODES[da.mode].op,ADDRMODES[sa.mode].op).c_str());


	Arg a;
	if(*s=='L') a=sa;
	else		a=da;

	addop(s,a);
}

void Compiler::opmov(const string &dst,const string &src)
{
	Arg da=getarg(dst.c_str());
	Arg sa=getarg(src.c_str());

	opmov(da,sa);
}

void Compiler::opmov3(const string &a1,const string &a2,const string &a3)
{
    Arg aa1=getarg(a1.c_str());
	Arg aa2=getarg(a2.c_str());

    if( (aa1.mode==AM_ACC && aa2.mode==AM_X) ||
        (aa1.mode==AM_X && aa2.mode==AM_ACC) )
    {
        // LAX
        opunary("LAX",a3);
        return;
    }

    opmov(a2,a3);
    opmov(a1,a2);
}

void Compiler::opmovseq(const string &movseq)
{
	const char *s = movseq.c_str();
	Arg src  = getarg(ParseString(s).c_str());
	Arg dst1 = getarg(ParseString(s).c_str());
	Arg dst2 = getarg(ParseString(s).c_str());

	while(dst1.mode!=AM_NONE)
	{
		// check for LAX
		if( (dst1.mode==AM_ACC && dst2.mode==AM_X  ) ||
			(dst1.mode==AM_X   && dst2.mode==AM_ACC) )
		{
			opunary("LAX",src);
			// use X for next transfers
			src = (dst1.mode==AM_X) ? dst1 : dst2;
			// shift in 2 destinations
			dst1 = getarg(ParseString(s).c_str());
			dst2 = getarg(ParseString(s).c_str());
			continue;
		}

		// single MOV
		opmov(dst1,src);

		switch(dst1.mode)
		{
		case AM_IMM:
			if(src.mode==AM_Y) break;	// better source already present
		case AM_Y:
			if(src.mode==AM_ACC) break;	// better source already present
		case AM_ACC:
			if(src.mode==AM_X) break;	// better source already present
		case AM_X:
			src = dst1;
		}

		dst1 = dst2;
		dst2 = getarg(ParseString(s).c_str());
	}

}


string Compiler::invert_branch(const string &cmd)
{
		 if(cmd=="BCS") return "BCC";
    else if(cmd=="BCC") return "BCS";
    else if(cmd=="BEQ") return "BNE";
    else if(cmd=="BNE") return "BEQ";
    else if(cmd=="BMI") return "BPL";
    else if(cmd=="BPL") return "BMI";
    else if(cmd=="BVS") return "BVC";
    else if(cmd=="BVC") return "BVS";
    else Error(format("Branch instruction %s can't be inverted",cmd.c_str()).c_str());
	return "???";
}

void Compiler::opbranch(const string &cmd,const string &lab)
{
	if( !code ) Error("[internal] No active section");
	code->Assemble(format("    %-8s%s",cmd.c_str(),lab.c_str()));
}

void Compiler::opbranch_repeat(const string &cmd,const string &lab,AsmSection::Location loc)
{
	if( !code ) Error("[internal] No active section");
	code->AssembleInsert(format("    %-8s%s",cmd.c_str(),lab.c_str()),loc);
}

void Compiler::oplabel(const string &lab)
{
	Var *v = find_var(lab,true);
	if(v->type!=VT_UNKNOWN || v->has_value || v->size)
		Error(format("Label name '%s' already in use",lab.c_str()));
	v->type=VT_LABEL;

	if( !code ) Error("[internal] No active section");
	code->Assemble(lab);
}

string Compiler::genlabel()
{
	return format("__label_%d",label_id_gen++);
}

string Compiler::flag2jump(const string &flag,bool flag_state)
{
	if( flag=="c" || flag=="C" ) return flag_state ? "BCC" : "BCS";
	if( flag=="o" || flag=="O" ) return flag_state ? "BVC" : "BVS";
	if( flag=="z" || flag=="Z" ) return flag_state ? "BEQ" : "BNE";	// TBD: this can't really happen right now
	if( flag=="n" || flag=="N" ) return flag_state ? "BPL" : "BMI";	// TBD: this can't really happen right now
	Error(format("[internal] Unknown flag '%s'",flag.c_str()).c_str());
	return "";
}

void Compiler::opend()
{
	if(comms.size()<=0) return;

	if( code )
	{
		//if(code.size()<=0 || code.back().c_str()[0]!=';')
		//	code.Assemble("");

		for( int i=0; i<(int)comms.size(); i++ )
			code->Assemble(comms[i]);
	}

	comms.clear();
}

void Compiler::op_delayed_repeat(const string &cmd)
{
	if( !code ) Error("[internal] No active section");

	Repeat rep;
	rep.op = cmd;
	rep.loc = code->GetLocation();
	rep.line = line;
	delayed_repeats.push_back(rep);
}

void Compiler::check_loop_jumps()
{
	if(break_labels.size()>0)
	{
		const char *s = break_labels[0].c_str();
		ParseString(s);
		ParseWhitespace(s);
		if(!*s) s="???";
		Error(format("'break' outside loop in line %s",s).c_str());
	}
	break_labels.clear();

	if(delayed_repeats.size()>0)
		Error(format("'repeat' outside loop in line %d",delayed_repeats[0].line).c_str());
	delayed_repeats.clear();
}

void Compiler::flush_loop_jumps(const string &br2_multi_data)
{
	const char *s = br2_multi_data.c_str();
	string loop_start = ParseString(s);
	int break_depth = ParseInt(s);
	int repeat_depth = ParseInt(s);

	while((int)break_labels.size()>break_depth)
	{
		const char *s = break_labels.back().c_str();
		oplabel(ParseString(s).c_str());
		break_labels.pop_back();
	}

	while((int)delayed_repeats.size()>repeat_depth)
	{
		const Repeat &rep = delayed_repeats.back();
		opbranch_repeat(rep.op,loop_start,rep.loc);
		delayed_repeats.pop_back();
	}
}

void Compiler::makesection(const string &name,const string &type)
{
	if( !code ) Error("[internal] No active section");
	
	check_loop_jumps();

	code->name = name;
	code->type = type;

	if( code->type=="inline" )
	{
		if( code->big_align_step )
			Error(format("Inline section '%s' can't have alignment restrictions", name.c_str()).c_str());

		for( int i=0; i<256; i++ )
			if( !code->alignments[i] )
				Error(format("Inline section '%s' can't have alignment restrictions", name.c_str()).c_str());
	}

	Var *v = find_var(name,true);
	if(v->type==VT_UNKNOWN)
		v->type = VT_RESERVED;

	code = NULL;

	local_index++;
}

void Compiler::makeimagesection(const string &name,string path)
{
	if( !code ) Error("[internal] No active section");

	if(path.size()>=2 && path[0]=='"' && path[path.size()-1]=='"')
	{
		path.erase(path.end()-1);
		path.erase(path.begin());
	}

	code->name = name;
	code->type = "image";
	code->bank_list.clear();

	img.Load(path.c_str());
	code->raw_table = img.data;
	code->img_width = img.w;
	code->img_height = img.h;

	Var *v = find_var(name,true);
	if(v->type!=VT_UNKNOWN || v->has_value || v->size)
		Error(format("Image identifier '%s' already in use",name.c_str()));
	v->type = VT_IMAGE;
}

void Compiler::makebinarysection(const string &name, string path)
{
	if( !code ) Error("[internal] No active section");

	if( path.size()>=2 && path[0]=='"' && path[path.size()-1]=='"' )
	{
		path.erase(path.end()-1);
		path.erase(path.begin());
	}

	code->name = name;
	code->type = "binary";

	static vector<uint8_t> data;
	if( !NFS.GetFileBytes(path.c_str(), data) )
		Error(format("Can't open file: %s", path.c_str()));

	code->raw_table.resize(data.size());
	for( int i=0; i<(int)data.size(); i++ )
		code->raw_table[i] = data[i];
	code->img_width = data.size();
	code->img_height = 1;

	Var *v = find_var(name, true);
	if( v->type!=VT_UNKNOWN || v->has_value || v->size )
		Error(format("Section identifier '%s' already in use", name.c_str()));
	v->type = VT_BINARY;
}



void Compiler::setalign(int a,int offs)
{
	if( !code ) Error("[internal] No active section");

	switch( a )
	{
	case 1:
	case 2:
	case 4:
	case 8:
	case 16:
	case 32:
	case 64:
	case 128:
	case 256:
		if( offs<0 || offs>=a )
			Error("Alignment offset can't exceed alignment value");

		for( int i=0; i<256; i++ )
			if( i%a!=offs )
				code->alignments[i] = false;
		break;

	case 1<<9:
	case 1<<10:
	case 1<<11:
	case 1<<12:
	case 1<<13:
	case 1<<14:
	case 1<<15:
	case 1<<16:
		if( offs<0 || offs>=a )
			Error("Alignment offset can't exceed alignment value");
		code->big_align_step = a;
		code->big_align_offset = offs;
		break;

	default:
		Error("Alignment must be power of 2 from 1..65536 range");
	}
}

void Compiler::setaddress(int addr)
{
	if( !code ) Error("[internal] No active section");
	code->fixed_address = addr;
}


void Compiler::dofunction(const string &id, bool farcall)
{
	const char *pid = id.c_str();
	int mode = *pid ? *pid++ - 'a' : AM_NONE;

	if(mode==AM_IMM && !farcall)
		return;	// drop immediate value "call"

	if(mode!=AM_VAR)
		Error("Invalid operation");

	if( !code ) Error("[internal] No active section");

	AsmSection *as = state.FindSection(pid);
	if( !as ) Error(format("No function named '%s'",pid).c_str());

    if(as->type=="inline")
	{
		if(farcall) Error("Inline functions shouldn't use far prefix");
		code->Inline( *as );
	}
    else if(as->type=="func")
	{
		if( farcall )
		{
			sqlink.InvokeFarCall( *code, *as, *this );
		}
		else
		{
			if(as->bank_list.size()!=1)
				Error("[internal] Call must target function in exactly one bank");
			if(as->bank_list[0]!=cur_bank)
				Error(format("Function '%s' is not in the same bank (use far call)",pid).c_str());
			code->Assemble( format("    JSR     %s",as->name.c_str()).c_str() );
		}
	}
    else Error(format("Function '%s' is not inline",pid).c_str());
}

void Compiler::dofarjump(const string &id)
{
	const char *pid = id.c_str();
	int mode = *pid ? *pid++ - 'a' : AM_NONE;

	if( mode!=AM_VAR )
		Error("Invalid operation");

	if( !code ) Error("[internal] No active section");

	sqlink.InvokeFarJump(*code, pid, *this);
}


void Compiler::pulltile()
{
    img.NextTile();
    for(int i=0;i<img.img_len;i++)
		datavalue(format("%d",img.GetRow()&0xFF));
}

void Compiler::loadbinary(const char *path)
{
	if( !NFS.GetFileBytes(path, binary) )
		Error(format("Can't open file: %s", path));
}

void Compiler::pullbinary()
{
	for( int i=0; i<(int)binary.size(); i++ )
		datavalue(format("%d", binary[i]));
}


void Compiler::pp_if(bool result)
{
	preproc_state_stack.push_back(preproc_state);
	if(result)	preproc_state = PREPROC_IF_TAKEN,		parser_enabled.push(true);
	else		preproc_state = PREPROC_IF_NOT_TAKEN,	parser_enabled.push(false);
}

void Compiler::pp_else()
{
	switch(preproc_state)
	{
	case PREPROC_ELIF_DO_NOT_TAKE:
	case PREPROC_IF_TAKEN:
		if(!parser_enabled.set_top(false)) Error("#else without matching #if");
		preproc_state = PREPROC_ELSE_NOT_TAKEN;
		break;
	case PREPROC_IF_NOT_TAKEN:
		if(!parser_enabled.set_top(true)) Error("#else without matching #if");
		preproc_state = PREPROC_ELSE_TAKEN;
		break;
	default:
		Error("#else without matching #if");
		break;
	}
}

void Compiler::pp_elif(bool result)
{
	switch(preproc_state)
	{
	case PREPROC_IF_TAKEN:
	case PREPROC_ELIF_DO_NOT_TAKE:
		if(!parser_enabled.set_top(false)) Error("#elif without matching #if");
		preproc_state = PREPROC_ELIF_DO_NOT_TAKE;	// don't take any further blocks
		break;

	case PREPROC_IF_NOT_TAKEN:
		if(!parser_enabled.set_top(result)) Error("#elif without matching #if");
		preproc_state = result ? PREPROC_ELIF_DO_NOT_TAKE : PREPROC_IF_NOT_TAKEN;
		break;
	default:
		Error("#elif without matching #if");
		break;
	}
}

void Compiler::pp_endif()
{
	switch(preproc_state)
	{
	case PREPROC_IF_TAKEN:
	case PREPROC_IF_NOT_TAKEN:
	case PREPROC_ELSE_NOT_TAKEN:
	case PREPROC_ELSE_TAKEN:
		// OK
		break;
	default:
		Error("#endif without matching #if");
		break;
	}

	if( !parser_enabled.pop() || preproc_state_stack.size()<1 )
		Error("#endif without matching #if");
	preproc_state = preproc_state_stack.back();
	preproc_state_stack.pop_back();
}



void Compiler::LineStart(const char *s)
{
	const char *b = s;
	while(*s && *s!='\n') s++;
	comms.push_back(string(";  ")+string(b,s));
}

int Compiler::GetChar()
{
    if(!*src) return 0;
	if(*src=='\n')
	{
		LineStart(src+1);
		line++;
	}
    return *src++;
}

void Compiler::Error(const char *e)
{
    static string _e;
    _e = format("Line %d: ",line)+e;
    throw _e.c_str();
}

void Compiler::Warn(const char *e)
{
    static string _e;
    _e = format("Line %d: ",line)+e;
    printf("Warning: %s\n",_e.c_str());
}




	//code.Clear();
	//code.Assemble("    processor 6502");
	//code.Assemble("    include vcs.h");
	//code.Assemble("    include macro.h");
	//code.Assemble("    org $F000");
	//code.Assemble("");
	//code.Assemble("EntryPoint");

	//// main section
	//int mid = -1;
	//for(int i=0;i<sections.size();i++)
	//	if(sections[i].type=="main")
	//	{
	//		if(mid>=0) Error("Duplicate entry point");
	//		mid = i;
	//	}
	//if(mid<0) Error("No entry point");
	//PutSection( sections[mid] );

	//// data
	//for(int i=0;i<sections.size();i++)
	//	if(sections[i].type=="data")
	//		PutSection( sections[i] );

	//code.Assemble("");
	//code.Assemble("    org $FFFC");
	//code.Assemble("    .word EntryPoint");
	//code.Assemble("    .word EntryPoint");

void Compiler::InitCompile()
{
	// clear
	src = "";
	line = 0;
 	label_id_gen = 1;
	var_addr = 0;
    error.clear();
	vars.clear();
	comms.clear();
	break_labels.clear();
	delayed_repeats.clear();
	code = NULL;
	cur_bank = "default";
	charset.clear();
	evaluator.Clear();
	for(int i=0;i<NUM_ADDR_MODES;i++)
		for(int j=0;j<NUM_ADDR_MODES;j++)
			movmap[i][j].clear();
    img.Reset();
	parser_enabled.clear();
	preproc_state_stack.clear();
	preproc_state = PREPROC_DEFAULT;
	eval_functions.clear();
	eval_fn_table.clear();
	eval_stack.clear();
	eval_local_alloc = 0;
	tmp_eval.Clear();
	local_index = 0;

	state.Clear();


	// init
	movmap[AM_ACC][AM_X]="TXA";
	movmap[AM_ACC][AM_Y]="TYA";
	movmap[AM_X][AM_ACC]="TAX";
	movmap[AM_Y][AM_ACC]="TAY";
	movmap[AM_X][AM_S]="TSX";
	movmap[AM_S][AM_X]="TXS";

	for(int i=0;ADDRMODES[i].op;i++)
	{
		const AddrMode &f = ADDRMODES[i];
		int a = f.mode;
		const char *s = f.op;
		if( f.lda ) movmap[AM_ACC][a]	= string("LDA     ")+s;
		if( f.ldx ) movmap[AM_X][a]		= string("LDX     ")+s;
		if( f.ldy ) movmap[AM_Y][a]		= string("LDY     ")+s;
		if( f.sta ) movmap[a][AM_ACC]	= string("STA     ")+s;
		if( f.stx ) movmap[a][AM_X]		= string("STX     ")+s;
		if( f.sty ) movmap[a][AM_Y]		= string("STY     ")+s;
	}

//	// add A2600 registers
//	int vaddr = 0;
//	for(int i=0;REGS[i];i++)
//		if(REGS[i][0]=='$')
//			vaddr = getnum(REGS[i]+1);
//		else
//		{
//			Var *v = find_var(REGS[i],true);
//			if(v->type==VT_UNKNOWN)
//			{
//				v->type=VT_VAR;
//				v->value = vaddr++;
//				v->has_value = true;
//
//				state.AddLabel(v->name.c_str(),v->value,NULL,false,this);
//			}
//		}
}

void Compiler::SetBank(const char *bank)
{
	cur_bank = bank;
}

const char *Compiler::Compile(const char *codetext)
{
	// compile
    try {
		try {

			src = codetext;
			line = 1;
			LineStart(src);
			opend();

			//eval.Clear();

			RunParser();
		}
		catch(const char *e)
		{
			Error(string(e));
		}
		catch( const string &e )
		{
			Error(e);
		}
	}
	catch(const char *err)
    {
        error = err;
		delete code;
		code = NULL;
		state.Clear();
    }

    return (error.size()>0) ? error.c_str() : NULL;
}
