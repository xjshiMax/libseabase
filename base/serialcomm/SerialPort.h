/*
 * Copyright (c) 2008,
 * All rights reserved.
 *
 * 文件名称：SerialPort.h 
 * 摘     要：简要描述本文件的内容
 * 文件描述： 串口通信
 *
 *
 * 当前版本：V1.0.0
 * 作    者：regbin
 * 修改内容：2012.3.7日创建
 *           
 * 完成日期：2012年03月07日
 *
 * 版本历史信息
 */


#ifndef __SERIALPORT__
#define __SERIALPORT__

#ifdef WIN32

//#define DLLAPI  __declspec(dllexport)
#include "Windows.h"

#else
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/select.h>

#define DLLAPI

#define INVALID_HANDLE_VALUE     -1
#define MAXSOCKFD                10
#define MAX_PATH                 260

#define FALSE   0
#define TRUE    1

typedef int            BOOL;     /* f */
typedef unsigned char  BYTE;

#ifndef DWORD
typedef unsigned long       DWORD;
#endif

typedef int HANDLE;
typedef unsigned short      WORD;

#define GETTIMEUSED(tv1, tv2)   ((tv1.tv_sec - tv2.tv_sec)*1000 + (tv1.tv_usec - tv2.tv_usec)/1000)

#endif

#define ERROR_COM_SUCC				(0)
#define ERROR_COM_PARAMETER_ERR		(-1)
#define ERROR_COM_COMM_ERR			(-2)
#define ERROR_COM_CANCELLED			(-3)
#define ERROR_COM_TIMEOUT                	(-4)          //超时

#define LOG_ALLOC_SAVE			(1024)

//#define LOGACTIVATE(a)	CSerialPortAutoLog _auto_log_this_Func(this, a)

typedef enum
{
	PURGE_IN = 1,
	PURGE_OUT = 2,
	PURGE_IO = 3,
}PURGE_FLAG;

#ifdef WIN32
#else

class CCAutoMutex
{

public :
	CCAutoMutex(pthread_mutex_t *Automutex)
	{
		mutex = Automutex;
		pthread_mutex_lock(mutex);
	}

	~CCAutoMutex()
	{
		pthread_mutex_unlock(mutex);
	}
private:
	pthread_mutex_t *mutex;
};

#endif

class CLock
{
public:
	CLock()
	{
#ifdef WIN32
	      InitializeCriticalSection(&pCritSect);
#else
	      pthread_mutex_init(&portmutex,NULL); 
#endif
	}
	~CLock()
	{
#ifdef WIN32
		DeleteCriticalSection(&pCritSect);
#else
#endif
	}
	
	void Lock()
	{
#ifdef WIN32
		EnterCriticalSection(&pCritSect);
#else		
		pthread_mutex_lock(&portmutex);
#endif
	}
	void UnLock()
	{
#ifdef WIN32
		LeaveCriticalSection(&pCritSect);
#else		
		pthread_mutex_unlock(&portmutex);
#endif
	}
	
private:
#ifdef WIN32  
	CRITICAL_SECTION  pCritSect;
#else	
	pthread_mutex_t portmutex;
#endif
};


// class DLLAPI CDriverLog
// {	
// public:
// 	CDriverLog(const char *pDeviceName);
// 	virtual ~CDriverLog();
// 
// 
// 
// 	/**************************************************************************
// 	* 函数名称： WriteFuncName(const char *pFuncName);
// 	* 功能描述： 写函数名称日志
// 	* 访问的表： 
// 	* 修改的表： 
// 	* 输入参数： char *pFuncName
// 	* 输出参数： 
// 	* 返 回 值： 0 成功     <0 失败
// 	* 其它说明： 
// 	* 修改日期    版本号     修改人	     修改内容
// 	* -----------------------------------------------
// 	* 2012/03/07  V1.0	     regbin	     创建文件
// 	**************************************************************************/
// 	 int WriteFuncName(const char *pFuncName);
// 
// 	/**************************************************************************
// 	* 函数名称： WriteFLSHLog(const char *pFlshStr);
// 	* 功能描述： 写函数名称日志
// 	* 访问的表： 
// 	* 修改的表： 
// 	* 输入参数： const char *pFlshStr
// 	* 输出参数： 
// 	* 返 回 值： 0 成功     <0 失败
// 	* 其它说明： 
// 	* 修改日期    版本号     修改人	     修改内容
// 	* -----------------------------------------------
// 	* 2012/03/07  V1.0	     regbin	     创建文件
// 	**************************************************************************/
// 	 int WriteFLSHLog(const char *pFlshStr);
// 
// 
// 	 /**************************************************************************
// 	 * 函数名称： WriteSendDataHex(const char *pSendStr, int nLen);
// 	 * 功能描述： 写发送数据到设备数据日志
// 	 * 访问的表： 
// 	 * 修改的表： 
// 	 * 输入参数： const char *pSendStr, int nLen
// 	 * 输出参数： 
// 	 * 返 回 值： 0 成功     <0 失败
// 	 * 其它说明： 
// 	 * 修改日期    版本号     修改人	     修改内容
// 	 * -----------------------------------------------
// 	 * 2012/03/07  V1.0	     regbin	     创建文件
// 	 **************************************************************************/	 
// 	 int WriteSendDataHex(const char *pSendStr, int nLen);
// 	 
// 	 
// 	 /**************************************************************************
// 	 * 函数名称： WriteSendDataHex(const char *pSendStr, int nLen);
// 	 * 功能描述： 写发送数据到设备数据日志
// 	 * 访问的表： 
// 	 * 修改的表： 
// 	 * 输入参数： const char *pReadStr, int nLen
// 	 * 输出参数： 
// 	 * 返 回 值： 0 成功     <0 失败
// 	 * 其它说明： 
// 	 * 修改日期    版本号     修改人	     修改内容
// 	 * -----------------------------------------------
// 	 * 2012/03/07  V1.0	     regbin	     创建文件
// 	 **************************************************************************/	 
// 	 int WriteReadDataHex(const char *pReadStr, int nLen);
// 	 
// 
// 	 /**************************************************************************
// 	 * 函数名称： WriteErrorLog(const char *pStr);
// 	 * 功能描述： 写错误日志
// 	 * 访问的表： 
// 	 * 修改的表： 
// 	 * 输入参数： cconst char *pStr
// 	 * 输出参数： 
// 	 * 返 回 值： 0 成功     <0 失败
// 	 * 其它说明： 
// 	 * 修改日期    版本号     修改人	     修改内容
// 	 * -----------------------------------------------
// 	 * 2012/03/08  V1.0	     regbin	     创建文件
// 	 **************************************************************************/	 
// 	 int WriteErrorLog(const char *pStr);
// 	 
// 	 /**************************************************************************
// 	 * 函数名称： WriteLogFile()
// 	 * 功能描述： 将数据写入文件中
// 	 * 访问的表： 
// 	 * 修改的表： 
// 	 * 输入参数： 
// 	 * 输出参数： 
// 	 * 返 回 值： 0 成功     <0 失败
// 	 * 其它说明： 
// 	 * 修改日期    版本号     修改人	     修改内容
// 	 * -----------------------------------------------
// 	 * 2012/03/07  V1.0	     regbin	     创建文件
// 	 **************************************************************************/	 
// 	 void WriteLogFile();
// 
// private:
// 	 /**************************************************************************
// 	 * 函数名称： GetLogTimeStr(char *pBuf)
// 	 * 功能描述： 获取系统时间日期分秒毫秒字符
// 	 * 访问的表： 
// 	 * 修改的表： 
// 	 * 输入参数： 
// 	 * 输出参数： char *pBuf
// 	 * 返 回 值： 0 成功     <0 失败
// 	 * 其它说明： 
// 	 * 修改日期    版本号     修改人	     修改内容
// 	 * -----------------------------------------------
// 	 * 2012/03/07  V1.0	     regbin	     创建文件
// 	 **************************************************************************/
// 	 void GetLocalTimeStr(char *pBuf);
// 
// 	 /**************************************************************************
// 	 * 函数名称： GetShortLocalTimeStr(char *pBuf)
// 	 * 功能描述： 获取系统时间分秒毫秒字符
// 	 * 访问的表： 
// 	 * 修改的表： 
// 	 * 输入参数： 
// 	 * 输出参数： char *pBuf
// 	 * 返 回 值： 0 成功     <0 失败
// 	 * 其它说明： 
// 	 * 修改日期    版本号     修改人	     修改内容
// 	 * -----------------------------------------------
// 	 * 2012/03/07  V1.0	     regbin	     创建文件
// 	 **************************************************************************/
// 	 void GetShortLocalTimeStr(char *pBuf);
// 
// 	 /**************************************************************************
// 	 * 函数名称： SaveLog(const char *pStr, int nLen)
// 	 * 功能描述： 写保存数据
// 	 * 访问的表： 
// 	 * 修改的表： 
// 	 * 输入参数： const char *pStr, int nLen
// 	 * 输出参数： 
// 	 * 返 回 值： 0 成功     <0 失败
// 	 * 其它说明： 
// 	 * 修改日期    版本号     修改人	     修改内容
// 	 * -----------------------------------------------
// 	 * 2012/03/07  V1.0	     regbin	     创建文件
// 	 **************************************************************************/	 
// 	 void SaveLog(const char *pStr, int nLen = -1);
// 
// private:
// 	char m_szBuf[MAX_PATH];
// 	char* m_pLogData;
// 	int m_nLogDataLen;
// 	int m_nAllLogLen;
// 	char m_szDeviceName[MAX_PATH];
// 
// };
// 

struct stComDevParam 
{
	int iPort;					// 串口号
	unsigned long dwBoud;				// 波特率
	unsigned char byByteSize;			// 数据位
	unsigned char byParity;				// 效验位
	unsigned char byStopBits;			// 停止位
	
	stComDevParam()
	{
		iPort=1;					// 串口号 1
		dwBoud=(unsigned long)9600;			// 波特率 9600
		byByteSize=(unsigned char)8;			// 数据位 8
		byParity=0;			// 效验位 无
		byStopBits=0;		// 停止位 1
	}
};

class CSerialPort
{

public:
    CSerialPort(const char * pDataLogFile);
	CSerialPort();
	virtual ~CSerialPort();

//protected:


	/**************************************************************************
	* 函数名称： OpenPort(const char* pComName,unsigned int uBaudRate, unsigned int uParity, unsigned int uByteSize, unsigned int uStopBits)
	* 功能描述： 打开串口
	* 访问的表： 
	* 修改的表： 
	* 输入参数： const char* pComName,const DWORD  dwpBaud
	* 输出参数： 
	* 返 回 值： 0 成功     <0 失败
	* 其它说明： 
	* 修改日期    版本号     修改人	     修改内容
	* -----------------------------------------------
	* 2013/01/23  V1.0	     regbin	     创建文件
	**************************************************************************/
    int OpenPort(const char* pComName,unsigned int uBaudRate, unsigned int uParity, unsigned int uByteSize, unsigned int uStopBits);




   	/**************************************************************************
	* 函数名称： WriteComm(const char *pBuf, unsigned long dwLength,unsigned long dwTimeout)
	* 功能描述： //读串口
	* 访问的表： 
	* 修改的表： 
	* 输入参数： unsigned long dwTimeout
	* 输出参数： char *pBuf, DWORD dwLength
	* 返 回 值： 0 成功     <0 失败
	* 其它说明： 
	* 修改日期    版本号     修改人	     修改内容
	* -----------------------------------------------
	* 2013/01/23  V1.0	     regbin	     创建文件
	**************************************************************************/	
    int WriteComm(const char *pBuf, unsigned long dwLength,unsigned long dwTimeout);

    	/**************************************************************************
	* 函数名称： ReadComm(char *pBuf, unsigned long dwLength,unsigned long dwTimeout)
	* 功能描述： //读串口
	* 访问的表： 
	* 修改的表： 
	* 输入参数： DWORD dwTimeout,DWORD dwIntervalTimeout = 250
	* 输出参数： char *pBuf, DWORD dwLength
	* 返 回 值： 0 成功     <0 失败
	* 其它说明： 
	* 修改日期    版本号     修改人	     修改内容
	* -----------------------------------------------
	* 2013/01/23  V1.0	     regbin	     创建文件
	**************************************************************************/	
    int ReadComm(char *pBuf, unsigned long dwLength,unsigned long dwTimeout,unsigned long  dwIntervalTimeout = 250);//读串口
	/**************************************************************************
	* 函数名称： WriteAndReadComm(const char *pWriteBuf, DWORD dwWriteLen, char *pReadBuf, DWORD dwReadLen,DWORD dwReadTimeout,DWORD dwReadInterval = 250, DWORD dwWriteTimeout = 1000)
	* 功能描述： //写读串口
	* 访问的表： 
	* 修改的表： 
	* 输入参数： const char *pWriteBuf, DWORD dwWriteLen,DWORD dwReadInterval = 250,DWORD dwWriteTimeout = 1000
	* 输出参数： char *pReadBuf, DWORD dwReadLen
	* 返 回 值： 0 成功     <0 失败
	* 其它说明： 
	* 修改日期    版本号     修改人	     修改内容
	* -----------------------------------------------
	* 2013/01/23  V1.0	     regbin	     创建文件
	**************************************************************************/	
 	int WriteAndReadComm(const char *pWriteBuf, unsigned long dwWriteLen, char *pReadBuf, unsigned long  dwReadLen, 
					unsigned long  dwReadTimeout, 
					unsigned long dwReadInterval = 250, 
					unsigned long  dwWriteTimeout = 1000);
    	/**************************************************************************
	* 函数名称： PurgeCommFlag(PURGE_FLAG Flag);
	* 功能描述： 清空读写缓冲区数据
	* 访问的表： 
	* 修改的表： 
	* 输入参数： PURGE_FLAG Flag
	* 输出参数： 
	* 返 回 值： 0 成功     <0 失败
	* 其它说明： 
	* 修改日期    版本号     修改人	     修改内容
	* -----------------------------------------------
	* 2013/01/23  V1.0	     regbin	     创建文件
	**************************************************************************/	
    void PurgeCommFlag(PURGE_FLAG Flag);

    
    	/**************************************************************************
	* 函数名称： ClosePort()
	* 功能描述： 关闭串口
	* 访问的表： 
	* 修改的表： 
	* 输入参数： 
	* 输出参数： 
	* 返 回 值： 0 成功     <0 失败
	* 其它说明： 
	* 修改日期    版本号     修改人	     修改内容
	* -----------------------------------------------
	* 2013/01/23  V1.0	     regbin	     创建文件
	**************************************************************************/
    void ClosePort();

  
 	/**************************************************************************
	* 函数名称： PortIsOpen()
	* 功能描述： 测试串口是否打开
	* 访问的表： 
	* 修改的表： 
	* 输入参数： PURGE_FLAG Flag
	* 输出参数： 
	* 返 回 值： 0 成功     <0 失败
	* 其它说明： 
	* 修改日期    版本号     修改人	     修改内容
	* -----------------------------------------------
	* 2013/01/23  V1.0	     regbin	     创建文件
	**************************************************************************/	   
    inline BOOL PortIsOpen() { return m_hComm != INVALID_HANDLE_VALUE; }

	// 设置串口通信参数
	int iSetComParam(stComDevParam p_stComDevParam);
	// 开启串口
	int iOpenPort();
	// 关闭串口
	int iClosePort();
	// 发送命令
	int iSendCmd(void *, unsigned long);
	// 接受命令结果信息
	int iRecvResult(char *, int, unsigned long& p_dwBytes, int timeOut);

	// 清理接受缓冲区
	int iClearSendBuff();
	// 清理发送缓冲区
	int iClearRecvBuff();

private:

	void BuildMode(const char **pComName);

	/**************************************************************************
	* 函数名称： SetWriteTimeOut(cDWORD dwTimeOut)
	* 功能描述： 设置写数据超时
	* 访问的表： 
	* 修改的表： 
	* 输入参数： 
	* 输出参数： const char **pComName
	* 返 回 值： 0 成功     <0 失败
	* 其它说明： 
	* 修改日期    版本号     修改人	     修改内容
	* -----------------------------------------------
	* 2012/03/08  V1.0	     regbin	     创建文件
	**************************************************************************/
	int SetWriteTimeOut(DWORD dwTimeOut);


	/**************************************************************************
	* 函数名称： SetReadTimeOut(DWORD dwTimeOut,DWORD dwIntervalTimeout)
	* 功能描述： 设置读数据超时
	* 访问的表： 
	* 修改的表： 
	* 输入参数： 
	* 输出参数： const char **pComName
	* 返 回 值： 0 成功     <0 失败
	* 其它说明： 
	* 修改日期    版本号     修改人	     修改内容
	* -----------------------------------------------
	* 2012/03/08  V1.0	     regbin	     创建文件
	**************************************************************************/
	int SetReadTimeOut(DWORD dwTimeOut,DWORD dwIntervalTimeout);

protected:
	HANDLE m_hComm;
	//CDriverLog m_Log;
	//friend class CSerialPortAutoLog;
	stComDevParam m_stComDevParam;
};

// #ifdef WIN32
// class _declspec(dllexport) CSerialPortAutoLog
// #else
// class CSerialPortAutoLog
// #endif
// {
// public:
// 	CSerialPortAutoLog(CSerialPort *pDevice, const char *pFuncName)
// 	{
// 		m_pDevice = pDevice;
// 		pDevice->m_Log.WriteFuncName(pFuncName);
// 	}
// 
// 	~CSerialPortAutoLog()
// 	{
// 		m_pDevice->m_Log.WriteLogFile();
// 	}
// 
// private:
// 	CSerialPort *m_pDevice;
// };
// 
#endif
