
#ifndef _BASE_VFS_H
#define _BASE_VFS_H


#include <vector>


namespace base
{


class FileSystem {
public:
	virtual InStream *GetFileAsStream(const char *path) = 0;

	virtual bool GetFileBytes(const char *path,std::vector<uint8_t> &data)
	{
		InStream *s = GetFileAsStream(path);
		bool ok = GetStreamBytes(data,s);
		if(s) delete s;
		return ok;
	}

	virtual bool GetFileLines(const char *path,std::vector<std::string> &data)
	{
		InStream *s = GetFileAsStream(path);
		bool ok = GetStreamLines(data,s);
		if(s) delete s;
		return ok;
	}

	virtual bool GetFileText(const char *path,std::string &data)
	{
		InStream *s = GetFileAsStream(path);
		bool ok = GetStreamText(data,s);
		if(s) delete s;
		return ok;
	}

	template <class _T>
	bool ReadRawVector(const char *path,std::vector<_T> &out);

	virtual bool GetSubdirList(const char *path,std::vector<std::string> &out) { out.clear(); return false; }
	virtual bool GetFileList(const char *path,std::vector<std::string> &out) { out.clear(); return false; }
	virtual int  GetFileSize(const char *path) { return 0; }

	virtual ~FileSystem() {}
};


template<class _T>
bool FileSystem::ReadRawVector(const char *path,std::vector<_T> &out)
{
	InStream *in = GetFileAsStream(path);
	if(!in || !sizeof(_T)) { out.resize(0); return false; }

	out.resize(0);

	// TODO: add error checking
	uint8_t buffer[16*1024];
	int fill = 0;
	do {
		int len = in->ReadBytes(buffer,sizeof(buffer));
		if(len<=0) break;
		
		out.resize((fill+len+sizeof(_T)-1)/sizeof(_T));
		memcpy(((uint8_t*)&out[0])+fill,buffer,len);
		fill += len;
	} while(true);

	out.resize(fill/sizeof(_T));

	return true;
}


class NativeFileSystem : public FileSystem {
public:
	virtual FileReaderStream *GetFileAsStream(const char *path);
	//virtual bool GetSubdirList(const char *path,std::vector<std::string> &out);
	//virtual bool GetFileList(const char *path,std::vector<std::string> &out);
	//virtual int  GetFileSize(const char *path);

	bool WriteFileLines(const char *path,std::vector<std::string> &v);

	bool DumpRaw(const char *path,void *data,int size);

	template <class _T>
	bool DumpRawVector(const char *path,std::vector<_T> &v)
	{ return DumpRaw(path,v.size()?&v[0]:NULL,sizeof(_T)*v.size()); }

	virtual ~NativeFileSystem() {};
};



std::string FilePathGetPart(const char *path,bool dir,bool name,bool ext);
std::string GetCurrentDir();
unsigned long long GetFileTime(const char *path);


extern NativeFileSystem NFS;


}



#endif
