//定义事件，四字节
#pragma once
#include<stdio.h>
const unsigned int Cmd_Getcupinfp			= 0x00000101;
const unsigned int Cmd_GetcupVersion			= 0x00000102;
const unsigned int Cmd_GetProcessInfo		= 0x00000103;
const unsigned int Cmd_openssl_md5encode		= 0x00000104;
const unsigned int Cmd_openssl_sha1encode	= 0x00000105;
const unsigned int Cmd_openssl_sha256encode	= 0x00000106;
const unsigned int Cmd_openssl_base64encode	= 0x00000107;
const unsigned int Cmd_openssl_base64decode	= 0x00000108;

