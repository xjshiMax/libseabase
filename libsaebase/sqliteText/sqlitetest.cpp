// sqlitetest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "../../base/sqlite3/include/sqlite3.h"
#pragma comment(lib,"../../base/sqlite3/lib/windows/32/sqlit.lib")
using namespace std;
//创建数据库
bool Createdb(sqlite3**pdb)
{
	/*
		如果文件不存在，则创建，存在则打开。 ---pdb为输出参数,sqlite3_open 会给pdb分配内存
		成功返回SQLITE_OK
	*/
	int iret = sqlite3_open("data.db",pdb);
	if(iret==SQLITE_OK)
		return true;
	return false;
}
//关闭数据库
bool CloseDB(sqlite3*pdb)
{
	int iret = sqlite3_close(pdb);
	return true;
}
//创建表
bool CreateTable(sqlite3*pdb,const char*sql,char**errmsg)
{
	int iret = sqlite3_exec(pdb,sql,NULL,NULL,errmsg);
	if(iret==SQLITE_OK)
		return true;
	return false;
}

//插入数据
bool InsertRecord(sqlite3*pdb,const char*sql,char**errmsg)
{
	int iret = sqlite3_exec(pdb,sql,NULL,NULL,errmsg);
		if(iret==SQLITE_OK)
			return true;
	return false;
}

//查询数据 查询需要从回调里得到查询的数据
//貌似式阻塞的，回调完以后，才返回select的iret.
//每条记录进一次回调，如果查询批量数据，则多次进回调。
/*
	pv： 由sqlite3_exec 第四个参数传过来，也就式用户数据
	argc: 表的列数
	argv: 查询结果的指针数组，即一条记录数据组成的数组 sqlite3_column_text() 
	col : 字段名数组。即由所有字段名组成的数组 ，sqlite3_column_name()可以获取
*/
int callback_select(void*pv,int argc,char** argv,char**col)
{
	static int i=1;
	if(i==1)
	{
		for(int j=0;j<argc;j++)
			cout<<col[j]<<"\t"<<"|";
		cout<<endl;;
	}
	for(int j=0;j<argc;j++)
		cout<<argv[j]<<"\t"<<"|";
	cout<<endl;;
	i++;
	return 0;
}
bool SelectRecord(sqlite3*pdb,const char*sql,char**errmsg)
{
	int iret = sqlite3_exec(pdb,sql,&callback_select,"userinfo",errmsg);
		if(iret==SQLITE_OK)
			return true;
	return false;
}

//删除表
bool DeleteTable(sqlite3*pdb,const char*sql,char**errmsg)
{
	int iret = sqlite3_exec(pdb, sql, NULL, NULL, errmsg);
	if(iret==SQLITE_OK)
		return true;
	return false;
}

 //非回调式查询
bool SelectTable(sqlite3*pdb,const char*sql,char**errmsg)
{
	int nrow = 0;
	int ncolumn = 0;
	char ** azResult; //返回结果集
	sqlite3_get_table(pdb , sql , &azResult , &nrow , &ncolumn , errmsg );	//age,sex,17,male,18,female, 结果集为每一行平铺的一维数组
	for(int i=0;i<=nrow;i++)
	{
		for(int j=0;j<ncolumn;j++){
			printf("value:%s ",azResult[i*ncolumn+j]);	    
		}
		printf("\n");
	}
	sqlite3_free_table(azResult);
	return true;
}
//显示改变了多少行
void Showchange(sqlite3*pdb)
{
	int count = sqlite3_changes(pdb);
	printf("[DB Log]: <UPADTE> %d item changes\n", count);
}
int _tmain(int argc, _TCHAR* argv[])
{
	sqlite3* pdb=NULL;
	Createdb(&pdb);
	char*mesg=NULL;
	CreateTable(pdb,"create table student (age int ,sex varchar)",&mesg);
	Showchange(pdb);
	InsertRecord(pdb,"Insert into student (age,sex) values (17,'male')",&mesg);
	Showchange(pdb);
	InsertRecord(pdb,"Insert into student (age,sex) values (18,'female')",&mesg);
	Showchange(pdb);
	SelectRecord(pdb,"select * from student",&mesg);
	Showchange(pdb);
	SelectTable(pdb,"select * from student",&mesg);
	Showchange(pdb);
	DeleteTable(pdb,"drop table student;",&mesg);
	CloseDB(pdb);
	return 0;
}

