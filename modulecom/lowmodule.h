//����ģ��
/*
����ģ�鸺����ӻ�����
1.��ͻ��˽���������tcp��http
2.���ݳ־û�
3.��־����
4. ��������
*/
#pragma once
#include "ExAppOnbase/include/module.h"
#include "ConnectHandle.h"
enum lowmodule_timer
{
	timer_reconnect=0x01,
};
class lowModule	:  public moduleBase<messageC>
{
public:
	lowModule(ManagerM<messageC>* manager):moduleBase(manager)
	{

	}
	void HandleMessage(messageC& Message) ;
	int startlowmodule();
	void reconnect();
	void sendData(char*pdata,int len);


	int m_timerhandle_reconn;
	ConnectHandle m_tcpConnect;


};
