#include "xsema.h"
using namespace SEABASE;

#ifndef _WIN32
static int32_t get_abs_timespec(struct timespec* ts, int32_t millisecond) {
	struct timeval tv;
	int32_t ret;

	if (NULL == ts) {
		return EINVAL;
	}

	ret = gettimeofday(&tv, NULL);
	if (0 != ret) {
		return ret;
	}

	ts->tv_sec = tv.tv_sec;
	ts->tv_nsec = tv.tv_usec * 1000UL;

	ts->tv_sec += millisecond / 1000UL;
	ts->tv_nsec += millisecond % 1000UL * 1000000UL;

	ts->tv_sec += ts->tv_nsec/(1000UL * 1000UL *1000UL);
	ts->tv_nsec %= (1000UL * 1000UL *1000UL);

	return 0;
}
#endif
xSemaphore::xSemaphore(int init)
{
	if(init<0)
	{
		init=0;
	}
#ifdef _WIN32
	_sem = CreateSemaphore(NULL,init,LONG_MAX,NULL);
#else
	sem_init(&_sem,0,init);
#endif
}

xSemaphore::~xSemaphore()
{
#ifdef _WIN32
	if(NULL!=_sem)
	{
		bool ret = CloseHandle(_sem);
		if(0!=ret)
		{
			_sem=NULL;
		}
	}
#else
	sem_destroy(&_sem);
#endif
}

int32_t xSemaphore::wait(uint32_t millisecond /* = INFINITE */)
{
#ifdef _WIN32
	if(NULL==_sem){return SEA_NULL_POINTER;}
	DWORD ret = WaitForSingleObject(_sem,millisecond);
	if(WAIT_OBJECT_0 == ret || WAIT_ABANDONED == ret){return 0;}
	else if (WAIT_TIMEOUT == ret)
	{
		return SEA_TIMEOUT;
	}
	else return SEA_SYSERROR;
#else
	int32_t ret = 0;
	if(millisecond == INFINITE)
	{
		while((ret=sem_wait(&_sem))==-1&&EINTR==errno);
	}
	else{
		struct timespec ts = {0,0};
		get_abs_timespec(&ts,millisecond);
		while((ret=sem_timedwait(&_sem,&ts))==-1&&EINTR==errno);
	}
	if(0!=ret)
	{
		if(errno == ETIMEDOUT)
			return SEA_TIMEOUT;
		else
			return SEA_SYSERROR;
	}

	return SEA_SUCCESS;
#endif
}
bool xSemaphore::try_wait(){
#ifdef _WIN32
	if (NULL == _sem) {
		return false;
	}

	DWORD ret = WaitForSingleObject(_sem, 0);
	if (WAIT_OBJECT_0 == ret || WAIT_ABANDONED == ret) {
		return true;
	}

	return false;
#else
	int32_t ret=0;
	while((ret=sem_trywait(&_sem))==-1 && EINTR==errno);
	return (0==ret);
#endif

}

int32_t xSemaphore::signal()
{
#ifdef _WIN32
	bool ret = FALSE;
	if(NULL != _sem)
	{
		ret = ReleaseSemaphore(_sem,1,NULL);
	}
	return (0!=ret?0:SEA_SYSERROR);
#else
	int32_t ret=0;
	while((ret=sem_post(&_sem))==-1&&EINTR==errno);
	return (0==ret?0:SEA_SYSERROR);
#endif
}