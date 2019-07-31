#include "../include/xEcharacterCode.h"
#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#else
#include<dlfcn.h>
#include <iconv.h>
#endif

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
    if (iconv(cd, pin, &src_len, &out, &dst_len) == -1)
        return "";
    iconv_close(cd);
    string strtemp(dst_str,strlen(dst_str));
    delete[] dst_str;
    return strtemp;
#endif
}