
#include "stdafx.h"
#include "common.h"


ComState state;



void ComState::Clear()
{
	for( int i=0; i<(int)labels.size(); i++ )
		delete labels[i];
	labels.clear();

	for( int i=0; i<(int)sections.size(); i++ )
		delete sections[i];
	sections.clear();
}


void ComState::AddLabel(const char *name,int addr,AsmSection *as,bool update,IErrorHandler *eh)
{
	if(!eh) eh = this;

    Label *old = FindLabel(name);
    
    if(update)
    {
        if(!old) eh->Error(format("[internal] Label '%s' not found for update",name).c_str());
        old->address = addr;
		old->section = as;
        return;
    }

    if(old) eh->Error(format("Label '%s' redefined",name).c_str());

    Label *l = new Label();
    l->name = name;
    l->address = addr;
	l->section = as;
    labels.push_back(l);
}

Label *ComState::FindLabel(const char *name)
{
    for(int i=0;i<(int)labels.size();i++)
        if(labels[i]->name==name)
            return labels[i];
    return NULL;
}



AsmSection *ComState::CreateSection()
{
	AsmSection *as = new AsmSection();
	sections.push_back(as);
	return as;
}

//AsmSection *ComState::AddSection(const AsmSection &as)
//{
//	AsmSection *new_as = new AsmSection(as);
//	sections.push_back(new_as);
//	return new_as;
//}


int ComState::FindSectionId(const char *name)
{
	for(int i=0;i<(int)sections.size();i++)
		if(sections[i]->name==name)
			return i;
	return -1;
}

AsmSection *ComState::GetSection(int id)
{
	if( id==-2 ) return cmp.code;
	return (id>=0 && id<(int)sections.size()) ? sections[id] : NULL;
}

int ComState::GetSectionId(const AsmSection *as)
{
	//if( as==cmp.code ) return -2;

	for( int i=0; i<(int)sections.size(); i++ )
		if( sections[i]==as )
			return i;
	
	return -1;
}

string ComState::GetSectionName(int index)
{
	AsmSection *sec = GetSection(index);
	if( !sec ) return "invalid index";
	return sec->name;
}

int ComState::SectionToHandle(const AsmSection *as)
{
	return GetSectionId(as) + 1;	// -1 correctly changes to 0
}

AsmSection *ComState::HandleToSection(int handle)
{
	return GetSection( handle-1 );
}



void ComState::DumpSym(const char *path)
{
	FILE *fp = fopen(path,"wt");
	if(!fp) return;
	fprintf(fp,"--- Symbol List\n");

	vector<string> sym;
	for(int i=0;i<(int)labels.size();i++)
		if( !labels[i]->section || labels[i]->section->referenced )
			sym.push_back(format("%-24s %04x                  ",labels[i]->name.c_str(),labels[i]->address));

	for(int i=0;i<(int)sym.size();i++)
		fprintf(fp,"%s\n",sym[i].c_str());
	
	fprintf(fp,"--- End of Symbol List.\n");
	fclose(fp);
}
