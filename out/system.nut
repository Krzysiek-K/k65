
output_file_name <- "program.bin"


OPTIONS <- {}





function option_args_all(opt)
{
	local p = 0;
	while(p<opt.len() && (opt[p]!=' ' && opt[p]!='\t')) p++;
	while(p<opt.len() && (opt[p]==' ' || opt[p]=='\t')) p++;
	return  opt.slice(p);
}

function opt_output(opt)
{
	output_file_name = option_args_all(opt)
}

OPTIONS.o <- opt_output
OPTIONS.output <- opt_output


function link_create_bank(name)
{
	error("No system specified. Please use \"-system <system>\" flag first.");
}

function link_invoke_far_call( as_code, as_target_fn )
{
	error("System does not support far calls.");
}

function link_make_sections()
{
	error("No system specified. Please use \"-system <system>\" flag first.");
}

function link_write_binary(path)
{
	error("No system specified. Please use \"-system <system>\" flag first.");
}

function link_option(opt)
{
	parse_setline(opt);
	local cmd = parse_string().tolower();
	if(cmd.len()>0 && cmd[0]=='-')
		cmd = cmd.slice(1);

	if( cmd in OPTIONS )
	{
		OPTIONS[cmd](opt);
		return 1;
	}
	return 0;
}

//function link_print_stats()
//{
//	print("No stats available.\n");
//}
