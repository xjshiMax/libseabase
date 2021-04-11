//xjshi 2019/3/13 
//重构hpp xReacotr.cpp

#include "xReactor.h"
using namespace SEABASE;
using namespace std;

link_queue_t g_accept_events;
link_queue_t g_rd_event;
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
int xReactor::RegisterHandler(xReceivebackbase*handler,SEABASE::handle_t&sockfd,int type)
{
	return m_reactorimp->RegisterHandler(handler,sockfd,type);
}

// int xReactor::RemoveHandler(xEventHandler* handler)
// {
// 	return m_reactorimp->RemoveHandler(handler);
// }
int xReactor::RemoveHandlerbyfd(SEABASE::handle_t handlefd)
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


xReactorImplentation::xReactorImplentation()
{
#ifdef WIN32
	m_demultiplexer = new xSelectDemultiplexer();
#else
	m_demultiplexer = new xEpollDemultiplexer();
#endif
	//m_demultiplexer = static_cast<xEventDemultiplexer*>(new xEpollDemultiplexer());
	m_eventtimer = new xtime_heap(INITSIZE);
	link_queue_init(&g_accept_events);
	link_queue_init(&g_rd_event);
}

int xReactorImplentation::RegisterHandler(xReceivebackbase*handler,SEABASE::handle_t&sockfd,int type)
{
	xEvent_t e;
	if(type==datatype::TcpAcceptCallback)
		Eventcallback::InitEvent(e,sockfd,handler,Eventcallback::AcceptCallback);
	else if(type==datatype::TcpDataCallback)
		Eventcallback::InitEvent(e,sockfd,handler,Eventcallback::DataCallback);
	return m_demultiplexer->RequestEvent(e);
}

int xReactorImplentation::RemoveHandlerbyfd(SEABASE::handle_t handlefd)
{
	return m_demultiplexer->UnrequestEvent(handlefd);
}
//这里添加事件循环，
//添加start
void xReactorImplentation::HandlerEvents()
{
	while(!_bIsstop)
	{
		int timeout = 1;
		if(m_eventtimer->top() ==NULL)
		{
			timeout = 1;
		}
		else
		{
			timeout = (m_eventtimer->top()->expire-time(NULL))*1000;
		}
		if(m_demultiplexer==NULL)
			return;
		m_demultiplexer->WaitEvents(timeout,m_eventtimer);
		process_event(&g_rd_event);

	}
}
int xReactorImplentation::process_event(link_queue_t *posted)
{
	link_queue_t  *q;
	xEvent  *ev;

	while (!link_queue_empty(posted)){
		//printf("in process_event\n ");
		q = link_queue_head(posted);
		ev = link_queue_data(q, xEvent, equeue);
		(ev)->m_posted = 0;                                                         \
		link_queue_remove(&(ev)->equeue); 

		//ev->handler(ev);
		if(ev->m_eventback&xReadEvent && ev->m_readptr)
		{
			ev->m_readptr(ev);
		}
		else if(ev->m_eventback&xWriteEvent && ev->m_writeptr)
		{
			ev->m_writeptr(ev);
		}
		else if(ev->m_eventback&xErrorEvent && ev->m_errorptr)
		{
			ev->m_errorptr(ev);
		}
	}
	//printf("out of process_event empty=%d\n ",link_queue_empty(posted));
	return 0;
}
int xReactorImplentation::RegisterTimeTask(xheaptimer* timerevent)
{
	if(timerevent == NULL)
		return -1;
	m_eventtimer->add_timer(timerevent);
	return 0;
}
xReactor* ReactorInstance::m_reactor=NULL;