// xsemaTest.cpp : 定义控制台应用程序的入口点。
//

#include "../../base/include/xsema.h"
#include "../../base/include/xthreadbase.h"
#include "../../base/include/xEtcpclient.h"
#include "../../base/inifile/inifile.h"
#include <stdio.h>
#pragma comment(lib,"../../base/inifile/lib/inifile.lib")
using namespace std;
using namespace SEABASE;
using namespace inifile;
class onTime:public Threadbase
{
public:
	onTime():_isStop(false),Count(0){


	};
	void init()
	{
		IniFile IniService;
		IniService.load("Service.ini");
		int iret = -1;
		strip=IniService.getStringValue("service","ip",iret);
		if(iret!=0)
		{
			exit(0);
		}
		iret=-1;
		port=IniService.getIntValue("service","port",iret);
		if(iret!=0)
		{
			exit(1);
		}
		iret=-1;
		timeout=IniService.getIntValue("service","timeout",iret);
		if(iret!=0)
		{
			timeout=120000;
		}
		iret=-1;
		Count=IniService.getIntValue("service","taskID",iret);
		if(iret!=0)
		{
			Count=0;
		}
		iret=-1;
		speechCraftID=IniService.getIntValue("service","speechCraftID",iret);
		if(iret!=0)
		{
			speechCraftID=3;
		}
		client.connectTCP((char*)strip.c_str(),port);
	}
	~onTime(){ stopontime();printf("~onTime\n");};
	void run()
	{
		while(!_isStop)
		{
			
			ontime();
			m_ontimesema.wait(timeout);
			printf("count:%d\n",Count++);
		}
	}
	int ontime()
	{
		char pmsg[256]={0};
		//string msg="{\"speechCraftID\":3,\"taskID\":3,\"taskName\":\"test2\"}";
		sprintf(pmsg,"{\"speechCraftID\":%d,\"taskID\":%d,\"taskName\":\"test2\"}",speechCraftID,Count);
		client.sendMsg(pmsg,strlen(pmsg));
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
	ExTcpClient client;
	string strip;
	int port;
	int timeout;  //ms
	int beginnode;
	int speechCraftID;
};

int main()
{
	onTime myontime;
// 	vector<onTime*> myset;
// 	for(int i=0;i<20;i++)
// 	{
// 		onTime myontime;
// 		myontime.start();
// 		myset.push_back(&myontime);
// 		printf("i=%d\n",i);
// 	}
// 	for(int i=0;i<20;i++)
// 	{
// 		myset[i]->join();
// 	}
	myontime.init();
	myontime.start();
	system("pause");
	return 0;
}

