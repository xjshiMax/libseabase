//2019-09-17 by xjshi
/*
1）封装基类，方便以后换掉底层实现
2) 主要接口 上传 下载 进度 断点续传
*/
#include <stdio.h>
#include <string>
using namespace std;
namespace SEABASE
{
    class ftpClientBase
    {
    public:
        ftpClientBase(){};
        virtual~ftpClientBase(){};

    public:
        int FTP_InitParam(string username,string password,string url)
        {
            m_username=username;
            m_password=password;
            m_url=url;
            return 0;
        }
        //上传文件
        virtual int FTP_UpLoadFile(string remotepath,string localfilepath,int timeout,int trytimes=3){return 0;};
        //断点续传
        virtual int FTP_UpLoad_Till(){return 0;};
        //下载文件
        virtual int FTP_DownLoadFile( void *deststream,string srcfile=""){return 0;};
        //获取进度
        virtual int FPT_GetProcessPoint(){return 0;};

    public:
        string m_username;
        string m_password;
        string m_url;
    };
}