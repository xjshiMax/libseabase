//2019/3/22
//xjshi 
/*
��Ҫʵ��tcp �ͻ��� ���߷���˽������ݡ�
*/
//һ������ȡ8k�ֽڡ�
#define MAXREADSIZE		1024*8
#include "xbaseclass.h"
#include "basesock.h"
namespace SEABASE{
	class xReceivebackbase
	{
	public:
		xReceivebackbase(){};
		virtual ~xReceivebackbase(){}
		//virtual void Onopen(){};
		virtual void Ondata(int socketfd,char*data,int len)=0;
		virtual void Onclose(int socketfd){};
	};
	class xReceiveback :public xReceivebackbase,public xEventHandler
	{
	public:
		virtual handle_t GetHandler()const
		{
			return m_Eventfd;
		}
		virtual void HandleRead(int listentfd)
		{
			char buf[MAXREADSIZE]={0};
			int len=MAXREADSIZE;
			int iret = ReadSocket(listentfd,buf,len);
			len=sizeof(buf);
			if(iret==0)
			{
				CloseSocket(listentfd);
				ShutDownSocket(listentfd,0);
				this->Onclose(listentfd);
				//CloseSocket(listentfd);
			}
			else if(iret>=0)
				this->Ondata(listentfd,buf,iret);
			else
				return ;
		}
		virtual void  Ondata(int socketfd,char*data,int len){};

	};
}