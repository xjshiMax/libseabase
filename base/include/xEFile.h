/*
2019-7-31
xjshi
1)���Ӷ��ļ����ļ�·�������Ľӿں���
2)������window��linux
3)��ʱ��֧�ֶ��̰߳�ȫ
*/
#pragma once
#include <string>
#include <vector>

using namespace std;
namespace SEABASE
{
    class xEFile
    {
        //����·��(�����Զ������༶·��)
        //������path ��Ҫ�������ļ���·��
        //����ֵ���ɹ�����true , ʧ�ܷ���false
        static bool MakePath(const string& path);

        //�����ļ�
        //������sourceFile Դ�ļ�
        //      destFle    Ŀ���ļ�����
        //     overwrite   �Ƿ񸲸�
        static bool Copy(const string& sourceFile, const string& destFile, bool overwrite = false);
       
        //�ļ�����·���Ƿ����
        //������filename �ļ�����·����
        //����ֵ�����ڷ���true, ʧ�ܷ���false
        static bool Exists(const string& filename);

        //ɾ��ָ���ļ�
        //������ filename     �ļ���
        //����ֵ�� ɾ���ɹ�����true
        static bool Remove(const string& filename);

        //�ƶ��ļ�����������
        //������ sourceFile  Դ�ļ�
        //       destFile    Ŀ���ļ�
        static bool move(const string& sourceFile, const string& destFile);

        //�Ƿ�ɶ�
        //������  path �ļ�·��
        //����ֵ�� �ɶ�����true, ���򷵻�false
        static bool canRead(const string& path);

        //�Ƿ��д
        //������  path �ļ�·��
        //����ֵ�� ��д����true, ���򷵻�false
        static bool canWrite(const string& path);

        //��ȡ�ļ���С
        //������path  �ļ�·��
        //����ֵ�� ���ش�С��Ϊ0�򲻴���
        static int GetFileSize(const string &path);

        //���������������ļ�
        //������ contidion  �������� ��"c:/windows/*.*"
        //       files     �����������ļ������ϣ�����·��
        //����ֵ��������ڷ����������ļ�������ture,���򷵻�false
        static bool search(const string& condition, vector< string >& files);

    };
}