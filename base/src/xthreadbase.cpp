#include "xthreadbase.h"
using namespace SEABASE;

#ifdef WIN32
	 unsigned int __stdcall Threadbase::thread_proxy(void* arg)
#else
	 void*  __stdcall Threadbase::thread_proxy(void* arg)
#endif
{
	Threadbase* pbase=static_cast<Threadbase*> (arg);
// 	pbase->m_LockState.lock();
// 	pbase->m_ConditionState.signal();
// 	pbase->m_LockState.unlock();
	pbase->m_sema.signal();
	pbase->run();
	return 0;
}

Threadbase::Threadbase(bool bDetach):m_state(INIT),bExit_(false)
{
	thr_id=0;
}
Threadbase::~Threadbase()
{
	//join();
	m_sema.signal();
	destory();
	m_state=STOP;
	//printf("~Threadbase\n");
}

int Threadbase::start()
{
	if(m_state!=INIT)
		return -1;
	//xAutoLock L(m_LockState);
#ifdef WIN32
	unsigned int nval=_beginthreadex(0,0,thread_proxy,this,0,&thr_id);
	thr_id=nval;
#else
	pthread_attr_t attr;
	int arg=0;
	pthread_create(&thr_id,NULL,thread_proxy,this);
#endif
	m_sema.wait();
	
	m_state=START;
	return 0;
}
int Threadbase::join()
{
	if(m_state!=START&&m_state!=STOP)
		return -1;
#ifdef WIN32
	//WAIT_OBJECT 表示执行结束
	if(thr_id!=0)
	{
		DWORD dw= WaitForSingleObject(reinterpret_cast<HANDLE>(thr_id),INFINITE);
		if(WAIT_OBJECT_0==dw ||WAIT_ABANDONED == dw)
		{
			CloseHandle(reinterpret_cast<HANDLE>(thr_id)); //释放句柄资源，线程并没有结束
			thr_id=0;
			printf("\n join thread %d finish\n",thr_id);
		}
	}
#else
	pthread_join(thr_id,NULL);
#endif
	m_state = JOINED;
	return 0;
}
void Threadbase::destory()
{
	if(m_state!=STOP && m_state>=START)
	{
		bExit_ = true;
		m_state = STOP;
#ifdef WIN32
		CloseHandle(reinterpret_cast<HANDLE>(thr_id));
#else
		int thread_return;
		//pthread_exit((void*)&thread_return); //如果强行退出，线程里面的一些对象资源不会调用析构，可能会内存泄露
#endif
		thr_id=NULL;
	}

}
//////////////////////////////////////////////////////////////////////////
//xThread 实现


int xThread::start(pfunc func,void *arg)
{
	if(m_state!=INIT)
		return -1;
#ifdef WIN32
	unsigned int nval=_beginthreadex(0,0,func,arg,0,&thr_id);
	thr_id=nval;
#else
	pthread_create(&thr_id,NULL,func,arg);
#endif
	m_state=START;
	return 0;
}
int xThread::join()
{
	if(m_state!=START&&m_state!=STOP)
		return -1;
#ifdef WIN32
	//WAIT_OBJECT 表示执行结束
	if(thr_id!=0)
	{
		DWORD dw= WaitForSingleObject(reinterpret_cast<HANDLE>(thr_id),INFINITE);
		if(WAIT_OBJECT_0==dw ||WAIT_ABANDONED == dw)
		{
			CloseHandle(reinterpret_cast<HANDLE>(thr_id)); //释放句柄资源，线程并没有结束
			thr_id=0;
			printf("\n join thread %d finish\n",thr_id);
		}
	}
#else
	pthread_join(thr_id,NULL);
#endif
	m_state = JOINED;
	return 0;
}
void xThread::destory()
{
	if(m_state!=STOP && m_state>=START)
	{
		bExit_ = true;
		m_state = STOP;
#ifdef WIN32
		CloseHandle(reinterpret_cast<HANDLE>(thr_id));
#else
		int thread_return;
		//pthread_exit((void*)&thread_return);
#endif
	}
}