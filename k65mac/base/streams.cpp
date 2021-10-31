
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"

using namespace std;



namespace base {


// ---------------- In/Out Stream ----------------

int OutStream::operator <<(InStream &input)
{
	char buffer[4096];
	int rlen, wlen, rpos, total = 0;

	if(WasError())
		return 0;

	if(input.WasError())
	{
		error = 1;
		return 0;
	}

	while(1)
	{
		rlen = input.ReadBytes(buffer,sizeof(buffer));

		if(input.WasError())
		{
			error = 1;
			break;
		}

		if(rlen<=0)
			break;

		rpos = 0;
		while(rlen>0)
		{
			wlen = WriteBytes(buffer+rpos,rlen);
			if(wlen<=0) break;
			total += wlen;
			rpos += wlen;
			rlen -= wlen;
		}
	}

	if(rlen>0)
		error = 1;

	return total;
}



// ---------------- File Reader/Writer Stream ----------------

FileReaderStream::FileReaderStream(const char *path,bool binary)
{
	fp = fopen(path, binary ? "rb" : "rt" );
	if(!fp) error |= STREAM_ERR_NOT_OPEN;
}

FileReaderStream::~FileReaderStream()
{
	if(fp) fclose(fp);
}

int FileReaderStream::ReadBytes(void *buffer,int size)
{
	if(!fp) return 0;
	return fread(buffer,1,size,fp);
}


FileWriterStream::FileWriterStream(const char *path,bool binary)
{
	fp = fopen(path, binary ? "wb" : "wt" );
	if(!fp) error |= STREAM_ERR_NOT_OPEN;
}

FileWriterStream::~FileWriterStream()
{
	if(fp) fclose(fp);
}

int FileWriterStream::WriteBytes(const void *buffer,int size)
{
	if(!fp) return 0;
	return fwrite(buffer,1,size,fp);
}



// ---------------- Stored Byte Array Streams ----------------

int StoredByteArrayReader::ReadBytes(void *buffer,int size)
{
	if(pos>=(int)data.size())
	{
		pos = data.size();
		error |= STREAM_ERR_EOF;
		return 0;
	}

	int s1 = size;
	if(pos+s1>=(int)data.size())
	{
		error |= STREAM_ERR_EOF;
		s1 = data.size() - pos;
	}

	if(s1>0) memcpy(buffer,&data[pos],s1);
	pos += s1;

	return s1;
}


int StoredByteArrayWriter::WriteBytes(const void *buffer,int size)
{
	int psize = data.size();
	data.resize(psize+size);
	if(size) memcpy(&data[psize],buffer,size);
	return size;
}


// ---------------- helper functions ----------------



bool GetStreamBytes(vector<uint8_t> &out,InStream *in)
{
	if(!in) { out.resize(0); return false; }

	out.resize(0);

	// TODO: add error checking
	uint8_t buffer[16*1024];
	do {
		int len = in->ReadBytes(buffer,sizeof(buffer));
		if(len<=0) break;
		out.insert(out.end(),buffer+0,buffer+len);
	} while(true);

	return true;
}

bool GetStreamLines(vector<string> &out,InStream *in)
{
	if(!in) { out.resize(0); return false; }

	out.resize(1);
	out[0].clear();

	// TODO: add error checking
	char buffer[16*1024];
	do {
		int len = in->ReadBytes(buffer,sizeof(buffer));
		if(len<=0) break;

		char *s = buffer;
		char *e = buffer + len;
		while(s<e)
		{
			while(s<e && *s=='\r') s++;
			if(s<e && *s=='\n') { out.push_back(string()); s++; continue; }

			char *b = s;
			while(s<e && *s!='\n' && *s!='\r')
				s++;
			if(b<s)
				out.back().append(b,s);
		}
	} while(true);

	return true;
}


bool GetStreamText(string &out,InStream *in)
{
	out.clear();
	if(!in) return false;

	// TODO: add error checking
	char buffer[16*1024];
	do {
		int len = in->ReadBytes(buffer,sizeof(buffer));
		if(len<=0) break;

		char *s = buffer;
		char *e = buffer + len;

		while(s<e)
		{
			while(s<e && *s=='\r') s++;
			char *p = s;
			while(s<e && *s!='\r') s++;
			out.append(p,s);
		}
	} while(true);

	return true;
}



}
