
#ifndef _BASE_CONVERT2_H
#define _BASE_CONVERT2_H


namespace base
{


void		ParseWhitespace(const char *&s);
int         ParseHex(const char *&s);
int			ParseInt(const char *&s);
float		ParseFloat(const char *&s);
void		ParseString(const char *&s,std::string &out);
std::string	ParseString(const char *&s);
void		ParseStringT(const char *&s,std::string &out,const char *terminators);
void        ParseHexBuffer(const char *&s,std::vector<uint8_t> &buff);


inline void AppendHex(std::string &str,int value) { str += format("0x%08x",value); }
inline void AppendInt(std::string &str,int value) { str += format("%d",value); }
void        AppendFloat(std::string &str,float value);
void        AppendString(std::string &str,const char *v,const char *escape);
void        AppendHexBuffer(std::string &str,const void *v,int size);



}




#endif
