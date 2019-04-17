//2019/3/22
//xjshi 
/*
主要实现tcp 客户端 或者服务端接收数据。
*/
//一次最大读取8k字节。
#define MAXREADSIZE		1024*8
#include "xbaseclass.h"
#include "basesock.h"
namespace SEABASE{
	class xReceivebackbase
	{
	public:
		xReceivebackbase(){};
		virtual ~xReceivebackbase(){}
		/*
		这里onopen 个一个xEventHandler 为输入参数，后续可以将其他的类传入，注册接收到的fd
		*/
		//virtual void Onopen(int socketfd,char*date,int len,IN xEventHandler *clientHandle){};
		virtual void Ondata(int socketfd,char*data,int len)=0;
		virtual void Onclose(int socketfd)=0;
	};
	class xtcpserver:public xReceivebackbase,public xEventHandler
	{
		virtual int Onaccept(int socketfd,char*data,int len,IN xEventHandler**clientHandle=NULL)=0;
		virtual int Ondata(int socketfd,char*date,int len){return 0;};
		virtual int Onclose(int socketfd){return 0;};
	};
	class Eventcallback
	{
	public:
		static void AcceptCallback(int sockfd,xEventDemultiplexer*Demultiplexer,void *arg);
		static void DataCallback(int sockfd,xEventDemultiplexer*Demultiplexer,void *arg);
	};
	class xReceivebackbase
	{
	public:
		xReceivebackbase(){};
		virtual ~xReceivebackbase(){}
		/*
		这里onopen 个一个xEventHandler 为输入参数，后续可以将其他的类传入，注册接收到的fd
		*/
		//virtual void Onopen(int socketfd,char*date,int len,IN xEventHandler *clientHandle){};
		virtual void Ondata(int socketfd,char*data,int len)=0;
		virtual void Onclose(int socketfd){};
	};
	class xReceiveback :public xReceivebackbase,public xEventHandler
	{
	public:
		//virtual void Onopen(int socketfd,char*date,int len,IN xEventHandler *clientHandle){};
		virtual void Ondata(int socketfd,char*data,int len)=0;
		virtual void Onclose(int socketfd){};
		virtual handle_t GetHandler()const
		{
			//return m_Eventfd;
			return 0;
		}
		virtual void HandleRead(int listentfd,xEventDemultiplexer*demultiplex)
		{
			char buf[MAXREADSIZE]={0};
			int len=MAXREADSIZE;
			int iret = ReadSocket(listentfd,buf,len);
			len=sizeof(buf);
			if(iret==0)
			{
				CloseSocket(listentfd);
				//ShutDownSocket(listentfd,0);
				this->Onclose(listentfd);
				if(demultiplex!=NULL)
					demultiplex->UnrequestEvent(listentfd);
				//CloseSocket(listentfd);
			}
			else if(iret>=0)
				this->Ondata(listentfd,buf,iret);
			else
				return ;
		}
		//virtual void  Ondata(int socketfd,char*data,int len){};

	};
}