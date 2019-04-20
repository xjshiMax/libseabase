#include "xEthreadpool.h"
using namespace SEABASE;
/*class xShareable*/
xShareable::xShareable() : m_count(0) { }

void xShareable::inc()
{
	xEAutoLock lock(&m_mutex);
	++m_count;
}
int32_t xShareable::dec()
{
	xEAutoLock lock(&m_mutex);
	if(m_count>0)
		--m_count;
	return m_count;
}
int32_t xShareable::get_count()
{
	xEAutoLock lock(&m_mutex);
	return m_count;
}

/* class xRunable*/

/*class xEthreadbase*/
xEthreadbase::xEthreadbase(xsmartPtr<xRunable>runner,bool detached )
	: m_use_functor(true),
	m_runfuncptr(runner),
	m_funcptr(NULL),
	m_func_arg(NULL),
	m_detached(detached),
	m_state(INIT),
	m_isstoped(false)
#ifdef _WIN32
	,_handle(NULL)
#endif
{ }

xEthreadbase::xEthreadbase(threadfunc_t func, void* arg , bool detached)
	: m_use_functor(false),
	m_funcptr(func),
	m_func_arg(arg),
	m_detached(detached),
	m_state(INIT),
	m_isstoped(false)
#ifdef WIN32
	,_handle(NULL)
#endif
{ }
xEthreadbase::~xEthreadbase()
{
	join();
	m_state=STOP;
}
bool xEthreadbase::start()
{
	if(INIT!=m_state)
		return false;
	//xAutoLock L(m_LockState);
#ifdef WIN32
	_handle = _beginthreadex(0,0,thread_proxy,this,0,&_thread_id);
#else
	int ret;
	pthread_attr_t attr;
	ret = pthread_attr_init(&attr);
	if (0 != ret) {
		return false;
	}
	int arg=0;
	pthread_create(&_thread_id,NULL,thread_proxy,this);
#endif
	//m_ConditionState.wait(m_LockState);
	m_sema.wait();
	m_state=START;
	return 0;

}
bool xEthreadbase::join()
{
	if(m_state!=START&&m_state!=STOP)
		return false;
#ifdef WIN32
	//WAIT_OBJECT 表示执行结束
	if(_handle!=0)
	{
		DWORD dw= WaitForSingleObject(reinterpret_cast<HANDLE>(_thread_id),INFINITE);
		if(WAIT_OBJECT_0==dw ||WAIT_ABANDONED == dw)
		{
			CloseHandle(reinterpret_cast<HANDLE>(_handle)); //释放句柄资源，线程并没有结束
			_handle=0;
			printf("\n join thread %d finish\n",_handle);
		}
	}
#else
	pthread_join(_thread_id,NULL);
#endif
	m_state = JOINED;
	return 0;
}
bool xEthreadbase::stop()
{
	bool ret = false;
	if (m_state != STOP && m_state >= START)
	{
		m_isstoped = true;
		m_state = STOP;
		ret = true;
	}
	return ret;
}
#ifdef WIN32
unsigned int xEthreadbase::get_thread_id() const
{
	return _thread_id;
}
size_t xEthreadbase::gethandle()
{
	return _handle;
}
#else
pthread_t xEthreadbase::get_thread_id() const
{
	return _thread_id;
}
#endif
#ifdef WIN32
unsigned int xEthreadbase::thread_proxy(void* arg)
#else
void* xEthreadbase::thread_proxy(void* arg)
#endif
{
	xEthreadbase*thread = (xEthreadbase*)arg;
	xsmartPtr<xRunable> runner=thread->m_runfuncptr;
	bool use_functor = thread->m_use_functor;
	threadfunc_t func = thread->m_funcptr;
	void *parg = thread->m_func_arg;
	thread->m_sema.signal();

	if(use_functor)	//使用了第一种的构造函数
	{
		if(runner.is_valid())
		{
			runner->Onrun(&thread->m_isstoped,arg);
		}
	}
	else
	{
		if(func)
		{
			func(&thread->m_isstoped,arg);
		}
	}
	return 0;
}

/* class threadgroup*/

xThreadGroup::xThreadGroup()
{

}
xThreadGroup::~xThreadGroup()
{

}
bool xThreadGroup::addThread(xsmartPtr<xEthreadbase>thread)
{
	try {
		m_threads.push_back(thread);
	} catch(std::bad_alloc& ) {
		return false;
	}
	return true;
}
bool xThreadGroup::join()
{
	citr_type citr;

	for (citr = m_threads.begin(); citr != m_threads.end(); ++citr) {
		(*citr)->join();
	}

	m_threads.clear();

	return true;
}
size_t xThreadGroup::size()
{
	return m_threads.size();
}
bool xThreadGroup::terminateAll()
{
	citr_type citr;

	for (citr = m_threads.begin(); citr != m_threads.end(); ++citr) {
		(*citr)->stop();
	}

	return true;
}

/* class xThreadPool*/
class xThreadPool::ThreadPoolRunner:public xRunable
{
public:
	ThreadPoolRunner(xThreadPool*tp);
	virtual int32_t Onrun(const bool * isstoped,void*param=NULL);
private:
	xThreadPool* _tp;
};
xThreadPool::ThreadPoolRunner::ThreadPoolRunner(xThreadPool*tp):_tp(tp)
{

}
int32_t xThreadPool::ThreadPoolRunner::Onrun(const bool * isstoped,void*param)
{
	while(!(*isstoped))
	{
		xRunable* prun=NULL;
		if(_tp->m_tasks.get(prun, INFINITE)==0&&prun){
			prun->Onrun(isstoped, param);
		}
	}
	return 0;
}
xThreadPool::xThreadPool():m_state(UNINITIALIZED)
{

}
xThreadPool::~xThreadPool()
{
	terninate();
}
//static const int DEFAULT_THREADS_NUM = 10; //默认线程数量
int xThreadPool::init(int nThreads)
{
	int ret = 0;
	if (UNINITIALIZED == m_state) {
		m_state = INITIALIZED;

		addthread(nThreads);
	}

	return ret;
}
bool xThreadPool::addTask(xRunable* runinst)
{
	return 0 == m_tasks.put(runinst);
}
bool xThreadPool::join()
{
	 return m_threadgroup.join();
}
size_t xThreadPool::size()
{
	return m_threadgroup.size();
}
bool xThreadPool::terninate()
{
	return m_threadgroup.terminateAll();
}
int xThreadPool::addthread(int nthreads) {
	int ret = 0;
	for (int i = 0; i < nthreads; ++i) {
		xsmartPtr<xEthreadbase>workerThread =xsmartPtr<xEthreadbase>(new xEthreadbase(xsmartPtr<ThreadPoolRunner>(new ThreadPoolRunner(this))));
		if (workerThread.is_valid()) {
			workerThread->start();
			m_threadgroup.addThread(workerThread);
			++ret;
		}
	}
	return ret;
}