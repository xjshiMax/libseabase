//2021/1/17
/*
1.�������������
2.���幫�ýṹ��
*/
//error code
#pragma once
#define ERROR_OK			0
#define ERROR_FAIL		1



struct messageC{
	int messageType;
	char DeviceID[32];
	char DeviceIP[32];
	int Port;
	int status;
	int No;
	char data[256];

};
const unsigned int  timer_event = 0x00FF0000;


//����ģ�������
struct process_cycle_t
{				 

};