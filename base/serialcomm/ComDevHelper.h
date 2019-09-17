#pragma once

#include <string>

#ifdef WIN32
#include "CComDevBase.h"
#else
#include "SerialPort.h"
#endif

typedef void (*ProgressNotify)(int maxFrame,int currentFrame,int frameSize,void *args);


class CComDevHelper
{
public:
	CComDevHelper(void);

	~CComDevHelper(void);

	bool IsValid();

	//int InitComParam(int nPort,int baud=115200);

	int OpenCom(int nPort,int baud);

	int CloseCom();

	int ClearSendBuffer();

	int ClearRecvBuffer();

	int Send(char * pData,unsigned int uSize);

	int Recv(char * pData,int uDataSize,unsigned long & recvLen, int timeOut = 3000);

	int SendFile(std::string filePath,int frameSize,ProgressNotify notify,void * args);

private:

#ifdef WIN32
	CComDevBaseSync m_ComDev;
#else
	CSerialPort m_ComDev;
#endif

	stComDevParam                    m_ComParam;

	bool m_bValid;
/*	CComDevBaseSync * m_pComDev;*/
};
