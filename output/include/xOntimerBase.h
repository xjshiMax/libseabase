//2018-12-18��Ӷ�ʱ������
/*
1����ʱ��������һ���̣߳�
2���̳ж�ʱ�����࣬Ȼ�����һֱִ�С�
3) ȷ�������̻߳�ȴ������������˳�����Ȼ��ʱ���߳�Ҳû���㹻��ʱ��ִ�С�
*/
//#include "xAutoLock.h"
#include "xsema.h"
#include "xthreadbase.h"
namespace SEABASE{
	//��ʱ�������뼶��
	class OnTimerBase:public Threadbase
	{
	public:	
		OnTimerBase(int timeout):m_TimeOut(timeout),m_bIsstop(false){}
		int startTimer()
		{
			return start();
		}
		void stopTimer()
		{
			destory();
			m_bIsstop=true;
		}
		virtual void timeout()=0;
	private:
		virtual void run()
		{
			while(!m_bIsstop){
				m_sema.wait(m_TimeOut);
				this->timeout();
			}

		}
	private:
		int m_TimeOut;
		xSemaphore m_sema;
		bool m_bIsstop;
	};
}