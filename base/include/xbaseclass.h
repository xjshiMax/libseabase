#pragma once
#include <map>
#include <vector>
#include "xtimeheap.h"
#include "link_queue.h"
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
		xTimeEvent    =0x08,
		xSignalEvent  =0x10,
		xEventMask    =0xff
};

class xEventDemultiplexer;
struct xEvent;
typedef void (*pcallbackptr)(xEvent*ev);
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
		m_accept= 0;
		m_instance = 0;
		m_eventback = 0;
	}
	handle_t m_Eventfd;
	unsigned int m_eventmask;		//��д�������¼�
	unsigned int m_accept;//�Ƿ��������� 0:��Ҫaccpet,1����Ҫaccpet
	unsigned int m_instance;//�¼��Ƿ����,�����¼����������Ҵ�socket�Ӽ����Ƴ� 0:������1������
	unsigned int m_posted; //�Ƿ��Ѿ����� 0:δ����1�����
	handle_t m_eventback;	//�����¼�����
	pcallbackptr m_readptr;
	pcallbackptr m_writeptr;
	pcallbackptr m_errorptr;

	void*	 m_readarg;
	void*	 m_writearg;
	void*	 m_errorarg;
	/* the posted queue */
	link_queue_t      equeue;
	xEventDemultiplexer* m_distributor;
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

class Noncopyable
{
protected:
	Noncopyable(){};
	~Noncopyable(){};
private:
	Noncopyable(const Noncopyable&);
	Noncopyable& operator=(const Noncopyable&);
};

class xReceivebackbase
{
public:
	xReceivebackbase(){};
	virtual ~xReceivebackbase(){}

	virtual void Ondata(int socketfd,char*data,int len)=0;
	virtual void Onclose(int socketfd)=0;
};
// extern link_queue_t g_accept_events;
// extern link_queue_t g_rd_event;
}

#ifndef WIN32
	#define LONGLONG long long
#endif