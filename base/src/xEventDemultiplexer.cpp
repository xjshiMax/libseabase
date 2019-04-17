//xjshi 2019/3/13
//�ع�hpp
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

//��ʱΪ0,���������������أ�timeout��λ ms.
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
				m_handlers[handle]->HandlerError();
			}
			else
			{
				if(ep_events[idx].events & EPOLLIN)
				{
					//(*handlers)[handle]->HandleRead(handle,this);
					if(m_handlers[handle]->m_readptr)
					{
						m_handlers[handle]->m_readptr(handle,this,(void*)m_handlers[handle]);
					}
				}
				if(ep_events[idx].events & EPOLLOUT)
				{
					m_handlers[handle]->HandlerWrite();
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
	if(evt &xReadEvent ) //	 ���¼�
	{
		ep_event.events |= EPOLLIN;
	}
	if(evt&xWriteEvent) // д�¼�
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
	std::map<handle_t,xEventHandler*>::iterator it = m_handlers.find(handle);
	if(it==m_handlers.end())
	{
		m_handlers[handle]=peventhandler;
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
	std::map<handle_t,xEventHandler*>::iterator it = m_handlers.find(handle);
	if(it!=m_handlers.end())
	{
		m_handlers.erase(handle);
	}
}

#endif
