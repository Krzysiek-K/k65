
#include "common.h"


bool g_Options[256];



int main(int argc,const char *argv[])
{
    if(argc>=2 && argv[1][0]=='-')
    {
        const char *s = argv[1];
        s++;
        while(*s)
            g_Options[*s++] = true;
        argc--;
        argv++;
    }

	if(argc<3)
	{
		printf("\n");
		printf("Usage:\n");
		printf("\t%s [options] <input-grammar> <output-code>\n", argv[0]);
		printf("\n");
		printf("Options:\n");
		printf("\t-D\tAdd debug info\n");
		printf("\n");
		return -1;
	}

	FILE *fp = fopen(argv[1],"rt");
	if(!fp)
	{
		printf("Can't open %s\n",argv[1]);
		return -1;
	}

	CompilerBuilder cb;
	cb.GetSymbolID("Syntax");

	string header;
	string footer;

	string filename = argv[1];
	for(int i=0;i<filename.size();i++)
		if(filename[i]=='\\')
			filename[i] = '/';
	char line[1000];
	int line_id = 0;
	int mode = 0;
	while(fgets(line,1000,fp))
	{
		// *nix fix
		{
			char *fix = line;
			while( *fix && *fix!='\r' && *fix!='\n' ) fix++;
			*fix = 0;
		}

		line_id++;
		if(line[0]=='$' && line[1]=='$')
		{
			const char *s = line+2;
			string cmd;
			{
				// cmd = ParseString(s);
				while( *s && isspace(*s) ) s++;
				const char *b = s;
				while( *s && !isspace(*s) ) s++;
				cmd.assign(b, s);

			}
			while( isspace(*s) ) s++;		//  ParseWhitespace(s);
			string rest;
			while(*s && *s!='\n' && *s!='\r')
				rest.push_back(*s++);

			if( cmd=="G" || cmd=="Rules" )
				mode = 0;
			else if( cmd=="H" || cmd=="Code" )
			{
//				header += format("#line %d \"%s\"\n",line_id+1,filename.c_str());
				mode = 1;
			}
			else if( cmd=="F" || cmd=="Parser" )
			{
//				header += format("#line %d \"%s\"\n",line_id+1,filename.c_str());
				mode = 2;
			}
			else if( cmd=="LexerPrecode"	) cb.lexer_precode = rest;
			else if( cmd=="LexerPostcode"	) cb.lexer_postcode = rest;
			else if( cmd=="ParserPrecode"	) cb.parser_precode = rest;
			else if( cmd=="ParserPostcode"	) cb.parser_postcode = rest;
			else if( cmd=="Precode"			) cb.lexer_precode = cb.parser_precode = rest;
			else if( cmd=="Postcode"		) cb.lexer_postcode = cb.parser_postcode = rest;
			else
			{
				printf("Error on line %d\n%s\n",line_id,line);
				fclose(fp);
				return -1;
			}
		}
		else if(mode==0)
		{
			if(!cb.AddRule(line))
			{
				printf("Error on line %d\n%s\n",line_id,line);
				fclose(fp);
				return -1;
			}
		}
		else if(mode==1)
		{
			header += line;
			header += "\n";
		}
		else
		{
			footer += line;
			footer += "\n";
		}
	}
	fclose(fp);

	if(!cb.BuildStateTable())
		return -1;

//	cb.DumpTransitionTables();

	fp = fopen(argv[2],"wt");
	if(fp)
	{
		fprintf(fp,"%s",header.c_str());
		cb.GenerateParser(fp);
		fprintf(fp,"%s",footer.c_str());
		fclose(fp);
	}
	else
	{
		printf("Can't write to %s\n",argv[2]);
		return -1;
	}

	printf("\n");

	return 0;
}
