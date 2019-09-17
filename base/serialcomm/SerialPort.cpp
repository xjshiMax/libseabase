// SerialPort.cpp : Defines the entry point for the DLL application.
//

#include "SerialPort.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>

#endif

// #include "WriteLog.h"
// #pragma comment(lib, "WriteLog.lib") 

// #else
// 
// #include "Log.h"
// 
// #endif
// 
// 


const char * ThisFile = "Serialport.cpp";


#ifdef WIN32

#else

int speed_arr[] = 	   {B115200,B57600, B38400, B19200, B9600, B4800, B2400, B1200, B300, };
unsigned int name_arr[] =  {115200,  57600,  38400,  19200,  9600,  4800,  2400,  1200,  300, };
#endif

#ifdef WIN32

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}


class CFileEvent
{
public:
	CFileEvent()
	{
		m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}

	~CFileEvent()
	{
		CloseHandle(m_hEvent);
		m_hEvent = NULL;
	}

	HANDLE GetHandle() const { return m_hEvent; } 

private:
	HANDLE m_hEvent;
};
#else
#endif

/**************************************************************************
*                                                                         *
*                                                                         *
**************************************************************************/
CSerialPort::CSerialPort(const char * pDataLogFile)
 /*m_Log(pDataLogFile)*/
{
    m_hComm = INVALID_HANDLE_VALUE;
}

CSerialPort::CSerialPort()
{
	m_hComm = INVALID_HANDLE_VALUE;
}

CSerialPort::~CSerialPort()
{

}

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
int CSerialPort::OpenPort(const char* pComName,unsigned int uBaudRate, unsigned int uParity, unsigned int uByteSize, unsigned int uStopBits)
{
	
	const char *ThisFunc = "OpenPort";

#ifdef WIN32
	

	DWORD dwErr;
	char szComName[200] = {0};
	if (pComName[0] >='1' && pComName[0] <= '9')
	{
		int nComPort = atoi(pComName);
	}
	if (strnicmp(pComName,"COM",3)!=0)
	{
// 		WriteLog(__FILE__,ThisFunc,-1, 
// 			"ConName�ִ�������COM��ͷ:%s",
// 			pComName);
		return ERROR_COM_PARAMETER_ERR;
	}
	
	int nComPort = atoi(pComName + 3);
	if (nComPort <= 0 || nComPort >255)
	{
// 		WriteLog(__FILE__,ThisFunc,-1,
// 			"���ں�[%d]���Ϸ�",
// 			nComPort);
		return ERROR_COM_PARAMETER_ERR;
	}
	ClosePort();
	
	char szPath[MAX_PATH + 1];
	sprintf(szPath, "\\\\.\\COM%d", nComPort);
	m_hComm = CreateFile(szPath,						
		GENERIC_READ | GENERIC_WRITE,	
		0,								
		NULL,							
		OPEN_EXISTING,					
		FILE_FLAG_OVERLAPPED,   		
		NULL);							
	
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
// 		WriteLog(__FILE__,ThisFunc,-2,
// 			"CreateFile(%s)ʧ��: GetLastError() = %d",
// 			szPath,dwErr);
		return ERROR_COM_COMM_ERR;
	}
	
	DCB dcb;
	ZeroMemory(&dcb, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb);
	BOOL bRet = GetCommState(m_hComm, &dcb);
	if (!bRet)
	{
		dwErr = GetLastError();
		ClosePort(); 
// 		WriteLog(__FILE__,ThisFunc, -2,
// 			"GetCommState(%s)ʧ��: GetLastError() = %d",
// 			szPath,dwErr);
		return ERROR_COM_COMM_ERR;
	}
	if (uParity == 'N')
	{
		dcb.Parity = NOPARITY;				// У��ģʽ
	}
	if (uParity == 'O')
	{
		dcb.Parity = ODDPARITY;				// У��ģʽ
	}
	if (uParity == 'E')
	{
		dcb.Parity = EVENPARITY;				// У��ģʽ
	}	
	
	//"baud=9600 parity=E data=7 stop=2  dtr=on rts=on");
	dcb.BaudRate = uBaudRate;
	dcb.ByteSize = uByteSize;
	dcb.StopBits =uStopBits;
	
	BuildMode(&pComName);
	
	bRet = BuildCommDCB(pComName,&dcb);
	if (!bRet)
	{
		dwErr = GetLastError();
		ClosePort();
// 		WriteLog(__FILE__,ThisFunc,-1,
// 			"BuildCommDCB(%s)ʧ��: GetLastError() = %d",
// 			pComName,dwErr);
		return ERROR_COM_PARAMETER_ERR;
	}
	
	bRet = SetCommState(m_hComm, &dcb);
	if (!bRet)
	{
		dwErr = GetLastError();
		ClosePort();
// 		WriteLog(__FILE__,ThisFunc,-1,
// 			"SetCommState(%s)ʧ�ܣ� GetLastError() = %d",
// 			szPath, dwErr);
	}
#else
	 //WriteInfo(ThisFile,__LINE__, ThisFunc, 0, "OpenPort begin pComName = [%s] uBaudRate = [%d] uParity = [%d] uByteSize = [%d] uStopBits = [%d]",pComName,uBaudRate,uParity,uByteSize,uStopBits);
	
        char szPort[200] = {0};
        if (pComName[0] >= '1' && pComName[0] <= '9' )
        {
                int nPort = atoi(pComName);
                sprintf(szPort, "ttyS%d", nPort-1);
                pComName = szPort;
        }

        if(strncasecmp(pComName, "tty", 3) != 0)
        {
	  	  
	  	//WriteError(ThisFile,__LINE__, ThisFunc, -1, "ConName�ִ�������tty��ͷ:%s",pComName);
		return ERROR_COM_PARAMETER_ERR;
        }


        ClosePort();

        char szPath[260];
        sprintf(szPath, "/dev/%s", pComName);

        m_hComm = open(szPath, O_RDWR|O_NOCTTY|O_NDELAY);
        if (m_hComm == -1)
        {
	  
	  	//WriteError(ThisFile,__LINE__, ThisFunc, -2, "open(%s)ʧ��: m_hComm = %d",szPath,m_hComm);
                //return ERROR_COM_COMM_ERR;
				return errno;
        }
        unsigned char ctrlbits;
	ioctl(m_hComm,TIOCMGET,&ctrlbits);
	ctrlbits &=~TIOCM_CTS;
	ioctl(m_hComm,TIOCMSET,&ctrlbits);
		
        struct termios   Opt;
        int nRet = tcgetattr(m_hComm, &Opt);
        if(nRet != 0)
        {
	  
	  	//WriteError(ThisFile,__LINE__, ThisFunc, nRet,"tcgetattr(%s)ʧ��: Error() = %d",szPath,nRet);
 	  	ClosePort();
                return ERROR_COM_PARAMETER_ERR;
        }

        int i;
        for (i= 0;  i < 9;  i++)
        {
                if(uBaudRate == name_arr[i])
                {
                        tcflush(m_hComm, TCIOFLUSH);
                        cfsetispeed(&Opt, speed_arr[i]);
                        cfsetospeed(&Opt, speed_arr[i]);

                }
        }
	printf("%s \t\n",szPath);
	
	
	 //WriteInfo(ThisFile,__LINE__, ThisFunc, 0, "���ںţ�%s�� ������ [%d] ��żЧ�� = [%d] ����λ�� = [%d] ֹͣλ = [%d] m_hComm = [%d] ",pComName,uBaudRate,uParity,uByteSize,uStopBits,m_hComm);
 
	 
	 Opt.c_cflag &= ~CSIZE;
        switch (uByteSize) /*��������λ��*/
        {
        case 7:
                Opt.c_cflag |= CS7;
                break;
        case 8:
                Opt.c_cflag |= CS8;
                break;
        default:
	  	//WriteError(ThisFile,__LINE__, ThisFunc, -1,"��������λ��ʧ��(%s): uByteSize() = %d",szPath,uByteSize);
		ClosePort();
                return ERROR_COM_PARAMETER_ERR;
        }

        switch (uParity)
        {
                case 'n':
                case 'N':
                        Opt.c_cflag &= ~PARENB;   /* Clear parity enable */
                        Opt.c_iflag &= ~INPCK;     /* Enable parity checking */
                        break;
                case 'o':
                case 'O':
                        Opt.c_cflag |= (PARODD | PARENB); /* ����Ϊ��Ч��*/
                        Opt.c_iflag |= INPCK;             /* Disnable parity checking */
                        break;
                case 'e':
                case 'E':
                        Opt.c_cflag |= PARENB;     /* Enable parity */
                        Opt.c_cflag &= ~PARODD;   /* ת��ΪżЧ��*/
                        Opt.c_iflag |= INPCK;       /* Disnable parity checking */
                        break;
                case 'S':
                case 's':  /*as no parity*/
                        Opt.c_cflag &= ~PARENB;
                        Opt.c_cflag &= ~CSTOPB;
			break;
                default:
	  	//WriteError(ThisFile,__LINE__, ThisFunc, -1,"������żλ��ʧ��(%s): uParity() = %c",szPath,uParity);
		ClosePort();
                return ERROR_COM_PARAMETER_ERR;
        }
        /* ����ֹͣλ*/
        switch (uStopBits)
        {
                case 1:
                        Opt.c_cflag &= ~CSTOPB;
                        break;
                case 2:
                        Opt.c_cflag |= CSTOPB;
                        break;
                default:
	  	//WriteError(ThisFile,__LINE__, ThisFunc, -1,"����ֹͣλʧ��(%s): uStopBits() = %c",szPath,uStopBits);		  
                 return ERROR_COM_PARAMETER_ERR;
        }
        
        Opt.c_iflag &= ~(INLCR|ICRNL|BRKINT|IXON|IXOFF|IXANY);
        Opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
//        Opt.c_oflag &= ~OPOST;
//	Opt.c_oflag |= (OPOST|ONLCR);
        Opt.c_cflag |= (CLOCAL|CREAD);

//        tcflush(m_hComm,TCIFLUSH);

        Opt.c_oflag=0;
        Opt.c_lflag=0;
        Opt.c_cc[VMIN] = 0;
        Opt.c_cc[VTIME] = 30;//3??
        

        nRet = tcsetattr(m_hComm,TCSANOW,&Opt);
        if(nRet != 0)
        {
	  	//WriteError(ThisFile,__LINE__, ThisFunc, nRet,"tcsetattr(%s)ʧ��: Error() = %d",szPath,nRet);	   	  
		ClosePort();
                return ERROR_COM_PARAMETER_ERR;
        }
        tcflush(m_hComm,TCIOFLUSH);
#endif
		
	return ERROR_COM_SUCC;
}


void CSerialPort::BuildMode(const char **pComName)
{
	BOOL bFind = FALSE; // �Ƿ��ҵ���ð�š�:��
	while ('\0' != **pComName)
	{
		if (!bFind)
		{
			if (':' == **pComName)
			{
				(*pComName)++;
				bFind = TRUE;
			}
			else
			{
				(*pComName)++;
			}	
		}
		else
		{
			if (' ' != **pComName)
			{
				break;
			}
			else
			{
				(*pComName)++;
			}
		}
	}
	return;
}


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
* 2012/03/08  V1.0	     regbin	     �����ļ�
**************************************************************************/
void CSerialPort::ClosePort()
{
#ifdef WIN32	
	if (m_hComm != INVALID_HANDLE_VALUE)
		CloseHandle(m_hComm);
	m_hComm = INVALID_HANDLE_VALUE;
#else
	if (m_hComm != INVALID_HANDLE_VALUE)
    {
        close(m_hComm);	
	//WriteError(ThisFile,__LINE__, "ClosePort",1,"�رմ���m_hComm = [%d]",m_hComm); 
	
    }
     m_hComm = INVALID_HANDLE_VALUE;
#endif
}



/**************************************************************************
* �������ƣ� WriteComm(const char * pBuf, DWORD dwLength,DWORD dwTimeout)
* ���������� //д����
* ���ʵı� 
* �޸ĵı� 
* ��������� const char *pBuf, DWORD dwLength,DWORD dwTimeout
* ��������� 
* �� �� ֵ�� 0 �ɹ�     <0 ʧ��
* ����˵���� 
* �޸�����    �汾��     �޸���	     �޸�����
* -----------------------------------------------
* 2012/03/08  V1.0	     regbin	     �����ļ�
**************************************************************************/
int CSerialPort::WriteComm(const char *pBuf, DWORD dwLength,DWORD dwTimeout)
{
	const char *ThisFunc = "WriteComm";
#ifdef WIN32

	DWORD dwRet = 0;

	int nRet = SetWriteTimeOut(dwTimeout);
	if (nRet != 0)
	{
// 		WriteLog(__FILE__, ThisFunc, nRet,
// 			"SetWriteTimeOutʧ��:%d",
// 			nRet);
		return nRet;
	}
	
	if (dwLength == 0)
		return ERROR_COM_SUCC;
	if (dwLength == -1)
		dwLength = strlen(pBuf);

	//m_Log.WriteSendDataHex(pBuf,dwLength);

	
	CFileEvent FileEvent;
	OVERLAPPED Overlap;
	ZeroMemory(&Overlap, sizeof(Overlap));
	
	Overlap.hEvent = FileEvent.GetHandle();

	BOOL bRet = WriteFile(m_hComm, pBuf, dwLength, &dwRet, &Overlap);
	if (!bRet)
	{
		dwRet = GetLastError();
		if (dwRet != ERROR_IO_PENDING)
		{
// 			WriteLog(__FILE__,ThisFunc, -1,
// 				"WriteFileʧ��: GetLastError() = %d",
// 				GetLastError());
// 			m_Log.WriteErrorLog("ERROR");
			return ERROR_COM_PARAMETER_ERR;
		}

		dwRet = 0;
		bRet = GetOverlappedResult(m_hComm, &Overlap, &dwRet, TRUE);
		if (!bRet)
		{
// 			WriteLog(__FILE__,ThisFunc, -1,
// 				"GetOverlappedResultʧ�ܷ�����:%d",GetLastError());
			return ERROR_COM_COMM_ERR;
		}
		if (dwRet < dwLength)
		{
// 			WriteLog(__FILE__,ThisFunc, -1,
// 				"WriteFileʧ��:д����Ϊ%d,(ʵ�ʳ���=%d)",dwRet,dwLength);
// 			char temp[30];
// 			sprintf(temp,"%d",dwRet);
// 			m_Log.WriteErrorLog(temp);
			return ERROR_COM_COMM_ERR;
		}
	}

#else
	        if (dwLength == 0)
                return ERROR_COM_SUCC;
        if (dwLength == -1)
                dwLength = strlen(pBuf);
	
	char szbuf[120688]  = {0};
	memset(szbuf,0x00,sizeof(szbuf));
	for (int i = 0; i < dwLength; i++)
	{
		sprintf(szbuf+2*i, "%2.2X ", (unsigned char )(pBuf[i]));
	}
	
//	WriteInfo(ThisFile,__LINE__, ThisFunc, 0, "WRIT[ %d]: %s",dwLength,szbuf);
	//m_Log.WriteSendDataHex(pBuf,dwLength);

	struct timeval sendtime;
	struct timeval nowtime;
	gettimeofday(&sendtime, NULL);
	gettimeofday(&nowtime, NULL);
	
	int nRet = 0;
	int WriteLen = 0;
	while (1)
	{     
	  	
		gettimeofday(&nowtime, NULL);
		if(!(GETTIMEUSED(nowtime,sendtime) < dwTimeout))
		{
			//WriteError(ThisFile,__LINE__, ThisFunc, -2,
			 // "WriteFileʧ��:д���ݳ�ʱ ����Ϊ%d,(ʵ�ʳ���=%d)",nRet,dwLength);
			//m_Log.WriteErrorLog("ERROR");
			return ERROR_COM_TIMEOUT;		  		  
		}
	  	 	  
	  
                nRet = write(m_hComm, pBuf + WriteLen, dwLength);
                if(nRet == -1)
                {
/*		  
			//WriteError(ThisFile,__LINE__, ThisFunc,-1,
			"WriteFileʧ��: GetLastError() = %d",
			 nRet);
*/			 
			continue;
	      }

	      if (nRet < dwLength)
	      {
			//WriteError(ThisFile,__LINE__, ThisFunc,-1,
			//"WriteFileʧ��:д����Ϊ%d,(ʵ�ʳ���=%d)",nRet,dwLength);		
			WriteLen += nRet;
			dwLength = dwLength - nRet;
			 continue;
	      }
	      else
	      {
//			WriteError(ThisFile,__LINE__, ThisFunc,-1,
//			"WriteFile�ɹ�:д����Ϊ%d,(ʵ�ʳ���=%d)",nRet,dwLength);		
			return nRet;
	      }
	}
        
        return nRet;
#endif



	return ERROR_COM_SUCC;	
}
#ifdef WIN32

#else
ssize_t tread(int fd, void *buf, size_t nbytes, unsigned int timout)
{
	
	int nfds;
	
	fd_set  readfds;
	
	struct timeval  tv;
	
	tv.tv_sec = timout / 1000;
	
	tv.tv_usec = (timout % 1000) * 1000;
	
	
	FD_ZERO(&readfds);
	
	FD_SET(fd, &readfds);
	
	nfds = select(fd+1, &readfds, NULL, NULL, &tv);
	
	if (nfds <= 0)
	{
		if (nfds == 0)
			
			errno = ETIME;
		
		return(-1);
		
	}
	
	return(read(fd, buf, nbytes));
	
}

ssize_t treadn(int fd, void *buf, size_t nbytes, unsigned int timout)
{
	
	size_t      nleft;
	ssize_t     nread = 0;
	
	nleft = nbytes;
	while (nleft > 0)
	{
		if ((nread = tread(fd, buf, nleft, timout)) < 0)
		{
			if (nleft == nbytes)
				return(-1); /* error, return -1 */
			else
				break;      /* error, return amount read so far */
			
		}
		else if (nread == 0)
		{
			break;          /* EOF */
			
		}
		
		nleft -= nread;
		buf += nread;
		
	}
	
	return(nbytes - nleft);      /* return >= 0 */
	
}
#endif
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
int CSerialPort::SetWriteTimeOut(DWORD dwTimeOut)
{
	const char *ThisFunc = "SetWriteTimeOut";
#ifdef WIN32	
	COMMTIMEOUTS CommTimeOuts;

	if (!GetCommTimeouts(m_hComm,&CommTimeOuts))
	{
// 		WriteLog(__FILE__,ThisFunc, -2,
// 			"GetCommTimeoutsʧ��: GetLashError()= %d",
// 			GetLastError());
		return ERROR_COM_COMM_ERR;
	}

	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = dwTimeOut;

	if (!SetCommTimeouts(m_hComm, &CommTimeOuts))
	{
// 		WriteLog(__FILE__,ThisFunc, -2,
// 			"SetCommTimeoutsʧ��: GetLastError() = %d",
// 			GetLastError());
		return ERROR_COM_COMM_ERR;
	}
#else
#endif
	return ERROR_COM_SUCC;
}


/**************************************************************************
* �������ƣ� WriteComm(const char * pBuf, DWORD dwLength,DWORD dwTimeout)
* ���������� //������
* ���ʵı� 
* �޸ĵı� 
* ��������� DWORD dwTimeout,DWORD dwIntervalTimeout = 250
* ��������� char *pBuf, DWORD dwLength
* �� �� ֵ�� 0 �ɹ�     <0 ʧ��
* ����˵���� 
* �޸�����    �汾��     �޸���	     �޸�����
* -----------------------------------------------
* 2012/03/08  V1.0	     regbin	     �����ļ�
**************************************************************************/	
int CSerialPort::ReadComm(char *pBuf, DWORD dwLength,DWORD dwTimeout,DWORD dwIntervalTimeout)
{
	const char *ThisFunc = "ReadComm";
#ifdef WIN32

	if (dwLength == 0)
		return ERROR_COM_SUCC;

	int nRet = 0;

	nRet = SetReadTimeOut(dwTimeout, dwIntervalTimeout);
	if (nRet != 0)
	{
// 		WriteLog(__FILE__, ThisFunc,  nRet,
// 			"SetReadTimeOutʧ��: %d", nRet);
		return nRet;
	}

	CFileEvent FileEvent;
	OVERLAPPED Overlap;
	ZeroMemory(&Overlap, sizeof(Overlap));
	Overlap.hEvent = FileEvent.GetHandle();
	DWORD dwRet = 0;
	BOOL bRet = ReadFile(m_hComm, pBuf, dwLength, &dwRet, &Overlap);
	if (!bRet)
	{
		dwRet = GetLastError();
		if (dwRet != ERROR_IO_PENDING)
		{
// 			WriteLog(__FILE__,ThisFunc, -1,
// 				"ReadFileʧ��,ͨ�Ŵ��ھ��0x:%x, pBuf=%s,����������:%d,���ش�����:%d",
// 				m_hComm,pBuf,dwLength,dwRet);
			return ERROR_COM_PARAMETER_ERR;
		}

		dwRet = 0;

		bRet = GetOverlappedResult(m_hComm, &Overlap, &dwRet, TRUE);
		if (!bRet && GetLastError() != ERROR_OPERATION_ABORTED)
		{
// 			WriteLog(__FILE__,ThisFunc, -1,
// 				"GetOverlappedResultʧ��,ͨѶ���ھ��0x:%x, pbuf=%s,����������:%d,�Ѷ����ݳ���dwRet:%d,���ش�����:%d",
// 				m_hComm, pBuf, dwLength, dwRet, GetLastError());
			return ERROR_COM_COMM_ERR;
		}
		if (nRet == 1 && dwRet == 0)
		{
			//m_Log.WriteErrorLog("(CANCELLED)");
			return ERROR_COM_CANCELLED;
		}

		if (nRet < 0)
		{
			//m_Log.WriteErrorLog("(ERROR)");
			return ERROR_COM_COMM_ERR;
		}
	}

	//m_Log.WriteReadDataHex(pBuf,dwLength);
	return dwRet;
#else
       if (dwLength == 0)
                return ERROR_COM_SUCC;

	//   printf("ReadComm:m_hComm = %d.\r\n", m_hComm);

	   if(m_hComm == INVALID_HANDLE_VALUE)
	   {
		   return ERROR_COM_PARAMETER_ERR;
	   }


        int nRet = -1;

        nRet = treadn(m_hComm, pBuf, dwLength, dwTimeout);
        if(nRet < 0)
        {
/*		WriteError(ThisFile,__LINE__, ThisFunc,-1,
                "treadn,ͨ�Ŵ��ھ��0x:[%d], pBuf=%s,����������:%d,���ش�����:%d",
                m_hComm,pBuf,dwLength,nRet);*/
		//m_Log.WriteErrorLog("(ERROR)");
                return ERROR_COM_PARAMETER_ERR;
        }
        else if(nRet == 0)
	{
	  
		//m_Log.WriteErrorLog("(CANCELLED)");

	}
        else
	{
		char szbuf[4096];
		memset(szbuf,0x00,sizeof(szbuf));
		for (int i = 0; i < nRet; i++)
		{
			sprintf(szbuf+2*i, "%2.2X ", (unsigned char )(pBuf[i]));
		}
//		WriteInfo(ThisFile,__LINE__, ThisFunc, 0, "READ[ %d]: %s",dwLength,szbuf);
		//m_Log.WriteReadDataHex(pBuf,dwLength);

		return nRet;

        }
        return nRet;
#endif
	
}


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
int CSerialPort::SetReadTimeOut(DWORD dwTimeOut,DWORD dwIntervalTimeout)
{
	const char *ThisFunc = "SetReadTimeOut";
	
#ifdef WIN32	
	COMMTIMEOUTS CommTimeOuts;

	if (!GetCommTimeouts(m_hComm,&CommTimeOuts))
	{
// 		WriteLog(__FILE__,ThisFunc, -2,
// 			"GetCommTimeoutsʧ��: GetLashError()= %d",
// 			GetLastError());
		return ERROR_COM_COMM_ERR;
	}

	CommTimeOuts.ReadIntervalTimeout = dwIntervalTimeout;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = dwTimeOut;

	if (!SetCommTimeouts(m_hComm, &CommTimeOuts))
	{
// 		WriteLog(__FILE__,ThisFunc, -2,
// 			"SetCommTimeoutsʧ��: GetLastError() = %d",
// 			GetLastError());
		return ERROR_COM_COMM_ERR;
	}
#else
#endif
	return ERROR_COM_SUCC;
}

/**************************************************************************
* �������ƣ� WriteAndReadComm(const char *pWriteBuf, DWORD dwLen, char *pReadBuf, DWORD dwReadLen,DWORD dwReadTimeout,DWORD dwReadInterval = 250, DWORD dwWriteTimeout = 1000)
* ���������� //д������
* ���ʵı� 
* �޸ĵı� 
* ��������� const char *pWriteBuf, DWORD dwLen,DWORD dwReadInterval = 250,DWORD dwWriteTimeout = 1000
* ��������� char *pReadBuf, DWORD dwReadLen
* �� �� ֵ�� 0 �ɹ�     <0 ʧ��
* ����˵���� 
* �޸�����    �汾��     �޸���	     �޸�����
* -----------------------------------------------
* 2012/03/08  V1.0	     regbin	     �����ļ�
**************************************************************************/	
int CSerialPort::WriteAndReadComm(const char *pWriteBuf, DWORD dwWriteLen, char *pReadBuf, DWORD dwReadLen, 
					 DWORD dwReadTimeout, 
					 DWORD dwReadInterval, 
					 DWORD dwWriteTimeout)
{
	const char *ThisFunc = "WriteAndReadComm";

#ifdef WIN32

	int nRet = WriteComm(pWriteBuf, dwWriteLen, dwWriteTimeout);
	if (nRet < 0)
	{
// 		WriteLog(__FILE__,ThisFunc,nRet,
// 			"WriteCommʧ��:%d", nRet);
		return nRet;
	}

	nRet = ReadComm(pReadBuf, dwReadLen, dwReadTimeout, dwReadInterval);
	if (nRet < 0)
 	{
// 		WriteLog(__FILE__,ThisFunc, nRet == ERROR_COM_CANCELLED ? 0 : -1,
// 			"ReadCommʧ��:%d", nRet);
		return nRet;		
	}
		return nRet;
#else

	int nRet = WriteComm(pWriteBuf, dwWriteLen, dwWriteTimeout);
	if (nRet < 0)
	{
		//WriteError(ThisFile,__LINE__, ThisFunc,nRet,"WriteCommʧ��:%d", nRet);
		return nRet;
	}
	
	nRet = ReadComm(pReadBuf, dwReadLen, dwReadTimeout);
	if (nRet < 0)
	{
		//WriteError(ThisFile,__LINE__, ThisFunc,nRet == ERROR_COM_CANCELLED ? 0 : -1,"ReadCommʧ��:%d", nRet);
		return nRet;
	}
        return nRet;
#endif


}

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
* 2012/03/08  V1.0	     regbin	     �����ļ�
**************************************************************************/	
void CSerialPort::PurgeCommFlag(PURGE_FLAG Flag)
{

#ifdef WIN32

	char buf[100];
	DWORD dwErr;
    COMSTAT stComStat;

	DWORD dwFlags = PURGE_TXABORT | PURGE_RXABORT;

	switch(Flag) 
	{
	case PURGE_IN:
		dwFlags |= PURGE_RXCLEAR;
		strcpy(buf, " IN");
		break;
	case PURGE_OUT:
		dwFlags |= PURGE_TXCLEAR;
		strcpy(buf, " OUT");
		break;
	case PURGE_IO:
		dwFlags |= PURGE_RXCLEAR | PURGE_TXCLEAR;
		strcpy(buf, " IO");
		break;
	}

	PurgeComm(m_hComm, dwFlags);
	ClearCommError(m_hComm, &dwErr, &stComStat);

	//m_Log.WriteFLSHLog(buf);
	return;
#else

	char buf[100];
	switch(Flag)
	{
	case PURGE_IN:
		tcflush(m_hComm,TCIFLUSH);
		strcpy(buf, " IN");
		break;
	case PURGE_OUT:
		tcflush(m_hComm,TCOFLUSH);
		strcpy(buf, " OUT");		
		break;
	case PURGE_IO:
		tcflush(m_hComm,TCIOFLUSH);
		strcpy(buf, " IO");		
		break;
	}
	
	//m_Log.WriteFLSHLog(buf);
    return;
#endif
	
}


// CDriverLog::CDriverLog(const char *pDeviceName)
// {
// 	m_szBuf[0] = 0;
// 	m_pLogData = NULL;
// 	m_nAllLogLen = 0;
// 	
// 	if (pDeviceName != NULL)
// 		strcpy(m_szDeviceName, pDeviceName);
// 	if (pDeviceName == NULL || pDeviceName[0] == '\0')//��־�ļ���Ϊ�գ�����¼�����ļ�
// 		return;
// 	
// 	m_nAllLogLen = LOG_ALLOC_SAVE;
// 	m_pLogData = new char[m_nAllLogLen];
// 	m_nLogDataLen = 0;
// }

// CDriverLog::~CDriverLog()
// {
// 	//WriteLogFile();
// 	if (m_pLogData)
// 	{
// 		delete [] m_pLogData;
// 		m_pLogData = NULL;
// 	}
// }



// /**************************************************************************
// * �������ƣ� GetLogTimeStr(char *pBuf)
// * ���������� ��ȡϵͳʱ���ַ�
// * ���ʵı� 
// * �޸ĵı� 
// * ��������� 
// * ��������� char *pBuf
// * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// * ����˵���� 
// * �޸�����    �汾��     �޸���	     �޸�����
// * -----------------------------------------------
// * 2012/03/07  V1.0	     regbin	     �����ļ�
// **************************************************************************/
// void CDriverLog::GetLocalTimeStr(char *pBuf)
// {
// #ifdef WIN32
// 	SYSTEMTIME t;
// 	GetLocalTime(&t);
// 	sprintf(pBuf, "%04d-%02d-%02d %02d:%02d:%02d:%03d",
// 		t.wYear, t.wMonth, t.wDay, 
// 		t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
// #else
//  	struct timeval tv;
// 	gettimeofday(&tv,0);	
// 	time_t t = tv.tv_sec;
// 	struct tm *ptm = localtime(&t);
// 	
// 	char buf[100] = {0};
// 	strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S:", ptm);
// 	sprintf(buf,"%s:%03ld >",buf,tv.tv_usec/1000);
// 	
// 	memcpy(pBuf,buf,sizeof(buf));
// 	
// #endif
// }
// 
// /**************************************************************************
// * �������ƣ� GetShortLocalTimeStr(char *pBuf)
// * ���������� ��ȡϵͳʱ���������ַ�
// * ���ʵı� 
// * �޸ĵı� 
// * ��������� 
// * ��������� char *pBuf
// * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// * ����˵���� 
// * �޸�����    �汾��     �޸���	     �޸�����
// * -----------------------------------------------
// * 2012/03/07  V1.0	     regbin	     �����ļ�
// **************************************************************************/
// void CDriverLog::GetShortLocalTimeStr(char *pBuf)
// {
// #ifdef WIN32
// 	SYSTEMTIME t;
// 	GetLocalTime(&t);
// 	sprintf(pBuf, "%02d:%02d:%03d",
// 		t.wMinute, t.wSecond, t.wMilliseconds);
// #else
//  	struct timeval tv;
// 	gettimeofday(&tv,0);	
// 	time_t t = tv.tv_sec;
// 	struct tm *ptm = localtime(&t);
// 	char buf[100] = {0};
// 	strftime(buf, sizeof(buf), "%M:%S:", ptm);
// 	sprintf(buf,"%s:%03ld >",buf,tv.tv_usec/1000);
// 	
// 	memcpy(pBuf,buf,sizeof(buf));	
// #endif
// 	
// }
// 
// 
// /**************************************************************************
// * �������ƣ� SaveLog(const char *pStr, int nLen)
// * ���������� д��������
// * ���ʵı� 
// * �޸ĵı� 
// * ��������� const char *pStr, int nLen
// * ��������� 
// * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// * ����˵���� 
// * �޸�����    �汾��     �޸���	     �޸�����
// * -----------------------------------------------
// * 2012/03/07  V1.0	     regbin	     �����ļ�
// **************************************************************************/	 
// void CDriverLog::SaveLog(const char *pStr, int nLen)
// {
// 	if (nLen < 0)
// 		nLen = strlen(pStr);
// 
// 	if (m_nLogDataLen + nLen > m_nAllLogLen)
// 	{
// 		int nNewAllLoglen =  m_nAllLogLen * 2;
// 		if (nNewAllLoglen < m_nLogDataLen + nLen)
// 		{
// 			nNewAllLoglen = (m_nLogDataLen + nLen + LOG_ALLOC_SAVE -1)
// 				/LOG_ALLOC_SAVE * LOG_ALLOC_SAVE;
// 		}
// 		char *pNew = new char[nNewAllLoglen];
// 		if (m_nLogDataLen > 0)
// 			memcpy(pNew, m_pLogData, m_nLogDataLen);
// 		delete []m_pLogData;
// 		m_pLogData = pNew;
// 		m_nAllLogLen = nNewAllLoglen;
// 	}
// 
// 	memcpy(m_pLogData + m_nLogDataLen, pStr, nLen);
// 	m_nLogDataLen += nLen;
// }
// 
// 
// /**************************************************************************
// * �������ƣ� WriteLogFile()
// * ���������� ������д���ļ���
// * ���ʵı� 
// * �޸ĵı� 
// * ��������� 
// * ��������� 
// * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// * ����˵���� 
// * �޸�����    �汾��     �޸���	     �޸�����
// * -----------------------------------------------
// * 2012/03/07  V1.0	     regbin	     �����ļ�
// **************************************************************************/	 
// void CDriverLog::WriteLogFile()
// {
// 	if(m_nLogDataLen == 0)
// 		return;
// 
// 	char szLogFile[MAX_PATH];
// 
// #ifdef WIN32
// 	SYSTEMTIME t;
// 	GetSystemTime(&t);	
// 	sprintf(szLogFile,"./%s_%04d-%02d-%02d.log",m_szDeviceName,t.wYear, t.wMonth, t.wDay);
// 
// #else
// 	struct timeval tv;
// 	gettimeofday(&tv,0);	
// 	time_t t = tv.tv_sec;
// 	struct tm *ptm = localtime(&t);
// 	
// 	char bufTime[100];
// 	strftime(bufTime, sizeof(bufTime), "%Y-%m-%d", ptm);
// 	
// 	sprintf(szLogFile,"./%s_%s.log",m_szDeviceName,bufTime);
// 	
// #endif
// 
// 		//д��־���ļ���
// 	int nDataLogLen = m_nLogDataLen;
// 	m_nLogDataLen = 0;
// 	FILE *fp = fopen(szLogFile, "a+t");
// 	if (fp == NULL)
// 		return;
// 	fwrite(m_pLogData, nDataLogLen, 1, fp);
// 	fclose(fp);
// }
// 
// /**************************************************************************
// * �������ƣ� WriteFuncName(char *pFuncName);
// * ���������� д��������
// * ���ʵı� 
// * �޸ĵı� 
// * ��������� char *pFuncName
// * ��������� 
// * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// * ����˵���� 
// * �޸�����    �汾��     �޸���	     �޸�����
// * -----------------------------------------------
// * 2012/03/07  V1.0	     regbin	     �����ļ�
// **************************************************************************/
// int CDriverLog::WriteFuncName(const char *pFuncName)
// {
// 	char Buf[100];
// 	SaveLog("\n\n");
// 	GetLocalTimeStr(Buf);
// 	SaveLog(Buf);
// 	SaveLog(" ");
// 	SaveLog(pFuncName);
// 	SaveLog("\n");
// 	return 0;
// }
// 
// 
// 
// /**************************************************************************
// * �������ƣ� WriteFLSHLog(const char *pFlshStr);
// * ���������� д����������־
// * ���ʵı� 
// * �޸ĵı� 
// * ��������� const char *pFlshStr
// * ��������� 
// * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// * ����˵���� 
// * �޸�����    �汾��     �޸���	     �޸�����
// * -----------------------------------------------
// * 2012/03/07  V1.0	     regbin	     �����ļ�
// **************************************************************************/
// int CDriverLog::WriteFLSHLog(const char *pFlshStr)
// {
// 	char Buf[100];
// 	GetShortLocalTimeStr(Buf);
// 	SaveLog(Buf);
// 	sprintf(m_szBuf, "  FLSH[ %s]",pFlshStr);
// 	SaveLog(m_szBuf);
// 	SaveLog("\n");
// 	return 0;
// }
// 
// 
// 
// /**************************************************************************
// * �������ƣ� WriteSendDataHex(const char *pSendStr, int nLen);
// * ���������� д�������ݵ��豸������־
// * ���ʵı� 
// * �޸ĵı� 
// * ��������� const char *pSendStr, int nLen
// * ��������� 
// * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// * ����˵���� 
// * �޸�����    �汾��     �޸���	     �޸�����
// * -----------------------------------------------
// * 2012/03/07  V1.0	     regbin	     �����ļ�
// **************************************************************************/	 
// int CDriverLog::WriteSendDataHex(const char *pSendStr, int nLen)
// {
// 
// 	char Buf[100];
// 	GetShortLocalTimeStr(Buf);
// 	SaveLog(Buf);
// 	SaveLog(" ");	
// 	
// 	int Len =0;
// 	Len = nLen;
// 	if (nLen < 0)
// 		Len = strlen(pSendStr);
// 
// 	sprintf(m_szBuf, " WRIT[ %d] ",Len);
// 	SaveLog(m_szBuf);
// 
// 	char szbuf[100];
// 	for (int i = 0; i < Len; i++)
// 	{
// 		sprintf(szbuf, "%02X ", (BYTE)(pSendStr[i]));
// 		SaveLog(szbuf);
// 
// 	}
// 	SaveLog("\n");
// 	return 0;
// 
// }
// 
// 
// /**************************************************************************
// * �������ƣ� WriteSendDataHex(const char *pSendStr, int nLen);
// * ���������� д�������ݵ��豸������־
// * ���ʵı� 
// * �޸ĵı� 
// * ��������� const char *pReadStr, int nLen
// * ��������� 
// * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// * ����˵���� 
// * �޸�����    �汾��     �޸���	     �޸�����
// * -----------------------------------------------
// * 2012/03/07  V1.0	     regbin	     �����ļ�
// **************************************************************************/	 
// int CDriverLog::WriteReadDataHex(const char *pReadStr, int nLen)
// {
// 
// 	
// 	char Buf[100];
// 	GetShortLocalTimeStr(Buf);
// 	SaveLog(Buf);
// 	SaveLog(" ");	
// 	
// 	int Len =0;
// 	Len = nLen;
// 	if (nLen < 0)
// 		Len = strlen(pReadStr);
// 
// 	sprintf(m_szBuf, " READ[ %d] ", Len);
// 	SaveLog(m_szBuf);
// 
// 	char szbuf[100];
// 	for (int i = 0; i < Len; i++)
// 	{
// 		sprintf(szbuf, "%02X ", (BYTE)(pReadStr[i]));
// 		SaveLog(szbuf);
// 	}
// 	SaveLog("\n");
// 	return 0;	
// }
// 
// 
// 
// /**************************************************************************
// * �������ƣ� WriteErrorLog(const char *pStr);
// * ���������� д������־
// * ���ʵı� 
// * �޸ĵı� 
// * ��������� const char *pStr
// * ��������� 
// * �� �� ֵ�� 0 �ɹ�     <0 ʧ��
// * ����˵���� 
// * �޸�����    �汾��     �޸���	     �޸�����
// * -----------------------------------------------
// * 2012/03/08  V1.0	     regbin	     �����ļ�
// **************************************************************************/	 
// int CDriverLog::WriteErrorLog(const char *pStr)
// {
// 	SaveLog(pStr);
// 	SaveLog("\n");
// 	return 0;
// }


// ���ô���ͨ�Ų���
int CSerialPort::iSetComParam(stComDevParam p_stComDevParam)
{
	memcpy(&m_stComDevParam, &p_stComDevParam, sizeof(stComDevParam));
	
	return 0;
}
// ��������
int CSerialPort::iOpenPort()
{
	char portName[10];
	memset(portName, 0x00, sizeof(portName));

	sprintf(portName, "%d", m_stComDevParam.iPort);

	return OpenPort(portName, m_stComDevParam.dwBoud, 'N', 8, 1);
}

// �رմ���
int CSerialPort::iClosePort()
{
	ClosePort();

	return 0;
}
// ��������
int CSerialPort::iSendCmd(void *pBuf, unsigned long dwLength)
{
//	printf("CSerialPort::iSendCmd length = %d.\r\n", dwLength);
	return WriteComm((const char *)pBuf, dwLength, 10);
}

// ������������Ϣ
int CSerialPort::iRecvResult(char *pBuf, int dwLength, unsigned long& p_dwBytes, int timeOut)
{
	p_dwBytes = ReadComm(pBuf, dwLength, timeOut);

	if(p_dwBytes != dwLength)
		return 1;

	return 0;
}

// ������ܻ�����
int CSerialPort::iClearSendBuff()
{
	PurgeCommFlag(PURGE_OUT);

	return 0;
}

// �����ͻ�����
int CSerialPort::iClearRecvBuff()
{
	PurgeCommFlag(PURGE_IN);

	return 0;
}
