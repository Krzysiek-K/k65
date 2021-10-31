
#include "stdafx.h"
#include "common.h"

SqLinker sqlink;


#define IS_SINGLE_BIT(x)			( (x) && ((((x)-1) & (x)) == 0) )


//static int BANK_SEL[SqLinker::MAX_BANKS] = {
//	//			--	F8	F6	F4		<bits>
//	0x1FF8,	//	0	0	2	4	b0	1111 1000
//	0x1FF9,	//	-	1	3	5	b1	1111 1001
//	0x1FF6,	//	-	-	0	2	b2	1111 0110
//	0x1FF7,	//	-	-	1	3	b3	1111 0111
//	0x1FF4,	//	-	-	-	0	b4	1111 0100
//	0x1FF5,	//	-	-	-	1	b5	1111 0101
//	0x1FFA,	//	-	-	-	6	b6	1111 1010
//	0x1FFB	//	-	-	-	7	b7	1111 1011
//};

//static int BANK_ORDER_2[] = {0,1};
//static int BANK_ORDER_4[] = {2,3,0,1};
//static int BANK_ORDER_8[] = {4,5,2,3,0,1,6,7};



static bool _section_sort(AsmSection *a1,AsmSection *a2)
{
	return a1->link_weight > a2->link_weight; 
}



void SqLinker::Clear()
{
	banks.clear();
	entry_point_section_index = -1;
}

void SqLinker::Error(const char *e)
{
    static string _e;
    _e = "Linker: ";
    _e += e;

	PrintStats();

	string fname = vm.GetString("output_file_name");
	string fbase = FilePathGetPart(fname.c_str(), true, true, false);
	DumpMap((fbase+".gmap").c_str());

    throw _e.c_str();
}

void SqLinker::Error(const AsmSymbol &s,const char *e)
{
    static string _e;
    _e = e;
    _e += format(" (line %d)",s.src_line);
	Error(_e.c_str());
}

void SqLinker::Error(const AsmSection &s,const char *e)
{
    static string _e;
    _e = e;
    _e += format(" (section %s)",s.name.c_str() );
	Error(_e.c_str());
}

void SqLinker::InvokeFarCall(AsmSection &code,AsmSection &target_fn,IErrorHandler &eh)
{
//    if( target_fn.type!="func")
//		eh.Error(format("[internal] Far call target is not a function (call %s->%s)",code.name.c_str(),target_fn.name.c_str()).c_str());
//
//	if( code.bank_list.size()!=1 )
//		eh.Error(format("[internal] Far call can only be used in function resident in exactly one bank (call %s->%s)",code.name.c_str(),target_fn.name.c_str()).c_str());
//
//	if( target_fn.bank_list.size()!=1 )
//		eh.Error(format("[internal] Far call must target function in exactly one bank (call %s->%s)",code.name.c_str(),target_fn.name.c_str()).c_str());
//	
//	
//	// generate stub name
//	string func = target_fn.name;
//	string bfrom = code.bank_list[0];
//	string bto = target_fn.bank_list[0];
//	string farname = string("__far_") + bfrom + "_" + bto + "__" + func;
//
//	// generate stub code if required
//	if( !state.FindSection( farname.c_str() ) )
//	{
//		AsmSection &s = state.AddSection( AsmSection() );
//		s.name = farname;
//		s.type = "stub";
//		s.bank_list.clear();
//		s.bank_list.push_back(bfrom);
//		s.bank_list.push_back(bto);
//		s.Assemble(s.name);									// label
//		s.Assemble(string("    BIT     __banksel_")+bto);	//	BIT		__banksel_to
//		s.Assemble(string("    JSR     ")+func);			//	JSR		func
//		s.Assemble(string("    BIT     __banksel_")+bfrom);	//	BIT		__banksel_from
//		s.Assemble(string("    RTS"));						//	RET
//	}
//
//	code.Assemble( format("    JSR     %s",farname.c_str()).c_str() );

	IErrorHandler *_eh = sqapi_errorhandler;
	sqapi_errorhandler = &eh;

	if( !vm.Run( "link_invoke_far_call", state.SectionToHandle(&code), state.SectionToHandle(&target_fn) ) )
		Error( code, "[script] link_invoke_far_call failed.");

	sqapi_errorhandler = _eh;
}

void SqLinker::InvokeFarJump(AsmSection &code, const char *target_label, IErrorHandler &eh)
{
	IErrorHandler *_eh = sqapi_errorhandler;
	sqapi_errorhandler = &eh;

	if( !vm.Run("link_invoke_far_jump", state.SectionToHandle(&code), target_label) )
		Error(code, "[script] link_invoke_far_jump failed.");

	sqapi_errorhandler = _eh;
}


void SqLinker::UpdateSectionBanks(AsmSection &as)
{
	as.layer_bits = 0;
	as.bank_start = 0;
	as.bank_end = 0xFFFF;
	as.banks.clear();

	if( as.type=="inline" || as.type=="image" )
		return;	// ignore images and inlines

	for(int i=0;i<(int)as.bank_list.size();i++)
	{
		const string &bank_name = as.bank_list[i];

		if( bank_name=="*" )
		{
			as.layer_bits |= -1;
			continue;
		}

		bool found = false;
		for(int j=0;j<(int)banks.size();j++)
			if(banks[j].name==bank_name)
			{
				as.banks.push_back(j);
				found = true;
				break;
			}
		if( found )
			continue;

		// add bank
		int nbanks = banks.size();
		if( !vm.Run("link_create_bank",bank_name.c_str()) )
			Error(as,"[script] link_create_bank failed.");

		if( (int)banks.size() != nbanks+1 )
			Error(as,"[script] link_create_bank should create exactly one bank.");

		as.banks.push_back( banks.back().bank_number );
	}

	// overlay bank restrictions
	for(int i=0;i<(int)as.banks.size();i++)
	{
		Bank &b = banks[as.banks[i]];

		as.layer_bits |= b.layer_bits;
		if(b.addr_start>as.bank_start)	as.bank_start = b.addr_start;
		if(b.addr_end<as.bank_end)		as.bank_end = b.addr_end;

		if( b.alloc_mode==0 ) as.alloc_top = false;
		if( b.alloc_mode==1 ) as.alloc_top = true;
		if( b.alloc_mode==2 ) as.alloc_top = (as.type!="data");
		if( b.alloc_mode==3 ) as.alloc_top = (as.type=="data");
	}

	if( as.bank_start>as.bank_end )
		Error(as,"Section bank restrictions don't allow any possible allocation");

	if( !as.layer_bits )
		Error(format("Section '%s' is not assigned to any bank",as.name.c_str()).c_str());
}

void SqLinker::InitSection(AsmSection &as)
{
	as.layer_bits = 0;
	as.bank_start = 0;
	as.bank_end = 0xFFFF;
	as.alloc_top = false;
	as.address = -1;

	if(as.type=="inline" || as.type=="image")
		return;	// ignore images and inlines

	UpdateSectionBanks(as);

	
    // add labels
    for(int i=0;i<(int)as.code.size();i++)
        if(as.code[i].type==AST_LABEL)
			state.AddLabel(as.code[i].text.c_str(), -1, &as);

    if(as.type=="main")
	{
		if( as.banks.size()!=1 || !IS_SINGLE_BIT(as.layer_bits) )
			Error("Entry point should be in exactly one bank");
		
		if(entry_point_section_index>=0)
			Error("Multiple entry points (main) present");

		entry_point_section_index = state.GetSectionId(&as);
	}
}

void SqLinker::ReduceZeroPage(AsmSection &as)
{
	if( !as.referenced )
		return;

    for(int i=0;i+1<(int)as.code.size();i++)
    {
        AsmSymbol &s  = as.code[i];
        AsmSymbol &s2 = as.code[i+1];
        
        // opcode followed by address?
        if(s.type!=AST_OPCODE_BYTE || s2.type!=AST_ADDRESS)
            continue;

        // get target label
        Label *target = state.FindLabel(s2.text.c_str());
        if(!target) Error(s2,format("Reference to undefined label '%s'",s2.text.c_str()).c_str());
        
        // known location and zero page?
        if( target->address<0 || ((target->address+s2.value)&~0xFF)!=0 )
            continue;

        // can opcode be simplified?
        int enc2 = FindZeroPageReduction(s.value);
        if(enc2<0)
            continue;

        // simplify
        s.value = enc2;
        s2.type = AST_ZP_ADDRESS;
    }
}


bool SqLinker::MarkReferences(AsmSection &as)
{
	if(as.type=="inline" || as.type=="image")
		return false;	// ignore images and inlines

	bool found = false;
    for(int i=0;i<(int)as.code.size();i++)
    {
        const AsmSymbol &s = as.code[i];

        switch( s.type )
        {
        case AST_LINE_COMMENT:
        case AST_APPEND_COMMENT:
        case AST_OPCODE_BYTE:
        case AST_DATA_BYTE:
        case AST_IGNORED_BYTE:
            break;

        case AST_LABEL:
			{
                Label *l = state.FindLabel(s.text.c_str());
                if(!l) Error(s,"[internal] Label should be already defined");
				if( l->section!=&as )
				{
					l->section = &as;
					found = true;
				}
			}
            break;

        case AST_RELATIVE_TARGET:
        case AST_LO_ADDRESS:
        case AST_HI_ADDRESS:
        case AST_ZP_ADDRESS:
        case AST_ADDRESS:
			if(as.referenced)
			{
                Label *l = state.FindLabel(s.text.c_str());
                if(!l) Error(s,format("Unknown label '%s'",s.text.c_str()).c_str());
				if(l->section && !l->section->referenced)
				{
					l->section->referenced = true;
					found = true;
				}
			}
            break;

		default:
			Error(s,"[internal] Unsupported symbol type");
			break;
        };
	}

	return found;
}

void SqLinker::PrepareBankBitmasks(AsmSection &as)
{
	if(!as.referenced)
		return;

	// clear bitmask
	as.code_bitmask.clear();


    // scan code, check restrictions
    for(int i=0;i<(int)as.code.size();i++)
    {
        const AsmSymbol &s = as.code[i];
        
        int nb = -1;
        switch( s.type )
        {
        case AST_LINE_COMMENT:
        case AST_APPEND_COMMENT:
        case AST_LABEL:
            nb = 0;
            break;

        case AST_RELATIVE_TARGET:
        case AST_OPCODE_BYTE:
        case AST_DATA_BYTE:
        case AST_IGNORED_BYTE:
        case AST_LO_ADDRESS:
        case AST_HI_ADDRESS:
        case AST_ZP_ADDRESS:
            nb = 1;
            break;

        case AST_ADDRESS:
            nb = 2;
            break;
        };

        if(nb<0) Error(s,"[internal] Unsupported symbol type");
        
        if( s.flags & ASF_NO_PAGE_CROSS )
        {
            for(int j=1;j<=nb;j++)
            {
                // cpos+j can't happen to be at $xx00
                // 
                // offset from start:   cpos+j-addr
                // invalid alignment:   ( align + (cpos+j-addr) )%256 = 0
                //                      align = (-(cpos+j-addr))&0xFF

                as.alignments[ (-((int)as.code_bitmask.size()+j))&0xFF ] = false;
            }
        }

		for(int p=0;p<nb;p++)
		{
			if( s.type==AST_IGNORED_BYTE )	as.code_bitmask.push_back(0);
			else							as.code_bitmask.push_back(as.layer_bits);
		}
    }
}


void SqLinker::UpdateSectionWeight(AsmSection &as)
{
	as.link_weight = 0;

	if(!as.referenced) return;

	if(as.fixed_address>=0)
		as.link_weight = 1000000000;
	else
	{
		int nblock = 0;
		for(int a=0;a<256;a++)
			if( !as.alignments[a] )
				nblock++;

		if( as.big_align_step )
			nblock = as.big_align_step - 1;

		if(nblock>0)
			as.link_weight += int(floor(log(nblock*1.f)/log(2.f)*1000+.5f));	// 0...8000 points for alignment
		
		int nbank = 0;
		for(int a=0;a<(int)banks.size();a++)
			if(as.layer_bits & banks[a].layer_bits)
				nbank++;
		as.link_weight += 4000*nbank;
	}
}

bool SqLinker::TryInsertSection(AsmSection &as,int addr)
{
	// check alignment
	if( as.big_align_step && addr % as.big_align_step != as.big_align_offset )
		return false;

	if( !as.alignments[addr&0xFF] )
		return false;

	// check allocation
	for(int i=0;i<(int)as.code_bitmask.size();i++)
		if( alloc_mask[addr+i] & as.code_bitmask[i] )
			return false;


	// allocate
	as.address = addr;
	for(int i=0;i<(int)as.code_bitmask.size();i++)
		alloc_mask[addr+i] |= as.code_bitmask[i];


	// reduce bank allocation ranges
	for(int i=0;i<(int)banks.size();i++)
	{
		Bank &b = banks[i];
		while( b.alloc_bottom<=b.alloc_top && (alloc_mask[b.alloc_bottom] & b.layer_bits) )
			b.alloc_bottom++;

		while( b.alloc_bottom<=b.alloc_top && (alloc_mask[b.alloc_top] & b.layer_bits) )
			b.alloc_top--;
	}

	return true;
}

void SqLinker::InsertSection(AsmSection &as)
{
	if( !as.referenced || !as.layer_bits || as.code_bitmask.size()<=0 )
		return;	// don't alloc

	bool ok = false;
	if( as.big_align_step )
	{
		ok = as.alignments[0];
	}
	else
	{
		for( int i=0; i<=0xFF; i++ )
			if( as.alignments[i] )
				ok = true;
	}

	if( !ok )
		Error(as,"Section alignment restrictions don't allow any alignment");


	int addr_min = as.bank_start;
	int addr_max = as.bank_end;

	if( addr_min<0 ) addr_min = 0;
	if( addr_max>IMAGE_SIZE ) addr_max = IMAGE_SIZE;

	for(int i=0;i<(int)as.banks.size();i++)
	{
		Bank &b = banks[as.banks[i]];
		if( addr_min<b.alloc_bottom )	addr_min = b.alloc_bottom;
		if( addr_max>b.alloc_top )		addr_max = b.alloc_top;
	}

	addr_max -= as.code_bitmask.size()-1;


	if( as.fixed_address>=0 )
	{
		if( as.fixed_address<addr_min || as.fixed_address>addr_max )
			Error(as,"Section has fixed address specified that doesn't fullfill bank address");

		if( as.big_align_step && as.fixed_address % as.big_align_step != as.big_align_offset )
			Error(as, "Section has fixed address specified that doesn't fullfill alignment restrictions");

		if( !as.alignments[as.fixed_address&0xFF] )
			Error(as,"Section has fixed address specified that doesn't fullfill alignment restrictions");

		if( !TryInsertSection(as,as.fixed_address) )
			Error(as,"Can't allocate fixed address section");
		return;
	}

	if( addr_min > addr_max )
		Error(as,"Can't allocate section");

	if( as.alloc_top )
	{
		for(int addr=addr_max;addr>=addr_min;addr--)
			if( TryInsertSection(as,addr) )
				break;
	}
	else
	{
		for(int addr=addr_min;addr<=addr_max;addr++)
			if( TryInsertSection(as,addr) )
				break;
	}

	if( as.address<0 )
		Error(as,"Can't allocate section");
}

void SqLinker::UpdateLabelAddresses(AsmSection &as)
{
	if( !as.referenced || !as.layer_bits || as.code_bitmask.size()<=0 )
		return;	// not used

	if( as.address<0 )
		Error(as,"[internal] This section should have been allocated by now");

	// scan code, update labels
	int offs = 0;
    for(int i=0;i<(int)as.code.size();i++)
    {
        const AsmSymbol &s = as.code[i];
        
        int nb = -1;
        switch( s.type )
        {
        case AST_LINE_COMMENT:
        case AST_APPEND_COMMENT:
            nb = 0;
            break;

		case AST_LABEL:
            state.AddLabel( s.text.c_str(), as.address+offs, &as, true );
            nb = 0;
            break;

        case AST_RELATIVE_TARGET:
        case AST_OPCODE_BYTE:
        case AST_DATA_BYTE:
        case AST_IGNORED_BYTE:
        case AST_LO_ADDRESS:
        case AST_HI_ADDRESS:
        case AST_ZP_ADDRESS:
            nb = 1;
            break;

        case AST_ADDRESS:
            nb = 2;
            break;
        };

        if(nb<0) Error(s,"[internal] Unsupported symbol type");

		offs += nb;
    }

	if( offs != (int)as.code_bitmask.size() )
		Error(as,"[internal] UpdateLabelAddresses computed bad section size");
}

void SqLinker::PutByte(int addr, uint8_t value,int layer_bits)
{
	if( addr<0 || addr>=IMAGE_SIZE )
		Error("[internal] Address outside image size");

	if( alloc_mask[addr] & layer_bits)
		Error("[internal] Image byte already occupied");

	for(int i=0;i<MAX_BANKS;i++)
		if( layer_bits & (1<<i) )
		{
			raw_image[i][addr] = value;
			alloc_mask[addr] |= layer_bits;
		}
}

void SqLinker::GenerateBytes(AsmSection &as)
{
	if( !as.referenced || !as.layer_bits || as.code_bitmask.size()<=0 )
		return;	// not used

	if( as.address<0 )
		Error(as,"[internal] This section should have been allocated by now");

	if( as.big_align_step && as.address % as.big_align_step != as.big_align_offset )
		Error(as, "[internal] Alignment restrictions not met");

	if( !as.alignments[as.address&0xFF] )
        Error(as,"[internal] Alignment restrictions not met");


	// scan code, update labels
	int addr = as.address;
    for(int i=0;i<(int)as.code.size();i++)
    {
        const AsmSymbol &s = as.code[i];
        int prev_addr = addr;

        bool ok = false;
        switch( s.type )
        {
        case AST_LINE_COMMENT:
        case AST_APPEND_COMMENT:
        case AST_LABEL:
            ok = true;
            break;

        case AST_OPCODE_BYTE:
        case AST_DATA_BYTE:
			PutByte( addr++, s.value, as.layer_bits );
            ok = true;
            break;

        case AST_IGNORED_BYTE:
			addr++;
            ok = true;
            break;

		case AST_ADDRESS:
        case AST_RELATIVE_TARGET:
        case AST_LO_ADDRESS:
        case AST_HI_ADDRESS:
        case AST_ZP_ADDRESS:
            {
                Label *l = state.FindLabel(s.text.c_str());
                if(!l) Error(s,format("Unknown label '%s'",s.text.c_str()).c_str());
                if(l->address<0) Error(s,format("Unresolved label '%s'",s.text.c_str()).c_str());
                int trg = l->address + s.value;
                if( s.type==AST_ZP_ADDRESS && (trg&~0xFF)!=0 ) Error(s,format("Zero page target '%s' is not on zero page",s.text.c_str()).c_str());
                if( s.type==AST_RELATIVE_TARGET )
                {
                    trg -= addr + 1;
					if( trg<-128 || trg>127 ) Error(s,format("Jump target '%s' outside -128..127 range",s.text.c_str()).c_str());
                }
                if( s.type==AST_HI_ADDRESS )
                    trg >>= 8;

                PutByte( addr++, trg, as.layer_bits );
                if( s.type==AST_ADDRESS )
					PutByte( addr++, trg>>8, as.layer_bits );
            }
            ok = true;
            break;
        };

        if(!ok) Error(s,"[internal] Unsupported symbol type");
        
        if( (s.flags&ASF_NO_PAGE_CROSS) && (prev_addr>>8)!=(addr>>8))
            Error(s,"[internal] Page crossing restriction not met");
    }

	if( addr - as.address != (int)as.code_bitmask.size() )
		Error(as,"[internal] GenerateBytes computed bad section size");
}



void SqLinker::RunLinker()
{
	printf("Linking...\n");

	// variable labels already added by compiler

    // add sections
	for(int i=0;i<state.NumSections();i++)
		InitSection( *state.GetSection(i) );
	
	if(entry_point_section_index<0)
		Error("No entry point");

	if( !vm.Run("link_make_sections") )
		Error("[script] link_make_sections failed.");

    // generate vector table
	//{
	//	AsmSection &as = state.AddSection( AsmSection() );
	//	AsmSymbol symb;
	//	as.name = "__vectors";
	//	as.type = "system";
	//	as.fixed_address = 0xFFF3;
	//	as.bank_list.push_back("*");
	//	as.Assemble("    NOP");
	//	as.Assemble("    NOP");
	//	as.Assemble("    NOP");
	//	as.Assemble("    NOP");
	//	as.Assemble("    NOP");
	//	as.Assemble("    NOP");
	//	as.Assemble("    NOP");
	//	as.Assemble("    NOP");
	//	as.Assemble("    NOP");
	//	symb.type = AST_ADDRESS;
	//	symb.text = "__entry";
	//	as.code.push_back(symb);
	//	as.code.push_back(symb);
	//	as.referenced = true;
	//	InitSection(as);
	//}

    // generate entry stub
	//{
	//	AsmSection &as = state.AddSection( AsmSection() );

	//	// this must be after above AddSection (potential vector realloc)
	//	AsmSection &main = *state.GetSection(entry_point_section_index);

	//	as.name = "__entry";
	//	as.type = "system";
	//	as.bank_list.push_back("*");
	//	as.Assemble("__entry");		// label
	//	as.Assemble(format("    BIT     __banksel_%s",main.bank_list[0].c_str()));	// switch bank
	//	as.Assemble(format("    JMP     %s",main.name.c_str()));					// jump to main function
	//	InitSection(as);
	//}

	
	// ---- old link starts here ----

	// mark referenced sections
	bool work = true;
	while(work)
	{
		work = false;

		for(int i=0;i<state.NumSections();i++)
			if(MarkReferences(*state.GetSection(i)))
				work = true;
	}

	// optimize zero page references
	for(int i=0;i<state.NumSections();i++)
		ReduceZeroPage( *state.GetSection(i) );

	// prepare bank bitmasks
	for(int i=0;i<state.NumSections();i++)
		PrepareBankBitmasks( *state.GetSection(i) );

	// compute weights
	for(int i=0;i<state.NumSections();i++)
		UpdateSectionWeight( *state.GetSection(i) );

	// sort sections
	vector<AsmSection*> sl;
	for(int i=0;i<state.NumSections();i++)
	{
		AsmSection &as = *state.GetSection(i);
		if( as.referenced )
			sl.push_back( &as );
	}
	sort(sl.begin(),sl.end(),_section_sort);

	// reset allocation state
	for(int i=0;i<(int)banks.size();i++)
	{
		Bank &b = banks[i];
		b.alloc_bottom = b.addr_start;
		b.alloc_top = b.addr_end;
	}
	memset(alloc_mask,0,sizeof(alloc_mask));

	// allocate
	for(int i=0;i<(int)sl.size();i++)
		InsertSection( *sl[i] );

	// final label update
	for(int i=0;i<(int)sl.size();i++)
		UpdateLabelAddresses( *sl[i] );

    // generate bytes
	memset(alloc_mask,0,sizeof(alloc_mask));
	memset(raw_image,0,sizeof(raw_image));

	for(int i=0;i<(int)sl.size();i++)
		GenerateBytes( *sl[i] );

	
	PrintStats();

	
	// save bin
	string fname = vm.GetString("output_file_name");
	string fbase = FilePathGetPart(fname.c_str(),true,true,false);
	DumpBin( fname.c_str() );
	DumpAsm((fbase+".lst").c_str());
	DumpMap( (fbase+".gmap").c_str() );
	state.DumpSym( (fbase+".sym").c_str() );
}

void SqLinker::DumpBin(const char *path)
{
//    FILE *fp = fopen(path,"wb");
//    if(!fp) Error(format("Can't write to '%s'",path).c_str());
//
//	int nbanks = banks.size();
//	int *order = BANK_ORDER_2;
//	//nbanks = 8;
//	if(nbanks>2 && nbanks<=4) nbanks = 4, order = BANK_ORDER_4;
//	if(nbanks>4 && nbanks<=8) nbanks = 8, order = BANK_ORDER_8;
//
//	if(nbanks>MAX_BANKS)
//		Error("Bank number limit exceeded");
//
//	for(int j=0;j<nbanks;j++)
//	{
//		int b = order[j];
//		fwrite(&raw_image[b][0xF000],1,0x1000,fp);
//	}
//    fclose(fp);
	if( !vm.Run("link_write_binary",path) )
		Error("[script] link_write_binary failed.");
}

void SqLinker::DumpAsm(const char *path)
{
	vector<string> lst;
	for(int i=0;i<state.NumSections();i++)
	{
		AsmSection &as = *state.GetSection(i);
		if(as.referenced)
			as.AppendDisassembly(lst);
	}
	FILE *fp = fopen(path,"wt");
	if(!fp) return;
	for(int i=0;i<(int)lst.size();i++)
		fprintf(fp,"%s\n",lst[i].c_str());
	fclose(fp);
}

void SqLinker::DumpMap(const char *path)
{
	FILE *fp = fopen(path, "wt");
	if( !fp ) return;
	//fprintf(fp, "<html><body>\n");

	map<int, map<int, AsmSection*> > bmap;
	static AsmSection collision_marker;

	for( int i=0; i<state.NumSections(); i++ )
	{
		AsmSection &as = *state.GetSection(i);
		if( !as.referenced || as.address<0 )
			continue;

		for( int j=0; j<(int)as.code_bitmask.size(); j++ )
		{
			int mask = as.code_bitmask[j];
			for( int k=0; k<(int)banks.size(); k++ )
				if( mask&(1<<k) )
				{
					AsmSection *&ptr = bmap[k][as.address+j];
					if( ptr && ptr!=&as )
						ptr = &collision_marker;
					else
						ptr = &as;
				}
		}
	}

	for( map<int, map<int, AsmSection*> >::iterator bp=bmap.begin(); bp!=bmap.end(); ++bp )
	{
		map<int, AsmSection*> &mp = bp->second;
		if( mp.size()<=0 )
			continue;

		const int rowlen = 64;
		int addr_min = mp.begin()->first;
		//int addr_min = bank_get_start(bp->first);
		map<int, AsmSection*>::iterator p = mp.end();
		int addr_max = (--p)->first;
		//int addr_max = bank_get_last_used_byte(bp->first);	// (--p)->first;

		addr_min &= ~(rowlen-1);
		addr_max = (addr_max | (rowlen-1)) + 1;

		fprintf(fp, "Bank %d: %s\n", bp->first, banks[bp->first].name.c_str());

		//fprintf(fp, "Bank %d: %s<br/>\n", bp->first, banks[bp->first].name.c_str());
		//fprintf(fp, "<table border=0 cellpadding=0 cellspacing=0>\n");
		//<table border=0 cellpadding=0 cellspacing=0>
		//	<tr>
		//	<td width=30px height=30 style='border-top: 1px solid black;border-left: 1px solid black' align=center>63</td>
		//	</tr>
		//	</table>

		AsmSection *cur_sec = NULL;
		const char *cur_name = "";
		for( int addr=addr_min; addr<addr_max; )
		{
			//fprintf(fp, "<tr>\n");
			//fprintf(fp, "<td width=64px style='' align=center>$%04X</td>\n", addr);
			fprintf(fp, "$%04X:  ", addr);

			for( int i=0; i<rowlen; i++ )
			{
				AsmSection *as = mp[addr];
				if( as==NULL )
				{
					fprintf(fp, "?");
					cur_sec = NULL;
				}
				else
				{
					if( as!=cur_sec )
					{
						cur_sec = as;
						cur_name = as->name.c_str();
						fprintf(fp, "[");
					}
					else if( addr == cur_sec->address + (int)cur_sec->code_bitmask.size() - 1 )
						fprintf(fp, "]");
					else
					{
						if( *cur_name )
							fprintf(fp, "%c", *cur_name++);
						else
							fprintf(fp, "-");
					}
				}
				addr++;
			}

			fprintf(fp, "\n");

			//fprintf(fp, "</tr>\n");
		}
		//fprintf(fp, "</table>\n");
		fprintf(fp, "\n");
	}

	//fprintf(fp, "</body></html>\n");
	fclose(fp);
}



const char *SqLinker::Link()
{
	try {
		RunLinker();
	}
	catch( const char *e )
	{
		static string err;
		err = e;

		state.DumpSym("test_raw.sym");

		return err.c_str();
	}

	return NULL;
}

void SqLinker::PrintStats()
{
	printf("\n");
	printf("Bank            Used  Free  BlkFree NoCrossFree\n");
	int totfree = 0;
	int totused = 0;
	for( int i=0; i<(int)banks.size(); i++ )
	{
		Bank &b = banks[i];
		int used = 0;
		int free = 0;
		int block_free = 0;
		int max_block_free = 0;
		int nocross_free = 0;
		int max_nocross_free = 0;

		for( int j=b.addr_start; j<b.addr_end; j++ )
		{
			if( j%256==0 ) nocross_free = 0;
			if( alloc_mask[j] & b.layer_bits )
			{
				used++;
				block_free = 0;
				nocross_free = 0;
			}
			else
			{
				free++;
				nocross_free++;
				block_free++;
				if( block_free  >max_block_free ) max_block_free  =block_free;
				if( nocross_free>max_nocross_free ) max_nocross_free=nocross_free;
			}
		}
		totfree += free;
		totused += used;

		printf("%-16s%5d %5d   %5d         %3d\n", b.name.c_str(), used, free, max_block_free, max_nocross_free);
	}
	printf("%16s%5d %5d\n", "--- Total ---  ", totused, totfree);
	printf("\n");

	//	if( !vm.Run("link_print_stats") )
	//		Error("[script] link_print_stats failed.");
}
