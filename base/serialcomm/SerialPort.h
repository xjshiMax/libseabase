/*
 * Copyright (c) 2008,
 * All rights reserved.
 *
 * �ļ����ƣ�SerialPort.h 
 * ժ     Ҫ����Ҫ�������ļ�������
 * �ļ������� ����ͨ��
 *
 *
 * ��ǰ�汾��V1.0.0
 * ��    �ߣ�regbin
 * �޸����ݣ�2012.3.7�մ���
 *           
 * ������ڣ�2012��03��07��
 *
 * �汾��ʷ��Ϣ
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
#define ERROR_COM_TIMEOUT                	(-4)          //��ʱ

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
// 	* �������ƣ� WriteFuncName(const char *pFuncName);
// 	* ���������� д����������־
// 	* ���ʵı� 
// 	* �޸ĵı� 
// 	* ��������� char *pFuncName
// 	* ��������� 
// 	* �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// 	* ����˵���� 
// 	* �޸�����    �汾��     �޸���	     �޸�����
// 	* -----------------------------------------------
// 	* 2012/03/07  V1.0	     regbin	     �����ļ�
// 	**************************************************************************/
// 	 int WriteFuncName(const char *pFuncName);
// 
// 	/**************************************************************************
// 	* �������ƣ� WriteFLSHLog(const char *pFlshStr);
// 	* ���������� д����������־
// 	* ���ʵı� 
// 	* �޸ĵı� 
// 	* ��������� const char *pFlshStr
// 	* ��������� 
// 	* �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// 	* ����˵���� 
// 	* �޸�����    �汾��     �޸���	     �޸�����
// 	* -----------------------------------------------
// 	* 2012/03/07  V1.0	     regbin	     �����ļ�
// 	**************************************************************************/
// 	 int WriteFLSHLog(const char *pFlshStr);
// 
// 
// 	 /**************************************************************************
// 	 * �������ƣ� WriteSendDataHex(const char *pSendStr, int nLen);
// 	 * ���������� д�������ݵ��豸������־
// 	 * ���ʵı� 
// 	 * �޸ĵı� 
// 	 * ��������� const char *pSendStr, int nLen
// 	 * ��������� 
// 	 * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// 	 * ����˵���� 
// 	 * �޸�����    �汾��     �޸���	     �޸�����
// 	 * -----------------------------------------------
// 	 * 2012/03/07  V1.0	     regbin	     �����ļ�
// 	 **************************************************************************/	 
// 	 int WriteSendDataHex(const char *pSendStr, int nLen);
// 	 
// 	 
// 	 /**************************************************************************
// 	 * �������ƣ� WriteSendDataHex(const char *pSendStr, int nLen);
// 	 * ���������� д�������ݵ��豸������־
// 	 * ���ʵı� 
// 	 * �޸ĵı� 
// 	 * ��������� const char *pReadStr, int nLen
// 	 * ��������� 
// 	 * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// 	 * ����˵���� 
// 	 * �޸�����    �汾��     �޸���	     �޸�����
// 	 * -----------------------------------------------
// 	 * 2012/03/07  V1.0	     regbin	     �����ļ�
// 	 **************************************************************************/	 
// 	 int WriteReadDataHex(const char *pReadStr, int nLen);
// 	 
// 
// 	 /**************************************************************************
// 	 * �������ƣ� WriteErrorLog(const char *pStr);
// 	 * ���������� д������־
// 	 * ���ʵı� 
// 	 * �޸ĵı� 
// 	 * ��������� cconst char *pStr
// 	 * ��������� 
// 	 * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// 	 * ����˵���� 
// 	 * �޸�����    �汾��     �޸���	     �޸�����
// 	 * -----------------------------------------------
// 	 * 2012/03/08  V1.0	     regbin	     �����ļ�
// 	 **************************************************************************/	 
// 	 int WriteErrorLog(const char *pStr);
// 	 
// 	 /**************************************************************************
// 	 * �������ƣ� WriteLogFile()
// 	 * ���������� ������д���ļ���
// 	 * ���ʵı� 
// 	 * �޸ĵı� 
// 	 * ��������� 
// 	 * ��������� 
// 	 * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// 	 * ����˵���� 
// 	 * �޸�����    �汾��     �޸���	     �޸�����
// 	 * -----------------------------------------------
// 	 * 2012/03/07  V1.0	     regbin	     �����ļ�
// 	 **************************************************************************/	 
// 	 void WriteLogFile();
// 
// private:
// 	 /**************************************************************************
// 	 * �������ƣ� GetLogTimeStr(char *pBuf)
// 	 * ���������� ��ȡϵͳʱ�����ڷ�������ַ�
// 	 * ���ʵı� 
// 	 * �޸ĵı� 
// 	 * ��������� 
// 	 * ��������� char *pBuf
// 	 * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// 	 * ����˵���� 
// 	 * �޸�����    �汾��     �޸���	     �޸�����
// 	 * -----------------------------------------------
// 	 * 2012/03/07  V1.0	     regbin	     �����ļ�
// 	 **************************************************************************/
// 	 void GetLocalTimeStr(char *pBuf);
// 
// 	 /**************************************************************************
// 	 * �������ƣ� GetShortLocalTimeStr(char *pBuf)
// 	 * ���������� ��ȡϵͳʱ���������ַ�
// 	 * ���ʵı� 
// 	 * �޸ĵı� 
// 	 * ��������� 
// 	 * ��������� char *pBuf
// 	 * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// 	 * ����˵���� 
// 	 * �޸�����    �汾��     �޸���	     �޸�����
// 	 * -----------------------------------------------
// 	 * 2012/03/07  V1.0	     regbin	     �����ļ�
// 	 **************************************************************************/
// 	 void GetShortLocalTimeStr(char *pBuf);
// 
// 	 /**************************************************************************
// 	 * �������ƣ� SaveLog(const char *pStr, int nLen)
// 	 * ���������� д��������
// 	 * ���ʵı� 
// 	 * �޸ĵı� 
// 	 * ��������� const char *pStr, int nLen
// 	 * ��������� 
// 	 * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// 	 * ����˵���� 
// 	 * �޸�����    �汾��     �޸���	     �޸�����
// 	 * -----------------------------------------------
// 	 * 2012/03/07  V1.0	     regbin	     �����ļ�
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
	int iPort;					// ���ں�
	unsigned long dwBoud;				// ������
	unsigned char byByteSize;			// ����λ
	unsigned char byParity;				// Ч��λ
	unsigned char byStopBits;			// ֹͣλ
	
	stComDevParam()
	{
		iPort=1;					// ���ں� 1
		dwBoud=(unsigned long)9600;			// ������ 9600
		byByteSize=(unsigned char)8;			// ����λ 8
		byParity=0;			// Ч��λ ��
		byStopBits=0;		// ֹͣλ 1
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
	* �������ƣ� OpenPort(const char* pComName,unsigned int uBaudRate, unsigned int uParity, unsigned int uByteSize, unsigned int uStopBits)
	* ���������� �򿪴���
	* ���ʵı� 
	* �޸ĵı� 
	* ��������� const char* pComName,const DWORD  dwpBaud
	* ��������� 
	* �� �� ֵ�� 0 �ɹ�     <0 ʧ��
	* ����˵���� 
	* �޸�����    �汾��     �޸���	     �޸�����
	* -----------------------------------------------
	* 2013/01/23  V1.0	     regbin	     �����ļ�
	**************************************************************************/
    int OpenPort(const char* pComName,unsigned int uBaudRate, unsigned int uParity, unsigned int uByteSize, unsigned int uStopBits);




   	/**************************************************************************
	* �������ƣ� WriteComm(const char *pBuf, unsigned long dwLength,unsigned long dwTimeout)
	* ���������� //������
	* ���ʵı� 
	* �޸ĵı� 
	* ��������� unsigned long dwTimeout
	* ��������� char *pBuf, DWORD dwLength
	* �� �� ֵ�� 0 �ɹ�     <0 ʧ��
	* ����˵���� 
	* �޸�����    �汾��     �޸���	     �޸�����
	* -----------------------------------------------
	* 2013/01/23  V1.0	     regbin	     �����ļ�
	**************************************************************************/	
    int WriteComm(const char *pBuf, unsigned long dwLength,unsigned long dwTimeout);

    	/**************************************************************************
	* �������ƣ� ReadComm(char *pBuf, unsigned long dwLength,unsigned long dwTimeout)
	* ���������� //������
	* ���ʵı� 
	* �޸ĵı� 
	* ��������� DWORD dwTimeout,DWORD dwIntervalTimeout = 250
	* ��������� char *pBuf, DWORD dwLength
	* �� �� ֵ�� 0 �ɹ�     <0 ʧ��
	* ����˵���� 
	* �޸�����    �汾��     �޸���	     �޸�����
	* -----------------------------------------------
	* 2013/01/23  V1.0	     regbin	     �����ļ�
	**************************************************************************/	
    int ReadComm(char *pBuf, unsigned long dwLength,unsigned long dwTimeout,unsigned long  dwIntervalTimeout = 250);//������
	/**************************************************************************
	* �������ƣ� WriteAndReadComm(const char *pWriteBuf, DWORD dwWriteLen, char *pReadBuf, DWORD dwReadLen,DWORD dwReadTimeout,DWORD dwReadInterval = 250, DWORD dwWriteTimeout = 1000)
	* ���������� //д������
	* ���ʵı� 
	* �޸ĵı� 
	* ��������� const char *pWriteBuf, DWORD dwWriteLen,DWORD dwReadInterval = 250,DWORD dwWriteTimeout = 1000
	* ��������� char *pReadBuf, DWORD dwReadLen
	* �� �� ֵ�� 0 �ɹ�     <0 ʧ��
	* ����˵���� 
	* �޸�����    �汾��     �޸���	     �޸�����
	* -----------------------------------------------
	* 2013/01/23  V1.0	     regbin	     �����ļ�
	**************************************************************************/	
 	int WriteAndReadComm(const char *pWriteBuf, unsigned long dwWriteLen, char *pReadBuf, unsigned long  dwReadLen, 
					unsigned long  dwReadTimeout, 
					unsigned long dwReadInterval = 250, 
					unsigned long  dwWriteTimeout = 1000);
    	/**************************************************************************
	* �������ƣ� PurgeCommFlag(PURGE_FLAG Flag);
	* ���������� ��ն�д����������
	* ���ʵı� 
	* �޸ĵı� 
	* ��������� PURGE_FLAG Flag
	* ��������� 
	* �� �� ֵ�� 0 �ɹ�     <0 ʧ��
	* ����˵���� 
	* �޸�����    �汾��     �޸���	     �޸�����
	* -----------------------------------------------
	* 2013/01/23  V1.0	     regbin	     �����ļ�
	**************************************************************************/	
    void PurgeCommFlag(PURGE_FLAG Flag);

    
    	/**************************************************************************
	* �������ƣ� ClosePort()
	* ���������� �رմ���
	* ���ʵı� 
	* �޸ĵı� 
	* ��������� 
	* ��������� 
	* �� �� ֵ�� 0 �ɹ�     <0 ʧ��
	* ����˵���� 
	* �޸�����    �汾��     �޸���	     �޸�����
	* -----------------------------------------------
	* 2013/01/23  V1.0	     regbin	     �����ļ�
	**************************************************************************/
    void ClosePort();

  
 	/**************************************************************************
	* �������ƣ� PortIsOpen()
	* ���������� ���Դ����Ƿ��
	* ���ʵı� 
	* �޸ĵı� 
	* ��������� PURGE_FLAG Flag
	* ��������� 
	* �� �� ֵ�� 0 �ɹ�     <0 ʧ��
	* ����˵���� 
	* �޸�����    �汾��     �޸���	     �޸�����
	* -----------------------------------------------
	* 2013/01/23  V1.0	     regbin	     �����ļ�
	**************************************************************************/	   
    inline BOOL PortIsOpen() { return m_hComm != INVALID_HANDLE_VALUE; }

	// ���ô���ͨ�Ų���
	int iSetComParam(stComDevParam p_stComDevParam);
	// ��������
	int iOpenPort();
	// �رմ���
	int iClosePort();
	// ��������
	int iSendCmd(void *, unsigned long);
	// ������������Ϣ
	int iRecvResult(char *, int, unsigned long& p_dwBytes, int timeOut);

	// ������ܻ�����
	int iClearSendBuff();
	// �����ͻ�����
	int iClearRecvBuff();

private:

	void BuildMode(const char **pComName);

	/**************************************************************************
	* �������ƣ� SetWriteTimeOut(cDWORD dwTimeOut)
	* ���������� ����д���ݳ�ʱ
	* ���ʵı� 
	* �޸ĵı� 
	* ��������� 
	* ��������� const char **pComName
	* �� �� ֵ�� 0 �ɹ�     <0 ʧ��
	* ����˵���� 
	* �޸�����    �汾��     �޸���	     �޸�����
	* -----------------------------------------------
	* 2012/03/08  V1.0	     regbin	     �����ļ�
	**************************************************************************/
	int SetWriteTimeOut(DWORD dwTimeOut);


	/**************************************************************************
	* �������ƣ� SetReadTimeOut(DWORD dwTimeOut,DWORD dwIntervalTimeout)
	* ���������� ���ö����ݳ�ʱ
	* ���ʵı� 
	* �޸ĵı� 
	* ��������� 
	* ��������� const char **pComName
	* �� �� ֵ�� 0 �ɹ�     <0 ʧ��
	* ����˵���� 
	* �޸�����    �汾��     �޸���	     �޸�����
	* -----------------------------------------------
	* 2012/03/08  V1.0	     regbin	     �����ļ�
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
