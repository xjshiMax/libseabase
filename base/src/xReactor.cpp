//xjshi 2019/3/13 
//重构hpp xReacotr.cpp

#include "xReactor.h"
using namespace std;
xReactor::xReactor()
{
	m_reactorimp = new xReactorImplentation();

}
xReactor::~xReactor()
{
	if(m_reactorimp!=NULL)
	{
		delete m_reactorimp;
		m_reactorimp=NULL;
	}
}
int xReactor::RegisterHandler(xEventHandler*handler,event_t event_)
{
	return m_reactorimp->RegisterHandler(handler,event_);
}

int xReactor::RemoveHandler(xEventHandler* handler)
{
	return m_reactorimp->RemoveHandler(handler);
}
int xReactor::RemoveHandlerbyfd(handle_t handlefd)
{
	return m_reactorimp->RemoveHandlerbyfd(handlefd);
}
void xReactor::HandlerEvents()
{
	m_reactorimp->StartLoop();
}
int xReactor::RegisterTimeTask(xheaptimer* timerevent)
{
	m_reactorimp->RegisterTimeTask(timerevent);
	return 0;
}

int xReactorImplentation::RegisterHandler(xEventHandler*handler,event_t event_)
{
	handle_t handle = handler->GetHandler();
	std::map<handle_t,xEventHandler*>::iterator it = m_handlers.find(handle);
	if(it == m_handlers.end())
	{
		m_handlers[handle] = handler;
	}
	return m_demultiplexer->RequestEvent(handle,event_);
}
int xReactorImplentation::RemoveHandler(xEventHandler* handler)
{
	handle_t handle =handler->GetHandler();
	m_handlers.erase(handle);
	return m_demultiplexer->UnrequestEvent(handle);
}
int xReactorImplentation::RemoveHandlerbyfd(handle_t handlefd)
{
	std::map<handle_t,xEventHandler*>::iterator it = m_handlers.find(handlefd);
	if(it==m_handlers.end())
		return -1;
	m_handlers.erase(handlefd);
	return m_demultiplexer->UnrequestEvent(handlefd);
}
//这里添加事件循环，
//添加start
void xReactorImplentation::HandlerEvents()
{
	while(!_bIsstop)
	{
		int timeout = 0;
		if(m_eventtimer->top() ==NULL)
		{
			timeout = 0;
		}
		else
		{
			timeout = (m_eventtimer->top()->expire-time(NULL))*1000;
		}
		if(m_demultiplexer==NULL)
			return;
		m_demultiplexer->WaitEvents(&m_handlers,timeout,m_eventtimer);

	}
}
int xReactorImplentation::RegisterTimeTask(xheaptimer* timerevent)
{
	if(timerevent == NULL)
		return -1;
	m_eventtimer->add_timer(timerevent);
	return 0;
}
