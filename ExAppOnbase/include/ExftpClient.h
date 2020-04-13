//2019-09-17 by xjshi
/*
1）基于libcurl做封装，实现ftp client的基本功能
2）继承基类，方便以后换掉底层实现
3）简单实用为主
*/
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;
#include "ExftpClientbase.h"
#ifdef EXAPPLICATION_EXPORTS
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT
#endif
namespace SEABASE{
    struct FtpFile
    {
        const char*filename;
        FILE* stream;
    };
    typedef int(*pcallback)(int point);
    class API_EXPORT  ExftpClient:public ftpClientBase
    {
    public:
        //remotepath newfile/
       int FTP_UpLoadFile(string remotepath,string localfilepath,int timeout,int trytimes=3);
       int FTP_UpLoad_Till();
       int FTP_DownLoadFile(void *deststream,string srcfile="");
       int FPT_GetProcessPoint();
            //获取进度，以回掉函数的方式返回进度
        virtual void FTP_SETProcessPointCallback(pcallback callback){};
    private:
        string inner_getsrcFullPath();
        pcallback m_callback;
    };
};