/*
�����ļ�
1)֧�ִ�sqlite���ݿ��ȡ������
2)֧�ֶ��û����ݵĲ���,��ѯ,
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

	//�û�������
public:
	int CreateTableA(sqlite3*db);//����Ĭ���������
	int updateA(sqlite3*db,string username,string userid,int lastppid,string starttime,int duration);
private:
	bool inner_execSQL(sqlite3*db,const string& sql);
public:
	string m_username;
	int m_userID;
	int m_lastppid;  //�ϴ����н��̺�
	string m_starttime;  //YYYY-MM-DD hh:mm:ss
	int m_Duration;		//����ʱ��

};