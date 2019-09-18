/*
2019-7-31
xjshi
1)增加对文件和文件路径操作的接口函数
2)适用于window和linux
3)暂时不支持多线程安全
*/
#pragma once
#include <string>
#include <vector>

using namespace std;
namespace SEABASE
{
    class xEFile
    {
    public:
        //创建路径(不可自动创建多级路径)
        //参数：path 需要创建的文件夹路径
        //返回值：成功返回true , 失败返回false
        static bool MakePath(const string& path);

        //复制文件
        //参数：sourceFile 源文件
        //      destFle    目标文件名称
        //     overwrite   是否覆盖
        static bool Copy(const string& sourceFile, const string& destFile, bool overwrite = false);
       
        //文件或者路径是否存在
        //参数：filename 文件名或路径名
        //返回值：存在返回true, 失败返回false
        static bool Exists(const string& filename);

        //删除指定文件
        //参数： filename     文件名
        //返回值： 删除成功返回true
        static bool Remove(const string& filename);

        //移动文件（重命名）
        //参数： sourceFile  源文件
        //       destFile    目标文件
        static bool move(const string& sourceFile, const string& destFile);

        //是否可读
        //参数：  path 文件路径
        //返回值： 可读返回true, 否则返回false
        static bool canRead(const string& path);

        //是否可写
        //参数：  path 文件路径
        //返回值： 可写返回true, 否则返回false
        static bool canWrite(const string& path);

        //获取文件大小
        //参数：path  文件路径
        //返回值： 返回大小，为0则不存在
        static int GetFileSize(const string &path);

        //搜索符合条件的文件
        //参数： contidion  搜索条件 如"c:/windows/*.*"
        //       files     符合条件的文件名集合，不带路径
        //返回值：如果存在符合条件的文件，返回ture,否则返回false
        static bool search(const string& condition, vector< string >& files);

    };
}