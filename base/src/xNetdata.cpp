#include "xNetdata.h"
using namespace SEABASE;

void Eventcallback::InitEvent(xEvent_t& e, SOCKET sock, void *arg,pcallbackptr func,int isinstance,int isaccped)
{
	e.m_Eventfd=sock;
	e.m_eventmask=xReadEvent|xErrorEvent;
	e.m_readptr = func;
	e.m_readarg = arg;
	e.m_writearg=arg;
	//e.m_writeptr=
	e.m_errorptr=ErrCallback;
	e.m_errorarg=arg;
	e.m_instance = isinstance;
	e.m_accept = isaccped;
}
void Eventcallback::AcceptCallback(xEvent*ev)
{
	//printf("Eventcallback::AcceptCallback\n");
	struct sockaddr_in clientaddr;
	socklen_t socklen=sizeof(struct sockaddr_in);
	int sockfd = ev->m_Eventfd;
	xItcpserver*arg = (xItcpserver*)ev->m_readarg;
	int acceptfd=AccpetSocket(sockfd,(SOCKADDR*)&clientaddr,&socklen);
	if((SOCKET)acceptfd==INVALID_SOCKET)
		return ;
	xReceivebackbase * pclientEvent=NULL;
	xItcpserver*pserver = (xItcpserver*)arg;
	if(!pserver)	return ;
	pserver->Onaccept(acceptfd,NULL,0,(xReceivebackbase**)&pclientEvent);
	//允许用户在	Onaccept 修改接收数据的回调类
	//m_Eventfd=acceptfd;
	xEventDemultiplexer* distributor = (xEventDemultiplexer*)ev->m_distributor;
	if(pclientEvent)  //这里注册accept的fd,
	{
		xEvent_t e;
		InitEvent(e,acceptfd,pclientEvent,DataCallback,0,1);
		distributor->RequestEvent(e);
	}
	else if(pclientEvent==NULL)
	{
		//pserver->m_readptr=DataCallback;
		xEvent_t e;
		InitEvent(e,acceptfd,arg,DataCallback ,0,1);
		distributor->RequestEvent(e);
	}
	
	return ;
}
void Eventcallback::DataCallback(xEvent*ev)
{
	char buf[MAXREADSIZE]={0};
	int len=MAXREADSIZE;
	int sockfd = ev->m_Eventfd;
	xItcpserver*arg = (xItcpserver*)ev->m_readarg;
	xReceivebackbase*pserver = (xReceivebackbase*)arg;
	if(!pserver)	return ;
	int iret = ReadSocket(sockfd,buf,len);
	len=sizeof(buf);
	xEventDemultiplexer* distributor = (xEventDemultiplexer*)ev->m_distributor;
	if(iret==0)
	{
		CloseSocket(sockfd);
		ev->m_instance = 1;//设置过期，后续该socket的事件不处理
		if(distributor)
			distributor->UnrequestEvent(sockfd);
		//ShutDownSocket(listentfd,0);
		pserver->Onclose(sockfd);
		//CloseSocket(listentfd);
	}
	else if(iret>=0)
		pserver->Ondata(sockfd,buf,iret);
	else
		return ;
}
void Eventcallback::ErrCallback(xEvent*ev)
{

}