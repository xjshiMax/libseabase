//2019-09-17 by xjshi
/*
1������libcurl����װ��ʵ��ftp client�Ļ�������
2���̳л��࣬�����Ժ󻻵��ײ�ʵ��
3����ʵ��Ϊ��
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
    class API_EXPORT  ExftpClient:public ftpClientBase
    {
    public:
        //remotepath newfile/
       int FTP_UpLoadFile(string remotepath,string localfilepath,int timeout,int trytimes=3);
       int FTP_UpLoad_Till();
       int FTP_DownLoadFile(void *deststream,string srcfile="");
       int FPT_GetProcessPoint();
    private:
        string inner_getsrcFullPath();
    };
};