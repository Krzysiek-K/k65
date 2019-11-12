

Syntax -> Sequence						% $0=0;
Sequence -> Instr Sequence
Sequence ->

FnInstr -> Ident = Expr ;				% bf_getsetint($1,true);
FnInstr -> `out ( Expr ) ;				% printf(".[-]");
FnInstr -> ;
Instr -> FnInstr
Instr -> FnInstr , Instr

ISeq -> Instr
ISeq -> { Sequence }

Instr -> `if ( Expr IfStart ) ISeq						% printf("]");
IfStart ->												% printf("[[-]");

Instr -> `if ( Expr IfStart ) ISeq `else IfElse ISeq	% printf(">]<");
IfElse ->												% printf(">+<]>[-<");

Instr -> `while WhileA ( Expr WhileB ) ISeq				% printf(">+<]>]<");
WhileA ->	% printf(">+[-<");
WhileB ->	% printf("[[-]");

Sequence -> `byte DefSeq
DefSeq -> DefOne , DefSeq PopDef
DefSeq -> DefOne ; Sequence PopDef
DefOne -> Ident									% printf(">"); bf_vars.push_back(pair<int,int>($1,bf_depth)); bf_depth++;
DefOne -> Ident = Expr							% printf(">"); bf_vars.push_back(pair<int,int>($1,bf_depth)); bf_depth++;
PopDef ->										% printf("<"); bf_vars.erase(bf_vars.end()-1); bf_depth--;

Expr -> LogOr ? IfStart Expr IfElse : Expr		% printf(">]<");
Expr -> LogOr
LogOr -> LogOr || bfL LogAnd					% printf("[[-]<[-]+>]<"); bf_depth--;
LogOr -> LogAnd
LogAnd -> LogAnd && bfL Cmpr					% printf("[[-]>+<]<[[-]>>[[-]<<+>>]<<]>>[-]<<"); bf_depth--;
LogAnd -> Cmpr
Cmpr -> Sum != bfL Cmpr							% printf("[-<->]<"); bf_depth--;
Cmpr -> Sum == bfL Cmpr							% printf("[-<->]+<[[-]>-<]>[-<+>]<"); bf_depth--;
Cmpr -> Sum > bfL Cmpr							% printf("[-<[-[->>+<<]]>>[-<<+>>]<]<"); bf_depth--;
Cmpr -> Sum <= bfL Cmpr							% printf("[-<[-[->>+<<]]>>[-<<+>>]<]<[->+<]+>[-<->]<"); bf_depth--;
Cmpr -> Sum < bfL Cmpr							% printf("<[->[-[->+<]]>[-<+>]<<]>[-<+>]<"); bf_depth--;
Cmpr -> Sum >= bfL Cmpr							% printf("<[->[-[->+<]]>[-<+>]<<]+>[[-]<->]<"); bf_depth--;
Cmpr -> Sum

Sum -> Elem + bfL Expr							% printf("[-<+>]<"); bf_depth--;
Sum -> Elem - bfL Expr							% printf("[-<->]<"); bf_depth--;
Sum -> Elem
Elem -> ! Elem									% printf("[[-]>+<]+>[-<->]<");
Elem -> - Elem									% printf("[->+<]>[-<->]<");
Elem -> Int										% bf_makeint($1);
Elem -> Ident									% bf_getsetint($1,false);
Elem -> ( Expr )
Elem -> `in ( )									% printf(",");

bfL -> % printf(">"); bf_depth++;

Int :: [0-9]+						% $0=atoi($1)&0xFF;
Int :: "'[^]'"						% $0=$1[1];
Ident :: [a-zA-Z_]+[a-zA-Z_0-9]*	% $0=bf_ident($1);
Comment :: "[ \t\n]+"				% COMMENT
Comment :: "//[^\n]*"				% COMMENT
Comment :: "/[*]([^]*[*])+/"		% COMMENT
_default_ ::						%

$$LexerPrecode		/*A*/
$$LexerPostcode		/*B*/
$$ParserPrecode		/*C*/
$$ParserPostcode	/*D*/


$$Code

#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <string>
using namespace std;

//#include <base.h>
//using namespace base;


#define DBGINFO(x)      printf("%s\n",x);


class Compiler {
public:
	typedef int symb_t;

	symb_t  Compile(const char *path);

private:
	int		GetChar();
	void	Error(const char *message);
	symb_t	Parse();

	FILE	*fp_src;
	int		src_line;
	bool	was_error;

};


int bf_depth = 0;
vector<string> bf_ids;
vector<pair<int,int> > bf_vars;


int bf_ident(const char *s)
{
	for(int i=0;i<bf_ids.size();i++)
		if(bf_ids[i]==s)
			return i;
	bf_ids.push_back(s);
	return bf_ids.size()-1;
}

void bf_getsetint(int id,bool set)
{
	for(int i=bf_vars.size()-1;i>=0;i--)
		if(bf_vars[i].first==id)
		{
			int depth = bf_depth - bf_vars[i].second;
			string jmpL(depth,'<');
			string jmpR(depth,'>');

			if(set)
			{
				printf("%s[-]%s",jmpL.c_str(),jmpR.c_str());
				printf("[-%s+%s]",jmpL.c_str(),jmpR.c_str());
			}
			else
			{
				printf("%s[-%s+>+<%s]",jmpL.c_str(),jmpR.c_str(),jmpL.c_str());
				printf("%s>[-%s<+%s>]<",jmpR.c_str(),jmpL.c_str(),jmpR.c_str());
			}

			return;
		}
	printf("Undeclared variable '%s'.\n", bf_ids[id].c_str());
}

void bf_makeint(int v)
{
	v &= 0xFF;
	if(!v) return;
	char symb = '+';
	if(v>=128) v = 256-v, symb = '-';
	int bl = v, bd = 0, be = 0, l;
	for(int d=2;d*d<=v;d++)
	{
		l = d + v/d + 7 + v%d;
		if(l<bl) bl=l, bd=d, be=v/d;
		l = d + (v/d+1) + 7 + (d*(v/d+1)-v);
		if(l<bl) bl=l, bd=d, be=v/d+1;
	}
	if(bd>1)
	{
		printf(">");
		for(int i=0;i<bd;i++) printf("+");
		printf("[-<");
		for(int i=0;i<be;i++) printf("%c",symb);
		printf(">]<");
		v -= bd*be;
	}
	if(v<0) symb=((symb=='+')?'-':'+'), v=-v;
	for(int i=0;i<v;i++) printf("%c",symb);
}



Compiler::symb_t Compiler::Compile(const char *path)
{
	src_line = 1;
	fp_src = fopen(path, "rt");
	was_error = false;

	if( !fp_src )
		Error("can't open source file");

	return Parse();
}

int	Compiler::GetChar()
{
	int ch = fgetc(fp_src);
	if( ch == EOF )
		return 0;
	if( ch=='\n' ) src_line++;
	return ch;
}

void Compiler::Error(const char *message)
{
	printf("Error on line %d:%s.\n",src_line,message);
	was_error = true;
}

Compiler::symb_t Compiler::Parse()
{
$$Parser
}


int main()
{
	Compiler c;

	int v = c.Compile("source.src");
	printf("\nresult: %d\n", v);

#ifdef WIN32
	system("pause");
#endif

	return 0;
}
