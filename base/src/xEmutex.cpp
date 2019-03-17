#include "xEmutex.h"
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
xEmutex::xEmutex()
{
#ifdef _WIN32
	_mutex = CreateMutex(NULL, FALSE, NULL);
#else
	int32_t ret = 0;
	pthread_mutexattr_t attr;

	ret = pthread_mutexattr_init(&attr);
	if (0 != ret) {
		ret = pthread_mutex_init(&this->_mutex, NULL);
	} else {
		ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK_NP);
		ret = pthread_mutex_init(&_mutex, &attr);
		pthread_mutexattr_destroy(&attr);
	}
#endif
}

xEmutex::~xEmutex()
{
#ifdef _WIN32
	BOOL ret = CloseHandle(_mutex);
	if (0 != ret) {
		_mutex = NULL;
	}
#else
	pthread_mutex_destroy(&_mutex);
#endif
}

int32_t xEmutex::lock(uint32_t millisecond) {
#ifdef _WIN32
	if (NULL == _mutex) {
		return SEA_NULL_POINTER;
	}

	DWORD ret = WaitForSingleObject(_mutex, millisecond);
	if (WAIT_OBJECT_0 == ret) {
		return 0;
	}
	else if (WAIT_TIMEOUT == ret) {
		return SEA_TIMEOUT;
	}
	else {
		return SEA_SYSERROR;
	}
#else
	int32_t ret = 0;

	if (INFINITE == millisecond) {
		ret = pthread_mutex_lock(&_mutex);
	}
	else {
		struct timespec ts = {0, 0};
		get_abs_timespec(&ts, millisecond);
		ret = pthread_mutex_timedlock(&_mutex, &ts);
	}

	if (0 != ret) {
		int32_t e = BgccGetLastError();
		if (ETIMEDOUT == e) {
			return SEA_TIMEOUT;
		}
		else {
			return SEA_SYSERROR;
		}
	}
	return 0;
#endif
}

int32_t xEmutex::try_lock() {
#ifdef _WIN32
	return lock(1);
#else
	int32_t ret = 0;
	ret = pthread_mutex_trylock(&_mutex);
	return (0 == ret ? 0 : SEA_SYSERROR);
#endif
}

int32_t xEmutex::unlock() {
#ifdef _WIN32
	BOOL ret = FALSE;

	if (NULL != _mutex) {
		ret = ReleaseMutex(_mutex);
	}
	return (0 != ret ? 0 : SEA_SYSERROR);
#else
	int32_t ret = 0;
	ret = pthread_mutex_unlock(&_mutex);
	return (0 == ret ? 0 : SEA_SYSERROR);
#endif
} 