#include "xthreadbase.h"
using namespace SAEBASE;

#ifdef WIN32
	 unsigned int __stdcall Threadbase::thread_proxy(void* arg)
#else
	 void*  __stdcall Threadbase::thread_proxy(void* arg)
#endif
{

	//xAutoLock antolock(zx);
	//timeobj proxylife;
	Threadbase* pbase=static_cast<Threadbase*> (arg);
	pbase->m_LockState.lock();
	pbase->m_ConditionState.signal();
	pbase->m_LockState.unlock();
	pbase->run();
	return 0;
}

Threadbase::Threadbase(bool bDetach)
{
	thr_id=0;
}
int Threadbase::start()
{
	xAutoLock L(m_LockState);
#ifdef WIN32
	unsigned int nval=_beginthreadex(0,0,thread_proxy,this,0,&thr_id);
	thr_id=nval;
#else
	pthread_attr_t attr;
	int arg=0;
	pthread_create(&thr_id,NULL,thread_proxy,this);
#endif
	m_ConditionState.wait(m_LockState);
	return 0;
}
int Threadbase::join()
{
#ifdef WIN32
	//WAIT_OBJECT 表示执行结束
	if(WaitForSingleObject(reinterpret_cast<HANDLE>(thr_id),INFINITE)==WAIT_OBJECT_0)
	{
		printf("\n join thread %d finish\n",thr_id);
	}
#else
	pthread_join(thr_id,NULL);
#endif
	return 0;
}
void Threadbase::destory()
{
#ifdef WIN32
	CloseHandle(reinterpret_cast<HANDLE>(thr_id));
#else
	int thread_return;
	pthread_exit((void*)&thread_return);
#endif
}
//////////////////////////////////////////////////////////////////////////
//xThread 实现


int xThread::start(pfunc func,void *arg)
{
#ifdef WIN32
	unsigned int nval=_beginthreadex(0,0,func,arg,0,&thr_id);
	thr_id=nval;
#else
	pthread_create(&thr_id,NULL,func,arg);
#endif
	return 0;
}
int xThread::join()
{
#ifdef WIN32
	//WAIT_OBJECT 表示执行结束
	if(WaitForSingleObject(reinterpret_cast<HANDLE>(thr_id),INFINITE)==WAIT_OBJECT_0)
	{
		printf("\n join thread %d finish\n",thr_id);
	}
#else
	pthread_join(thr_id,NULL);
#endif
	return 0;
}
void xThread::destory()
{
#ifdef WIN32
	CloseHandle(reinterpret_cast<HANDLE>(thr_id));
#else
	int thread_return;
	pthread_exit((void*)&thread_return);
#endif
}