
#include "stdafx.h"
#include "common.h"



struct AsmEncoding {
    const char  *op;
    int         arg;
    int         encoding;
    int         bytes;
    int         clocks;
};

enum {
    ARG_IMPL,
    ARG_ACC,
    ARG_IMM,
    ARG_ZP,
    ARG_ZP_X,
    ARG_ZP_Y,
    ARG_ADDR,
    ARG_ADDR_X,
    ARG_ADDR_Y,
    ARG_IND,
    ARG_IND_X,
    ARG_IND_Y,
    ARG_REL,
	ARG_IGNORED,
    NUM_ARG_MODES
};

const char *ARG_NAMES[] = {
    "implied",
    "accumulator",
    "immediate",
    "zero page,X",
    "zero page",
    "zero page,Y",
    "address",
    "address,X",
    "address,Y",
    "indirect",
    "(indirect,X)",
    "(indirect),Y",
    "relative",
	"ignored",
    "<unknown>"
};

const AsmEncoding ASM_ENC[] = {
#include "optab.h"
// undocumented / extra opcodes

//  ANC     a &. value
//  SAX     mem = a & x         mem = x & a
//  ARR
//  ASR
//  AXS     x &= a - value
//  DCP     a ? --mem
//  ISC     a - ++mem
//  LAX     a=x=value           x=a=value
//  RLA
//  SLO
//  SRE


{"ANC"  ,ARG_IMM        ,0x0B   ,2  ,2  },  // ANC:     A <- A & imm      C <- bit 7
{"SAX"  ,ARG_ZP         ,0x87   ,2  ,3  },  // SAX:     mem <- A & X
{"SAX"  ,ARG_ZP_Y       ,0x97   ,2  ,4  },
{"SAX"  ,ARG_IND_X      ,0x83   ,2  ,6  },
{"SAX"  ,ARG_ADDR       ,0x8F   ,3  ,4  },
{"ARR"  ,ARG_IMM        ,0x6B   ,2  ,2  },  // ARR:     A <- (A & imm) ror>>>       C, V <- complex
{"ASR"  ,ARG_IMM        ,0x4B   ,2  ,2  },  // ASR:     A <- (A & imm) >> 1
{"AXS"  ,ARG_IMM        ,0xCB   ,2  ,2  },  // AXS:     X <- (A & X) - imm      [no borrow]
{"DCP"  ,ARG_ZP         ,0xC7   ,2  ,5  },  // DCP:     mem <- mem - 1          A - mem
{"DCP"  ,ARG_ZP_X       ,0xD7   ,2  ,6  },
{"DCP"  ,ARG_ADDR       ,0xCF   ,3  ,6  },
{"DCP"  ,ARG_ADDR_X     ,0xDF   ,3  ,7  },
{"DCP"  ,ARG_ADDR_Y     ,0xDB   ,3  ,7  },
{"DCP"  ,ARG_IND_X      ,0xC3   ,2  ,8  },
{"DCP"  ,ARG_IND_Y      ,0xD3   ,2  ,8  },
{"ISC"  ,ARG_ZP         ,0xE7   ,2  ,5  },  // ISC:     mem <- mem + 1          A <- A - mem    [with borrow]
{"ISC"  ,ARG_ZP_X       ,0xF7   ,2  ,6  },
{"ISC"  ,ARG_ADDR       ,0xEF   ,3  ,6  },
{"ISC"  ,ARG_ADDR_X     ,0xFF   ,3  ,7  },
{"ISC"  ,ARG_ADDR_Y     ,0xFB   ,3  ,7  },
{"ISC"  ,ARG_IND_X      ,0xE3   ,2  ,8  },
{"ISC"  ,ARG_IND_Y      ,0xF3   ,2  ,8  },
{"LAS"  ,ARG_ADDR_Y     ,0xBB   ,3  ,4  },  // LAS:     A,X,S <- mem & S
{"LAX"  ,ARG_ZP         ,0xA7   ,2  ,3  },  // LAX:     A,X <- mem
{"LAX"  ,ARG_ZP_Y       ,0xB7   ,2  ,4  },
{"LAX"  ,ARG_ADDR       ,0xAF   ,3  ,4  },
{"LAX"  ,ARG_ADDR_Y     ,0xBF   ,3  ,4  },
{"LAX"  ,ARG_IND_X      ,0xA3   ,2  ,6  },
{"LAX"  ,ARG_IND_Y      ,0xB3   ,2  ,5  },
{"RLA"  ,ARG_ZP         ,0x27   ,2  ,5  },  // RLA:     mem <- mem <<<          A <- A & mem
{"RLA"  ,ARG_ZP_X       ,0x37   ,2  ,6  },
{"RLA"  ,ARG_ADDR       ,0x2F   ,3  ,6  },
{"RLA"  ,ARG_ADDR_X     ,0x3F   ,3  ,7  },
{"RLA"  ,ARG_ADDR_Y     ,0x3B   ,3  ,7  },
{"RLA"  ,ARG_IND_X      ,0x23   ,2  ,8  },
{"RLA"  ,ARG_IND_Y      ,0x33   ,2  ,8  },
{"RRA"  ,ARG_ZP         ,0x67   ,2  ,5  },  // RRA:     mem <- mem >>>          A <- A + mem    [with carry]
{"RRA"  ,ARG_ZP_X       ,0x77   ,2  ,6  },
{"RRA"  ,ARG_ADDR       ,0x6F   ,3  ,6  },
{"RRA"  ,ARG_ADDR_X     ,0x7F   ,3  ,7  },
{"RRA"  ,ARG_ADDR_Y     ,0x7B   ,3  ,7  },
{"RRA"  ,ARG_IND_X      ,0x63   ,2  ,8  },
{"RRA"  ,ARG_IND_Y      ,0x73   ,2  ,8  },
{"SLO"  ,ARG_ZP         ,0x07   ,2  ,5  },  // SLO:     mem <- mem << 1         A <- A | mem
{"SLO"  ,ARG_ZP_X       ,0x17   ,2  ,6  },
{"SLO"  ,ARG_ADDR       ,0x0F   ,3  ,6  },
{"SLO"  ,ARG_ADDR_X     ,0x1F   ,3  ,7  },
{"SLO"  ,ARG_ADDR_Y     ,0x1B   ,3  ,7  },
{"SLO"  ,ARG_IND_X      ,0x03   ,2  ,8  },
{"SLO"  ,ARG_IND_Y      ,0x13   ,2  ,8  },
{"SRE"  ,ARG_ZP         ,0x47   ,2  ,5  },  // SRE:     mem <- mem >> 1         A <- A ^ mem
{"SRE"  ,ARG_ZP_X       ,0x57   ,2  ,6  },
{"SRE"  ,ARG_ADDR       ,0x4F   ,3  ,6  },
{"SRE"  ,ARG_ADDR_X     ,0x5F   ,3  ,7  },
{"SRE"  ,ARG_ADDR_Y     ,0x5B   ,3  ,7  },
{"SRE"  ,ARG_IND_X      ,0x43   ,2  ,8  },
{"SRE"  ,ARG_IND_Y      ,0x53   ,2  ,8  },
{"NOP"  ,ARG_ZP         ,0x04   ,2  ,3  },  // NOP ZP
{"BYTE" ,ARG_IMM        ,-1	    ,0  ,0  },  // byte value
{"UNDEF",ARG_IGNORED	,-1	    ,0  ,0  },  // ignored byte value
{}
};

struct ArgFormat {
	int			mode;
	int			ast;
	const char	*pattern;
};

const ArgFormat ARG_FMTS[] = {
	{ ARG_IMPL,		AST_NONE,				""				},
	{ ARG_ACC,		AST_NONE,				"a"				},
	{ ARG_ACC,		AST_NONE,				""				},
	{ ARG_IMM,		AST_DATA_BYTE,			"#i"			},
	{ ARG_IMM,		AST_LO_ADDRESS,			"#<s"			},
	{ ARG_IMM,		AST_LO_ADDRESS,			"#<(s)"		    },
	{ ARG_IMM,		AST_LO_ADDRESS,			"#<si"			},
	{ ARG_IMM,		AST_LO_ADDRESS,			"#<(si)"		},
	{ ARG_IMM,		AST_HI_ADDRESS,			"#>s"			},
	{ ARG_IMM,		AST_HI_ADDRESS,			"#>(s)"		    },
	{ ARG_IMM,		AST_HI_ADDRESS,			"#>(si)"		},
	{ ARG_IMM,		AST_ZP_ADDRESS,			"#s"			},
	{ ARG_IMM,		AST_ZP_ADDRESS,			"#(s)"			},
	{ ARG_IMM,		AST_ZP_ADDRESS,			"#si"			},
	{ ARG_IMM,		AST_ZP_ADDRESS,			"#(si)"		    },
	{ ARG_ZP,		AST_DATA_BYTE,			"i"				},
	{ ARG_ZP_X,		AST_DATA_BYTE,			"i,x"			},
	{ ARG_ZP_Y,		AST_DATA_BYTE,			"i,y"			},
	{ ARG_ADDR,		AST_ADDRESS,			"s"				},
	{ ARG_ADDR,		AST_ADDRESS,			"si"			},
	{ ARG_ADDR_X,	AST_ADDRESS,			"s,x"			},
	{ ARG_ADDR_X,	AST_ADDRESS,			"si,x"			},
	{ ARG_ADDR_Y,	AST_ADDRESS,			"s,y"			},
	{ ARG_ADDR_Y,	AST_ADDRESS,			"si,y"			},
	{ ARG_ZP,		AST_ZP_ADDRESS,			"s"				},
	{ ARG_ZP,		AST_ZP_ADDRESS,			"si"			},
	{ ARG_ZP_X,	    AST_ZP_ADDRESS,			"s,x"			},
	{ ARG_ZP_X,	    AST_ZP_ADDRESS,			"si,x"			},
	{ ARG_ZP_Y,	    AST_ZP_ADDRESS,			"s,y"			},
	{ ARG_ZP_Y,	    AST_ZP_ADDRESS,			"si,y"			},
	{ ARG_IND,		AST_ADDRESS,			"(s)"			},
	{ ARG_IND,		AST_ADDRESS,			"(si)"			},
	{ ARG_IND_X,	AST_ZP_ADDRESS,			"(s,x)"			},
	{ ARG_IND_X,	AST_ZP_ADDRESS,			"(si,x)"		},
	{ ARG_IND_Y,	AST_ZP_ADDRESS,			"(s),y"			},
	{ ARG_IND_Y,	AST_ZP_ADDRESS,			"(si),y"		},
	{ ARG_REL,		AST_RELATIVE_TARGET,	"s"				},
	{ ARG_IGNORED,	AST_IGNORED_BYTE,		""				},
	{}
};


template<class T>
void insert_tail(vector<T> &vect,int dst_pos,int tail_start)
{
	vector<T> tmp(vect.begin()+tail_start,vect.end());
	vect.erase(vect.begin()+tail_start,vect.end());
	vect.insert(vect.begin()+dst_pos,tmp.begin(),tmp.end());
}

template<class T>
void repeat_tail(vector<T> &vect,int tail_start,int count)
{
	if(count<=0) return;
	vector<T> tmp(vect.begin()+tail_start,vect.end());
	for(int i=0;i<count;i++)
		vect.insert(vect.end(),tmp.begin(),tmp.end());
}



static bool match(const char *s,const char *p,string &vs,int &vi)
{
	vs = "";
	vi = 0;
	while(1)
	{
		ParseWhitespace(s);
		ParseWhitespace(p);
		if(!*s && !*p) break;
		if(!*s) return false;
		if(!*p) return false;

		if(*p=='i')
		{
			int base=10, sign=1;
			p++;
			if(*s=='+') s++;
			if(*s=='-') sign=-1, s++, ParseWhitespace(s);
			if(*s=='$') s++, base=16;
			if(*s=='%') s++, base=2;

            const char *b = s;
			vi = 0;
			while(1)
			{
				int d=-1;
					 if(*s>='0' && *s<='9') d = *s - '0';
				else if(*s>='a' && *s<='z') d = *s - 'a' + 10;
				else if(*s>='A' && *s<='Z') d = *s - 'A' + 10;
				else break;

				if(d>=base) return false;

				vi = vi*base + d;
				s++;
			}
            if(s==b) return false;
            vi *= sign;
		}
		else if(*p=='s')
		{
			const char *b = s;
			p++;
			while(*s)
			{
				if(*s>='0' && *s<='9') { s++; continue; }
				if(*s>='a' && *s<='z') { s++; continue; }
				if(*s>='A' && *s<='Z') { s++; continue; }
				if(*s=='_') { s++; continue; }
				break;
			}
			if(s==b) return false;
			vs.assign(b,s);
		}
		else
		{
			if(tolower(*s)!=tolower(*p)) return false;
			p++;
			s++;
		}
	}

	return true;
}


int FindZeroPageReduction(int opcode)
{
    for(int i=0;ASM_ENC[i].op;i++)
        if(ASM_ENC[i].encoding==opcode)
        {
            int am = -1;
            if(ASM_ENC[i].arg==ARG_ADDR  ) am = ARG_ZP;
            if(ASM_ENC[i].arg==ARG_ADDR_X) am = ARG_ZP_X;
            if(ASM_ENC[i].arg==ARG_ADDR_Y) am = ARG_ZP_Y;
            if(am<0) return -1; // opcode not in addr mode

            for(int j=0;ASM_ENC[j].op;j++)
                if(ASM_ENC[j].arg==am && strcmp(ASM_ENC[i].op,ASM_ENC[j].op)==0)
                    return ASM_ENC[j].encoding; // found

            return -1; // no support for zero page in this opcode and mode
        }

    return -1; // unknown opcode
}



void AsmSection::Clear()
{
    name = "<unnamed>";
    code.clear();
	code_bitmask.clear();
	big_align_step = 0;
	big_align_offset = 0;
	alignments.set();
    raw_line = "";
    line_counter = 0;
    cur_flags = 0;
	bank_list.clear();
	referenced = false;
    clocks = 0;
	asm_lines.clear();
	raw_table_valid = false;
	raw_table.clear();
	img_width = 0;
	img_height = 0;
	link_weight = 0;

    address = -1;
    fixed_address = -1;
	layer_bits = 0;
	bank_start = 0;
	bank_end = 0xFFFF;
	alloc_top = false;
	banks.clear();
}

void AsmSection::Error(const char *e)
{
    static string _e;
    _e = format("[assembler(%d)] ",line_counter)+e;

    //if(raw_line.size()>0)
    //    _e += string("\n>") + raw_line;

    throw _e;
}


void AsmSection::AssembleInstruction(const char *s)
{
	raw_table_valid = false;

	ParseWhitespace(s);
    if(*s=='.') s++;

    // parse opcode
    string op = ParseString(s);
    for(int i=0;i<(int)op.size();i++)
        op[i] = toupper(op[i]);
    ParseWhitespace(s);

    // special handling: byte
    //if(op=="BYTE")
    //{
    //    string vs;
    //    int vi;

    //    while(1)
    //    {
    //        ParseWhitespace(s);
    //        if(!*s) break;
    //        const char *b = s;
    //        while(*s && *s!=',') s++;

    //        string tmp(b,s);
    //             if(match(tmp.c_str(),"i",vs,vi)) add(AST_DATA_BYTE,"",vi);
    //        else if(match(tmp.c_str(),"#i",vs,vi)) add(AST_DATA_BYTE,"",vi);
    //        else Error(format("Byte command can't accept '%s'",tmp.c_str()).c_str());
    //        if(*s==',') s++;
    //    }
    //    return;
    //}


    // check if opcode is correct
    int  encoding_id[NUM_ARG_MODES];
    bool found_op = false;
    memset(encoding_id,-1,sizeof(encoding_id));
    for(int i=0;ASM_ENC[i].op;i++)
        if(op==ASM_ENC[i].op)
        {
            encoding_id[ ASM_ENC[i].arg ] = i;
            found_op = true;
        }
    if(!found_op) Error(format("Unknown opcode '%s'",op.c_str()).c_str());

    // decode argument
	string vs, found_vs;
	int vi = 0, found_vi = 0;
    int found_arg = -1;
    int found_ast = -1;
    int num_match = 0;
    int mode = -1;
    
    for(int j=0;ARG_FMTS[j].pattern;j++)
        if( match(s,ARG_FMTS[j].pattern,vs,vi) )
        {
            if(mode<0 || num_match==0)
                mode = ARG_FMTS[j].mode;

            if( encoding_id[ARG_FMTS[j].mode] >= 0 )
            {
                if(num_match==0)
                {
                    found_arg = ARG_FMTS[j].mode;
                    found_ast = ARG_FMTS[j].ast;
                    found_vs = vs;
                    found_vi = vi;
                }
                num_match++;
            }
        }

    if(found_arg>=0) mode = found_arg;
    if(mode<0) mode = NUM_ARG_MODES;

    if(num_match<=0) Error(format("Opcode %s doesn't support %s argument type",op.c_str(),ARG_NAMES[mode]).c_str());
    //if(num_match> 1) Error("[internal] Multiple argument format matches");


    // emit instruction
    const AsmEncoding &enc = ASM_ENC[encoding_id[found_arg]];
    if(enc.encoding>=0)
        add(AST_OPCODE_BYTE,"",enc.encoding);

    if(found_ast!=AST_NONE)
        add(found_ast,found_vs.c_str(),found_vi);

    clocks += enc.clocks;
}

void AsmSection::Assemble(const char *line)
{
	asm_lines.push_back(line);
	raw_table_valid = false;

    const char *s = line;
    raw_line = line;
    line_counter++;

    ParseWhitespace(s);


    // empty or starting with ';' - whole-line comment
    if(!*s || *s==';')
    {
        add(AST_LINE_COMMENT,line);
        return;
    }

    // starting from first column - add label
    if(s==line)
    {
        string lab = ParseString(s);
        add(AST_LABEL,lab.c_str());
    }

    // instruction
    ParseWhitespace(s);
    const char *b = s;
    while(*s && *s!=';') s++;
    if(s!=b)
        AssembleInstruction(string(b,s).c_str());

    // process trailing comments
    if(*s==';')
        add(AST_APPEND_COMMENT,s);
}

void AsmSection::AssembleInsert(const char *line,Location pos)
{
	Location start = GetLocation();
	Assemble(line);

	insert_tail(code,pos.code_pos,start.code_pos);
	insert_tail(asm_lines,pos.asm_lines_pos,start.asm_lines_pos);
	raw_table_valid = false;
}

void AsmSection::RepeatTail(Location tail_start,int count)
{
	Location tail_end = GetLocation();
	if(count<1) Error(format("Data repeat count must be at least 1 (specified %d)",count).c_str());
	count--;
	repeat_tail(code,tail_start.code_pos,count);
	repeat_tail(asm_lines,tail_start.asm_lines_pos,count);
	raw_table_valid = false;
}

void AsmSection::Inline(const AsmSection &as)
{
    static int inline_cnt = 0;
    raw_line = string("inlining: ") + as.name;
	raw_table_valid = false;

    // checks
	if( big_align_step )
		Error("Can't inline section with alignment restrictions set");

	for(int i=0;i<256;i++)
		if( !as.alignments[i] )
            Error("Can't inline section with alignment restrictions set");

    // gather local symbols
    map<string,bool> is_local;
    for(int i=0;i<(int)as.code.size();i++)
        if(as.code[i].type==AST_LABEL)
            is_local[as.code[i].text] = true;

    // inline
    inline_cnt++;

    for(int i=0;i<(int)as.code.size();i++)
    {
        code.push_back( as.code[i] );
        
        AsmSymbol &s = code[code.size()-1];
        s.flags |= cur_flags;

        switch( s.type )
        {
            case AST_LABEL:
            case AST_RELATIVE_TARGET:
            case AST_ADDRESS:
            case AST_LO_ADDRESS:
            case AST_HI_ADDRESS:
            case AST_ZP_ADDRESS:
                if( is_local.find(s.text) != is_local.end() )
                    s.text = format("__I%d",inline_cnt) + s.text;
                break;

            case AST_OPCODE_BYTE:
                {
                    bool found = false;
                    for(int i=0;ASM_ENC[i].op;i++)
                        if(ASM_ENC[i].encoding == s.value)
                        {
                            found = true;
                            clocks += ASM_ENC[i].clocks;
                            break;
                        }
                    if(!found)
                        Error(format("Invalid opcode 0x%02X during inlining",s.value).c_str());
                }
                break;
        }
    }

	// inline asm lines
	asm_lines.push_back(format("\t; inlined %s",as.name.c_str()));
	for(int i=0;i<(int)as.asm_lines.size();i++)
	{
		const char *s = as.asm_lines[i].c_str();
		const char *b = s;
		ParseWhitespace(s);
		if(*s==';')
		{
			//asm_lines.push_back(as.asm_lines[i]);
			continue;
		}
		if(s==b)
		{
			// local label
			asm_lines.push_back( format("__I%d",inline_cnt) + as.asm_lines[i] );
			continue;
		}

		string opname = ParseString(s);
		ParseWhitespace(s);
		const char *p = s;
		string label = ParseString(s);
		if( label.size()>0 && is_local.find(label) != is_local.end() )
		{
			asm_lines.push_back( "\t" + opname + "\t" + format("__I%d",inline_cnt) + p );
		}
		else
			asm_lines.push_back(as.asm_lines[i]);
	}
	asm_lines.push_back(format("\t; end of inlined %s",as.name.c_str()));
}


void AsmSection::AllowPageCross()
{
    raw_line = "";

    if( !(cur_flags & ASF_NO_PAGE_CROSS) )
        Error("Page crossing already enabled");
    
    cur_flags &= ~ASF_NO_PAGE_CROSS;
}

void AsmSection::DisallowPageCross()
{
    raw_line = "";

    if( cur_flags & ASF_NO_PAGE_CROSS )
        Error("Page crossing already disabled");
    
    cur_flags |= ASF_NO_PAGE_CROSS;
}

void AsmSection::ClearDisallowPageCross()
{
    cur_flags &= ~ASF_NO_PAGE_CROSS;
}

bool AsmSection::BuildRawTable()
{
	if( raw_table_valid )
		return true;

	if( type=="image" )
		return true;	// table already present

	raw_table.clear();
	for(int i=0;i<(int)code.size();i++)
	{
		AsmSymbol &s = code[i];
		switch(s.type)
		{
		case AST_LINE_COMMENT:
		case AST_APPEND_COMMENT:
		case AST_LABEL:
			break;

		case AST_OPCODE_BYTE:
		case AST_DATA_BYTE:
			raw_table.push_back(s.value);
			break;

		case AST_IGNORED_BYTE:
			raw_table.push_back(0);
			break;


		default:
			raw_table.clear();
			return false;
		}
	}
	raw_table_valid = true;
	return true;
}


void AsmSection::AppendDisassembly(vector<string> &out)
{
	out.push_back(format("; section %s",name.c_str()));
	for(int i=0;i<(int)asm_lines.size();i++)
		out.push_back(asm_lines[i]);


	//out.push_back(format("; section %s",name.c_str()));

	//int pos = 0;
	//while(pos<code.size())
	//{
	//	AsmSymbol &s = code[pos++];
	//	switch(s.type)
	//	{
	//	case AST_LINE_COMMENT:
	//	case AST_APPEND_COMMENT:
	//	case AST_LABEL:
	//	case AST_RELATIVE_TARGET:
	//	case AST_ADDRESS:
	//	case AST_DATA_BYTE:
	//	case AST_LO_ADDRESS:
	//	case AST_ZP_ADDRESS:
	//	case AST_HI_ADDRESS:
	//	case AST_OPCODE_BYTE:

	//	default:
	//		out.push_back(format("!!! unexpected symbol type %d, text %s, value %02Xh",s.type,s.text.c_str(),s.value);
	//		break;
	//	}
	//}
}
