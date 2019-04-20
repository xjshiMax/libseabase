#pragma once
//#include <Winsock2.h>
#ifdef WIN32
	#include <process.h>
	#include <Windows.h>
#else
	#define __stdcall
	#include<pthread.h>
#endif
#include "xsema.h"
//#include "xAutoLock.h"
namespace SEABASE{

#pragma once
#ifdef  WIN32
	typedef unsigned int (__stdcall*pfunc)(void*);
#else
	typedef void* (__stdcall pfunc)(void*);
#endif
	enum threadstatus
	{
		INIT,
		START,
		JOINED,
		STOP
	};

//���ڶ����ģʽ
class Threadbase
{
public:
	Threadbase(bool bDetach=true);
	virtual ~Threadbase();
	/*
	�ڼ̳�run �Ժ�ҵ��ִ�����ʹ��ѭ�����м�������֮ǰ�˳�ѭ���������̻߳�һֱ���С�
	*/
	virtual void run()=0;		//ҵ��ӿ�
	int start();			//�����߳�
	int join();				//�ȴ��߳̽���
	void destory();			//�����߳����������Դ

	int get_thread_id(){return thr_id;}
	int set_thread_id(unsigned long thrID){thr_id=thrID;}

protected:
#ifdef WIN32
	static unsigned int __stdcall thread_proxy(void* arg);
#else
	static void*  __stdcall thread_proxy(void* arg);
#endif
private:
#ifdef WIN32
	size_t thr_id;
#else
	pthread_t thr_id;
#endif
	bool bExit_;			//�߳��Ƿ�Ҫ�˳���־
	threadstatus m_state;
	xSemaphore m_sema;
};
//��������ģʽ
class xThread
{
public:
	xThread(bool bDetach=true):thr_id(0),m_state(INIT)
	{
	}
	virtual ~xThread(){
		destory();
		m_state=STOP;
	};
	int start(pfunc func,void *arg);			//�����߳�
	int join();				//�ȴ��߳̽���
	void destory();			//�����߳����������Դ

	int get_thread_id(){return thr_id;}
	int set_thread_id(unsigned long thrID){thr_id=thrID;}
public:
#ifdef WIN32
	size_t thr_id;
#else
	pthread_t thr_id;
#endif
	bool bExit_;
	threadstatus m_state;
};





}