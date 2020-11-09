#pragma once
#include <string>
#include <stdio.h>
#include "xTimeuil.h"
#include "xEmutex.h"
#include "xEFile.h"
#ifdef WIN32
#include <io.h>
#define __FILENAME(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x
#else
#include <unistd.h>
#define __FILENAME(x) strrchr(x,'/')?strrchr(x,'/')+1:x
#include <string>
#include <string.h>
#include<stdarg.h>
#endif
namespace SEABASE{
	using std::string;


  
    const string logdsc[]={"ERROR","INFO","FLOW","DEBUG"};
#define logprefix __FILENAME(__FILE__),__LINE__
	class xbaseLog
	{
		//////////////////////////////////////////////////////////////////////////
			//method
	public:
		enum{
			LOG_ERROR = 0,
			LOG_INFO  = 1,
			LOG_FLOW  = 2,
			LOG_DEBUG = 3,
		}loglevel;
	public:
		xbaseLog();
		xbaseLog(string logname);
		~xbaseLog();
	public:
		void setLogName(string strLogPath);
        void setLoglevel(int level);
		void setLogModule(string strLogPath);
		void setLogPath(string strLogPath);
		void printLog(const char* format, ...);
		void info(const char* format, ...);
		void error(const char* format, ...);
          
        //日志打印改造
        void printerror(const char* filename,int line,const char*format,...);
        void printinfo(const char* filename,int line,const char*format,...);
        void printdebug(const char* filename,int line,const char*format,...);
        void innerprintlog(const char* filename,int line,const char*strdsc,const char *format ,va_list ap);

		bool openLogFile();
		void closelogFile();
		void closeLogFile();
		void close();
		void warn(const char* format, ...);
		void info(unsigned int index, const char* format, ...);
		void error(unsigned int index, const char* format, ...);
		void writeLog(string strInfo);
	private:
		string m_logDate;
		string m_logName;
		string m_logPath;
	//	string m_versionStr;
		FILE* m_logFile;
		xEmutex log_mutex;
        int m_loglevel;
        string m_loglevelstr;
	};
}
