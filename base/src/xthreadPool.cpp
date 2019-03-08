#include "xthreadPool.h"
using namespace SAEBASE;
bool xsimpleThreadPool::shutdown=false;
xMutex xsimpleThreadPool::m_threadLock;
xCondition xsimpleThreadPool::m_threadCond;
std::deque<xtaskbase*> xsimpleThreadPool::m_taskList;
#ifdef WIN32
	 unsigned int __stdcall xsimpleThreadPool::threadproxy(void* arg)
#else
	 void*  __stdcall xsimpleThreadPool::threadproxy(void* arg)
#endif
{
	pthread_t tid = pthread_self();
	xThread* pthread=(xThread*)arg;
	while(1)
	{
		xAutoLock L(m_threadLock);
		while(m_taskList.size()==0&&!shutdown)
		{
			m_threadCond.wait(m_threadLock);
		}
		if(shutdown)
		{
			pthread->destory();
			break;
		}
		xtaskbase* task=m_taskList.front();
		m_taskList.pop_front();
		task->run();
	}
	return 0;
}
xMutex  xthreadPool::m_poollock;
void xthreadPool::initsimplePool(size_t ThreadNumber,size_t IdleTimeout,size_t Tasklistsize,size_t threadStackSize)
{
	stopPool();
	m_nFreeThreadCount=0;
	m_nIdleTimeout=IdleTimeout;
	m_threadNum = ThreadNumber;
	m_nThreadStackSize = threadStackSize;
	m_tasklist.resizeQueue(Tasklistsize);

}
void xthreadPool::startPool(bool defaultpools )
{
	m_tasklist.setActive();// 设置任务队列为开启状态，否则添加和读取都会失败
	//size_t threadnum = m_threadNum?m_threadNum:4
	for(size_t i=0;i<m_threadNum;i++)
	{
		//xAutoLock L(m_lockForThread);
		//threadobj thread;
		threadobj*pthread_ = new threadobj;
		//m_ThreadList.push_back(&thread);
		pthread_->beginthreadobj(this);
		m_ThreadList.push_back(pthread_);
	}

}