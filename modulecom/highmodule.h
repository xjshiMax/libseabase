//һ��ģ��
//һ��ģ�鴦������صģ�
/*
1.��Ӧ������ָ��
2.��ȡ�ڴ��ϵͳ��Ϣ
*/
#pragma once
#include "ExAppOnbase/include/module.h"
#include "base/include/xbaseLog.h"
#include "eventdef.h"
typedef struct MEMPACKED         //����һ��mem occupy�Ľṹ��  
{  
	char name1[20];      //����һ��char���͵�������name��20��Ԫ��  
	unsigned long Sw;  
	char name2[20];  
	unsigned long MemFree;  
	char name3[20];  
	unsigned long Buffers;  
	char name4[20];  
	unsigned long Cached;  
	char name5[20];  
	unsigned long SwapCached;  
}MEM_OCCUPY;  

 struct Processinfo
 {
	 char name[6][20];

 };
 enum timerMessage{
	 timer_getsystemtimr=0x1,
	 timer_getuserip=0x02
 };
class highModule	:  public moduleBase<messageC>
{
public:
	highModule(ManagerM<messageC>* manager);
	void HandleMessage(messageC& Message);

	void handleGetcpuinfo(messageC& Message);
	void handleGetVersioninfo(messageC& Message);
	void handleGetProcessinfo(messageC& Message);

public:
	void startgetipTimer();
	void cleargetiptimer();
public:
	xbaseLog m_log;

	int m_timer_getsystimeHandler;
	int m_timer_getuserip;

};
