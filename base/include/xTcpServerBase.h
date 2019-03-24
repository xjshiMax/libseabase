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
namespace SEABASE{
//一次最大读取8k字节。
#define MAXREADSIZE		1024*8

class xTcpServerBase:public xEventHandler
{
public:
	int startTCPServer(xReactor* xreacotr,const char* ip,int port);
	int stop();
	//如果要设置client的事件响应（读写）为单独的xEventHandler派生类实例，则在Onaccept给clientHandle赋值。
	virtual int Onaccept(int socketfd,char*data,int len,IN xEventHandler **clientHandle=NULL);
	virtual int Ondata(int socketfd,char*date,int len);
	virtual int Onclose(int socketfd);
	int SendMsg(int peerfd,char*buf,int len);
	bool GetLocalInfo(IN int socket,OUT char*ip,OUT int &port)
	{
		return getLocalInfo(socket,ip,port);
	}
	bool GetPeerInfo(IN int socket,OUT char*ip,OUT int &port)
	{
		return getPeerInfo(socket,ip,port);
	}
	int getListenHandle()const
	{
		return m_listenfd;
	}
public:
	virtual handle_t GetHandler()const;
	virtual void HandleRead(int listentfd,xEventDemultiplexer*demultiplex);
	virtual void HandlerWrite(){}
	virtual void HandlerError(){}
private:
	handle_t m_listenfd;
	handle_t m_acceptfd;
	xReactor* m_reactor;
};


}