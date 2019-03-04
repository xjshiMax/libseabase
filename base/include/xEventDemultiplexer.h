//2018/12/11
// 分发器实现（IO复用分离时间的机制）
#pragma once
#include "xbaseclass.h"
#include "xtimeheap.h"
#ifndef WIN32
#include<sys/epoll.h>
#include <unistd.h>
#endif
#include <errno.h>
namespace SAEBASE{
//epoll IO复用实现分离器
///
/*
			epoll_create()
				|
			   \|/
	fd-----> epoll_ctl(epoll_fd,EPOLL_CTL_ADD,max_epoll_size,epll_event_set)
				|
				|
			 epoll_wait()
				|-------------> event_handler()
	
*/
///
class xEpollDemultiplexer:public xEventDemultiplexer
{
public:
	xEpollDemultiplexer();
	virtual ~xEpollDemultiplexer();
	virtual int WaitEvents(std::map<handle_t,xEventHandler*>*handlers,
		int timeout=0,xtime_heap* event_timer=NULL );
	//添加或则修改文件描述符的注册事件信息
	virtual int RequestEvent(handle_t handle,event_t evt);


	virtual int UnrequestEvent(handle_t handle);
private:
	int m_epoll_fd;  //epoll_creat 返回的描述符
	int m_fd_num;	  // 当前加入集合的描述符数量
};

xEpollDemultiplexer::xEpollDemultiplexer()
{
	m_epoll_fd=::epoll_create(FD_SETSIZE);
	//assert(m_epoll_fd!=-1);
	m_fd_num=0;
}
xEpollDemultiplexer::~xEpollDemultiplexer()
{
	::close(m_epoll_fd);
}

//超时为0,则不阻塞，立即返回，timeout单位 ms.
int xEpollDemultiplexer::WaitEvents(std::map<handle_t,xEventHandler*>*handlers, int timeout/* =0 */,
	xtime_heap* event_timer/* =NULL */ )
{
	std::vector<epoll_event> ep_events(m_fd_num);
	int num = epoll_wait(m_epoll_fd,&ep_events[0],ep_events.size(),timeout);
	if(num > 0)
	{
		for(int idx = 0;idx<num;++idx)
		{
			handle_t handle = ep_events[idx].data.fd;

			if(ep_events[idx].events & EPOLLERR || (ep_events[idx].events & EPOLLHUP))
			{
				(*handlers)[handle]->HandlerError();
			}
			else
			{
				if(ep_events[idx].events & EPOLLIN)
				{
					(*handlers)[handle]->HandleRead(handle);
				}
				if(ep_events[idx].events & EPOLLOUT)
				{
					(*handlers)[handle]->HandlerWrite();
				}
			}
		}
		
	}
	if(event_timer !=NULL)
	{
		event_timer->tick();
	}
	return num;
}

int xEpollDemultiplexer::RequestEvent(handle_t handle,event_t evt)
{
	epoll_event ep_event;
	ep_event.data.fd = handle;
	ep_event.events = 0;
	if(evt &xReadEvent ) //	 读事件
	{
		ep_event.events |= EPOLLIN;
	}
	if(evt&xWriteEvent) // 写事件
	{
		ep_event.events |=EPOLLOUT;
	}
	if(epoll_ctl(m_epoll_fd,EPOLL_CTL_MOD,handle,&ep_event)!=0)
	{
		if(errno ==ENOENT)
		{
			if(epoll_ctl(m_epoll_fd,EPOLL_CTL_ADD,handle,&ep_event)!=0)
			{
				return -errno;
			}
			++m_fd_num;
		}
	}
	return 0;
}

 int xEpollDemultiplexer::UnrequestEvent(handle_t handle)
{
	epoll_event ep_event;
	if(epoll_ctl(m_epoll_fd,EPOLL_CTL_DEL,handle,&ep_event)!=0)
	{
		return -errno;
	}
	--m_fd_num;
}
 }