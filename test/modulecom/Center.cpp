#include "Center.h"
int Center::cmdparse(char cmd,char*param)
{
	printf("Center::cmdparse %c,%s\n",cmd,param);
	if(cmd=='f'&&*param=='1')
	{
		messageC msg;
		msg.messageType = Cmd_Getcupinfp  ;
		globalManager::getInstance().send2module(highM,msg);
	}
	else if(cmd=='f'&&*param=='2')
	{
		messageC msg;
		msg.messageType = Cmd_GetcupVersion  ;
		globalManager::getInstance().send2module(highM,msg);
	}
	else if(cmd=='o'&&strncmp(param,"md5",3)==0)
	{
		messageC msg;
		msg.messageType = Cmd_openssl_md5encode  ;
		globalManager::getInstance().send2module(highM,msg);
	}
	else if(cmd=='o'&&strncmp(param,"sha1",4)==0)
	{
		messageC msg;
		msg.messageType = Cmd_openssl_sha1encode  ;
		globalManager::getInstance().send2module(highM,msg);
	}
	else if(cmd=='o'&&strncmp(param,"sha256",6)==0)
	{
		messageC msg;
		msg.messageType = Cmd_openssl_sha256encode  ;
		globalManager::getInstance().send2module(highM,msg);
	}
	else if(cmd=='o'&&strncmp(param,"base64",6)==0)
	{
		messageC msg;
		msg.messageType = Cmd_openssl_base64encode  ;
		globalManager::getInstance().send2module(highM,msg);
	}
	else if(cmd=='o'&&strncmp(param,"decbase64",9)==0)
	{
		messageC msg;
		msg.messageType = Cmd_openssl_base64decode ;
		globalManager::getInstance().send2module(highM,msg);
	}
	
	return 0;
};