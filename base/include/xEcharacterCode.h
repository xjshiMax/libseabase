//2019-7-31 xjshi
/*
1)����ַ�����֮���ת��
2) ��Ҫ�� utf-8 gbk asic bdc�� hex dec ֮��ת��
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
        static bool Ascii2utf8();
        static bool Utf8ToAscii();
        static bool Ascii2BCD();

        static bool Hex2Ascii();
    };
}

/*���뷽ʽ���*/
/*
GB2312
GBK
UTF-8
ASCII
BCD

*/