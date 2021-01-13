#include "../include/xEcharacterCode.h"
#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#else
#include<dlfcn.h>
#include <iconv.h>
#endif
#include<string.h>
#include<stdio.h>
#include<errno.h>
using namespace std;

using namespace SEABASE;

int CharacterCode::GetCharacterTpye()
{
    return 0;
}
string CharacterCode::Gb2312ToUTF_8(char* gb2312)
{
#ifdef WIN32
    int len=MultiByteToWideChar(CP_ACP,0,gb2312,-1,NULL,0);
    wchar_t*wstr=new wchar_t[len+1];
    memset(wstr,0,len+1);
    MultiByteToWideChar(CP_ACP,0,gb2312,-1,wstr,len);
    len=WideCharToMultiByte(CP_UTF8,0,wstr,-1,NULL,0,NULL,NULL);
    char*str=new char[len+1];
    memset(str,0,len+1);
    WideCharToMultiByte(CP_UTF8,0,wstr,-1,str,len,NULL,NULL);
    if(wstr)delete[] wstr;
    string strtemp(str,strlen(str));
    if(str) delete[] str;
    return strtemp;
#else
    iconv_t cd;
    char **pin = &gb2312;
    size_t src_len=strlen(gb2312);
    cd = iconv_open("utf8", "gbk");
    if (cd == 0)
        return "";
    size_t dst_len=2*src_len+1;
    char *dst_str=new char[dst_len];
    char*out=dst_str;
    memset(dst_str, 0, dst_len);
	int ret = iconv(cd, pin, &src_len, &out, &dst_len);
	printf("ret=%d,erron=%d\n",ret,errno);
	printf("out=%s\n",out);
	switch(errno)
	{
	case  E2BIG:
		printf("E2BIG\n");
	case  EILSEQ:
		printf("EILSEQ\n");
	case  EINVAL:
		printf("EINVAL\n");
	}
    if (ret == -1)
        return "";
    iconv_close(cd);
    string strtemp(dst_str,strlen(dst_str));
    delete[] dst_str;
    return strtemp;
#endif
}
string CharacterCode::UTF_8ToGb2312(const char* utf8)
{
#ifdef WIN32
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
#else
	iconv_t cd;
	char **pin = (char**)&utf8;
	size_t src_len=strlen(utf8);
	cd = iconv_open("gbk", "utf8");
	if (cd == 0)
		return "";
	size_t dst_len=2*src_len+1;
	char *dst_str=new char[dst_len];
	char*out=dst_str;
	memset(dst_str, 0, dst_len);
	if (iconv(cd, pin, &src_len, &out, &dst_len) == -1)
		return "";
	iconv_close(cd);
	string strtemp(dst_str,strlen(dst_str));
	delete[] dst_str;
	return strtemp;
#endif
}
void CharacterCode::Ascii2BCD( char *bcd_buf, char *asc_buf,int num)
{
    int     i, len;

    len = num / 2 ;
    for ( i=0; i<len; i++)
    {
        if (asc_buf[i * 2 + 0] >= '0' && asc_buf[i * 2 + 0] <= '9')
        {
            bcd_buf[i] = (asc_buf[i * 2 + 0] - 48) * 16 ;
        }
        if (asc_buf[i * 2 + 0] >= 'A' && asc_buf[i * 2 + 0] <= 'Z')
        {
            bcd_buf[i] = (asc_buf[i * 2 + 0] - 'A' + 10) * 16 ;
        }
        if (asc_buf[i * 2 + 0] >= 'a' && asc_buf[i * 2 + 0] <= 'z')
        {
            bcd_buf[i] = (asc_buf[i * 2 + 0] - 'a' + 10) * 16 ;
        }

        if (asc_buf[i * 2 + 1] >= '0' && asc_buf[i * 2 + 1] <= '9')
        {
            bcd_buf[i] += (asc_buf[i * 2 + 1] - 48)  ;
        }
        if (asc_buf[i * 2 + 1] >= 'A' && asc_buf[i * 2 + 1] <= 'Z')
        {
            bcd_buf[i] += (asc_buf[i * 2 + 1] - 'A' + 10)  ;
        }
        if (asc_buf[i * 2 + 1] >= 'a' && asc_buf[i * 2 + 1] <= 'z')
        {
            bcd_buf[i] += (asc_buf[i * 2 + 1] - 'a' + 10)  ;
        }
    }
}
    //		bcd_buf[i]=((asc_buf[2*i] & 0x0f) << 4)+(asc_buf[2*i+1] & 0x0f);

	//Õ­×Ö·û×ª¿í×Ö·û
	wchar_t* CharacterCode::AnsiToUnicode(const char* szStr)
{
#ifdef WIN32
		int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0 );

		if (nLen == 0)
		{
			return NULL;
		}
		wchar_t* pResult = new wchar_t[nLen];
		MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen );
		return pResult;
#else
#endif
	return NULL;

	}
