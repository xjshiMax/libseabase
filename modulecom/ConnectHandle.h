/* 2021-3-23 xjshi
在多进程模型架构中，负责与上级节点进行消息通信
1.tcp 客户端模式
2.tcp服务端模式
3.数据组包
4.接收队列
5.发送队列
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