
Syntax -> TopList					%

TopList -> TopElem					% opend();
TopList -> TopList TopElem			% opend();

TopElem -> PPIf TopList TopListPPElse PPEndif
TopListPPElse ->
TopListPPElse -> PPElse TopList
TopListPPElse -> PPElIf TopList TopListPPElse

TopElem -> PPError


PPIf	-> #if PPIfNumber			% pp_if(num($2)!=0); opend();
PPElse	-> #else					% pp_else(); opend();
PPElIf	-> #elif PPIfNumber			% pp_elif(num($2)!=0); opend();
PPEndif	-> #endif					% pp_endif(); opend();

PPError -> #error String			% ST Error($2); opend();
PPError -> #warn String				% ST Warn($2); opend();

PPIfNumber -> Number				% $0=$1;
PPIfNumber -> AllIdent				% $0="@?"+$1; $0=doeval($0,true);
PPIfNumber -> ! PPIfNumber			% $0=(num($2)!=0) ? "0" : "1";



TopElem -> ;

TopElem -> [ EvalCode ]						% ST doeval($2,false);

TopElem -> `var VarList						% opend();
VarList -> Var								%
VarList -> VarList , Var					%
Var -> Ident Verbose						% ST var($1,"",false,1,$2!="");
Var -> Ident = Number Verbose				% ST var($1,$3,false,1,$4!="");
Var -> Ident BracketNumber Verbose			% ST var($1,"",false,num($2),$3!="");
Var -> Ident BracketNumber = Number Verbose	% ST var($1,$4,false,num($2),$5!="");
Verbose ->									% $0="";
Verbose -> ?								% $0="1";


TopElem -> `const ConstList			% opend();
ConstList -> Const					%
ConstList -> ConstList , Const		%
Const -> Ident						% ST var($1,"",true,0);
Const -> Ident = Number				% ST var($1,$3,true,0);


TopElem -> `bank Ident				% ST cur_bank = $2;


TopElem -> `image Ident = String	% ST init_section($2); makeimagesection($2,$4); opend();
TopElem -> `image String = String	% ST init_section($2); makeimagesection($2,$4); opend();
TopElem -> `binary Ident = String	% ST init_section($2); loadbinary(unquote($4).c_str()); pullbinary(); makesection($2,"binary"); opend();


TopElem -> `data SecStart Align OptNoCross DataList }					% ST if($4=="nc") GetCode().AllowPageCross(); makesection($2,"data"); opend();
DataList ->																%
DataList -> DataList Data												% opend();
Data -> Arg																% ST oparith(".byte",$1,'A'); opend();
Data -> && VarArg														% ST oparith(".byte",argto(AM_OFS_LO,$2),'A'); oparith(".byte",argto(AM_OFS_HI,$2),'A'); opend();
Data -> ImgLoad Number Number Number BitDir BitSeq Number RowDir ImgOpt	% ST img.ImgPos(num($2),num($3)); img.bit_len=num($4); img.img_len=num($7); pulltile(); opend();
ImgLoad -> `image Ident													% ST img.Load(($2+".bmp").c_str());
ImgLoad -> `image String												% ST img.Load((unquote($2)+".bmp").c_str());
Data -> `tiles Number Number Number										% ST img.tile_dx=num($2); img.tile_dy=num($3); for(int iii=0;iii<num($4);iii++) pulltile(); opend();
Data -> `colormode Number												% ST img.color_mode=num($2); opend();
Data -> ImgWaveStart OptWaveArgs					% ST opend();
Data -> BinLoad															% ST pullbinary(); opend();
BinLoad -> `binary Ident												% ST loadbinary(($2).c_str());
BinLoad -> `binary String												% ST loadbinary(unquote($2).c_str());
Data -> NoCross { DataList }						% ST GetCode().AllowPageCross();
Data -> ?											% ST opsimp(".undef"); opend();
Data -> `repeat Number { AsmLocation DataList }		% ST GetCode().RepeatTail(AsmSection::Location($4),num($2));
Data -> `code { Sequence }							% ST opend();
Data -> NoCross `code { Sequence }					% ST GetCode().AllowPageCross(); opend();
AsmLocation ->										% $0=GetCode().GetLocation().ToString();


ImgWaveStart -> `imgwave				% ST img.img_steps.clear();
OptWaveArgs ->							% ST 
OptWaveArgs -> WaveArgs					% ST 
WaveArgs -> Number						% ST img.img_steps.push_back(num($1));
WaveArgs -> WaveArgs Number				% ST img.img_steps.push_back(num($2));
WaveArgs -> String						% ST img.img_steps.push_back(num($1));
WaveArgs -> WaveArgs String				% ST img.img_steps.push_back(num($2));

OptNoCross ->							% $0="";
OptNoCross -> `nocross					% $0="nc"; ST GetCode().DisallowPageCross();

Data -> `charset String										% ST charset=$2; charset.erase(charset.begin()); opend();
Data -> `evaluator [ EvalCode ]								% ST Eval_Precompile(evaluator,$3.c_str()); opend();
Data -> String												% ST datastr($1);
Data -> `for AllIdent = Number .. Number `eval [ EvalCode ]	% ST int x=num($4), end=num($6); settmpeval($9); while(1){ setevalvar($2.c_str(),x); datavalue(dotmpeval(true)); if(x==end) break; x+=(x<end?1:-1); }
Data -> Ident :												% ST oplabel($1); opend();

Data -> PPIf DataList DataListPPElse PPEndif
DataListPPElse ->
DataListPPElse -> PPElse DataList
DataListPPElse -> PPElIf DataList DataListPPElse



BitDir -> `v		% ST img.bit_dx= 0; img.bit_dy= 1;
BitDir -> ^			% ST img.bit_dx= 0; img.bit_dy=-1;
BitDir -> <			% ST img.bit_dx=-1; img.bit_dy= 0;
BitDir -> >			% ST img.bit_dx= 1; img.bit_dy= 0;
BitSeq ->			% ST 
BitSeq -> String	% ST img.bit_pos=$1;
RowDir -> `v		% ST img.img_dx= 0; img.img_dy= 1;
RowDir -> ^			% ST img.img_dx= 0; img.img_dy=-1;
RowDir -> <			% ST img.img_dx=-1; img.img_dy= 0;
RowDir -> >			% ST img.img_dx= 1; img.img_dy= 0;
ImgOpt ->			% ST 
ImgOpt -> `inv		% ST img.bit_white=0;


TopElem -> `inline SecStart Sequence }						% ST makesection($2,"inline"); opend();
//TopElem -> `macro Ident ( OptMacroArgList ) { Sequence }	% ST makesection($2,"inline"); opend();
TopElem -> `func SecStart Align Sequence }					% ST opsimp("RTS"); makesection($2,"func"); opend();
TopElem -> `naked SecStart Align Sequence }					% ST makesection($2,"func"); opend();
TopElem -> `main { MainStart Align Sequence }				% ST makesection("main","main"); opend();
SecStart -> Ident {											% $0=$1; ST init_section($1); oplabel($1);
MainStart ->												% ST init_section("main"); oplabel("main");

OptMacroArgList ->							%
OptMacroArgList -> MacroArgList				%
MacroArgList -> MacroArgList , MacroArg		%
MacroArgList -> MacroArg					%
MacroArg -> Ident

Align ->							%
Align -> `align Number				% ST setalign(num($2)); opend();
Align -> `align Number + Number		% ST setalign(num($2),num($4)); opend();
Align -> `address Number			% ST setaddress(num($2)); opend();


Sequence -> Sequence Instr			%
Sequence ->							%

Instr -> PPIf Sequence SeqListPPElse PPEndif
SeqListPPElse ->
SeqListPPElse -> PPElse Sequence
SeqListPPElse -> PPElIf Sequence SeqListPPElse



Instr -> Instr ;					%

Instr -> *									% ST opnop(2); opend();
Instr -> * Number							% ST opnop(num($2)); opend();
Instr -> `%									% ST opnop(3); opend();
Instr -> Arg								% ST dofunction($1,false); opend();
Instr -> `far Arg							% ST dofunction($2,true); opend();
Instr -> `far `goto Arg						% ST dofarjump($3); opend();
Instr -> A ArithOp Arg						% ST oparith($2,$3,'A'); opend();
Instr -> X ArithOp Arg						% ST oparith($2,$3,'X'); opend();
Instr -> Y ArithOp Arg						% ST oparith($2,$3,'Y'); opend();
Instr -> Arg PostfixOp						% ST opunary($2,$1); opend();
Instr -> Flag +								% ST opsimp(string("SE")+$1); opend();
Instr -> Flag -								% ST opsimp(string("CL")+$1); opend();
Instr -> A ??								% ST opsimp("PLA"); opend();
Instr -> A !!								% ST opsimp("PHA"); opend();
Instr -> Flag ??							% ST opsimp("PLP"); opend();
Instr -> Flag !!							% ST opsimp("PHP"); opend();
//Instr -> Arg = Arg							% ST opmov($1,$3); opend();
//Instr -> Arg = Arg = Arg					% ST opmov3($1,$3,$5); opend();
Instr -> MovSeq								% ST opmovseq($1); opend();
Instr -> Arg = A & X						% ST opunary("SAX",$1); opend();
Instr -> Arg = X & A						% ST opunary("SAX",$1); opend();
Instr -> X &= A - Arg						% ST opunary("AXS",$5); opend();
Instr -> `return							% ST opsimp("RTS"); opend();
Instr -> `return_i							% ST opsimp("RTI"); opend();

MovSeq -> Arg = Arg							% $0=$3+" "+$1;	/*MovSeq uses reverse order*/
MovSeq -> MovSeq = Arg						% $0=$3+" "+$1;

Instr -> BrInstr							%
Instr -> NoCross BrInstr					% ST GetCode().AllowPageCross();

BrInstr -> Br2 Sequence }					%

BrInstr -> Br1 Sequence }					% ST oplabel($1); opend();
Br1 -> BranchOp {							% $0=genlabel(); ST opbranch(invert_branch($1),$0); opend();
Br1 -> `never {								% $0=genlabel(); ST opbranch("JMP",$0); opend();

BrInstr -> IfElse { Sequence }				% ST oplabel($1); opend();
IfElse -> Br1 Sequence } `else				% $0=genlabel(); ST opbranch("JMP",$0); oplabel($1); opend();

BrInstr -> Br2 Sequence } BranchOp			% ST opbranch($4,multi_get_1($1)); flush_loop_jumps($1); opend();
Br2 -> {									% ST $0=genlabel(); oplabel($0); $0=make_multi($0,break_labels.size(),delayed_repeats.size()); opend();

BrInstr -> Br2 Sequence } `always			% ST opbranch("JMP",multi_get_1($1)); flush_loop_jumps($1); opend();
BrInstr -> Br2 Sequence } `never			% ST flush_loop_jumps($1); opend();


Instr -> `goto VarArg						% ST opbranch("JMP",argaddr($2)); opend();
Instr -> BranchOp `goto VarArg				% ST opbranch($1,argaddr($3)); opend();
Instr -> `goto ( VarArg )					% ST opbranch("JMP",string("(")+argaddr($3)+")"); opend();
Instr -> `call VarArg						% ST opbranch("JSR",argaddr($2)); opend();
Instr -> Ident :							% ST oplabel($1); opend();

Instr -> `data { DataList }					% ST opend();
Instr -> NoCross `data { DataList }			% ST GetCode().AllowPageCross(); opend();


Instr -> `break								% ST $0=genlabel(); opbranch("JMP",$0); $0=make_multi($0,line); break_labels.push_back($0); opend();
Instr -> BranchOp `break					% ST $0=genlabel(); opbranch($1,$0); $0=make_multi($0,line); break_labels.push_back($0); opend();

Instr -> `repeat							% ST op_delayed_repeat("JMP"); opend();
Instr -> BranchOp `repeat					% ST op_delayed_repeat($1); opend();



NoCross -> `nocross							% ST GetCode().DisallowPageCross();

PutLabel ->									% $0=genlabel(); ST oplabel($0);




AllIdent -> Ident		% $0=$1;
AllIdent -> A			% $0=$1;
AllIdent -> X			% $0=$1;
AllIdent -> Y			% $0=$1;
AllIdent -> S			% $0=$1;
AllIdent -> Flag		% $0=$1;

A -> `a				% $0="a";
A -> `A				% $0="A";
X -> `x				% $0="x";
X -> `X				% $0="X";
Y -> `y				% $0="y";
Y -> `Y				% $0="Y";
S -> `s				% $0="s";
S -> `S				% $0="S";

Flag -> `C			% $0="C";
Flag -> `c			% $0="c";
Flag -> `D			% $0="D";
Flag -> `d			% $0="d";
Flag -> `I			% $0="I";
Flag -> `i			% $0="i";
Flag -> `O			% $0="V";
Flag -> `o			% $0="v";



Arg -> A					% $0=arg(AM_ACC);
Arg -> X					% $0=arg(AM_X);
Arg -> Y					% $0=arg(AM_Y);
Arg -> S					% $0=arg(AM_S);
Arg -> VarArg				% $0=$1;
Arg -> Number				% $0=arg(AM_IMM,$1);
Arg -> &< VarArg			% $0=argto(AM_OFS_LO,$2);
Arg -> &> VarArg			% $0=argto(AM_OFS_HI,$2);
Arg -> VarArg , X			% $0=argto(AM_VAR_X,$1);
Arg -> VarArg , Y			% $0=argto(AM_VAR_Y,$1);
Arg -> ( VarArg )			% $0=argto(AM_IND,$2);
Arg -> ( VarArg , X )		% $0=argto(AM_IND_X,$2);
Arg -> ( VarArg ) , Y		% $0=argto(AM_IND_Y,$2);

VarArg -> Ident				% $0=ident2arg($1,"0",false);
VarArg -> Ident + Ident		% $0=ident2arg($1,$3,false);
VarArg -> Ident - Ident		% $0=ident2arg($1,$3,true);
VarArg -> Ident + Number	% $0=ident2arg($1,$3,false);
VarArg -> Ident - Number	% $0=ident2arg($1,$3,true);



ArithOp -> +				% $0="ADC";
ArithOp -> &				% $0="AND";
ArithOp -> &.				% $0="ANC";
ArithOp -> &?				% $0="BIT";
ArithOp -> ?				% $0="CMP";
ArithOp -> ? --				% $0="DCP";
ArithOp -> - ++				% $0="ISC";
ArithOp -> ^				% $0="EOR";
ArithOp -> -				% $0="SBC";
ArithOp -> |				% $0="ORA";

PostfixOp -> <<				% $0="ASL";
PostfixOp -> --				% $0="DEC";
PostfixOp -> ++				% $0="INC";
PostfixOp -> >>				% $0="LSR";
PostfixOp -> <<<			% $0="ROL";
PostfixOp -> >>>			% $0="ROR";

BranchOp -> >=				% $0="BCS";
BranchOp -> <				% $0="BCC";
BranchOp -> ==				% $0="BEQ";
BranchOp -> <0				% $0="BMI";
BranchOp -> !=				% $0="BNE";
BranchOp -> >=0				% $0="BPL";
BranchOp -> >>=				% $0="BVC";
BranchOp -> <<=				% $0="BVS";
BranchOp -> `c+?			% $0="BCS";
BranchOp -> `c-?			% $0="BCC";
BranchOp -> `z+?			% $0="BEQ";
BranchOp -> `n+?			% $0="BMI";
BranchOp -> `z-?			% $0="BNE";
BranchOp -> `n-?			% $0="BPL";
BranchOp -> `v-?			% $0="BVC";
BranchOp -> `v+?			% $0="BVS";


//BRK	....	interrupt									brk
//JSR	....	jump subroutine								call (##)
//RTI	....	return from interrupt						rti


Number -> RawNumber					% $0=$1;
Number -> [ EvalCode ]				% ST $0=doeval($2,true);

BracketNumber -> [ EvalCode ]		% ST $0=doeval($2,true);


Ident -> IdentText					% $0=$1;
Ident -> . IdentText				% $0=format("__local%d_",local_index) + $2;






// -------- Evaluator --------
//
//	,					pop one value
//	=<ident>			store into <ident> (don't pop)
//	@<ident>			read value from <ident>
//	#<number>			push one immediate
//	?:					ternary operation (3->1)
//	| ^ &				bitwise or/xor/and
//	< > >= <= == !=		comparisons
//	+ - * /				arighmetic
//	%					modulo
//	$<argnum><name>		call function <name> with <argnum> arguments
//							pop all arguments and replace with single result value
//							<argnum> is composed of a number of dots
//	~-					negate topmost value
//
//
//
EvalCode -> EvalInstr								% $0=$1;
EvalCode -> EvalCode EvalInstr						% $0=$1+" , "+$2;

EvalCode -> EvalInstr ;								% $0=$1;
EvalInstr -> EvExpr									% $0=$1;
EvalInstr -> { EvalCode }							% $0=$2;
EvalInstr -> `if EvExpr EvalInstr					% string l=genlabel(); $0="#0 "+$2+" Jz"+l+" , "+$3+" :"+l;
EvalInstr -> `if EvExpr EvalInstr `else EvalInstr	% string l1=genlabel(), l2=genlabel(); $0=$2+" Jz"+l1+" "+$3+" Ja"+l2+" :"+l1+" "+$5+" :"+l2;
EvalInstr -> `while EvExpr EvalInstr				% string l1=genlabel(), l2=genlabel(); $0="#0 :"+l2+" "+$2+" Jz"+l1+" , "+$3+" Ja"+l2+" :"+l1;



EvExpr -> EvSetVar									% $0=$1;
EvExpr -> EvExpr , EvSetVar							% $0=$1+" , "+$3;

EvSetVar -> EvLogOr									% $0=$1;
EvSetVar -> AllIdent = EvSetVar						% $0=$3+" @="+$1;
EvSetVar -> AllIdent += EvSetVar					% $0="@?"+$1+" "+$3+" + @="+$1;
EvSetVar -> AllIdent -= EvSetVar					% $0="@?"+$1+" "+$3+" - @="+$1;
EvSetVar -> AllIdent *= EvSetVar					% $0="@?"+$1+" "+$3+" * @="+$1;
EvSetVar -> AllIdent /= EvSetVar					% $0="@?"+$1+" "+$3+" / @="+$1;
EvSetVar -> AllIdent `%= EvSetVar					% $0="@?"+$1+" "+$3+" % @="+$1;
EvSetVar -> AllIdent |= EvSetVar					% $0="@?"+$1+" "+$3+" | @="+$1;
EvSetVar -> AllIdent &= EvSetVar					% $0="@?"+$1+" "+$3+" & @="+$1;
EvSetVar -> AllIdent ^= EvSetVar					% $0="@?"+$1+" "+$3+" ^ @="+$1;
EvSetVar -> AllIdent <<= EvSetVar					% $0="@?"+$1+" "+$3+" << @="+$1;
EvSetVar -> AllIdent >>= EvSetVar					% $0="@?"+$1+" "+$3+" >> @="+$1;

EvSetVar -> EvLogOr ? EvExpr : EvSetVar				% $0=$1+" "+$3+" "+$5+" ?:";

EvLogOr -> EvLogAnd									% $0=$1;
EvLogOr -> EvLogOr && EvLogAnd						% $0=$1+" "+$3+" ||";

EvLogAnd -> EvBitOr									% $0=$1;
EvLogAnd -> EvLogAnd && EvBitOr						% $0=$1+" "+$3+" &&";

EvBitOr -> EvBitXor									% $0=$1;
EvBitOr -> EvBitOr | EvBitXor						% $0=$1+" "+$3+" |";

EvBitXor -> EvBitAnd								% $0=$1;
EvBitXor -> EvBitXor ^ EvBitAnd						% $0=$1+" "+$3+" ^";

EvBitAnd -> EvCompare                               % $0=$1;
EvBitAnd -> EvBitAnd & EvCompare                    % $0=$1+" "+$3+" &";

EvCompare -> EvRelCompare							% $0=$1;
EvCompare -> EvCompare == EvRelCompare				% $0=$1+" "+$3+" ==";
EvCompare -> EvCompare != EvRelCompare				% $0=$1+" "+$3+" !=";

EvRelCompare -> EvShift								% $0=$1;
EvRelCompare -> EvRelCompare > EvShift				% $0=$1+" "+$3+" >";
EvRelCompare -> EvRelCompare < EvShift				% $0=$1+" "+$3+" <";
EvRelCompare -> EvRelCompare >= EvShift				% $0=$1+" "+$3+" >=";
EvRelCompare -> EvRelCompare <= EvShift				% $0=$1+" "+$3+" <=";
EvRelCompare -> EvRelCompare ?> EvShift             % $0=$1+" "+$3+" !..max";
EvRelCompare -> EvRelCompare ?< EvShift             % $0=$1+" "+$3+" !..min";

EvShift -> EvSum                                    % $0=$1;
EvShift -> EvShift << EvSum                         % $0=$1+" "+$3+" <<";
EvShift -> EvShift >> EvSum                         % $0=$1+" "+$3+" >>";

EvSum -> EvMult                                     % $0=$1;
EvSum -> EvSum + EvMult                             % $0=$1+" "+$3+" +";
EvSum -> EvSum - EvMult                             % $0=$1+" "+$3+" -";

EvMult -> EvUnary									% $0=$1;
EvMult -> EvMult * EvUnary                          % $0=$1+" "+$3+" *";
EvMult -> EvMult / EvUnary                          % $0=$1+" "+$3+" /";
EvMult -> EvMult `% EvUnary                         % $0=$1+" "+$3+" %";

EvUnary -> EvElem									% $0=$1;
EvUnary -> + EvUnary								% $0=$2;
EvUnary -> - EvUnary								% $0=$2+" ~-";
EvUnary -> ~ EvUnary								% $0=$2+" ~";
EvUnary -> ! EvUnary								% $0=$2+" ~!";

EvElem -> String									% $0=$1;
EvElem -> RawNumber									% $0="#"+$1;
EvElem -> RawFloat									% $0="#"+$1;
EvElem -> `pi										% $0="#3.141593";
EvElem -> ( EvExpr )								% $0=$2;
EvElem -> AllIdent									% $0="@?"+$1;
EvElem -> ++ AllIdent								% $0="@?"+$1+" #1 + @="+$1;
EvElem -> -- AllIdent								% $0="@?"+$1+" #1 - @="+$1;
EvElem -> AllIdent ++								% $0="@?"+$1+" #1 + @="+$1+" #1 -";
EvElem -> AllIdent --								% $0="@?"+$1+" #1 - @="+$1+" #1 +";
EvElem -> EvElem [ EvSetVar ]						% $0=$1+" "+$3+" !..index";
EvElem -> EvElem [ EvSetVar , EvSetVar ]			% $0=$1+" "+$3+" "+$5+" !...index";
EvElem -> AllIdent ( OptEvArgList )					% $0=$3+$1;
EvElem -> EvElem . AllIdent							% $0=$1+" !."+$3;
EvElem -> EvElem . AllIdent	( OptEvArgList1 )		% $0=$1+" "+$5+$3;

// returns eval code for all arguments ending with "!..." where number of dots equals argument count
OptEvArgList ->										% $0="!";
OptEvArgList -> EvArgList							% $0=$1;
EvArgList -> EvArg									% $0=$1+" !.";
EvArgList -> EvArg , EvArgList						% $0=$1+" "+$3+".";
EvArg -> EvSetVar									% $0=$1;

// returns eval code for all arguments ending with "!..." where number of dots equals argument count + 1
OptEvArgList1 ->									% $0="!.";
OptEvArgList1 -> EvArgList1							% $0=$1;
EvArgList1 -> EvArg									% $0=$1+" !..";
EvArgList1 -> EvArg , EvArgList1					% $0=$1+" "+$3+".";


TopElem -> `evalfunc AllIdent ( OptEvArgDefs ) [ EvalCode ]		% ST Eval_AddFunction($2,$4,$7); opend();
TopElem -> `evalfunc AllIdent ( OptEvArgDefs ) { EvalCode }		% ST Eval_AddFunction($2,$4,$7); opend();
OptEvArgDefs ->													% $0="";
OptEvArgDefs -> EvArgDefs										% $0=$1;
EvArgDefs -> EvArgDef											% $0=$1;
EvArgDefs -> EvArgDef , EvArgDefs								% $0=$1+" "+$3;
EvArgDef -> AllIdent											% $0=$1;



// -------- Terminal --------
//Number :: [0-9]+    							% $0=getnum($1);
//Number :: [0-9]*[.][0-9]*		    			% $0=getnum($1);
//Number :: [0-9]+e[+-]?[0-9]+    				% $0=getnum($1);
//Number :: [0-9]*[.][0-9]*e[+-]?[0-9]+   		% $0=getnum($1);
//Ident  :: [a-zA-Z_][a-zA-Z0-9_]*				% $0=string2id($1);
//Comment :: "[ \t\n]+"				            % COMMENT
//Comment :: "//[^\n]*"				            % COMMENT
//Comment :: "/[*]([^]*[*])+/"		            % COMMENT




// -------- Terminal --------

RawNumber :: [0-9]+								% $0=$1;
RawNumber :: 0x[0-9a-zA-Z]+						% $0=$1;
RawNumber :: 0b[0-9a-zA-Z]+						% $0=$1;
RawFloat :: [0-9]*[.][0-9]+		    			% $0=$1;

IdentText :: [a-zA-Z_][a-zA-Z0-9_]*				% $0=$1;
String :: "\"[^\"]*\""							% $0=$1;
//EvalString :: "[[][^]]*[]]"					% $0=$1;
Comment :: "[ \t\n\r]+"				            % COMMENT
Comment :: "//[^\n]*"				            % COMMENT
Comment :: "/[*]([^]*[*])+/"		            % COMMENT


$$H

#include "stdafx.h"
#include "common.h"


#define ST		if(!parser_enabled.get_and()) { opend(); break; }


Compiler::symb_t Compiler::RunParser()
{
$$F
}
