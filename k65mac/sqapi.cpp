
#include "stdafx.h"
#include "common.h"


IErrorHandler *sqapi_errorhandler = NULL;

SqVM vm;
string current_script_path;
string current_exe_path;


void error(const char *err);




// -------------------------------- XSq callbacks --------------------------------

void xsq_error( const char *err )
{
	fprintf(stderr,"Linker VM error: %s\n",err);
}

void xsq_print( const char *err )
{
	printf("%s",err);
}

bool xsq_getfile( const char *path, std::vector<unsigned char> &data )
{
	return NFS.GetFileBytes(path,data);
}

unsigned long long xsq_getfiletime( const char *path )
{
	return 0;
}

// -------------------------------- List macros --------------------------------

#define VM_LIST_API(list,prefix,etype)	\
	int prefix##_count()		{ return list.size();								}											XSQ_REGISTER_FN( prefix##_size )	\
	int prefix##_new()			{ list.resize(list.size()+1); return list.size()-1;	}											XSQ_REGISTER_FN( prefix##_new )		\
	int prefix##_insert(int at)	{ if(at<0) at=0; if(at>list.size()) at=list.size(); list.insert(list.begin()+at); return at; }	XSQ_REGISTER_FN( prefix##_insert )	\
	bool prefix##_delete(int at){ return (at>=0 && at<list.size()) ? list.erase(list.begin()+at),true : false; }				XSQ_REGISTER_FN( prefix##_delete)	\
	SqRef prefix##_get(int at)	{ return (at>=0 && at<list.size()) ? etype##_get(list[at]) : SqRef(); }							XSQ_REGISTER_FN( prefix##_get)		\
	bool prefix##_set(int at,SqRef r)	{ return (at>=0 && at<list.size()) ? etype##_set(list[at],r) : false; }					XSQ_REGISTER_FN( prefix##_set)		\
	bool prefix##_add(SqRef r)	{ return etype##_set(list[prefix##_new()],r); }													XSQ_REGISTER_FN( prefix##_add)		\
	SqRef prefix##_default()	{ return etype##_default(); }																	XSQ_REGISTER_FN( prefix##_default)	\
	// end of multiline macro








// -------------------------------- Text files --------------------------------
static vector<string>	cur_file;
static int				cur_file_pos;

// ---- reading ----
/** \brief Read text file into internal array and set pointer to its start. */
bool text_readfile(const char *path)
{
	vector<uint8_t> tmp;
	cur_file_pos = 0;
	cur_file.clear();
	if(!NFS.GetFileLines(path,cur_file))
		return false;
	return cur_file.size()>0;
}
XSQ_REGISTER_FN(text_readfile);

/** \brief Get next line of text. */
const char *text_getline()
{
	if(cur_file_pos>=(int)cur_file.size())
		return "";
	return cur_file[cur_file_pos++].c_str();
}
XSQ_REGISTER_FN(text_getline);

/** \brief Check if file pointer is at the end. */
bool text_iseof()
{
	return cur_file_pos>=(int)cur_file.size();
}
XSQ_REGISTER_FN(text_iseof);

// ---- writing ----
/** \brief Clear text buffer. */
void text_clear()
{
	cur_file_pos = 0;
	cur_file.clear();
}
XSQ_REGISTER_FN(text_clear);

/** \brief Add line to text buffer. */
void text_addline(const char *line)
{
	cur_file.insert(cur_file.begin()+cur_file_pos,line);
	cur_file_pos++;
}
XSQ_REGISTER_FN(text_addline);

/** \brief Frite text buffer to file. */
bool text_writefile(const char *path)
{
	vector<uint8_t> tmp;
	for(int i=0;i<(int)cur_file.size();i++)
	{
		tmp.insert(tmp.end(),cur_file[i].begin(),cur_file[i].end());
		if(i+1<(int)cur_file.size())
			tmp.push_back('\n');
	}
	FILE *fp = fopen(path,"wt");
	if(!fp) return false;
	if(tmp.size()>0) fwrite(&tmp[0],1,tmp.size(),fp);
	fclose(fp);
	return true;
}
XSQ_REGISTER_FN(text_writefile);



// -------------------------------- Parsing --------------------------------

static string _parse_buffer;
static const char *_parse_ptr = "";

/** \brief Set line to be parsed. */
void parse_setline(const char *line)
{
	_parse_buffer = line;
	_parse_ptr = _parse_buffer.c_str();
}
XSQ_REGISTER_FN(parse_setline);

/** \brief Skip whitespaces. */
void parse_white()
{
	ParseWhitespace(_parse_ptr);
}
XSQ_REGISTER_FN(parse_white);

/** \brief Check if numerical value is coming next. */
bool parse_isint()
{
	ParseWhitespace(_parse_ptr);
	return *_parse_ptr=='-' || (*_parse_ptr>='0' && *_parse_ptr<='9');
}
XSQ_REGISTER_FN(parse_isint);

/** \brief Parse integer. */
int parse_int()
{
	ParseWhitespace(_parse_ptr);
	return ParseInt(_parse_ptr);
}
XSQ_REGISTER_FN(parse_int);

/** \brief Parse float. */
float parse_float()
{
	ParseWhitespace(_parse_ptr);
	return ParseFloat(_parse_ptr);
}
XSQ_REGISTER_FN(parse_float);

/** \brief Parse string. */
const char *parse_string()
{
	static string ps;
	ParseWhitespace(_parse_ptr);
	ParseString(_parse_ptr,ps);
	return ps.c_str();
}
XSQ_REGISTER_FN(parse_string);







// -------------------------------- General --------------------------------

void print(const char *s)
{
	printf("%s\n",s);
}
XSQ_REGISTER_FN(print)

string path_get_ext(const char *s)
{
	string ext = FilePathGetPart(s,false,false,true);
	if( ext.size()>=1 && ext[0]=='.' )
		ext.erase(ext.begin());
	return ext;
}
XSQ_REGISTER_FN(path_get_ext)

string path_get_noext(const char *s)
{
	return FilePathGetPart(s,true,true,false);
}
XSQ_REGISTER_FN(path_get_noext)


// -------------------------------- Compiler interface --------------------------------

void set_bank(const char *bank)
{
	cmp.SetBank(bank);
}
XSQ_REGISTER_FN(set_bank)

string compile(const char *code)
{
	const char *err = cmp.Compile(code);
	return err ? err : "";
}
XSQ_REGISTER_FN(compile)




// -------------------------------- Section interface --------------------------------

int sec_count()
{
	return state.NumSections();
}
XSQ_REGISTER_FN(sec_count)

int sec_create()
{
	AsmSection *as = state.CreateSection();
	return state.SectionToHandle(as);
}
XSQ_REGISTER_FN(sec_create)

void sec_init(int sec)
{
	AsmSection *as = state.HandleToSection(sec);
	if(!as) error("[script] Trying to init null section.");
	sqlink.InitSection(*as);
}
XSQ_REGISTER_FN(sec_init)

int sec_find(const char *name)
{
	return state.FindSectionId(name) + 1;	// returns handle
}
XSQ_REGISTER_FN(sec_find)

int sec_entrypoint()
{
	return sqlink.entry_point_section_index+1;
}
XSQ_REGISTER_FN(sec_entrypoint)

string sec_get_name(int sec)
{
	AsmSection *as = state.HandleToSection(sec);
	return as ? as->name : "";
}
XSQ_REGISTER_FN(sec_get_name)

void sec_set_name(int sec,const char *name)
{
	AsmSection *as = state.HandleToSection(sec);
	if(!as) error("[script] Trying to set name of null section.");
	as->name = name;
}
XSQ_REGISTER_FN(sec_set_name)

string sec_get_type(int sec)
{
	AsmSection *as = state.HandleToSection(sec);
	return as ? as->type: "";
}
XSQ_REGISTER_FN(sec_get_type)

void sec_set_type(int sec,const char *type)
{
	AsmSection *as = state.HandleToSection(sec);
	if(!as) error("[script] Trying to set type of null section.");
	as->type = type;
}
XSQ_REGISTER_FN(sec_set_type)

int sec_get_fixaddr(int sec)
{
	AsmSection *as = state.HandleToSection(sec);
	return as ? as->fixed_address : -1;
}
XSQ_REGISTER_FN(sec_get_fixaddr)

void sec_set_fixaddr(int sec,int addr)
{
	AsmSection *as = state.HandleToSection(sec);
	if(!as) error("[script] Trying to set fixed address of null section.");
	as->fixed_address = addr;
}
XSQ_REGISTER_FN(sec_set_fixaddr)

int sec_get_bank_count(int sec)
{
	AsmSection *as = state.HandleToSection(sec);
	if(!as) error("[script] Trying to get bank count of null section.");
	return (int)as->bank_list.size();
}
XSQ_REGISTER_FN(sec_get_bank_count)

string sec_get_bank(int sec,int id)
{
	AsmSection *as = state.HandleToSection(sec);
	if( !as ) error("[script] Trying to get bank of null section.");
	if( id<0 || id>=(int)as->bank_list.size() ) error("[script] Trying to get section bank with index outside valid range.");
	return as->bank_list[id];
}
XSQ_REGISTER_FN(sec_get_bank)

void sec_add_bank(int sec,const char *bank)
{
	AsmSection *as = state.HandleToSection(sec);
	if(!as) error("[script] Trying to add bank to null section.");
	as->bank_list.push_back(bank);
}
XSQ_REGISTER_FN(sec_add_bank)

void sec_set_referenced(int sec,int ref_value)
{
	AsmSection *as = state.HandleToSection(sec);
	if(!as) error("[script] Trying to set refrenced state of null section.");
	as->referenced = (ref_value!=0);
}
XSQ_REGISTER_FN(sec_set_referenced)

void sec_asm(int sec,const char *asmcode)
{
	AsmSection *as = state.HandleToSection(sec);
	if(!as) error("[script] Trying to add asm code to null section.");
	as->Assemble(asmcode);
}
XSQ_REGISTER_FN(sec_asm)

void sec_asm_byte(int sec,int value)
{
	AsmSection *as = state.HandleToSection(sec);
	if(!as) error("[script] Trying to add asm code to null section.");

	AsmSymbol symb;
	symb.type = AST_DATA_BYTE;
	symb.value = value;
	as->code.push_back(symb);
}
XSQ_REGISTER_FN(sec_asm_byte)

void sec_asm_word(int sec,int value)
{
	AsmSection *as = state.HandleToSection(sec);
	if(!as) error("[script] Trying to add asm code to null section.");

	AsmSymbol symb;
	symb.type = AST_DATA_BYTE;
	symb.value = value&0xFF;
	as->code.push_back(symb);

	symb.type = AST_DATA_BYTE;
	symb.value = (value>>8)&0xFF;
	as->code.push_back(symb);
}
XSQ_REGISTER_FN(sec_asm_word)

void sec_asm_string(int sec,const char *s)
{
	AsmSection *as = state.HandleToSection(sec);
	if(!as) error("[script] Trying to add asm code to null section.");

	while( *s )
	{
		AsmSymbol symb;
		symb.type = AST_DATA_BYTE;
		symb.value = *s++;
		as->code.push_back(symb);
	}
}
XSQ_REGISTER_FN(sec_asm_string)

void sec_asm_addr(int sec,const char *label)
{
	AsmSection *as = state.HandleToSection(sec);
	if(!as) error("[script] Trying to add asm code to null section.");

	AsmSymbol symb;
	symb.type = AST_ADDRESS;
	symb.text = label;
	as->code.push_back(symb);
}
XSQ_REGISTER_FN(sec_asm_addr)




// -------------------------------- Linker bank interface --------------------------------

int bank_count()
{
	return sqlink.banks.size();
}
XSQ_REGISTER_FN(bank_count)


void bank_create(const char *name,int layer_bits,int addr_start,int addr_end,int alloc_mode)
{
	SqLinker::Bank b;
	b.name = name;
	b.bank_number = sqlink.banks.size();
	b.layer_bits = layer_bits;
	b.addr_start = addr_start;
	b.addr_end = addr_end;
	b.alloc_mode = alloc_mode;
	sqlink.banks.push_back(b);
}
XSQ_REGISTER_FN(bank_create)

string bank_get_name(int id)
{
	if(id<0 || id>=(int)sqlink.banks.size()) error("[script] Requesting invalid bank id.");
	return sqlink.banks[id].name;
}
XSQ_REGISTER_FN(bank_get_name)

int bank_get_start(int id)
{
	if(id<0 || id>=(int)sqlink.banks.size()) error("[script] Requesting invalid bank id.");
	return sqlink.banks[id].addr_start;
}
XSQ_REGISTER_FN(bank_get_start)

int bank_get_end(int id)
{
	if(id<0 || id>=(int)sqlink.banks.size()) error("[script] Requesting invalid bank id.");
	return sqlink.banks[id].addr_end;
}
XSQ_REGISTER_FN(bank_get_end)

int bank_get_bottom(int id)
{
	if(id<0 || id>=(int)sqlink.banks.size()) error("[script] Requesting invalid bank id.");
	return sqlink.banks[id].alloc_bottom;
}
XSQ_REGISTER_FN(bank_get_bottom)

int bank_get_top(int id)
{
	if(id<0 || id>=(int)sqlink.banks.size()) error("[script] Requesting invalid bank id.");
	return sqlink.banks[id].alloc_top;
}
XSQ_REGISTER_FN(bank_get_top)

int bank_get_last_used_byte(int id)
{
	if( id<0 || id>=(int)sqlink.banks.size() ) error("[script] Requesting invalid bank id.");
	SqLinker::Bank &bank = sqlink.banks[id];
	for(int a=bank.addr_end;a>=bank.addr_start;a--)
	{
		if( a>=0 && a<SqLinker::IMAGE_SIZE && (sqlink.alloc_mask[a]&bank.layer_bits) )
			return a;
	}
	return -1;
}
XSQ_REGISTER_FN(bank_get_last_used_byte)



// -------------------------------- Linker interface --------------------------------

void label_add(const char *name,int addr,int as,int update)
{
	state.AddLabel(name,addr,state.HandleToSection(as),update!=0);
}
XSQ_REGISTER_FN(label_add)

int label_get_section(const char *name)
{
	Label *l = state.FindLabel(name);
	if( !l ) return 0;		// NULL handle
	return state.SectionToHandle(l->section);
}
XSQ_REGISTER_FN(label_get_section)

void error(const char *err)
{
	if( sqapi_errorhandler )	sqapi_errorhandler->Error(err);
	else						sqlink.Error(err);
}
XSQ_REGISTER_FN(error)


void sec_error(int sec,const char *err)
{
	AsmSection *as = state.HandleToSection(sec);
	if(as)	sqlink.Error(*as,err);
	else	sqlink.Error(err);
}
XSQ_REGISTER_FN(sec_error)


void save_bin(const char *path)
{
	//link.DumpBin(path);
}
XSQ_REGISTER_FN(save_bin)

void save_lst(const char *path)
{
	//link.DumpAsm(path);
}
XSQ_REGISTER_FN(save_lst)



// -------------------------------- Linker file output interface --------------------------------

FILE *output_fp;

void bin_fopen_wb(const char *path)
{
	if(output_fp) fclose(output_fp);
	output_fp = fopen(path,"wb");
	if(!output_fp) error(format("Can't write to '%s'",path).c_str());
}
XSQ_REGISTER_FN(bin_fopen_wb)

void bin_fopen_wt(const char *path)
{
	if(output_fp) fclose(output_fp);
	output_fp = fopen(path,"wt");
	if(!output_fp) error(format("Can't write to '%s'",path).c_str());
}
XSQ_REGISTER_FN(bin_fopen_wt)

void bin_write_byte(int value)
{
	if(!output_fp) error("[script] No output file open.");
	fwrite(&value,1,1,output_fp);
}
XSQ_REGISTER_FN(bin_write_byte)

void bin_write_word(int value)
{
	if(!output_fp) error("[script] No output file open.");
	fwrite(&value,1,2,output_fp);
}
XSQ_REGISTER_FN(bin_write_word)

void bin_emit(int layer,int addr,int size)
{
	if(!output_fp) error("[script] No output file open.");
	if(layer<0 || layer>=SqLinker::MAX_BANKS) error("[script] Invalid layer number in bin_emit().");
	if(addr<0 || addr>=SqLinker::IMAGE_SIZE) error("[script] Invalid address in bin_emit().");
	if(size<0) error("[script] Invalid size in bin_emit().");
	if(addr+size>SqLinker::IMAGE_SIZE) error("[script] Invalid end address in bin_emit().");
	fwrite(sqlink.raw_image[layer]+addr,1,size,output_fp);
}
XSQ_REGISTER_FN(bin_emit)

void bin_fclose()
{
	if(output_fp) fclose(output_fp);
	output_fp = NULL;
}
XSQ_REGISTER_FN(bin_fclose)



int bin_get(int layer,int addr)
{
	if(layer<0 || layer>=SqLinker::MAX_BANKS) error("[script] Invalid layer number in bin_get().");
	if(addr<0 || addr>=SqLinker::IMAGE_SIZE) error("[script] Invalid address in bin_get().");
	return sqlink.raw_image[layer][addr];
}
XSQ_REGISTER_FN(bin_get)





// -------------------------------- execute() --------------------------------

int vm_DoFile(const char *path)
{
	string _path = current_script_path;
	string current_script_path = FilePathGetPart(path,true,false,false);
	if( current_script_path.size()>0 && (current_script_path[current_script_path.size()-1]=='/' || current_script_path[current_script_path.size()-1]=='\\') )
		current_script_path.erase(current_script_path.end()-1);

	printf("Executing script: %s\n",path);
	bool status = vm.DoFile(path);

	current_script_path = _path;

	return status ? 1 : 0;
}

int execute(const char *str)
{
	string line = str;
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
	
	// test if it's a file name
	string fname = ParseString(s);
	ParseWhitespace(s);
	bool is_file = (!*s && FilePathGetPart(fname.c_str(),false,false,true)!="");

	int status = 0;
	try {
		if(is_file)
		{
			// load script file
			if( vm_DoFile( fixpath(fname).c_str() ) ) return 1;
		}
		else
		{
			// execute as script
			if( vm.DoString(str) ) return 1;
		}
	} catch(const char *err)
	{
		printf("Error: %s\n",err);
		printf("During execution of: %s\n",str);
		return 0;
	}

	return status;
}
XSQ_REGISTER_FN(execute)
