//一级模块
//一级模块处理功能相关的，
/*
1.响应控制行指令
2.获取内存等系统信息
*/
#pragma once
#include "ExAppOnbase/include/module.h"
#include "base/include/xbaseLog.h"
#include "eventdef.h"
typedef struct MEMPACKED         //定义一个mem occupy的结构体  
{  
	char name1[20];      //定义一个char类型的数组名name有20个元素  
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
