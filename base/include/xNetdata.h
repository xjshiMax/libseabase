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

	class xItcpserver:public xReceivebackbase
	{
	public:
		virtual int Onaccept(int socketfd,char*data,int len,IN xReceivebackbase**clientHandle=NULL)=0;
		virtual void Ondata(int socketfd,char*date,int len){return ;};
		virtual void Onclose(int socketfd){return ;};
	};
	class Eventcallback
	{
	public:
		static void InitEvent(xEvent_t& e, SOCKET sock, void *arg,pcallbackptr func);
		static void AcceptCallback(int sockfd,xEventDemultiplexer*Demultiplexer,void *arg);
		static void DataCallback(int sockfd,xEventDemultiplexer*Demultiplexer,void *arg);
		static void ErrCallback(int sockfd,xEventDemultiplexer*Demultiplexer,void *arg);
	};
	//class xReceivebackbase
	//{
	//public:
	//	xReceivebackbase(){};
	//	virtual ~xReceivebackbase(){}
	//	/*
	//	����onopen ��һ��xEventHandler Ϊ����������������Խ��������ഫ�룬ע����յ���fd
	//	*/
	//	//virtual void Onopen(int socketfd,char*date,int len,IN xEventHandler *clientHandle){};
	//	virtual void Ondata(int socketfd,char*data,int len)=0;
	//	virtual void Onclose(int socketfd){};
	//};
	//class xReceiveback :public xReceivebackbase,public xEventHandler
	//{
	//public:
	//	//virtual void Onopen(int socketfd,char*date,int len,IN xEventHandler *clientHandle){};
	//	virtual void Ondata(int socketfd,char*data,int len)=0;
	//	virtual void Onclose(int socketfd){};
	//	virtual handle_t GetHandler()const
	//	{
	//		//return m_Eventfd;
	//		return 0;
	//	}
	//	virtual void HandleRead(int listentfd,xEventDemultiplexer*demultiplex)
	//	{
	//		char buf[MAXREADSIZE]={0};
	//		int len=MAXREADSIZE;
	//		int iret = ReadSocket(listentfd,buf,len);
	//		len=sizeof(buf);
	//		if(iret==0)
	//		{
	//			CloseSocket(listentfd);
	//			//ShutDownSocket(listentfd,0);
	//			this->Onclose(listentfd);
	//			if(demultiplex!=NULL)
	//				demultiplex->UnrequestEvent(listentfd);
	//			//CloseSocket(listentfd);
	//		}
	//		else if(iret>=0)
	//			this->Ondata(listentfd,buf,iret);
	//		else
	//			return ;
	//	}
	//	//virtual void  Ondata(int socketfd,char*data,int len){};

	//};
}