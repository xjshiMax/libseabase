#include "lowmodule.h"
#include "base/include/xsema.h"
#include "ctkvset.h"
int lowModule::
	startlowmodule()
{
	 startModule();
	 sendData("",0);
	 m_timerhandle_reconn = timerStart(timer_reconnect,2000);
}
void lowModule::HandleMessage(messageC& Message) 
{
	switch(Message.messageType)
	{
	case timer_event:
		{
			  switch(Message.No)
			  {
			  case timer_reconnect:
				  reconnect();
			  }
		}
		break;
	}
}
void lowModule::reconnect()
{
	timerClear(m_timerhandle_reconn);
	//Sleep(2000);
	xSemaphore sema;
	sema.wait(2000);
	int ret = m_tcpConnect.Connect("192.168.31.1",6000);
	if(ret==-1)//¡¨Ω” ß∞‹
	{
		printf("connect failed\n");
		 m_timerhandle_reconn =  timerStart(timer_reconnect,2000);
	}
	else
	printf("connect success\n");
}
void lowModule::sendData(char*pdata,int len)
{
	//CTtranInfo notify(0, 0, EvtAFC_SUNTEK_TvmDisconnected);
	//notify.GetMessageData().PutString(AFC_SUNTEK_Host, sock.getIPAddress());
	//notify.GetMessageData().PutUInt(AFC_SUNTEK_Port, sock.getPort());	
	//CommApp::getRef().sendToTvmModule(notify);
	  CTuint id= 9999;
	  TKVSet setinst;
	  setinst.PutInt(0x00000001,id);
	  char data[128];
	  int ilen = setinst.KVSet2String(data,128);
	  for(int i=0;i<ilen;i++)
	  {
		   printf("sendData:%02x\n",data[i]);
	  }
	  printf("\n");
}
