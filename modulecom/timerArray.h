#include "base/include/xtimeheap.h"
#include "base/include/xOntimerBase.h"
#include "base/include/xTimeuil.h"
#include "base/include/xEMsgqueue.h"
#include "base/include/xdefine.h"

using namespace SEABASE;

typedef xEmsgqueue<messageC> MessageCQueue;
class timerheap:public xheaptimer
{
public:
	timerheap(int msecond):xheaptimer(msecond) //ms
	{
		expire =xTimeUtil::get_timestamp_ms()+msecond; 
	}

	int m_timertype;
	MessageCQueue*m_pqueue;
	

};
class timerArray:public OnTimerBase
{
public:
	timerArray();
	virtual void timeout(); //超时检测，满足条件投递事件
	int timerStart(int timertype,int time_ms,MessageCQueue*pqueue);//return timerhandler
	int timerClear(int timerhandler);

	static void sendMessage(void*data);
	xtime_heap m_heap;
};