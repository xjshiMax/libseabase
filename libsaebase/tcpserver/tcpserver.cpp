// tcpserver.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "xEtcpserver.h"
#include "xReactorwithThread.h"
#include <vector>
using namespace std;
using namespace SEABASE;

// class session:public xReceiveback
// {
// public:
// 	virtual void Ondata(int socketfd,char*data,int len)
// 	{
// 		printf("this is in session:%s\n",data);
// 	}
// 	virtual void Onclose(int socketfd){};
// };


class tcpser :public xtcpserver
{
	virtual int Onaccept(int socketfd,char*data,int len,IN xReceivebackbase**clientHandle=NULL)
	{
		printf("get a accept\n");
//  		session *mysession=new session();
//  		*clientHandle=mysession;
//  		sessionset.push_back(mysession);
		return 0;
	}
	virtual void Ondata(int socketfd,char*data,int len)
	{
		printf("%s\n",data);
		return ;
	}
	virtual void Onclose(int socketfd)
	{
		return ;
	}
	//vector<session*> sessionset;
};
int main(int argc, char* argv[])
{
	xReactor reactor;
	tcpser mytcp;
	int listenfd = mytcp.startTcpSvr("192.168.1.101",8000);

	reactor.RegisterHandler(&mytcp,listenfd);
	reactor.start();
	//reactor.join();
	return 0;
}

