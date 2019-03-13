//2018-12-18添加定时器基类
/*
1）定时器单独开一个线程，
2）继承定时器基类，然后可以一直执行。
3) 确保在主线程会等待，不会马上退出，不然定时器线程也没有足够的时间执行。
*/
#include "xAutoLock.h"
#include "xthreadbase.h"
namespace SAEBASE{
	//定时器，秒级。
	class OnTimerBase:public Threadbase
	{
	public:	
		OnTimerBase(int timeout):m_TimeOut(timeout){}
		int startTimer()
		{
			return start();
		}
		void stopTimer()
		{
			//join();
		}
		virtual void timeout()=0;
	private:
		virtual void run()
		{
			while(1){
				xAutoLock L(m_mutex);
				struct timespec tc;
				tc.tv_sec=m_TimeOut;
				tc.tv_nsec=0;
				//m_SleepCondition.timewait(m_mutex,tc);
				m_SleepCondition.timewait(m_mutex,tc);
				this->timeout();
			}

		}
	private:
		int m_TimeOut;
		xCondition m_SleepCondition;
		xMutex m_mutex;
	};
}