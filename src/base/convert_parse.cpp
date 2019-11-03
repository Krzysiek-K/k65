
#include "base.h"


using namespace std;


namespace base
{




void ParseWhitespace(const char *&s)
{
	while(*s==' ' || *s=='\t' || *s=='\n' || *s=='\r')
		s++;
}

int ParseHexNoSkip(const char *&s)
{
    int v = 0;
    while(1)
    {
        if(*s>='0' && *s<='9') v = (v<<4) + (*s++ - '0');
        else if(*s>='a' && *s<='f') v = (v<<4) + (*s++ - 'a' + 10);
        else if(*s>='A' && *s<='F') v = (v<<4) + (*s++ - 'A' + 10);
        else break;
    }
    return v;
}

int ParseHex(const char *&s)
{
    ParseWhitespace(s);
    return ParseHexNoSkip(s);
}

int ParseInt(const char *&s)
{
    ParseWhitespace(s);

    int sign = 1;
    if(*s=='+') s++;
    else if(*s=='-') s++, sign = -1;

    if(s[0]=='0' && (s[1]=='x' || s[1]=='X'))
    {
        s += 2;
        return sign*ParseHexNoSkip(s);
    }

    int vv = 0;
    while(*s>='0' && *s<='9')
        vv = vv*10 + (*s++ - '0');

    return vv*sign;
}

float ParseFloat(const char *&s)
{
    ParseWhitespace(s);

    int sign = 0;
    if(*s=='+') s++;
    else if(*s=='-') s++, sign = 1;

    float vv = 0;
    const char *bs = s;
    while(*s>='0' && *s<='9') s++;
    if(*s=='.')
    {
        s++;
        while(*s>='0' && *s<='9') s++;
    }
    if(*s=='e')
    {
        s++;
        if(*s=='+' || *s=='-') s++;
        while(*s>='0' && *s<='9') s++;
    }

    if(*s=='#')
    {
        s++;
        //if(_strnicmp(s,"Inf",3)==0)
        //{
        //    s += 3;
        //    *(uint32_t*)&vv = sign ? 0xFF800000 : 0x7F800000;
        //    return vv;
        //}
        //else if(_strnicmp(s,"QNAN",4)==0)
        //{
        //    s += 4;
        //    *(uint32_t*)&vv = sign ? 0xFFFFFFFF : 0x7FFFFFFF;
        //    return vv;
        //}
    }

    sscanf(bs,"%f",&vv);

    if(sign) *(uint32_t*)&vv |= 0x80000000;
    return vv;
}


static const uint32_t TERM_PARSE_WORD[8] = {0xFFFFFFFF,(1<<(' '-32))};
static const uint32_t TERM_BREAK_QUOTED[8] = {(1<<0) | (1<<'\n') | (1<<'\r'), (1<<('"'-32)), (1<<('\\'-64))};


static inline void _parse_string_raw(const char *&s,string &out,const uint32_t term[8])
{
    const char *b = s;
    while(!( term[uint8_t(*s)>>5] & (1<<(uint8_t(*s)&31)) ) )
        s++;
    out.assign(b,s);
}

static inline void _parse_string_quoted_t(const char *&s,string &out,const uint32_t term[8])
{
    out.clear();
    while(1)
    {
        const char *b = s;
        while(!( term[uint8_t(*s)>>5] & (1<<(uint8_t(*s)&31)) ) )
            s++;
        if(s!=b) out.append(b,s);

        if(*s!='\\') break;

        s++;
        if(!*s) break;

        if(*s=='n') out.push_back('\n');
        else if(*s=='r') out.push_back('\r');
        else if(*s=='t') out.push_back('\t');
        else if(*s=='b') out.push_back('\b');
        else if(*s>='0' && *s<='7')
        {
            int v = 0, n = 0;
            while(*s>='0' && *s<='7' && n<3)
            {
                v = v*8 + (*s++ - '0');
                n++;
            }
            out.push_back(v);
            s--;    // compensate for upcoming s++
        }
        else if(*s=='\n') {}
        else out.push_back(*s);
        s++;
    }
}

void ParseString(const char *&s,std::string &out)
{
    ParseWhitespace(s);
    if(*s=='"')
    {
        s++;
        _parse_string_quoted_t(s,out,TERM_BREAK_QUOTED);
        if(*s=='"')
            s++;
    }
    else
        _parse_string_raw(s,out,TERM_PARSE_WORD);
}

std::string	ParseString(const char *&s)
{
	string str;
	ParseString(s,str);
    return str;
}

void ParseStringT(const char *&s,std::string &out,const char *terminators)
{
    ParseWhitespace(s);
    if(*s=='"')
    {
        s++;
        _parse_string_quoted_t(s,out,TERM_BREAK_QUOTED);
        if(*s=='"')
            s++;
    }
    else
    {
		uint32_t term[8]={TERM_PARSE_WORD[0],TERM_PARSE_WORD[1],TERM_PARSE_WORD[2],TERM_PARSE_WORD[3]};
        while(*terminators)
        {
            term[uint8_t(*terminators)/32] |= (1<<(uint8_t(*terminators)%32));
            terminators++;
        }

        _parse_string_raw(s,out,term);
    }
}

void ParseHexBuffer(const char *&s,vector<uint8_t> &buff)
{
    buff.clear();

    while(1)
    {
		uint8_t v;
             if(*s>='0' && *s<='9') v = (*s++ - '0')<<4;
        else if(*s>='a' && *s<='f') v = (*s++ - 'a' + 10)<<4;
        else if(*s>='A' && *s<='F') v = (*s++ - 'A' + 10)<<4;
        else break;

        if(*s>='0' && *s<='9') v |= (*s++ - '0');
        else if(*s>='a' && *s<='f') v |= (*s++ - 'a' + 10);
        else if(*s>='A' && *s<='F') v |= (*s++ - 'A' + 10);
        else break;

        buff.push_back(v);
    }
}



}
