#include "ctkvset.h"
#include <sstream>
//////////////////////////////////////////////////////////////////////////
// 2011/08/18 dcj say:
//  (1) 优化 CTerror TKVSet::Remove( CTuint Key)的实现
//      memcpy 移出循环外，做一次就足够,没有必要做多次
//////////////////////////////////////////////////////////////////////////
CTtime CTtranInfo::m_currTimeStamp = 0;

void  CTshort2CTbyte( CTshort Number, char *szString )
{
	if( !szString ) 
		return ;

	union 
	{
		CTshort value ;
		char    str[2] ;
	}val;
	val.value = Number ;

#ifdef __i386
	szString[0] = val.str[1] ;
	szString[1] = val.str[0] ;
#else
	szString[0] = val.str[0] ;
	szString[1] = val.str[1] ;
#endif

}

CTshort  CTbyte2CTshort(  const char *szString, CTshort *number )
{
	if( !szString ) 
		return 0 ;

	union 
	{
		CTshort value ;
		char    str[2] ;
	}val;

#ifdef __i386
	val.str[0] = szString[1];
	val.str[1] = szString[0];
#else
	val.str[0] = szString[0];
	val.str[1] = szString[1];
#endif

#ifdef SOLARIS
	if( number ) 
		memcpy(number, &(val.value), sizeof(CTshort));
#else
	if( number ) 
		*number = val.value ;
#endif

	return val.value ;
}

void  CTushort2CTbyte( CTushort Number, char *szString )
{
	if( !szString ) 
		return ;

	union 
	{
		CTushort value ;
		char     str[2] ;
	}val;
	val.value = Number ;

#ifdef __i386
	szString[0] = val.str[1] ;
	szString[1] = val.str[0] ;
#else
	szString[0] = val.str[0] ;
	szString[1] = val.str[1] ;
#endif

}

CTushort  CTbyte2CTushort(  const char *szString, CTushort *number )
{
	if( !szString ) 
		return 0 ;

	union 
	{
		CTushort value ;
		char     str[2] ;
	}val;

#ifdef __i386
	val.str[0] = szString[1];
	val.str[1] = szString[0];
#else
	val.str[0] = szString[0];
	val.str[1] = szString[1];
#endif

#ifdef SOLARIS
	if( number ) 
		memcpy(number, &(val.value), sizeof(CTushort));
#else
	if( number ) 
		*number = val.value ;
#endif

	return val.value ;
}

void  CTuint2CTbyte( CTuint Number, char *szString )
{
	if( !szString ) 
		return ;
	union 
	{
		CTuint   value ;
		char     str[4] ;
	}val;
	val.value = Number ;

#ifdef __i386
	szString[0] = val.str[3] ;
	szString[1] = val.str[2] ;
	szString[2] = val.str[1] ;
	szString[3] = val.str[0] ;
#else
	szString[0] = val.str[0] ;
	szString[1] = val.str[1] ;
	szString[2] = val.str[2] ;
	szString[3] = val.str[3] ;
#endif
}

CTuint  CTbyte2CTuint(  const char *szString, CTuint *number )
{
	if( !szString ) 
		return 0 ;

	
	union 
	{
		CTuint   value ;
		char     str[4] ;
	}val;

#ifdef __i386
	val.str[0] = szString[3];
	val.str[1] = szString[2];
	val.str[2] = szString[1];
	val.str[3] = szString[0];
#else
	val.str[0] = szString[0];
	val.str[1] = szString[1];
	val.str[2] = szString[2];
	val.str[3] = szString[3];
#endif

#ifdef SOLARIS
	if( number ) 
		memcpy(number, &(val.value), sizeof(CTuint));
#else
	if( number ) 
		*number = val.value ;
#endif

	return val.value ;
}

void  CTfloat2CTbyte( CTfloat number, char *szString )
{
	if( !szString ) 
		return ;
	union 
	{
		CTfloat   value ;
		char     str[4] ;
	}val;
	val.value = number;

#ifdef __i386
	szString[0] = val.str[3] ;
	szString[1] = val.str[2] ;
	szString[2] = val.str[1] ;
	szString[3] = val.str[0] ;
#else
	szString[0] = val.str[0] ;
	szString[1] = val.str[1] ;
	szString[2] = val.str[2] ;
	szString[3] = val.str[3] ;
#endif
}

CTfloat  CTbyte2CTfloat( const char *szString, CTfloat *number )
{
	if( !szString ) 
		return 0 ;
	union 
	{
		CTfloat   value ;
		char     str[4] ;
	}val;

#ifdef __i386
	val.str[0] = szString[3];
	val.str[1] = szString[2];
	val.str[2] = szString[1];
	val.str[3] = szString[0];
#else
	val.str[0] = szString[0];
	val.str[1] = szString[1];
	val.str[2] = szString[2];
	val.str[3] = szString[3];
#endif

#ifdef SOLARIS
	if( number )
		memcpy(number, &(val.value), sizeof(CTfloat));
#else
	if( number ) 
		*number = val.value ;
#endif

	return val.value ;
}

TKVSet::TKVSet()
{
	DataLength = 0;
	PairCount = 0;
	MaxBuffLength = constMINDATABUFFSZIE; 
	DataBuff = new char[MaxBuffLength];
	if(!DataBuff)
		MaxBuffLength = 0;
}

TKVSet::TKVSet(const TKVSet& kvset ) 
{
	MaxBuffLength = 0; 
	DataBuff   = NULL;
	*this = kvset ;
}

const TKVSet& TKVSet::operator = ( const TKVSet& kvset )
{
	if (this==&kvset)
		return *this;
	DataLength    = kvset.GetDataLength();
	PairCount = kvset.GetPairCount();
	if( DataLength > MaxBuffLength )
	{
		MaxBuffLength = (DataLength > constMINDATABUFFSZIE ? DataLength:constMINDATABUFFSZIE);
		if(DataBuff)
			delete[] DataBuff;
		DataBuff = new char[MaxBuffLength];
		if(!DataBuff)
		{
			DataLength    = 0;
			PairCount = 0;
			MaxBuffLength= 0;
			return *this;
		}
	}
	memcpy(DataBuff,kvset.GetData(),DataLength);
	memcpy(PairArray,kvset.GetPair(),sizeof(TKVPair)*PairCount);

	return *this ;
}

void TKVSet::Clear( )
{
	DataLength= 0 ;
	PairCount = 0 ;
}

CTerror TKVSet::Remove( CTuint Key)
{
	CTerror ret=CT_errorBadKey;

	for(int i=0;i<PairCount;i++)
	{
		if(PairArray[i].key == Key)
		{
			int pointer  = PairArray[i].pointer;
			int removeLen = PairArray[i].size;
			DataLength -= removeLen;

			int leftLength = 0;

			for(int j=i+1;j<PairCount;j++)
			{
				PairArray[j-1].type    = PairArray[j].type;
				PairArray[j-1].key     = PairArray[j].key;
				PairArray[j-1].size    = PairArray[j].size;
				PairArray[j-1].count   = PairArray[j].count;
				PairArray[j-1].pointer = PairArray[j].pointer - removeLen;

				leftLength += PairArray[j].size;
			}

			if(leftLength > 0)
			{// 这里是可保证不会重叠的，不使用memmove
				memcpy(&DataBuff[pointer],&DataBuff[pointer + removeLen],leftLength);
			}

			PairCount -- ;
			ret = CT_errorOK;
			break;
		}
	}

	return ret;
}

CTerror	TKVSet::CheckDataBuff(CTuint toSize)
{
	if( DataLength + toSize > MaxBuffLength)
	{
		MaxBuffLength = DataLength + toSize + 1024;
		char *p = new char[MaxBuffLength];
		if(!p)
		{
			MaxBuffLength = DataLength;
			return CT_errorBadMemory;
		}
		memcpy(p,DataBuff,DataLength);
		delete[] DataBuff;
		DataBuff = p;
	}
	return CT_errorOK;
}

CTerror TKVSet::AddPair( CTuint toKey, CTuint toType, CTuint toSize, void *toValue,CTuint eiElements)
{
	if( PairCount >= constMAXPAIRNUM  )
		return CT_errorNotSupported;

	if( CheckDataBuff(toSize) != CT_errorOK)
		return CT_errorBadMemory;

	PairArray[PairCount].key  = toKey ;
	PairArray[PairCount].type = (CTbyte)toType ;
	PairArray[PairCount].size = (CTushort)toSize ;
	PairArray[PairCount].count= eiElements;
	PairArray[PairCount].pointer = DataLength;

	if( toSize )
		memcpy(&DataBuff[DataLength],toValue,toSize);

	DataLength += (CTushort)toSize;
	PairCount ++ ;
	return CT_errorOK;
}


CTerror TKVSet::AddPair( CTuint tokey, const char * const szString[], CTuint eiElements )
{
	if( PairCount >= constMAXPAIRNUM  )
		return CT_errorNotSupported;

	CTuint toSize = SIZEOFCTINT + eiElements*SIZEOFPOINT ;
	int szLen;

	for(int i=0; i<(int)eiElements; i++ )
	{
		if( szString[i])
			toSize += strlen(szString[i]) + 1  ;
		else
			toSize += 1 ;
	}

	if( CheckDataBuff(toSize) != CT_errorOK)
		return CT_errorBadMemory;

	PairArray[PairCount].key  = tokey ;
	PairArray[PairCount].type = CTkvs_valtypSTRINGARRAY ;
	PairArray[PairCount].count= eiElements;
	PairArray[PairCount].size= (CTushort)toSize;
	PairArray[PairCount].pointer = DataLength;


	memcpy( DataBuff+DataLength, (void *)(&eiElements), SIZEOFCTINT);

	char *p = &DataBuff[DataLength+SIZEOFCTINT + eiElements * SIZEOFPOINT];
	for(int i=0; i<(int)eiElements; i++ )
	{
		szLen = strlen(szString[i]) + 1;
		memcpy(p,szString[i], szLen);
		p +=szLen;
	}

	DataLength += (CTushort)toSize;
	PairCount ++ ;

	return CT_errorOK ;
}

CTerror TKVSet::AddPair( CTuint tokey, const std::string* szString, CTuint eiElements )
{
	if( PairCount >= constMAXPAIRNUM  )
		return CT_errorNotSupported;

	CTuint toSize = SIZEOFCTINT + eiElements*SIZEOFPOINT ;
	int szLen;

	for(int i=0; i<(int)eiElements; i++ )
	{
		if( !szString  )
			return CT_errorBadKey ;

		toSize += szString[i].length() + 1;
	}

	if( CheckDataBuff(toSize) != CT_errorOK)
		return CT_errorBadMemory;

	PairArray[PairCount].key  = tokey ;
	PairArray[PairCount].type = CTkvs_valtypSTRINGARRAY ;
	PairArray[PairCount].count= eiElements;
	PairArray[PairCount].size= (CTushort)toSize;
	PairArray[PairCount].pointer = DataLength;

	memcpy( DataBuff+DataLength, (void *)(&eiElements), SIZEOFCTINT);

	char *p = &DataBuff[DataLength+SIZEOFCTINT + eiElements * SIZEOFPOINT];
	for(int i=0; i<(int)eiElements; i++ )
	{
		szLen = szString[i].length() + 1;
		memcpy(p,szString[i].c_str(), szLen);
		p +=szLen;
	}
	DataLength += (CTushort)toSize;
	PairCount ++ ;

	return CT_errorOK ;
}


CTerror TKVSet::PutByte( CTuint key, CTbyte bValue )
{
	Remove( key ) ;
	return AddPair( key, CTkvs_valtypBYTE, SIZEOFCTBYTE,&bValue,1);
}

CTerror TKVSet::PutShort( CTuint key, CTshort sValue )
{
	Remove( key ) ;
	return AddPair( key, CTkvs_valtypSHORT, SIZEOFCTSHORT, &sValue,1);
}

CTerror TKVSet::PutUShort( CTuint key, CTushort cValue )
{
	Remove( key ) ;
	return AddPair( key, CTkvs_valtypUSHORT, SIZEOFCTSHORT, &cValue,1);
}

CTerror TKVSet::PutInt( CTuint key, CTint iValue )
{
	Remove( key ) ;
	return AddPair( key, CTkvs_valtypINT, SIZEOFCTINT, &iValue,1);
}

CTerror TKVSet::PutUInt( CTuint key, CTuint uiValue )
{
	Remove( key ) ;
	return AddPair( key, CTkvs_valtypUINT, SIZEOFCTINT, &uiValue,1);
}

CTerror TKVSet::PutFloat( CTuint key, CTfloat fValue )
{
	Remove( key ) ;
	return AddPair( key, CTkvs_valtypFLOAT, SIZEOFCTFLOAT, &fValue,1);
}

CTerror TKVSet::PutBool( CTuint key, CTbool bValue )
{
	Remove( key ) ;
	return AddPair( key, CTkvs_valtypBOOL, SIZEOFCTBOOL, &bValue,1);
}

CTerror TKVSet::PutTime( CTuint key, CTtime tValue )
{
	Remove( key ) ;
	return AddPair( key, CTkvs_valtypTIME, SIZEOFCTTIME, &tValue,1);
}

CTerror TKVSet::PutString( CTuint key, const char *szString )
{
	if( !szString ) 
		return CT_errorBadKey;

	Remove( key ) ;
	CTushort Size = strlen(szString)+1;
	return AddPair( key, CTkvs_valtypSTRING, Size , (void *)szString, 1);
}

CTerror TKVSet::PutString( CTuint key, const std::string &str)
{
	return PutString(key, str.c_str());
}

CTerror TKVSet::PutKVSet( CTuint key, TKVSet &kvset )
{
	CTerror ret=CT_errorBadKey;

	Remove( key ) ;

	int  maxsize = kvset.GetLength()+128;
	char *szString = new char[maxsize];
	if( !szString ) 
		return CT_errorBadMemory;

	CTuint Size = kvset.KVSet2String(szString,maxsize);
	if( Size )
	{
		AddPair( key, CTkvs_valtypBYTEARRAY, Size, (void *)szString, 1);
		ret = CT_errorOK;
	}

	delete[] szString;

	return ret ;
}

CTerror TKVSet::PutByteArray( CTuint key, CTbyte aByte[], CTuint  uiElements )
{
	if( !aByte )
		return CT_errorBadKey ;

	Remove( key ) ;
	return AddPair( key, CTkvs_valtypBYTEARRAY, SIZEOFCTBYTE*uiElements ,(void *)aByte,uiElements );
}

CTerror TKVSet::PutShortArray( CTuint key, CTshort aShort[], CTuint  uiElements )
{
	if( !aShort  )
		return CT_errorBadKey ;

	Remove( key ) ;
	return AddPair( key, CTkvs_valtypSHORTARRAY, SIZEOFCTSHORT*uiElements, (void *)aShort,uiElements);
}

CTerror TKVSet::PutUShortArray( CTuint key, CTushort aUShort[], CTuint  uiElements )
{
	if( !aUShort  )
		return CT_errorBadKey ;
	Remove( key ) ;
	return AddPair( key, CTkvs_valtypUSHORTARRAY, SIZEOFCTSHORT*uiElements, (void *)aUShort,uiElements);
}

CTerror TKVSet::PutIntArray( CTuint key, CTint aInt[], CTuint  uiElements )
{
	if( !aInt  )
		return CT_errorBadKey ;
	Remove( key ) ;
	return AddPair( key, CTkvs_valtypINTARRAY, SIZEOFCTINT*uiElements, (void *)aInt,uiElements);
}

//add on 2011.12.26
CTerror TKVSet::PutIntArray( CTuint key, CTintArray& aIntArray)
{
	if(aIntArray.empty())
	{
		CTint  intArray[1]={0};
		return PutIntArray(key,intArray,aIntArray.size());
	}
	else
		return PutIntArray(key,&(aIntArray[0]),aIntArray.size());
}

CTerror TKVSet::PutUIntArray( CTuint key, CTuint aUInt[], CTuint  uiElements )
{
	if( !aUInt)
		return CT_errorBadKey ;

	Remove( key ) ;
	return AddPair( key, CTkvs_valtypUINTARRAY, SIZEOFCTINT*uiElements, (void *)aUInt,uiElements);
}

CTerror TKVSet::PutUIntArray( CTuint key, CTuintArray& aUIntArray)
{
	if(aUIntArray.empty())
	{
		CTuint uintArray[1]={0};
		return PutUIntArray(key,uintArray,aUIntArray.size());
	}
	else
		return PutUIntArray(key,&(aUIntArray[0]),aUIntArray.size());
}

CTerror TKVSet::PutFloatArray( CTuint key, CTfloat aFloat[], CTuint  uiElements )
{
	if( !aFloat  )
		return CT_errorBadKey ;
	Remove( key ) ;
	return AddPair( key, CTkvs_valtypFLOATARRAY, SIZEOFCTFLOAT*uiElements, (void *)aFloat,uiElements);
}

//add on 2011.12.26
CTerror TKVSet::PutFloatArray( CTuint key, CTfloatArray& aFloatArray )
{
	if(aFloatArray.empty())
	{
		CTfloat floatArray[1]={0};
		return PutFloatArray(key,floatArray,aFloatArray.size());
	}
	else
		return PutFloatArray(key,&(aFloatArray[0]),aFloatArray.size());
}

CTerror TKVSet::PutBoolArray( CTuint key, CTint aBool[], CTuint  uiElements )
{
	if( !aBool  )
		return CT_errorBadKey ;

	Remove( key ) ;
	return AddPair( key, CTkvs_valtypBOOLARRAY, SIZEOFCTBOOL*uiElements, (void *)aBool,uiElements);
}

CTerror TKVSet::PutStringArray( CTuint key, const char * const szString[], CTuint eiElements )
{
	if( !szString ) 
		return CT_errorBadKey;

	Remove( key ) ;
	return AddPair( key, szString, eiElements );
}

CTerror TKVSet::PutStringArray( CTuint key, const std::string* szString, CTuint eiElements )
{
	if( !szString ) 
		return CT_errorBadKey;

	Remove( key ) ;
	return AddPair( key, szString, eiElements );
}


CTerror TKVSet::PutStringArray( CTuint key, const std::vector<std::string> &strArray)
{
	size_t size = strArray.size();
	std::vector<const char *>info(size);
	for(size_t i=0; i<size; ++i)
		info[i] = strArray[i].c_str();
	if(size == 0)
		info.push_back("");
	return PutStringArray(key, &info[0], info.size());
}


/////////////////////////////////
TKVPair * TKVSet::GetKVPair( CTuint key)
{
	int i;
	for(i=0;i<PairCount;i++)
	{
		if(PairArray[i].key == key)
			return &PairArray[i];
	}

	return NULL;
}

CTerror TKVSet::GetByte( CTuint Key, CTbyte *ByteValue )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypBYTE )
		return CT_errorBadKey ;

#ifdef SOLARIS
	memcpy(ByteValue, (DataBuff + pair->pointer), sizeof(CTbyte));
#else
	*ByteValue = *((CTbyte *)( DataBuff + pair->pointer )) ;
#endif

	return CT_errorOK ;
}

CTerror TKVSet::GetShort( CTuint Key, CTshort *pShort)
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypSHORT && pair->type != CTkvs_valtypUSHORT  )
		return CT_errorBadKey ;

#ifdef SOLARIS
	memcpy(pShort , (DataBuff + pair->pointer), sizeof(CTshort));
#else
	*pShort = *((CTshort*)(DataBuff + pair->pointer) );
#endif

	return CT_errorOK ;
}

CTerror TKVSet::GetUShort( CTuint Key, CTushort *pUShort )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypUSHORT && pair->type != CTkvs_valtypSHORT )
		return CT_errorBadKey ;

#ifdef SOLARIS
	memcpy(pUShort , (DataBuff + pair->pointer), sizeof(CTushort));
#else
	*pUShort = *((CTushort*)(DataBuff + pair->pointer) );
#endif
	return CT_errorOK ;
}

CTerror TKVSet::GetInt( CTuint Key, CTint *pInt )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypINT && pair->type != CTkvs_valtypUINT)
		return CT_errorBadKey ;

#ifdef SOLARIS
	memcpy(pInt , (DataBuff + pair->pointer), sizeof(CTint));
#else
	*pInt = *((CTint*)(DataBuff + pair->pointer) );
#endif
	
	return CT_errorOK ;
}

CTerror TKVSet::GetUInt( CTuint Key, CTuint *pUInt )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypUINT && pair->type != CTkvs_valtypINT)
		return CT_errorBadKey ;

#ifdef SOLARIS
	memcpy(pUInt, (DataBuff + pair->pointer), sizeof(CTuint));
#else
	*pUInt = *((CTuint*)(DataBuff + pair->pointer) );
#endif

	return CT_errorOK ;
}

CTerror TKVSet::GetBool( CTuint Key, CTbool *pBool )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypBOOL )
		return CT_errorBadKey ;

#ifdef SOLARIS
	memcpy(pBool, (DataBuff + pair->pointer), sizeof(CTbool));
#else
	*pBool = *((CTbool*)(DataBuff + pair->pointer) );
#endif

	return CT_errorOK ;
}

CTerror TKVSet::GetFloat( CTuint Key, CTfloat *pFloat )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if(pair->type != CTkvs_valtypFLOAT )
		return CT_errorBadKey ;

#ifdef SOLARIS
	memcpy(pFloat, (DataBuff + pair->pointer), sizeof(CTfloat));
#else
	*pFloat = *((CTfloat*)(DataBuff + pair->pointer) );
#endif

	return CT_errorOK ;
}

CTerror TKVSet::GetTime( CTuint Key, CTtime *pTime )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypTIME )
		return CT_errorBadKey ;

#ifdef SOLARIS
	memcpy(pTime, (DataBuff + pair->pointer), sizeof(CTtime));
#else
	*pTime = *((CTtime*)(DataBuff + pair->pointer));
#endif
	return CT_errorOK ;
}

CTerror TKVSet::GetString( CTuint Key, char **pString )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypSTRING )
		return CT_errorBadKey ;

	*pString = (char *)(DataBuff + pair->pointer);
	return CT_errorOK ;
}

CTerror TKVSet::GetString( CTuint Key, std::string &str)
{
	char *ptr = {0};
	CTerror ret = GetString(Key, &ptr);
	if(ret == CT_errorOK)
		str.assign(ptr);
	return ret;
}

CTerror TKVSet::GetKVSet( CTuint Key, TKVSet &kvset )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypBYTEARRAY )
		return CT_errorBadKey ;

	return kvset.String2KVSet((char *)(DataBuff + pair->pointer),pair->size);
}

CTerror TKVSet::GetByteArray( CTuint Key, CTbyteArray& uintElements) 
{
#ifndef SOLARIS
	CTbyte* ppByte=NULL;
	CTuint nCount=0;
	CTerror ret=GetByteArray(Key,&ppByte,&nCount);
	for(size_t i=0;i<nCount;i++)
		uintElements.push_back(ppByte[i]);
	return ret;
#else
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypBYTEARRAY )
		return CT_errorBadKey ;

	CTuint data_count = pair->count;
	for(CTuint i = 0; i < data_count; i++)
	{
		CTbyte byte_value;
		memcpy(&byte_value, (DataBuff + pair->pointer + i * sizeof(CTbyte)), sizeof(CTbyte));
		uintElements.push_back(byte_value);
	}
	return CT_errorOK ;
#endif
}


#ifndef SOLARIS
CTerror TKVSet::GetByteArray( CTuint Key, CTbyte **pByte, CTuint *puiElements )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypBYTEARRAY )
		return CT_errorBadKey ;

	*puiElements = pair->count ;
	*pByte = (CTbyte *)(DataBuff + pair->pointer) ;
	return CT_errorOK ;
}
#endif

CTerror TKVSet::GetShortArray( CTuint Key, CTshortArray& uintElements)
{
#ifndef SOLARIS
	CTshort* ppShort=NULL;
	CTuint nCount=0;
	CTerror ret=GetShortArray(Key,&ppShort,&nCount);
	for(size_t i=0;i<nCount;i++)
		uintElements.push_back(ppShort[i]);
	return ret;
#else
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypSHORTARRAY && pair->type != CTkvs_valtypUSHORTARRAY)
		return CT_errorBadKey ;

	CTuint data_count = pair->count;
	for(CTuint i = 0; i < data_count; i++)
	{
		CTshort short_value;
		memcpy(&short_value, (DataBuff + pair->pointer + i * sizeof(CTshort)), sizeof(CTshort));
		uintElements.push_back(short_value);
	}
	return CT_errorOK ;
#endif

}

#ifndef SOLARIS
CTerror TKVSet::GetShortArray( CTuint Key, CTshort **pShort, CTuint *puiElements )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypSHORTARRAY && pair->type != CTkvs_valtypUSHORTARRAY)
		return CT_errorBadKey ;

	*puiElements = pair->count ;
	*pShort = (CTshort *)(DataBuff + pair->pointer);

	return CT_errorOK ;
}
#endif

CTerror TKVSet::GetUShortArray( CTuint Key, CTushortArray& uintElements)
{
#ifndef SOLARIS
	CTushort* ppUShort=NULL;
	CTuint nCount=0;
	CTerror ret=GetUShortArray(Key,&ppUShort,&nCount);
	for(size_t i=0;i<nCount;i++)
		uintElements.push_back(ppUShort[i]);
	return ret;
#else
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypUSHORTARRAY && pair->type != CTkvs_valtypSHORTARRAY)
		return CT_errorBadKey ;
	
		CTuint data_count = pair->count;
		for(CTuint i = 0; i < data_count; i++)
		{
			CTushort ushort_value;
			memcpy(&ushort_value, (DataBuff + pair->pointer + i * sizeof(CTushort)), sizeof(CTushort));
			uintElements.push_back(ushort_value);
		}
		return CT_errorOK ;
#endif

}

#ifndef SOLARIS
CTerror TKVSet::GetUShortArray( CTuint Key, CTushort **pUShort, CTuint *puiElements )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypUSHORTARRAY && pair->type != CTkvs_valtypSHORTARRAY)
		return CT_errorBadKey ;

	*puiElements = pair->count ;

	*pUShort = (CTushort *)(DataBuff + pair->pointer);

	return CT_errorOK ;
}
#endif

CTerror TKVSet::GetIntArray( CTuint Key, CTintArray& uintElements)
{
#ifndef SOLARIS
	CTint* ppInt=NULL;
	CTuint nCount=0;
	CTerror ret=GetIntArray(Key,&ppInt,&nCount);
	for(size_t i=0;i<nCount;i++)
		uintElements.push_back(ppInt[i]);
	return ret;
#else
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypINTARRAY &&  pair->type != CTkvs_valtypUINTARRAY)
		return CT_errorBadKey ;

	CTuint data_count = pair->count;
	for(CTuint i = 0; i < data_count; i++)
	{
		CTint int_value;
		memcpy(&int_value, (DataBuff + pair->pointer + i * sizeof(CTint)), sizeof(CTint));
		uintElements.push_back(int_value);
	}
	return CT_errorOK ;
#endif
}

#ifndef SOLARIS
CTerror TKVSet::GetIntArray( CTuint Key, CTint **pInt, CTuint *puiElements  )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypINTARRAY &&  pair->type != CTkvs_valtypUINTARRAY)
		return CT_errorBadKey ;

	*puiElements = pair->count ;
	*pInt = (CTint *)(DataBuff + pair->pointer);
	return CT_errorOK ;
}
#endif

CTerror TKVSet::GetUIntArray( CTuint Key, CTuintArray& uintElements)
{
#ifndef SOLARIS
	CTuint* ppUint=NULL;
	CTuint nCount=0;
	CTerror ret=GetUIntArray(Key,&ppUint,&nCount);
	for(size_t i=0;i<nCount;i++)
		uintElements.push_back(ppUint[i]);
	return ret;
#else
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypUINTARRAY &&  pair->type != CTkvs_valtypINTARRAY)
		return CT_errorBadKey ;

	CTuint data_count = pair->count;
	for(CTuint i = 0; i < data_count; i++)
	{
		CTuint uint_value;
		memcpy(&uint_value, (DataBuff + pair->pointer + i * sizeof(CTuint)), sizeof(CTuint));
		uintElements.push_back(uint_value);
	}
	return CT_errorOK ;
#endif
}

#ifndef SOLARIS
CTerror TKVSet::GetUIntArray( CTuint Key, CTuint **pUInt, CTuint *puiElements  )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypUINTARRAY &&  pair->type != CTkvs_valtypINTARRAY)
		return CT_errorBadKey ;

	*puiElements = pair->count ;

	*pUInt = (CTuint *)(DataBuff + pair->pointer) ;

	return CT_errorOK ;
}
#endif

#ifndef SOLARIS
CTerror TKVSet::GetBoolArray( CTuint Key, CTbool **pBool, CTuint *puiElements  )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypBOOLARRAY )
		return CT_errorBadKey ;

	*puiElements = pair->count ;

	*pBool = (CTbool *)(DataBuff + pair->pointer) ;

	return CT_errorOK ;
}
#endif

#ifndef SOLARIS
CTerror TKVSet::GetFloatArray( CTuint Key, CTfloat **pFloat, CTuint *puiElements  )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypFLOATARRAY )
		return CT_errorBadKey ;

	*puiElements = pair->count ;

	*pFloat = (CTfloat *)(DataBuff + pair->pointer) ;

	return CT_errorOK ;
}
#endif

//add on 2011.12.26
CTerror TKVSet::GetFloatArray( CTuint Key, CTfloatArray& floatElements)
{
#ifndef SOLARIS
	CTfloat* ppFloat=NULL;
	CTuint nCount=0;
	CTerror ret=GetFloatArray(Key,&ppFloat,&nCount);
	for(size_t i=0;i<nCount;i++)
		floatElements.push_back(ppFloat[i]);
	return ret;
#else
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypFLOATARRAY )
		return CT_errorBadKey ;

	CTuint data_count = pair->count;
	for(CTuint i = 0; i < data_count; i++)
	{
		CTfloat float_value;
		memcpy(&float_value, (DataBuff + pair->pointer + i * sizeof(CTfloat)), sizeof(CTfloat));
		floatElements.push_back(float_value);
	}
	return CT_errorOK ;
#endif
}

#ifndef IA64 //该还是在64位系统下有问题，故封存，可以改用GetStringArray( CTuint Key, CTstringArray& strings)函数 by djh 20110709
CTerror TKVSet::GetStringArray( CTuint Key, char **pString[], CTuint *puiElements )
{
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypSTRINGARRAY )
		return CT_errorBadKey ;

	int uiElements = pair->count ;
	*puiElements = uiElements;

	int szLen;
	char *p = (char*)(DataBuff + pair->pointer);
	char **ptrptr = ( char **)( p+SIZEOFCTINT ) ;
	p +=(SIZEOFCTINT +SIZEOFPOINT * (uiElements));

	for(int i=0;i<(int)uiElements;i++)
	{
		ptrptr[i] = (char*)p;
		szLen = strlen(p)+1;
		p += szLen;
	}
	*pString = ptrptr;
	return CT_errorOK ;
}
#endif

CTerror TKVSet::GetStringArray( CTuint Key, CTstringArray& strings)
{
#ifndef IA64
	#ifndef SOLARIS
	char** ppStr=NULL;
	CTuint nCount=0;
	CTerror ret=GetStringArray(Key,&ppStr,&nCount);
	for(size_t i=0;i<nCount;i++)
	{
		strings.push_back(ppStr[i]);
	}
	return ret;
	#else
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypSTRINGARRAY )
		return CT_errorBadKey ;

	int uiElements = pair->count ;
	int szLen;
	int offset = pair->pointer + SIZEOFCTINT +SIZEOFPOINT * (uiElements);
	for(int i = 0; i < uiElements; i++)
	{
		strings.push_back(CTstring(DataBuff + offset,strlen(DataBuff + offset)));
		szLen = strings.back().size()+1;
		offset += szLen;
	}
	return CT_errorOK;
	#endif
#else
	TKVPair *pair=GetKVPair(Key);
	if( pair == NULL )
		return CT_errorKeyNotFound ;

	if( pair->type != CTkvs_valtypSTRINGARRAY )
		return CT_errorBadKey ;

	int uiElements = pair->count ;

	int szLen;
	char *p = (char*)(DataBuff + pair->pointer);
	p +=(SIZEOFCTINT +SIZEOFPOINT * (uiElements));

	for(int i=0;i<(int)uiElements;i++)
	{
		strings.push_back((char*)p);
		szLen = strlen(p)+1;
		p += szLen;
	}
	return CT_errorOK;
#endif
}

int TKVSet::KVSet2String( char *szString, CTuint maxlen )
{
	char *tmpPtr=szString;
	int   Size; 
	//CTushort length = GetLength(); // dcj 2012/1/30 当kvset > 64K 时，length 大于 0xffff，CTushort会溢出，
	int length = GetLength();


	if( (int)maxlen < length )
		return 0 ;

	*szString = KVSET_START;
	szString++;
	// 这里不能修改为CTuint2CTbyte 否则存在兼容性问题，由于String2KVSet 事实上不使用这个Length，所以这个值有误也不影响使用
	CTushort2CTbyte( length,szString ) ;
	szString +=SIZEOFCTSHORT;
	*szString = PairCount;// 这里限制最多 256 个key
	szString ++;
	CTuint j=0;

	for(int i=0;i<PairCount;i++)
	{
		Size = PairArray[i].size;
		char *offsetptr = (DataBuff + PairArray[i].pointer) ;

		CTuint2CTbyte( PairArray[i].key, szString ) ;
		szString += SIZEOFCTINT ;
		CTuint2CTbyte( PairArray[i].type, szString ) ;
		szString += SIZEOFCTINT ;
		CTuint2CTbyte( PairArray[i].size,szString ) ;
		szString += SIZEOFCTINT ;

		switch( PairArray[i].type )
		{
		case CTkvs_valtypNULL :
		case CTkvs_valtypBYTE :
		case CTkvs_valtypBYTEARRAY  :
		case CTkvs_valtypSTRING	:
			memcpy( szString, offsetptr , Size ) ;
			szString +=Size;
			break ;

		case CTkvs_valtypSHORT :
		case CTkvs_valtypUSHORT :
#ifdef SOLARIS
		{
			CTushort short_value;
			memcpy(&short_value, offsetptr, sizeof(CTshort));
			CTshort2CTbyte( short_value, szString ) ; 
		}
#else
			CTshort2CTbyte( *((CTshort *)offsetptr), szString ) ; 
#endif
			szString +=Size;
			break ;
		case CTkvs_valtypINT :
		case CTkvs_valtypUINT:
		case CTkvs_valtypBOOL:
		case CTkvs_valtypERROR :
		case CTkvs_valtypSTATUS :
		case CTkvs_valtypSYMBOL :
		case CTkvs_valtypTIME  :   
		case CTkvs_valtypFLOAT :
#ifdef SOLARIS
		{
			CTuint uint_value;
			memcpy(&uint_value, offsetptr, sizeof(CTuint ));
			CTuint2CTbyte( uint_value, szString ) ; 
		}
#else
			CTuint2CTbyte( *((CTuint *)offsetptr), szString ) ;
#endif
			szString +=Size;
			break ;

		case CTkvs_valtypSHORTARRAY  :
		case CTkvs_valtypUSHORTARRAY  :
			for( j=0; j<PairArray[i].count; j++ )
			{
#ifdef SOLARIS
				CTushort short_value;
				memcpy(&short_value, offsetptr, sizeof(CTshort));
				CTshort2CTbyte( short_value, szString ) ; 
#else
				CTshort2CTbyte( *( (CTshort *)offsetptr ) , szString) ;
#endif
				szString +=SIZEOFCTSHORT;
				offsetptr += SIZEOFCTSHORT;
			}
			break ;

		case CTkvs_valtypINTARRAY:
		case CTkvs_valtypUINTARRAY :
		case CTkvs_valtypBOOLARRAY :
		case CTkvs_valtypERRORARRAY :
		case CTkvs_valtypSTATUSARRAY :
		case CTkvs_valtypSYMBOLARRAY :
			for( j=0; j<PairArray[i].count; j++ )
			{
#ifdef SOLARIS
				CTuint uint_value;
				memcpy(&uint_value, offsetptr, sizeof(CTuint ));
				CTuint2CTbyte( uint_value, szString ) ; 
#else
				CTuint2CTbyte( *( (CTuint *)offsetptr) , szString ) ;
#endif
				szString +=SIZEOFCTINT;
				offsetptr += SIZEOFCTINT;
			}
			break ;

		case CTkvs_valtypFLOATARRAY  :  //新增处理 by djh 20110709
			for( j=0; j<PairArray[i].count; j++ )
			{
#ifdef SOLARIS
				CTfloat float_value;
				memcpy(&float_value, offsetptr, sizeof(CTfloat));
				CTfloat2CTbyte( float_value, szString ) ; 
#else
				CTfloat2CTbyte( *( (CTfloat *)offsetptr) , szString ) ;
#endif
				szString +=SIZEOFCTINT;
				offsetptr += SIZEOFCTINT;
			}
			break ;

		case CTkvs_valtypSTRINGARRAY:
			memcpy( szString, offsetptr , Size ) ;
			CTuint2CTbyte( PairArray[i].count ,szString );
			szString +=Size;
			break ;
		}
	}

	return length;
}

CTerror TKVSet::String2KVSet( const char *szString, CTuint maxlen )
{
	CTuint   Key=0, Size=0, Type=0 ;
	CTuint   num_CTuint=0;
	CTushort len=0;
	CTshort  num_CTshort=0;
	int      uiElements=0;
	int      Count=0,j;
	const char *p = szString;

	if (maxlen<constKVSETHEADSIZE)//Access Violation 
		return CT_errorBadKVSet ;

	if( (CTbyte)*p != KVSET_START )
		return CT_errorBadKVSet ;

	PairCount = 0 ;
	DataLength    = 0 ;

	p++ ;
	CTbyte2CTushort( p, &len ) ;
	p += sizeof( CTushort ) ;

	if( len > (CTushort)maxlen )
	{
		len = constKVSETHEADSIZE ;
		PairCount= 0 ;
		return CT_errorBadKey ;
	}

	Count = (int)*p++ ;
	for( int i=0; i<Count ; i++ )
	{		
		if (CTuint(p-szString+SIZEOFCTINT*3)>maxlen)//Access Violation
			return CT_errorBadKVSet;

		CTbyte2CTuint( p, &Key ) ;
		p += SIZEOFCTINT ;
		CTbyte2CTuint( p, &Type ) ;
		p += SIZEOFCTINT ;
		CTbyte2CTuint( p, &Size ) ;
		p += SIZEOFCTINT ;

		if (CTuint(p-szString+Size)>maxlen)//Access Violation
			return CT_errorBadKVSet;

		switch( Type ) 
		{
		case CTkvs_valtypNULL :
		case CTkvs_valtypBYTE :
		case CTkvs_valtypSTRING :
			AddPair( Key,Type, Size, (void *)p,1 );
			break ;
		case CTkvs_valtypSHORT  :
		case CTkvs_valtypUSHORT  :
			CTbyte2CTshort( p, &num_CTshort ) ;
			AddPair( Key,Type, Size, (void *)&num_CTshort,1 );
			break ;
		case CTkvs_valtypINT :
		case CTkvs_valtypUINT:
		case CTkvs_valtypBOOL:
		case CTkvs_valtypERROR :
		case CTkvs_valtypSTATUS :
		case CTkvs_valtypSYMBOL :
		case CTkvs_valtypTIME  :   
		case CTkvs_valtypFLOAT :
			CTbyte2CTuint( p, &num_CTuint ) ;
			AddPair( Key,Type, Size, (void *)&num_CTuint,1 );
			break ;

		case CTkvs_valtypBYTEARRAY :
			uiElements = Size / SIZEOFCTBYTE ;
			AddPair( Key,Type, Size, (void *)p,uiElements);
			break;

		case CTkvs_valtypSHORTARRAY  :
		case CTkvs_valtypUSHORTARRAY  :
			uiElements = Size / SIZEOFCTSHORT ;
			for(j=0; j<uiElements; j++ )
			{	
#ifndef SOLARIS
				CTbyte2CTshort( p, (CTshort*)p ) ;
#else
				CTshort tmp_val(0);
				CTbyte2CTshort( p, &tmp_val ) ;
				memcpy((void*)p, &tmp_val, sizeof(CTshort));
#endif
				p +=SIZEOFCTSHORT;
			}
			p -= Size;
			AddPair( Key,Type, Size, (void *)p,uiElements);
			break ;

		case CTkvs_valtypINTARRAY :
		case CTkvs_valtypUINTARRAY:        
		case CTkvs_valtypBOOLARRAY:    
		case CTkvs_valtypERRORARRAY :
		case CTkvs_valtypSTATUSARRAY :
		case CTkvs_valtypSYMBOLARRAY :
			uiElements = Size / SIZEOFCTINT  ;
			for( j=0; j<uiElements; j++ ) 
			{
#ifndef SOLARIS
				CTbyte2CTuint( p, (CTuint*)p ) ;
#else
				CTuint tmp_val(0);
				CTbyte2CTuint( p, &tmp_val ) ;
				memcpy((void*)p, &tmp_val, sizeof(CTuint));
#endif
				p +=SIZEOFCTINT;
			}
			p -= Size;
			AddPair( Key,Type, Size, (void *)p,uiElements );
			break ;
		case CTkvs_valtypFLOATARRAY  :
			uiElements = Size / SIZEOFCTFLOAT  ;
			for( j=0; j<uiElements; j++ ) 
			{
#ifndef SOLARIS
				CTbyte2CTfloat( p, (CTfloat*)p ) ;
#else
				CTfloat tmp_val(0.0);
				CTbyte2CTfloat( p, &tmp_val ) ;
				memcpy((void*)p, &tmp_val, sizeof(CTfloat));
#endif
				p += SIZEOFCTFLOAT;
			}
			p -= Size;
			AddPair( Key,Type, Size, (void *)p,uiElements );
			break;

		case CTkvs_valtypSTRINGARRAY:
			CTbyte2CTuint( p, &num_CTuint ) ;
			AddPair( Key,Type, Size, (void *)p,num_CTuint );
			break;
		}
		p +=Size;		
	}	

	return CT_errorOK;
}

CTstring TKVSet::getInfo(bool withValue)
{
	std::stringstream outString ;
	int i,j;
	char str[512]="";

	outString << CTstring("TKVSet Info:");
	snprintf( str, sizeof(str)-1, "MaxBuffLength=%d, DataLength=%d, PairCount=%d\n",
		MaxBuffLength, DataLength, PairCount);
	outString << CTstring(str);
	for( i=0; i<PairCount; i++)
	{
		snprintf( str, sizeof(str)-1, "Key=H'%X, type=%d, size=%d, elements=%d, offset=%d,",
			PairArray[i].key, PairArray[i].type, PairArray[i].size, PairArray[i].count, PairArray[i].pointer);
		outString << CTstring(str);

		if(false == withValue)
		{
			outString << "\n";
			continue;
		}

		outString << "Value: ";

		switch ( PairArray[i].type )
		{
		case CTkvs_valtypBYTE :
			{
				unsigned char c=DataBuff[PairArray[i].pointer];
				snprintf( str, sizeof(str)-1, "%02X ",c );
				outString << CTstring(str); 
			}
			break; 
		case CTkvs_valtypSTRING :
			snprintf( str, sizeof(str)-1, "%s", &DataBuff[PairArray[i].pointer] );
			outString << CTstring(str) ;
			break ;
		case CTkvs_valtypSHORT  :
		case CTkvs_valtypUSHORT  :
		case CTkvs_valtypINT :
		case CTkvs_valtypUINT:
		case CTkvs_valtypBOOL:
		case CTkvs_valtypERROR :
		case CTkvs_valtypSTATUS :
		case CTkvs_valtypSYMBOL :
		case CTkvs_valtypTIME  :   
			snprintf( str, sizeof(str)-1, "%d, X'%X", DataBuff[PairArray[i].pointer],DataBuff[PairArray[i].pointer] );
			outString << CTstring(str);;
			break;
		case CTkvs_valtypFLOAT :
			snprintf( str, sizeof(str)-1, "%02X", DataBuff[PairArray[i].pointer] );
			outString << CTstring(str); 
			break ;

		case CTkvs_valtypBYTEARRAY :
			{
				unsigned char c;
				for( j=0; j<PairArray[i].size; j++) {
					c = DataBuff[PairArray[i].pointer+j] ;
					snprintf( str, sizeof(str)-1, " %02X", c);
					outString << CTstring(str); 
				}
			}
			break;

		case CTkvs_valtypSHORTARRAY  :
		case CTkvs_valtypUSHORTARRAY  :
			for( j=0; j<(int)(PairArray[i].count); j++) {
				snprintf( str, sizeof(str)-1, " %d", *( (CTshort *)(&DataBuff[PairArray[i].pointer]) + j)  );
				outString << CTstring(str); 
			}
			break ;
		case CTkvs_valtypINTARRAY :
		case CTkvs_valtypUINTARRAY:        
		case CTkvs_valtypBOOLARRAY:    
		case CTkvs_valtypERRORARRAY :
		case CTkvs_valtypSTATUSARRAY :
		case CTkvs_valtypSYMBOLARRAY :
			for( j=0; j<(int)(PairArray[i].count); j++) {
				snprintf( str, sizeof(str)-1, " %d", *( (CTint *)(&DataBuff[PairArray[i].pointer]) + j)  );
				outString << CTstring(str); 
			}
			break ;
		case CTkvs_valtypFLOATARRAY  :
			for( j=0; j<(int)(PairArray[i].count); j++) {
				snprintf( str, sizeof(str)-1, " %f", *( (CTfloat *)(&DataBuff[PairArray[i].pointer]) + j)  );
				outString << CTstring(str); 
			}
			break ;
		case CTkvs_valtypSTRINGARRAY:
			{
				outString << "{";
				char *p = (char*)(DataBuff + PairArray[i].pointer);
				p +=(SIZEOFCTINT +SIZEOFPOINT * (PairArray[i].count));
				for(int i=0;i<(int)PairArray[i].count;i++)
				{
					outString << "(" << CTstring(p) << ") "; 
					p += strlen(p)+1;
				}
				outString << "}";
			}
			break;

		}
		outString << "\n" ;
	}

	return outString.str();
}


////////////////////////////////////////////////////
// CTtranInfo member function
CTtranInfo::CTtranInfo(const CTtranInfo &tranInfo)
{
	*this = tranInfo;
}

CTtranInfo::CTtranInfo() 
: version(constTHISVERSION), commSender(0), commReceiver(0),sender(0),
receiver(0), messageID(0), tranID(0),
status(0), qualifier(0), errorData(CT_errorOK),immidiate(false)
{
	timeStamp = time(0);
}

CTtranInfo::CTtranInfo( CTobj snd, CTobj rcv, CTsymbol msgid, TKVSet *kvset/*=NULL*/, CTerror err/*=CT_errorOK*/, CTstatus sts/*=0*/, CTuint tranid/*=0*/, CTuint qlfer/*=0*/ ) 
: version(constTHISVERSION), commSender(0), commReceiver(0),sender(snd), receiver(rcv),
messageID(msgid),tranID(tranid),
status(sts), qualifier(qlfer), errorData(err),immidiate(false)
{
	timeStamp = time(0);
	if( kvset )
		messageData = *kvset ;
}
CTtranInfo & CTtranInfo::operator = (const  CTtranInfo &tranInfo)
{
	if (this==&tranInfo)
		return *this;
	version = tranInfo.version;
	commSender = tranInfo.commSender ;
	commReceiver = tranInfo.commReceiver;
	sender = tranInfo.sender;
	receiver = tranInfo.receiver;
	messageID = tranInfo.messageID;
	tranID = tranInfo.tranID;
	status = tranInfo.status;
	qualifier = tranInfo.qualifier;
	errorData = tranInfo.errorData;
	sourAddress = tranInfo.sourAddress;
	messageData = tranInfo.messageData ;
	senderURI = tranInfo.senderURI;
	receiverURI = tranInfo.receiverURI;
	timeStamp = tranInfo.timeStamp;
	immidiate = tranInfo.immidiate;

	return *this;
}

CTint CTtranInfo::toString(char *str, CTint maxlen)
{
	if( maxlen < constTRANINFOHEADSIZE )
		return 0 ;

	char *p = str;

	CTuint2CTbyte( commSender,  p);
	p += SIZEOFCTINT;
	CTuint2CTbyte( commReceiver, p);
	p += SIZEOFCTINT;

	CTuint2CTbyte( version, p );
	p += SIZEOFCTINT;
	CTuint2CTbyte( sender,  p);
	p += SIZEOFCTINT;
	CTuint2CTbyte( receiver, p);
	p += SIZEOFCTINT;
	CTuint2CTbyte(messageID, p);
	p += SIZEOFCTINT;
	CTuint2CTbyte(tranID, p);
	p += SIZEOFCTINT;
	CTuint2CTbyte(status, p);
	p += SIZEOFCTINT;
	CTuint2CTbyte(qualifier, p);
	p += SIZEOFCTINT;
	CTuint2CTbyte(errorData, p);
	p += SIZEOFCTINT;
	p += messageData.KVSet2String(p, maxlen-constTRANINFOHEADSIZE);

	return (p-str);
}

CTerror CTtranInfo::fromString(const sockaddr_in &from, char *str, CTint len)
{
	CTerror     ret     = CT_errorOK;
	if( len < constTRANINFOHEADSIZE )
		return CT_errorFAIL;

	sourAddress = CTsockaddr(from);

	char *p = str;

	CTbyte2CTuint( p, &commSender);
	p += SIZEOFCTINT;
	CTbyte2CTuint( p, &commReceiver);
	p += SIZEOFCTINT;

	CTbyte2CTuint( p, (CTuint*)&version);
	p += SIZEOFCTINT;
	CTbyte2CTuint( p, &sender);
	p += SIZEOFCTINT;
	CTbyte2CTuint( p, &receiver);
	p += SIZEOFCTINT;
	CTbyte2CTuint(p, &messageID);
	p += SIZEOFCTINT;
	CTbyte2CTuint(p, &tranID);
	p += SIZEOFCTINT;
	CTbyte2CTuint(p, &status);
	p += SIZEOFCTINT;
	CTbyte2CTuint(p, &qualifier);
	p += SIZEOFCTINT;
	CTbyte2CTuint(p, &errorData);
	p += SIZEOFCTINT;

	if (len>constTRANINFOHEADSIZE)
	{
		ret = messageData.String2KVSet(p, len-constTRANINFOHEADSIZE);		
	}
	else
	{
		messageData.Clear();
	}

	return ret;
}


int CTtranInfo::TestCaseTKVSet(int type)
{
#define COUNT 3
#define BUFFER_LEN 4096

	TKVSet kv1, kv2;
	CTbyte iByte1,  iByte3[COUNT], oByte1,  *oByte3;
	CTshort iShort1,  iShort3[COUNT], oShort1,  *oShort3;
	CTint   iInt1,  iInt3[COUNT], oInt1,  *oInt3;
	CTfloat iFloat1,  iFloat3[COUNT], oFloat1,  *oFloat3;
	CTbool	iBool1,  iBool3[COUNT], oBool1,  *oBool3;
	CTtime	iTime1,  iTime3[COUNT], oTime1;
	const char *iString1="hello  string 1!", *iString2="hello string 2!";
	char *iString3[COUNT], *oString1;
	CTstringArray stString3;
	CTuint elements;
	int length1, length2, i,j;
	char buffer[4096] = {0};

	for( i=0; i<COUNT; i++)
	{
		iString3[i] = new char [64] ;
		sprintf( iString3[i], "hello string %d", i+1);
	}
	switch( type )
	{
	case 1:
		iByte1='1', iShort1=11, iInt1=1111, iFloat1=1111.1f, iBool1=CT_boolTRUE, iTime1=time(0);
		kv1.PutByte( 1001, iByte1);
		kv1.PutShort(1002, iShort1);
		kv1.PutInt(1003, iInt1);
		kv1.PutFloat(1004, iFloat1);
		kv1.PutBool(1005, iBool1);
		kv1.PutTime(1006, iTime1);
		kv1.PutString(1007, iString1);

		if( kv1.GetBool(1005, &oBool1) != CT_errorOK ||
			kv1.GetInt(1003, &oInt1) != CT_errorOK ||
			kv1.GetByte(1001, &oByte1) != CT_errorOK ||
			kv1.GetShort(1002, &oShort1) != CT_errorOK ||
			kv1.GetString( 1007, &oString1 ) != CT_errorOK ||
			kv1.GetTime( 1006, &oTime1 ) != CT_errorOK ||
			kv1.GetFloat(1004, &oFloat1 ) != CT_errorOK )
			return -1 ;

		if( iByte1 != oByte1 )
			return -2 ;
		if( iShort1 != oShort1 )
			return -3 ;
		if( iInt1 != oInt1 )
			return -4 ;
		if( iBool1 != oBool1  )
			return -5; 
		if( iTime1 != oTime1 )
			return -6;
		if( iFloat1 - oFloat1 > 0.0001f  || oFloat1 - iFloat1 > 0.0001f )
			return -7;
		if( strcmp( iString1, oString1) )
			return -8 ;

		break;

	case 2:
		for( i=0; i<COUNT; i++ )
		{
			iByte3[i] = 'a'+i;
			iShort3[i] = 11+i;
			iInt3[i] = 111+i;
			iFloat3[i] = 1111.1f+i;
			iBool3[i] = CT_boolFALSE ;
			iTime3[i] = time(0)+i;
		}
		kv1.PutStringArray(1007, iString3, COUNT);
		kv1.PutByteArray( 1001, iByte3, COUNT);
		kv1.PutIntArray(1003, iInt3, COUNT);
		kv1.PutFloatArray(1004, iFloat3, COUNT);
		kv1.PutShortArray(1002, iShort3, COUNT);
		kv1.PutBoolArray(1005, iBool3, COUNT);
		elements = 0 ;

		if(	kv1.GetStringArray( 1007, stString3  ) != CT_errorOK ||stString3.size() != COUNT )
			return -5;
#ifndef SOLARIS
		if( kv1.GetBoolArray(1005, &oBool3, &elements) != CT_errorOK || elements != COUNT )
			return -1;
		if(	kv1.GetIntArray(1003, &oInt3, &elements ) != CT_errorOK || elements != COUNT )
			return -2;
		if(	kv1.GetByteArray(1001, &oByte3, &elements ) != CT_errorOK ||elements != COUNT )
			return -3;
		if(	kv1.GetShortArray(1002, &oShort3, &elements ) != CT_errorOK ||elements != COUNT )
			return -4;
		if(	kv1.GetFloatArray(1004, &oFloat3, &elements ) != CT_errorOK || elements != COUNT )
			return -6;
#endif

		for( j=0; j<COUNT; j++ )
		{
			if( iBool3[j] != oBool3[j] )
				return -8 ;
			if( iInt3[j] != oInt3[j] )
				return -9;
			if( iByte3[j] != oByte3[j] )
				return -10;
			if( iShort3[j] != oShort3[j] )
				return -11;
			if( strcmp( iString3[j], stString3[j].c_str()) )
				return -12;
			if( iFloat3[j] - oFloat3[j] > 0.0001f  || oFloat3[j] - iFloat3[j] > 0.0001f )
				return -13 ;
		}
		break;

	case 3:
		iByte1=1, iShort1=11, iInt1=111, iFloat1=111.1f, iBool1=CT_boolTRUE, iTime1=time(0);
		for( i=0; i<COUNT; i++ )
		{
			iInt3[i] = 111+i;
			iShort3[i] = 11+i;
		}

		kv1.PutByte( 1001, iByte1);
		kv1.PutShortArray(1002, iShort3, COUNT);
		kv1.PutIntArray(1003, iInt3, COUNT);
		kv1.PutFloat(1004, iFloat1);
		kv1.PutBool(1005, iBool1);
		kv1.PutTime(1006, iTime1);
		kv1.PutStringArray(1007, iString3, COUNT);

		kv2 = kv1 ;

		if( kv2.GetBool(1005, &oBool1) != CT_errorOK ||
			kv2.GetByte(1001, &oByte1) != CT_errorOK ||
			kv2.GetTime( 1006, &oTime1 ) != CT_errorOK ||
			kv2.GetFloat(1004, &oFloat1 ) != CT_errorOK )
			return -1 ;
		
#ifndef SOLARIS
		if(	kv2.GetIntArray(1003, &oInt3, &elements) != CT_errorOK || elements != 3 )
			return -2 ;
		if(	kv2.GetShortArray(1002, &oShort3, &elements ) != CT_errorOK ||elements != 3 )
			return -3 ;
#endif
		if(	kv2.GetStringArray( 1007, stString3  ) != CT_errorOK ||stString3.size() != 3 )
			return -4;

		if(elements != COUNT )
			return -5 ;
		if( iByte1 != oByte1 || iShort3[0] != oShort3[0] || iInt3[1] != oInt3[1] || iBool1 != oBool1 ||  iTime1 != oTime1 )
			return -6 ;
		if( strcmp( iString3[2], stString3[2].c_str()) )
			return -7 ;

		break;

	case 4:
		iByte1=1, iShort1=11, iInt1=1111, iFloat1=1111.1f, iBool1=CT_boolTRUE, iTime1=time(0);
		for( i=0; i<COUNT; i++ )
		{
			iInt3[i] = 1+i;
			iShort3[i] = 11+i;
		}

		kv1.PutByte( 1001, iByte1);
		kv1.PutShortArray(1002, iShort3, COUNT);
		kv1.PutIntArray(1003, iInt3, COUNT);
		kv1.PutFloat(1004, iFloat1);
		kv1.PutBool(1005, iBool1);
		kv1.PutTime(1006, iTime1);
		kv1.PutStringArray(1007, iString3, COUNT);

		length1=kv1.KVSet2String(buffer, BUFFER_LEN);
		if( length1 != kv1.GetLength() )
			return -1 ;

		if( kv2.String2KVSet(buffer, length1) != CT_errorOK )
			return -2;

		length2 = kv2.GetLength();
		if( length1 != length2 )
			return -3;

		if( kv2.GetBool(1005, &oBool1) != CT_errorOK ||
			kv2.GetByte(1001, &oByte1) != CT_errorOK ||
			kv2.GetTime( 1006, &oTime1 ) != CT_errorOK ||
			kv2.GetFloat(1004, &oFloat1 ) != CT_errorOK )
			return -4 ;

#ifndef SOLARIS
		if(	kv2.GetIntArray(1003, &oInt3, &elements) != CT_errorOK || elements != 3 )
			return -5 ;
		if(	kv2.GetShortArray(1002, &oShort3, &elements ) != CT_errorOK ||elements != 3 )
			return -6 ;
#endif
		if(	kv2.GetStringArray( 1007, stString3  ) != CT_errorOK ||stString3.size() != 3 )
			return -7;

		if(elements != COUNT )
			return -8 ;
		if( iByte1 != oByte1 || iShort3[0] != oShort3[0] || iInt3[1] != oInt3[1] || iBool1 != oBool1 ||  iTime1 != oTime1 )
			return -9 ;
		if( strcmp( iString3[2], stString3[2].c_str()) )
			return -10 ;

	case 5:
		{
			CTstringArray strArray;
			for(size_t i=0;i<1024;i++)
			{
				CTstring str;
				for(size_t j=0;j<64;j++)
					str=str+"a";
				strArray.push_back(str);
			}
			kv2.PutStringArray(1008,strArray);
		}
	default:
		break;
	}

	for( i=0; i<COUNT; i++)
		delete iString3[i] ;

	return 0 ;
}

void CTtranInfo::PutStableKey()
{
	if (senderURI.size()>0)
		messageData.PutString(PUBLIC_SUNTEK_SenderAddress,senderURI);
	if (receiverURI.size()>0)
		messageData.PutString(PUBLIC_SUNTEK_ReceiverAddress,receiverURI);
	messageData.PutTime(PUBLIC_SUNTEK_TraninfoTimeStamp,timeStamp);
	return ;
}

