//二级模块
/*
二级模块负责可视化交互
1.与客户端交互，包括tcp，http
2.数据持久化
3.日志处理
4.
*/
#pragma once
#include "ExAppOnbase/include/module.h"
class lowModule	:  public moduleBase<messageC>
{
public:
	lowModule(ManagerM<messageC>* manager):moduleBase(manager)
	{

	}
	void HandleMessage(messageC& Message)
	{
		printf("lowModule get a message:%d\n",Message.messageType);
	}
};
