#include "xEtcpserver.h"
using namespace SEABASE;

int xEtcpListen::startlisten(const char*ip,int port)
{
	InitSocket();
	m_listenFd = CreateSocket(SOCK_STREAM);
	bool bReuseaddr=TRUE;
	setsockopt(m_listenFd,SOL_SOCKET,SO_REUSEADDR,(const char*)&bReuseaddr,sizeof(bool));
	if(m_listenFd==INVALID_SOCKET)
		return -1;
	struct sockaddr_in addrsvr;
	addrsvr.sin_family = AF_INET;
	addrsvr.sin_port = htons(port);
	addrsvr.sin_addr.s_addr = inet_addr(ip);
	BindSocket(m_listenFd,(SOCKADDR*)&addrsvr,sizeof(addrsvr));
	if(ListenSocket(m_listenFd,10)==INVALID_SOCKET)
		return -1;
	return m_listenFd;
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

	int listenfd = m_tcplistener.startlisten(ip,port);
	//m_tcpreactor = reactor;
	//m_tcpreactor->Register
	return listenfd;
}
int xtcpserver::stopTcpSvr()
{
	m_tcplistener.stoplisten();
	return 0;
}
int xtcpserver::getListenfd()
{
	 return m_tcplistener.getSockfd();
}