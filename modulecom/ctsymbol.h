#ifndef __CTSYMBOL_H__
#define __CTSYMBOL_H__

/*=============================================================================
// Symbol construction, segment extraction and comparison
//===========================================================================*/
#define ADDRESS_OFFSET        30
#define ADDRESS_MASK          0x3
#define OBJECT_OFFSET         20
#define OBJECT_MASK           0x03FF
#define VENDOR_OFFSET         10
#define VENDOR_MASK           0x03FF
#define ITEM_OFFSET           0
#define ITEM_MASK             0x03FF
 
// Build a symbol.
/*  Symbol name looks like: Obj_VENDOR_ItemName
	Object  for which this symbol was defined
	Vendor who assigned the name and value for this symbol
	Item Name for this particular symbol.
*/
#define CTkvs_Sym( object, vendor, item )\
	(CTsymbol)(((OBJECT_MASK & (object)) << OBJECT_OFFSET) |\
		   ((VENDOR_MASK & (vendor)) << VENDOR_OFFSET) |\
		    (  ITEM_MASK &   (item)))


#define CTkvs_Object( symbol )\
	(CTuint)(((symbol) >> OBJECT_OFFSET) & OBJECT_MASK)
#define CTkvs_Vendor( symbol )\
	(CTuint)(((symbol) >> VENDOR_OFFSET) & VENDOR_MASK)
#define CTkvs_Item( symbol )\
	(CTuint)(((symbol) >>   ITEM_OFFSET) &   ITEM_MASK)

#define CTsym_Build        CTkvs_Sym
#define CTsym_Object       CTkvs_Object
#define CTsym_Vendor       CTkvs_Vendor
#define CTsym_Item         CTkvs_Item

/******************************************************************************
 *    ECTF defined symbol object values.
 *****************************************************************************/
#define CT_objANY                (0x0000)       /* ANY OBJECT */
#define CT_objCONFERENCE         (0x0001)       /* CONFERENCE */
#define CT_objCONNECTION         (0x0002)       /* CONNECTION */
#define CT_objCONTAINER          (0x0003)       /* CONTAINER */
#define CT_objFAXRECEIVER        (0x0004)       /* FAX RECEIVER */
#define CT_objFAXSENDER          (0x0005)       /* FAX SENDER */
#define CT_objFAXSERVICE         (0x0006)       /* FAX SERVICE */
#define CT_objGROUP              (0x0007)       /* GROUP */
#define CT_objKVSET              (0x0008)       /* KVSET */
#define CT_objMACRO              (0x0009)       /* MACRO */
#define CT_objPLAYER             (0x000A)       /* PLAYER */
#define CT_objRECORDER           (0x000B)       /* RECORDER */
#define CT_objSCR                (0x000C)       /* SCR */
#define CT_objSESSION            (0x000D)       /* SESSION */
#define CT_objSIGD               (0x000E)       /* SIGNAL DETECTOR */
#define CT_objSIGG               (0x000F)       /* SIGNAL GENERATOR */
#define CT_objASR                (0x0010)       /* ASR */
#define CT_objADMIN              (0x0011)       /* ADMINISTRATION */
#define CT_objCCR                (0x0012)       /* CCR */
#define CT_objDATAOBJECT         (0x0013)       /* CONT DATA OBJECT */
#define CT_objMESSAGE            (0x0014)       /* MESSAGE */
#define CT_objFAXLL              (0x0015)       /* FAX LOW LEVEL */
#define CT_objERROR              (0x0016)       /* ERROR */
#define CT_objSESSIONMANAGER     (0x0018)       /* SESSION MANAGER */
#define CT_objSYMBOL             (0x0019)       /* SYMBOL TABLE */
#define CT_objTRIGGER            (0x001A)       /* EVENT TRIGGER */
#define CT_objMEDIA              (0x001B)       /* media server symbol */
#define CT_objPROFILE            (0x001C)       /* profile module*/
#define CT_objCOMMUNICATION      (0x001D)
#define CT_objSIA                (0x001E)       /* Service Interface Adapter */
#define CT_objAUTHEN            (0x001F)       /* authen module,Walker */
#define CT_objCOMMCTRL			(0x0020)
#define CT_objSWITCH			(0X0021)
#define CT_objMAINT             (0X0022)
#define CT_objCONFIG            (0X0023)
#define CT_objSCHEDULER         (0X0024)       /* Scheduler,Walker */
#define CT_objSS7				(0x0025)
#define CT_objSHORTMESSAGE		(0x0026)
#define CT_objCTSI				(0x0027)		// ctsi obj
#define CT_objRADIUS			(0x0027)
#define CT_objIPSWITCH			(0x0028)
#define CT_objOCM				(0x0029)
#define CT_objGOR			    (0x002a)
#define CT_objTCP				(0x002b)
#define CT_objCTIServer  		(0x002c)
#define CT_objQQServer			(0x002d)
#define CT_objEMG				(0x002e)
#define CT_objICB				(0x002f)            // IPSwitch Communication Bridge
#define CT_objTCAP				(0x0030)
#define CT_objINAP				(0x0031)
#define CT_objVIDEO				(0x0032)
#define CT_objPROXY				(0x0033)
#define CT_objSIP				(0x0040) //TZJ added for BEA project
#define CT_objRTSP				(0x0041) //YWB add for rtsp
#define CT_objACTION			(0x0057)
#define CT_objNMS				(0x0069)
#define CT_objAUDIOCODES		(0x006A)
#define CT_objMG				(0x006F)
#define CT_objTERMINAL			(0x007E)
#define CT_objPSP				(0x007F)
#define CT_objPUBLIC			(0X0080)
#define CT_objAAA				(0x00AF)
#define CT_objAPPLICATION       (0x00F0)       /* Local Application */
#define CT_objTTS				(0x00B0)
#define CT_objDBA				(0x00BF)
#define CT_objSNMP				(0x00C0)	  //add by zcb 2004.5.9
#define CT_objDLL				(0x00C1)      //add by zcb 2004.5.27
#define CT_objHTTP              (0x00C2)      //add by zcb 2004.7.15
#define CT_objAgentX            (0x00C3)      //add by zcb 2004.8.19
#define CT_objSNS			    (0x00C4) 	  //add by zcb 2004.9.1 

#define CT_objSOAP			    (0x00C5) 	  //add by wangyequan 2008.3.19
#define CT_objCallServer		(0x00C6)
#define CT_objVAG			    (0x00C7) 	  //add by wangyequan 2008.7.10
#define CT_objMediaSwitch	    (0x00C8) 	  // for MediaSwtich
#define CT_objIVVR	    (0x00C9)

#define CT_objAlarmServer	    (0x00D0) 	  //added for AlarmServer by wj 2009.04.20
#define CT_objOTB         (0x00D1)       //added for ocs by wj 2010.05.27
#define CT_objPDS         (0x00D2)       //added for ocs by wj 2010.05.27

#define CT_objOSS	    (0x0100) 	  //added for AlarmServer by wj 2009.04.20
/******************************************************************************
 *    ECTF defined symbol vendor values.
 *****************************************************************************/
 
#define CT_vendECTF                    (0x0001)
#define CT_vendDLGC                    (0x0002)
#define CT_vendSUNTEK		       (0x0003)
#define CT_vendEXCEL		       (0x0004)	
/******************************************************************************
*    Definitions of standard status.
*****************************************************************************/

//Q:why not const?
//A:because	CTStatus not defined in this head, faint!

//what's i wanna is:
//const CTStatus CT_statusOK = 0x0000;


#define	CT_statusOK					(0x0000)//add by akumas	2006.09.04
#define	CT_statusFail				(0x0001)//add by akumas	2006.09.04

/******************************************************************************
 *    Definitions of standard errors.
 *****************************************************************************/
#define __CTErrorSym(item)             CTsym_Build( CT_objERROR,\
						  CT_vendECTF,\
                                                  (item))

#define CT_errorOK                                          __CTErrorSym(0x000)
#define CT_errorBadGroup                                    __CTErrorSym(0x001)
#define CT_errorBadGroupConfig                              __CTErrorSym(0x002)
#define CT_errorBadGroupSet                                 __CTErrorSym(0x003)
#define CT_errorBadParm                                     __CTErrorSym(0x004)
#define CT_errorBadResource                                 __CTErrorSym(0x005)
#define CT_errorBadRTC                                      __CTErrorSym(0x006)
#define CT_errorBadSession                                  __CTErrorSym(0x007)
#define CT_errorBusy                                        __CTErrorSym(0x008)
#define CT_errorSystem                                      __CTErrorSym(0x009)
#define CT_errorTimeout                                     __CTErrorSym(0x00A)
#define CT_errorStopped                                     __CTErrorSym(0x00B)
#define CT_errorNoMem                                       __CTErrorSym(0x00C)
#define CT_errorTransNotStopped                             __CTErrorSym(0x00D) 
#define CT_errorNotOwner                                    __CTErrorSym(0x00E)
#define CT_errorBadContainerName                            __CTErrorSym(0x00F)
#define CT_errorBadObjectName                               __CTErrorSym(0x010)
#define CT_errorContainerExists                             __CTErrorSym(0x011)
#define CT_errorContainerNotExist                           __CTErrorSym(0x012)
#define CT_errorInvalidParameter                            __CTErrorSym(0x013)
#define CT_errorObjectExists                                __CTErrorSym(0x014)
#define CT_errorObjectNotExist                              __CTErrorSym(0x015)
#define CT_errorContainerFull                               __CTErrorSym(0x016)
#define CT_errorObjectFull                                  __CTErrorSym(0x017)
#define CT_errorLocked                                      __CTErrorSym(0x018)
#define CT_errorInvPosition                                 __CTErrorSym(0x019)
#define CT_errorPermission                                  __CTErrorSym(0x01A)
#define CT_errorBadKVSet                                    __CTErrorSym(0x01B)
#define CT_errorBadKey                                      __CTErrorSym(0x01C)
#define CT_errorKeyNotFound                                 __CTErrorSym(0x01D)
#define CT_errorBadValueType                                __CTErrorSym(0x01E)
#define CT_errorNullArray                                   __CTErrorSym(0x01F)
#define CT_errorValueIsArray                                __CTErrorSym(0x020)
#define CT_errorValueNotArray                               __CTErrorSym(0x021)
#define CT_errorNotSupported                                __CTErrorSym(0x022)                 
#define CT_errorInvalidOp                                   __CTErrorSym(0x023)
#define CT_errorBadObjectHandle                             __CTErrorSym(0x024)
#define CT_errorEndOfStream                                 __CTErrorSym(0x025)
#define CT_errorMediaChange                                 __CTErrorSym(0x026)
#define CT_errorBadArg                                      __CTErrorSym(0x027)
#define CT_errorNoTranStopped                               __CTErrorSym(0x029)
#define CT_errorBadParmValue                                __CTErrorSym(0x02A)
#define CT_errorNotOnStack                                  __CTErrorSym(0x02B)
#define CT_errorShuttingDown                                __CTErrorSym(0x02C)
#define CT_errorStartOfStream                               __CTErrorSym(0x02D)
#define CT_errorBadMediaType                                __CTErrorSym(0x02E)
#define CT_errorNotAnswered                                 __CTErrorSym(0x02F)
#define CT_errorCouldNotDrop                                __CTErrorSym(0x030)
#define CT_errorDisconnected                                __CTErrorSym(0x031)
#define CT_errorOutOfService                                __CTErrorSym(0x032)
#define CT_errorNoDonor                                     __CTErrorSym(0x033)
#define CT_errorBadASI                                      __CTErrorSym(0x034)
#define CT_errorUnconnectable                               __CTErrorSym(0x035)
#define CT_errorNotFound                                    __CTErrorSym(0x036)
#define CT_errorBadData                                     __CTErrorSym(0x037)
#define CT_errorBadParameters                               __CTErrorSym(0x039)
#define CT_errorNoBandWidth                                 __CTErrorSym(0x03A)
#define CT_errorBufferTooSmall                              __CTErrorSym(0x03B)
#define CT_errorDirectionality                              __CTErrorSym(0x03C)
#define CT_errorMissingSymTable                             __CTErrorSym(0x03E)
#define CT_errorUnknownKey                                  __CTErrorSym(0x03F)
#define CT_errorBadHandle                                   __CTErrorSym(0x040)
#define CT_errorDupHandler                                  __CTErrorSym(0x041)
#define CT_errorBadEvent                                    __CTErrorSym(0x042)
#define CT_errorBadServer                                   __CTErrorSym(0x043)
#define CT_errorComms                                       __CTErrorSym(0x044)
#define CT_errorHandlerNotFound                             __CTErrorSym(0x045)
#define CT_errorBadAddress                                  __CTErrorSym(0x046)
#define CT_errorClientFailed                                __CTErrorSym(0x047)
#define CT_errorServerFailed                                __CTErrorSym(0x048)
#define CT_errorBandWidthMismatch                           __CTErrorSym(0x049)
#define CT_errorFileNotFound                                __CTErrorSym(0x04A)
#define CT_errorNumSignals                                  __CTErrorSym(0x04B)
#define CT_errorNotAvailable                                __CTErrorSym(0x04C)
#define CT_errorNoReceiver                                  __CTErrorSym(0x04D)
#define CT_errorTooManyProfs                                __CTErrorSym(0x04E)
#define CT_errorExists                                      __CTErrorSym(0x04F)
#define CT_errorExportError                                 __CTErrorSym(0x050) 
#define CT_errorCantOpenFile                                __CTErrorSym(0x051)   
#define CT_errorImportError                                 __CTErrorSym(0x052)
#define CT_errorBadName                                     __CTErrorSym(0x053)
#define CT_errorInvalidCallState                            __CTErrorSym(0x054)
#define CT_errorNoConnections                               __CTErrorSym(0x055)
#define CT_errorBadSide                                     __CTErrorSym(0x056)
#define CT_errorResourcesUnavailable                        __CTErrorSym(0x057)
#define CT_errorUnableToHandoff                             __CTErrorSym(0x058)
#define CT_errorNoDeviceAvailable                           __CTErrorSym(0x059)
#define CT_errorNoRuleMatched                               __CTErrorSym(0x05A)
#define CT_errorNoConsultationCall                          __CTErrorSym(0x05B)
#define CT_errorCallDropped                                 __CTErrorSym(0x05C)
#define CT_errorNoRequests                                  __CTErrorSym(0x05D)
#define CT_errorBadProfile                                  __CTErrorSym(0x05E)
#define CT_errorBadObjectList                               __CTErrorSym(0x05F)
#define CT_errorBadContext                                  __CTErrorSym(0x060)
#define CT_errorIncorrectContext                            __CTErrorSym(0x061)
#define CT_errorNoExists                                    __CTErrorSym(0x062)
#define CT_errorSignalID                                    __CTErrorSym(0x063)
#define CT_errorInvalidProfileName                          __CTErrorSym(0x064)
#define CT_errorASRFULL                                     __CTErrorSym(0x065)
#define CT_errorLINEERROR                                   __CTErrorSym(0x066)
#define CT_errorEndOfKey                                    __CTErrorSym(0x067)
#define CT_errorBadMemory                                   __CTErrorSym(0x068)
#define CT_errorKeyExists				    __CTErrorSym(0x069)
#define CT_errorBadStatus				    __CTErrorSym(0x06A)
#define CT_errorUnallocatedNumber            __CTSUNTEKErrorSym(0x06c)
/////////////////////////////////////////////////////////////////////////////
#define __CTSUNTEKErrorSym(item)             CTsym_Build( CT_objERROR,\
							  CT_vendSUNTEK,\
							  (item))
#define CT_errorQueueInvaliable      __CTSUNTEKErrorSym(0x001)
#define CT_errorPutQueueMsg          __CTSUNTEKErrorSym(0x002)
#define CT_errorShmInvaliable        __CTSUNTEKErrorSym(0x003)
#define CT_errorCreateThread		 __CTSUNTEKErrorSym(0x004)
#define CT_errorNullData			 __CTSUNTEKErrorSym(0x005)
#define CT_errorGetQueueMsg	   		 __CTSUNTEKErrorSym(0x006)
#define CT_errorAccept				 __CTSUNTEKErrorSym(0x007)
#define CT_errorDisconnect         	 __CTSUNTEKErrorSym(0x008)
#define CT_errorBadReceiver          __CTSUNTEKErrorSym(0x009)
#define CT_errorConnect  	   	     __CTSUNTEKErrorSym(0x00A)
#define CT_errorTCPRegister          __CTSUNTEKErrorSym(0x00B)

#define CT_errorFAIL			     __CTSUNTEKErrorSym(0x00C)
#define CT_errorSessionFree                  __CTSUNTEKErrorSym(0x00D) //Walker
//-------------------   add by zg  10/22/98
#define CT_errorMsgQueueWarn         __CTSUNTEKErrorSym(0x00E)
#define CT_errorQUEUEFULL			__CTSUNTEKErrorSym(0x010)
#define CT_errorTCBPAUSE			__CTSUNTEKErrorSym(0x011)
#define CT_errorTCBNOTREADY			__CTSUNTEKErrorSym(0x012)
#define CT_errorTCBNOTFOUND			__CTSUNTEKErrorSym(0x013)
//-------------------   add by hxb  2002.04.05
#define CT_errorOpenDev				__CTSUNTEKErrorSym(0x014)
#define CT_errorGetXmitSlot			__CTSUNTEKErrorSym(0x015)
#define CT_errorWaitCall			__CTSUNTEKErrorSym(0x016)
#define CT_errorResetLine			__CTSUNTEKErrorSym(0x017)
//-------------------   add by oroming  2007.06.14
#define CT_errorDATATOOLONG			__CTSUNTEKErrorSym(0x018)

///////////////////////////
/*****container error*****/
///////////////////////////
#define CT_errorContOpen                     __CTSUNTEKErrorSym(0x051)
#define CT_errorContBadFormat                __CTSUNTEKErrorSym(0x052)
#define CT_errorContEmpty                    __CTSUNTEKErrorSym(0x053)
#define CT_errorContNoRoom                   __CTSUNTEKErrorSym(0x054)
#define CT_errorContLock                     __CTSUNTEKErrorSym(0x055)
#define CT_errorContBadHeader                __CTSUNTEKErrorSym(0x056)
#define CT_errorContNotReaded                __CTSUNTEKErrorSym(0x057)
#define CT_errorContIndexOutofBound          __CTSUNTEKErrorSym(0x058)
#define CT_errorContProtected                __CTSUNTEKErrorSym(0x059)
#define CT_errorContNotFound                 __CTSUNTEKErrorSym(0x060)
#define CT_errorInValidOperate               __CTSUNTEKErrorSym(0x061)
#define CT_errorContNotEmpty                 __CTSUNTEKErrorSym(0x062)

#define CT_errorBadParmPriRscNotExist		     __CTSUNTEKErrorSym(0x0070)
#define CT_errorBadParmSessionID	     __CTSUNTEKErrorSym(0x0071)
#define CT_errorBadParmRscRepeat	     __CTSUNTEKErrorSym(0x0072)
#define CT_errorSpcAlloc		     __CTSUNTEKErrorSym(0x0073)
#define CT_errorNoPriRscInGroup		     __CTSUNTEKErrorSym(0x0074)
#define CT_errorRscInsert		     __CTSUNTEKErrorSym(0x0075)
#define CT_errorIntendToReleasePriRsc	     __CTSUNTEKErrorSym(0x0076)

#define CT_errorRscNotFound		     __CTSUNTEKErrorSym(0x0077)
#define CT_errorSpcConnect		     __CTSUNTEKErrorSym(0x0078)
#define CT_errorNoMixFileInMem		    __CTSUNTEKErrorSym(0x0079)
#define CT_errorHardWareOperate	     __CTSUNTEKErrorSym(0x0070)

#define CT_errorRscHandleEvent		     __CTSUNTEKErrorSym(0x0069)

#define CT_errorMediaHandleEvent	     __CTSUNTEKErrorSym(0x0068)

#define CT_errorSpcHandleEvent		     __CTSUNTEKErrorSym(0x0067)

#define CT_errorSpcStop			     __CTSUNTEKErrorSym(0x0066)

#define CT_errorDeviceIOError                __CTSUNTEKErrorSym(0x081)
#define CT_errorLoopCurrentOff               __CTSUNTEKErrorSym(0x082)
#define CT_errorErrorEventHappened           __CTSUNTEKErrorSym(0x083)
#define CT_errorBadEventBlock                __CTSUNTEKErrorSym(0x084)
#define CT_errorUnknownEvent                 __CTSUNTEKErrorSym(0x085)
#define CT_errorUserStopIt                   __CTSUNTEKErrorSym(0x086)
#define CT_errorMaxSilencePassed	     __CTSUNTEKErrorSym(0x087)

/*****************************************************************************
 * Error Data Used by Authen - Walker 98-02-27
 *****************************************************************************/

#define CT_errorNoData                       __CTSUNTEKErrorSym(0x100)
#define CT_errorGetCellData                  __CTSUNTEKErrorSym(0x101)
#define CT_errorPutCellData                  __CTSUNTEKErrorSym(0x102)

/******************************************************************************
 *    Definitions of well known keys.                                    
 *****************************************************************************/

#define __CTAnySym(item)               CTsym_Build( CT_objANY,\
                                                    CT_vendECTF,\
                                                    (item))                

#define Any_ECTF_Null                                      __CTAnySym(0x000 )
#define Any_ECTF_Standard                                  __CTAnySym(0x100 )
#define Any_ECTF_Stop                                      __CTAnySym(0x101 )
#define Any_ECTF_Duration                                  __CTAnySym(0x102 )


/******************************************************************************
 * Redundant definitions - temporary
 *****************************************************************************/
                                                                         
#define CT_symbolNULL                  Any_ECTF_Null                     
                                                                         
                                                                         
/******************************************************************************
 *    KV Set Reserved Keys                                               
 *****************************************************************************/
                                                                         
#define __CTKVSSym(item)               CTsym_Build( CT_objKVSET,\
                                                    CT_vendECTF,\
                                                    (item))                
                                                                         
#define KVS_ECTF_FirstKey                                     __CTKVSSym(0x000)
#define KVS_ECTF_EOKeys                                       __CTKVSSym(0x001)


/******************************************************************************
 *    Connection symbols.                                                
 *****************************************************************************/
                                                                         
#define __CTConnSym(item)              CTsym_Build( CT_objCONNECTION,\
                                                    CT_vendECTF,\
                                                    (item) )               
                                                                         
#define Conn_ECTF_Create                                     __CTConnSym(0x000)
#define Conn_ECTF_GetParameters                              __CTConnSym(0x001)
#define Conn_ECTF_Destroy                                    __CTConnSym(0x002)
#define Conn_ECTF_Make                                       __CTConnSym(0x003)
#define Conn_ECTF_SetParameters                              __CTConnSym(0x004)
#define Conn_ECTF_Break                                      __CTConnSym(0x005)
#define Conn_ECTF_Directionality                             __CTConnSym(0x006)
#define Conn_ECTF_ToTarget                                   __CTConnSym(0x007)
#define Conn_ECTF_FromTarget                                 __CTConnSym(0x008)
#define Conn_ECTF_Default                                    __CTConnSym(0x009)
#define Conn_ECTF_ConnectionHandle                           __CTConnSym(0x00A)
#define Conn_ECTF_Parms                                      __CTConnSym(0x00B)
#define Conn_ECTF_ConnType                                   __CTConnSym(0x00C)
#define Conn_ECTF_Left                                       __CTConnSym(0x00D)
#define Conn_ECTF_Right                                      __CTConnSym(0x00E)
#define Conn_ECTF_ConnectTo                                  __CTConnSym(0x00F)
#define Conn_ECTF_Connect                                    __CTConnSym(0x010)
#define Conn_ECTF_Disconnect                                 __CTConnSym(0x011)

//following was 0x012. Conn_ECTF_ConnectToGroup now same as Conn_ECTF_Create
#define Conn_ECTF_ConnectToGroup                             __CTConnSym(0x000)
//following was 0x013. Conn_ECTF_DisconnectFromGroup now same as Conn_ECTF_Destroy
#define Conn_ECTF_DisconnectFromGroup                        __CTConnSym(0x002)

#define Conn_ECTF_UniDirectional                             __CTConnSym(0x014)
#define Conn_ECTF_Enabled                                    __CTConnSym(0x015)
#define Conn_ECTF_Side                                       __CTConnSym(0x016)

                                                                         
/******************************************************************************
 *    Symbol symbols.                                                    
 *****************************************************************************/
                                                                         
#define __CTSymbolSym(item)            CTsym_Build( CT_objSYMBOL,\
                                                    CT_vendECTF,\
                                                    (item) )               
                                                                         
#define Symbol_ECTF_LoadTable                              __CTSymbolSym(0x001)	


/******************************************************************************
 *    SCR symbols.
 *****************************************************************************/

#define __CTSCRSym(item)               CTsym_Build( CT_objSCR,\
						    CT_vendECTF,\
						    (item) )

#define SCR_ECTF_ASI                                          __CTSCRSym(0x001)
#define SCR_ECTF_Timeout                                      __CTSCRSym(0x002)
#define SCR_ECTF_ParmList                                     __CTSCRSym(0x003)
#define SCR_ECTF_HandMeOff                                    __CTSCRSym(0x004)
#define SCR_ECTF_Tag                                          __CTSCRSym(0x005)
#define SCR_ECTF_DropCall                                     __CTSCRSym(0x006)
#define SCR_ECTF_AnswerCall                                   __CTSCRSym(0x007)
#define SCR_ECTF_HandOff                                      __CTSCRSym(0x008)
#define SCR_ECTF_MakeConsultationCall                         __CTSCRSym(0x009)
#define SCR_ECTF_UnreceivedCount                              __CTSCRSym(0x00A)
#define SCR_ECTF_DestAddress                                  __CTSCRSym(0x00B)
#define SCR_ECTF_OrigGroup                                    __CTSCRSym(0x00C)
#define SCR_ECTF_DestGroup                                    __CTSCRSym(0x00D)
#define SCR_ECTF_Config                                       __CTSCRSym(0x00E)
#define SCR_ECTF_Group                                        __CTSCRSym(0x00F)
#define SCR_ECTF_SessionAddr                                  __CTSCRSym(0x010)
#define SCR_ECTF_MakeCall                                     __CTSCRSym(0x011)
#define SCR_ECTF_TransferCall                                 __CTSCRSym(0x012)
#define SCR_ECTF_RequestGroup                                 __CTSCRSym(0x013)
#define SCR_ECTF_AdvertCount                                  __CTSCRSym(0x014)
#define SCR_ECTF_AppProfile                                   __CTSCRSym(0x015)
#define SCR_ECTF_GroupConfig                                  __CTSCRSym(0x016)
#define SCR_ECTF_GroupSet                                     __CTSCRSym(0x017)
#define SCR_ECTF_AppProfName                                  __CTSCRSym(0x018)
#define SCR_ECTF_ASIName                                      __CTSCRSym(0x019)
#define SCR_ECTF_OrigAddress                                  __CTSCRSym(0x01A)
#define SCR_ECTF_SendMessage                                  __CTSCRSym(0x01B)
#define SCR_ECTF_NumRings                                     __CTSCRSym(0x01C)

/******************************************************************************
 *    CCR symbols.
 *****************************************************************************/

#define __CTCCRSym(item)               CTsym_Build( CT_objCCR,\
						    CT_vendECTF,\
						    (item) )

#define CCR_ECTF_ResClass                                     __CTCCRSym(0x001)
#define CCR_ECTF_Active                                       __CTCCRSym(0x002)
#define CCR_ECTF_Idle                                         __CTCCRSym(0x003)
#define CCR_ECTF_Hold                                         __CTCCRSym(0x004)
#define CCR_ECTF_ProviderType                                 __CTCCRSym(0x005)
#define CCR_ECTF_ServiceProviderId                            __CTCCRSym(0x006)
#define CCR_ECTF_DeviceName                                   __CTCCRSym(0x007)
#define CCR_ECTF_State                                        __CTCCRSym(0x008)
#define CCR_ECTF_NonIdleTime                                  __CTCCRSym(0x009)
#define CCR_ECTF_StateChange                                  __CTCCRSym(0x010)


/******************************************************************************
 *    Message symbols.
 *****************************************************************************/
#define __CTMsgSym(item)               CTsym_Build( CT_objMESSAGE,\
                                                    CT_vendECTF,\
                                                    (item))

#define Message_ECTF_SessionID                               __CTMsgSym (0x000)       
#define Message_ECTF_EventID                                 __CTMsgSym (0x001)       
#define Message_ECTF_Status                                  __CTMsgSym (0x002)       
#define Message_ECTF_Error                                   __CTMsgSym (0x003)       
#define Message_ECTF_SubError                                __CTMsgSym (0x004)       
#define Message_ECTF_EventQualifier                          __CTMsgSym (0x005)
#define Message_ECTF_ObjectID                                __CTMsgSym (0x006)
#define Message_ECTF_ObjectClass                             __CTMsgSym (0x007)
#define Message_ECTF_TransactionID                           __CTMsgSym (0x008)
      

/******************************************************************************
 *    Session symbols.
 *****************************************************************************/
#define __CTSessSym(item)              CTsym_Build( CT_objSESSION,\
                                                    CT_vendECTF,\
                                                    (item))

#define Session_ECTF_ServerName                           __CTSessSym ( 0x000 )
#define Session_ECTF_AuthType                             __CTSessSym ( 0x001 )
#define Session_ECTF_AuthToken                            __CTSessSym ( 0x002 )
#define Session_ECTF_UserID                               __CTSessSym ( 0x003 )
#define Session_ECTF_Password                             __CTSessSym ( 0x004 )
#define Session_ECTF_ParmList                             __CTSessSym ( 0x005 )
#define Session_ECTF_ProfileName                          __CTSessSym ( 0x006 )
#define Session_ECTF_StopTransactionID                    __CTSessSym ( 0x007 )
#define Session_ECTF_Create                               __CTSessSym ( 0x008 )
#define Session_ECTF_Destroy                              __CTSessSym ( 0x009 )
#define Session_ECTF_GetParameters                        __CTSessSym ( 0x00A )
#define Session_ECTF_SetParameters                        __CTSessSym ( 0x00B )
#define Session_ECTF_Stop                                 __CTSessSym ( 0x00C )
#define Session_ECTF_LinkDown                             __CTSessSym ( 0x00D )
#define Session_ECTF_Register                             __CTSessSym ( 0x00E )
#define Session_ECTF_FindService                          __CTSessSym ( 0x00F )
#define Session_ECTF_UnregisterService                    __CTSessSym ( 0x010 )
#define Session_ECTF_SendMessage                          __CTSessSym ( 0x011 )
#define Session_ECTF_OSU                                  __CTSessSym ( 0x012 )
#define Session_DLGC_Admin                                __CTSessSym ( 0x017 )
#define Session_ECTF_Group                                __CTSessSym ( 0x018 )
#define Session_ECTF_ReceiveGroup                         __CTSessSym ( 0x019 )
#define Session_DLGC_Address                              __CTSessSym ( 0x01A )
#define Session_DLGC_EmergencyShutdown                    __CTSessSym ( 0x01B )
#define Session_DLGC_NormalShutdown                       __CTSessSym ( 0x01C )
#define Session_ECTF_SourceAddress                        __CTSessSym ( 0x01D )
#define Session_DLGC_DestroySession                       __CTSessSym ( 0x01E )
#define Session_ECTF_ACT                                  __CTSessSym ( 0x01F )

/******************************************************************************
 *    Container symbols.
 *****************************************************************************/
#define __CTContSym( item )            CTsym_Build( CT_objCONTAINER,\
						    CT_vendECTF,\
						    (item) )

#define Container_ECTF_StreamHandle                          __CTContSym(0x000)
#define Container_ECTF_WriteContents                         __CTContSym(0x001)
#define Container_ECTF_AccessMode                            __CTContSym(0x002)
#define Container_ECTF_ChangeMode                            __CTContSym(0x003)
#define Container_ECTF_Flags                                 __CTContSym(0x004)
#define Container_ECTF_Name                                  __CTContSym(0x005)
#define Container_ECTF_CloseObject                           __CTContSym(0x006)
#define Container_ECTF_Options                               __CTContSym(0x007)
#define Container_ECTF_Copy                                  __CTContSym(0x009)
#define Container_ECTF_InputParameters                       __CTContSym(0x00A)
#define Container_ECTF_Create                                __CTContSym(0x00B)
#define Container_ECTF_Destroy                               __CTContSym(0x00D)
#define Container_ECTF_GetObjectList                         __CTContSym(0x00E)
#define Container_ECTF_GetParameters                         __CTContSym(0x00F)
#define Container_ECTF_OpenObject                            __CTContSym(0x010)
#define Container_ECTF_ReadSize                              __CTContSym(0x011)
#define Container_ECTF_Seek                                  __CTContSym(0x012)
#define Container_ECTF_SeekSize                              __CTContSym(0x013)
#define Container_ECTF_Rename                                __CTContSym(0x014)
#define Container_ECTF_Data                                  __CTContSym(0x015)
#define Container_ECTF_MediaInfo                             __CTContSym(0x016)
#define Container_ECTF_WriteSize                             __CTContSym(0x017)
#define Container_ECTF_SetParameters                         __CTContSym(0x018)
#define Container_ECTF_TargetName                            __CTContSym(0x019)
#define Container_ECTF_OutputParameters                      __CTContSym(0x01A)
#define Container_ECTF_InputBuffer                           __CTContSym(0x01B)
#define Container_ECTF_ReadContents                          __CTContSym(0x01C)
#define Container_ECTF_ObjectList                            __CTContSym(0x01D)
#define Container_ECTF_DataStreamHandle                      __CTContSym(0x01E)
#define Container_ECTF_BytesWritten                          __CTContSym(0x01F)
#define Container_ECTF_FileStrategy                          __CTContSym(0x020)
#define Container_ECTF_Created                               __CTContSym(0x021)
#define Container_ECTF_LastChanged                           __CTContSym(0x022)
#define Container_ECTF_FileName                              __CTContSym(0x023)
#define Container_ECTF_Reference                             __CTContSym(0x024)
#define Container_ECTF_Size                                  __CTContSym(0x025)
#define Container_ECTF_Strategy                              __CTContSym(0x026)
#define Container_ECTF_6kADPCM                               __CTContSym(0x027)
#define Container_ECTF_8kADPCM                               __CTContSym(0x028)
#define Container_ECTF_11kADPCM                              __CTContSym(0x029)
#define Container_ECTF_6kMuLawPCM                            __CTContSym(0x02A)
#define Container_ECTF_8kMuLawPCM                            __CTContSym(0x02B)
#define Container_ECTF_11kMuLawPCM                           __CTContSym(0x02C)
#define Container_ECTF_6kALawPCM                             __CTContSym(0x02D)
#define Container_ECTF_8kALawPCM                             __CTContSym(0x02E)
#define Container_ECTF_11kALawPCM                            __CTContSym(0x02F)
#define Container_ECTF_6k8BitLinear                          __CTContSym(0x030)
#define Container_ECTF_8k8BitLinear                          __CTContSym(0x031)
#define Container_ECTF_11k8BitLinear                         __CTContSym(0x032)
#define Container_ECTF_ADSI                                  __CTContSym(0x033)
#define Container_ECTF_TDD                                   __CTContSym(0x034)
#define Container_ECTF_VoiceView                             __CTContSym(0x035)
#define Container_ECTF_EnglishText                           __CTContSym(0x036)
#define Container_ECTF_GermanText                            __CTContSym(0x037)
#define Container_ECTF_SpanishText                           __CTContSym(0x038)
#define Container_ECTF_FrenchText                            __CTContSym(0x039)
#define Container_ECTF_DutchText                             __CTContSym(0x03A)
#define Container_ECTF_KoreanText                            __CTContSym(0x03B)
#define Container_ECTF_AsciiText                             __CTContSym(0x03C)
#define Container_ECTF_Offset                                __CTContSym(0x03D)
#define Container_ECTF_Container                             __CTContSym(0x03E)
#define Container_ECTF_MediaType                             __CTContSym(0x044)
#define Container_ECTF_DefaultMediaType                      __CTContSym(0x045)
#define Container_ECTF_AcceptableMediaTypes                  __CTContSym(0x046)
#define Container_ECTF_CreateObject                          __CTContSym(0x04A)
#define Container_ECTF_Commit                                __CTContSym(0x04B)

/******************************************************************************
 *    Signal Detector symbols.
 *****************************************************************************/
#define __CTSIGDSym(item)              CTsym_Build( CT_objSIGD,\
						    CT_vendECTF,\
                                                    (item))

#define SIGD_ECTF_RetrieveSignals                            __CTSIGDSym(0x000)
#define SIGD_ECTF_FlushBuffer                                __CTSIGDSym(0x001)
#define SIGD_ECTF_NumSignals                                 __CTSIGDSym(0x002)
#define SIGD_ECTF_Patterns                                   __CTSIGDSym(0x003)
#define SIGD_ECTF_OutputBuffer                               __CTSIGDSym(0x004)
#define SIGD_ECTF_SignalBuffer                               __CTSIGDSym(0x005)
#define SIGD_ECTF_ResClass                                   __CTSIGDSym(0x006)
#define SIGD_ECTF_Pattern1                                   __CTSIGDSym(0x008)
#define SIGD_ECTF_Pattern2                                   __CTSIGDSym(0x009)
#define SIGD_ECTF_Pattern3                                   __CTSIGDSym(0x00A)
#define SIGD_ECTF_Pattern4                                   __CTSIGDSym(0x00B)
#define SIGD_ECTF_Pattern5                                   __CTSIGDSym(0x00C)
#define SIGD_ECTF_Pattern6                                   __CTSIGDSym(0x00D)
#define SIGD_ECTF_Pattern7                                   __CTSIGDSym(0x00E)
#define SIGD_ECTF_Pattern8                                   __CTSIGDSym(0x00F)
#define SIGD_ECTF_Pattern9                                   __CTSIGDSym(0x010)
#define SIGD_ECTF_Pattern10                                  __CTSIGDSym(0x011)
#define SIGD_ECTF_Pattern11                                  __CTSIGDSym(0x012)
#define SIGD_ECTF_Pattern12                                  __CTSIGDSym(0x013)
#define SIGD_ECTF_Pattern13                                  __CTSIGDSym(0x014)
#define SIGD_ECTF_Pattern14                                  __CTSIGDSym(0x015)
#define SIGD_ECTF_Pattern15                                  __CTSIGDSym(0x016)
#define SIGD_ECTF_Pattern16                                  __CTSIGDSym(0x017)
#define SIGD_ECTF_DiscardOldest                              __CTSIGDSym(0x018)
#define SIGD_ECTF_BufferSize                                 __CTSIGDSym(0x019)
#define SIGD_ECTF_InitialTimeout                             __CTSIGDSym(0x01A)
#define SIGD_ECTF_IntersigTimeout                            __CTSIGDSym(0x01B)
#define SIGD_ECTF_SignalDetected                             __CTSIGDSym(0x01F)
#define SIGD_ECTF_Stop                                       __CTSIGDSym(0x020)
#define SIGD_ECTF_Mode                                       __CTSIGDSym(0x021)
#define SIGD_ECTF_EnabledEvents                              __CTSIGDSym(0x022)
#define SIGD_ECTF_Buffering                                  __CTSIGDSym(0x023)
#define SIGD_DLGC_Consume                                    __CTSIGDSym(0x024)
#define SIGD_ECTF_PatternCount                               __CTSIGDSym(0x025)
#define SIGD_ECTF_Duration                                   __CTSIGDSym(0x026)
#define SIGD_ECTF_Idle                                       __CTSIGDSym(0x027)
#define SIGD_ECTF_Detecting                                  __CTSIGDSym(0x028)
#define SIGD_DLGC_SignalID                                   __CTSIGDSym(0x02A)
#define SIGD_DLGC_PatternSyntax                              __CTSIGDSym(0x02B)


/******************************************************************************
 *    Group symbols.
 *****************************************************************************/
#define __CTGrpSym(item)            CTsym_Build( CT_objGROUP,\
                                                 CT_vendECTF,\
                                                 (item))

#define Group_ECTF_ACT                                      __CTGrpSym( 0x001 )
#define Group_ECTF_Arrival                                  __CTGrpSym( 0x002 )
#define Group_ECTF_Cause                                    __CTGrpSym( 0x003 )
#define Group_ECTF_Configure                                __CTGrpSym( 0x004 )
#define Group_ECTF_Create                                   __CTGrpSym( 0x005 )
#define Group_ECTF_Destroy                                  __CTGrpSym( 0x006 )
#define Group_ECTF_GetGroupInfo                             __CTGrpSym( 0x007 )
#define Group_ECTF_GetParameterNames                        __CTGrpSym( 0x008 )
#define Group_ECTF_GetParameterRange                        __CTGrpSym( 0x009 )
#define Group_ECTF_GetParameters                            __CTGrpSym( 0x00A )
#define Group_ECTF_GetRTC                                   __CTGrpSym( 0x00B )
#define Group_ECTF_Group                                    __CTGrpSym( 0x00C ) 
#define Group_ECTF_GroupConfig                              __CTGrpSym( 0x00D )
#define Group_ECTF_GroupInfo                                __CTGrpSym( 0x00E )
#define Group_ECTF_GroupSet                                 __CTGrpSym( 0x00F )
#define Group_ECTF_Handoff                                  __CTGrpSym( 0x010 )
#define Group_ECTF_Keys                                     __CTGrpSym( 0x011 )
#define Group_ECTF_KVSet                                    __CTGrpSym( 0x012 )
#define Group_ECTF_NewOwner                                 __CTGrpSym( 0x013 )
#define Group_ECTF_ParameterNames                           __CTGrpSym( 0x014 )
#define Group_ECTF_ParameterRangeSet                        __CTGrpSym( 0x015 )
#define Group_ECTF_Parameters                               __CTGrpSym( 0x016 )
#define Group_ECTF_ParmList                                 __CTGrpSym( 0x017 )
#define Group_ECTF_PutGroupInfo                             __CTGrpSym( 0x018 )
#define Group_ECTF_Retrieve                                 __CTGrpSym( 0x019 )
#define Group_ECTF_Return                                   __CTGrpSym( 0x01A )
#define Group_ECTF_Returned                                 __CTGrpSym( 0x01B )
#define Group_ECTF_RTC                                      __CTGrpSym( 0x01C )
#define Group_ECTF_RTCValidate                              __CTGrpSym( 0x01D )
#define Group_ECTF_SetParameters                            __CTGrpSym( 0x01E )
#define Group_ECTF_SetRTC                                   __CTGrpSym( 0x01F )
#define Group_ECTF_Stop                                     __CTGrpSym( 0x020 )
#define Group_ECTF_Tag                                      __CTGrpSym( 0x021 )
#define Group_ECTF_Timeout                                  __CTGrpSym( 0x022 )
#define Group_ECTF_Unwind                                   __CTGrpSym( 0x023 )
#define Group_ECTF_Session                                  __CTGrpSym( 0x024 )
#define Group_ECTF_DestroyGroups                            __CTGrpSym( 0x027 )
#define Group_ECTF_RTCTrigger                               __CTGrpSym( 0x028 )
#define Group_ECTF_ConditionInfo                            __CTGrpSym( 0x029 )
#define Group_ECTF_WaitEvent                                __CTGrpSym( 0x02A )
#define Group_ECTF_ASI                                      __CTGrpSym( 0x02B )
#define Group_ECTF_Destroyed                                __CTGrpSym( 0x02C )
#define Group_ECTF_Retrieved                                __CTGrpSym( 0x02D )
#define Group_ECTF_ProfileName                              __CTGrpSym( 0x02E )
#define Group_ECTF_HandToMe                                 __CTGrpSym( 0x02F )
#define Group_ECTF_OutputParameters                         __CTGrpSym( 0x030 )
#define Group_ECTF_Command                                  __CTGrpSym( 0x031 )
#define Group_ECTF_TriggerInfo                              __CTGrpSym( 0x032 )
#define Group_ECTF_ResourceName                             __CTGrpSym( 0x033 )
#define Group_ECTF_ArbitrationScheme                        __CTGrpSym( 0x034 )
#define Group_ECTF_FailingRTC                               __CTGrpSym( 0x035 )


/******************************************************************************
 *    Signal Generator Symbols.
 *****************************************************************************/
#define __CTSIGGSym(item)              CTsym_Build( CT_objSIGG,\
                                                    CT_vendECTF,\
                                                    (item))

#define SIGG_ECTF_SendSignals                                __CTSIGGSym(0x000)
#define SIGG_ECTF_SignalList                                 __CTSIGGSym(0x001)
#define SIGG_ECTF_ResClass                                   __CTSIGGSym(0x002)
#define SIGG_ECTF_Stop                                       __CTSIGGSym(0x004)


/******************************************************************************
 *    Player symbols.
 *****************************************************************************/
#define __CTPlayerSym(item)            CTsym_Build( CT_objPLAYER,\
                                                    CT_vendECTF,\
                                                    (item))

#define Player_ECTF_Play                                   __CTPlayerSym(0x000)
#define Player_ECTF_TvmList                                __CTPlayerSym(0x001)
#define Player_ECTF_Offset                                 __CTPlayerSym(0x002)
#define Player_ECTF_ResClass                               __CTPlayerSym(0x003)
#define Player_ECTF_Speed                                  __CTPlayerSym(0x004)
#define Player_ECTF_Volume                                 __CTPlayerSym(0x005)
#define Player_ECTF_Pause                                  __CTPlayerSym(0x006)
#define Player_ECTF_Resume                                 __CTPlayerSym(0x007)
#define Player_ECTF_VolumeChange                           __CTPlayerSym(0x008)
#define Player_ECTF_SpeedChange                            __CTPlayerSym(0x009)
#define Player_ECTF_Marker                                 __CTPlayerSym(0x00A)
#define Player_ECTF_EOD                                    __CTPlayerSym(0x00B)
#define Player_ECTF_Coder                                  __CTPlayerSym(0x00C)
#define Player_ECTF_EnabledEvents                          __CTPlayerSym(0x00D)
#define Player_ECTF_StartPaused                            __CTPlayerSym(0x00E)
#define Player_ECTF_CoderTypes                             __CTPlayerSym(0x00F)
#define Player_ECTF_Duration                               __CTPlayerSym(0x010)
#define Player_ECTF_SpeedUp                                __CTPlayerSym(0x011)
#define Player_ECTF_SpeedDown                              __CTPlayerSym(0x012)
#define Player_ECTF_VolumeUp                               __CTPlayerSym(0x013)
#define Player_ECTF_VolumeDown                             __CTPlayerSym(0x014)
#define Player_ECTF_Stop                                   __CTPlayerSym(0x015)
#define Player_ECTF_ChangeType                             __CTPlayerSym(0x016)
#define Player_ECTF_TVM                                    __CTPlayerSym(0x017)
#define Player_ECTF_ToggleSpeed                            __CTPlayerSym(0x018)
#define Player_ECTF_NormalSpeed                            __CTPlayerSym(0x019)
#define Player_ECTF_ToggleVolume                           __CTPlayerSym(0x01A)
#define Player_ECTF_NormalVolume                           __CTPlayerSym(0x01B)
#define Player_ECTF_JumpForward                            __CTPlayerSym(0x01C)
#define Player_ECTF_JumpBackward                           __CTPlayerSym(0x01D)
#define Player_ECTF_Adjustment                             __CTPlayerSym(0x01E)
#define Player_ECTF_AdjustSpeed                            __CTPlayerSym(0x01F)
#define Player_ECTF_AdjustVolume                           __CTPlayerSym(0x020)
#define Player_ECTF_PlayStarted                            __CTPlayerSym(0x021)
#define Player_ECTF_JumpIncrement                          __CTPlayerSym(0x022)
#define Player_ECTF_Jump                                   __CTPlayerSym(0x023)
#define Player_ECTF_PauseTermination                       __CTPlayerSym(0x024)




/******************************************************************************
 *    Recorder symbols.
 *****************************************************************************/
#define __CTRecorderSym(item)          CTsym_Build( CT_objRECORDER,\
                                                    CT_vendECTF,\
						    (item))

#define Recorder_ECTF_Record                             __CTRecorderSym(0x000)
#define Recorder_ECTF_Tvm                                __CTRecorderSym(0x001)
#define Recorder_ECTF_ResClass                           __CTRecorderSym(0x002)
#define Recorder_ECTF_Pause                              __CTRecorderSym(0x003)
#define Recorder_ECTF_Resume                             __CTRecorderSym(0x004)
#define Recorder_ECTF_Coder                              __CTRecorderSym(0x005)
#define Recorder_ECTF_Stop                               __CTRecorderSym(0x006)
#define Recorder_ECTF_Beep                               __CTRecorderSym(0x007)
#define Recorder_DLGC_FixedBeep                          __CTRecorderSym(0x008)
#define Recorder_ECTF_EnabledEvents                      __CTRecorderSym(0x009)
#define Recorder_ECTF_Duration                           __CTRecorderSym(0x00A)
#define Recorder_ECTF_StartBeep                          __CTRecorderSym(0x00B)
#define Recorder_ECTF_StartPaused                        __CTRecorderSym(0x00C)
#define Recorder_ECTF_CoderTypes                         __CTRecorderSym(0x00D)
#define Recorder_DLGC_Append                             __CTRecorderSym(0x00E)
#define Recorder_DLGC_AGC                                __CTRecorderSym(0x00F)
#define Recorder_ECTF_BeepLength                         __CTRecorderSym(0x010)
#define Recorder_ECTF_BeepFrequency                      __CTRecorderSym(0x011)
#define Recorder_ECTF_PauseCompression                   __CTRecorderSym(0x012)
#define Recorder_ECTF_PauseThreshold                     __CTRecorderSym(0x013)
#define Recorder_ECTF_SilenceTerminationOn               __CTRecorderSym(0x014)
#define Recorder_ECTF_SilenceThreshold                   __CTRecorderSym(0x015)
#define Recorder_ECTF_Silence                            __CTRecorderSym(0x016)
#define Recorder_ECTF_PauseCompressionOn                 __CTRecorderSym(0x017)

/******************************************************************************
 *    EVENT TRIGGER symbols.
 *****************************************************************************/
#define __CTTRISym(item)	CTsym_Build(CT_objTRIGGER,\
					    CT_vendSUNTEK,\
					    (item) )
#define Trigger_SUNTEK_ChannelHandle		             __CTTRISym(0x001)
#define Trigger_SUNTEK_EventType			     __CTTRISym(0x002)
#define Trigger_SUNTEK_DataLength			     __CTTRISym(0x003)
#define Trigger_SUNTEK_EventData			     __CTTRISym(0x004)
#define Trigger_SUNTEK_TermReason 			     __CTTRISym(0x005)
#define Trigger_SUNTEK_MetaEventData			 __CTTRISym(0x006)		// Added by hxb (2002.04.04)
//*************************************************************************
//Public keys
//*************************************************************************
//base value for Switch Control defined keys
#define __CTkvs_PUBLIC(item)  	CTsym_Build( CT_objPUBLIC,\
				             CT_vendSUNTEK,\
					     (item) )

//KVSet in messages sent by Switch Control
#define PUBLIC_SUNTEK_MessageType                __CTkvs_PUBLIC(0x0000)  
#define PUBLIC_SUNTEK_NodeID                     __CTkvs_PUBLIC(0x0001)
#define PUBLIC_SUNTEK_SpanID                     __CTkvs_PUBLIC(0x0002)
#define PUBLIC_SUNTEK_Channel                    __CTkvs_PUBLIC(0x0003)
#define PUBLIC_SUNTEK_OrigSpanID                 __CTkvs_PUBLIC(0x0004)
#define PUBLIC_SUNTEK_TermSpanID                 __CTkvs_PUBLIC(0x0005)
#define PUBLIC_SUNTEK_OrigChannel                __CTkvs_PUBLIC(0x0006)
#define PUBLIC_SUNTEK_TermChannel                __CTkvs_PUBLIC(0x0007)
#define PUBLIC_SUNTEK_SpanIDA                    __CTkvs_PUBLIC(0x0008)
#define PUBLIC_SUNTEK_ChannelA                   __CTkvs_PUBLIC(0x0009)
#define PUBLIC_SUNTEK_SpanIDB                    __CTkvs_PUBLIC(0x000a)
#define PUBLIC_SUNTEK_ChannelB                   __CTkvs_PUBLIC(0x000b)
#define PUBLIC_SUNTEK_Status                     __CTkvs_PUBLIC(0x000c)
#define PUBLIC_SUNTEK_Data                       __CTkvs_PUBLIC(0x000d)
#define PUBLIC_SUNTEK_BusyOutAction              __CTkvs_PUBLIC(0x000e)
#define PUBLIC_SUNTEK_BusyOutFlag                __CTkvs_PUBLIC(0x000f)
#define PUBLIC_SUNTEK_Const                      __CTkvs_PUBLIC(0x0010)
#define PUBLIC_SUNTEK_NoLengthData               __CTkvs_PUBLIC(0x0011)
#define PUBLIC_SUNTEK_ICBData                    __CTkvs_PUBLIC(0x0012)
#define PUBLIC_SUNTKE_DataWithLength             __CTkvs_PUBLIC(0x0013)
#define PUBLIC_SUNTEK_Length                     __CTkvs_PUBLIC(0x0014)
#define PUBLIC_SUNTEK_MultiAIB                   __CTkvs_PUBLIC(0x0015)

#define PUBLIC_SUNTEK_CallMode                   __CTkvs_PUBLIC(0x0016)
#define PUBLIC_SUNTEK_ConnectMode                __CTkvs_PUBLIC(0x0017)
#define PUBLIC_SUNTEK_BillFlag                   __CTkvs_PUBLIC(0x0018)
#define PUBLIC_SUNTEK_Caller                     __CTkvs_PUBLIC(0x0019)
#define PUBLIC_SUNTEK_Called                     __CTkvs_PUBLIC(0x001a)
#define PUBLIC_SUNTEK_CallingPartyCategory       __CTkvs_PUBLIC(0x001b)
#define	PUBLIC_SUNTEK_StartTime                  __CTkvs_PUBLIC(0x001c)
#define	PUBLIC_SUNTEK_EndTime                    __CTkvs_PUBLIC(0x001e)
#define	PUBLIC_SUNTEK_NotifyWay                  __CTkvs_PUBLIC(0x001f)
#define	PUBLIC_SUNTEK_NotifyCount                __CTkvs_PUBLIC(0x0020)
#define	PUBLIC_SUNTEK_NotifyInterval             __CTkvs_PUBLIC(0x0021)
#define	PUBLIC_SUNTEK_ScheduleNo                 __CTkvs_PUBLIC(0x0022)
#define	PUBLIC_SUNTEK_ScheduleParam              __CTkvs_PUBLIC(0x0023)
#define	PUBLIC_SUNTEK_TimerID                    __CTkvs_PUBLIC(0x0024)
#define	PUBLIC_SUNTEK_SequenceID                 __CTkvs_PUBLIC(0x0025)
#define	PUBLIC_SUNTEK_ErrorMessage               __CTkvs_PUBLIC(0x0026)
#define	PUBLIC_SUNTEK_HowToLoadProfile           __CTkvs_PUBLIC(0x0027)
#define	PUBLIC_SUNTEK_ProfileName                __CTkvs_PUBLIC(0x0028)
#define PUBLIC_SUNTEK_ReduanceAppName			 __CTkvs_PUBLIC(0x0029)
#define PUBLIC_SUNTEK_ReduanceStatus			 __CTkvs_PUBLIC(0x002A)
#define PUBLIC_SUNTEK_MultiTLV			 __CTkvs_PUBLIC(0x002B)

#define PUBLIC_SUNTEK_ContainerName				 __CTkvs_PUBLIC(0x007f)
#define PUBLIC_SUNTEK_KeepliveFlag				 __CTkvs_PUBLIC(0x0080)
#define PUBLIC_SUNTEK_ExecuteName				 __CTkvs_PUBLIC(0x0081)
#define PUBLIC_SUNTEK_CommonAlertLevel           __CTkvs_PUBLIC(0x0082)
#define PUBLIC_SUNTEK_CommonAlertString          __CTkvs_PUBLIC(0x0083)
#define PUBLIC_SUNTEK_IP                         __CTkvs_PUBLIC(0x0084)
#define PUBLIC_SUNTEK_Port                       __CTkvs_PUBLIC(0x0085)
#define PUBLIC_SUNTEK_SenderModule               __CTkvs_PUBLIC(0x0086)
#define PUBLIC_SUNTEK_ReceiverModule             __CTkvs_PUBLIC(0x0087)
#define PUBLIC_SUNTEK_TotalAdjacentAddress  	 __CTkvs_PUBLIC(0x0088)
#define PUBLIC_SUNTEK_LeavingsNumber			 __CTkvs_PUBLIC(0x0089)
#define PUBLIC_SUNTEK_ConfigData				 __CTkvs_PUBLIC(0x008a)
#define PUBLIC_SUNTEK_StationNo                  __CTkvs_PUBLIC(0x008b)
#define PUBLIC_SUNTEK_Entity                     __CTkvs_PUBLIC(0x008c)
#define PUBLIC_SUNTEK_Severity                   __CTkvs_PUBLIC(0x008d)
#define PUBLIC_SUNTEK_AlarmNumber                __CTkvs_PUBLIC(0x008e)
#define PUBLIC_SUNTEK_AlarmData                  __CTkvs_PUBLIC(0x008f)
#define PUBLIC_SUNTEK_SecondIP					 __CTkvs_PUBLIC(0x0090)
#define PUBLIC_SUNTEK_ApplicationName			 __CTkvs_PUBLIC(0x0091)
#define PUBLIC_SUNTEK_ActiveModule				 __CTkvs_PUBLIC(0x0092)
#define PUBLIC_SUNTEK_Domain					 __CTkvs_PUBLIC(0x0093)
#define PUBLIC_SUNTEK_AdjacentStationNo          __CTkvs_PUBLIC(0x0094)
#define PUBLIC_SUNTEK_CommCenterIP				 __CTkvs_PUBLIC(0x0095)
#define PUBLIC_SUNTEK_CommCenterStationNo		 __CTkvs_PUBLIC(0x0096)
#define PUBLIC_SUNTEK_Version					 __CTkvs_PUBLIC(0x0097)
#define PUBLIC_SUNTEK_ActivedHost				 __CTkvs_PUBLIC(0x0098)
#define PUBLIC_SUNTEK_ReduanceIP				 __CTkvs_PUBLIC(0x0099)
#define PUBLIC_SUNTEK_ReduancePort				 __CTkvs_PUBLIC(0x009a)
#define PUBLIC_SUNTEK_AdjacentIP		         __CTkvs_PUBLIC(0x009b)
#define PUBLIC_SUNTEK_AdjacentPort               __CTkvs_PUBLIC(0x009c)
#define PUBLIC_SUNTEK_AdjacentIP2		         __CTkvs_PUBLIC(0x009d)
#define PUBLIC_SUNTEK_IsAutoAdjusttime		     __CTkvs_PUBLIC(0x009e)
#define PUBLIC_SUNTEK_RequesterCurrentTime	     __CTkvs_PUBLIC(0x009f)
#define PUBLIC_SUNTEK_CurrentTime			     __CTkvs_PUBLIC(0x00a0)
#define PUBLIC_SUNTEK_HWMACAddress			     __CTkvs_PUBLIC(0x00a1)
#define PUBLIC_SUNTEK_ModuleReadyFlag		     __CTkvs_PUBLIC(0x00a2)
#define PUBLIC_SUNTEK_AppVersion				 __CTkvs_PUBLIC(0x00a3)
#define PUBLIC_SUNTEK_MemoryUsage				 __CTkvs_PUBLIC(0x00a4)
#define PUBLIC_SUNTEK_CPUUsage					 __CTkvs_PUBLIC(0x00a5)
#define PUBLIC_SUNTEK_EntityType				 __CTkvs_PUBLIC(0x00a6)
#define PUBLIC_SUNTEK_EntityNo					 __CTkvs_PUBLIC(0x00a7)
#define PUBLIC_SUNTEK_EntityName				 __CTkvs_PUBLIC(0x00a8)
#define PUBLIC_SUNTEK_AlarmType					 __CTkvs_PUBLIC(0x00a9)
#define PUBLIC_SUNTEK_PrivateData				 __CTkvs_PUBLIC(0x00aa)
#define PUBLIC_SUNTEK_TraceLevelThreshold		__CTkvs_PUBLIC(0x00ab)
#define PUBLIC_SUNTEK_AdjacentApplicationName   __CTkvs_PUBLIC(0x00ac)
#define PUBLIC_SUNTEK_StationType			    __CTkvs_PUBLIC(0x00ad)
#define	PUBLIC_SUNTEK_Filename					__CTkvs_PUBLIC(0x00ae)
#define	PUBLIC_SUNTEK_LogContent				__CTkvs_PUBLIC(0x00af)
#define	PUBLIC_SUNTEK_LogLevel					__CTkvs_PUBLIC(0x00b0)
#define	PUBLIC_SUNTEK_NodeName					__CTkvs_PUBLIC(0x00b1)
#define	PUBLIC_SUNTEK_TaskName					__CTkvs_PUBLIC(0x00b2)
//add by oroming for PetraII
#define PUBLIC_SUNTEK_WorkPath					__CTkvs_PUBLIC(0x00b3)
#define PUBLIC_SUNTEK_DependApp					__CTkvs_PUBLIC(0x00b4)
#define PUBLIC_SUNTEK_AppType					__CTkvs_PUBLIC(0x00b5)
#define PUBLIC_SUNTEK_WaitStartTime				__CTkvs_PUBLIC(0x00b6)
#define PUBLIC_SUNTEK_WaitStopTime				__CTkvs_PUBLIC(0x00b7)
#define PUBLIC_SUNTEK_AutoRunFlag				__CTkvs_PUBLIC(0x00b8)
#define PUBLIC_SUNTEK_StartKey					__CTkvs_PUBLIC(0x00b9)
#define PUBLIC_SUNTEK_CmdLine					__CTkvs_PUBLIC(0x00ba)
#define PUBLIC_SUNTEK_LastExitTime				__CTkvs_PUBLIC(0x00bb)
#define PUBLIC_SUNTEK_ProcessID					__CTkvs_PUBLIC(0x00bc)
#define PUBLIC_SUNTEK_ThreadCount				__CTkvs_PUBLIC(0x00bd)
#define PUBLIC_SUNTEK_PingTimeOutCount			__CTkvs_PUBLIC(0x00be)
#define PUBLIC_SUNTEK_SnapshotData				__CTkvs_PUBLIC(0x00bf)
#define PUBLIC_SUNTEK_ModuleName				__CTkvs_PUBLIC(0x00c0)
#define PUBLIC_SUNTEK_SnapshotSeqNo				__CTkvs_PUBLIC(0x00c1)
#define PUBLIC_SUNTEK_VncPassword				__CTkvs_PUBLIC(0x00c2)
#define PUBLIC_SUNTEK_SenderAddress				__CTkvs_PUBLIC(0x00c3)
#define PUBLIC_SUNTEK_ReceiverAddress			__CTkvs_PUBLIC(0x00c4)
#define PUBLIC_SUNTEK_MemoryUsage_InUse			__CTkvs_PUBLIC(0x00c5)
#define PUBLIC_SUNTEK_MemoryUsage_Avail			__CTkvs_PUBLIC(0x00c6)
#define PUBLIC_SUNTEK_MemoryUsage_InUse_PerCent __CTkvs_PUBLIC(0x00c7)
#define PUBLIC_SUNTEK_MemoryUsage_Limit			__CTkvs_PUBLIC(0x00c8)
#define PUBLIC_SUNTEK_HD_DriveName				__CTkvs_PUBLIC(0x00c9)
#define PUBLIC_SUNTEK_HD_DriveType				__CTkvs_PUBLIC(0x00ca)
#define PUBLIC_SUNTEK_HD_VolumnName				__CTkvs_PUBLIC(0x00cb)
#define PUBLIC_SUNTEK_HD_SerialNumber			__CTkvs_PUBLIC(0x00cc)
#define PUBLIC_SUNTEK_HD_FileSystemType			__CTkvs_PUBLIC(0x00cd)
#define PUBLIC_SUNTEK_HD_FreeRatio				__CTkvs_PUBLIC(0x00ce)
#define PUBLIC_SUNTEK_HD_TotalSpace				__CTkvs_PUBLIC(0x00cf)
#define PUBLIC_SUNTEK_HD_FreeSpace				__CTkvs_PUBLIC(0x00d0)
#define PUBLIC_SUNTEK_HD_FormatedTotalSpace		__CTkvs_PUBLIC(0x00d1)
#define PUBLIC_SUNTEK_HD_FormatedFreeSpace		__CTkvs_PUBLIC(0x00d2)

//////////////////////////////////////////////////////////////////////////
//for petra2 trace
//hr	2006.12.05
#define	PUBLIC_SUNTEK_URI						__CTkvs_PUBLIC(0x00d3)
#define PUBLIC_SUNTEK_TraceType					__CTkvs_PUBLIC(0x00d4)
#define PUBLIC_SUNTEK_TraceMessage				__CTkvs_PUBLIC(0x00d5)
//add by orome
#define PUBLIC_SUNTEK_ContainerStatus			__CTkvs_PUBLIC(0x00d6)
#define PUBLIC_SUNTEK_AdjacentDomainName		__CTkvs_PUBLIC(0x00d7)
#define PUBLIC_SUNTEK_WebServiceID				__CTkvs_PUBLIC(0x00d8)
#define PUBLIC_SUNTEK_WebServiceName			__CTkvs_PUBLIC(0x00d9)
#define PUBLIC_SUNTEK_WebServiceTitle			__CTkvs_PUBLIC(0x00da)
#define PUBLIC_SUNTEK_WebServiceDesc			__CTkvs_PUBLIC(0x00db)
#define PUBLIC_SUNTEK_WebServiceMsgID			__CTkvs_PUBLIC(0x00dc)
#define PUBLIC_SUNTEK_WebServiceMsgStr			__CTkvs_PUBLIC(0x00dd)
#define PUBLIC_SUNTEK_WebServiceKeyID			__CTkvs_PUBLIC(0x00de)
#define PUBLIC_SUNTEK_WebServiceKeyStr			__CTkvs_PUBLIC(0x00df)
#define PUBLIC_SUNTEK_WebServiceRequestFlag		__CTkvs_PUBLIC(0x00e0)
#define PUBLIC_SUNTEK_WebServiceOriginalReceiver __CTkvs_PUBLIC(0x00e1)
#define PUBLIC_SUNTEK_XdrStatus					__CTkvs_PUBLIC(0x00e2)

//add by ywb
#define PUBLIC_SUNTEK_NetSummary				__CTkvs_PUBLIC(0x00e3)
#define PUBLIC_SUNTEK_NetAdapter_Descrition		__CTkvs_PUBLIC(0x00e4)
#define PUBLIC_SUNTEK_NetAdapter_InTrafice		__CTkvs_PUBLIC(0x00e5)
#define PUBLIC_SUNTEK_NetAdapter_OutTrafice		__CTkvs_PUBLIC(0x00e6)

#define PUBLIC_SUNTEK_TranInfo_Data		__CTkvs_PUBLIC(0x00e7)
#define PUBLIC_SUNTEK_TranInfo_Count		__CTkvs_PUBLIC(0x00e8)
#define PUBLIC_SUNTEK_TranInfo_Index		__CTkvs_PUBLIC(0x00e9)
#define PUBLIC_SUNTEK_TranInfo_Guid		__CTkvs_PUBLIC(0x00f0)

#define PUBLIC_SUNTEK_PhysicalMemory_Total __CTkvs_PUBLIC(0x00f1)
#define PUBLIC_SUNTEK_PhysicalMemory_Avail __CTkvs_PUBLIC(0x00f2)
#define PUBLIC_SUNTEK_PageingFile_Total __CTkvs_PUBLIC(0x00f3)
#define PUBLIC_SUNTEK_PageingFile_Avail __CTkvs_PUBLIC(0x00f4)
#define PUBLIC_SUNTEK_VirtualMemory_Total __CTkvs_PUBLIC(0x00f5)
#define PUBLIC_SUNTEK_VirtualMemory_Avail __CTkvs_PUBLIC(0x00f6)
#define PUBLIC_SUNTEK_TraninfoTimeStamp __CTkvs_PUBLIC(0x00f7)

//*************************************************************************
//Private keys of SCR
//**************************************************************************
//base value for SCR defined keys
#define __CTkvs_SCR(item)  CTsym_Build(CT_objSCR,CT_vendSUNTEK, (item))

#define SCR_SUNTEK_StationNo                   __CTkvs_SCR(1)
#define SCR_SUNTEK_ASIName                     __CTkvs_SCR(2)
#define SCR_SUNTEK_TotalIncoming	       __CTkvs_SCR(3)
#define SCR_SUNTEK_ValidServer		       __CTkvs_SCR(4)
#define SCR_SUNTEK_StartTime 		       __CTkvs_SCR(5)
#define SCR_SUNTEK_Command		       __CTkvs_SCR(6)
#define SCR_SUNTEK_TraceFileName	       __CTkvs_SCR(7)
#define SCR_SUNTEK_TraceValue		       __CTkvs_SCR(8)
#define SCR_SUNTEK_TraceStatus		       __CTkvs_SCR(9)
#define SCR_SUNTEK_TotalSession		       __CTkvs_SCR(10)
#define SCR_SUNTEK_IdleSession		       __CTkvs_SCR(11)
#define SCR_SUNTEK_CalloutTimes		       __CTkvs_SCR(12)
#define SCR_SUNTEK_CalloutSuccTimes	       __CTkvs_SCR(13)
#define SCR_SUNTEK_InValidServer	       __CTkvs_SCR(14)
#define SCR_SUNTEK_ErrorReason		       __CTkvs_SCR(15)
//*************************************************************************
//Private keys of SWITCH
//**************************************************************************
#define __CTkvs_SWITCH(item)  CTsym_Build(CT_objSWITCH,CT_vendSUNTEK,(item))

#define SWITCH_SUNTEK_ConferenceID               __CTkvs_SWITCH(0x0004)
#define SWITCH_SUNTEK_ConferenceType             __CTkvs_SWITCH(0x0005)
#define SWITCH_SUNTEK_CallProcessingEvent        __CTkvs_SWITCH(0x0006)
#define SWITCH_SUNTEK_ReleaseDataType            __CTkvs_SWITCH(0x0007)
//Collect Digit String --- Cds
#define SWITCH_SUNTEK_CdsMode                    __CTkvs_SWITCH(0x0008)
#define SWITCH_SUNTEK_CdsMaxDigits               __CTkvs_SWITCH(0x0009)
#define SWITCH_SUNTEK_CdsNumTermCharactors       __CTkvs_SWITCH(0x000a)
#define SWITCH_SUNTEK_CdsConfigBytes             __CTkvs_SWITCH(0x000b)
#define SWITCH_SUNTEK_CdsTermCharactors          __CTkvs_SWITCH(0x000c)
#define SWITCH_SUNTEK_CdsInterdigitTimer         __CTkvs_SWITCH(0x000d)
#define SWITCH_SUNTEK_CdsFirstDigitTimer         __CTkvs_SWITCH(0x000e)
#define SWITCH_SUNTEK_CdsCompletionTimer         __CTkvs_SWITCH(0x000f)
#define SWITCH_SUNTEK_CdsMinRecvDigitDurationTimer  __CTkvs_SWITCH(0x0010)
#define SWITCH_SUNTEK_CdsAddrSignalingType       __CTkvs_SWITCH(0x0011)
#define SWITCH_SUNTEK_CdsNumDigitStrings         __CTkvs_SWITCH(0x0012)
#define SWITCH_SUNTEK_CdsResuDigitCollectTimer   __CTkvs_SWITCH(0x0013)

#define SWITCH_SUNTEK_ConferenceSize             __CTkvs_SWITCH(0x0014)
#define SWITCH_SUNTEK_BroadcastEnable            __CTkvs_SWITCH(0x0015)
#define SWITCH_SUNTEK_TransmitCallProgressPatternID __CTkvs_SWITCH(0x0016)
#define SWITCH_SUNTEK_NumCyclesToTransmit        __CTkvs_SWITCH(0x0017)
#define SWITCH_SUNTEK_GenerateEventFlag          __CTkvs_SWITCH(0x0018)
#define SWITCH_SUNTEK_ConnectDataType            __CTkvs_SWITCH(0x0019)
#define SWITCH_SUNTEK_ChannelAPadValue           __CTkvs_SWITCH(0x001a)
#define SWITCH_SUNTEK_ChannelBPadValue           __CTkvs_SWITCH(0x001b)
#define SWITCH_SUNTEK_CpcDetectionAction         __CTkvs_SWITCH(0x001c)
#define SWITCH_SUNTEK_ChannelAEncodingFormat     __CTkvs_SWITCH(0x001d)
#define SWITCH_SUNTEK_ChannelBEncodingFormat     __CTkvs_SWITCH(0x001e)
#define SWITCH_SUNTEK_ServiceType                __CTkvs_SWITCH(0x001f)
#define SWITCH_SUNTEK_StringCount                __CTkvs_SWITCH(0x0020)
#define SWITCH_SUNTEK_StringMode                 __CTkvs_SWITCH(0x0021)
#define SWITCH_SUNTEK_FirstDigitDuration         __CTkvs_SWITCH(0x0022)
#define SWITCH_SUNTEK_DigitDuration              __CTkvs_SWITCH(0x0023)
#define SWITCH_SUNTEK_InterdigitDuration         __CTkvs_SWITCH(0x0024)
#define SWITCH_SUNTEK_DelayDuration              __CTkvs_SWITCH(0x0025)
#define SWITCH_SUNTEK_String1DigitCount          __CTkvs_SWITCH(0x0026)
#define SWITCH_SUNTEK_String1Digits              __CTkvs_SWITCH(0x0027)
#define SWITCH_SUNTEK_String2DigitCount          __CTkvs_SWITCH(0x0028)
#define SWITCH_SUNTEK_String2Digits              __CTkvs_SWITCH(0x0029)
#define SWITCH_SUNTEK_PPLComponentID             __CTkvs_SWITCH(0x002a)
#define SWITCH_SUNTEK_PPLEvent                   __CTkvs_SWITCH(0x002b)
#define SWITCH_SUNTEK_ConfigFlag                 __CTkvs_SWITCH(0x002c)
#define SWITCH_SUNTEK_EventFlag                  __CTkvs_SWITCH(0x002d)
#define SWITCH_SUNTEK_AnnouncementCount          __CTkvs_SWITCH(0x002e)

#define SWITCH_SUNTEK_SpanService        	 __CTkvs_SWITCH(0x002f)
#define SWITCH_SUNTEK_ChannelService             __CTkvs_SWITCH(0x0030)

#define SWITCH_SUNTEK_Channels   	 	 __CTkvs_SWITCH(0x0032)
#define SWITCH_SUNTEK_EventID                    __CTkvs_SWITCH(0x0033)

//************************************************************************
//Private keys of COMM
//************************************************************************

//KVset in meggages from COMMUNICATIONS module

#define __CTkvs_COMM(item)	 CTsym_Build( CT_objCOMMCTRL, CT_vendSUNTEK, (item) )

#define COMM_SUNTEK_ConferenceID              __CTkvs_COMM(0x0000)
#define COMM_SUNTEK_CallProcessingEvent       __CTkvs_COMM(0x0001)
#define COMM_SUNTEK_ReleaseDataType           __CTkvs_COMM(0x0002)

// Call Processing Analysis --- Cpa
#define COMM_SUNTEK_CpaResult		      __CTkvs_COMM(0x0003)
#define COMM_SUNTEK_ChannelStatus             __CTkvs_COMM(0x0004)
#define COMM_SUNTEK_PurgeReason               __CTkvs_COMM(0x0005)
#define COMM_SUNTEK_StackID                   __CTkvs_COMM(0x0006)
#define COMM_SUNTEK_LinkID                    __CTkvs_COMM(0x0007)
#define COMM_SUNTEK_PPLComponentID            __CTkvs_COMM(0x0008)
#define COMM_SUNTEK_PPLEvent                  __CTkvs_COMM(0x0009)
#define COMM_SUNTEK_ResendFlag                __CTkvs_COMM(0x000a)
#define COMM_SUNTEK_AddrDataType              __CTkvs_COMM(0x000b)

#define COMM_SUNTEK_Slot				__CTkvs_COMM(0x000c)
#define COMM_SUNTEK_PhysicalSpan		__CTkvs_COMM(0x000d)
#define COMM_SUNTEK_NodeEntity          __CTkvs_COMM(0x000e)
#define COMM_SUNTEK_DataLength          __CTkvs_COMM(0x000f)

#define COMM_SUNTEK_SystemType			__CTkvs_COMM(0x0011)
#define COMM_SUNTEK_EXCPUID				__CTkvs_COMM(0x0012)
#define COMM_SUNTEK_EXCPUState			__CTkvs_COMM(0x0013)
#define COMM_SUNTEK_AdjacentEXCPUState	__CTkvs_COMM(0x0014)
#define COMM_SUNTEK_StatusBits			__CTkvs_COMM(0x0015)
#define COMM_SUNTEK_Reserved			__CTkvs_COMM(0x0016)
#define COMM_SUNTEK_Severity			__CTkvs_COMM(0x0017)
#define COMM_SUNTEK_Entity				__CTkvs_COMM(0x0018)
#define COMM_SUNTEK_AlarmNumber			__CTkvs_COMM(0x0019)

#define C0MM_SUNTEK_SlotNumber			__CTkvs_COMM(0x001b)
#define C0MM_SUNTEK_PhysicalNodeID		__CTkvs_COMM(0x001c)
#define C0MM_SUNTEK_NewNodeID			__CTkvs_COMM(0x001d)
#define COMM_SUNTEK_SIMMNumber			__CTkvs_COMM(0x001e)
#define C0MM_SUNTEK_DestinationID		__CTkvs_COMM(0x001f)
#define COMM_SUNTEK_RouteID				__CTkvs_COMM(0x0020)
#define COMM_SUNTEK_SlotofPrimaryCard	__CTkvs_COMM(0x0021)
#define COMM_SUNTEK_SlotofSecondaryCard __CTkvs_COMM(0x0022)
#define COMM_SUNTEK_SlotofActiveCard	__CTkvs_COMM(0x0023)
#define COMM_SUNTEK_AnnounceCount		__CTkvs_COMM(0x0024)
#define COMM_SUNTEK_CommMainVersion  __CTkvs_COMM(0x0025)


//***********************************************************************
//Private keys of MAINT
//***********************************************************************
#define __CTkvs_MAINT(item)  CTsym_Build(CT_objMAINT,CT_vendSUNTEK, (item) )

#define MAINT_SUNTEK_LogicalNodeID   __CTkvs_MAINT(0x0001)

#define MAINT_SUNTEK_AnswerSupervisionMode  __CTkvs_MAINT(0x0006)
//Assign EXS Host/Slave
#define MAINT_SUNTEK_HostID          __CTkvs_MAINT(0x0007)
#define MAINT_SUNTEK_SlaveID         __CTkvs_MAINT(0x0008)
//Assign logical node ID
#define MAINT_SUNTEK_PhysicalNodeID  __CTkvs_MAINT(0x0009)
//Asign logical span ID
#define MAINT_SUNTEK_LogicalSpanID   __CTkvs_MAINT(0x000a)
#define MAINT_SUNTEK_SlotNumber      __CTkvs_MAINT(0x000b)
#define MAINT_SUNTEK_PhysicalSpan    __CTkvs_MAINT(0x000c)
//B channel configure
#define MAINT_SUNTEK_Entity          __CTkvs_MAINT(0x000d)
#define MAINT_SUNTEK_Value           __CTkvs_MAINT(0x000e)
//Busy out flag configure
#define MAINT_SUNTEK_BusyOutFlag     __CTkvs_MAINT(0x000f)
//Call progress analysis class configure
#define MAINT_SUNTEK_UpdateAllFlag   __CTkvs_MAINT(0x0010)
#define MAINT_SUNTEK_ClassID         __CTkvs_MAINT(0x0011)
#define MAINT_SUNTEK_Action          __CTMAINTCmdsym(0x0012)
//Call progress analysis pattern configure
#define CmdNAINT_SUNTEK_PatternID       __CTkvs_MAINT(0x0014)
//CCS redundancy configure
#define MAINT_SUNTEK_PrimaryCardSlot __CTkvs_MAINT(0x0015)
#define MAINT_SUNTEK_SecondCardSlot  __CTkvs_MAINT(0x0016)
#define MAINT_SUNTEK_RedundancyType  __CTkvs_MAINT(0x0017)
//D channel assign
#define MAINT_SUNTEK_AddressType     __CTkvs_MAINT(0x0018)
#define MAINT_SUNTEK_SecondFacility  __CTkvs_MAINT(0x0019)

#define MAINT_SUNTEK_PrimarySpanID   __CTkvs_MAINT(0x001b)
#define MAINT_SUNTEK_PrimaryChannel  __CTkvs_MAINT(0x001c)
#define MAINT_SUNTEK_SecondSpanID    __CTkvs_MAINT(0x001d)
#define MAINT_SUNTEK_SecondChannel   __CTkvs_MAINT(0x001e)
//Distant end release mode configure
#define MAINT_SUNTEK_DistantReleaseMode __CTkvs_MAINT(0x001f)
//DSP SIMM configure
#define MAINT_SUNTEK_SIMMNumber      __CTkvs_MAINT(0x0020)
#define MAINT_SUNTEK_FuncTypeDSP0    __CTkvs_MAINT(0x0021)
#define MAINT_SUNTEK_FuncTypeDSP1    __CTkvs_MAINT(0x0022)
#define MAINT_SUNTEK_FuncTypeDSP2    __CTkvs_MAINT(0x0023)
#define MAINT_SUNTEK_FuncTypeDSP3    __CTkvs_MAINT(0x0024)
//E1 span configure
#define MAINT_SUNTEK_Format          __CTkvs_MAINT(0x0025)
#define MAINT_SUNTEK_LineLength      __CTkvs_MAINT(0x0026)
#define MAINT_SUNTEK_SARegisters     __CTkvs_MAINT(0x0027)
#define MAINT_SUNTEK_TS16Register    __CTkvs_MAINT(0x0028)
//Filter/Timer configure
#define MAINT_SUNTEK_FilterTimerType __CTkvs_MAINT(0x0029)
#define MAINT_SUNTEK_FilterTimerID   __CTkvs_MAINT(0x002a)
//Flash timing configure
#define MAINT_SUNTEK_FlashMode       __CTkvs_MAINT(0x002b)
//Inpulsing parameters configure
#define MAINT_SUNTEK_StageNumber     __CTkvs_MAINT(0x002c)
#define MAINT_SUNTEK_DigStrNum       __CTkvs_MAINT(0x002d)
#define MAINT_SUNTEK_StageComTimeOut __CTkvs_MAINT(0x002e)
#define MAINT_SUNTEK_AddressSignType __CTkvs_MAINT(0x002f)
#define MAINT_SUNTEK_CollMethod1     __CTkvs_MAINT(0x0030)
#define MAINT_SUNTEK_CollData1       __CTkvs_MAINT(0x0031)
#define MAINT_SUNTEK_CollMethod2     __CTkvs_MAINT(0x0032)
#define MAINT_SUNTEK_CollData2       __CTkvs_MAINT(0x0033)
//Inseize instruction list configure
#define MAINT_SUNTEK_InstructNumber  __CTkvs_MAINT(0x0034)
#define MAINT_SUNTEK_InstructType    __CTkvs_MAINT(0x0035)
//Local end release mode configure
#define MAINT_SUNTEK_LocalReleaseMode __CTkvs_MAINT(0x0036)
//Loop timing configure
#define MAINT_SUNTEK_LoopTimingType  __CTkvs_MAINT(0x0037)
//Poll interval configure
#define MAINT_SUNTEK_PollInterval    __CTkvs_MAINT(0x0038)
//PPL asign
#define MAINT_SUNTEK_PPLComponent    __CTkvs_MAINT(0x0039)
#define MAINT_SUNTEK_ProtocolID      __CTkvs_MAINT(0x003a)
//PPL audit configure
#define MAINT_SUNTEK_AuditType       __CTkvs_MAINT(0x003b)
//PPL configure
#define MAINT_SUNTEK_PPLEntity       __CTkvs_MAINT(0x003c)
//PPL create
#define MAINT_SUNTEK_PPLProtocolName __CTkvs_MAINT(0x003d)
//PPL delete
#define MAINT_SUNTEK_PPLEntityID     __CTkvs_MAINT(0x003e)
//PPL table download
#define MAINT_SUNTEK_TableType       __CTkvs_MAINT(0x003f)
#define MAINT_SUNTEK_TableID         __CTkvs_MAINT(0x0040)
//PPL timer configure
#define MAINT_SUNTEK_PPLTimerType    __CTkvs_MAINT(0x0041)
#define MAINT_SUNTEK_PPLTimerID      __CTkvs_MAINT(0x0042)
#define MAINT_SUNTEK_TimerValue      __CTkvs_MAINT(0x0043)
//PPL transmit signal configure
#define MAINT_SUNTEK_ProtocolSignalingState  __CTkvs_MAINT(0x0044)
#define CmdMAINT_SUNTEK_SignalingBits   __CTkvs_MAINT(0x0045)
//Receive signaling configure
#define MAINT_SUNTEK_SignalingType   __CTkvs_MAINT(0x0046)
#define MAINT_SUNTEK_SignalingValue  __CTkvs_MAINT(0x0047)
#define MAINT_SUNTEK_TransmissionMode  __CTkvs_MAINT(0x0048)
#define MAINT_SUNTEK_BitMask         __CTkvs_MAINT(0x0049)
//Recorded announcement delete
#define MAINT_SUNTEK_ForceFlag       __CTkvs_MAINT(0x004a)
//Recorded announcement download
#define MAINT_SUNTEK_AnnounID        __CTkvs_MAINT(0x004b)
//Recorded announcement download initiate
#define MAINT_SUNTEK_AnnounSize      __CTkvs_MAINT(0x004c)
#define MAINT_SUNTEK_AnnounChecksum  __CTkvs_MAINT(0x004d)
#define MAINT_SUNTEK_AnnounFormat    __CTkvs_MAINT(0x004e)
#define MAINT_SUNTEK_EncodingFormat  __CTkvs_MAINT(0x004f)
//Server state configure
#define MAINT_SUNTEK_LogicalRingID   __CTkvs_MAINT(0x0050)
//SS7 CIC configure
#define MAINT_SUNTEK_DPC             __CTkvs_MAINT(0x0051)
//SS7 ISUP message format configure
#define MAINT_SUNTEK_StackID         __CTkvs_MAINT(0x0052)
//SS7 signaling link donfigure
#define MAINT_SUNTEK_SignalingLinkCode  __CTkvs_MAINT(0x0053)
#define MAINT_SUNTEK_DataRate           __CTkvs_MAINT(0x0054)
#define MAINT_SUNTEK_LinkSetID          __CTkvs_MAINT(0x0055)
#define MAINT_SUNTEK_LinkID             __CTkvs_MAINT(0x0056)
//SS7 signaling link set configure
#define MAINT_SUNTEK_APC                __CTkvs_MAINT(0x0057)
//SS7 signaling route configure
#define MAINT_SUNTEK_DestinationID      __CTkvs_MAINT(0x0058)
#define MAINT_SUNTEK_RouteID            __CTkvs_MAINT(0x0059)
#define MAINT_SUNTEK_Priority           __CTkvs_MAINT(0x005a)
//Standby lien card configure
#define MAINT_SUNTEK_CardType           __CTkvs_MAINT(0x005b)
//Start dial configure
#define MAINT_SUNTEK_StartDialType      __CTkvs_MAINT(0x005c)
#define MAINT_SUNTEK_StartDialValue     __CTkvs_MAINT(0x005d)
//Synchromization priority list configure
#define MAINT_SUNTEK_PriSynMode1        __CTkvs_MAINT(0x005e)
#define MAINT_SUNTEK_PriSynMode2        __CTkvs_MAINT(0x005f)
#define MAINT_SUNTEK_PriSynMode3        __CTkvs_MAINT(0x0060)
#define MAINT_SUNTEK_PriSynMode4        __CTkvs_MAINT(0x0061)
#define MAINT_SUNTEK_PriSynMode5        __CTkvs_MAINT(0x0062)
//Tag configure
#define MAINT_SUNTEK_Tag                __CTkvs_MAINT(0x0063)
//Time set
#define MAINT_SUNTEK_Month              __CTkvs_MAINT(0x0064)
#define MAINT_SUNTEK_Day                __CTkvs_MAINT(0x0065)
#define MAINT_SUNTEK_Year               __CTkvs_MAINT(0x0066)
#define MAINT_SUNTEK_Hour               __CTkvs_MAINT(0x0067)
#define MAINT_SUNTEK_Minute             __CTkvs_MAINT(0x0068)
#define MAINT_SUNTEK_Second             __CTkvs_MAINT(0x0069)
//Transmit tone configure
#define MAINT_SUNTEK_ToneType           __CTkvs_MAINT(0x006a)

#define MAINT_SUNTEK_Flag                  __CTkvs_MAINT(0x0072)
#define MAINT_SUNTEK_ChaBPadVal            __CTkvs_MAINT(0x0073)
#define MAINT_SUNTEK_ConferenceID          __CTkvs_MAINT(0x0076)
#define MAINT_SUNTEK_ServiceType           __CTkvs_MAINT(0x0077)
#define MAINT_SUNTEK_ConfigType            __CTkvs_MAINT(0x0078)
#define MAINT_SUNTEK_AnnouncementID        __CTkvs_MAINT(0x0079)

#define MAINT_SUNTEK_Slot				   __CTkvs_MAINT(0x007a)
#define MAINT_SUNTEK_NewNodeID			   __CTkvs_MAINT(0x007b)
#define MAINT_SUNTEK_BaseCICNumber		   __CTkvs_MAINT(0x007c)
#define MAINT_SUNTEK_BaseCICSpan		   __CTkvs_MAINT(0X007d)
#define MAINT_SUNTEK_BaseChanel			   __CTkvs_MAINT(0x007e)
#define MAINT_SUNTEK_GroupCIINumber		   __CTkvs_MAINT(0x007f)	


#define MAINT_SUNTEK_CommandCode			__CTkvs_MAINT(0x00A0)
#define MAINT_SUNTEK_InputInt1				__CTkvs_MAINT(0x00A1)
#define MAINT_SUNTEK_InputInt2				__CTkvs_MAINT(0x00A2)
#define	MAINT_SUNTEK_InputString1			__CTkvs_MAINT(0x00A3)
#define MAINT_SUNTEK_InputString2			__CTkvs_MAINT(0x00A4)
	
#define MAINT_SUNTEK_ResultStatus			__CTkvs_MAINT(0x00A7)
#define MAINT_SUNTEK_ResultString			__CTkvs_MAINT(0x00A8)
#define MAINT_SUNTEK_ResultStringArray		__CTkvs_MAINT(0x00A9)

//
//*********************************************************************
//Private keys of CONFIG
//**********************************************************************

#define __CTkvs_CONFIG(item) CTsym_Build(CT_objCONFIG,\
					    CT_vendSUNTEK,\
					    (item) )
#define CONFIG_SUNTEK_BootLoaderMaRev     __CTkvs_CONFIG(0x00a3)
#define CONFIG_SUNTEK_BootLoaderMiRev     __CTkvs_CONFIG(0x00a4)
#define CONFIG_SUNTEK_SysSoftMaRev        __CTkvs_CONFIG(0x00a5)
#define CONFIG_SUNTEK_SysSoftMiRev        __CTkvs_CONFIG(0x00a6)
#define CONFIG_SUNTEK_SysSoftBDNum        __CTkvs_CONFIG(0x00a7)
#define CONFIG_SUNTEK_EX_CPUTimestamp     __CTkvs_CONFIG(0x00a8)
#define CONFIG_SUNTEK_AdjEX_CPUTimestamp  __CTkvs_CONFIG(0x00a9)


#define CONFIG_SUNTEK_SocketNumber        __CTkvs_CONFIG(0x0001)
//Length of Ip address Number
#define CONFIG_SUNTEK_IPNumber            __CTkvs_CONFIG(0x0002)
//Ip address Number pointer (string)
#define CONFIG_SUNTEK_LogicalNodeId       __CTkvs_CONFIG(0x0003)
#define CONFIG_SUNTEK_LogicSpanID         __CTkvs_CONFIG(0x0004)
#define CONFIG_SUNTEK_SlotNumber          __CTkvs_CONFIG(0x0005)
#define CONFIG_SUNTEK_PhysicalSpan        __CTkvs_CONFIG(0x0006)
#define CONFIG_SUNTEK_Status              __CTkvs_CONFIG(0x0007)
#define CONFIG_SUNTEK_AnswerMode          __CTkvs_CONFIG(0x000c)
#define CONFIG_SUNTEK_HostLogicId         __CTkvs_CONFIG(0x000d)
#define CONFIG_SUNTEK_SlaveLogicId        __CTkvs_CONFIG(0x000e)
#define CONFIG_SUNTEK_PhysicalNode        __CTkvs_CONFIG(0x000f)
#define CONFIG_SINTEK_NewNode             __CTkvs_CONFIG(0x0010)
#define CONFIG_SUNTEK_Flag                __CTkvs_CONFIG(0x0011)
#define CONFIG_SUNTEK_UpdateFlag          __CTkvs_CONFIG(0x0012)
#define CONFIG_SUNTEK_ClassId             __CTkvs_CONFIG(0x0013)
#define CONFIG_SUNTEK_Action              __CTkvs_CONFIG(0x0014)
#define CONFIG_SUNTEK_PatternId           __CTkvs_CONFIG(0x0015)
#define CONFIG_SUNTEK_Data                __CTkvs_CONFIG(0x0016)
#define CONFIG_SUNTEK_SlotPrim            __CTkvs_CONFIG(0x0017)
#define CONFIG_SUNTEK_SlotSecond          __CTkvs_CONFIG(0x0018)
#define CONFIG_SUNTEK_PrimSlot            __CTkvs_CONFIG(0x0019)
#define CONFIG_SUNTEK_SecondSlot          __CTkvs_CONFIG(0x001a)
#define CONFIG_SUNTEK_RedunType           __CTkvs_CONFIG(0x001b)
#define CONFIG_SUNTEK_ReleaseMode         __CTkvs_CONFIG(0x001c)
#define CONFIG_SUNTEK_BReNum              __CTkvs_CONFIG(0x001d)
#define CONFIG_SUNTEK_BRecord             __CTkvs_CONFIG(0x001e)
#define CONFIG_SUNTEK_TimeStamp           __CTkvs_CONFIG(0x001f)
#define CONFIG_SUNTEK_SReNum              __CTkvs_CONFIG(0x0020)
#define CONFIG_SUNTEK_SRecord             __CTkvs_CONFIG(0x0021)
#define CONFIG_SUNTEK_DspSlot             __CTkvs_CONFIG(0x0022)
#define CONFIG_SUNTEK_SimmNum             __CTkvs_CONFIG(0x0023)
#define CONFIG_SUNTEK_Dsp0                __CTkvs_CONFIG(0x0024)
#define CONFIG_SUNTEK_Dsp1                __CTkvs_CONFIG(0x0025)
#define CONFIG_SUNTEK_Dsp2                __CTkvs_CONFIG(0x0026)
#define CONFIG_SUNTEK_Dsp3                __CTkvs_CONFIG(0x0027)
#define CONFIG_SUNTEK_Format              __CTkvs_CONFIG(0x0028)
#define CONFIG_SUNTEK_LineLen             __CTkvs_CONFIG(0x0029)
#define CONFIG_SUNTEK_SARegi              __CTkvs_CONFIG(0x002a)
#define CONFIG_SUNTEK_Ts16Regi            __CTkvs_CONFIG(0x002b)
#define CONFIG_SUNTEK_LogicRing           __CTkvs_CONFIG(0x002c)
#define CONFIG_SUNTEK_Entity              __CTkvs_CONFIG(0x002d)
#define CONFIG_SUNTEK_RingData            __CTkvs_CONFIG(0x002e)
#define CONFIG_SUNTEK_EntityTime          __CTkvs_CONFIG(0x002f)
#define CONFIG_SUNTEK_DataTime            __CTkvs_CONFIG(0x0030)
#define CONFIG_SUNTEK_NodeEntity          __CTkvs_CONFIG(0x0031)
#define CONFIG_SUNTEK_DataLength          __CTkvs_CONFIG(0x0032)
#define CONFIG_SUNTEK_NodeData            __CTkvs_CONFIG(0x0033)
#define CONFIG_SUNTEK_FilterType          __CTkvs_CONFIG(0x0034)
#define CONFIG_SUNTEK_FilterId            __CTkvs_CONFIG(0x0035)
#define CONFIG_SUNTEK_Value               __CTkvs_CONFIG(0x0036)
#define CONFIG_SUNTEK_StageNum            __CTkvs_CONFIG(0x0037)
#define CONFIG_SUNTEK_DigNum              __CTkvs_CONFIG(0x0038)
#define CONFIG_SUNTEK_StageComp           __CTkvs_CONFIG(0x0039)
#define CONFIG_SUNTEK_AddrSign            __CTkvs_CONFIG(0x003a)
#define CONFIG_SUNTEK_CollMeth1           __CTkvs_CONFIG(0x003b)
#define CONFIG_SUNTEK_CollData1           __CTkvs_CONFIG(0x003c)
#define CONFIG_SUNTEK_CollMeth2           __CTkvs_CONFIG(0x003d)
#define CONFIG_SUNTEK_CollData2           __CTkvs_CONFIG(0x003e)
#define CONFIG_SUNTEK_InstrNum            __CTkvs_CONFIG(0x003f)
#define CONFIG_SUNTEK_InstrType           __CTkvs_CONFIG(0x0040)
#define CONFIG_SUNTEK_Data0               __CTkvs_CONFIG(0x0041)
#define CONFIG_SUNTEK_Data1               __CTkvs_CONFIG(0x0042)
#define CONFIG_SUNTEK_RealMode            __CTkvs_CONFIG(0x0043)
#define CONFIG_SUNTEK_LoopSlot            __CTkvs_CONFIG(0x0044)
#define CONFIG_SUNTEK_LoopType            __CTkvs_CONFIG(0x0045)
#define CONFIG_SUNTEK_EncodeFormat        __CTkvs_CONFIG(0x0046)
#define CONFIG_SUNTEK_PollInterv          __CTkvs_CONFIG(0x0047)
#define CONFIG_SUNTEK_CompoId             __CTkvs_CONFIG(0x0048)
#define CONFIG_SUNTEK_ProtoId             __CTkvs_CONFIG(0x0049)
#define CONFIG_SUNTEK_PplSlot             __CTkvs_CONFIG(0x004a)
#define CONFIG_SUNTEK_AuditType           __CTkvs_CONFIG(0x004b)
#define CONFIG_SUNTEK_PplEntity           __CTkvs_CONFIG(0x004c)
#define CONFIG_SUNTEK_ConfiData           __CTkvs_CONFIG(0x004d)
#define CONFIG_SUNTEK_NumLocat            __CTkvs_CONFIG(0x004e)
#define CONFIG_SUNTEK_LocatData           __CTkvs_CONFIG(0x004f)
#define CONFIG_SUNTEK_ProtoName           __CTkvs_CONFIG(0x0050)
#define CONFIG_SUNTEK_TabNum              __CTkvs_CONFIG(0x0051)
#define CONFIG_SUNTEK_TabData             __CTkvs_CONFIG(0x0052)
#define CONFIG_SUNTEK_TableType           __CTkvs_CONFIG(0x0053)
#define CONFIG_SUNTEK_TableId             __CTkvs_CONFIG(0x0054)
#define CONFIG_SUNTEK_DataTable           __CTkvs_CONFIG(0x0055)
#define CONFIG_SUNTEK_ErrorLength         __CTkvs_CONFIG(0x0056)
#define CONFIG_SUNTEK_ErrorType           __CTkvs_CONFIG(0x0057)
#define CONFIG_SUNTEK_ErrorData           __CTkvs_CONFIG(0x0058)
#define CONFIG_SUNTEK_TableSize           __CTkvs_CONFIG(0x0059)
#define CONFIG_SUNTEK_TableName           __CTkvs_CONFIG(0x005a)
#define CONFIG_SUNTEK_PplLogicSpan        __CTkvs_CONFIG(0x005b)
#define CONFIG_SUNTEK_PplChannel          __CTkvs_CONFIG(0x005c)
#define CONFIG_SUNTEK_PplTimerType        __CTkvs_CONFIG(0x005d)
#define CONFIG_SUNTEK_PplTimerId          __CTkvs_CONFIG(0x005e)
#define CONFIG_SUNTEK_PplTimerValue       __CTkvs_CONFIG(0x005f)
#define CONFIG_SUNTEK_SignalingState      __CTkvs_CONFIG(0x0060)
#define CONFIG_SUNTEK_SignalingBits       __CTkvs_CONFIG(0x0061)
#define CONFIG_SUNTEK_SignalingType       __CTkvs_CONFIG(0x0062)
#define CONFIG_SUNTEK_SignalingValue      __CTkvs_CONFIG(0x0063)
#define CONFIG_SUNTEK_SignalingMode       __CTkvs_CONFIG(0x0064)
#define CONFIG_SUNTEK_BitMask             __CTkvs_CONFIG(0x0065)
#define CONFIG_SUNTEK_ForceFlag           __CTkvs_CONFIG(0x0066)
#define CONFIG_SUNTEK_AnnoId              __CTkvs_CONFIG(0x0067)
#define CONFIG_SUNTEK_AnnoData            __CTkvs_CONFIG(0x0068)
#define CONFIG_SUNTEK_AnnoSize            __CTkvs_CONFIG(0x0069)
#define CONFIG_SUNTEK_AnnoChecksum        __CTkvs_CONFIG(0x006a)
#define CONFIG_SUNTEK_AnnoFormat          __CTkvs_CONFIG(0x006b)
#define CONFIG_SUNTEK_AnnoEncod           __CTkvs_CONFIG(0x006c)
#define CONFIG_SUNTEK_LogicRingNum        __CTkvs_CONFIG(0x006d)
#define CONFIG_SUNTEK_FilterEnti          __CTkvs_CONFIG(0x006e)
#define CONFIG_SUNTEK_FilterValue         __CTkvs_CONFIG(0x006f)
#define CONFIG_SUNTEK_StackId             __CTkvs_CONFIG(0x0070)
#define CONFIG_SUNTEK_CICNum              __CTkvs_CONFIG(0x0071)
#define CONFIG_SUNTEK_CICSpan             __CTkvs_CONFIG(0x0072)
#define CONFIG_SUNTEK_CICChann            __CTkvs_CONFIG(0x0073)
#define CONFIG_SUNTEK_CICGroup            __CTkvs_CONFIG(0x0074)
#define CONFIG_SUNTEK_DPC                 __CTkvs_CONFIG(0x0075)
#define CONFIG_SUNTEK_IsupMsgIn           __CTkvs_CONFIG(0x0076)
#define CONFIG_SUNTEK_IsupMsgId           __CTkvs_CONFIG(0x0077)
#define CONFIG_SUNTEK_IsupPrior           __CTkvs_CONFIG(0x0078)
#define CONFIG_SUNTEK_MsgLen              __CTkvs_CONFIG(0x0079)
#define CONFIG_SUNTEK_IsupData            __CTkvs_CONFIG(0x007a)
#define CONFIG_SUNTEK_S7LogicSpan         __CTkvs_CONFIG(0x007b)
#define CONFIG_SUNTEK_S7Chan              __CTkvs_CONFIG(0x007c)
#define CONFIG_SUNTEK_LinkCode            __CTkvs_CONFIG(0x007d)
#define CONFIG_SUNTEK_LinkRate            __CTkvs_CONFIG(0x007e)
#define CONFIG_SUNTEK_Reserve             __CTkvs_CONFIG(0x007f)
#define CONFIG_SUNTEK_S7StackId           __CTkvs_CONFIG(0x0080)
// duplicate : #define CONFIG_SUNTEK_LinkSet    __CTkvs_CONFIG(0x0081)
#define CONFIG_SUNTEK_APC                 __CTkvs_CONFIG(0x0082)
#define CONFIG_SUNTEK_SS7Dest             __CTkvs_CONFIG(0x0083)
#define CONFIG_SUNTEK_SS7Rout             __CTkvs_CONFIG(0x0084)
#define CONFIG_SUNTEK_LinkSet             __CTkvs_CONFIG(0x0085)
#define CONFIG_SUNTEK_SS7Prio             __CTkvs_CONFIG(0x0086)
#define CONFIG_SUNTEK_S7Slot              __CTkvs_CONFIG(0x0087)
#define CONFIG_SUNTEK_OPC                 __CTkvs_CONFIG(0x0088)
#define CONFIG_SUNTEK_ModuleNum           __CTkvs_CONFIG(0x0089)
#define CONFIG_SUNTEK_ModuleData          __CTkvs_CONFIG(0x008a)
#define CONFIG_SUNTEK_CardType            __CTkvs_CONFIG(0x008b)
#define CONFIG_SUNTEK_DialType            __CTkvs_CONFIG(0x008c)
#define CONFIG_SUNTEK_DialValue           __CTkvs_CONFIG(0x008d)
#define CONFIG_SUNTEK_PrioMode1           __CTkvs_CONFIG(0x008e)
#define CONFIG_SUNTEK_PrioMode2           __CTkvs_CONFIG(0x008f)
#define CONFIG_SUNTEK_PrioMode3           __CTkvs_CONFIG(0x0090)
#define CONFIG_SUNTEK_PrioMode4           __CTkvs_CONFIG(0x0091)
#define CONFIG_SUNTEK_PrioMode5           __CTkvs_CONFIG(0x0092)
#define CONFIG_SUNTEK_ConfType            __CTkvs_CONFIG(0x0093)
#define CONFIG_SUNTEK_SysData             __CTkvs_CONFIG(0x0094)
#define CONFIG_SUNTEK_T1Format            __CTkvs_CONFIG(0x0095)
#define CONFIG_SUNTEK_T1Line              __CTkvs_CONFIG(0x0096)
#define CONFIG_SUNTEK_Tag                 __CTkvs_CONFIG(0x0097)
#define CONFIG_SUNTEK_Year                __CTkvs_CONFIG(0x0098)
#define CONFIG_SUNTEK_Month               __CTkvs_CONFIG(0x0099)
#define CONFIG_SUNTEK_Day                 __CTkvs_CONFIG(0x009a)
#define CONFIG_SUNTEK_Hour                __CTkvs_CONFIG(0x009b)
#define CONFIG_SUNTEK_Minute              __CTkvs_CONFIG(0x009c)
#define CONFIG_SUNTEK_Second              __CTkvs_CONFIG(0x009d)
#define CONFIG_SUNTEK_SignType            __CTkvs_CONFIG(0x009e)
#define CONFIG_SUNTEK_TrunkType           __CTkvs_CONFIG(0x00a1)
#define CONFIG_SUNTEK_IP_Matrix           __CTkvs_CONFIG(0x00a2)
#define CONFIG_SUNTEK_Channels            __CTkvs_CONFIG(0X00aa)
#define CONFIG_SUNTEK_ChannelStatus       __CTkvs_CONFIG(0X00ab)

#define CONFIG_SUNTEK_swiNodeId            __CTkvs_CONFIG(0x00ac)
#define CONFIG_SUNTEK_swiLogicSpans        __CTkvs_CONFIG(0x00ad)
#define CONFIG_SUNTEK_swiChannelSpan       __CTkvs_CONFIG(0x00ae)
#define CONFIG_SUNTEK_swiData              __CTkvs_CONFIG(0x00af)

#define CONFIG_SUNTEK_LinkID		__CTkvs_CONFIG(0x00b0)
#define CONFIG_SUNTEK_SignalValue	__CTkvs_CONFIG(0x00b1)
#define CONFIG_SUNTEK_TransmisMOde	__CTkvs_CONFIG(0x00b2)
#define CONFIG_SUNTEK_PPLEntityID	__CTkvs_CONFIG(0x00b3)
#define CONFIG_SUNTEK_DistantReleaseMode	__CTkvs_CONFIG(0x00b4)
#define CONFIG_SUNTEK_LocalReleaseMode		__CTkvs_CONFIG(0x00b5)



/******************************************************************************
 *    defined communication key.
 *****************************************************************************/

#define __CTCommSym(item)              CTsym_Build( CT_objCOMMUNICATION,\
						    CT_vendSUNTEK,\
						    (item) )

#define Comm_SUNTEK_Priority      __CTCommSym(0x001)
#define Comm_SUNTEK_MsgKey        __CTCommSym(0x002)
#define Comm_SUNTEK_ShmKey        __CTCommSym(0x003)
#define Comm_SUNTEK_ShmSize       __CTCommSym(0x004)
#define Comm_SUNTEK_DataOffset    __CTCommSym(0x005)
#define Comm_SUNTEK_ClientData    __CTCommSym(0x006)
#define Comm_SUNTEK_ClientQueueCount __CTCommSym(0x007)
#define Comm_SUNTEK_MainQueueCount __CTCommSym(0x008)
#define Comm_SUNTEK_TCPMsgKey      __CTCommSym(0x009)
//-------------------------   add by zg  10/22/98
#define Comm_SUNTEK_MsgJudgeOffset      __CTCommSym(0x00a)


/******************************************************************************
 * defined profile module key. (Please let Walker Gun2 modified these )
 *****************************************************************************/
#define __CTCfgKeySym(item)             CTsym_Build( CT_objPROFILE,\
						  CT_vendSUNTEK,\
						  (item))

#define Config_SUNTEK_NullValue                 __CTCfgKeySym(0x000)
#define Config_SUNTEK_APPLICATION_SERVICE       __CTCfgKeySym(0x001)
#define Config_SUNTEK_ASIMap                    __CTCfgKeySym(0x002)
#define Config_SUNTEK_CCR                       __CTCfgKeySym(0x003)
#define Config_SUNTEK_CCRONLY                   __CTCfgKeySym(0x004)
#define Config_SUNTEK_DEFAULT_CONFIGURATION     __CTCfgKeySym(0x005)
#define Config_SUNTEK_FAX                       __CTCfgKeySym(0x006)
#define Config_SUNTEK_GROUP_SET                 __CTCfgKeySym(0x007)
#define Config_SUNTEK_NONE                      __CTCfgKeySym(0x008)
#define Config_SUNTEK_PLAYER                    __CTCfgKeySym(0x009)
#define Config_SUNTEK_PRIMARY_RESOURCE          __CTCfgKeySym(0x00a)
#define Config_SUNTEK_RECORDER                  __CTCfgKeySym(0x00b)
#define Config_SUNTEK_SIGD                      __CTCfgKeySym(0x00c)
#define Config_SUNTEK_SIGG                      __CTCfgKeySym(0x00d)
#define Config_SUNTEK_SPCTable                  __CTCfgKeySym(0x00e)
#define Config_SUNTEK_UserDefinedID             __CTCfgKeySym(0x00f)
#define Config_SUNTEK_FirstParam                __CTCfgKeySym(0x010)
#define Config_SUNTEK_LastParam                 __CTCfgKeySym(0x02f)
#define Config_SUNTEK_End                       __CTCfgKeySym(0x100)
#define Config_SUNTEK_Delimit                   __CTCfgKeySym(0x101)
#define Config_SUNTEK_Number                    __CTCfgKeySym(0x102)
#define Config_SUNTEK_ValidKey                  __CTCfgKeySym(0x200)
#define Config_SUNTEK_ASI                       __CTCfgKeySym(0x201)
#define Config_SUNTEK_ASIInfo                   __CTCfgKeySym(0x204)
#define Config_SUNTEK_PhoneNumber               __CTCfgKeySym(0x205)
#define Config_SUNTEK_NetDev                    __CTCfgKeySym(0x206)
#define Config_SUNTEK_VocDev                    __CTCfgKeySym(0x207)
#define Config_SUNTEK_SubDevType                __CTCfgKeySym(0x208)
#define Config_SUNTEK_SPCTableInfo              __CTCfgKeySym(0x209)

/******************************************************************************
 * defined SIA and CTFunction modules key.(Please remind Walker when modified )
 *****************************************************************************/
#define __CTSIAKeySym(item)             CTsym_Build( CT_objSIA,\
						  CT_vendSUNTEK,\
                                                  (item) )

#define SIA_SUNTEK_SessionID                    __CTCfgKeySym(0x001)
#define SIA_SUNTEK_TraceResultString		__CTCfgKeySym(0x002)
#define SIA_SUNTEK_StateArray                   __CTCfgKeySym(0x003)

/******************************************************************************
 * defined Authen (Please remind Walker when modified )
 *****************************************************************************/
#define __CTAuthenKeySym(item)             CTsym_Build( CT_objAUTHEN,\
						  CT_vendSUNTEK,\
                                                  (item) )

#define Authen_SUNTEK_MailBoxNo                    __CTAuthenKeySym(0x001)
#define Authen_SUNTEK_VerifyFlag                   __CTAuthenKeySym(0x002)
#define Authen_SUNTEK_NotifyType                   __CTAuthenKeySym(0x003)
#define Authen_SUNTEK_NotifyNo                     __CTAuthenKeySym(0x004)
#define Authen_SUNTEK_SubMailBoxNo                 __CTAuthenKeySym(0x005)
#define Authen_SUNTEK_Password                     __CTAuthenKeySym(0x006) 
#define Authen_SUNTEK_MailBoxPath                  __CTAuthenKeySym(0x007)
#define Authen_SUNTEK_MailNum                      __CTAuthenKeySym(0x008)
#define Authen_SUNTEK_SubMailBoxNum                __CTAuthenKeySym(0x009)
#define Authen_SUNTEK_ValidMaxMailNum              __CTAuthenKeySym(0x00a)
#define Authen_SUNTEK_ValidMaxMailTime             __CTAuthenKeySym(0x00b)
#define Authen_SUNTEK_FeeType                      __CTAuthenKeySym(0x00c)
#define Authen_SUNTEK_Status                       __CTAuthenKeySym(0x00d)
#define Authen_SUNTEK_Caller                       __CTAuthenKeySym(0x00f) 
#define Authen_SUNTEK_Called                       __CTAuthenKeySym(0x010) 
#define Authen_SUNTEK_ServiceStartTime             __CTAuthenKeySym(0x011) 
#define Authen_SUNTEK_ServiceValidtime             __CTAuthenKeySym(0x012) 
#define Authen_SUNTEK_VoxLength                    __CTAuthenKeySym(0x013) 
#define Authen_SUNTEK_NewPassword                  __CTAuthenKeySym(0x014) 
#define Authen_SUNTEK_AcceptType                   __CTAuthenKeySym(0x015) 
#define Authen_SUNTEK_ServiceValidTime             __CTAuthenKeySym(0x016) 
#define Authen_SUNTEK_NotifyStartTime              __CTAuthenKeySym(0x017)
#define Authen_SUNTEK_NotifyEndTime                __CTAuthenKeySym(0x018)
#define Authen_SUNTEK_NotifyIndex                  __CTAuthenKeySym(0x019)

#define Authen_SUNTEK_SrvCmdMsgTotal               __CTAuthenKeySym(0x100) 
#define Authen_SUNTEK_SrvCmdMsgUnknown             __CTAuthenKeySym(0x101) 

#define Authen_SUNTEK_SrvCmdMsgAccount             __CTAuthenKeySym(0x110) 
#define Authen_SUNTEK_SrvCmdMsgVerify              __CTAuthenKeySym(0x112) 
#define Authen_SUNTEK_SrvCmdMsgChangePassword      __CTAuthenKeySym(0x114) 
#define Authen_SUNTEK_SrvCmdMsgSetNotify           __CTAuthenKeySym(0x115) 
#define Authen_SUNTEK_SrvCmdMsgSchedule            __CTAuthenKeySym(0x116) 
#define Authen_SUNTEK_SrvCmdMsgGetNotify           __CTAuthenKeySym(0x117) 

#define Authen_SUNTEK_ClnCmdMsgTotal               __CTAuthenKeySym(0x200)
#define Authen_SUNTEK_ClnCmdMsgUnknown             __CTAuthenKeySym(0x201)
#define Authen_SUNTEK_ClnRespMsgUnknown            __CTAuthenKeySym(0x202)
#define Authen_SUNTEK_ClnCmdMsgPollInterval        __CTAuthenKeySym(0x203)
#define Authen_SUNTEK_ClnRespMsgPollInterval       __CTAuthenKeySym(0x204)

#define Authen_SUNTEK_ClnCmdMsgAccount              __CTAuthenKeySym(0x210)
#define Authen_SUNTEK_ClnRespMsgSuccAccount         __CTAuthenKeySym(0x211)
#define Authen_SUNTEK_ClnRespMsgFailAccount         __CTAuthenKeySym(0x212)
#define Authen_SUNTEK_ClnCmdMsgVerify               __CTAuthenKeySym(0x213)
#define Authen_SUNTEK_ClnRespMsgSuccVerify          __CTAuthenKeySym(0x214)
#define Authen_SUNTEK_ClnRespMsgFailVerify          __CTAuthenKeySym(0x215)
#define Authen_SUNTEK_ClnCmdMsgChangePassword       __CTAuthenKeySym(0x216)
#define Authen_SUNTEK_ClnRespMsgSuccChangePassword  __CTAuthenKeySym(0x217)
#define Authen_SUNTEK_ClnRespMsgFailChangePassword  __CTAuthenKeySym(0x218)
#define Authen_SUNTEK_ClnCmdMsgSetNotify            __CTAuthenKeySym(0x219)
#define Authen_SUNTEK_ClnRespMsgSuccSetNotify       __CTAuthenKeySym(0x21a)
#define Authen_SUNTEK_ClnRespMsgFailSetNotify       __CTAuthenKeySym(0x21b)
#define Authen_SUNTEK_ClnCmdMsgGetNotify            __CTAuthenKeySym(0x21c)
#define Authen_SUNTEK_ClnRespMsgSuccGetNotify       __CTAuthenKeySym(0x21d)
#define Authen_SUNTEK_ClnRespMsgFailGetNotify       __CTAuthenKeySym(0x21e)

/******************************************************************************
 * defined Scheduler (Please remind Walker when modified )
 *****************************************************************************/
#define __CTSchedulerKeySym(item)                CTsym_Build( CT_objSCHEDULER,\
                                                              CT_vendSUNTEK,\
                                                              (item) )
#define Scheduler_SUNTEK_Unknown                     __CTSchedulerKeySym(0x001)
#define Scheduler_SUNTEK_TimerReceived               __CTSchedulerKeySym(0x002)
#define Scheduler_SUNTEK_CmdAuthen                   __CTSchedulerKeySym(0x003)
#define Scheduler_SUNTEK_RespAuthen                  __CTSchedulerKeySym(0x004)
#define Scheduler_SUNTEK_CmdSCR                      __CTSchedulerKeySym(0x005)
#define Scheduler_SUNTEK_RespSCR                     __CTSchedulerKeySym(0x006)

#define Scheduler_SUNTEK_RecordCount                 __CTSchedulerKeySym(0x010)
#define Scheduler_SUNTEK_RecordArray                 __CTSchedulerKeySym(0x011)
#define Scheduler_SUNTEK_ArrayIndex                  __CTSchedulerKeySym(0x012)
#define Scheduler_SUNTEK_Caller                      __CTSchedulerKeySym(0x013)
#define Scheduler_SUNTEK_Called                      __CTSchedulerKeySym(0x014)
#define Scheduler_SUNTEK_StartTime                   __CTSchedulerKeySym(0x015)
#define Scheduler_SUNTEK_EndTime                     __CTSchedulerKeySym(0x016)
#define Scheduler_SUNTEK_NotifyWay                   __CTSchedulerKeySym(0x017)

/******************************************************************************
 * CTSI
 *****************************************************************************/
#define __CTCTSIKeySym(item)                CTsym_Build( CT_objCTSI,\
                                                              CT_vendSUNTEK,\
                                                              (item) )
#define CTSI_SUNTEK_Cause					__CTCTSIKeySym(0x001)
#define CTSI_SUNTEK_MenuID					__CTCTSIKeySym(0x002)
#define CTSI_SUNTEK_MenuFuncID				__CTCTSIKeySym(0x003)
#define CTSI_SUNTEK_MenuContent				__CTCTSIKeySym(0x004)
#define CTSI_SUNTEK_IcpOp					__CTCTSIKeySym(0x005)
#define CTSI_SUNTEK_IcpPromptAttr			__CTCTSIKeySym(0x006)


/******************************************************************************
 * GOR
 *****************************************************************************/
#define __CTGORSym(item)                    CTsym_Build( CT_objGOR,\
                                                       CT_vendSUNTEK,\
                                                       (item) )

#define GOR_SUNTEK_Base                     __CTGORSym(0x000)
#define OAM_SUNTEK_Version					__CTGORSym(0x001)


/******************************************************************************
 * SNS
 *****************************************************************************/
#define __CTSNSSym(item)                     CTsym_Build( CT_objSNS,\
                                                    	CT_vendSUNTEK,\
                                                    	(item) )  

#endif

