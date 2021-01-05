output_file_name <- "program.rom"
low_addr <- 0x8000
high_addr <- 0xBFFF

function opt_lowaddr(cmd)
{
	if( !parse_isint() )
		error("Address argument missing")
	local addr = parse_int();
	if( addr<low_addr || addr>=high_addr )
		error("Address outside 0x8000..0xBFFF range")
	low_addr = addr;
}
OPTIONS.lowaddr <- opt_lowaddr

function opt_hiaddr(opt)
{
	if( !parse_isint() )
		error("Address argument missing")
	local addr = parse_int();
	if( addr<low_addr || addr>=high_addr )
		error("Address outside 0x8000..0xBFFF range")
	high_addr = addr;
}
OPTIONS.hiaddr <- opt_hiaddr

function no_system(cmd)
{
}
OPTIONS.noos <- no_system

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
	as <- sec_create()
	sec_set_name(as,"__start")
	sec_set_type(as,"system")
	sec_set_fixaddr(as,low_addr)
	sec_add_bank(as,"main")
	sec_asm(as,"    JMP		main");
	sec_set_referenced(as,1)
	sec_init(as)
}

// write final binary to file
function link_write_binary(path)
{
	bin_fopen_wb(path);

	local nbanks = bank_count();

	if( nbanks!=1 )
		error("Atari XL supports only single bank");

	local bstart = bank_get_start(0);

	bin_emit(0,bstart,1024*16-8);
	bin_write_word(0x0060);
	bin_write_word(low_addr);
	bin_write_word(0x0400);
	bin_write_word(0xBFF8);

	bin_fclose();
}
