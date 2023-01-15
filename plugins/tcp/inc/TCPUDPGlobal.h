/*
 * TCPUDPGlobal.h
 *
 *  Created on: 15-Jul-2016
 *      Author: deb
 */

#ifndef PLUGINS_TCP_INC_TCPUDPGLOBAL_H_
#define PLUGINS_TCP_INC_TCPUDPGLOBAL_H_


#include <map>

#include "SpectaTypedef.h"
#include "IPGlobal.h"

using namespace std;

//#define IP_SESSION_MAX_CLEAUP_COUNT		70000

#define UDP_HDR_LEN		8
#define DNS_HDR_LEN		12
#define IP4LEN			4
#define IP6LEN			16
#define	STUN_PORT		3478

#define UDP_NO_ERROR	0

#define IP_POOL_ARRAY_ELEMENTS			100		//Poosible values 10, 100, 1000, 10000, 100000....

#define IP_FLUSH_POOL_ARRAY_ELEMENTS	100		//Poosible values 10, 100, 1000, 10000, 100000....
#define IP_FLUSH_POOL_ARRAY_SIZE		5000

#define DNS_FLUSH_POOL_ARRAY_ELEMENTS	100		//Poosible values 10, 100, 1000, 10000, 100000....
#define DNS_FLUSH_POOL_ARRAY_SIZE		3000

//#define IP_XDR_FLUSH_ARRAY_SIZE		500000
//#define DNS_XDR_FLUSH_ARRAY_SIZE	200000


#define DIAMETER_SEQ_ID	263

typedef enum {
    CHANGE_CIPHER_SPEC 	= 20,
	ALERT 				= 21,
	HANDSHAKE 			= 22,
    APP_DATA 			= 23
}TLSContentType;

namespace errorCode {
	extern char *dnsErrorCode[];
}

namespace tcpPort {
	extern TCHAR *TCPPort[];
}

typedef struct _stunData
{
	uint32_t 	appIp;
	uint64_t	createEpochSec;
	_stunData()
	{
		appIp = 0;
		createEpochSec = 0;
    }
}stunData;

namespace STUNMAP {
	extern std::map<uint32_t, stunData> stunMap;
}

typedef struct _dnsUrl{
	uint64_t	pckLastTimeEpcohSec;
	char 		URL[50];
	uint32_t 	address;

	_dnsUrl()
	{
		pckLastTimeEpcohSec = 0;
		URL[0] = 0;
		address = 0;
	}
}dnsUrl;



typedef struct _flushData
{
	string key;
	int mapId;
	int mapArrId;

	_flushData()
	{
		key = "";
		mapId = -1;
		mapArrId = -1;
	}
}flushData;


//typedef struct _xdrStore
//{
//	int idx;
//	char xdr[XDR_MAX_LEN];
//
//	_xdrStore()
//	{
//		reset();
//	}
//	_xdrStore(const _xdrStore& obj)
//	{
//		this->idx = obj.idx;
//		strcpy(this->xdr, obj.xdr);
//	}
//	void set(const _xdrStore *obj)
//	{
//		this->idx = obj->idx;
//		strcpy(this->xdr, obj->xdr);
//	}
//	void copy(const _xdrStore* obj)
//	{
//		this->idx = obj->idx;
//		strcpy(this->xdr, obj->xdr);
//	}
//	void operator=(const _xdrStore& obj)
//	{
//		this->idx = obj.idx;
//		strcpy(this->xdr, obj.xdr);
//	}
//	void reset()
//	{
//		this->idx = 0;
//		strcpy(this->xdr, "");
//	}
//}xdrStore;


typedef struct _fData
{
	uint32_t totalPackets;
	uint32_t totalVolume;
	uint32_t upPackets;
	uint32_t upVolume;
	uint32_t dnPackets;
	uint32_t dnVolume;

        _fData()
        {
        	totalPackets = 0;
        	totalVolume = 0;
        	upPackets = 0;
        	upVolume = 0;
        	dnPackets = 0;
        	dnVolume = 0;
        }
}fData;


typedef struct _dnsSession{

	uint32_t	transactionId;

	int32_t		sourcePort;
	int32_t		destPort;

	uint128_t 	queryStartEpochNanoSec;
	uint128_t	queryEndEpochNanoSec;
	uint128_t 	resolveTimeNanoSec;
	uint128_t	pckLastTimeEpcohMicroSec;

	uint32_t 	sourceIP;
	uint32_t 	destIP;
	char 		address[IP_ADDR_LEN];
	char 		URL[DNS_LEN];

	int32_t		causeCode;
	int32_t		errorCode;
	char 		errorDesc[DESC_LEN];
	uint64_t	FlushTimeEpochMicroSec;
	uint16_t	state;

	_dnsSession()
	{ reset(); }

	void set(const _dnsSession *obj)
	{
		this->transactionId = obj->transactionId;

		this->sourcePort = obj->sourcePort;
		this->destPort = obj->destPort;

		this->queryStartEpochNanoSec = obj->queryStartEpochNanoSec;
		this->queryEndEpochNanoSec = obj->queryEndEpochNanoSec;
		this->resolveTimeNanoSec = obj->resolveTimeNanoSec;
		this->pckLastTimeEpcohMicroSec = obj->pckLastTimeEpcohMicroSec;

		this->sourceIP = obj->sourceIP;
		this->destIP = obj->destIP;
		strcpy(this->address, obj->address);
		strcpy(this->URL, obj->URL);

		this->causeCode = obj->causeCode;
		this->errorCode = obj->errorCode;
		strcpy(this->errorDesc, obj->errorDesc);
		this->FlushTimeEpochMicroSec = obj->FlushTimeEpochMicroSec;
		this->state	= obj->state;
	}

	void copy(const _dnsSession* obj)
	{
		this->transactionId = obj->transactionId;

		this->sourcePort = obj->sourcePort;
		this->destPort = obj->destPort;

		this->queryStartEpochNanoSec = obj->queryStartEpochNanoSec;
		this->queryEndEpochNanoSec = obj->queryEndEpochNanoSec;
		this->resolveTimeNanoSec = obj->resolveTimeNanoSec;
		this->pckLastTimeEpcohMicroSec = obj->pckLastTimeEpcohMicroSec;

		this->sourceIP = obj->sourceIP;
		this->destIP = obj->destIP;
		strcpy(this->address, obj->address);
		strcpy(this->URL, obj->URL);

		this->causeCode = obj->causeCode;
		this->errorCode = obj->errorCode;
		strcpy(this->errorDesc, obj->errorDesc);
		this->FlushTimeEpochMicroSec = obj->FlushTimeEpochMicroSec;
		this->state = obj->state;
	}

	void operator=(const _dnsSession& obj)
	{
		this->transactionId = obj.transactionId;

		this->sourcePort = obj.sourcePort;
		this->destPort = obj.destPort;

		this->queryStartEpochNanoSec = obj.queryStartEpochNanoSec;
		this->queryEndEpochNanoSec = obj.queryEndEpochNanoSec;
		this->resolveTimeNanoSec = obj.resolveTimeNanoSec;
		this->pckLastTimeEpcohMicroSec = obj.pckLastTimeEpcohMicroSec;

		this->sourceIP = obj.sourceIP;
		this->destIP = obj.destIP;
		strcpy(this->address, obj.address);
		strcpy(this->URL, obj.URL);

		this->causeCode = obj.causeCode;
		this->errorCode = obj.errorCode;
		strcpy(this->errorDesc, obj.errorDesc);
		this->FlushTimeEpochMicroSec = obj.FlushTimeEpochMicroSec;
		this->state = obj.state;
	}

	void reset()
	{
		transactionId = 0;

		sourcePort = 0;
		destPort = 0;

		queryStartEpochNanoSec = 0;
		queryEndEpochNanoSec = 0;
		resolveTimeNanoSec = 0;
		pckLastTimeEpcohMicroSec = 0;

		sourceIP = 0;
		destIP = 0;
		address[0] = 0;
		URL[0] = 0;

		causeCode = 0;
		errorCode = 0;
		errorDesc[0] = 0;
		FlushTimeEpochMicroSec = 0;
		state = -1;
	}
}dnsSession;


//typedef std::map<uint64_t, fData> emptyPackTimeMap1;

//typedef struct _ipXdrData{
//
//	uint32_t 	teid_up;
//	uint32_t 	teid_dn;
//	bool		teidLookUp;
//	uint64_t	lastActivityTimeEpohSec;
//	uint32_t	sourceIP;
//	uint32_t	destIP;
//    char xdrData[XDR_MAX_LEN];
//
//    _ipXdrData()
//	{ reset(); }
//
//	void reset()
//	{
//		teid_up = 0;
//		teid_dn = 0;
//		teidLookUp = true;
//		lastActivityTimeEpohSec = 0;
//		sourceIP = 0;
//		destIP = 0;
//		xdrData[0] = 0;
//	}
//
//	_ipXdrData(const _ipXdrData& obj)
//	{
//		teid_up = obj.teid_up;
//		teid_dn = obj.teid_dn;
//		teidLookUp = obj.teidLookUp;
//		lastActivityTimeEpohSec = obj.lastActivityTimeEpohSec;
//		sourceIP = obj.sourceIP;
//		destIP = obj.destIP;
//		strcpy(this->xdrData, obj.xdrData);
//
//	}
//	void copy(const _ipXdrData* obj)
//	{
//		teid_up = obj->teid_up;
//		teid_dn = obj->teid_dn;
//		teidLookUp = obj->teidLookUp;
//		lastActivityTimeEpohSec = obj->lastActivityTimeEpohSec;
//		sourceIP = obj->sourceIP;
//		destIP = obj->destIP;
//		strcpy(xdrData, obj->xdrData);
//	}
//
//	void operator=(const _ipXdrData& obj)
//	{
//		teid_up = obj.teid_up;
//		teid_dn = obj.teid_dn;
//		teidLookUp = obj.teidLookUp;
//		lastActivityTimeEpohSec = obj.lastActivityTimeEpohSec;
//		sourceIP = obj.sourceIP;
//		destIP = obj.destIP;
//		strcpy(xdrData, obj.xdrData);
//	}
//
//	~_ipXdrData()
//	{
//
//	}
//}ipXdrData;

typedef struct _ipSession{

    uint16_t 	state;

    uint32_t	sourceIP;
    uint32_t	destIP;

    uint16_t 	sourcePort;
    uint16_t 	destPort;

    uint32_t 	teid_up;
    uint32_t 	teid_dn;

    uint32_t	sgsnIPAddr;
    uint32_t	ggsnIPAddr;

    uint16_t 	sgsnPort;
    uint16_t 	ggsnPort;

    uint16_t 	payloadPacket;
    uint16_t 	upPayloadPacket;
    uint16_t 	dnPayloadPacket;

    uint32_t	payloadSize;
    uint32_t	upPayloadSize;
    uint32_t	dnPayloadSize;

    uint16_t 	frameCount;
    uint16_t 	upFrameCount;
    uint16_t 	dnFrameCount;

    uint32_t	frameSize;
    uint32_t	upFrameSize;
    uint32_t	dnFrameSize;

    uint8_t 	sliceCounter;

    uint64_t 	pckLastTimeEpochSec;
    uint128_t 	pckLastTimeEpochNanoSec;

    uint64_t	startTimeEpochSec;
    uint128_t 	startTimeEpochNanoSec;

    uint64_t	endTimeEpochSec;
    uint128_t	endTimeEpochNanoSec;

    uint16_t 	pckTotalTimeSec;
    uint16_t	UpTotalTimeSec;
    uint16_t	DnTotalTimeSec;


	bool		isUpDir;

    char		sourceMacAddr[MAC_ADDR_LEN];
    char		destMacAddr[MAC_ADDR_LEN];

    bool		synRcv;
    bool		synAckRcv;
    bool		dataRcv;
    bool		finRcv;

    uint64_t	synTSval;
    uint64_t	synAckTSvl;
    uint64_t	synLatency;
    uint64_t  	pshTSecr;
    uint64_t  	pshTSval;
    uint16_t  	pshLatency;
    uint64_t	synStartSE;
    uint64_t	synEndSE;

    uint32_t 	sessionTP;
    uint32_t	peakSessionTP;
    uint32_t 	upSessionTP;
    uint32_t 	dnSessionTP;
    uint32_t	upPeakSessionTP;
    uint32_t 	dnPeakSessionTP;

	uint8_t		causeCode;
	uint8_t		protocolType;
	char		sessionKey[SESSION_ID_LEN];

	std::map<uint64_t, fData> packTimeMap;		//EpochTimeSec & fData
	char 		contentType[CONTENT_TYPE_LEN];
	uint128_t	synTimeEpochNanoSec;
	uint128_t	synAckTimeEpochNanoSec;
	uint128_t	ackTimeEpochNanoSec;
	uint128_t	finTimeEpochNanoSec;
    bool		firstDataFlag;
    uint128_t	firstDataTimeEpochNanoSec;
    uint32_t		appIp;

    int			mapIndex;

    char dnVolPerSec[VPS_MAX_LEN];
	char upVolPerSec[VPS_MAX_LEN];
	int	flushOrgId;
	uint64_t flushTime;
	uint64_t lastActivityTimeEpohSec;
	char URL[URL_LEN];
	char IMSI[IMSI_LEN];
	char MSISDN[MSISDN_LEN];
	char IMEI[IMEI_LEN];
	uint16_t	RAT;
	uint16_t	MCC;
	uint16_t	MNC;
	uint16_t	LAC;
	uint16_t	CI;
	bool		activeState;

	~_ipSession(){}

	_ipSession()
	{ reset(); }

	void reset()
	{
	    state = 0;

	    sourcePort = 0;
	    destPort = 0;

	    sourceIP = 0;
	    destIP = 0;

	    isUpDir=false;

	    teid_up = 0;
	    teid_dn = 0;

	    sgsnIPAddr = 0;
	    ggsnIPAddr = 0;

	    sgsnPort = 0;
	    ggsnPort = 0;

	    pckTotalTimeSec = 0;
	    UpTotalTimeSec = 0;
	    DnTotalTimeSec = 0;

	    payloadPacket = 0;
	    upPayloadPacket = 0;
	    dnPayloadPacket = 0;

	    payloadSize = 0;
	    upPayloadSize = 0;
	    dnPayloadSize = 0;

	    frameCount = 0;
	    upFrameCount = 0;
	    dnFrameCount = 0;

	    frameSize = 0;
	    upFrameSize = 0;
	    dnFrameSize = 0;

	    sliceCounter = 0;
	    pckLastTimeEpochSec = 0;
	    pckLastTimeEpochNanoSec = 0;
	    startTimeEpochNanoSec = 0;
	    endTimeEpochNanoSec = 0;
	    startTimeEpochSec = 0;
	    endTimeEpochSec = 0;

	    sourceMacAddr[0] = 0;
	    destMacAddr[0] = 0;

	    synRcv = false;
	    synAckRcv = false;
	    dataRcv = false;
	    finRcv = false;

	    synTSval = 0;
	    synAckTSvl = 0;
	    synLatency = 0;
	    pshTSecr = 0;
	    pshTSval = 0;
	    pshLatency = 0;
		synStartSE = 0;
		synEndSE = 0;

		sessionTP = 0;
		peakSessionTP = 0;
		upSessionTP = 0;
		dnSessionTP = 0;
		upPeakSessionTP = 0;
		dnPeakSessionTP = 0;

		causeCode = 0;
		protocolType = 0;
		sessionKey[0] = 0;

		packTimeMap.clear();
		contentType[0] = 0;

	    synTimeEpochNanoSec = 0;
	    synAckTimeEpochNanoSec = 0;
	    ackTimeEpochNanoSec = 0;
	    finTimeEpochNanoSec = 0;
	    firstDataFlag = false;
	    firstDataTimeEpochNanoSec = 0;
	    appIp = 0;
	    mapIndex = 0;
	    dnVolPerSec[0] = 0;
		upVolPerSec[0] = 0;
		flushOrgId = 0;
		flushTime = 0;
		lastActivityTimeEpohSec = 0;
		URL[0] = 0;
		IMSI[0] = 0;
		MSISDN[0] = 0;
		IMEI[0] = 0;
		RAT = 0;
		MCC = 0;
		MNC = 0;
		LAC = 0;
		CI = 0;
		activeState = false;
	}

	void reuse()
	{
		this->packTimeMap.clear();

		this->frameCount 		= 0;
		this->upFrameCount 	= 0;
		this->dnFrameCount 	= 0;
		this->frameSize 		= 0;
		this->upFrameSize 	= 0;
		this->dnFrameSize 	= 0;

		this->payloadPacket 	= 0;
		this->upPayloadPacket	= 0;
		this->dnPayloadPacket	= 0;

		this->payloadSize 	= 0;
		this->upPayloadSize 	= 0;
		this->dnPayloadSize 	= 0;

		this->startTimeEpochNanoSec = pckLastTimeEpochNanoSec;

		this->pckTotalTimeSec = 0;
		this->sessionTP 		= 0;
		this->peakSessionTP 	= 0;

		this->upSessionTP 	= 0;
		this->upPeakSessionTP	= 0;
		this->dnSessionTP 	= 0;
		this->dnPeakSessionTP	= 0;
		this->dnVolPerSec[0] = 0;
		this->upVolPerSec[0] = 0;
	}

	_ipSession(const _ipSession& obj)
	{
	    this->state = obj.state;
	    this->sourcePort = obj.sourcePort;
	    this->destPort = obj.destPort;

	    this->sourceIP = obj.sourceIP;
	    this->destIP = obj.destIP;

	    this->isUpDir = obj.isUpDir;

	    this->teid_up = obj.teid_up;
	    this->teid_dn = obj.teid_dn;

	    this->sgsnIPAddr = obj.sgsnIPAddr;
	    this->ggsnIPAddr = obj.ggsnIPAddr;
	    this->sgsnPort = obj.sgsnPort;
	    this->ggsnPort = obj.ggsnPort;

	    this->pckTotalTimeSec = obj.pckTotalTimeSec;
	    this->UpTotalTimeSec = obj.UpTotalTimeSec;
	    this->DnTotalTimeSec = obj.DnTotalTimeSec;

	    this->payloadPacket = obj.payloadPacket;
	    this->upPayloadPacket = obj.upPayloadPacket;
	    this->dnPayloadPacket = obj.dnPayloadPacket;

	    this->payloadSize = obj.payloadSize;
	    this->upPayloadSize = obj.upPayloadSize;
	    this->dnPayloadSize = obj.dnPayloadSize;

	    this->frameCount = obj.frameCount;
	    this->upFrameCount = obj.upFrameCount;
	    this->dnFrameCount = obj.dnFrameCount;

	    this->frameSize = obj.frameSize;
	    this->upFrameSize = obj.upFrameSize;
	    this->dnFrameSize = obj.dnFrameSize;

	    this->sliceCounter = obj.sliceCounter;

	    this->pckLastTimeEpochSec = obj.pckLastTimeEpochSec;
	    this->pckLastTimeEpochNanoSec = obj.pckLastTimeEpochNanoSec;
	    this->startTimeEpochNanoSec = obj.startTimeEpochNanoSec;
	    this->endTimeEpochNanoSec = obj.endTimeEpochNanoSec;
	    this->startTimeEpochSec = obj.startTimeEpochSec;
	    this->endTimeEpochSec = obj.endTimeEpochSec;

	    strcpy(this->sourceMacAddr, obj.sourceMacAddr);
	    strcpy(this->destMacAddr, obj.destMacAddr);

	    this->synRcv = obj.synRcv;
	    this->synAckRcv = obj.synAckRcv;
	    this->dataRcv = obj.dataRcv;
	    this->finRcv = obj.finRcv;

	    this->synTSval = obj.synTSval;
	    this->synAckTSvl = obj.synAckTSvl;
	    this->synLatency = obj.synLatency;
	    this->pshTSecr = obj.pshTSecr;
	    this->pshTSval = obj.pshTSval;
	    this->pshLatency = obj.pshLatency;
	    this->synStartSE = obj.synStartSE;
	    this->synEndSE = obj.synEndSE;

	    this->sessionTP = obj.sessionTP;
	    this->peakSessionTP = obj.peakSessionTP;
	    this->upSessionTP = obj.upSessionTP;
	    this->dnSessionTP = obj.dnSessionTP;
	    this->upPeakSessionTP = obj.upPeakSessionTP;
	    this->dnPeakSessionTP = obj.dnPeakSessionTP;

	    this->causeCode = obj.causeCode;
	    this->protocolType = obj.protocolType;
	    strcpy(this->sessionKey,obj.sessionKey);
	    packTimeMap = obj.packTimeMap;
	    strcpy(this->contentType, obj.contentType);

	    this->synTimeEpochNanoSec = obj.synTimeEpochNanoSec;
	    this->synAckTimeEpochNanoSec = obj.synAckTimeEpochNanoSec;
	    this->ackTimeEpochNanoSec = obj.ackTimeEpochNanoSec;
	    this->finTimeEpochNanoSec = obj.finTimeEpochNanoSec;
	    this->firstDataFlag = obj.firstDataFlag;
	    this->firstDataTimeEpochNanoSec = obj.firstDataTimeEpochNanoSec;
	    this->appIp = obj.appIp;
	    this->mapIndex = obj.mapIndex;
	    strcpy(this->dnVolPerSec, obj.dnVolPerSec);
		strcpy(this->upVolPerSec, obj.upVolPerSec);

		this->flushOrgId = obj.flushOrgId;
		this->flushTime = obj.flushTime;
		this->lastActivityTimeEpohSec = obj.lastActivityTimeEpohSec;
		strcpy(this->URL, obj.URL);
		strcpy(this->IMSI, obj.IMSI);
		strcpy(this->MSISDN, obj.MSISDN);
		strcpy(this->IMEI, obj.IMEI);
		this->RAT = obj.RAT;
		this->MCC = obj.MCC;
		this->MNC = obj.MNC;
		this->LAC = obj.LAC;
		this->CI = obj.CI;
		this->activeState = obj.activeState;
	}


	void copy(const _ipSession* obj)
	{
		state = obj->state;
	    sourcePort = obj->sourcePort;
	    destPort = obj->destPort;

	    sourceIP = obj->sourceIP;
	    destIP = obj->destIP;

	    isUpDir = obj->isUpDir;

	    teid_up = obj->teid_up;
	    teid_dn = obj->teid_dn;

	    sgsnIPAddr = obj->sgsnIPAddr;
	    ggsnIPAddr = obj->ggsnIPAddr;
	    sgsnPort = obj->sgsnPort;
	    ggsnPort = obj->ggsnPort;

	    pckTotalTimeSec = obj->pckTotalTimeSec;
	    UpTotalTimeSec = obj->UpTotalTimeSec;
	    DnTotalTimeSec = obj->DnTotalTimeSec;

	    payloadPacket = obj->payloadPacket;
	    upPayloadPacket = obj->upPayloadPacket;
	    dnPayloadPacket = obj->dnPayloadPacket;

	    payloadSize = obj->payloadSize;
	    upPayloadSize = obj->upPayloadSize;
	    dnPayloadSize = obj->dnPayloadSize;

	    frameCount = obj->frameCount;
	    upFrameCount = obj->upFrameCount;
	    dnFrameCount = obj->dnFrameCount;

	    frameSize = obj->frameSize;
	    upFrameSize = obj->upFrameSize;
	    dnFrameSize = obj->dnFrameSize;

	    sliceCounter = obj->sliceCounter;

	    pckLastTimeEpochSec = obj->pckLastTimeEpochSec;
	    pckLastTimeEpochNanoSec = obj->pckLastTimeEpochNanoSec;
	    startTimeEpochNanoSec = obj->startTimeEpochNanoSec;
	    endTimeEpochNanoSec = obj->endTimeEpochNanoSec;
	    startTimeEpochSec = obj->startTimeEpochSec;
	    endTimeEpochSec = obj->endTimeEpochSec;

	    strcpy(sourceMacAddr, obj->sourceMacAddr);
	    strcpy(destMacAddr, obj->destMacAddr);

	    synRcv = obj->synRcv;
	    synAckRcv = obj->synAckRcv;
	    dataRcv = obj->dataRcv;
	    finRcv = obj->finRcv;


	    synTSval = obj->synTSval;
	    synAckTSvl = obj->synAckTSvl;
	    synLatency = obj->synLatency;
	    pshTSecr = obj->pshTSecr;
	    pshTSval = obj->pshTSval;
	    pshLatency = obj->pshLatency;
	    synStartSE = obj->synStartSE;
	    synEndSE = obj->synEndSE;

	    sessionTP = obj->sessionTP;
	    peakSessionTP = obj->peakSessionTP;
	    upSessionTP = obj->upSessionTP;
	    dnSessionTP = obj->dnSessionTP;
	    upPeakSessionTP = obj->upPeakSessionTP;
	    dnPeakSessionTP = obj->dnPeakSessionTP;

	    causeCode = obj->causeCode;
	    protocolType = obj->protocolType;
	    strcpy(sessionKey,obj->sessionKey);
	    packTimeMap = obj->packTimeMap;
	    strcpy(contentType, obj->contentType);

	    synTimeEpochNanoSec = obj->synTimeEpochNanoSec;
	    synAckTimeEpochNanoSec = obj->synAckTimeEpochNanoSec;
	    ackTimeEpochNanoSec = obj->ackTimeEpochNanoSec;
	    finTimeEpochNanoSec = obj->finTimeEpochNanoSec;
	    firstDataFlag = obj->firstDataFlag;
	    firstDataTimeEpochNanoSec = obj->firstDataTimeEpochNanoSec;
	    appIp = obj->appIp;
	    mapIndex = obj->mapIndex;
	    strcpy(dnVolPerSec, obj->dnVolPerSec);
		strcpy(upVolPerSec, obj->upVolPerSec);

		flushOrgId = obj->flushOrgId;
		flushTime = obj->flushTime;
		lastActivityTimeEpohSec = obj->lastActivityTimeEpohSec;
		strcpy(URL, obj->URL);
		strcpy(IMSI, obj->IMSI);
		strcpy(MSISDN, obj->MSISDN);
		strcpy(IMEI, obj->IMEI);
		RAT = obj->RAT;
		MCC = obj->MCC;
		MNC = obj->MNC;
		LAC = obj->LAC;
		CI = obj->CI;
		activeState = obj->activeState;
	}

	void operator=(const _ipSession& obj)
	{
	    state = obj.state;

	    sourcePort = obj.sourcePort;
	    destPort = obj.destPort;

	    sourceIP = obj.sourceIP;
	    destIP = obj.destIP;

	    isUpDir = obj.isUpDir;

	    teid_up = obj.teid_up;
	    teid_dn = obj.teid_dn;

	    sgsnIPAddr = obj.sgsnIPAddr;
	    ggsnIPAddr = obj.ggsnIPAddr;
	    sgsnPort = obj.sgsnPort;
	    ggsnPort = obj.ggsnPort;

	    pckTotalTimeSec = obj.pckTotalTimeSec;
	    UpTotalTimeSec = obj.UpTotalTimeSec;
	    DnTotalTimeSec = obj.DnTotalTimeSec;

	    payloadPacket = obj.payloadPacket;
	    upPayloadPacket = obj.upPayloadPacket;
	    dnPayloadPacket = obj.dnPayloadPacket;

	    payloadSize = obj.payloadSize;
	    upPayloadSize = obj.upPayloadSize;
	    dnPayloadSize = obj.dnPayloadSize;

	    frameCount = obj.frameCount;
	    upFrameCount = obj.upFrameCount;
	    dnFrameCount = obj.dnFrameCount;

	    frameSize = obj.frameSize;
	    upFrameSize = obj.upFrameSize;
	    dnFrameSize = obj.dnFrameSize;

	    sliceCounter = obj.sliceCounter;

	    pckLastTimeEpochSec = obj.pckLastTimeEpochSec;
	    pckLastTimeEpochNanoSec = obj.pckLastTimeEpochNanoSec;
	    startTimeEpochNanoSec = obj.startTimeEpochNanoSec;
	    endTimeEpochNanoSec = obj.endTimeEpochNanoSec;
	    startTimeEpochSec = obj.startTimeEpochSec;
	    endTimeEpochSec = obj.endTimeEpochSec;

	    strcpy(sourceMacAddr, obj.sourceMacAddr);
	    strcpy(destMacAddr, obj.destMacAddr);

	    synRcv = obj.synRcv;
	    synAckRcv = obj.synAckRcv;
	    dataRcv = obj.dataRcv;
	    finRcv = obj.finRcv;

	    synTSval = obj.synTSval;
	    synAckTSvl = obj.synAckTSvl;
	    synLatency = obj.synLatency;
	    pshTSecr = obj.pshTSecr;
	    pshTSval = obj.pshTSval;
	    pshLatency = obj.pshLatency;
	    synStartSE = obj.synStartSE;
	    synEndSE = obj.synEndSE;

	    sessionTP = obj.sessionTP;
	    peakSessionTP = obj.peakSessionTP;
	    upSessionTP = obj.upSessionTP;
	    dnSessionTP = obj.dnSessionTP;
	    upPeakSessionTP = obj.upPeakSessionTP;
	    dnPeakSessionTP = obj.dnPeakSessionTP;

	    causeCode = obj.causeCode;
	    protocolType = obj.protocolType;
	    strcpy(sessionKey,obj.sessionKey);
	    packTimeMap = obj.packTimeMap;

	    strcpy(contentType, obj.contentType);

	    synTimeEpochNanoSec = obj.synTimeEpochNanoSec;
	    synAckTimeEpochNanoSec = obj.synAckTimeEpochNanoSec;
	    ackTimeEpochNanoSec = obj.ackTimeEpochNanoSec;
	    finTimeEpochNanoSec = obj.finTimeEpochNanoSec;
	    firstDataFlag = obj.firstDataFlag;
	    firstDataTimeEpochNanoSec = obj.firstDataTimeEpochNanoSec;
	    appIp = obj.appIp;
	    mapIndex = obj.mapIndex;
	    strcpy(dnVolPerSec, obj.dnVolPerSec);
		strcpy(upVolPerSec, obj.upVolPerSec);

		flushOrgId = obj.flushOrgId;
		flushTime = obj.flushTime;
		lastActivityTimeEpohSec = obj.lastActivityTimeEpohSec;
		strcpy(URL, obj.URL);
		strcpy(IMSI, obj.IMSI);
		strcpy(MSISDN, obj.MSISDN);
		strcpy(IMEI, obj.IMEI);
		RAT = obj.RAT;
		MCC = obj.MCC;
		MNC = obj.MNC;
		LAC = obj.LAC;
		CI = obj.CI;
		activeState = obj.activeState;
	}
}ipSession;

typedef struct _tcpSession{

	uint16_t 	cType;
    uint16_t 	state;

    uint32_t 	sourcePort;
    uint32_t 	destPort;

    uint32_t 	teid;
    ULONG 		dataPackTimeEpochNanoSec;
    ULONG 		pckLastTimeEpochNanoSec;

    uint32_t 	payloadPacket;
    uint32_t 	upPayloadPacket;
    uint32_t 	dnPayloadPacket;

    ULONG	 	payloadSize;
    ULONG	 	upPayloadSize;
    ULONG	 	dnPayloadSize;

    uint32_t 	frameCount;
    uint32_t 	upFrameCount;
    uint32_t 	dnFrameCount;

    ULONG	 	frameSize;
    ULONG	 	upFrameSize;
    ULONG	 	dnFrameSize;

    uint32_t 	sliceCounter;

    ULONG 		startTimeEpochNanoSec;
    ULONG 		endTimeEpochNanoSec;

    ULONG 		startTimeEpochSec;
    ULONG 		endTimeEpochSec;

    uint32_t 	pckTotalTimeSec;
    uint32_t	UpTotalTimeSec;
    uint32_t	DnTotalTimeSec;

    uint32_t	sourceIP;
    uint32_t	destIP;

	bool		isUpDir;

    std::string	sourceMacAddr;
    std::string	destMacAddr;

    ULONG	  	synTSval;
    ULONG	  	synAckTSvl;
    ULONG	  	synLatency;
    ULONG 	  	pshTSecr;
    ULONG 	  	pshTSval;
    ULONG 	  	pshLatency;
	ULONG		synStartSE;
	ULONG		synEndSE;

	ULONG 		sessionTP;
	ULONG	 	peakSessionTP;
	ULONG 		upSessionTP;
	ULONG 		dnSessionTP;
	ULONG	 	upPeakSessionTP;
	ULONG 		dnPeakSessionTP;

	uint16_t	causeCode;
	uint16_t	protocolType;
	std::string	sessionKey;

	std::map<ULONG, fData> packTimeMap;		//EpochTimeSec & fData
	std::string 	contentType;
    ULONG	 		synTimeMs;
    ULONG			synAckTimeMs;
    ULONG			ackTimeMs;
    ULONG			finTimeMs;
    bool			firstDataFlag;
    ULONG			firstDataTimeMs;
    std::string		appIp;

	_tcpSession()
	{ reset(); }

	void set(const _tcpSession *obj)
	{
		this->cType = obj->cType;
	    this->state = obj->state;

	    this->sourcePort = obj->sourcePort;
	    this->destPort = obj->destPort;

	    this->sourceIP = obj->sourceIP;
	    this->destIP = obj->destIP;

	    this->isUpDir = obj->isUpDir;

	    this->teid = obj->teid;
	    this->dataPackTimeEpochNanoSec = obj->dataPackTimeEpochNanoSec;
	    this->pckLastTimeEpochNanoSec = obj->pckLastTimeEpochNanoSec;
	    this->pckTotalTimeSec = obj->pckTotalTimeSec;
	    this->UpTotalTimeSec = obj->UpTotalTimeSec;
	    this->DnTotalTimeSec = obj->DnTotalTimeSec;

	    this->payloadPacket = obj->payloadPacket;
	    this->upPayloadPacket = obj->upPayloadPacket;
	    this->dnPayloadPacket = obj->dnPayloadPacket;

	    this->payloadSize = obj->payloadSize;
	    this->upPayloadSize = obj->upPayloadSize;
	    this->dnPayloadSize = obj->dnPayloadSize;

	    this->frameCount = obj->frameCount;
	    this->upFrameCount = obj->upFrameCount;
	    this->dnFrameCount = obj->dnFrameCount;

	    this->frameSize = obj->frameSize;
	    this->upFrameSize = obj->upFrameSize;
	    this->dnFrameSize = obj->dnFrameSize;

	    this->sliceCounter = obj->sliceCounter;

	    this->startTimeEpochNanoSec = obj->startTimeEpochNanoSec;
	    this->endTimeEpochNanoSec = obj->endTimeEpochNanoSec;
	    this->startTimeEpochSec = obj->startTimeEpochSec;
	    this->endTimeEpochSec = obj->endTimeEpochSec;

	    this->sourceMacAddr.assign(obj->sourceMacAddr);
	    this->destMacAddr.assign(obj->destMacAddr);

	    this->synTSval = obj->synTSval;
	    this->synAckTSvl = obj->synAckTSvl;
	    this->synLatency = obj->synLatency;
	    this->pshTSecr = obj->pshTSecr;
	    this->pshTSval = obj->pshTSval;
	    this->pshLatency = obj->pshLatency;
	    this->synStartSE = obj->synStartSE;
	    this->synEndSE = obj->synEndSE;

	    this->sessionTP = obj->sessionTP;
	    this->peakSessionTP = obj->peakSessionTP;
	    this->upSessionTP = obj->upSessionTP;
	    this->dnSessionTP = obj->dnSessionTP;
	    this->upPeakSessionTP = obj->upPeakSessionTP;
	    this->dnPeakSessionTP = obj->dnPeakSessionTP;

	    this->causeCode = obj->causeCode;
	    this->protocolType = obj->protocolType;
	    this->sessionKey.assign(obj->sessionKey);

	    this->packTimeMap = obj->packTimeMap;
	    this->contentType.assign(obj->contentType);

	    this->synTimeMs = obj->synTimeMs;
	    this->synAckTimeMs = obj->synAckTimeMs;
	    this->ackTimeMs = obj->ackTimeMs;
	    this->finTimeMs = obj->finTimeMs;
	    this->firstDataFlag = obj->firstDataFlag;
	    this->firstDataTimeMs = obj->firstDataTimeMs;
	    this->appIp = obj->appIp;
	}

	void reset()
	{
		cType = 0;
	    state = 0;

	    sourcePort = 0;
	    destPort = 0;

	    sourceIP = 0;
	    destIP = 0;

	    isUpDir=false;

	    teid = 0;
	    dataPackTimeEpochNanoSec = 0;
	    pckLastTimeEpochNanoSec = 0;
	    pckTotalTimeSec = 0;
	    UpTotalTimeSec = 0;
	    DnTotalTimeSec = 0;

	    payloadPacket = 0;
	    upPayloadPacket = 0;
	    dnPayloadPacket = 0;

	    payloadSize = 0;
	    upPayloadSize = 0;
	    dnPayloadSize = 0;

	    frameCount = 0;
	    upFrameCount = 0;
	    dnFrameCount = 0;

	    frameSize = 0;
	    upFrameSize = 0;
	    dnFrameSize = 0;

	    sliceCounter = 0;

	    startTimeEpochNanoSec = 0;
	    endTimeEpochNanoSec = 0;
	    startTimeEpochSec = 0;
	    endTimeEpochSec = 0;

	    sourceMacAddr.clear();
	    destMacAddr.clear();

	    synTSval = 0;
	    synAckTSvl = 0;
	    synLatency = 0;
	    pshTSecr = 0;
	    pshTSval = 0;
	    pshLatency = 0;
		synStartSE = 0;
		synEndSE = 0;

		sessionTP = 0;
		peakSessionTP = 0;
		upSessionTP = 0;
		dnSessionTP = 0;
		upPeakSessionTP = 0;
		dnPeakSessionTP = 0;

		causeCode = 0;
		protocolType = 0;
		sessionKey.clear();

		packTimeMap.clear();
		contentType.clear();

	    synTimeMs = 0;
	    synAckTimeMs = 0;
	    ackTimeMs = 0;
	    finTimeMs = 0;
	    firstDataFlag = false;
	    firstDataTimeMs = 0;
	    appIp = "NULL";
	}
}tcpSession;

typedef struct _udpSession{

	uint16_t 	state;

    uint32_t 	sourcePort;
    uint32_t 	destPort;

    uint32_t	sourceIP;
    uint32_t	destIP;

	bool		isUpDir;

    ULONG 		dataPackTimeEpochNanoSec;
    ULONG 		pckLastTimeEpochNanoSec;

    uint32_t 	pckTotalTimeSec;
    uint32_t	UpTotalTimeSec;
    uint32_t	DnTotalTimeSec;

    uint32_t 	payloadPacket;
    uint32_t 	upPayloadPacket;
    uint32_t 	dnPayloadPacket;

    ULONG	 	payloadSize;
    ULONG	 	upPayloadSize;
    ULONG	 	dnPayloadSize;

    uint32_t 	frameCount = 0;
    uint32_t 	upFrameCount = 0;
    uint32_t 	dnFrameCount = 0;

    ULONG	 	frameSize = 0;
    ULONG	 	upFrameSize = 0;
    ULONG	 	dnFrameSize = 0;

    uint32_t 	sliceCounter;

    ULONG 		startTimeEpochNanoSec;
    ULONG 		endTimeEpochNanoSec;

    std::string	sourceMacAddr;
    std::string	destMacAddr;

	ULONG 		sessionTP;
	ULONG	 	peakSessionTP;
	ULONG 		upSessionTP;
	ULONG 		dnSessionTP;
	ULONG	 	upPeakSessionTP;
	ULONG 		dnPeakSessionTP;

	uint16_t	causeCode;
	uint16_t	protocolType;
	std::string	sessionKey;
	uint32_t 	teid;

	std::map<ULONG, fData> packTimeMap;		//EpochTimeSec & fData
	std::string	appIp;

	_udpSession()
	{ reset(); }

	void set(const _udpSession *obj)
	{
	    this->state = obj->state;

	    this->sourcePort = obj->sourcePort;
	    this->destPort = obj->destPort;

	    this->sourceIP = obj->sourceIP;
	    this->destIP = obj->destIP;

	    this->isUpDir = obj->isUpDir;

	    this->dataPackTimeEpochNanoSec = obj->dataPackTimeEpochNanoSec;
	    this->pckLastTimeEpochNanoSec = obj->pckLastTimeEpochNanoSec;
	    this->pckTotalTimeSec = obj->pckTotalTimeSec;
	    this->UpTotalTimeSec = obj->UpTotalTimeSec;
	    this->DnTotalTimeSec = obj->DnTotalTimeSec;

	    this->payloadPacket = obj->payloadPacket;
	    this->upPayloadPacket = obj->upPayloadPacket;
	    this->dnPayloadPacket = obj->dnPayloadPacket;

	    this->payloadSize = obj->payloadSize;
	    this->upPayloadSize = obj->upPayloadSize;
	    this->dnPayloadSize = obj->dnPayloadSize;

	    this->frameCount = obj->frameCount;
	    this->upFrameCount = obj->upFrameCount;
	    this->dnFrameCount = obj->dnFrameCount;

	    this->frameSize = obj->frameSize;
	    this->upFrameSize = obj->upFrameSize;
	    this->dnFrameSize = obj->dnFrameSize;

	    this->sliceCounter = obj->sliceCounter;

	    this->startTimeEpochNanoSec = obj->startTimeEpochNanoSec;
	    this->endTimeEpochNanoSec = obj->endTimeEpochNanoSec;

	    this->sourceMacAddr.assign(obj->sourceMacAddr);
	    this->destMacAddr.assign(obj->destMacAddr);

	    this->sessionTP = obj->sessionTP;
	    this->peakSessionTP = obj->peakSessionTP;
	    this->upSessionTP = obj->upSessionTP;
	    this->dnSessionTP = obj->dnSessionTP;
	    this->upPeakSessionTP = obj->upPeakSessionTP;
	    this->dnPeakSessionTP = obj->dnPeakSessionTP;

	    this->causeCode = obj->causeCode;
	    this->protocolType = obj->protocolType;
	    this->sessionKey.assign(obj->sessionKey);

	    this->packTimeMap = obj->packTimeMap;
	    this->teid = obj->teid;
	    this->appIp = obj->appIp;
	}

	void reset()
	{
	    state 		= 0;

	    sourcePort = 0;
	    destPort = 0;

	    sourceIP = 0;
	    destIP = 0;

	    isUpDir = false;

	    dataPackTimeEpochNanoSec = 0;
	    pckLastTimeEpochNanoSec = 0;
	    pckTotalTimeSec = 0;
	    UpTotalTimeSec = 0;
	    DnTotalTimeSec = 0;

	    payloadPacket = 0;
	    upPayloadPacket = 0;
	    dnPayloadPacket = 0;

	    payloadSize = 0;
	    upPayloadSize = 0;
	    dnPayloadSize = 0;

	    frameCount = 0;
	    upFrameCount = 0;
	    dnFrameCount = 0;

	    frameSize = 0;
	    upFrameSize = 0;
	    dnFrameSize = 0;

	    sliceCounter = 0;

	    startTimeEpochNanoSec = 0;
	    endTimeEpochNanoSec = 0;

	    sourceMacAddr.clear();
	    destMacAddr.clear();

		sessionTP = 0;
		peakSessionTP = 0;
		upSessionTP = 0;
		dnSessionTP = 0;
		upPeakSessionTP = 0;
		dnPeakSessionTP = 0;

		causeCode = 0;
		protocolType = 0;

		sessionKey.clear();
		packTimeMap.clear();
		teid = 0;
		appIp = "NULL";
	}
}udpSession;

typedef struct _otrSession{

    int32_t		protocol;

	std::string sessionKey;

	string		sourceMacAddr;
	string		destMacAddr;

	uint32_t		sourceIP;
	uint32_t		destIP;

    ULONG	 	frameSize;
    ULONG	 	upFrameSize;
    ULONG	 	dnFrameSize;

    ULONG		startTimeEpochNanoSec;
    ULONG		endTimeEpochNanoSec;
    ULONG 		startTimeEpochSec;
    ULONG 		endTimeEpochSec;

    _otrSession()
    { reset(); }

	void set(const _otrSession *obj)
	{
		this->protocol = obj->protocol;

		this->sessionKey.assign(obj->sessionKey);

		this->sourceMacAddr.assign(obj->sourceMacAddr);
		this->destMacAddr.assign(obj->destMacAddr);

		this->sourceIP = obj->sourceIP;
		this->destIP = obj->destIP;

		this->frameSize = obj->frameSize;
		this->upFrameSize = obj->upFrameSize;
		this->dnFrameSize = obj->dnFrameSize;

		this->startTimeEpochNanoSec = obj->startTimeEpochNanoSec;
		this->endTimeEpochNanoSec = obj->endTimeEpochNanoSec;

		this->startTimeEpochSec = obj->startTimeEpochSec;
	    this->endTimeEpochSec = obj->endTimeEpochSec;
	}

    void reset()
	{
		protocol = 0;

		sessionKey.clear();

		sourceMacAddr.clear();
		destMacAddr.clear();

		sourceIP = 0;
		destIP = 0;

		frameSize = 0;
		upFrameSize = 0;
		dnFrameSize = 0;

		startTimeEpochNanoSec = 0;
		endTimeEpochNanoSec = 0;

	    startTimeEpochSec = 0;
	    endTimeEpochSec = 0;
	}
}otrSession;

namespace DnsDataMap {
	extern std::map<uint32_t, std::string> dailyDnsDump;
}

namespace DNSGlobal
{
	extern std::map<string, dnsUrl> dnsDatabaseMap_0;
	extern std::map<string, dnsUrl> dnsDatabaseMap_1;
	extern std::map<string, dnsUrl> dnsDatabaseMap_2;
	extern std::map<string, dnsUrl> dnsDatabaseMap_3;
	extern std::map<string, dnsUrl> dnsDatabaseMap_4;
	extern std::map<string, dnsUrl> dnsDatabaseMap_5;
	extern std::map<string, dnsUrl> dnsDatabaseMap_6;
	extern std::map<string, dnsUrl> dnsDatabaseMap_7;
	extern std::map<string, dnsUrl> dnsDatabaseMap_8;
	extern std::map<string, dnsUrl> dnsDatabaseMap_9;

	extern std::map<uint32_t, string> dnsLookUpMap_0;
	extern std::map<uint32_t, string> dnsLookUpMap_1;
	extern std::map<uint32_t, string> dnsLookUpMap_2;
	extern std::map<uint32_t, string> dnsLookUpMap_3;
	extern std::map<uint32_t, string> dnsLookUpMap_4;
	extern std::map<uint32_t, string> dnsLookUpMap_5;
	extern std::map<uint32_t, string> dnsLookUpMap_6;
	extern std::map<uint32_t, string> dnsLookUpMap_7;
	extern std::map<uint32_t, string> dnsLookUpMap_8;
	extern std::map<uint32_t, string> dnsLookUpMap_9;
}

namespace IPFlushRepository {

	extern std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_9;

	extern int ipFlushMap_f_0_sm_0_t_0_cnt;
	extern int ipFlushMap_f_0_sm_0_t_1_cnt;
	extern int ipFlushMap_f_0_sm_0_t_2_cnt;
	extern int ipFlushMap_f_0_sm_0_t_3_cnt;
	extern int ipFlushMap_f_0_sm_0_t_4_cnt;
	extern int ipFlushMap_f_0_sm_0_t_5_cnt;
	extern int ipFlushMap_f_0_sm_0_t_6_cnt;
	extern int ipFlushMap_f_0_sm_0_t_7_cnt;
	extern int ipFlushMap_f_0_sm_0_t_8_cnt;
	extern int ipFlushMap_f_0_sm_0_t_9_cnt;

	extern std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_9;

	extern int ipFlushMap_f_0_sm_1_t_0_cnt;
	extern int ipFlushMap_f_0_sm_1_t_1_cnt;
	extern int ipFlushMap_f_0_sm_1_t_2_cnt;
	extern int ipFlushMap_f_0_sm_1_t_3_cnt;
	extern int ipFlushMap_f_0_sm_1_t_4_cnt;
	extern int ipFlushMap_f_0_sm_1_t_5_cnt;
	extern int ipFlushMap_f_0_sm_1_t_6_cnt;
	extern int ipFlushMap_f_0_sm_1_t_7_cnt;
	extern int ipFlushMap_f_0_sm_1_t_8_cnt;
	extern int ipFlushMap_f_0_sm_1_t_9_cnt;

	extern std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_9;

	extern int ipFlushMap_f_0_sm_2_t_0_cnt;
	extern int ipFlushMap_f_0_sm_2_t_1_cnt;
	extern int ipFlushMap_f_0_sm_2_t_2_cnt;
	extern int ipFlushMap_f_0_sm_2_t_3_cnt;
	extern int ipFlushMap_f_0_sm_2_t_4_cnt;
	extern int ipFlushMap_f_0_sm_2_t_5_cnt;
	extern int ipFlushMap_f_0_sm_2_t_6_cnt;
	extern int ipFlushMap_f_0_sm_2_t_7_cnt;
	extern int ipFlushMap_f_0_sm_2_t_8_cnt;
	extern int ipFlushMap_f_0_sm_2_t_9_cnt;

	extern std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_9;

	extern int ipFlushMap_f_0_sm_3_t_0_cnt;
	extern int ipFlushMap_f_0_sm_3_t_1_cnt;
	extern int ipFlushMap_f_0_sm_3_t_2_cnt;
	extern int ipFlushMap_f_0_sm_3_t_3_cnt;
	extern int ipFlushMap_f_0_sm_3_t_4_cnt;
	extern int ipFlushMap_f_0_sm_3_t_5_cnt;
	extern int ipFlushMap_f_0_sm_3_t_6_cnt;
	extern int ipFlushMap_f_0_sm_3_t_7_cnt;
	extern int ipFlushMap_f_0_sm_3_t_8_cnt;
	extern int ipFlushMap_f_0_sm_3_t_9_cnt;

	extern std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_9;

	extern int ipFlushMap_f_0_sm_4_t_0_cnt;
	extern int ipFlushMap_f_0_sm_4_t_1_cnt;
	extern int ipFlushMap_f_0_sm_4_t_2_cnt;
	extern int ipFlushMap_f_0_sm_4_t_3_cnt;
	extern int ipFlushMap_f_0_sm_4_t_4_cnt;
	extern int ipFlushMap_f_0_sm_4_t_5_cnt;
	extern int ipFlushMap_f_0_sm_4_t_6_cnt;
	extern int ipFlushMap_f_0_sm_4_t_7_cnt;
	extern int ipFlushMap_f_0_sm_4_t_8_cnt;
	extern int ipFlushMap_f_0_sm_4_t_9_cnt;

	extern std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_9;

	extern int ipFlushMap_f_1_sm_0_t_0_cnt;
	extern int ipFlushMap_f_1_sm_0_t_1_cnt;
	extern int ipFlushMap_f_1_sm_0_t_2_cnt;
	extern int ipFlushMap_f_1_sm_0_t_3_cnt;
	extern int ipFlushMap_f_1_sm_0_t_4_cnt;
	extern int ipFlushMap_f_1_sm_0_t_5_cnt;
	extern int ipFlushMap_f_1_sm_0_t_6_cnt;
	extern int ipFlushMap_f_1_sm_0_t_7_cnt;
	extern int ipFlushMap_f_1_sm_0_t_8_cnt;
	extern int ipFlushMap_f_1_sm_0_t_9_cnt;

	extern std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_9;

	extern int ipFlushMap_f_1_sm_1_t_0_cnt;
	extern int ipFlushMap_f_1_sm_1_t_1_cnt;
	extern int ipFlushMap_f_1_sm_1_t_2_cnt;
	extern int ipFlushMap_f_1_sm_1_t_3_cnt;
	extern int ipFlushMap_f_1_sm_1_t_4_cnt;
	extern int ipFlushMap_f_1_sm_1_t_5_cnt;
	extern int ipFlushMap_f_1_sm_1_t_6_cnt;
	extern int ipFlushMap_f_1_sm_1_t_7_cnt;
	extern int ipFlushMap_f_1_sm_1_t_8_cnt;
	extern int ipFlushMap_f_1_sm_1_t_9_cnt;

	extern std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_9;

	extern int ipFlushMap_f_1_sm_2_t_0_cnt;
	extern int ipFlushMap_f_1_sm_2_t_1_cnt;
	extern int ipFlushMap_f_1_sm_2_t_2_cnt;
	extern int ipFlushMap_f_1_sm_2_t_3_cnt;
	extern int ipFlushMap_f_1_sm_2_t_4_cnt;
	extern int ipFlushMap_f_1_sm_2_t_5_cnt;
	extern int ipFlushMap_f_1_sm_2_t_6_cnt;
	extern int ipFlushMap_f_1_sm_2_t_7_cnt;
	extern int ipFlushMap_f_1_sm_2_t_8_cnt;
	extern int ipFlushMap_f_1_sm_2_t_9_cnt;

	extern std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_9;

	extern int ipFlushMap_f_1_sm_3_t_0_cnt;
	extern int ipFlushMap_f_1_sm_3_t_1_cnt;
	extern int ipFlushMap_f_1_sm_3_t_2_cnt;
	extern int ipFlushMap_f_1_sm_3_t_3_cnt;
	extern int ipFlushMap_f_1_sm_3_t_4_cnt;
	extern int ipFlushMap_f_1_sm_3_t_5_cnt;
	extern int ipFlushMap_f_1_sm_3_t_6_cnt;
	extern int ipFlushMap_f_1_sm_3_t_7_cnt;
	extern int ipFlushMap_f_1_sm_3_t_8_cnt;
	extern int ipFlushMap_f_1_sm_3_t_9_cnt;

	extern std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_9;

	extern int ipFlushMap_f_1_sm_4_t_0_cnt;
	extern int ipFlushMap_f_1_sm_4_t_1_cnt;
	extern int ipFlushMap_f_1_sm_4_t_2_cnt;
	extern int ipFlushMap_f_1_sm_4_t_3_cnt;
	extern int ipFlushMap_f_1_sm_4_t_4_cnt;
	extern int ipFlushMap_f_1_sm_4_t_5_cnt;
	extern int ipFlushMap_f_1_sm_4_t_6_cnt;
	extern int ipFlushMap_f_1_sm_4_t_7_cnt;
	extern int ipFlushMap_f_1_sm_4_t_8_cnt;
	extern int ipFlushMap_f_1_sm_4_t_9_cnt;

	/* Flusher 2 SM 0 */
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_9;

	extern int ipFlushMap_f_2_sm_0_t_0_cnt;
	extern int ipFlushMap_f_2_sm_0_t_1_cnt;
	extern int ipFlushMap_f_2_sm_0_t_2_cnt;
	extern int ipFlushMap_f_2_sm_0_t_3_cnt;
	extern int ipFlushMap_f_2_sm_0_t_4_cnt;
	extern int ipFlushMap_f_2_sm_0_t_5_cnt;
	extern int ipFlushMap_f_2_sm_0_t_6_cnt;
	extern int ipFlushMap_f_2_sm_0_t_7_cnt;
	extern int ipFlushMap_f_2_sm_0_t_8_cnt;
	extern int ipFlushMap_f_2_sm_0_t_9_cnt;

	/* Flusher 2 SM 1 */
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_9;

	extern int ipFlushMap_f_2_sm_1_t_0_cnt;
	extern int ipFlushMap_f_2_sm_1_t_1_cnt;
	extern int ipFlushMap_f_2_sm_1_t_2_cnt;
	extern int ipFlushMap_f_2_sm_1_t_3_cnt;
	extern int ipFlushMap_f_2_sm_1_t_4_cnt;
	extern int ipFlushMap_f_2_sm_1_t_5_cnt;
	extern int ipFlushMap_f_2_sm_1_t_6_cnt;
	extern int ipFlushMap_f_2_sm_1_t_7_cnt;
	extern int ipFlushMap_f_2_sm_1_t_8_cnt;
	extern int ipFlushMap_f_2_sm_1_t_9_cnt;

	/* Flusher 2 SM 2 */
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_9;

	extern int ipFlushMap_f_2_sm_2_t_0_cnt;
	extern int ipFlushMap_f_2_sm_2_t_1_cnt;
	extern int ipFlushMap_f_2_sm_2_t_2_cnt;
	extern int ipFlushMap_f_2_sm_2_t_3_cnt;
	extern int ipFlushMap_f_2_sm_2_t_4_cnt;
	extern int ipFlushMap_f_2_sm_2_t_5_cnt;
	extern int ipFlushMap_f_2_sm_2_t_6_cnt;
	extern int ipFlushMap_f_2_sm_2_t_7_cnt;
	extern int ipFlushMap_f_2_sm_2_t_8_cnt;
	extern int ipFlushMap_f_2_sm_2_t_9_cnt;

	/* Flusher 2 SM 3 */
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_9;

	extern int ipFlushMap_f_2_sm_3_t_0_cnt;
	extern int ipFlushMap_f_2_sm_3_t_1_cnt;
	extern int ipFlushMap_f_2_sm_3_t_2_cnt;
	extern int ipFlushMap_f_2_sm_3_t_3_cnt;
	extern int ipFlushMap_f_2_sm_3_t_4_cnt;
	extern int ipFlushMap_f_2_sm_3_t_5_cnt;
	extern int ipFlushMap_f_2_sm_3_t_6_cnt;
	extern int ipFlushMap_f_2_sm_3_t_7_cnt;
	extern int ipFlushMap_f_2_sm_3_t_8_cnt;
	extern int ipFlushMap_f_2_sm_3_t_9_cnt;

	/* Flusher 2 SM 4 */
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_9;

	extern int ipFlushMap_f_2_sm_4_t_0_cnt;
	extern int ipFlushMap_f_2_sm_4_t_1_cnt;
	extern int ipFlushMap_f_2_sm_4_t_2_cnt;
	extern int ipFlushMap_f_2_sm_4_t_3_cnt;
	extern int ipFlushMap_f_2_sm_4_t_4_cnt;
	extern int ipFlushMap_f_2_sm_4_t_5_cnt;
	extern int ipFlushMap_f_2_sm_4_t_6_cnt;
	extern int ipFlushMap_f_2_sm_4_t_7_cnt;
	extern int ipFlushMap_f_2_sm_4_t_8_cnt;
	extern int ipFlushMap_f_2_sm_4_t_9_cnt;

	/* Flusher 3 SM 0 */
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_9;

	extern int ipFlushMap_f_3_sm_0_t_0_cnt;
	extern int ipFlushMap_f_3_sm_0_t_1_cnt;
	extern int ipFlushMap_f_3_sm_0_t_2_cnt;
	extern int ipFlushMap_f_3_sm_0_t_3_cnt;
	extern int ipFlushMap_f_3_sm_0_t_4_cnt;
	extern int ipFlushMap_f_3_sm_0_t_5_cnt;
	extern int ipFlushMap_f_3_sm_0_t_6_cnt;
	extern int ipFlushMap_f_3_sm_0_t_7_cnt;
	extern int ipFlushMap_f_3_sm_0_t_8_cnt;
	extern int ipFlushMap_f_3_sm_0_t_9_cnt;

	/* Flusher 3 SM 1 */
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_9;

	extern int ipFlushMap_f_3_sm_1_t_0_cnt;
	extern int ipFlushMap_f_3_sm_1_t_1_cnt;
	extern int ipFlushMap_f_3_sm_1_t_2_cnt;
	extern int ipFlushMap_f_3_sm_1_t_3_cnt;
	extern int ipFlushMap_f_3_sm_1_t_4_cnt;
	extern int ipFlushMap_f_3_sm_1_t_5_cnt;
	extern int ipFlushMap_f_3_sm_1_t_6_cnt;
	extern int ipFlushMap_f_3_sm_1_t_7_cnt;
	extern int ipFlushMap_f_3_sm_1_t_8_cnt;
	extern int ipFlushMap_f_3_sm_1_t_9_cnt;

	/* Flusher 3 SM 2 */
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_9;

	extern int ipFlushMap_f_3_sm_2_t_0_cnt;
	extern int ipFlushMap_f_3_sm_2_t_1_cnt;
	extern int ipFlushMap_f_3_sm_2_t_2_cnt;
	extern int ipFlushMap_f_3_sm_2_t_3_cnt;
	extern int ipFlushMap_f_3_sm_2_t_4_cnt;
	extern int ipFlushMap_f_3_sm_2_t_5_cnt;
	extern int ipFlushMap_f_3_sm_2_t_6_cnt;
	extern int ipFlushMap_f_3_sm_2_t_7_cnt;
	extern int ipFlushMap_f_3_sm_2_t_8_cnt;
	extern int ipFlushMap_f_3_sm_2_t_9_cnt;

	/* Flusher 3 SM 3 */
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_9;

	extern int ipFlushMap_f_3_sm_3_t_0_cnt;
	extern int ipFlushMap_f_3_sm_3_t_1_cnt;
	extern int ipFlushMap_f_3_sm_3_t_2_cnt;
	extern int ipFlushMap_f_3_sm_3_t_3_cnt;
	extern int ipFlushMap_f_3_sm_3_t_4_cnt;
	extern int ipFlushMap_f_3_sm_3_t_5_cnt;
	extern int ipFlushMap_f_3_sm_3_t_6_cnt;
	extern int ipFlushMap_f_3_sm_3_t_7_cnt;
	extern int ipFlushMap_f_3_sm_3_t_8_cnt;
	extern int ipFlushMap_f_3_sm_3_t_9_cnt;

	/* Flusher 3 SM 4 */
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_0;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_1;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_2;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_3;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_4;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_5;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_6;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_7;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_8;
	extern std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_9;

	extern int ipFlushMap_f_3_sm_4_t_0_cnt;
	extern int ipFlushMap_f_3_sm_4_t_1_cnt;
	extern int ipFlushMap_f_3_sm_4_t_2_cnt;
	extern int ipFlushMap_f_3_sm_4_t_3_cnt;
	extern int ipFlushMap_f_3_sm_4_t_4_cnt;
	extern int ipFlushMap_f_3_sm_4_t_5_cnt;
	extern int ipFlushMap_f_3_sm_4_t_6_cnt;
	extern int ipFlushMap_f_3_sm_4_t_7_cnt;
	extern int ipFlushMap_f_3_sm_4_t_8_cnt;
	extern int ipFlushMap_f_3_sm_4_t_9_cnt;


	extern std::map<int, xdrStore> ip_xdr_flush_f_0_t_0;
	extern std::map<int, xdrStore> ip_xdr_flush_f_0_t_1;
	extern std::map<int, xdrStore> ip_xdr_flush_f_0_t_2;
	extern std::map<int, xdrStore> ip_xdr_flush_f_0_t_3;
	extern std::map<int, xdrStore> ip_xdr_flush_f_0_t_4;
	extern std::map<int, xdrStore> ip_xdr_flush_f_0_t_5;
	extern std::map<int, xdrStore> ip_xdr_flush_f_0_t_6;
	extern std::map<int, xdrStore> ip_xdr_flush_f_0_t_7;
	extern std::map<int, xdrStore> ip_xdr_flush_f_0_t_8;
	extern std::map<int, xdrStore> ip_xdr_flush_f_0_t_9;

	extern int ip_xdr_flush_f_0_t_0_cnt;
	extern int ip_xdr_flush_f_0_t_1_cnt;
	extern int ip_xdr_flush_f_0_t_2_cnt;
	extern int ip_xdr_flush_f_0_t_3_cnt;
	extern int ip_xdr_flush_f_0_t_4_cnt;
	extern int ip_xdr_flush_f_0_t_5_cnt;
	extern int ip_xdr_flush_f_0_t_6_cnt;
	extern int ip_xdr_flush_f_0_t_7_cnt;
	extern int ip_xdr_flush_f_0_t_8_cnt;
	extern int ip_xdr_flush_f_0_t_9_cnt;

	extern std::map<int, xdrStore> ip_xdr_flush_f_1_t_0;
	extern std::map<int, xdrStore> ip_xdr_flush_f_1_t_1;
	extern std::map<int, xdrStore> ip_xdr_flush_f_1_t_2;
	extern std::map<int, xdrStore> ip_xdr_flush_f_1_t_3;
	extern std::map<int, xdrStore> ip_xdr_flush_f_1_t_4;
	extern std::map<int, xdrStore> ip_xdr_flush_f_1_t_5;
	extern std::map<int, xdrStore> ip_xdr_flush_f_1_t_6;
	extern std::map<int, xdrStore> ip_xdr_flush_f_1_t_7;
	extern std::map<int, xdrStore> ip_xdr_flush_f_1_t_8;
	extern std::map<int, xdrStore> ip_xdr_flush_f_1_t_9;

	extern int ip_xdr_flush_f_1_t_0_cnt;
	extern int ip_xdr_flush_f_1_t_1_cnt;
	extern int ip_xdr_flush_f_1_t_2_cnt;
	extern int ip_xdr_flush_f_1_t_3_cnt;
	extern int ip_xdr_flush_f_1_t_4_cnt;
	extern int ip_xdr_flush_f_1_t_5_cnt;
	extern int ip_xdr_flush_f_1_t_6_cnt;
	extern int ip_xdr_flush_f_1_t_7_cnt;
	extern int ip_xdr_flush_f_1_t_8_cnt;
	extern int ip_xdr_flush_f_1_t_9_cnt;

	extern std::map<int, xdrStore> ip_xdr_flush_f_2_t_0;
	extern std::map<int, xdrStore> ip_xdr_flush_f_2_t_1;
	extern std::map<int, xdrStore> ip_xdr_flush_f_2_t_2;
	extern std::map<int, xdrStore> ip_xdr_flush_f_2_t_3;
	extern std::map<int, xdrStore> ip_xdr_flush_f_2_t_4;
	extern std::map<int, xdrStore> ip_xdr_flush_f_2_t_5;
	extern std::map<int, xdrStore> ip_xdr_flush_f_2_t_6;
	extern std::map<int, xdrStore> ip_xdr_flush_f_2_t_7;
	extern std::map<int, xdrStore> ip_xdr_flush_f_2_t_8;
	extern std::map<int, xdrStore> ip_xdr_flush_f_2_t_9;

	extern int ip_xdr_flush_f_2_t_0_cnt;
	extern int ip_xdr_flush_f_2_t_1_cnt;
	extern int ip_xdr_flush_f_2_t_2_cnt;
	extern int ip_xdr_flush_f_2_t_3_cnt;
	extern int ip_xdr_flush_f_2_t_4_cnt;
	extern int ip_xdr_flush_f_2_t_5_cnt;
	extern int ip_xdr_flush_f_2_t_6_cnt;
	extern int ip_xdr_flush_f_2_t_7_cnt;
	extern int ip_xdr_flush_f_2_t_8_cnt;
	extern int ip_xdr_flush_f_2_t_9_cnt;

	extern std::map<int, xdrStore> ip_xdr_flush_f_3_t_0;
	extern std::map<int, xdrStore> ip_xdr_flush_f_3_t_1;
	extern std::map<int, xdrStore> ip_xdr_flush_f_3_t_2;
	extern std::map<int, xdrStore> ip_xdr_flush_f_3_t_3;
	extern std::map<int, xdrStore> ip_xdr_flush_f_3_t_4;
	extern std::map<int, xdrStore> ip_xdr_flush_f_3_t_5;
	extern std::map<int, xdrStore> ip_xdr_flush_f_3_t_6;
	extern std::map<int, xdrStore> ip_xdr_flush_f_3_t_7;
	extern std::map<int, xdrStore> ip_xdr_flush_f_3_t_8;
	extern std::map<int, xdrStore> ip_xdr_flush_f_3_t_9;

	extern int ip_xdr_flush_f_3_t_0_cnt;
	extern int ip_xdr_flush_f_3_t_1_cnt;
	extern int ip_xdr_flush_f_3_t_2_cnt;
	extern int ip_xdr_flush_f_3_t_3_cnt;
	extern int ip_xdr_flush_f_3_t_4_cnt;
	extern int ip_xdr_flush_f_3_t_5_cnt;
	extern int ip_xdr_flush_f_3_t_6_cnt;
	extern int ip_xdr_flush_f_3_t_7_cnt;
	extern int ip_xdr_flush_f_3_t_8_cnt;
	extern int ip_xdr_flush_f_3_t_9_cnt;


	extern std::map<int, xdrStore> ip_zmq_flush_f_0_t_0;
	extern std::map<int, xdrStore> ip_zmq_flush_f_0_t_1;
	extern std::map<int, xdrStore> ip_zmq_flush_f_0_t_2;
	extern std::map<int, xdrStore> ip_zmq_flush_f_0_t_3;
	extern std::map<int, xdrStore> ip_zmq_flush_f_0_t_4;
	extern std::map<int, xdrStore> ip_zmq_flush_f_0_t_5;
	extern std::map<int, xdrStore> ip_zmq_flush_f_0_t_6;
	extern std::map<int, xdrStore> ip_zmq_flush_f_0_t_7;
	extern std::map<int, xdrStore> ip_zmq_flush_f_0_t_8;
	extern std::map<int, xdrStore> ip_zmq_flush_f_0_t_9;

	extern int ip_zmq_flush_f_0_t_0_cnt;
	extern int ip_zmq_flush_f_0_t_1_cnt;
	extern int ip_zmq_flush_f_0_t_2_cnt;
	extern int ip_zmq_flush_f_0_t_3_cnt;
	extern int ip_zmq_flush_f_0_t_4_cnt;
	extern int ip_zmq_flush_f_0_t_5_cnt;
	extern int ip_zmq_flush_f_0_t_6_cnt;
	extern int ip_zmq_flush_f_0_t_7_cnt;
	extern int ip_zmq_flush_f_0_t_8_cnt;
	extern int ip_zmq_flush_f_0_t_9_cnt;

	extern std::map<int, xdrStore> ip_zmq_flush_f_1_t_0;
	extern std::map<int, xdrStore> ip_zmq_flush_f_1_t_1;
	extern std::map<int, xdrStore> ip_zmq_flush_f_1_t_2;
	extern std::map<int, xdrStore> ip_zmq_flush_f_1_t_3;
	extern std::map<int, xdrStore> ip_zmq_flush_f_1_t_4;
	extern std::map<int, xdrStore> ip_zmq_flush_f_1_t_5;
	extern std::map<int, xdrStore> ip_zmq_flush_f_1_t_6;
	extern std::map<int, xdrStore> ip_zmq_flush_f_1_t_7;
	extern std::map<int, xdrStore> ip_zmq_flush_f_1_t_8;
	extern std::map<int, xdrStore> ip_zmq_flush_f_1_t_9;

	extern int ip_zmq_flush_f_1_t_0_cnt;
	extern int ip_zmq_flush_f_1_t_1_cnt;
	extern int ip_zmq_flush_f_1_t_2_cnt;
	extern int ip_zmq_flush_f_1_t_3_cnt;
	extern int ip_zmq_flush_f_1_t_4_cnt;
	extern int ip_zmq_flush_f_1_t_5_cnt;
	extern int ip_zmq_flush_f_1_t_6_cnt;
	extern int ip_zmq_flush_f_1_t_7_cnt;
	extern int ip_zmq_flush_f_1_t_8_cnt;
	extern int ip_zmq_flush_f_1_t_9_cnt;

	extern std::map<int, xdrStore> ip_zmq_flush_f_2_t_0;
	extern std::map<int, xdrStore> ip_zmq_flush_f_2_t_1;
	extern std::map<int, xdrStore> ip_zmq_flush_f_2_t_2;
	extern std::map<int, xdrStore> ip_zmq_flush_f_2_t_3;
	extern std::map<int, xdrStore> ip_zmq_flush_f_2_t_4;
	extern std::map<int, xdrStore> ip_zmq_flush_f_2_t_5;
	extern std::map<int, xdrStore> ip_zmq_flush_f_2_t_6;
	extern std::map<int, xdrStore> ip_zmq_flush_f_2_t_7;
	extern std::map<int, xdrStore> ip_zmq_flush_f_2_t_8;
	extern std::map<int, xdrStore> ip_zmq_flush_f_2_t_9;

	extern int ip_zmq_flush_f_2_t_0_cnt;
	extern int ip_zmq_flush_f_2_t_1_cnt;
	extern int ip_zmq_flush_f_2_t_2_cnt;
	extern int ip_zmq_flush_f_2_t_3_cnt;
	extern int ip_zmq_flush_f_2_t_4_cnt;
	extern int ip_zmq_flush_f_2_t_5_cnt;
	extern int ip_zmq_flush_f_2_t_6_cnt;
	extern int ip_zmq_flush_f_2_t_7_cnt;
	extern int ip_zmq_flush_f_2_t_8_cnt;
	extern int ip_zmq_flush_f_2_t_9_cnt;

	extern std::map<int, xdrStore> ip_zmq_flush_f_3_t_0;
	extern std::map<int, xdrStore> ip_zmq_flush_f_3_t_1;
	extern std::map<int, xdrStore> ip_zmq_flush_f_3_t_2;
	extern std::map<int, xdrStore> ip_zmq_flush_f_3_t_3;
	extern std::map<int, xdrStore> ip_zmq_flush_f_3_t_4;
	extern std::map<int, xdrStore> ip_zmq_flush_f_3_t_5;
	extern std::map<int, xdrStore> ip_zmq_flush_f_3_t_6;
	extern std::map<int, xdrStore> ip_zmq_flush_f_3_t_7;
	extern std::map<int, xdrStore> ip_zmq_flush_f_3_t_8;
	extern std::map<int, xdrStore> ip_zmq_flush_f_3_t_9;

	extern int ip_zmq_flush_f_3_t_0_cnt;
	extern int ip_zmq_flush_f_3_t_1_cnt;
	extern int ip_zmq_flush_f_3_t_2_cnt;
	extern int ip_zmq_flush_f_3_t_3_cnt;
	extern int ip_zmq_flush_f_3_t_4_cnt;
	extern int ip_zmq_flush_f_3_t_5_cnt;
	extern int ip_zmq_flush_f_3_t_6_cnt;
	extern int ip_zmq_flush_f_3_t_7_cnt;
	extern int ip_zmq_flush_f_3_t_8_cnt;
	extern int ip_zmq_flush_f_3_t_9_cnt;

	/* -- DNS - Flusher 0 SM 0 */
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_9;

	extern int dnsFlushMap_f_0_sm_0_t_0_cnt;
	extern int dnsFlushMap_f_0_sm_0_t_1_cnt;
	extern int dnsFlushMap_f_0_sm_0_t_2_cnt;
	extern int dnsFlushMap_f_0_sm_0_t_3_cnt;
	extern int dnsFlushMap_f_0_sm_0_t_4_cnt;
	extern int dnsFlushMap_f_0_sm_0_t_5_cnt;
	extern int dnsFlushMap_f_0_sm_0_t_6_cnt;
	extern int dnsFlushMap_f_0_sm_0_t_7_cnt;
	extern int dnsFlushMap_f_0_sm_0_t_8_cnt;
	extern int dnsFlushMap_f_0_sm_0_t_9_cnt;

	/* Flusher 0 SM 1 */
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_9;

	extern int dnsFlushMap_f_0_sm_1_t_0_cnt;
	extern int dnsFlushMap_f_0_sm_1_t_1_cnt;
	extern int dnsFlushMap_f_0_sm_1_t_2_cnt;
	extern int dnsFlushMap_f_0_sm_1_t_3_cnt;
	extern int dnsFlushMap_f_0_sm_1_t_4_cnt;
	extern int dnsFlushMap_f_0_sm_1_t_5_cnt;
	extern int dnsFlushMap_f_0_sm_1_t_6_cnt;
	extern int dnsFlushMap_f_0_sm_1_t_7_cnt;
	extern int dnsFlushMap_f_0_sm_1_t_8_cnt;
	extern int dnsFlushMap_f_0_sm_1_t_9_cnt;

	/* Flusher 0 SM 2 */
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_9;

	extern int dnsFlushMap_f_0_sm_2_t_0_cnt;
	extern int dnsFlushMap_f_0_sm_2_t_1_cnt;
	extern int dnsFlushMap_f_0_sm_2_t_2_cnt;
	extern int dnsFlushMap_f_0_sm_2_t_3_cnt;
	extern int dnsFlushMap_f_0_sm_2_t_4_cnt;
	extern int dnsFlushMap_f_0_sm_2_t_5_cnt;
	extern int dnsFlushMap_f_0_sm_2_t_6_cnt;
	extern int dnsFlushMap_f_0_sm_2_t_7_cnt;
	extern int dnsFlushMap_f_0_sm_2_t_8_cnt;
	extern int dnsFlushMap_f_0_sm_2_t_9_cnt;

	/* Flusher 0 SM 3 */
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_9;

	extern int dnsFlushMap_f_0_sm_3_t_0_cnt;
	extern int dnsFlushMap_f_0_sm_3_t_1_cnt;
	extern int dnsFlushMap_f_0_sm_3_t_2_cnt;
	extern int dnsFlushMap_f_0_sm_3_t_3_cnt;
	extern int dnsFlushMap_f_0_sm_3_t_4_cnt;
	extern int dnsFlushMap_f_0_sm_3_t_5_cnt;
	extern int dnsFlushMap_f_0_sm_3_t_6_cnt;
	extern int dnsFlushMap_f_0_sm_3_t_7_cnt;
	extern int dnsFlushMap_f_0_sm_3_t_8_cnt;
	extern int dnsFlushMap_f_0_sm_3_t_9_cnt;

	/* Flusher 0 SM 4 */
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_9;

	extern int dnsFlushMap_f_0_sm_4_t_0_cnt;
	extern int dnsFlushMap_f_0_sm_4_t_1_cnt;
	extern int dnsFlushMap_f_0_sm_4_t_2_cnt;
	extern int dnsFlushMap_f_0_sm_4_t_3_cnt;
	extern int dnsFlushMap_f_0_sm_4_t_4_cnt;
	extern int dnsFlushMap_f_0_sm_4_t_5_cnt;
	extern int dnsFlushMap_f_0_sm_4_t_6_cnt;
	extern int dnsFlushMap_f_0_sm_4_t_7_cnt;
	extern int dnsFlushMap_f_0_sm_4_t_8_cnt;
	extern int dnsFlushMap_f_0_sm_4_t_9_cnt;

	/* -- DNS - Flusher 1 SM 0 */
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_9;

	extern int dnsFlushMap_f_1_sm_0_t_0_cnt;
	extern int dnsFlushMap_f_1_sm_0_t_1_cnt;
	extern int dnsFlushMap_f_1_sm_0_t_2_cnt;
	extern int dnsFlushMap_f_1_sm_0_t_3_cnt;
	extern int dnsFlushMap_f_1_sm_0_t_4_cnt;
	extern int dnsFlushMap_f_1_sm_0_t_5_cnt;
	extern int dnsFlushMap_f_1_sm_0_t_6_cnt;
	extern int dnsFlushMap_f_1_sm_0_t_7_cnt;
	extern int dnsFlushMap_f_1_sm_0_t_8_cnt;
	extern int dnsFlushMap_f_1_sm_0_t_9_cnt;

	/* Flusher 1 SM 1 */
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_9;

	extern int dnsFlushMap_f_1_sm_1_t_0_cnt;
	extern int dnsFlushMap_f_1_sm_1_t_1_cnt;
	extern int dnsFlushMap_f_1_sm_1_t_2_cnt;
	extern int dnsFlushMap_f_1_sm_1_t_3_cnt;
	extern int dnsFlushMap_f_1_sm_1_t_4_cnt;
	extern int dnsFlushMap_f_1_sm_1_t_5_cnt;
	extern int dnsFlushMap_f_1_sm_1_t_6_cnt;
	extern int dnsFlushMap_f_1_sm_1_t_7_cnt;
	extern int dnsFlushMap_f_1_sm_1_t_8_cnt;
	extern int dnsFlushMap_f_1_sm_1_t_9_cnt;

	/* Flusher 1 SM 2 */
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_9;

	extern int dnsFlushMap_f_1_sm_2_t_0_cnt;
	extern int dnsFlushMap_f_1_sm_2_t_1_cnt;
	extern int dnsFlushMap_f_1_sm_2_t_2_cnt;
	extern int dnsFlushMap_f_1_sm_2_t_3_cnt;
	extern int dnsFlushMap_f_1_sm_2_t_4_cnt;
	extern int dnsFlushMap_f_1_sm_2_t_5_cnt;
	extern int dnsFlushMap_f_1_sm_2_t_6_cnt;
	extern int dnsFlushMap_f_1_sm_2_t_7_cnt;
	extern int dnsFlushMap_f_1_sm_2_t_8_cnt;
	extern int dnsFlushMap_f_1_sm_2_t_9_cnt;

	/* Flusher 1 SM 3 */
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_9;

	extern int dnsFlushMap_f_1_sm_3_t_0_cnt;
	extern int dnsFlushMap_f_1_sm_3_t_1_cnt;
	extern int dnsFlushMap_f_1_sm_3_t_2_cnt;
	extern int dnsFlushMap_f_1_sm_3_t_3_cnt;
	extern int dnsFlushMap_f_1_sm_3_t_4_cnt;
	extern int dnsFlushMap_f_1_sm_3_t_5_cnt;
	extern int dnsFlushMap_f_1_sm_3_t_6_cnt;
	extern int dnsFlushMap_f_1_sm_3_t_7_cnt;
	extern int dnsFlushMap_f_1_sm_3_t_8_cnt;
	extern int dnsFlushMap_f_1_sm_3_t_9_cnt;

	/* Flusher 1 SM 4 */
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_9;

	extern int dnsFlushMap_f_1_sm_4_t_0_cnt;
	extern int dnsFlushMap_f_1_sm_4_t_1_cnt;
	extern int dnsFlushMap_f_1_sm_4_t_2_cnt;
	extern int dnsFlushMap_f_1_sm_4_t_3_cnt;
	extern int dnsFlushMap_f_1_sm_4_t_4_cnt;
	extern int dnsFlushMap_f_1_sm_4_t_5_cnt;
	extern int dnsFlushMap_f_1_sm_4_t_6_cnt;
	extern int dnsFlushMap_f_1_sm_4_t_7_cnt;
	extern int dnsFlushMap_f_1_sm_4_t_8_cnt;
	extern int dnsFlushMap_f_1_sm_4_t_9_cnt;

	/* -- DNS - Flusher 2 SM 0 */
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_9;

	extern int dnsFlushMap_f_2_sm_0_t_0_cnt;
	extern int dnsFlushMap_f_2_sm_0_t_1_cnt;
	extern int dnsFlushMap_f_2_sm_0_t_2_cnt;
	extern int dnsFlushMap_f_2_sm_0_t_3_cnt;
	extern int dnsFlushMap_f_2_sm_0_t_4_cnt;
	extern int dnsFlushMap_f_2_sm_0_t_5_cnt;
	extern int dnsFlushMap_f_2_sm_0_t_6_cnt;
	extern int dnsFlushMap_f_2_sm_0_t_7_cnt;
	extern int dnsFlushMap_f_2_sm_0_t_8_cnt;
	extern int dnsFlushMap_f_2_sm_0_t_9_cnt;

	/* Flusher 2 SM 1 */
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_9;

	extern int dnsFlushMap_f_2_sm_1_t_0_cnt;
	extern int dnsFlushMap_f_2_sm_1_t_1_cnt;
	extern int dnsFlushMap_f_2_sm_1_t_2_cnt;
	extern int dnsFlushMap_f_2_sm_1_t_3_cnt;
	extern int dnsFlushMap_f_2_sm_1_t_4_cnt;
	extern int dnsFlushMap_f_2_sm_1_t_5_cnt;
	extern int dnsFlushMap_f_2_sm_1_t_6_cnt;
	extern int dnsFlushMap_f_2_sm_1_t_7_cnt;
	extern int dnsFlushMap_f_2_sm_1_t_8_cnt;
	extern int dnsFlushMap_f_2_sm_1_t_9_cnt;

	/* Flusher 2 SM 2 */
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_9;

	extern int dnsFlushMap_f_2_sm_2_t_0_cnt;
	extern int dnsFlushMap_f_2_sm_2_t_1_cnt;
	extern int dnsFlushMap_f_2_sm_2_t_2_cnt;
	extern int dnsFlushMap_f_2_sm_2_t_3_cnt;
	extern int dnsFlushMap_f_2_sm_2_t_4_cnt;
	extern int dnsFlushMap_f_2_sm_2_t_5_cnt;
	extern int dnsFlushMap_f_2_sm_2_t_6_cnt;
	extern int dnsFlushMap_f_2_sm_2_t_7_cnt;
	extern int dnsFlushMap_f_2_sm_2_t_8_cnt;
	extern int dnsFlushMap_f_2_sm_2_t_9_cnt;

	/* Flusher 2 SM 3 */
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_9;

	extern int dnsFlushMap_f_2_sm_3_t_0_cnt;
	extern int dnsFlushMap_f_2_sm_3_t_1_cnt;
	extern int dnsFlushMap_f_2_sm_3_t_2_cnt;
	extern int dnsFlushMap_f_2_sm_3_t_3_cnt;
	extern int dnsFlushMap_f_2_sm_3_t_4_cnt;
	extern int dnsFlushMap_f_2_sm_3_t_5_cnt;
	extern int dnsFlushMap_f_2_sm_3_t_6_cnt;
	extern int dnsFlushMap_f_2_sm_3_t_7_cnt;
	extern int dnsFlushMap_f_2_sm_3_t_8_cnt;
	extern int dnsFlushMap_f_2_sm_3_t_9_cnt;

	/* Flusher 2 SM 4 */
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_9;

	extern int dnsFlushMap_f_2_sm_4_t_0_cnt;
	extern int dnsFlushMap_f_2_sm_4_t_1_cnt;
	extern int dnsFlushMap_f_2_sm_4_t_2_cnt;
	extern int dnsFlushMap_f_2_sm_4_t_3_cnt;
	extern int dnsFlushMap_f_2_sm_4_t_4_cnt;
	extern int dnsFlushMap_f_2_sm_4_t_5_cnt;
	extern int dnsFlushMap_f_2_sm_4_t_6_cnt;
	extern int dnsFlushMap_f_2_sm_4_t_7_cnt;
	extern int dnsFlushMap_f_2_sm_4_t_8_cnt;
	extern int dnsFlushMap_f_2_sm_4_t_9_cnt;

	/* -- DNS - Flusher 3 SM 0 */
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_9;

	extern int dnsFlushMap_f_3_sm_0_t_0_cnt;
	extern int dnsFlushMap_f_3_sm_0_t_1_cnt;
	extern int dnsFlushMap_f_3_sm_0_t_2_cnt;
	extern int dnsFlushMap_f_3_sm_0_t_3_cnt;
	extern int dnsFlushMap_f_3_sm_0_t_4_cnt;
	extern int dnsFlushMap_f_3_sm_0_t_5_cnt;
	extern int dnsFlushMap_f_3_sm_0_t_6_cnt;
	extern int dnsFlushMap_f_3_sm_0_t_7_cnt;
	extern int dnsFlushMap_f_3_sm_0_t_8_cnt;
	extern int dnsFlushMap_f_3_sm_0_t_9_cnt;

	/* Flusher 3 SM 1 */
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_9;

	extern int dnsFlushMap_f_3_sm_1_t_0_cnt;
	extern int dnsFlushMap_f_3_sm_1_t_1_cnt;
	extern int dnsFlushMap_f_3_sm_1_t_2_cnt;
	extern int dnsFlushMap_f_3_sm_1_t_3_cnt;
	extern int dnsFlushMap_f_3_sm_1_t_4_cnt;
	extern int dnsFlushMap_f_3_sm_1_t_5_cnt;
	extern int dnsFlushMap_f_3_sm_1_t_6_cnt;
	extern int dnsFlushMap_f_3_sm_1_t_7_cnt;
	extern int dnsFlushMap_f_3_sm_1_t_8_cnt;
	extern int dnsFlushMap_f_3_sm_1_t_9_cnt;

	/* Flusher 3 SM 2 */
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_9;

	extern int dnsFlushMap_f_3_sm_2_t_0_cnt;
	extern int dnsFlushMap_f_3_sm_2_t_1_cnt;
	extern int dnsFlushMap_f_3_sm_2_t_2_cnt;
	extern int dnsFlushMap_f_3_sm_2_t_3_cnt;
	extern int dnsFlushMap_f_3_sm_2_t_4_cnt;
	extern int dnsFlushMap_f_3_sm_2_t_5_cnt;
	extern int dnsFlushMap_f_3_sm_2_t_6_cnt;
	extern int dnsFlushMap_f_3_sm_2_t_7_cnt;
	extern int dnsFlushMap_f_3_sm_2_t_8_cnt;
	extern int dnsFlushMap_f_3_sm_2_t_9_cnt;

	/* Flusher 3 SM 3 */
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_9;

	extern int dnsFlushMap_f_3_sm_3_t_0_cnt;
	extern int dnsFlushMap_f_3_sm_3_t_1_cnt;
	extern int dnsFlushMap_f_3_sm_3_t_2_cnt;
	extern int dnsFlushMap_f_3_sm_3_t_3_cnt;
	extern int dnsFlushMap_f_3_sm_3_t_4_cnt;
	extern int dnsFlushMap_f_3_sm_3_t_5_cnt;
	extern int dnsFlushMap_f_3_sm_3_t_6_cnt;
	extern int dnsFlushMap_f_3_sm_3_t_7_cnt;
	extern int dnsFlushMap_f_3_sm_3_t_8_cnt;
	extern int dnsFlushMap_f_3_sm_3_t_9_cnt;

	/* Flusher 3 SM 4 */
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_0;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_1;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_2;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_3;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_4;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_5;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_6;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_7;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_8;
	extern std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_9;

	extern int dnsFlushMap_f_3_sm_4_t_0_cnt;
	extern int dnsFlushMap_f_3_sm_4_t_1_cnt;
	extern int dnsFlushMap_f_3_sm_4_t_2_cnt;
	extern int dnsFlushMap_f_3_sm_4_t_3_cnt;
	extern int dnsFlushMap_f_3_sm_4_t_4_cnt;
	extern int dnsFlushMap_f_3_sm_4_t_5_cnt;
	extern int dnsFlushMap_f_3_sm_4_t_6_cnt;
	extern int dnsFlushMap_f_3_sm_4_t_7_cnt;
	extern int dnsFlushMap_f_3_sm_4_t_8_cnt;
	extern int dnsFlushMap_f_3_sm_4_t_9_cnt;

	extern std::map<int, xdrStore> dns_xdr_flush_f_0_t_0;
	extern std::map<int, xdrStore> dns_xdr_flush_f_0_t_1;
	extern std::map<int, xdrStore> dns_xdr_flush_f_0_t_2;
	extern std::map<int, xdrStore> dns_xdr_flush_f_0_t_3;
	extern std::map<int, xdrStore> dns_xdr_flush_f_0_t_4;
	extern std::map<int, xdrStore> dns_xdr_flush_f_0_t_5;
	extern std::map<int, xdrStore> dns_xdr_flush_f_0_t_6;
	extern std::map<int, xdrStore> dns_xdr_flush_f_0_t_7;
	extern std::map<int, xdrStore> dns_xdr_flush_f_0_t_8;
	extern std::map<int, xdrStore> dns_xdr_flush_f_0_t_9;

	extern int dns_xdr_flush_f_0_t_0_cnt;
	extern int dns_xdr_flush_f_0_t_1_cnt;
	extern int dns_xdr_flush_f_0_t_2_cnt;
	extern int dns_xdr_flush_f_0_t_3_cnt;
	extern int dns_xdr_flush_f_0_t_4_cnt;
	extern int dns_xdr_flush_f_0_t_5_cnt;
	extern int dns_xdr_flush_f_0_t_6_cnt;
	extern int dns_xdr_flush_f_0_t_7_cnt;
	extern int dns_xdr_flush_f_0_t_8_cnt;
	extern int dns_xdr_flush_f_0_t_9_cnt;

	extern std::map<int, xdrStore> dns_xdr_flush_f_1_t_0;
	extern std::map<int, xdrStore> dns_xdr_flush_f_1_t_1;
	extern std::map<int, xdrStore> dns_xdr_flush_f_1_t_2;
	extern std::map<int, xdrStore> dns_xdr_flush_f_1_t_3;
	extern std::map<int, xdrStore> dns_xdr_flush_f_1_t_4;
	extern std::map<int, xdrStore> dns_xdr_flush_f_1_t_5;
	extern std::map<int, xdrStore> dns_xdr_flush_f_1_t_6;
	extern std::map<int, xdrStore> dns_xdr_flush_f_1_t_7;
	extern std::map<int, xdrStore> dns_xdr_flush_f_1_t_8;
	extern std::map<int, xdrStore> dns_xdr_flush_f_1_t_9;

	extern int dns_xdr_flush_f_1_t_0_cnt;
	extern int dns_xdr_flush_f_1_t_1_cnt;
	extern int dns_xdr_flush_f_1_t_2_cnt;
	extern int dns_xdr_flush_f_1_t_3_cnt;
	extern int dns_xdr_flush_f_1_t_4_cnt;
	extern int dns_xdr_flush_f_1_t_5_cnt;
	extern int dns_xdr_flush_f_1_t_6_cnt;
	extern int dns_xdr_flush_f_1_t_7_cnt;
	extern int dns_xdr_flush_f_1_t_8_cnt;
	extern int dns_xdr_flush_f_1_t_9_cnt;

	extern std::map<int, xdrStore> dns_xdr_flush_f_2_t_0;
	extern std::map<int, xdrStore> dns_xdr_flush_f_2_t_1;
	extern std::map<int, xdrStore> dns_xdr_flush_f_2_t_2;
	extern std::map<int, xdrStore> dns_xdr_flush_f_2_t_3;
	extern std::map<int, xdrStore> dns_xdr_flush_f_2_t_4;
	extern std::map<int, xdrStore> dns_xdr_flush_f_2_t_5;
	extern std::map<int, xdrStore> dns_xdr_flush_f_2_t_6;
	extern std::map<int, xdrStore> dns_xdr_flush_f_2_t_7;
	extern std::map<int, xdrStore> dns_xdr_flush_f_2_t_8;
	extern std::map<int, xdrStore> dns_xdr_flush_f_2_t_9;

	extern int dns_xdr_flush_f_2_t_0_cnt;
	extern int dns_xdr_flush_f_2_t_1_cnt;
	extern int dns_xdr_flush_f_2_t_2_cnt;
	extern int dns_xdr_flush_f_2_t_3_cnt;
	extern int dns_xdr_flush_f_2_t_4_cnt;
	extern int dns_xdr_flush_f_2_t_5_cnt;
	extern int dns_xdr_flush_f_2_t_6_cnt;
	extern int dns_xdr_flush_f_2_t_7_cnt;
	extern int dns_xdr_flush_f_2_t_8_cnt;
	extern int dns_xdr_flush_f_2_t_9_cnt;

	extern std::map<int, xdrStore> dns_xdr_flush_f_3_t_0;
	extern std::map<int, xdrStore> dns_xdr_flush_f_3_t_1;
	extern std::map<int, xdrStore> dns_xdr_flush_f_3_t_2;
	extern std::map<int, xdrStore> dns_xdr_flush_f_3_t_3;
	extern std::map<int, xdrStore> dns_xdr_flush_f_3_t_4;
	extern std::map<int, xdrStore> dns_xdr_flush_f_3_t_5;
	extern std::map<int, xdrStore> dns_xdr_flush_f_3_t_6;
	extern std::map<int, xdrStore> dns_xdr_flush_f_3_t_7;
	extern std::map<int, xdrStore> dns_xdr_flush_f_3_t_8;
	extern std::map<int, xdrStore> dns_xdr_flush_f_3_t_9;

	extern int dns_xdr_flush_f_3_t_0_cnt;
	extern int dns_xdr_flush_f_3_t_1_cnt;
	extern int dns_xdr_flush_f_3_t_2_cnt;
	extern int dns_xdr_flush_f_3_t_3_cnt;
	extern int dns_xdr_flush_f_3_t_4_cnt;
	extern int dns_xdr_flush_f_3_t_5_cnt;
	extern int dns_xdr_flush_f_3_t_6_cnt;
	extern int dns_xdr_flush_f_3_t_7_cnt;
	extern int dns_xdr_flush_f_3_t_8_cnt;
	extern int dns_xdr_flush_f_3_t_9_cnt;

	extern std::map<int, xdrStore> dns_zmq_flush_f_0_t_0;
	extern std::map<int, xdrStore> dns_zmq_flush_f_0_t_1;
	extern std::map<int, xdrStore> dns_zmq_flush_f_0_t_2;
	extern std::map<int, xdrStore> dns_zmq_flush_f_0_t_3;
	extern std::map<int, xdrStore> dns_zmq_flush_f_0_t_4;
	extern std::map<int, xdrStore> dns_zmq_flush_f_0_t_5;
	extern std::map<int, xdrStore> dns_zmq_flush_f_0_t_6;
	extern std::map<int, xdrStore> dns_zmq_flush_f_0_t_7;
	extern std::map<int, xdrStore> dns_zmq_flush_f_0_t_8;
	extern std::map<int, xdrStore> dns_zmq_flush_f_0_t_9;

	extern int dns_zmq_flush_f_0_t_0_cnt;
	extern int dns_zmq_flush_f_0_t_1_cnt;
	extern int dns_zmq_flush_f_0_t_2_cnt;
	extern int dns_zmq_flush_f_0_t_3_cnt;
	extern int dns_zmq_flush_f_0_t_4_cnt;
	extern int dns_zmq_flush_f_0_t_5_cnt;
	extern int dns_zmq_flush_f_0_t_6_cnt;
	extern int dns_zmq_flush_f_0_t_7_cnt;
	extern int dns_zmq_flush_f_0_t_8_cnt;
	extern int dns_zmq_flush_f_0_t_9_cnt;

	extern std::map<int, xdrStore> dns_zmq_flush_f_1_t_0;
	extern std::map<int, xdrStore> dns_zmq_flush_f_1_t_1;
	extern std::map<int, xdrStore> dns_zmq_flush_f_1_t_2;
	extern std::map<int, xdrStore> dns_zmq_flush_f_1_t_3;
	extern std::map<int, xdrStore> dns_zmq_flush_f_1_t_4;
	extern std::map<int, xdrStore> dns_zmq_flush_f_1_t_5;
	extern std::map<int, xdrStore> dns_zmq_flush_f_1_t_6;
	extern std::map<int, xdrStore> dns_zmq_flush_f_1_t_7;
	extern std::map<int, xdrStore> dns_zmq_flush_f_1_t_8;
	extern std::map<int, xdrStore> dns_zmq_flush_f_1_t_9;

	extern int dns_zmq_flush_f_1_t_0_cnt;
	extern int dns_zmq_flush_f_1_t_1_cnt;
	extern int dns_zmq_flush_f_1_t_2_cnt;
	extern int dns_zmq_flush_f_1_t_3_cnt;
	extern int dns_zmq_flush_f_1_t_4_cnt;
	extern int dns_zmq_flush_f_1_t_5_cnt;
	extern int dns_zmq_flush_f_1_t_6_cnt;
	extern int dns_zmq_flush_f_1_t_7_cnt;
	extern int dns_zmq_flush_f_1_t_8_cnt;
	extern int dns_zmq_flush_f_1_t_9_cnt;

	extern std::map<int, xdrStore> dns_zmq_flush_f_2_t_0;
	extern std::map<int, xdrStore> dns_zmq_flush_f_2_t_1;
	extern std::map<int, xdrStore> dns_zmq_flush_f_2_t_2;
	extern std::map<int, xdrStore> dns_zmq_flush_f_2_t_3;
	extern std::map<int, xdrStore> dns_zmq_flush_f_2_t_4;
	extern std::map<int, xdrStore> dns_zmq_flush_f_2_t_5;
	extern std::map<int, xdrStore> dns_zmq_flush_f_2_t_6;
	extern std::map<int, xdrStore> dns_zmq_flush_f_2_t_7;
	extern std::map<int, xdrStore> dns_zmq_flush_f_2_t_8;
	extern std::map<int, xdrStore> dns_zmq_flush_f_2_t_9;

	extern int dns_zmq_flush_f_2_t_0_cnt;
	extern int dns_zmq_flush_f_2_t_1_cnt;
	extern int dns_zmq_flush_f_2_t_2_cnt;
	extern int dns_zmq_flush_f_2_t_3_cnt;
	extern int dns_zmq_flush_f_2_t_4_cnt;
	extern int dns_zmq_flush_f_2_t_5_cnt;
	extern int dns_zmq_flush_f_2_t_6_cnt;
	extern int dns_zmq_flush_f_2_t_7_cnt;
	extern int dns_zmq_flush_f_2_t_8_cnt;
	extern int dns_zmq_flush_f_2_t_9_cnt;

	extern std::map<int, xdrStore> dns_zmq_flush_f_3_t_0;
	extern std::map<int, xdrStore> dns_zmq_flush_f_3_t_1;
	extern std::map<int, xdrStore> dns_zmq_flush_f_3_t_2;
	extern std::map<int, xdrStore> dns_zmq_flush_f_3_t_3;
	extern std::map<int, xdrStore> dns_zmq_flush_f_3_t_4;
	extern std::map<int, xdrStore> dns_zmq_flush_f_3_t_5;
	extern std::map<int, xdrStore> dns_zmq_flush_f_3_t_6;
	extern std::map<int, xdrStore> dns_zmq_flush_f_3_t_7;
	extern std::map<int, xdrStore> dns_zmq_flush_f_3_t_8;
	extern std::map<int, xdrStore> dns_zmq_flush_f_3_t_9;

	extern int dns_zmq_flush_f_3_t_0_cnt;
	extern int dns_zmq_flush_f_3_t_1_cnt;
	extern int dns_zmq_flush_f_3_t_2_cnt;
	extern int dns_zmq_flush_f_3_t_3_cnt;
	extern int dns_zmq_flush_f_3_t_4_cnt;
	extern int dns_zmq_flush_f_3_t_5_cnt;
	extern int dns_zmq_flush_f_3_t_6_cnt;
	extern int dns_zmq_flush_f_3_t_7_cnt;
	extern int dns_zmq_flush_f_3_t_8_cnt;
	extern int dns_zmq_flush_f_3_t_9_cnt;
}

typedef enum{
	SYSTEM_CLEANUP_TCP_CONN_DATA		= 10,
	SYSTEM_CLEANUP_TCP_CONN_NODATA		= 11,
	SYSTEM_CLEANUP_TCP_NOCONN_DATA		= 12,
	SYSTEM_CLEANUP_TCP_NOCONN_NODATA	= 13,
	SYSTEM_CLEANUP_UDP_DATA				= 14,
	SYSTEM_CLEANUP_DNS_QUERY			= 15,
	SYSTEM_CLEANUP_LONG_SESSION			= 16,

	SESSION_TERM_TCP_CONN_DATA			= 20,
	SESSION_TERM_TCP_CONN_NODATA		= 21,
	SESSION_TERM_TCP_NOCONN_DATA		= 22,
	SESSION_TERM_TCP_NOCONN_NODATA		= 23,
	SESSION_TERM_TCP_OVERWRITE			= 24,
	SESSION_TERM_DNS_QUERY_SUCCESS		= 25,


	SYSTEM_PKTLIMIT_TCP_CONN_DATA		= 30,
	SYSTEM_PKTLIMIT_TCP_NOCONN_DATA		= 31,
	SYSTEM_PKTLIMIT_UDP_DATA			= 32,

	DUPLICATE_SYN						= 40,
	FIN_NO_SESSION						= 50,

}causeCode;

typedef enum{
	UD_SYN_TSVAL = 1,
	UD_SYSACK_TSVAL,
	UD_SYN_LATENCY,
	UD_TCP_DATA,
	UD_TCP_DISCONN,
	UD_UDP_DATA,
	CR_TCP_SESSION,
	CR_UDP_SESSION,
	UD_HTTP_DATA_REQ,
	UD_HTTP_DATA_RSP,
	UP_TCP_DATA_SLICE,
	TCP_UNKNOWN_PACKET_TYPE
}tcp_udp_commands;

typedef enum{
	SYN_RCV = 1,
	SYN_ACK_RCV,
	ACK_RCV,
	CONNECTED,
	DATA_RCV,
	FIN_RCV,
	UNKNOWN
}IPState;
#endif /* PLUGINS_TCP_INC_TCPUDPGLOBAL_H_ */
