//2019-7-31 xjshi
/*
1)添加字符编码之间的转换
2) 主要在 utf-8 gbk asic bdc码 hex dec 之间转换
*/

#pragma once
#include <string>

#ifdef WIN32

#else

#endif
using namespace std;
namespace SEABASE
{
    class CharacterCode
    {
    public:
        static int GetCharacterTpye();
        static string Gb2312ToUTF_8(char* gb2312);
		static string UTF_8ToGb2312(const char* utf8);
        static bool Ascii2utf8();
        static bool Utf8ToAscii();
        static void Ascii2BCD( char *bcd_buf, char *asc_buf,int num);

        static bool Hex2Ascii();

		static wchar_t* AnsiToUnicode(const char* szStr);
    };
}

/*编码方式简介*/
/*
GB2312
GBK
1) GBK 兼容GB2312,用两个字节表示一个汉字。为中国特有的一种字符编码。
UTF-8
1）UTF-8 国际标准，英文用一个字节表示，中文用三个字节表示
ASCII
BCD
1)    BCD码（Binary-Coded Decimal‎），用4位二进制数来表示1位十进制数中的0~9这10个数码，是一种二进制的数字编码形式，用二进制编码的十进制代码。
BCD码这种编码形式利用了四个位元来储存一个十进制的数码，使二进制和十进制之间的转换得以快捷的进行。
2)    比如56 将十位和个位分开，即两位十进制数，表示为 0101 0110
*/