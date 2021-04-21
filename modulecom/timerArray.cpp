#include "timerArray.h"

timerArray::timerArray():m_heap(30),OnTimerBase(1)
{

}
void timerArray::timeout() //超时检测，满足条件投递事件
{
	//printf("timerArray::timeout\n");
	 vector<xheaptimer*> listofdelete;
	 m_heap.tick_ms(listofdelete);
	 //释放资源
	for(int i=0;i<listofdelete.size();i++)
	{
		xheaptimer*	ptimer = listofdelete[i];
		if(ptimer)
			delete ptimer;		
	}
}
int timerArray::timerStart(int timertype,int time_ms,MessageCQueue*pqueue)
{
	timerheap* timerb = new timerheap(time_ms);
	timerb->m_timertype = timertype;
	timerb->cb_func = &timerArray::sendMessage ;
	timerb->m_pqueue =pqueue;
	timerb->user_data = timerb;
	m_heap.add_timer(timerb);
	return (int)timerb;
}
int timerArray::timerClear(int timerhandler)
{
	 timerheap* timerb = (timerheap*)timerhandler;
	 m_heap.del_timer(timerb);
	 return 0;
}
void timerArray::sendMessage(void*data)
{
	  timerheap*ptimerb = (timerheap*)data;
	  MessageCQueue*pQueue = ptimerb->m_pqueue;
	  if(pQueue)
	  {
		  messageC msg;
		  msg.messageType =  timer_event;
		  msg.No = ptimerb->m_timertype;
		  pQueue->in_queue(msg);
	  }

}