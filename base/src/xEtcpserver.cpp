#include "xEtcpserver.h"
using namespace SEABASE;

int xEtcpListen::startlisten(const char*ip,int port)
{
	InitSocket();
	m_listenFd = CreateSocket(SOCK_STREAM);
	if(m_listenFd==INVALID_SOCKET)
		return -1;
	struct sockaddr_in addrsvr;
	addrsvr.sin_family = AF_INET;
	addrsvr.sin_port = htons(port);
	addrsvr.sin_addr.s_addr = inet_addr(ip);
	BindSocket(m_listenFd,(SOCKADDR*)&addrsvr,sizeof(addrsvr));
	if(ListenSocket(m_listenFd,10)==INVALID_SOCKET)
		return -1;
	return 0;
}
xtcpserver::xtcpserver():m_tcpreactor(NULL)
{

}
xtcpserver::~xtcpserver()
{

}
int xEtcpListen::stoplisten()
{
	return CloseSocket(m_listenFd);
}
int xEtcpListen::getSockfd()
{
	return m_listenFd;
}

int xtcpserver::startTcpSvr(const char*ip,int port)
{
	m_tcplistener.startlisten(ip,port);
	//m_tcpreactor = reactor;
	//m_tcpreactor->Register
	return 0;
}
int xtcpserver::stopTcpSvr()
{
	return 0;
}

void xtcpserver::HandleRead(int listentfd,xEventDemultiplexer*demultiplex)
{
	if(listentfd==m_tcplistener.getSockfd())
	{

		struct sockaddr_in clientaddr;
		socklen_t socklen=sizeof(struct sockaddr_in);
		int acceptfd=AccpetSocket(m_tcplistener.getSockfd(),(SOCKADDR*)&clientaddr,&socklen);
		if((SOCKET)acceptfd==INVALID_SOCKET)
			return ;
		xEventHandler * pclientEvent=NULL;
		//this->Onopen(acceptfd,NULL,0,pclientEvent);

	}
	else
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
}