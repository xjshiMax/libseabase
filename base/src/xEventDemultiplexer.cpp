//xjshi 2019/3/13
//重构hpp
#include "xEventDemultiplexer.h"
using namespace SEABASE;
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
			handle_t handle = ep_events[idx].data.fd;

			if(ep_events[idx].events & EPOLLERR || (ep_events[idx].events & EPOLLHUP))
			{
				if(m_handlers[fd].m_errorptr)
				{
					m_handlers[fd].m_errorptr(fd,this,(void*)m_handlers[fd].m_errorarg);
				}
			}
			else
			{
				if(ep_events[idx].events & EPOLLIN)
				{
					//(*handlers)[handle]->HandleRead(handle,this);
					if(m_handlers[fd].m_readptr)
					{
						m_handlers[fd].m_readptr(fd,this,(void*)m_handlers[fd].m_readarg);
					}
				}
				if(ep_events[idx].events & EPOLLOUT)
				{
					if(m_handlers[fd].m_writeptr)
					{
						m_handlers[fd].m_writeptr(fd,this,(void*)m_handlers[fd].m_writearg);
					}
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

int xEpollDemultiplexer::RequestEvent(xEvent_t&e)
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
	int handle = e.m_Eventfd;
	std::map<handle_t,xEvent_t>::iterator it = m_handlers.find(handle);
	if(it==m_handlers.end())
	{
		m_handlers[handle]=e;
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
	std::map<handle_t,xEvent_t>::iterator it = m_handlers.find(handle);
	if(it==m_handlers.end())
	{
		m_handlers.erase(handle);
	}
}

#endif
