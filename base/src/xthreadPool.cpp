#include "xthreadPool.h"
using namespace SEABASE;
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


void xthreadPool::initPool(size_t LowThreadNumber)
{
	if (UNINITIALIZED == m_state) {
		m_state = INITIALIZED;}
	m_threadNum=LowThreadNumber;
}
void xthreadPool::startPool(bool defaultpools )
{
	m_tasklist.setActive();// 设置任务队列为开启状态，否则添加和读取都会失败
	//size_t threadnum = m_threadNum?m_threadNum:4
	for(size_t i=0;i<m_threadNum;i++)
	{
		//xAutoLock L(m_lockForThread);
		threadobj *thread=new threadobj;
		//m_ThreadList.push_back(&thread);
		thread->beginthreadobj(this);
		m_ThreadList.push_back(thread);
	}

}
bool xthreadPool::pushObj(xtaskbase*node,const struct timespec & Timeout)
{
	//if(m_boStartPool && isBusy())/
	//这里有个讲究，不直接插入xtaskbase的子类对象，因为如果存对象，在插入的时候，会被强制转换成基类，丧失子类的部分
	//如果存子类指针，在waitForTask 接口无法将指针作为传出参数，这样取不到该指针的地址。
	//用pair<xtaskbase*，bool> 作为值类型，存入，这样取出的时候，可以将它的引用取出，这样，封装了多态问题，
	//同时bool型变量也可用来以后拓展。
	m_tasklist.pushTask(pair<xtaskbase*, bool>(node,false));
	return true;
}
void xthreadPool::stopPool(bool defaultpools/*=true*/){
	xAutoLock lock(m_lockForThread);
	m_tasklist.setDeadstatus();
	std::list<threadobj*>::iterator ite = m_ThreadList.begin();
	while(ite!=m_ThreadList.end())
	{
		(*ite)->endthreadobj();
		(*ite)->destory();
		threadobj* pobj=*ite;
		if(pobj)
			delete pobj;
		ite++;
	}
	m_tasklist.clearAllTask();
}
void xthreadPool::joinAllThread()
{
	std::list<threadobj*>::iterator ite = m_ThreadList.begin();
	while(ite!=m_ThreadList.end())
	{
		(*ite)->join();
		ite++;
	}

}