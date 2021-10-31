
#pragma once



enum {
    AST_NONE = 0,
    AST_LINE_COMMENT,       // text: comment line
    AST_APPEND_COMMENT,     // text: comment after instruction
    AST_LABEL,              // text: label                              / marks label position
    AST_RELATIVE_TARGET,    // text: target label   value: +ofs         / add relative address to target
    AST_ADDRESS,            // text: target label   value: +ofs         / add full address of target
    AST_OPCODE_BYTE,        //                      value: byte         / add byte value
    AST_DATA_BYTE,          //                      value: byte         / add byte value (data or immediate)
    AST_LO_ADDRESS,         // text: target label   value: +ofs         / add low byte of address
    AST_HI_ADDRESS,         // text: target label   value: +ofs         / add high byte of address
    AST_ZP_ADDRESS,         // text: target label   value: +ofs         / add low byte of address (and crash if address is not zero page)
	AST_IGNORED_BYTE,		//											/ add byte that can be of any value
};

enum {
    ASF_NO_PAGE_CROSS   = (1<<0),
};


struct BitSet {
	bool	v[256];
	BitSet() { clear(); }
	void clear() { memset(v,0,sizeof(v)); }
	void set() { for(int i=0;i<256;i++) v[i]=true; }
    bool &operator [](int i) { return v[i]; }
    bool operator [](int i) const { return v[i]; }
};



struct AsmSymbol {
    int     type;
    string  text;
    int     value;
    int     src_line;
    int     flags;

    AsmSymbol() : type(0), value(0), src_line(0), flags(0) {}
};


struct AsmSection {
	struct Location {
		int	code_pos;
		int	asm_lines_pos;

		Location() {}

		Location(const string &str) {
			const char *s = str.c_str();
			code_pos = ParseInt(s);
			asm_lines_pos = ParseInt(s);
		}

		string ToString() { return format("%d %d",code_pos,asm_lines_pos); }
	};

    string              name;
    string			    type;
    vector<AsmSymbol>   code;
	int					big_align_step;
	int					big_align_offset;
    BitSet              alignments;
	vector<string>		bank_list;
    int                 fixed_address;		// linker (in)
	bool				referenced;
    int                 clocks;
	bool				raw_table_valid;
	vector<int>			raw_table;
	int					img_width;
	int					img_height;
	double				link_weight;

	vector<int>			code_bitmask;		// linker
	vector<int>			banks;				// linker	(generated from bank_list)
    int                 address;			// linker
	bool				alloc_top;			// linker
	int					layer_bits;			// linker
	int					bank_start;			// linker
	int					bank_end;			// linker


	AsmSection() { Clear(); }

    void Clear();
    void Error(const char *e);
    void Assemble(const char *line);
    void Assemble(const string &s)						{ Assemble(s.c_str()); }
    void AssembleInsert(const char *line,Location pos);
    void AssembleInsert(const string &s,Location pos)	{ AssembleInsert(s.c_str(),pos); }
	void RepeatTail(Location tail_start,int count);
    void Inline(const AsmSection &as);

	Location GetLocation() {
		Location loc;
		loc.code_pos = code.size();
		loc.asm_lines_pos = asm_lines.size();
		return loc;
	}

    void AllowPageCross();
    void DisallowPageCross();
    void ClearDisallowPageCross();

	bool BuildRawTable();

	void AppendDisassembly(vector<string> &out);

private:
    string			raw_line;
    int				line_counter;
    int				cur_flags;
	vector<string>	asm_lines;

    void add(int type,const char *text=NULL,int value=0) {
        AsmSymbol s;
        s.type = type;
        s.text = text ? text : "";
        s.value = value;
        s.src_line = line_counter;
        s.flags = cur_flags;
        code.push_back(s);
    }

    void AssembleInstruction(const char *s);
};


int FindZeroPageReduction(int opcode);
