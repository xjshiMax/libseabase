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

        //复制文件
        //参数：sourceFile 源文件
        //      destFle    目标文件名称
        //     overwrite   是否覆盖
bool xEFile::Copy(const string& sourceFile, const string& destFile, bool overwrite = false)
{
#ifdef WIN32
    if (!canRead(sourceFile))
    {
        //源文件不存在或不可读
        return false;
    }
    if (overwrite && Exists(destFile))
    {
        //目标文件存在
        if (!canWrite(destFile))
        {
            //不可写
            return false;
        }
    }
    //读文件流
    fstream readStream;
    //写文件流
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
        //源文件不存在或不可读
        return false;
    }
    if (overwrite && exists(destFile))
    {
        //目标文件存在
        if (!canWrite(destFile))
        {
            //不可写
            return false;
        }
    }
    //读文件流
    fstream readStream;
    //写文件流
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
        //不存在
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
//仅可移动文件
    return (0 == rename(sourceFile.c_str(), destFile.c_str()));
#endif
}

bool xEFile::canRead(const string& path)
{
    if (!Exists(path))
    {
        //文件不存在
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
        //文件不存在
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

        //获取文件大小
        //参数：path  文件路径
        //返回值： 返回大小，为0则不存在
int xEFile::GetFileSize(const string &path)
{
    if (!Exists(path))
    {
        return 0;
    }
#ifdef
    struct _stat status;
    if (0 == _stat(path.c_str(), &status))
    {
        //获取成功
        return status.st_size;
    }
    else{
        //获取失败
        return 0;
    }
#else

    struct stat status;
    if (0 == stat(path.c_str(), &status))
    {
        //获取成功
        return status.st_size;
    }
    else{
        //获取失败
        return 0;
    }
#endif
}

        //搜索符合条件的文件
        //参数： contidion  搜索条件 如"c:/windows/*.*"
        //       files     符合条件的文件名集合，不带路径
        //返回值：如果存在符合条件的文件，返回ture,否则返回false
bool xEFile::search(const string& condition, vector< string >& files)
{
#ifdef WIN32
    struct _finddata_t file_data;
    intptr_t hFile;
    hFile = _findfirst(condition.c_str(), &file_data);
    if ( -1L == hFile)
    {
        //没有匹配文件
        return false;
    }
    do{
        //遍历所有文件
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

    //最后的‘/’
    const int pos = condition.find_last_of('/')+1;
    //目录
    const string dir = condition.substr(0, pos);
    //文件
    const string file = condition.substr(pos, condition.size());

    //文件类型
    string fileType("");
    //包含“.”
    if(string::npos != file.find('.'))
    {
        fileType = condition.substr(file.find_last_of('.')+1, file.size());
    }
    else
    {
        fileType = file;
    }

    //打开目录
    if((dfd = opendir(dir.c_str())) == NULL)
    {
        return false;
    }
    //轮询目录下的文件
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
                //不带路径的文件名
                files.push_back(fileName);
            }
            else if(string::npos != fileName.find(fileType))
            {
                //不带路径的文件名
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