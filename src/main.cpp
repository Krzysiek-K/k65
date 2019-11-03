
#include "stdafx.h"
#include "common.h"


static bool link_done = false;



string run_line(const char *_line,const string &caller);



bool _fixpath(const string &path,string &newpath)
{
	newpath = path;

	//vector<string> elems;
	//const char *s = path;
	//while(*s)
	//{
	//	const char *p = s;
	//	while(*s && *s!='/' && *s!='\\')
	//		s++;
	//	elems.push_back(string(p,s));
	//	while(*s=='/' || *s=='\\')
	//		s++;
	//}

	//for(int i=0;i<elems.size();i++)
	//	if(elems[i]==".")
	//	{
	//		elems.erase(elems.begin()+i);
	//		i--;
	//	}
	//	else if(elems[i]==".." && i>0)
	//	{
	//		// remove elements at i-1 and i
	//		elems.erase(elems.begin()+(i-1),elems.begin()+(i+1));
	//		i -= 2;
	//	}

	//string newpath;
	//for(int i=0;i<elems.size();i++)
	//{
	//	if(i) newpath.push_back('/');
	//	newpath.append(elems[i]);
	//}

	FILE *fp = fopen(newpath.c_str(),"rb");
	if(fp) fclose(fp);
	//printf("fixpath: %s -> %s\n",newpath.c_str(),fp ? "FOUND" : "NOT FOUND");

//	printf(">%c %s\n",(fp?'+':'-'),newpath.c_str());
	
	return fp != NULL;
}

string fixpath(const char *path)
{
	string newpath;
	if( _fixpath( current_script_path+"/"+path, newpath ) ) return newpath;		// try relative to script path
	if( _fixpath( path, newpath ) ) return newpath;								// try relative to script path
	if( _fixpath( current_exe_path+"/"+path, newpath ) ) return newpath;		// try relative to script path
	return path;
}



string run_file(const char *fname)
{
	vector<string> lines;
	string path = fixpath( fname );

	if( !NFS.GetFileLines(path.c_str(),lines) ) 
		return "Can't open file '"+string(fname)+"'";

	string _path = current_script_path;
	current_script_path = FilePathGetPart(path.c_str(),true,false,false);
	if( current_script_path.size()>0 && (current_script_path[current_script_path.size()-1]=='/' || current_script_path[current_script_path.size()-1]=='\\') )
		current_script_path.erase(current_script_path.end()-1);
	
	for(int i=0;i<(int)lines.size();i++)
	{
		string err = run_line(lines[i].c_str(),path);
		if( err.size()>0 ) return err;
	}
	
	current_script_path = _path;

	return "";
}


string run_line(const char *_line,const string &caller)
{
	string line = _line;
	const char *s = line.c_str();

	// cut comment
	for(int i=0;i<(int)line.size();i++)
	{
		s = line.c_str()+i;
		if(*s=='#' || (*s=='/' && s[1]=='/'))
		{
			line.resize(i);
			break;
		}
	}
	
	s = line.c_str();
	ParseWhitespace(s);
	if( !*s )
		return "";

	// execute script
	if( *s=='$' )
	{
		s++;
		if( !execute(s) ) return "Error during execution of "+caller+"\nLine: "+line;
		return "";
	}

	// include file
	const char *p = s;
	if( *s=='@' )
	{
		s++;
		p = s;
		string fname = ParseString(s);
		ParseWhitespace(s);
		if(*s) return "Invalid file name: "+string(p)+"\n  (put quoes around file name if the name contains spaces)";
		return run_file(fname.c_str());
	}

	// execute system command
	if( *s=='!' )
	{
		s++;
		printf("%s\n",s);
		int code = system(s);
		if(code!=0) return format("System command returned exit code %d",code);
		return "";
	}

	// execute option
	if( *s=='-' )
	{
		string opt = ParseString(s);
		if(opt=="-system")
		{
			string sys = "system_" + ParseString(s) + ".nut";
			for(int i=0;i<(int)sys.size();i++)
				sys[i]=tolower(sys[i]);
			if( !execute(sys.c_str()) ) return "Error during execution of "+caller+"\nLine: "+line;
		}
		else if(opt=="-link")
		{
			if(link_done) return "Linking already done";
			const char *_err = sqlink.Link();
			link_done = true;
			if(_err) return _err;
		}
		else
		{
			try {
				if( !vm.RunRet<int>("link_option",opt+s) )
					return "Unknown option "+opt;
				return "";
			}
			catch(const char *err)
			{
				return format("Error: %s\nDuring execution of: link_option(\"%s\")",err,opt.c_str());
			}
		}
	}

	// set variable
	p = s;
	string vname = ParseString(s);
	if( s>p && vname.size()>0 )
	{
		ParseWhitespace(s);
		if( *s=='=' )
		{
			s++;
			string value = ParseString(s);

			// try parsing as integer
			s = value.c_str();
			ParseWhitespace(s);
			int ivalue = ParseInt(s);
			ParseWhitespace(s);
			if(!*s)
			{
				cmp.SetVar(vname.c_str(),ivalue);
				if( !vm.Set(("_v_"+vname).c_str(),ivalue) ) return "Error during execution of "+caller+": can't set variable '"+vname+"'";
				return "";
			}

			// try parsing as float
			s = value.c_str();
			ParseWhitespace(s);
			float fvalue = ParseFloat(s);
			ParseWhitespace(s);
			if(!*s)
			{
				cmp.SetVar(vname.c_str(),fvalue);
				if( !vm.Set(("_v_"+vname).c_str(),fvalue) ) return "Error during execution of "+caller+": can't set variable '"+vname+"'";
				return "";
			}

			// set as string
			if( !vm.Set(("_v_"+vname).c_str(),value) ) return "Error during execution of "+caller+": can't set variable '"+vname+"'";
			return "";
		}
	}
	s = p;

	// otherwise: raw line
	if( vm.GetInt("config_line_installed") )
	{
		// run script line
		if(!vm.Run("config_line",line,caller)) return "Error during execution of "+caller;
	}
	else
	{
		// compile file
		string fname = ParseString(s);
		if(fname.size()<=0 ) return "";

		string bank = ParseString(s);
		if(bank.size()<=0) bank = "default";
					
		if(link_done) return "Linking already done";

		printf("Compiling file: %s ...\n",fname.c_str());


        // open
		string path = fixpath( fname );
		FILE *fp = fopen(path.c_str(),"rt");
		if(!fp)
			return "Can't open source file '"+string(fname)+"'";

        // read
		string code;
        char buff[10000];
        while(1)
        {
            int len = fread(buff,1,10000,fp);
            code.append(buff,buff+len);
            if(len<=0) break;
        }

        // done
        fclose(fp);

		// compile
		cmp.SetBank(bank.c_str());
		const char *_err = cmp.Compile(code.c_str());
		if(_err) return _err;
	}

	return "";
}


string run_command_line(int argc,char *argv[])
{
	vector<string> filenames;
	vector<string> banks;
	vector<string> files;
	vector<const char *> pfiles;

	cmp.InitCompile();

	if( !execute("system.nut") ) return "Error during execution of system.nut";


	// read file names
	for(int i=1;i<argc;i++)
	{
		string err = run_line(argv[i],format("commandline arg #%d",i));
		if(err.size()>0) return err;
	}

	if(!link_done)
	{
		const char *_err = sqlink.Link();
		link_done = true;
		if(_err) return _err;
	}

	return "";
}



int main(int argc, char * argv[])
{
	// print version info
	printf("K65 compiler, version " K65_VERSION_TEXT() ", build " __DATE__ " " __TIME__ ".\n");
	printf("Copyright (C) 2012-2015 Krzysztof Kluczek ( devkk.net ).\n");
	printf("This is free software; see the source for copying conditions.  There is NO\n");
	printf("warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
	printf("\n");


	// setup paths
#ifdef WIN32
	current_exe_path = FilePathGetPart(_pgmptr,true,false,false);
#else
	current_exe_path = FilePathGetPart(argv[0], true, false, false);
#endif
	current_script_path = ".";

	// setup VM
	vm.Init();
	vm.Set("config_line_installed",0);

	// run
	string err = run_command_line(argc,argv);

	if(err.size()>0)
	{
		printf("%s\n",err.c_str());
		printf("\n\n\n");
		system("pause");
		return 1;
	}
	else
		printf("All OK.\n");

	return 0;
}
