#ifndef __CTtypes_H__
#define __CTtypes_H__

#ifdef WIN32
#if (defined(_MSC_VER) && _MSC_VER >= 1400)
#define MY_SNPRINTF _snprintf_s
#else
#define MY_SNPRINTF _snprintf
#endif
#else
#define MY_SNPRINTF snprintf
#endif // WIN32

#ifdef WIN32
	#define vsnprintf _vsnprintf 
	#define snprintf  _snprintf

//add on 2012.08.10 WinSocket里面默认FD_SETSIZE为64,解决了客户端比较多时,有的客户端socket接收不到数据的问题
//#ifndef FD_SETSIZE
	#define FD_SETSIZE  (256)
//#endif

#ifdef __WINSOCK2__
	#include <winsock2.h>
#else
	#include <winsock.h>
#endif
	#include <windows.h>
	#include <cstring>
	#include <ctime>
#else
	#include <unistd.h>
	typedef int SOCKET;

	#include <sys/time.h>
	#include <string.h>
	#if     !defined(__linux__) && !defined( hpux )
		#include <sys/systeminfo.h>
	#endif
	#include <sys/param.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>

#endif

#include <time.h>
#include <string>
#include <vector>

//define the short name types
typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned int 		uint;
typedef unsigned long       ulong;

//define the CT types
typedef unsigned char       CTbyte;
typedef short  int          CTshort;
typedef unsigned short int  CTushort;
typedef float               CTfloat;

#ifdef IA64
typedef signed int              CTint;
typedef unsigned int            CTuint;
typedef unsigned int            CTstatus;
typedef unsigned int            CTerror;
typedef unsigned int            CTsymbol;
typedef unsigned int            CTobj;
typedef signed int              CTbool;
typedef unsigned int            CTtime;
#else
typedef signed long         CTint;
typedef unsigned long       CTuint;
typedef unsigned long       CTstatus;
typedef unsigned long       CTerror;
typedef unsigned long 		CTsymbol;
typedef unsigned long       CTobj;
typedef signed long 		CTbool;
typedef time_t              CTtime;
#endif

typedef std::string					CTstring;
typedef std::vector<CTbyte>			CTbyteArray;
typedef std::vector<CTshort>		CTshortArray;
typedef std::vector<CTushort>		CTushortArray;
typedef std::vector<CTint>			CTintArray;
typedef std::vector<CTuint>			CTuintArray;
typedef std::vector<CTbool>			CTboolArray;
typedef std::vector<CTfloat>		CTfloatArray;
typedef std::vector<CTstring>		CTstringArray;



#define CT_boolTRUE         1
#define CT_boolFALSE        0

#ifdef _WORKSHOP5
#define true	1
#define false	0
#endif


// KV Set value type definitions
#define VALTYP_SCALAR_BASE        10
#define VALTYP_NONSCALAR_BASE     40
#define VALTYP_ARRAY_BASE         60

#define CTkvs_valtypNULL         VALTYP_SCALAR_BASE + 0
#define CTkvs_valtypBYTE         VALTYP_SCALAR_BASE + 1
#define CTkvs_valtypSHORT        VALTYP_SCALAR_BASE + 2
#define CTkvs_valtypINT          VALTYP_SCALAR_BASE + 3
#define CTkvs_valtypUINT         VALTYP_SCALAR_BASE + 4
#define CTkvs_valtypBOOL         VALTYP_SCALAR_BASE + 5
#define CTkvs_valtypFLOAT        VALTYP_SCALAR_BASE + 6
#define CTkvs_valtypERROR        VALTYP_SCALAR_BASE + 7
#define CTkvs_valtypSTATUS       VALTYP_SCALAR_BASE + 8
#define CTkvs_valtypSYMBOL       VALTYP_SCALAR_BASE + 9
#define CTkvs_valtypTIME         VALTYP_SCALAR_BASE + 10
#define CTkvs_valtypUSHORT       VALTYP_SCALAR_BASE + 11 // Walker,1998-06-02

#define CTkvs_valtypIRANGE       VALTYP_NONSCALAR_BASE + 0
#define CTkvs_valtypFRANGE       VALTYP_NONSCALAR_BASE + 1
#define CTkvs_valtypSTRING       VALTYP_NONSCALAR_BASE + 2

#define CTkvs_valtypNULLARRAY       VALTYP_ARRAY_BASE + 0
#define CTkvs_valtypBYTEARRAY       VALTYP_ARRAY_BASE + 1
#define CTkvs_valtypSHORTARRAY      VALTYP_ARRAY_BASE + 2
#define CTkvs_valtypINTARRAY        VALTYP_ARRAY_BASE + 3
#define CTkvs_valtypUINTARRAY       VALTYP_ARRAY_BASE + 4
#define CTkvs_valtypBOOLARRAY       VALTYP_ARRAY_BASE + 5
#define CTkvs_valtypSYMBOLARRAY     VALTYP_ARRAY_BASE + 6
#define CTkvs_valtypFLOATARRAY      VALTYP_ARRAY_BASE + 7
#define CTkvs_valtypSTRINGARRAY     VALTYP_ARRAY_BASE + 8
#define CTkvs_valtypARRAYARRAY      VALTYP_ARRAY_BASE + 9
#define CTkvs_valtypERRORARRAY      VALTYP_ARRAY_BASE + 10
#define CTkvs_valtypSTATUSARRAY     VALTYP_ARRAY_BASE + 11
#define CTkvs_valtypFRANGEARRAY     VALTYP_ARRAY_BASE + 12
#define CTkvs_valtypIRANGEARRAY     VALTYP_ARRAY_BASE + 13
#define CTkvs_valtypUSHORTARRAY     VALTYP_ARRAY_BASE + 14

//告警级别
const int ALARM_Notify   = 0;						//通知
const int ALARM_Common   = 1;						//一般告警
const int ALARM_Urgency	 = 2;						//紧急告警
const int ALARM_Severity = 3;						//严重告警

typedef enum { CT_modeSYNC, CT_modeASYNC } CTmode;

typedef enum {
	RSC_NULL        = 0,
	RSC_PLAYER      = 0x1,
	RSC_RECORDER    = 0x2,
	RSC_SD          = 0x4,
	RSC_SG          = 0x8,
	RSC_CCR         = 0x10,
	RSC_SENDFAX     = 0x20,
	RSC_RECFAX      = 0x40,
	RSC_MSI         = 0x80
} CTresourceType ;

typedef enum {
	GRP_IDLE=0,
	GRP_PLAY_PROMPT,
	GRP_PLAY_CONT,
	GRP_REC,
	GRP_SD,
	GRP_SG,
	GRP_SENDFAX,
	GRP_RECVFAX
} CTgrpStatus ;

typedef enum {
	RSC_PRIMARY,
	RSC_SECONDARY
} CTresourceStatus ;

typedef enum 
{
	SPC_Net,
	SPC_Voice
} TSPCType  ;

typedef enum 
{
	KPI_Cycle_Minute = 0,
	KPI_Cycle_Hour,
	KPI_Cycle_Day
} TKpiCycleType; 

const std::string constStrKpiFilePath = "../kpi/";
const std::string constStrKpiXdrType = "kpi";

#define connectModeSingle     0
#define connectModeDouble     1
#define disconnectModeSingle  0
#define disconnectModeDouble  1

// Integer Range
typedef struct {
   CTint         lower;
   CTint         upper;
} CTirange ;

// Floating point range
typedef struct {
   CTfloat        lower;         
   CTfloat        upper;
} CTfrange ;

typedef struct {
   CTuint         lower;
   CTuint         upper;
} CTurange ;
/*
typedef struct {
   CTuint mailboxKey ;
   CTint voxOffset ;
   CTint voxLength ;
   CTint voxIndex ;
} CTMailBoxInfo ;

typedef struct {
   char   caller[18];
   char   called[21];
   char   notifyType;
   int    notifyCount;
   long   notifyInterval;
} CTScheduleInfo ;
*/
#define _delete(p) {delete p; p=0;}


#define BROADCASTADDRESS      "255.255.255.255"
#ifndef INADDR_NONE
#define INADDR_NONE             0xffffffff
#endif
class CTsockaddr
{
public:
	CTsockaddr() 
	{
		memset( &addr, 0, sizeof(sockaddr_in) ) ;
		addr.sin_family = AF_INET ;
	}
	~CTsockaddr( ) {}

	CTsockaddr( const char * address, int port ) 
	{
		memset( &addr, 0, sizeof(sockaddr_in) ) ;
		addr.sin_family = AF_INET  ;
		if( address )
		{
			addr.sin_port	= htons((u_short)port) ;
			addr.sin_addr.s_addr = inet_addr((char*)address) ;
			if (addr.sin_addr.s_addr==INADDR_NONE&&
				strcmp(address,BROADCASTADDRESS))
				addr.sin_addr.s_addr=0;
			ipAddr=address;
		}
	}
	CTsockaddr( const CTstring address, int port)
	{
		memset( &addr, 0, sizeof(sockaddr_in) ) ;
		addr.sin_family = AF_INET  ;
		addr.sin_port	= htons((u_short)port) ;
		addr.sin_addr.s_addr = inet_addr((char*)address.c_str()) ;
		if (addr.sin_addr.s_addr==INADDR_NONE&&
			address!=BROADCASTADDRESS)
			addr.sin_addr.s_addr=0;
		ipAddr=address;
	}
	CTsockaddr( const sockaddr_in& saddr) 
	{
		memmove( &addr, &saddr, sizeof(sockaddr_in) ) ;
		addr.sin_family	= AF_INET ;
		ipAddr=inet_ntoa(addr.sin_addr);
	}
	CTsockaddr( const CTsockaddr &p ) 
	{
		*this=p;
	}
	CTsockaddr& operator = ( const CTsockaddr & p) 
	{
		if (this!=&p)
		{		
			memmove( &addr, &p.addr, sizeof(sockaddr_in) ) ;
			addr.sin_family = AF_INET ;
			ipAddr=p.ipAddr;
		}
		return * this ;
	}
	bool operator == ( const CTsockaddr & p) const 
	{
		if( addr.sin_addr.s_addr == p.addr.sin_addr.s_addr &&
			addr.sin_port == p.addr.sin_port )
			return true;
		return false;
	}
	bool operator != ( const CTsockaddr & p) const 
	{
		if( addr.sin_addr.s_addr == p.addr.sin_addr.s_addr &&
			addr.sin_port == p.addr.sin_port )
			return false;
		return true;
	}

	const char *getIPAddress()  const { return ipAddr.c_str(); }
	int		getPort() const { return ntohs(addr.sin_port); }

	static bool IsValidIPAddr(const char* ipAddr)
	{
		if (strcmp(ipAddr,BROADCASTADDRESS)==0)
			return true;
		unsigned long nRet=inet_addr(ipAddr);
		return (nRet>0&&nRet!=INADDR_NONE);
	}
	static bool IsValidIPAddr(const CTstring& ipAddr)
	{
		return IsValidIPAddr(ipAddr.c_str());
	}
public:
	CTstring ipAddr;
	sockaddr_in addr ;
} ;

class CTAlarmEvent
{
	CTint   RecordNumber; //记录序号
	CTint   Type;		//事件类型
	CTint   EventID;	//标识符
	CTint   Srouce;	//来源
	CTtime  TimeGenerated; //产生时间
	CTstring User; //用户名
	CTstring Desciption; //相关描述信息
};



class CTDBIdentifier
{
public:
	CTDBIdentifier()
		:m_dbType(1)
	{
	}
	CTDBIdentifier& operator=(const CTDBIdentifier& rhs)
	{
		if (this!=&rhs)
		{
			m_SourceName=rhs.m_SourceName;
			m_Charset=rhs.m_Charset;
			m_DB_Server=rhs.m_DB_Server;
			m_DB_User=rhs.m_DB_User;
			m_DB_Password=rhs.m_DB_Password;
			m_DB_Database=rhs.m_DB_Database;
			m_dbType=rhs.m_dbType;
		}
		return *this;
	}
	CTDBIdentifier(const CTDBIdentifier& rhs)
	{
		*this=rhs;
	}
	CTstring		m_SourceName;
	CTstring		m_Charset;
	
	CTstring		m_DB_Server;
	CTstring		m_DB_User;
	CTstring		m_DB_Password;
	CTstring		m_DB_Database;

	CTuint			m_dbType;//0,SQLSERVER;1,SYBASE;2,ORACLE;3,DB2
};

#define MAXSQLLENGTH 1024 //ywb.为了统一sql语句长度	

typedef CTsockaddr 		PEER; //zsw.仅仅是为了兼容


struct TAlarmType
{
public:
	TAlarmType():m_uNmsAlarmType(0), m_uSuntekAlarmType(0){};
	TAlarmType(const CTuint uNmsAlarmType, const CTuint uSuntekAlarmTypem, const CTstring& strAlarmTitle)
		:m_uNmsAlarmType(uNmsAlarmType), m_uSuntekAlarmType(uSuntekAlarmTypem), m_strAlarmTitle(strAlarmTitle){};
	~TAlarmType(){};

	CTuint m_uNmsAlarmType;
	CTuint m_uSuntekAlarmType;
	CTstring m_strAlarmTitle;
};

#endif

