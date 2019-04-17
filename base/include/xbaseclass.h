#pragma once
#include <map>
#include <vector>
#include "xtimeheap.h"
namespace SEABASE
{

//event_t �¼�����, ֧����������
typedef unsigned int event_t;
//handle_t ����������socket
typedef int handle_t;
	enum{
		xReadEvent    =0x01,
		xWriteEvent   =0x02,
		xErrorEvent   =0x04,
		xEventMask    =0xff
};

class xEventDemultiplexer;

typedef void (*preadptr)(int sockfd,xEventDemultiplexer*Demultiplexer,void *arg);
//�¼������������
class xEventHandler
{
public:
	xEventHandler():preadptr(NULL){}
	virtual~xEventHandler(){}
	// ��ȡ��Ҫע����׽��ֻ��������ļ�������
	virtual handle_t GetHandler()const = 0;
	virtual void HandleRead(int listentfd,xEventDemultiplexer*demultiplex){}
	virtual void HandlerWrite(){}
	virtual void HandlerError(){}
	preadptr m_readptr;
	handle_t m_Eventfd; //ע���¼�ʱ����Ӧ��fd.���������ͬʱҪע����fd����ô��Ҫ�޸�m_EventfdΪ��Ӧ��fd.
};
// �ַ���ʵ�֣�IO���÷���ʱ��Ļ��ƣ�

class xEventDemultiplexer
{
public:
	virtual ~xEventDemultiplexer(){}
	//�������ȴ��¼�����
	virtual int WaitEvents(int timeout=1,xtime_heap* event_timer=NULL )=0;
	virtual int RequestEvent(handle_t handle,event_t evt,xEventHandler*peventhandler)=0;


	virtual int UnrequestEvent(handle_t handle)=0;
	std::map<handle_t,xEventHandler*> m_handlers;
};
class Noncopyable
{
protected:
	Noncopyable(){};
	~Noncopyable(){};
private:
	Noncopyable(const Noncopyable&){};
	Noncopyable& operator=(const Noncopyable&){};
};
class sockfdHandle
{
public:
	virtual ~sockfdHandle(){};
	virtual int getSockfd()=0;
};
}

#ifndef WIN32
	#define LONGLONG long long
#endif