//2021-3-18
//��װopenssl ���õ��ã��ӽ���
/*
1)md5 ժҪ
2��sha1ժҪ
3��sha256ժҪ
4��base64���ܽ���
5��des ���ܽ���
6��
*/
#include <stdio.h>
#include<string.h>
#include<string>
using namespace std;
class cryptWapper
{
public:
	int getmd5();
	int	getsha1();
	int getsha256();
	int enCode_base64();
	int dec_base64();
	int enCode_rsa();
	int dec_rsa();
	string m_data; //ԭʼ����
	string m_encodeData;	 //����

};