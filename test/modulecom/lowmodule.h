//����ģ��
/*
����ģ�鸺����ӻ�����
1.��ͻ��˽���������tcp��http
2.���ݳ־û�
3.��־����
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
