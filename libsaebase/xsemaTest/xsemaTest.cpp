// xsemaTest.cpp : 定义控制台应用程序的入口点。
//

#include "../../base/include/xsema.h"
#include "../../base/include/xthreadbase.h"
#include <stdio.h>
using namespace std;
using namespace SEABASE;

class onTime:public Threadbase
{
public:
	onTime():_isStop(false),Count(0){};
	~onTime(){ stopontime();printf("~onTime\n");};
	void run()
	{
		while(!_isStop)
		{
			
			ontime();
			m_ontimesema.wait(30000);
			printf("count:%d\n",Count++);
		}
	}
	int ontime()
	{
		printf("i love you \n");
		return 0;
	}
	void stopontime()
	{
		_isStop=true;
		m_ontimesema.signal();
	}
	xSemaphore m_ontimesema;
	bool _isStop;
	int Count;
};

int main()
{
	//onTime myontime;
	vector<onTime*> myset;
	for(int i=0;i<20;i++)
	{
		onTime myontime;
		myontime.start();
		myset.push_back(&myontime);
		printf("i=%d\n",i);
	}
	for(int i=0;i<20;i++)
	{
		myset[i]->join();
	}
//	myontime.start();
	system("pause");
	return 0;
}

