// sqlitetest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../../base/sqlite3/include/sqlite3.h"
#pragma comment(lib,"../../base/sqlite3/lib/windows/32/sqlit.lib")
using namespace std;


bool execSQL(sqlite3*db,const string& sql)
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
//查看表是否存在

bool IstableExist(sqlite3*pdb,string tablename)
{
	  std::string strFindTable = "SELECT COUNT(*) FROM '" + tablename + "'";
	  int nrow = 0;
	  int ncolumn = 0;
	  char ** azResult; //返回结果集
	  char*errmsg=NULL;
	  int iret= sqlite3_get_table(pdb , strFindTable.c_str() , &azResult , &nrow , &ncolumn , &errmsg );	//age,sex,17,male,18,female, 结果集为每一行平铺的一维数组
	 if(iret==SQLITE_OK)
		 return true;
	 return false;

}

typedef struct changchunPuTicketFault
{
    char PrintPaperType;        //打印格式 0x01:二维码购票超时。0x02:购票部分失败。0x03:二维码充值超时 。0x04:现金充值成功/未确定
    char Stationname[8];        //车站名称：双丰（2号线）
    char DeviceID[8];           //    设备ID：02240702（设备编号：TVM02）
    char EquipmentNo[8];        //    设备编号
    char FaultTime[20];         //    故障时间：2019-07-16 08:00:00
    int  Car_classes;           //    班次：44
    char chMOrderID[32];            //订单号
    int  BookAmount;            //    订单金额：54.00
    int  PayStatus;             //    支付状态：成功 0x01 /未确定  0x02
    int  TransAt;               //    交易金额：6.00
    int  NumOfTickets;          //    交易数量：9
    int  NumofSuccess;          //成功 4 笔
    char CardID[128];           //卡号
    int  NumofFail;             //失败 5 笔
    int  TotalOfSucessAt;         //    成功交易总金额：24.00
    int  TotalOfFailAt;         //    失败交易总金额：30.00
    int  Faultmoney;            //    故障金额：30.00
    int  balance;   //    交易前卡内余额
    char jobNumber[6];             //工号：
    unsigned char LogicalIDSet[20][30];     //出卡成功数组
    int realcardSize;           //set集合大小
}t_changchunPuTicketFault;

bool CreatePurTicketTable(sqlite3*pdb,const char*sql,char**errmsg)
{
#if 0
    stringstream cache("");
    cache << "CREATE TABLE IF NOT  EXISTS  ChangchunPurchTickFaultData ( ";
    cache << "PRINTPAPERTYPE INT,STATIONNAME VARCHAR,DEVICEID VARCHAR,EQUIPMENTNO VARCHAR, " ;
    cache << "FAULTTIME VARCHAR, CARCLASSES INT,CHMORDERID VARCHAR,BOOKAMOUNT INT, ";
    cache << "PAYSTATUS INT,TRANSAT INT, NUMOFTICKETS INT, NUMMOFSUCCESS INT, ";
    cache << "CARDID VARCHAR,NUMOFFAAIL INT,TOTALOFSUCCESSAT INT,TOTALOFFAILAT INT, ";
    cache << "FAULTMONEY INT,BALAANCE INT,JOBNUMBER VARCHAR,LOGICALIDSET VARCHAR,REALCARDSIZE INT )";
#endif
#if 0
    t_changchunPuTicketFault *Data=new t_changchunPuTicketFault;
    Data->PrintPaperType=0x01;
    memset(Data,0,sizeof(t_changchunPuTicketFault));
    char ptemp[720]={0};
    stringstream  cache("");
    cache << "INSERT INTO ChangchunPurchTickFaultData ( PRINTPAPERTYPE, STATIONNAME, DEVICEID, EQUIPMENTNO, " ;
    cache << "FAULTTIME, CARCLASSES, CHMORDERID, BOOKAMOUNT, ";
    cache << "PAYSTATUS, TRANSAT, NUMOFTICKETS, NUMMOFSUCCESS, ";
    cache << "CARDID, NUMOFFAAIL, TOTALOFSUCCESSAT, TOTALOFFAILAT, ";
    cache << "FAULTMONEY, BALAANCE, JOBNUMBER, LOGICALIDSET, REALCARDSIZE ) VALUES (";
    cache << Data->PrintPaperType << ", '" << Data->Stationname << "', '" << Data->DeviceID << "', '" << Data->EquipmentNo << "', '" ;
    cache << Data->FaultTime << "', " << Data->Car_classes << ", '" << Data->chMOrderID << "', " << Data->BookAmount << ", " ;
    cache << Data->PayStatus << ", " << Data->TransAt << ", " << Data->NumOfTickets << ", " << Data->NumofSuccess << ", '" ;
    cache << Data->CardID << "', " << Data->NumofFail << ", " << Data->TotalOfSucessAt << ", " << Data->TotalOfFailAt << ", ";
    cache << Data->Faultmoney << ", " << Data->balance << ", '";
    cache << Data->jobNumber << "','" << ptemp << "'," << Data->realcardSize << ")";
#endif

    char*p="INSERT INTO ChangchunPurchTickFaultData ( PRINTPAPERTYPE, STATIONNAME, DEVICEID, EQUIPMENTNO, FAULTTIME, CARCLASSES, CHMORDERID, BOOKAMOUNT, PAYSTATUS, TRANSAT, NUMOFTICKETS, NUMMOFSUCCESS, CARDID, NUMOFFAAIL, TOTALOFSUCCESSAT, TOTALOFFAILAT, FAULTMONEY, BALAANCE, JOBNUMBER, LOGICALIDSET, REALCARDSIZE ) VALUES (1, '', '0821070101', '01', '2019-07-26 12:33:13', 0, '0821007001190726123313000124', 2000, 1, 2000, -460486171, 0, '03104890000001471030', -460486171, 0, 2000, 0, 15810, '','',0)";
    if (!CreateTable(pdb,p,errmsg))
    {
        return false;
    }

    return true;
}
int _tmain(int argc, _TCHAR* argv[])
{
	sqlite3* pdb=NULL;
	Createdb(&pdb);
	char*mesg=NULL;
  //  CreatePurTicketTable(pdb,"",&mesg);


    //char*psql=" SELECT  FAULTTIME, DeviceID FROM ChangchunPurchTickFaultData WHERE  FAULTTIME >= '2019-06-26 00:00:00.000'";
    stringstream cache;
    cache.str("");

    cache << "SELECT PRINTPAPERTYPE, STATIONNAME, DEVICEID, EQUIPMENTNO, " ;
    cache << "FAULTTIME, CARCLASSES, CHMORDERID, BOOKAMOUNT, ";
    cache << "PAYSTATUS, TRANSAT, NUMOFTICKETS, NUMMOFSUCCESS, ";
    cache << "CARDID, NUMOFFAAIL, TOTALOFSUCCESSAT, TOTALOFFAILAT, ";
    cache << "FAULTMONEY, BALAANCE, JOBNUMBER, LOGICALIDSET, REALCARDSIZE  ";
    cache <<"FROM ChangchunPurchTickFaultData WHERE FAULTTIME=\"";
    cache << "2019-07-26 12:33:13";
    cache <<"\"";
    SelectTable(pdb,cache.str().c_str(),&mesg);
	/*IstableExist(pdb,"student");
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
	CloseDB(pdb);*/
	return 0;
}

