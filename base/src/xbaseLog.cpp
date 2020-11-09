///////////////////////////////////////////////////////////////////////
/* 文件名： xbaseLog.cpp
 文件作用：		
    实现配置文件数据的读取功能、存放全局变量和全局静态方法。   
//-------------------------------------------------------------------
 修改历史记录：
    修改时间      2020-11-9
    修改人        xjshi
    修改内容概要  
*/
///////////////////////////////////////////////////////////////////////

//#include "stdafx.h"

#include <sstream>
#include "xbaseLog.h"


#define SLASH "/"

namespace SEABASE{


	xbaseLog::xbaseLog()
	{
		m_logDate = "";
		m_logPath = "../log/";
		m_logName = "log";
		m_logFile = NULL;
        m_loglevel = LOG_DEBUG;
        m_loglevelstr = "DEBUG";
	}
	
	xbaseLog::xbaseLog(string logname)
	{
		m_logDate = "";
		m_logPath = "../log/";
		m_logName = logname;
		m_logFile = NULL;	
        loglevel=LOG_DEBUG;
	}

	xbaseLog::~xbaseLog()
	{
	   closelogFile();
	}

	void xbaseLog::setLogName(string strLogName)
	{
		m_logName = strLogName;
	}
     void xbaseLog::setLoglevel(int level)
     {
         switch(level)
         {
         case LOG_ERROR:
             {
                 m_loglevel = LOG_ERROR;
                 m_loglevelstr = "ERROR";
             }
             break;
         case LOG_INFO:
             {
                 m_loglevel = LOG_INFO;
                 m_loglevelstr = "INFO";
             }
             break;
         case LOG_DEBUG:
             {
                 m_loglevel = LOG_DEBUG;
                 m_loglevelstr = "DEBUG";
             }
             break;
         }
     }
	void xbaseLog::setLogModule(string strLogName)
	{
		m_logName = strLogName;
	}

	void xbaseLog::setLogPath(string strLogPath)
	{
		m_logPath = strLogPath;

		if (xEFile::Exists(m_logPath))
		{
			xEFile::MakePath(m_logPath);
		}
	}
		////////////////////////////////////////////////////////////////
	// 函数名：  openLogFile()
	// 说明：   打开日志记录文件
	// 输入参数：无
	// 返回值：  无
	//-------------------------------------------------------------
	// 修改历史记录：
	//    修改时间      2012-03-16 
	//    修改人        zlc
	//    修改内容概要
	////////////////////////////////////////////////////////////////
	bool xbaseLog::openLogFile()
	{
		if(NULL != m_logFile)
			fclose(m_logFile);

		string strDate = xTimeUtil::get_date();

		if (!xEFile::Exists(m_logPath))
		{
			xEFile::MakePath(m_logPath);
		}

		string logDate = xTimeUtil::get_date();
		m_logDate = logDate;

		string dateDir = m_logPath + logDate + SLASH;
		if(!xEFile::Exists(dateDir))
		{
			xEFile::MakePath(dateDir);
		}

		if(!xEFile::Exists(m_logPath +  strDate + SLASH))
		{
			xEFile::MakePath(m_logPath + strDate + SLASH);
		}
		string filename = m_logPath + strDate + SLASH + m_logName + ".log";
		m_logFile = fopen(filename.c_str(), "at+");

		return (NULL != m_logFile);
	}


	////////////////////////////////////////////////////////////////
	// 函数名：  closelogFile()
	// 说明：   关闭志记录文件
	// 输入参数：无
	// 返回值：  无
	//-------------------------------------------------------------
	// 修改历史记录：
	//    修改时间      2012-03-16 
	//    修改人        zlc
	//    修改内容概要
	////////////////////////////////////////////////////////////////
	void xbaseLog::closelogFile()
	{
		if(NULL != m_logFile)
		{
			fprintf(m_logFile, "log file close\n\n");
			fflush(m_logFile);
			fclose(m_logFile);
		}

		m_logFile = NULL;
	}

	void xbaseLog::closeLogFile()
	{
		if(NULL != m_logFile)
		{
			fprintf(m_logFile, "log file close\n\n");
			fflush(m_logFile);
			fclose(m_logFile);
		}

		m_logFile = NULL;
	}

	void xbaseLog::close()
	{
		
	}
	////////////////////////////////////////////////////////////////
	// 函数名：  printLog()
	// 说明：   打印日志
	// 输入参数：format - 日志串
	// 返回值：  无
	//-------------------------------------------------------------
	// 修改历史记录：
	//    修改时间      2012-03-16 
	//    修改人        zlc
	//    修改内容概要
	////////////////////////////////////////////////////////////////
	void xbaseLog::printLog(const char* format, ...)
	{
		xGuard<xEmutex> lock(&log_mutex);


		enum{
			max_buf_length = 1000,
		};

		if(NULL == m_logFile)
		{
			if(!openLogFile())
				return;
		}


		try
		{
			string logDate = xTimeUtil::get_date();
			if(m_logDate.compare(logDate) != 0)
			{
				openLogFile();
				//m_currLogCount = 1;
			}

			if(NULL == m_logFile)
				return;

			char buffer[max_buf_length + 1] = {0};
			memset(buffer, 0x00, sizeof(buffer));
			va_list ap;
			va_start(ap, format);
			vsnprintf(buffer, max_buf_length, format, ap);
			va_end(ap);

		//	string content(buffer);
			fprintf(m_logFile, "%s  %s", xTimeUtil::getCurrentTimeStamp().c_str(), buffer);
			fflush(m_logFile);
		}
		catch (...){}
	}
    void xbaseLog::innerprintlog(const char* filename,int line,const char*strdsc,const char *format ,va_list ap)
    {
        enum{
            max_buf_length = 8192,
        };

        if(NULL == m_logFile)
        {
            if(!openLogFile())
                return;
        }

        if(m_logDate != xTimeUtil::get_date())
        {
            if(!openLogFile())
                return;
        }

        try
        {
            char buffer[max_buf_length + 1] = {0};
          //  va_list ap;
         //   va_start(ap, format);
            vsnprintf(buffer, max_buf_length, format, ap);
         //   va_end(ap);

            //	string content(buffer);
            fprintf(m_logFile, "[%s:%05d][%s][%s]%s", filename,line,strdsc,xTimeUtil::getCurrentTimeStamp().c_str(), buffer);
            fflush(m_logFile);
        }
        catch (...){}
    }
    void xbaseLog::printerror(const char* filename,int line,const char*format,...)
    {
		xGuard<xEmutex> lock(&log_mutex);
        if(m_loglevel < LOG_ERROR)
            return;
        va_list ap;
        va_start(ap,format);
        innerprintlog(filename,line,logdsc[LOG_ERROR].c_str(),format,ap);
        va_end(ap);
    }
    void xbaseLog::printinfo(const char* filename,int line,const char*format,...)
    {
		xGuard<xEmutex> lock(&log_mutex);
        if(m_loglevel < LOG_INFO)
            return;
        va_list ap;
        va_start(ap,format);
        innerprintlog(filename,line,logdsc[LOG_INFO].c_str(),format,ap);
        va_end(ap);
        //innerprintlog(filename,line,logdsc[LOG_INFO].c_str(),format);
    }
    void xbaseLog::printdebug(const char* filename,int line,const char*format,...)
    {
		xGuard<xEmutex> lock(&log_mutex);

        if(m_loglevel < LOG_DEBUG)
            return;
       // innerprintlog(filename,line,logdsc[LOG_DEBUG].c_str(),format);
        va_list ap;
        va_start(ap,format);
        innerprintlog(filename,line,logdsc[LOG_DEBUG].c_str(),format,ap);
        va_end(ap);
    }
	void xbaseLog::info(const char* format, ...)
	{
		xGuard<xEmutex> lock(&log_mutex);

        enum{
			max_buf_length = 8192,
		};

		if(NULL == m_logFile)
		{
			if(!openLogFile())
				return;
		}

		if(m_logDate != xTimeUtil::get_date())
		{
		    if(!openLogFile())
				return;
		}

		try
		{
			char buffer[max_buf_length + 1] = {0};
			va_list ap;
			va_start(ap, format);
			vsnprintf(buffer, max_buf_length, format, ap);
			va_end(ap);

		//	string content(buffer);
			fprintf(m_logFile, "%s  %s", xTimeUtil::getCurrentTimeStamp().c_str(), buffer);
			fflush(m_logFile);
		}
		catch (...){}
	}
	void xbaseLog::info(unsigned int index, const char* format, ...)
	{
		xGuard<xEmutex> lock(&log_mutex);


		enum{
			max_buf_length = 8192,
		};

		if(NULL == m_logFile)
		{
			if(!openLogFile())
				return;
		}

		if(m_logDate != xTimeUtil::get_date())
		{
		    if(!openLogFile())
				return;
		}

		try
		{
		    char buffer[max_buf_length + 1] = {0};
			va_list ap;
			va_start(ap, format);
			vsnprintf(buffer, max_buf_length, format, ap);
			va_end(ap);

		//	string content(buffer);
			string strInfo = xTimeUtil::getCurrentTimeStamp() + " " + buffer;
		    fprintf(m_logFile, "%s", strInfo.c_str());
			fflush(m_logFile);
		}
		catch (...){}
	}
	
	void xbaseLog::error(const char* format, ...)
	{
		enum{
			max_buf_length = 8192,
		};

		if(NULL == m_logFile)
		{
			if(!openLogFile())
				return;
		}

		if(m_logDate != xTimeUtil::get_date())
		{
		    if(!openLogFile())
				return;
		}

		try
		{
			char buffer[max_buf_length + 1] = {0};
			va_list ap;
			va_start(ap, format);
			vsnprintf(buffer, max_buf_length, format, ap);
			va_end(ap);

		//	string content(buffer);
			fprintf(m_logFile, "%s  %s", xTimeUtil::getCurrentTimeStamp().c_str(), buffer);
			fflush(m_logFile);
		}
		catch (...){}
	}

	void xbaseLog::error(unsigned int index, const char* format, ...)
	{
		enum{
			max_buf_length = 8192,
		};

		if(NULL == m_logFile)
		{
			if(!openLogFile())
				return;
		}

		if(m_logDate != xTimeUtil::get_date())
		{
		    if(!openLogFile())
				return;
		}

		try
		{
			char buffer[max_buf_length + 1] = {0};
			va_list ap;
			va_start(ap, format);
			vsnprintf(buffer, max_buf_length, format, ap);
			va_end(ap);

	//		string content(buffer);
			fprintf(m_logFile, "%s  %s", xTimeUtil::getCurrentTimeStamp().c_str(), buffer);
			fflush(m_logFile);
		}
		catch (...){}
	
	}

	void xbaseLog::warn(const char* format, ...)
	{
	    xGuard<xEmutex> lock(&log_mutex);

		enum{
			max_buf_length = 8192,
		};

		if(NULL == m_logFile)
		{
			if(!openLogFile())
				return;
		}

		if(m_logDate != xTimeUtil::get_date())
		{
		    if(!openLogFile())
				return;
		}

		try
		{
			char buffer[max_buf_length + 1] = {0};
			va_list ap;
			va_start(ap, format);
			vsnprintf(buffer, max_buf_length, format, ap);
			va_end(ap);

		//	string content(buffer);
			string strInfo = xTimeUtil::getCurrentTimeStamp() + " " + buffer;

		//	m_msgQueue.TryPut(strInfo);

			fprintf(m_logFile, "%s  %s", xTimeUtil::get_date().c_str(), buffer);
			fflush(m_logFile);
		}
		catch (...){}
	}

	void xbaseLog::writeLog(string strInfo)
	{
		enum{
			max_buf_length = 8192,
		};

		if(NULL == m_logFile)
		{
			if(!openLogFile())
				return;
		}

		if(m_logDate != xTimeUtil::get_date())
		{
		    if(!openLogFile())
				return;
		}

		try
		{
			fprintf(m_logFile, "%s", strInfo.c_str());
			fflush(m_logFile);
		}
		catch (...){}
	}
}
