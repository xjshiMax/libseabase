//2018-12-17
// 基于select io 复用模式，实现分离器
/*
1）继承	xEventDemultiplexer。 实现相应的接口
2) 默认读，写，错误 最多各注册64个fd.
*/
#pragma once
#include "xbaseclass.h"
#include "basesock.h"
namespace SAEBASE{
class xSelectDemultiplexer:public xEventDemultiplexer
{
public:
	xSelectDemultiplexer();
	virtual ~xSelectDemultiplexer();
	virtual int WaitEvents(std::map<handle_t,xEventHandler*>*handlers,
		int timeout=0,xtime_heap* event_timer=NULL );
	//添加或则修改文件描述符的注册事件信息
	virtual int RequestEvent(handle_t handle,event_t evt);


	virtual int UnrequestEvent(handle_t handle);
private:
	int m_epoll_fd;  //epoll_creat 返回的描述符
	int m_fd_num;	  // 当前加入集合的描述符数量
	int m_maxfdID;	  //最大fd值加1.在select模型中常用这个代替数量。
	//fd_set m_fdread;
	//fd_set m_fdError;
	//fd_set m_fdwrite;
	fd_set m_fdReadSave;
	std::vector<handle_t> m_Readevents;
};
xSelectDemultiplexer::xSelectDemultiplexer()
{
	m_fd_num=0;
	FD_ZERO(&m_fdReadSave);
}
xSelectDemultiplexer::~xSelectDemultiplexer()
{

}

int xSelectDemultiplexer::WaitEvents(std::map<handle_t,xEventHandler*>*handlers,
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
					(*handlers)[fd]->HandleRead(fd);
				}
			}

	}
	if(event_timer !=NULL)
	{
		event_timer->tick();
	}
	return 0;
}
int xSelectDemultiplexer::RequestEvent(handle_t handle,event_t evt)
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
int xSelectDemultiplexer::UnrequestEvent(handle_t handle)
{
	if((SOCKET)handle!=INVALID_SOCKET)
	{
		FD_CLR((SOCKET)handle,&m_fdReadSave);
		--m_fd_num;
	}
	return 0;
}
}