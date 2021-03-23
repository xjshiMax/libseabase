//2021/1/13 by xjshi
/*
构建模块类，模块管理类，
实现功能：
1.继承基类，获得模块处理能力，模块独立消息线程和消息队列
2.manager负责模块之间的通信，提供接口投递消息给各个模块队列
3.不同进程之间使用tcp连接
//2021-3-23 
添加了定时器接口 timerStart   timerClear 给派生类使用面向对象的定时器接口
*/
#pragma once
#include "base/include/xEMsgqueue.h"
#include "timerArray.h"
#include "base/include/xdefine.h"
using namespace SEABASE;


#define ModuleBase 0x00001
#define Module1		ModuleBase+1
#define Module2		ModuleBase+2


template <class element>
class ManagerM;

template<class T>
class moduleBase:protected xEmsgqueue<T>
{
public:
	moduleBase(ManagerM<T>* manager);
	int startModule();
	virtual void HandleMessage(T& Message)=0;
	virtual void PutMessage2self(T&	Message);
	virtual void SendBroadcast(T&	Message){};
	virtual void Wait2end();//等待线程退出

	int timerStart(int timertype,int time_ms);//return timerhandler
	int timerClear(int timerhandler);
	ManagerM<T>* m_manager;

private:
	virtual void handleMessage(T&msg); //对内
};

template<class T>
moduleBase<T>::moduleBase(ManagerM<T>* manager)
{
	m_manager = manager;
}
template<class T>
int moduleBase<T>::startModule()
{
	return xEmsgqueue<T>::start();
}
template<class T>
void moduleBase<T>::Wait2end()//等待线程退出
{
	xEmsgqueue<T>::join();
}

template<class T>
void moduleBase<T>::PutMessage2self(T&	Message)
{
	xEmsgqueue<T>::in_queue(Message);
}

template<class T>
void moduleBase<T>::handleMessage(T&msg)
{
	HandleMessage(msg);
}

template<class T>
int moduleBase<T>::timerStart(int timertype,int time_ms)//return timerhandler
{
	m_manager->timerStart(timertype,time_ms,this);
}
template<class T>
int moduleBase<T>::timerClear(int timerhandler)
{
   m_manager->timerClear(timerhandler);
}

//模块管理类
template <class element>
class ManagerM:public xEmsgqueue<element>
{
public:
	ManagerM();
	virtual void handleMessage(element&msg); //
	void send2module(int modulepos,element& msg);
	//void SendMessage();
	void register2global(int modulepos,moduleBase<element>* ele);

	int timerStart(int timertype,int time_ms,moduleBase<element>*pmodule);//return timerhandler
	int timerClear(int timerhandler);
private:
	map<int,moduleBase<element>*> m_ModuleSet;
	timerArray m_timerArray;

};

template <class element>
 ManagerM<element>::ManagerM()
 {
	 m_timerArray.startTimer();
 }

template <class element>
void ManagerM<element>::handleMessage(element&msg)
{
	
}
template <class element>
void ManagerM<element>::send2module(int modulepos,element& msg)
{
	if(m_ModuleSet.find(modulepos)!=m_ModuleSet.end())
	{
		if(m_ModuleSet[modulepos]!=NULL)
		m_ModuleSet[modulepos]->PutMessage2self(msg);
	}
}
//void SendMessage();

template <class element>
void ManagerM<element>::register2global(int modulepos,moduleBase<element>*ele)
{
	if(m_ModuleSet.find(modulepos)==m_ModuleSet.end())
		m_ModuleSet[modulepos] = ele;
}

template <class element>
int ManagerM<element>::timerStart(int timertype,int time_ms,moduleBase<element>*pmodule)//return timerhandler
{
	 m_timerArray.timerStart(timertype,time_ms,pmodule);
}

template <class element>
int ManagerM<element>::timerClear(int timerhandler)
{
	 m_timerArray.timerClear(timerhandler);
}
