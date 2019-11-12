
#include "common.h"

#include "lexer.inl"



static bool parse_string(const char *&s,string &out)
{
	while(*s==' ' || *s=='\t' || *s=='\n')
		s++;
	if(*s!='"')
	{
		const char *p = s;
		while(*s && *s!=' ' && *s!='\t' && *s!='\n')
			s++;
		out.assign(p,s-p);
	}
	else
	{
		s++;
		out.clear();
		while(*s && *s!='"' && *s!='\n')
		{
			if(*s=='\\')
			{
				s++;
				if(*s=='n') out.push_back('\n'), s++;
				else if(*s=='t') out.push_back('\t'), s++;
				else if(*s=='b') out.push_back('\b'), s++;
				else if(*s=='r') out.push_back('\r'), s++;
				else if(*s=='"') out.push_back('"'), s++;
				else if(*s=='\\') out.push_back('\\'), s++;
			}
			else
				out.push_back(*s++);
		}
		if(*s=='"')
			s++;
	}
	return out.size()>0;
}


int CompilerBuilder::GetSymbolID(const char *name)
{
	for(int i=0;i<symbols.size();i++)
		if(symbols[i].name==name)
			return i;
	int id = symbols.size();
	symbols.push_back(Symbol());
	symbols[id].name = name;
	symbols[id].terminal = !( (name[0]>='A' && name[0]<='Z') || (name[0]>='a' && name[0]<='z') );
	if(symbols[id].terminal)
		symbols[id].symb_id = n_terminals++;
	else
		symbols[id].symb_id = n_nonterminals++;
	return id;
}

bool CompilerBuilder::AddRule(const char *line)
{
	Rule r;
	string tmp, idstr;

	if(line[0]=='#') return true;
	if(line[0]=='/') return true;

    {
        const char *s = line;
        while(*s && *s!='%') s++;
        r.rule_text.assign(line,s);
    }

	if(!parse_string(line,idstr)) return true;
	r.id_left = GetSymbolID(idstr.c_str());

	if(!parse_string(line,tmp)) { printf("Unexpected end of line.\n"); return false; }
	
	if(tmp=="::")
	{
		LexerRule lr;
		bool def = (idstr=="_default_");
		if(def)
		{
			lr.regex = "";
			lr.symb_id = -1;
		}
		else
		{
			if(symbols[r.id_left].terminal) { printf("Symbol name expected.\n"); return false; }
			if(!parse_string(line,tmp)) { printf("Regex expected.\n"); return false; }
			lr.regex = tmp;
			lr.symb_id = r.id_left;
		}
		if(parse_string(line,tmp))
		{
			if(tmp!="%") { printf("'%%' expected.\n"); return false; }
			lr.action = line;
		}
		lexer_rules.push_back(lr);

		if(!def)
		{
			int i = lexer_rules.size()-1;
			Automation a;
			if(!a.BuildRegex(i,lexer_rules[i].regex.c_str()))
			{
				printf("Regex '%s' compilation error.\n",lexer_rules[i].regex.c_str());
				return false;
			}
			if(!lexer.MergeParallel(a))
			{
				printf("Conflicting regular expressions with '%s'.\n",lexer_rules[i].regex.c_str());
				return false;
			}
		}

		return true;
	}

	if(symbols[r.id_left].terminal) { printf("Symbol name expected.\n"); return false; }
	if(tmp!="->") { printf("'->' or '::' expected.\n"); return false; }

	while(parse_string(line,tmp))
	{
		if(tmp!="%")
			r.id_right.push_back(GetSymbolID(tmp.c_str()));
		else
		{
			r.action = line;
			break;
		}
	}

	rules.push_back(r);

	return true;
}

bool CompilerBuilder::VerifyRules()
{
	for(int i=0;i<lexer_rules.size();i++)
		if(lexer_rules[i].symb_id>=0)
			symbols[lexer_rules[i].symb_id].terminal = true;

	n_terminals = 0;
	n_nonterminals = 0;
	for(int i=0;i<symbols.size();i++)
		if(symbols[i].terminal)	symbols[i].symb_id = n_terminals++;
		else					symbols[i].symb_id = n_nonterminals++;

	for(int i=0;i<rules.size();i++)
	{
		if( (i==0) != (rules[i].id_left==0) )
		{
			printf("First rule and only first rule should define syntax.\n");
			return false;
		}

		if(symbols[rules[i].id_left].terminal)
		{
			printf("Symbol '%s' defined as both terminal nad nonterminal.\n",symbols[rules[i].id_left].name.c_str());
			return false;
		}

		for(int j=0;j<rules[i].id_right.size();j++)
			if(rules[i].id_right[j]==0)
			{
				printf("'Syntax' symbol used on right side.\n");
				return 0;
			}
	}

	for(int i=0;i<symbols.size();i++)
		if(!symbols[i].terminal)
		{
			bool found = false;
			for(int j=0;j<rules.size();j++)
				if(rules[j].id_left==i)
				{
					found = true;
					break;
				}
			if(!found)
			{
				printf("No rules for '%s' defined.\n",symbols[i].name.c_str());
				return false;
			}
		}

	return true;
}

int CompilerBuilder::ExpandAndGetStateID(State &s)
{
	// expand
	for(int i=0;i<s.rules.size();i++)
	{
		State::XRule xr = s.rules[i];
		if(xr.pos>=rules[xr.rule].id_right.size())
			continue;
		int sid = rules[xr.rule].id_right[xr.pos];
		if(symbols[sid].terminal)
			continue;

		for(int j=0;j<rules.size();j++)
			if(rules[j].id_left==sid)
			{
				bool n=true;
				for(int k=0;k<s.rules.size() && n;k++)
					if(s.rules[k].rule==j && s.rules[k].pos==0)
						n = false;
				if(n)
				{
					State::XRule nxr;
					nxr.rule = j;
					nxr.pos = 0;
					s.rules.push_back(nxr);
				}
			}
	}

	// get state id
	sort(s.rules.begin(),s.rules.end());

	for(int i=0;i<states.size();i++)
		if(states[i]==s)
			return i;
	states.push_back(s);
	return states.size()-1;
}

bool CompilerBuilder::BuildStateTable()
{
	if(!VerifyRules())
		return false;

	for(int i=0;i<symbols.size();i++)
		if(symbols[i].terminal)
		{
			int ch = symbols[i].name.c_str()[0];
			if((ch>='a'&&ch<='z') || (ch>='A'&&ch<='Z'))
				continue;
			Automation a;
			const char *s = symbols[i].name.c_str();
			if(*s=='`') s++;
			if(!a.BuildString(symbols[i].symb_id+lexer_rules.size(),s))
			{
				printf("Can't build lexer for symbol '%s'.\n",symbols[i].name.c_str());
				return false;
			}
			if(!lexer.MergeParallel(a,true))
			{
				printf("Conflicting regular expressions with symbol '%s'.\n",symbols[i].name.c_str());
				return false;
			}
		}

	Symbol eof;
	eof.symb_id = n_terminals++;
	eof.terminal = true;
	symbols.push_back(eof);
	Automation a;
	a.states.resize(2);
	a.states[1].final = true;
	a.states[0].trans[0] = 1;
	a.states[1].symbol_id = eof.symb_id+lexer_rules.size();
	lexer.MergeParallel(a);
	lexer.Optimize();

	State start;
	State::XRule xr;
	xr.rule = 0;
	xr.pos = 0;
	start.rules.push_back(xr);

	ExpandAndGetStateID(start);

	for(int i=0;i<states.size();i++)
	{
		states.reserve(states.size() + states[i].rules.size());
		State *s = &states[i];
		s->reduction = -1;

		for(int j=0;j<s->rules.size();j++)
		{
			State::XRule xr = s->rules[j];
			if(xr.pos >= rules[xr.rule].id_right.size())
			{
				if(s->reduction!=-1)
				{
					printf("reduce/reduce conflict.\n");
					for(int k=0;k<2;k++)
					{
						int rd = (k==0) ? s->reduction : xr.rule;
						printf("%s ->",symbols[rules[rd].id_left].name.c_str());
						for(int l=0;l<rules[rd].id_right.size();l++)
							printf(" %s",symbols[rules[rd].id_right[l]].name.c_str());
						printf("\n");
					}
					return false;
				}
				s->reduction = xr.rule;
				continue;
			}

			int sid = rules[xr.rule].id_right[xr.pos];
			for(int k=0;k<s->transitions.size();k++)
				if(s->transitions[k].symbol==sid)
					sid = -1;
			if(sid<0)
				continue;

			State trg;
			for(int k=0;k<s->rules.size();k++)
			{
				State::XRule nxr = s->rules[k];
				if(nxr.pos >= rules[nxr.rule].id_right.size())
					continue;
				if(rules[nxr.rule].id_right[nxr.pos]!=sid)
					continue;
				nxr.pos++;
				trg.rules.push_back(nxr);
			}

			State::Trans tr;
			tr.symbol = sid;
			tr.target = ExpandAndGetStateID(trg);
			s->transitions.push_back(tr);
		}
	}

	printf("Created %d states.\n",states.size());

	return true;
}

void CompilerBuilder::DumpTransitionTables()
{
	for(int i=0;i<states.size();i++)
	{
		printf("\nState %d:\n",i);
		for(int j=0;j<states[i].rules.size();j++)
		{
			printf("%s ->",symbols[rules[states[i].rules[j].rule].id_left].name.c_str());
			int k=0;
			for(;k<rules[states[i].rules[j].rule].id_right.size();k++)
			{
				if(states[i].rules[j].pos==k)
					printf(" .");
				printf(" %s",symbols[rules[states[i].rules[j].rule].id_right[k]].name.c_str());
			}
			if(states[i].rules[j].pos==k)
				printf(" .");
			printf("\n");
		}
	}

	for(int t=0;t<2;t++)
	{
		bool term = (t==0);

		printf(term ? "\n\nTransition table:\n" : "\n\nGOTO table:\n");
		for(int i=0;i<symbols.size();i++)
			if(symbols[i].terminal==term)
				printf("\t%s",symbols[i].name.c_str());
		printf("\n");
		for(int i=0;i<states.size();i++)
		{
			printf("%d",i);
			for(int j=0;j<symbols.size();j++)
			{
				if(symbols[j].terminal!=term)
					continue;

				int tr = -1;
				for(int k=0;k<states[i].transitions.size();k++)
					if(states[i].transitions[k].symbol==j)
						tr = states[i].transitions[k].target;
				if(term)
				{
					if(tr>=0)	printf("\ts%d",tr);
					else
						if(states[i].reduction>=0)	printf("\tr%d",states[i].reduction);
						else						printf("\t");
				}
				else
				{
					if(tr>=0)	printf("\t%d",tr);
					else		printf("\t");
				}
			}
			printf("\n");
		}
	}
}

void CompilerBuilder::GP_AppendAction(const char *action,bool is_parser,string &target)
{
	bool in_quote = false;
	string name;

	const char *s = action;


	while(*s)
	{
		if( *s=='"' )
			in_quote = !in_quote;

		if(!in_quote && *s=='$')
		{
			s++;
			const char *b = s;
			bool is_number = true;
			while(1)
			{
					 if(*s>='0' && *s<='9') s++;
				else if(*s>='a' && *s<='z') s++, is_number=false;
				else if(*s>='A' && *s<='Z') s++, is_number=false;
				else break;
			}
			name.assign(b,s);

			if(is_number)
			{
				int number = atoi(name.c_str());
				if(is_parser)
				{
					// parser
					if(number==0)	target.append("S0");
					else	
					{
						char buff[32];
						sprintf(buff, "S(%d)", number);
						target += buff;
					}
				}
				else
				{
					// lexer
					if(number==0)	target.append("next_symb");
					else			target.append("st.c_str()");
				}
			}
		}
		else
		{
			if(*s!='\n') target.push_back(*s);
			s++;
		}
	}
}


void CompilerBuilder::GenerateParser(FILE *fp)
{
	fprintf(fp,"\tstatic const int LEXER[%d][%d] = {\n",N_CHARS,lexer.states.size());
	for(int i=0;i<N_CHARS;i++)
	{
		fprintf(fp,"\t\t{");
		for(int j=0;j<lexer.states.size();j++)
			fprintf(fp,"%4d,",lexer.states[j].trans[i]);
		fprintf(fp," }, // %c\n",(i>=' ' && i<127 && i!='\\')?i:' ');
	}
	fprintf(fp,"\t};\n\n");

	fprintf(fp,"\tstatic const int MATCH[%d] = {\n\t\t",lexer.states.size());
	for(int i=0;i<lexer.states.size();i++)
		fprintf(fp,"%4d,",lexer.states[i].final?lexer.states[i].symbol_id:-1);
	fprintf(fp,"\n\t};\n\n");

	fprintf(fp,"\tstatic const int ACTION[%d][%d] = {\n",states.size(),n_terminals);
	for(int i=0;i<states.size();i++)
	{
		fprintf(fp,"\t\t{");
		for(int j=0;j<symbols.size();j++)
			if(symbols[j].terminal)
			{
				int tr = 0;
				for(int k=0;k<states[i].transitions.size();k++)
					if(states[i].transitions[k].symbol==j)
					{
						tr = states[i].transitions[k].target+1;
						break;
					}
				if(tr==0 && states[i].reduction>=0)
					if(states[i].reduction!=0 || symbols[j].symb_id==n_terminals-1)
						tr = ~states[i].reduction;
				fprintf(fp,"%4d,",tr);
			}
		fprintf(fp," },\n");
	}
	fprintf(fp,"\t};\n\n");

	fprintf(fp,"\tstatic const int GOTO[%d][%d] = {\n",states.size(),n_nonterminals-1);
	for(int i=0;i<states.size();i++)
	{
		fprintf(fp,"\t\t{");
		for(int j=1;j<symbols.size();j++)
			if(!symbols[j].terminal)
			{
				int tr = -1;
				for(int k=0;k<states[i].transitions.size();k++)
					if(states[i].transitions[k].symbol==j)
					{
						tr = states[i].transitions[k].target;
						break;
					}
				fprintf(fp,"%4d,",tr);
			}
		fprintf(fp," },\n");
	}
	fprintf(fp,"\t};\n\n");

	fprintf(fp,"\tstatic const char *SYMB[%d] = {\n\t\t",n_terminals);
	for(int i=0;i<symbols.size();i++)
		if(symbols[i].terminal)
			fprintf(fp,"\"%s\",",symbols[i].name.c_str());
	fprintf(fp,"\n\t};\n\n");

	fprintf(fp, CODE_PRELEXER );

	bool was_default = false;
	for(int i=0;i<lexer_rules.size();i++)
	{
		if(lexer_rules[i].symb_id>=0)
			fprintf(fp,"\t\t\tcase %4d: { next_type = %d; ",i,symbols[lexer_rules[i].symb_id].symb_id);
		else
		{
			fprintf(fp,"\t\t\tdefault  : { next_type = best_match-%d; ",lexer_rules.size());
			was_default = true;
		}
		
		string src = lexer_precode + lexer_rules[i].action + " " + lexer_postcode;
		string ns;
		const char *s = src.c_str();
		while(*s)
		{
			if(*s=='$')
			{
				s++;
				int v = 0;
				while(*s>='0' && *s<='9')
					v = v*10 + (*s++) - '0';
				if(v==0)	ns.append("next_symb");
				else		ns.append("st.c_str()");
			}
			else
				if(*s!='\n')
					ns.push_back(*s++);
				else
					s++;
		}
		fprintf(fp,"%s } break;\n",ns.c_str());
	}

	if(!was_default)
		fprintf(fp,"\t\t\tdefault  : next_type = best_match-%d; next_symb = symb_t(); break;\n",lexer_rules.size());

	fprintf(fp, CODE_POSTLEXER	);

	fprintf(fp, CODE_PREPARSER );

	for(int i=0;i<rules.size();i++)
	{
		fprintf(fp,"\t\t\tcase %4d: { nr=%4d; nst=%4d; ",
					i,rules[i].id_right.size(),symbols[rules[i].id_left].symb_id-1);

		string src = parser_precode + rules[i].action + " " + parser_postcode;
		string ns;
		const char *s = src.c_str();
		while(*s)
		{
			if(*s=='$')
			{
				s++;
				int v = 0;
				while(*s>='0' && *s<='9')
					v = v*10 + (*s++) - '0';
				if(v==0)
					ns.append("S0");
				else
				{
					char buff[20];
					sprintf(buff,"S(%d)",v);
					ns.append(buff);
				}
			}
			else
				if(*s!='\n')
					ns.push_back(*s++);
				else
					s++;
		}

        if(g_Options['D'])
        {
            Rule &r = rules[i];
            const char *ds = r.rule_text.c_str();

            ns.append(" DBGINFO(\"");
            while(*ds)
            {
                if(*ds=='\t')
                    ns.append("\\t");
                else if(*ds=='\n' && ds[1]!=0)
                    ns.append("<nl>");
                else if((int(*ds)&0xFF)>=' ')
                {
                    if(*ds=='"' || *ds=='\\') ns.push_back('\\');
                    ns.push_back(*ds);
                }
                ds++;
            }
            ns.append("\")");
        }

		fprintf(fp,"%s } break;\n",ns.c_str());
	}

	fprintf(fp, CODE_POSTPARSER );
}
