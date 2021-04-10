//二级模块
/*
二级模块负责可视化交互
1.与客户端交互，包括tcp，http
2.数据持久化
3.日志处理
4. 断线重连
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
