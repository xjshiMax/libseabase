//2018-12-17
/*
��װ����tcpserver base
1) �̳и��ָ࣬�� ip��port ����xreactor���Ϳ�����������������״̬����ȡ���ݡ�
2�����Ժ������¼�����ϣ��ﵽ�����ֻ����������ȫ�������µ��¼�����ȥ��ɡ�
3��
*/
#pragma once
#include "xReactor.h"
#include "xbaseclass.h"
#include "basesock.h"
namespace SEABASE{
//һ������ȡ8k�ֽڡ�
#define MAXREADSIZE		1024*8

class xTcpServerBase:public xEventHandler
{
public:
	int startTCPServer(xReactor* xreacotr,const char* ip,int port);
	int stop();
	//���Ҫ����client���¼���Ӧ����д��Ϊ������xEventHandler������ʵ��������Onaccept��clientHandle��ֵ��
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