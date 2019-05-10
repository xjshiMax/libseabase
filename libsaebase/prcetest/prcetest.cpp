// prcetest.cpp : �������̨Ӧ�ó������ڵ㡣
//
#define SUPPORT_PCRE8
#define PCRE_STATIC
#include <stdio.h>
#include <string>
#include "pcre.h"
#include <Windows.h>
#include <WinBase.h>
using namespace std;
// #define OVECCOUNT 30 /* should be a multiple of 3 */  
// #define EBUFLEN 128  
// #define BUFLEN 1024 
//#pragma comment(lib,"prcelib.lib")
//#pragma comment(lib,"E:/workstation/libsaebase/bindebug/pcredll.lib")

typedef  pcre*(*ppcre_compile)(const char *, int, const char **, int *,
	const unsigned char *); 
typedef int  (*ppcre_exec)(const pcre *, const pcre_extra *, PCRE_SPTR,
	int, int, int, int *, int);


ppcre_compile  L_pcre_compile;
ppcre_exec	   L_pcre_exec;
BOOL  fFreeResult;

//����DLL�ļ�����ȡDLL���
HMODULE hinstLib =LoadLibraryA((LPCSTR)"E:/workstation/libsaebase/bindebug/pcredll.dll");

//�����Ч����ȡsum������ַ


int main(void)
{
	if ( hinstLib != NULL )
	{
		L_pcre_compile =(ppcre_compile)GetProcAddress(hinstLib,"pcre_compile");
		L_pcre_exec = (ppcre_exec)GetProcAddress(hinstLib,"pcre_exec");
		

		//fFreeResult = FreeLibrary(hinstLib);
	}
	int erroroffset;
	int offsetcount;
	int offset[(10)*3];
	const char * error;
	char *cm_pattern = "^(9999)$";
	char *un_pattern = "^agt(.*)";
	char *cdma_pattern = "[0-9]{13}";
//	char *isnum_pattern = "^1[0-9]{10}$";
	//char str[15] = {0};
	pcre *cmPN, *unPN, *cdmaPN, *isnumPN;
	int cm, un, cdma, isnum;
	void *p1,*p2,*p3,*p4;
	pcre_extra*pextra;
	const unsigned char*pchar;
	char*ppchar;
	//ppchar=(char*)pcre_version();
	//pcre_pattern_to_host_byte_order(cmPN,pextra,pchar);
//	printf("\n�ֻ�������Ӫ�̼�⣬�����������ֻ����룺\n>");
	//scanf("%s", str);
	//char str[]="sofia/internal/1006@192.168.2.143:56926";
	char str[]="8815990071965";
 	cmPN = L_pcre_compile(cm_pattern, 0,&error, &erroroffset, NULL);
 	unPN = L_pcre_compile(un_pattern, 0, &error, &erroroffset, NULL);
 	cdmaPN = L_pcre_compile(cdma_pattern, 0, &error, &erroroffset, NULL);
// 	isnumPN = L_pcre_compile(isnum_pattern, 0, &error, &erroroffset, NULL);   
	if (cmPN == NULL
		&&unPN == NULL
		&&cdmaPN == NULL
		&&isnumPN == NULL){
			printf("������ʽ����\n");
	}

	//isnum = L_pcre_exec(isnumPN, NULL, str, strlen(str), 0, 0, offset, (10)*3);
// 	if (isnum < 0){
// 		if (isnum == PCRE_ERROR_NOMATCH){
// 			printf("�ֻ����볤�Ȳ���11λ����\n");
// 		}else{
// 			printf("������ʽƥ�����!\n");
// 		}
// 		return 1;
// 	}

	cm = L_pcre_exec(cmPN, NULL, str, strlen(str), 0, 0, offset, (10)*3);
	if (cm > 0){
		printf("��������ǣ��й��ƶ����롣\n");
		return 0;
	}
	un = L_pcre_exec(unPN, NULL,str, strlen(str), 0, 0, offset, (10)*3);
	if (un > 0){
		printf("��������ǣ��й���ͨ���롣\n");
		return 0;
	}
	cdma = L_pcre_exec(cdmaPN, NULL, str, strlen(str), 0, 0, offset, (10)*3);
	string strsub="";
	if (cdma > 0){
		//printf("��������ǣ��й����ź��롣\n");
		string strsrc=str;
		int len =offset[1]-offset[0];
		strsub=strsrc.substr(offset[0],len);
		strsub=strsub.erase(0,1);
		strsub=strsub.erase(strsub.length()-1,1);
		return 0;
	}
	return 0;
}