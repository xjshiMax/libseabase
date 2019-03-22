#include "xEtcpserver.h"
using namespace SEABASE;

int xEtcpListen::startlisten(const char*ip,int port)
{
	InitSocket();
	m_listenFd = CreateSocket(SOCK_STREAM);
	if(m_Eventfd==INVALID_SOCKET)
		return -1;
	struct sockaddr_in addrsvr;
	addrsvr.sin_family = AF_INET;
	addrsvr.sin_port = htons(port);
	addrsvr.sin_addr.s_addr = inet_addr(ip);
	BindSocket(m_Eventfd,(SOCKADDR*)&addrsvr,sizeof(addrsvr));
	if(ListenSocket(m_Eventfd,10)==INVALID_SOCKET)
		return -1;
	return 0;
}
int xEtcpListen::stoplisten()
{
	CloseSocket(m_listenFd);
}
int xEtcpListen::getSockfd()
{
	return m_listenFd;
}