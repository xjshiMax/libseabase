// ThreadpoolTest.cpp : 定义控制台应用程序的入口点。
//
#include "../../base/include/xthreadPool.h"
using namespace SEABASE;
class mytask:public xtaskbase
{
public:
	~mytask(){}
	virtual int run()
	{
		printf("i love you\n");
		return 0;
	} 
};
int main()
{
	xthreadPool mypool;
	mypool.initPool(40);
	mypool.startPool();
	mytask taskInst;
	for(int i=0;i<10000;i++)
	{
		mypool.pushObj(&taskInst);
		printf("%d\n",i);
	}
	//mypool.joinAllThread();
	mypool.stopPool();
	system("pause");
	return 0;
}

