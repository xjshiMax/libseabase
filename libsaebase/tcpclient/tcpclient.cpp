// tcpclient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "xNetdata.h"
#include "xEtcpclient.h"
#include "xReactor.h"
using namespace SEABASE;

class databack:public xReceiveback
{
public:
	void Init()
	{
		int iret=m_client.connectTCP("192.168.1.104",60000);
		if(iret==-1)exit(0);
		m_Eventfd=m_client.getSockfd();
		m_reactor.RegisterHandler(this,xReadEvent); 
		m_reactor.start();
	}
	virtual void Ondata(int socketfd,char*data,int len)
	{
		printf("i receive a message:%s\nlen=%d\n",data,len);
	}
	virtual void Onclose(int socketfd){
		printf("server close,i am so sad\n");
	};
	xReactor m_reactor;
	ExTcpClient m_client;
};
int main(int argc, char* argv[])
{
	databack tcpclient;
	tcpclient.Init();
	return 0;
}

