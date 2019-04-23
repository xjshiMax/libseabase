// openssltest.cpp : 定义控制台应用程序的入口点。
//  sha1 加密
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <openssl/sha.h>
#include <openssl/md5.h>
using namespace std;
//#pragma comment(lib,"windows/libcrypto.lib")
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
int main() {

	sha1crypt();
	md5crypt();
	return 0;


}

