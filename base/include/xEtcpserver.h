//2019/3/22
//easy listen tcp
//tcp服务类，面向对象，定义对象即可调用。
//结合callback 接收数据
#pragma once
#include<string>
#include "basesock.h"
#define _IS_NEED_CALLBACK
#ifdef _IS_NEED_CALLBACK
#include "xbaseclass.h"
#endif
#include "xNetdata.h"
#include "xReactor.h"
using namespace std;
namespace SEABASE{

	class xEtcpListen:public sockfdHandle
	{
	public:
		int startlisten(const char*ip,int port);
		int stoplisten();
		virtual int getSockfd();
	private:
		int m_listenFd;
		string m_listenIp;
		int m_listenPort;
	};
	class xtcpserver:public xReceiveback
	{
	public:
		xtcpserver();
		~xtcpserver();
		int startTcpSvr(const char*ip,int port);
		int stopTcpSvr();
	protected:
		virtual void HandleRead(int listentfd,xEventDemultiplexer*demultiplex);

	private:
		xEtcpListen m_tcplistener;
		xReactor* m_tcpreactor;
	};
}