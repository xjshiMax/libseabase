// tcpclient.cpp : 定义控制台应用程序的入口点。
//



#include "xNetdata.h"
#include "xEtcpclient.h"
#include "xReactor.h"
#pragma comment(lib,"../../output/lib/windows/libseabase.lib")
using namespace SEABASE;

class databack:public xReceivebackbase
{
public:
	void Init()
	{
		int iret=m_client.connectTCP("192.168.1.103",60000);
		if(iret==-1)exit(0);
		int Eventfd=m_client.getSockfd();
		m_reactor.RegisterHandler(this,Eventfd,datatype::TcpDataCallback); 
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

