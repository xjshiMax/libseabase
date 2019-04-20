//2019/3/17 xjshi
//�߳�ͬ����������xCondition ��������
//ʵ���̼߳������ͬ��,����Ҫ������
#ifndef _XSEMA_H
#define _XSEMA_H
#pragma once
#ifdef WIN32
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <time.h>
#else
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>
#include <linux/unistd.h>
#include <semaphore.h>
#endif
#ifdef _WIN32
//#define INFINITE INFINITE
#define _sem_t HANDLE
#else
#define INFINITE            0xFFFFFFFF 
#define _sem_t sem_t
#endif
namespace SEABASE
{
// 	enum xstatus_e{
// 		SEA_SUCCESS,
// 		SEA_NULL_POINTER = -10000,
// 		SEA_CONF_ERROR,
// 		SEA_NOMEM,
// 		SEA_INVALID_PARAM,
// 		SEA_SYSERROR,
// 		SEA_TIMEOUT,
// 		SEA_SERVER_ALREADY_INIT,
// 		SEA_SERVER_INIT_FAILED,
// 		SEA_SERVER_NEED_INIT,
// 		SEA_SERVER_CREATE_LISTENFD_FAILED,
// 		SEA_SERVICE_NOT_FOUND,
// 		SEA_OUT_MAX_TRY_COUNT
// 	};
	class xSemaphore
	{
		enum xstatus_e{
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
	public:
		xSemaphore(int init = 0);
		~xSemaphore();
		/*
		wait �ȴ��ź���
		millisecond����ʱʱ�������룩
		return �ɹ�����0�����򷵻ش�����
		*/
		int wait(uint32_t millisecond = INFINITE);
		bool try_wait();
		/*
		signal �����ź���
		�ɹ�����0�����򷵻ش�����
		*/
		int32_t signal();
	protected:
		//��ֹʹ�ÿ�������͸�ֵ�����
		xSemaphore(const xSemaphore&);
		xSemaphore& operator =(const xSemaphore&);
	private:

		_sem_t _sem;

	};
}

#endif