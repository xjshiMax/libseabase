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
//#include "openssl/evp_locl.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
/*#include "openssl/evp_locl"*/
#include <Windows.h>
using namespace std;
//#pragma comment(lib,"windows/libcrypto.lib")
#pragma comment(lib,"../../base/openssl/lib/windows/lib32/debug/libssl.lib")
#pragma comment(lib,"../../base/openssl/lib/windows/lib32/debug/libcrypto.lib")
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
    unsigned char digest[SHA256_DIGEST_LENGTH+1]={0};
    string string_ ="backUrl=39.96.46.166&body=01&limitCreditPay=0&mchCreateIp=39.96.46.166&mchntOrderId=201907090928550000000000&signCertId=17092992268642546173&signMethod=RSA2&timeExpired=20190709092955&timeStart=20190709092855&transAt=1&version=1.0.0";
    int len=string_.length();
    int lensizeof=sizeof(string_);
    int lenstelen=strlen(string_.c_str());
//  	SHA256_CTX ctx;;
//  	SHA256_Init(&ctx);
//  	SHA256_Update(&ctx, string_, sizeof(string_));
//  	SHA256_Final(digest, &ctx);
	char mdString[SHA256_DIGEST_LENGTH*2+1];
    SHA256((const unsigned char*)string_.c_str(),len,digest);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)

		sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

	printf("SHA1 digest: %s\n", mdString);
}
int littletest()
{
    unsigned char md[33] = {0};
    const unsigned char* string_ =(const unsigned char*)"backUrl=39.96.46.166&body=01&limitCreditPay=0&mchCreateIp=39.96.46.166&mchntOrderId=201907090928550000000000&signCertId=17092992268642546173&signMethod=RSA2&timeExpired=20190709092955&timeStart=20190709092855&transAt=1&version=1.0.0";

    SHA256((const unsigned char *)string_, strlen((const char*)string_), md);  

    int i = 0;  
    char buf[65] = {0};  
    char tmp[3] = {0};  
    for(i = 0; i < 32; i++ )  
    {  
        sprintf(tmp,"%02X", md[i]);  
        strcat(buf, tmp);  
    }  

    cout << buf << endl;   

    return 0;  
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
int Base64Encode(const char *encoded, int encoded_length, char *decoded){
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
string GetBase64Enc(string rsatext)
{
#if 1
    string finalresult="";
    BIO * bmem = NULL;
    BIO * b64 = NULL;
    BUF_MEM * bptr = NULL;
    int length=rsatext.length();
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);// 默认每64个字符换行，设置不换行
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, rsatext.c_str(), length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char * buff = (char *)malloc(bptr->length + 1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;
    string strtemp=string(buff,bptr->length);
    finalresult+=strtemp;
    BIO_free_all(b64);
    free(buff);
    return finalresult;
#endif
    return "";
}

int pubkey_decrypt(const unsigned char *in, int in_len,
    unsigned char **out, int &out_len)
{
    FILE* fp;
    RSA *rsa = NULL;  
    //m_sSSLKEY为pfx文件地址
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

    rsa=EVP_PKEY_get1_RSA(pkey);

    out_len =  RSA_size(rsa);
    *out =  (unsigned char *)malloc(out_len);
    if(NULL == *out)
    {
        printf("pubkey_decrypt:malloc error!\n");
        return -1;
    }
    memset((void *)*out, 0, out_len);

    printf("pubkey_decrypt:Begin RSA_public_decrypt ...\n");
    int ret =  RSA_private_decrypt(in_len, in, *out, rsa, RSA_NO_PADDING);

    return ret;
}

// 公钥加密函数
int pubkey_encrypt(const unsigned char *in, int in_len,
    unsigned char **out, int &out_len)
{
    FILE* fp;
    RSA *rsa = NULL;  
    //m_sSSLKEY为pfx文件地址
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

    rsa=EVP_PKEY_get1_RSA(pkey);
    out_len =  RSA_size(rsa);
    *out =  (unsigned char *)malloc(out_len);
    if(NULL == *out)
    {
        printf("pubkey_encrypt:malloc error!\n");
        return -1;
    }
    memset((void *)*out, 0, out_len);

    printf("pubkey_encrypt:Begin RSA_public_encrypt ...\n");
    int ret =  RSA_public_encrypt(in_len, in, *out, rsa, RSA_PKCS1_PADDING/*RSA_NO_PADDING*/);


    return ret;
}
char* Gb2312ToUTF_8(char* gb2312)
{
    int len=MultiByteToWideChar(CP_ACP,0,gb2312,-1,NULL,0);
    wchar_t*wstr=new wchar_t[len+1];
    memset(wstr,0,len+1);
    MultiByteToWideChar(CP_ACP,0,gb2312,-1,wstr,len);
    len=WideCharToMultiByte(CP_UTF8,0,wstr,-1,NULL,0,NULL,NULL);
    char*str=new char[len+1];
    memset(str,0,len+1);
    WideCharToMultiByte(CP_UTF8,0,wstr,-1,str,len,NULL,NULL);
    if(wstr)delete[] wstr;
    return str;
}
int main() {
	
    char* firsttxt="上网";
    char*secondtxt=Gb2312ToUTF_8(firsttxt);
    unsigned char*pencrypt=new unsigned char[1024];
    int encryptlen=strlen((char*)firsttxt);
    int utf8len=strlen(secondtxt);
    EVP_EncodeBlock(pencrypt,(unsigned char*)firsttxt,encryptlen);
    memset(pencrypt,0,1024);
    EVP_EncodeBlock(pencrypt,(unsigned char*)secondtxt,utf8len);
    //char* debase64 = Base64Encode((char*)firsttxt.c_str(),firsttxt.length(),false);
   // unsigned char*dectext;
   // int declen=0;
  //  pubkey_decrypt((const unsigned char*)debase64,strlen((const char*)debase64),&dectext,declen);
	return 0;


}

