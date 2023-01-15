/*
 * diameterMsg.h
 *
 *  Created on: 08-Oct-2016
 *      Author: deb
 */

#ifndef PLUGINS_GX_INC_GXMESSAGE_H_
#define PLUGINS_GX_INC_GXMESSAGE_H_

#include "SpectaTypedef.h"

using namespace std;

typedef struct _gxData
{
	uint16_t	messageType;
	uint32_t 	commandCode;
	ULONG		appId;
	string		appName;
	string		sessionId;
	string		interfaceName;
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
	ULONG		subscriptionType;

	_gxData()
	{ reset(); }

//	~_gxData(){}

	void reset()
	{
		messageType = 0;
		commandCode = 0;
		appId = 0;
		appName.clear();
		interfaceName.clear();
		sessionId.clear();
		originHost.assign("NA");
		originRealm.assign("NA");
		destinationHost.assign("NA");
		destinationRealm.assign("NA");
		ccRequestType = 0;
		ccReqTypeDesc.assign("NA");
		tCause = 0;
		tCauseDesc.assign("NA");
		eventTrigger.clear();
		bearerOperation = 0;
		bearerOperationDesc.assign("NA");
		calledStationId.assign("NA");
		accessNetworkChargingAddress.assign("NA");
		framedIPAddress.assign("NA");
		GPPS_GSN_Address.assign("NA");
		ratType = 0;
		ratTypeDesc.assign("NA");
		imei.assign("NA");
		imsi.assign("NA");
		msisdn.assign("NA");
		resultCode = 0;
		resultCodeDesc.assign("NA");
		requestPacket = 0;
		answerPacket = 0;
		subscriptionType = 0;
	}

	void set(const _gxData *obj)
	{
		this->messageType						= obj->messageType;
		this->commandCode 					= obj->commandCode;
		this->appId 						= obj->appId;
		this->appName						= obj->appName;
		this->interfaceName					= obj->interfaceName;
		this->sessionId 					= obj->sessionId;
		this->originHost 					= obj->originHost;
		this->originRealm 					= obj->originRealm;
		this->destinationHost				= obj->destinationHost;
		this->destinationRealm 				= obj->destinationRealm;
		this->calledStationId				= obj->calledStationId;
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
		this->subscriptionType				= obj->subscriptionType;
	}
}gxVar;

#endif /* PLUGINS_GX_INC_GXMESSAGE_H_ */
