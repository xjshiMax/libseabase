
#include "comdevhelper.h"
//#include "FileUtil.h"

#define   FUNCTION_EXCUTE_FAILED ( -1 )
#define   FUNCTION_EXCUTE_SUCESSED ( 0 )

CComDevHelper::CComDevHelper()
{

	//m_ComDev.reset(new CComDevBaseSync());

	m_bValid =false;
}

CComDevHelper::~CComDevHelper(void)
{
}

bool CComDevHelper::IsValid(){

	return m_bValid;
}

// int CComDevHelper::InitComParam(int nPort,int baud){
// 
// 	m_ComParam.iPort = nPort;
// 
// 	m_ComParam.dwBoud = baud;
// 
// 
// 	return m_ComDev.iSetComParam(m_ComParam);
// 
// }

int CComDevHelper::OpenCom(int nPort,int baud)
{
	if (m_bValid)
	{
		return FUNCTION_EXCUTE_FAILED;
	}

	m_ComParam.iPort = nPort;

	m_ComParam.dwBoud = baud;

	m_ComDev.iSetComParam(m_ComParam);

	if (FUNCTION_EXCUTE_SUCESSED == m_ComDev.iOpenPort())
	{
		m_bValid=true;

		return FUNCTION_EXCUTE_SUCESSED;
	}

	return FUNCTION_EXCUTE_FAILED;
}

int CComDevHelper::CloseCom(){

	if (m_bValid)
	{
		m_bValid = false;

		m_ComDev.iClosePort();		
	}

	return FUNCTION_EXCUTE_SUCESSED;
}

int CComDevHelper::ClearSendBuffer(){

	if (m_bValid)
	{
		return m_ComDev.iClearSendBuff(); 
	}

	return FUNCTION_EXCUTE_FAILED;
}

int CComDevHelper::ClearRecvBuffer(){

	if (m_bValid)
	{
		return m_ComDev.iClearRecvBuff(); 
	}

	return FUNCTION_EXCUTE_FAILED;

}

int CComDevHelper::Send(char * pData,unsigned int uSize){

	if (m_bValid)
	{
		//m_ComDev.iClearRecvBuff(); 
		int ret = m_ComDev.iSendCmd(pData,uSize);
		if(ret != uSize)
		{
		    printf("CComDevHelper::Send  Send data failed ret = %d uSize = %d\r\n", ret, uSize);
			m_ComDev.iClearSendBuff();
		}
		else
		{
		   return 0;
		}

	}

	return FUNCTION_EXCUTE_FAILED;

	
}


int CComDevHelper::Recv(char * pData,int uDataSize,unsigned long & recvLen, int timeOut)
{

	if (m_bValid)
	{
		int ret = 0;
#ifdef WIN32
		ret = m_ComDev.iRecvResult(pData,uDataSize,recvLen);
#else
		ret = m_ComDev.iRecvResult(pData,uDataSize,recvLen, timeOut);
#endif
		if(ret != 0)
		{
		    printf("CComDevHelper::Recv Recv data failed.\r\n");
			m_ComDev.iClearRecvBuff();
		}
		else
		{
			return 0;
		}
	}

	return FUNCTION_EXCUTE_FAILED;	
}


int CComDevHelper::SendFile(std::string filePath,int frameSize,ProgressNotify notify,void * args){

	unsigned long uFileSize =0;

	if (filePath.empty()|| frameSize<=0)
	{
		return FUNCTION_EXCUTE_FAILED;
	}
	
//	if (FileUtil_GetFileSize((char*)filePath.c_str(),uFileSize))
//	{
//		return FUNCTION_EXCUTE_FAILED;
//	}

	



	
	return FUNCTION_EXCUTE_SUCESSED;
}
