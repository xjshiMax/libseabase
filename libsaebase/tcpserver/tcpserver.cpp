// tcpserver.cpp : 定义控制台应用程序的入口点。
//

//#include "xEtcpserver.h"
#include "xTcpServerBase.h"
#include "xReactorwithThread.h"
#include "xNetdata.h"
#include <vector>
using namespace std;
using namespace SEABASE;

class session:public xReceiveback
{
public:
	virtual void Ondata(int socketfd,char*data,int len)
	{
		printf("this is in session:%s\n",data);
	}
	virtual void Onclose(int socketfd){};
};


class tcpser :public xTcpServerBase
{
	virtual int Onaccept(int socketfd,char*data,int len,IN xEventHandler **clientHandle=NULL)
	{
		printf("get a accept\n");
 		session *mysession=new session();
 		*clientHandle=mysession;
 		sessionset.push_back(mysession);
		return 0;
	}
	virtual int Ondata(int socketfd,char*data,int len)
	{
		printf("%s\n",data);
		return 0;
	}
	virtual int Onclose(int socketfd)
	{
		return 0;
	}
	vector<session*> sessionset;
};
int main(int argc, char* argv[])
{
	xReactorwithThread reactor;
	tcpser mytcp;
	mytcp.startTCPServer(&reactor,"192.168.1.104",8000);
	reactor.startReactorWithThread();
	reactor.join();
	return 0;
}

