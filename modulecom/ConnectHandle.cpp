#include "ConnectHandle.h"
#include <stdlib.h>
void ConnectHandle::init()
{
	int iret=m_client.connectTCP("192.168.31.1",60000);
	if(iret==-1)exit(0);
	int Eventfd=m_client.getSockfd();
	m_reactor.RegisterHandler(this,Eventfd,datatype::TcpDataCallback); 
	m_reactor.start();
}
void ConnectHandle::Ondata(int socketfd,char*data,int len)
{

}
void ConnectHandle::Onclose(int socketfd)
{
	 	 int  Connect(string charip,int port);
}
int  ConnectHandle::Connect(string charip,int port)
{
	   	return m_client.connectTCP((char*)charip.c_str(),port);
}