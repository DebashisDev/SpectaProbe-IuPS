/*
 * TCPGlobal.h
 *
 *  Created on: Nov 14, 2015
 *      Author: debashis
 */

#ifndef INC_IPGLOBAL_H_
#define INC_IPGLOBAL_H_

#include <pthread.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <array>
#include <bitset>

#include "GTPMsg.h"
#include "SpectaTypedef.h"
#include "TCP-UDPMsg.h"
#include "IPV4Msg.h"
#include "ETHMsg.h"
#include "GConfig.h"

using namespace std;

// Need to move to Global Defination file

#define MAX_INTERFACE_SUPPORT	4

#define XDR_MAX_LEN			5000
#define TDR_MAX_LEN			10000
#define XDR_RECORDS_BATCH_SIZE	1000
#define VPS_MAX_LEN				2000
#define MAX_VPS_ELEMENTS		600
#define MAX_CLEAN_COUNT	100000

#define ZMQ_FLUSHER_REPOSITORY_LIMIT	500000
#define TRACE_QUEUE_LIMIT				1000

#define SESSION_ID_LEN  	40		//sip_sp_dip_dp_appid
#define IMSI_LEN			20
#define MSISDN_LEN			16
#define IMEI_LEN			20
#define APN_LEN		 		50
#define DNS_LEN		 		50
#define URL_LEN		 		50
#define CONTENT_TYPE_LEN	20
#define DESC_LEN			100

#define DNS_MAX_IPS			10

#define RANAP_SESSION	1
#define GMM_SESSION		2
#define MME_SESSION		3
#define MAX_VI_SUPPORT	10

#define MAC_ADDR_LEN		18
#define IP_ADDR_LEN 		40

#define MAX_ADDR_LENGTH  40
#define MAX_IMSI_LEN 17
#define MAX_APN_LENGTH 100

#define XDR_ID_IP_SESSION 			10
#define XDR_ID_IP_BW 				11
#define XDR_ID_IP_DNS_SESSION		12
#define XDR_ID_GTPC_SESSION 		20
#define XDR_ID_GTPC_SESSION_CNT		21

#define FLUSH_TYPE_CR_REQ_NO_TEID 	10
#define FLUSH_TYPE_CR_REQ_RESREQ 	11
#define FLUSH_TYPE_CR_REQ_DUP 		12
#define FLUSH_TYPE_CR_RES_NO_TEID 	13
#define FLUSH_TYPE_CR_RES_REQRES 	14
#define FLUSH_TYPE_CR_RES_DUP 		15
#define FLUSH_TYPE_CR_RES_NO_REQ	16

#define FLUSH_TYPE_UP_REQ_NO_TEID  	20
#define FLUSH_TYPE_UP_REQ_RESREQ 	21
#define FLUSH_TYPE_UP_REQ_DUP 		22
#define FLUSH_TYPE_UP_RES_NO_TEID 	23
#define FLUSH_TYPE_UP_RES_REQRES 	24
#define FLUSH_TYPE_UP_RES_DUP 		25
#define FLUSH_TYPE_UP_RES_NO_REQ	26

#define FLUSH_TYPE_DL_REQ_NO_TEID 	30
#define FLUSH_TYPE_DL_REQ_RESREQ 	31
#define FLUSH_TYPE_DL_REQ_DUP 		32
#define FLUSH_TYPE_DL_RES_NO_TEID 	33
#define FLUSH_TYPE_DL_RES_REQRES 	34
#define FLUSH_TYPE_DL_RES_DUP 		35
#define FLUSH_TYPE_DL_RES_NO_REQ 	36

#define FLUSH_TYPE_CLEANUP 			40

//How many total active IP Sessions that can be stored per SM
//Assuming 200K PPS 100K Sessiosn per Sec all goes to one SM, with 30 sec cleanup 3M per SM
#define IP_SESSION_POOL_ARRAY_ELEMENTS	100
#define IP_SESSION_POOL_ARRAY_SIZE		10000

#define DNS_SESSION_POOL_ARRAY_ELEMENTS	100
#define DNS_SESSION_POOL_ARRAY_SIZE		5000

#define IUPS_SESSION_POOL_ARRAY_ELEMENTS	100
#define IUPS_SESSION_POOL_ARRAY_SIZE		2000

#define PACKET_NO					200000

//#define TIME_INDEX(sec) (sec / 10) % 3
//#define NEXT_TIME_INDEX(idx) (idx+1) % 3

#define PKT_WRITE_TIME_INDEX(epochsec) ( ((epochsec % 10) + 1) > 9 ? 0 : ((epochsec % 10) + 1) )
#define PKT_READ_TIME_INDEX(epochsec) ( epochsec % 10 )
#define PKT_READ_NEXT_TIME_INDEX(idx) ( (idx+1) > 9 ? 0 : (idx+1) )

#define WRITE_TIME_INDEX(epochsec) ( (((epochsec % 50) / 5) + 1) > 9 ? 0 : (((epochsec % 50) / 5) + 1) )
#define READ_TIME_INDEX(epochsec) ( (epochsec % 50) / 5 )
#define NEXT_TIME_INDEX(idx) ( (idx+1) > 9 ? 0 : (idx+1) )

//#define WRITE_TIME_INDEX(epochsec) ( ((epochsec % 10) + 1) > 9 ? 0 : (epochsec % 10) + 1 )
////#define WRITE_TIME_INDEX_GTPU(sec) ( ((sec % 10) + 1) > 9 ? 0 : (sec % 10) + 1 )
//#define READ_TIME_INDEX(sec) ( ((sec % 10) - 1) < 0 ? 9 : ((sec % 10) - 1) )
////#define READ_TIME_INDEX(sec) ( sec % 10)
//#define NEXT_TIME_INDEX(idx) ( (idx+1) > 9 ? 0 : (idx+1) )
//
////#define WRITE_TIME_INDEX(sec) ( ((sec % 10) + 1) > 9 ? 0 : (sec % 10) + 1 )
////#define READ_TIME_INDEX(sec) ( ((sec % 10) - 1) < 0 ? 9 : ((sec % 10) - 1) )
////#define NEXT_TIME_INDEX(idx) ( (idx+1) > 9 ? 0 : (idx+1) )
//
//#define FLUSHER_WRITE_TIME_INDEX(sec) ( (((sec % 100) / 10) + 1) > 9 ? 0 : (((sec % 100) / 10) + 1) )
//#define FLUSHER_READ_TIME_INDEX(sec) ( (((sec % 100) / 10) - 1) < 0 ? 9 : (((sec % 100) / 10) - 1) )
////#define FLUSHER_READ_TIME_INDEX(sec) ( (sec % 100) / 10)
//#define FLUSHER_NEXT_TIME_INDEX(idx) ( (idx+1) > 9 ? 0 : (idx+1) )

//For 0 - 9, current sec writing, prev to prev for reading
//#define WRITE_TIME_INDEX(sec) (sec % 10)
//#define PREV_SEC(sec) ((sec-1) < 0 ? 59 : (sec -1))
//#define READ_TIME_INDEX(sec) ( ((PREV_SEC(sec) -1) < 0 ? 59 : (PREV_SEC(sec) - 1)) % 10 )
//#define NEXT_TIME_INDEX(idx) ((idx+1) > 9 ? 0 : (idx+1))

//For 0 - 5, current sec writing, prev to prev for reading
//#define WRITE_TIME_INDEX(sec) (sec % 5)
//#define PREV_SEC(sec) ((sec-1) < 0 ? 59 : (sec -1))
////#define READ_TIME_INDEX(sec) ( ((PREV_SEC(sec) -1) < 0 ? 59 : (PREV_SEC(sec) - 1)) % 5 )
//#define READ_TIME_INDEX(sec) ( ((sec -1) < 0 ? 59 : (sec - 1)) % 5 )
//#define NEXT_TIME_INDEX(idx) ((idx+1) > 5 ? 0 : (idx+1))



namespace GContainer
{ extern GConfig *config; }

enum dnsResponse
{
	QUERY 		= 0,
	RESPONSE 	= 1,
	STATUS 		= 2,
	UNASSIGNED 	= 3,
	NOTIFY 		= 4,
	UPDATE 		= 5
};

typedef enum
{
	PACKET_IPPROTO_IP 		= 0,	/** Dummy protocol for TCP		*/
	PACKET_IPPROTO_HOPOPTS 	= 0,	/** IPv6 Hop-by-Hop options		*/
	PACKET_IPPROTO_ICMP 	= 1,	/** Internet Control Message Protocol */
	PACKET_IPPROTO_IGMP 	= 2,	/** Internet Group management Protocol */
	PACKET_IPPROTO_IPIP 	= 4,	/** IPIP tunnels (older KA9Q tunnels use 94) */
	PACKET_IPPROTO_TCP		= 6,	/** Transmission Control Protocol	*/
	PACLET_IPPROTO_EGP 		= 8,	/** Exterior Gateway Protocol */
	PACKET_IPPROTO_PUP 		= 12,	/** PUP Protocol */
	PACKET_IPPROTO_UDP 		= 17,	/** User Datagram Protocol		*/
	PACKET_IPPROTO_DNS 		= 18,	/** DNS		*/
	PACKET_IPPROTO_IDP 		= 22,	/** XNS IDP protocol */
	PACKET_IPPROTO_TP 		= 29,	/** SO Transport Protocol Class 4. */
	PACKET_IPPROTO_DCCP 	= 33,	/** Datagram Congestion Control Protocol. */
	PACKET_IPPROTO_IPV6 	= 41,	/** IPv6 header */
	PACKET_IPPROTO_ROUTING 	= 43,	/** IPv6 Routing header */
	PACKET_IPPROTO_FRAGMENT = 44,	/** IPv6 fragmentation header */
	PACKET_IPPROTO_RSVP 	= 46,	/** Reservation Protocol */
	PACKET_IPPROTO_GRE 		= 47,	/** General Routing Encapsulation */
	PACKET_IPPROTO_GTPU 	= 48,	/** GTPU Protocol		*/
	PACKET_IPPROTO_GTPC 	= 49,	/** GTPC Protocol		*/
	PACKET_IPPROTO_ESP 		= 50,	/** encapsulating security Payload */
	PACKET_IPPROTO_AH 		= 51,	/** Authentication header */
	PACKET_IPPROTO_GX 		= 52,	/** GTPU Protocol		*/
	PACKET_IPPROTO_RADIUS 	= 53,	/** RADIUS Protocol		*/
	PACKET_IPPROTO_ICMPV6 	= 58,	/** ICMPV6 */
	PACKET_IPPROTO_NONE 	= 59,	/** IPv6 no next header */
	PACKET_IPPROTO_DSTOPTS 	= 60,	/** IPv6 destination options */
	PACKET_IPPROTO_MTP 		= 92,	/** Multicast Transport Protocol */
	PACKET_IPPROTO_ENCAP 	= 98,	/** Encapsulation Header */
	PACKET_IPPROTO_PIM 		= 103,	/** Protocol Independent Multicast */
	PACKET_IPPROTO_COMP 	= 108,	/** Compression Header Protocol */
	PACKET_IPPROTO_SCTP 	= 132,	/** SCTP Protocol		*/
	PACKET_IPPROTO_UDPLITE 	= 136,	/** UDP-Lite protocol */
	PACKET_IPPROTO_RAW 		= 255	/** Raw IP Packets */
}IPProtocolTypes;

typedef struct _xdrStore
{
	int idx;
	char xdr[XDR_MAX_LEN];

	_xdrStore()
	{
		reset();
	}
	_xdrStore(const _xdrStore& obj)
	{
		this->idx = obj.idx;
		strcpy(this->xdr, obj.xdr);
	}
	void set(const _xdrStore *obj)
	{
		this->idx = obj->idx;
		strcpy(this->xdr, obj->xdr);
	}
	void copy(const _xdrStore* obj)
	{
		this->idx = obj->idx;
		strcpy(this->xdr, obj->xdr);
	}
	void operator=(const _xdrStore& obj)
	{
		this->idx = obj.idx;
		strcpy(this->xdr, obj.xdr);
	}
	void reset()
	{
		this->idx = 0;
		strcpy(this->xdr, "");
	}
}xdrStore;

inline string getSessionId(string sessionKey, ULONG frEpochTimeNanoSec)
	{
		char buffer[40];
		sprintf(buffer, "%s_%ld", sessionKey.c_str(), frEpochTimeNanoSec);
		return string(buffer);
	}

typedef enum{
	HTTP 	= 2,
	BW 		= 3,
	IUPS	= 21,
	SCCP	= 22,
	NONTCPUDP	= 20
}protocolId;

typedef enum {
	DNS_PORT 	= 53,
	HTTP_PORT 	= 80,
	HTTPS_PORT 	= 443,
	GTPU_PORT 	= 2152,
	GTPC_PORT 	= 2123,
	GTPC_PORT1 	= 3386,
	HTTP_PORT1 	= 8080,
	GX_PORT		= 3868,
	RADIUS_AUTH	= 1812,
	RADIUS_ACCO = 1813,
	RADIUS_AUTH1= 31812,
	RADIUS_ACCO1 = 31813
};

typedef struct {
  int startIp;
  int mask;
}_ipRange;

namespace ipRange{
	extern int totalIps;
	extern _ipRange ipRange[100];
}


namespace PCons
{
	extern bool WARNING;
	extern bool DEBUG;
	extern bool TRACE;
	extern bool LOG;

	extern bool P_MTP3;
	extern bool P_SCTP;
	extern bool P_SCCP;
	extern bool P_SCCPSM;
	extern bool P_RANAP;
	extern bool P_NAS;
	extern bool P_IUPSSM;
	extern bool P_MME;
	extern bool P_MME_NAS;

	extern long PKT_COUNT;

	extern long r_pkt_cnt;
	extern long r_line_cnt;

	extern long sccp_s_cnt;
	extern long iups_s_cnt;
	extern long gmm_s_cnt;
	extern long r_s_cnt;

	extern long sccp_flush_cnt;
	extern long iups_flush_cnt;

	extern long sccp_flush_init_cnt;
	extern long iups_flush_init_cnt;

	extern long iups_gmm_flush_init_cnt;
	extern long iups_ranap_flush_init_cnt;

}

/*
 * FrameData structure should be in Global.h as it is been used by diffrent packet source
 */

typedef struct _frameData
{
	string		interfaceName;
	ULONG		frameCount;
	string 		frameTimeStamp;
	ULONG 		epochTimeMicroSec;
	ULONG	    epochTimeMilliSec;
	ULONG		epochTimeSec;
	ULONG		frameSize;			/* Frame size in Bytes */
	uint32_t	frameSecond;		/* Short Second Part */
	uint32_t	frameMinute;		/* Short Minutes Part */
	bool		frameDirUp;

	_frameData()
	{ reset(); }

	void reset()
	{
		interfaceName = "NA";
		frameCount = 0;
		frameTimeStamp = "NA";
		epochTimeMicroSec = 0;
		epochTimeMilliSec = 0;
		epochTimeSec = 0;
		frameSize = 0;
		frameSecond = 0;
		frameMinute = 0;
		frameDirUp = true;
	}

	void set (const _frameData *obj)
	{
		reset();

		this->interfaceName	 	= obj->interfaceName;
		this->frameCount 		= obj->frameCount;
		this->frameTimeStamp 	= obj->frameTimeStamp;
		this->epochTimeMicroSec = obj->epochTimeMicroSec;
		this->epochTimeMilliSec = obj->epochTimeMilliSec;
		this->epochTimeSec 		= obj->epochTimeSec;
		this->frameSize 		= obj->frameSize;
		this->frameSecond 		= obj->frameSecond;
		this->frameMinute 		= obj->frameMinute;
		this->frameDirUp 		= obj->frameDirUp;
	}
}frameVar;

typedef struct _RawPkt
{
	uint16_t	len;
	long 		tv_sec;
	uint32_t 	tv_nsec;
	BYTE		pkt;
	uint64_t 	pkt_no;

	_RawPkt() {
		reset();
		pkt = (BYTE) malloc(2048);
	}

	_RawPkt(const _RawPkt& rpkt) {
		len 	= rpkt.len;
		tv_sec 	= rpkt.tv_sec;
		tv_nsec = rpkt.tv_nsec;
		pkt 	= rpkt.pkt;
		pkt_no	= rpkt.pkt_no;
	}

	void copy(const _RawPkt* rpkt) {
		len 	= rpkt->len;
		tv_sec 	= rpkt->tv_sec;
		tv_nsec = rpkt->tv_nsec;
		pkt 	= rpkt->pkt;
		pkt_no	= rpkt->pkt_no;
	}

	void operator=(const _RawPkt& rpkt) {
		len 	= rpkt.len;
		tv_sec 	= rpkt.tv_sec;
		tv_nsec = rpkt.tv_nsec;
		pkt 	= rpkt.pkt;
		pkt_no	= rpkt.pkt_no;
	}

	void reset() {
		len = 0;
		tv_sec = 0;
		tv_nsec = 0;
		pkt_no = 0;
	}

}RawPkt;


//class  TPacket{
//	public:
//		otrIP4Var	*otrIP4Data;
//		frameVar	*frameData;
//		ethernetVar *ethernetData;
//		ipVar 		*ipData;
//		tcpVar 		*tcpData;
//		udpVar 		*udpData;
//		dnsVar 		*dnsData;
////		gxVar 		*gxData;
//		gtpV1Msg	*gtpV1Data;
//
//		int			threadId;
//		string		sessionKey;
//
//		TPacket()
//		{
//			otrIP4Data	= new otrIP4Var();
//			frameData 	= new frameVar();
//			ethernetData= new ethernetVar();
//			ipData 		= new ipVar();
//			tcpData 	= new tcpVar();
//			udpData 	= new udpVar();
//			dnsData 	= new dnsVar();
////			gxData		= new gxVar();
//			gtpV1Data	= new gtpV1Msg();
//			threadId    = 0;
//			sessionKey  = "";
//		}
//
//		~TPacket()
//		{
//			delete 	otrIP4Data;
//			delete	frameData;
//			delete  ethernetData;
//			delete  ipData;
//			delete  tcpData;
//			delete  udpData;
//			delete  dnsData;
////			delete 	gxData;
//			delete 	gtpV1Data;
//		}
//
//		void reset()
//		{
//			otrIP4Data->reset();
//			frameData->reset();
//			ethernetData->reset();
//			ipData->reset();
//			tcpData->reset();
//			udpData->reset();
//			dnsData->reset();
////			gxData->reset();
//			gtpV1Data->reset();
//		}
//
//		void set(TPacket &msgObj)
//		{
//			otrIP4Data->set(msgObj.otrIP4Data);
//			frameData->set(msgObj.frameData);
//			ethernetData->set(msgObj.ethernetData);
//			ipData->set(msgObj.ipData);
//			tcpData->set(msgObj.tcpData);
//			udpData->set(msgObj.udpData);
//			dnsData->set(msgObj.dnsData);
////			gxData->set(msgObj.gxData);
//			gtpV1Data->set(msgObj.gtpV1Data);
//		}
//};

typedef struct _SCTP
{
	unsigned int sctp_tsn;
	unsigned int sctp_sequence_no;
	int sctp_opc;
	int sctp_dpc;
	int sctp_protocol;

	/* SCCP Data */
	char 	sccp_slr[10];
	char 	sccp_dlr[10];
	char 	sccp_session_id[20];
	int 	sccp_message_type;
	char	sccp_message_desc[DESC_LEN];
	int 	sccp_release_cause;
	char	sccp_release_desc[DESC_LEN];
	bool	sccp_ranap_present;

	/* IUPS Data */
	unsigned int iups_packetLengthRANAP;
	int 	iups_packetLengthNAS;
	//Two types of transaction sessions maintained
	// RANAP session or GMM session, they are mutually exclusive
	// and is determined by the value stored in sessiontype
	int 	iups_sessiontype;
	bool 	iups_rsessionstart;
	bool 	iups_rsessionend;
	bool 	iups_gmmsessionstart;
	bool 	iups_gmmsessionintmd;
	bool 	iups_gmmsessionend;
    unsigned int iups_ranap_bytes;
    char	iups_session_ranap_id[DESC_LEN];		//ranap session key of the session originating procedure
	int 	iups_procedure_code;
	char 	iups_procedure_desc[DESC_LEN];
    int 	iups_session_mmsm_id;		//mmsm_id of the session originating procedure
    int 	iups_mmsm_id;
    char	iups_mmsm_desc[DESC_LEN];
    //Session specific parameters
    //will be set either by a RANAP session or MMSM session
    int 	iups_RABCauseId;
    char	iups_RABCauseDesc[DESC_LEN];
    char	iups_Mbrupl[10];
    char	iups_Mbrdnl[10];
    char	iups_ExtendedMbr[10];
    char 	iups_RABId[DESC_LEN];
    char 	iups_TEId[DESC_LEN];
    char 	iups_PDPType[DESC_LEN];
    int 	iups_RAUpdateId;
    int 	iups_EndCauseId;
    char 	iups_EndCauseDesc[DESC_LEN];
    int 	iups_AttachDetachId;
    char 	iups_AttachDetachDir[DESC_LEN];
    char 	iups_AttachDetachDesc[DESC_LEN];
    int 	iups_PDPStaticAddressRequested;
    char 	iups_PDPAddressRequested[DESC_LEN];
    char 	iups_PDPAddressAllocated[DESC_LEN];
    char 	iups_RNCId[DESC_LEN];
    char	iups_LACIdHex[DESC_LEN];
    long	iups_LACIdDec;
    char	iups_RACIdHex[DESC_LEN];
    long	iups_RACIdDec;
    char	iups_SACIdHex[DESC_LEN];
	long	iups_SACIdDec;
    char	iups_PLMNIdHex[DESC_LEN];
    char 	iups_RAIOldHex[DESC_LEN];
    char 	iups_RAIOldDec[DESC_LEN];
    char 	iups_RAINewHex[DESC_LEN];
    char 	iups_RAINewDec[DESC_LEN];
	char	iups_IMSI[IMSI_LEN];
	char	iups_TMSI[IMSI_LEN];
	char	iups_IMEI[IMEI_LEN];
	char	iups_MSISDN[MSISDN_LEN];
	char	iups_APN[APN_LEN];

	uint16_t iups_pdp_Mbrupl;
	uint16_t iups_pdp_Mbrdnl;
	uint16_t iups_pdp_ExtMbrdnl;


    _SCTP()
    { reset(); }

    void reset()
    {
    	sctp_reset();
    	sccp_reset();
    	iups_reset();
    }

    void sctp_reset()
	{
		/* SCTP Data */
		sctp_tsn = 0;
		sctp_sequence_no = 0;
		sctp_opc = 0;
		sctp_dpc = 0;
		sctp_protocol = 0;
	}

	void sccp_reset()
	{
		/* SCCP Data */
		strcpy(sccp_slr, "NA");
		strcpy(sccp_dlr, "NA");
		strcpy(sccp_session_id, "NA");	//Important to keep "NA" as it is used to validate in later sections
		sccp_message_type = -1;
		strcpy(sccp_message_desc, "NA");
		sccp_release_cause = -1;
		strcpy(sccp_release_desc, "NA");
		sccp_ranap_present = false;
	}

	void iups_reset()
	{
		/* IUPS Data */
		iups_packetLengthRANAP = 0;
		iups_packetLengthNAS = 0;
		//Two types of transaction sessions maintained
		// RANAP session or GMM session, they are mutually exclusive
		// and is determined by the value stored in sessiontype
		iups_sessiontype = 0;
		iups_rsessionstart = false;
		iups_rsessionend = false;
		iups_gmmsessionstart = false;
		iups_gmmsessionintmd = false;
		iups_gmmsessionend = false;
		iups_ranap_bytes = 0;
		iups_session_ranap_id[0] = 0;		//ranap session key of the session originating procedure
		iups_procedure_code = -1;
		iups_procedure_desc[0] = 0;
		iups_session_mmsm_id = -1;		//mmsm_id of the session originating procedure
		iups_mmsm_id = -1;
		iups_mmsm_desc[0] = 0;
		//Session specific parameters
		//will be set either by a RANAP session or MMSM session
		iups_RABCauseId = -1;
		iups_RABCauseDesc[0] = 0;
	    strcpy(iups_Mbrupl, "0");
	    strcpy(iups_Mbrdnl, "0");
	    strcpy(iups_ExtendedMbr, "0");
		iups_RABId[0] = 0;
		iups_TEId[0] = 0;
		iups_PDPType[0] = 0;
		iups_RAUpdateId = -1;
		iups_EndCauseId = -1;
		iups_EndCauseDesc[0] = 0;
		iups_AttachDetachId = -1;
		//int AttachDetachDir;
		iups_AttachDetachDir[0] = 0;
		iups_AttachDetachDesc[0] = 0;
		iups_PDPStaticAddressRequested = -1;
		iups_PDPAddressRequested[0] = 0;
		iups_PDPAddressAllocated[0] = 0;
		iups_RNCId[0] = 0;
		iups_LACIdHex[0] = 0;
		iups_LACIdDec = 0;
		iups_RACIdHex[0] = 0;
		iups_RACIdDec = 0;
		iups_SACIdHex[0] = 0;
		iups_SACIdDec = 0;
		iups_PLMNIdHex[0] = 0;
		iups_RAIOldHex[0] = 0;
		iups_RAIOldDec[0] = 0;
		iups_RAINewHex[0] = 0;
		iups_RAINewDec[0] = 0;
		iups_IMSI[0] = 0;
		iups_TMSI[0] = 0;
		iups_IMEI[0] = 0;
		iups_MSISDN[0] = 0;
		iups_APN[0] = 0;

		iups_pdp_Mbrupl = 0;
		iups_pdp_Mbrdnl = 0;
		iups_pdp_ExtMbrdnl = 0;
	}

	_SCTP(const _SCTP& mpkt)
	{
		sctp_tsn = mpkt.sctp_tsn;
		sctp_sequence_no = mpkt.sctp_sequence_no;
		sctp_opc = mpkt.sctp_opc;
		sctp_dpc = mpkt.sctp_dpc;
		sctp_protocol = mpkt.sctp_protocol;

		/* SCCP Data */
		strcpy(sccp_slr, mpkt.sccp_slr);
		strcpy(sccp_dlr, mpkt.sccp_dlr);
		strcpy(sccp_session_id, mpkt.sccp_session_id);
		sccp_message_type = mpkt.sccp_message_type;
		strcpy(sccp_message_desc, mpkt.sccp_message_desc);
		sccp_release_cause = mpkt.sccp_release_cause;
		strcpy(sccp_release_desc, mpkt.sccp_release_desc);
		sccp_ranap_present = mpkt.sccp_ranap_present;

		/* IUPS Data */
		iups_packetLengthRANAP= mpkt.iups_packetLengthRANAP;
		iups_packetLengthNAS = mpkt.iups_packetLengthNAS;
		//Two types of transaction sessions maintained
		// RANAP session or GMM session, they are mutually exclusive
		// and is determined by the value stored in sessiontype
		iups_sessiontype = mpkt.iups_sessiontype;
		iups_rsessionstart = mpkt.iups_rsessionstart;
		iups_rsessionend = mpkt.iups_rsessionend;
		iups_gmmsessionstart = mpkt.iups_gmmsessionstart;
		iups_gmmsessionintmd = mpkt.iups_gmmsessionintmd;
		iups_gmmsessionend = mpkt.iups_gmmsessionend;
	    iups_ranap_bytes = mpkt.iups_ranap_bytes;
	    strcpy(iups_session_ranap_id, mpkt.iups_session_ranap_id);		//ranap session key of the session originating procedure
		iups_procedure_code = mpkt.iups_procedure_code;
		strcpy(iups_procedure_desc, mpkt.iups_procedure_desc);
	    iups_session_mmsm_id = mpkt.iups_session_mmsm_id;		//mmsm_id of the session originating procedure
	    iups_mmsm_id = mpkt.iups_mmsm_id;
	    strcpy(iups_mmsm_desc, mpkt.iups_mmsm_desc);
	    //Session specific parameters
	    //will be set either by a RANAP session or MMSM session
	    iups_RABCauseId = mpkt.iups_RABCauseId;
	    strcpy(iups_RABCauseDesc, mpkt.iups_RABCauseDesc);
	    strcpy(iups_Mbrupl, mpkt.iups_Mbrupl);
	    strcpy(iups_Mbrdnl, mpkt.iups_Mbrupl);
	    strcpy(iups_ExtendedMbr, mpkt.iups_ExtendedMbr);
	    strcpy(iups_RABId, mpkt.iups_RABId);
	    strcpy(iups_TEId, mpkt.iups_TEId);
	    strcpy(iups_PDPType, mpkt.iups_PDPType);
	    iups_RAUpdateId = mpkt.iups_RAUpdateId;
	    iups_EndCauseId = mpkt.iups_EndCauseId;
	    strcpy(iups_EndCauseDesc, mpkt.iups_EndCauseDesc);
	    iups_AttachDetachId = mpkt.iups_AttachDetachId;
	    //int AttachDetachDir;
	    strcpy(iups_AttachDetachDir, mpkt.iups_AttachDetachDir);
	    strcpy(iups_AttachDetachDesc, mpkt.iups_AttachDetachDesc);
	    iups_PDPStaticAddressRequested = mpkt.iups_PDPStaticAddressRequested;
	    strcpy(iups_PDPAddressRequested, mpkt.iups_PDPAddressRequested);
	    strcpy(iups_PDPAddressAllocated, mpkt.iups_PDPAddressAllocated);
	    strcpy(iups_RNCId, mpkt.iups_RNCId);
	    strcpy(iups_LACIdHex, mpkt.iups_LACIdHex);
	    iups_LACIdDec = mpkt.iups_LACIdDec;
	    strcpy(iups_RACIdHex, mpkt.iups_RACIdHex);
	    iups_RACIdDec = mpkt.iups_RACIdDec;
	    strcpy(iups_SACIdHex, mpkt.iups_SACIdHex);
		iups_SACIdDec = mpkt.iups_SACIdDec;
		strcpy(iups_PLMNIdHex, mpkt.iups_PLMNIdHex);
		strcpy(iups_RAIOldHex, mpkt.iups_RAIOldHex);
		strcpy(iups_RAIOldDec, mpkt.iups_RAIOldDec);
		strcpy(iups_RAINewHex, mpkt.iups_RAINewHex);
		strcpy(iups_RAINewDec, mpkt.iups_RAINewDec);

		strcpy(iups_IMSI, mpkt.iups_IMSI);
		strcpy(iups_TMSI, mpkt.iups_TMSI);
		strcpy(iups_IMEI, mpkt.iups_IMEI);
		strcpy(iups_MSISDN, mpkt.iups_MSISDN);
		strcpy(iups_APN, mpkt.iups_APN);

		iups_pdp_Mbrupl = mpkt.iups_pdp_Mbrupl;
		iups_pdp_Mbrdnl = mpkt.iups_pdp_Mbrdnl;
		iups_pdp_ExtMbrdnl = mpkt.iups_pdp_ExtMbrdnl;
	}

	void copy(const _SCTP* mpkt)
	{
		sctp_tsn = mpkt->sctp_tsn;
		sctp_sequence_no = mpkt->sctp_sequence_no;
		sctp_opc = mpkt->sctp_opc;
		sctp_dpc = mpkt->sctp_dpc;
		sctp_protocol = mpkt->sctp_protocol;

		/* SCCP Data */
		strcpy(sccp_slr, mpkt->sccp_slr);
		strcpy(sccp_dlr, mpkt->sccp_dlr);
		strcpy(sccp_session_id, mpkt->sccp_session_id);
		sccp_message_type = mpkt->sccp_message_type;
		strcpy(sccp_message_desc, mpkt->sccp_message_desc);
		sccp_release_cause = mpkt->sccp_release_cause;
		strcpy(sccp_release_desc, mpkt->sccp_release_desc);
		sccp_ranap_present = mpkt->sccp_ranap_present;

		/* IUPS Data */
		iups_packetLengthRANAP= mpkt->iups_packetLengthRANAP;
		iups_packetLengthNAS = mpkt->iups_packetLengthNAS;
		//Two types of transaction sessions maintained
		// RANAP session or GMM session, they are mutually exclusive
		// and is determined by the value stored in sessiontype
		iups_sessiontype = mpkt->iups_sessiontype;
		iups_rsessionstart = mpkt->iups_rsessionstart;
		iups_rsessionend = mpkt->iups_rsessionend;
		iups_gmmsessionstart = mpkt->iups_gmmsessionstart;
		iups_gmmsessionintmd = mpkt->iups_gmmsessionintmd;
		iups_gmmsessionend = mpkt->iups_gmmsessionend;
	    iups_ranap_bytes = mpkt->iups_ranap_bytes;
	    strcpy(iups_session_ranap_id, mpkt->iups_session_ranap_id);		//ranap session key of the session originating procedure
		iups_procedure_code = mpkt->iups_procedure_code;
		strcpy(iups_procedure_desc, mpkt->iups_procedure_desc);
	    iups_session_mmsm_id = mpkt->iups_session_mmsm_id;		//mmsm_id of the session originating procedure
	    iups_mmsm_id = mpkt->iups_mmsm_id;
	    strcpy(iups_mmsm_desc, mpkt->iups_mmsm_desc);
	    //Session specific parameters
	    //will be set either by a RANAP session or MMSM session
	    iups_RABCauseId = mpkt->iups_RABCauseId;
	    strcpy(iups_RABCauseDesc, mpkt->iups_RABCauseDesc);
	    strcpy(iups_Mbrupl, mpkt->iups_Mbrupl);
	    strcpy(iups_Mbrdnl, mpkt->iups_Mbrupl);
	    strcpy(iups_ExtendedMbr, mpkt->iups_ExtendedMbr);
	    strcpy(iups_RABId, mpkt->iups_RABId);
	    strcpy(iups_TEId, mpkt->iups_TEId);
	    strcpy(iups_PDPType, mpkt->iups_PDPType);
	    iups_RAUpdateId = mpkt->iups_RAUpdateId;
	    iups_EndCauseId = mpkt->iups_EndCauseId;
	    strcpy(iups_EndCauseDesc, mpkt->iups_EndCauseDesc);
	    iups_AttachDetachId = mpkt->iups_AttachDetachId;
	    //int AttachDetachDir;
	    strcpy(iups_AttachDetachDir, mpkt->iups_AttachDetachDir);
	    strcpy(iups_AttachDetachDesc, mpkt->iups_AttachDetachDesc);
	    iups_PDPStaticAddressRequested = mpkt->iups_PDPStaticAddressRequested;
	    strcpy(iups_PDPAddressRequested, mpkt->iups_PDPAddressRequested);
	    strcpy(iups_PDPAddressAllocated, mpkt->iups_PDPAddressAllocated);
	    strcpy(iups_RNCId, mpkt->iups_RNCId);
	    strcpy(iups_LACIdHex, mpkt->iups_LACIdHex);
	    iups_LACIdDec = mpkt->iups_LACIdDec;
	    strcpy(iups_RACIdHex, mpkt->iups_RACIdHex);
	    iups_RACIdDec = mpkt->iups_RACIdDec;
	    strcpy(iups_SACIdHex, mpkt->iups_SACIdHex);
		iups_SACIdDec = mpkt->iups_SACIdDec;
		strcpy(iups_PLMNIdHex, mpkt->iups_PLMNIdHex);
		strcpy(iups_RAIOldHex, mpkt->iups_RAIOldHex);
		strcpy(iups_RAIOldDec, mpkt->iups_RAIOldDec);
		strcpy(iups_RAINewHex, mpkt->iups_RAINewHex);
		strcpy(iups_RAINewDec, mpkt->iups_RAINewDec);
		strcpy(iups_IMSI, mpkt->iups_IMSI);
		strcpy(iups_TMSI, mpkt->iups_TMSI);
		strcpy(iups_IMEI, mpkt->iups_IMEI);
		strcpy(iups_MSISDN, mpkt->iups_MSISDN);
		strcpy(iups_APN, mpkt->iups_APN);
		iups_pdp_Mbrupl = mpkt->iups_pdp_Mbrupl;
		iups_pdp_Mbrdnl = mpkt->iups_pdp_Mbrdnl;
		iups_pdp_ExtMbrdnl = mpkt->iups_pdp_ExtMbrdnl;

	}
	void operator=(const _SCTP& mpkt)
	{
		sctp_tsn = mpkt.sctp_tsn;
		sctp_sequence_no = mpkt.sctp_sequence_no;
		sctp_opc = mpkt.sctp_opc;
		sctp_dpc = mpkt.sctp_dpc;
		sctp_protocol = mpkt.sctp_protocol;

		/* SCCP Data */
		strcpy(sccp_slr, mpkt.sccp_slr);
		strcpy(sccp_dlr, mpkt.sccp_dlr);
		strcpy(sccp_session_id, mpkt.sccp_session_id);
		sccp_message_type = mpkt.sccp_message_type;
		strcpy(sccp_message_desc, mpkt.sccp_message_desc);
		sccp_release_cause = mpkt.sccp_release_cause;
		strcpy(sccp_release_desc, mpkt.sccp_release_desc);
		sccp_ranap_present = mpkt.sccp_ranap_present;

		/* IUPS Data */
		iups_packetLengthRANAP= mpkt.iups_packetLengthRANAP;
		iups_packetLengthNAS = mpkt.iups_packetLengthNAS;
		//Two types of transaction sessions maintained
		// RANAP session or GMM session, they are mutually exclusive
		// and is determined by the value stored in sessiontype
		iups_sessiontype = mpkt.iups_sessiontype;
		iups_rsessionstart = mpkt.iups_rsessionstart;
		iups_rsessionend = mpkt.iups_rsessionend;
		iups_gmmsessionstart = mpkt.iups_gmmsessionstart;
		iups_gmmsessionintmd = mpkt.iups_gmmsessionintmd;
		iups_gmmsessionend = mpkt.iups_gmmsessionend;
	    iups_ranap_bytes = mpkt.iups_ranap_bytes;
	    strcpy(iups_session_ranap_id, mpkt.iups_session_ranap_id);		//ranap session key of the session originating procedure
		iups_procedure_code = mpkt.iups_procedure_code;
		strcpy(iups_procedure_desc, mpkt.iups_procedure_desc);
	    iups_session_mmsm_id = mpkt.iups_session_mmsm_id;		//mmsm_id of the session originating procedure
	    iups_mmsm_id = mpkt.iups_mmsm_id;
	    strcpy(iups_mmsm_desc, mpkt.iups_mmsm_desc);
	    //Session specific parameters
	    //will be set either by a RANAP session or MMSM session
	    iups_RABCauseId = mpkt.iups_RABCauseId;
	    strcpy(iups_RABCauseDesc, mpkt.iups_RABCauseDesc);
	    strcpy(iups_Mbrupl, mpkt.iups_Mbrupl);
	    strcpy(iups_Mbrdnl, mpkt.iups_Mbrupl);
	    strcpy(iups_ExtendedMbr, mpkt.iups_ExtendedMbr);
	    strcpy(iups_RABId, mpkt.iups_RABId);
	    strcpy(iups_TEId, mpkt.iups_TEId);
	    strcpy(iups_PDPType, mpkt.iups_PDPType);
	    iups_RAUpdateId = mpkt.iups_RAUpdateId;
	    iups_EndCauseId = mpkt.iups_EndCauseId;
	    strcpy(iups_EndCauseDesc, mpkt.iups_EndCauseDesc);
	    iups_AttachDetachId = mpkt.iups_AttachDetachId;
	    //int AttachDetachDir;
	    strcpy(iups_AttachDetachDir, mpkt.iups_AttachDetachDir);
	    strcpy(iups_AttachDetachDesc, mpkt.iups_AttachDetachDesc);
	    iups_PDPStaticAddressRequested = mpkt.iups_PDPStaticAddressRequested;
	    strcpy(iups_PDPAddressRequested, mpkt.iups_PDPAddressRequested);
	    strcpy(iups_PDPAddressAllocated, mpkt.iups_PDPAddressAllocated);
	    strcpy(iups_RNCId, mpkt.iups_RNCId);
	    strcpy(iups_LACIdHex, mpkt.iups_LACIdHex);
	    iups_LACIdDec = mpkt.iups_LACIdDec;
	    strcpy(iups_RACIdHex, mpkt.iups_RACIdHex);
	    iups_RACIdDec = mpkt.iups_RACIdDec;
	    strcpy(iups_SACIdHex, mpkt.iups_SACIdHex);
		iups_SACIdDec = mpkt.iups_SACIdDec;
		strcpy(iups_PLMNIdHex, mpkt.iups_PLMNIdHex);
		strcpy(iups_RAIOldHex, mpkt.iups_RAIOldHex);
		strcpy(iups_RAIOldDec, mpkt.iups_RAIOldDec);
		strcpy(iups_RAINewHex, mpkt.iups_RAINewHex);
		strcpy(iups_RAINewDec, mpkt.iups_RAINewDec);

		strcpy(iups_IMSI, mpkt.iups_IMSI);
		strcpy(iups_TMSI, mpkt.iups_TMSI);
		strcpy(iups_IMEI, mpkt.iups_IMEI);
		strcpy(iups_MSISDN, mpkt.iups_MSISDN);
		strcpy(iups_APN, mpkt.iups_APN);
		iups_pdp_Mbrupl = mpkt.iups_pdp_Mbrupl;
		iups_pdp_Mbrdnl = mpkt.iups_pdp_Mbrdnl;
		iups_pdp_ExtMbrdnl = mpkt.iups_pdp_ExtMbrdnl;
	}

}SCTP;

typedef std::map<int, SCTP> SCTPChunkMap;

typedef struct _MPacket
{
	/* Frame Data */
	uint8_t		frInterfaceId;
	uint8_t		frRouterId;
	uint8_t		frTimeIndex;
	uint64_t	frTimeEpochSec;				//Check size to optimize
	uint128_t	frTimeEpochNanoSec;
	uint16_t	frSize;

	/* Ethernet Data */
	char		ethSourceMACAddr[MAC_ADDR_LEN];
	char		ethDestMACAddr[MAC_ADDR_LEN];
	uint16_t	ethVLanId;

	/* MPLS */
	uint32_t	mplsLevel;
	uint16_t	mplsBits;
	uint16_t	mplsStack;
	uint16_t	mplsTtl;

	/* IPV4 Data */
	uint8_t 	ipVer;
	uint16_t 	ipTLen;
	uint16_t 	ipHLen;
	uint8_t 	ipProtocol;
	uint8_t 	ipAppProtocol;
	uint8_t 	ipTtl;
	BOOL		dirUserNetwork;
	uint32_t 	ipSourceAddr;
	uint32_t	ipDestAddr;

	char 		sourceAddr[9];
	char		destAddr[9];

//	uint128_t	ipSessionKeySrc;
//	uint128_t	ipSessionKeyDest;

	/* L3-Protocol Data TCP/UDP etc*/
	uint16_t 	protoTLen;
	uint16_t 	tcpHLen;
	uint16_t 	protoSourcePort;
	uint16_t 	protoDestPort;
	uint16_t	protoPayload;

	uint32_t 	tcpSeqNo;
	uint16_t	tcpFlags;
	uint32_t	tcpTsVal;
	uint32_t	tcpTsEcr;
	char 		tcpCType[CONTENT_TYPE_LEN];
	uint16_t	tcpSSLVer;

	/* DNS Data */
	uint8_t		dnsQRFlag;
	uint8_t		dnsResponseCode;
	uint32_t	dnsTransactionId;
	uint16_t 	dnsTLen;
	char 		dnsName[DNS_LEN];
	char 		dnsIpAddress[IP_ADDR_LEN];

	/* GTP Common Data */
	uint32_t	gtpTeid;
	uint32_t	gtpSGSNAddr;
	uint32_t	gtpGGSNAddr;
	uint16_t	gtpSGSNPort;
	uint16_t	gtpGGSNPort;
	uint8_t 	gtpUserIpAddressType;
	char 		gtpUserIpAddress[IP_ADDR_LEN];

	/* GTPc Common Data */
	uint16_t 	gtpcMsgLen;
	uint8_t		gtpcVersion;
	uint8_t		gtpcMsgType;

	uint32_t 	gtpcPktTunnelId;
	BOOL		gtpcIsSquenceFlag;
	uint16_t 	gtpcSequenceNo;
	uint16_t 	gtpcMCC;
	uint16_t 	gtpcMNC;
	uint16_t 	gtpcLAC;
	uint8_t 	gtpcRAC;
	uint16_t	gtpcCellId;
	uint8_t 	gtpcRAT;
	uint32_t 	gtpcTunnel_Id_Control;
	uint32_t 	gtpcTunnel_Id_Data_1;
	uint32_t 	gtpcTunnel_Id_Data_2;
	uint8_t 	gtpcNsapi;
	char 		gtpcAPN[APN_LEN];

	uint16_t	gtpcMbrupl;
	uint16_t	gtpcMbrdnl;
	uint16_t	gtpcExtMbrdnl;
	char 		gtpcSgsnAddrData[IP_ADDR_LEN];
	char 		gtpcSgsnAddrCtl[IP_ADDR_LEN];
	char 		gtpcGSN[IP_ADDR_LEN];
	char 		gtpcChargingGWAddr[IP_ADDR_LEN];
	uint8_t 	gtpcCauseCode;
	int			gtpcSgsnId;

	char 		IMSI[IMSI_LEN];
	char 		IMEI[IMEI_LEN];
	char 		MSISDN[MSISDN_LEN];

	uint64_t	packetNo;

	_MPacket()
	{ reset(); }

	_MPacket(const _MPacket& mpkt)
	{
		/* Frame Data */
		frInterfaceId 	= mpkt.frInterfaceId;
		frRouterId 		= mpkt.frRouterId;
		frTimeIndex 	= mpkt.frTimeIndex;
		frTimeEpochSec 	= mpkt.frTimeEpochSec;
		frTimeEpochNanoSec = mpkt.frTimeEpochNanoSec;
		frSize 			= mpkt.frSize;

		/* Ethernet Data */
		strcpy(ethSourceMACAddr, mpkt.ethSourceMACAddr);
		strcpy(ethDestMACAddr, mpkt.ethDestMACAddr);
		ethVLanId 		= mpkt.ethVLanId;

		/* MPLS */
		mplsLevel 		= mpkt.mplsLevel;
		mplsBits 		= mpkt.mplsBits;
		mplsStack 		= mpkt.mplsStack;
		mplsTtl 		= mpkt.mplsTtl;

		/* IPV4 Data */
		ipVer 			= mpkt.ipVer;
		ipTLen 			= mpkt.ipTLen;
		ipHLen 			= mpkt.ipHLen;
		ipProtocol 		= mpkt.ipProtocol;
		ipAppProtocol 	= mpkt.ipAppProtocol;
		ipTtl 			= mpkt.ipTtl;
		dirUserNetwork 	= mpkt.dirUserNetwork;
		ipSourceAddr 	= mpkt.ipSourceAddr;
		ipDestAddr 		= mpkt.ipDestAddr;
		strcpy(sourceAddr, mpkt.sourceAddr);
		strcpy(destAddr, mpkt.destAddr);

//		ipSessionKeySrc = mpkt.ipSessionKeySrc;
//		ipSessionKeyDest= mpkt.ipSessionKeyDest;

		/* L3-Protocol Data TCP/UDP etc*/
		protoTLen		= mpkt.protoTLen;
		tcpHLen 		= mpkt.tcpHLen;
		protoSourcePort = mpkt.protoSourcePort;
		protoDestPort 	= mpkt.protoDestPort;
		protoPayload 	= mpkt.protoPayload;
		tcpSeqNo 		= mpkt.tcpSeqNo;
		tcpFlags 		= mpkt.tcpFlags;
		tcpTsVal 		= mpkt.tcpTsVal;
		tcpTsEcr 		= mpkt.tcpTsEcr;
		strcpy(tcpCType, mpkt.tcpCType);
		tcpSSLVer 		= mpkt.tcpSSLVer;

		/* DNS Data */
		dnsResponseCode = mpkt.dnsResponseCode;
		dnsQRFlag		= mpkt.dnsQRFlag;
		dnsTransactionId= mpkt.dnsTransactionId;
		dnsTLen			= mpkt.dnsTLen;
		strcpy(dnsName, mpkt.dnsName);
		strcpy(dnsIpAddress, mpkt.dnsIpAddress);

		/* GTP Common Data */
		gtpTeid = mpkt.gtpTeid;
		gtpSGSNAddr = mpkt.gtpSGSNAddr;
		gtpGGSNAddr = mpkt.gtpGGSNAddr;
		gtpSGSNPort = mpkt.gtpSGSNPort;
		gtpGGSNPort = mpkt.gtpGGSNPort;
		gtpUserIpAddressType = mpkt.gtpUserIpAddressType;
		strcpy(gtpUserIpAddress, mpkt.gtpUserIpAddress);

		/* GTPc Common Data */
		gtpcMsgLen = mpkt.gtpcMsgLen;
		gtpcVersion = mpkt.gtpcVersion;
		gtpcMsgType = mpkt.gtpcMsgType;

		gtpcPktTunnelId = mpkt.gtpcPktTunnelId;
		gtpcIsSquenceFlag = mpkt.gtpcIsSquenceFlag;
		gtpcSequenceNo = mpkt.gtpcSequenceNo;
		gtpcMCC = mpkt.gtpcMCC;
		gtpcMNC = mpkt.gtpcMNC;
		gtpcLAC = mpkt.gtpcLAC;
		gtpcRAC = mpkt.gtpcRAC;
		gtpcCellId = mpkt.gtpcCellId;
		gtpcRAT = mpkt.gtpcRAT;
		gtpcTunnel_Id_Control = mpkt.gtpcTunnel_Id_Control;
		gtpcTunnel_Id_Data_1 = mpkt.gtpcTunnel_Id_Data_1;
		gtpcTunnel_Id_Data_2 = mpkt.gtpcTunnel_Id_Data_2;
		gtpcNsapi = mpkt.gtpcNsapi;
		strcpy(gtpcAPN, mpkt.gtpcAPN);

		gtpcMbrupl = mpkt.gtpcMbrupl;
		gtpcMbrdnl = mpkt.gtpcMbrdnl;
		gtpcExtMbrdnl = mpkt.gtpcExtMbrdnl;
		strcpy(gtpcSgsnAddrData, mpkt.gtpcSgsnAddrData);
		strcpy(gtpcSgsnAddrCtl, mpkt.gtpcSgsnAddrCtl);
		strcpy(gtpcGSN, mpkt.gtpcGSN);;
		strcpy(gtpcChargingGWAddr, mpkt.gtpcChargingGWAddr);
		gtpcCauseCode = mpkt.gtpcCauseCode;
		gtpcSgsnId = mpkt.gtpcSgsnId;

		strcpy(IMSI, mpkt.IMSI);
		strcpy(IMEI, mpkt.IMEI);
		strcpy(MSISDN, mpkt.MSISDN);
		packetNo = mpkt.packetNo;
	}

	void copy(const _MPacket* mpkt)
	{
		/* Frame Data */
		frInterfaceId = mpkt->frInterfaceId;
		frRouterId = mpkt->frRouterId;
		frTimeIndex = mpkt->frTimeIndex;
		frTimeEpochSec = mpkt->frTimeEpochSec;
		frTimeEpochNanoSec = mpkt->frTimeEpochNanoSec;
		frSize = mpkt->frSize;

		/* Ethernet Data */
		strcpy(ethSourceMACAddr, mpkt->ethSourceMACAddr);
		strcpy(ethDestMACAddr, mpkt->ethDestMACAddr);
		ethVLanId 		= mpkt->ethVLanId;

		/* MPLS */
		mplsLevel 	= mpkt->mplsLevel;
		mplsBits 		= mpkt->mplsBits;
		mplsStack 		= mpkt->mplsStack;
		mplsTtl 		= mpkt->mplsTtl;

		/* IPV4 Data */
		ipVer 			= mpkt->ipVer;
		ipTLen 			= mpkt->ipTLen;
		ipHLen 			= mpkt->ipHLen;
		ipProtocol 		= mpkt->ipProtocol;
		ipAppProtocol 	= mpkt->ipAppProtocol;
		ipTtl 			= mpkt->ipTtl;
		dirUserNetwork 	= mpkt->dirUserNetwork;
		ipSourceAddr 	= mpkt->ipSourceAddr;
		ipDestAddr 		= mpkt->ipDestAddr;
		strcpy(sourceAddr, mpkt->sourceAddr);
		strcpy(destAddr, mpkt->destAddr);

//		ipSessionKeySrc = mpkt->ipSessionKeySrc;
//		ipSessionKeyDest= mpkt->ipSessionKeyDest;

		/* L3-Protocol Data TCP/UDP etc*/
		protoTLen		= mpkt->protoTLen;
		tcpHLen 		= mpkt->tcpHLen;
		protoSourcePort = mpkt->protoSourcePort;
		protoDestPort 	= mpkt->protoDestPort;
		protoPayload 	= mpkt->protoPayload;
		tcpSeqNo 		= mpkt->tcpSeqNo;
		tcpFlags 		= mpkt->tcpFlags;
		tcpTsVal 		= mpkt->tcpTsVal;
		tcpTsEcr 		= mpkt->tcpTsEcr;
		strcpy(tcpCType, mpkt->tcpCType);
		tcpSSLVer 		= mpkt->tcpSSLVer;

		/* DNS Data */
		dnsQRFlag		= mpkt->dnsQRFlag;
		dnsResponseCode = mpkt->dnsResponseCode;
		dnsTransactionId= mpkt->dnsTransactionId;
		dnsTLen			= mpkt->dnsTLen;
		strcpy(dnsName, mpkt->dnsName);
		strcpy(dnsIpAddress, mpkt->dnsIpAddress);

		/* GTP Common Data */
		gtpTeid = mpkt->gtpTeid;
		gtpSGSNAddr = mpkt->gtpSGSNAddr;
		gtpGGSNAddr = mpkt->gtpGGSNAddr;
		gtpSGSNPort = mpkt->gtpSGSNPort;
		gtpGGSNPort = mpkt->gtpGGSNPort;
		gtpUserIpAddressType = mpkt->gtpUserIpAddressType;
		strcpy(gtpUserIpAddress, mpkt->gtpUserIpAddress);

		/* GTPc Common Data */
		gtpcMsgLen = mpkt->gtpcMsgLen;
		gtpcVersion = mpkt->gtpcVersion;
		gtpcMsgType = mpkt->gtpcMsgType;

		gtpcPktTunnelId = mpkt->gtpcPktTunnelId;
		gtpcIsSquenceFlag = mpkt->gtpcIsSquenceFlag;
		gtpcSequenceNo = mpkt->gtpcSequenceNo;
		gtpcMCC = mpkt->gtpcMCC;
		gtpcMNC = mpkt->gtpcMNC;
		gtpcLAC = mpkt->gtpcLAC;
		gtpcRAC = mpkt->gtpcRAC;
		gtpcCellId = mpkt->gtpcCellId;
		gtpcRAT = mpkt->gtpcRAT;
		gtpcTunnel_Id_Control = mpkt->gtpcTunnel_Id_Control;
		gtpcTunnel_Id_Data_1 = mpkt->gtpcTunnel_Id_Data_1;
		gtpcTunnel_Id_Data_2 = mpkt->gtpcTunnel_Id_Data_2;
		gtpcNsapi = mpkt->gtpcNsapi;
		strcpy(gtpcAPN, mpkt->gtpcAPN);

		gtpcMbrupl = mpkt->gtpcMbrupl;
		gtpcMbrdnl = mpkt->gtpcMbrdnl;
		gtpcExtMbrdnl = mpkt->gtpcExtMbrdnl;
		strcpy(gtpcSgsnAddrData, mpkt->gtpcSgsnAddrData);
		strcpy(gtpcSgsnAddrCtl, mpkt->gtpcSgsnAddrCtl);
		strcpy(gtpcGSN, mpkt->gtpcGSN);;
		strcpy(gtpcChargingGWAddr, mpkt->gtpcChargingGWAddr);
		gtpcCauseCode = mpkt->gtpcCauseCode;
		gtpcSgsnId = mpkt->gtpcSgsnId;

		strcpy(IMSI, mpkt->IMSI);
		strcpy(IMEI, mpkt->IMEI);
		strcpy(MSISDN, mpkt->MSISDN);
		packetNo = mpkt->packetNo;
	}

	void operator=(const _MPacket& mpkt)
	{
		/* Frame Data */
		frInterfaceId = mpkt.frInterfaceId;
		frRouterId = mpkt.frRouterId;
		frTimeIndex = mpkt.frTimeIndex;
		frTimeEpochSec = mpkt.frTimeEpochSec;
		frTimeEpochNanoSec = mpkt.frTimeEpochNanoSec;
		frSize = mpkt.frSize;

		/* Ethernet Data */
		strcpy(ethSourceMACAddr, mpkt.ethSourceMACAddr);
		strcpy(ethDestMACAddr, mpkt.ethDestMACAddr);
		ethVLanId 		= mpkt.ethVLanId;

		/* MPLS */
		mplsLevel 	= mpkt.mplsLevel;
		mplsBits 		= mpkt.mplsBits;
		mplsStack 		= mpkt.mplsStack;
		mplsTtl 		= mpkt.mplsTtl;

		/* IPV4 Data */
		ipVer 			= mpkt.ipVer;
		ipTLen 			= mpkt.ipTLen;
		ipHLen 			= mpkt.ipHLen;
		ipProtocol 		= mpkt.ipProtocol;
		ipAppProtocol 	= mpkt.ipAppProtocol;
		ipTtl 			= mpkt.ipTtl;
		dirUserNetwork 	= mpkt.dirUserNetwork;
		ipSourceAddr 	= mpkt.ipSourceAddr;
		ipDestAddr 		= mpkt.ipDestAddr;
		strcpy(sourceAddr, mpkt.sourceAddr);
		strcpy(destAddr, mpkt.destAddr);

//		ipSessionKeySrc = mpkt.ipSessionKeySrc;
//		ipSessionKeyDest= mpkt.ipSessionKeyDest;

		/* L3-Protocol Data TCP/UDP etc*/
		protoTLen		= mpkt.protoTLen;
		tcpHLen 		= mpkt.tcpHLen;
		protoSourcePort = mpkt.protoSourcePort;
		protoDestPort 	= mpkt.protoDestPort;
		protoPayload 	= mpkt.protoPayload;
		tcpSeqNo 		= mpkt.tcpSeqNo;
		tcpFlags 		= mpkt.tcpFlags;
		tcpTsVal 		= mpkt.tcpTsVal;
		tcpTsEcr 		= mpkt.tcpTsEcr;
		strcpy(tcpCType, mpkt.tcpCType);
		tcpSSLVer 		= mpkt.tcpSSLVer;

		/* DNS Data */
		dnsQRFlag		= mpkt.dnsQRFlag;
		dnsResponseCode = mpkt.dnsResponseCode;
		dnsTransactionId= mpkt.dnsTransactionId;
		dnsTLen			= mpkt.dnsTLen;
		strcpy(dnsName, mpkt.dnsName);
		strcpy(dnsIpAddress, mpkt.dnsIpAddress);

		/* GTP Common Data */
		gtpTeid = mpkt.gtpTeid;
		gtpSGSNAddr = mpkt.gtpSGSNAddr;
		gtpGGSNAddr = mpkt.gtpGGSNAddr;
		gtpSGSNPort = mpkt.gtpSGSNPort;
		gtpGGSNPort = mpkt.gtpGGSNPort;
		gtpUserIpAddressType = mpkt.gtpUserIpAddressType;
		strcpy(gtpUserIpAddress, mpkt.gtpUserIpAddress);

		/* GTPc Common Data */
		gtpcMsgLen = mpkt.gtpcMsgLen;
		gtpcVersion = mpkt.gtpcVersion;
		gtpcMsgType = mpkt.gtpcMsgType;

		gtpcPktTunnelId = mpkt.gtpcPktTunnelId;
		gtpcIsSquenceFlag = mpkt.gtpcIsSquenceFlag;
		gtpcSequenceNo = mpkt.gtpcSequenceNo;
		gtpcMCC = mpkt.gtpcMCC;
		gtpcMNC = mpkt.gtpcMNC;
		gtpcLAC = mpkt.gtpcLAC;
		gtpcRAC = mpkt.gtpcRAC;
		gtpcCellId = mpkt.gtpcCellId;
		gtpcRAT = mpkt.gtpcRAT;
		gtpcTunnel_Id_Control = mpkt.gtpcTunnel_Id_Control;
		gtpcTunnel_Id_Data_1 = mpkt.gtpcTunnel_Id_Data_1;
		gtpcTunnel_Id_Data_2 = mpkt.gtpcTunnel_Id_Data_2;
		gtpcNsapi = mpkt.gtpcNsapi;
		strcpy(gtpcAPN, mpkt.gtpcAPN);

		gtpcMbrupl = mpkt.gtpcMbrupl;
		gtpcMbrdnl = mpkt.gtpcMbrdnl;
		gtpcExtMbrdnl = mpkt.gtpcExtMbrdnl;

		strcpy(gtpcSgsnAddrData, mpkt.gtpcSgsnAddrData);
		strcpy(gtpcSgsnAddrCtl, mpkt.gtpcSgsnAddrCtl);
		strcpy(gtpcGSN, mpkt.gtpcGSN);;
		strcpy(gtpcChargingGWAddr, mpkt.gtpcChargingGWAddr);
		gtpcCauseCode = mpkt.gtpcCauseCode;
		gtpcSgsnId = mpkt.gtpcSgsnId;

		strcpy(IMSI, mpkt.IMSI);
		strcpy(IMEI, mpkt.IMEI);
		strcpy(MSISDN, mpkt.MSISDN);
		packetNo = mpkt.packetNo;
	}

	void reset()
	{
		/* Frame Data */
//		frCount = 0;
		frInterfaceId = 0;
		frRouterId = 0;
		frTimeIndex = 0;
		frTimeEpochSec = 0;
		frTimeEpochNanoSec = 0;
		frSize = 0;

		/* Ethernet Data */
		ethSourceMACAddr[0] = 0;
		ethDestMACAddr[0] 	= 0;
		ethVLanId 			= 0;

		/* MPLS */
		mplsLevel 	= 0;
		mplsBits 		= 0;
		mplsStack 		= 0;
		mplsTtl 		= 0;

		/* IPV4 Data */
		ipVer 			= 0;
		ipTLen 			= 0;
		ipHLen 			= 0;
		ipProtocol 		= 0;
		ipAppProtocol 	= 0;
		ipTtl 			= 0;
		dirUserNetwork	= false;
		ipSourceAddr 	= 0;
		ipDestAddr 		= 0;
		sourceAddr[0] = 0;
		destAddr[0] = 0;

//		ipSessionKeySrc = 0;
//		ipSessionKeyDest= 0;

		/* L3-Protocol Data TCP/UDP etc*/
		protoTLen		= 0;
		tcpHLen 		= 0;
		protoSourcePort	= 0;
		protoDestPort 	= 0;
		protoPayload 	= 0;

		tcpSeqNo 		= 0;
		tcpFlags 		= 0;
		tcpTsVal 		= 0;
		tcpTsEcr 		= 0;
		tcpCType[0] 	= 0;
		tcpSSLVer 		= 0;

		/* DNS Data */
		dnsQRFlag		= 0;
		dnsResponseCode = 0;
		dnsTransactionId= 0;
		dnsTLen			= 0;
		dnsName[0]		= 0;
		dnsIpAddress[0]	= 0;

		/* GTP Common Data */
		gtpTeid		= 0;
		gtpSGSNAddr = 0;
		gtpGGSNAddr = 0;
		gtpSGSNPort = 0;
		gtpGGSNPort = 0;
		gtpUserIpAddressType = 0;
		strcpy(gtpUserIpAddress, "NA");

		/* GTPc Common Data */
		gtpcMsgLen = 0;
		gtpcVersion = 0;
		gtpcMsgType = 0;

		gtpcPktTunnelId = 0;
		gtpcIsSquenceFlag = false;
		gtpcSequenceNo = 0;
		gtpcMCC = 0;
		gtpcMNC = 0;
		gtpcLAC = 0;
		gtpcRAC = 0;
		gtpcCellId = 0;
		gtpcRAT = 0;
		gtpcTunnel_Id_Control = 0;
		gtpcTunnel_Id_Data_1 = 0;
		gtpcTunnel_Id_Data_2 = 0;
		gtpcNsapi = 0;
		strcpy(gtpcAPN, "NA");

		gtpcMbrupl = 0;
		gtpcMbrdnl = 0;
		gtpcExtMbrdnl = 0;
		gtpcSgsnAddrData[0] = 0;
		gtpcSgsnAddrCtl[0] = 0;
		gtpcGSN[0] = 0;
		gtpcChargingGWAddr[0] = 0;
		gtpcCauseCode = 0;
		gtpcSgsnId = 0;

		strcpy(IMSI, "NA");
		//strcpy(TMSI, "NA");
		strcpy(IMEI, "NA");
		strcpy(MSISDN, "NA");
		packetNo = 0;
	}
}MPacket;

typedef enum{
	NOK = 0,
	OK
}retType;


typedef struct _bwData
{
	ULONG Volume;
	ULONG upVolume;
	ULONG dnVolume;
	_bwData()
	{
		Volume = 0;
		upVolume = 0;
		dnVolume = 0;
	}
}bwData;

namespace GTPStats {

//	extern uint64_t gtp_get_imsi_req_cnt;
//	extern uint64_t gtp_get_imsi_suc_cnt;
	extern int unique_imsi_cnt;

	extern uint64_t gtpc_pkt_cnt_i_0_r_0;
	extern uint64_t gtpc_pkt_cnt_i_0_r_1;
	extern uint64_t gtpc_pkt_cnt_i_0_r_2;
	extern uint64_t gtpc_pkt_cnt_i_0_r_3;

	extern uint64_t gtpc_pkt_cnt_i_1_r_0;
	extern uint64_t gtpc_pkt_cnt_i_1_r_1;
	extern uint64_t gtpc_pkt_cnt_i_1_r_2;
	extern uint64_t gtpc_pkt_cnt_i_1_r_3;

	extern uint64_t gtpc_pkt_cnt_i_2_r_0;
	extern uint64_t gtpc_pkt_cnt_i_2_r_1;
	extern uint64_t gtpc_pkt_cnt_i_2_r_2;
	extern uint64_t gtpc_pkt_cnt_i_2_r_3;

	extern uint64_t gtpc_pkt_cnt_i_3_r_0;
	extern uint64_t gtpc_pkt_cnt_i_3_r_1;
	extern uint64_t gtpc_pkt_cnt_i_3_r_2;
	extern uint64_t gtpc_pkt_cnt_i_3_r_3;

	extern uint64_t gtpu_pkt_cnt_i_0_r_0;
	extern uint64_t gtpu_pkt_cnt_i_0_r_1;
	extern uint64_t gtpu_pkt_cnt_i_0_r_2;
	extern uint64_t gtpu_pkt_cnt_i_0_r_3;

	extern uint64_t gtpu_pkt_cnt_i_1_r_0;
	extern uint64_t gtpu_pkt_cnt_i_1_r_1;
	extern uint64_t gtpu_pkt_cnt_i_1_r_2;
	extern uint64_t gtpu_pkt_cnt_i_1_r_3;

	extern uint64_t gtpu_pkt_cnt_i_2_r_0;
	extern uint64_t gtpu_pkt_cnt_i_2_r_1;
	extern uint64_t gtpu_pkt_cnt_i_2_r_2;
	extern uint64_t gtpu_pkt_cnt_i_2_r_3;

	extern uint64_t gtpu_pkt_cnt_i_3_r_0;
	extern uint64_t gtpu_pkt_cnt_i_3_r_1;
	extern uint64_t gtpu_pkt_cnt_i_3_r_2;
	extern uint64_t gtpu_pkt_cnt_i_3_r_3;

	extern bool gtp_glb_sessions_cnt_process;

	extern uint32_t gtp_glb_lku_up_active_sessions_cnt;
	extern uint32_t gtp_glb_lku_up_sessions_cnt;
	extern uint32_t gtp_glb_lku_dn_active_sessions_cnt;
	extern uint32_t gtp_glb_lku_dn_sessions_cnt;

	extern uint32_t gtp_glb_inactive_session_cln_cnt;
	extern uint32_t gtp_glb_lku_up_sessions_cln_cnt;
	extern uint32_t gtp_glb_lku_dn_sessions_cln_cnt;

	extern int gtp_glb_sessions_total_cnt;
	extern int gtp_glb_sessions_utran_cnt;
	extern int gtp_glb_sessions_geran_cnt;
//	extern int gtp_glb_sessions_total[60];
//	extern int gtp_glb_sessions_utran[60];
//	extern int gtp_glb_sessions_geran[60];

//	extern uint32_t gtp_glb_sessions_cnt;
	extern int gtp_glb_active_sessions_cnt;

	extern int gtp_glb_ctl_up_cnt;
	extern int gtp_glb_data_up_cnt;
	extern int gtp_glb_ctl_dn_cnt;
	extern int gtp_glb_data_dn_cnt;

	extern uint32_t gtp_glb_sessions_op_cr_cnt;
	extern uint32_t gtp_glb_sessions_op_up_cnt;
	extern uint32_t gtp_glb_sessions_op_dl_cnt;

	extern uint32_t gtp_pdp_cr_flush_sm_0;
	extern uint32_t gtp_pdp_cr_flush_sm_1;
	extern uint32_t gtp_pdp_cr_flush_sm_2;
	extern uint32_t gtp_pdp_cr_flush_sm_3;

	extern uint32_t gtp_pdp_up_flush_sm_0;
	extern uint32_t gtp_pdp_up_flush_sm_1;
	extern uint32_t gtp_pdp_up_flush_sm_2;
	extern uint32_t gtp_pdp_up_flush_sm_3;

	extern uint32_t gtp_pdp_dl_flush_sm_0;
	extern uint32_t gtp_pdp_dl_flush_sm_1;
	extern uint32_t gtp_pdp_dl_flush_sm_2;
	extern uint32_t gtp_pdp_dl_flush_sm_3;

	extern uint32_t gtp_pdp_cr_session_sm_0;
	extern uint32_t gtp_pdp_cr_session_sm_1;
	extern uint32_t gtp_pdp_cr_session_sm_2;
	extern uint32_t gtp_pdp_cr_session_sm_3;

	extern uint32_t gtp_pdp_up_session_sm_0;
	extern uint32_t gtp_pdp_up_session_sm_1;
	extern uint32_t gtp_pdp_up_session_sm_2;
	extern uint32_t gtp_pdp_up_session_sm_3;

	extern uint32_t gtp_pdp_dl_session_sm_0;
	extern uint32_t gtp_pdp_dl_session_sm_1;
	extern uint32_t gtp_pdp_dl_session_sm_2;
	extern uint32_t gtp_pdp_dl_session_sm_3;

	extern uint32_t gtpc_pdp_cr_req_sm_0;
	extern uint32_t gtpc_pdp_cr_req_sm_1;
	extern uint32_t gtpc_pdp_cr_req_sm_2;
	extern uint32_t gtpc_pdp_cr_req_sm_3;
	extern uint32_t gtpc_pdp_cr_res_sm_0;
	extern uint32_t gtpc_pdp_cr_res_sm_1;
	extern uint32_t gtpc_pdp_cr_res_sm_2;
	extern uint32_t gtpc_pdp_cr_res_sm_3;

	extern uint32_t gtpc_pdp_up_req_sm_0;
	extern uint32_t gtpc_pdp_up_req_sm_1;
	extern uint32_t gtpc_pdp_up_req_sm_2;
	extern uint32_t gtpc_pdp_up_req_sm_3;
	extern uint32_t gtpc_pdp_up_res_sm_0;
	extern uint32_t gtpc_pdp_up_res_sm_1;
	extern uint32_t gtpc_pdp_up_res_sm_2;
	extern uint32_t gtpc_pdp_up_res_sm_3;

	extern uint32_t gtpc_pdp_dl_req_sm_0;
	extern uint32_t gtpc_pdp_dl_req_sm_1;
	extern uint32_t gtpc_pdp_dl_req_sm_2;
	extern uint32_t gtpc_pdp_dl_req_sm_3;
	extern uint32_t gtpc_pdp_dl_res_sm_0;
	extern uint32_t gtpc_pdp_dl_res_sm_1;
	extern uint32_t gtpc_pdp_dl_res_sm_2;
	extern uint32_t gtpc_pdp_dl_res_sm_3;

}

namespace IPGlobal {

	extern BOOL	PROBE_RUNNING_STATUS;

	extern BOOL	PKT_LISTENER_RUNNING_STATUS[4];
	extern BOOL	PKT_LISTENER_INTF_MON_RUNNING_STATUS[4];
	extern BOOL	PKT_LISTENER_DAYCHANGE_INDICATION[4];
	extern BOOL	PKT_ROUTER_RUNNING_STATUS[4][4];
	extern BOOL	GN_SESSION_MANAGER_RUNNING_STATUS[8];
	extern BOOL	FLUSHER_RUNNING_STATUS;
	extern BOOL	GN_XDR_RUNNING_STATUS;
	extern BOOL	GN_GTPC_FLUSHER_RUNNING_STATUS;
	extern BOOL	GN_GTPU_FLUSHER_RUNNING_STATUS;

	extern BOOL	GN_FLUSHER_ZMQ_RUNNING_STATUS;
	extern BOOL	PROBE_STATS_RUNNING_STATUS;

	extern long CURRENT_TIME_EPOCH_SEC;
	extern long CURRENT_TIME_EPOCH_MICRO_SEC;

	extern int CURRENT_TIME_SEC;
	extern int CURRENT_TIME_MIN;
	extern int CURRENT_TIME_HOUR;
	extern int CURRENT_TIME_DAY;
	extern int CURRENT_TIME_MONTH;
	extern int CURRENT_TIME_YEAR;

	extern int 		PROBE_ID;
	extern bool 	PRINT_STATS;
	extern int 		PRINT_STATS_FREQ_SEC;

	extern int 		ACTIVE_INTERFACE;
	extern string 	PCAP_FILE_NAME;
	extern int 		PCAP_REPEAT;

	extern int 		NO_OF_INTERFACES;
	extern string 	ETHERNET_INTERFACES[MAX_INTERFACE_SUPPORT];
	extern string 	SOLAR_INTERFACES[MAX_INTERFACE_SUPPORT];
	extern int 		ROUTER_PER_INTERFACE[MAX_INTERFACE_SUPPORT];
	extern int		PKT_LISTENER_CPU_CORE[MAX_INTERFACE_SUPPORT];
	extern int 		PKT_ROUTER_CPU_CORE[MAX_INTERFACE_SUPPORT][MAX_INTERFACE_SUPPORT];
	extern int 		LINE_RATE_PER_INTERFACE[MAX_INTERFACE_SUPPORT];
	extern int 		PPS_PER_INTERFACE[MAX_INTERFACE_SUPPORT];
	extern int		PPS_CAP_PERCENTAGE[MAX_INTERFACE_SUPPORT];

	extern int 		GN_GTPU_FLUSHER_NO;
	extern int		GN_GTPU_FLUSHER_CPU_CORE[4];
	extern int		GN_GTPC_FLUSHER_CPU_CORE;
	extern int		GN_ZMQ_FLUSHER_CPU_CORE;
	extern int		GN_XDR_FLUSHER_CPU_CORE;

	extern uint32_t PKT_RATE_INTF_0;
	extern uint32_t PKT_RATE_INTF_1;
	extern uint32_t PKT_RATE_INTF_2;
	extern uint32_t PKT_RATE_INTF_3;

	extern uint128_t PKTS_TOTAL_INTF_0;
	extern uint128_t PKTS_TOTAL_INTF_1;
	extern uint128_t PKTS_TOTAL_INTF_2;
	extern uint128_t PKTS_TOTAL_INTF_3;

	extern uint64_t BW_MBPS_INTF_0;
	extern uint64_t BW_MBPS_INTF_1;
	extern uint64_t BW_MBPS_INTF_2;
	extern uint64_t BW_MBPS_INTF_3;

	extern bwData BW_MBPS_i_0_r_0;
	extern bwData BW_MBPS_i_0_r_1;
	extern bwData BW_MBPS_i_0_r_2;
	extern bwData BW_MBPS_i_0_r_3;

	extern bwData BW_MBPS_i_1_r_0;
	extern bwData BW_MBPS_i_1_r_1;
	extern bwData BW_MBPS_i_1_r_2;
	extern bwData BW_MBPS_i_1_r_3;

	extern bwData BW_MBPS_i_2_r_0;
	extern bwData BW_MBPS_i_2_r_1;
	extern bwData BW_MBPS_i_2_r_2;
	extern bwData BW_MBPS_i_2_r_3;

	extern bwData BW_MBPS_i_3_r_0;
	extern bwData BW_MBPS_i_3_r_1;
	extern bwData BW_MBPS_i_3_r_2;
	extern bwData BW_MBPS_i_3_r_3;

	extern int GN_SESSION_MANAGER_INSTANCES;
	extern int GN_SESSION_MANAGER_CPU_CORE[8];
	extern int SESSION_MANAGER_TIMEINDEX;
	extern long SESSION_MANAGER_PER_TIMEINDEX_PKTS;
	extern int FLUSHER_TIMEINDEX;
	extern int ZMQ_FLUSHER_TIMEINDEX;
	extern int SESSION_MANAGER_WRITE_INDEX_ADV;
	extern int SESSION_MANAGER_READ_INDEX_LAG;

	extern int IUPS_SESSION_MANAGER_INSTANCES;
	extern int IUPS_SESSION_MANAGER_CPU_CORE[8];
	extern int IUPS_ZMQ_FLUSHER_CPU_CORE;
	extern int IUPS_FLUSHER_CPU_CORE;
	extern int	IUPS_FLUSHER_NO;

	extern int  SRC_MAC_NOS;
	extern int 	DST_MAC_NOS;
	extern char RNC_MAC[8][18];
	extern char SGSN_MAC[8][18];
	extern char GGSN_MAC[8][18];
	extern int	SGSN_PC[8];
	extern int 	TOTAL_SGSN_PC;

	extern int IPV4_MULTIPLIER_OCTET_1;
	extern int IPV4_MULTIPLIER_OCTET_2;
	extern int IPV4_MULTIPLIER_OCTET_3;

	extern ULONG IPV6_MULTIPLIER_OCTET_1;
	extern ULONG IPV6_MULTIPLIER_OCTET_2;
	extern ULONG IPV6_MULTIPLIER_OCTET_3;
	extern ULONG IPV6_MULTIPLIER_OCTET_4;
	extern ULONG IPV6_MULTIPLIER_OCTET_5;
	extern ULONG IPV6_MULTIPLIER_OCTET_6;

	extern bool  queueFlag;

	extern int IP_SESSION_PKT_LIMIT;
	extern int IP_SESSION_REPO_MAX_LIMIT;
	extern int IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE;
	extern int IP_SESSION_CLEAN_UP_SCAN_FREQ_SEC;
	extern int IP_SESSION_CLEAN_UP_BATCH_LIMIT;
	extern int IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC;

	extern ULONG lastFlusherEpochTimeSec;
	extern ULONG lastCleanUpEpochTimeSec;
	extern ULONG sessionSrNo;

	extern uint32_t 	currentDay;

	//Global parameters
    extern TCHAR tcpConfigFile[50];
    extern TCHAR dnsDbDumpFile[50];
    extern TCHAR TDRFile[100];
    extern TCHAR DNSTDRFile[100];
    extern ULONG processedPacket[2];
    extern ULONG	t_FrameCount;
    extern fstream tcpConfigHandler;
    extern fstream IPXdrHandler;
    extern fstream bwLogHandler;
    extern fstream httpLogHandler;
    extern fstream dnsDumpHandler;
    extern fstream dnsUploadHandler;
    extern fstream dnsDayHandler;
	extern fstream IUPSXdrHandler;
	extern fstream IUPSCsvXdrHandler;
	extern fstream GXCsvXdrHandler;
	extern fstream RadiusXdrHandler;
    extern uint32_t	dummyLoop;
    extern uint32_t zmqCount;

    extern int sliceValue;
    extern fstream 	gtpDumpHandler;

	/*
	 * For GN related file stream
	 */
	extern fstream 	dnsCsvHandler;
	extern fstream	GTPuCsvHandler;
	extern fstream	GTPuTdrHandler;
	extern fstream	GTPcCsvHandler;
	extern fstream	GTPcTdrHandler;

    /*
     *  TCP (Broadband Flush Connection)
     */
    extern void 	*tcpZmqContext;
    extern void 	*tcpZmqRequester;
    /*
     *  GXGY (Diameter)
     */
    extern void 	*gxZmqContext;
    extern void 	*gxZmqRequester;

    /*
     * Radius (Flush Connection)
     */
	extern void 		*radiusZmqContext;
    extern void 		*radiusZmqRequester;

    /*
     * GN (Flush Connection)
     */
	extern void 	*gtpcZmqContext;
    extern void 	*gtpcZmqRequester;
    extern void 	*gtpuZmqContext;
    extern void 	*gtpuZmqRequester;
    /*
     * DNS (Broadband Flush Connection)
     */
    extern void 	*dnsZmqContext;
    extern void 	*dnsZmqRequester;
    extern void 	*iupsZmqContext;
    extern void 	*iupsZmqRequester;

    extern int		idleSessionExpireTime;
    extern int 		activeSessionExpireTime;
    extern int		sessionCleanFreq;

    extern uint32_t inputType;
    extern TCHAR	inputSource[200];
    extern TCHAR	smQueuePath[500];
    extern TCHAR	ffQueuePath[500];

    extern int		ffQid;
    extern int 		xdrFlag;
    extern int 		flushFlag;
    extern uint16_t	logLevel;
    extern std::ifstream ranapxmlfile;
    extern ULONG	sendQ;
    extern ULONG	recvQ;
    extern ULONG	smRcv;
    extern vector<string> TraceSCCPSessionIds;
    extern vector<string> ipRange;

    extern ULONG	CleanFlush;

    extern ULONG	PDPCreateReq;
    extern ULONG 	PDPCreateReqNew;
    extern ULONG	PDPCreateReqExist;

    extern ULONG	PDPCreateRsp;
    extern ULONG	PDPCreateClose;
    extern ULONG	PDPCreateRspNotFound;

    extern ULONG	PDPUpdateReq;
    extern ULONG	PDPUpdateReqNew;
    extern ULONG	PDPUpdateReqExist;

    extern ULONG	PDPUpdateRsp;
    extern ULONG	PDPUpdateClose;
    extern ULONG	PDPUpdateRspNotFound;

    extern ULONG	PDPDeleteReq;
    extern ULONG	PDPDeleteReqNew;
    extern ULONG	PDPDeleteReqExist;

    extern ULONG	PDPDeleteRsp;
    extern ULONG	PDPDeleteClose;
    extern ULONG	PDPDeleteRspNotFound;

    extern ULONG	globalTableCreate;
    extern ULONG	globalTableDelete;
    extern ULONG	PDPDeleteFlush;

    extern uint16_t	gtpVersion;

    extern std::map<int, int> IPRange;
    extern std::map<char*, int> macAddress;

    extern uint64_t ip_processed_packets_i_0_r_0;
    extern uint64_t ip_processed_packets_i_0_r_1;
    extern uint64_t ip_processed_packets_i_0_r_2;
    extern uint64_t ip_processed_packets_i_0_r_3;

    extern uint64_t ip_processed_packets_i_1_r_0;
    extern uint64_t ip_processed_packets_i_1_r_1;
    extern uint64_t ip_processed_packets_i_1_r_2;
    extern uint64_t ip_processed_packets_i_1_r_3;

    extern uint64_t ip_processed_packets_i_2_r_0;
    extern uint64_t ip_processed_packets_i_2_r_1;
    extern uint64_t ip_processed_packets_i_2_r_2;
    extern uint64_t ip_processed_packets_i_2_r_3;

    extern uint64_t ip_processed_packets_i_3_r_0;
    extern uint64_t ip_processed_packets_i_3_r_1;
    extern uint64_t ip_processed_packets_i_3_r_2;
    extern uint64_t ip_processed_packets_i_3_r_3;

    extern uint64_t ip_discarded_packets_i_0_r_0;
    extern uint64_t ip_discarded_packets_i_0_r_1;
    extern uint64_t ip_discarded_packets_i_0_r_2;
    extern uint64_t ip_discarded_packets_i_0_r_3;

    extern uint64_t ip_discarded_packets_i_1_r_0;
    extern uint64_t ip_discarded_packets_i_1_r_1;
    extern uint64_t ip_discarded_packets_i_1_r_2;
    extern uint64_t ip_discarded_packets_i_1_r_3;

    extern uint64_t ip_discarded_packets_i_2_r_0;
    extern uint64_t ip_discarded_packets_i_2_r_1;
    extern uint64_t ip_discarded_packets_i_2_r_2;
    extern uint64_t ip_discarded_packets_i_2_r_3;

    extern uint64_t ip_discarded_packets_i_3_r_0;
    extern uint64_t ip_discarded_packets_i_3_r_1;
    extern uint64_t ip_discarded_packets_i_3_r_2;
    extern uint64_t ip_discarded_packets_i_3_r_3;

    extern uint64_t ip_discarded_large_packets_i_0;
    extern uint64_t ip_discarded_large_packets_i_1;
    extern uint64_t ip_discarded_large_packets_i_2;
    extern uint64_t ip_discarded_large_packets_i_3;

    extern uint64_t ip_noproto_packets_i_0_r_0;
    extern uint64_t ip_noproto_packets_i_0_r_1;
    extern uint64_t ip_noproto_packets_i_0_r_2;
    extern uint64_t ip_noproto_packets_i_0_r_3;

    extern uint64_t ip_noproto_packets_i_1_r_0;
    extern uint64_t ip_noproto_packets_i_1_r_1;
    extern uint64_t ip_noproto_packets_i_1_r_2;
    extern uint64_t ip_noproto_packets_i_1_r_3;

    extern uint64_t ip_noproto_packets_i_2_r_0;
    extern uint64_t ip_noproto_packets_i_2_r_1;
    extern uint64_t ip_noproto_packets_i_2_r_2;
    extern uint64_t ip_noproto_packets_i_2_r_3;

    extern uint64_t ip_noproto_packets_i_3_r_0;
    extern uint64_t ip_noproto_packets_i_3_r_1;
    extern uint64_t ip_noproto_packets_i_3_r_2;
    extern uint64_t ip_noproto_packets_i_3_r_3;
}

namespace IPStats {

	extern uint64_t dns_resolved_lookup_size;
	extern uint64_t dns_lookup_map_size;
	extern int dns_session_sm_0_cnt;
	extern int dns_session_sm_1_cnt;
	extern int dns_session_sm_2_cnt;
	extern int dns_session_sm_3_cnt;
	extern int dns_session_sm_4_cnt;

	extern uint64_t ip_session_fin_only_sm_0_cnt;
	extern uint64_t ip_session_fin_only_sm_1_cnt;
	extern uint64_t ip_session_fin_only_sm_2_cnt;
	extern uint64_t ip_session_fin_only_sm_3_cnt;
	extern uint64_t ip_session_fin_only_sm_4_cnt;

	extern int ip_session_total_sm_0_cnt;
	extern int ip_session_total_sm_1_cnt;
	extern int ip_session_total_sm_2_cnt;
	extern int ip_session_total_sm_3_cnt;
	extern int ip_session_total_sm_4_cnt;

	extern int ip_session_scanned_sm_0_cnt;
	extern int ip_session_scanned_sm_1_cnt;
	extern int ip_session_scanned_sm_2_cnt;
	extern int ip_session_scanned_sm_3_cnt;
	extern int ip_session_scanned_sm_4_cnt;

	extern int ip_session_cleaned_tcp_sm_0_cnt;
	extern int ip_session_cleaned_tcp_sm_1_cnt;
	extern int ip_session_cleaned_tcp_sm_2_cnt;
	extern int ip_session_cleaned_tcp_sm_3_cnt;
	extern int ip_session_cleaned_tcp_sm_4_cnt;

	extern int ip_session_cleaned_udp_sm_0_cnt;
	extern int ip_session_cleaned_udp_sm_1_cnt;
	extern int ip_session_cleaned_udp_sm_2_cnt;
	extern int ip_session_cleaned_udp_sm_3_cnt;
	extern int ip_session_cleaned_udp_sm_4_cnt;
}

namespace PKTStore
{
	// Interface_0
	extern std::map<long, RawPkt*> pktRepository_i_0_r_0_t_0;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_0_t_1;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_0_t_2;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_0_t_3;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_0_t_4;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_0_t_5;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_0_t_6;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_0_t_7;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_0_t_8;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_0_t_9;

	extern long pktRepository_i_0_r_0_t_0_cnt;
	extern long pktRepository_i_0_r_0_t_1_cnt;
	extern long pktRepository_i_0_r_0_t_2_cnt;
	extern long pktRepository_i_0_r_0_t_3_cnt;
	extern long pktRepository_i_0_r_0_t_4_cnt;
	extern long pktRepository_i_0_r_0_t_5_cnt;
	extern long pktRepository_i_0_r_0_t_6_cnt;
	extern long pktRepository_i_0_r_0_t_7_cnt;
	extern long pktRepository_i_0_r_0_t_8_cnt;
	extern long pktRepository_i_0_r_0_t_9_cnt;

	extern bool pktRepository_i_0_r_0_t_0_busy;
	extern bool pktRepository_i_0_r_0_t_1_busy;
	extern bool pktRepository_i_0_r_0_t_2_busy;
	extern bool pktRepository_i_0_r_0_t_3_busy;
	extern bool pktRepository_i_0_r_0_t_4_busy;
	extern bool pktRepository_i_0_r_0_t_5_busy;
	extern bool pktRepository_i_0_r_0_t_6_busy;
	extern bool pktRepository_i_0_r_0_t_7_busy;
	extern bool pktRepository_i_0_r_0_t_8_busy;
	extern bool pktRepository_i_0_r_0_t_9_busy;

	extern std::map<long, RawPkt*> pktRepository_i_0_r_1_t_0;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_1_t_1;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_1_t_2;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_1_t_3;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_1_t_4;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_1_t_5;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_1_t_6;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_1_t_7;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_1_t_8;
	extern std::map<long, RawPkt*> pktRepository_i_0_r_1_t_9;

	extern long pktRepository_i_0_r_1_t_0_cnt;
	extern long pktRepository_i_0_r_1_t_1_cnt;
	extern long pktRepository_i_0_r_1_t_2_cnt;
	extern long pktRepository_i_0_r_1_t_3_cnt;
	extern long pktRepository_i_0_r_1_t_4_cnt;
	extern long pktRepository_i_0_r_1_t_5_cnt;
	extern long pktRepository_i_0_r_1_t_6_cnt;
	extern long pktRepository_i_0_r_1_t_7_cnt;
	extern long pktRepository_i_0_r_1_t_8_cnt;
	extern long pktRepository_i_0_r_1_t_9_cnt;

	extern bool pktRepository_i_0_r_1_t_0_busy;
	extern bool pktRepository_i_0_r_1_t_1_busy;
	extern bool pktRepository_i_0_r_1_t_2_busy;
	extern bool pktRepository_i_0_r_1_t_3_busy;
	extern bool pktRepository_i_0_r_1_t_4_busy;
	extern bool pktRepository_i_0_r_1_t_5_busy;
	extern bool pktRepository_i_0_r_1_t_6_busy;
	extern bool pktRepository_i_0_r_1_t_7_busy;
	extern bool pktRepository_i_0_r_1_t_8_busy;
	extern bool pktRepository_i_0_r_1_t_9_busy;

//	extern std::map<long, RawPkt*> pktRepository_i_0_r_2_t_0;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_2_t_1;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_2_t_2;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_2_t_3;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_2_t_4;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_2_t_5;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_2_t_6;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_2_t_7;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_2_t_8;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_2_t_9;
//
//	extern long pktRepository_i_0_r_2_t_0_cnt;
//	extern long pktRepository_i_0_r_2_t_1_cnt;
//	extern long pktRepository_i_0_r_2_t_2_cnt;
//	extern long pktRepository_i_0_r_2_t_3_cnt;
//	extern long pktRepository_i_0_r_2_t_4_cnt;
//	extern long pktRepository_i_0_r_2_t_5_cnt;
//	extern long pktRepository_i_0_r_2_t_6_cnt;
//	extern long pktRepository_i_0_r_2_t_7_cnt;
//	extern long pktRepository_i_0_r_2_t_8_cnt;
//	extern long pktRepository_i_0_r_2_t_9_cnt;
//
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_3_t_0;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_3_t_1;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_3_t_2;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_3_t_3;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_3_t_4;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_3_t_5;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_3_t_6;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_3_t_7;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_3_t_8;
//	extern std::map<long, RawPkt*> pktRepository_i_0_r_3_t_9;
//
//	extern long pktRepository_i_0_r_3_t_0_cnt;
//	extern long pktRepository_i_0_r_3_t_1_cnt;
//	extern long pktRepository_i_0_r_3_t_2_cnt;
//	extern long pktRepository_i_0_r_3_t_3_cnt;
//	extern long pktRepository_i_0_r_3_t_4_cnt;
//	extern long pktRepository_i_0_r_3_t_5_cnt;
//	extern long pktRepository_i_0_r_3_t_6_cnt;
//	extern long pktRepository_i_0_r_3_t_7_cnt;
//	extern long pktRepository_i_0_r_3_t_8_cnt;
//	extern long pktRepository_i_0_r_3_t_9_cnt;


	// Interface_1
	extern std::map<long, RawPkt*> pktRepository_i_1_r_0_t_0;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_0_t_1;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_0_t_2;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_0_t_3;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_0_t_4;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_0_t_5;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_0_t_6;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_0_t_7;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_0_t_8;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_0_t_9;

	extern long pktRepository_i_1_r_0_t_0_cnt;
	extern long pktRepository_i_1_r_0_t_1_cnt;
	extern long pktRepository_i_1_r_0_t_2_cnt;
	extern long pktRepository_i_1_r_0_t_3_cnt;
	extern long pktRepository_i_1_r_0_t_4_cnt;
	extern long pktRepository_i_1_r_0_t_5_cnt;
	extern long pktRepository_i_1_r_0_t_6_cnt;
	extern long pktRepository_i_1_r_0_t_7_cnt;
	extern long pktRepository_i_1_r_0_t_8_cnt;
	extern long pktRepository_i_1_r_0_t_9_cnt;

	extern bool pktRepository_i_1_r_0_t_0_busy;
	extern bool pktRepository_i_1_r_0_t_1_busy;
	extern bool pktRepository_i_1_r_0_t_2_busy;
	extern bool pktRepository_i_1_r_0_t_3_busy;
	extern bool pktRepository_i_1_r_0_t_4_busy;
	extern bool pktRepository_i_1_r_0_t_5_busy;
	extern bool pktRepository_i_1_r_0_t_6_busy;
	extern bool pktRepository_i_1_r_0_t_7_busy;
	extern bool pktRepository_i_1_r_0_t_8_busy;
	extern bool pktRepository_i_1_r_0_t_9_busy;

	extern std::map<long, RawPkt*> pktRepository_i_1_r_1_t_0;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_1_t_1;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_1_t_2;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_1_t_3;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_1_t_4;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_1_t_5;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_1_t_6;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_1_t_7;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_1_t_8;
	extern std::map<long, RawPkt*> pktRepository_i_1_r_1_t_9;

	extern long pktRepository_i_1_r_1_t_0_cnt;
	extern long pktRepository_i_1_r_1_t_1_cnt;
	extern long pktRepository_i_1_r_1_t_2_cnt;
	extern long pktRepository_i_1_r_1_t_3_cnt;
	extern long pktRepository_i_1_r_1_t_4_cnt;
	extern long pktRepository_i_1_r_1_t_5_cnt;
	extern long pktRepository_i_1_r_1_t_6_cnt;
	extern long pktRepository_i_1_r_1_t_7_cnt;
	extern long pktRepository_i_1_r_1_t_8_cnt;
	extern long pktRepository_i_1_r_1_t_9_cnt;

	extern bool pktRepository_i_1_r_1_t_0_busy;
	extern bool pktRepository_i_1_r_1_t_1_busy;
	extern bool pktRepository_i_1_r_1_t_2_busy;
	extern bool pktRepository_i_1_r_1_t_3_busy;
	extern bool pktRepository_i_1_r_1_t_4_busy;
	extern bool pktRepository_i_1_r_1_t_5_busy;
	extern bool pktRepository_i_1_r_1_t_6_busy;
	extern bool pktRepository_i_1_r_1_t_7_busy;
	extern bool pktRepository_i_1_r_1_t_8_busy;
	extern bool pktRepository_i_1_r_1_t_9_busy;

//	extern std::map<long, RawPkt*> pktRepository_i_1_r_2_t_0;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_2_t_1;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_2_t_2;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_2_t_3;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_2_t_4;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_2_t_5;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_2_t_6;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_2_t_7;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_2_t_8;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_2_t_9;
//
//	extern long pktRepository_i_1_r_2_t_0_cnt;
//	extern long pktRepository_i_1_r_2_t_1_cnt;
//	extern long pktRepository_i_1_r_2_t_2_cnt;
//	extern long pktRepository_i_1_r_2_t_3_cnt;
//	extern long pktRepository_i_1_r_2_t_4_cnt;
//	extern long pktRepository_i_1_r_2_t_5_cnt;
//	extern long pktRepository_i_1_r_2_t_6_cnt;
//	extern long pktRepository_i_1_r_2_t_7_cnt;
//	extern long pktRepository_i_1_r_2_t_8_cnt;
//	extern long pktRepository_i_1_r_2_t_9_cnt;
//
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_3_t_0;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_3_t_1;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_3_t_2;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_3_t_3;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_3_t_4;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_3_t_5;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_3_t_6;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_3_t_7;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_3_t_8;
//	extern std::map<long, RawPkt*> pktRepository_i_1_r_3_t_9;
//
//	extern long pktRepository_i_1_r_3_t_0_cnt;
//	extern long pktRepository_i_1_r_3_t_1_cnt;
//	extern long pktRepository_i_1_r_3_t_2_cnt;
//	extern long pktRepository_i_1_r_3_t_3_cnt;
//	extern long pktRepository_i_1_r_3_t_4_cnt;
//	extern long pktRepository_i_1_r_3_t_5_cnt;
//	extern long pktRepository_i_1_r_3_t_6_cnt;
//	extern long pktRepository_i_1_r_3_t_7_cnt;
//	extern long pktRepository_i_1_r_3_t_8_cnt;
//	extern long pktRepository_i_1_r_3_t_9_cnt;


	// Interface_2
	extern std::map<long, RawPkt*> pktRepository_i_2_r_0_t_0;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_0_t_1;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_0_t_2;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_0_t_3;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_0_t_4;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_0_t_5;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_0_t_6;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_0_t_7;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_0_t_8;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_0_t_9;

	extern long pktRepository_i_2_r_0_t_0_cnt;
	extern long pktRepository_i_2_r_0_t_1_cnt;
	extern long pktRepository_i_2_r_0_t_2_cnt;
	extern long pktRepository_i_2_r_0_t_3_cnt;
	extern long pktRepository_i_2_r_0_t_4_cnt;
	extern long pktRepository_i_2_r_0_t_5_cnt;
	extern long pktRepository_i_2_r_0_t_6_cnt;
	extern long pktRepository_i_2_r_0_t_7_cnt;
	extern long pktRepository_i_2_r_0_t_8_cnt;
	extern long pktRepository_i_2_r_0_t_9_cnt;

	extern bool pktRepository_i_2_r_0_t_0_busy;
	extern bool pktRepository_i_2_r_0_t_1_busy;
	extern bool pktRepository_i_2_r_0_t_2_busy;
	extern bool pktRepository_i_2_r_0_t_3_busy;
	extern bool pktRepository_i_2_r_0_t_4_busy;
	extern bool pktRepository_i_2_r_0_t_5_busy;
	extern bool pktRepository_i_2_r_0_t_6_busy;
	extern bool pktRepository_i_2_r_0_t_7_busy;
	extern bool pktRepository_i_2_r_0_t_8_busy;
	extern bool pktRepository_i_2_r_0_t_9_busy;

	extern std::map<long, RawPkt*> pktRepository_i_2_r_1_t_0;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_1_t_1;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_1_t_2;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_1_t_3;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_1_t_4;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_1_t_5;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_1_t_6;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_1_t_7;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_1_t_8;
	extern std::map<long, RawPkt*> pktRepository_i_2_r_1_t_9;

	extern long pktRepository_i_2_r_1_t_0_cnt;
	extern long pktRepository_i_2_r_1_t_1_cnt;
	extern long pktRepository_i_2_r_1_t_2_cnt;
	extern long pktRepository_i_2_r_1_t_3_cnt;
	extern long pktRepository_i_2_r_1_t_4_cnt;
	extern long pktRepository_i_2_r_1_t_5_cnt;
	extern long pktRepository_i_2_r_1_t_6_cnt;
	extern long pktRepository_i_2_r_1_t_7_cnt;
	extern long pktRepository_i_2_r_1_t_8_cnt;
	extern long pktRepository_i_2_r_1_t_9_cnt;

	extern bool pktRepository_i_2_r_1_t_0_busy;
	extern bool pktRepository_i_2_r_1_t_1_busy;
	extern bool pktRepository_i_2_r_1_t_2_busy;
	extern bool pktRepository_i_2_r_1_t_3_busy;
	extern bool pktRepository_i_2_r_1_t_4_busy;
	extern bool pktRepository_i_2_r_1_t_5_busy;
	extern bool pktRepository_i_2_r_1_t_6_busy;
	extern bool pktRepository_i_2_r_1_t_7_busy;
	extern bool pktRepository_i_2_r_1_t_8_busy;
	extern bool pktRepository_i_2_r_1_t_9_busy;

//	extern std::map<long, RawPkt*> pktRepository_i_2_r_2_t_0;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_2_t_1;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_2_t_2;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_2_t_3;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_2_t_4;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_2_t_5;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_2_t_6;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_2_t_7;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_2_t_8;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_2_t_9;
//
//	extern long pktRepository_i_2_r_2_t_0_cnt;
//	extern long pktRepository_i_2_r_2_t_1_cnt;
//	extern long pktRepository_i_2_r_2_t_2_cnt;
//	extern long pktRepository_i_2_r_2_t_3_cnt;
//	extern long pktRepository_i_2_r_2_t_4_cnt;
//	extern long pktRepository_i_2_r_2_t_5_cnt;
//	extern long pktRepository_i_2_r_2_t_6_cnt;
//	extern long pktRepository_i_2_r_2_t_7_cnt;
//	extern long pktRepository_i_2_r_2_t_8_cnt;
//	extern long pktRepository_i_2_r_2_t_9_cnt;
//
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_3_t_0;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_3_t_1;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_3_t_2;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_3_t_3;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_3_t_4;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_3_t_5;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_3_t_6;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_3_t_7;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_3_t_8;
//	extern std::map<long, RawPkt*> pktRepository_i_2_r_3_t_9;
//
//	extern long pktRepository_i_2_r_3_t_0_cnt;
//	extern long pktRepository_i_2_r_3_t_1_cnt;
//	extern long pktRepository_i_2_r_3_t_2_cnt;
//	extern long pktRepository_i_2_r_3_t_3_cnt;
//	extern long pktRepository_i_2_r_3_t_4_cnt;
//	extern long pktRepository_i_2_r_3_t_5_cnt;
//	extern long pktRepository_i_2_r_3_t_6_cnt;
//	extern long pktRepository_i_2_r_3_t_7_cnt;
//	extern long pktRepository_i_2_r_3_t_8_cnt;
//	extern long pktRepository_i_2_r_3_t_9_cnt;


	// Interface_3
	extern std::map<long, RawPkt*> pktRepository_i_3_r_0_t_0;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_0_t_1;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_0_t_2;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_0_t_3;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_0_t_4;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_0_t_5;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_0_t_6;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_0_t_7;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_0_t_8;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_0_t_9;

	extern long pktRepository_i_3_r_0_t_0_cnt;
	extern long pktRepository_i_3_r_0_t_1_cnt;
	extern long pktRepository_i_3_r_0_t_2_cnt;
	extern long pktRepository_i_3_r_0_t_3_cnt;
	extern long pktRepository_i_3_r_0_t_4_cnt;
	extern long pktRepository_i_3_r_0_t_5_cnt;
	extern long pktRepository_i_3_r_0_t_6_cnt;
	extern long pktRepository_i_3_r_0_t_7_cnt;
	extern long pktRepository_i_3_r_0_t_8_cnt;
	extern long pktRepository_i_3_r_0_t_9_cnt;

	extern bool pktRepository_i_3_r_0_t_0_busy;
	extern bool pktRepository_i_3_r_0_t_1_busy;
	extern bool pktRepository_i_3_r_0_t_2_busy;
	extern bool pktRepository_i_3_r_0_t_3_busy;
	extern bool pktRepository_i_3_r_0_t_4_busy;
	extern bool pktRepository_i_3_r_0_t_5_busy;
	extern bool pktRepository_i_3_r_0_t_6_busy;
	extern bool pktRepository_i_3_r_0_t_7_busy;
	extern bool pktRepository_i_3_r_0_t_8_busy;
	extern bool pktRepository_i_3_r_0_t_9_busy;

	extern std::map<long, RawPkt*> pktRepository_i_3_r_1_t_0;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_1_t_1;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_1_t_2;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_1_t_3;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_1_t_4;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_1_t_5;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_1_t_6;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_1_t_7;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_1_t_8;
	extern std::map<long, RawPkt*> pktRepository_i_3_r_1_t_9;

	extern long pktRepository_i_3_r_1_t_0_cnt;
	extern long pktRepository_i_3_r_1_t_1_cnt;
	extern long pktRepository_i_3_r_1_t_2_cnt;
	extern long pktRepository_i_3_r_1_t_3_cnt;
	extern long pktRepository_i_3_r_1_t_4_cnt;
	extern long pktRepository_i_3_r_1_t_5_cnt;
	extern long pktRepository_i_3_r_1_t_6_cnt;
	extern long pktRepository_i_3_r_1_t_7_cnt;
	extern long pktRepository_i_3_r_1_t_8_cnt;
	extern long pktRepository_i_3_r_1_t_9_cnt;

	extern bool pktRepository_i_3_r_1_t_0_busy;
	extern bool pktRepository_i_3_r_1_t_1_busy;
	extern bool pktRepository_i_3_r_1_t_2_busy;
	extern bool pktRepository_i_3_r_1_t_3_busy;
	extern bool pktRepository_i_3_r_1_t_4_busy;
	extern bool pktRepository_i_3_r_1_t_5_busy;
	extern bool pktRepository_i_3_r_1_t_6_busy;
	extern bool pktRepository_i_3_r_1_t_7_busy;
	extern bool pktRepository_i_3_r_1_t_8_busy;
	extern bool pktRepository_i_3_r_1_t_9_busy;

//	extern std::map<long, RawPkt*> pktRepository_i_3_r_2_t_0;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_2_t_1;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_2_t_2;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_2_t_3;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_2_t_4;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_2_t_5;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_2_t_6;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_2_t_7;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_2_t_8;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_2_t_9;
//
//	extern long pktRepository_i_3_r_2_t_0_cnt;
//	extern long pktRepository_i_3_r_2_t_1_cnt;
//	extern long pktRepository_i_3_r_2_t_2_cnt;
//	extern long pktRepository_i_3_r_2_t_3_cnt;
//	extern long pktRepository_i_3_r_2_t_4_cnt;
//	extern long pktRepository_i_3_r_2_t_5_cnt;
//	extern long pktRepository_i_3_r_2_t_6_cnt;
//	extern long pktRepository_i_3_r_2_t_7_cnt;
//	extern long pktRepository_i_3_r_2_t_8_cnt;
//	extern long pktRepository_i_3_r_2_t_9_cnt;
//
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_3_t_0;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_3_t_1;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_3_t_2;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_3_t_3;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_3_t_4;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_3_t_5;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_3_t_6;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_3_t_7;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_3_t_8;
//	extern std::map<long, RawPkt*> pktRepository_i_3_r_3_t_9;
//
//	extern long pktRepository_i_3_r_3_t_0_cnt;
//	extern long pktRepository_i_3_r_3_t_1_cnt;
//	extern long pktRepository_i_3_r_3_t_2_cnt;
//	extern long pktRepository_i_3_r_3_t_3_cnt;
//	extern long pktRepository_i_3_r_3_t_4_cnt;
//	extern long pktRepository_i_3_r_3_t_5_cnt;
//	extern long pktRepository_i_3_r_3_t_6_cnt;
//	extern long pktRepository_i_3_r_3_t_7_cnt;
//	extern long pktRepository_i_3_r_3_t_8_cnt;
//	extern long pktRepository_i_3_r_3_t_9_cnt;

}

namespace TraceStore
{
	extern std::string tr_msg_i_0_r_0_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_0_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_0_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_0_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_0_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_0_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_0_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_0_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_0_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_0_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_0_r_0_t_0_cnt;
	extern int tr_msg_i_0_r_0_t_1_cnt;
	extern int tr_msg_i_0_r_0_t_2_cnt;
	extern int tr_msg_i_0_r_0_t_3_cnt;
	extern int tr_msg_i_0_r_0_t_4_cnt;
	extern int tr_msg_i_0_r_0_t_5_cnt;
	extern int tr_msg_i_0_r_0_t_6_cnt;
	extern int tr_msg_i_0_r_0_t_7_cnt;
	extern int tr_msg_i_0_r_0_t_8_cnt;
	extern int tr_msg_i_0_r_0_t_9_cnt;

	extern std::string tr_msg_i_0_r_1_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_1_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_1_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_1_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_1_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_1_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_1_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_1_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_1_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_1_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_0_r_1_t_0_cnt;
	extern int tr_msg_i_0_r_1_t_1_cnt;
	extern int tr_msg_i_0_r_1_t_2_cnt;
	extern int tr_msg_i_0_r_1_t_3_cnt;
	extern int tr_msg_i_0_r_1_t_4_cnt;
	extern int tr_msg_i_0_r_1_t_5_cnt;
	extern int tr_msg_i_0_r_1_t_6_cnt;
	extern int tr_msg_i_0_r_1_t_7_cnt;
	extern int tr_msg_i_0_r_1_t_8_cnt;
	extern int tr_msg_i_0_r_1_t_9_cnt;

	extern std::string tr_msg_i_0_r_2_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_2_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_2_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_2_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_2_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_2_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_2_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_2_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_2_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_2_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_0_r_2_t_0_cnt;
	extern int tr_msg_i_0_r_2_t_1_cnt;
	extern int tr_msg_i_0_r_2_t_2_cnt;
	extern int tr_msg_i_0_r_2_t_3_cnt;
	extern int tr_msg_i_0_r_2_t_4_cnt;
	extern int tr_msg_i_0_r_2_t_5_cnt;
	extern int tr_msg_i_0_r_2_t_6_cnt;
	extern int tr_msg_i_0_r_2_t_7_cnt;
	extern int tr_msg_i_0_r_2_t_8_cnt;
	extern int tr_msg_i_0_r_2_t_9_cnt;

	extern std::string tr_msg_i_0_r_3_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_3_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_3_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_3_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_3_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_3_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_3_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_3_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_3_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_0_r_3_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_0_r_3_t_0_cnt;
	extern int tr_msg_i_0_r_3_t_1_cnt;
	extern int tr_msg_i_0_r_3_t_2_cnt;
	extern int tr_msg_i_0_r_3_t_3_cnt;
	extern int tr_msg_i_0_r_3_t_4_cnt;
	extern int tr_msg_i_0_r_3_t_5_cnt;
	extern int tr_msg_i_0_r_3_t_6_cnt;
	extern int tr_msg_i_0_r_3_t_7_cnt;
	extern int tr_msg_i_0_r_3_t_8_cnt;
	extern int tr_msg_i_0_r_3_t_9_cnt;



	extern std::string tr_msg_i_1_r_0_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_0_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_0_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_0_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_0_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_0_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_0_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_0_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_0_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_0_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_1_r_0_t_0_cnt;
	extern int tr_msg_i_1_r_0_t_1_cnt;
	extern int tr_msg_i_1_r_0_t_2_cnt;
	extern int tr_msg_i_1_r_0_t_3_cnt;
	extern int tr_msg_i_1_r_0_t_4_cnt;
	extern int tr_msg_i_1_r_0_t_5_cnt;
	extern int tr_msg_i_1_r_0_t_6_cnt;
	extern int tr_msg_i_1_r_0_t_7_cnt;
	extern int tr_msg_i_1_r_0_t_8_cnt;
	extern int tr_msg_i_1_r_0_t_9_cnt;

	extern std::string tr_msg_i_1_r_1_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_1_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_1_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_1_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_1_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_1_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_1_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_1_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_1_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_1_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_1_r_1_t_0_cnt;
	extern int tr_msg_i_1_r_1_t_1_cnt;
	extern int tr_msg_i_1_r_1_t_2_cnt;
	extern int tr_msg_i_1_r_1_t_3_cnt;
	extern int tr_msg_i_1_r_1_t_4_cnt;
	extern int tr_msg_i_1_r_1_t_5_cnt;
	extern int tr_msg_i_1_r_1_t_6_cnt;
	extern int tr_msg_i_1_r_1_t_7_cnt;
	extern int tr_msg_i_1_r_1_t_8_cnt;
	extern int tr_msg_i_1_r_1_t_9_cnt;

	extern std::string tr_msg_i_1_r_2_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_2_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_2_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_2_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_2_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_2_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_2_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_2_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_2_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_2_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_1_r_2_t_0_cnt;
	extern int tr_msg_i_1_r_2_t_1_cnt;
	extern int tr_msg_i_1_r_2_t_2_cnt;
	extern int tr_msg_i_1_r_2_t_3_cnt;
	extern int tr_msg_i_1_r_2_t_4_cnt;
	extern int tr_msg_i_1_r_2_t_5_cnt;
	extern int tr_msg_i_1_r_2_t_6_cnt;
	extern int tr_msg_i_1_r_2_t_7_cnt;
	extern int tr_msg_i_1_r_2_t_8_cnt;
	extern int tr_msg_i_1_r_2_t_9_cnt;

	extern std::string tr_msg_i_1_r_3_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_3_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_3_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_3_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_3_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_3_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_3_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_3_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_3_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_1_r_3_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_1_r_3_t_0_cnt;
	extern int tr_msg_i_1_r_3_t_1_cnt;
	extern int tr_msg_i_1_r_3_t_2_cnt;
	extern int tr_msg_i_1_r_3_t_3_cnt;
	extern int tr_msg_i_1_r_3_t_4_cnt;
	extern int tr_msg_i_1_r_3_t_5_cnt;
	extern int tr_msg_i_1_r_3_t_6_cnt;
	extern int tr_msg_i_1_r_3_t_7_cnt;
	extern int tr_msg_i_1_r_3_t_8_cnt;
	extern int tr_msg_i_1_r_3_t_9_cnt;

	extern std::string tr_msg_i_2_r_0_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_0_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_0_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_0_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_0_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_0_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_0_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_0_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_0_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_0_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_2_r_0_t_0_cnt;
	extern int tr_msg_i_2_r_0_t_1_cnt;
	extern int tr_msg_i_2_r_0_t_2_cnt;
	extern int tr_msg_i_2_r_0_t_3_cnt;
	extern int tr_msg_i_2_r_0_t_4_cnt;
	extern int tr_msg_i_2_r_0_t_5_cnt;
	extern int tr_msg_i_2_r_0_t_6_cnt;
	extern int tr_msg_i_2_r_0_t_7_cnt;
	extern int tr_msg_i_2_r_0_t_8_cnt;
	extern int tr_msg_i_2_r_0_t_9_cnt;

	extern std::string tr_msg_i_2_r_1_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_1_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_1_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_1_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_1_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_1_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_1_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_1_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_1_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_1_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_2_r_1_t_0_cnt;
	extern int tr_msg_i_2_r_1_t_1_cnt;
	extern int tr_msg_i_2_r_1_t_2_cnt;
	extern int tr_msg_i_2_r_1_t_3_cnt;
	extern int tr_msg_i_2_r_1_t_4_cnt;
	extern int tr_msg_i_2_r_1_t_5_cnt;
	extern int tr_msg_i_2_r_1_t_6_cnt;
	extern int tr_msg_i_2_r_1_t_7_cnt;
	extern int tr_msg_i_2_r_1_t_8_cnt;
	extern int tr_msg_i_2_r_1_t_9_cnt;

	extern std::string tr_msg_i_2_r_2_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_2_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_2_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_2_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_2_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_2_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_2_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_2_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_2_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_2_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_2_r_2_t_0_cnt;
	extern int tr_msg_i_2_r_2_t_1_cnt;
	extern int tr_msg_i_2_r_2_t_2_cnt;
	extern int tr_msg_i_2_r_2_t_3_cnt;
	extern int tr_msg_i_2_r_2_t_4_cnt;
	extern int tr_msg_i_2_r_2_t_5_cnt;
	extern int tr_msg_i_2_r_2_t_6_cnt;
	extern int tr_msg_i_2_r_2_t_7_cnt;
	extern int tr_msg_i_2_r_2_t_8_cnt;
	extern int tr_msg_i_2_r_2_t_9_cnt;

	extern std::string tr_msg_i_2_r_3_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_3_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_3_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_3_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_3_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_3_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_3_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_3_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_3_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_2_r_3_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_2_r_3_t_0_cnt;
	extern int tr_msg_i_2_r_3_t_1_cnt;
	extern int tr_msg_i_2_r_3_t_2_cnt;
	extern int tr_msg_i_2_r_3_t_3_cnt;
	extern int tr_msg_i_2_r_3_t_4_cnt;
	extern int tr_msg_i_2_r_3_t_5_cnt;
	extern int tr_msg_i_2_r_3_t_6_cnt;
	extern int tr_msg_i_2_r_3_t_7_cnt;
	extern int tr_msg_i_2_r_3_t_8_cnt;
	extern int tr_msg_i_2_r_3_t_9_cnt;


	extern std::string tr_msg_i_3_r_0_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_0_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_0_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_0_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_0_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_0_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_0_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_0_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_0_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_0_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_3_r_0_t_0_cnt;
	extern int tr_msg_i_3_r_0_t_1_cnt;
	extern int tr_msg_i_3_r_0_t_2_cnt;
	extern int tr_msg_i_3_r_0_t_3_cnt;
	extern int tr_msg_i_3_r_0_t_4_cnt;
	extern int tr_msg_i_3_r_0_t_5_cnt;
	extern int tr_msg_i_3_r_0_t_6_cnt;
	extern int tr_msg_i_3_r_0_t_7_cnt;
	extern int tr_msg_i_3_r_0_t_8_cnt;
	extern int tr_msg_i_3_r_0_t_9_cnt;

	extern std::string tr_msg_i_3_r_1_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_1_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_1_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_1_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_1_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_1_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_1_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_1_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_1_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_1_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_3_r_1_t_0_cnt;
	extern int tr_msg_i_3_r_1_t_1_cnt;
	extern int tr_msg_i_3_r_1_t_2_cnt;
	extern int tr_msg_i_3_r_1_t_3_cnt;
	extern int tr_msg_i_3_r_1_t_4_cnt;
	extern int tr_msg_i_3_r_1_t_5_cnt;
	extern int tr_msg_i_3_r_1_t_6_cnt;
	extern int tr_msg_i_3_r_1_t_7_cnt;
	extern int tr_msg_i_3_r_1_t_8_cnt;
	extern int tr_msg_i_3_r_1_t_9_cnt;

	extern std::string tr_msg_i_3_r_2_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_2_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_2_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_2_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_2_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_2_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_2_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_2_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_2_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_2_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_3_r_2_t_0_cnt;
	extern int tr_msg_i_3_r_2_t_1_cnt;
	extern int tr_msg_i_3_r_2_t_2_cnt;
	extern int tr_msg_i_3_r_2_t_3_cnt;
	extern int tr_msg_i_3_r_2_t_4_cnt;
	extern int tr_msg_i_3_r_2_t_5_cnt;
	extern int tr_msg_i_3_r_2_t_6_cnt;
	extern int tr_msg_i_3_r_2_t_7_cnt;
	extern int tr_msg_i_3_r_2_t_8_cnt;
	extern int tr_msg_i_3_r_2_t_9_cnt;

	extern std::string tr_msg_i_3_r_3_t_0[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_3_t_1[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_3_t_2[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_3_t_3[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_3_t_4[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_3_t_5[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_3_t_6[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_3_t_7[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_3_t_8[TRACE_QUEUE_LIMIT];
	extern std::string tr_msg_i_3_r_3_t_9[TRACE_QUEUE_LIMIT];
	extern int tr_msg_i_3_r_3_t_0_cnt;
	extern int tr_msg_i_3_r_3_t_1_cnt;
	extern int tr_msg_i_3_r_3_t_2_cnt;
	extern int tr_msg_i_3_r_3_t_3_cnt;
	extern int tr_msg_i_3_r_3_t_4_cnt;
	extern int tr_msg_i_3_r_3_t_5_cnt;
	extern int tr_msg_i_3_r_3_t_6_cnt;
	extern int tr_msg_i_3_r_3_t_7_cnt;
	extern int tr_msg_i_3_r_3_t_8_cnt;
	extern int tr_msg_i_3_r_3_t_9_cnt;

}

namespace mapTcpLock {
	extern pthread_mutex_t lockCount;
	extern pthread_cond_t nonzero;
	extern unsigned count;
}

namespace mapGtpLock {
	extern pthread_mutex_t lockCount;
	extern pthread_cond_t nonzero;
	extern unsigned count;
}

namespace mapUdpLock {
	extern pthread_mutex_t lockCount;
	extern pthread_cond_t nonzero;
	extern unsigned count;
}

namespace mapDnsLock {
	extern pthread_mutex_t lockCount;
	extern pthread_cond_t nonzero;
	extern unsigned count;
}

namespace mapOtrLock {
	extern pthread_mutex_t lockCount;
	extern pthread_cond_t nonzero;
	extern unsigned count;
}

namespace vInterfaceLock {
	extern pthread_mutex_t readyMutex;
	extern pthread_cond_t  readyCond;
	extern int             readyCount;
}

namespace mapGxLock {
	extern pthread_mutex_t lockCount;
	extern pthread_cond_t nonzero;
	extern unsigned count;
}

namespace mapRaLock {
	extern pthread_mutex_t lockCount;
	extern pthread_cond_t nonzero;
	extern unsigned count;
}

namespace gSessionLock {
	extern pthread_mutex_t lockCount;
	extern pthread_cond_t nonzero;
	extern unsigned count;
}

typedef struct cTimeParameters
{
	int currentSec;
	int currentMin;
	int currentHour;
	int currentDay;
	int currentMonth;
	int currentYear;

	void initialize()
	{
		currentSec = 0;
		currentMin = 0;
		currentHour = 0;
		currentDay = 0;
		currentMonth = 0;
		currentYear = 0;
	};
};
#endif /* INC_IPGLOBAL_H_ */
