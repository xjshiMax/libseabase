//2021-3-18
//封装openssl 常用调用，加解密
/*
1)md5 摘要
2）sha1摘要
3）sha256摘要
4）base64加密解密
5）des 加密解密
6）
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
	string m_data; //原始数据
	string m_encodeData;	 //密文

};