//2019-09-17 by xjshi
/*
1����װ���࣬�����Ժ󻻵��ײ�ʵ��
2) ��Ҫ�ӿ� �ϴ� ���� ���� �ϵ�����
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
        //�ϴ��ļ�
        virtual int FTP_UpLoadFile(string remotepath,string localfilepath,int timeout,int trytimes=3){return 0;};
        //�ϵ�����
        virtual int FTP_UpLoad_Till(){return 0;};
        //�����ļ�
        virtual int FTP_DownLoadFile( void *deststream,string srcfile=""){return 0;};
        //��ȡ����
        virtual int FPT_GetProcessPoint(){return 0;};

    public:
        string m_username;
        string m_password;
        string m_url;
    };
}