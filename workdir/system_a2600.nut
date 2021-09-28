

compile(@"

var VSYNC = 0;		// $00   0000 00x0   Vertical Sync Set-Clear
var VBLANK;			// $01   xx00 00x0   Vertical Blank Set-Clear
var WSYNC;			// $02   ---- ----   Wait for Horizontal Blank
var RSYNC;			// $03   ---- ----   Reset Horizontal Sync Counter
var NUSIZ0;			// $04   00xx 0xxx   Number-Size player/missle 0
var NUSIZ1;			// $05   00xx 0xxx   Number-Size player/missle 1
var COLUP0;			// $06   xxxx xxx0   Color-Luminance Player 0
var COLUP1;			// $07   xxxx xxx0   Color-Luminance Player 1
var COLUPF;			// $08   xxxx xxx0   Color-Luminance Playfield
var COLUBK;			// $09   xxxx xxx0   Color-Luminance Background
var CTRLPF;			// $0A   00xx 0xxx   Control Playfield, Ball, Collisions
var REFP0;			// $0B   0000 x000   Reflection Player 0
var REFP1;			// $0C   0000 x000   Reflection Player 1
var PF0;			// $0D   xxxx 0000   Playfield Register Byte 0
var PF1;			// $0E   xxxx xxxx   Playfield Register Byte 1
var PF2;			// $0F   xxxx xxxx   Playfield Register Byte 2
var RESP0;			// $10   ---- ----   Reset Player 0
var RESP1;			// $11   ---- ----   Reset Player 1
var RESM0;			// $12   ---- ----   Reset Missle 0
var RESM1;			// $13   ---- ----   Reset Missle 1
var RESBL;			// $14   ---- ----   Reset Ball
var AUDC0;			// $15   0000 xxxx   Audio Control 0
var AUDC1;			// $16   0000 xxxx   Audio Control 1
var AUDF0;			// $17   000x xxxx   Audio Frequency 0
var AUDF1;			// $18   000x xxxx   Audio Frequency 1
var AUDV0;			// $19   0000 xxxx   Audio Volume 0
var AUDV1;			// $1A   0000 xxxx   Audio Volume 1
var GRP0;			// $1B   xxxx xxxx   Graphics Register Player 0
var GRP1;			// $1C   xxxx xxxx   Graphics Register Player 1
var ENAM0;			// $1D   0000 00x0   Graphics Enable Missle 0
var ENAM1;			// $1E   0000 00x0   Graphics Enable Missle 1
var ENABL;			// $1F   0000 00x0   Graphics Enable Ball
var HMP0;			// $20   xxxx 0000   Horizontal Motion Player 0
var HMP1;			// $21   xxxx 0000   Horizontal Motion Player 1
var HMM0;			// $22   xxxx 0000   Horizontal Motion Missle 0
var HMM1;			// $23   xxxx 0000   Horizontal Motion Missle 1
var HMBL;			// $24   xxxx 0000   Horizontal Motion Ball
var VDELP0;			// $25   0000 000x   Vertical Delay Player 0
var VDELP1;			// $26   0000 000x   Vertical Delay Player 1
var VDELBL;			// $27   0000 000x   Vertical Delay Ball
var RESMP0;			// $28   0000 00x0   Reset Missle 0 to Player 0
var RESMP1;			// $29   0000 00x0   Reset Missle 1 to Player 1
var HMOVE;			// $2A   ---- ----   Apply Horizontal Motion
var HMCLR;			// $2B   ---- ----   Clear Horizontal Move Registers
var CXCLR;			// $2C   ---- ----   Clear Collision Latches

var CXM0P = 0;	    // $00  xx00 0000       Read Collision  M0-P1   M0-P0
var CXM1P;			// $01  xx00 0000                       M1-P0   M1-P1
var CXP0FB;			// $02  xx00 0000                       P0-PF   P0-BL
var CXP1FB;			// $03  xx00 0000                       P1-PF   P1-BL
var CXM0FB;			// $04  xx00 0000                       M0-PF   M0-BL
var CXM1FB;			// $05  xx00 0000                       M1-PF   M1-BL
var CXBLPF;			// $06  x000 0000                       BL-PF   -----
var CXPPMM;			// $07  xx00 0000                       P0-P1   M0-M1
var INPT0;			// $08  x000 0000       Read Pot Port 0
var INPT1;			// $09  x000 0000       Read Pot Port 1
var INPT2;			// $0A  x000 0000       Read Pot Port 2
var INPT3;			// $0B  x000 0000       Read Pot Port 3
var INPT4;			// $0C	x000 0000       Read Input (Trigger) 0
var INPT5;			// $0D	x000 0000       Read Input (Trigger) 1

var SWCHA = 0x280;	// $280     Port A data register for joysticks:
					//			Bits 4-7 for player 1.  Bits 0-3 for player 2.

var SWACNT;			// $281     Port A data direction register (DDR)
var SWCHB;			// $282		Port B data (console switches)
var SWBCNT;			// $283     Port B DDR
var INTIM;			// $284		Timer output
var TIMINT;     	// $285
		        
var TIM1T = 0x294;	// $294		set 1 clock interval
var TIM8T;			// $295     set 8 clock interval
var TIM64T;			// $296     set 64 clock interval
var T1024T;			// $297     set 1024 clock interval

");


BANK_SEL <- [
	//			--	F8	F6	F4		<bits>
	0x1FF8,	//	0	0	2	4	b0	1111 1000
	0x1FF9,	//	-	1	3	5	b1	1111 1001
	0x1FF6,	//	-	-	0	2	b2	1111 0110
	0x1FF7,	//	-	-	1	3	b3	1111 0111
	0x1FF4,	//	-	-	-	0	b4	1111 0100
	0x1FF5,	//	-	-	-	1	b5	1111 0101
	0x1FFA,	//	-	-	-	6	b6	1111 1010
	0x1FFB	//	-	-	-	7	b7	1111 1011
];



// option: -superchip
function opt_superchip(cmd)
{
	SUPERCHIP = 1

	compile(@"
		var SCRamWrite = 0x1000;
		var SCRamRead  = 0x1080;
	");

}
OPTIONS.superchip <- opt_superchip
SUPERCHIP <- 0


// option: -keep
keep_section_names  <- [];
function opt_keep(cmd)
{
	keep_section_names.push(parse_string());
}
OPTIONS.keep <- opt_keep


far_jump_stubs <- []



// creates a bank with default parameters
function link_create_bank(name)
{
	local bnum = bank_count();
	local minaddr = SUPERCHIP ? 0xF100 : 0xF000;

	if( bnum>=8 )
		error("Bank count limit exceeded");

	bank_create( name, 1<<bnum, minaddr, 0xFFFF, 3 );

	label_add( "__banksel_"+name, BANK_SEL[bnum], 0 , 0 );
}

// called every time a far call is made
function link_invoke_far_call( as_code, as_target_fn )
{
    if( sec_get_type(as_target_fn)!="func")
		error("[internal] Far call target is not a function (call "+sec_get_name(as_code)+"->"+sec_get_name(as_target_fn)+")");

	if( sec_get_bank_count(as_code)!=1 )
		error("[internal] Far call can only be used in function resident in exactly one bank (call "+sec_get_name(as_code)+"->"+sec_get_name(as_target_fn)+")");

	if( sec_get_bank_count(as_target_fn)!=1 )
		error("[internal] Far call must target function in exactly one bank (call "+sec_get_name(as_code)+"->"+sec_get_name(as_target_fn)+")");
	
	
	// generate stub name
	local func = sec_get_name( as_target_fn );
	local bfrom = sec_get_bank( as_code, 0 );
	local bto = sec_get_bank( as_target_fn, 0 );
	local farname = "__far_" + bfrom + "_" + bto + "__" + func;

	// generate stub code if required
	if( !sec_find( farname ) )
	{
		local as = sec_create();
		sec_set_name( as, farname );
		sec_set_type( as, "stub" );
		sec_add_bank( as, bfrom );
		sec_add_bank( as, bto );
		sec_asm( as, farname );								// label
		sec_asm( as, "    BIT     __banksel_"+bto );		//	BIT		__banksel_to
		sec_asm( as, "    JSR     "+func );					//	JSR		func
		sec_asm( as, "    BIT     __banksel_"+bfrom	);		//	BIT		__banksel_from
		sec_asm( as, "    RTS" );							//	RET
	}

	sec_asm( as_code, "    JSR     "+farname );
}

// called every time a far jump is made
function link_invoke_far_jump( as_code, target_label )
{
	local name = sec_get_name(as_code);
	local bfrom = sec_get_bank(as_code,0);
	local stubname = "__farjmp_" + bfrom + "_" + target_label;
	local found = false;

	foreach(j in far_jump_stubs)
		if(j.stub_name==stubname)
		{
			found = true;
			break;
		}

	if(!found)
		far_jump_stubs.push( {
			stub_name = stubname,
			src_name = name,
			target_label = target_label
		});

	//print("Jump to: "+stubname);
	sec_asm( as_code, "    JMP     "+stubname );
}


// executed in linker just after initializing all other sections
function link_make_sections()
{
	if( bank_count()<=0 )
		error("No banks present")

	if( SUPERCHIP )
		print("SuperChip is ENABLED!");

	// generate vector section
	local as = sec_create()
	sec_set_name(as,"__vectors")
	sec_set_type(as,"system")
	sec_set_fixaddr(as,0xFFF3)
	sec_add_bank(as,"*")
	sec_asm(as,"    NOP");
	sec_asm(as,"    NOP");
	sec_asm(as,"    NOP");
	sec_asm(as,"    NOP");
	sec_asm(as,"    NOP");
	sec_asm(as,"    NOP");
	sec_asm(as,"    NOP");
	sec_asm(as,"    NOP");
	sec_asm(as,"    NOP");
	sec_asm_addr(as,"__entry")
	sec_asm_addr(as,"__entry")
	sec_set_referenced(as,1)
	sec_init(as)

	// generate entry stub
	local entry_bank = sec_get_bank( sec_entrypoint(), 0 );
	as = sec_create()
	sec_set_name(as,"__entry")
	sec_set_type(as,"system")
	sec_set_fixaddr(as,0xFFED)
	sec_add_bank(as,"*")
	sec_add_bank(as,bank_get_name(0))
	sec_asm(as,"__entry")								// label
	sec_asm(as,"    BIT     __banksel_"+entry_bank)		// switch bank
	sec_asm(as,"    JMP     main")						// jump to main function
	sec_init(as)


	// generate far jumps trampolines
	foreach( j in far_jump_stubs )
	{
		local as_src = sec_find(j.src_name);
		if( sec_get_bank_count(as_src)!=1 )
			error("Far jump can only be used in function resident in exactly one bank (jump "+j.src_name+"->"+j.target_label+")");

		local as_dst = label_get_section(j.target_label);
		if( !as_dst )
			error("Target label can't be found in any section (jump "+j.src_name+"->"+j.target_label+")");

		if( sec_get_bank_count(as_dst)!=1 )
			error("Far jump can only jump to a label resident in exactly one bank (jump "+j.src_name+"->"+j.target_label+")");


		local bfrom = sec_get_bank(as_src,0);
		local bto = sec_get_bank(as_dst,0);
		local stubname = "__farjmp_" + bfrom + "_" + j.target_label;

		//print("FarJmp: " + j.src_name + "(" + bfrom + ") -> " + j.target_label + "(" + bto + ")" );
		//print("Stub: "+stubname);

		local as = sec_create();
		sec_set_name( as, stubname );
		sec_set_type( as, "stub" );
		sec_add_bank( as, bfrom );
		sec_add_bank( as, bto );
		sec_asm( as, stubname );							// label
		sec_asm( as, "    BIT     __banksel_"+bto );		//	BIT		__banksel_to
		sec_asm( as, "    JMP     "+j.target_label );		//	JMP		target
		sec_init(as);
	}


	// -keep sections
	foreach( name in keep_section_names )
	{
		local as = sec_find(name);
		if( !as )
			error("Missing section '"+name+"' specified as -keep paramater");
		
		sec_set_referenced(as, 1);
	}
}

// write final binary to file
function link_write_binary(path)
{
	bin_fopen_wb(path);

	local nbanks = bank_count();

	if( nbanks==1 )
	{
		bin_emit(0,0xF000,0x1000);
	}
	else if( nbanks<=2 )
	{
		bin_emit(0,0xF000,0x1000);
		bin_emit(1,0xF000,0x1000);
	}
	else if( nbanks<=4 )
	{
		bin_emit(2,0xF000,0x1000);
		bin_emit(3,0xF000,0x1000);
		bin_emit(0,0xF000,0x1000);
		bin_emit(1,0xF000,0x1000);
	}
	else if( nbanks<=8 )
	{
		bin_emit(4,0xF000,0x1000);
		bin_emit(5,0xF000,0x1000);
		bin_emit(2,0xF000,0x1000);
		bin_emit(3,0xF000,0x1000);
		bin_emit(0,0xF000,0x1000);
		bin_emit(1,0xF000,0x1000);
		bin_emit(6,0xF000,0x1000);
		bin_emit(7,0xF000,0x1000);
	}
	else
		error("Bank count limit exceeded");

	bin_fclose();
}


//function link_print_stats()
//{
//	print("");
//	print("Bank            Used  Free  BlkFree NoCrossFree");
//	local totfree = 0;
//	local totused = 0;
//	local i;
//
//	local IMAGE_SIZE = 0x1000;
//
//	for(i=0;i<bank_count();i++)
//	{
//		local mask = 1<<i;
//		local used = 0;
//		local free = 0;
//		local block_free = 0;
//		local max_block_free = 0;
//		local nocross_free = 0;
//		local max_nocross_free = 0;
//		
//	//	for(int j=0;j<IMAGE_SIZE;j++)
//	//	{
//	//		if(j%256==0) nocross_free = 0;
//	//		if(taken[j]&mask)
//	//		{
//	//			used++;
//	//			block_free = 0;
//	//			nocross_free = 0;
//	//		}
//	//		else
//	//		{
//	//			free++;
//	//			nocross_free++;
//	//			block_free++;
//	//			if(block_free  >max_block_free  ) max_block_free  =block_free;
//	//			if(nocross_free>max_nocross_free) max_nocross_free=nocross_free;
//	//		}
//	//	}
//		totfree += free;
//		totused += used;
//	
//		print(format("%-16s%5d %5d   %5d         %3d",bank_get_name(i),used,free,max_block_free,max_nocross_free));
//	}
//
//	print(format("%16s%5d %5d","--- Total ---  ",totused,totfree));
//	print("");
//}
