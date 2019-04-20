//2019-4-17 �°��̳߳� ���ȶ�
/*
addTask �������Ȼ��ȴ��߳�ȥִ�У��ڷ��䵽�߳��Ժ�
ȥ��Ӧ�����Onrun��������ȥִ�С�
����Onrun���� �Ժ�ֻ�й����߳�һ����
*/

#include "xEmutex.h"
#include "xsema.h"
#include "xsync_vector.h"
#include "xsmartPtr.h"
#include <vector>
#ifdef WIN32
#include <process.h>
#include <Windows.h>
#else
#define __stdcall
#include<pthread.h>
#endif
namespace SEABASE
{
	typedef void* (*threadfunc_t)(const bool*, void*);

	/*
	 ����ԭ�Ӽ������ܵ���
	*/
	class xShareable
	{
	public:
		virtual ~xShareable(){}
		void inc();
		int32_t dec();
		int32_t get_count();
	protected:
		xShareable();
	private:
		int32_t m_count;
		xEmutex m_mutex;

	};
	/*
		�߳����л��࣬�ڴ����߳�ʱ����Ҫ�ȼ̳У�ʵ�����࣬Ȼ�󵱲�������
	*/
	class xRunable:public xShareable
	{
	public:
		virtual int32_t Onrun(const bool * isstoped,void*param=NULL)=0;
		virtual ~xRunable(){};
	};

	/*
		���������̻߳��࣬
	*/

	class xEthreadbase:public xShareable
	{
	private:
		enum state_t{
			INIT,
			START,
			JOINED,
			STOP
		};
	public:
		xEthreadbase(xsmartPtr<xRunable>runner,bool detached = false);
		xEthreadbase(threadfunc_t func, void* arg = NULL, bool detached = false);
		~xEthreadbase();
		bool start();		//��ʼ�߳�
		bool join();		//�ȴ��߳�
		bool stop();		//ֹͣ�߳�
#ifdef WIN32
		unsigned int get_thread_id() const;  //�����߳�id
		size_t gethandle();			  //�����߳̾��
#else
		pthread_t get_thread_id() const; // �����߳�id
#endif
	private:
		bool setDetached();
#ifdef WIN32
		static unsigned int __stdcall thread_proxy(void* arg);
#else
		static void*  __stdcall thread_proxy(void* arg);
#endif
		bool m_use_functor;
		xsmartPtr<xRunable>m_runfuncptr;
		threadfunc_t m_funcptr;
		void* m_func_arg;
		xSemaphore m_sema;
		volatile bool m_detached;
		state_t m_state;

		bool m_isstoped;
#ifdef WIN32
		size_t _handle;
		unsigned int _thread_id;
#else
		pthread_t _thread_id;
#endif
	};

	/*
		�߳��飬����һ���̣߳�������Ӻ͹ر��̡߳�
	*/
	class xThreadGroup
	{
	public:
		xThreadGroup();
		~xThreadGroup();
		bool addThread(xsmartPtr<xEthreadbase>thread);
		bool join();		//�ȴ����е��߳̽���
		size_t size();		//��ȡ�̸߳���
		bool terminateAll();//��ֹ�����߳�
	private:
		xThreadGroup(const xThreadGroup&);
		xThreadGroup& operator=(const xThreadGroup&);

		std::vector<xsmartPtr<xEthreadbase> > m_threads;
		typedef std::vector<xsmartPtr<xEthreadbase> >::const_iterator citr_type;
	};

	/*
		���̳߳أ�ά��һ��Ԥ�ȴ����õ��߳��Լ�һ��������С��߳�����ִ����������е�����
	*/
	class xThreadPool:public xShareable
	{
	private:
		class ThreadPoolRunner;
	public:
		enum state_t{
			 UNINITIALIZED, INITIALIZED
		};
		xThreadPool();
		~xThreadPool();
		static const int DEFAULT_THREADS_NUM = 10; //Ĭ���߳�����
		int init(int nThreads=DEFAULT_THREADS_NUM); //	��ʼ���̳߳أ�ָ���߳�����
		bool addTask(xRunable* runinst);			// 	�������
		bool join();								//�ȴ������߳̽���
		size_t size();			//��ȡ�̳߳����߳�����
		bool terninate();		//��ֹ�����̵߳�ִ��
	private:
		int addthread(int nthreads);	//���nthreads���߳�
		xSyncVector<xRunable*> m_tasks;	//�������
		xThreadGroup m_threadgroup;		//�߳���
		state_t m_state;				//�̳߳�״̬

	};
}

