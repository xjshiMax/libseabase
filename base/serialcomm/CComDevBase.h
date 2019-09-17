/**********************************************************************
  Function : 串口通信基础类定义文件
  CopyRight: ht
  Author   : ylshan
  ========================= Modified list ============================  
  Version    : v1.0.0
  Author     : ylshan
  Modify Date: 2010-7-27
  Mender     : ylshan
  Why        : Create
  How        :
  Attention  : 这里定义了两个串口通信类 同步通信使用CComDevBaseSync类 
				异步通信使用线程处理类 CComDevBaseAsynTrd
 **********************************************************************/
#ifdef WIN32

#ifndef COMDEVBASE_H
#define COMDEVBASE_H

#define SUCCESS	0
#define FAIL	1

//当接受到数据送到窗口的消息
#define ON_COM_RECEIVE WM_USER + 618	 //	 WPARAM 端口号
#include "basictypes.hpp"
#include <WinSock2.h>
#include <Windows.h>
// 串口通信参数结构体
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
		byParity=NOPARITY;			// 效验位 无
		byStopBits=ONESTOPBIT;		// 停止位 1
	}
};

// 错误码定义
#define ERRORBASE					10000					// 错误码基值
#define COM_BE_USEING				1+ERRORBASE				// 串口被占用
#define COM_NOT_FOUND				2+ERRORBASE				// 串口未找到
#define COM_NOT_INIT				3+ERRORBASE				// 串口未初始化

// 同步处理的串口通信类
class CComDevBaseSync
{

public:
	COMMTIMEOUTS	m_iTimeOuts;				// 超时设置
	DCB				m_dcbCom;					// 串口配置信息

	CComDevBaseSync();
	~CComDevBaseSync();

	// 设置串口通信参数
	int iSetComParam(stComDevParam);
	// 开启串口
	int iOpenPort();
	// 关闭串口
	int iClosePort();
	// 发送命令
	int iSendCmd(void *, unsigned long);
	// 接受命令结果信息
	int iRecvResult(char *, int, unsigned long&);
	// 发送并接受命令信息
	int iSendAndRecvCmd(char *, unsigned long);
	// 清理接受缓冲区
	int iClearSendBuff();
	// 清理发送缓冲区
	int iClearRecvBuff();

protected:
	HANDLE			m_hCom;						// 串口句柄
	stComDevParam   m_stComDevParam;			// 串口参数
	
private:

};

// 异步多线程串口处理类(基于重叠IO)
class CComDevBaseAsynTrd
{
	
public:
	COMMTIMEOUTS	m_iTimeOuts;				// 超时设置
	DCB				m_dcbCom;					// 串口配置信息
	
	CComDevBaseAsynTrd();
	~CComDevBaseAsynTrd();
	
	// 设置串口通信参数
	int iSetComParam(stComDevParam);
	// 开启串口
	int iOpenPort();
	// 关闭串口
	int iClosePort();
	// 发送命令
	int iSendCmd(char *, unsigned long);
	// 接受命令结果信息
	int iRecvResult(char *, unsigned long&);
	// 发送并接受命令信息
	int iSendAndRecvCmd(char *, unsigned long);
	// 清理接受缓冲区
	int iClearSendBuff();
	// 清理发送缓冲区
	int iClearRecvBuff();


	// 线程控制函数
	// 挂起
	bool bSuspend();
	// 恢复
	bool bResume();
	// 获取线程句柄
	HANDLE hGetTrdHandle();
	// 设置串口消息窗口句柄
	void vSetMessageHwnd(HWND);
	// 消息发送
	void OnComRecv();
		
protected:
	HANDLE			m_hCom;						// 串口句柄
	stComDevParam   m_stComDevParam;			// 串口参数
	volatile bool	m_bTrdFlag;					// 线程运行循环标志
	OVERLAPPED		m_stWait;					// WaitCommEvent use
	OVERLAPPED		m_stRead, m_stWrite;		// 重叠I/O
	
private:
	HWND			m_hWnd;						// 窗口句柄
	HANDLE			m_hTrd;						// 辅助线程的句柄

	//监视线程
	static unsigned long WINAPI GetComMessageTrd(LPVOID para);
	
};

#endif

#endif
