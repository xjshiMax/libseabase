/**********************************************************************
  Function : ����ͨ�Ż�����ʵ���ļ�
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

	// ���ó�ʱ����
	m_iTimeOuts.ReadIntervalTimeout			= 500;
	m_iTimeOuts.ReadTotalTimeoutMultiplier	= 500;
	m_iTimeOuts.ReadTotalTimeoutConstant	= 3000;
	m_iTimeOuts.WriteTotalTimeoutMultiplier = 10;
	m_iTimeOuts.WriteTotalTimeoutConstant	= 100;

	m_hCom = 0;			//�˿ھ��

}
CComDevBaseSync::~CComDevBaseSync()
{

}

// ���ô���ͨ�Ų���
int CComDevBaseSync::iSetComParam(stComDevParam p_stComDevParam)
{
	memcpy(&m_stComDevParam, &p_stComDevParam, sizeof(stComDevParam));

	return SUCCESS;
}
// ��������
int CComDevBaseSync::iOpenPort()
{
	BOOL bSuccess;
	char l_acPort[20]={0x00};	// �˿�����
	char l_acShow[50]={0x00};	// ��������
	
	DWORD iBytesLength=0;
	DWORD l_dwErrorCode=0;
	
	// Ϊ�����Ӷ�COM10�����ϴ��ж˿ڵ�֧�֣�΢��涨�����Ҫ�����������豸��Ӧʹ���������ļ�������COM10Ϊ������\\.\COM10
	if (m_stComDevParam.iPort > 9 )
	{
		sprintf( l_acPort, "\\\\.\\COM%d", m_stComDevParam.iPort);
	}
	else
	{
		sprintf( l_acPort, "COM%d", m_stComDevParam.iPort);
	}

	// ��ֹ�ظ����õ�����
	if (m_hCom)
	{
		sprintf(l_acShow, "%s�����Ѿ��� �ظ�����!",l_acPort);
		OutputDebugString(l_acShow);
		return SUCCESS;
	}
	
	// �򿪶˿�
	// �����첽��ʽ�Ĵ���ͨ�ű���ʹ�� �ڶ�������ΪGENERIC_READ | GENERIC_WRITE
	// OPEN_EXISTING��ʽ FILE_ATTRIBUTE_NORMAL->���FILE_FLAG_OVERLAPPED ���һ��Ϊ�첽�¼�(��䵽�ṹ LPOVERLAPPED�е�) 
	// ��������첽����ʹ�õȴ��¼��ķ�ʽʵ��ͬ��,һ���ļ������ɹ������¼�Ϊ���ź�״̬
	m_hCom = CreateFile(l_acPort, GENERIC_READ | GENERIC_WRITE,
		0, NULL, 
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL );
	
	if (m_hCom == INVALID_HANDLE_VALUE)
	{
		l_dwErrorCode = GetLastError();
		if (ERROR_FILE_NOT_FOUND == l_dwErrorCode)
		{
			sprintf(l_acShow, "%s�˿ڴ򿪴���[δ�ҵ�����]! ������:%d",l_acPort, l_dwErrorCode);
			OutputDebugString(l_acShow);
		}
		else if (ERROR_ACCESS_DENIED == l_dwErrorCode)
		{
			sprintf(l_acShow, "%s�˿ڴ򿪴���[���ڱ�ռ��]! ������:%d",l_acPort, l_dwErrorCode);
			OutputDebugString(l_acShow);
		}
		else
		{
			sprintf(l_acShow, "%s�˿ڴ򿪴���[�����쳣]! ������:%d",l_acPort, l_dwErrorCode);
			OutputDebugString(l_acShow);
		}
		
		CloseHandle(m_hCom);
		m_hCom = NULL;
		return l_dwErrorCode;
	}
	
	SetupComm(m_hCom, 1024, 1024);									// ���ö˿ڻ���
	
	SetCommTimeouts(m_hCom, &m_iTimeOuts);							// ���ó�ʱ����		
	
	bSuccess = GetCommState(m_hCom, &m_dcbCom);						// ��õ�ǰ��������
	
	// ����������Ϣ
	m_dcbCom.BaudRate	= m_stComDevParam.dwBoud;					// ���ò����� 
	m_dcbCom.ByteSize	= m_stComDevParam.byByteSize;				// ����λ, 8bit
	m_dcbCom.Parity		= m_stComDevParam.byParity;					// У��, ��
	m_dcbCom.StopBits	= m_stComDevParam.byStopBits;				// ֹͣλ, 1λ
	
	bSuccess = SetCommState(m_hCom, &m_dcbCom);						// ���ô���

	// �������������
	PurgeComm(m_hCom, PURGE_TXCLEAR);

	return l_dwErrorCode;
}
// �رմ���
int CComDevBaseSync::iClosePort()
{
	if (m_hCom)
	{
		CloseHandle(m_hCom);
		m_hCom = NULL;
		OutputDebugString("�رվ���ɹ�");
	}
	else
	{
		OutputDebugString(("���Ϊ�ղ���Ҫ�ر�"));
	}

	return SUCCESS;
}

// ��������
int CComDevBaseSync::iSendCmd(void *p_chCutPaperCode, DWORD p_dwBytes)
{
	int l_iRet=0;

	if (!m_hCom)
	{
		OutputDebugString("����δ��");
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

// ������������Ϣ
int CComDevBaseSync::iRecvResult(char *p_chCutPaperCode, int p_iLen, DWORD& p_dwBytes)
{
	int l_iRet=0;

	if (!m_hCom)
	{
		OutputDebugString("����δ��");
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
// ���Ͳ�����������Ϣ
int CComDevBaseSync::iSendAndRecvCmd(char *p_chCutPaperCode, DWORD p_dwBytes)
{

	return SUCCESS;
}
// ������ܻ�����
int CComDevBaseSync::iClearSendBuff()
{
	if (!m_hCom)
	{
		OutputDebugString("����δ��");
		return COM_NOT_INIT;
	}

	// �������������
	PurgeComm(m_hCom, PURGE_TXCLEAR);
	return SUCCESS;
}
// �����ͻ�����
int CComDevBaseSync::iClearRecvBuff()
{
	if (!m_hCom)
	{
		OutputDebugString("����δ��");
		return COM_NOT_INIT;
	}

	// �������������
	PurgeComm(m_hCom, PURGE_RXCLEAR);
	return SUCCESS;

}


////////////////////////////////////////////////////////�첽�߳�/////////////////////////////////////////////////////////
// ���캯��
CComDevBaseAsynTrd::CComDevBaseAsynTrd()
{
	// ���ó�ʱ����
	m_iTimeOuts.ReadIntervalTimeout			= 10;
	m_iTimeOuts.ReadTotalTimeoutMultiplier	= 0;
	m_iTimeOuts.ReadTotalTimeoutConstant	= 0;
	m_iTimeOuts.WriteTotalTimeoutMultiplier = 20;
	m_iTimeOuts.WriteTotalTimeoutConstant	= 100;

	memset(&m_stRead,  0, sizeof(m_stRead));
	memset(&m_stWrite, 0, sizeof(m_stWrite));
	
	m_stRead.hEvent  = CreateEvent(NULL, true, false, NULL);
	m_stWrite.hEvent = CreateEvent(NULL, true, false, NULL);

	m_hCom = 0;			// �˿ھ��
	m_hWnd = NULL;
	m_hTrd = NULL;
	
	memset(&m_stWait, 0, sizeof(m_stWait));
	m_stWait.hEvent = CreateEvent(NULL, true, false, NULL);

}
// ��������
CComDevBaseAsynTrd::~CComDevBaseAsynTrd()
{
	iClosePort();
}

// ���ô���ͨ�Ų���
int CComDevBaseAsynTrd::iSetComParam(stComDevParam p_stComDevParam)
{
	memcpy(&m_stComDevParam, &p_stComDevParam, sizeof(stComDevParam));

	return SUCCESS;
}
// ��������
int CComDevBaseAsynTrd::iOpenPort()
{
	BOOL bSuccess;
	char l_acPort[20]={0x00};	// �˿�����
	char l_acShow[50]={0x00};	// ��������
	
	DWORD iBytesLength=0;
	DWORD l_dwErrorCode=0;
	
	// Ϊ�����Ӷ�COM10�����ϴ��ж˿ڵ�֧�֣�΢��涨�����Ҫ�����������豸��Ӧʹ���������ļ�������COM10Ϊ������\\.\COM10
	if (m_stComDevParam.iPort > 9 )
	{
		sprintf( l_acPort, "\\\\.\\COM%d", m_stComDevParam.iPort);
	}
	else
	{
		sprintf( l_acPort, "COM%d", m_stComDevParam.iPort);
	}

	// ��ֹ�ظ����õ�����
	if (m_hCom)
	{
		sprintf(l_acShow, "%s�����Ѿ��� �ظ�����!",l_acPort);
		OutputDebugString(l_acShow);
		return SUCCESS;
	}
	
	// �򿪶˿�
	// �����첽��ʽ�Ĵ���ͨ�ű���ʹ�� �ڶ�������ΪGENERIC_READ | GENERIC_WRITE
	// OPEN_EXISTING��ʽ FILE_ATTRIBUTE_NORMAL->���FILE_FLAG_OVERLAPPED ���һ��Ϊ�첽�¼�(��䵽�ṹ LPOVERLAPPED�е�) 
	// ��������첽����ʹ�õȴ��¼��ķ�ʽʵ��ͬ��,һ���ļ������ɹ������¼�Ϊ���ź�״̬
	m_hCom = CreateFile(l_acPort, GENERIC_READ | GENERIC_WRITE,
		0, NULL, 
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL );
	
	if (m_hCom == INVALID_HANDLE_VALUE)
	{
		l_dwErrorCode = GetLastError();
		if (ERROR_FILE_NOT_FOUND == l_dwErrorCode)
		{
			sprintf(l_acShow, "%s�˿ڴ򿪴���[δ�ҵ�����]! ������:%d",l_acPort, l_dwErrorCode);
			OutputDebugString(l_acShow);
		}
		else if (ERROR_ACCESS_DENIED == l_dwErrorCode)
		{
			sprintf(l_acShow, "%s�˿ڴ򿪴���[���ڱ�ռ��]! ������:%d",l_acPort, l_dwErrorCode);
			OutputDebugString(l_acShow);
		}
		else
		{
			sprintf(l_acShow, "%s�˿ڴ򿪴���[�����쳣]! ������:%d",l_acPort, l_dwErrorCode);
			OutputDebugString(l_acShow);
		}
		
		CloseHandle(m_hCom);
		m_hCom = NULL;
		return FAIL;
	}
	
	SetupComm(m_hCom, 1024, 1024);									// ���ö˿ڻ���
	
	SetCommTimeouts(m_hCom, &m_iTimeOuts);							// ���ó�ʱ����		
	
	bSuccess = GetCommState(m_hCom, &m_dcbCom);						// ��õ�ǰ��������
	
	// ����������Ϣ
	m_dcbCom.BaudRate	= m_stComDevParam.dwBoud;					// ���ò����� 
	m_dcbCom.ByteSize	= m_stComDevParam.byByteSize;				// ����λ, 8bit
	m_dcbCom.Parity		= m_stComDevParam.byParity;					// У��, ��
	m_dcbCom.StopBits	= m_stComDevParam.byStopBits;				// ֹͣλ, 1λ
	
	bSuccess = SetCommState(m_hCom, &m_dcbCom);						// ���ô���

	// �������������
	PurgeComm(m_hCom, PURGE_TXCLEAR);

	// �����߳�
	m_bTrdFlag = true; 
	DWORD id;
	m_hTrd = CreateThread(NULL, 0, GetComMessageTrd, this, 0, &id); //�����߳�
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
// �رմ���
int CComDevBaseAsynTrd::iClosePort()
{
	if (m_hCom)
	{
		CloseHandle(m_hCom);
		OutputDebugString("�رվ���ɹ�");

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
		OutputDebugString(("���Ϊ�ղ���Ҫ�ر�"));
	}

	return SUCCESS;
}

// ��������
int CComDevBaseAsynTrd::iSendCmd(char *p_chCutPaperCode, DWORD p_dwBytes)
{
	if (!m_hCom)
	{
		OutputDebugString("����δ��");
		return COM_NOT_INIT;
	}
	
	DWORD  error;
	if(ClearCommError(m_hCom, &error, NULL) && error > 0)	// �������
		PurgeComm(m_hCom, PURGE_TXABORT | PURGE_TXCLEAR);	
	
	DWORD p_dwBytesWritten = 0;

	if(!WriteFile(m_hCom, p_chCutPaperCode, p_dwBytes, &p_dwBytesWritten, &m_stWrite))
		if(GetLastError() != ERROR_IO_PENDING)
			p_dwBytes = 0;
		
	OutputDebugString(p_chCutPaperCode);
		
//	return SUCCESS;

	return p_dwBytesWritten;
}

// ������������Ϣ
int CComDevBaseAsynTrd::iRecvResult(char *p_chCutPaperCode, DWORD& p_dwBytes)
{
	if (!m_hCom)
	{
		OutputDebugString("����δ��");
		return COM_NOT_INIT;
	}

	p_chCutPaperCode[0] = '\0';
	
	COMSTAT  stat;
	DWORD error=0;
	
	if(ClearCommError(m_hCom, &error, &stat) && error > 0)	// �������
	{
		PurgeComm(m_hCom, PURGE_RXABORT | PURGE_RXCLEAR);	// ������뻺����
		return 0;
	}
	
	if(!stat.cbInQue)// ������������
		return 0;
	
	p_dwBytes = min((int)(p_dwBytes - 1), (int)stat.cbInQue);
	
	if(!ReadFile(m_hCom, p_chCutPaperCode, 256, &p_dwBytes, &m_stRead)) // 2000 �� ReadFile ʼ�շ��� True
	{
		if(GetLastError() == ERROR_IO_PENDING) // �����첽I/O
		{
			if(!GetOverlappedResult(m_hCom, &m_stRead, &p_dwBytes, false))
			{
				if(GetLastError() != ERROR_IO_INCOMPLETE)// ��������
					p_dwBytes = 0;
			}
		}
		else
			p_dwBytes = 0;
	}
	
	p_chCutPaperCode[p_dwBytes] = '\0';

	return SUCCESS;
}
// ���Ͳ�����������Ϣ
int CComDevBaseAsynTrd::iSendAndRecvCmd(char *p_chCutPaperCode, DWORD p_dwBytes)
{

	return SUCCESS;
}
// ������ܻ�����
int CComDevBaseAsynTrd::iClearSendBuff()
{
	if (!m_hCom)
	{
		OutputDebugString("����δ��");
		return COM_NOT_INIT;
	}

	// �������������
	PurgeComm(m_hCom, PURGE_TXCLEAR);
	return SUCCESS;
}
// �����ͻ�����
int CComDevBaseAsynTrd::iClearRecvBuff()
{
	if (!m_hCom)
	{
		OutputDebugString("����δ��");
		return COM_NOT_INIT;
	}

	// �������������
	PurgeComm(m_hCom, PURGE_RXCLEAR);
	return SUCCESS;

}

// �߳̿��ƺ���
// ����
bool CComDevBaseAsynTrd::bSuspend()
{
	return m_hTrd != NULL ? SuspendThread(m_hTrd) != 0xFFFFFFFF : false;
}
// �ָ�
bool CComDevBaseAsynTrd::bResume()
{
	return m_hTrd != NULL ? ResumeThread(m_hTrd) != 0xFFFFFFFF : false;
}
// ��ȡ�߳̾��
HANDLE CComDevBaseAsynTrd::hGetTrdHandle()
{
	return m_hTrd;
}
// ���ô�����Ϣ���ھ��
void CComDevBaseAsynTrd::vSetMessageHwnd(HWND p_hWnd)
{
	m_hWnd = p_hWnd;
}
// ��Ϣ����
void CComDevBaseAsynTrd::OnComRecv()
{
	// ����ǻ�����Ϣ��Ӧ�� ��Ҫ���ھ��
	
	if(m_hWnd)
		PostMessage(m_hWnd, ON_COM_RECEIVE, WPARAM(m_stComDevParam.iPort), LPARAM(0));
		
	// ��ʵ��ʹ������Ϊ����ģ���ϲ����ʹ����Ϣ������� ���ǲ�����ѯ�ķ�ʽ����
	/*char p_chCutPaperCode[256]={0x00};
	DWORD p_dwBytes;
	iRecvResult(p_chCutPaperCode, p_dwBytes);*/
	
}
// �����߳�
DWORD WINAPI CComDevBaseAsynTrd::GetComMessageTrd(LPVOID p_para)
{
	CComDevBaseAsynTrd *l_pcom = (CComDevBaseAsynTrd *)p_para;	
	
	// ���ù��ĵ��¼���Ϣ
	if(!SetCommMask(l_pcom->m_hCom, EV_RXCHAR | EV_ERR))
		return 0;
	
	COMSTAT		l_stat;
	DWORD		l_dwerror;
	
	for(DWORD l_dwlength, l_dwmask = 0; l_pcom->m_bTrdFlag && l_pcom->m_hCom!=INVALID_HANDLE_VALUE; l_dwmask = 0)
	{
		// �ȴ������¼�
		if(!WaitCommEvent(l_pcom->m_hCom, &l_dwmask, &l_pcom->m_stWait))
		{
			if(GetLastError() == ERROR_IO_PENDING) // ����Ϊ�������ڷ��� ����������
			{
				GetOverlappedResult(l_pcom->m_hCom, &l_pcom->m_stWait, &l_dwlength, true); // ��ȡ���һ�β����Ľ����Ϣ
			}
		}
		
		if(l_dwmask & EV_ERR) // == EV_ERR
			ClearCommError(l_pcom->m_hCom, &l_dwerror, &l_stat); // ������ڴ�����Ϣ
		
		if(l_dwmask & EV_RXCHAR) // == EV_RXCHAR
		{
			ClearCommError(l_pcom->m_hCom, &l_dwerror, &l_stat); // ������ڴ�����Ϣ
			l_pcom->OnComRecv();
		}
	}
	
	return SUCCESS;
}

#endif
