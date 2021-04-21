#include "moduleConfig.h"
#include <sstream>
#include <iostream>
int moduleConfig::loadFromDB(string filename)
{
	printf("moduleConfig::loadFromDB\n");
	sqlite3* pdb;
	int iret = sqlite3_open("configdata.s3db",&pdb);
	printf("sqlite3_open ret=%d\n",iret);
	if(iret!=SQLITE_OK)
	{
	   CreateTableA(pdb);
	}
	stringstream cache("");
	cache << "select  username, userid,,lastppid,starttime,duration from data where";
	cache <<"username VARCHAR, userid VARCHAR,lastppid int,  ";
	cache <<"starttime VARCHAR,duration int )";
	//inner_execSQL("begin transaction");
	string sql = cache.str();
	sqlite3_stmt* pStateMent = NULL;
	const char* pzTail = NULL;
	printf("before select\n");
	try
	{
		int ret = sqlite3_prepare(pdb, sql.c_str(), sql.size()+1, &pStateMent, &pzTail);
		//  m_error = sqlite3_errcode(db);
		if(SQLITE_OK != ret)
		{
			//  m_sleLog.printLog("<execSQL> exec SQL:%s failed, result %d!\n", sql.c_str(), ret);
			sqlite3_finalize(pStateMent);
			return false;
		}	
		ret = sqlite3_step(pStateMent);
		// m_error = sqlite3_errcode(db);
		if(SQLITE_DONE == ret)
		{
			sqlite3_finalize(pStateMent);
			//  m_sleLog.printLog("<execSQL> exec SQL:%s OK, result %d!\n", sql.c_str(), ret);
		//	return true;
		}
		else
		{
			// m_sleLog.printLog("<execSQL> exec SQL:%s failed, step %d!\n", sql.c_str(), ret);
			sqlite3_finalize(pStateMent);
			return false;
		}
		while(SQLITE_ROW == ret)  // SQLITE_DONE-->执行成功; SQLITE_ROW-->表示有数据返回
		{
			char username[256];
			char*p = (char *)sqlite3_column_text(pStateMent, 0);
			if(p) memcpy(username, (char *)sqlite3_column_text(pStateMent, 0), strlen((char *)sqlite3_column_text(pStateMent, 0)));
			m_username = username;
			m_userID = sqlite3_column_int(pStateMent, 1);
			m_lastppid = sqlite3_column_int(pStateMent, 2);
			char starttime[32];
			p = (char *)sqlite3_column_text(pStateMent, 3);
			if(p) memcpy(starttime, (char *)sqlite3_column_text(pStateMent, 3), strlen((char *)sqlite3_column_text(pStateMent, 3)));
			m_starttime = starttime;
			m_Duration = sqlite3_column_int(pStateMent, 4);

		}
	}
	catch (...)
	{
		// m_sleLog.printLog("<execSQL> exec SQL:%s failed, catch unknown exception!\n", sql.c_str());
		sqlite3_finalize(pStateMent);

		return false;
	}


		return true;
	return false;
}

int moduleConfig::CreateTableA(sqlite3*db)
{
	stringstream cache("");
	cache << "CREATE TABLE  IF NOT  EXISTS  data ( ";
	cache <<"username VARCHAR, userid VARCHAR,lastppid int,  ";
	cache <<"starttime VARCHAR,duration int )";
	printf("moduleConfig::CreateTableA\n");
	inner_execSQL(db,"begin transaction");
	string sql= cache.str();
	if(!inner_execSQL(db,sql.c_str()));
	{
		printf("failed to create table data\n");
		inner_execSQL(db,"rollback transaction");
		return false;
	}
	inner_execSQL(db,"commit transaction");
	printf("success to create table data\n");
}
int moduleConfig::updateA(sqlite3*db,string username,string userid,int lastppid,string starttime,int duration)
{

}
bool moduleConfig::inner_execSQL(sqlite3*db,const string& sql)
{
	if(sql.length() <= 0)
		return false;

	sqlite3_stmt* pStateMent = NULL;
	const char* pzTail = NULL;
	try
	{
		int ret = sqlite3_prepare(db, sql.c_str(), sql.size()+1, &pStateMent, &pzTail);
		//  m_error = sqlite3_errcode(db);
		if(SQLITE_OK != ret)
		{
			//  m_sleLog.printLog("<execSQL> exec SQL:%s failed, result %d!\n", sql.c_str(), ret);
			sqlite3_finalize(pStateMent);
			return false;
		}	
		ret = sqlite3_step(pStateMent);
		// m_error = sqlite3_errcode(db);
		if(SQLITE_DONE == ret)
		{
			sqlite3_finalize(pStateMent);
			//  m_sleLog.printLog("<execSQL> exec SQL:%s OK, result %d!\n", sql.c_str(), ret);
			return true;
		}
		else
		{
			// m_sleLog.printLog("<execSQL> exec SQL:%s failed, step %d!\n", sql.c_str(), ret);
			sqlite3_finalize(pStateMent);
			return false;
		}
	}
	catch (...)
	{
		// m_sleLog.printLog("<execSQL> exec SQL:%s failed, catch unknown exception!\n", sql.c_str());
		sqlite3_finalize(pStateMent);

		return false;
	}

	return false;
}