//2019/1/6 ���̵߳�reactor 
/*
1�� ��Щʵ��Ӧ�õ�ʱ���֣����reactor�����̣߳���ôÿ�����ⲿ����start����������
2�� �����ü�һ���Լ��Ĺ����̣߳�start�����Ժ����߳���Ȼ������ִ�У�
*/
#pragma once
#include <stdio.h>
#include "xthreadbase.h"
#include "xReactor.h"
namespace SEABASE{
class xReactorwithThread:public xReactor,public Threadbase
{
public:
	virtual void run()
	{
		xReactor::start();
	}
	xReactorwithThread(){}
	~xReactorwithThread()
	{
		destory();
		printf("~xReactorwithThread\n");
	}
	void startReactorWithThread()
	{
		Threadbase::start();
	}
};
}