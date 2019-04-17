#include "xNetdata.h"
using namespace SEABASE;

void Eventcallback::InitEvent(xEvent_t& e, SOCKET sock, void *arg,pcallbackptr func)
{
	e.m_Eventfd=sock;
	e.m_eventmask=xReadEvent|xErrorEvent;
	e.m_readptr = func;
	e.m_writearg=arg;
	//e.m_writeptr=
	e.m_errorptr=ErrCallback;
	e.m_errorarg=arg;
}
void Eventcallback::AcceptCallback(int sockfd,xEventDemultiplexer*Demultiplexer,void *arg)
{
	struct sockaddr_in clientaddr;
	socklen_t socklen=sizeof(struct sockaddr_in);
	int acceptfd=AccpetSocket(sockfd,(SOCKADDR*)&clientaddr,&socklen);
	if((SOCKET)acceptfd==INVALID_SOCKET)
		return ;
	xReceivebackbase * pclientEvent=NULL;
	xItcpserver*pserver = (xItcpserver*)arg;
	if(!pserver)	return ;
	pserver->Onaccept(acceptfd,NULL,0,(xReceivebackbase**)&pclientEvent);
	//m_Eventfd=acceptfd;
	if(pclientEvent)  //ÕâÀï×¢²áacceptµÄfd,
	{
		if(pclientEvent==NULL)
		{
			//pserver->m_readptr=DataCallback;
			xEvent_t e;
			InitEvent(e,acceptfd,arg,DataCallback);
			Demultiplexer->RequestEvent(e);
		}
		else
		{
			xEvent_t e;
			InitEvent(e,acceptfd,pclientEvent,DataCallback);
			Demultiplexer->RequestEvent(e);
		}
	}
	return ;
}
void Eventcallback::DataCallback(int sockfd,xEventDemultiplexer*Demultiplexer,void *arg)
{
	char buf[MAXREADSIZE]={0};
	int len=MAXREADSIZE;
	xReceivebackbase*pserver = (xReceivebackbase*)arg;
	if(!pserver)	return ;
	int iret = ReadSocket(sockfd,buf,len);
	len=sizeof(buf);
	if(iret==0)
	{
		CloseSocket(sockfd);
		if(Demultiplexer)
			Demultiplexer->UnrequestEvent(sockfd);
		//ShutDownSocket(listentfd,0);
		pserver->Onclose(sockfd);
		//CloseSocket(listentfd);
	}
	else if(iret>=0)
		pserver->Ondata(sockfd,buf,iret);
	else
		return ;
}
void Eventcallback::ErrCallback(int sockfd,xEventDemultiplexer*Demultiplexer,void *arg)
{

}