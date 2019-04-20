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
typedef void (*pcallbackptr)(int sockfd,xEventDemultiplexer*Demultiplexer,void *arg);
	//ע���¼��ṹ��
typedef struct xEvent{
	xEvent()
	{
		reset();
	}
	void reset()
	{
		m_Eventfd=-1;
		m_eventmask=xEventMask;
		m_readptr=NULL;
		m_writeptr=NULL;
		m_errorptr=NULL;
		m_readarg=NULL;
		m_writearg=NULL;
		m_errorarg=NULL;
	}
	handle_t m_Eventfd;
	unsigned int m_eventmask;		//��д�������¼�
	pcallbackptr m_readptr;
	pcallbackptr m_writeptr;
	pcallbackptr m_errorptr;

	void*	 m_readarg;
	void*	 m_writearg;
	void*	 m_errorarg;
}xEvent_t;

class xEventDemultiplexer
{
public:
	virtual ~xEventDemultiplexer(){}
	//�������ȴ��¼�����
	virtual int WaitEvents(int timeout=1,xtime_heap* event_timer=NULL )=0;
	virtual int RequestEvent(xEvent_t&xevent)=0;


	virtual int UnrequestEvent(handle_t handle)=0;
	std::map<handle_t,xEvent_t> m_handlers;
};

//�¼���������


// class xEventHandler
// {
// public:
// 	xEventHandler():preadptr(NULL),callbackhandle(this){}
// 	virtual~xEventHandler(){}
// 	// ��ȡ��Ҫע����׽��ֻ��������ļ�������
// 	virtual handle_t GetHandler()const = 0;
// 	virtual void HandleRead(int listentfd,xEventDemultiplexer*demultiplex){}
// 	virtual void HandlerWrite(){}
// 	virtual void HandlerError(){}
// 	pcallbackptr m_readptr;
// 	handle_t m_Eventfd; //ע���¼�ʱ����Ӧ��fd.���������ͬʱҪע����fd����ô��Ҫ�޸�m_EventfdΪ��Ӧ��fd.
// 	xEventHandler* callbackhandle;
// };
// �ַ���ʵ�֣�IO���÷���ʱ��Ļ��ƣ�

class Noncopyable
{
protected:
	Noncopyable(){};
	~Noncopyable(){};
private:
	Noncopyable(const Noncopyable&){};
	Noncopyable& operator=(const Noncopyable&){};
};

class xReceivebackbase
{
public:
	xReceivebackbase(){};
	virtual ~xReceivebackbase(){}

	virtual void Ondata(int socketfd,char*data,int len)=0;
	virtual void Onclose(int socketfd)=0;
};

}

#ifndef WIN32
	#define LONGLONG long long
#endif