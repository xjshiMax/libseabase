#pragma once
#include <map>
#include <vector>
#include "xtimeheap.h"
namespace SAEBASE
{

//event_t 事件类型, 支持以下四种
typedef unsigned int event_t;
//handle_t 描述符，如socket
typedef int handle_t;
	enum{
		xReadEvent    =0x01,
		xWriteEvent   =0x02,
		xErrorEvent   =0x04,
		xEventMask    =0xff
};

//事件处理基类句柄，
class xEventHandler
{
public:
	// 获取需要注册的套截字或者其他文件描述符
	virtual handle_t GetHandler()const = 0;
	virtual void HandleRead(int listentfd){}
	virtual void HandlerWrite(){}
	virtual void HandlerError(){}
	handle_t m_Eventfd; //注册事件时，对应的fd.如果派生类同时要注册多个fd，那么需要修改m_Eventfd为对应的fd.
};

// 分发器实现（IO复用分离时间的机制）

class xEventDemultiplexer
{
public:
	virtual ~xEventDemultiplexer(){}
	//分离器等待事件到来
	virtual int WaitEvents(std::map<handle_t,xEventHandler*>*handlers,
		int timeout=0,xtime_heap* event_timer=NULL )=0;
	virtual int RequestEvent(handle_t handle,event_t evt)=0;


	virtual int UnrequestEvent(handle_t handle)=0;
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
}

#ifndef WIN32
	#define LONGLONG long long
#endif