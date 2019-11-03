
#define _CRT_SECURE_NO_WARNINGS

//#include <windows.h>

#include "base.h"

using namespace std;



namespace base
{


NativeFileSystem NFS;




FileReaderStream *NativeFileSystem::GetFileAsStream(const char *path)
{
	FileReaderStream *fr = new FileReaderStream(path);
	if(fr->WasError())
	{
		delete fr;
		return NULL;
	}
	return fr;
}

#if 0
bool NativeFileSystem::GetSubdirList(const char *path,std::vector<std::string> &out)
{
	out.clear();
	
	WIN32_FIND_DATA fdata;
	HANDLE h = FindFirstFile(path,&fdata);
	if(h==INVALID_HANDLE_VALUE) return false;

	do {
		if(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			out.push_back(fdata.cFileName);
	} while( FindNextFile(h,&fdata) != 0 );

	FindClose(h);

	return true;
}

bool NativeFileSystem::GetFileList(const char *path,std::vector<std::string> &out)
{
	out.clear();
	
	WIN32_FIND_DATA fdata;
	HANDLE h = FindFirstFile(path,&fdata);
	if(h==INVALID_HANDLE_VALUE) return false;

	do {
		if(!(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			out.push_back(fdata.cFileName);
	} while( FindNextFile(h,&fdata) != 0 );

	FindClose(h);

	return true;
}

int NativeFileSystem::GetFileSize(const char *path)
{
	HANDLE h = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(h == INVALID_HANDLE_VALUE) return 0;

	int s = ::GetFileSize(h,NULL);
	if(s<0) s = 0;

	CloseHandle(h);

	return s;
}
#endif

bool NativeFileSystem::WriteFileLines(const char *path,std::vector<std::string> &v)
{
	FILE *fp = fopen(path,"wt");
	if(!fp) return false;
	for(int i=0;i<(int)v.size();i++)
	{
		fputs(v[i].c_str(),fp);
		fputc('\n',fp);
	}
	fclose(fp);
	return true;
}

bool NativeFileSystem::DumpRaw(const char *path,void *data,int size)
{
	FILE *fp = fopen(path,"wb");
	if(!fp) return false;
	fwrite(data,1,size,fp);
	fclose(fp);
	return true;
}




string FilePathGetPart(const char *path,bool dir,bool name,bool ext)
{
	const char *p = path;
	while(*p) p++;
	p--;
	while(p>=path && *p!='/' && *p!='\\') p--;
	p++;

	const char *dir_e = p;
	const char *name_b = (*p=='/' || *p=='\\') ? p+1 : p;
	while(*p && *p!='.') p++;
	const char *ext_b = p;

	if(dir)	if(name)	if(ext)	return string(path);								// dir	name	ext
						else	return string(path,ext_b);							// dir	name
			else		if(ext)	{ }													// dir			ext
						else	return string(path,dir_e);							// dir
	else	if(name)	if(ext)	return string(name_b);								//		name	ext
						else	return string(name_b,ext_b);						//		name
			else		if(ext)	return string(ext_b);								//				ext
						else	return string();									//

	// dir + ext
	string out(path,dir_e);
	out.append(ext_b);
	return out;
}


#if 0
string GetCurrentDir()
{
	vector<char> buff;
	int len = GetCurrentDirectory(0,NULL);
	buff.resize(len+1);
	GetCurrentDirectory(len+1,&buff[0]);
	return string(&buff[0]);
}


unsigned long long GetFileTime(const char *path)
{
    WIN32_FILE_ATTRIBUTE_DATA a;
    if(!GetFileAttributesEx(path,GetFileExInfoStandard,&a))
        return 0;

    return (((unsigned long long)a.ftLastWriteTime.dwHighDateTime)<<32) | a.ftLastWriteTime.dwLowDateTime;
}
#endif



}
