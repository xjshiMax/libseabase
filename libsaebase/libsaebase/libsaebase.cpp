// libsaebase.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../../base/include/xthreadPool.h"
using namespace std;
using namespace SAEBASE;
class mytask:public xtaskbase
{
public:
	int run()
	{
		cout<<"in mytask"<<endl;
		return 0;
	}


};
int main()
{
	/*xsimpleThreadPool mypool("thin");
	mypool.initPool(4);
	mypool.startPool();
	mytask mtask;
	for(int i=0;i<2000;i++)
	{
		mypool.pushObj(&mtask);
	}
	//mypool.waitforAllTaskDone();
	while(1) {
		printf("There are still %d tasks need to handle\n", mypool.getTaskSize());
		//���������û��������
		if(mypool.getTaskSize()==0) {
			//����̳߳�
			mypool.stopPool();
			break;
		}
		//sleep(2);
		printf("2 seconds later...\n");
	} */

	xthreadPool mypool("greaterpool");
	mypool.initPool(4);
	mypool.startPool();

	for(int i=0;i<2000;i++)
	{
		mytask *mtask=new mytask;
		mypool.trypushObj(*mtask);

	}
	mypool.waitforAllTaskDone();
	system("pause");
	return 0;
}

