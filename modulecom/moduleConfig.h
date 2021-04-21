/*
配置文件
1)支持从sqlite数据库读取配置项
2)支持对用户数据的插入,查询,
*/
#include<stdio.h>
#include <string>
#include<string.h>
#include "base/sqlite3/include/sqlite3.h"
using namespace std;
class moduleConfig
{
public:
	int loadFromDB(string filename);

	//用户属性类
public:
	int CreateTableA(sqlite3*db);//创建默认配置项表
	int updateA(sqlite3*db,string username,string userid,int lastppid,string starttime,int duration);
private:
	bool inner_execSQL(sqlite3*db,const string& sql);
public:
	string m_username;
	int m_userID;
	int m_lastppid;  //上次运行进程号
	string m_starttime;  //YYYY-MM-DD hh:mm:ss
	int m_Duration;		//运行时长

};