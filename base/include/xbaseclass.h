#pragma once
#include <map>
#include <vector>
#include "xtimeheap.h"
#include "link_queue.h"
namespace SEABASE
{

//event_t 事件类型, 支持以下四种
typedef unsigned int event_t;
//handle_t 描述符，如socket
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
	//注册事件结构体
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
	unsigned int m_eventmask;		//读写，错误事件
	unsigned int m_accept;//是否是新连接 0:需要accpet,1不需要accpet
	unsigned int m_instance;//事件是否过期,过期事件不处理，并且从socket从集合移除 0:正常，1：过期
	unsigned int m_posted; //是否已经处理 0:未处理，1处理过
	handle_t m_eventback;	//返回事件类型
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
	//分离器等待事件到来
	virtual int WaitEvents(int timeout=1,xtime_heap* event_timer=NULL )=0;
	virtual int RequestEvent(xEvent_t&xevent)=0;


	virtual int UnrequestEvent(handle_t handle)=0;
	std::map<handle_t,xEvent_t> m_handlers;
};

//事件处理基类句

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