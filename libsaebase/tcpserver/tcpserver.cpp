// tcpserver.cpp : 定义控制台应用程序的入口点。
//
#include "xEtcpserver.h"
#include "xReactorwithThread.h"
#include <stdio.h>
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
        static int i=0;
		printf("%s %d\n",data,i++);
        SendSocket(socketfd,"hello!\n",7);
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
	int listenfd = mytcp.startTcpSvr("172.28.71.53",8000);

	reactor.RegisterHandler(&mytcp,listenfd);
	reactor.start();
	//reactor.join();
	return 0;
}

