//xjshi 2019/3/13
//重构hpp
#include "xEventDemultiplexer.h"
using namespace SEABASE;
extern link_queue_t g_accept_events;
extern link_queue_t g_rd_event;
#ifndef WIN32
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
int xEpollDemultiplexer::WaitEvents( int timeout/* =0 */,xtime_heap* event_timer/* =NULL */ )
{
	std::vector<epoll_event> ep_events(m_fd_num);
	int num = epoll_wait(m_epoll_fd,&ep_events[0],ep_events.size(),timeout);
	if(num > 0)
	{
		for(int idx = 0;idx<num;++idx)
		{
			//int handle = ep_events[idx].data.fd;
			xEvent_t* ev = (xEvent_t*)ep_events[idx].data.ptr;
			//这里需要添加事件的过期判断	。 
			if(ev==NULL||ev->m_instance!=0)
			{
				continue;
			}

			if(ep_events[idx].events & EPOLLERR || (ep_events[idx].events & EPOLLHUP))
			{
				ev->m_eventback = xErrorEvent;
			}
			else
			{
				if(ep_events[idx].events & EPOLLIN)
				{
						ev->m_eventback = xReadEvent;
				}
				if(ep_events[idx].events & EPOLLOUT)
				{
					ev->m_eventback = xWriteEvent;
				}
			}
			link_queue_insert_tail(&g_rd_event,&ev->equeue);
		}

	}
	if(event_timer !=NULL)
	{
		event_timer->tick();
	}
	return num;
}

int xEpollDemultiplexer::RequestEvent(xEvent_t&e)
{
	epoll_event ep_event;
	//ep_event.data.fd = e.m_Eventfd;
	int handle = e.m_Eventfd;
	e.m_distributor = this;
	std::map<handle_t,xEvent_t>::iterator it = m_handlers.find(handle);
	if(it==m_handlers.end())
	{
		m_handlers[handle]=e;
	}
	ep_event.data.ptr = &m_handlers[handle];	   //记录整个指针
	ep_event.events = 0;
	if(e.m_eventmask &xReadEvent ) //	 读事件
	{
		ep_event.events |= EPOLLIN;
	}
	if(e.m_eventmask&xWriteEvent) // 写事件
	{
		ep_event.events |=EPOLLOUT;
	}
	if(epoll_ctl(m_epoll_fd,EPOLL_CTL_MOD,e.m_Eventfd,&ep_event)!=0)
	{
		if(errno ==ENOENT)
		{
			if(epoll_ctl(m_epoll_fd,EPOLL_CTL_ADD,e.m_Eventfd,&ep_event)!=0)
			{
				return -errno;
			}
			++m_fd_num;
		}
	}
// 	int handle = e.m_Eventfd;
// 	std::map<handle_t,xEvent_t>::iterator it = m_handlers.find(handle);
// 	if(it==m_handlers.end())
// 	{
// 		m_handlers[handle]=e;
// 	}
//	ep_event.data.ptr = &e;	   //记录整个指针
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
	std::map<handle_t,xEvent_t>::iterator it = m_handlers.find(handle);
	if(it==m_handlers.end())
	{
		m_handlers.erase(handle);
	}
}

#endif
