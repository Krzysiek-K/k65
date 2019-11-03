

#pragma once



// -------------------------------- ComState --------------------------------

struct Label {
    string		name;
    int			address;
	AsmSection	*section;

	Label() : section(NULL) {}
};


// compiler/linker common state

class ComState : public IErrorHandler {
public:

	~ComState() { Clear(); }

	void		Clear();

	// labels
	int			NumLabels()								{ return (int)labels.size(); }
	void		AddLabel(const char *name,int addr,AsmSection *as,bool update=false,IErrorHandler *eh=NULL);
    Label		*FindLabel(const char *name);

	// sections
	int			NumSections()							{ return (int)sections.size(); }
	AsmSection *CreateSection();
	//AsmSection *AddSection(const AsmSection &as);
	int			FindSectionId(const char *name);
	AsmSection *FindSection(const char *name)			{ return GetSection( FindSectionId(name) ); }

	AsmSection *GetSection(int id);
	int			GetSectionId(const AsmSection *as);
	string		GetSectionName(int index);

	// section handles (== section index + 1)
	int			SectionToHandle(const AsmSection *as);
	AsmSection *HandleToSection(int handle);


	// dump
	void		DumpSym(const char *path);


private:
	vector<Label*>			labels;
	vector<AsmSection*>		sections;


};

extern ComState state;
