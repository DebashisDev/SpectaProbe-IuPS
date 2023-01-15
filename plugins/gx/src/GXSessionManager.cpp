/*
 * GXSessionManager.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: Debashis
 */

#include "GXSessionManager.h"

GXSessionManager::GXSessionManager() {
	// TODO Auto-generated constructor stub

}

GXSessionManager::~GXSessionManager() {
	// TODO Auto-generated destructor stub
}

VOID GXSessionManager::updateGxSession(MPacket *msgObj, int selfId)
{
	switch(msgObj->messageType)
	{
		case ANSWER:
					closeGxSession(msgObj, selfId);
					break;

		case REQUEST:
					createGxSession(msgObj, selfId);
					break;
	}
}

void GXSessionManager::initialize(sh_GxPacket pktstruct)
{
	pktstruct->commandCode = 0;
	pktstruct->appId = 0;
	pktstruct->appName.clear();
	pktstruct->interfaceName.clear();
	pktstruct->sessionId.clear();
	pktstruct->originHost.clear();
	pktstruct->originRealm.clear();
	pktstruct->destinationHost.clear();
	pktstruct->destinationRealm.clear();
	pktstruct->ccRequestType = 0;
	pktstruct->ccReqTypeDesc.clear();
	pktstruct->tCause = 0;
	pktstruct->tCauseDesc.clear();
	pktstruct->eventTrigger.clear();
	pktstruct->bearerOperation = 0;
	pktstruct->bearerOperationDesc.clear();
	pktstruct->calledStationId.clear();
	pktstruct->accessNetworkChargingAddress.clear();
	pktstruct->framedIPAddress.clear();
	pktstruct->GPPS_GSN_Address.clear();
	pktstruct->ratType = 0;
	pktstruct->ratTypeDesc.clear();
	pktstruct->imei.clear();
	pktstruct->imsi.clear();
	pktstruct->msisdn.clear();
	pktstruct->resultCode = 0;
	pktstruct->resultCodeDesc.clear();
	pktstruct->requestPacket = 0;
	pktstruct->answerPacket = 0;

	pktstruct->StartTimeEpochMicroSec = 0;
	pktstruct->EndTimeEpochMicroSec = 0;
	pktstruct->StartTime.clear();
	pktstruct->EndTime.clear();
	pktstruct->s_addr_mac.clear();
	pktstruct->d_addr_mac.clear();
	pktstruct->sourceAddr.clear();
	pktstruct->destAddr.clear();
	pktstruct->s_port = 0;
	pktstruct->d_port = 0;
}

VOID GXSessionManager::createGxSession(MPacket *msgObj, int selfId)
{
	sh_GxPacket pktstruct = sh_GxPacket(new GxPacket);
	initialize(pktstruct);

	string key = msgObj->sessionId;
	gxPacketMap& createGx = SessionStore::gxMap[selfId];

	if (createGx.find(key) != createGx.end())
	{
		createGx.erase(createGx.find(key));
		createSession(pktstruct, msgObj);
		createGx.insert(std::pair<string, sh_GxPacket>(key, pktstruct));
	}
	else
	{
		createSession(pktstruct, msgObj);
		SessionStore::gxMap[selfId].insert(std::pair<string, sh_GxPacket>(key, pktstruct));
	}
}

VOID GXSessionManager::createSession(sh_GxPacket pGxSession, MPacket *msgObj)
{
	pGxSession->requestPacket 		= msgObj->requestPacket;
	pGxSession->commandCode 	 	= msgObj->commandCode;
	pGxSession->appId 	 			= msgObj->appId;
	pGxSession->appName				= msgObj->appName;
	pGxSession->sessionId 	 		= msgObj->sessionId;
	pGxSession->originHost 			= msgObj->originHost;
	pGxSession->originRealm			= msgObj->originRealm;
	pGxSession->destinationHost		= msgObj->destinationHost;
	pGxSession->destinationRealm 	= msgObj->destinationRealm;
	pGxSession->calledStationId		= msgObj->calledStationId;
	pGxSession->ccRequestType 		= msgObj->ccRequestType;
	pGxSession->ccReqTypeDesc 		= msgObj->ccReqTypeDesc;
	pGxSession->tCause				= msgObj->tCause;
	pGxSession->tCauseDesc			= msgObj->tCauseDesc;
	pGxSession->eventTrigger 		= msgObj->eventTrigger;
	pGxSession->bearerOperation 	= msgObj->bearerOperation;
	pGxSession->bearerOperationDesc = msgObj->bearerOperationDesc;
	pGxSession->calledStationId 	= msgObj->calledStationId;
	pGxSession->accessNetworkChargingAddress = msgObj->accessNetworkChargingAddress;
	pGxSession->framedIPAddress 	= msgObj->framedIPAddress;
	pGxSession->GPPS_GSN_Address 	= msgObj->GPPS_GSN_Address;
	pGxSession->ratType 			= msgObj->ratType;
	pGxSession->ratTypeDesc 		= msgObj->ratTypeDesc;
	pGxSession->imei 				= msgObj->imei;
	pGxSession->imsi 				= msgObj->imsi;
	pGxSession->msisdn 				= msgObj->msisdn;

	pGxSession->StartTimeEpochMicroSec 	= msgObj->frTimeEpochSec;
//	pGxSession->StartTime 			= msgObj->frameData->frameTimeStamp;

	pGxSession->s_addr_mac			= msgObj->ethSourceMACAddr;
	pGxSession->d_addr_mac			= msgObj->ethDestMACAddr;
//	pGxSession->sourceAddr			= msgObj->ipData->sourceAddr;
//	pGxSession->destAddr			= msgObj->ipData->destAddr;
//	pGxSession->s_port 	 			= msgObj->tcpData->s_port;
//	pGxSession->d_port 				= msgObj->tcpData->d_port;
	pGxSession->upframeBytes		= msgObj->frSize;
}

void GXSessionManager::closeGxSession(MPacket *msgObj, int selfId)
{
	string key = msgObj->sessionId;

	gxPacketMap::iterator itr = SessionStore::gxMap[selfId].find(key);

	if (itr != SessionStore::gxMap[selfId].end())
	{
		gxSession *pGxSession = new gxSession();
		SessionStore::copyGxData(itr->second, pGxSession);

		pGxSession->EndTimeEpochMicroSec 	= msgObj->frTimeEpochSec;
//		pGxSession->EndTime 				= msgObj->frameData->frameTimeStamp;
		pGxSession->resultCode 				= msgObj->resultCode;
		pGxSession->resultCodeDesc 			= msgObj->resultCodeDesc;
		pGxSession->answerPacket 			= msgObj->answerPacket;
		pGxSession->dnframeBytes			= msgObj->frSize;

#if 1
		printf("Request # %ld\n", pGxSession->requestPacket);
		printf("Answer  # %ld\n", pGxSession->answerPacket);
		printf("commandCode        : %d\n", pGxSession->commandCode);
		printf("appId              : %ld\n", pGxSession->appId);
		printf("appName            : %s\n", pGxSession->appName.c_str());
		printf("sessionId          : %s\n", pGxSession->sessionId.c_str());
		printf("originHost         : %s\n", pGxSession->originHost.c_str());
		printf("originHostRealm    : %s\n", pGxSession->originRealm.c_str());
		printf("destinationHost    : %s\n", pGxSession->destinationHost.c_str());
		printf("destinationRealm   : %s\n", pGxSession->destinationRealm.c_str());
		printf("ccRequestType      : %d\n", pGxSession->ccRequestType);
		printf("ccReqTypeDesc      : %s\n", pGxSession->ccReqTypeDesc.c_str());
		printf("T_Cause            : %d\n", pGxSession->tCause);
		printf("T_CauseDesc        : %s\n", pGxSession->tCauseDesc.c_str());
		printf("eventTrigger       : %s\n", pGxSession->eventTrigger.c_str());
		printf("bearerOperation    : %d\n", pGxSession->bearerOperation);
		printf("bearerOperationDesc: %s\n", pGxSession->bearerOperationDesc.c_str());
		printf("calledStationId    : %s\n", pGxSession->calledStationId.c_str());
		printf("ChargingAddress    : %s\n", pGxSession->accessNetworkChargingAddress.c_str());
		printf("framedIPAddress    : %s\n", pGxSession->framedIPAddress.c_str());
		printf("GPPS_GSN_Address   : %s\n", pGxSession->GPPS_GSN_Address.c_str());
		printf("ratType            : %d\n", pGxSession->ratType);
		printf("ratTypeDesc        : %s\n", pGxSession->ratTypeDesc.c_str());
		printf("IMEI               : %s\n", pGxSession->imei.c_str());
		printf("IMSI               : %s\n", pGxSession->imsi.c_str());
		printf("MSISDN             : %s\n", pGxSession->msisdn.c_str());
		printf("Result             : %d\n", pGxSession->resultCode);
		printf("Result Desc        : %s\n", pGxSession->resultCodeDesc.c_str());
		printf("Up Size            : %d\n", pGxSession->upframeBytes);
		printf("Down Size          : %d\n", pGxSession->dnframeBytes);
#endif

		SessionStore::flushGxSession(msgObj->frTimeEpochSec, pGxSession, true, selfId);
		SessionStore::gxMap[selfId].erase(itr);
	}
}

VOID GXSessionManager::buildCSVData(gxSession *pGxSession, string& csvBuffer)
{
	csvBuffer.clear();

	csvBuffer.assign(to_string(IPGlobal::PROBE_ID))
		     .append(",")
			 .append(to_string(pGxSession->appId))				// GTP ID
			 .append(",")
			 .append(pGxSession->appName)			// Protocol Description
			 .append(",")
			 .append(pGxSession->interfaceName)
			 .append(",")
			 .append(pGxSession->sessionId)
			 .append(",")
			 .append(pGxSession->StartTime)
			 .append(",")
			 .append(to_string(pGxSession->StartTimeEpochMicroSec))
			 .append(",")
			 .append(pGxSession->EndTime)
			 .append(",")
			 .append(to_string(pGxSession->EndTimeEpochMicroSec))
			 .append(",")
			 .append("PCEF-->PCRF,")
			 .append(pGxSession->s_addr_mac)
			 .append(",")
			 .append(pGxSession->d_addr_mac)
			 .append(",")
			 .append(pGxSession->sourceAddr)
			 .append(",")
			 .append(pGxSession->destAddr)
			 .append(",")
			 .append(std::to_string(pGxSession->s_port))
			 .append(",")
			 .append(std::to_string(pGxSession->d_port))
			 .append(",")
			 .append(std::to_string(pGxSession->commandCode))
			 .append(",")
			 .append(pGxSession->originHost)
			 .append(",")
			 .append(pGxSession->originRealm)
			 .append(",")
			 .append(pGxSession->destinationHost)
			 .append(",")
			 .append(pGxSession->destinationRealm)
			 .append(",")
			 .append(std::to_string(pGxSession->ccRequestType))
			 .append(",")
			 .append(pGxSession->ccReqTypeDesc)
			 .append(",")
			 .append(std::to_string(pGxSession->tCause))
			 .append(",")
			 .append(pGxSession->tCauseDesc)
			 .append(",")
			 .append(pGxSession->eventTrigger)
			 .append(",")
			 .append(std::to_string(pGxSession->bearerOperation))
			 .append(",")
			 .append(pGxSession->bearerOperationDesc)
			 .append(",")
			 .append(pGxSession->calledStationId)
			 .append(",")
			 .append(pGxSession->accessNetworkChargingAddress)
			 .append(",")
			 .append(pGxSession->framedIPAddress)
			 .append(",")
			 .append(pGxSession->GPPS_GSN_Address)
			 .append(",")
			 .append(std::to_string(pGxSession->ratType))
			 .append(",")
			 .append(pGxSession->ratTypeDesc)
			 .append(",")
			 .append(pGxSession->imei)
			 .append(",")
			 .append(pGxSession->imsi)
			 .append(",")
			 .append(pGxSession->msisdn)
			 .append(",")
			 .append(std::to_string(pGxSession->resultCode))
			 .append(",")
			 .append(pGxSession->resultCodeDesc)
			 .append(",")
			 .append(std::to_string(pGxSession->upframeBytes))
			 .append(",")
			 .append(std::to_string(pGxSession->dnframeBytes));
}
