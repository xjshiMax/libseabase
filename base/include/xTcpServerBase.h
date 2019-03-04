//2018-12-17
/*
封装简易tcpserver base
1) 继承该类，指定 ip，port 启动xreactor，就可以正常监听，连接状态，获取数据。
2）可以和其他事件类组合，达到服务端只监听，数据全部创建新的事件对象去完成。
3）
*/
#pragma once
#include "xReactor.h"
#include "xbaseclass.h"
#include "basesock.h"
namespace SAEBASE{
//一次最大读取8k字节。
#define MAXREADSIZE		1024*8

class xTcpServerBase:public xEventHandler
{
public:
	int startTCPServer(xReactor* xreacotr,const char* ip,int port);
	int stop();
	//如果要设置client的事件响应（读写）为单独的xEventHandler派生类实例，则在Onaccept给clientHandle赋值。
	virtual int Onaccept(int socketfd,char*date,int len,IN xEventHandler *clientHandle=NULL);
	virtual int Ondata(int socketfd,char*date,int len);
	virtual int Onclose(int socketfd);
	int SendMsg(int peerfd,char*buf,int len);
	bool GetLocalInfo(IN int socket,OUT char*ip,OUT int &port)
	{
		return Network_function::getLocalInfo(socket,ip,port);
	}
	bool GetPeerInfo(IN int socket,OUT char*ip,OUT int &port)
	{
		return Network_function::getPeerInfo(socket,ip,port);
	}
	int getListenHandle()const
	{
		return m_listenfd;
	}
public:
	virtual handle_t GetHandler()const;
	virtual void HandleRead(int listentfd);
	virtual void HandlerWrite(){}
	virtual void HandlerError(){}
private:
	handle_t m_listenfd;
	handle_t m_acceptfd;
	xReactor* m_reactor;
};
//在调用startTCPServer 之后或者之前，一定要调用xReactor的start()接口，开启事件响应。
int xTcpServerBase::startTCPServer(xReactor* xreacotr,const char* ip,int port)
{
	InitSocket();
	m_Eventfd = CreateSocket(SOCK_STREAM);
	if(m_Eventfd==INVALID_SOCKET)
		return -1;
	m_listenfd = m_Eventfd;
	m_reactor = xreacotr;
	struct sockaddr_in addrsvr;
	addrsvr.sin_family = AF_INET;
	addrsvr.sin_port = htons(port);
	addrsvr.sin_addr.s_addr = inet_addr(ip);
	BindSocket(m_Eventfd,(SOCKADDR*)&addrsvr,sizeof(addrsvr));
	if(ListenSocket(m_Eventfd,10)==INVALID_SOCKET)
		return -1;
	if(m_reactor!=NULL)
		m_reactor->RegisterHandler(this,xReadEvent); // 注册写事件。
	return 0;
}
int xTcpServerBase::Onaccept(int socketfd,char*date,int len,IN xEventHandler *clientHandle)
{
	return 0;
}
int xTcpServerBase::Ondata(int socketfd,char*date,int len)
{
	return 0;
}
int xTcpServerBase::Onclose(int socketfd)
{
	return 0;
}
int xTcpServerBase::SendMsg(int peerfd,char*buf,int len)
{
	return SendSocket(peerfd,buf,len);
}
handle_t xTcpServerBase::GetHandler()const
{
	if(m_Eventfd!=INVALID_SOCKET)
		return m_Eventfd;
	return -1;
}
void xTcpServerBase::HandleRead(int listentfd)
{
	if(listentfd==m_listenfd) // 监听套接字的io事件
	{
		struct sockaddr_in clientaddr;
		socklen_t socklen=sizeof(struct sockaddr_in);
		int acceptfd=AccpetSocket(m_listenfd,(SOCKADDR*)&clientaddr,&socklen);
		if((SOCKET)acceptfd==INVALID_SOCKET)
			return ;
		xEventHandler * pclientEvent=NULL;
		this->Onaccept(acceptfd,NULL,0,pclientEvent);
		m_Eventfd=acceptfd;
		if(m_reactor)  //这里注册accept的fd,
		{
			if(pclientEvent==NULL)
				m_reactor->RegisterHandler(this,xReadEvent);
			else
			{
				pclientEvent->m_Eventfd=m_acceptfd;
				m_reactor->RegisterHandler(pclientEvent,xReadEvent);
			}
			//m_reactor->RegisterHandler(pclientEvent,xReadEvent);
		}
		return ;
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
			if(m_reactor)
				m_reactor->RemoveHandlerbyfd(listentfd);
			//ShutDownSocket(listentfd,0);
			this->Onclose(listentfd);
			//CloseSocket(listentfd);
		}
		else if(iret>=0)
			this->Ondata(listentfd,buf,iret);
		else
			return ;
	}

	return ;

}

}