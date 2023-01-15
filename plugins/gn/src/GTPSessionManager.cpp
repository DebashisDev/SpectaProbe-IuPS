/*
 * GTPSessionManager.cpp
 *
 *  Created on: Nov 27, 2016
 *      Author: Deb
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mutex>
#include <memory>
#include <stdlib.h>
#include <locale.h>

#include "GTPSessionManager.h"

using namespace std;

VOID GTPSessionManager::lockgSession()
{
	pthread_mutex_lock(&gSessionLock::lockCount);
	while (gSessionLock::count == 0){
		pthread_cond_wait(&gSessionLock::nonzero, &gSessionLock::lockCount);
	}
	gSessionLock::count = gSessionLock::count - 1;
	pthread_mutex_unlock(&gSessionLock::lockCount);
}

VOID GTPSessionManager::unLockgSession()
{
    pthread_mutex_lock(&gSessionLock::lockCount);
    if (gSessionLock::count == 0)
        pthread_cond_signal(&gSessionLock::nonzero);
    gSessionLock::count = gSessionLock::count + 1;
    pthread_mutex_unlock(&gSessionLock::lockCount);
}

VOID GTPSessionManager::lockDnsMap()
{
	    pthread_mutex_lock(&mapDnsLock::lockCount);
	    while (mapDnsLock::count == 0)
	        pthread_cond_wait(&mapDnsLock::nonzero, &mapDnsLock::lockCount);
	    mapDnsLock::count = mapDnsLock::count - 1;
	    pthread_mutex_unlock(&mapDnsLock::lockCount);
}

VOID GTPSessionManager::unLockDnsMap()
{
    pthread_mutex_lock(&mapDnsLock::lockCount);
    if (mapDnsLock::count == 0)
        pthread_cond_signal(&mapDnsLock::nonzero);
    mapDnsLock::count = mapDnsLock::count + 1;
    pthread_mutex_unlock(&mapDnsLock::lockCount);
}

GTPSessionManager::GTPSessionManager(int id, int coreid)
{
	//_thisLogLevel = 0;
	this->_name = "GTPSessionManager";
	this->setLogLevel(Log::theLog().level());

	this->instanceId = id;
	this->coreId = coreid;
	repoInitStatus = false;
	ipSMgr		= new IPSessionManager(id);
}

GTPSessionManager::~GTPSessionManager() {
//	printf("GTPSessionManager [%d] Destructor Invoked...\n",instanceId);
	if(instanceId == 0){
		lockgSession();
		dumpTeidDump();
		dumpTeidGlobalLku();
		unLockgSession();
		lockDnsMap();
		ipSMgr->dumpDnsLookupMap();			// Dump DNS Lookup Map
		unLockDnsMap();
	}
//	delete(pGtpGlobalSession);
	delete(ipSMgr);
}

VOID GTPSessionManager::run()
{
	TheLog_nc_v2(Log::Info, name()," [%d] Started, pinned to core :: %d", instanceId, coreId);

	int lastProcessedIndex = -1;
	int curIndex = -1;
	int curMin = 0, prevMin = 0;
	int curSecIdxSessionClnUp = 0 , prevSecIdxSessionClnUp = 0;
	int today = 0, lastday = 0;

	struct tm *now_tm;

	//Initialize Local and Global Repositories
	initializeGtpRepository();

	if(instanceId == 0){
		initializeGtpGlobalRepository();
		lockDnsMap();
		ipSMgr->loadDnsLookupMap();
		unLockDnsMap();
	}

	repoInitStatus = true;

	gettimeofday(&curTime, NULL);
	now_tm = localtime(&curTime.tv_sec);
	curMin = prevMin = now_tm->tm_min;
	curSecIdxSessionClnUp = prevSecIdxSessionClnUp = now_tm->tm_sec / IPGlobal::IP_SESSION_CLEAN_UP_SCAN_FREQ_SEC;
	today = lastday = now_tm->tm_mday;

	//curIndex = (((getCurrentEpochSeconds() % 100) /10)  % IPGlobal::SESSION_MANAGER_TIMEINDEX) - IPGlobal::SESSION_MANAGER_READ_INDEX_LAG;
	//if(curIndex < 0) curIndex = IPGlobal::SESSION_MANAGER_TIMEINDEX + curIndex;
	curIndex = READ_TIME_INDEX(curTime.tv_sec);
	lastProcessedIndex = curIndex;

	int teidDumpTimeCheckCounter = 0;
	const int TEID_DUMP_INTERVAL_MIN = 5;
	int lkuTeidDumpTimeCheckCounter = 0;
	const int LKU_TEID_DUMP_INTERVAL_MIN = 30;
	int glbCleanupTimeCheckCounter = 0;
	const int GLB_CLEANUP_INTERVAL_MIN = 15;
//	int dnsDumpTimeCheckCounter = 0;
//	const int DNS_DUMP_INTERVAL_MIN = 60;

	long THREAD_SLEEP_DUR_MICRO_SEC = 100000;
	int spCnt = 0;

	while(IPGlobal::GN_SESSION_MANAGER_RUNNING_STATUS[instanceId])
	{
		usleep(THREAD_SLEEP_DUR_MICRO_SEC);		// 100ms

		gettimeofday(&curTime, NULL);
		now_tm = localtime(&curTime.tv_sec);
		curMin = now_tm->tm_min;
		curSecIdxSessionClnUp = now_tm->tm_sec / IPGlobal::IP_SESSION_CLEAN_UP_SCAN_FREQ_SEC;
		today = now_tm->tm_mday;

		curIndex = READ_TIME_INDEX(curTime.tv_sec);

		while(lastProcessedIndex != curIndex)
		{
			processStartEpochSec = getCurrentEpochSeconds();
			usleep(100000);		// 100ms
			processQueue(lastProcessedIndex);
			lastProcessedIndex = NEXT_TIME_INDEX(lastProcessedIndex);

		}

		if(instanceId > 0){
			if(curSecIdxSessionClnUp != prevSecIdxSessionClnUp)
			{
				ipSMgr->cleanTimedOutSessionsIP();		// IP Cleanup
				prevSecIdxSessionClnUp = curSecIdxSessionClnUp;
			}
		}

		if(curMin != prevMin)
		{
			if(instanceId == 0){
				lockDnsMap();
				ipSMgr->getDnsLookUpMapSize();			// DNS Lookup Map Size
				ipSMgr->getDnsDatabaseMapSize();		// DNS Database Map Size
				ipSMgr->cleanDnsDatabaseMap();			// DNS Database Map Cleanup
//				dnsDumpTimeCheckCounter++;
//				if(dnsDumpTimeCheckCounter >= DNS_DUMP_INTERVAL_MIN){
//					dnsDumpTimeCheckCounter = 0;
//					ipSMgr->dumpDnsLookupMap();
//				}
				unLockDnsMap();

				lockgSession();
				cleanUpGTPcLkuSessions();						// GTPc LKU Map Cleanup

				glbCleanupTimeCheckCounter++;
				if(glbCleanupTimeCheckCounter >= GLB_CLEANUP_INTERVAL_MIN)
				{
					glbCleanupTimeCheckCounter = 0;
					cleanUpGTPcGlobalSessions(curTime.tv_sec);	// GTPc GLOBAL Map Cleanup
				}

				getGlobalSessionCount();
				getGlobalLkuSessionCount();

				teidDumpTimeCheckCounter++;
				if(teidDumpTimeCheckCounter >= TEID_DUMP_INTERVAL_MIN){
					teidDumpTimeCheckCounter = 0;
					dumpTeidDump();
				}
				lkuTeidDumpTimeCheckCounter++;
				if(lkuTeidDumpTimeCheckCounter >= LKU_TEID_DUMP_INTERVAL_MIN){
					lkuTeidDumpTimeCheckCounter = 0;
					dumpTeidGlobalLku();
				}
				unLockgSession();

				cleanTimedOutSessionsGTPcv1();			// GTP Cleanup


			}

			getGTPcLocalSessionCount();

			if(instanceId > 0){
				ipSMgr->cleanTimedOutSessionsDns();		// DNS Session Cleanup
				ipSMgr->getSessionSize();				// IP Session Count
			}
			prevMin = curMin;
		}

		if(lastday != today)
		{
			lastday = today;
			if(instanceId > 0){
				ipSMgr->resetFinOnlySessionsCount();	//Reset FIN Count
			}

			if(instanceId == 0)
			{
				lockgSession();
				//cleanUpGTPcGlobalSessions(curTime.tv_sec);
				GTPStore::GTPGlb_IMSI_MAP.clear();
				unLockgSession();
				resetPDPOperationsCounters();			//Reset PDP Ops Counters
			}
		}

	}
	printf("GTPSessionManager [%d] Shutdown Complete\n", instanceId);
}

VOID GTPSessionManager::processMessage(MPacket *msgObj)
{

	switch(msgObj->ipAppProtocol)
	{
			case PACKET_IPPROTO_GTPC:
							if(msgObj->gtpcVersion == GTPv1)
								updateGtpV1Session(msgObj, this->instanceId);

//							else if(msgObj->gtpcVersion == GTPv2)
//								updateGtpV2Session(msgObj);

							break;

			case PACKET_IPPROTO_GTPU:
							switch(msgObj->ipProtocol)
							{
								case IPPROTO_TCP:
										ipSMgr->processTcpSession(msgObj);
										break;

								case IPPROTO_UDP:
										ipSMgr->processUdpSession(msgObj);

										 if(msgObj->dnsQRFlag < QUERY || msgObj->dnsQRFlag > RESPONSE)
										    	return;
										 else
											ipSMgr->processDnsSession(msgObj);

										break;

//								case PACKET_IPPROTO_ICMP: 		// Internet Control Message Protocol.
//								case PACKET_IPPROTO_IGMP: 		// Internet Group management Protocol.
//								case PACLET_IPPROTO_EGP: 		// Exterior Gateway Protocol.
//								case PACKET_IPPROTO_PUP: 		// PUP Protocol.
//								case PACKET_IPPROTO_IDP: 		// XNS IDP protocol.
//								case PACKET_IPPROTO_TP: 		// SO Transport Protocol Class 4.
//								case PACKET_IPPROTO_IPV6: 		//IPv6 header.
//								case PACKET_IPPROTO_ROUTING: 	//IPv6 Routing header.
//								case PACKET_IPPROTO_FRAGMENT: 	//IPv6 fragmentation header.
//								case PACKET_IPPROTO_RSVP: 		//Reservation Protocol.
//								case PACKET_IPPROTO_GRE: 		//General Routing Encapsulation.
//								case PACKET_IPPROTO_ESP: 		//encapsulating security payload.
//								case PACKET_IPPROTO_AH: 		//Authentication header.
//								case PACKET_IPPROTO_ICMPV6: 	//ICMPV6.
//								case PACKET_IPPROTO_NONE: 		//IPv6 no next header.
//								case PACKET_IPPROTO_DSTOPTS: 	//IPv6 destination options.
//								case PACKET_IPPROTO_MTP: 		//Multicast Transport Protocol.
//								case PACKET_IPPROTO_ENCAP:	 	//Encapsulation Header.
//								case PACKET_IPPROTO_PIM: 		//Protocol Independent Multicast.
//								case PACKET_IPPROTO_COMP: 		//Compression Header Protocol.
//								case PACKET_IPPROTO_UDPLITE: 	//UDP-Lite protocol.
//								case PACKET_IPPROTO_RAW: 		//Raw IP Packets.:
////										ipSMgr->updateOtrSession(msgObj);
//										break;
//
//								default:
//										break;
							}

							break;
			default:
							break;
	}
	//msgObj->reset();
}

VOID GTPSessionManager::updateGtpV1Session(MPacket *msgObj, int id)
{
//	pGtpGlobalSession = NULL;
	updatePDPOperationsCounters(msgObj->gtpcMsgType);

	int Z_SGSN = 1;
	int E_SGSN = 2;
	int X_SGSN = 0;

	//ZTE-SGSN :: 3673707132 (218.248.82.124)
    //E-SGSN :: 3673704992 (218.248.74.32)

	if(msgObj->ipSourceAddr == 3673707132)
	{
		X_SGSN = Z_SGSN;
		msgObj->dirUserNetwork = true;
		msgObj->gtpcSgsnId = X_SGSN;
	}
	else if(msgObj->ipDestAddr == 3673707132)
	{
		X_SGSN = Z_SGSN;
		msgObj->dirUserNetwork = false;
		msgObj->gtpcSgsnId = X_SGSN;
	}
	else if(msgObj->ipSourceAddr == 3673704992)
	{
		X_SGSN = E_SGSN;
		msgObj->dirUserNetwork = true;
		msgObj->gtpcSgsnId = X_SGSN;
	}
	else if(msgObj->ipDestAddr == 3673704992)
	{
		X_SGSN = E_SGSN;
		msgObj->dirUserNetwork = false;
		msgObj->gtpcSgsnId = X_SGSN;
	}


	switch(msgObj->gtpcMsgType)
	{
		case GTPV1_CREATE_PDP_REQUEST:
									createPDPReq(msgObj);
									break;

		case GTPV1_CREATE_PDP_RESPONSE:
									createPDPRsp(msgObj);
									break;

		case GTPV1_UPDATE_PDP_REQUEST:
									if(X_SGSN == E_SGSN) updatePDPReq(msgObj,GTPcMapUP_E);
									else if(X_SGSN == Z_SGSN) updatePDPReq(msgObj,GTPcMapUP_Z);
									break;

		case GTPV1_UPDATE_PDP_RESPONSE:
									if(X_SGSN == E_SGSN) updatePDPRsp(msgObj,GTPcMapUP_E);
									else if(X_SGSN == Z_SGSN) updatePDPRsp(msgObj,GTPcMapUP_Z);
									break;

		case GTPV1_DELETE_PDP_REQUEST:
									if(X_SGSN == E_SGSN) deletePDPReq(msgObj,GTPcMapDL_E);
									else if(X_SGSN == Z_SGSN) deletePDPReq(msgObj,GTPcMapDL_Z);
									break;

		case GTPV1_DELETE_PDP_RESPONSE:
									if(X_SGSN == E_SGSN) deletePDPRsp(msgObj,GTPcMapDL_E);
									else if(X_SGSN == Z_SGSN) deletePDPRsp(msgObj,GTPcMapDL_Z);
									break;
	}
}

/*
 *  Create PDP Request Procedure
 */
VOID GTPSessionManager::createPDPReq(MPacket *msgObj)
{
	GTPSession *pGtpSession;
	//uint32_t key = (uint32_t) msgObj->gtpcSequenceNo;//gtpcTunnel_Id_Control;
	uint32_t key = msgObj->gtpcTunnel_Id_Control;

	if(key == 0) return;
//	{
//		GTPSession gTPSession;
//		pGtpSession = &gTPSession;
//		processRequestProcedure(pGtpSession, msgObj);
//		pGtpSession->EndTimeEpochSec 	= msgObj->frEpochTimeSec;
//		pGtpSession->EndTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
//		flushGTPSession(pGtpSession,FLUSH_TYPE_CR_REQ_NO_TEID);
//		return;
//	}

	std::map<uint32_t, GTPSession>::iterator it = GTPcMapCR.find(key);
	if(it != GTPcMapCR.end())
	{
		pGtpSession = &it->second;

		if(pGtpSession->GTPRspMsgId == GTPV1_CREATE_PDP_RESPONSE && pGtpSession->res_sequence_no == msgObj->gtpcSequenceNo)	//Response has arrieved before Req
		{

//			if(msgObj->frEpochTimeSec - pGtpSession->EndTimeEpochSec > 30)	//Create time later than Rsp time, Invalid
//			{
//				//Create a new session
//				GTPSession gtpSession;
//				GTPcMapCR[key] = gtpSession;
//				pGtpSession = &GTPcMapCR[key];
//				processRequestProcedure(pGtpSession, msgObj);
//				return;
//			}
//			else //Response has arrieved before Req
//			{
				processRequestProcedure(pGtpSession, msgObj);
				if(pGtpSession->EndCauseId == ACCEPT) {
					lockgSession();
					createGlobalSession(pGtpSession);
					unLockgSession();
				}
				flushGTPSession(pGtpSession,FLUSH_TYPE_CR_REQ_RESREQ);
				GTPcMapCR.erase(key);
				return;
//			}
		}
		else 	//Duplicate create req seems
		{
			pGtpSession->EndTimeEpochSec 	= msgObj->frTimeEpochSec;
			pGtpSession->EndTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
			flushGTPSession(pGtpSession,FLUSH_TYPE_CR_REQ_DUP);
			pGtpSession->reset();
			processRequestProcedure(pGtpSession, msgObj);
		}
	}
	else
	{
		//Create a new session
		GTPSession gtpSession;
		GTPcMapCR[key] = gtpSession;
		pGtpSession = &GTPcMapCR[key];
		processRequestProcedure(pGtpSession, msgObj);
	}
}

/*
 *  Create PDP Response Procedure
 */
VOID GTPSessionManager::createPDPRsp(MPacket *msgObj)
{
	GTPSession *pGtpSession;
	//uint32_t key = (uint32_t) msgObj->gtpcSequenceNo;//gtpcPktTunnelId;
	uint32_t key = msgObj->gtpcPktTunnelId;

	if (key == 0) return;
//	{
//		GTPSession gTPSession;
//		pGtpSession = &gTPSession;
//		processResponseProcedure(pGtpSession, msgObj);
//		flushGTPSession(pGtpSession,FLUSH_TYPE_CR_RES_NO_TEID);
//		return;
//	}

	std::map<uint32_t, GTPSession>::iterator it = GTPcMapCR.find(key);

	if(it != GTPcMapCR.end())
	{
		pGtpSession = &it->second;

		//printf("IMSI CR RSP [%u] [%u][%u] [%s] == [%d]\n",key, pGtpSession->tunnel_id_control_up, pGtpSession->tunnel_id_control_dn, pGtpSession->IMSI, GTPcMapCR.size());

		if(pGtpSession->GTPReqMsgId == GTPV1_CREATE_PDP_REQUEST && pGtpSession->req_sequence_no == msgObj->gtpcSequenceNo)	//Response has arrieved after Req
		{

//			if(msgObj->frEpochTimeSec < pGtpSession->StartTimeEpochSec)		//Create time later than Rsp time, Invalid
//			{
//				//Create a new session
//				GTPSession gTPSession;
//				GTPcMapCR[key] = gTPSession;
//				pGtpSession = &GTPcMapCR[key];
//				processResponseProcedure(pGtpSession, msgObj);
//				return;
//			}
//			else
//			{
				processResponseProcedure(pGtpSession, msgObj);

	//			printf("**Found** CTRL [%u] [%u] DATA [%u] [%u] IP[%s] Code[%d] Seq Req [%u] Seq Res [%u]\n",
	//					pGtpSession->tunnel_id_control_up, pGtpSession->tunnel_id_control_dn,
	//					pGtpSession->tunnel_id_data_up, pGtpSession->tunnel_id_data_dn,
	//					pGtpSession->userIPAddress, pGtpSession->EndCauseId,
	//					pGtpSession->sequence_noReq,pGtpSession->sequence_noRsp);


				if(pGtpSession->EndCauseId == ACCEPT) {
					lockgSession();
					createGlobalSession(pGtpSession);
					unLockgSession();
				}
				flushGTPSession(pGtpSession,FLUSH_TYPE_CR_RES_REQRES);
				GTPcMapCR.erase(key);
				return;
//			}
		}
		else 	//Duplicate create Response seems
		{
			pGtpSession->StartTimeEpochSec 	= msgObj->frTimeEpochSec;
			pGtpSession->StartTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
			flushGTPSession(pGtpSession,FLUSH_TYPE_CR_RES_DUP);
			pGtpSession->reset();
			processResponseProcedure(pGtpSession, msgObj);
		}
	}
	else
	{
		//Create a new session
		GTPSession gTPSession;
		GTPcMapCR[key] = gTPSession;
		pGtpSession = &GTPcMapCR[key];
		processResponseProcedure(pGtpSession, msgObj);
	}
}

/*
 *  Update PDP Request Procedure
 */
void GTPSessionManager::updatePDPReq(MPacket *msgObj, std::map<uint16_t, GTPSession> &GTPcMap)
{
	GTPSession *pGtpSession;
	uint16_t key = msgObj->gtpcSequenceNo;

	if(key == 0) return;
//	{
//		GTPSession gTPSession;
//		pGtpSession = &gTPSession;
//		processRequestProcedure(pGtpSession, msgObj);
//		flushGTPSession(pGtpSession,FLUSH_TYPE_UP_REQ_NO_TEID);
//		return;
//	}

	std::map<uint16_t, GTPSession>::iterator it = GTPcMap.find(key);

	if(it != GTPcMap.end())
	{
		pGtpSession = &it->second;

		if(pGtpSession->GTPRspMsgId == GTPV1_UPDATE_PDP_RESPONSE)	//Response has arrieved before Req
		{
//			int timeDiff = 0;
//			if(msgObj->frEpochTimeSec > pGtpSession->StartTimeEpochSec)
//				timeDiff = msgObj->frEpochTimeSec - pGtpSession->StartTimeEpochSec;
//			else
//				timeDiff =  pGtpSession->StartTimeEpochSec - msgObj->frEpochTimeSec;
//
//			if(timeDiff > 60)		//Create time later than Rsp time, Invalid
//			{
//				//Create a new session
//				GTPSession gtpSession;
//				GTPcMap[key] = gtpSession;
//				pGtpSession = &GTPcMap[key];
//				processRequestProcedure(pGtpSession, msgObj);
//				return;
//			}
//			else
//			{
				processRequestProcedure(pGtpSession, msgObj);
				if(pGtpSession->EndCauseId == ACCEPT) {
					lockgSession();
					updateGlobalSession(pGtpSession, msgObj);
					unLockgSession();
				}
				flushGTPSession(pGtpSession,FLUSH_TYPE_UP_REQ_RESREQ);
				GTPcMap.erase(key);
				return;
//			}
		}
		else 	//Duplicate Update Request seems
		{
			pGtpSession->EndTimeEpochSec 	= msgObj->frTimeEpochSec;
			pGtpSession->EndTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
			flushGTPSession(pGtpSession, FLUSH_TYPE_UP_REQ_DUP);
			pGtpSession->reset();
			processRequestProcedure(pGtpSession, msgObj);
		}
	}
	else
	{
		GTPSession gTPSession;
		GTPcMap[key] = gTPSession;
		pGtpSession = &GTPcMap[key];
		processRequestProcedure(pGtpSession, msgObj);
	}
}

/*
 *  Update PDP Response Procedure
 */
void GTPSessionManager::updatePDPRsp(MPacket *msgObj, std::map<uint16_t, GTPSession> &GTPcMap)
{
	GTPSession *pGtpSession;
	uint16_t key = msgObj->gtpcSequenceNo;

	if( key == 0) return;
//	{
//		GTPSession gTPSession;
//		pGtpSession = &gTPSession;
//		processResponseProcedure(pGtpSession, msgObj);
//		flushGTPSession(pGtpSession,FLUSH_TYPE_UP_RES_NO_TEID);
//		return;
//	}


	std::map<uint16_t, GTPSession>::iterator it = GTPcMap.find(key);
	if(it != GTPcMap.end())
	{
		pGtpSession = &it->second;

		if(pGtpSession->GTPReqMsgId == GTPV1_UPDATE_PDP_REQUEST)	//Response has arrieved after Req
		{

//			int timeDiff = 0;
//			if(msgObj->frEpochTimeSec > pGtpSession->StartTimeEpochSec)
//				timeDiff = msgObj->frEpochTimeSec - pGtpSession->StartTimeEpochSec;
//			else
//				timeDiff =  pGtpSession->StartTimeEpochSec - msgObj->frEpochTimeSec;
//
//			if(timeDiff > 60)		//Create time later than Rsp time, Invalid
//			{
//				//Create a new session
//				GTPSession gTPSession;
//				GTPcMap[key] = gTPSession;
//				pGtpSession = &GTPcMap[key];
//				processResponseProcedure(pGtpSession, msgObj);
//				return;
//			}
//			else
//			{
				processResponseProcedure(pGtpSession, msgObj);
				if(pGtpSession->EndCauseId == ACCEPT) {
					lockgSession();
					updateGlobalSession(pGtpSession, msgObj);
					unLockgSession();
				}
				flushGTPSession(pGtpSession,FLUSH_TYPE_UP_RES_REQRES);
				GTPcMap.erase(key);
				return;
//			}
		}
		else 	//Duplicate Update Response seems
		{
			pGtpSession->StartTimeEpochSec 	= msgObj->frTimeEpochSec;
			pGtpSession->StartTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
			flushGTPSession(pGtpSession, FLUSH_TYPE_UP_RES_DUP);
			pGtpSession->reset();
			processResponseProcedure(pGtpSession, msgObj);
		}
	}
	else
	{
		GTPSession gTPSession;
		GTPcMap[key] = gTPSession;
		pGtpSession = &GTPcMap[key];
		processResponseProcedure(pGtpSession, msgObj);
	}
}

/*
 *  Delete PDP Request Procedure
 */
VOID GTPSessionManager::deletePDPReq(MPacket *msgObj, std::map<uint16_t, GTPSession> &GTPcMap)
{
	GTPSession *pGtpSession;
	uint16_t key = msgObj->gtpcSequenceNo;

	if(key == 0) return;
//	{
//		GTPSession gTPSession;
//		pGtpSession = &gTPSession;
//		processRequestProcedure(pGtpSession, msgObj);
//		flushGTPSession(pGtpSession,FLUSH_TYPE_DL_REQ_NO_TEID);
//		return;
//	}

	std::map<uint16_t, GTPSession>::iterator it = GTPcMap.find(key);

	if(it != GTPcMap.end())
	{
		pGtpSession = &it->second;

		if(pGtpSession->GTPRspMsgId == GTPV1_DELETE_PDP_RESPONSE)	//Response has arrieved before Req
		{
//			int timeDiff = 0;
//			if(msgObj->frEpochTimeSec > pGtpSession->StartTimeEpochSec)
//				timeDiff = msgObj->frEpochTimeSec - pGtpSession->StartTimeEpochSec;
//			else
//				timeDiff =  pGtpSession->StartTimeEpochSec - msgObj->frEpochTimeSec;
//
//
//			if(timeDiff > 60)	//Create time later than Rsp time, Invalid
//			{
//				//Create a new session
//				GTPSession gtpSession;
//				GTPcMap[key] = gtpSession;
//				pGtpSession = &GTPcMap[key];
//				processRequestProcedure(pGtpSession, msgObj);
//				return;
//			}
//			else
//			{
				processRequestProcedure(pGtpSession, msgObj);
				if(pGtpSession->EndCauseId == ACCEPT) {
					lockgSession();
					removeGlobalSession(pGtpSession);
					unLockgSession();
				}
				flushGTPSession(pGtpSession,FLUSH_TYPE_UP_REQ_RESREQ);
				GTPcMap.erase(key);
				return;
//			}
		}
		else 	//Duplicate Delete Request seems
		{
			pGtpSession->EndTimeEpochSec 	= msgObj->frTimeEpochSec;
			pGtpSession->EndTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
			flushGTPSession(pGtpSession, FLUSH_TYPE_DL_REQ_DUP);
			pGtpSession->reset();
			processRequestProcedure(pGtpSession, msgObj);
		}
	}
	else
	{
		GTPSession gTPSession;
		GTPcMap[key] = gTPSession;
		pGtpSession = &GTPcMap[key];
		processRequestProcedure(pGtpSession, msgObj);
	}
}

/*
 *  Delete PDP Response Procedure
 */
VOID GTPSessionManager::deletePDPRsp(MPacket *msgObj, std::map<uint16_t, GTPSession> &GTPcMap)
{
	GTPSession *pGtpSession;
	uint16_t key = msgObj->gtpcSequenceNo;

	if( key == 0) return;
//	{
//		GTPSession gTPSession;
//		pGtpSession = &gTPSession;
//		processResponseProcedure(pGtpSession, msgObj);
//		flushGTPSession(pGtpSession,FLUSH_TYPE_DL_RES_NO_TEID);
//		return;
//	}

	std::map<uint16_t, GTPSession>::iterator it = GTPcMap.find(key);

	if(it != GTPcMap.end())
	{
		pGtpSession = &it->second;

		if(pGtpSession->GTPReqMsgId == GTPV1_DELETE_PDP_REQUEST)	//Response has arrieved after Req
		{
//			int timeDiff = 0;
//			if(msgObj->frEpochTimeSec > pGtpSession->StartTimeEpochSec)
//				timeDiff = msgObj->frEpochTimeSec - pGtpSession->StartTimeEpochSec;
//			else
//				timeDiff =  pGtpSession->StartTimeEpochSec - msgObj->frEpochTimeSec;
//
//
//			if(timeDiff > 60)		//Create time later than Rsp time, Invalid
//			{
//				//Create a new session
//				GTPSession gTPSession;
//				GTPcMap[key] = gTPSession;
//				pGtpSession = &GTPcMap[key];
//				processResponseProcedure(pGtpSession, msgObj);
//				return;
//			}
//			else
//			{
				processResponseProcedure(pGtpSession, msgObj);
				if(pGtpSession->EndCauseId == ACCEPT) {
					lockgSession();
					removeGlobalSession(pGtpSession);
					unLockgSession();
				}
				flushGTPSession(pGtpSession,FLUSH_TYPE_DL_RES_REQRES);
				GTPcMap.erase(key);
				return;
//			}
		}
		else 	//Duplicate Delete Response seems
		{
			pGtpSession->StartTimeEpochSec 	= msgObj->frTimeEpochSec;
			pGtpSession->StartTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
			flushGTPSession(pGtpSession, FLUSH_TYPE_DL_RES_DUP);
			pGtpSession->reset();
			processResponseProcedure(pGtpSession, msgObj);
		}
	}
	else
	{
		GTPSession gTPSession;
		GTPcMap[key] = gTPSession;
		pGtpSession = &GTPcMap[key];
		processResponseProcedure(pGtpSession, msgObj);
	}
}

/*
 *  Store PDP Request Data
 */
VOID GTPSessionManager::processRequestProcedure(GTPSession *gtpSession, MPacket *msgObj)
{
//	gtpSession->frInterfaceIdReq 	= msgObj->frInterfaceId;
	gtpSession->StartTimeEpochSec 	= msgObj->frTimeEpochSec;
	gtpSession->StartTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
//	gtpSession->EndTimeEpochSec 	= msgObj->frEpochTimeSec;
//	gtpSession->EndTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;

	strcpy(gtpSession->sgsnMACAddr, msgObj->ethSourceMACAddr);
	strcpy(gtpSession->ggsnMACAddr, msgObj->ethDestMACAddr);
	gtpSession->VLanId = msgObj->ethVLanId;

	gtpSession->sgsnPort 	= msgObj->gtpSGSNPort;
	gtpSession->ggsnPort 	= msgObj->gtpGGSNPort;
	gtpSession->sgsnIPAddr 	= msgObj->gtpSGSNAddr;
	gtpSession->ggsnIPAddr 	= msgObj->gtpGGSNAddr;

	gtpSession->GTPReqMsgId = msgObj->gtpcMsgType;

	strcpy(gtpSession->SessionId, getSessionKey(msgObj).c_str());

	gtpSession->SgsnId = msgObj->gtpcSgsnId;

	gtpSession->dirSgsnGgsn = msgObj->dirUserNetwork;

	gtpSession->MCC 		= msgObj->gtpcMCC;
	gtpSession->MNC 		= msgObj->gtpcMNC;
	gtpSession->LAC 		= msgObj->gtpcLAC;
	gtpSession->RAC 		= msgObj->gtpcRAC;
	gtpSession->CI 			= msgObj->gtpcCellId;

	gtpSession->RAT 		= msgObj->gtpcRAT;
	gtpSession->RATOld 		= msgObj->gtpcRAT;

	gtpSession->req_mbrupl 	= msgObj->gtpcMbrupl;
	gtpSession->req_mbrdnl 	= msgObj->gtpcMbrdnl;

	gtpSession->req_ext_mbrdnl = msgObj->gtpcExtMbrdnl;


	gtpSession->req_sequence_no	= msgObj->gtpcSequenceNo;
//	gtpSession->sequenceFlag= msgObj->gtpcIsSquenceFlag;
	gtpSession->nsapi_val 	= msgObj->gtpcNsapi;

	if(msgObj->dirUserNetwork) {
		switch(msgObj->gtpcMsgType) {
			case GTPV1_CREATE_PDP_REQUEST:
						strcpy(gtpSession->IMSI, msgObj->IMSI);
						strcpy(gtpSession->IMEI, msgObj->IMEI);
						strcpy(gtpSession->MSISDN, msgObj->MSISDN);
						if(strlen(msgObj->gtpcAPN) > 2) strcpy(gtpSession->APN, &msgObj->gtpcAPN[1]);
						else strcpy(gtpSession->APN, &msgObj->gtpcAPN[0]);
						gtpSession->ByteSizeUL = msgObj->gtpcMsgLen;
						gtpSession->tunnel_id_control_up = msgObj->gtpcTunnel_Id_Control;
						gtpSession->tunnel_id_data_up = msgObj->gtpcTunnel_Id_Data_1;
						strcpy(gtpSession->ggsnDataIPAddr, msgObj->gtpcSgsnAddrData);
						strcpy(gtpSession->ggsnCtlIPAddr, msgObj->gtpcSgsnAddrCtl);
						break;
			case GTPV1_UPDATE_PDP_REQUEST:
						gtpSession->ByteSizeUL = msgObj->gtpcMsgLen;
						gtpSession->pkt_tunnel_id_up = msgObj->gtpcPktTunnelId;
						gtpSession->tunnel_id_control_up = msgObj->gtpcTunnel_Id_Control;
						gtpSession->tunnel_id_data_up = msgObj->gtpcTunnel_Id_Data_1;
						strcpy(gtpSession->ggsnDataIPAddr, msgObj->gtpcSgsnAddrData);
						strcpy(gtpSession->ggsnCtlIPAddr, msgObj->gtpcSgsnAddrCtl);
						break;

			case GTPV1_DELETE_PDP_REQUEST:
						gtpSession->ByteSizeUL = msgObj->gtpcMsgLen;
						gtpSession->pkt_tunnel_id_up = msgObj->gtpcPktTunnelId;
						gtpSession->tunnel_id_control_up = msgObj->gtpcPktTunnelId;
						break;
		}
	}
	else {
		switch(msgObj->gtpcMsgType) {
//			case GTPV1_CREATE_PDP_REQUEST:
//						gtpSession->ByteSizeDL = msgObj->gtpcMsgLen;
//						gtpSession->tunnel_id_control_dn = msgObj->gtpcTunnel_Id_Control;
//						gtpSession->tunnel_id_data_dn = msgObj->gtpcTunnel_Id_Data_1;
//						strcpy(gtpSession->sgsnDataIPAddr, msgObj->gtpcSgsnAddrData);
//						strcpy(gtpSession->sgsnCtlIPAddr, msgObj->gtpcSgsnAddrCtl);
//						break;

			case GTPV1_UPDATE_PDP_REQUEST:
						gtpSession->ByteSizeDL = msgObj->gtpcMsgLen;
						gtpSession->pkt_tunnel_id_dn = msgObj->gtpcPktTunnelId;
						gtpSession->tunnel_id_control_dn = msgObj->gtpcTunnel_Id_Control;
						gtpSession->tunnel_id_data_dn = msgObj->gtpcTunnel_Id_Data_1;
						strcpy(gtpSession->sgsnDataIPAddr, msgObj->gtpcSgsnAddrData);
						strcpy(gtpSession->sgsnCtlIPAddr, msgObj->gtpcSgsnAddrCtl);
						break;

			case GTPV1_DELETE_PDP_REQUEST:
						gtpSession->ByteSizeDL = msgObj->gtpcMsgLen;
						gtpSession->pkt_tunnel_id_dn = msgObj->gtpcPktTunnelId;
						gtpSession->tunnel_id_control_dn = msgObj->gtpcPktTunnelId;
						break;
		}
	}
}

/*
 *  Store PDP Response Data
 */
VOID GTPSessionManager::processResponseProcedure(GTPSession *gtpSession, MPacket *msgObj)
{
	gtpSession->res_mbrupl = msgObj->gtpcMbrupl;
	gtpSession->res_mbrdnl = msgObj->gtpcMbrdnl;

	gtpSession->res_ext_mbrdnl = msgObj->gtpcExtMbrdnl;

	gtpSession->GTPRspMsgId 		= msgObj->gtpcMsgType;
	gtpSession->EndCauseId 			= msgObj->gtpcCauseCode;
	gtpSession->EndTimeEpochSec 	= msgObj->frTimeEpochSec;
	gtpSession->EndTimeEpochNanoSec = msgObj->frTimeEpochNanoSec;
//	gtpSession->dirSgsnGgsn 		= msgObj->isUpDir;
	gtpSession->res_sequence_no		= msgObj->gtpcSequenceNo;

	gtpSession->SgsnId = msgObj->gtpcSgsnId;

	if(gtpSession->sgsnPort == 0)
		gtpSession->sgsnPort 	= msgObj->gtpSGSNPort;

	if(gtpSession->ggsnPort == 0)
		gtpSession->ggsnPort 	= msgObj->gtpGGSNPort;

	if(gtpSession->sgsnIPAddr == 0)
		gtpSession->sgsnIPAddr 	= msgObj->gtpSGSNAddr;

	if(gtpSession->ggsnIPAddr == 0)
		gtpSession->ggsnIPAddr 	= msgObj->gtpGGSNAddr;

	strcpy(gtpSession->userIPAddress, msgObj->gtpUserIpAddress);
	strcpy(gtpSession->chargingGWAddr, msgObj->gtpcChargingGWAddr);


	if(msgObj->dirUserNetwork)	{
		switch(msgObj->gtpcMsgType)	{
//			case GTPV1_CREATE_PDP_RESPONSE:
//						gtpSession->ByteSizeUL 				= msgObj->gtpcMsgLen;
//						gtpSession->pkt_tunnel_id_up		= msgObj->gtpcPktTunnelId;
//						gtpSession->tunnel_id_control_up 	= msgObj->gtpcTunnel_Id_Control;
//						gtpSession->tunnel_id_data_up 		= msgObj->gtpcTunnel_Id_Data_1;
//						strcpy(gtpSession->ggsnCtlIPAddr, msgObj->gtpcSgsnAddrCtl);
//						strcpy(gtpSession->ggsnDataIPAddr, msgObj->gtpcSgsnAddrData);
						break;
			case GTPV1_UPDATE_PDP_RESPONSE:
						gtpSession->ByteSizeUL 				= msgObj->gtpcMsgLen;
						gtpSession->pkt_tunnel_id_up 		= msgObj->gtpcPktTunnelId;
						gtpSession->tunnel_id_control_up 	= msgObj->gtpcTunnel_Id_Control;
						gtpSession->tunnel_id_data_up 		= msgObj->gtpcTunnel_Id_Data_1;
						strcpy(gtpSession->ggsnCtlIPAddr, msgObj->gtpcSgsnAddrCtl);
						strcpy(gtpSession->ggsnDataIPAddr, msgObj->gtpcSgsnAddrData);
						break;

			case GTPV1_DELETE_PDP_RESPONSE:
						gtpSession->ByteSizeUL = msgObj->gtpcMsgLen;
						gtpSession->pkt_tunnel_id_up = msgObj->gtpcPktTunnelId;
						gtpSession->tunnel_id_control_up = msgObj->gtpcPktTunnelId;
						break;
		}
	}
	else {
		switch(msgObj->gtpcMsgType)	{
			case GTPV1_CREATE_PDP_RESPONSE:
						gtpSession->ByteSizeDL 				= msgObj->gtpcMsgLen;
						gtpSession->pkt_tunnel_id_dn		= msgObj->gtpcPktTunnelId;
						gtpSession->tunnel_id_control_dn 	= msgObj->gtpcTunnel_Id_Control;
						gtpSession->tunnel_id_data_dn 		= msgObj->gtpcTunnel_Id_Data_1;
						strcpy(gtpSession->sgsnCtlIPAddr, msgObj->gtpcSgsnAddrCtl);
						strcpy(gtpSession->sgsnDataIPAddr, msgObj->gtpcSgsnAddrData);
						break;
			case GTPV1_UPDATE_PDP_RESPONSE:
						gtpSession->ByteSizeDL 				= msgObj->gtpcMsgLen;
						gtpSession->pkt_tunnel_id_dn 		= msgObj->gtpcPktTunnelId;
						gtpSession->tunnel_id_control_dn 	= msgObj->gtpcTunnel_Id_Control;
						gtpSession->tunnel_id_data_dn 		= msgObj->gtpcTunnel_Id_Data_1;
						strcpy(gtpSession->sgsnCtlIPAddr, msgObj->gtpcSgsnAddrCtl);
						strcpy(gtpSession->sgsnDataIPAddr, msgObj->gtpcSgsnAddrData);
						break;

			case GTPV1_DELETE_PDP_RESPONSE:
						gtpSession->ByteSizeDL 				= msgObj->gtpcMsgLen;
						gtpSession->pkt_tunnel_id_dn = msgObj->gtpcPktTunnelId;
						gtpSession->tunnel_id_control_dn 	= msgObj->gtpcPktTunnelId;
						break;
		}
	}
}

/*
 * Create Global Session Procedure
 */
VOID GTPSessionManager::createGlobalSession(GTPSession *pGtpSession)
{
	int glbIndex = -1;
	uint32_t teidIndex = 0;
	bool reusingGlobal = true;


	if(pGtpSession->tunnel_id_control_up == 0 || pGtpSession->tunnel_id_data_up == 0 || pGtpSession->tunnel_id_control_dn == 0 || pGtpSession->tunnel_id_data_dn == 0)
	{
		TheLog_nc_v5(Log::Info, name()," INVALID TEID in CR c_up [%u]| d_up [%u]| c_dn [%u]| d_dn [%u] for IMSI [%s]",pGtpSession->tunnel_id_control_up, pGtpSession->tunnel_id_data_up, pGtpSession->tunnel_id_control_dn, pGtpSession->tunnel_id_data_dn, pGtpSession->IMSI);
		return;
	}

//	if(pGtpSession->tunnel_id_control_up == pGtpSession->tunnel_id_data_up)
//	{
//		TheLog_nc_v5(Log::Info, name()," SAME TEID in CR c_up [%u]| d_up [%u]| c_dn [%u]| d_dn [%u] for IMSI [%s]",pGtpSession->tunnel_id_control_up, pGtpSession->tunnel_id_data_up, pGtpSession->tunnel_id_control_dn, pGtpSession->tunnel_id_data_dn, pGtpSession->IMSI);
//	}

	int step = -1;

	std::map<uint32_t, int>::iterator itr;

	if(pGtpSession->tunnel_id_control_up != 0)
	{
		teidIndex = INDEX_TEID(pGtpSession->tunnel_id_control_up);
		itr = GTPStore::GTPGlbMap_CTL_UP[teidIndex].find(pGtpSession->tunnel_id_control_up);
		if (itr != GTPStore::GTPGlbMap_CTL_UP[teidIndex].end())
		{
			glbIndex = itr->second;
			step = 1;
		}
	}

	if(glbIndex == -1 && pGtpSession->tunnel_id_control_dn != 0)
	{
		teidIndex = INDEX_TEID(pGtpSession->tunnel_id_control_dn);
		itr = GTPStore::GTPGlbMap_CTL_DW[teidIndex].find(pGtpSession->tunnel_id_control_dn);
		if (itr != GTPStore::GTPGlbMap_CTL_DW[teidIndex].end())
		{
			glbIndex = itr->second;
			step = 2;
		}
	}

	if(glbIndex == -1 && pGtpSession->tunnel_id_data_up != 0)
	{
		teidIndex = INDEX_TEID(pGtpSession->tunnel_id_data_up);
		itr = GTPStore::GTPGlbMap_DATA_UP[teidIndex].find(pGtpSession->tunnel_id_data_up);
		if (itr != GTPStore::GTPGlbMap_DATA_UP[teidIndex].end())
		{
			glbIndex = itr->second;
			step = 3;
		}
	}

	if(glbIndex == -1 && pGtpSession->tunnel_id_data_dn != 0)
	{
		teidIndex = INDEX_TEID(pGtpSession->tunnel_id_data_dn);
		itr = GTPStore::GTPGlbMap_DATA_DW[teidIndex].find(pGtpSession->tunnel_id_data_dn);
		if (itr != GTPStore::GTPGlbMap_DATA_DW[teidIndex].end())
		{
			glbIndex = itr->second;
			step = 4;
		}
	}

	if(glbIndex == -1)
	{
		//Existing glbIndex not found, get one
		glbIndex = getGlbFreeIndex();
		reusingGlobal = false;
		step = 0;
//		activeSessionCntTotal++;
//		if(pGtpSession->RAT == 1)
//			activeSessionCntUtran++;
//		else if (pGtpSession->RAT == 2)
//			activeSessionCntGeran++;
	}

	int arrid = glbIndex / GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
	int elemid = glbIndex % GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;


//	if(step > 0)
//	{
//		GTPSession *pGlbSession = GTPStore::GTPGlbSession[arrid][elemid];
//		TheLog_nc_v6(Log::Info, name()," Duplicate TEID in Step [%d] NEW c_up [%u]| d_up [%u]| c_dn [%u]| d_dn [%u] for IMSI [%s]",step, pGtpSession->tunnel_id_control_up, pGtpSession->tunnel_id_data_up, pGtpSession->tunnel_id_control_dn, pGtpSession->tunnel_id_data_dn, pGtpSession->IMSI);
//		TheLog_nc_v5(Log::Info, name()," Duplicate TEID in Step [%d] NEW GGSN_MAC [%s]| SGSN_MAC [%s]| GGSN_IP [%u] SGSN_IP [%u]",step, pGtpSession->ggsnMACAddr, pGtpSession->sgsnMACAddr, pGtpSession->ggsnIPAddr, pGtpSession->sgsnIPAddr);
//
//		TheLog_nc_v6(Log::Info, name()," Duplicate TEID in Step [%d] OLD c_up [%u]| d_up [%u]| c_dn [%u]| d_dn [%u] for IMSI [%s]",step, pGlbSession->tunnel_id_control_up, pGlbSession->tunnel_id_data_up, pGlbSession->tunnel_id_control_dn, pGlbSession->tunnel_id_data_dn, pGlbSession->IMSI);
//		TheLog_nc_v5(Log::Info, name()," Duplicate TEID in Step [%d] OLD GGSN_MAC [%s]| SGSN_MAC [%s]| GGSN_IP [%u] SGSN_IP [%u]",step, pGlbSession->ggsnMACAddr, pGlbSession->sgsnMACAddr, pGlbSession->ggsnIPAddr, pGlbSession->sgsnIPAddr);
//	}


	if(reusingGlobal)
	{
		GTPSession *pGtpGlobalSession = GTPStore::GTPGlbSession[arrid][elemid];
		//Delete old TEID entries
		GTPStore::GTPGlbMap_CTL_UP[INDEX_TEID(pGtpGlobalSession->tunnel_id_control_up)].erase(pGtpGlobalSession->tunnel_id_control_up);
		GTPStore::GTPGlbMap_CTL_DW[INDEX_TEID(pGtpGlobalSession->tunnel_id_control_dn)].erase(pGtpGlobalSession->tunnel_id_control_dn);
		GTPStore::GTPGlbMap_DATA_UP[INDEX_TEID(pGtpGlobalSession->tunnel_id_data_up)].erase(pGtpGlobalSession->tunnel_id_data_up);
		GTPStore::GTPGlbMap_DATA_DW[INDEX_TEID(pGtpGlobalSession->tunnel_id_data_dn)].erase(pGtpGlobalSession->tunnel_id_data_dn);

		strcpy(pGtpSession->IMSI_OLD, pGtpGlobalSession->IMSI);
//		pGtpSession->old_tunnel_id_control_up = pGtpGlobalSession->tunnel_id_control_up;
//		pGtpSession->old_tunnel_id_data_up = pGtpGlobalSession->tunnel_id_data_up;
//		pGtpSession->old_tunnel_id_control_dn = pGtpGlobalSession->tunnel_id_control_dn;
//		pGtpSession->old_tunnel_id_data_dn = pGtpGlobalSession->tunnel_id_data_dn;
//		pGtpSession->old_sgsnIPAddr = pGtpGlobalSession->sgsnIPAddr;
//		pGtpSession->old_ggsnIPAddr = pGtpGlobalSession->ggsnIPAddr;
//		strcpy(pGtpSession->old_sgsnMACAddr, pGtpGlobalSession->sgsnMACAddr);
//		strcpy(pGtpSession->old_ggsnMACAddr, pGtpGlobalSession->ggsnMACAddr);
//		pGtpSession->old_sequence_no = pGtpGlobalSession->sequence_no;
//		pGtpSession->old_StartTimeEpochNanoSec = pGtpGlobalSession->StartTimeEpochNanoSec;

		int teidIndex = 0;
		std::map<uint32_t, GTPSession>::iterator itrLku;

		if(pGtpGlobalSession->tunnel_id_data_up != pGtpSession->tunnel_id_data_up)
		{
			teidIndex = INDEX_TEID(pGtpGlobalSession->tunnel_id_data_up);
			itrLku = GTPStore::GTPGlbMap_LKU_DATA_UP[teidIndex].find(pGtpGlobalSession->tunnel_id_data_up);
			if( itrLku != GTPStore::GTPGlbMap_LKU_DATA_UP[teidIndex].end()){
				GTPStore::GTPGlbMap_LKU_DATA_UP[teidIndex][pGtpGlobalSession->tunnel_id_data_up].expiredFlag = true;
				GTPStore::GTPGlbMap_LKU_DATA_UP[teidIndex][pGtpGlobalSession->tunnel_id_data_up].expiredTimeEpochSec = processStartEpochSec;
			}
		}
		if(pGtpGlobalSession->tunnel_id_data_dn != pGtpSession->tunnel_id_data_dn)
		{
			teidIndex = INDEX_TEID(pGtpGlobalSession->tunnel_id_data_dn);
			itrLku = GTPStore::GTPGlbMap_LKU_DATA_DW[teidIndex].find(pGtpGlobalSession->tunnel_id_data_dn);
			if( itrLku != GTPStore::GTPGlbMap_LKU_DATA_DW[teidIndex].end()){
				GTPStore::GTPGlbMap_LKU_DATA_DW[teidIndex][pGtpGlobalSession->tunnel_id_data_dn].expiredFlag = true;
				GTPStore::GTPGlbMap_LKU_DATA_DW[teidIndex][pGtpGlobalSession->tunnel_id_data_dn].expiredTimeEpochSec = processStartEpochSec;
			}
		}
	}

	pGtpSession->active_session = true;
	pGtpSession->lastActivityTime = pGtpSession->EndTimeEpochSec;
	pGtpSession->lastActivityTimeGtpc = pGtpSession->EndTimeEpochSec;

	pGtpSession->create_step = step;

	GTPStore::GTPGlbSession[arrid][elemid]->copy(pGtpSession);

	if(pGtpSession->tunnel_id_control_up != 0)
		GTPStore::GTPGlbMap_CTL_UP[INDEX_TEID(pGtpSession->tunnel_id_control_up)][pGtpSession->tunnel_id_control_up] = glbIndex;

	if(pGtpSession->tunnel_id_data_up != 0){
		GTPStore::GTPGlbMap_DATA_UP[INDEX_TEID(pGtpSession->tunnel_id_data_up)][pGtpSession->tunnel_id_data_up]	= glbIndex;
		//if(strlen(pGtpSession->IMSI) >= 15 || pGtpSession->CI != 0)
			GTPStore::GTPGlbMap_LKU_DATA_UP[INDEX_TEID(pGtpSession->tunnel_id_data_up)][pGtpSession->tunnel_id_data_up].copy(pGtpSession);
	}

	if(pGtpSession->tunnel_id_control_dn != 0)
		GTPStore::GTPGlbMap_CTL_DW[INDEX_TEID(pGtpSession->tunnel_id_control_dn)][pGtpSession->tunnel_id_control_dn] = glbIndex;

	if(pGtpSession->tunnel_id_data_dn != 0){
		GTPStore::GTPGlbMap_DATA_DW[INDEX_TEID(pGtpSession->tunnel_id_data_dn)][pGtpSession->tunnel_id_data_dn]	= glbIndex;
		//if(strlen(pGtpSession->IMSI) >= 15 || pGtpSession->CI != 0)
			GTPStore::GTPGlbMap_LKU_DATA_DW[INDEX_TEID(pGtpSession->tunnel_id_data_dn)][pGtpSession->tunnel_id_data_dn].copy(pGtpSession);
	}

}


VOID GTPSessionManager::updateGlobalSession(GTPSession *pGtpSession, MPacket *msgObj)
{

	int glbIndex = -1;
	bool glbFound = false;
	uint32_t old_teid_ctl_up = 0;
	uint32_t old_teid_data_up = 0;
	uint32_t old_teid_ctl_dn = 0;
	uint32_t old_teid_data_dn = 0;

	GTPStats::gtp_glb_sessions_op_up_cnt++;

	GTPSession *pGlbSession = NULL;

	if(pGtpSession->pkt_tunnel_id_up > 0)
		glbIndex = getGlobalIndex(pGtpSession->pkt_tunnel_id_up, CTL_DW);
	if(glbIndex == -1)
	{
		if(pGtpSession->pkt_tunnel_id_dn > 0)
			glbIndex = getGlobalIndex(pGtpSession->pkt_tunnel_id_dn, CTL_UP);
	}

	if(glbIndex >= 0)
	{
		int arrid = glbIndex / GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
		int bitid = glbIndex % GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;

		std::map<int, GTPSession*>::iterator itrGlb = GTPStore::GTPGlbSession[arrid].find(bitid);

		if(itrGlb != GTPStore::GTPGlbSession[arrid].end())
		{
			pGlbSession = itrGlb->second;

			old_teid_ctl_up = pGlbSession->tunnel_id_control_up;
			old_teid_data_up = pGlbSession->tunnel_id_data_up;
			old_teid_ctl_dn = pGlbSession->tunnel_id_control_dn;
			old_teid_data_dn = pGlbSession->tunnel_id_data_dn;

//			//Keep a copy of the old session if data_up changed and data_dw is same for look-up of old GTPU packets
//			if(pGtpSession->tunnel_id_data_up != 0 &&
//					pGlbSession->tunnel_id_data_up != pGtpSession->tunnel_id_data_up)
//			{
//				if(pGtpSession->tunnel_id_data_dn != 0 &&
//						pGlbSession->tunnel_id_data_dn == pGtpSession->tunnel_id_data_dn)
//				{
//
//				}
//
//			}


			glbFound = true;
			pGlbSession->active_session = true;
			pGlbSession->lastActivityTime = pGtpSession->EndTimeEpochSec;
			pGlbSession->lastActivityTimeGtpc = pGtpSession->EndTimeEpochSec;

			if(pGtpSession->RAT != 0){
				pGtpSession->RATOld = pGlbSession->RAT;
				pGlbSession->RATOld = pGlbSession->RAT;
				pGlbSession->RAT = pGtpSession->RAT;
			}

			if(pGtpSession->CI != 0) {
				pGlbSession->CI = pGtpSession->CI;
				pGlbSession->LAC = pGtpSession->LAC;
				pGlbSession->MCC = pGtpSession->MCC;
				pGlbSession->MNC = pGtpSession->MNC;
			}

			if(pGlbSession->req_mbrupl != pGtpSession->req_mbrupl)
				pGlbSession->req_mbrupl = pGtpSession->req_mbrupl;

			if(pGlbSession->res_mbrupl != pGtpSession->res_mbrupl)
				pGlbSession->res_mbrupl = pGtpSession->res_mbrupl;

			if(pGlbSession->req_mbrdnl != pGtpSession->req_mbrdnl)
				pGlbSession->req_mbrdnl = pGtpSession->req_mbrdnl;

			if(pGlbSession->res_mbrdnl != pGtpSession->res_mbrdnl)
				pGlbSession->res_mbrdnl = pGtpSession->res_mbrdnl;

			if(pGlbSession->req_ext_mbrdnl != pGtpSession->req_ext_mbrdnl)
				pGlbSession->req_ext_mbrdnl = pGtpSession->req_ext_mbrdnl;

			if(pGlbSession->res_ext_mbrdnl != pGtpSession->res_ext_mbrdnl)
				pGlbSession->res_ext_mbrdnl = pGtpSession->res_ext_mbrdnl;

			//Now delete the old TEID present in Global session and update with the newly allocated TEID
			if(pGtpSession->tunnel_id_control_up != 0 &&
					old_teid_ctl_up != pGtpSession->tunnel_id_control_up)
			{
				pGlbSession->tunnel_id_control_up = pGtpSession->tunnel_id_control_up;

				GTPStore::GTPGlbMap_CTL_UP[INDEX_TEID(old_teid_ctl_up)].erase(old_teid_ctl_up);
				GTPStore::GTPGlbMap_CTL_UP[INDEX_TEID(pGlbSession->tunnel_id_control_up)][pGlbSession->tunnel_id_control_up] = glbIndex;
			}
			if(pGtpSession->tunnel_id_data_up != 0 &&
					old_teid_data_up != pGtpSession->tunnel_id_data_up)
			{
				pGlbSession->tunnel_id_data_up = pGtpSession->tunnel_id_data_up;

				GTPStore::GTPGlbMap_DATA_UP[INDEX_TEID(old_teid_data_up)].erase(old_teid_data_up);
				GTPStore::GTPGlbMap_DATA_UP[INDEX_TEID(pGlbSession->tunnel_id_data_up)][pGlbSession->tunnel_id_data_up] = glbIndex;
			}

			if(pGtpSession->tunnel_id_control_dn != 0 &&
					old_teid_ctl_dn != pGtpSession->tunnel_id_control_dn)
			{
				pGlbSession->tunnel_id_control_dn = pGtpSession->tunnel_id_control_dn;

				GTPStore::GTPGlbMap_CTL_DW[INDEX_TEID(old_teid_ctl_dn)].erase(old_teid_ctl_dn);
				GTPStore::GTPGlbMap_CTL_DW[INDEX_TEID(pGlbSession->tunnel_id_control_dn)][pGlbSession->tunnel_id_control_dn] = glbIndex;
			}

			if(pGtpSession->tunnel_id_data_dn != 0 &&
					old_teid_data_dn != pGtpSession->tunnel_id_data_dn)
			{
				pGlbSession->tunnel_id_data_dn = pGtpSession->tunnel_id_data_dn;

				GTPStore::GTPGlbMap_DATA_DW[INDEX_TEID(old_teid_data_dn)].erase(old_teid_data_dn);
				GTPStore::GTPGlbMap_DATA_DW[INDEX_TEID(pGlbSession->tunnel_id_data_dn)][pGlbSession->tunnel_id_data_dn] = glbIndex;
			}

			//Once global session is updated with new values, update the lookup Maps
			if(strlen(pGlbSession->IMSI) >= 15 || pGlbSession->CI != 0)
			{
				GTPStore::GTPGlbMap_LKU_DATA_UP[INDEX_TEID(pGlbSession->tunnel_id_data_up)][pGlbSession->tunnel_id_data_up].copy(pGlbSession);
				GTPStore::GTPGlbMap_LKU_DATA_DW[INDEX_TEID(pGlbSession->tunnel_id_data_dn)][pGlbSession->tunnel_id_data_dn].copy(pGlbSession);
			}

			if(old_teid_data_up != 0 && old_teid_data_up != pGtpSession->tunnel_id_data_up)
			{
				int teidIndex = INDEX_TEID(old_teid_data_up);
				std::map<uint32_t, GTPSession>::iterator itrLku = GTPStore::GTPGlbMap_LKU_DATA_UP[teidIndex].find(old_teid_data_up);
				if( itrLku != GTPStore::GTPGlbMap_LKU_DATA_UP[teidIndex].end()){
					GTPStore::GTPGlbMap_LKU_DATA_UP[teidIndex][old_teid_data_up].expiredFlag = true;
					GTPStore::GTPGlbMap_LKU_DATA_UP[teidIndex][old_teid_data_up].expiredTimeEpochSec = processStartEpochSec;
					GTPStore::GTPGlbMap_LKU_DATA_UP[teidIndex][old_teid_data_up].lastActivityTime = processStartEpochSec;
				}
			}

			if(old_teid_data_dn != 0 && old_teid_data_dn != pGtpSession->tunnel_id_data_dn)
			{
				int teidIndex = INDEX_TEID(old_teid_data_dn);
				std::map<uint32_t, GTPSession>::iterator itrLku = GTPStore::GTPGlbMap_LKU_DATA_DW[teidIndex].find(old_teid_data_dn);
				if( itrLku != GTPStore::GTPGlbMap_LKU_DATA_DW[teidIndex].end()){
					GTPStore::GTPGlbMap_LKU_DATA_DW[teidIndex][old_teid_data_dn].expiredFlag = true;
					GTPStore::GTPGlbMap_LKU_DATA_DW[teidIndex][old_teid_data_dn].expiredTimeEpochSec = processStartEpochSec;
					GTPStore::GTPGlbMap_LKU_DATA_DW[teidIndex][old_teid_data_dn].lastActivityTime = processStartEpochSec;
				}
			}

			strcpy(pGtpSession->IMSI, pGlbSession->IMSI);
			strcpy(pGtpSession->IMEI, pGlbSession->IMEI);
			strcpy(pGtpSession->MSISDN, pGlbSession->MSISDN);

		}
	}


//	printf("*** Before IMSI::%s| RAT::%d| CI::%d\n", pGtpSession->IMSI, pGtpSession->RAT, pGtpSession->CI);
//	if(glbFound && pGlbSession != NULL) {
//		strcpy(pGtpSession->IMSI, pGlbSession->IMSI);
//		strcpy(pGtpSession->IMEI, pGlbSession->IMEI);
//		strcpy(pGtpSession->MSISDN, pGlbSession->MSISDN);
//		pGtpSession->RAT = pGlbSession->RAT;
//		pGtpSession->MCC = pGlbSession->MCC;
//		pGtpSession->MNC = pGlbSession->MNC;
//		pGtpSession->LAC = pGlbSession->LAC;
//		pGtpSession->CI = pGlbSession->CI;
//		pGtpSession->req_mbrupl = pGlbSession->req_mbrupl;
//		pGtpSession->res_mbrupl = pGlbSession->res_mbrupl;
//		pGtpSession->req_mbrdnl = pGlbSession->req_mbrdnl;
//		pGtpSession->res_mbrdnl = pGlbSession->res_mbrdnl;
//		pGtpSession->active_session = pGlbSession->active_session;
//		pGtpSession->lastActivityTime = pGlbSession->lastActivityTime;
//		pGtpSession->lastActivityTimeGtpc = pGlbSession->lastActivityTimeGtpc;
//		pGtpSession->lastActivityTimeGtpu = pGlbSession->lastActivityTimeGtpu;
//		printf("*** After IMSI::%s| RAT::%d| CI::%d\n", pGtpSession->IMSI, pGtpSession->RAT, pGtpSession->CI);
//	}

}



/*
 * Remore Global Session Store Procedure
 */
VOID GTPSessionManager::removeGlobalSession(GTPSession *pGtpSession)
{
	int glbIndex = -1;

	glbIndex = getGlobalIndex(pGtpSession->tunnel_id_control_up, CTL_DW);
//	if(glbIndex == -1)
//		glbIndex = getGlobalIndex(pGtpSession->tunnel_id_control_up, CTL_UP);
	if(glbIndex == -1)
		glbIndex = getGlobalIndex(pGtpSession->tunnel_id_control_dn, CTL_UP);
//	if(glbIndex == -1)
//		glbIndex = getGlobalIndex(pGtpSession->tunnel_id_control_dn, CTL_DW);

	if(glbIndex == -1) return;

	GTPSession *pGtpGlobalSession = GTPStore::GTPGlbSession[glbIndex / GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS][glbIndex % GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS];
	if(pGtpGlobalSession != NULL) {
		strcpy(pGtpSession->IMSI, pGtpGlobalSession->IMSI);
		strcpy(pGtpSession->IMEI, pGtpGlobalSession->IMEI);
		strcpy(pGtpSession->MSISDN, pGtpGlobalSession->MSISDN);
		pGtpSession->RAT = pGtpGlobalSession->RAT;
		pGtpSession->RATOld = pGtpGlobalSession->RATOld;
		pGtpSession->MCC = pGtpGlobalSession->MCC;
		pGtpSession->MNC = pGtpGlobalSession->MNC;
		pGtpSession->LAC = pGtpGlobalSession->LAC;
		pGtpSession->CI = pGtpGlobalSession->CI;
		if(pGtpSession->EndCauseId == ACCEPT){
			pGtpGlobalSession->active_session = false;
			pGtpGlobalSession->lastActivityTime = pGtpSession->EndTimeEpochSec;
			pGtpGlobalSession->lastActivityTimeGtpc = pGtpSession->EndTimeEpochSec;
//			pGtpGlobalSession->deleteTimeEpochSec = pGtpSession->EndTimeEpochSec;
		}

		deleteGlobalSession(glbIndex, pGtpGlobalSession);
	}
}


VOID GTPSessionManager::deleteGlobalSession(int glbIndex, GTPSession *pGtpGlobalSession)
{
	if(pGtpGlobalSession->tunnel_id_data_up != 0)
	{
		int tIndex = INDEX_TEID(pGtpGlobalSession->tunnel_id_data_up);
		std::map<uint32_t, GTPSession>::iterator itrLku = GTPStore::GTPGlbMap_LKU_DATA_UP[tIndex].find(pGtpGlobalSession->tunnel_id_data_up);
		if( itrLku != GTPStore::GTPGlbMap_LKU_DATA_UP[tIndex].end()){
			GTPStore::GTPGlbMap_LKU_DATA_UP[tIndex][pGtpGlobalSession->tunnel_id_data_up].expiredFlag = true;
			GTPStore::GTPGlbMap_LKU_DATA_UP[tIndex][pGtpGlobalSession->tunnel_id_data_up].expiredTimeEpochSec = processStartEpochSec;
			GTPStore::GTPGlbMap_LKU_DATA_UP[tIndex][pGtpGlobalSession->tunnel_id_data_up].lastActivityTime = processStartEpochSec;
		}
	}
	if(pGtpGlobalSession->tunnel_id_data_dn != 0)
	{
		int tIndex = INDEX_TEID(pGtpGlobalSession->tunnel_id_data_dn);
		std::map<uint32_t, GTPSession>::iterator itrLku = GTPStore::GTPGlbMap_LKU_DATA_DW[tIndex].find(pGtpGlobalSession->tunnel_id_data_dn);
		if( itrLku != GTPStore::GTPGlbMap_LKU_DATA_DW[tIndex].end()){
			GTPStore::GTPGlbMap_LKU_DATA_DW[tIndex][pGtpGlobalSession->tunnel_id_data_dn].expiredFlag = true;
			GTPStore::GTPGlbMap_LKU_DATA_DW[tIndex][pGtpGlobalSession->tunnel_id_data_dn].expiredTimeEpochSec = processStartEpochSec;
			GTPStore::GTPGlbMap_LKU_DATA_DW[tIndex][pGtpGlobalSession->tunnel_id_data_dn].lastActivityTime = processStartEpochSec;
		}
	}

	GTPStore::GTPGlbMap_CTL_UP[INDEX_TEID(pGtpGlobalSession->tunnel_id_control_up)].erase(pGtpGlobalSession->tunnel_id_control_up);
	GTPStore::GTPGlbMap_CTL_DW[INDEX_TEID(pGtpGlobalSession->tunnel_id_control_dn)].erase(pGtpGlobalSession->tunnel_id_control_dn);
	GTPStore::GTPGlbMap_DATA_UP[INDEX_TEID(pGtpGlobalSession->tunnel_id_data_up)].erase(pGtpGlobalSession->tunnel_id_data_up);
	GTPStore::GTPGlbMap_DATA_DW[INDEX_TEID(pGtpGlobalSession->tunnel_id_data_dn)].erase(pGtpGlobalSession->tunnel_id_data_dn);
	releaseGlbIndex(glbIndex);

}


VOID GTPSessionManager::getGTPcLocalSessionCount()
{
	switch(instanceId)
	{
		case 0:
			GTPStats::gtp_pdp_cr_session_sm_0 = GTPcMapCR.size();
			GTPStats::gtp_pdp_up_session_sm_0 = GTPcMapUP_E.size() + GTPcMapUP_Z.size();
			GTPStats::gtp_pdp_dl_session_sm_0 = GTPcMapDL_E.size() + GTPcMapDL_Z.size();
			break;

//		case 1:
//			GTPStats::gtp_pdp_cr_session_sm_1 = GTPcMapCR.size();
//			GTPStats::gtp_pdp_up_session_sm_1 = GTPcMapUP.size();
//			GTPStats::gtp_pdp_dl_session_sm_1 = GTPcMapDL.size();
//			break;
//
//		case 2:
//			GTPStats::gtp_pdp_cr_session_sm_2 = GTPcMapCR.size();
//			GTPStats::gtp_pdp_up_session_sm_2 = GTPcMapUP.size();
//			GTPStats::gtp_pdp_dl_session_sm_2 = GTPcMapDL.size();
//			break;
//
//		case 3:
//			GTPStats::gtp_pdp_cr_session_sm_3 = GTPcMapCR.size();
//			GTPStats::gtp_pdp_up_session_sm_3 = GTPcMapUP.size();
//			GTPStats::gtp_pdp_dl_session_sm_3 = GTPcMapDL.size();
//			break;
//
//		case 4:
//			GTPStats::gtp_pdp_cr_session_sm_4 = GTPcMapCR.size();
//			GTPStats::gtp_pdp_up_session_sm_4 = GTPcMapUP.size();
//			GTPStats::gtp_pdp_dl_session_sm_4 = GTPcMapDL.size();
//			break;
	}
}


VOID GTPSessionManager::getGlobalSessionCount()
{
	GTPStats::gtp_glb_sessions_cnt_process = true;

//	GTPStats::gtp_glb_sessions_cnt = 0;
	GTPStats::gtp_glb_active_sessions_cnt = 0;
	GTPStats::gtp_glb_sessions_total_cnt = 0;
	GTPStats::gtp_glb_sessions_utran_cnt = 0;
	GTPStats::gtp_glb_sessions_geran_cnt = 0;

	for(int i = 0; i< GTP_GLB_SESSION_POOL_ARRAY_SIZE; i++) {
		for(int n = 0; n< GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS; n++) {

			if(GTPStore::bitFlags[i].test(n))
				GTPStats::gtp_glb_active_sessions_cnt++;

			if( GTPStore::GTPGlbSession[i][n]->active_session && (strlen(GTPStore::GTPGlbSession[i][n]->IMSI) >= 15 || GTPStore::GTPGlbSession[i][n]->RAT != 0 || GTPStore::GTPGlbSession[i][n]->CI != 0)){
//				GTPStats::gtp_glb_sessions_cnt++;
				GTPStats::gtp_glb_sessions_total_cnt++;
				if(GTPStore::GTPGlbSession[i][n]->RAT == 1)
					GTPStats::gtp_glb_sessions_utran_cnt++;
				else
					GTPStats::gtp_glb_sessions_geran_cnt++;
//				if(GTPStore::GTPGlbSession[i][n]->active_session)
//					GTPStats::gtp_glb_active_sessions_cnt++;
			}
		}
	}


//	//Get peak of this minute's session count
//	GTPStats::gtp_glb_sessions_total_cnt = 0;
//	GTPStats::gtp_glb_sessions_utran_cnt = 0;
//	GTPStats::gtp_glb_sessions_geran_cnt = 0;
//
//	for(int i=0; i<60; i++){
//		if(GTPStats::gtp_glb_sessions_total_cnt < GTPStats::gtp_glb_sessions_total[i])
//			GTPStats::gtp_glb_sessions_total_cnt = GTPStats::gtp_glb_sessions_total[i];
//
//		if(GTPStats::gtp_glb_sessions_utran_cnt < GTPStats::gtp_glb_sessions_utran[i])
//			GTPStats::gtp_glb_sessions_utran_cnt = GTPStats::gtp_glb_sessions_utran[i];
//
//		if(GTPStats::gtp_glb_sessions_geran_cnt < GTPStats::gtp_glb_sessions_geran[i])
//			GTPStats::gtp_glb_sessions_geran_cnt = GTPStats::gtp_glb_sessions_geran[i];
//
//	}

	GTPStats::gtp_glb_ctl_up_cnt = 0;
	GTPStats::gtp_glb_data_up_cnt = 0;
	GTPStats::gtp_glb_ctl_dn_cnt = 0;
	GTPStats::gtp_glb_data_dn_cnt = 0;

	for(int i=0; i<GTP_GLB_SESSION_TEID_ARRAY_SIZE; i++)
	{
		GTPStats::gtp_glb_ctl_up_cnt += GTPStore::GTPGlbMap_CTL_UP[i].size();
		GTPStats::gtp_glb_data_up_cnt += GTPStore::GTPGlbMap_DATA_UP[i].size();
		GTPStats::gtp_glb_ctl_dn_cnt += GTPStore::GTPGlbMap_CTL_DW[i].size();
		GTPStats::gtp_glb_data_dn_cnt += GTPStore::GTPGlbMap_DATA_DW[i].size();
	}

	GTPStats::unique_imsi_cnt = GTPStore::GTPGlb_IMSI_MAP.size();

	GTPStats::gtp_glb_sessions_cnt_process = false;
}


VOID GTPSessionManager::getGlobalLkuSessionCount()
{
	GTPStats::gtp_glb_lku_up_sessions_cnt = 0;
	GTPStats::gtp_glb_lku_up_active_sessions_cnt = 0;
	GTPStats::gtp_glb_lku_dn_sessions_cnt = 0;
	GTPStats::gtp_glb_lku_dn_active_sessions_cnt = 0;

	for(int i = 0; i< GTP_GLB_SESSION_TEID_ARRAY_SIZE; i++) {

		GTPStats::gtp_glb_lku_up_sessions_cnt += GTPStore::GTPGlbMap_LKU_DATA_UP[i].size();
		GTPStats::gtp_glb_lku_dn_sessions_cnt += GTPStore::GTPGlbMap_LKU_DATA_DW[i].size();

		for(auto elem : GTPStore::GTPGlbMap_LKU_DATA_UP[i])
		{
			if(!elem.second.expiredFlag)
				GTPStats::gtp_glb_lku_up_active_sessions_cnt++;
		}

		for(auto elem : GTPStore::GTPGlbMap_LKU_DATA_DW[i])
		{
			if(!elem.second.expiredFlag)
				GTPStats::gtp_glb_lku_dn_active_sessions_cnt++;
		}
	}
}

VOID GTPSessionManager::cleanUpGTPcGlobalSessions(long curTimeEpochSec)
{

	//Cleanup sessions that are in-active for more than 12 Hours
	int cleanTEIDArray_cnt = 0;

	GTPStats::gtp_glb_inactive_session_cln_cnt = 0;
	for(int i = 0; i< GTP_GLB_SESSION_TEID_ARRAY_SIZE; i++)
	{
		for(auto elem : GTPStore::GTPGlbSession[i])
		{
			if(curTimeEpochSec - elem.second->lastActivityTime >= GContainer::config->gtpConfig->GN_GTPC_GLOBAL_SESSION_CLEANUP_TIMEOUT_SEC)
			{
				deleteGlobalSession(elem.first, elem.second);
				cleanTEIDArray_cnt++;
			}
		}
	}
	GTPStats::gtp_glb_inactive_session_cln_cnt = cleanTEIDArray_cnt;
	TheLog_nc_v1(Log::Info, name(),"  GTPGlbSession cleanup done for [%u] records", GTPStats::gtp_glb_inactive_session_cln_cnt);
}

VOID GTPSessionManager::cleanUpGTPcLkuSessions()
{

	int cleanTEIDArray_cnt = 0;

	GTPStats::gtp_glb_lku_up_sessions_cln_cnt = 0;
	for(int i = 0; i< GTP_GLB_SESSION_TEID_ARRAY_SIZE; i++)
	{
		for(auto elem : GTPStore::GTPGlbMap_LKU_DATA_UP[i])
		{
//			if(elem.second.lastActivityTime > 0 && processStartEpochSec - elem.second.lastActivityTime > 4800)
			if(processStartEpochSec - elem.second.lastActivityTime > 4800)
			{
//				if(elem.second.expiredFlag && (processStartEpochSec - elem.second.expiredTimeEpochSec > 4800))
//				{
					cleanUpmap[cleanTEIDArray_cnt].index = i;
					cleanUpmap[cleanTEIDArray_cnt].tunnel_id = elem.first;
					cleanTEIDArray_cnt++;
					if(cleanTEIDArray_cnt >= GTPC_GLB_CLEAN_BATCH_LIMIT)
						break;
//				}
			}
		}
	}
	for(int i = 0; i< cleanTEIDArray_cnt; i++)
	{
		GTPStore::GTPGlbMap_LKU_DATA_UP[cleanUpmap[i].index].erase(cleanUpmap[i].tunnel_id);
	}
	GTPStats::gtp_glb_lku_up_sessions_cln_cnt = cleanTEIDArray_cnt;
	cleanUpmap.clear();
	cleanTEIDArray_cnt = 0;


	GTPStats::gtp_glb_lku_dn_sessions_cln_cnt = 0;
	for(int i = 0; i< GTP_GLB_SESSION_TEID_ARRAY_SIZE; i++)
	{
		for(auto elem : GTPStore::GTPGlbMap_LKU_DATA_DW[i])
		{
//			if(elem.second.lastActivityTime > 0 && processStartEpochSec - elem.second.lastActivityTime > 4800)
			if(processStartEpochSec - elem.second.lastActivityTime > 4800)
			{
//				if(elem.second.expiredFlag && (processStartEpochSec - elem.second.expiredTimeEpochSec > 4800))
//				{
				cleanUpmap[cleanTEIDArray_cnt].index = i;
				cleanUpmap[cleanTEIDArray_cnt].tunnel_id = elem.first;
				cleanTEIDArray_cnt++;
				if(cleanTEIDArray_cnt >= GTPC_GLB_CLEAN_BATCH_LIMIT)
					break;
//				}
			}
		}
	}
	for(int i = 0; i< cleanTEIDArray_cnt; i++)
	{
		GTPStore::GTPGlbMap_LKU_DATA_DW[cleanUpmap[i].index].erase(cleanUpmap[i].tunnel_id);
	}
	GTPStats::gtp_glb_lku_dn_sessions_cln_cnt = cleanTEIDArray_cnt;
	cleanUpmap.clear();
	cleanTEIDArray_cnt = 0;

	TheLog_nc_v3(Log::Info, name()," [%d] GTPGlbMap_LKU_DATA cleanup done UP [%u] | DN [%u] records", instanceId, GTPStats::gtp_glb_lku_up_sessions_cln_cnt, GTPStats::gtp_glb_lku_dn_sessions_cln_cnt);

}

//VOID GTPSessionManager::cleanUpLkuGlobalSessions()
//{
//	GTPStats::gtp_glb_sessions_dl_cln_cnt = 0;
//
//	uint32_t cleanTEIDArray[GTPC_GLB_CLEAN_BATCH_LIMIT];
//	int cleanTEIDArray_cnt = 0;
//
//	for(auto elem : GTPStore::GTPGlbMap_DL_DATA_UP)
//	{
//		if(processStartEpochSec - elem.second.deleteTimeEpochSec > 600)
//		{
//			cleanTEIDArray[cleanTEIDArray_cnt] = elem.first;
//			cleanTEIDArray_cnt++;
//			if(cleanTEIDArray_cnt >= GTPC_GLB_CLEAN_BATCH_LIMIT)
//				break;
//		}
//	}
//	for(int i = 0; i< cleanTEIDArray_cnt; i++)
//	{
//		GTPStore::GTPGlbMap_DL_DATA_UP.erase(cleanTEIDArray[i]);
//	}
//	TheLog_nc_v3(Log::Info, name(),"  PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);
//	GTPStats::gtp_glb_sessions_dl_cln_cnt += cleanTEIDArray_cnt;
//	cleanTEIDArray_cnt = 0;
//
//
//	for(auto elem : GTPStore::GTPGlbMap_DL_DATA_DW)
//	{
//		if(processStartEpochSec - elem.second.deleteTimeEpochSec > 600)
//		{
//			cleanTEIDArray[cleanTEIDArray_cnt] = elem.first;
//			cleanTEIDArray_cnt++;
//			if(cleanTEIDArray_cnt >= GTPC_GLB_CLEAN_BATCH_LIMIT)
//				break;
//		}
//	}
//	for(int i = 0; i< cleanTEIDArray_cnt; i++)
//	{
//		GTPStore::GTPGlbMap_DL_DATA_DW.erase(cleanTEIDArray[i]);
//	}
//	GTPStats::gtp_glb_sessions_dl_cln_cnt += cleanTEIDArray_cnt;
//	cleanTEIDArray_cnt = 0;
//
//}


uint32_t GTPSessionManager::getGlbFreeIndex()
{
	GTPStore::freeGlbBitPos++;
	if(GTPStore::freeGlbBitPos >= GTPStore::freeGlbBitPosMax) GTPStore::freeGlbBitPos = 0;
	int arrId = GTPStore::freeGlbBitPos / GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
	int bitId = GTPStore::freeGlbBitPos % GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;

	while(GTPStore::bitFlags[arrId].test(bitId)){
		GTPStore::freeGlbBitPos++;
		if(GTPStore::freeGlbBitPos >= GTPStore::freeGlbBitPosMax) GTPStore::freeGlbBitPos = 0;
		arrId = GTPStore::freeGlbBitPos / GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
		bitId = GTPStore::freeGlbBitPos % GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
	}
	if(GTPStore::freeGlbBitPos >= GTPStore::freeGlbBitPosMax){
		printf("[%d] getGlbFreeIndex GTPStore::freeGlbBitPos [%lu] >= GTPStore::freeGlbBitPosMax [%lu]\n",instanceId, GTPStore::freeGlbBitPos, GTPStore::freeGlbBitPosMax);
	}
	GTPStore::bitFlags[arrId].set(bitId);
	GTPStats::gtp_glb_sessions_op_cr_cnt++;
	return GTPStore::freeGlbBitPos;
}

VOID GTPSessionManager::releaseGlbIndex(int glbIndex)
{
	int arrId = glbIndex / GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
	int bitId = glbIndex % GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
	GTPStore::GTPGlbSession[arrId][bitId]->reset();
	GTPStore::bitFlags[arrId].reset(bitId);
	GTPStats::gtp_glb_sessions_op_dl_cnt++;
}



//GTPSession* GTPSessionManager::globalLookup(const uint32_t tunnelId, TIED_TYPE type)
//{
//	std::map<uint32_t, int>::iterator itr;
//	std::map<int, GTPSession*>::iterator itrGlb;
//
//	int arrid = 0;
//	int bitid = 0;
//
//	switch(type)
//	{
//		case CTL_UP:
//		{
//			itr = GTPStore::GTPGlbMap_CTL_UP[INDEX_TEID(tunnelId)].find(tunnelId);
//			if (itr != GTPStore::GTPGlbMap_CTL_UP[INDEX_TEID(tunnelId)].end()){
//				arrid = itr->second / GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
//				bitid = itr->second % GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
//				itrGlb = GTPStore::GTPGlbSession[arrid].find(bitid);
//				if(itrGlb != GTPStore::GTPGlbSession[arrid].end()){
//					return itrGlb->second;
//				}
//			}
//		}
//		break;
//
//		case DATA_UP:
//		{
//			itr = GTPStore::GTPGlbMap_DATA_UP[INDEX_TEID(tunnelId)].find(tunnelId);
//			if (itr != GTPStore::GTPGlbMap_DATA_UP[INDEX_TEID(tunnelId)].end()) {
//				arrid = itr->second / GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
//				bitid = itr->second % GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
//				itrGlb = GTPStore::GTPGlbSession[arrid].find(bitid);
//				if(itrGlb != GTPStore::GTPGlbSession[arrid].end()){
//					return itrGlb->second;
//				}
//			}
//		}
//		break;
//
//		case CTL_DW:
//		{
//			itr = GTPStore::GTPGlbMap_CTL_DW[INDEX_TEID(tunnelId)].find(tunnelId);
//			if (itr != GTPStore::GTPGlbMap_CTL_DW[INDEX_TEID(tunnelId)].end())
//				arrid = itr->second / GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
//				bitid = itr->second % GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
//				itrGlb = GTPStore::GTPGlbSession[arrid].find(bitid);
//				if(itrGlb != GTPStore::GTPGlbSession[arrid].end()){
//					return itrGlb->second;
//				}
//		}
//		break;
//
//		case DATA_DW:
//		{
//			itr = GTPStore::GTPGlbMap_DATA_DW[INDEX_TEID(tunnelId)].find(tunnelId);
//			if (itr != GTPStore::GTPGlbMap_DATA_DW[INDEX_TEID(tunnelId)].end()) {
//				arrid = itr->second / GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
//				bitid = itr->second % GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
//				itrGlb = GTPStore::GTPGlbSession[arrid].find(bitid);
//				if(itrGlb != GTPStore::GTPGlbSession[arrid].end()){
//					return itrGlb->second;
//				}
//			}
//		}
//		break;
//
//		default:
//			break;
//	}
//
//
//	return (NULL);
//}


int GTPSessionManager::getGlobalIndex(const uint32_t tunnelId, TIED_TYPE type)
{
	uint32_t teidIndex = 0;
	std::map<uint32_t, int>::iterator itr;

	if(tunnelId == 0) return -1;

	teidIndex = INDEX_TEID(tunnelId);

	switch(type)
	{
		case CTL_UP:
		{
				itr = GTPStore::GTPGlbMap_CTL_UP[teidIndex].find(tunnelId);
				if (itr != GTPStore::GTPGlbMap_CTL_UP[teidIndex].end())
					return itr->second;
		}
		break;

		case CTL_DW:
		{
				itr = GTPStore::GTPGlbMap_CTL_DW[teidIndex].find(tunnelId);
				if (itr != GTPStore::GTPGlbMap_CTL_DW[teidIndex].end())
					return itr->second;
		}
		break;
		case DATA_UP:
		{
				itr = GTPStore::GTPGlbMap_DATA_UP[teidIndex].find(tunnelId);
				if (itr != GTPStore::GTPGlbMap_DATA_UP[teidIndex].end())
					return itr->second;
		}
		break;

		case DATA_DW:
		{
				itr = GTPStore::GTPGlbMap_DATA_DW[teidIndex].find(tunnelId);
				if (itr != GTPStore::GTPGlbMap_DATA_DW[teidIndex].end())
					return itr->second;
		}
		break;
	}

	return -1;
}


//int GTPSessionManager::getGlobalIndex(uint32_t tunnelId, TIED_TYPE teidType)
//{
//	uint32_t teidIndex = INDEX_TEID(tunnelId);
//
//	std::map<uint32_t, int>::iterator itr;
//
//	if(teidType == DATA)
//	{
//		itr = GTPStore::GTPGlbMap_DATA_UP[teidIndex].find(tunnelId);
//		if (itr != GTPStore::GTPGlbMap_DATA_UP[teidIndex].end())
//			return itr->second;
//		else
//		{
//			itr = GTPStore::GTPGlbMap_DATA_DW[teidIndex].find(tunnelId);
//			if (itr != GTPStore::GTPGlbMap_DATA_DW[teidIndex].end())
//				return itr->second;
//		}
//	}
//	else
//	{
//		itr = GTPStore::GTPGlbMap_CTL_UP[teidIndex].find(tunnelId);
//		if (itr != GTPStore::GTPGlbMap_CTL_UP[teidIndex].end())
//		{
//			return itr->second;
//		}else{
//			itr = GTPStore::GTPGlbMap_CTL_DW[teidIndex].find(tunnelId);
//			if (itr != GTPStore::GTPGlbMap_CTL_DW[teidIndex].end())
//				return itr->second;
//		}
//	}
//
//	return -1;
//}


VOID GTPSessionManager::cleanTimedOutSessionsGTPcv1()
{
	uint32_t cleanedSessionList[GTPC_CLEAN_BATCH_LIMIT];
	int cleanedSessionCnt = 0;
	long curEpochSec = getCurrentEpochSeconds();

	uint128_t curEpochNanoSec = getCurrentEpochMicroSeconds() * 1000;

	uint32_t	key = 0;
	GTPSession *gtpSession;

//	if(instanceId == 0)
//		printf("Instance [%d] GTPcMapCR:: [%d]\n", instanceId, GTPcMapCR.size());

	for(auto elem : GTPcMapCR) {
		key = elem.first;
		gtpSession = &elem.second;

		if( (gtpSession->StartTimeEpochSec > 0 && (curEpochSec - gtpSession->StartTimeEpochSec) > GContainer::config->gtpConfig->GN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC) ||
			(gtpSession->EndTimeEpochSec > 0 && (curEpochSec - gtpSession->EndTimeEpochSec) > GContainer::config->gtpConfig->GN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC) )
		{
			if(gtpSession->EndTimeEpochSec == 0) {
				gtpSession->EndTimeEpochSec 	= curEpochSec;
				gtpSession->EndTimeEpochNanoSec = curEpochNanoSec;
			}

			flushGTPSession(gtpSession,FLUSH_TYPE_CLEANUP);

			cleanedSessionList[cleanedSessionCnt] = key;

			cleanedSessionCnt++;
			if(cleanedSessionCnt >= GTPC_CLEAN_BATCH_LIMIT)
				break;

//			gtpcSessionCleanUpMap[gtpcSessionCleanUpMap_cnt] = key;
//			gtpcSessionCleanUpMap_cnt++;
		}
	}

	for(uint32_t i=0; i<cleanedSessionCnt; i++){
		GTPcMapCR.erase(cleanedSessionList[i]);
		cleanedSessionList[i] = 0;
	}

	cleanedSessionCnt = 0;
	for(auto elem : GTPcMapUP_E) {
		key = elem.first;
		gtpSession = &elem.second;

		if( (gtpSession->StartTimeEpochSec > 0 && (curEpochSec - gtpSession->StartTimeEpochSec) > GContainer::config->gtpConfig->GN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC) ||
			(gtpSession->EndTimeEpochSec > 0 && (curEpochSec - gtpSession->EndTimeEpochSec) > GContainer::config->gtpConfig->GN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC) )
		{
			if(gtpSession->EndTimeEpochSec == 0) {
				gtpSession->EndTimeEpochSec 	= curEpochSec;
				gtpSession->EndTimeEpochNanoSec = curEpochNanoSec;
			}

			flushGTPSession(gtpSession,FLUSH_TYPE_CLEANUP);
			cleanedSessionList[cleanedSessionCnt] = key;

			cleanedSessionCnt++;
			if(cleanedSessionCnt >= GTPC_CLEAN_BATCH_LIMIT)
				break;

//			gtpcSessionCleanUpMap[gtpcSessionCleanUpMap_cnt] = key;
//			gtpcSessionCleanUpMap_cnt++;
		}
	}

	for(uint16_t i=0; i<cleanedSessionCnt; i++){
		GTPcMapUP_E.erase(cleanedSessionList[i]);
		cleanedSessionList[i] = 0;
	}

	cleanedSessionCnt = 0;
	for(auto elem : GTPcMapUP_Z) {
		key = elem.first;
		gtpSession = &elem.second;

		if( (gtpSession->StartTimeEpochSec > 0 && (curEpochSec - gtpSession->StartTimeEpochSec) > GContainer::config->gtpConfig->GN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC) ||
			(gtpSession->EndTimeEpochSec > 0 && (curEpochSec - gtpSession->EndTimeEpochSec) > GContainer::config->gtpConfig->GN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC) )
		{
			if(gtpSession->EndTimeEpochSec == 0) {
				gtpSession->EndTimeEpochSec 	= curEpochSec;
				gtpSession->EndTimeEpochNanoSec = curEpochNanoSec;
			}

			flushGTPSession(gtpSession,FLUSH_TYPE_CLEANUP);
			cleanedSessionList[cleanedSessionCnt] = key;

			cleanedSessionCnt++;
			if(cleanedSessionCnt >= GTPC_CLEAN_BATCH_LIMIT)
				break;

//			gtpcSessionCleanUpMap[gtpcSessionCleanUpMap_cnt] = key;
//			gtpcSessionCleanUpMap_cnt++;
		}
	}

	for(uint16_t i=0; i<cleanedSessionCnt; i++){
		GTPcMapUP_Z.erase(cleanedSessionList[i]);
		cleanedSessionList[i] = 0;
	}


	cleanedSessionCnt = 0;
//	printf("Instance [%d] GTPcMapDL:: [%d]\n", instanceId, GTPcMapDL.size());
	for(auto elem : GTPcMapDL_E) {
		key = elem.first;
		gtpSession = &elem.second;

		if( (gtpSession->StartTimeEpochSec > 0 && (curEpochSec - gtpSession->StartTimeEpochSec) > GContainer::config->gtpConfig->GN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC) ||
			(gtpSession->EndTimeEpochSec > 0 && (curEpochSec - gtpSession->EndTimeEpochSec) > GContainer::config->gtpConfig->GN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC) )
		{
			if(gtpSession->EndTimeEpochSec == 0) {
				gtpSession->EndTimeEpochSec 	= curEpochSec;
				gtpSession->EndTimeEpochNanoSec = curEpochNanoSec;
			}

			flushGTPSession(gtpSession,FLUSH_TYPE_CLEANUP);
			cleanedSessionList[cleanedSessionCnt] = key;

			cleanedSessionCnt++;
			if(cleanedSessionCnt >= GTPC_CLEAN_BATCH_LIMIT)
				break;

//			gtpcSessionCleanUpMap[gtpcSessionCleanUpMap_cnt] = key;
//			gtpcSessionCleanUpMap_cnt++;
		}
	}

	for(uint16_t i=0; i<cleanedSessionCnt; i++){
		GTPcMapDL_E.erase(cleanedSessionList[i]);
		cleanedSessionList[i] = 0;
	}
//	printf("Instance [%d] GTPcMapDL:: [%d] Count [%d]\n", instanceId, GTPcMapDL.size(), cleanedSessionCnt);

	cleanedSessionCnt = 0;
//	printf("Instance [%d] GTPcMapDL:: [%d]\n", instanceId, GTPcMapDL.size());
	for(auto elem : GTPcMapDL_Z) {
		key = elem.first;
		gtpSession = &elem.second;

		if( (gtpSession->StartTimeEpochSec > 0 && (curEpochSec - gtpSession->StartTimeEpochSec) > GContainer::config->gtpConfig->GN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC) ||
			(gtpSession->EndTimeEpochSec > 0 && (curEpochSec - gtpSession->EndTimeEpochSec) > GContainer::config->gtpConfig->GN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC) )
		{
			if(gtpSession->EndTimeEpochSec == 0) {
				gtpSession->EndTimeEpochSec 	= curEpochSec;
				gtpSession->EndTimeEpochNanoSec = curEpochNanoSec;
			}

			flushGTPSession(gtpSession,FLUSH_TYPE_CLEANUP);
			cleanedSessionList[cleanedSessionCnt] = key;

			cleanedSessionCnt++;
			if(cleanedSessionCnt >= GTPC_CLEAN_BATCH_LIMIT)
				break;

//			gtpcSessionCleanUpMap[gtpcSessionCleanUpMap_cnt] = key;
//			gtpcSessionCleanUpMap_cnt++;
		}
	}

	for(uint16_t i=0; i<cleanedSessionCnt; i++){
		GTPcMapDL_Z.erase(cleanedSessionList[i]);
		cleanedSessionList[i] = 0;
	}
//	printf("Instance [%d] GTPcMapDL:: [%d] Count [%d]\n", instanceId, GTPcMapDL.size(), cleanedSessionCnt);

	cleanedSessionCnt = 0;
}

VOID GTPSessionManager::getProcedureMapSize(int *createCount, int *updateCount, int *deleteCount)
{
#if 0
	*createCount = pdp_req_map.size();
	*updateCount = pdp_upd_map.size();
	*deleteCount = pdp_del_map.size();
#endif
}

//uint32_t GTPSessionManager::storeFlushSessionInRepo(
//		GTPSession *pGTPSession,
//		uint32_t &gtpcV1FlushFreeBitPos_sm,
//		std::bitset<GTPC_V1_FLUSH_POOL_ARRAY_ELEMENTS> (&gtpcV1FlushRepoFlags_sm)[GTPC_V1_FLUSH_POOL_ARRAY_SIZE],
//		std::map<int, GTPSession*> (&gtpcV1FlushRepository_sm)[GTPC_V1_FLUSH_POOL_ARRAY_SIZE])
//{
//	int arrId = 0;
//	int bitId = 0;
//
//	gtpcV1FlushFreeBitPos_sm++;
//	if(gtpcV1FlushFreeBitPos_sm >= GTPFlushRepository::gtpcV1FlushFreeBitPosMax){
//		gtpcV1FlushFreeBitPos_sm = 0;
//	}
//	arrId = gtpcV1FlushFreeBitPos_sm / GTPC_V1_FLUSH_POOL_ARRAY_ELEMENTS;
//	bitId = gtpcV1FlushFreeBitPos_sm % GTPC_V1_FLUSH_POOL_ARRAY_ELEMENTS;
//
//	while(gtpcV1FlushRepoFlags_sm[arrId].test(bitId)){
//		gtpcV1FlushFreeBitPos_sm++;
//		if(gtpcV1FlushFreeBitPos_sm >= GTPFlushRepository::gtpcV1FlushFreeBitPosMax){
//			gtpcV1FlushFreeBitPos_sm = 0;
//		}
//		arrId = gtpcV1FlushFreeBitPos_sm / GTPC_V1_FLUSH_POOL_ARRAY_ELEMENTS;
//		bitId = gtpcV1FlushFreeBitPos_sm % GTPC_V1_FLUSH_POOL_ARRAY_ELEMENTS;
//	}
//	gtpcV1FlushRepoFlags_sm[arrId].set(bitId);
//	gtpcV1FlushRepository_sm[arrId][bitId]->copy(pGTPSession);
//	return gtpcV1FlushFreeBitPos_sm;
//}


VOID GTPSessionManager::countFlushSession(GTPSession *pGTPSession)
{
	switch(instanceId)
	{
		case 0:
			if(pGTPSession->GTPReqMsgId == 16 || pGTPSession->GTPRspMsgId == 17)
				GTPStats::gtp_pdp_cr_flush_sm_0++;
			else if(pGTPSession->GTPReqMsgId == 18 || pGTPSession->GTPRspMsgId == 19)
				GTPStats::gtp_pdp_up_flush_sm_0++;
			else if(pGTPSession->GTPReqMsgId == 20 || pGTPSession->GTPRspMsgId == 21)
				GTPStats::gtp_pdp_dl_flush_sm_0++;
			break;

		case 1:
			if(pGTPSession->GTPReqMsgId == 16 || pGTPSession->GTPRspMsgId == 17)
				GTPStats::gtp_pdp_cr_flush_sm_1++;
			else if(pGTPSession->GTPReqMsgId == 18 || pGTPSession->GTPRspMsgId == 19)
				GTPStats::gtp_pdp_up_flush_sm_1++;
			else if(pGTPSession->GTPReqMsgId == 20 || pGTPSession->GTPRspMsgId == 21)
				GTPStats::gtp_pdp_dl_flush_sm_1++;
			break;

		case 2:
			if(pGTPSession->GTPReqMsgId == 16 || pGTPSession->GTPRspMsgId == 17)
				GTPStats::gtp_pdp_cr_flush_sm_2++;
			else if(pGTPSession->GTPReqMsgId == 18 || pGTPSession->GTPRspMsgId == 19)
				GTPStats::gtp_pdp_up_flush_sm_2++;
			else if(pGTPSession->GTPReqMsgId == 20 || pGTPSession->GTPRspMsgId == 21)
				GTPStats::gtp_pdp_dl_flush_sm_2++;
			break;

		case 3:
			if(pGTPSession->GTPReqMsgId == 16 || pGTPSession->GTPRspMsgId == 17)
				GTPStats::gtp_pdp_cr_flush_sm_3++;
			else if(pGTPSession->GTPReqMsgId == 18 || pGTPSession->GTPRspMsgId == 19)
				GTPStats::gtp_pdp_up_flush_sm_3++;
			else if(pGTPSession->GTPReqMsgId == 20 || pGTPSession->GTPRspMsgId == 21)
				GTPStats::gtp_pdp_dl_flush_sm_3++;
			break;
	}
}


VOID GTPSessionManager::flushGTPSession(GTPSession *pGTPSession, int flushType)
{
	long epochSecNow = getCurrentEpochSeconds();
	int idx = WRITE_TIME_INDEX(epochSecNow);

//	int idx = (((epochSecNow % 100) /10)  % IPGlobal::FLUSHER_TIMEINDEX) + 1;
//	if(idx >= IPGlobal::FLUSHER_TIMEINDEX) idx = idx - IPGlobal::FLUSHER_TIMEINDEX;


	pGTPSession->flushInstanceId = instanceId;
	pGTPSession->flushType = flushType;
	pGTPSession->FlushTimeEpochMicroSec = epochSecNow * 1000;
	countFlushSession(pGTPSession);

	switch(instanceId)
	{
			case 0:
					switch(idx)
					{
						case 0:
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_0[GTPFlushRepository::gtpcV1FlushMap_sm_0_t_0_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_0_cnt++;
							break;
						case 1:
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_1[GTPFlushRepository::gtpcV1FlushMap_sm_0_t_1_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_1_cnt++;
							break;
						case 2:
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_2[GTPFlushRepository::gtpcV1FlushMap_sm_0_t_2_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_2_cnt++;
							break;
						case 3:
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_3[GTPFlushRepository::gtpcV1FlushMap_sm_0_t_3_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_3_cnt++;
							break;
						case 4:
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_4[GTPFlushRepository::gtpcV1FlushMap_sm_0_t_4_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_4_cnt++;
							break;
						case 5:
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_5[GTPFlushRepository::gtpcV1FlushMap_sm_0_t_5_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_5_cnt++;
							break;
						case 6:
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_6[GTPFlushRepository::gtpcV1FlushMap_sm_0_t_6_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_6_cnt++;
							break;
						case 7:
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_7[GTPFlushRepository::gtpcV1FlushMap_sm_0_t_7_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_7_cnt++;
							break;
						case 8:
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_8[GTPFlushRepository::gtpcV1FlushMap_sm_0_t_8_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_8_cnt++;
							break;
						case 9:
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_9[GTPFlushRepository::gtpcV1FlushMap_sm_0_t_9_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_0_t_9_cnt++;
							break;
					}
					break;

			case 1:
					switch(idx)
					{
						case 0:
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_0[GTPFlushRepository::gtpcV1FlushMap_sm_1_t_0_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_0_cnt++;
							break;
						case 1:
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_1[GTPFlushRepository::gtpcV1FlushMap_sm_1_t_1_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_1_cnt++;
							break;
						case 2:
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_2[GTPFlushRepository::gtpcV1FlushMap_sm_1_t_2_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_2_cnt++;
							break;
						case 3:
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_3[GTPFlushRepository::gtpcV1FlushMap_sm_1_t_3_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_3_cnt++;
							break;
						case 4:
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_4[GTPFlushRepository::gtpcV1FlushMap_sm_1_t_4_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_4_cnt++;
							break;
						case 5:
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_5[GTPFlushRepository::gtpcV1FlushMap_sm_1_t_5_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_5_cnt++;
							break;
						case 6:
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_6[GTPFlushRepository::gtpcV1FlushMap_sm_1_t_6_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_6_cnt++;
							break;
						case 7:
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_7[GTPFlushRepository::gtpcV1FlushMap_sm_1_t_7_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_7_cnt++;
							break;
						case 8:
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_8[GTPFlushRepository::gtpcV1FlushMap_sm_1_t_8_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_8_cnt++;
							break;
						case 9:
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_9[GTPFlushRepository::gtpcV1FlushMap_sm_1_t_9_cnt].copy(pGTPSession);
							GTPFlushRepository::gtpcV1FlushMap_sm_1_t_9_cnt++;
							break;
					}
					break;
//			case 2:
//					switch(idx)
//					{
//						case 0:
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_0[GTPFlushRepository::gtpcV1FlushMap_sm_2_t_0_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_0_cnt++;
//							break;
//						case 1:
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_1[GTPFlushRepository::gtpcV1FlushMap_sm_2_t_1_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_1_cnt++;
//							break;
//						case 2:
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_2[GTPFlushRepository::gtpcV1FlushMap_sm_2_t_2_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_2_cnt++;
//							break;
//						case 3:
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_3[GTPFlushRepository::gtpcV1FlushMap_sm_2_t_3_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_3_cnt++;
//							break;
//						case 4:
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_4[GTPFlushRepository::gtpcV1FlushMap_sm_2_t_4_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_4_cnt++;
//							break;
//						case 5:
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_5[GTPFlushRepository::gtpcV1FlushMap_sm_2_t_5_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_5_cnt++;
//							break;
//						case 6:
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_6[GTPFlushRepository::gtpcV1FlushMap_sm_2_t_6_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_6_cnt++;
//							break;
//						case 7:
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_7[GTPFlushRepository::gtpcV1FlushMap_sm_2_t_7_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_7_cnt++;
//							break;
//						case 8:
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_8[GTPFlushRepository::gtpcV1FlushMap_sm_2_t_8_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_8_cnt++;
//							break;
//						case 9:
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_9[GTPFlushRepository::gtpcV1FlushMap_sm_2_t_9_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_2_t_9_cnt++;
//							break;
//						}
//					break;
//
//			case 3:
//					switch(idx)
//					{
//						case 0:
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_0[GTPFlushRepository::gtpcV1FlushMap_sm_3_t_0_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_0_cnt++;
//							break;
//						case 1:
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_1[GTPFlushRepository::gtpcV1FlushMap_sm_3_t_1_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_1_cnt++;
//							break;
//						case 2:
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_2[GTPFlushRepository::gtpcV1FlushMap_sm_3_t_2_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_2_cnt++;
//							break;
//						case 3:
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_3[GTPFlushRepository::gtpcV1FlushMap_sm_3_t_3_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_3_cnt++;
//							break;
//						case 4:
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_4[GTPFlushRepository::gtpcV1FlushMap_sm_3_t_4_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_4_cnt++;
//							break;
//						case 5:
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_5[GTPFlushRepository::gtpcV1FlushMap_sm_3_t_5_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_5_cnt++;
//							break;
//						case 6:
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_6[GTPFlushRepository::gtpcV1FlushMap_sm_3_t_6_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_6_cnt++;
//							break;
//						case 7:
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_7[GTPFlushRepository::gtpcV1FlushMap_sm_3_t_7_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_7_cnt++;
//							break;
//						case 8:
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_8[GTPFlushRepository::gtpcV1FlushMap_sm_3_t_8_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_8_cnt++;
//							break;
//						case 9:
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_9[GTPFlushRepository::gtpcV1FlushMap_sm_3_t_9_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_3_t_9_cnt++;
//							break;
//						}
//					break;
//
//			case 4:
//					switch(idx)
//					{
//						case 0:
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_0[GTPFlushRepository::gtpcV1FlushMap_sm_4_t_0_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_0_cnt++;
//							break;
//						case 1:
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_1[GTPFlushRepository::gtpcV1FlushMap_sm_4_t_1_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_1_cnt++;
//							break;
//						case 2:
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_2[GTPFlushRepository::gtpcV1FlushMap_sm_4_t_2_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_2_cnt++;
//							break;
//						case 3:
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_3[GTPFlushRepository::gtpcV1FlushMap_sm_4_t_3_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_3_cnt++;
//							break;
//						case 4:
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_4[GTPFlushRepository::gtpcV1FlushMap_sm_4_t_4_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_4_cnt++;
//							break;
//						case 5:
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_5[GTPFlushRepository::gtpcV1FlushMap_sm_4_t_5_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_5_cnt++;
//							break;
//						case 6:
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_6[GTPFlushRepository::gtpcV1FlushMap_sm_4_t_6_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_6_cnt++;
//							break;
//						case 7:
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_7[GTPFlushRepository::gtpcV1FlushMap_sm_4_t_7_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_7_cnt++;
//							break;
//						case 8:
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_8[GTPFlushRepository::gtpcV1FlushMap_sm_4_t_8_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_8_cnt++;
//							break;
//						case 9:
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_9[GTPFlushRepository::gtpcV1FlushMap_sm_4_t_9_cnt].copy(pGTPSession);
//							GTPFlushRepository::gtpcV1FlushMap_sm_4_t_9_cnt++;
//							break;
//						}
//					break;
	}

}

string GTPSessionManager::getSessionKey(MPacket *msgObj)
{
		char buffer[40];

		if(msgObj->dirUserNetwork)	// If Direction is UP -> True DN -> False
			sprintf(buffer,"1%03d%010u%05d%010u%05d1", msgObj->ipProtocol, msgObj->gtpSGSNAddr, msgObj->gtpSGSNPort, msgObj->gtpGGSNAddr, msgObj->gtpGGSNPort);
		else
			sprintf(buffer,"1%03d%010u%05d%010u%05d1", msgObj->ipProtocol, msgObj->gtpGGSNAddr, msgObj->gtpGGSNPort, msgObj->gtpSGSNAddr, msgObj->gtpSGSNPort);

		return string(buffer);
}

VOID GTPSessionManager::processQueue(int t_index)
{
	switch(instanceId)
	{
		case 0:
			{
				if(IPGlobal::NO_OF_INTERFACES > 0)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 0)
						processQueue_sm_0_i_0_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 1)
						processQueue_sm_0_i_0_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 2)
						processQueue_sm_0_i_0_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 3)
						processQueue_sm_0_i_0_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 1)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 0)
						processQueue_sm_0_i_1_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 1)
						processQueue_sm_0_i_1_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 2)
						processQueue_sm_0_i_1_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 3)
						processQueue_sm_0_i_1_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 2)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 0)
						processQueue_sm_0_i_2_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 1)
						processQueue_sm_0_i_2_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 2)
						processQueue_sm_0_i_2_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 3)
						processQueue_sm_0_i_2_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 3)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 0)
						processQueue_sm_0_i_3_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 1)
						processQueue_sm_0_i_3_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 2)
						processQueue_sm_0_i_3_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 3)
						processQueue_sm_0_i_3_r_3(t_index);
				}
			}
			break;

		case 1:
			{
				if(IPGlobal::NO_OF_INTERFACES > 0)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 0)
						processQueue_sm_1_i_0_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 1)
						processQueue_sm_1_i_0_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 2)
						processQueue_sm_1_i_0_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 3)
						processQueue_sm_1_i_0_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 1)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 0)
						processQueue_sm_1_i_1_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 1)
						processQueue_sm_1_i_1_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 2)
						processQueue_sm_1_i_1_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 3)
						processQueue_sm_1_i_1_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 2)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 0)
						processQueue_sm_1_i_2_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 1)
						processQueue_sm_1_i_2_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 2)
						processQueue_sm_1_i_2_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 3)
						processQueue_sm_1_i_2_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 3)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 0)
						processQueue_sm_1_i_3_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 1)
						processQueue_sm_1_i_3_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 2)
						processQueue_sm_1_i_3_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 3)
						processQueue_sm_1_i_3_r_3(t_index);
				}
			}
			break;

		case 2:
			{
				if(IPGlobal::NO_OF_INTERFACES > 0)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 0)
						processQueue_sm_2_i_0_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 1)
						processQueue_sm_2_i_0_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 2)
						processQueue_sm_2_i_0_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 3)
						processQueue_sm_2_i_0_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 1)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 0)
						processQueue_sm_2_i_1_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 1)
						processQueue_sm_2_i_1_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 2)
						processQueue_sm_2_i_1_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 3)
						processQueue_sm_2_i_1_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 2)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 0)
						processQueue_sm_2_i_2_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 1)
						processQueue_sm_2_i_2_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 2)
						processQueue_sm_2_i_2_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 3)
						processQueue_sm_2_i_2_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 3)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 0)
						processQueue_sm_2_i_3_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 1)
						processQueue_sm_2_i_3_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 2)
						processQueue_sm_2_i_3_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 3)
						processQueue_sm_2_i_3_r_3(t_index);
				}
			}
			break;

		case 3:
			{
				if(IPGlobal::NO_OF_INTERFACES > 0)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 0)
						processQueue_sm_3_i_0_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 1)
						processQueue_sm_3_i_0_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 2)
						processQueue_sm_3_i_0_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 3)
						processQueue_sm_3_i_0_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 1)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 0)
						processQueue_sm_3_i_1_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 1)
						processQueue_sm_3_i_1_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 2)
						processQueue_sm_3_i_1_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 3)
						processQueue_sm_3_i_1_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 2)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 0)
						processQueue_sm_3_i_2_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 1)
						processQueue_sm_3_i_2_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 2)
						processQueue_sm_3_i_2_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 3)
						processQueue_sm_3_i_2_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 3)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 0)
						processQueue_sm_3_i_3_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 1)
						processQueue_sm_3_i_3_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 2)
						processQueue_sm_3_i_3_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 3)
						processQueue_sm_3_i_3_r_3(t_index);
				}
			}
			break;

		case 4:
			{
				if(IPGlobal::NO_OF_INTERFACES > 0)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 0)
						processQueue_sm_4_i_0_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 1)
						processQueue_sm_4_i_0_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 2)
						processQueue_sm_4_i_0_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[0] > 3)
						processQueue_sm_4_i_0_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 1)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 0)
						processQueue_sm_4_i_1_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 1)
						processQueue_sm_4_i_1_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 2)
						processQueue_sm_4_i_1_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 3)
						processQueue_sm_4_i_1_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 2)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 0)
						processQueue_sm_4_i_2_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 1)
						processQueue_sm_4_i_2_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 2)
						processQueue_sm_4_i_2_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[2] > 3)
						processQueue_sm_4_i_2_r_3(t_index);
				}
				if(IPGlobal::NO_OF_INTERFACES > 3)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 0)
						processQueue_sm_4_i_3_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 1)
						processQueue_sm_4_i_3_r_1(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 2)
						processQueue_sm_4_i_3_r_2(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[3] > 3)
						processQueue_sm_4_i_3_r_3(t_index);
				}
			}
			break;
	}
}

BOOL GTPSessionManager::isRepositoryInitialized(){
	return repoInitStatus;
}

VOID GTPSessionManager::initializeGtpRepository()
{
	initializeGTPcLocalRepository();
	initializeGtpMpktRepository();
	if(instanceId == 0)
		initializeGtpFlusherRepository();
}

VOID GTPSessionManager::initializeGtpMpktRepository(){
//	if(IPGlobal::NO_OF_INTERFACES > 0)
//		initializeGtpMpktRepository_i_0(0);
//	if(IPGlobal::NO_OF_INTERFACES > 1)
//		initializeGtpMpktRepository_i_1(1);
//	if(IPGlobal::NO_OF_INTERFACES > 2)
//		initializeGtpMpktRepository_i_2(2);
//	if(IPGlobal::NO_OF_INTERFACES > 3)
//		initializeGtpMpktRepository_i_3(3);

}


VOID GTPSessionManager::initializeGtpFlusherRepository(){

		printf("GTPSessionManager [%d] Initializing Flusher     Repository [%'07d]...\n", instanceId, GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
		TheLog_nc_v2(Log::Info, name()," [%d] Initializing Flusher     Repository [%'07d]...", instanceId, GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);

		GTPZmqFlushStore::zmq_flush_map_gtpc_t_0.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
		GTPZmqFlushStore::zmq_flush_map_gtpc_t_1.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
		GTPZmqFlushStore::zmq_flush_map_gtpc_t_2.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
		GTPZmqFlushStore::zmq_flush_map_gtpc_t_3.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
		GTPZmqFlushStore::zmq_flush_map_gtpc_t_4.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
		GTPZmqFlushStore::zmq_flush_map_gtpc_t_5.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
		GTPZmqFlushStore::zmq_flush_map_gtpc_t_6.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
		GTPZmqFlushStore::zmq_flush_map_gtpc_t_7.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
		GTPZmqFlushStore::zmq_flush_map_gtpc_t_8.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
		GTPZmqFlushStore::zmq_flush_map_gtpc_t_9.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);

		if( IPGlobal::GN_SESSION_MANAGER_INSTANCES > 0){
			GTPFlushRepository::gtpcV1FlushMap_sm_0_t_0.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_0_t_1.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_0_t_2.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_0_t_3.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_0_t_4.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_0_t_5.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_0_t_6.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_0_t_7.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_0_t_8.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_0_t_9.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
		}
		if( IPGlobal::GN_SESSION_MANAGER_INSTANCES > 1){
			GTPFlushRepository::gtpcV1FlushMap_sm_1_t_0.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_1_t_1.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_1_t_2.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_1_t_3.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_1_t_4.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_1_t_5.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_1_t_6.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_1_t_7.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_1_t_8.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
			GTPFlushRepository::gtpcV1FlushMap_sm_1_t_9.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
		}
//		if( IPGlobal::SESSION_MANAGER_INSTANCES > 2){
//			GTPFlushRepository::gtpcV1FlushMap_sm_2_t_0.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_2_t_1.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_2_t_2.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_2_t_3.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_2_t_4.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_2_t_5.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_2_t_6.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_2_t_7.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_2_t_8.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_2_t_9.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//		}
//		if( IPGlobal::SESSION_MANAGER_INSTANCES > 3){
//			GTPFlushRepository::gtpcV1FlushMap_sm_3_t_0.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_3_t_1.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_3_t_2.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_3_t_3.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_3_t_4.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_3_t_5.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_3_t_6.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_3_t_7.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_3_t_8.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_3_t_9.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//		}
//		if( IPGlobal::SESSION_MANAGER_INSTANCES > 4){
//			GTPFlushRepository::gtpcV1FlushMap_sm_4_t_0.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_4_t_1.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_4_t_2.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_4_t_3.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_4_t_4.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_4_t_5.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_4_t_6.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_4_t_7.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_4_t_8.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//			GTPFlushRepository::gtpcV1FlushMap_sm_4_t_9.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
//		}
		printf("GTPSessionManager [%d] Initializing Flusher     Repository [%'07d]...Completed\n", instanceId, GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
		TheLog_nc_v2(Log::Info, name()," [%d] Initializing Flusher     Repository [%'07d]...Completed", instanceId, GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
}


//VOID GTPSessionManager::initializeGtpMpktRepository_i_0(int intfid){
//
//	switch(instanceId)
//	{
//		case 0:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 1:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 2:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 3:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 4:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//	}
//}
//
//VOID GTPSessionManager::initializeGtpMpktRepository_i_1(int intfid){
//
//	switch(instanceId)
//	{
//		case 0:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 1:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 2:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 3:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 4:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//	}
//}
//
//VOID GTPSessionManager::initializeGtpMpktRepository_i_2(int intfid){
//
//	switch(instanceId)
//	{
//		case 0:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 1:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 2:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 3:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 4:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//	}
//}
//
//VOID GTPSessionManager::initializeGtpMpktRepository_i_3(int intfid){
//
//	switch(instanceId)
//	{
//		case 0:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 1:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 2:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 3:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//		case 4:
//			{
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 2){
//					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 3){
//					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("GTPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//	}
//}


VOID GTPSessionManager::initializeGTPcLocalRepository()
{
//	setlocale(LC_NUMERIC, "");
//	//Initialize
//	freeBitPos = -1;
//	freeBitPosMax = GTPC_SESSION_POOL_ARRAY_ELEMENTS * GTPC_SESSION_POOL_ARRAY_SIZE;
//	printf("GTPSessionManager [%d] Initializing GTPc Local Session Total Repository [%'08lu]...\n", instanceId, freeBitPosMax);
//
//	for(int n = 0; n < GTPC_SESSION_POOL_ARRAY_SIZE; n++){
//		gtpSessionRepository[n].reserve(GTPC_SESSION_POOL_ARRAY_ELEMENTS);
//		repoFlags[n].reset();
//		for(int i = 0; i < GTPC_SESSION_POOL_ARRAY_ELEMENTS; i++)
//		{
//			gtpSessionRepository[n][i] = new GTPSession();
//		}
//	}
//	printf("GTPSessionManager [%d] Initializing GTPc Local Session Total Repository [%'08lu]...Completed.\n", instanceId, freeBitPosMax);
}

VOID GTPSessionManager::initializeGtpGlobalRepository()
{
	printf("GTPSessionManager [%d] GTP Global Session       Initializing for [%'08lu] entries...\n",instanceId, GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS * GTP_GLB_SESSION_POOL_ARRAY_SIZE);
	TheLog_nc_v2(Log::Info, name()," [%d] GTP Global Session       Initializing for [%'08lu] entries...",instanceId, GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS * GTP_GLB_SESSION_POOL_ARRAY_SIZE);
	GTPStore::freeGlbBitPos = -1;
	GTPStore::freeGlbBitPosMax = GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS * GTP_GLB_SESSION_POOL_ARRAY_SIZE;
	for(int n=0; n<GTP_GLB_SESSION_POOL_ARRAY_SIZE; n++){
//		GTPStore::GTPGlbSession[n].reserve(GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS);
		for(int i = 0; i < GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS; i++)
		{
			GTPStore::GTPGlbSession[n][i] = new GTPSession();
		}
	}

	for(int i=0; i<GTP_GLB_SESSION_POOL_ARRAY_SIZE; i++)
		GTPStore::bitFlags[i].reset();

//	for(int i=0; i<60; i++)
//	{
//		GTPStats::gtp_glb_sessions_total[i] = 0;
//		GTPStats::gtp_glb_sessions_utran[i] = 0;
//		GTPStats::gtp_glb_sessions_geran[i] = 0;
//	}

	//Reading saved tunnel data from the file
	readGNTunnelData(string("tidlookup.csv"));
	readTeidGlbDataUp();
	readTeidGlbDataDn();

	printf("GTPSessionManager [%d] GTP Global Session       Initializing for [%'08lu] entries...Completed\n",instanceId, GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS * GTP_GLB_SESSION_POOL_ARRAY_SIZE);
	TheLog_nc_v2(Log::Info, name()," [%d] GTP Global Session       Initializing for [%'08lu] entries...Completed",instanceId, GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS * GTP_GLB_SESSION_POOL_ARRAY_SIZE);
}

VOID GTPSessionManager::readGNTunnelData(std::string filename)
{
	string filePath = GContainer::config->DATA_DIR + filename;
	std::string line;
	char * 		pch;

	ifstream fp;

	fp.open(filePath.c_str());

	if(fp.fail())
	{
		printf("GTPSessionManager [%d] GTP Global Session       Error in Loading TEID file [%s]\n", instanceId, filePath.c_str());
		TheLog_nc_v2(Log::Warn, name()," [%d] GTP Global Session       Error in Loading TEID file [%s]", instanceId, filePath.c_str());

	}
	else
	{
		GTPSession *gtpS = new GTPSession();

		uint64_t curTimeEpochSec = (uint64_t) getCurrentEpochSeconds();

		while(!fp.eof())
		{
			getline(fp,line);
			//TheLog_nc_v2(Log::Debug, name,"[%d] Line :: [%s]",lineCnt, line.c_str());

			if(!line.empty() && line.length() > 0)
			{

				pch = strtok ((char *)line.c_str(), ",");
				strcpy(gtpS->IMSI, pch);

				if(strlen(gtpS->IMSI) >= 15){// || gtpS->RAT != 0 || gtpS->CI != 0){

					pch = strtok (NULL, ",");
					strcpy(gtpS->MSISDN, pch);

					pch = strtok (NULL, ",");
					strcpy(gtpS->IMEI, pch);

					pch = strtok (NULL, ",");
					gtpS->tunnel_id_control_up = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->tunnel_id_data_up = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->tunnel_id_control_dn = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->tunnel_id_data_dn = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->RAT = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->RATOld = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->MCC = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->MNC = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->LAC = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->CI = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->lastActivityTime = atol(pch);

					if(curTimeEpochSec - gtpS->lastActivityTime < 4*3600)
					{
						pch = strtok (NULL, ",");
						gtpS->lastActivityTimeGtpc = atol(pch);

						pch = strtok (NULL, ",");
						gtpS->lastActivityTimeGtpu = atol(pch);

						if(gtpS->lastActivityTime > 0)
						{
							GTPStore::freeGlbBitPos++;

							gtpS->active_session = true;

		//					activeSessionCntTotal++;
		//					if(gtpS->RAT == 1)
		//						activeSessionCntUtran++;
		//					else if (gtpS->RAT == 2)
		//						activeSessionCntGeran++;


							int arrid = GTPStore::freeGlbBitPos / GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
							int elemid = GTPStore::freeGlbBitPos % GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;

							GTPStore::GTPGlbSession[arrid][elemid]->copy(gtpS);
							GTPStore::bitFlags[arrid].set(elemid);

							if(gtpS->tunnel_id_control_up > 0)
								GTPStore::GTPGlbMap_CTL_UP[INDEX_TEID(gtpS->tunnel_id_control_up)][gtpS->tunnel_id_control_up] 	= GTPStore::freeGlbBitPos;
							if(gtpS->tunnel_id_data_up > 0){
		//						GTPStore::GTPGlbMap_LKU_DATA_UP[INDEX_TEID(gtpS->tunnel_id_data_up)][gtpS->tunnel_id_data_up].copy(gtpS);
								GTPStore::GTPGlbMap_DATA_UP[INDEX_TEID(gtpS->tunnel_id_data_up)][gtpS->tunnel_id_data_up] 		= GTPStore::freeGlbBitPos;
							}
							if(gtpS->tunnel_id_control_dn > 0)
								GTPStore::GTPGlbMap_CTL_DW[INDEX_TEID(gtpS->tunnel_id_control_dn)][gtpS->tunnel_id_control_dn] 	= GTPStore::freeGlbBitPos;
							if(gtpS->tunnel_id_data_dn > 0){
		//						GTPStore::GTPGlbMap_LKU_DATA_DW[INDEX_TEID(gtpS->tunnel_id_data_dn)][gtpS->tunnel_id_data_dn].copy(gtpS);
								GTPStore::GTPGlbMap_DATA_DW[INDEX_TEID(gtpS->tunnel_id_data_dn)][gtpS->tunnel_id_data_dn] 		= GTPStore::freeGlbBitPos;
							}
						}
					}
				}
			}
		}

		fp.close();
		delete gtpS;
	}

	int loadedCnt = 0;
	for(int i = 0; i< GTP_GLB_SESSION_POOL_ARRAY_SIZE; i++) {
		for(int n = 0; n< GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS; n++) {
			if( strlen(GTPStore::GTPGlbSession[i][n]->IMSI) >= 15)// || GTPStore::GTPGlbSession[i][n]->RAT != 0 || GTPStore::GTPGlbSession[i][n]->CI != 0)
				loadedCnt++;
//				printf("IMSI in [%d][%d] %s\n", i,n, GTPStore::GTPGlbSession[i][n]->IMSI);
		}
	}
	printf("GTPSessionManager [%d] GTP Global Session       Loaded [%d] records in GTP Global Session from file [%s] reading [%d] lines\n",instanceId, loadedCnt, filePath.c_str(), (GTPStore::freeGlbBitPos + 1));
	TheLog_nc_v4(Log::Info, name()," [%d] Loaded [%d] TEID records from file [%s] reading [%d] lines",instanceId, loadedCnt, filePath.c_str(), (GTPStore::freeGlbBitPos + 1));



	filePath = GContainer::config->DATA_DIR + "imsidump.csv";
	fp.open(filePath.c_str());
	int lineCnt = 0;
	if(fp.fail())
	{
		printf("GTPSessionManager [%d] GTP Global Session       Error in Loading IMSI file [%s]\n", instanceId, filePath.c_str());
		TheLog_nc_v2(Log::Warn, name()," [%d] GTP Global Session       Error in Loading IMSI file [%s]", instanceId, filePath.c_str());

	}
	else
	{
		while(!fp.eof())
		{
			getline(fp,line);
			lineCnt++;
			if(!line.empty() && line.length() >= 15)
			{
				GTPStore::GTPGlb_IMSI_MAP[line] = 1;
			}
		}
		fp.close();
	}

	printf("GTPSessionManager [%d] GTP Global Session       Loaded [%d] records in IMSI Store from file [%s] reading [%d] lines\n",instanceId, GTPStore::GTPGlb_IMSI_MAP.size(), filePath.c_str(),lineCnt);
	TheLog_nc_v4(Log::Info, name()," [%d] Loaded [%d] records in IMSI Store from file [%s] reading [%d] lines",instanceId, GTPStore::GTPGlb_IMSI_MAP.size(), filePath.c_str(),lineCnt);


}

VOID GTPSessionManager::dumpTeidDump()
{
	string filePath = GContainer::config->DATA_DIR + "tidlookup.csv";

	printf("GTPSessionManager [%d] Dumping TEID Global Store to file [%s]...\n",instanceId, filePath.c_str());
	TheLog_nc_v2(Log::Info, name()," [%d] Dumping TEID Global Store to file [%s]...",instanceId,filePath.c_str());

	ofstream fileHandler;

	fileHandler.open(filePath.c_str(), ios :: out);

	if(fileHandler.fail())
	{
		printf("GTPSessionManager [%d] Error in Dumping TEID Global Store File : %s\n",instanceId, filePath.c_str());
		TheLog_nc_v2(Log::Warn, name()," [%d] Error in Dumping TEID Global Store to file [%s]...",instanceId,filePath.c_str());
	}
	else
	{
		for(int i = 0; i< GTP_GLB_SESSION_POOL_ARRAY_SIZE; i++) {
			for(int n = 0; n< GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS; n++) {
//				if( (strlen(GTPStore::GTPGlbSession[i][n]->IMSI) >= 15 || GTPStore::GTPGlbSession[i][n]->RAT != 0 || GTPStore::GTPGlbSession[i][n]->CI != 0) && GTPStore::GTPGlbSession[i][n]->active_session){
				if( (strlen(GTPStore::GTPGlbSession[i][n]->IMSI) >= 15) && GTPStore::GTPGlbSession[i][n]->active_session){
					fileHandler << GTPStore::GTPGlbSession[i][n]->IMSI << ","
								<< GTPStore::GTPGlbSession[i][n]->MSISDN << ","
								<< GTPStore::GTPGlbSession[i][n]->IMEI << ","
								<< GTPStore::GTPGlbSession[i][n]->tunnel_id_control_up << ","
								<< GTPStore::GTPGlbSession[i][n]->tunnel_id_data_up << ","
								<< GTPStore::GTPGlbSession[i][n]->tunnel_id_control_dn << ","
								<< GTPStore::GTPGlbSession[i][n]->tunnel_id_data_dn << ","
								<< GTPStore::GTPGlbSession[i][n]->RAT << ","
								<< GTPStore::GTPGlbSession[i][n]->RATOld << ","
								<< GTPStore::GTPGlbSession[i][n]->MCC << ","
								<< GTPStore::GTPGlbSession[i][n]->MNC << ","
								<< GTPStore::GTPGlbSession[i][n]->LAC << ","
								<< GTPStore::GTPGlbSession[i][n]->CI << ","
								<< GTPStore::GTPGlbSession[i][n]->lastActivityTime << ","
								<< GTPStore::GTPGlbSession[i][n]->lastActivityTimeGtpc << ","
								<< GTPStore::GTPGlbSession[i][n]->lastActivityTimeGtpu
								<< endl;
				}
			}
		}
		fileHandler.close();
		printf("GTPSessionManager [%d] Dumping TEID Global Store to file [%s]...Completed\n",instanceId,filePath.c_str());
		TheLog_nc_v2(Log::Info, name()," [%d] Dumping TEID Global Store to file [%s]...Completed",instanceId,filePath.c_str());
	}



	filePath = GContainer::config->DATA_DIR + "imsidump.csv";

	printf("GTPSessionManager [%d] Dumping IMSI Store to file [%s]...\n",instanceId,filePath.c_str());
	TheLog_nc_v2(Log::Info, name()," [%d] Dumping IMSI Store to file [%s]...",instanceId,filePath.c_str());

	fileHandler.open(filePath.c_str(), ios :: out);

	if(fileHandler.fail())
	{
		printf("GTPSessionManager [%d] Error in Dumping IMSI Store File : %s\n", instanceId, filePath.c_str());
		TheLog_nc_v2(Log::Warn, name()," [%d] Error in Dumping IMSI Store to file [%s]...",instanceId, filePath.c_str());
	}
	else
	{
		for(auto elem : GTPStore::GTPGlb_IMSI_MAP) {
			fileHandler << elem.first << endl;
		}

		fileHandler.close();
		printf("GTPSessionManager [%d] Dumping TEID Global Store to file [%s]...Completed\n",instanceId,filePath.c_str());
		TheLog_nc_v2(Log::Info, name()," [%d] Dumping IMSI Store to file [%s]...Completed",instanceId,filePath.c_str());
	}
}


VOID GTPSessionManager::readTeidGlbDataUp()
{
	string filePath = GContainer::config->DATA_DIR + "teidglblookup_up.csv";
	std::string line;
	char * 		pch;
	int lineCnt = 0, loadedCntUp = 0, loadedCntDn = 0;
	ifstream fp;
	uint32_t teid = 0;

	fp.open(filePath.c_str());

	if(fp.fail())
	{
		printf("GTPSessionManager [%d] GTP Global Session       Error in Loading TEID LKU_UP file [%s]\n", instanceId, filePath.c_str());
		TheLog_nc_v2(Log::Warn, name()," [%d] GTP Global Session       Error in Loading TEID LKU_UP file [%s]", instanceId, filePath.c_str());

	}
	else
	{
		GTPSession *gtpS = new GTPSession();

		while(!fp.eof())
		{
			getline(fp,line);
			//TheLog_nc_v2(Log::Debug, name,"[%d] Line :: [%s]",lineCnt, line.c_str());
			lineCnt++;

			if(!line.empty() && line.length() > 0)
			{

				pch = strtok ((char *)line.c_str(), ",");
				teid = atol(pch);

				pch = strtok (NULL, ",");
				strcpy(gtpS->IMSI, pch);

				if(strlen(gtpS->IMSI) >= 15){// || gtpS->RAT != 0 || gtpS->CI != 0){

					pch = strtok (NULL, ",");
					strcpy(gtpS->MSISDN, pch);

					pch = strtok (NULL, ",");
					strcpy(gtpS->IMEI, pch);

					pch = strtok (NULL, ",");
					gtpS->tunnel_id_control_up = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->tunnel_id_data_up = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->tunnel_id_control_dn = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->tunnel_id_data_dn = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->RAT = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->RATOld = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->MCC = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->MNC = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->LAC = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->CI = atoi(pch);

					pch = strtok (NULL, ",");
					atoi(pch) == 1 ? gtpS->expiredFlag = true : gtpS->expiredFlag = false;

					if(!gtpS->expiredFlag)
						gtpS->active_session = true;

					pch = strtok (NULL, ",");
					gtpS->expiredTimeEpochSec = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->lastActivityTime = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->lastActivityTimeGtpc = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->lastActivityTimeGtpu = atol(pch);

					if(gtpS->tunnel_id_data_up > 0){
						loadedCntUp++;
						GTPStore::GTPGlbMap_LKU_DATA_UP[INDEX_TEID(gtpS->tunnel_id_data_up)][gtpS->tunnel_id_data_up].copy(gtpS);
					}
//					if(gtpS->tunnel_id_data_dn > 0){
//						loadedCntDn++;
//						GTPStore::GTPGlbMap_LKU_DATA_DW[INDEX_TEID(gtpS->tunnel_id_data_dn)][gtpS->tunnel_id_data_dn].copy(gtpS);
//					}
				}
			}
		}

		fp.close();
		delete gtpS;
	}

	int upSize = 0, dnSize = 0;
	for(int i=0; i<GTP_GLB_SESSION_TEID_ARRAY_SIZE; i++)
	{
		upSize += GTPStore::GTPGlbMap_LKU_DATA_UP[i].size();
		dnSize += GTPStore::GTPGlbMap_LKU_DATA_DW[i].size();
	}
	printf("GTPSessionManager [%d] GTP Global Session       Loaded [%d] [%d] [%d] [%d] records in TEID LKU_UP from file [%s] reading [%d] lines\n",instanceId, loadedCntUp, loadedCntDn, upSize, dnSize, filePath.c_str(), lineCnt);
	TheLog_nc_v5(Log::Warn, name()," [%d] GTP Global Session       Loaded [%d] [%d] TEID LKU_UP records from file [%s] reading [%d] lines",instanceId, loadedCntUp, loadedCntDn, filePath.c_str(), lineCnt);
}


VOID GTPSessionManager::readTeidGlbDataDn()
{
	string filePath = GContainer::config->DATA_DIR + "teidglblookup_dn.csv";
	std::string line;
	char * 		pch;
	int lineCnt = 0, loadedCntUp = 0, loadedCntDn = 0;
	ifstream fp;
	uint32_t teid = 0;

	fp.open(filePath.c_str());

	if(fp.fail())
	{
		printf("GTPSessionManager [%d] GTP Global Session       Error in Loading TEID LKU_DN file [%s]\n", instanceId, filePath.c_str());
		TheLog_nc_v2(Log::Warn, name()," [%d] GTP Global Session       Error in Loading TEID LKU_DN file [%s]", instanceId, filePath.c_str());

	}
	else
	{
		GTPSession *gtpS = new GTPSession();

		while(!fp.eof())
		{
			getline(fp,line);
			//TheLog_nc_v2(Log::Debug, name,"[%d] Line :: [%s]",lineCnt, line.c_str());
			lineCnt++;

			if(!line.empty() && line.length() > 0)
			{

				pch = strtok ((char *)line.c_str(), ",");
				teid = atol(pch);

				pch = strtok (NULL, ",");
				strcpy(gtpS->IMSI, pch);

				if(strlen(gtpS->IMSI) >= 15){// || gtpS->RAT != 0 || gtpS->CI != 0){

					pch = strtok (NULL, ",");
					strcpy(gtpS->MSISDN, pch);

					pch = strtok (NULL, ",");
					strcpy(gtpS->IMEI, pch);

					pch = strtok (NULL, ",");
					gtpS->tunnel_id_control_up = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->tunnel_id_data_up = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->tunnel_id_control_dn = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->tunnel_id_data_dn = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->RAT = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->RATOld = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->MCC = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->MNC = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->LAC = atoi(pch);

					pch = strtok (NULL, ",");
					gtpS->CI = atoi(pch);

					pch = strtok (NULL, ",");
					atoi(pch) == 1 ? gtpS->expiredFlag = true : gtpS->expiredFlag = false;

					if(!gtpS->expiredFlag)
						gtpS->active_session = true;

					pch = strtok (NULL, ",");
					gtpS->expiredTimeEpochSec = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->lastActivityTime = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->lastActivityTimeGtpc = atol(pch);

					pch = strtok (NULL, ",");
					gtpS->lastActivityTimeGtpu = atol(pch);

//					if(gtpS->tunnel_id_data_up > 0){
//						loadedCntUp++;
//						GTPStore::GTPGlbMap_LKU_DATA_UP[INDEX_TEID(gtpS->tunnel_id_data_up)][gtpS->tunnel_id_data_up].copy(gtpS);
//					}
					if(gtpS->tunnel_id_data_dn > 0){
						loadedCntDn++;
						GTPStore::GTPGlbMap_LKU_DATA_DW[INDEX_TEID(gtpS->tunnel_id_data_dn)][gtpS->tunnel_id_data_dn].copy(gtpS);
					}
				}
			}
		}

		fp.close();
		delete gtpS;
	}

	int upSize = 0, dnSize = 0;
	for(int i=0; i<GTP_GLB_SESSION_TEID_ARRAY_SIZE; i++)
	{
		upSize += GTPStore::GTPGlbMap_LKU_DATA_UP[i].size();
		dnSize += GTPStore::GTPGlbMap_LKU_DATA_DW[i].size();
	}

	printf("GTPSessionManager [%d] GTP Global Session       Loaded [%d] [%d] [%d] [%d] records in TEID LKU_UP from file [%s] reading [%d] lines\n",instanceId, loadedCntUp, loadedCntDn, upSize, dnSize, filePath.c_str(), lineCnt);
	TheLog_nc_v5(Log::Warn, name()," [%d] GTP Global Session       Loaded [%d] [%d] TEID LKU_DN records from file [%s] reading [%d] lines",instanceId, loadedCntUp, loadedCntDn, filePath.c_str(), lineCnt);
}

VOID GTPSessionManager::dumpTeidGlobalLku()
{
	ofstream tidlookup_file;
	string filePath = "";

	filePath = GContainer::config->DATA_DIR + "teidglblookup_up.csv";
	printf("Dumping TEID Global LKU_UP Store to file [%s]...\n",filePath.c_str());

	tidlookup_file.open(filePath.c_str(), ios :: out);

	if(tidlookup_file.fail())
	{
		printf("  Error in Opening TEID Global LKU_UP Dump File : %s\n", filePath.c_str());
	}else
	{
		for(int i = 0; i< GTP_GLB_SESSION_TEID_ARRAY_SIZE; i++) {
			for(auto elem : GTPStore::GTPGlbMap_LKU_DATA_UP[i]) {
				tidlookup_file  << elem.first << ","
								<< elem.second.IMSI << ","
								<< elem.second.MSISDN << ","
								<< elem.second.IMEI << ","
								<< elem.second.tunnel_id_control_up << ","
								<< elem.second.tunnel_id_data_up << ","
								<< elem.second.tunnel_id_control_dn << ","
								<< elem.second.tunnel_id_data_dn << ","
								<< elem.second.RAT << ","
								<< elem.second.RATOld << ","
								<< elem.second.MCC << ","
								<< elem.second.MNC << ","
								<< elem.second.LAC << ","
								<< elem.second.CI << ","
								<< (elem.second.expiredFlag == true ? 1 : 0) << ","
								<< elem.second.expiredTimeEpochSec << ","
								<< elem.second.lastActivityTime << ","
								<< elem.second.lastActivityTimeGtpc << ","
								<< elem.second.lastActivityTimeGtpu
								<< endl;
				}
		}
		tidlookup_file.close();
		printf("Dumping TEID Global LKU_UP Store to file [%s]...Completed\n",filePath.c_str());
	}


	filePath = GContainer::config->DATA_DIR + "teidglblookup_dn.csv";
	printf("Dumping TEID Global LKU_DN Store to file [%s]...\n",filePath.c_str());

	tidlookup_file.open(filePath.c_str(), ios :: out);

	if(tidlookup_file.fail())
	{
		printf("  Error in Opening TEID Global LKU_DN Dump File : %s\n", filePath.c_str());
	}else
	{
		for(int i = 0; i< GTP_GLB_SESSION_TEID_ARRAY_SIZE; i++) {
			for(auto elem : GTPStore::GTPGlbMap_LKU_DATA_DW[i]) {
				tidlookup_file  << elem.first << ","
								<< elem.second.IMSI << ","
								<< elem.second.MSISDN << ","
								<< elem.second.IMEI << ","
								<< elem.second.tunnel_id_control_up << ","
								<< elem.second.tunnel_id_data_up << ","
								<< elem.second.tunnel_id_control_dn << ","
								<< elem.second.tunnel_id_data_dn << ","
								<< elem.second.RAT << ","
								<< elem.second.RATOld << ","
								<< elem.second.MCC << ","
								<< elem.second.MNC << ","
								<< elem.second.LAC << ","
								<< elem.second.CI << ","
								<< (elem.second.expiredFlag == true ? 1 : 0) << ","
								<< elem.second.expiredTimeEpochSec << ","
								<< elem.second.lastActivityTime << ","
								<< elem.second.lastActivityTimeGtpc << ","
								<< elem.second.lastActivityTimeGtpu
								<< endl;
				}
		}
		tidlookup_file.close();
		printf("Dumping TEID Global LKU_DN Store to file [%s]...Completed\n",filePath.c_str());
	}

}


VOID GTPSessionManager::updatePDPOperationsCounters(uint8_t id)
{
	switch(instanceId)
	{
		case 0:
			{
				switch(id)
				{
					case GTPV1_CREATE_PDP_REQUEST:
								GTPStats::gtpc_pdp_cr_req_sm_0++;
								break;

					case GTPV1_CREATE_PDP_RESPONSE:
								GTPStats::gtpc_pdp_cr_res_sm_0++;
								break;

					case GTPV1_UPDATE_PDP_REQUEST:
								GTPStats::gtpc_pdp_up_req_sm_0++;
								break;

					case GTPV1_UPDATE_PDP_RESPONSE:
								GTPStats::gtpc_pdp_up_res_sm_0++;
								break;

					case GTPV1_DELETE_PDP_REQUEST:
								GTPStats::gtpc_pdp_dl_req_sm_0++;
								break;

					case GTPV1_DELETE_PDP_RESPONSE:
								GTPStats::gtpc_pdp_dl_res_sm_0++;
								break;
				}
			}
			break;

		case 1:
			{
				switch(id)
				{
					case GTPV1_CREATE_PDP_REQUEST:
								GTPStats::gtpc_pdp_cr_req_sm_1++;
								break;

					case GTPV1_CREATE_PDP_RESPONSE:
								GTPStats::gtpc_pdp_cr_res_sm_1++;
								break;

					case GTPV1_UPDATE_PDP_REQUEST:
								GTPStats::gtpc_pdp_up_req_sm_1++;
								break;

					case GTPV1_UPDATE_PDP_RESPONSE:
								GTPStats::gtpc_pdp_up_res_sm_1++;
								break;

					case GTPV1_DELETE_PDP_REQUEST:
								GTPStats::gtpc_pdp_dl_req_sm_1++;
								break;

					case GTPV1_DELETE_PDP_RESPONSE:
								GTPStats::gtpc_pdp_dl_res_sm_1++;
								break;
				}
			}
			break;

		case 2:
			{
				switch(id)
				{
					case GTPV1_CREATE_PDP_REQUEST:
								GTPStats::gtpc_pdp_cr_req_sm_2++;
								break;

					case GTPV1_CREATE_PDP_RESPONSE:
								GTPStats::gtpc_pdp_cr_res_sm_2++;
								break;

					case GTPV1_UPDATE_PDP_REQUEST:
								GTPStats::gtpc_pdp_up_req_sm_2++;
								break;

					case GTPV1_UPDATE_PDP_RESPONSE:
								GTPStats::gtpc_pdp_up_res_sm_2++;
								break;

					case GTPV1_DELETE_PDP_REQUEST:
								GTPStats::gtpc_pdp_dl_req_sm_2++;
								break;

					case GTPV1_DELETE_PDP_RESPONSE:
								GTPStats::gtpc_pdp_dl_res_sm_2++;
								break;
				}
			}
			break;

		case 3:
			{
				switch(id)
				{
					case GTPV1_CREATE_PDP_REQUEST:
								GTPStats::gtpc_pdp_cr_req_sm_3++;
								break;

					case GTPV1_CREATE_PDP_RESPONSE:
								GTPStats::gtpc_pdp_cr_res_sm_3++;
								break;

					case GTPV1_UPDATE_PDP_REQUEST:
								GTPStats::gtpc_pdp_up_req_sm_3++;
								break;

					case GTPV1_UPDATE_PDP_RESPONSE:
								GTPStats::gtpc_pdp_up_res_sm_3++;
								break;

					case GTPV1_DELETE_PDP_REQUEST:
								GTPStats::gtpc_pdp_dl_req_sm_3++;
								break;

					case GTPV1_DELETE_PDP_RESPONSE:
								GTPStats::gtpc_pdp_dl_res_sm_3++;
								break;
				}
			}
			break;

	}
}

VOID GTPSessionManager::resetPDPOperationsCounters()
{
//	GTPStats::gtp_get_imsi_req_cnt = 0;
//	GTPStats::gtp_get_imsi_suc_cnt = 0;

	switch(instanceId)
	{
		case 0:
			{
				GTPStats::gtpc_pdp_cr_req_sm_0 = 0;
				GTPStats::gtpc_pdp_cr_res_sm_0 = 0;
				GTPStats::gtpc_pdp_up_req_sm_0 = 0;
				GTPStats::gtpc_pdp_up_res_sm_0 = 0;
				GTPStats::gtpc_pdp_dl_req_sm_0 = 0;
				GTPStats::gtpc_pdp_dl_res_sm_0 = 0;
			}
			break;

		case 1:
			{
				GTPStats::gtpc_pdp_cr_req_sm_1 = 0;
				GTPStats::gtpc_pdp_cr_res_sm_1 = 0;
				GTPStats::gtpc_pdp_up_req_sm_1 = 0;
				GTPStats::gtpc_pdp_up_res_sm_1 = 0;
				GTPStats::gtpc_pdp_dl_req_sm_1 = 0;
				GTPStats::gtpc_pdp_dl_res_sm_1 = 0;
			}
			break;

		case 2:
			{
				GTPStats::gtpc_pdp_cr_req_sm_2 = 0;
				GTPStats::gtpc_pdp_cr_res_sm_2 = 0;
				GTPStats::gtpc_pdp_up_req_sm_2 = 0;
				GTPStats::gtpc_pdp_up_res_sm_2 = 0;
				GTPStats::gtpc_pdp_dl_req_sm_2 = 0;
				GTPStats::gtpc_pdp_dl_res_sm_2 = 0;
			}
			break;

		case 3:
			{
				GTPStats::gtpc_pdp_cr_req_sm_3 = 0;
				GTPStats::gtpc_pdp_cr_res_sm_3 = 0;
				GTPStats::gtpc_pdp_up_req_sm_3 = 0;
				GTPStats::gtpc_pdp_up_res_sm_3 = 0;
				GTPStats::gtpc_pdp_dl_req_sm_3 = 0;
				GTPStats::gtpc_pdp_dl_res_sm_3 = 0;
			}
			break;

	}
}


//VOID GTPSessionManager::processQueue_sm(bool &gtp_msg_sm_busy, uint32_t &gtp_msg_sm_cnt, std::vector<MPacket> &gtp_msg_sm)
VOID GTPSessionManager::processQueue_sm(bool &gtp_msg_sm_busy, uint32_t &gtp_msg_sm_cnt, std::map<uint32_t, MPacket> &gtp_msg_sm)
{
	uint32_t recCnt = gtp_msg_sm_cnt;
	if(recCnt > 0)
	{
		gtp_msg_sm_busy = true;
		for(uint32_t i=0; i<recCnt; i++)
		{
			processMessage(&gtp_msg_sm[i]);
			gtp_msg_sm_cnt--;
			//gtp_msg_sm[i].reset();
			gtp_msg_sm.erase(i);
		}
		gtp_msg_sm.clear();
//		gtp_msg_sm = std::vector<MPacket>();
//		gtp_msg_sm.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
		gtp_msg_sm_cnt = 0;
		gtp_msg_sm_busy = false;
	}

}

VOID GTPSessionManager::processQueue_sm_0_i_0_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_0_i_0_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_0_i_0_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_0_i_0_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_1_i_0_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_1_i_0_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_1_i_0_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_1_i_0_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_2_i_0_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_2_i_0_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_2_i_0_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_2_i_0_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_3_i_0_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_3_i_0_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_3_i_0_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_3_i_0_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_4_i_0_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_4_i_0_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_4_i_0_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_4_i_0_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_0_i_1_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_0_i_1_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_0_i_1_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_0_i_1_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_1_i_1_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_1_i_1_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_1_i_1_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_1_i_1_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_2_i_1_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_2_i_1_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_2_i_1_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_2_i_1_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_3_i_1_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_3_i_1_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_3_i_1_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_3_i_1_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_4_i_1_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_4_i_1_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_4_i_1_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_4_i_1_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_0_i_2_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_0_i_2_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_0_i_2_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_0_i_2_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_1_i_2_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_1_i_2_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_1_i_2_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_1_i_2_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_2_i_2_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_2_i_2_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_2_i_2_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_2_i_2_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_3_i_2_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_3_i_2_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_3_i_2_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_3_i_2_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_4_i_2_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_4_i_2_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_4_i_2_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_4_i_2_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_0_i_3_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_0_i_3_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_0_i_3_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_0_i_3_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_1_i_3_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_1_i_3_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_1_i_3_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_1_i_3_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_2_i_3_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_2_i_3_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_2_i_3_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_2_i_3_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_3_i_3_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_3_i_3_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_3_i_3_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_3_i_3_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_9);
		break;
	}
}

VOID GTPSessionManager::processQueue_sm_4_i_3_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_0_cnt, GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_4_i_3_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_0_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_0);
			break;

		case 1:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_1);
			break;

		case 2:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_2);
			break;

		case 3:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_3);
			break;

		case 4:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_4);
			break;

		case 5:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_5);
			break;

		case 6:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_6);
			break;

		case 7:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_7);
			break;

		case 8:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_8);
			break;

		case 9:
			processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_9);
			break;
	}
}

VOID GTPSessionManager::processQueue_sm_4_i_3_r_2(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_0_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_9);
		break;

	}
}

VOID GTPSessionManager::processQueue_sm_4_i_3_r_3(int t_index)
{
	switch(t_index)
	{
	case 0:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_0_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_0_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_0);
		break;

	case 1:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_1_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_1_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_1);
		break;

	case 2:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_2_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_2_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_2);
		break;

	case 3:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_3_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_3_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_3);
		break;

	case 4:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_4_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_4_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_4);
		break;

	case 5:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_5_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_5_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_5);
		break;

	case 6:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_6_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_6_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_6);
		break;

	case 7:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_7_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_7_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_7);
		break;

	case 8:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_8_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_8_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_8);
		break;

	case 9:
		processQueue_sm(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_9_busy, GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_9_cnt,GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_9);
		break;
	}
}

