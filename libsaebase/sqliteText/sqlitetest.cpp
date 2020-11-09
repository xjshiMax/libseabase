// sqlitetest.cpp : �������̨Ӧ�ó������ڵ㡣
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

typedef struct changchunPuTicketFault
{
    char PrintPaperType;        //��ӡ��ʽ 0x01:��ά�빺Ʊ��ʱ��0x02:��Ʊ����ʧ�ܡ�0x03:��ά���ֵ��ʱ ��0x04:�ֽ��ֵ�ɹ�/δȷ��
    char Stationname[8];        //��վ���ƣ�˫�ᣨ2���ߣ�
    char DeviceID[8];           //    �豸ID��02240702���豸��ţ�TVM02��
    char EquipmentNo[8];        //    �豸���
    char FaultTime[20];         //    ����ʱ�䣺2019-07-16 08:00:00
    int  Car_classes;           //    ��Σ�44
    char chMOrderID[32];            //������
    int  BookAmount;            //    ������54.00
    int  PayStatus;             //    ֧��״̬���ɹ� 0x01 /δȷ��  0x02
    int  TransAt;               //    ���׽�6.00
    int  NumOfTickets;          //    ����������9
    int  NumofSuccess;          //�ɹ� 4 ��
    char CardID[128];           //����
    int  NumofFail;             //ʧ�� 5 ��
    int  TotalOfSucessAt;         //    �ɹ������ܽ�24.00
    int  TotalOfFailAt;         //    ʧ�ܽ����ܽ�30.00
    int  Faultmoney;            //    ���Ͻ�30.00
    int  balance;   //    ����ǰ�������
    char jobNumber[6];             //���ţ�
    unsigned char LogicalIDSet[20][30];     //�����ɹ�����
    int realcardSize;           //set���ϴ�С
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
typedef struct
{
	unsigned int ud_length;
	char ud_data[500];
}UDDATA_SJZ, *PUDDATA_SJZ;
struct TransRecordData
{
	int serial;
	char businessDay[8];
	UDDATA_SJZ uddata;
};

void testblobData()
{
	sqlite3* pdb=NULL;
	int iret = sqlite3_open("TVMDB_TRANSDATA.s3db",&pdb);
#if 0 //��������
	TransRecordData data;
	memset(&data,0,sizeof(data));
	data.serial=0x06;
	strncpy(data.businessDay,"20200705",8);
	data.uddata.ud_length=12;
	data.uddata.ud_data[2]=0x09;
	sqlite3_stmt* stat = NULL;
	sqlite3_bind_blob(stat, 1, &data.uddata, sizeof(data.uddata), NULL);
	//sqlite3_bind_blob(stat, 1, ffile, filesize, NULL);
	//sqlite3_step(stat);
	char psql[128]={0};
	sprintf(psql,"insert into SJTTransData (BusinessDay, SerialNo, UDData) values(%s,%d,?)",string(data.businessDay).c_str(),data.serial);
	string sql = "insert into SJTTransData (BusinessDay, SerialNo, UDData) values(?,?,?)";
	sqlite3_prepare(pdb, psql, -1, &stat, 0);  //Ԥ����sql���
	//int result = sqlite3_bind_text(stat,1,string(data.businessDay).c_str(),-1,NULL); 
	//result= sqlite3_bind_int(stat,2,data.serial);
	int result = sqlite3_bind_blob(stat, 1, &data.uddata, sizeof(data.uddata), NULL); //�󶨵������ֶε�ֵ
	sqlite3_step(stat);
		sqlite3_reset(stat);
		sqlite3_finalize(stat);
#else //��ѯ�����
	string sql="select BusinessDay, SerialNo, UDData from SJTTransData where SerialNo = 6";
	sqlite3_stmt* stat = NULL;
	int ret = sqlite3_prepare(pdb, sql.c_str(), sql.size()+1, &stat, 0);
	ret = sqlite3_step(stat);
	int serial = sqlite3_column_int(stat, 1);
	char*pbusiness =(char*) sqlite3_column_text(stat, 0);
	//int blob_size = sqlite3_column_bytes(stat,2)/sizeof(TransRecordData);                  //��ȡ����ĳ���
	UDDATA_SJZ*pdata=(UDDATA_SJZ*)sqlite3_column_blob(stat,2);
	sqlite3_reset(stat);
	sqlite3_finalize(stat);
	


#endif
// 	const void * test = sqlite3_column_blob(stat, 1);
// 	int size = sqlite3_column_bytes(stat, 1);
// 	changchunPuTicketFault
}
int _tmain(int argc, _TCHAR* argv[])
{
	testblobData();
#if 0
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
#endif
	return 0;
}

