
#ifndef _COMMON_H
#define _COMMON_H


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//#include <base.h>
//using namespace base;


#define N_CHARS		128


extern bool g_Options[256];



class Automation {
public:
	struct State {
		int  trans[N_CHARS];
		bool final;
		int  symbol_id;

		State()
		{
			for(int i=0;i<N_CHARS;i++)
				trans[i] = -1;
			final = false;
			symbol_id = -1;
		}
	};

	vector<State>	states;

	bool BuildString(int type,const char *s);
	bool BuildRegex(int type,const char *regex,const char *regex_en=NULL);
	bool BuildComment(int type,const char *start,const char *end);
	bool MergeParallel(const Automation &a,bool ovr=false);
	bool MergeSerial(const Automation &a,char rep_mode);
	void Optimize();

	void DumpTable(int min_char,int max_char);
};




class CompilerBuilder {
public:
	struct Symbol {
		bool	terminal;
		string	name;
		int		symb_id;
	};

	struct Rule {
		int			id_left;
		vector<int>	id_right;
        string		action;
        string		rule_text;
	};

	struct LexerRule {
		int			symb_id;
		string		regex;
		string		action;
	};

	struct State {
		struct XRule {
			int rule;
			int pos;

			bool operator <(const XRule &r) const
			{ return (rule!=r.rule) ? (rule<r.rule) : (pos<r.pos); }
		};

		struct Trans {
			int symbol;
			int target;
		};

		vector<XRule>	rules;
		vector<Trans>	transitions;
		int				reduction;

		bool operator ==(const State &s) const
		{
			if(rules.size() != s.rules.size()) return false;
			for(int i=0;i<rules.size();i++)
				if(rules[i].rule!=s.rules[i].rule || rules[i].pos!=s.rules[i].pos)
					return false;
			return true;
		}
	};

	vector<Symbol>		symbols;
	vector<Rule>		rules;
	vector<LexerRule>	lexer_rules;
	vector<State>		states;
	int					n_terminals;
	int					n_nonterminals;
	Automation			lexer;
	string				lexer_precode;
	string				lexer_postcode;
	string				parser_precode;
	string				parser_postcode;


	CompilerBuilder()
	{
		n_terminals = 0;
		n_nonterminals = 0;
		lexer.states.clear();
		lexer.states.resize(1);
	}

	int  GetSymbolID(const char *name);
	bool AddRule(const char *line);
	bool VerifyRules();
	int  ExpandAndGetStateID(State &s);
	bool BuildStateTable();
	void DumpTransitionTables();


	void GP_AppendAction(const char *action,bool is_parser,string &target);
	void GenerateParser(FILE *fp);
};




#endif
