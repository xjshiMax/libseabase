/**********************************************************************
  Function : 串口通信基础类实现文件
  CopyRight: ht
  Author   : ylshan
  ========================= Modified list ============================  
  Version    : v1.0.0
  Author     : ylshan
  Modify Date: 2010-7-27
  Mender     : ylshan
  Why        : Create
  How        :
  Attention  :
 **********************************************************************/
#ifdef WIN32

#include "CComDevBase.h"
#include <stdio.h>
CComDevBaseSync::CComDevBaseSync()
{

	// 设置超时参数
	m_iTimeOuts.ReadIntervalTimeout			= 500;
	m_iTimeOuts.ReadTotalTimeoutMultiplier	= 500;
	m_iTimeOuts.ReadTotalTimeoutConstant	= 3000;
	m_iTimeOuts.WriteTotalTimeoutMultiplier = 10;
	m_iTimeOuts.WriteTotalTimeoutConstant	= 100;

	m_hCom = 0;			//端口句柄

}
CComDevBaseSync::~CComDevBaseSync()
{

}

// 设置串口通信参数
int CComDevBaseSync::iSetComParam(stComDevParam p_stComDevParam)
{
	memcpy(&m_stComDevParam, &p_stComDevParam, sizeof(stComDevParam));

	return SUCCESS;
}
// 开启串口
int CComDevBaseSync::iOpenPort()
{
	BOOL bSuccess;
	char l_acPort[20]={0x00};	// 端口名称
	char l_acShow[50]={0x00};	// 错误描述
	
	DWORD iBytesLength=0;
	DWORD l_dwErrorCode=0;
	
	// 为了增加对COM10及以上串行端口的支持，微软规定，如果要访问这样的设备，应使用这样的文件名（以COM10为例）：\\.\COM10
	if (m_stComDevParam.iPort > 9 )
	{
		sprintf( l_acPort, "\\\\.\\COM%d", m_stComDevParam.iPort);
	}
	else
	{
		sprintf( l_acPort, "COM%d", m_stComDevParam.iPort);
	}

	// 防止重复调用的问题
	if (m_hCom)
	{
		sprintf(l_acShow, "%s串口已经打开 重复调用!",l_acPort);
		OutputDebugString(l_acShow);
		return SUCCESS;
	}
	
	// 打开端口
	// 采用异步方式的串口通信必须使用 第二个参数为GENERIC_READ | GENERIC_WRITE
	// OPEN_EXISTING方式 FILE_ATTRIBUTE_NORMAL->变成FILE_FLAG_OVERLAPPED 最后一个为异步事件(填充到结构 LPOVERLAPPED中的) 
	// 如果采用异步可以使用等待事件的方式实现同步,一旦文件操作成功将置事件为有信号状态
	m_hCom = CreateFile(l_acPort, GENERIC_READ | GENERIC_WRITE,
		0, NULL, 
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL );
	
	if (m_hCom == INVALID_HANDLE_VALUE)
	{
		l_dwErrorCode = GetLastError();
		if (ERROR_FILE_NOT_FOUND == l_dwErrorCode)
		{
			sprintf(l_acShow, "%s端口打开错误[未找到串口]! 错误码:%d",l_acPort, l_dwErrorCode);
			OutputDebugString(l_acShow);
		}
		else if (ERROR_ACCESS_DENIED == l_dwErrorCode)
		{
			sprintf(l_acShow, "%s端口打开错误[串口被占用]! 错误码:%d",l_acPort, l_dwErrorCode);
			OutputDebugString(l_acShow);
		}
		else
		{
			sprintf(l_acShow, "%s端口打开错误[串口异常]! 错误码:%d",l_acPort, l_dwErrorCode);
			OutputDebugString(l_acShow);
		}
		
		CloseHandle(m_hCom);
		m_hCom = NULL;
		return l_dwErrorCode;
	}
	
	SetupComm(m_hCom, 1024, 1024);									// 设置端口缓冲
	
	SetCommTimeouts(m_hCom, &m_iTimeOuts);							// 设置超时控制		
	
	bSuccess = GetCommState(m_hCom, &m_dcbCom);						// 获得当前串口配置
	
	// 串口配置信息
	m_dcbCom.BaudRate	= m_stComDevParam.dwBoud;					// 设置波特率 
	m_dcbCom.ByteSize	= m_stComDevParam.byByteSize;				// 数据位, 8bit
	m_dcbCom.Parity		= m_stComDevParam.byParity;					// 校验, 无
	m_dcbCom.StopBits	= m_stComDevParam.byStopBits;				// 停止位, 1位
	
	bSuccess = SetCommState(m_hCom, &m_dcbCom);						// 配置串口

	// 清除缓冲区数据
	PurgeComm(m_hCom, PURGE_TXCLEAR);

	return l_dwErrorCode;
}
// 关闭串口
int CComDevBaseSync::iClosePort()
{
	if (m_hCom)
	{
		CloseHandle(m_hCom);
		m_hCom = NULL;
		OutputDebugString("关闭句柄成功");
	}
	else
	{
		OutputDebugString(("句柄为空不需要关闭"));
	}

	return SUCCESS;
}

// 发送命令
int CComDevBaseSync::iSendCmd(void *p_chCutPaperCode, DWORD p_dwBytes)
{
	int l_iRet=0;

	if (!m_hCom)
	{
		OutputDebugString("串口未打开");
		return COM_NOT_INIT;
	}

	DWORD p_dwBytesWritten = 0;

	l_iRet = WriteFile(m_hCom, p_chCutPaperCode, p_dwBytes, &p_dwBytesWritten, NULL);

//	if (l_iRet == 0)
//	{
//		l_iRet = FAIL;
//	}
//	else l_iRet = SUCCESS;

	OutputDebugString((LPCSTR)p_chCutPaperCode);

//	return SUCCESS;

	return p_dwBytesWritten;
}

// 接受命令结果信息
int CComDevBaseSync::iRecvResult(char *p_chCutPaperCode, int p_iLen, DWORD& p_dwBytes)
{
	int l_iRet=0;

	if (!m_hCom)
	{
		OutputDebugString("串口未打开");
		return COM_NOT_INIT;
	}

 	l_iRet = ReadFile(m_hCom, p_chCutPaperCode, p_iLen, &p_dwBytes, NULL);

	if (l_iRet == 0)
	{
		l_iRet = FAIL;
	}
	else l_iRet = SUCCESS;

	return SUCCESS;
}
// 发送并接受命令信息
int CComDevBaseSync::iSendAndRecvCmd(char *p_chCutPaperCode, DWORD p_dwBytes)
{

	return SUCCESS;
}
// 清理接受缓冲区
int CComDevBaseSync::iClearSendBuff()
{
	if (!m_hCom)
	{
		OutputDebugString("串口未打开");
		return COM_NOT_INIT;
	}

	// 清除缓冲区数据
	PurgeComm(m_hCom, PURGE_TXCLEAR);
	return SUCCESS;
}
// 清理发送缓冲区
int CComDevBaseSync::iClearRecvBuff()
{
	if (!m_hCom)
	{
		OutputDebugString("串口未打开");
		return COM_NOT_INIT;
	}

	// 清除缓冲区数据
	PurgeComm(m_hCom, PURGE_RXCLEAR);
	return SUCCESS;

}


////////////////////////////////////////////////////////异步线程/////////////////////////////////////////////////////////
// 构造函数
CComDevBaseAsynTrd::CComDevBaseAsynTrd()
{
	// 设置超时参数
	m_iTimeOuts.ReadIntervalTimeout			= 10;
	m_iTimeOuts.ReadTotalTimeoutMultiplier	= 0;
	m_iTimeOuts.ReadTotalTimeoutConstant	= 0;
	m_iTimeOuts.WriteTotalTimeoutMultiplier = 20;
	m_iTimeOuts.WriteTotalTimeoutConstant	= 100;

	memset(&m_stRead,  0, sizeof(m_stRead));
	memset(&m_stWrite, 0, sizeof(m_stWrite));
	
	m_stRead.hEvent  = CreateEvent(NULL, true, false, NULL);
	m_stWrite.hEvent = CreateEvent(NULL, true, false, NULL);

	m_hCom = 0;			// 端口句柄
	m_hWnd = NULL;
	m_hTrd = NULL;
	
	memset(&m_stWait, 0, sizeof(m_stWait));
	m_stWait.hEvent = CreateEvent(NULL, true, false, NULL);

}
// 析构函数
CComDevBaseAsynTrd::~CComDevBaseAsynTrd()
{
	iClosePort();
}

// 设置串口通信参数
int CComDevBaseAsynTrd::iSetComParam(stComDevParam p_stComDevParam)
{
	memcpy(&m_stComDevParam, &p_stComDevParam, sizeof(stComDevParam));

	return SUCCESS;
}
// 开启串口
int CComDevBaseAsynTrd::iOpenPort()
{
	BOOL bSuccess;
	char l_acPort[20]={0x00};	// 端口名称
	char l_acShow[50]={0x00};	// 错误描述
	
	DWORD iBytesLength=0;
	DWORD l_dwErrorCode=0;
	
	// 为了增加对COM10及以上串行端口的支持，微软规定，如果要访问这样的设备，应使用这样的文件名（以COM10为例）：\\.\COM10
	if (m_stComDevParam.iPort > 9 )
	{
		sprintf( l_acPort, "\\\\.\\COM%d", m_stComDevParam.iPort);
	}
	else
	{
		sprintf( l_acPort, "COM%d", m_stComDevParam.iPort);
	}

	// 防止重复调用的问题
	if (m_hCom)
	{
		sprintf(l_acShow, "%s串口已经打开 重复调用!",l_acPort);
		OutputDebugString(l_acShow);
		return SUCCESS;
	}
	
	// 打开端口
	// 采用异步方式的串口通信必须使用 第二个参数为GENERIC_READ | GENERIC_WRITE
	// OPEN_EXISTING方式 FILE_ATTRIBUTE_NORMAL->变成FILE_FLAG_OVERLAPPED 最后一个为异步事件(填充到结构 LPOVERLAPPED中的) 
	// 如果采用异步可以使用等待事件的方式实现同步,一旦文件操作成功将置事件为有信号状态
	m_hCom = CreateFile(l_acPort, GENERIC_READ | GENERIC_WRITE,
		0, NULL, 
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL );
	
	if (m_hCom == INVALID_HANDLE_VALUE)
	{
		l_dwErrorCode = GetLastError();
		if (ERROR_FILE_NOT_FOUND == l_dwErrorCode)
		{
			sprintf(l_acShow, "%s端口打开错误[未找到串口]! 错误码:%d",l_acPort, l_dwErrorCode);
			OutputDebugString(l_acShow);
		}
		else if (ERROR_ACCESS_DENIED == l_dwErrorCode)
		{
			sprintf(l_acShow, "%s端口打开错误[串口被占用]! 错误码:%d",l_acPort, l_dwErrorCode);
			OutputDebugString(l_acShow);
		}
		else
		{
			sprintf(l_acShow, "%s端口打开错误[串口异常]! 错误码:%d",l_acPort, l_dwErrorCode);
			OutputDebugString(l_acShow);
		}
		
		CloseHandle(m_hCom);
		m_hCom = NULL;
		return FAIL;
	}
	
	SetupComm(m_hCom, 1024, 1024);									// 设置端口缓冲
	
	SetCommTimeouts(m_hCom, &m_iTimeOuts);							// 设置超时控制		
	
	bSuccess = GetCommState(m_hCom, &m_dcbCom);						// 获得当前串口配置
	
	// 串口配置信息
	m_dcbCom.BaudRate	= m_stComDevParam.dwBoud;					// 设置波特率 
	m_dcbCom.ByteSize	= m_stComDevParam.byByteSize;				// 数据位, 8bit
	m_dcbCom.Parity		= m_stComDevParam.byParity;					// 校验, 无
	m_dcbCom.StopBits	= m_stComDevParam.byStopBits;				// 停止位, 1位
	
	bSuccess = SetCommState(m_hCom, &m_dcbCom);						// 配置串口

	// 清除缓冲区数据
	PurgeComm(m_hCom, PURGE_TXCLEAR);

	// 创建线程
	m_bTrdFlag = true; 
	DWORD id;
	m_hTrd = CreateThread(NULL, 0, GetComMessageTrd, this, 0, &id); //辅助线程
	if(!m_hTrd)
	{
		CloseHandle(m_hCom);
		m_hCom = INVALID_HANDLE_VALUE;
		l_dwErrorCode = FAIL;
	}
	else
		l_dwErrorCode=SUCCESS;

	return l_dwErrorCode;
}
// 关闭串口
int CComDevBaseAsynTrd::iClosePort()
{
	if (m_hCom)
	{
		CloseHandle(m_hCom);
		OutputDebugString("关闭句柄成功");

		m_bTrdFlag = false;
		SetCommMask(m_hCom, 0);
		ResetEvent(m_stWait.hEvent);
		
		if(WaitForSingleObject(m_hTrd, 100) != WAIT_OBJECT_0)
			TerminateThread(m_hTrd, 0);
		
		CloseHandle(m_hCom);
		CloseHandle(m_hTrd);
		
		if(m_stRead.hEvent != INVALID_HANDLE_VALUE)
			CloseHandle(m_stRead.hEvent);
		
		if(m_stWrite.hEvent != INVALID_HANDLE_VALUE)
			CloseHandle(m_stWrite.hEvent);

		m_hTrd = NULL;
		m_hCom = INVALID_HANDLE_VALUE;

		if(m_stWait.hEvent != INVALID_HANDLE_VALUE)
			CloseHandle(m_stWait.hEvent);
	}
	else
	{
		OutputDebugString(("句柄为空不需要关闭"));
	}

	return SUCCESS;
}

// 发送命令
int CComDevBaseAsynTrd::iSendCmd(char *p_chCutPaperCode, DWORD p_dwBytes)
{
	if (!m_hCom)
	{
		OutputDebugString("串口未打开");
		return COM_NOT_INIT;
	}
	
	DWORD  error;
	if(ClearCommError(m_hCom, &error, NULL) && error > 0)	// 清除错误
		PurgeComm(m_hCom, PURGE_TXABORT | PURGE_TXCLEAR);	
	
	DWORD p_dwBytesWritten = 0;

	if(!WriteFile(m_hCom, p_chCutPaperCode, p_dwBytes, &p_dwBytesWritten, &m_stWrite))
		if(GetLastError() != ERROR_IO_PENDING)
			p_dwBytes = 0;
		
	OutputDebugString(p_chCutPaperCode);
		
//	return SUCCESS;

	return p_dwBytesWritten;
}

// 接受命令结果信息
int CComDevBaseAsynTrd::iRecvResult(char *p_chCutPaperCode, DWORD& p_dwBytes)
{
	if (!m_hCom)
	{
		OutputDebugString("串口未打开");
		return COM_NOT_INIT;
	}

	p_chCutPaperCode[0] = '\0';
	
	COMSTAT  stat;
	DWORD error=0;
	
	if(ClearCommError(m_hCom, &error, &stat) && error > 0)	// 清除错误
	{
		PurgeComm(m_hCom, PURGE_RXABORT | PURGE_RXCLEAR);	// 清除输入缓冲区
		return 0;
	}
	
	if(!stat.cbInQue)// 缓冲区无数据
		return 0;
	
	p_dwBytes = min((int)(p_dwBytes - 1), (int)stat.cbInQue);
	
	if(!ReadFile(m_hCom, p_chCutPaperCode, 256, &p_dwBytes, &m_stRead)) // 2000 下 ReadFile 始终返回 True
	{
		if(GetLastError() == ERROR_IO_PENDING) // 结束异步I/O
		{
			if(!GetOverlappedResult(m_hCom, &m_stRead, &p_dwBytes, false))
			{
				if(GetLastError() != ERROR_IO_INCOMPLETE)// 其他错误
					p_dwBytes = 0;
			}
		}
		else
			p_dwBytes = 0;
	}
	
	p_chCutPaperCode[p_dwBytes] = '\0';

	return SUCCESS;
}
// 发送并接受命令信息
int CComDevBaseAsynTrd::iSendAndRecvCmd(char *p_chCutPaperCode, DWORD p_dwBytes)
{

	return SUCCESS;
}
// 清理接受缓冲区
int CComDevBaseAsynTrd::iClearSendBuff()
{
	if (!m_hCom)
	{
		OutputDebugString("串口未打开");
		return COM_NOT_INIT;
	}

	// 清除缓冲区数据
	PurgeComm(m_hCom, PURGE_TXCLEAR);
	return SUCCESS;
}
// 清理发送缓冲区
int CComDevBaseAsynTrd::iClearRecvBuff()
{
	if (!m_hCom)
	{
		OutputDebugString("串口未打开");
		return COM_NOT_INIT;
	}

	// 清除缓冲区数据
	PurgeComm(m_hCom, PURGE_RXCLEAR);
	return SUCCESS;

}

// 线程控制函数
// 挂起
bool CComDevBaseAsynTrd::bSuspend()
{
	return m_hTrd != NULL ? SuspendThread(m_hTrd) != 0xFFFFFFFF : false;
}
// 恢复
bool CComDevBaseAsynTrd::bResume()
{
	return m_hTrd != NULL ? ResumeThread(m_hTrd) != 0xFFFFFFFF : false;
}
// 获取线程句柄
HANDLE CComDevBaseAsynTrd::hGetTrdHandle()
{
	return m_hTrd;
}
// 设置串口消息窗口句柄
void CComDevBaseAsynTrd::vSetMessageHwnd(HWND p_hWnd)
{
	m_hWnd = p_hWnd;
}
// 消息发送
void CComDevBaseAsynTrd::OnComRecv()
{
	// 这个是基于消息响应的 需要窗口句柄
	
	if(m_hWnd)
		PostMessage(m_hWnd, ON_COM_RECEIVE, WPARAM(m_stComDevParam.iPort), LPARAM(0));
		
	// 在实际使用中作为单独模块上层很难使用消息处理机制 而是采用轮询的方式进行
	/*char p_chCutPaperCode[256]={0x00};
	DWORD p_dwBytes;
	iRecvResult(p_chCutPaperCode, p_dwBytes);*/
	
}
// 辅助线程
DWORD WINAPI CComDevBaseAsynTrd::GetComMessageTrd(LPVOID p_para)
{
	CComDevBaseAsynTrd *l_pcom = (CComDevBaseAsynTrd *)p_para;	
	
	// 设置关心的事件信息
	if(!SetCommMask(l_pcom->m_hCom, EV_RXCHAR | EV_ERR))
		return 0;
	
	COMSTAT		l_stat;
	DWORD		l_dwerror;
	
	for(DWORD l_dwlength, l_dwmask = 0; l_pcom->m_bTrdFlag && l_pcom->m_hCom!=INVALID_HANDLE_VALUE; l_dwmask = 0)
	{
		// 等待串口事件
		if(!WaitCommEvent(l_pcom->m_hCom, &l_dwmask, &l_pcom->m_stWait))
		{
			if(GetLastError() == ERROR_IO_PENDING) // 错误为数据正在发送 属正常现象
			{
				GetOverlappedResult(l_pcom->m_hCom, &l_pcom->m_stWait, &l_dwlength, true); // 获取最后一次操作的结果信息
			}
		}
		
		if(l_dwmask & EV_ERR) // == EV_ERR
			ClearCommError(l_pcom->m_hCom, &l_dwerror, &l_stat); // 清除串口错误信息
		
		if(l_dwmask & EV_RXCHAR) // == EV_RXCHAR
		{
			ClearCommError(l_pcom->m_hCom, &l_dwerror, &l_stat); // 清楚串口错误信息
			l_pcom->OnComRecv();
		}
	}
	
	return SUCCESS;
}

#endif
