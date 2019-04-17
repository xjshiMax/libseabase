#include "xNetdata.h"
using namespace SEABASE;

void Eventcallback::AcceptCallback(int sockfd,xEventDemultiplexer*Demultiplexer,void *arg)
{
	struct sockaddr_in clientaddr;
	socklen_t socklen=sizeof(struct sockaddr_in);
	int acceptfd=AccpetSocket(sockfd,(SOCKADDR*)&clientaddr,&socklen);
	if((SOCKET)acceptfd==INVALID_SOCKET)
		return ;
	xEventHandler * pclientEvent=NULL;
	xtcpserver*pserver = (xEventHandler*)arg;
	if(!pserver)	return ;
	pserver->Onaccept(acceptfd,NULL,0,&pclientEvent);
	//m_Eventfd=acceptfd;
	if(pclientEvent)  //ÕâÀï×¢²áacceptµÄfd,
	{
		if(pclientEvent==NULL)
		{
			//pserver->m_readptr=DataCallback;

			Demultiplexer->RequestEvent(acceptfd,xReadEvent,pclientEvent);
		}
		else
		{
			pclientEvent->m_Eventfd=acceptfd;
			pclientEvent->m_readptr=DataCallback;
			//reactor->RegisterHandler(pclientEvent,xReadEvent,acceptfd);
			Demultiplexer->RequestEvent(acceptfd,xReadEvent,pclientEvent);
		}
		//m_reactor->RegisterHandler(pclientEvent,xReadEvent);
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
