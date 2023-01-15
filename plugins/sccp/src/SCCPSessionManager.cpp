/*
 * SCCPSessionManager.cpp
 *
 *  Created on: 17-Jul-2016
 *      Author: Deb
 */
#include <map>

#include "SCCPSessionManager.h"

SCCPSessionManager::SCCPSessionManager(int id, int coreid) {

	printf("SCCP SESSION MANAGER SCCPSessionManager()\n");
	_thisLogLevel = 0;
	this->_name = "SCCPSessionManager";
	this->setLogLevel(Log::theLog().level());

	this->instanceId = id;
	this->coreId = coreid;

	iupsSm = new IUPSSessionManager();
}

SCCPSessionManager::~SCCPSessionManager() {
	delete (iupsSm);
}

VOID SCCPSessionManager::run()
{
	TheLog_nc_v2(Log::Info, name()," [%d] Started, pinned to core :: %d", instanceId, coreId);

	int lastProcessedIndex = -1;
	int curIndex = -1;
	int curMin = 0, prevMin = 0;
	int curSecIdx = 0 , prevSecIdx = 0;
	int today = 0, lastday = 0;
	int minCnt = 0;

	struct tm *now_tm;

//	initializeRepository();
	loadTraceSessionIds();
//	iupsSm->initializeIUPSFlushRepository();

	gettimeofday(&curTime, NULL);
	now_tm = localtime(&curTime.tv_sec);
	curMin = prevMin = now_tm->tm_min;
	curSecIdx = prevSecIdx = now_tm->tm_sec / 10;
	today = lastday = now_tm->tm_mday;

//	curIndex = (((getCurrentEpochSeconds() % 100) /10)  % IPGlobal::SESSION_MANAGER_TIMEINDEX);
//	if(curIndex < 0) curIndex = IPGlobal::SESSION_MANAGER_TIMEINDEX + curIndex;

	curIndex = READ_TIME_INDEX(curTime.tv_sec);

	lastProcessedIndex = curIndex;

	long THREAD_SLEEP_DUR_MICRO_SEC = 100000;

	while(IPGlobal::GN_SESSION_MANAGER_RUNNING_STATUS[instanceId])
	{
		usleep(THREAD_SLEEP_DUR_MICRO_SEC);		// 100ms

		gettimeofday(&curTime, NULL);
		now_tm = localtime(&curTime.tv_sec);
		curMin = now_tm->tm_min;
		curSecIdx = now_tm->tm_sec / 10;
		today = now_tm->tm_mday;

//		curIndex = (((getCurrentEpochSeconds() % 100) /10)  % IPGlobal::SESSION_MANAGER_TIMEINDEX);
//		if(curIndex < 0) curIndex = IPGlobal::SESSION_MANAGER_TIMEINDEX + curIndex;

		curIndex = READ_TIME_INDEX(curTime.tv_sec);

		while(lastProcessedIndex != curIndex)
		{
			sleep(1);
			processStartEpochSec = getCurrentEpochSeconds();
			processQueue(lastProcessedIndex);
//			lastProcessedIndex++;
//			if(lastProcessedIndex >= IPGlobal::SESSION_MANAGER_TIMEINDEX)
//				lastProcessedIndex = 0;
			lastProcessedIndex = NEXT_TIME_INDEX(lastProcessedIndex);
		}

		if(curSecIdx != prevSecIdx)
		{
			cleanTimedOutSccpSessions();		// Clean SCCP Sessions
			prevSecIdx = curSecIdx;
		}

		if(prevMin != curMin)
		{
			SCCPGlobal::SCCPSessionCnt = sccpSessionMap.size();
			SCCPGlobal::SCCPKeyMap1Cnt = S_MAP_KEY1.size();
			SCCPGlobal::SCCPKeyMap2Cnt = S_MAP_KEY2.size();
			SCCPGlobal::SCCPImsiTmsiMaoCnt = S_IMSI_IMEI_MAP.size();

			iupsSm->countImsiTmsiEnrty();
			minCnt++;
			if(minCnt >= 5)
			{
				minCnt = 0;
				iupsSm->dumpImsiTmsiMap();
			}
			prevMin = curMin;
		}
	}
	printf("SCCPSessionManager [%d] Shutdown Complete\n", instanceId);
}


VOID SCCPSessionManager::processQueue(int t_index)
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
				}
				if(IPGlobal::NO_OF_INTERFACES > 1)
				{
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 0)
						processQueue_sm_0_i_1_r_0(t_index);
					if(IPGlobal::ROUTER_PER_INTERFACE[1] > 1)
						processQueue_sm_0_i_1_r_1(t_index);
				}
			}
			break;
	}
}

//VOID SCCPSessionManager::processQueue_sm(bool &sccp_msg_sm_busy, int &sccp_msg_sm_cnt, std::vector<MPacket> &sccp_msg_sm, std::map<uint64_t, SCTPChunkMap> &sctpChunkMap_sm)
VOID SCCPSessionManager::processQueue_sm(bool &sccp_msg_sm_busy, int &sccp_msg_sm_cnt, std::map<int, MPacket> &sccp_msg_sm, std::map<uint64_t, SCTPChunkMap> &sctpChunkMap_sm)
{
	int recCnt = sccp_msg_sm_cnt;
	if(recCnt > 0)
	{
		sccp_msg_sm_busy = true;
		for(int i=0; i<recCnt; i++)
		{
			processMessage(&sccp_msg_sm[i], sctpChunkMap_sm[sccp_msg_sm[i].packetNo]);
			sctpChunkMap_sm[sccp_msg_sm[i].packetNo].clear();
			sctpChunkMap_sm.erase(sccp_msg_sm[i].packetNo);
			sccp_msg_sm.erase(i);
			sccp_msg_sm_cnt--;
		}
		sctpChunkMap_sm.clear();
		sccp_msg_sm.clear();
//		sccp_msg_sm = std::vector<MPacket>();
//		sccp_msg_sm.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
		sccp_msg_sm_cnt = 0;
		sccp_msg_sm_busy = false;
	}
}


VOID SCCPSessionManager::processMessage(MPacket *msgObj, SCTPChunkMap sctpChunkMap)
{
	bool found = false;
	sccpSession *pSccpSession = NULL;
	SCTP *pSctpPacket;
	string sessionKey = "";

	for(auto elem : sctpChunkMap)
	{
		pSctpPacket = NULL;
		pSctpPacket = &elem.second;

		if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : processMessage() Type : %s [%d]\n", pSctpPacket->sccp_message_desc, pSctpPacket->sccp_message_type);

		switch(pSctpPacket->sccp_message_type)
		{
			case SCCP_CR:
				sprintf(pSctpPacket->sccp_session_id, "%d%s", pSctpPacket->sctp_opc, pSctpPacket->sccp_slr);

				sessionKey = std::string(pSctpPacket->sccp_session_id);
				pSccpSession = getSccpSession(sessionKey, &found);

				if(!found) {
					create_sccp_session(msgObj, pSctpPacket, pSccpSession);
					pSccpSession->sccp_cr = true;
					pSccpSession->CRTimeEpochMicroSec = getCurrentEpochMicroSeconds();
				}

				pSccpSession->frameSizeBytesUp += msgObj->frSize;
				traceSession("SCCP_CR", pSctpPacket->iups_procedure_desc, msgObj, pSctpPacket);

				if(strlen(pSctpPacket->iups_IMSI) >= 15)
					strcpy(pSccpSession->IMSI,pSctpPacket->iups_IMSI);

				iupsSm->updateSession(pSccpSession, msgObj, pSctpPacket);

				break;

			case SCCP_CC:
				sprintf(pSctpPacket->sccp_session_id, "%d%s", pSctpPacket->sctp_dpc, pSctpPacket->sccp_dlr);

				sessionKey = std::string(pSctpPacket->sccp_session_id);
				pSccpSession = getSccpSession(sessionKey, &found);

				if(!found){
					create_sccp_session(msgObj, pSctpPacket, pSccpSession);
				}

				pSccpSession->frameSizeBytesDn += msgObj->frSize;

				//Update DLR value in session object
				strcpy(pSccpSession->Dlr, pSctpPacket->sccp_slr);

				update_sccp_session(msgObj, pSctpPacket, pSccpSession);
				pSccpSession->sccp_cc = true;
//				pSccpSession->CCTimeEpochMicroSec = msgObj->frTimeEpochNanoSec / 1000;
				pSccpSession->CCTimeEpochMicroSec = getCurrentEpochMicroSeconds();
				create_session_key_lookup(msgObj, pSctpPacket);
				traceSession("SCCP_CC", "", msgObj, pSctpPacket);

				if(strlen(pSctpPacket->iups_IMSI) >= 15)
					strcpy(pSccpSession->IMSI,pSctpPacket->iups_IMSI);

				iupsSm->updateSession(pSccpSession, msgObj, pSctpPacket);

				break;

			case SCCP_RLSD:
				if(msgObj->dirUserNetwork)
					sprintf(pSctpPacket->sccp_session_id,"%d%s", pSctpPacket->sctp_opc, pSctpPacket->sccp_slr);
				else
					sprintf(pSctpPacket->sccp_session_id,"%d%s", pSctpPacket->sctp_dpc, pSctpPacket->sccp_dlr);

				sessionKey = std::string(pSctpPacket->sccp_session_id);
				pSccpSession = getSccpSession(sessionKey, &found);

				if(!found){
					create_sccp_session(msgObj, pSctpPacket, pSccpSession);
				}

				if(msgObj->dirUserNetwork)
					pSccpSession->frameSizeBytesUp += msgObj->frSize;
				else
					pSccpSession->frameSizeBytesDn += msgObj->frSize;


				update_sccp_session(msgObj, pSctpPacket, pSccpSession);
				pSccpSession->sccp_rlsd = true;
				pSccpSession->RLSDTimeEpochMicroSec = getCurrentEpochMicroSeconds();
//				create_session_key_lookup(msgObj, pSctpPacket);
				traceSession("SCCP_RLSD", SCCPGlobal::SCCP_REL_CAUSE_Val_String[pSctpPacket->sccp_release_cause], msgObj, pSctpPacket);

				if(strlen(pSctpPacket->iups_IMSI) >= 10)
					strcpy(pSccpSession->IMSI,pSctpPacket->iups_IMSI);

				iupsSm->updateSession(pSccpSession, msgObj, pSctpPacket);

				break;

			case SCCP_RLC:
				if(msgObj->dirUserNetwork)
					sprintf(pSctpPacket->sccp_session_id,"%d%s", pSctpPacket->sctp_opc, pSctpPacket->sccp_slr);
				else
					sprintf(pSctpPacket->sccp_session_id,"%d%s", pSctpPacket->sctp_dpc, pSctpPacket->sccp_dlr);

				sessionKey = std::string(pSctpPacket->sccp_session_id);
				pSccpSession = getSccpSession(sessionKey, &found);

				if(!found)
					create_sccp_session(msgObj, pSctpPacket, pSccpSession);

				if(msgObj->dirUserNetwork)
					pSccpSession->frameSizeBytesUp += msgObj->frSize;
				else
					pSccpSession->frameSizeBytesDn += msgObj->frSize;

				update_sccp_session(msgObj, pSctpPacket, pSccpSession);

				pSccpSession->sccp_rlc = true;
				pSccpSession->RLCTimeEpochMicroSec = getCurrentEpochMicroSeconds();
				traceSession("SCCP_RLC", "", msgObj, pSctpPacket);

				if(pSccpSession->sccp_cr && pSccpSession->sccp_cc && pSccpSession->sccp_rlsd) {
					pSccpSession->sccp_session_end = true;
				}

				if(strlen(pSctpPacket->iups_IMSI) >= 10)
					strcpy(pSccpSession->IMSI,pSctpPacket->iups_IMSI);

				iupsSm->updateSession(pSccpSession, msgObj, pSctpPacket);

				break;

			case SCCP_DT1:
				strcpy(pSctpPacket->sccp_session_id, get_session_id_from_lookup(pSctpPacket).c_str());
				sessionKey = std::string(pSctpPacket->sccp_session_id);

				if(strcmp(pSctpPacket->sccp_session_id, "NA") != 0)
				{
					pSccpSession = getSccpSession(sessionKey, &found);

					if(!found)
						create_sccp_session(msgObj, pSctpPacket, pSccpSession);

					if(msgObj->dirUserNetwork)
						pSccpSession->frameSizeBytesUp += msgObj->frSize;
					else
						pSccpSession->frameSizeBytesDn += msgObj->frSize;

					update_sccp_session(msgObj, pSctpPacket, pSccpSession);
					traceSession("SCCP_DT1", pSctpPacket->iups_procedure_desc, msgObj, pSctpPacket);
					//Populate IMSI from session tables if not available
					//parser->populateIMSI();
					pSccpSession->sccp_dt = true;
					pSccpSession->DTTimeEpochMicroSec = getCurrentEpochMicroSeconds();

					if(strlen(pSctpPacket->iups_IMSI) >= 10)
						strcpy(pSccpSession->IMSI,pSctpPacket->iups_IMSI);

					iupsSm->updateSession(pSccpSession, msgObj, pSctpPacket);
				}
				break;

			case SCCP_UDT:
				//We get IMSI-TMSI here for mapping on paging request
				if(strlen(pSctpPacket->iups_IMSI) >= 15 && strlen(pSctpPacket->iups_TMSI) >= 5)
					iupsSm->updateImsiTmsiMap(std::string(pSctpPacket->iups_IMSI), std::string(pSctpPacket->iups_TMSI));
				break;
		}

		//Delete session
		if(pSccpSession != NULL && pSccpSession->sccp_session_end){
			delete_sccp_lookup(msgObj, pSctpPacket);
			eraseSCCPKey(pSctpPacket->sccp_session_id);
		}
	}

	sctpChunkMap.clear();
}

void SCCPSessionManager::create_sccp_session(MPacket *msgObj, SCTP *pSctpPacket, sccpSession *pSccpSession)
{
	if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : create_sccp_session()\n");

	strcpy(pSccpSession->SessionId, pSctpPacket->sccp_session_id);
	pSccpSession->StartTimeEpochMicroSec = msgObj->frTimeEpochNanoSec / 1000;
	pSccpSession->EndTimeEpochMicroSec = msgObj->frTimeEpochNanoSec / 1000;
	pSccpSession->LastUpdateTimeEpcohMicroSec = msgObj->frTimeEpochNanoSec / 1000;

	if(msgObj->dirUserNetwork) {
		pSccpSession->TotalBytesUL += msgObj->frSize;
		strcpy(pSccpSession->sourceMacAddr, msgObj->ethSourceMACAddr);
		strcpy(pSccpSession->destMacAddr, msgObj->ethDestMACAddr);
		pSccpSession->SourceIP = msgObj->ipSourceAddr;
		pSccpSession->DestinationIP = msgObj->ipDestAddr;
		pSccpSession->SessionStartDirUp = msgObj->dirUserNetwork;
		pSccpSession->OPC = pSctpPacket->sctp_opc;
		pSccpSession->DPC = pSctpPacket->sctp_dpc;

		if(strcmp(pSctpPacket->sccp_slr, "NA") != 0)
			strcpy(pSccpSession->Slr, pSctpPacket->sccp_slr);
		if(strcmp(pSctpPacket->sccp_dlr, "NA") != 0)
			strcpy(pSccpSession->Dlr, pSctpPacket->sccp_dlr);
	} else {
		pSccpSession->TotalBytesDL += msgObj->frSize;
		strcpy(pSccpSession->destMacAddr, msgObj->ethSourceMACAddr);
		strcpy(pSccpSession->sourceMacAddr, msgObj->ethDestMACAddr);
		pSccpSession->DestinationIP = msgObj->ipSourceAddr;
		pSccpSession->SourceIP = msgObj->ipDestAddr;
		pSccpSession->SessionStartDirUp = msgObj->dirUserNetwork;
		pSccpSession->DPC = pSctpPacket->sctp_opc;
		pSccpSession->OPC = pSctpPacket->sctp_dpc;

		if(strcmp(pSctpPacket->sccp_slr, "NA") != 0)
			strcpy(pSccpSession->Dlr, pSctpPacket->sccp_slr);
		if(strcmp(pSctpPacket->sccp_dlr, "NA") != 0)
			strcpy(pSccpSession->Slr, pSctpPacket->sccp_dlr);
	}

	pSccpSession->sccp_vlanId = msgObj->ethVLanId;

	pSccpSession->SCCPMsgId = pSctpPacket->sccp_message_type;

	if(strlen(pSctpPacket->iups_IMSI) >= 15 && strlen(pSctpPacket->iups_TMSI) >= 5)
		printf("SCCP SM CR :: IMSI [%s] TMSI [%s]\n",pSctpPacket->iups_IMSI, pSctpPacket->iups_TMSI);

	if(strlen(pSctpPacket->iups_IMSI) >= 15)
		strcpy(pSccpSession->IMSI, pSctpPacket->iups_IMSI);
	if(strlen(pSctpPacket->iups_IMEI) >= 15)
		strcpy(pSccpSession->IMEI, pSctpPacket->iups_IMEI);
	if(strlen(pSctpPacket->iups_TMSI) >= 5)
		strcpy(pSccpSession->TMSI, pSctpPacket->iups_TMSI);
	if(strlen(pSctpPacket->iups_MSISDN) >= 10)
		strcpy(pSccpSession->MSISDN, pSctpPacket->iups_MSISDN);

	if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : New session created with id : %s\n", pSccpSession->SessionId);
}

void SCCPSessionManager::update_sccp_session(MPacket *msgObj, SCTP *pSctpPacket, sccpSession *pSccpSession)
{
	if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : update_sccp_session()\n");

	pSccpSession->EndTimeEpochMicroSec = msgObj->frTimeEpochNanoSec / 1000;
	pSccpSession->LastUpdateTimeEpcohMicroSec = msgObj->frTimeEpochNanoSec / 1000;

	if(msgObj->dirUserNetwork)
		pSccpSession->TotalBytesUL += msgObj->frSize;
	else
		pSccpSession->TotalBytesDL += msgObj->frSize;

	if(strlen(pSctpPacket->iups_IMSI) >= 15 && strlen(pSctpPacket->iups_TMSI) >= 5)
		printf("SCCP SM UP :: IMSI [%s] TMSI [%s]\n",pSctpPacket->iups_IMSI, pSctpPacket->iups_TMSI);

	if(strlen(pSctpPacket->iups_IMSI) >= 15)
		strcpy(pSccpSession->IMSI, pSctpPacket->iups_IMSI);
	if(strlen(pSctpPacket->iups_IMEI) >= 15)
		strcpy(pSccpSession->IMEI, pSctpPacket->iups_IMEI);
	if(strlen(pSctpPacket->iups_TMSI) >= 5)
		strcpy(pSccpSession->TMSI, pSctpPacket->iups_TMSI);
	if(strlen(pSctpPacket->iups_MSISDN) >= 10)
		strcpy(pSccpSession->MSISDN, pSctpPacket->iups_MSISDN);

	if(pSctpPacket->sccp_release_cause >= 0){
		pSccpSession->RelCause = pSctpPacket->sccp_release_cause;
	}

	if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : Session [%s] updated\n", pSctpPacket->sccp_session_id);
}

void SCCPSessionManager::create_session_key_lookup(MPacket *msgObj, SCTP *sctpPacket)
{
	string strkey = "";
	char key[30];

	if(msgObj->dirUserNetwork)
	{
		sprintf(key,"%d%d%s",sctpPacket->sctp_dpc,sctpPacket->sctp_opc,sctpPacket->sccp_slr);		//Need to validate
		strkey = std::string(key);
		S_MAP_KEY1[strkey] = std::string(sctpPacket->sccp_session_id);
		sprintf(key,"%d%d%s",sctpPacket->sctp_opc,sctpPacket->sctp_dpc,sctpPacket->sccp_dlr);		//Need to validate
		strkey = std::string(key);
		S_MAP_KEY2[strkey] = std::string(sctpPacket->sccp_session_id);
	}
	else
	{
		sprintf(key,"%d%d%s",sctpPacket->sctp_opc,sctpPacket->sctp_dpc,sctpPacket->sccp_dlr);		//Need to validate
		strkey = std::string(key);
		S_MAP_KEY1[strkey] = std::string(sctpPacket->sccp_session_id);
		sprintf(key,"%d%d%s",sctpPacket->sctp_dpc,sctpPacket->sctp_opc,sctpPacket->sccp_slr);		//Need to validate
		strkey = std::string(key);
		S_MAP_KEY2[strkey] = std::string(sctpPacket->sccp_session_id);
	}
}

string SCCPSessionManager::get_session_id_from_lookup(SCTP *sctpPacket)
{
	// SCCP session id is stored in MAP_KEY1 or MAP_KEY2 depending on OPC+DPC+DLR/SLR
	// We have to search both the MAPs to get the session key depending on which information is available

	char key[30];
	sprintf(key,"%d%d%s",sctpPacket->sctp_opc,sctpPacket->sctp_dpc, sctpPacket->sccp_dlr);

	string strkey = std::string(key);

	if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : get_sccp_session_id() Key : %s\n", key);

	std::map<string, string>::iterator it1 = S_MAP_KEY1.find(strkey);
	if(it1 != S_MAP_KEY1.end())
	{
	   //element found;
		if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : session id [%s] found in S_MAP_KEY1 for key : %s\n", it1->second.c_str(), key);
		return it1->second;

	}else{
		std::map<string, string>::iterator it2 = S_MAP_KEY2.find(strkey);
		//Forward direction session found
		if(it2 != S_MAP_KEY2.end())
		{
		   //element found;
			if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : session id [%s] found in S_MAP_KEY2 for key : %s\n", it1->second.c_str(), key);
			return it2->second;
		}else{
			if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : get_sccp_session_id() NOT FOUND found key : %s\n", key);
			return "NA";
		}
	}
}

sccpSession* SCCPSessionManager::getSccpSession(string sessionKey, bool *found)
{
	sccpSession *pSccpSession = NULL;

	std::map<std::string,sccpSession>::iterator sccpIt = sccpSessionMap.find(sessionKey);
	if(sccpIt != sccpSessionMap.end())
	{
		if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : getSccpSession() FOUND for key : %s\n", sessionKey.c_str());
		pSccpSession = &sccpIt->second;
		*found = true;
	}
	else
	{
		if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : getSccpSession() NOT FOUND for key : %s\n", sessionKey.c_str());
		sccpSession sccp;
		sccp.pIupsGlbSession = new iupsGlobalSession();
		sccpSessionMap[sessionKey]  = sccp;
		pSccpSession = &sccpSessionMap[sessionKey];
		*found = false;
	}
	return pSccpSession;
}

VOID SCCPSessionManager::eraseSCCPKey(string sessionKey)
{
	std::map<std::string,sccpSession>::iterator itsccp = sccpSessionMap.find(sessionKey);
	if(itsccp != sccpSessionMap.end()) {
		delete(itsccp->second.pIupsGlbSession);
		sccpSessionMap.erase(sessionKey);
	}
}

void SCCPSessionManager::delete_sccp_lookup(MPacket *msgObj, SCTP *sctpPacket)
{
	//Three step process
	//Step-1 Fetch IMSI and IMEI from session table
	//Step-1 Update the IMSI table with IMEI if available
	//Step-2 Delete from MAP
//	string imsi; imsi.assign("");
//	string imei; imei.assign("");
//	imsi.assign(select_from_sccp_lookup(SCCPGlobal::COL_IMSI, sctpPacket->sccp_session_id));
//	imei.assign(select_from_sccp_lookup(SCCPGlobal::COL_IMEI, sctpPacket->sccp_session_id));
//	if(!imsi.empty() && imsi.length() >= IMEI_LENGTH_MIN){
//		if(!imei.empty() && imei.length() >= IMEI_LENGTH_MIN){
			//update IMSI table
//			S_IMSI_IMEI_MAP[imsi] = imei;
			//printf("******** updating IMEI for IMSI\n");
//		}
//	}
//	//Now delete the SCCP session
//	std::map<string,struct::s_sccp>::iterator itsccp = S_MAP.find(msgObj->sccp_session_id);
//	if(itsccp != S_MAP.end())
//	{
//		S_MAP.erase(msgObj->sccp_session_id);
//	}
	char key[30];
	sprintf(key,"%d%d%s",sctpPacket->sctp_opc,sctpPacket->sctp_dpc,sctpPacket->sccp_dlr);
	//printf("                SCCP SM : try delete_sccp_lookup() S_MAP_KEY1 for key : %s\n", key);
	string strKey = std::string(key);

	std::map<string, string>::iterator itsccp1;
	std::map<string, string>::iterator itsccp2;

	if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : delete_sccp_lookup() S_MAP_KEY1 for key : %s\n", key);
	itsccp1 = S_MAP_KEY1.find(strKey);
	if(itsccp1 != S_MAP_KEY1.end())
	{
		S_MAP_KEY1.erase(strKey);
		//printf("                SCCP SM : delete_sccp_lookup() S_MAP_KEY1 deleted for key : %s\n", key);
	}
	else
	{
		itsccp2 = S_MAP_KEY2.find(strKey);
		if(itsccp2 != S_MAP_KEY2.end())
		{
			S_MAP_KEY2.erase(strKey);
			//printf("                SCCP SM : delete_sccp_lookup() else S_MAP_KEY2 deleted for key : %s\n", key);
		}
	}

	strcpy(key,"");
	sprintf(key,"%d%d%s",sctpPacket->sctp_dpc,sctpPacket->sctp_opc,sctpPacket->sccp_slr);
	strKey = std::string(key);

	if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : delete_sccp_lookup() S_MAP_KEY2 for key : %s\n", key);
	itsccp2 = S_MAP_KEY2.find(strKey);
	if(itsccp2 != S_MAP_KEY2.end())
	{
		S_MAP_KEY2.erase(strKey);
		//printf("                SCCP SM : delete_sccp_lookup() S_MAP_KEY2 for key : %s\n", key);
	}
	else
	{
		itsccp1 = S_MAP_KEY1.find(strKey);
		if(itsccp1 != S_MAP_KEY1.end())
		{
			S_MAP_KEY1.erase(strKey);
			//printf("                SCCP SM : delete_sccp_lookup() else S_MAP_KEY1 deleted for key : %s\n", key);
		}
	}
}

string SCCPSessionManager::select_from_sccp_lookup(int id, char *sccp_session_Id)
{
	bool found = false;

	string sccpSessionId = std::string(sccp_session_Id);

	sccpSession *s = getSccpSession(sccpSessionId, &found);

	if(found)
	{
		if(id == SCCPGlobal::COL_IMSI){
			if(strlen(s->IMSI) >= 5){
				return std::string(s->IMSI);
			}
		}else if(id == SCCPGlobal::COL_TMSI){
			if(strlen(s->TMSI) > 5){
				return std::string(s->TMSI);
			}
		}else if(id == SCCPGlobal::COL_IMEI){
			if(strlen(s->IMEI) > 5){
				return std::string(s->IMEI);
			}
		}else if(id == SCCPGlobal::COL_MSISDN){
			if(strlen(s->MSISDN) > 5){
				return std::string(s->MSISDN);
			}
		}else if(id == SCCPGlobal::COL_DLR){
			if(strlen(s->Dlr) > 3){
				return std::string(s->Dlr);
			}
		}
	}
	return "";
}

void SCCPSessionManager::traceSession(const char *sender, const char *str, MPacket *msgObj, SCTP *pSctpPacket)
{
	return;
		char file_name[100] = "";
		sprintf(file_name,"%s%s/%s",GContainer::config->TRACE_DIR.c_str(), GContainer::config->sccpConfig->SCCP_WRITE_SESSION_DIR_PREFIX.c_str(), pSctpPacket->sccp_session_id);
		FILE* file = fopen( file_name, "a" );

		if(pSctpPacket->sccp_message_type > -1)
			fprintf(file, "%s :: %s ", sender, SCCPGlobal::SCCP_TYPE_Val_String[pSctpPacket->sccp_message_type]);
		fprintf(file, "%s ", str);
		if(strlen(pSctpPacket->iups_IMSI) > 0)
			fprintf(file, "%s ", pSctpPacket->iups_IMSI);
		if(strlen(pSctpPacket->iups_IMEI) > 0)
			fprintf(file, "%s ", pSctpPacket->iups_IMEI);
		fprintf(file, "\n");

		fclose(file);
}

void SCCPSessionManager::loadTraceSessionIds()
{
	IPGlobal::TraceSCCPSessionIds = ProbeUtility::split(GContainer::config->sccpConfig->SCCP_TRACE_SESSION_IDS, ',');
//	printf("SCCPParser::TraceSessionIds loaded with %d entries\n", IPGlobal::TraceSCCPSessionIds.size());
}


VOID SCCPSessionManager::processQueue_sm_0_i_0_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_0_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_0_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_0, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_0);
			break;

		case 1:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_1_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_1_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_1, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_1);
			break;

		case 2:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_2_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_2_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_2, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_2);
			break;

		case 3:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_3_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_3_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_3, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_3);
			break;

		case 4:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_4_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_4_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_4, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_4);
			break;

		case 5:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_5_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_5_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_5, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_5);
			break;

		case 6:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_6_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_6_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_6, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_6);
			break;

		case 7:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_7_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_7_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_7, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_7);
			break;

		case 8:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_8_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_8_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_8, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_8);
			break;

		case 9:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_9_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_9_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_9, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_9);
			break;
	}
}


VOID SCCPSessionManager::processQueue_sm_0_i_0_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_0_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_0_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_0, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_0);
			break;

		case 1:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_1_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_1_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_1, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_1);
			break;

		case 2:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_2_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_2_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_2, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_2);
			break;

		case 3:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_3_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_3_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_3, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_3);
			break;

		case 4:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_4_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_4_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_4, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_4);
			break;

		case 5:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_5_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_5_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_5, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_5);
			break;

		case 6:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_6_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_6_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_6, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_6);
			break;

		case 7:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_7_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_7_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_7, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_7);
			break;

		case 8:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_8_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_8_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_8, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_8);
			break;

		case 9:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_9_busy, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_9_cnt, SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_9, SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_9);
			break;
	}
}


VOID SCCPSessionManager::processQueue_sm_0_i_1_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_0_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_0_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_0, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_0);
			break;

		case 1:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_1_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_1_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_1, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_1);
			break;

		case 2:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_2_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_2_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_2, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_2);
			break;

		case 3:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_3_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_3_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_3, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_3);
			break;

		case 4:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_4_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_4_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_4, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_4);
			break;

		case 5:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_5_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_5_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_5, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_5);
			break;

		case 6:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_6_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_6_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_6, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_6);
			break;

		case 7:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_7_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_7_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_7, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_7);
			break;

		case 8:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_8_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_8_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_8, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_8);
			break;

		case 9:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_9_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_9_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_9, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_9);
			break;
	}
}


VOID SCCPSessionManager::processQueue_sm_0_i_1_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_0_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_0_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_0, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_0);
			break;

		case 1:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_1_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_1_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_1, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_1);
			break;

		case 2:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_2_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_2_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_2, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_2);
			break;

		case 3:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_3_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_3_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_3, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_3);
			break;

		case 4:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_4_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_4_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_4, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_4);
			break;

		case 5:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_5_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_5_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_5, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_5);
			break;

		case 6:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_6_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_6_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_6, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_6);
			break;

		case 7:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_7_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_7_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_7, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_7);
			break;

		case 8:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_8_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_8_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_8, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_8);
			break;

		case 9:
			processQueue_sm(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_9_busy, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_9_cnt, SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_9, SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_9);
			break;
	}
}



//VOID SCCPSessionManager::initializeRepository()
//{
//	if(IPGlobal::NO_OF_INTERFACES > 0)
//		initializeMpktRepository_i_0(0);
//	if(IPGlobal::NO_OF_INTERFACES > 1)
//		initializeMpktRepository_i_1(1);
//}


//VOID SCCPSessionManager::initializeMpktRepository_i_0(int intfid){
//
//	switch(instanceId)
//	{
//		case 0:
//			{
//				printf("SCCPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("SCCPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//	}
//}


//VOID SCCPSessionManager::initializeMpktRepository_i_1(int intfid){
//
//	switch(instanceId)
//	{
//		case 0:
//			{
//				printf("SCCPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 0){
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				if( IPGlobal::ROUTER_PER_INTERFACE[intfid] > 1){
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_0.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_1.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_2.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_3.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_4.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_5.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_6.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_7.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_8.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//					SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_9.reserve(IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				}
//				printf("SCCPSessionManager [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed\n", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//				TheLog_nc_v3(Log::Info, name()," [%d] Initializing SM Time     Repository for Interface [%d] with [%'08lu] x 10 ...Completed", instanceId, intfid, IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
//			}
//			break;
//
//	}
//}

VOID SCCPSessionManager::cleanTimedOutSccpSessions()
{
	std::string key;
	sccpSession *pSccpSession;
	int cleanCount = 0;
	std::map<int, std::string> cleanupMap;

	uint64_t curEpochMicroSec = getCurrentEpochMicroSeconds();

	for(auto elem : sccpSessionMap)
	{
		key = elem.first;
		pSccpSession = &elem.second;

		if(((pSccpSession->StartTimeEpochMicroSec > 0) && ((curEpochMicroSec - pSccpSession->StartTimeEpochMicroSec) > 120000000)) ||
				((pSccpSession->EndTimeEpochMicroSec > 0) && ((curEpochMicroSec - pSccpSession->EndTimeEpochMicroSec) > 120000000)))
		{
			pSccpSession->sccp_session_end = true;
			cleanupMap[cleanCount] = key;
			cleanKEYMap(pSccpSession);
		}

		cleanCount++;
	}

	if(cleanupMap.size() > 0)
	{
		for(int j=0; j<cleanCount; j++)
		{
			 key = cleanupMap[j];
			 eraseSCCPKey(key);
		}
		cleanupMap.clear();
	}
}

VOID SCCPSessionManager::cleanKEYMap(sccpSession *pSccpSession)
{
	char key[30];

	std::map<string, string>::iterator itsccp1;
	std::map<string, string>::iterator itsccp2;

	sprintf(key,"%d%d%s",pSccpSession->OPC, pSccpSession->DPC, pSccpSession->Dlr);

	string strKey = std::string(key);

	if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : delete_sccp_lookup() S_MAP_KEY1 for key : %s\n", key);

	itsccp1 = S_MAP_KEY1.find(strKey);
	if(itsccp1 != S_MAP_KEY1.end())
	{
		S_MAP_KEY1.erase(strKey);
	}
	else
	{
		itsccp2 = S_MAP_KEY2.find(strKey);
		if(itsccp2 != S_MAP_KEY2.end())
			S_MAP_KEY2.erase(strKey);
	}

	strcpy(key,"");
	sprintf(key,"%d%d%s",pSccpSession->DPC,pSccpSession->OPC,pSccpSession->Slr);
	strKey = std::string(key);

	itsccp1 = S_MAP_KEY1.find(strKey);
	if(PCons::P_SCCPSM && PCons::TRACE) printf("                SCCP SM : delete_sccp_lookup() S_MAP_KEY2 for key : %s\n", key);
	if(itsccp1 != S_MAP_KEY1.end())
	{
		S_MAP_KEY1.erase(strKey);
	}
	else
	{
		itsccp2 = S_MAP_KEY2.find(strKey);
		if(itsccp2 != S_MAP_KEY2.end())
			S_MAP_KEY2.erase(strKey);
	}
}
