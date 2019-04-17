//xjshi 2019/3/13 
//重构hpp xReacotr.cpp

#include "xReactor.h"
using namespace SEABASE;
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
int xReactor::RegisterHandler(xReceivebackbase*handler,SEABASE::handle_t&sockfd)
{
	return m_reactorimp->RegisterHandler(handler,sockfd);
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


int xReactorImplentation::RegisterHandler(xReceivebackbase*handler,SEABASE::handle_t&sockfd)
{
	xEvent_t e;
	Eventcallback::InitEvent(e,sockfd,handler,Eventcallback::AcceptCallback);
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

	}
}
