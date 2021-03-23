#include <stdio.h>
#include "cryptWapper.h"
//#include "base/openssl/include/openssl/md5.h" ���·����openssl��ʼ������ᱨ��
#include"openssl/md5.h"
#include"openssl/sha.h"
//�����
#include "openssl/evp.h"
#include "openssl/bio.h"
#include "openssl/buffer.h"
int cryptWapper::getmd5()
{
	//md5 ժҪΪ16���ֽڳ��ȣ�ת�����ַ���32���ַ�.
	 MD5_CTX md5;
	 MD5_Init(&md5);
	 MD5_Update(&md5,m_data.c_str(),m_data.length());
	 unsigned char result[64]={0};
	 MD5_Final(result,&md5);
	 printf("md5 data:  %s",m_data.c_str());
	 printf("md5 encode:");
	 for(int i=0;i<16;i++)
		printf("%02x",result[i]);
	  printf("\n\n");
	  unsigned char other[64];
	 // MD5_Transform(&md5,other);
	  //ֱ�ӵ���md5 ������3����Ľ����һ����
	  MD5((unsigned char*)m_data.c_str(),m_data.length(),other);
	   printf("other md5 encode:");
	  for(int i=0;i<16;i++)
		  printf("%02x",other[i]);
	  printf("\n\n");
}
int	cryptWapper::getsha1()
{
	//ժҪΪ20�ֽ�����
	printf("sha1 data:  %s",m_data.c_str());
	printf("sha1 encode:");
	unsigned char other[64];
	SHA1((unsigned char*)m_data.c_str(),m_data.length(),other);
	for(int i=0;i<20;i++)
		printf("%02x",other[i]);
	printf("\n\n");
}
int cryptWapper::getsha256()
{
	//ժҪΪ32�ֽ�����
	printf("sha256 data:  %s",m_data.c_str());
	printf("sha256 encode:");
	unsigned char other[64];
	SHA256((unsigned char*)m_data.c_str(),m_data.length(),other);
	for(int i=0;i<32;i++)
		printf("%02x",other[i]);
	printf("\n\n");
}
int cryptWapper::enCode_base64()
{

	//Base64Ҫ���ÿ����8Bit���ֽ�ת��Ϊ�ĸ�6Bit���ֽڣ�3*8 = 4*6 = 24����Ȼ���6Bit������λ��λ0������ĸ�8Bit���ֽڣ�
	//Ҳ����˵��ת������ַ��������Ͻ�Ҫ��ԭ���ĳ�1/3��
	BIO *bmem = NULL;
	BIO *b64 = NULL;
	BUF_MEM *bptr;

	b64 = BIO_new(BIO_f_base64());
	if (!false) {
		BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	}
	bmem = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64, bmem);
	BIO_write(b64, m_data.c_str(),m_data.length());
	BIO_flush(b64);
	BIO_get_mem_ptr(b64, &bptr);
	BIO_set_close(b64, BIO_NOCLOSE);

	char *buff = (char *)malloc(bptr->length + 1);
	memcpy(buff, bptr->data, bptr->length);
	buff[bptr->length] = 0;
	BIO_free_all(b64);
	string strbuff=buff;
	printf("origin data:%s\n",m_data.c_str());
	printf("encode data:%s\n",strbuff.c_str());
	return 0;
	//return buff;

}
int cryptWapper::dec_base64()
{
	BIO *b64 = NULL;
	BIO *bmem = NULL;
	char *buffer = (char *)malloc(m_encodeData.length());
	memset(buffer, 0, m_encodeData.length());
	b64 = BIO_new(BIO_f_base64());
	if (!false) {
		BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	}
	bmem = BIO_new_mem_buf(m_encodeData.c_str(), m_encodeData.length());
	bmem = BIO_push(b64, bmem);
	BIO_read(bmem, buffer, m_encodeData.length());
	BIO_free_all(bmem);
	string strbuff=buffer;
	printf("origin data:%s\n",m_encodeData.c_str());
	printf("deccode data:%s\n",strbuff.c_str());
	//return buffer;

}
int cryptWapper::enCode_rsa()
{

}
int cryptWapper::dec_rsa()
{

}