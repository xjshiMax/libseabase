//2019/3/17 xjshi
//这里封装一下不需要引用pthread库的锁，
//不过这个锁不能和xCondition  一起使用，单纯的锁
// 优点，方便，单一

#pragma once
#pragma once
#ifdef WIN32
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>>
#include <stdint.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <time.h>
#else
#include <unistd.h>
#include <stdint.h>
#include <semaphore.h>
#include<pthread.h>
#endif
#ifdef _WIN32
#define SEA_MUTEX_WAIT_INFINITE INFINITE
#define SEA_mutex_t HANDLE
#else
#define SEA_MUTEX_WAIT_INFINITE UINT_MAX
#define SEA_mutex_t pthread_mutex_t
#endif

namespace SEABASE
{
	enum {
		SEA_SUCCESS,
		SEA_NULL_POINTER = -10000,
		SEA_CONF_ERROR,
		SEA_NOMEM,
		SEA_INVALID_PARAM,
		SEA_SYSERROR,
		SEA_TIMEOUT,
		SEA_SERVER_ALREADY_INIT,
		SEA_SERVER_INIT_FAILED,
		SEA_SERVER_NEED_INIT,
		SEA_SERVER_CREATE_LISTENFD_FAILED,
		SEA_SERVICE_NOT_FOUND,
		SEA_OUT_MAX_TRY_COUNT
	};
	class xEmutex
	{
	public:
		xEmutex();
		~xEmutex();
		int32_t lock(uint32_t millisecond = INFINITE);
		int32_t try_lock();
		int32_t unlock();
	protected:
		xEmutex(const xEmutex&);
		xEmutex& operator=(const xEmutex&);
	private:
		SEA_mutex_t _mutex;

	};
}
