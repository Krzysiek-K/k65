BEGIN{
	indef=0
}

{
	gsub(/\r/,"");
	ok=1;
}

$1=="$$"{
	print "" >OUTFILE;
	print "#define " $2 "\t\\" >OUTFILE;
	ok=0;
	indef=1;
}
$0!~/^[ \t]*$/ && ok {
	gsub(/\\/,"\\\\");
	gsub(/"/,"\\\"");
	gsub(/\t/,"\\t");
	gsub(/^\.[ \t]*$/,"");
	print "\t\"" $0 "\\n\" \\" >OUTFILE;
}
END{
	print"" >OUTFILE;
}