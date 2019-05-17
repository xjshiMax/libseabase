// sqlitetest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "../../base/sqlite3/include/sqlite3.h"
#pragma comment(lib,"../../base/sqlite3/lib/windows/32/sqlit.lib")
using namespace std;
//�������ݿ�
bool Createdb(sqlite3**pdb)
{
	/*
		����ļ������ڣ��򴴽���������򿪡� ---pdbΪ�������,sqlite3_open ���pdb�����ڴ�
		�ɹ�����SQLITE_OK
	*/
	int iret = sqlite3_open("data.db",pdb);
	if(iret==SQLITE_OK)
		return true;
	return false;
}
//�ر����ݿ�
bool CloseDB(sqlite3*pdb)
{
	int iret = sqlite3_close(pdb);
	return true;
}
//������
bool CreateTable(sqlite3*pdb,const char*sql,char**errmsg)
{
	int iret = sqlite3_exec(pdb,sql,NULL,NULL,errmsg);
	if(iret==SQLITE_OK)
		return true;
	return false;
}

//��������
bool InsertRecord(sqlite3*pdb,const char*sql,char**errmsg)
{
	int iret = sqlite3_exec(pdb,sql,NULL,NULL,errmsg);
		if(iret==SQLITE_OK)
			return true;
	return false;
}

//��ѯ���� ��ѯ��Ҫ�ӻص���õ���ѯ������
//ò��ʽ�����ģ��ص����Ժ󣬲ŷ���select��iret.
//ÿ����¼��һ�λص��������ѯ�������ݣ����ν��ص���
/*
	pv�� ��sqlite3_exec ���ĸ�������������Ҳ��ʽ�û�����
	argc: �������
	argv: ��ѯ�����ָ�����飬��һ����¼������ɵ����� sqlite3_column_text() 
	col : �ֶ������顣���������ֶ�����ɵ����� ��sqlite3_column_name()���Ի�ȡ
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

//ɾ����
bool DeleteTable(sqlite3*pdb,const char*sql,char**errmsg)
{
	int iret = sqlite3_exec(pdb, sql, NULL, NULL, errmsg);
	if(iret==SQLITE_OK)
		return true;
	return false;
}

 //�ǻص�ʽ��ѯ
bool SelectTable(sqlite3*pdb,const char*sql,char**errmsg)
{
	int nrow = 0;
	int ncolumn = 0;
	char ** azResult; //���ؽ����
	sqlite3_get_table(pdb , sql , &azResult , &nrow , &ncolumn , errmsg );	//age,sex,17,male,18,female, �����Ϊÿһ��ƽ�̵�һά����
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
//��ʾ�ı��˶�����
void Showchange(sqlite3*pdb)
{
	int count = sqlite3_changes(pdb);
	printf("[DB Log]: <UPADTE> %d item changes\n", count);
}
//�鿴���Ƿ����

bool IstableExist(sqlite3*pdb,string tablename)
{
	  std::string strFindTable = "SELECT COUNT(*) FROM '" + tablename + "'";
	  int nrow = 0;
	  int ncolumn = 0;
	  char ** azResult; //���ؽ����
	  char*errmsg=NULL;
	  int iret= sqlite3_get_table(pdb , strFindTable.c_str() , &azResult , &nrow , &ncolumn , &errmsg );	//age,sex,17,male,18,female, �����Ϊÿһ��ƽ�̵�һά����
	 if(iret==SQLITE_OK)
		 return true;
	 return false;

}
int _tmain(int argc, _TCHAR* argv[])
{
	sqlite3* pdb=NULL;
	Createdb(&pdb);
	char*mesg=NULL;
	IstableExist(pdb,"student");
	CreateTable(pdb,"create table student (age int ,sex varchar)",&mesg);

	IstableExist(pdb,"student")	 ;
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

