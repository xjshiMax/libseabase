 #ifndef __CTGOR_H__
#define __CTGOR_H__

#include <map>
#include "cttypes.h"

/////////////////////////////////////////////////////////////////////////////
// Module identification
#define GOR_CommManager		0x00 // CommMain
#define GOR_CommCenter		0x01 // CommMain configure server
#define GOR_HWDevice		0x03 // MG HardWare
#define GOR_SIA 			0x04 // IVR
#define GOR_CommContainer	0x05
#define GOR_CHATSERVER		0x08 //ICS
#define GOR_CTSERVER		0x0A //CCS
#define GOR_PREDIALSERVER	0x0B //OBS
#define GOR_MAINTAINSERVER	0x0D 
#define GOR_VIRTUALDEVICE	0x0E 
#define GOR_Console 		0x0F // Console of CommMain
#define GOR_Configuration	0x11 // ExcelGW CFG    
#define GOR_SwitchControl	0x12 // SwitchControl  
#define GOR_Maint			0x14 // ICS Maint    
#define GOR_ConfigServer	0x15 // Config Server 
#define GOR_Terminal		0x16 //OAMTerm
#define GOR_AAASERVER		0x18 //AAA
#define GOR_DBACCESSSERVER	0x19 //DBA
#define GOR_GATEWAYSERVER	0x1a //GW
#define GOR_CTDGateway 	    0x1b //CTDGW
#define GOR_FaxGateway		0x1c //FAXServer    
#define GOR_NMSSERVER		0x1D 
#define GOR_STM				0x1E //STM
#define GOR_SBC				0x20 //Session border controller，老田同学增加
#define GOR_DtiDevice		0x21 //MG DTI
#define GOR_VoxDevice		0x22 //MG VOX
#define GOR_MsiDevice		0x23 //MG MSI
#define GOR_FaxDevice		0x24 //MG FAX
#define GOR_IptDevice		0x25 //MG IPT
#define GOR_LsiDevice		0x26 //MG LSI
#define GOR_SS7Service		0x27 //SG
#define GOR_SIU						GOR_SS7Service
#define GOR_ConfDevice		0x28 //MG CONFDevice
#define GOR_ConfManager		0x29 //MG CONFModule
#define GOR_H323Device		0x2a //H323Device    ？？？  
#define GOR_VideoGateway	0x2b //VideoGW
#define GOR_MMDevice		0x2c //MG MultiMedia Module
#define GOR_FusionDevice	0x2d //MG NMS fusion Device
#define GOR_H324UnitDevice  0x2e //MG H324 Unit Device lxg add
#define GOR_SipProxy		0x2f //Sip Proxy Module
#define GOR_CallManager		0x31 //CallManager  ??
#define GOR_SoftPhone		0x32 //SoftPhone
#define GOR_StaticsManager	0x33 //CMS
#define GOR_eService		0x34 //
#define	GOR_WebService		0x35 //Web service module
#define GOR_MediaSwitchOAM	0x36 //DS Module use, add by djh 2008/10/06
#define GOR_GM							0x37 //group manager module(RCS of a module) add by djh 2011/04/26
#define GOR_IM							0x38 //instant messaging module(RCS of a module) add by djh 2011/04/26
#define GOR_DBI             0x39 //DBA Interface ？？
#define GOR_OAM				0x3a //OAM ？？
#define GOR_SMI 			0x3b //SMI ？？？
#define GOR_DCM				0x3c //MG OAMModule
#define GOR_RLS				0x3d //Resources list Server module(RCS of a module) add by djh 2011/04/26
#define GOR_PS				0x3e //Presence Server module(RCS of a module) add by djh 2011/04/26
#define GOR_RECORDER		0x3f //ICS RECORDER
#define GOR_TTS				0x40 //TTS
#define GOR_SPY				0x41 //Signal SPY
#define GOR_MissCallGW		0x42 //Miss Call GW
#define GOR_SipServer		0x43 //SipServer module(RCS of a module) add by djh 2011/04/26
#define GOR_XcapServer	0x44 //XcapServer module(RCS of a module) add by djh 2011/04/26
#define GOR_SHARECOMM		0x45 //ICS SHARECOMM
#define GOR_EMediaGW		0x47 //EMG
#define GOR_OiddDP			0x48 //OIDDDP
#define GOR_OiddBalance		0x49 //OIDDBalance
#define GOR_MDDRealTime		GOR_OiddDP
#define GOR_MDDLoadBalance	GOR_OiddBalance //
#define GOR_OiddCS			0x4a //OIDDCS
#define GOR_OiddRM			0x4b //OIDDRM
#define GOR_OiddRDI			0x4c //OIDDRDI
#define GOR_OiddPDI			0x4d //OIDDPDI
#define GOR_SMSC_Load		0x51 //SMSC Load  固网短信
#define GOR_SMSC_Balance	0x52 //SMSC Balance
#define GOR_SMSC_ExecSQL	0x53 //SMSC ExecSQL
#define GOR_SMSC_SMPPClient	0x54 //SMSC SMPPClient
#define GOR_SMGW			0x55 //SMGW
#define GOR_VPRGW     0x56   //Voiceprint Recognition GateWay, added by sl 20100127
#define GOR_ICSCLIENT		0x57 //ICS Client
#define GOR_RecordNode		0x58 //RecordNode
#define GOR_PhoneProxy		0x59 //HPPROXY
#define GOR_QQRouter		0x5a //QQRouter ？？
#define GOR_AsrGW			0x5b //ASRGW
#define GOR_IPMS			0x5c //IPMS
#define GOR_StreamGW		0x5d //Stream GW,RTSP网关，老田同学增加，20081210
#define GOR_ThirdPartyVox	0x5e //MG 第三方device 模块,add by tm,20081220
#define GOR_ConvertServer   0x5f //Convert Server, add by djh 20090226
#define GOR_SipManager		0x61 //SipManager, using for bridged conference, add by lxg 20070228
#define GOR_GSMService 		0x62 //GSM MAP
#define GOR_CDMAService		0x63 //CDMA MAP
#define GOR_ITUTcapService	0x64 //ITU-T TCAP
#define GOR_ANSITcapService	0x65 //ANSI TCAP
#define GOR_GWMODULE 		0x66 //GateWay
#define GOR_MciDevice		0x66 //MC3Device
#define GOR_Mc3Manager		0x67 //MC3Manager  
#define GOR_MediaSvrACD		0x68 //MG SS
#define GOR_BBS 			0x69 //老田临时加上的，明天就知道还要不要
#define GOR_TIMESYNC		0x6a //TimeSync 
#define GOR_VXML			0x6b //VXML
#define GOR_H324Device		0x6c //lxg add for H324
#define GOR_SCF				GOR_SIA
#define GOR_LogModule		0x6d //日志模块，用于CommContainer
#define GOR_PreAlarm 		0x6e //预警模块
#define GOR_CTIAdapter		0x6f //CTI Adapter
#define GOR_FAKEDEVICE		0x70 //Fake device
#define	GOR_SSF				0x71 //SSF
#define GOR_SRF				0x72 //SRF
#define GOR_SDF				0x73 //SDF
#define GOR_CallOut			0x74 //CallOut
#define GOR_IPSoftSwitch	0x75 //IPSoftSwitch 
#define GOR_TFtp			0x76 //TFTP模块
#define GOR_NETMODULE		0x77 //全部联网模块
#define GOR_ComProxyServer	0x78 //全国联网通讯代理服务器模块
#define GOR_ComProxyClient	0x79 //全国联网通讯代理客户端模块
#define GOR_Statistic		0x7a //Statistic
#define GOR_DLLProxy		0x7b //DLL代理模块
#define GOR_SNMPAGENTX		0x7c //SNMP Agent模块
#define GOR_NTP				0x7d //？？ NTP Module
#define GOR_SNMPSERVICE		0x7e //SNMP Service
#define GOR_LicenseServer	0x7f //licenseserver
#define GOR_StreamDevice	0x80 //Stream Server device, using for TB card, add by tangmin 20070205
#define GOR_VAG             GOR_GWMODULE //视频监控  add by wangyequan 20080709
#define GOR_STREAMSERVER    GOR_GWMODULE //视频监控  add by wangyequan 20081019
#define GOR_ExcelSSS         GOR_GWMODULE   //EXCEL系统软件下载服务


//MAX is 0x7F!!!!


// +---------+------+-----------+
// |31     20|19  16|15        0|             A Key
// +---------+------+-----------+
//  StationNo  Type  Alloc Value

// +---------+------+-------+------------+
// |31     20|19  16|15    8|7          0|    A Module Id
// +---------+------+-------+------------+
//  StationNo  Type  Reserve Module Index

const CTuint constGORStationOffset = 20;     // 0 ~ 4095
const CTuint constGORStationMask   = 0xFFF;

const CTuint constGORTypeOffset    = 16;     // 0 ~ F
const CTuint constGORTypeMask      = 0xF;

const CTuint constGORModuleMask    = 0x7F;   // For A Module Id, 0 ~ 255
const CTuint constGORIndexMask     = 0xFFFF; // For A Key,       0 ~ 65535

const CTuint constGORModuleType = 0;
const CTuint constGORModuleRange = 0xFFFF;

const CTuint constGORResourceType = 1;
const CTuint constGORResourceRange = 0xFFFF;

const CTuint constGORSpcType = 2;
const CTuint constGORSpcRange = 0xFFFF;

const CTuint constGORSessionType = 3;
const CTuint constGORSessionRange = 0xFFFF;

const CTuint constGORContainerType = 4;
const CTuint constGORContainerRange = 0xFFFF;

const CTuint constGORGroupType = 5;
const CTuint constGORGroupRange = 0xFFFF;

const CTuint constGORPromptType = 6;
const CTuint constGORPromptRange = 0xFFFF;

const CTuint constGORGatewayType = 7;
const CTuint constGORGatewayRange = 0xFFFF;

const CTuint constGORConferenceType = 8;		// MCU MediaServer	1999-4-6 wsh
const CTuint constGORConferenceRange = 0xFFFF;

const CTuint constGORConferenceControlerType = 9;	// MCU Service	1999-4-6 llz
const CTuint constGORConferenceControlerRange = 0xFFFF;

// Macros to process IDs

#define  MAKEGOR(stationno, type, index) \
		( ( ((stationno)&constGORStationMask)<<constGORStationOffset) | \
		  ( ((type)&constGORTypeMask)<<constGORTypeOffset) | \
		    ((index)&constGORIndexMask) )

#define  MAKEGORRANGE(stationno, type, range) MAKEGOR(stationno, type, range)

// Form an id of a certain kind of module.
#define  MAKEMODULEGOR(stationno, moduleno)     \
		MAKEGOR(stationno, constGORModuleType, (moduleno)&constGORModuleMask)

// Get the station No. from an id.
#define  GETGORSTATION(gorno) \
		( ((gorno)>>constGORStationOffset)&constGORStationMask )

#define  GETGORTYPE(gorno) \
                ( ((gorno)>>constGORTypeOffset)&constGORTypeMask )

// Get the kind of module from an id.
#define  GETGORINDEX(gorno)    ( (gorno)&constGORIndexMask )
#define  GETSTATION(moduleno) GETGORSTATION(moduleno)
// just don't delete it !!!
#define  GETMODULE(moduleno)   ( (moduleno&constGORModuleMask) )

/////////////////////////////////////////////////////////////////////////////
// UDP performence related stuff

#define UDP_VSVMS_PORT 3333

const int MAX_TCBSUM           = 1024;
const int constMAXSTATIONSUM   = MAX_TCBSUM;
const int constMINSTATIONNUM   = 1;
const int constMAXSTATIONNUM   = constMAXSTATIONSUM;
const int constMAXMODULENUM    = 128;
const int constMINMODULEGOR    = 0;
const int constMINCLIENTMODULEGOR = GOR_CommManager+1;
const int constMAXMODULEGOR    = constMAXMODULENUM - 1;
const int constSTATIONDATASIZE = constMAXMODULENUM / 8;
								//(constMAXMODULENUM+7) / 8;

/////////////////////////////////////////////////////////////////////////////
// Alarm Entity

const int constAlarmEntityAdjacent           = 1;
const int constAlarmEntityFlowControl        = 2;
const int constAlarmEntityAbnormal           = 3;
const int constAlarmEntityUDP                = 4;

// Alarm Level
const int constAlarmLevelVenial              = 1;
const int constAlarmLevelMedium              = 2;
const int constAlarmLevelSevere              = 3;

// Alarm No.
const int constAlarmNoActivate               = 1;
const int constAlarmNoDeactivate             = 2;
const int constAlarmNoModuleActivate         = 3;
const int constAlarmNoModuleDeactivate       = 4;
const int constAlarmNoStationConnect         = 5;
const int constAlarmNoStationDisconnect      = 6;

const int constAlarmNoValveSet               = 1;
const int constAlarmNoValveClear             = 2;
const int constAlarmNoUnknownModule          = 3;
const int constAlarmNoUnknownStation         = 4;

const int constAlarmNoModuleAbort            = 1;
const int constAlarmNoStationAbort           = 2;

const int constAlarmNoQueueFull              = 1;
const int constAlarmNoTCBPause               = 2;
const int constAlarmNoDeliverFailure         = 3; // Not used

class TAppTypeDef
{
public:
	enum
	{
		InvalidAppType  = 0x0000,

		DirectoryServer = 0x0015,

		Container       = 0x0002,		

		IVR             = 0x0004,
		AppServer       = 0x0104,
		VxmlServer      = 0x0204,
					
		CCS             = 0x000a,
		CCSApp          = 0x010a,
		
		OBS             = 0x000b,
		OCS             = 0x010b,
		OCS3             = 0x030b,
		SoftACD			= 0x0012,
		CSCF            = 0x0112,
		CALLSERVER            = 0x0212,
		CTIServer_cvct	= 0x0812,
		
		ICSMaint        = 0x0014,
		AAA             = 0x0018,
	  AAA_OCS             = 0x0118,
	  AAA_VAC             = 0x0218,	
		
		DBA_odbc        = 0x0019,
		DBA_conn        = 0x0119,
		DBAdvance		= 0x0219,
		
		GWServer		= 0x001a,
		AAA_Proxy		= 0x011a,
		AIC_IVR_GW		= 0x021a,
		VAC_GW			= 0x031a,
		OCS_GW			= 0x041a,
		VideoShare_GW	= 0x051a,
		CTD_GW          = 0x061a,
		OMC					= 0x71a,

		FaxServer       = 0x001c,
		FaxGW3          = 0x011c,	
		NMSServer       = 0x001d,
		SBC             = 0x0020,
		MediaGW_dlg     = 0x0021,
		MediaGW_nms     = 0x0121,
		MediaGW_excel   = 0x0221,
		MediaGW_yh      = 0x0321,
		MediaGW_tb		= 0x0421,
		MediaGW_ocmp    = 0x0521,
		SIMMG           = 0x0721,
		MediaGW_eastcom = 0x0821,
		MediaServer_eastcom = 0x0822, 
    IPMG            = 0x0921,
    MediaGW_dlg_ms  = 0x0a21,  
    
		
		MediaServer_dlg = 0x0022,	
		MediaServer_nms = 0x0122,
		MediaServer_tb  = 0x0422,
			
    MediaServer_dlg_ms  = 0x0a22,
    MediaServer_dlg_acta_ngn  = 0x0b22,
    MediaServer_ac		= 0x0c22,
      			
		SignalGW_dlg    = 0x0027,
		SignalGW_nms    = 0x0127,
		MediaSwitch_SG  = 0x0627,
		SIMSG           = 0x0727,
	
		SignalGW_dlg_ms    = 0x0a27,		
		
		ICS				= 0x0029,	
		ConfProxy		= 0x0129,
		PolicyServer	= 0x0229,
		SPProxy         = 0x0032,
		CMS             = 0x0033,		
		ESERVICE        = 0x0034,

		WebMonitor		= 0x0035,		

		ExcelSSS        = 0x0036,
		GM							= 0x0037,
		IM							= 0x0038,
		RLS							=	0x003d, 
		PS							=	0x003e,
		
		RecordServer_syb= 0x003f,
		RecordServer_odbc= 0x013f,
		
		SipServer				=	0x0043,
		XcapServer			=	0x0044,
		EMG             = 0x0047,

		OiddDP			= 0x0048,
		OiddBalance		= 0x0096,
		OiddCS			= 0x004a,
		OiddRM			= 0x004b,
		OiddRDI			= 0x004c,
		OiddPDI			= 0x004d,
		MDDRealTime     = OiddDP,
		MDDLoadBalance	= OiddBalance,

		TTSGW           = 0x0040,
		TTSGW_iFly		= 0x0140,
		TTSGW_IT		= 0x0240,
		TTSGW_Sino		= 0x0340,
		TTSGW_MS        = 0x0440,        //添加微软TTS支持,

		SignalSpy		= 0x0041,
		MissCallGW		= 0X0042,
		ResourceManager =0x0043,

		QQRoute         = 0x0049,
		
		VPRGW						= 0x0056,

		RecordNode      = 0x0058,
		RecordNode_EJIN = 0x0158,
		RecordNode_CAP  = 0x0258,           //通过获取rtp的数据包进行录音
		RecordNode_HPX  = 0x0358,           //使用HPXMedia驱动进行录音
		
		HPProxy         = 0x0059,
		
    ASRGW           = 0x005b,
		StreamGW		= 0x005d,           //add by tzj 20081210

		SipManager		= 0x0061,           //add by lxg 20070604

		GWModule        = 0x0066,
		LogServer		= 0x006d,
		PreAlarm        = 0x006e,		
    Mc3Manager      = 0x0067,
        

    CTIAdapter_cvct = 0x006f,        
    CTIAdapter_icm  = 0x016f,
    CTIAdapter_genesys= 0x026f,
        
    FTPProxy		= 0x0076,
    SPManager		= 0x0077,
    TermManager		= 0x0177,
        
    ProxyServer     = 0x0078,
    ProxyClient     = 0x0079,
                
		SNMPAgent       = 0x007c,

		LicenseServer   = 0x007f,
		
		AutoTestAgent   = 0x0082,



    SingleApplication = 0xfffb,
	SinglePcApp		  = 0xfffc, //add on 2009.08.28

    UNKNOWN         = 0xffff
	};	
	static CTuint   GetMainAppType(CTuint value) { return value & 0x00ff ; }
	static CTuint   GetSubAppType(CTuint value) { return (value & 0xff00) >> 8; } 
	static CTuintArray GetConRelAppType(CTuint appType);
};
	
class TGorNameMap:public std::map<CTuint,CTstring>
{
public:
	TGorNameMap()
	{
		(*this)[GOR_CommManager]="CommMain";
		(*this)[GOR_CommCenter]="CommMain configure server";
		(*this)[GOR_HWDevice]="MG HardWare";
		(*this)[GOR_SIA]="IVR";
		(*this)[GOR_CHATSERVER]="ICS CHATSERVER";
		(*this)[GOR_CTSERVER]="CCS";
		(*this)[GOR_PREDIALSERVER]="OBS";
		(*this)[GOR_VIRTUALDEVICE]="VirtualDevice";
		(*this)[GOR_Console]="Console of CommMain";
		(*this)[GOR_Configuration]="ExcelGW CFG";   
		(*this)[GOR_SwitchControl]="SwitchControl";
		(*this)[GOR_Maint]="ICS Maint";  
		(*this)[GOR_ConfigServer]="Config Server";
		(*this)[GOR_Terminal]="OAMTerm";
		(*this)[GOR_AAASERVER]="AAA";
		(*this)[GOR_DBACCESSSERVER]="DBA";
		(*this)[GOR_GATEWAYSERVER]="PreAlarm";
		(*this)[GOR_FaxGateway]="FAXServer"; 
		(*this)[GOR_STM]="STM"; 
		(*this)[GOR_DtiDevice]="MG DTI";
		(*this)[GOR_VoxDevice]="MG VOX";
		(*this)[GOR_MsiDevice]="MG MSI";
		(*this)[GOR_FaxDevice]="MG FAX";
		(*this)[GOR_IptDevice]="MG IPT";
		(*this)[GOR_LsiDevice]="MG LSI";
		(*this)[GOR_SS7Service]="SG";
		(*this)[GOR_ConfDevice]="MG CONFDevice";
		(*this)[GOR_ConfManager]="MG CONFModule";
		(*this)[GOR_H323Device]="H323Device";
		(*this)[GOR_VideoGateway]="VideoGW";
		(*this)[GOR_CallManager]="CallManager";
		(*this)[GOR_SoftPhone]="SoftPhone";
		(*this)[GOR_StaticsManager]="CMS";
		(*this)[GOR_WebService]="WebService";
		(*this)[GOR_OAM]="OAM";
		(*this)[GOR_SMI]="SMI";
		(*this)[GOR_DCM]="MG OAMModule";
		(*this)[GOR_RECORDER]="ICS RECORDER";
		(*this)[GOR_TTS] ="TTS";
		(*this)[GOR_SPY] ="Signal SPY";
		(*this)[GOR_SHARECOMM]="ICS SHARECOMM";
		(*this)[GOR_EMediaGW]="EMG";
		(*this)[GOR_SMSC_Load]="SMSC Load";
		(*this)[GOR_SMSC_Balance]="SMSC Balance";
		(*this)[GOR_SMSC_ExecSQL]="SMSC ExecSQL";
		(*this)[GOR_SMSC_SMPPClient]="SMSC SMPPClient";
		(*this)[GOR_SMGW]="SMGW";
		(*this)[GOR_VPRGW]="VPRGW";
		(*this)[GOR_ICSCLIENT]="ICS Client";
		(*this)[GOR_RecordNode]="RecordNode";
		(*this)[GOR_PhoneProxy]="HPPROXY";
		(*this)[GOR_QQRouter]="QQRouter";
		(*this)[GOR_AsrGW]="ASRGW";
		(*this)[GOR_GSMService]="GSM MAP";
		(*this)[GOR_CDMAService]="CDMA MAP";
		(*this)[GOR_ITUTcapService] ="ITU-T TCAP";
		(*this)[GOR_ANSITcapService]="ANSI TCAP";
		(*this)[GOR_GWMODULE]="GateWay";
		(*this)[GOR_MciDevice]="MC3Device";
		(*this)[GOR_Mc3Manager]="MC3Manager";  
		(*this)[GOR_MediaSvrACD]="MG SS";
		(*this)[GOR_TIMESYNC]="TimeSync";
		(*this)[GOR_VXML]="VXML";
		(*this)[GOR_H324Device]="H324Module";
		(*this)[GOR_SSF]="SSF";
		(*this)[GOR_SRF]="SRF";
		(*this)[GOR_SDF]="SDF";
		(*this)[GOR_CallOut]="CallOut";
		(*this)[GOR_NETMODULE]="NetModule";
		(*this)[GOR_ComProxyServer]="ProxyServer";
		(*this)[GOR_ComProxyClient]="ProsyClient";
		(*this)[GOR_Statistic]="Statistic";
		(*this)[GOR_DLLProxy]="DLLProsy";
		(*this)[GOR_SNMPAGENTX]="SNMP Agent";
		(*this)[GOR_NTP]="NTP Module";
		(*this)[GOR_SNMPSERVICE]="SNMP Service";
		(*this)[GOR_CommContainer]="CommContainer";
		(*this)[GOR_FAKEDEVICE]="FakeDevice";
		(*this)[GOR_LogModule]="LogModule";
		(*this)[GOR_TFtp]="TFtp";	
		(*this)[GOR_MAINTAINSERVER]="MAINTAINSERVER";			
		(*this)[GOR_NMSSERVER]="NMSSERVER";
		(*this)[GOR_IPSoftSwitch]="IPSoftSwitch";
		(*this)[GOR_LicenseServer]="LicenseServer";
		(*this)[GOR_BBS]="BBS";
	}
};

class TGorDescript
{
public:	
	TGorDescript(){};
public:
	static const char *getName(int gor)
	{
		static TGorNameMap m_gorNameMap;
		static const char* pUnknownModule="Unknown Module";

		TGorNameMap::iterator it=m_gorNameMap.find(gor);
		if( it!=m_gorNameMap.end())
			return it->second.c_str();
		else 
			return pUnknownModule;
	}
	static CTstring &getNameString(int gor)
	{
		static CTstring strModuleName;
		strModuleName=getName(gor);
		return strModuleName;
	}
};
#endif
