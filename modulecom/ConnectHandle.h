/* 2021-3-23 xjshi
�ڶ����ģ�ͼܹ��У��������ϼ��ڵ������Ϣͨ��
1.tcp �ͻ���ģʽ
2.tcp�����ģʽ
3.�������
4.���ն���
5.���Ͷ���
*/
#pragma once
#include "base/include/xbaseclass.h"
#include "base/include/xEtcpclient.h"
#include "base/include/xReactor.h"
using namespace SEABASE;
class ConnectHandle : public  xReceivebackbase
{
public:
	 void init();
	 void Ondata(int socketfd,char*data,int len);
	 void Onclose(int socketfd);
	 int  Connect(string charip,int port);
	 xReactor m_reactor;
	 ExTcpClient m_client;
};