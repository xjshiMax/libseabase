//2019-7-31 xjshi
#include "../include/xEFile.h"
using namespace SEABASE;
#include <fstream>
#include <iostream>
#ifdef WIN32

#include <direct.h>
#include <io.h>
#else

#endif
bool xEFile::MakePath(const string& path)
{
#ifdef WIN32
     return (0 == _mkdir(path.c_str()));
#else
     return (0==mkdir(path.c_str(),0777));
#endif
}

        //�����ļ�
        //������sourceFile Դ�ļ�
        //      destFle    Ŀ���ļ�����
        //     overwrite   �Ƿ񸲸�
bool xEFile::Copy(const string& sourceFile, const string& destFile, bool overwrite )
{
#ifdef WIN32
    if (!canRead(sourceFile))
    {
        //Դ�ļ������ڻ򲻿ɶ�
        return false;
    }
    if (overwrite && Exists(destFile))
    {
        //Ŀ���ļ�����
        if (!canWrite(destFile))
        {
            //����д
            return false;
        }
    }
    //���ļ���
    fstream readStream;
    //д�ļ���
    fstream writeStream;
    readStream.open(sourceFile.c_str(), ios_base::in|ios_base::binary);
    writeStream.open(destFile.c_str(), ios_base::out|ios_base::binary);
    char currentChar = 0;
    while (!readStream.eof())
    {
        readStream.get(currentChar);
        if (!readStream.eof())
        {
            writeStream << currentChar;
        }					
    }
    readStream.close();
    writeStream.close();
    return true;
#else 
    if (!canRead(sourceFile))
    {
        //Դ�ļ������ڻ򲻿ɶ�
        return false;
    }
    if (overwrite && exists(destFile))
    {
        //Ŀ���ļ�����
        if (!canWrite(destFile))
        {
            //����д
            return false;
        }
    }
    //���ļ���
    fstream readStream;
    //д�ļ���
    fstream writeStream;
    readStream.open(sourceFile.c_str(), ios_base::in|ios_base::binary);
    writeStream.open(destFile.c_str(), ios_base::out|ios_base::binary);
    char currentChar = 0;
    while (!readStream.eof())
    {
        readStream.get(currentChar);
        if (!readStream.eof())
        {
            writeStream << currentChar;
        }					
    }
    readStream.close();
    writeStream.close();
    return true;
#endif
}
       
bool xEFile::Exists(const string& filename)
{
#ifdef WIN32
            return (0 == _access(filename.c_str(), 0));
#else
            return (0 == access(filename.c_str(), 0));
#endif
}

bool xEFile::Remove(const string& filename)
{
    if (!Exists(filename))
    {
        //������
        return false;
    }
#ifdef WIN32
    return (0 == _unlink(filename.c_str()));
#else
    return (0 == unlink(filename.c_str()));
#endif
}

bool xEFile::move(const string& sourceFile, const string& destFile)
{
#ifdef WIN32
    return (0 == rename(sourceFile.c_str(), destFile.c_str()));
#else
//�����ƶ��ļ�
    return (0 == rename(sourceFile.c_str(), destFile.c_str()));
#endif
}

bool xEFile::canRead(const string& path)
{
    if (!Exists(path))
    {
        //�ļ�������
        return false;
    }
#ifdef WIN32
    if (0 == _access(path.c_str(), 4))
    {
        //read only
        return true;
    }
    if (0 == _access(path.c_str(), 6))
    {
        //read write
        return true;
    }
#else
    if (0 == access(path.c_str(), 4))
    {
        //read only
        return true;
    }
    if (0 == access(path.c_str(), 6))
    {
        //read write
        return true;
    }
#endif
    return false;
}


bool xEFile::canWrite(const string& path)
{
    if (!Exists(path))
    {
        //�ļ�������
        return false;
    }
#ifdef WIN32
    if (0 == _access(path.c_str(), 2))
    {
        //read only
        return true;
    }
    if (0 == _access(path.c_str(), 6))
    {
        //read write
        return true;
    }
#else
    if (0 == access(path.c_str(), 2))
    {
        //read only
        return true;
    }
    if (0 == access(path.c_str(), 6))
    {
        //read write
        return true;
    }
#endif
    return false;
}

        //��ȡ�ļ���С
        //������path  �ļ�·��
        //����ֵ�� ���ش�С��Ϊ0�򲻴���
int xEFile::GetFileSize(const string &path)
{
    if (!Exists(path))
    {
        return 0;
    }
#if 0
#ifdef WIN32
    struct _stat status;
    if (0 == _stat(path.c_str(), &status))
    {
        //��ȡ�ɹ�
        return status.st_size;
    }
    else{
        //��ȡʧ��
        return 0;
    }
#else

    struct stat status;
    if (0 == stat(path.c_str(), &status))
    {
        //��ȡ�ɹ�
        return status.st_size;
    }
    else{
        //��ȡʧ��
        return 0;
    }
#endif

#endif
    return 0;
}

        //���������������ļ�
        //������ contidion  �������� ��"c:/windows/*.*"
        //       files     �����������ļ������ϣ�����·��
        //����ֵ��������ڷ����������ļ�������ture,���򷵻�false
bool xEFile::search(const string& condition, vector< string >& files)
{
#ifdef WIN32
    struct _finddata_t file_data;
    intptr_t hFile;
    hFile = _findfirst(condition.c_str(), &file_data);
    if ( -1L == hFile)
    {
        //û��ƥ���ļ�
        return false;
    }
    do{
        //���������ļ�
        files.push_back(file_data.name);
    }
    while (0 == _findnext(hFile, &file_data));
    _findclose(hFile);
    if (0 != files.size())
    {
        return true;
    }
    else{
        return false;
    }
#else
    struct dirent *dp;
    DIR *dfd = NULL;

    //���ġ�/��
    const int pos = condition.find_last_of('/')+1;
    //Ŀ¼
    const string dir = condition.substr(0, pos);
    //�ļ�
    const string file = condition.substr(pos, condition.size());

    //�ļ�����
    string fileType("");
    //������.��
    if(string::npos != file.find('.'))
    {
        fileType = condition.substr(file.find_last_of('.')+1, file.size());
    }
    else
    {
        fileType = file;
    }

    //��Ŀ¼
    if((dfd = opendir(dir.c_str())) == NULL)
    {
        return false;
    }
    //��ѯĿ¼�µ��ļ�
    for(dp = readdir(dfd); NULL!=dp; dp = readdir(dfd))
    {
        if(dp->d_type == 4 || dp->d_type == 10)// dir/link file
        {
            //		continue;
            string fileName(dp->d_name);
            files.push_back(fileName);
        }
        else if(dp->d_type == 8)//file
        {
            string fileName(dp->d_name);
            if((0 == file.compare("*")) || (0 == file.compare("*.*")))
            {
                //����·�����ļ���
                files.push_back(fileName);
            }
            else if(string::npos != fileName.find(fileType))
            {
                //����·�����ļ���
                files.push_back(fileName);
            }
        }

    }
    closedir(dfd);
    return true;
}
#endif
    return true;
}