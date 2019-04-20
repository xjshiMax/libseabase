// ThreadpoolTest.cpp : 定义控制台应用程序的入口点。
//
#include "../../output/include/xEthreadpool.h"
#pragma comment(lib,"../../output/lib/windows/libseabase.lib")
using namespace SEABASE;
class mytask:public xRunable
{
public:
	~mytask(){}
	virtual int32_t Onrun(const bool * isstoped,void*param=NULL)
	{
		printf("i love you\n");
		return 0;
	} 
};
int main()
{
	xThreadPool mypool;
	mypool.init(40);
	mytask taskInst;
	for(int i=0;i<10000;i++)
	{
		mypool.addTask(&taskInst);
		printf("%d\n",i);
	}
	system("pause");
	return 0;
}

