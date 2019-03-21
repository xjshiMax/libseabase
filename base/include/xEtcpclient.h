//tcp client
#pragma once
#include<string>
#include "basesock.h"
using namespace std;
namespace SEABASE{
	class ExTcpClient
	{
	public:
		ExTcpClient()
		{
			InitSocket();
			m_sockfd=CreateSocket(SOCK_STREAM);
		}

		//ExTcpClient(char* clientip,int clientport);
		int connectTCP(char*serverip,int serverport);
		int recieve(char* buf,int len);
		int sendMsg(char*buf,int len);
		int close();
		int getSockfd()
		{
			return m_sockfd;
		}
	private:
		char m_clientip[32];
		char m_serverip[32];
		int  m_clientport;
		int  m_serverport;
		int  m_sockfd;
	};
}