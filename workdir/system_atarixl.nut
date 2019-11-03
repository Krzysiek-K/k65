

output_file_name <- "program.xex"
low_addr <- 0x4000
high_addr <- 0x6FFF
intro_mode <- 0

function opt_lowaddr(cmd)
{
	if( !parse_isint() )
		error("Address argument missing")
	local addr = parse_int();
	if( addr<0 || addr>=0xFFFF )
		error("Address outside 0x0000..0xFFFF range")
	low_addr = addr;
}
OPTIONS.lowaddr <- opt_lowaddr

function opt_hiaddr(opt)
{
	if( !parse_isint() )
		error("Address argument missing")
	local addr = parse_int();
	if( addr<0 || addr>=0xFFFF )
		error("Address outside 0x0000..0xFFFF range")
	high_addr = addr;
}
OPTIONS.hiaddr <- opt_hiaddr

function no_system(cmd)
{
}
OPTIONS.noos <- no_system

function set_intro_mode(cmd)
{
	intro_mode = 1; 
}
OPTIONS.intro <- set_intro_mode




// creates a bank with default parameters
function link_create_bank(name)
{
	local bnum = bank_count();

	if( bnum>0 )
		error("Atari XL supports only single bank");

	bank_create( name, 1, low_addr, high_addr, 0 );
}

// executed in linker just after initializing all other sections
function link_make_sections()
{
	// generate start
	if( intro_mode )
	{
		as <- sec_entrypoint()
		sec_set_fixaddr(as,low_addr)
		sec_set_referenced(as,1)
	}
	else
	{
		as <- sec_create()
		sec_set_name(as,"__start")
		sec_set_type(as,"system")
		sec_set_fixaddr(as,low_addr)
		sec_add_bank(as,"main")
		sec_asm(as,"    JMP		main");
		sec_set_referenced(as,1)
		sec_init(as)
	}
}

// write final binary to file
function link_write_binary(path)
{
	bin_fopen_wb(path);

	local nbanks = bank_count();

	if( nbanks!=1 )
		error("Atari XL supports only single bank");

	local bstart = bank_get_start(0);
	local bsize = bank_get_last_used_byte(0)+1 - bstart;

	bin_write_word(0xFFFF);
	bin_write_word(bstart);
	bin_write_word(bstart+bsize-1);
	bin_emit(0,bstart,bsize);

	if( !intro_mode )
	{
		bin_write_word(0x02E0);
		bin_write_word(0x02E1);
		bin_write_word(low_addr);
	}

	bin_fclose();
}
