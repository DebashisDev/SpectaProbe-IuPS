/*
 * IPSessionManager.cpp
 *
 *  Created on: 20-Jul-2016
 *      Author: deb
 */

#include "sys/time.h"
#include <locale.h>

#include "IPSessionManager.h"

IPSessionManager::IPSessionManager(int id) {
	_thisLogLevel = 0;
	this->_name = "IPSessionManager";
	this->setLogLevel(Log::theLog().level());
	this->instanceId = id;
	today = IPGlobal::CURRENT_TIME_DAY;
	tcpFlusherUtility = new TCPFlusherUtility();
	initializeIPFlushRepository();
	initializeDNSFlushRepository();
}

IPSessionManager::~IPSessionManager() {
	delete(tcpFlusherUtility);
}


VOID IPSessionManager::processTcpSession(MPacket *msgObj)
{

	bool found = false;
	ULONG latency = 0;
	ipSession *pIpSession;

	switch(msgObj->tcpFlags)
	{
		case  SYN_RCV:
				pIpSession = getIpSession(msgObj, &found, true);
				if(pIpSession == NULL) return;

				if(!found) {		// New Session
					initializeTcpSession(pIpSession, msgObj);
					updateTcpFrame(pIpSession, msgObj);
					return;
				}

				// If SYN received, and session is already created, flush the existing session and create new session.
				if(pIpSession->synTimeEpochNanoSec == 0)
				{
					pIpSession->synTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
					pIpSession->synRcv = true;
				}

				switch(pIpSession->state)
				{
					case SYN_ACK_RCV:
							updateTcpFrame(pIpSession, msgObj);
							break;

					case CONNECTED:
							flushIpSession(1, pIpSession, false, false);
							pIpSession->reuse();
							initializeTcpSession(pIpSession, msgObj);
							updateTcpFrame(pIpSession, msgObj);
							break;

					default:
							updateTcpFrame(pIpSession, msgObj);
							break;
				}
				break;

		case SYN_ACK_RCV:
				pIpSession = getIpSession(msgObj, &found, true);
				if(pIpSession == NULL) return;

				if(!found)
				{
					initializeTcpSession(pIpSession, msgObj);
					updateTcpFrame(pIpSession, msgObj);
					return;
				}

				if(pIpSession->synAckTimeEpochNanoSec == 0)
				{
					pIpSession->synAckTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
					pIpSession->synAckRcv = true;
				}

				switch(pIpSession->state)
				{
					case SYN_RCV: 			// If session found update the frame parameters
							pIpSession->state = SYN_ACK_RCV;
							updateTcpFrame(pIpSession, msgObj);
							break;

					case SYN_ACK_RCV:
							updateTcpFrame(pIpSession, msgObj);
							break;

					case CONNECTED:
							updateTcpFrame(pIpSession, msgObj);
							break;

					default:
							updateTcpFrame(pIpSession, msgObj);
							break;
				}
				break;

		case ACK_RCV:
				pIpSession = getIpSession(msgObj, &found, true);
				if(pIpSession == NULL) return;

				if(!found)
				{
					pIpSession->state = UNKNOWN;
					initializeTcpSession(pIpSession, msgObj);
					updateTcpFrame(pIpSession, msgObj);
					return;
				}

				if(pIpSession->ackTimeEpochNanoSec == 0)
					pIpSession->ackTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;

				switch(pIpSession->state)
				{
					case SYN_RCV:
							updateTcpFrame(pIpSession, msgObj);
							break;

					case SYN_ACK_RCV:
							pIpSession->state = CONNECTED;
							pIpSession->causeCode = SESSION_TERM_TCP_CONN_DATA;

							// Calculate Connection Latency in ms
							if(msgObj->frTimeEpochNanoSec > pIpSession->startTimeEpochNanoSec)
							{
								latency = msgObj->frTimeEpochNanoSec - pIpSession->startTimeEpochNanoSec;
								if(latency > 1000000)
									latency = latency / 1000000;
								else
									latency = 0;
							}

							pIpSession->synLatency = latency;
							updateTcpFrame(pIpSession, msgObj);
							break;

					case CONNECTED:
							updateTcpFrame(pIpSession, msgObj);
							break;

					default:
							updateTcpFrame(pIpSession, msgObj);
							break;
				}
				break;

		case DATA_RCV:
				pIpSession = getIpSession(msgObj, &found, true);
				if(pIpSession == NULL) return;

				if(!found)
				{
					pIpSession->state = UNKNOWN;
					initializeTcpSession(pIpSession, msgObj);
					updateTcpFrame(pIpSession, msgObj);
					pIpSession->dataRcv = true;
					pIpSession->firstDataTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
					pIpSession->firstDataFlag = true;
					return;
				}

				if(pIpSession->firstDataFlag == false) {
					pIpSession->dataRcv = true;
					pIpSession->firstDataTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
					pIpSession->firstDataFlag = true;
				}

				switch(pIpSession->state)
				{
					case SYN_RCV:
					case SYN_ACK_RCV:
							updateTcpFrame(pIpSession, msgObj);
							break;

					case CONNECTED:
							updateTcpFrame(pIpSession, msgObj);
							break;

					default:
							updateTcpFrame(pIpSession, msgObj);
							break;
				}

				break;

		case FIN_RCV:
				pIpSession = getIpSession(msgObj, &found, false);
				if(pIpSession == NULL) return;

				if(!found)
				{
//					pIpSession->causeCode = FIN_NO_SESSION;
//					initializeTcpSession(pIpSession, msgObj);
//					updateTcpFrame(pIpSession, msgObj);
//					flushIpSession(2, pIpSession, true);

					countFinOnlySessions();
					return;
				}

				pIpSession->finTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
				pIpSession->finRcv = true;

				switch(pIpSession->state)
				{
					case SYN_RCV:
					case SYN_ACK_RCV:
							if(pIpSession->payloadPacket > 0)
								pIpSession->causeCode = SESSION_TERM_TCP_NOCONN_DATA;
							else
								pIpSession->causeCode = SESSION_TERM_TCP_NOCONN_NODATA;

							updateTcpFrame(pIpSession, msgObj);
//							pIpSession->state = FIN_RCV;
							break;

					case CONNECTED:
							// The the slice counter, if slicing done already, increment the counter by 1
							if(pIpSession->sliceCounter >= 1)
								pIpSession->sliceCounter += 1;

							//Valid Disconnection
							if(pIpSession->payloadPacket > 0) {
								pIpSession->causeCode = SESSION_TERM_TCP_CONN_DATA;
							}
							else {
								pIpSession->causeCode = SESSION_TERM_TCP_CONN_NODATA;
							}
//							pIpSession->state = FIN_RCV;
							updateTcpFrame(pIpSession, msgObj);
							break;

					default:
							// The the slice counter, if slicing done already, increment the counter by 1
							if(pIpSession->sliceCounter >= 1)
								pIpSession->sliceCounter += 1;

							if(pIpSession->payloadPacket > 0)
								pIpSession->causeCode = SESSION_TERM_TCP_NOCONN_DATA;
							else
								pIpSession->causeCode = SESSION_TERM_TCP_NOCONN_NODATA;

//							pIpSession->state = FIN_RCV;
							updateTcpFrame(pIpSession, msgObj);
							break;
				}

				flushIpSession(3,pIpSession, true, false);
				break;

		default:
				break;

	}	// End of Main Switch
	pIpSession = NULL;
} // End Of updateTCPSession Function

VOID IPSessionManager::initializeTcpSession(ipSession *pIpSession, MPacket *msgObj)
{
	//Set session values
	pIpSession->protocolType = PACKET_IPPROTO_TCP;
	if(msgObj->dirUserNetwork)
		pIpSession->teid_up = msgObj->gtpcPktTunnelId;
	else
		pIpSession->teid_dn = msgObj->gtpcPktTunnelId;
	pIpSession->sourceIP = msgObj->ipSourceAddr;
	pIpSession->destIP = msgObj->ipDestAddr;
	pIpSession->isUpDir = msgObj->dirUserNetwork;
	pIpSession->sourcePort = msgObj->protoSourcePort;
	pIpSession->destPort = msgObj->protoDestPort;

	pIpSession->sgsnIPAddr = msgObj->gtpSGSNAddr;
	pIpSession->ggsnIPAddr = msgObj->gtpGGSNAddr;
	pIpSession->sgsnPort = msgObj->gtpSGSNPort;
	pIpSession->ggsnPort = msgObj->gtpGGSNPort;

	strcpy(pIpSession->sourceMacAddr, msgObj->ethSourceMACAddr);
	strcpy(pIpSession->destMacAddr, msgObj->ethDestMACAddr);
	pIpSession->synLatency = 0;
	pIpSession->sliceCounter = 0;

	pIpSession->pckLastTimeEpochSec = msgObj->frTimeEpochSec;
	pIpSession->pckLastTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;

	pIpSession->startTimeEpochSec = msgObj->frTimeEpochSec;
	pIpSession->startTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;

	pIpSession->endTimeEpochSec = msgObj->frTimeEpochSec;
	pIpSession->endTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;

	switch(msgObj->tcpFlags)
	{
		case SYN_RCV:
			pIpSession->synRcv = true;
			pIpSession->state = SYN_RCV;
			pIpSession->synTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
			break;

		case SYN_ACK_RCV:
			pIpSession->synAckRcv = true;
			pIpSession->state = SYN_ACK_RCV;
			pIpSession->synAckTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
			break;

		case ACK_RCV:
			pIpSession->state = ACK_RCV;
			pIpSession->ackTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
			break;

		case FIN_RCV:
			pIpSession->finRcv = true;
			pIpSession->state = FIN_RCV;
			pIpSession->finTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
			break;
	}

	if(strlen(pIpSession->contentType) == 0)
		strcpy(pIpSession->contentType, msgObj->tcpCType);
}

VOID IPSessionManager::updateTcpFrame(ipSession *pIpSession, MPacket *msgObj)
{
	if(strlen(pIpSession->contentType) == 0)
		strcpy(pIpSession->contentType, msgObj->tcpCType);


	//Set last packet time & end time as current time in micro second
	pIpSession->pckLastTimeEpochSec = msgObj->frTimeEpochSec;
	pIpSession->pckLastTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
	pIpSession->endTimeEpochSec = msgObj->frTimeEpochSec;
	pIpSession->endTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;

	pIpSession->frameCount ++;
	pIpSession->frameSize += msgObj->frSize;

	/* In Second Calculation (Total Packets and Total Volume) */
	/* Note: Pick Throughput can be calculated from this MAP */

	pIpSession->packTimeMap[msgObj->frTimeEpochSec].totalPackets ++;
	pIpSession->packTimeMap[msgObj->frTimeEpochSec].totalVolume += msgObj->frSize;

	if(msgObj->dirUserNetwork == true) {
		pIpSession->teid_up = msgObj->gtpcPktTunnelId;
		pIpSession->upFrameSize += msgObj->frSize;
		pIpSession->upFrameCount++;

		pIpSession->packTimeMap[msgObj->frTimeEpochSec].upPackets += 1;
		pIpSession->packTimeMap[msgObj->frTimeEpochSec].upVolume += msgObj->frSize;

		if(msgObj->protoPayload > 0) {
			pIpSession->payloadPacket++;
			pIpSession->payloadSize +=  msgObj->protoPayload;
			pIpSession->upPayloadPacket ++;
			pIpSession->upPayloadSize += msgObj->protoPayload;
		}
	}
	else {
		pIpSession->teid_dn = msgObj->gtpcPktTunnelId;
		pIpSession->dnFrameSize += msgObj->frSize;
		pIpSession->dnFrameCount++;

		pIpSession->packTimeMap[msgObj->frTimeEpochSec].dnPackets += 1;
		pIpSession->packTimeMap[msgObj->frTimeEpochSec].dnVolume += msgObj->frSize;

		if(msgObj->protoPayload > 0) {
			pIpSession->payloadPacket++;
			pIpSession->payloadSize +=  msgObj->protoPayload;
			pIpSession->dnPayloadPacket ++;
			pIpSession->dnPayloadSize += msgObj->protoPayload;
		}
	}

	//Set data latency values
	if(pIpSession->state == CONNECTED)
	{
		pIpSession->pshTSval = 0;
		pIpSession->pshTSecr = 0;
		pIpSession->pshLatency = 0;

		if(msgObj->protoPayload > 0){
			if(msgObj->tcpTsEcr == pIpSession->pshTSval) {
				if(msgObj->tcpTsVal > 0 && msgObj->tcpTsVal >= pIpSession->pshTSecr) {
					pIpSession->pshLatency = msgObj->tcpTsVal - pIpSession->pshTSecr;
				}
			}
			else {
				pIpSession->pshTSval = msgObj->tcpTsVal;
				pIpSession->pshTSecr = msgObj->tcpTsEcr;
			}
		}
	}

	if(pIpSession->frameCount >= IPGlobal::IP_SESSION_PKT_LIMIT)
	{
		pIpSession->sliceCounter += 1;
		if(pIpSession->state == CONNECTED)
			pIpSession->causeCode = SYSTEM_PKTLIMIT_TCP_CONN_DATA;
		else
			pIpSession->causeCode = SYSTEM_PKTLIMIT_TCP_NOCONN_DATA;

		flushIpSession(4,pIpSession,false, false);
		pIpSession->reuse();
	}
}

VOID IPSessionManager::processUdpSession(MPacket *msgObj)
{
	bool found = false;

	ipSession *pIpSession = getIpSession(msgObj, &found, true);
	if(pIpSession == NULL) return;

	if(!found)
	{
		createUdpSession(pIpSession, msgObj);
		updateUdpFrame(pIpSession, msgObj);
	}
	else
	{
		updateUdpFrame(pIpSession, msgObj);
	}
	pIpSession = NULL;
}

VOID IPSessionManager::createUdpSession(ipSession *pIpSession, MPacket *msgObj)
{
	pIpSession->protocolType = PACKET_IPPROTO_UDP;
	pIpSession->state = UD_UDP_DATA;
	pIpSession->sourceIP = msgObj->ipSourceAddr;
	pIpSession->destIP = msgObj->ipDestAddr;
	pIpSession->isUpDir = msgObj->dirUserNetwork;
	pIpSession->sourcePort = msgObj->protoSourcePort;
	pIpSession->destPort = msgObj->protoDestPort;

	pIpSession->sgsnIPAddr = msgObj->gtpSGSNAddr;
	pIpSession->ggsnIPAddr = msgObj->gtpGGSNAddr;
	pIpSession->sgsnPort = msgObj->gtpSGSNPort;
	pIpSession->ggsnPort = msgObj->gtpGGSNPort;


	strcpy(pIpSession->sourceMacAddr, msgObj->ethSourceMACAddr);
	strcpy(pIpSession->destMacAddr, msgObj->ethDestMACAddr);
	pIpSession->sliceCounter = 0;

	if(msgObj->dirUserNetwork)
		pIpSession->teid_up = msgObj->gtpcPktTunnelId;
	else
		pIpSession->teid_dn = msgObj->gtpcPktTunnelId;

	pIpSession->pckLastTimeEpochSec = msgObj->frTimeEpochSec;
	pIpSession->pckLastTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
	pIpSession->startTimeEpochSec = msgObj->frTimeEpochSec;
	pIpSession->startTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
	pIpSession->endTimeEpochSec = msgObj->frTimeEpochSec;
	pIpSession->endTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;

}

VOID IPSessionManager::updateUdpFrame(ipSession *pIpSession, MPacket *msgObj)
{
	//Set last packet time & end time as current time in micro second

	pIpSession->pckLastTimeEpochSec = msgObj->frTimeEpochSec;
	pIpSession->pckLastTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;

	pIpSession->endTimeEpochSec = msgObj->frTimeEpochSec;
	pIpSession->endTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;

	pIpSession->frameCount ++;
	pIpSession->frameSize += msgObj->frSize;

	/* In Second Calculation (Total Packets and Total Volume) */
	/* Note: Pick Throughput can be calculated from this MAP */
	pIpSession->packTimeMap[msgObj->frTimeEpochSec].totalPackets ++;
	pIpSession->packTimeMap[msgObj->frTimeEpochSec].totalVolume += msgObj->frSize;

	if(msgObj->dirUserNetwork == true) {
		pIpSession->teid_up = msgObj->gtpcPktTunnelId;
		pIpSession->upFrameSize += msgObj->frSize;
		pIpSession->upFrameCount ++;
		pIpSession->packTimeMap[msgObj->frTimeEpochSec].upPackets += 1;
		pIpSession->packTimeMap[msgObj->frTimeEpochSec].upVolume += msgObj->frSize;

		pIpSession->payloadPacket ++;
		pIpSession->payloadSize +=  msgObj->protoPayload;
		pIpSession->upPayloadPacket ++;
		pIpSession->upPayloadSize += msgObj->protoPayload;
	}
	else {
		pIpSession->teid_dn = msgObj->gtpcPktTunnelId;
		pIpSession->dnFrameSize += msgObj->frSize;
		pIpSession->dnFrameCount ++;
		pIpSession->packTimeMap[msgObj->frTimeEpochSec].dnPackets += 1;
		pIpSession->packTimeMap[msgObj->frTimeEpochSec].dnVolume += msgObj->frSize;

		pIpSession->payloadPacket ++;
		pIpSession->payloadSize +=  msgObj->protoPayload;
		pIpSession->dnPayloadPacket ++;
		pIpSession->dnPayloadSize += msgObj->protoPayload;
	}

	/** Lookup for Stun specific AppIP **/
	if(pIpSession->appIp == 0) {
		//Lookup from StunMAP if exists
		//If found pIpSession->appIp = appIP from StunMAP

		if(STUNMAP::stunMap.size() > 0){
			std::map<uint32_t, stunData>::iterator itSrc = STUNMAP::stunMap.find(msgObj->ipSourceAddr);
			if(itSrc != STUNMAP::stunMap.end())
			{
				pIpSession->appIp = itSrc->second.appIp;
			}
			else
			{
				std::map<uint32_t, stunData>::iterator itDst = STUNMAP::stunMap.find(msgObj->ipDestAddr);
				if(itDst != STUNMAP::stunMap.end())
				{
					pIpSession->appIp = itSrc->second.appIp;
				}
			}
		}
	}

	/** Check the Data Slicing **/
	if(pIpSession->frameCount >= IPGlobal::IP_SESSION_PKT_LIMIT)
	{
		pIpSession->sliceCounter += 1;
		pIpSession->causeCode = SYSTEM_PKTLIMIT_UDP_DATA;

		flushIpSession(5,pIpSession,false, false);
		pIpSession->reuse();
	}
}


VOID IPSessionManager::processDnsSession(MPacket *msgObj)
{
	dnsSession *pDnsSession;

	switch(msgObj->dnsQRFlag)
	{
		case QUERY:
			{
				std::map<uint32_t, dnsSession>::iterator it = dnsSessionMap.find(msgObj->dnsTransactionId);
				if(it != dnsSessionMap.end())
				{
					pDnsSession = &it->second;

					if(pDnsSession->state == RESPONSE)	//Response has arrieved before Req
					{
						createDnsSession(pDnsSession, msgObj);
						flushDnsSession(pDnsSession);
						dnsSessionMap.erase(msgObj->dnsTransactionId);
						return;
					}
					else 	//Duplicate DNS Request seems
					{
						pDnsSession->reset();
						createDnsSession(pDnsSession, msgObj);
					}
				}
				else
				{
					dnsSession dnsSessionNew;
					pDnsSession = &dnsSessionNew;
					createDnsSession(pDnsSession, msgObj);
					dnsSessionMap[msgObj->dnsTransactionId] = dnsSessionNew;
				}
			}
			break;

		case RESPONSE:
			{
				std::map<uint32_t, dnsSession>::iterator it = dnsSessionMap.find(msgObj->dnsTransactionId);
				if(it != dnsSessionMap.end())
				{
					pDnsSession = &it->second;

					if(pDnsSession->state == QUERY)
					{
						updateDnsSession(pDnsSession, msgObj);
						flushDnsSession(pDnsSession);
						dnsSessionMap.erase(msgObj->dnsTransactionId);
					}
					else 	//Duplicate DNS Response seems
					{
						pDnsSession->reset();
						updateDnsSession(pDnsSession, msgObj);
					}
				}
				else
				{
					dnsSession dnsSessionNew;
					pDnsSession = &dnsSessionNew;
					updateDnsSession(pDnsSession, msgObj);
					dnsSessionMap[msgObj->dnsTransactionId] = dnsSessionNew;
				}
			}
			break;

		default:
			break;
	}
}

VOID IPSessionManager:: createDnsSession(dnsSession *pDnsSession, MPacket *msgObj)
{
	pDnsSession->transactionId = msgObj->dnsTransactionId;
	pDnsSession->queryStartEpochNanoSec =  msgObj->frTimeEpochNanoSec;
	pDnsSession->sourceIP = msgObj->ipSourceAddr;
	pDnsSession->sourcePort = msgObj->protoSourcePort;
	pDnsSession->destIP = msgObj->ipDestAddr;
	pDnsSession->destPort = msgObj->protoDestPort;
	strcpy(pDnsSession->URL, msgObj->dnsName);
	pDnsSession->state = QUERY;
}

VOID IPSessionManager:: updateDnsSession(dnsSession *pDnsSession, MPacket *msgObj)
{
	pDnsSession->queryEndEpochNanoSec = msgObj->frTimeEpochNanoSec;
	strcpy(pDnsSession->URL, msgObj->dnsName);
	strcpy(pDnsSession->address, msgObj->dnsIpAddress);
	pDnsSession->errorCode = msgObj->dnsResponseCode;
	pDnsSession->state = RESPONSE;
	strcpy(pDnsSession->errorDesc, errorCode::dnsErrorCode[msgObj->dnsResponseCode]);
}


VOID IPSessionManager::processOtrSession(MPacket *msgObj)
{
#if 0
	bool found = false;
	ipSession *pIpSession;

	getSessionKey(msgObj, pIpSession->sessionKey);

	pIpSession = getIpSession(msgObj, &found, true);
	if(pIpSession == NULL) return;

	pIpSession->sourceIP 				= msgObj->ipSourceAddr;
	pIpSession->destIP 					= msgObj->ipDestAddr;
	pIpSession->protocolType 			= msgObj->ipProtocol;
	pIpSession->frameSize 				= msgObj->frSize;
	pIpSession->startTimeEpochNanoSec 	= msgObj->frTimeEpochNanoSec;

	pIpSession->endTimeEpochNanoSec 	= msgObj->frTimeEpochNanoSec;

	strcpy(pIpSession->sourceMacAddr, msgObj->ethSourceMACAddr);
	strcpy(pIpSession->destMacAddr, msgObj->ethDestMACAddr);
	pIpSession->startTimeEpochNanoSec 	= msgObj->frTimeEpochSec;

	if(msgObj->dirUserNetwork)
		pIpSession->upFrameSize = msgObj->frSize;
	else
		pIpSession->dnFrameSize = msgObj->frSize;

	flushIpSession(6,pIpSession,true);

#endif
}

ipSession* IPSessionManager::getIpSession(MPacket *msgObj, bool *found, bool create)
{
	char charSessionKey[SESSION_ID_LEN];
	ipSession *pIpSession = NULL;

	int mapIndex = getSessionKey(msgObj, charSessionKey);
	std::string sessionKey = std::string(charSessionKey);

	std::map<std::string, ipSession>::iterator it = ipSessionMap[mapIndex].find(sessionKey);
	if(it != ipSessionMap[mapIndex].end())
	{
		pIpSession = &it->second;
		*found = true;
	}
	else
	{
		if(create && sessionSizeInLimit()) //ipSessionMap.size() < IPGlobal::IP_SESSION_REPO_MAX_LIMIT) //
		{
			ipSession ipSessionObj;
			strcpy(ipSessionObj.sessionKey, charSessionKey);
			ipSessionObj.mapIndex = mapIndex;
			ipSessionMap[mapIndex][sessionKey] = ipSessionObj;

			pIpSession = &ipSessionMap[mapIndex][sessionKey];
		}
//		if(create) //ipSessionMap.size() < IPGlobal::IP_SESSION_REPO_MAX_LIMIT) //
//		{
//			if(sessionSizeInLimit())
//			{
//				ipSession ipSessionObj;
//				strcpy(ipSessionObj.sessionKey, charSessionKey);
//				ipSessionObj.mapIndex = mapIndex;
//				ipSessionMap[mapIndex][sessionKey] = ipSessionObj;
//
//				pIpSession = &ipSessionMap[mapIndex][sessionKey];
//			}
//			else
//			{
//				//Block UDP-DNS sessions if size limit exceeded
//				if(msgObj->ipProtocol == IPPROTO_UDP && (msgObj->protoDestPort == DNS_PORT || msgObj->protoSourcePort == DNS_PORT))
//				{
//					//Do nothing
//				}
//				else
//				{
//					ipSession ipSessionObj;
//					strcpy(ipSessionObj.sessionKey, charSessionKey);
//					ipSessionObj.mapIndex = mapIndex;
//					ipSessionMap[mapIndex][sessionKey] = ipSessionObj;
//
//					pIpSession = &ipSessionMap[mapIndex][sessionKey];
//				}
//			}
//		}
		*found = false;
	}

	return pIpSession;

}

VOID IPSessionManager::getSessionSize()
{
	int i = 0;
	switch(instanceId)
	{
		case 0:
			IPStats::ip_session_total_sm_0_cnt = 0;
			for(i = 0; i < IP_SESSION_ARRAY_SIZE; i++) {
				IPStats::ip_session_total_sm_0_cnt += ipSessionMap[i].size();
			}
			break;
		case 1:
			IPStats::ip_session_total_sm_1_cnt = 0;
			for(i = 0; i < IP_SESSION_ARRAY_SIZE; i++) {
				IPStats::ip_session_total_sm_1_cnt += ipSessionMap[i].size();
			}
			break;
		case 2:
			IPStats::ip_session_total_sm_2_cnt = 0;
			for(i = 0; i < IP_SESSION_ARRAY_SIZE; i++) {
				IPStats::ip_session_total_sm_2_cnt += ipSessionMap[i].size();
			}
			break;
		case 3:
			IPStats::ip_session_total_sm_3_cnt = 0;
			for(i = 0; i < IP_SESSION_ARRAY_SIZE; i++) {
				IPStats::ip_session_total_sm_3_cnt += ipSessionMap[i].size();
			}
			break;
		case 4:
			IPStats::ip_session_total_sm_4_cnt = 0;
			for(i = 0; i < IP_SESSION_ARRAY_SIZE; i++) {
				IPStats::ip_session_total_sm_4_cnt += ipSessionMap[i].size();
			}
			break;
	}
}

bool IPSessionManager::sessionSizeInLimit()
{
	switch(instanceId)
	{
		case 0:
			if(IPStats::ip_session_total_sm_0_cnt >= IPGlobal::IP_SESSION_REPO_MAX_LIMIT) return false;
			break;
		case 1:
			if(IPStats::ip_session_total_sm_1_cnt >= IPGlobal::IP_SESSION_REPO_MAX_LIMIT) return false;
			break;
		case 2:
			if(IPStats::ip_session_total_sm_2_cnt >= IPGlobal::IP_SESSION_REPO_MAX_LIMIT) return false;
			break;
		case 3:
			if(IPStats::ip_session_total_sm_3_cnt >= IPGlobal::IP_SESSION_REPO_MAX_LIMIT) return false;
			break;
		case 4:
			if(IPStats::ip_session_total_sm_4_cnt >= IPGlobal::IP_SESSION_REPO_MAX_LIMIT) return false;
			break;
	}

	return true;
}

VOID IPSessionManager::flushIpSession(int flushOrgId, ipSession *pIpSession, bool erase, bool ignoreSessionFlush)
{
	long epochSecNow = getCurrentEpochSeconds();

//	getVolPerSec(pIpSession);

	pIpSession->flushOrgId = flushOrgId;
	pIpSession->flushTime = epochSecNow;
	pIpSession->lastActivityTimeEpohSec = epochSecNow;

//	if(pIpSession->causeCode != FIN_NO_SESSION)
//		tcpFlusherUtility->getGTPcData(pIpSession);

//	tcpFlusherUtility->getDnsData(pIpSession);

//	int index = (((epochSecNow % 100) /10)  % IPGlobal::FLUSHER_TIMEINDEX) + 1;
//	if(index >= IPGlobal::FLUSHER_TIMEINDEX) index = index - IPGlobal::FLUSHER_TIMEINDEX;

	int idx = WRITE_TIME_INDEX(epochSecNow);

	storeIpSession(idx, pIpSession);

	if(erase)
		eraseIpSession(pIpSession);
}

VOID IPSessionManager::storeIpSession(int idx, ipSession *pIpSession)
{
	switch(IPGlobal::GN_GTPU_FLUSHER_NO)
	{
		case 2:
				switch(instanceId)
				{
					case 1:
					case 2:
						storeIpSession_f_0(idx, pIpSession);
						break;

					case 3:
					case 4:
						storeIpSession_f_1(idx, pIpSession);
						break;
				}
				break;

		case 4:
				switch(instanceId)
				{
					case 1:
						storeIpSession_f_0(idx, pIpSession);
						break;
					case 2:
						storeIpSession_f_1(idx, pIpSession);
						break;
					case 3:
						storeIpSession_f_2(idx, pIpSession);
						break;
					case 4:
						storeIpSession_f_3(idx, pIpSession);
						break;
				}
				break;
	}
}

VOID IPSessionManager::storeIpSession_f_0(int index, ipSession *pIpSession)
{

	switch(instanceId)
	{
			case 0:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_0[IPFlushRepository::ipFlushMap_f_0_sm_0_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_1[IPFlushRepository::ipFlushMap_f_0_sm_0_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_2[IPFlushRepository::ipFlushMap_f_0_sm_0_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_3[IPFlushRepository::ipFlushMap_f_0_sm_0_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_4[IPFlushRepository::ipFlushMap_f_0_sm_0_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_5[IPFlushRepository::ipFlushMap_f_0_sm_0_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_6[IPFlushRepository::ipFlushMap_f_0_sm_0_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_7[IPFlushRepository::ipFlushMap_f_0_sm_0_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_8[IPFlushRepository::ipFlushMap_f_0_sm_0_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_9[IPFlushRepository::ipFlushMap_f_0_sm_0_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_0_t_9_cnt++;
						break;
					}
					break;

			case 1:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_0[IPFlushRepository::ipFlushMap_f_0_sm_1_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_1[IPFlushRepository::ipFlushMap_f_0_sm_1_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_2[IPFlushRepository::ipFlushMap_f_0_sm_1_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_3[IPFlushRepository::ipFlushMap_f_0_sm_1_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_4[IPFlushRepository::ipFlushMap_f_0_sm_1_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_5[IPFlushRepository::ipFlushMap_f_0_sm_1_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_6[IPFlushRepository::ipFlushMap_f_0_sm_1_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_7[IPFlushRepository::ipFlushMap_f_0_sm_1_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_8[IPFlushRepository::ipFlushMap_f_0_sm_1_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_9[IPFlushRepository::ipFlushMap_f_0_sm_1_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_1_t_9_cnt++;
						break;
					}
					break;
			case 2:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_0[IPFlushRepository::ipFlushMap_f_0_sm_2_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_1[IPFlushRepository::ipFlushMap_f_0_sm_2_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_2[IPFlushRepository::ipFlushMap_f_0_sm_2_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_3[IPFlushRepository::ipFlushMap_f_0_sm_2_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_4[IPFlushRepository::ipFlushMap_f_0_sm_2_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_5[IPFlushRepository::ipFlushMap_f_0_sm_2_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_6[IPFlushRepository::ipFlushMap_f_0_sm_2_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_7[IPFlushRepository::ipFlushMap_f_0_sm_2_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_8[IPFlushRepository::ipFlushMap_f_0_sm_2_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_9[IPFlushRepository::ipFlushMap_f_0_sm_2_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_2_t_9_cnt++;
						break;
					}
					break;

			case 3:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_0[IPFlushRepository::ipFlushMap_f_0_sm_3_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_1[IPFlushRepository::ipFlushMap_f_0_sm_3_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_2[IPFlushRepository::ipFlushMap_f_0_sm_3_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_3[IPFlushRepository::ipFlushMap_f_0_sm_3_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_4[IPFlushRepository::ipFlushMap_f_0_sm_3_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_5[IPFlushRepository::ipFlushMap_f_0_sm_3_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_6[IPFlushRepository::ipFlushMap_f_0_sm_3_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_7[IPFlushRepository::ipFlushMap_f_0_sm_3_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_8[IPFlushRepository::ipFlushMap_f_0_sm_3_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_9[IPFlushRepository::ipFlushMap_f_0_sm_3_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_3_t_9_cnt++;
						break;
					}
					break;

			case 4:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_0[IPFlushRepository::ipFlushMap_f_0_sm_4_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_1[IPFlushRepository::ipFlushMap_f_0_sm_4_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_2[IPFlushRepository::ipFlushMap_f_0_sm_4_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_3[IPFlushRepository::ipFlushMap_f_0_sm_4_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_4[IPFlushRepository::ipFlushMap_f_0_sm_4_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_5[IPFlushRepository::ipFlushMap_f_0_sm_4_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_6[IPFlushRepository::ipFlushMap_f_0_sm_4_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_7[IPFlushRepository::ipFlushMap_f_0_sm_4_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_8[IPFlushRepository::ipFlushMap_f_0_sm_4_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_9[IPFlushRepository::ipFlushMap_f_0_sm_4_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_0_sm_4_t_9_cnt++;
						break;
					}
					break;
	}
}

VOID IPSessionManager::storeIpSession_f_1(int index, ipSession *pIpSession)
{
	switch(instanceId)
	{
			case 0:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_0[IPFlushRepository::ipFlushMap_f_1_sm_0_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_1[IPFlushRepository::ipFlushMap_f_1_sm_0_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_2[IPFlushRepository::ipFlushMap_f_1_sm_0_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_3[IPFlushRepository::ipFlushMap_f_1_sm_0_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_4[IPFlushRepository::ipFlushMap_f_1_sm_0_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_5[IPFlushRepository::ipFlushMap_f_1_sm_0_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_6[IPFlushRepository::ipFlushMap_f_1_sm_0_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_7[IPFlushRepository::ipFlushMap_f_1_sm_0_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_8[IPFlushRepository::ipFlushMap_f_1_sm_0_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_9[IPFlushRepository::ipFlushMap_f_1_sm_0_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_0_t_9_cnt++;
						break;
					}
					break;

			case 1:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_0[IPFlushRepository::ipFlushMap_f_1_sm_1_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_1[IPFlushRepository::ipFlushMap_f_1_sm_1_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_2[IPFlushRepository::ipFlushMap_f_1_sm_1_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_3[IPFlushRepository::ipFlushMap_f_1_sm_1_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_4[IPFlushRepository::ipFlushMap_f_1_sm_1_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_5[IPFlushRepository::ipFlushMap_f_1_sm_1_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_6[IPFlushRepository::ipFlushMap_f_1_sm_1_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_7[IPFlushRepository::ipFlushMap_f_1_sm_1_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_8[IPFlushRepository::ipFlushMap_f_1_sm_1_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_9[IPFlushRepository::ipFlushMap_f_1_sm_1_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_1_t_9_cnt++;
						break;
					}
					break;
			case 2:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_0[IPFlushRepository::ipFlushMap_f_1_sm_2_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_1[IPFlushRepository::ipFlushMap_f_1_sm_2_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_2[IPFlushRepository::ipFlushMap_f_1_sm_2_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_3[IPFlushRepository::ipFlushMap_f_1_sm_2_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_4[IPFlushRepository::ipFlushMap_f_1_sm_2_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_5[IPFlushRepository::ipFlushMap_f_1_sm_2_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_6[IPFlushRepository::ipFlushMap_f_1_sm_2_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_7[IPFlushRepository::ipFlushMap_f_1_sm_2_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_8[IPFlushRepository::ipFlushMap_f_1_sm_2_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_9[IPFlushRepository::ipFlushMap_f_1_sm_2_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_2_t_9_cnt++;
						break;
					}
					break;

			case 3:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_0[IPFlushRepository::ipFlushMap_f_1_sm_3_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_1[IPFlushRepository::ipFlushMap_f_1_sm_3_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_2[IPFlushRepository::ipFlushMap_f_1_sm_3_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_3[IPFlushRepository::ipFlushMap_f_1_sm_3_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_4[IPFlushRepository::ipFlushMap_f_1_sm_3_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_5[IPFlushRepository::ipFlushMap_f_1_sm_3_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_6[IPFlushRepository::ipFlushMap_f_1_sm_3_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_7[IPFlushRepository::ipFlushMap_f_1_sm_3_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_8[IPFlushRepository::ipFlushMap_f_1_sm_3_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_9[IPFlushRepository::ipFlushMap_f_1_sm_3_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_3_t_9_cnt++;
						break;
					}
					break;

			case 4:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_0[IPFlushRepository::ipFlushMap_f_1_sm_4_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_1[IPFlushRepository::ipFlushMap_f_1_sm_4_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_2[IPFlushRepository::ipFlushMap_f_1_sm_4_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_3[IPFlushRepository::ipFlushMap_f_1_sm_4_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_4[IPFlushRepository::ipFlushMap_f_1_sm_4_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_5[IPFlushRepository::ipFlushMap_f_1_sm_4_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_6[IPFlushRepository::ipFlushMap_f_1_sm_4_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_7[IPFlushRepository::ipFlushMap_f_1_sm_4_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_8[IPFlushRepository::ipFlushMap_f_1_sm_4_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_9[IPFlushRepository::ipFlushMap_f_1_sm_4_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_1_sm_4_t_9_cnt++;
						break;
					}
					break;
	}
}

VOID IPSessionManager::storeIpSession_f_2(int index, ipSession *pIpSession)
{
	switch(instanceId)
	{
			case 0:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_0[IPFlushRepository::ipFlushMap_f_2_sm_0_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_1[IPFlushRepository::ipFlushMap_f_2_sm_0_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_2[IPFlushRepository::ipFlushMap_f_2_sm_0_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_3[IPFlushRepository::ipFlushMap_f_2_sm_0_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_4[IPFlushRepository::ipFlushMap_f_2_sm_0_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_5[IPFlushRepository::ipFlushMap_f_2_sm_0_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_6[IPFlushRepository::ipFlushMap_f_2_sm_0_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_7[IPFlushRepository::ipFlushMap_f_2_sm_0_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_8[IPFlushRepository::ipFlushMap_f_2_sm_0_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_9[IPFlushRepository::ipFlushMap_f_2_sm_0_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_0_t_9_cnt++;
						break;
					}
					break;

			case 1:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_0[IPFlushRepository::ipFlushMap_f_2_sm_1_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_1[IPFlushRepository::ipFlushMap_f_2_sm_1_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_2[IPFlushRepository::ipFlushMap_f_2_sm_1_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_3[IPFlushRepository::ipFlushMap_f_2_sm_1_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_4[IPFlushRepository::ipFlushMap_f_2_sm_1_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_5[IPFlushRepository::ipFlushMap_f_2_sm_1_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_6[IPFlushRepository::ipFlushMap_f_2_sm_1_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_7[IPFlushRepository::ipFlushMap_f_2_sm_1_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_8[IPFlushRepository::ipFlushMap_f_2_sm_1_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_9[IPFlushRepository::ipFlushMap_f_2_sm_1_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_1_t_9_cnt++;
						break;
					}
					break;
			case 2:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_0[IPFlushRepository::ipFlushMap_f_2_sm_2_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_1[IPFlushRepository::ipFlushMap_f_2_sm_2_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_2[IPFlushRepository::ipFlushMap_f_2_sm_2_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_3[IPFlushRepository::ipFlushMap_f_2_sm_2_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_4[IPFlushRepository::ipFlushMap_f_2_sm_2_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_5[IPFlushRepository::ipFlushMap_f_2_sm_2_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_6[IPFlushRepository::ipFlushMap_f_2_sm_2_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_7[IPFlushRepository::ipFlushMap_f_2_sm_2_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_8[IPFlushRepository::ipFlushMap_f_2_sm_2_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_9[IPFlushRepository::ipFlushMap_f_2_sm_2_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_2_t_9_cnt++;
						break;
					}
					break;

			case 3:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_0[IPFlushRepository::ipFlushMap_f_2_sm_3_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_1[IPFlushRepository::ipFlushMap_f_2_sm_3_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_2[IPFlushRepository::ipFlushMap_f_2_sm_3_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_3[IPFlushRepository::ipFlushMap_f_2_sm_3_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_4[IPFlushRepository::ipFlushMap_f_2_sm_3_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_5[IPFlushRepository::ipFlushMap_f_2_sm_3_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_6[IPFlushRepository::ipFlushMap_f_2_sm_3_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_7[IPFlushRepository::ipFlushMap_f_2_sm_3_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_8[IPFlushRepository::ipFlushMap_f_2_sm_3_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_9[IPFlushRepository::ipFlushMap_f_2_sm_3_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_3_t_9_cnt++;
						break;
					}
					break;

			case 4:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_0[IPFlushRepository::ipFlushMap_f_2_sm_4_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_1[IPFlushRepository::ipFlushMap_f_2_sm_4_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_2[IPFlushRepository::ipFlushMap_f_2_sm_4_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_3[IPFlushRepository::ipFlushMap_f_2_sm_4_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_4[IPFlushRepository::ipFlushMap_f_2_sm_4_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_5[IPFlushRepository::ipFlushMap_f_2_sm_4_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_6[IPFlushRepository::ipFlushMap_f_2_sm_4_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_7[IPFlushRepository::ipFlushMap_f_2_sm_4_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_8[IPFlushRepository::ipFlushMap_f_2_sm_4_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_9[IPFlushRepository::ipFlushMap_f_2_sm_4_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_2_sm_4_t_9_cnt++;
						break;
					}
					break;
	}
}

VOID IPSessionManager::storeIpSession_f_3(int index, ipSession *pIpSession)
{
	switch(instanceId)
	{
			case 0:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_0[IPFlushRepository::ipFlushMap_f_3_sm_0_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_1[IPFlushRepository::ipFlushMap_f_3_sm_0_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_2[IPFlushRepository::ipFlushMap_f_3_sm_0_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_3[IPFlushRepository::ipFlushMap_f_3_sm_0_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_4[IPFlushRepository::ipFlushMap_f_3_sm_0_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_5[IPFlushRepository::ipFlushMap_f_3_sm_0_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_6[IPFlushRepository::ipFlushMap_f_3_sm_0_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_7[IPFlushRepository::ipFlushMap_f_3_sm_0_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_8[IPFlushRepository::ipFlushMap_f_3_sm_0_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_9[IPFlushRepository::ipFlushMap_f_3_sm_0_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_0_t_9_cnt++;
						break;
					}
					break;

			case 1:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_0[IPFlushRepository::ipFlushMap_f_3_sm_1_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_1[IPFlushRepository::ipFlushMap_f_3_sm_1_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_2[IPFlushRepository::ipFlushMap_f_3_sm_1_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_3[IPFlushRepository::ipFlushMap_f_3_sm_1_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_4[IPFlushRepository::ipFlushMap_f_3_sm_1_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_5[IPFlushRepository::ipFlushMap_f_3_sm_1_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_6[IPFlushRepository::ipFlushMap_f_3_sm_1_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_7[IPFlushRepository::ipFlushMap_f_3_sm_1_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_8[IPFlushRepository::ipFlushMap_f_3_sm_1_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_9[IPFlushRepository::ipFlushMap_f_3_sm_1_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_1_t_9_cnt++;
						break;
					}
					break;
			case 2:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_0[IPFlushRepository::ipFlushMap_f_3_sm_2_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_1[IPFlushRepository::ipFlushMap_f_3_sm_2_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_2[IPFlushRepository::ipFlushMap_f_3_sm_2_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_3[IPFlushRepository::ipFlushMap_f_3_sm_2_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_4[IPFlushRepository::ipFlushMap_f_3_sm_2_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_5[IPFlushRepository::ipFlushMap_f_3_sm_2_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_6[IPFlushRepository::ipFlushMap_f_3_sm_2_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_7[IPFlushRepository::ipFlushMap_f_3_sm_2_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_8[IPFlushRepository::ipFlushMap_f_3_sm_2_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_9[IPFlushRepository::ipFlushMap_f_3_sm_2_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_2_t_9_cnt++;
						break;
					}
					break;

			case 3:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_0[IPFlushRepository::ipFlushMap_f_3_sm_3_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_1[IPFlushRepository::ipFlushMap_f_3_sm_3_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_2[IPFlushRepository::ipFlushMap_f_3_sm_3_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_3[IPFlushRepository::ipFlushMap_f_3_sm_3_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_4[IPFlushRepository::ipFlushMap_f_3_sm_3_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_5[IPFlushRepository::ipFlushMap_f_3_sm_3_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_6[IPFlushRepository::ipFlushMap_f_3_sm_3_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_7[IPFlushRepository::ipFlushMap_f_3_sm_3_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_8[IPFlushRepository::ipFlushMap_f_3_sm_3_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_9[IPFlushRepository::ipFlushMap_f_3_sm_3_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_3_t_9_cnt++;
						break;
					}
					break;

			case 4:
					switch(index)
					{
					case 0:
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_0[IPFlushRepository::ipFlushMap_f_3_sm_4_t_0_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_1[IPFlushRepository::ipFlushMap_f_3_sm_4_t_1_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_2[IPFlushRepository::ipFlushMap_f_3_sm_4_t_2_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_3[IPFlushRepository::ipFlushMap_f_3_sm_4_t_3_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_4[IPFlushRepository::ipFlushMap_f_3_sm_4_t_4_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_5[IPFlushRepository::ipFlushMap_f_3_sm_4_t_5_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_6[IPFlushRepository::ipFlushMap_f_3_sm_4_t_6_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_7[IPFlushRepository::ipFlushMap_f_3_sm_4_t_7_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_8[IPFlushRepository::ipFlushMap_f_3_sm_4_t_8_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_9[IPFlushRepository::ipFlushMap_f_3_sm_4_t_9_cnt].copy(pIpSession);
						IPFlushRepository::ipFlushMap_f_3_sm_4_t_9_cnt++;
						break;
					}
					break;
	}
}


VOID IPSessionManager::storeDnsSession(int index, dnsSession *pDnsSession)
{
	switch(IPGlobal::GN_GTPU_FLUSHER_NO)
	{
		case 2:
				switch(instanceId)
				{
					case 1:
					case 2:
						storeDnsSession_f_0(index, pDnsSession);
						break;

					case 3:
					case 4:
						storeDnsSession_f_1(index, pDnsSession);
						break;
				}
				break;

		case 4:
				switch(instanceId)
				{
					case 1:
						storeDnsSession_f_0(index, pDnsSession);
						break;
					case 2:
						storeDnsSession_f_1(index, pDnsSession);
						break;
					case 3:
						storeDnsSession_f_2(index, pDnsSession);
						break;
					case 4:
						storeDnsSession_f_3(index, pDnsSession);
						break;
				}
				break;
	}
}

VOID IPSessionManager::storeDnsSession_f_0(int index, dnsSession *pDnsSession)
{
	switch(instanceId)
	{
			case 0:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_0[IPFlushRepository::dnsFlushMap_f_0_sm_0_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_1[IPFlushRepository::dnsFlushMap_f_0_sm_0_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_2[IPFlushRepository::dnsFlushMap_f_0_sm_0_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_3[IPFlushRepository::dnsFlushMap_f_0_sm_0_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_4[IPFlushRepository::dnsFlushMap_f_0_sm_0_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_5[IPFlushRepository::dnsFlushMap_f_0_sm_0_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_6[IPFlushRepository::dnsFlushMap_f_0_sm_0_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_7[IPFlushRepository::dnsFlushMap_f_0_sm_0_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_8[IPFlushRepository::dnsFlushMap_f_0_sm_0_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_9[IPFlushRepository::dnsFlushMap_f_0_sm_0_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_0_t_9_cnt++;
						break;
					}
					break;

			case 1:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_0[IPFlushRepository::dnsFlushMap_f_0_sm_1_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_1[IPFlushRepository::dnsFlushMap_f_0_sm_1_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_2[IPFlushRepository::dnsFlushMap_f_0_sm_1_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_3[IPFlushRepository::dnsFlushMap_f_0_sm_1_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_4[IPFlushRepository::dnsFlushMap_f_0_sm_1_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_5[IPFlushRepository::dnsFlushMap_f_0_sm_1_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_6[IPFlushRepository::dnsFlushMap_f_0_sm_1_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_7[IPFlushRepository::dnsFlushMap_f_0_sm_1_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_8[IPFlushRepository::dnsFlushMap_f_0_sm_1_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_9[IPFlushRepository::dnsFlushMap_f_0_sm_1_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_1_t_9_cnt++;
						break;
					}
					break;
			case 2:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_0[IPFlushRepository::dnsFlushMap_f_0_sm_2_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_1[IPFlushRepository::dnsFlushMap_f_0_sm_2_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_2[IPFlushRepository::dnsFlushMap_f_0_sm_2_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_3[IPFlushRepository::dnsFlushMap_f_0_sm_2_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_4[IPFlushRepository::dnsFlushMap_f_0_sm_2_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_5[IPFlushRepository::dnsFlushMap_f_0_sm_2_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_6[IPFlushRepository::dnsFlushMap_f_0_sm_2_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_7[IPFlushRepository::dnsFlushMap_f_0_sm_2_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_8[IPFlushRepository::dnsFlushMap_f_0_sm_2_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_9[IPFlushRepository::dnsFlushMap_f_0_sm_2_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_2_t_9_cnt++;
						break;
					}
					break;

			case 3:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_0[IPFlushRepository::dnsFlushMap_f_0_sm_3_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_1[IPFlushRepository::dnsFlushMap_f_0_sm_3_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_2[IPFlushRepository::dnsFlushMap_f_0_sm_3_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_3[IPFlushRepository::dnsFlushMap_f_0_sm_3_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_4[IPFlushRepository::dnsFlushMap_f_0_sm_3_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_5[IPFlushRepository::dnsFlushMap_f_0_sm_3_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_6[IPFlushRepository::dnsFlushMap_f_0_sm_3_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_7[IPFlushRepository::dnsFlushMap_f_0_sm_3_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_8[IPFlushRepository::dnsFlushMap_f_0_sm_3_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_9[IPFlushRepository::dnsFlushMap_f_0_sm_3_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_3_t_9_cnt++;
						break;
					}
					break;

			case 4:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_0[IPFlushRepository::dnsFlushMap_f_0_sm_4_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_1[IPFlushRepository::dnsFlushMap_f_0_sm_4_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_2[IPFlushRepository::dnsFlushMap_f_0_sm_4_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_3[IPFlushRepository::dnsFlushMap_f_0_sm_4_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_4[IPFlushRepository::dnsFlushMap_f_0_sm_4_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_5[IPFlushRepository::dnsFlushMap_f_0_sm_4_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_6[IPFlushRepository::dnsFlushMap_f_0_sm_4_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_7[IPFlushRepository::dnsFlushMap_f_0_sm_4_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_8[IPFlushRepository::dnsFlushMap_f_0_sm_4_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_9[IPFlushRepository::dnsFlushMap_f_0_sm_4_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_0_sm_4_t_9_cnt++;
						break;
					}
					break;
	}
}

VOID IPSessionManager::storeDnsSession_f_1(int index, dnsSession *pDnsSession)
{

	switch(instanceId)
	{
			case 0:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_0[IPFlushRepository::dnsFlushMap_f_1_sm_0_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_1[IPFlushRepository::dnsFlushMap_f_1_sm_0_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_2[IPFlushRepository::dnsFlushMap_f_1_sm_0_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_3[IPFlushRepository::dnsFlushMap_f_1_sm_0_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_4[IPFlushRepository::dnsFlushMap_f_1_sm_0_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_5[IPFlushRepository::dnsFlushMap_f_1_sm_0_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_6[IPFlushRepository::dnsFlushMap_f_1_sm_0_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_7[IPFlushRepository::dnsFlushMap_f_1_sm_0_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_8[IPFlushRepository::dnsFlushMap_f_1_sm_0_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_9[IPFlushRepository::dnsFlushMap_f_1_sm_0_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_0_t_9_cnt++;
						break;
					}
					break;

			case 1:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_0[IPFlushRepository::dnsFlushMap_f_1_sm_1_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_1[IPFlushRepository::dnsFlushMap_f_1_sm_1_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_2[IPFlushRepository::dnsFlushMap_f_1_sm_1_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_3[IPFlushRepository::dnsFlushMap_f_1_sm_1_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_4[IPFlushRepository::dnsFlushMap_f_1_sm_1_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_5[IPFlushRepository::dnsFlushMap_f_1_sm_1_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_6[IPFlushRepository::dnsFlushMap_f_1_sm_1_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_7[IPFlushRepository::dnsFlushMap_f_1_sm_1_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_8[IPFlushRepository::dnsFlushMap_f_1_sm_1_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_9[IPFlushRepository::dnsFlushMap_f_1_sm_1_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_1_t_9_cnt++;
						break;
					}
					break;
			case 2:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_0[IPFlushRepository::dnsFlushMap_f_1_sm_2_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_1[IPFlushRepository::dnsFlushMap_f_1_sm_2_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_2[IPFlushRepository::dnsFlushMap_f_1_sm_2_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_3[IPFlushRepository::dnsFlushMap_f_1_sm_2_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_4[IPFlushRepository::dnsFlushMap_f_1_sm_2_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_5[IPFlushRepository::dnsFlushMap_f_1_sm_2_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_6[IPFlushRepository::dnsFlushMap_f_1_sm_2_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_7[IPFlushRepository::dnsFlushMap_f_1_sm_2_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_8[IPFlushRepository::dnsFlushMap_f_1_sm_2_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_9[IPFlushRepository::dnsFlushMap_f_1_sm_2_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_2_t_9_cnt++;
						break;
					}
					break;

			case 3:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_0[IPFlushRepository::dnsFlushMap_f_1_sm_3_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_1[IPFlushRepository::dnsFlushMap_f_1_sm_3_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_2[IPFlushRepository::dnsFlushMap_f_1_sm_3_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_3[IPFlushRepository::dnsFlushMap_f_1_sm_3_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_4[IPFlushRepository::dnsFlushMap_f_1_sm_3_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_5[IPFlushRepository::dnsFlushMap_f_1_sm_3_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_6[IPFlushRepository::dnsFlushMap_f_1_sm_3_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_7[IPFlushRepository::dnsFlushMap_f_1_sm_3_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_8[IPFlushRepository::dnsFlushMap_f_1_sm_3_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_9[IPFlushRepository::dnsFlushMap_f_1_sm_3_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_3_t_9_cnt++;
						break;
					}
					break;

			case 4:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_0[IPFlushRepository::dnsFlushMap_f_1_sm_4_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_1[IPFlushRepository::dnsFlushMap_f_1_sm_4_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_2[IPFlushRepository::dnsFlushMap_f_1_sm_4_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_3[IPFlushRepository::dnsFlushMap_f_1_sm_4_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_4[IPFlushRepository::dnsFlushMap_f_1_sm_4_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_5[IPFlushRepository::dnsFlushMap_f_1_sm_4_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_6[IPFlushRepository::dnsFlushMap_f_1_sm_4_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_7[IPFlushRepository::dnsFlushMap_f_1_sm_4_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_8[IPFlushRepository::dnsFlushMap_f_1_sm_4_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_9[IPFlushRepository::dnsFlushMap_f_1_sm_4_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_1_sm_4_t_9_cnt++;
						break;
					}
					break;
	}
}

VOID IPSessionManager::storeDnsSession_f_2(int index, dnsSession *pDnsSession)
{
	switch(instanceId)
	{
			case 0:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_0[IPFlushRepository::dnsFlushMap_f_2_sm_0_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_1[IPFlushRepository::dnsFlushMap_f_2_sm_0_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_2[IPFlushRepository::dnsFlushMap_f_2_sm_0_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_3[IPFlushRepository::dnsFlushMap_f_2_sm_0_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_4[IPFlushRepository::dnsFlushMap_f_2_sm_0_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_5[IPFlushRepository::dnsFlushMap_f_2_sm_0_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_6[IPFlushRepository::dnsFlushMap_f_2_sm_0_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_7[IPFlushRepository::dnsFlushMap_f_2_sm_0_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_8[IPFlushRepository::dnsFlushMap_f_2_sm_0_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_9[IPFlushRepository::dnsFlushMap_f_2_sm_0_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_0_t_9_cnt++;
						break;
					}
					break;

			case 1:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_0[IPFlushRepository::dnsFlushMap_f_2_sm_1_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_1[IPFlushRepository::dnsFlushMap_f_2_sm_1_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_2[IPFlushRepository::dnsFlushMap_f_2_sm_1_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_3[IPFlushRepository::dnsFlushMap_f_2_sm_1_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_4[IPFlushRepository::dnsFlushMap_f_2_sm_1_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_5[IPFlushRepository::dnsFlushMap_f_2_sm_1_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_6[IPFlushRepository::dnsFlushMap_f_2_sm_1_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_7[IPFlushRepository::dnsFlushMap_f_2_sm_1_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_8[IPFlushRepository::dnsFlushMap_f_2_sm_1_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_9[IPFlushRepository::dnsFlushMap_f_2_sm_1_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_1_t_9_cnt++;
						break;
					}
					break;
			case 2:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_0[IPFlushRepository::dnsFlushMap_f_2_sm_2_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_1[IPFlushRepository::dnsFlushMap_f_2_sm_2_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_2[IPFlushRepository::dnsFlushMap_f_2_sm_2_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_3[IPFlushRepository::dnsFlushMap_f_2_sm_2_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_4[IPFlushRepository::dnsFlushMap_f_2_sm_2_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_5[IPFlushRepository::dnsFlushMap_f_2_sm_2_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_6[IPFlushRepository::dnsFlushMap_f_2_sm_2_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_7[IPFlushRepository::dnsFlushMap_f_2_sm_2_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_8[IPFlushRepository::dnsFlushMap_f_2_sm_2_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_9[IPFlushRepository::dnsFlushMap_f_2_sm_2_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_2_t_9_cnt++;
						break;
					}
					break;

			case 3:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_0[IPFlushRepository::dnsFlushMap_f_2_sm_3_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_1[IPFlushRepository::dnsFlushMap_f_2_sm_3_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_2[IPFlushRepository::dnsFlushMap_f_2_sm_3_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_3[IPFlushRepository::dnsFlushMap_f_2_sm_3_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_4[IPFlushRepository::dnsFlushMap_f_2_sm_3_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_5[IPFlushRepository::dnsFlushMap_f_2_sm_3_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_6[IPFlushRepository::dnsFlushMap_f_2_sm_3_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_7[IPFlushRepository::dnsFlushMap_f_2_sm_3_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_8[IPFlushRepository::dnsFlushMap_f_2_sm_3_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_9[IPFlushRepository::dnsFlushMap_f_2_sm_3_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_3_t_9_cnt++;
						break;
					}
					break;

			case 4:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_0[IPFlushRepository::dnsFlushMap_f_2_sm_4_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_1[IPFlushRepository::dnsFlushMap_f_2_sm_4_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_2[IPFlushRepository::dnsFlushMap_f_2_sm_4_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_3[IPFlushRepository::dnsFlushMap_f_2_sm_4_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_4[IPFlushRepository::dnsFlushMap_f_2_sm_4_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_5[IPFlushRepository::dnsFlushMap_f_2_sm_4_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_6[IPFlushRepository::dnsFlushMap_f_2_sm_4_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_7[IPFlushRepository::dnsFlushMap_f_2_sm_4_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_8[IPFlushRepository::dnsFlushMap_f_2_sm_4_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_9[IPFlushRepository::dnsFlushMap_f_2_sm_4_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_2_sm_4_t_9_cnt++;
						break;
					}
					break;
	}
}

VOID IPSessionManager::storeDnsSession_f_3(int index, dnsSession *pDnsSession)
{
	switch(instanceId)
	{
			case 0:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_0[IPFlushRepository::dnsFlushMap_f_3_sm_0_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_1[IPFlushRepository::dnsFlushMap_f_3_sm_0_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_2[IPFlushRepository::dnsFlushMap_f_3_sm_0_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_3[IPFlushRepository::dnsFlushMap_f_3_sm_0_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_4[IPFlushRepository::dnsFlushMap_f_3_sm_0_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_5[IPFlushRepository::dnsFlushMap_f_3_sm_0_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_6[IPFlushRepository::dnsFlushMap_f_3_sm_0_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_7[IPFlushRepository::dnsFlushMap_f_3_sm_0_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_8[IPFlushRepository::dnsFlushMap_f_3_sm_0_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_9[IPFlushRepository::dnsFlushMap_f_3_sm_0_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_0_t_9_cnt++;
						break;
					}
					break;

			case 1:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_0[IPFlushRepository::dnsFlushMap_f_3_sm_1_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_1[IPFlushRepository::dnsFlushMap_f_3_sm_1_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_2[IPFlushRepository::dnsFlushMap_f_3_sm_1_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_3[IPFlushRepository::dnsFlushMap_f_3_sm_1_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_4[IPFlushRepository::dnsFlushMap_f_3_sm_1_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_5[IPFlushRepository::dnsFlushMap_f_3_sm_1_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_6[IPFlushRepository::dnsFlushMap_f_3_sm_1_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_7[IPFlushRepository::dnsFlushMap_f_3_sm_1_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_8[IPFlushRepository::dnsFlushMap_f_3_sm_1_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_9[IPFlushRepository::dnsFlushMap_f_3_sm_1_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_1_t_9_cnt++;
						break;
					}
					break;
			case 2:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_0[IPFlushRepository::dnsFlushMap_f_3_sm_2_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_1[IPFlushRepository::dnsFlushMap_f_3_sm_2_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_2[IPFlushRepository::dnsFlushMap_f_3_sm_2_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_3[IPFlushRepository::dnsFlushMap_f_3_sm_2_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_4[IPFlushRepository::dnsFlushMap_f_3_sm_2_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_5[IPFlushRepository::dnsFlushMap_f_3_sm_2_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_6[IPFlushRepository::dnsFlushMap_f_3_sm_2_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_7[IPFlushRepository::dnsFlushMap_f_3_sm_2_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_8[IPFlushRepository::dnsFlushMap_f_3_sm_2_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_9[IPFlushRepository::dnsFlushMap_f_3_sm_2_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_2_t_9_cnt++;
						break;
					}
					break;

			case 3:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_0[IPFlushRepository::dnsFlushMap_f_3_sm_3_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_1[IPFlushRepository::dnsFlushMap_f_3_sm_3_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_2[IPFlushRepository::dnsFlushMap_f_3_sm_3_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_3[IPFlushRepository::dnsFlushMap_f_3_sm_3_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_4[IPFlushRepository::dnsFlushMap_f_3_sm_3_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_5[IPFlushRepository::dnsFlushMap_f_3_sm_3_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_6[IPFlushRepository::dnsFlushMap_f_3_sm_3_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_7[IPFlushRepository::dnsFlushMap_f_3_sm_3_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_8[IPFlushRepository::dnsFlushMap_f_3_sm_3_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_9[IPFlushRepository::dnsFlushMap_f_3_sm_3_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_3_t_9_cnt++;
						break;
					}
					break;

			case 4:
					switch(index)
					{
					case 0:
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_0[IPFlushRepository::dnsFlushMap_f_3_sm_4_t_0_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_0_cnt++;
						break;
					case 1:
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_1[IPFlushRepository::dnsFlushMap_f_3_sm_4_t_1_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_1_cnt++;
						break;
					case 2:
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_2[IPFlushRepository::dnsFlushMap_f_3_sm_4_t_2_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_2_cnt++;
						break;
					case 3:
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_3[IPFlushRepository::dnsFlushMap_f_3_sm_4_t_3_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_3_cnt++;
						break;
					case 4:
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_4[IPFlushRepository::dnsFlushMap_f_3_sm_4_t_4_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_4_cnt++;
						break;
					case 5:
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_5[IPFlushRepository::dnsFlushMap_f_3_sm_4_t_5_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_5_cnt++;
						break;
					case 6:
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_6[IPFlushRepository::dnsFlushMap_f_3_sm_4_t_6_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_6_cnt++;
						break;
					case 7:
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_7[IPFlushRepository::dnsFlushMap_f_3_sm_4_t_7_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_7_cnt++;
						break;
					case 8:
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_8[IPFlushRepository::dnsFlushMap_f_3_sm_4_t_8_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_8_cnt++;
						break;
					case 9:
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_9[IPFlushRepository::dnsFlushMap_f_3_sm_4_t_9_cnt].copy(pDnsSession);
						IPFlushRepository::dnsFlushMap_f_3_sm_4_t_9_cnt++;
						break;
					}
					break;
	}
}


VOID IPSessionManager::flushDnsSession(dnsSession *pDnsSession)
{
	long epochSecNow = getCurrentEpochSeconds();

//	int index = (((epochSecNow % 100) /10)  % IPGlobal::FLUSHER_TIMEINDEX) + 1;
//	if(index >= IPGlobal::FLUSHER_TIMEINDEX) index = index - IPGlobal::FLUSHER_TIMEINDEX;

	int idx = WRITE_TIME_INDEX(epochSecNow);

	pDnsSession->FlushTimeEpochMicroSec = (epochSecNow * 1000000);

	storeDnsSession(idx, pDnsSession);

}


VOID IPSessionManager::eraseIpSession(ipSession *pIpSession)
{
	string sKey = std::string(pIpSession->sessionKey);
	ipSessionMap[pIpSession->mapIndex][sKey].packTimeMap.clear();
	ipSessionMap[pIpSession->mapIndex].erase(sKey);
}


int IPSessionManager::getSessionKey(MPacket *msgObj, char *key)
{
	key[0] = 0;
	int index = 0;
//	uint128_t	sessionKey;

//	if(msgObj->ipSourceAddr < IPGlobal::IPV4_MULTIPLIER_OCTET_1 || msgObj->ipDestAddr < IPGlobal::IPV4_MULTIPLIER_OCTET_1){
//		printf("INVALID IP ADDRESS IN MESSAGE :: %u |%u\n",msgObj->ipSourceAddr,msgObj->ipDestAddr);
//	}

	switch(msgObj->ipProtocol)
	{
		case PACKET_IPPROTO_TCP:
		case PACKET_IPPROTO_UDP:
				if(msgObj->dirUserNetwork) {	// If Direction is UP -> True DN -> False
					sprintf(key,"%d-%u-%d-%u-%d", msgObj->ipProtocol, msgObj->ipSourceAddr, msgObj->protoSourcePort, msgObj->ipDestAddr, msgObj->protoDestPort);
//					sprintf(key,"%d%lu%lu", (1000 + msgObj->ipProtocol), msgObj->ipSessionKeySrc, msgObj->ipSessionKeyDest);

//					strcpy(key, (const char *)msgObj->ipProtocol);
//					strcat(key, msgObj->sourceAddr);
//					strcat(key, msgObj->destAddr);

//					printf(" %d| %u| %d| %u| %d| Key :%s\n", msgObj->ipProtocol,msgObj->ipSourceAddr, msgObj->protoSourcePort,
//													msgObj->ipDestAddr, msgObj->protoDestPort, key);

					index = (int) (msgObj->ipSourceAddr % IP_SESSION_ARRAY_SIZE);
				}else{
					sprintf(key,"%d-%u-%d-%u-%d", msgObj->ipProtocol, msgObj->ipDestAddr, msgObj->protoDestPort, msgObj->ipSourceAddr, msgObj->protoSourcePort);

//					sprintf(key,"%d%lu%lu", (1000 + msgObj->ipProtocol), msgObj->ipSessionKeyDest, msgObj->ipSessionKeySrc);

//					strcpy(key, (const char *)msgObj->ipProtocol);
//					strcat(key, msgObj->destAddr);
//					strcat(key, msgObj->sourceAddr);

//					printf(" %d| %u| %d| %u| %d| Key :%s\n", msgObj->ipProtocol,msgObj->ipDestAddr, msgObj->protoDestPort,
//													msgObj->ipSourceAddr, msgObj->protoSourcePort, key);
//
					index = (int) (msgObj->ipDestAddr % IP_SESSION_ARRAY_SIZE);
				}
				break;

		default:
//				if(msgObj->dirUserNetwork) {	// If Direction is UP -> True DN -> False
//					sprintf(key,"1%03d%010u%010u1",msgObj->ipProtocol, msgObj->ipSourceAddr, msgObj->ipDestAddr);
//					index = (int) (msgObj->ipSourceAddr % IP_SESSION_ARRAY_SIZE);
//				}else{
//					sprintf(key,"1%03d%010u%010u1",msgObj->ipProtocol, msgObj->ipDestAddr, msgObj->ipSourceAddr);
//					index = (int) (msgObj->ipDestAddr % IP_SESSION_ARRAY_SIZE);
//				}
				break;
	}
	return index;
}


VOID IPSessionManager::countFinOnlySessions()
{
	switch(instanceId)
	{
		case 0:
			IPStats::ip_session_fin_only_sm_0_cnt++;
			break;
		case 1:
			IPStats::ip_session_fin_only_sm_1_cnt++;
			break;
		case 2:
			IPStats::ip_session_fin_only_sm_2_cnt++;
			break;
		case 3:
			IPStats::ip_session_fin_only_sm_3_cnt++;
			break;
		case 4:
			IPStats::ip_session_fin_only_sm_4_cnt++;
			break;
	}
}

VOID IPSessionManager::resetFinOnlySessionsCount()
{
	switch(instanceId)
	{
		case 0:
			IPStats::ip_session_fin_only_sm_0_cnt = 0;
			break;
		case 1:
			IPStats::ip_session_fin_only_sm_1_cnt = 0;
			break;
		case 2:
			IPStats::ip_session_fin_only_sm_2_cnt = 0;
			break;
		case 3:
			IPStats::ip_session_fin_only_sm_3_cnt = 0;
			break;
		case 4:
			IPStats::ip_session_fin_only_sm_4_cnt = 0;
			break;
	}
}


VOID IPSessionManager::cleanTimedOutSessionsIP()
{
		switch(instanceId)
		{
			case 0:
				{
					IPStats::ip_session_scanned_sm_0_cnt = 0;
					IPStats::ip_session_cleaned_tcp_sm_0_cnt = 0;
					IPStats::ip_session_cleaned_udp_sm_0_cnt = 0;

					for(int i = 0; i < IP_SESSION_ARRAY_SIZE; i++)
					{
						for(auto elem : ipSessionMap[i]) {
							if(ipSessionCleanUpMap_cnt >= IPGlobal::IP_SESSION_CLEAN_UP_BATCH_LIMIT) break;
							IPStats::ip_session_scanned_sm_0_cnt++;
							processCleanTimedOutSessionsIP(0,i,&elem.second);
						}
					}
				}
				break;

			case 1:
				{
					IPStats::ip_session_scanned_sm_1_cnt = 0;
					IPStats::ip_session_cleaned_tcp_sm_1_cnt = 0;
					IPStats::ip_session_cleaned_udp_sm_1_cnt = 0;

					for(int i = 0; i < IP_SESSION_ARRAY_SIZE; i++)
					{
						for(auto elem : ipSessionMap[i]) {
							if(ipSessionCleanUpMap_cnt >= IPGlobal::IP_SESSION_CLEAN_UP_BATCH_LIMIT) break;
							IPStats::ip_session_scanned_sm_1_cnt++;
							processCleanTimedOutSessionsIP(0,i,&elem.second);
						}
					}
				}
				break;

			case 2:
				{
					IPStats::ip_session_scanned_sm_2_cnt = 0;
					IPStats::ip_session_cleaned_tcp_sm_2_cnt = 0;
					IPStats::ip_session_cleaned_udp_sm_2_cnt = 0;

					for(int i = 0; i < IP_SESSION_ARRAY_SIZE; i++)
					{
						for(auto elem : ipSessionMap[i]) {
							if(ipSessionCleanUpMap_cnt >= IPGlobal::IP_SESSION_CLEAN_UP_BATCH_LIMIT) break;
							IPStats::ip_session_scanned_sm_2_cnt++;
							processCleanTimedOutSessionsIP(0,i,&elem.second);
						}
					}
				}
				break;

			case 3:
				{
					IPStats::ip_session_scanned_sm_3_cnt = 0;
					IPStats::ip_session_cleaned_tcp_sm_3_cnt = 0;
					IPStats::ip_session_cleaned_udp_sm_3_cnt = 0;

					for(int i = 0; i < IP_SESSION_ARRAY_SIZE; i++)
					{
						for(auto elem : ipSessionMap[i]) {
							if(ipSessionCleanUpMap_cnt >= IPGlobal::IP_SESSION_CLEAN_UP_BATCH_LIMIT) break;
							IPStats::ip_session_scanned_sm_3_cnt++;
							processCleanTimedOutSessionsIP(0,i,&elem.second);
						}
					}

				}
				break;

			case 4:
				{
					IPStats::ip_session_scanned_sm_4_cnt = 0;
					IPStats::ip_session_cleaned_tcp_sm_4_cnt = 0;
					IPStats::ip_session_cleaned_udp_sm_4_cnt = 0;

					for(int i = 0; i < IP_SESSION_ARRAY_SIZE; i++)
					{
						for(auto elem : ipSessionMap[i]) {
							if(ipSessionCleanUpMap_cnt >= IPGlobal::IP_SESSION_CLEAN_UP_BATCH_LIMIT) break;
							IPStats::ip_session_scanned_sm_4_cnt++;
							processCleanTimedOutSessionsIP(0,i,&elem.second);
						}
					}
				}
				break;
		}

		//Delete the Repo
		eraseCleanedSessions();
}

//VOID IPSessionManager::eraseCleanedSessions(){
//
//	std::string key = "";
//	int index = 0;
//
//	for(int i=0; i<ipSessionCleanUpMap_cnt; i++){
//		 key = ipSessionCleanUpMap[i].key;
//		 index = ipSessionCleanUpMap[i].index;
//
//		 ipSessionMap[index].erase(key);
//	}
//	ipSessionCleanUpMap.clear();
//	ipSessionCleanUpMap_cnt = 0;
//}

VOID IPSessionManager::eraseCleanedSessions(){

	std::string key = "";
	int index = 0;

	for(int i=0; i<ipSessionCleanUpMap_cnt; i++){
		 key = ipSessionCleanUpMap[i].key;
		 index = ipSessionCleanUpMap[i].index;

		 ipSessionMap[index].erase(key);
	}
	ipSessionCleanUpMap.clear();
	ipSessionCleanUpMap_cnt = 0;
}

VOID IPSessionManager::processCleanTimedOutSessionsIP(int mapId, int mapArrId, ipSession *pIpSession)
{
	uint64_t curEpochSec = (uint64_t) getCurrentEpochSeconds();

//	printf("[%d] curEpochSec [%u] pIpSession->pckLastTimeEpochSec [%u] diff [%d]\n", instanceId, curEpochSec, pIpSession->pckLastTimeEpochSec, curEpochSec - pIpSession->pckLastTimeEpochSec);

	if((curEpochSec - pIpSession->pckLastTimeEpochSec) > GContainer::config->gtpConfig->GN_GTPU_IDLE_SESSION_TIMEOUT_IN_SEC) {
		if(pIpSession->protocolType == PACKET_IPPROTO_TCP) {
//			printf("Got TCP Data to be cleaned...\n");
			switch(pIpSession->state)
			{
				case CONNECTED:
					if(pIpSession->payloadPacket > 0) {
						pIpSession->causeCode = SYSTEM_CLEANUP_TCP_CONN_DATA;
					}
					else {
						pIpSession->causeCode = SYSTEM_CLEANUP_TCP_CONN_NODATA;
					}
					break;

				case SYN_RCV:
				case SYN_ACK_RCV:
					if(pIpSession->payloadPacket <= 0) {
						pIpSession->causeCode = SYSTEM_CLEANUP_TCP_NOCONN_NODATA;
					}
					else {
						pIpSession->causeCode = SYSTEM_CLEANUP_TCP_NOCONN_DATA;
					}
					break;

				case FIN_RCV:
//					Don't change the cause code
					break;

				default:
					if(pIpSession->payloadPacket <= 0) {
						pIpSession->causeCode = SYSTEM_CLEANUP_TCP_NOCONN_NODATA;
					}else{
						pIpSession->causeCode = SYSTEM_CLEANUP_TCP_NOCONN_DATA;
					}
					break;
			}
		}
		else if (pIpSession->protocolType == PACKET_IPPROTO_UDP)
		{
			pIpSession->causeCode = SYSTEM_CLEANUP_UDP_DATA;
		}

		// The the slice counter, if slicing done already, increment the counter by 1
		if(pIpSession->sliceCounter >= 1)
			pIpSession->sliceCounter += 1;

		switch(instanceId)
		{

			case 0:
			{
				if(pIpSession->protocolType == PACKET_IPPROTO_TCP)
					IPStats::ip_session_cleaned_tcp_sm_0_cnt++;
				else if(pIpSession->protocolType == PACKET_IPPROTO_UDP)
					IPStats::ip_session_cleaned_udp_sm_0_cnt++;
				break;
			}
			case 1:
			{
//				printf("Going to Increment Counter Instance [%d]...[%lu]\n", instanceId, IPStats::ip_session_cleaned_tcp_sm_0_cnt);
				if(pIpSession->protocolType == PACKET_IPPROTO_TCP)
					IPStats::ip_session_cleaned_tcp_sm_1_cnt++;
				else if(pIpSession->protocolType == PACKET_IPPROTO_UDP)
					IPStats::ip_session_cleaned_udp_sm_1_cnt++;
				break;
			}
			case 2:
			{
				if(pIpSession->protocolType == PACKET_IPPROTO_TCP)
					IPStats::ip_session_cleaned_tcp_sm_2_cnt++;
				else if(pIpSession->protocolType == PACKET_IPPROTO_UDP)
					IPStats::ip_session_cleaned_udp_sm_2_cnt++;
				break;
			}
			case 3:
			{
				if(pIpSession->protocolType == PACKET_IPPROTO_TCP)
					IPStats::ip_session_cleaned_tcp_sm_3_cnt++;
				else if(pIpSession->protocolType == PACKET_IPPROTO_UDP)
					IPStats::ip_session_cleaned_udp_sm_3_cnt++;
				break;
			}
			case 4:
			{
				if(pIpSession->protocolType == PACKET_IPPROTO_TCP)
					IPStats::ip_session_cleaned_tcp_sm_4_cnt++;
				else if(pIpSession->protocolType == PACKET_IPPROTO_UDP)
					IPStats::ip_session_cleaned_udp_sm_4_cnt++;
				break;
			}
		}

		ipSessionCleanUpMap[ipSessionCleanUpMap_cnt].key = std::string(pIpSession->sessionKey);
		ipSessionCleanUpMap[ipSessionCleanUpMap_cnt].index = pIpSession->mapIndex;
//		ipSessionCleanUpMap[ipSessionCleanUpMap_cnt] = std::string(pIpSession->sessionKey);
		ipSessionCleanUpMap_cnt++;

		bool ignoreSessionFlush = false;
//		if(ipSessionCleanUpMap_cnt >= IPGlobal::IP_SESSION_CLEAN_UP_BATCH_LIMIT * .6)
//		{
//			if(pIpSession->protocolType == PACKET_IPPROTO_UDP && pIpSession->frameCount < 3)
//				ignoreSessionFlush = true;
//		}
		flushIpSession(7,pIpSession, false, ignoreSessionFlush);
	}
}

VOID IPSessionManager::cleanTimedOutSessionsDns()
{
	uint128_t curEpochNanoSec = getCurrentEpochMicroSeconds() * 1000;
	uint128_t IdleTimeNanoSec = GContainer::config->gtpConfig->GN_GTPU_IDLE_SESSION_TIMEOUT_IN_SEC * 1000000000;

	switch(instanceId)
	{
		case 0:
			IPStats::dns_session_sm_0_cnt = dnsSessionMap.size();
			break;
		case 1:
			IPStats::dns_session_sm_1_cnt = dnsSessionMap.size();
			break;
		case 2:
			IPStats::dns_session_sm_2_cnt = dnsSessionMap.size();
			break;
		case 3:
			IPStats::dns_session_sm_3_cnt = dnsSessionMap.size();
			break;
		case 4:
			IPStats::dns_session_sm_4_cnt = dnsSessionMap.size();
			break;
	}

	for(auto elem : dnsSessionMap) {
			dnsSession *pDnsSession = &elem.second;

			if((curEpochNanoSec - pDnsSession->queryStartEpochNanoSec) > IdleTimeNanoSec ||
					(curEpochNanoSec - pDnsSession->queryEndEpochNanoSec) > IdleTimeNanoSec)
			{
				if(pDnsSession->queryStartEpochNanoSec == 0)
					pDnsSession->queryStartEpochNanoSec = curEpochNanoSec;

				if(pDnsSession->queryEndEpochNanoSec == 0)
					pDnsSession->queryEndEpochNanoSec = curEpochNanoSec;

//				pDnsSession->resolveTimeNanoSec = curEpochNanoSec - pDnsSession->queryStartEpochNanoSec;
				pDnsSession->resolveTimeNanoSec = 0;
				pDnsSession->causeCode = SYSTEM_CLEANUP_DNS_QUERY;
				strcpy(pDnsSession->address, "NULL");
				pDnsSession->errorCode = SYSTEM_CLEANUP_DNS_QUERY;
				strcpy(pDnsSession->errorDesc, "No Response");

				//uint32_t mapIndex = pDnsSession->transactionId % DNS_SESSION_ARRAY_SIZE;
				flushDnsSession(pDnsSession);
				dnsSessionCleanUpMap[dnsSessionCleanUpMap_cnt] = pDnsSession->transactionId;
				dnsSessionCleanUpMap_cnt++;
			}
		}

	for(int i=0; i<dnsSessionCleanUpMap_cnt; i++){
		dnsSessionMap.erase(dnsSessionCleanUpMap[i]);
	}
	dnsSessionCleanUpMap.clear();
	dnsSessionCleanUpMap_cnt = 0;

}

VOID IPSessionManager::cleanDnsDatabaseMap()
{
	uint64_t curEpochSec = getCurrentEpochSeconds();

	int totalCleanCnt = 0;

	dnsDatabaseCleanMap.clear();
	dnsDatabaseCleanMap_cnt = 0;

	for(auto elem : DNSGlobal::dnsDatabaseMap_0)
	{
		dnsUrl *pDnsUrl = &elem.second;
		if((curEpochSec - pDnsUrl->pckLastTimeEpcohSec) > IPGlobal::IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC)
		{
			dnsDatabaseCleanMap[dnsDatabaseCleanMap_cnt] = elem.first;
			dnsDatabaseCleanMap_cnt++;
		}
	}
	totalCleanCnt += dnsDatabaseCleanMap_cnt;

	for(int i=0; i<dnsDatabaseCleanMap_cnt; i++){
		DNSGlobal::dnsDatabaseMap_0.erase(dnsDatabaseCleanMap[i]);
	}
	dnsDatabaseCleanMap.clear();
	dnsDatabaseCleanMap_cnt = 0;


	for(auto elem : DNSGlobal::dnsDatabaseMap_1)
	{
		dnsUrl *pDnsUrl = &elem.second;
		if((curEpochSec - pDnsUrl->pckLastTimeEpcohSec) > IPGlobal::IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC)
		{
			dnsDatabaseCleanMap[dnsDatabaseCleanMap_cnt] = elem.first;
			dnsDatabaseCleanMap_cnt++;
		}
	}
	totalCleanCnt += dnsDatabaseCleanMap_cnt;

	for(int i=0; i<dnsDatabaseCleanMap_cnt; i++){
		DNSGlobal::dnsDatabaseMap_1.erase(dnsDatabaseCleanMap[i]);
	}

	dnsDatabaseCleanMap.clear();
	dnsDatabaseCleanMap_cnt = 0;


	for(auto elem : DNSGlobal::dnsDatabaseMap_2)
	{
		dnsUrl *pDnsUrl = &elem.second;
		if((curEpochSec - pDnsUrl->pckLastTimeEpcohSec) > IPGlobal::IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC)
		{
			dnsDatabaseCleanMap[dnsDatabaseCleanMap_cnt] = elem.first;
			dnsDatabaseCleanMap_cnt++;
		}
	}
	totalCleanCnt += dnsDatabaseCleanMap_cnt;

	for(int i=0; i<dnsDatabaseCleanMap_cnt; i++){
		DNSGlobal::dnsDatabaseMap_2.erase(dnsDatabaseCleanMap[i]);
	}
	dnsDatabaseCleanMap.clear();
	dnsDatabaseCleanMap_cnt = 0;


	for(auto elem : DNSGlobal::dnsDatabaseMap_3)
	{
		dnsUrl *pDnsUrl = &elem.second;
		if((curEpochSec - pDnsUrl->pckLastTimeEpcohSec) > IPGlobal::IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC)
		{
			dnsDatabaseCleanMap[dnsDatabaseCleanMap_cnt] = elem.first;
			dnsDatabaseCleanMap_cnt++;
		}
	}
	totalCleanCnt += dnsDatabaseCleanMap_cnt;

	for(int i=0; i<dnsDatabaseCleanMap_cnt; i++){
		DNSGlobal::dnsDatabaseMap_3.erase(dnsDatabaseCleanMap[i]);
	}
	dnsDatabaseCleanMap.clear();
	dnsDatabaseCleanMap_cnt = 0;


	for(auto elem : DNSGlobal::dnsDatabaseMap_4)
	{
		dnsUrl *pDnsUrl = &elem.second;
		if((curEpochSec - pDnsUrl->pckLastTimeEpcohSec) > IPGlobal::IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC)
		{
			dnsDatabaseCleanMap[dnsDatabaseCleanMap_cnt] = elem.first;
			dnsDatabaseCleanMap_cnt++;
		}
	}
	totalCleanCnt += dnsDatabaseCleanMap_cnt;

	for(int i=0; i<dnsDatabaseCleanMap_cnt; i++){
		DNSGlobal::dnsDatabaseMap_4.erase(dnsDatabaseCleanMap[i]);
	}
	dnsDatabaseCleanMap.clear();
	dnsDatabaseCleanMap_cnt = 0;


	for(auto elem : DNSGlobal::dnsDatabaseMap_5)
	{
		dnsUrl *pDnsUrl = &elem.second;
		if((curEpochSec - pDnsUrl->pckLastTimeEpcohSec) > IPGlobal::IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC)
		{
			dnsDatabaseCleanMap[dnsDatabaseCleanMap_cnt] = elem.first;
			dnsDatabaseCleanMap_cnt++;
		}
	}
	totalCleanCnt += dnsDatabaseCleanMap_cnt;

	for(int i=0; i<dnsDatabaseCleanMap_cnt; i++){
		DNSGlobal::dnsDatabaseMap_5.erase(dnsDatabaseCleanMap[i]);
	}
	dnsDatabaseCleanMap.clear();
	dnsDatabaseCleanMap_cnt = 0;


	for(auto elem : DNSGlobal::dnsDatabaseMap_6)
	{
		dnsUrl *pDnsUrl = &elem.second;
		if((curEpochSec - pDnsUrl->pckLastTimeEpcohSec) > IPGlobal::IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC)
		{
			dnsDatabaseCleanMap[dnsDatabaseCleanMap_cnt] = elem.first;
			dnsDatabaseCleanMap_cnt++;
		}
	}
	totalCleanCnt += dnsDatabaseCleanMap_cnt;

	for(int i=0; i<dnsDatabaseCleanMap_cnt; i++){
		DNSGlobal::dnsDatabaseMap_6.erase(dnsDatabaseCleanMap[i]);
	}
	dnsDatabaseCleanMap.clear();
	dnsDatabaseCleanMap_cnt = 0;


	for(auto elem : DNSGlobal::dnsDatabaseMap_7)
	{
		dnsUrl *pDnsUrl = &elem.second;
		if((curEpochSec - pDnsUrl->pckLastTimeEpcohSec) > IPGlobal::IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC)
		{
			dnsDatabaseCleanMap[dnsDatabaseCleanMap_cnt] = elem.first;
			dnsDatabaseCleanMap_cnt++;
		}
	}
	totalCleanCnt += dnsDatabaseCleanMap_cnt;

	for(int i=0; i<dnsDatabaseCleanMap_cnt; i++){
		DNSGlobal::dnsDatabaseMap_7.erase(dnsDatabaseCleanMap[i]);
	}
	dnsDatabaseCleanMap.clear();
	dnsDatabaseCleanMap_cnt = 0;


	for(auto elem : DNSGlobal::dnsDatabaseMap_8)
	{
		dnsUrl *pDnsUrl = &elem.second;
		if((curEpochSec - pDnsUrl->pckLastTimeEpcohSec) > IPGlobal::IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC)
		{
			dnsDatabaseCleanMap[dnsDatabaseCleanMap_cnt] = elem.first;
			dnsDatabaseCleanMap_cnt++;
		}
	}
	totalCleanCnt += dnsDatabaseCleanMap_cnt;

	for(int i=0; i<dnsDatabaseCleanMap_cnt; i++){
		DNSGlobal::dnsDatabaseMap_8.erase(dnsDatabaseCleanMap[i]);
	}
	dnsDatabaseCleanMap.clear();
	dnsDatabaseCleanMap_cnt = 0;


	for(auto elem : DNSGlobal::dnsDatabaseMap_9)
	{
		dnsUrl *pDnsUrl = &elem.second;
		if((curEpochSec - pDnsUrl->pckLastTimeEpcohSec) > IPGlobal::IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC)
		{
			dnsDatabaseCleanMap[dnsDatabaseCleanMap_cnt] = elem.first;
			dnsDatabaseCleanMap_cnt++;
		}
	}
	totalCleanCnt += dnsDatabaseCleanMap_cnt;

	for(int i=0; i<dnsDatabaseCleanMap_cnt; i++){
		DNSGlobal::dnsDatabaseMap_9.erase(dnsDatabaseCleanMap[i]);
	}
	dnsDatabaseCleanMap.clear();
	dnsDatabaseCleanMap_cnt = 0;

	TheLog_nc_v2(Log::Info, name(),"  IPSessionManager [%d] Cleaned [%d] DNS Database Map entries",instanceId,totalCleanCnt);

}

VOID IPSessionManager::dumpDnsLookupMap()
{
	string filePath = GContainer::config->DATA_DIR + "dnsdata.csv";

	printf("IPSessionManager [%d] Dumping DNS Lookup Store to file [%s]...\n",instanceId, filePath.c_str());
	TheLog_nc_v2(Log::Info, name()," [%d] Dumping DNS Lookup Store to file [%s]...",instanceId,filePath.c_str());

	ofstream fileHandler;

	fileHandler.open(filePath.c_str(), ios :: out);

	if(fileHandler.fail())
	{
		printf("IPSessionManager [%d] Error in Dumping DNS Lookup Store File : %s\n",instanceId, filePath.c_str());
		TheLog_nc_v2(Log::Warn, name()," [%d] Error in Dumping DNS Lookup Store to file [%s]...",instanceId,filePath.c_str());
	}
	else
	{
		for(auto elem : DNSGlobal::dnsLookUpMap_0) {
			fileHandler << elem.first << "," << elem.second << endl;
		}
		for(auto elem : DNSGlobal::dnsLookUpMap_1) {
			fileHandler << elem.first << "," << elem.second << endl;
		}
		for(auto elem : DNSGlobal::dnsLookUpMap_2) {
			fileHandler << elem.first << "," << elem.second << endl;
		}
		for(auto elem : DNSGlobal::dnsLookUpMap_3) {
			fileHandler << elem.first << "," << elem.second << endl;
		}
		for(auto elem : DNSGlobal::dnsLookUpMap_4) {
			fileHandler << elem.first << "," << elem.second << endl;
		}
		for(auto elem : DNSGlobal::dnsLookUpMap_5) {
			fileHandler << elem.first << "," << elem.second << endl;
		}
		for(auto elem : DNSGlobal::dnsLookUpMap_6) {
			fileHandler << elem.first << "," << elem.second << endl;
		}
		for(auto elem : DNSGlobal::dnsLookUpMap_7) {
			fileHandler << elem.first << "," << elem.second << endl;
		}
		for(auto elem : DNSGlobal::dnsLookUpMap_8) {
			fileHandler << elem.first << "," << elem.second << endl;
		}
		for(auto elem : DNSGlobal::dnsLookUpMap_9) {
			fileHandler << elem.first << "," << elem.second << endl;
		}

		fileHandler.close();
		printf("IPSessionManager [%d] Dumping DNS Lookup Store to file [%s]...Completed\n",instanceId,filePath.c_str());
		TheLog_nc_v2(Log::Info, name()," [%d] Dumping DNS Lookup Store to file [%s]...Completed",instanceId,filePath.c_str());
	}

}


VOID IPSessionManager::loadDnsLookupMap()
{
	string filePath = GContainer::config->DATA_DIR + "dnsdata.csv";

	std::string line;
	std::string url;
	uint32_t ip;
	int lineCnt = 0, loadedCnt = 0;
	char * 		pch;

	ifstream fp;

	fp.open(filePath.c_str());

	if(fp.fail())
	{
		printf("IPSessionManager [%d] Error in Loading DNS Lookup file [%s]\n", instanceId, filePath.c_str());
		TheLog_nc_v2(Log::Warn, name()," [%d] Error in Loading DNS Lookup file [%s]", instanceId, filePath.c_str());
	}
	else
	{
		while(!fp.eof())
		{
			getline(fp,line);
			//TheLog_nc_v2(Log::Debug, name,"[%d] Line :: [%s]",lineCnt, line.c_str());
			if(!line.empty() && line.length() > 0)
			{
				lineCnt++;
				pch = strtok ((char *)line.c_str(), ",");
				ip = atol(pch);

				pch = strtok (NULL, ",");
				url = std::string(pch);

				if(ip > 0)
				{
					loadedCnt++;
					int index = ip % 10;
					switch(index)
					{
						case 0:
							DNSGlobal::dnsLookUpMap_0[ip] = url;
							break;
						case 1:
							DNSGlobal::dnsLookUpMap_1[ip] = url;
							break;
						case 2:
							DNSGlobal::dnsLookUpMap_2[ip] = url;
							break;
						case 3:
							DNSGlobal::dnsLookUpMap_3[ip] = url;
							break;
						case 4:
							DNSGlobal::dnsLookUpMap_4[ip] = url;
							break;
						case 5:
							DNSGlobal::dnsLookUpMap_5[ip] = url;
							break;
						case 6:
							DNSGlobal::dnsLookUpMap_6[ip] = url;
							break;
						case 7:
							DNSGlobal::dnsLookUpMap_7[ip] = url;
							break;
						case 8:
							DNSGlobal::dnsLookUpMap_8[ip] = url;
							break;
						case 9:
							DNSGlobal::dnsLookUpMap_9[ip] = url;
							break;
					}
				}
			}
		}

		fp.close();
	}

	printf("IPSessionManager [%d] Loaded [%d] records in Dns Lookup Map from file [%s] reading [%d] lines\n",instanceId, loadedCnt, filePath.c_str(), lineCnt);
	TheLog_nc_v4(Log::Info, name()," [%d] Loaded [%d] records in Dns Lookup Map from file [%s] reading [%d] lines",instanceId, loadedCnt, filePath.c_str(), lineCnt);
}


VOID IPSessionManager::getDnsLookUpMapSize()
{
	IPStats::dns_lookup_map_size = 0;
	IPStats::dns_lookup_map_size += DNSGlobal::dnsLookUpMap_0.size();
	IPStats::dns_lookup_map_size += DNSGlobal::dnsLookUpMap_1.size();
	IPStats::dns_lookup_map_size += DNSGlobal::dnsLookUpMap_2.size();
	IPStats::dns_lookup_map_size += DNSGlobal::dnsLookUpMap_3.size();
	IPStats::dns_lookup_map_size += DNSGlobal::dnsLookUpMap_4.size();
	IPStats::dns_lookup_map_size += DNSGlobal::dnsLookUpMap_5.size();
	IPStats::dns_lookup_map_size += DNSGlobal::dnsLookUpMap_6.size();
	IPStats::dns_lookup_map_size += DNSGlobal::dnsLookUpMap_7.size();
	IPStats::dns_lookup_map_size += DNSGlobal::dnsLookUpMap_8.size();
	IPStats::dns_lookup_map_size += DNSGlobal::dnsLookUpMap_9.size();

	TheLog_nc_v5(Log::Info, name(),"  DnsLookUpMap size [%d] [%d] [%d] [%d] [%d]", DNSGlobal::dnsLookUpMap_0.size(), DNSGlobal::dnsLookUpMap_1.size(), DNSGlobal::dnsLookUpMap_2.size(), DNSGlobal::dnsLookUpMap_3.size(), DNSGlobal::dnsLookUpMap_4.size());
	TheLog_nc_v5(Log::Info, name(),"  DnsLookUpMap size [%d] [%d] [%d] [%d] [%d]", DNSGlobal::dnsLookUpMap_5.size(), DNSGlobal::dnsLookUpMap_6.size(), DNSGlobal::dnsLookUpMap_7.size(), DNSGlobal::dnsLookUpMap_8.size(), DNSGlobal::dnsLookUpMap_9.size());
}


VOID IPSessionManager::getDnsDatabaseMapSize()
{
	IPStats::dns_resolved_lookup_size = 0;
	IPStats::dns_resolved_lookup_size += DNSGlobal::dnsDatabaseMap_0.size();
	IPStats::dns_resolved_lookup_size += DNSGlobal::dnsDatabaseMap_1.size();
	IPStats::dns_resolved_lookup_size += DNSGlobal::dnsDatabaseMap_2.size();
	IPStats::dns_resolved_lookup_size += DNSGlobal::dnsDatabaseMap_3.size();
	IPStats::dns_resolved_lookup_size += DNSGlobal::dnsDatabaseMap_4.size();
	IPStats::dns_resolved_lookup_size += DNSGlobal::dnsDatabaseMap_5.size();
	IPStats::dns_resolved_lookup_size += DNSGlobal::dnsDatabaseMap_6.size();
	IPStats::dns_resolved_lookup_size += DNSGlobal::dnsDatabaseMap_7.size();
	IPStats::dns_resolved_lookup_size += DNSGlobal::dnsDatabaseMap_8.size();
	IPStats::dns_resolved_lookup_size += DNSGlobal::dnsDatabaseMap_9.size();

	TheLog_nc_v5(Log::Info, name(),"  dnsDatabaseMap size [%d] [%d] [%d] [%d] [%d]", DNSGlobal::dnsDatabaseMap_0.size(), DNSGlobal::dnsDatabaseMap_1.size(), DNSGlobal::dnsDatabaseMap_2.size(), DNSGlobal::dnsDatabaseMap_3.size(), DNSGlobal::dnsDatabaseMap_4.size());
	TheLog_nc_v5(Log::Info, name(),"  dnsDatabaseMap size [%d] [%d] [%d] [%d] [%d]", DNSGlobal::dnsDatabaseMap_5.size(), DNSGlobal::dnsDatabaseMap_6.size(), DNSGlobal::dnsDatabaseMap_7.size(), DNSGlobal::dnsDatabaseMap_8.size(), DNSGlobal::dnsDatabaseMap_9.size());
}

//VOID IPSessionManager::getVolPerSec(ipSession *pIpSession)
//{
//	char timeBuffer[100];
//
//	uint32_t packets, volume, c_pickThrPut, f_pickThrPut;
//	uint32_t c_up_pickThrPut, f_up_pickThrPut, c_dn_pickThrPut, f_dn_pickThrPut;
//	uint32_t uppackets, upvolume, dnpackets, dnvolume;
//	uint32_t tcpUpPacket, tcpDnPacket;
//	uint16_t tcpUpCount, tcpDnCount;
//
//	int timeDiff = 0;
//
//	tcpUpPacket = tcpDnPacket = 0;
//	tcpUpCount = tcpDnCount = 0;
//	ULONG firstSec = 0;
//
//	int packetTSCount = pIpSession->packTimeMap.size();
//	int packetCount = 0;
////	std::map<ULONG, fData> secDataIt = pIpSession->packTimeMap;
//	packets = volume = c_pickThrPut = f_pickThrPut = 0;
//	c_up_pickThrPut = f_up_pickThrPut = c_dn_pickThrPut = f_dn_pickThrPut = 0;
//
//	for(auto elem : pIpSession->packTimeMap)
//	{
//		packetCount ++;
//		packets = elem.second.totalPackets;
//		volume = elem.second.totalVolume;
//		upvolume = elem.second.upVolume;
//		dnvolume = elem.second.dnVolume;
//
//		c_pickThrPut = volume;
//		if (c_pickThrPut > f_pickThrPut)
//			f_pickThrPut = c_pickThrPut;
//
//		if(upvolume > 0) {
//			tcpUpCount += 1;
//			tcpUpPacket = elem.second.upPackets;
//			upvolume = elem.second.upVolume;
//			c_up_pickThrPut = upvolume;
//			if (c_up_pickThrPut > f_up_pickThrPut)
//				f_up_pickThrPut = c_up_pickThrPut;
//		}
//
//		if(dnvolume > 0){
//			tcpDnCount += 1;
//			tcpDnPacket = elem.second.dnPackets;
//			dnvolume = elem.second.dnVolume;
//			c_dn_pickThrPut = dnvolume;
//			if (c_dn_pickThrPut > f_dn_pickThrPut)
//				f_dn_pickThrPut = c_dn_pickThrPut;
//		}
//
//		if(packetCount == 1 ) {
//			firstSec = elem.first;
//			pIpSession->dnVolPerSec[0] = 0;
//			sprintf(pIpSession->dnVolPerSec, "%u=", firstSec);
//			pIpSession->upVolPerSec[0] = 0;
//			sprintf(pIpSession->upVolPerSec, "%u=", firstSec);
//		}
//
//		if(dnvolume > 0 && strlen(pIpSession->dnVolPerSec) < (VPS_MAX_LEN - 200))
//		{
//			timeDiff = elem.first - firstSec;
//			if(timeDiff >= 0){
//				timeBuffer[0] = 0;
//				sprintf(timeBuffer, "%d#%u#%u;", timeDiff, tcpDnPacket, dnvolume);	//Volume only, keep in Bytes
//				strcat(pIpSession->dnVolPerSec, timeBuffer);
////				dnVolPerSec.append(std::string(timeBuffer));
//				timeBuffer[0] = 0;    // Clear Internal Buffer
//				pIpSession->pckTotalTimeSec = tcpDnCount;
//			}
//		}
//
//
//		if(upvolume > 0 && strlen(pIpSession->upVolPerSec) < (VPS_MAX_LEN - 200))
//		{
//			timeDiff = elem.first - firstSec;
//			if(timeDiff >= 0)
//			{
//				timeBuffer[0] = 0;
//				sprintf(timeBuffer, "%d#%u#%u;", timeDiff, tcpUpPacket, upvolume);	//Volume only, keep in Bytes
//				strcat(pIpSession->upVolPerSec, timeBuffer);
////				upVolPerSec.append(std::string(timeBuffer));
//				timeBuffer[0] = 0;    // Clear Internal Buffer
//				pIpSession->pckTotalTimeSec = tcpUpCount;
//			}
//		}
//		dnvolume = upvolume = 0;
//	}
//
//	pIpSession->packTimeMap.clear();
//
//	if(tcpDnCount == 0)
//		strcpy(pIpSession->dnVolPerSec, "NULL");
//
//	if(tcpUpCount == 0)
//		strcpy(pIpSession->upVolPerSec, "NULL");
//
//	/* Pick Throughput / Sec */
//	pIpSession->peakSessionTP = f_pickThrPut * 8;		//Converting to bps
//	pIpSession->upPeakSessionTP = f_up_pickThrPut * 8;	//Converting to bps
//	pIpSession->dnPeakSessionTP = f_dn_pickThrPut * 8;	//Converting to bps
//
//	if(packetTSCount > 0 && pIpSession->frameSize > 0)
//		pIpSession->sessionTP = (pIpSession->frameSize * 8) / packetTSCount;		//Converting to bps
//	else
//		pIpSession->sessionTP = 0;
//
//	if(tcpUpPacket > 0 && pIpSession->upFrameSize > 0)
//		pIpSession->upSessionTP = (pIpSession->upFrameSize * 8) / tcpUpPacket;	//Converting to bps
//	else
//		pIpSession->upSessionTP = 0;
//
//	if(tcpDnPacket > 0 && pIpSession->dnFrameSize > 0)
//		pIpSession->dnSessionTP = (pIpSession->dnFrameSize * 8) / tcpDnPacket;	//Converting to bps
//	else
//		pIpSession->dnSessionTP = 0;
//
//	if(!f_dn_pickThrPut)
//		pIpSession->dnPeakSessionTP = pIpSession->dnSessionTP;
//
//	if(!f_up_pickThrPut)
//		pIpSession->upPeakSessionTP = pIpSession->upSessionTP;
//}


//VOID IPSessionManager::buildIpCsvBuffer(ipSession *pIpSession, char *csvBuffer)



VOID IPSessionManager::createTCPXdr(ipSession *pIpSession, char *xdr, string dnVol, string upVol)
{

	ULONG dataLatency = 0;
	ULONG sumWeightage = 0;
	xdr[0] = 0;

	if((pIpSession->pshLatency > 0) && (pIpSession->payloadPacket > 0))
		ULONG dataLatency = (pIpSession->pshLatency /  pIpSession->payloadPacket);

	if(strlen(pIpSession->contentType) == 0)
		strcpy(pIpSession->contentType, "NULL");

	if(GContainer::config->GN_PROBE)
	{
		sprintf(xdr, "%d,%d,%d,TCP,"
					 "%d,%s-%d,"
					 "%s,%s,"
					 "%u,%d,%u,%d,"
					 "%u,%d,%u,%d,"
					 "%u,%u,%d,"
					 "%d,%d,%d,"
					 "%u,%u,%u,"
					 "%d,%d,%d,"
					 "%u,%u,%u,"
					 "%llu,%llu,%d,"
					 "%u,%u,"
					 "%u,%u,%u,%u,"
					 "%u,0,0,"
					 "%d,%s,%s,"
					 "%d,%llu,"
					 "%d,%llu,"
					 "%d,%llu,"
					 "%d,%llu,"
					 "%s,%u",		//Last NULL is APP_IP
				IPGlobal::PROBE_ID,XDR_ID_IP_SESSION,pIpSession->protocolType,
				pIpSession->destPort, pIpSession->sessionKey, pIpSession->sliceCounter,
				pIpSession->sourceMacAddr, pIpSession->destMacAddr,
				pIpSession->sgsnIPAddr, pIpSession->sgsnPort, pIpSession->ggsnIPAddr, pIpSession->ggsnPort,
				pIpSession->sourceIP, pIpSession->sourcePort, pIpSession->destIP, pIpSession->destPort,
				pIpSession->teid_up,pIpSession->teid_dn,pIpSession->sliceCounter,
				pIpSession->frameCount, pIpSession->upFrameCount, pIpSession->dnFrameCount,
				pIpSession->frameSize, pIpSession->upFrameSize, pIpSession->dnFrameSize,
				pIpSession->payloadPacket, pIpSession->upPayloadPacket, pIpSession->dnPayloadPacket,
				pIpSession->payloadSize, pIpSession->upPayloadSize, pIpSession->dnPayloadSize,
				pIpSession->startTimeEpochNanoSec, pIpSession->endTimeEpochNanoSec, pIpSession->pckTotalTimeSec,
				pIpSession->sessionTP, pIpSession->peakSessionTP,
				pIpSession->upSessionTP, pIpSession->upPeakSessionTP, pIpSession->dnSessionTP, pIpSession->dnPeakSessionTP,
				pIpSession->synLatency,// dataLatency, sumWeightage,
				pIpSession->causeCode, pIpSession->contentType, dnVol.c_str(),
				pIpSession->synRcv, pIpSession->synTimeEpochNanoSec,
				pIpSession->synAckRcv, pIpSession->synAckTimeEpochNanoSec,
				pIpSession->dataRcv, pIpSession->firstDataTimeEpochNanoSec,
				pIpSession->finRcv, pIpSession->finTimeEpochNanoSec,
				upVol.c_str(), pIpSession->appIp);

		//printf("xdr :: %s\n",xdr);
	}
}

void IPSessionManager::createUDPXdr(ipSession *pIpSession, char *xdr, string dnVol, string upVol)
{

	bool found = false;
	std::string URL;
	ULONG dataLatency = 0;
	ULONG sumWeightage = 0;
	xdr[0] = 0;

	if(GContainer::config->GN_PROBE)
	{
		sprintf(xdr, "%d,%d,%d,UDP,"
					 "%d,%s-%d,"
				     "%s,%s,"
					 "%u,%d,%u,%d,"
				 	 "%u,%d,%u,%d,"
					 "%u,%u,%d,"
					 "%d,%d,%d,"
					 "%u,%u,%u,"
					 "%d,%d,%d,"
					 "%u,%u,%u,"
					 "%llu,%llu,%d,"
					 "%u,%u,"
					 "%u,%u,%u,%u,"
					 "0,0,0,"
					 "%d,NULL,%s,"
					 "0,0,0,0,0,0,0,0,"
					 "%s,%u",
				IPGlobal::PROBE_ID,XDR_ID_IP_SESSION,pIpSession->protocolType,
				pIpSession->destPort, pIpSession->sessionKey, pIpSession->sliceCounter,
				pIpSession->sourceMacAddr, pIpSession->destMacAddr,
				pIpSession->sgsnIPAddr, pIpSession->sgsnPort, pIpSession->ggsnIPAddr, pIpSession->ggsnPort,
				pIpSession->sourceIP, pIpSession->sourcePort, pIpSession->destIP, pIpSession->destPort,
				pIpSession->teid_up, pIpSession->teid_dn, pIpSession->sliceCounter,
				pIpSession->frameCount, pIpSession->upFrameCount, pIpSession->dnFrameCount,
				pIpSession->frameSize, pIpSession->upFrameSize, pIpSession->dnFrameSize,
				pIpSession->payloadPacket, pIpSession->upPayloadPacket, pIpSession->dnPayloadPacket,
				pIpSession->payloadSize, pIpSession->upPayloadSize, pIpSession->dnPayloadSize,
				pIpSession->startTimeEpochNanoSec, pIpSession->endTimeEpochNanoSec, pIpSession->pckTotalTimeSec,
				pIpSession->sessionTP, pIpSession->peakSessionTP,
				pIpSession->upSessionTP, pIpSession->upPeakSessionTP, pIpSession->dnSessionTP, pIpSession->dnPeakSessionTP,
				//0, dataLatency, sumWeightage,
				pIpSession->causeCode, dnVol.c_str(),
				upVol.c_str(), pIpSession->appIp);
	}
}

VOID IPSessionManager::initializeIPFlushRepository(){

//	switch(instanceId)
//	{
//		case 0:
//			{
//				printf("IPSessionManager  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
//					IPFlushRepository::ipFlushMap_f_0_sm_0_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_0_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_0_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_0_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_0_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_0_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_0_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_0_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_0_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_0_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ip_xdr_flush_f_0_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_0_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_0_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_0_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_0_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_0_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_0_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_0_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_0_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_0_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ip_zmq_flush_f_0_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_0_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_0_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_0_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_0_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_0_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_0_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_0_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_0_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_0_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ipFlushMap_f_1_sm_0_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_0_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_0_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_0_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_0_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_0_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_0_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_0_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_0_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_0_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ip_xdr_flush_f_1_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_1_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_1_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_1_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_1_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_1_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_1_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_1_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_1_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_1_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ip_zmq_flush_f_1_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_1_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_1_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_1_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_1_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_1_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_1_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_1_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_1_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_1_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
//					IPFlushRepository::ipFlushMap_f_2_sm_0_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_0_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_0_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_0_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_0_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_0_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_0_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_0_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_0_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_0_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ip_xdr_flush_f_2_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_2_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_2_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_2_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_2_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_2_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_2_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_2_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_2_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_2_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ip_zmq_flush_f_2_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_2_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_2_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_2_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_2_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_2_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_2_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_2_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_2_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_2_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ipFlushMap_f_3_sm_0_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_0_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_0_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_0_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_0_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_0_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_0_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_0_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_0_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_0_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ip_xdr_flush_f_3_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_3_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_3_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_3_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_3_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_3_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_3_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_3_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_3_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_xdr_flush_f_3_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ip_zmq_flush_f_3_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_3_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_3_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_3_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_3_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_3_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_3_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_3_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_3_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ip_zmq_flush_f_3_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//				printf("IPSessionManager  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...Completed\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...Completed", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//			}
//			break;
//
//		case 1:
//			{
//				printf("IPSessionManager  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
//					IPFlushRepository::ipFlushMap_f_0_sm_1_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_1_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_1_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_1_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_1_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_1_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_1_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_1_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_1_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_1_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ipFlushMap_f_1_sm_1_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_1_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_1_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_1_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_1_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_1_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_1_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_1_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_1_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_1_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
//					IPFlushRepository::ipFlushMap_f_2_sm_1_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_1_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_1_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_1_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_1_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_1_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_1_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_1_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_1_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_1_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ipFlushMap_f_3_sm_1_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_1_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_1_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_1_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_1_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_1_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_1_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_1_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_1_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_1_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//				printf("IPSessionManager  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...Completed\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...Completed", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//			}
//			break;
//
//		case 2:
//			{
//				printf("IPSessionManager  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 1)
//				{
//					IPFlushRepository::ipFlushMap_f_0_sm_2_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_2_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_2_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_2_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_2_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_2_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_2_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_2_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_2_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_2_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ipFlushMap_f_1_sm_2_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_2_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_2_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_2_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_2_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_2_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_2_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_2_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_2_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_2_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 2)
//				{
//					IPFlushRepository::ipFlushMap_f_2_sm_2_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_2_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_2_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_2_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_2_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_2_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_2_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_2_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_2_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_2_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ipFlushMap_f_3_sm_2_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_2_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_2_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_2_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_2_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_2_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_2_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_2_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_2_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_2_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//				printf("IPSessionManager  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...Completed\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...Completed", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//			}
//			break;
//
//		case 3:
//			{
//				printf("IPSessionManager  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 1)
//				{
//					IPFlushRepository::ipFlushMap_f_0_sm_3_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_3_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_3_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_3_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_3_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_3_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_3_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_3_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_3_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_3_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ipFlushMap_f_1_sm_3_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_3_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_3_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_3_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_3_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_3_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_3_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_3_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_3_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_3_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 2)
//				{
//					IPFlushRepository::ipFlushMap_f_2_sm_3_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_3_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_3_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_3_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_3_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_3_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_3_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_3_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_3_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_3_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ipFlushMap_f_3_sm_3_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_3_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_3_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_3_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_3_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_3_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_3_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_3_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_3_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_3_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//
//				printf("IPSessionManager  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...Completed\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...Completed", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//			}
//			break;
//
//		case 4:
//			{
//				printf("IPSessionManager  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 1)
//				{
//					IPFlushRepository::ipFlushMap_f_0_sm_4_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_4_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_4_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_4_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_4_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_4_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_4_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_4_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_4_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_0_sm_4_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ipFlushMap_f_1_sm_4_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_4_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_4_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_4_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_4_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_4_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_4_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_4_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_4_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_1_sm_4_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 2)
//				{
//					IPFlushRepository::ipFlushMap_f_2_sm_4_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_4_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_4_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_4_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_4_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_4_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_4_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_4_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_4_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_2_sm_4_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::ipFlushMap_f_3_sm_4_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_4_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_4_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_4_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_4_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_4_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_4_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_4_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_4_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::ipFlushMap_f_3_sm_4_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//				printf("IPSessionManager  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...Completed\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...Completed", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//			}
//			break;
//	}
}

VOID IPSessionManager::initializeDNSFlushRepository(){

//	switch(instanceId)
//	{
//		case 0:
//			{
//				printf("IPSessionManager  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 1)
//				{
//					IPFlushRepository::dnsFlushMap_f_0_sm_0_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_0_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_0_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_0_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_0_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_0_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_0_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_0_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_0_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_0_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dns_xdr_flush_f_0_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_0_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_0_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_0_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_0_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_0_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_0_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_0_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_0_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_0_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dns_zmq_flush_f_0_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_0_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_0_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_0_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_0_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_0_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_0_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_0_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_0_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_0_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dnsFlushMap_f_1_sm_0_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_0_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_0_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_0_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_0_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_0_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_0_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_0_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_0_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_0_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dns_xdr_flush_f_1_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_1_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_1_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_1_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_1_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_1_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_1_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_1_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_1_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_1_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dns_zmq_flush_f_1_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_1_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_1_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_1_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_1_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_1_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_1_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_1_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_1_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_1_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 2)
//				{
//					IPFlushRepository::dnsFlushMap_f_2_sm_0_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_0_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_0_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_0_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_0_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_0_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_0_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_0_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_0_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_0_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dns_xdr_flush_f_2_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_2_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_2_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_2_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_2_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_2_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_2_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_2_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_2_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_2_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dns_zmq_flush_f_2_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_2_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_2_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_2_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_2_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_2_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_2_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_2_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_2_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_2_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dnsFlushMap_f_3_sm_0_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_0_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_0_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_0_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_0_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_0_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_0_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_0_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_0_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_0_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dns_xdr_flush_f_3_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_3_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_3_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_3_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_3_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_3_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_3_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_3_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_3_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_xdr_flush_f_3_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dns_zmq_flush_f_3_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_3_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_3_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_3_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_3_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_3_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_3_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_3_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_3_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dns_zmq_flush_f_3_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//				printf("IPSessionManager  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...Completed\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...Completed", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//			}
//			break;
//
//		case 1:
//			{
//				printf("IPSessionManager  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 1)
//				{
//					IPFlushRepository::dnsFlushMap_f_0_sm_1_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_1_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_1_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_1_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_1_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_1_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_1_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_1_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_1_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_1_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dnsFlushMap_f_1_sm_1_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_1_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_1_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_1_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_1_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_1_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_1_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_1_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_1_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_1_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 2)
//				{
//					IPFlushRepository::dnsFlushMap_f_2_sm_1_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_1_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_1_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_1_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_1_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_1_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_1_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_1_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_1_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_1_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dnsFlushMap_f_3_sm_1_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_1_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_1_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_1_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_1_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_1_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_1_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_1_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_1_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_1_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//
//				printf("IPSessionManager  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...Completed\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...Completed", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//			}
//			break;
//
//		case 2:
//			{
//				printf("IPSessionManager  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 1)
//				{
//					IPFlushRepository::dnsFlushMap_f_0_sm_2_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_2_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_2_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_2_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_2_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_2_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_2_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_2_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_2_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_2_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dnsFlushMap_f_1_sm_2_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_2_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_2_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_2_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_2_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_2_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_2_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_2_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_2_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_2_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 2)
//				{
//					IPFlushRepository::dnsFlushMap_f_2_sm_2_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_2_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_2_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_2_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_2_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_2_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_2_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_2_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_2_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_2_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dnsFlushMap_f_3_sm_2_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_2_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_2_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_2_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_2_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_2_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_2_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_2_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_2_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_2_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//				printf("IPSessionManager  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...Completed\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...Completed", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//			}
//			break;
//
//		case 3:
//			{
//				printf("IPSessionManager  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 1)
//				{
//					IPFlushRepository::dnsFlushMap_f_0_sm_3_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_3_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_3_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_3_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_3_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_3_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_3_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_3_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_3_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_3_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dnsFlushMap_f_1_sm_3_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_3_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_3_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_3_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_3_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_3_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_3_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_3_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_3_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_3_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 2)
//				{
//					IPFlushRepository::dnsFlushMap_f_2_sm_3_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_3_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_3_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_3_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_3_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_3_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_3_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_3_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_3_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_3_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dnsFlushMap_f_3_sm_3_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_3_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_3_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_3_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_3_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_3_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_3_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_3_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_3_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_3_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//				printf("IPSessionManager  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...Completed\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...Completed", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//			}
//			break;
//
//		case 4:
//			{
//				printf("IPSessionManager  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 1)
//				{
//					IPFlushRepository::dnsFlushMap_f_0_sm_4_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_4_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_4_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_4_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_4_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_4_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_4_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_4_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_4_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_0_sm_4_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dnsFlushMap_f_1_sm_4_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_4_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_4_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_4_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_4_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_4_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_4_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_4_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_4_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_1_sm_4_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//
//				if(IPGlobal::GN_GTPU_FLUSHER_NO > 2)
//				{
//					IPFlushRepository::dnsFlushMap_f_2_sm_4_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_4_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_4_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_4_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_4_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_4_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_4_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_4_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_4_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_2_sm_4_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//
//					IPFlushRepository::dnsFlushMap_f_3_sm_4_t_0.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_4_t_1.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_4_t_2.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_4_t_3.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_4_t_4.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_4_t_5.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_4_t_6.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_4_t_7.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_4_t_8.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//					IPFlushRepository::dnsFlushMap_f_3_sm_4_t_9.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				}
//				printf("IPSessionManager  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...Completed\n", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//				TheLog_nc_v2(Log::Info, name(),"  [%d] Initializing DNS Flush   Repository with [%'07d] x 10 ...Completed", instanceId, IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//			}
//			break;
//	}
}
