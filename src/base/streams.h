
#ifndef _B_STREAMS_H
#define _B_STREAMS_H


#include <stdio.h>
#include <string>
#include <vector>



namespace base {


enum {
	STREAM_ERR_NONE			= 0,
	STREAM_ERR_EOF			= (1<<0),
	STREAM_ERR_NOT_OPEN		= (1<<1),
};


class InStream {
public:
	InStream() { error = 0; }

	virtual int ReadBytes(void *buffer,int size) { *(int*)0 = 0; return 0; }

	void Read(void *buffer,int size)
	{
		if(!error && size>0)
			if(ReadBytes(buffer,size)!=size)
				error |= STREAM_ERR_EOF;
	}
	bool WasError()		{ return (error!=0); }
	int  GetError()		{ return error; }
	void ClearError()	{ error &= ~STREAM_ERR_NOT_OPEN; }

	virtual ~InStream() {}

protected:
	int	error;
};

class OutStream {
public:
	OutStream() { error = 0; }

	virtual int WriteBytes(const void *buffer,int size) { *(int*)0 = 0; return 0; }
	int operator <<(InStream &input);

	void Write(const void *buffer,int size)
	{
		if(!error && size>0)
			if(WriteBytes(buffer,size)!=size)
				error |= STREAM_ERR_EOF;
	}
	bool WasError()		{ return (error!=0); }
	int  GetError()		{ return error; }
	void ClearError()	{ error &= ~STREAM_ERR_NOT_OPEN; }

	virtual ~OutStream() {}

protected:
	int error;
};


class FileReaderStream : public InStream {
public:
	FileReaderStream(const char *path,bool binary = true);
	virtual ~FileReaderStream();
	virtual int ReadBytes(void *buffer,int size);

private:
	FILE *fp;
};

class FileWriterStream : public OutStream {
public:
	FileWriterStream(const char *path,bool binary = true);
	virtual ~FileWriterStream();
	virtual int WriteBytes(const void *buffer,int size);

private:
	FILE *fp;
};


class StoredByteArrayReader : public InStream {
public:
	std::vector<uint8_t>	data;

	StoredByteArrayReader() : pos(0) {}
	virtual int ReadBytes(void *buffer,int size);
	void Rewind() { pos = 0; }

private:
	int				pos;
};

class StoredByteArrayWriter : public OutStream {
public:
	std::vector<uint8_t>	data;

	StoredByteArrayWriter() {}
	virtual int WriteBytes(const void *buffer,int size);

};


/*
class StringReaderStream : public InStream {
public:
	StringReaderStream(std::string &str);
	virtual ~StringReaderStream();
};

class StringWriterStream : public OutStream {
public:
	StringWriterStream(std::string &str);
	virtual ~StringWriterStream();
};
*/



bool GetStreamBytes(std::vector<uint8_t> &out,InStream *in);
bool GetStreamLines(std::vector<std::string> &out,InStream *in);
bool GetStreamText(std::string &out,InStream *in);




}



#endif
