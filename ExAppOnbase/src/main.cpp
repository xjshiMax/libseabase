/*
基于libseabase 进行模块封装和开发
1）具备主从进程 (---)
2）单进程具备多个模块
3）具备配置文件
4）具备读写数据库持久化数据
5）具备http交互
6）具备脚本打包
7）
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ExAppOnbase/include/module.h"
#include "test/modulecom/Center.h"
#include "base/include/xdefine.h"


#define ELFVERSION  "1.0.1"


static Center g_center;
int startService()
{
	//globalManager::getInstance().register2global();
	
	return 0;
}
void show_info()
{
		string userinfo="";
		userinfo+="Usage:\n elf [-h] [-s signal] [-f num]\n";
		userinfo+="-h			:help\n";
		userinfo+="-s signal		:实现信号 stop quit reload,reopen\n";
		userinfo+="-f num			:查询系统信息，0，全部信息，1内存，2版本，3进程相关信息\n";
		userinfo+="-o type      :openssl md5 sha1 sha256 ";
		userinfo+="\n\n\n";
		printf("%s",userinfo.c_str());
}
int get_optioncmd(int argc, char* argv[])
{
	printf("get_optioncmd \n");
	char*p;
	char*signalchar;
	 for(int i=1;i<argc;i++)
	 {
		 p=(char*)argv[i];
		 if(*p++!='-')
		 {
			 printf("error param\n");
			 return  ERROR_FAIL;
		 }
		 while(*p)
		 {
			 switch(*p++)
			 {
			 case '?':
			 case 'h':
				 show_info();
				 break;

			 case 's':
					 if(*p)
					 {
					    signalchar =  (char*)p;
					 } else if(argv[++i])
					 {
						signalchar = argv[i];
					 }
					 else
					 {
						 printf("error param\n");
						 return ERROR_FAIL;
					 }
					 if (strcmp(signalchar, "stop") == 0
						 || strcmp(signalchar, "quit") == 0
						 || strcmp(signalchar, "reopen") == 0
						 || strcmp(signalchar, "reload") == 0)
					 {
						  g_center.cmdparse(*p,signalchar);
						  return 0;
					 }
					 else
						 return ERROR_FAIL;
				 break;
			 case 'f':
				 if(*p)
				 {
					 signalchar =  (char*)p;
				 } else if(argv[++i])
				 {
					 signalchar = argv[i];
				 }
				 else
				 {
					 printf("error param\n");
					 return ERROR_FAIL;
				 }
				 printf("%c,%s\n",*p,signalchar);
				 if (strcmp(signalchar, "1") == 0
					 || strcmp(signalchar, "2") == 0
					 || strcmp(signalchar, "3") == 0
					 || strcmp(signalchar, "4") == 0)
				 {
					 g_center.cmdparse('f',signalchar);
					 return 0;
				 }
// 				 else
// 					 return ERROR_FAIL;
				 break;
			 case 'o':
				 {
					 if(*p)
					 {
						 signalchar =  (char*)p;
					 } else if(argv[++i])
					 {
						 signalchar = argv[i];
					 }
					 else
					 {
						 printf("error param\n");
						 return ERROR_FAIL;
					 }
					 printf("%c,%s\n",*p,signalchar);
					 if (strcmp(signalchar, "md5") == 0
						 || strcmp(signalchar, "sha1") == 0
						 || strcmp(signalchar, "sha256") == 0
						 || strcmp(signalchar, "base64") == 0
						  || strcmp(signalchar, "decbase64") == 0)
					 {
						 g_center.cmdparse('o',signalchar);
						 return 0;
					 }
				 }
				 break;

			 }
		 }
	 }
	 return 0;
}
int main(int argc, char* argv[])
{
	if(argc == 2)
	{
		if(0 == strcmp(argv[1], "-v")||0 == strcmp(argv[1], "--version"))
		{
			//string vstring = ELFVERSION;
			printf("main version:%s  (%s %s)\n\n",ELFVERSION,__DATE__,__TIME__);
			return 0;
		}
	}

	g_center.initsubModule();
	startService();
	//对命令行进行解析
	get_optioncmd(argc,  argv)  ;
// 	while(1)
// 	{
// 		char
// 		fgets();
// 	}
	g_center.waitallend();
	//system("pause");

	//pause();
}