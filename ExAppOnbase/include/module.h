//2021/1/13 by xjshi
/*
构建模块类，模块管理类，
实现功能：
1.继承基类，获得模块处理能力，模块独立消息线程和消息队列
2.manager负责模块之间的通信，提供接口投递消息给各个模块队列
3.不同进程之间使用tcp连接
*/
#include "base/include/xEMsgqueue.h"
using namespace SEABASE;

template<class T>
class moduleBase:protected xEmsgqueue<T>
{
public:
	//moduleBase();
	int startModule();
	virtual void HandleMessage(T& Message)=0;
	virtual void PutMessage2self(T&	Message);
	virtual void SendBroadcast(T&	Message){};
private:
	virtual void handleMessage(T&msg); //对内
};

template<class T>
int moduleBase<T>::startModule()
{
	return start();
}


template<class T>
void moduleBase<T>::PutMessage2self(T&	Message)
{
	in_queue(Message);
}

template<class T>
void moduleBase<T>::handleMessage(T&msg)
{
	HandleMessage(msg);
}

//模块管理类
template <class element>
class ManagerM:public xEmsgqueue<element>
{
public:
	virtual void handleMessage(element&msg); //
	void send2module(int modulepos,element& msg);
	//void SendMessage();
	void register2global(int modulepos,moduleBase<element>* ele);
private:
	map<int,moduleBase<element>*> m_ModuleSet;

};

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