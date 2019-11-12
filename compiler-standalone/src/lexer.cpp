
#include "common.h"


bool Automation::BuildString(int type,const char *s)
{
	states.clear();
	states.resize(1);
	states[0].final = true;

	while(*s)
	{
		Automation a;

		a.states.resize(2);
		a.states[1].final = true;
		int ch = *s++;
		if(ch<0 || ch>=N_CHARS)
			ch = N_CHARS-1;
		a.states[0].trans[ch] = 1;

		if(!MergeSerial(a,'.'))
			return false;
	}

	for(int i=0;i<states.size();i++)
		if(states[i].final)
			states[i].symbol_id = type;

	Optimize();

	return true;
}


bool Automation::BuildRegex(int type,const char *regex,const char *regex_end)
{
	if(!regex_end)
		regex_end = regex + strlen(regex);

	states.clear();
	states.resize(1);
	states[0].final = true;

	while(regex<regex_end)
	{
		Automation a;

		if(*regex=='(')	// group
		{
			regex++;
			const char *s = regex;
			int depth = 0;
			Automation b;
			bool first = true;

			while(regex<regex_end)
			{
				if(depth==0 && (*regex=='|' || *regex==')'))
				{
					if(first)
					{
						if(!a.BuildRegex(-1,s,regex))
							return false;
					}
					else
					{
						if(!b.BuildRegex(-1,s,regex) || !a.MergeParallel(b))
							return false;
					}
					first = false;
					if(*regex==')') break;
					regex++;
					s = regex;
				}
				else
				{
					if(*regex=='(') depth++;
					if(*regex==')') depth--;
					regex++;
				}
			}
			if(first || regex>=regex_end || *regex!=')')
				return false;
			regex++;
		}
		else if(*regex=='[')
		{
			regex++;
			a.states.clear();
			a.states.resize(2);
			a.states[1].final = true;

			bool invert = false;
			int prev = -1;
			if(*regex=='^') invert = true, regex++;
			while(regex<regex_end)
			{
				if(*regex==']' && !(regex<regex_end && regex[1]==']'))
					break;
				int ch = *regex++;
				if(ch<0 || ch>=N_CHARS) ch = N_CHARS-1;
				if(prev>=0 && ch=='-' && regex<regex_end && *regex!=']')
				{
					ch = *regex++;
					if(ch<0 || ch>=N_CHARS) ch = N_CHARS-1;
					for(int i=prev;i<=ch;i++)
						a.states[0].trans[i] = 1;
				}
				else
					a.states[0].trans[ch] = 1;
				prev = int(ch)&0xFF;
			}
			if(invert)
				for(int i=0;i<N_CHARS;i++)
					a.states[0].trans[i] = -a.states[0].trans[i];
			if(regex>=regex_end || *regex!=']')
				return false;
			regex++;
		}
		else
		{
			if(*regex=='?' || *regex=='+' || *regex=='*' || *regex==')' || *regex=='|' || *regex=='.')
				return false;

			a.states.clear();
			a.states.resize(2);
			a.states[1].final = true;
			int ch = *regex++;
			if(ch<0 || ch>=N_CHARS)
				ch = N_CHARS-1;
			a.states[0].trans[ch] = 1;
		}

		char mode = '.';
		if(regex<regex_end && (*regex=='?' || *regex=='+' || *regex=='*'))
			mode = *regex++;

		if(!MergeSerial(a,mode))
			return false;
	}

	for(int i=0;i<states.size();i++)
		if(states[i].final)
			states[i].symbol_id = type;

	Optimize();

	return true;
}

bool Automation::BuildComment(int type,const char *start,const char *end)
{
	return false;
}

bool Automation::MergeParallel(const Automation &a,bool ovr)
{
	vector<State> newauto;
	vector<pair<int,int> > statemap;

	newauto.resize(1);
	statemap.push_back(pair<int,int>(0,0));

	for(int i=0;i<statemap.size();i++)
	{
		int s1 = statemap[i].first;
		int s2 = statemap[i].second;
		bool final = false;
		int final_st = -1;

		for(int j=0;j<N_CHARS;j++)
		{
			pair<int,int> target;

			if(s1>=0 && s2>=0)
			{
				int n1 = states[s1].trans[j];
				int n2 = a.states[s2].trans[j];
				if(n1<0 && n2<0)
				{
					if(states[s1].final && (!final || !ovr))
					{
						if(final && final_st!=states[s1].symbol_id)
						{
							printf("MergeParallel: final state conflict.\n");
							return false;
						}
						final = true;
						final_st = states[s1].symbol_id;
					}
					if(a.states[s2].final)
					{
						if(final && final_st!=a.states[s2].symbol_id && !ovr)
						{
							printf("MergeParallel: final state conflict.\n");
							return false;
						}
						final = true;
						final_st = a.states[s2].symbol_id;
					}
				}
				target.first = n1;
				target.second = n2;
			}
			else if(s1<0)
			{
				target.first = -1;
				target.second = a.states[s2].trans[j];
				if(target.second<0 && a.states[s2].final)
				{
					if(final && final_st!=a.states[s2].symbol_id && !ovr)
					{
						printf("MergeParallel: final state conflict.\n");
						return false;
					}
					final = true;
					final_st = a.states[s2].symbol_id;
				}
			}
			else
			{
				target.first = states[s1].trans[j];
				target.second = -1;
				if(target.first<0 && states[s1].final && (!final || !ovr))
				{
					if(final && final_st!=states[s1].symbol_id)
					{
						printf("MergeParallel: final state conflict.\n");
						return false;
					}
					final = true;
					final_st = states[s1].symbol_id;
				}
			}

			if(target.first<0 && target.second<0)
				newauto[i].trans[j] = -1;
			else
			{
				int id = -1;
				for(int k=0;k<statemap.size();k++)
					if(statemap[k]==target)
					{
						id = k;
						break;
					}
				if(id<0)
				{
					id = statemap.size();
					statemap.push_back(target);
					newauto.push_back(State());
				}
				newauto[i].trans[j] = id;
			}
		}

		newauto[i].final = final;
		newauto[i].symbol_id = final_st;
	}

	states = newauto;

	return true;
}

bool Automation::MergeSerial(const Automation &a,char rep_mode)
{
	int base = states.size();
	states.resize(states.size()+a.states.size());

	for(int i=0;i<a.states.size();i++)
	{
		states[i+base] = a.states[i];
		for(int j=0;j<N_CHARS;j++)
			if(states[i+base].trans[j]>=0)
				states[i+base].trans[j] += base;
	}

	for(int i=0;i<states.size();i++)
	{
		if(i>=base && rep_mode!='+' && rep_mode!='*') break;
		if(states[i].final)
		{
			for(int j=0;j<N_CHARS;j++)
				if(states[base].trans[j]>=0)
					states[i].trans[j] = states[base].trans[j];
			if(i<base && (rep_mode=='.' || rep_mode=='+'))
			{
				states[i].final = false;
				states[i].symbol_id = -1;
			}
		}
	}

	return true;
}

void Automation::Optimize()
{
	bool repeat = true;
	vector<int> redirect;
	redirect.resize(states.size()+1);
	for(int i=-1;i<(int)states.size();i++)
		redirect[i+1] = i;
	while(repeat)
	{
		repeat = false;
		for(int i=0;i<states.size();i++)
			for(int j=0;j<states.size();j++)
			{
				if(states[i].final!=states[j].final)
					continue;
				if(states[i].final && states[i].symbol_id!=states[j].symbol_id)
					continue;
				bool same = true;
				for(int k=0;k<N_CHARS;k++)
					if(redirect[states[i].trans[k]+1] != redirect[states[j].trans[k]+1])
					{
						same = false;
						break;
					}

				if(same && redirect[j+1]!=redirect[i+1])
				{
					redirect[j+1] = redirect[i+1];
					repeat = true;
				}
			}
	}

	for(int i=0;i<states.size();i++)
		for(int j=0;j<N_CHARS;j++)
			states[i].trans[j] = redirect[states[i].trans[j]+1];

	MergeParallel(*this);
}

void Automation::DumpTable(int min_char,int max_char)
{
	if(min_char<0) min_char = 0;
	if(max_char>=N_CHARS) max_char = N_CHARS-1;

	printf("      ");
	for(int i=min_char;i<=max_char;i++)
		printf("   %c",i);
	printf("\n");

	for(int i=0;i<states.size();i++)
	{
		printf("%4d  ",i);
		for(int j=min_char;j<=max_char;j++)
			printf("%4d",states[i].trans[j]);
		printf("  %c %4d\n",states[i].final?'F':' ',states[i].symbol_id);
	}
}
