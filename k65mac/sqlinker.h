
#pragma once




class SqLinker : public IErrorHandler {
public:
	enum {
		IMAGE_SIZE	= 0x10000,
		MAX_BANKS	= 32,
	};

	SqLinker() { Clear(); }

	void Clear();

	virtual void Error(const char *e);

	void Error(const AsmSymbol &s,const char *e);
	void Error(const AsmSection &s,const char *e);


	void InvokeFarCall(AsmSection &code, AsmSection &target_fn, IErrorHandler &eh);
	void InvokeFarJump(AsmSection &code, const char *target_label, IErrorHandler &eh);

	void RunLinker();
	const char *Link();


//private:
	struct Bank {
		string		name;
		int			bank_number;	// banks[id].bank_bumber == id
		int			layer_bits;
		int			addr_start;
		int			addr_end;
		int			alloc_bottom;
		int			alloc_top;
		int			alloc_mode;		// 0:bottom, 1:top, 2:data bottom & code top, 3:data top & code bottom
	};

	vector<Bank>		banks;
	int					entry_point_section_index;
	int					alloc_mask[IMAGE_SIZE];
	uint8_t				raw_image[MAX_BANKS][IMAGE_SIZE];



	void UpdateSectionBanks(AsmSection &as);			// called from InitSection
	void InitSection(AsmSection &as);
	
	void ReduceZeroPage(AsmSection &as);
	
	bool MarkReferences(AsmSection &as);
	
	void PrepareBankBitmasks(AsmSection &as);
	
	void UpdateSectionWeight(AsmSection &as);
	
	bool TryInsertSection(AsmSection &as,int addr);		// called from InsertSection
	void InsertSection(AsmSection &as);

	void UpdateLabelAddresses(AsmSection &as);

	void PutByte(int addr, uint8_t value, int layer_bits);	// called from GenerateBytes
	void GenerateBytes(AsmSection &as);

	void DumpBin(const char *path);
	void DumpAsm(const char *path);
	//void DumpHTMLMap(const char *path);
	void DumpMap(const char *path);

	void PrintStats();
};


extern SqLinker sqlink;

// misc functions
int bank_get_start(int id);
int bank_get_last_used_byte(int id);
