// openssltest.cpp : 定义控制台应用程序的入口点。
//  sha1 加密
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "openssl/x509.h"
#include <openssl/sha.h>
#include <openssl/md5.h>
#include "openssl/rsa.h"
#include "openssl/pem.h"
#include "openssl/bio.h"
#include "openssl/pkcs12.h"
#include "openssl/evp.h"
#include "openssl/ossl_typ.h"
#include "openssl/evp_locl.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
/*#include "openssl/evp_locl"*/
using namespace std;
//#pragma comment(lib,"windows/libcrypto.lib")
#pragma comment(lib,"../../base/openssl/lib/windows/lib32/libssl_static.lib")
#pragma comment(lib,"../../base/openssl/lib/windows/lib32/libcrypto_static.lib")
//#pragma comment(lib,"E:/workstation/libsaebase/base/openssl/lib/windows/libssl_static.lib")
//#pragma comment(lib,"../../base/openssl/lib/windows/libcrypto_static.lib")

void sha1crypt()
{
	unsigned char digest[SHA_DIGEST_LENGTH];
	const char* string_ = "hello world";

	SHA_CTX ctx;
	SHA1_Init(&ctx);
	SHA1_Update(&ctx, string_, strlen(string_));
	SHA1_Final(digest, &ctx);

	char mdString[SHA_DIGEST_LENGTH*2+1];
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++)

		sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

	printf("SHA1 digest: %s\n", mdString);
}

void md5crypt()
{
	const std::string srcStr;
	std::string encodedStr;
	std::string encodedHexStr;
	unsigned char mdStr[33] = {0};  
	MD5((const unsigned char *)srcStr.c_str(), srcStr.length(), mdStr);  

	// 哈希后的字符串    
	encodedStr = std::string((const char *)mdStr);  
	// 哈希后的十六进制串 32字节    
	char buf[65] = {0};  
	char tmp[3] = {0};  
	for (int i = 0; i < 32; i++)  
	{  
		sprintf(tmp, "%02x", mdStr[i]);  
		strcat(buf, tmp);  
	}  
	buf[32] = '\0'; // 后面都是0，从32字节截断    
	encodedHexStr = std::string(buf);  
	printf("srcStr:%s\n",srcStr.c_str());
	printf("encodedStr:%s\n",encodedStr.c_str());
	printf("encodedHexStr:%s\n",encodedHexStr.c_str());
}
std::string rsa_pub_encrypt(const std::string &clearText, const std::string &pubKey)  
{  
	std::string strRet;  
	RSA *rsa = NULL;  
	BIO *keybio = BIO_new_mem_buf((unsigned char *)pubKey.c_str(), -1);  
	// 此处有三种方法  
	// 1, 读取内存里生成的密钥对，再从内存生成rsa  
	// 2, 读取磁盘里生成的密钥对文本文件，在从内存生成rsa  
	// 3，直接从读取文件指针生成rsa  
	RSA* pRSAPublicKey = RSA_new();  
	rsa = PEM_read_bio_RSAPublicKey(keybio, &rsa, NULL, NULL);  

	int len = RSA_size(rsa);  
	char *encryptedText = (char *)malloc(len + 1);  
	memset(encryptedText, 0, len + 1);  

	// 加密函数  
	int ret = RSA_public_encrypt(clearText.length(), (const unsigned char*)clearText.c_str(), (unsigned char*)encryptedText, rsa, RSA_PKCS1_PADDING);  
	if (ret >= 0)  
		strRet = std::string(encryptedText, ret);  

	// 释放内存  
	free(encryptedText);  
	BIO_free_all(keybio);  
	RSA_free(rsa);  

	return strRet;  
}  
void sha256crypt()
{
	unsigned char digest[SHA256_DIGEST_LENGTH];
    const unsigned char string_[] ="你好";
    int len=strlen((const char*)string_);
// 	SHA256_CTX ctx;;
// 	SHA256_Init(&ctx);
// 	SHA256_Update(&ctx, string_, strlen(string_));
// 	SHA256_Final(digest, &ctx);
	char mdString[SHA256_DIGEST_LENGTH*2+1];
    SHA256((const unsigned char*)string_,sizeof(string_),digest);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)

		sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

	printf("SHA1 digest: %s\n", mdString);
}

int pfxparse(string clearText)
{
	FILE* fp;
    std::string strRet;  
    RSA *rsa = NULL;  
   // BIO *keybio = BIO_new_mem_buf((unsigned char *)pubKey.c_str(), -1); 
	if (!(fp = fopen("utp_test_sign.pfx", "rb"))) 
	{ 
		fprintf(stderr, "Error opening file utp_test_sign.pfx\n");       
		return NULL;     
	}    
	PKCS12 *p12= d2i_PKCS12_fp(fp, NULL);  
	fclose (fp);    
	if (!p12) {      
		fprintf(stderr, "Error reading PKCS#12 file\n");   
		//ERR_print_errors_fp(stderr);  
		return NULL;   
	} 
	EVP_PKEY *pkey=NULL;     
	X509 *x509=NULL;
	STACK_OF(X509) *ca = NULL;
	if (!PKCS12_parse(p12, "000000", &pkey, &x509, &ca)) {         
		fprintf(stderr, "Error parsing PKCS#12 file\n");       
		//ERR_print_errors_fp(stderr);
		return NULL;
	}
	PKCS12_free(p12);
    rsa=EVP_PKEY_get1_RSA(pkey);
    int len = RSA_size(rsa);  
    char *encryptedText = (char *)malloc(len + 1);  
    memset(encryptedText, 0, len + 1);  

    // 加密函数  
    int ret = RSA_public_encrypt(clearText.length(), (const unsigned char*)clearText.c_str(), (unsigned char*)encryptedText, rsa, RSA_PKCS1_PADDING);  
    if (ret >= 0)  
        strRet = std::string(encryptedText, ret);  

    // 释放内存  
    free(encryptedText);  
  //  BIO_free_all(keybio);  
    RSA_free(rsa);  

    return 0;  
	//
//    RSA *rsaInst=EVP_PKEY_get1_RSA(pkey);
//     unsigned char n[300]={0};
//     unsigned char e[300]={0};
//     if(rsaInst->n!=NULL)
//     {
//         BN_bn2bin(rsaInst->n,n);
//         len=BN_num_bytes(rsaInst->n);
//         printf("N:\n");
//         for(int i=0;i<len;i++)
//             printf("%02x",n);
//         printf("\n");
//     }
//     if(rsaInst->n!=NULL)
//     {
//         BN_bn2bin(rsaInst->e,e);
//         len=BN_num_bytes(rsaInst->e);
//         printf("E:\n");
//         for(int i=0;i<len;i++)
//             printf("%02x",e);
//         printf("\n");
//    }
	return 0;
}
int32_t Base64Encode(const char *encoded, int encoded_length, char *decoded){
    return EVP_EncodeBlock((unsigned char*)decoded, (const unsigned char*)encoded, encoded_length);
}
void base64_encode(const char * input,int in_length,char** output)
{
    BIO* bmem = NULL;
    BIO* b64 = NULL;
    BUF_MEM* bptr = NULL;
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, in_length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);
    *output = (char *)malloc(bptr->length + 1);
    memcpy(*output, bptr->data, bptr->length);
    (*output)[bptr->length] = 0;
    BIO_free_all(b64);
//    BIO_free_all(bmem);
}
void base64_decode(const char * input,int in_length,char** output,int* out_length)
{
    BIO* b64 = NULL;
    BIO* bio = NULL;
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new_mem_buf(input, in_length);
    bio = BIO_push(b64, bio);
    *output = (char*)malloc(in_length);
    *out_length = BIO_read(bio, *output, in_length);
    BIO_free_all(bio);
    //BIO_free_all(b64);
}



char * Base64Encode(const char * input, int length, bool with_new_line)
{
    BIO * bmem = NULL;
    BIO * b64 = NULL;
    BUF_MEM * bptr = NULL;

    b64 = BIO_new(BIO_f_base64());
    if(!with_new_line) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char * buff = (char *)malloc(bptr->length + 1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;

    BIO_free_all(b64);

    return buff;
}

char * Base64Decode(char * input, int length, bool with_new_line)
{
    BIO * b64 = NULL;
    BIO * bmem = NULL;
    char * buffer = (char *)malloc(length);
    memset(buffer, 0, length);

    b64 = BIO_new(BIO_f_base64());
    if(!with_new_line) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);
    BIO_read(bmem, buffer, length);

    BIO_free_all(bmem);

    return buffer;
}
void testsort()
{
    string strfirst="123=w&1.0=4.0";
    int len = strfirst.length()+1;
    char*pstr=new char[strfirst.length()+1];
    memset(pstr,0,len);
    strncpy(pstr,strfirst.c_str(),len-1);
    for(int i=0;i<len-1;i++)
    {
        int minindex=i;
        for(int j=i;j<len-1;j++)
        {
            if(*(pstr+minindex)>*(pstr+j))
            {
                minindex=j;
            }
        }
        if(i!=minindex)
        {
            char chartemp=pstr[i];
            pstr[i]=pstr[minindex];
            pstr[minindex]=chartemp;
        }
    }

}
int main() {
	//sha256crypt();
// 	char*p="3082010a02 82 01 01 00 ab 1e a8 af 9c f0 3a be 26 cf f5 f4 06 d5 bb 6c cb c1 7f e4 94 14 21 54 58 a0 58 24 6d 85 b3 41 a2 5c 91 87 6d 86 78 87 74 df 87 df fb 0b c6 59 06 7f 6e 83 f5 36 d8 12 01 1c 4b 41 93 22 4b 93 d1 62 54 ee 16 ea 26 49 ec 70 5c e9 a8 db 5e 5d 69 32 a9 86 aa 4b 91 85 5f ab be 70 e1 06 7a 74 b2 6d 69 9d 2c cd 95 5e 22 cc 47 7f 95 46 10 0f 1c 17 f6 86 8e 8e 32 aa ab ec 21 cd 56 ef ff 4c 33 68 57 67 6f b3 16 ba 55 81 52 37 1c 86 d2 4a a9 82 d8 5b 1d bb 70 a6 e0 8b 2d fc 38 97 9a ac 63 72 76 68 81 af 0e fd 30 17 4a 4a 7b d4 a1 4d f1 30 5a 71 e0 c3 2e cf 2b ad 83 09 30 32 aa 41 89 93 6a 18 30 f0 c7 1c ac 6e b7 71 58 59 65 37 e7 94 b4 07 0f 9d 68 07 66 46 e0 7c 79 aa 0e a1 1d 16 0c 93 47 d5 70 cf d7 cb fb 94 34 7a f1 d4 05 d3 a8 a7 e5 86 dc 2d 27 47 3e 2f 65 a8 57 73 02 03 01 00 01";
// 	while(*p!='\0')
// 	{
// 		if(*p!=' ')
// 			printf("%c",*p);
// 		p++;
// 	}
			//rsa_pub_encrypt("are you ok","30 82 01 0a 02 82 01 01 00 ab 1e a8 af 9c f0 3a be 26 cf f5 f4 06 d5 bb 6c cb c1 7f e4 94 14 21 54 58 a0 58 24 6d 85 b3 41 a2 5c 91 87 6d 86 78 87 74 df 87 df fb 0b c6 59 06 7f 6e 83 f5 36 d8 12 01 1c 4b 41 93 22 4b 93 d1 62 54 ee 16 ea 26 49 ec 70 5c e9 a8 db 5e 5d 69 32 a9 86 aa 4b 91 85 5f ab be 70 e1 06 7a 74 b2 6d 69 9d 2c cd 95 5e 22 cc 47 7f 95 46 10 0f 1c 17 f6 86 8e 8e 32 aa ab ec 21 cd 56 ef ff 4c 33 68 57 67 6f b3 16 ba 55 81 52 37 1c 86 d2 4a a9 82 d8 5b 1d bb 70 a6 e0 8b 2d fc 38 97 9a ac 63 72 76 68 81 af 0e fd 30 17 4a 4a 7b d4 a1 4d f1 30 5a 71 e0 c3 2e cf 2b ad 83 09 30 32 aa 41 89 93 6a 18 30 f0 c7 1c ac 6e b7 71 58 59 65 37 e7 94 b4 07 0f 9d 68 07 66 46 e0 7c 79 aa 0e a1 1d 16 0c 93 47 d5 70 cf d7 cb fb 94 34 7a f1 d4 05 d3 a8 a7 e5 86 dc 2d 27 47 3e 2f 65 a8 57 73 02 03 01 00 01");
	//sha1crypt();
	//md5crypt();
//     string entext="hello world";
// 	pfxparse(entext);
#if 0
//     char *result=new char[100];
//     memset(result,0,100);
//     char origindata[]="hello world";
//     int length=sizeof(origindata);
//     base64_encode(origindata,length,&result);
//     std::cout<<result<<endl;
//     char*p;
//     int decodelen=0;
//     base64_decode(result,strlen(result),&p,&decodelen);
//     std::cout<<*p;
#endif
    //char name[]="123456789";
    //string strtemp=string(name,4);
   // testsort();
    sha256crypt();  
	return 0;


}

