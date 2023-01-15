/*
 * GXGlobal.h
 *
 *  Created on: Oct 13, 2016
 *      Author: Debashis
 */

#ifndef PLUGINS_GX_SRC_GXGLOBAL_H_
#define PLUGINS_GX_SRC_GXGLOBAL_H_

#include <map>
#include "SpectaTypedef.h"

using namespace std;

#define	REQUEST			1
#define	ANSWER			2

typedef struct _gxSession
{
	uint32_t 	commandCode;
	ULONG		appId;
	string		appName;
	string		interfaceName;
	string		sessionId;
	string		originHost;
	string		originRealm;
	string		destinationHost;
	string		destinationRealm;
	uint16_t 	ccRequestType;
	string		ccReqTypeDesc;
	uint16_t 	tCause;
	string		tCauseDesc;
	string		eventTrigger;
	uint16_t	bearerOperation;
	string		bearerOperationDesc;
	string		calledStationId;
	string		accessNetworkChargingAddress;
	string		framedIPAddress;
	string		GPPS_GSN_Address;
	uint32_t	ratType;
	string		ratTypeDesc;
	string		imei;
	string		imsi;
	string		msisdn;
	uint32_t 	resultCode;
	string		resultCodeDesc;

	ULONG		requestPacket;
	ULONG		answerPacket;

	ULONG 		StartTimeEpochMicroSec;
	ULONG 		EndTimeEpochMicroSec;
	string 		StartTime;
	string 		EndTime;
	string 		s_addr_mac;
	string 		d_addr_mac;
	string 		sourceAddr;
	string 		destAddr;
	uint32_t 	s_port;
	uint32_t 	d_port;
	uint32_t	upframeBytes;
	uint32_t	dnframeBytes;

	_gxSession()
	{ reset(); }

	void reset()
	{
		commandCode = 0;
		appId = 0;
		appName.clear();
		interfaceName.assign("NA");
		sessionId.clear();
		originHost.clear();
		originRealm.clear();
		destinationHost.clear();
		destinationRealm.clear();
		ccRequestType = 0;
		ccReqTypeDesc.clear();
		tCause = 0;
		tCauseDesc.clear();
		eventTrigger.clear();
		bearerOperation = 0;
		bearerOperationDesc.clear();
		calledStationId.clear();
		accessNetworkChargingAddress.clear();
		framedIPAddress.clear();
		GPPS_GSN_Address.clear();
		ratType = 0;
		ratTypeDesc.clear();
		imei.clear();
		imsi.clear();
		msisdn.clear();
		resultCode = 0;
		resultCodeDesc.clear();
		requestPacket = 0;
		answerPacket = 0;

		StartTimeEpochMicroSec = 0;
		EndTimeEpochMicroSec = 0;
		StartTime.clear();
		EndTime.clear();
		s_addr_mac.clear();
		d_addr_mac.clear();
		sourceAddr.clear();
		destAddr.clear();
		s_port = 0;
		d_port = 0;
		upframeBytes = 0;
		dnframeBytes = 0;
	}

	void set(const _gxSession *obj)
	{
		this->commandCode 					= obj->commandCode;
		this->appId 						= obj->appId;
		this->appName						= obj->appName;
		this->interfaceName					= obj->interfaceName;
		this->sessionId 					= obj->sessionId;
		this->originHost 					= obj->originHost;
		this->originRealm 					= obj->originRealm;
		this->destinationHost				= obj->destinationHost;
		this->destinationRealm 				= obj->destinationRealm;
		this->ccRequestType					= obj->ccRequestType;
		this->ccReqTypeDesc 				= obj->ccReqTypeDesc;
		this->tCause 						= obj->tCause;
		this->tCauseDesc 					= obj->tCauseDesc;
		this->eventTrigger 					= obj->eventTrigger;
		this->bearerOperation 				= obj->bearerOperation;
		this->bearerOperationDesc 			= obj->bearerOperationDesc;
		this->accessNetworkChargingAddress 	= obj->accessNetworkChargingAddress;
		this->framedIPAddress 				= obj->framedIPAddress;
		this->GPPS_GSN_Address 				= obj->GPPS_GSN_Address;
		this->ratType 						= obj->ratType;
		this->ratTypeDesc					= obj->ratTypeDesc;
		this->imei 							= obj->imei;
		this->imsi 							= obj->imsi;
		this->msisdn 						= obj->msisdn;
		this->resultCode 					= obj->resultCode;
		this->resultCodeDesc 				= obj->resultCodeDesc;
		this->requestPacket					= obj->requestPacket;
		this->answerPacket					= obj->answerPacket;

		this->StartTimeEpochMicroSec 		= obj->StartTimeEpochMicroSec;
		this->EndTimeEpochMicroSec 			= obj->EndTimeEpochMicroSec;
		this->StartTime 					= obj->StartTime;
		this->EndTime 						= obj->EndTime;
		this->s_addr_mac 					= obj->s_addr_mac;
		this->d_addr_mac 					= obj->d_addr_mac;
		this->sourceAddr 					= obj->sourceAddr;
		this->destAddr 						= obj->destAddr;
		this->s_port 						= obj->s_port;
		this->d_port 						= obj->d_port;
		this->upframeBytes					= obj->upframeBytes;
		this->dnframeBytes					= obj->dnframeBytes;
	}
}gxSession;

typedef struct GxPacket {
	uint32_t 	commandCode;
	ULONG		appId;
	string		appName;
	string		interfaceName;
	string		sessionId;
	string		originHost;
	string		originRealm;
	string		destinationHost;
	string		destinationRealm;
	uint16_t 	ccRequestType;
	string		ccReqTypeDesc;
	uint16_t 	tCause;
	string		tCauseDesc;
	string		eventTrigger;
	uint16_t	bearerOperation;
	string		bearerOperationDesc;
	string		calledStationId;
	string		accessNetworkChargingAddress;
	string		framedIPAddress;
	string		GPPS_GSN_Address;
	uint32_t	ratType;
	string		ratTypeDesc;
	string		imei;
	string		imsi;
	string		msisdn;
	uint32_t 	resultCode;
	string		resultCodeDesc;

	ULONG		requestPacket;
	ULONG		answerPacket;

	ULONG 		StartTimeEpochMicroSec;
	ULONG 		EndTimeEpochMicroSec;
	string 		StartTime;
	string 		EndTime;
	string 		s_addr_mac;
	string 		d_addr_mac;
	string 		sourceAddr;
	string 		destAddr;
	uint32_t 	s_port;
	uint32_t 	d_port;
	uint32_t	upframeBytes;
	uint32_t	dnframeBytes;
}*pGxPacket;

namespace GXFlushMap {

	extern 	std::map<ULONG, gxSession> gxEndSessionMap_0;
	extern 	std::map<ULONG, gxSession> gxEndSessionMap_1;
	extern 	std::map<ULONG, gxSession> gxEndSessionMap_2;
	extern 	std::map<ULONG, gxSession> gxEndSessionMap_3;
	extern 	std::map<ULONG, gxSession> gxEndSessionMap_4;
	extern 	std::map<ULONG, gxSession> gxEndSessionMap_5;
	extern 	std::map<ULONG, gxSession> gxEndSessionMap_6;
	extern 	std::map<ULONG, gxSession> gxEndSessionMap_7;
	extern 	std::map<ULONG, gxSession> gxEndSessionMap_8;
	extern 	std::map<ULONG, gxSession> gxEndSessionMap_9;

	extern 	ULONG gxEndSessionMapCounter_0;
	extern 	ULONG gxEndSessionMapCounter_1;
	extern 	ULONG gxEndSessionMapCounter_2;
	extern 	ULONG gxEndSessionMapCounter_3;
	extern 	ULONG gxEndSessionMapCounter_4;
	extern 	ULONG gxEndSessionMapCounter_5;
	extern 	ULONG gxEndSessionMapCounter_6;
	extern 	ULONG gxEndSessionMapCounter_7;
	extern 	ULONG gxEndSessionMapCounter_8;
	extern 	ULONG gxEndSessionMapCounter_9;
}

namespace GXAVPMap {
	extern TCHAR *bearerOperation[];
	extern TCHAR *requestType[];
	extern TCHAR *terminationCause[];
}

#endif /* PLUGINS_GX_SRC_GXGLOBAL_H_ */
