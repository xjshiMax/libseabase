#include "xEtcpclient.h"
using namespace  SEABASE;

int ExTcpClient::connectTCP(char*serverip,int serverport)
{
	strcpy(m_serverip,serverip);
	m_serverport=serverport;
	struct sockaddr_in tcpddr;
	tcpddr.sin_family=AF_INET;
	tcpddr.sin_addr.s_addr=inet_addr(m_serverip);
	tcpddr.sin_port=htons(m_serverport);
	return ConnectSocket(m_sockfd,(sockaddr*)&tcpddr,sizeof(struct sockaddr_in));
}
int ExTcpClient::recieve(char* buf,int len)
{
	return ReadSocket(m_sockfd,buf,len,0);

}
int ExTcpClient::sendMsg(char*buf,int len)
{
	return SendSocket(m_sockfd,buf,len);
}
int ExTcpClient::close()
{
	return CloseSocket(m_sockfd);
}