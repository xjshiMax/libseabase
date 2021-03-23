#include "highmodule.h"
#include "cryptWapper.h"
#include "moduleConfig.h"
#include "base/include/basesock.h"
#ifndef WIN32
#include<sys/sysinfo.h>
#endif
highModule::highModule(ManagerM<messageC>* manager):moduleBase(manager)
{
	m_log.setLoglevel(xbaseLog::LOG_INFO);
	m_log.setLogName("highmodule");
	moduleConfig configfile;
	//configfile.loadFromDB("");

	m_timer_getsystimeHandler = timerStart(timer_getsystemtimr,5000);
	startgetipTimer();
	//m_log.openLogFile();
}
void highModule::HandleMessage(messageC& Message)
{
	printf("highModule::HandleMessage\n");
	switch(Message.messageType)
	{
	case Cmd_Getcupinfp:
		{
			 handleGetcpuinfo( Message);
		}
		break;
	case Cmd_GetcupVersion:
		{
			handleGetVersioninfo(Message);
		}
		break;
	case Cmd_GetProcessInfo:
		{
		   handleGetProcessinfo(Message);
		}
		break;
	case Cmd_openssl_md5encode:
		{
			m_log.printinfo(logprefix,"Cmd_openssl_md5encode\n");
			printf("please input data that needs md5(no longer 1024 byte):\n");
			char buff[1024];
			fgets(buff,1024,stdin);
			cryptWapper cryptwa;
			cryptwa.m_data = buff;
			cryptwa.getmd5();

		}
		break;
	case Cmd_openssl_sha256encode:
		{
			m_log.printinfo(logprefix,"Cmd_openssl_sha256encode\n");
			printf("please input data that needs sha256(no longer 1024 byte):\n");
			char buff[1024];
			fgets(buff,1024,stdin);
			cryptWapper cryptwa;
			cryptwa.m_data = buff;
			cryptwa.getsha256();

		}
		break;
	case Cmd_openssl_sha1encode:
		{
			m_log.printinfo(logprefix,"Cmd_openssl_sha1encode\n");
			printf("please input data that needs sha1(no longer 1024 byte):\n");
			char buff[1024];
			fgets(buff,1024,stdin);
			cryptWapper cryptwa;
			cryptwa.m_data = buff;
			cryptwa.getsha1();

		}
		break;
	case Cmd_openssl_base64encode:
		{
			m_log.printinfo(logprefix,"Cmd_openssl_base64encode\n");
			printf("please input data that needs base64(no longer 1024 byte):\n");
			char buff[1024];
			fgets(buff,1024,stdin);
			cryptWapper cryptwa;
			cryptwa.m_data = buff;
			cryptwa.enCode_base64();

		}
		break;
	case Cmd_openssl_base64decode:
		{
			m_log.printinfo(logprefix,"Cmd_openssl_base64decode\n");
			printf("please input data that needs base64dec(no longer 1024 byte):\n");
			char buff[1024];
			fgets(buff,1024,stdin);
			cryptWapper cryptwa;
			cryptwa.m_encodeData = buff;
			cryptwa.dec_base64();

		}
		break;
	case timer_event:
		{
			switch(Message.No)
			{
			case timer_getsystemtimr:
				{
					timerClear(m_timer_getsystimeHandler);
					printf("hello world:%s\n",xTimeUtil::getCurrentTimeStamp().c_str());
					m_timer_getsystimeHandler = timerStart(timer_getsystemtimr,5000);
				}
				break;
			case timer_getuserip:
				{
					cleargetiptimer();
					char hostname[32];
					int ret = gethostname(hostname,32) ; //获得主机名
					struct hostent * myhost;
					myhost = gethostbyname(hostname); //获得本机信息
					printf("hello world:%s\n",hostname);
				}
				break;
			} ;
		}
		break;

	}
	printf("highModule get a message:%d\n",Message.messageType);
}
void highModule::handleGetcpuinfo(messageC& Message)
{
	m_log.printinfo(logprefix,"highModule::handleGetcpuinfo\n");//highModule::handleGetcpuinfo");
	char buff[256];
	FILE*fd;
	MEM_OCCUPY *memTo=new MEM_OCCUPY;
	fd = fopen("/proc/meminfo","r");
	fgets(buff,sizeof(buff),fd);
	sscanf(buff, "%s %lu ", memTo->name1, &memTo->Sw);  
	fgets(buff, sizeof(buff), fd);  
	sscanf(buff, "%s %lu ", memTo->name2, &memTo->MemFree);  
	fgets(buff, sizeof(buff), fd);  
	sscanf(buff, "%s %lu ", memTo->name3, &memTo->Buffers);  
	fgets(buff, sizeof(buff), fd);  
	sscanf(buff, "%s %lu ", memTo->name4, &memTo->Cached);  
	fgets(buff, sizeof(buff), fd);   
	sscanf(buff, "%s %lu", memTo->name5, &memTo->SwapCached);  
	printf("cpu info :\n");
	printf("%s:%d\n",memTo->name1,memTo->Sw);
	printf("%s:%d\n",memTo->name2,memTo->MemFree);
	printf("%s:%d\n",memTo->name3,memTo->Buffers);
	printf("%s:%d\n",memTo->name4,memTo->Cached);
	printf("%s:%d\n",memTo->name5,memTo->SwapCached);
}
void highModule::handleGetVersioninfo(messageC& Message)
{
#ifndef WIN32
	///*struct sysinfo {                    
	//	long uptime;              
	//	/* 启动到现在经过的时间 */                    
	//	unsigned long loads[3];    
	//	/* 1, 5, and 15 minute load averages */                    
	//	unsigned long totalram;  /* 总的可用的内存大小 */  
	//	unsigned long freeram;   /* 还未被使用的内存大小 */  
	//	unsigned long sharedram; /* 共享的存储器的大小 */  
	//	unsigned long bufferram; /* 缓冲区大小 */                    
	//	unsigned long totalswap; /* 交换区大小 */                    
	//	unsigned long freeswap;  /* 还可用的交换区大小 */  
	//	unsigned short procs;    /* 当前进程数目 */  
	//	char _f[22];         /* 64字节的补丁结构 */  
	//  */
	struct sysinfo info;
	int ret =   sysinfo(&info);
	char buff[256];
	FILE*fd;
	fd = fopen("/proc/version","r");
	fgets(buff,sizeof(buff),fd);
	printf("version:\n");

	printf("%s\n",buff);
#endif
}
void highModule::handleGetProcessinfo(messageC& Message)
{
	//typedef struct
	//{   
	//	/** 01 */ pid_t pid;                     /** 进程号，其允许的最大值，请查看/proc/sys/kernel/pid_max */
	//	/** 02 */ char comm[FILENAME_MAX];       /** 进程的名字，不包括路径 */
	//	/** 03 */ char state;                    /** 进程的状态 */
	//	/** 04 */ pid_t ppid;                    /** 父进程号 */
	//	/** 05 */ pid_t pgrp;                    /** 进程组号 */
	//	/** 06 */ pid_t session;                 /** 进程会话号 */
	//	/** 07 */ int tty_nr;                    /** The tty the process uses */
	//	/** 08 */ pid_t tpgid;                   /** The tty the process uses */
	//	/** 09 */ unsigned int flags;            /** The kernel flags word of the process (%lu before Linux 2.6.22) */
	//	/** 10 */ unsigned long minflt;          /** The number of minor faults the process has made which have not required loading a memory page from disk */
	//	/** 11 */ unsigned long cminflt;         /** The number of minor faults that the process's waited-for children have made */
	//	/** 12 */ unsigned long majflt;          /** The number of major faults the process has made which have required loading a memory page from disk */
	//	/** 13 */ unsigned long cmajflt;         /** The number of major faults that the process's waited-for children have made */
	//	/** 14 */ unsigned long utime;           /** The number of jiffies that this process has been scheduled in user mode */
	//	/** 15 */ unsigned long stime;           /** The number of jiffies that this process has been scheduled in kernel mode */
	//	/** 16 */ long cutime;                   /** The  number  of  jiffies that this process's waited-for children have been scheduled in user mode */
	//	/** 17 */ long cstime;                   /** The number of jiffies that this process's waited-for children have been scheduled in kernel mode */
	//	/** 18 */ long priority;                 /** The standard nice value, plus fifteen.  The value is never negative in the kernel */
	//	/** 19 */ long nice;                     /** The nice value ranges from 19 (nicest) to -19 (not nice to others) */
	//	/** 20 */ long num_threads;              /** Number of threads in this process (since Linux 2.6).  Before kernel 2.6, this field was hard coded to 0 as a placeholder */
	//	/** 21 */ long itrealvalue;              /** The  time  in  jiffies before the next SIGALRM is sent to the process due to an interval timer.2.6.17, this field is no longer maintained, and is hard coded as 0 */
	//	/** 22 */ long long starttime;           /** The time in jiffies the process started after system boot */
	//	/** 23 */ unsigned long vsize;           /** Virtual memory size in bytes */
	//	/** 24 */ long rss;                      /** Resident Set Size: number of pages the process has in real memory, minus 3 for administrative purposes */
	//	/** 25 */ unsigned long rlim;            /** Current limit in bytes on the rss of the process (usually 4294967295 on i386) */
	//	/** 26 */ unsigned long startcode;       /** The address above which program text can run */
	//	/** 27 */ unsigned long endcode;         /** The address below which program text can run */
	//	/** 28 */ unsigned long startstack;      /** The address of the start of the stack */
	//	/** 29 */ unsigned long kstkesp;         /** The current value of esp (stack pointer), as found in the kernel stack page for the process */
	//	/** 30 */ unsigned long kstkeip;         /** The current EIP (instruction pointer) */
	//	/** 31 */ unsigned long signal;          /** The bitmap of pending signals */
	//	/** 32 */ unsigned long blocked;         /** The bitmap of blocked signals */
	//	/** 33 */ unsigned long sigignore;       /** The bitmap of ignored signals */
	//	/** 34 */ unsigned long sigcatch;        /** The bitmap of caught signals */
	//	/** 35 */ unsigned long nswap;           /** Number of pages swapped (not maintained). */
	//	/** 36 */ unsigned long cnswap;          /** Cumulative nswap for child processes (not maintained) */
	//	/** 37 */ int exit_signal;               /** Signal to be sent to parent when we die (since Linux 2.1.22) */
	//	/** 38 */ int processor;                 /** CPU number last executed on (since Linux 2.2.8) */
	//}process_info_t;   

	char buff[256];
	FILE*fd;
	pid_t selfpid = getpid();
	printf("pid:%d\n",selfpid);
	char filename[30]={0};
	snprintf(filename,20,"/proc/%d/status",selfpid);
	fd = fopen("/proc/self/status","r");
	printf("process:\n");
	for(int i=0;i<30;i++)
	{
		fgets(buff,sizeof(buff),fd);
		printf("%s",buff);
	}
	printf("%s\n",buff);
}
void highModule::startgetipTimer()
{
	if(m_timer_getuserip)
		timerClear(m_timer_getuserip);
	m_timer_getuserip = timerStart(timer_getuserip,2000);
}
void highModule::cleargetiptimer()
{
	if(m_timer_getuserip)
		timerClear(m_timer_getuserip);
}