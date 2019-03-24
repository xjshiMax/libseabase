//xjshi 2019/3/13
//÷ÿππhpp
#include"xDemultiplexerSelect.h"
using namespace SEABASE;

//select

xSelectDemultiplexer::xSelectDemultiplexer()
{
	m_fd_num=0;
	FD_ZERO(&m_fdReadSave);
}
xSelectDemultiplexer::~xSelectDemultiplexer()
{

}

int xSelectDemultiplexer::WaitEvents(std::map<SEABASE::handle_t,xEventHandler*>*handlers,
	int timeout,xtime_heap* event_timer )
{
	//std::vector<handle_t> m_Readevents;
	fd_set fdread;
	FD_ZERO(&fdread);
	memcpy(&fdread,&m_fdReadSave,sizeof(m_fdReadSave));
	timeval timev_;
	timev_.tv_sec=timeout/1000;
	timev_.tv_usec=0;
	int res = select( 0,  &fdread , NULL,NULL, &timev_);
	if(res>0)
	{

		for(int j=0;j<m_fdReadSave.fd_count;j++)
		{
			int fd=m_fdReadSave.fd_array[j];
			if(FD_ISSET(fd,&fdread))
			{
				(*handlers)[fd]->HandleRead(fd,this);
			}
		}

	}
	if(event_timer !=NULL)
	{
		event_timer->tick();
	}
	return 0;
}
int xSelectDemultiplexer::RequestEvent(SEABASE::handle_t handle,event_t evt)
{
	if(evt & xReadEvent)
		FD_SET((SOCKET)handle,&m_fdReadSave);
	if((int)handle > m_maxfdID)
		m_maxfdID = (int)handle +1;
	++m_fd_num;
	// 	if(evt & xWriteEvent)
	// 		FD_SET(handle,&m_fdread);
	// 	if(evt &xErrorEvent)
	// 		FD_SET(handle,&m_fdError);
	return 0;
}
int xSelectDemultiplexer::UnrequestEvent(SEABASE::handle_t handle)
{
	if((SOCKET)handle!=INVALID_SOCKET)
	{
		FD_CLR((SOCKET)handle,&m_fdReadSave);
		--m_fd_num;
	}
	return 0;
}
