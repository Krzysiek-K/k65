
output_file_name <- "program.prg"
high_addr <- 0x1DFF



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

// option: -keep
keep_section_names  <- [];
function opt_keep(cmd)
{
	keep_section_names.push(parse_string());
}
OPTIONS.keep <- opt_keep

//compile(@"");


// creates a bank with default parameters
function link_create_bank(name)
{
	local bnum = bank_count();

	if( bnum>0 )
		error("VIC-20 supports only single bank");

	bank_create( name, 1, 0x1001, high_addr, 0 );
}

// executed in linker just after initializing all other sections
function link_make_sections()
{
	// generate start
	as <- sec_create()
	sec_set_name(as,"__start")
	sec_set_type(as,"system")
	sec_set_fixaddr(as,0x1001)
	sec_add_bank(as,"main")
	sec_asm_word(as,0x100B);			// next line pointer
	sec_asm_word(as,10);					// 10 SYS 4109
	sec_asm_byte(as,0x9E);
	sec_asm_string(as,"4109");
	sec_asm_byte(as,0);
	sec_asm_byte(as,0);
	sec_asm_byte(as,0);
	sec_asm(as,"    JMP		main");
	sec_set_referenced(as,1)
	sec_init(as)

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

	if( nbanks!=1 )
		error("VIC-20 supports only single bank");

	local bstart = bank_get_start(0);
	local bsize = bank_get_last_used_byte(0)+1 - bstart;

	bin_write_word(0x1001);
	bin_emit(0,bstart,bsize);

	bin_fclose();
}
