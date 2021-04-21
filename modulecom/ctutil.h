#ifndef __UTIL_H__
#define __UTIL_H__

#include "cttypes.h"

char*   newStr(const char *pStr);
int     GetFilePos(int fd);

#ifndef WIN32
int     min(int a, int b);
int     max(int a, int b);
int     Sleep(unsigned long t );

class CTimer{
	private:
		struct timeval    time_val;

	public:
                CTimer();
                CTimer(long sec,long usec);
                ~CTimer();
		void SetTimer(long sec,long usec);
		int Wait();
};
std::string GetCommandLine(int pi);
#endif

#ifdef _UNICODE
bool unicode2ascii(const char* src, int src_len, char* dest, int max_dest_len, int& ret_dest_len, bool is_network );
#endif

char* getmyipaddr(size_t nIndex=0);
int   getMAC(char * mac);
void  MYTRACE(const char *format,...);

char* str_trim(char* str);
int	  ReadDataFromFile(CTstring sFilName,CTstring& strFileContent);
int	  CopyFile(CTstring sSrcFilName,CTstring sDstFileName);

//from patterns/util/StringUtil.hpp
void trim(std::string& s);
unsigned int split(std::vector<std::string>& v, 
				   const std::string& s, const char* delimiter,
				   unsigned int maxSegments = INT_MAX);
#endif
