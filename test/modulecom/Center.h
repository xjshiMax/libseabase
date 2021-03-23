//服务中心
#include"highmodule.h"
#include "lowmodule.h"
#include "base/include/xapplication.h"


typedef SingletonObj<ManagerM<messageC> >	 globalManager	;

enum moudleid
{
	highM=1,
	lowM=2,
};
using namespace SEABASE;
class Center
{
public:
	void initsubModule()
	{
		p_highmodule = new highModule(&globalManager::getInstance());
		globalManager::getInstance().register2global(highM,p_highmodule);
		p_highmodule->startModule();
		p_lowmodule = new lowModule(&globalManager::getInstance());
		globalManager::getInstance().register2global(lowM,p_lowmodule);
		p_lowmodule->startModule();

	}
	int cmdparse(char cmd,char*param);
	void waitallend()
	{
		 p_highmodule->Wait2end();
		 p_lowmodule->Wait2end();
	}
public:
	highModule* p_highmodule;
	lowModule* p_lowmodule;
	//highModule* p_highmodule;
};