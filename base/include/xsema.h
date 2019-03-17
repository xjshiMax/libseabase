//2019/3/17 xjshi
//线程同步变量，和xCondition 功能类似
//实现线程间的任务同步
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
	class xSemaphore
	{
	public:
		xSemaphore(int init = 0);
		~xSemaphore();
		/*
		wait 等待信号量
		millisecond：超时时常（毫秒）
		return 成功返回0，否则返回错误码
		*/
		int wait(uint32_t millisecond = INFINITE);
		bool try_wait();
		/*
		signal 出发信号量
		成功返回0，否则返回错误码
		*/
		int32_t signal();
	protected:
		//禁止使用拷贝构造和赋值运算符
		xSemaphore(const xSemaphore&);
		xSemaphore& operator =(const xSemaphore&);
	private:
		HANDLE _sem;
	};
}