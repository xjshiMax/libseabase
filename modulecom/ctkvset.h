#ifndef __CTkvset_H__
#define __CTkvset_H__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#ifdef WIN32
#include <windows.h>
#pragma warning ( disable:4786) //once :
#endif

#include "ctsymbol.h"
#include "ctgor.h"
#include "ctutil.h"
#include "cttypes.h"
#include "base/include/xEmutex.h"
using namespace SEABASE;

#define    constMINDATABUFFSZIE   1024

const CTuint  constTHISVERSION  =  0x0300 ;
const CTuint   COMMAINVERSION_V1 = 0x0100;
const CTuint   COMMAINVERSION_V2 = 0x0200;

const CTbyte KVSET_START = 0xff ;
const int  constKVPAIRHEADSIZE = sizeof(CTsymbol)+sizeof(CTuint)+sizeof(CTuint);
// | | |:12bytes
const int  constKVSETHEADSIZE = sizeof(CTbyte)+sizeof(CTushort)+sizeof(CTbyte);
//| | |:4bytes
const int  constTRANINFOHEADSIZE = sizeof(CTint)+sizeof(CTint) + sizeof(CTint)+sizeof(CTobj)+sizeof(CTobj)+sizeof(CTsymbol)+sizeof(CTuint)+sizeof(CTstatus)+sizeof(CTuint)+sizeof(CTerror) ;
//| | | | | | | | | | | |:40bytes
//  const int  constTRANINFOHEADSIZE = sizeof(CTint)+sizeof(CTobj)+sizeof(CTobj)+sizeof(CTsymbol)+sizeof(CTuint)+sizeof(CTstatus)+sizeof(CTuint)+sizeof(CTerror) ;
//| | | | | | | | | |:32bytes
const int  constMAXPAIRNUM = 128;

const int SIZEOFCTBYTE=1;
const int SIZEOFCTSHORT=2;
const int SIZEOFCTINT=4;
const int SIZEOFCTFLOAT=4;
const int SIZEOFCTBOOL=4;
const int SIZEOFCTTIME=4;
const int SIZEOFPOINT=4;  //在64位下注意使用，容易出现问题 by djh 20110709

void    CTshort2CTbyte( CTshort number, char *szString );
CTshort CTbyte2CTshort( const char *szString, CTshort *number );
void    CTushort2CTbyte( CTushort number, char *szString );
CTushort CTbyte2CTushort( const char *szString, CTushort *number );
void    CTuint2CTbyte( CTuint number, char *szString );
CTuint  CTbyte2CTuint(  const char *szString, CTuint *number );
void    CTfloat2CTbyte( CTfloat Number, char *szString ) ;
CTfloat CTbyte2CTfloat( const char *szString, CTfloat *number ) ; 

///////////////////////////////////////////
//
// KVSet :
// KVPair -> KVPair -> KVPair ... -> KVPair
//
// KVPair :
// < Key , Value >
//
///////////////////////////////////////////

class TKVPair
{
public:
    CTbyte	  type;
    CTushort  size;
	CTuint    pointer;
    CTuint    key;
	CTuint    count;
} ;

class TKVSet
{
public :
	TKVSet() ;
	TKVSet(const TKVSet &kvset );
	~TKVSet() {	if(DataBuff) delete[] DataBuff; }

	const TKVSet& operator = ( const TKVSet &kvset ) ;

	void Clear();
	CTerror PutByte( CTuint key, CTbyte cValue ) ;
	CTerror PutShort( CTuint key, CTshort cValue );
	CTerror PutUShort( CTuint key, CTushort cValue );
	CTerror PutInt( CTuint key, CTint iValue ) ;
	CTerror PutUInt( CTuint key, CTuint uiValue ) ;
	CTerror PutFloat( CTuint key, CTfloat fValue ) ;
	CTerror PutBool( CTuint key, CTbool bValue ) ;
	CTerror PutTime( CTuint key, CTtime tValue ) ;

	CTerror PutString( CTuint Key, const char *szString );
	CTerror PutString( CTsymbol key, const std::string &str);

	CTerror PutKVSet( CTuint key, TKVSet &kvset );

	CTerror PutByteArray( CTuint key, CTbyte aByte[], CTuint  uiElements );
	CTerror PutShortArray( CTuint key, CTshort aShort[], CTuint  uiElements );
	CTerror PutUShortArray( CTuint key, CTushort aUShort[], CTuint  uiElements );
	CTerror PutIntArray( CTuint key, CTint aInt[], CTuint  uiElements  ) ;
	CTerror PutIntArray( CTuint key, CTintArray& aIntArray) ;  //add on 2011.12.26
	CTerror PutUIntArray( CTuint key, CTuint aUInt[], CTuint  uiElements ) ;
	CTerror PutUIntArray( CTuint key, CTuintArray& aUIntArray) ;
	CTerror PutFloatArray( CTuint key, CTfloat aFloat[], CTuint  uiElements  ) ;
	CTerror PutFloatArray( CTuint key, CTfloatArray& aFloatArray ) ; //add on 2011.12.26
	CTerror PutBoolArray( CTuint key, CTbool aBool[], CTuint  uiElements  ) ;

	CTerror PutStringArray( CTuint key, const char * const szString[], CTuint eiElements );
	CTerror PutStringArray( CTuint key, const CTstring * szString, CTuint eiElements );
	CTerror PutStringArray( CTuint key, const std::vector<std::string> &strArray);

	CTerror GetByte( CTuint Key, CTbyte *ByteValue );
	CTerror GetShort( CTuint Key, CTshort *shortValue );
	CTerror GetUShort( CTuint Key, CTushort *shortValue );
	CTerror GetInt( CTuint Key, CTint *pInt ) ;
	CTerror GetUInt( CTuint Key, CTuint *pUInt ) ;
	CTerror GetBool( CTuint Key, CTbool *pBool ) ;
	CTerror GetFloat( CTuint Key, CTfloat *pFloat ) ;
	CTerror GetTime( CTuint Key, CTtime *pTime ) ;
	CTerror GetKVSet( CTuint Key, TKVSet &kvset );

	CTerror GetString( CTuint Key, char **pString );
	CTerror GetString( CTuint Key, CTstring &str);

	CTerror GetByteArray( CTuint Key, CTbyteArray& uintElements) ;
	CTerror GetShortArray( CTuint Key, CTshortArray& uintElements) ;
	CTerror GetUShortArray( CTuint Key, CTushortArray& uintElements) ;

#ifndef SOLARIS
	CTerror GetUShortArray( CTuint Key, CTushort **pUShort, CTuint *puiElements );
	CTerror GetByteArray( CTuint Key, CTbyte **pByte, CTuint *puiElements );
	CTerror GetShortArray( CTuint Key, CTshort **pShort, CTuint *puiElements );
	CTerror GetIntArray( CTuint Key, CTint **pInt, CTuint *puiElements ) ;
	CTerror GetUIntArray( CTuint Key, CTuint **pUInt, CTuint *puiElements ) ;
	CTerror GetBoolArray( CTuint Key, CTbool **pBool, CTuint *puiElements ) ;
	CTerror GetFloatArray( CTuint Key, CTfloat **pFloat, CTuint *puiElements ) ;
#endif

	CTerror GetIntArray( CTuint Key, CTintArray& uintElements) ;
	CTerror GetUIntArray( CTuint Key, CTuintArray& uintElements) ;
	CTerror GetFloatArray( CTuint Key, CTfloatArray& floatElements) ; //add on 2011.12.26
#ifndef IA64
	CTerror GetStringArray( CTuint Key, char **pString[], CTuint *puiElement );    //这个函数在64位系统下有问题，这里封闭掉，请用CTstringArray接口的函数 by djh 20110709
#endif
	CTerror GetStringArray( CTuint Key, CTstringArray& strings);

	int     KVSet2String( char *szString, CTuint maxlen );
	CTerror String2KVSet( const char *szString, CTuint maxlen );
	int     GetLength() { return DataLength+constKVSETHEADSIZE+PairCount*constKVPAIRHEADSIZE ; };

	int     GetDataLength() const  {return DataLength;}
	int     GetPairCount()  const { return PairCount;}

	char *  GetData() const { return DataBuff; };
	TKVPair *GetPair() const { return (TKVPair *)PairArray; }
	CTerror Remove( CTuint Key );
	CTstring getInfo(bool withValue = false);

private :
	CTuint    MaxBuffLength;
	CTuint	  DataLength;
	int 	  PairCount;
	char*	  DataBuff;
	TKVPair   PairArray[constMAXPAIRNUM];

	CTerror AddPair( CTuint toKey, CTuint toType, CTuint toSize, void *toValue,CTuint eiElements );
	CTerror AddPair( CTsymbol key, const char * const szString[], CTuint eiElements );
	CTerror AddPair( CTsymbol tokey, const std::string* szString, CTuint eiElements );
	
	TKVPair* GetKVPair( CTuint key);
	CTerror	CheckDataBuff(CTuint toSize);
	template<typename T> 
	CTerror GetKeyValue(CTuint Key,CTuint Type,T *Value)
	{
		TKVPair *pair=GetKVPair(Key);
		if( pair == NULL )
			return CT_errorKeyNotFound ;

		if( pair->type != Type )
			return CT_errorBadKey ;

		*Value = *((T *)( DataBuff + pair->pointer )) ;
		return CT_errorOK ;
	}
};

//////////////////////////////////////
class CTtranInfo
{
public:
	CTint                   version ;
	CTuint				    commSender;
	CTuint					commReceiver;
	CTobj                   sender ;
	CTobj                   receiver ;
	CTsymbol                messageID ;
	CTuint                  tranID ;
	CTstatus                status ;
	CTuint                  qualifier ;
	CTerror                 errorData ;
	TKVSet                  messageData ;

	CTsockaddr				sourAddress;
	CTtime					timeStamp;

	CTstring				senderURI;
	CTstring				receiverURI;
	CTbool                  immidiate;
public:
	CTtranInfo();

	CTtranInfo(CTobj snd, CTobj rcv, CTsymbol msgid,
		TKVSet *kvset=NULL, CTerror err=CT_errorOK, CTstatus sts=0,
		CTuint tranid=0, CTuint qlfer=0);

	CTtranInfo(const CTtranInfo &tranInfo);
	~CTtranInfo(){	}

	CTtranInfo & operator = ( const CTtranInfo & tranInfo);

	CTint   toString(char *str, CTint maxlen);
	CTerror fromString(const sockaddr_in &from, char *str, CTint len);

	TKVSet& GetMessageData() { return messageData; }
	int		GetLength() { return constTRANINFOHEADSIZE+messageData.GetLength();}

	int		TestCaseTKVSet( int type );

	void PutStableKey();

private:
	static CTtime m_currTimeStamp;
} ;


class CTtranInfoMap
{
#define MAX_TRANINFO_MAPNUM 10240

public:
	CTtranInfoMap()
	{
		m_total = 0 ;
		m_currhandle = 0 ;
		//先为所有的CTMOUDLE创建一个CTtranInfo，用于CTMODULE取收到的消息。
		int i=0;
		for (i=0; i<constMAXMODULENUM && i <MAX_TRANINFO_MAPNUM; i++ ) 
		{	
			m_tranInfos[i] = new CTtranInfo();
			m_total ++ ;
			m_currhandle ++ ;
		}

		for (i=m_currhandle; i<MAX_TRANINFO_MAPNUM; i++ )
			m_tranInfos[i] = NULL;

	}

	~CTtranInfoMap()
	{
		for( int i=0; i<MAX_TRANINFO_MAPNUM; i++)
			if( m_tranInfos[i] )
				delete m_tranInfos[i] ;
	}

	int createInstance()
	{
		int handle=-1 ;
		CTbool found=CT_boolFALSE;
		xEAutoLock smartlock(&m_lock);

		for( handle=m_currhandle; handle<MAX_TRANINFO_MAPNUM; handle++ )
		{
			if( !m_tranInfos[handle]  )
			{
				found = CT_boolTRUE;
				break;
			}
		}

		if( found == CT_boolFALSE )
		{
			for( handle=0; handle<m_currhandle; handle++ )
			{
				if( !m_tranInfos[handle] )
				{
					found = CT_boolTRUE ;
					break;
				}
			}
		}

		if( found == CT_boolFALSE )
			return -1 ;

		m_tranInfos[handle] = new CTtranInfo();
		m_total ++;
		m_currhandle = (handle+1) % MAX_TRANINFO_MAPNUM ;

		return handle;
	}

	int destroyInstance(int handle)
	{
		int ret=-1;
		xEAutoLock smartlock(&m_lock);

		if( handle >= constMAXMODULENUM && handle < MAX_TRANINFO_MAPNUM )
		{
			if( m_tranInfos[handle] )
			{
				delete m_tranInfos[handle]; 
				m_tranInfos[handle] = NULL;
				m_total -- ;
				m_currhandle = handle;
				ret= handle;
			}
		}

		return ret;
	}


	int cloneInstance( int chandle)
	{
		int handle=-1 ;
		CTbool found=CT_boolFALSE;
		xEAutoLock smartlock(&m_lock);

		if( chandle<0 || chandle >= MAX_TRANINFO_MAPNUM || !m_tranInfos[chandle] )
			return -1;

		for( handle=m_currhandle; handle<MAX_TRANINFO_MAPNUM; handle++ )
		{
			if( !m_tranInfos[handle]  )
			{
				found = CT_boolTRUE;
				break;
			}
		}

		if( found == CT_boolFALSE )
		{
			for( handle=0; handle<m_currhandle; handle++ )
			{
				if( !m_tranInfos[handle] )
				{
					found = CT_boolTRUE ;
					break;
				}
			}
		}

		if( found == CT_boolFALSE )
			return -1 ;

		m_tranInfos[handle] = new CTtranInfo( *m_tranInfos[chandle] );
		m_total ++;
		m_currhandle = (handle+1) % MAX_TRANINFO_MAPNUM ;

		return handle;
	}


	CTtranInfo *getInstance( int handle )
	{
		xEAutoLock smartlock(&m_lock);

		if( handle >= 0 && handle < MAX_TRANINFO_MAPNUM )
			return m_tranInfos[handle];

		return NULL;
	}

private:
	CTtranInfo *m_tranInfos[MAX_TRANINFO_MAPNUM] ;
	xEmutex m_lock;
	int		m_total;
	int		m_currhandle;
private:
	CTtranInfoMap(const CTtranInfoMap& rhs);
	CTtranInfoMap& operator=(const CTtranInfoMap& rhs);
};

#endif
