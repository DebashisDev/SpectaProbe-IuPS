/*
 * IUPSSessionManager.cpp
 *
 *  Created on: 19-Jul-2016
 *      Author: Deb
 */

#include "IUPSSessionManager.h"


IUPSSessionManager::IUPSSessionManager() {
	_thisLogLevel = 0;
	this->_name = "IUPSSessionManager";
	this->setLogLevel(Log::theLog().level());
	loadImsiTmsiMap();
}

IUPSSessionManager::~IUPSSessionManager() {
	dumpImsiTmsiMap();
}

VOID IUPSSessionManager::dumpImsiTmsiMap()
{
	string filePath = GContainer::config->DATA_DIR + "imsi_tmsi.csv";

	printf("IUPSSessionManager Dumping IMSI TMSI Map to file [%s]...\n", filePath.c_str());
	TheLog_nc_v1(Log::Info, name()," Dumping IMSI TMSI Map to file [%s]...",filePath.c_str());

	ofstream fileHandler;

	fileHandler.open(filePath.c_str(), ios :: out);

	if(fileHandler.fail())
	{
		printf("IUPSSessionManager Error in Opening File : %s\n", filePath.c_str());
		TheLog_nc_v1(Log::Warn, name()," Error in Opening File [%s]...",filePath.c_str());
	}
	else
	{
		for(auto elem : IUPSGlobal::IMSI_TMSI_MAP) {
			fileHandler  << elem.first << "," << elem.second << endl;
		}
	}

	fileHandler.close();

	printf("IUPSSessionManager Dumping IMSI TMSI Map to file [%s]...Completed\n", filePath.c_str());
	TheLog_nc_v1(Log::Info, name()," Dumping IMSI TMSI Map to file [%s]...Completed",filePath.c_str());

}

VOID IUPSSessionManager::loadImsiTmsiMap()
{
	string filePath = GContainer::config->DATA_DIR + "imsi_tmsi.csv";
	std::string line;
	std::string imsi;
	std::string tmsi;
	char * 		pch;
	int lineCnt = 0, loadedCnt = 0;
	ifstream fp;

	fp.open(filePath.c_str());

	if(fp.fail())
	{
		printf("IUPSSessionManager Error in Opening File : %s\n", filePath.c_str());
		TheLog_nc_v1(Log::Warn, name()," Error in Opening File [%s]...",filePath.c_str());
	}
	else
	{

		while(!fp.eof())
		{
			getline(fp,line);
			lineCnt++;

			if(!line.empty() && line.length() > 0)
			{

				pch = strtok ((char *)line.c_str(), ",");
				imsi = std::string(pch);

				pch = strtok (NULL, ",");
				tmsi = std::string(pch);

				if(imsi.length() >= 15 && tmsi.length() >= 5)
				{
					loadedCnt++;
					IUPSGlobal::IMSI_TMSI_MAP[imsi] = tmsi;
					IUPSGlobal::TMSI_IMSI_MAP[tmsi] = imsi;
				}
			}
		}

		fp.close();
	}

	printf("IUPSSessionManager Loaded [%d] IMSI-TMSI records reading [%d] lines from file [%s]\n",loadedCnt, lineCnt, filePath.c_str());
	TheLog_nc_v3(Log::Warn, name()," Loaded [%d] IMSI-TMSI records reading [%d] lines from file [%s]\n",loadedCnt, lineCnt, filePath.c_str());
}


VOID IUPSSessionManager::countImsiTmsiEnrty()
{
	IUPSGlobal::IMSI_TMSI_MAP_SIZE = IUPSGlobal::IMSI_TMSI_MAP.size();
	IUPSGlobal::TMSI_IMSI_MAP_SIZE = IUPSGlobal::TMSI_IMSI_MAP.size();
}

VOID IUPSSessionManager::updateImsiTmsiMap(std::string imsi, std::string tmsi)
{

	std::map<std::string, std::string>::iterator it;
	//Populate IMSI-TMSI Map if necessary
	if(imsi.length() >= 15 && tmsi.length() >= 5)
	{
		it = IUPSGlobal::IMSI_TMSI_MAP.find(imsi);
		if(it != IUPSGlobal::IMSI_TMSI_MAP.end())
		{
			std::string oldtmsi = it->second;
			//Found entry TMSI entry for IMSI
			if(tmsi.compare(oldtmsi) == 0){
				//Same TMSI, Do nothing
			}
			else
			{
				//TMSI has changed for IMSI, so update both the MAPs
				IUPSGlobal::IMSI_TMSI_MAP[imsi] = tmsi;
				IUPSGlobal::TMSI_IMSI_MAP.erase(oldtmsi);
				IUPSGlobal::TMSI_IMSI_MAP[tmsi] = imsi;
			}
		}
		else
		{
			//printf("IUPS SM :: Inserting into IMSI_TMSI_MAP [%s] [%s]\n",imsi.c_str(), tmsi.c_str());
			//IMSI-TMSI not found, so insert in both MAPs
			IUPSGlobal::IMSI_TMSI_MAP[imsi] = tmsi;
			IUPSGlobal::TMSI_IMSI_MAP[tmsi] = imsi;
		}
	}
}


void IUPSSessionManager::updateSession(sccpSession *pSccpSession, MPacket *msgObj, SCTP *pSctpPacket)
{

	if((strlen(pSctpPacket->sccp_session_id) == 0) || (strlen(pSctpPacket->sccp_session_id) < 3))
		return;

	if(PCons::P_IUPSSM && PCons::TRACE) printf("                IUPS SM : updateSession()\n");

	switch(pSctpPacket->sccp_message_type)
	{
		case SCCP_CR:

			if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : Inside pSctpPacket->sccp_message_type == CR\n");
			//Start of a new session on SCCP_CR
			strcpy(pSccpSession->pIupsGlbSession->PLMNFirstId, pSctpPacket->iups_PLMNIdHex);
			strcpy(pSccpSession->pIupsGlbSession->SACFirstId, pSctpPacket->iups_SACIdHex);
			strcpy(pSccpSession->pIupsGlbSession->LACFirstId, pSctpPacket->iups_LACIdHex);
			strcpy(pSccpSession->pIupsGlbSession->RACFirstId, pSctpPacket->iups_RACIdHex);
			strcpy(pSccpSession->pIupsGlbSession->GlobalRNCId, pSctpPacket->iups_RNCId);

			break;

	}

	if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : In between session, only update relevant info\n");

	//---- In between session, only update relevant info ----
	if(msgObj->dirUserNetwork)
		pSccpSession->pIupsGlbSession->TotalBytesUL += pSctpPacket->iups_ranap_bytes;
	else
		pSccpSession->pIupsGlbSession->TotalBytesDL += pSctpPacket->iups_ranap_bytes;

	//Keep populating the last known Ranap Id irrespective of the session
	//this is to ensure populating it in case session terminatted adhoc
	if(pSctpPacket->iups_procedure_code >=0){
		pSccpSession->pIupsGlbSession->LastKnownRanapProcedureId = pSctpPacket->iups_procedure_code;
	}

//	if(strlen(pSctpPacket->iups_IMSI) >= 15 && strlen(pSctpPacket->iups_TMSI) >= 5)
//		printf("IUPS SM :: IMSI [%s] TMSI [%s]\n",pSctpPacket->iups_IMSI, pSctpPacket->iups_TMSI);

	if(strlen(pSctpPacket->iups_IMSI) >= 15)
		strcpy(pSccpSession->IMSI, pSctpPacket->iups_IMSI);

	if(strlen(pSctpPacket->iups_TMSI) >= 5)
		strcpy(pSccpSession->TMSI, pSctpPacket->iups_TMSI);


//	if(strlen(pSctpPacket->iups_IMSI) >= 15 && strlen(pSctpPacket->iups_TMSI) >= 5)
//		printf("IUPS SM :: IMSI [%s] [%s]   TMSI [%s] [%s]\n",pSctpPacket->iups_IMSI,pSctpPacket->iups_IMSI, pSctpPacket->iups_TMSI,pSctpPacket->iups_TMSI);

	if(strlen(pSctpPacket->iups_IMSI) >= 15 && strlen(pSctpPacket->iups_TMSI) >= 5)
	{
		updateImsiTmsiMap(std::string(pSctpPacket->iups_IMSI), std::string(pSctpPacket->iups_TMSI));
	}

	if((strlen(pSccpSession->IMSI) < 15) && strlen(pSccpSession->TMSI) >= 5)
	{
		//printf("IUPS SM :: TMSI but NO IMSI, checking MAP for TMSI [%s]\n", pSccpSession->TMSI);
		//TMSI there but IMSI not present, so try to lookup
		std::string tmsi = std::string(pSccpSession->TMSI);
		std::map<std::string, std::string>::iterator it = IUPSGlobal::TMSI_IMSI_MAP.find(tmsi);
		if(it != IUPSGlobal::TMSI_IMSI_MAP.end())
		{
			//printf("IUPS SM :: Found IMSI [%s] for TMSI [%s]\n", it->second.c_str(), pSccpSession->TMSI);
			strcpy(pSccpSession->IMSI, it->second.c_str());
		}
	}


	//Check for MM_SM session initiation
	if(pSctpPacket->iups_gmmsessionstart)
	{
//		pSccpSession->pIupsGlbSession->gmm_session_count++;
		if(PCons::P_IUPSSM && PCons::DEBUG) printf("Start of a new GMM session [%s]\n",IUPSGlobal::MM_SM_Message_Id_Val_String[pSctpPacket->iups_session_mmsm_id]);
//		TheLog_nc_v1(Log::Info, name(),"  Start of a new GMM session [%s]",IUPSGlobal::MM_SM_Message_Id_Val_String[pSctpPacket->iups_session_mmsm_id]);

		//Create a new transactional session
		iupsTrxSession this_s_trx;

		//Populate this transactional session with values
		this_s_trx.SessionActive = true;		//session is available for writing
		this_s_trx.SessionStartDirUp = msgObj->dirUserNetwork;
		this_s_trx.StartTimeEpochMicroSec = msgObj->frTimeEpochNanoSec / 1000;
		this_s_trx.StartRanapProcedureId = pSctpPacket->iups_procedure_code;
		strcpy(this_s_trx.StartRanapProcedureDesc, pSctpPacket->iups_procedure_desc);
		this_s_trx.StartMMSMMessageId = pSctpPacket->iups_mmsm_id;
		strcpy(this_s_trx.StartMMSMMessageDesc, pSctpPacket->iups_mmsm_desc);
		strcpy(this_s_trx.PLMNFirstId, pSctpPacket->iups_PLMNIdHex);
		strcpy(this_s_trx.SACFirstId, pSctpPacket->iups_SACIdHex);
		strcpy(this_s_trx.LACFirstId, pSctpPacket->iups_LACIdHex);
		strcpy(this_s_trx.RACFirstId, pSctpPacket->iups_RACIdHex);
		strcpy(this_s_trx.RAIOld, pSctpPacket->iups_RAIOldDec);
		strcpy(this_s_trx.RAINew, pSctpPacket->iups_RAINewDec);
		this_s_trx.PDPStaticAddressRequested = pSctpPacket->iups_PDPStaticAddressRequested;
		if(strlen(pSctpPacket->iups_PDPAddressRequested) > 0 && strlen(pSctpPacket->iups_PDPAddressRequested) > 3){
			strcpy(this_s_trx.PDPAddressRequested, pSctpPacket->iups_PDPAddressRequested);
		}

		this_s_trx.reqPdp_Mbrupl = pSctpPacket->iups_pdp_Mbrupl;
		this_s_trx.reqPdp_Mbrdnl = pSctpPacket->iups_pdp_Mbrdnl;

		//Pack it to the MAP
		//pSccpSession->pIupsGlbSession->SGMmSm[pSccpSession->pIupsGlbSession->gmm_session_count] = this_s_trx;
		pSccpSession->pIupsGlbSession->SGMmSm[pSctpPacket->iups_session_mmsm_id] = this_s_trx;

//		if(PCons::P_IUPSSM && PCons::DEBUG) printf("Successfully created new GMM session [%d]\n", pSccpSession->pIupsGlbSession->gmm_session_count);
		// TheLog_nc_v2(Log::Info, name(),"  Successfully created new GMM session [%s] :: Size [%d]",IUPSGlobal::MM_SM_Message_Id_Val_String[pSctpPacket->iups_session_mmsm_id], pSccpSession->pIupsGlbSession->SGMmSm.size());
	}

	//Check for ranap session initiation
	if(pSctpPacket->iups_rsessionstart)
	{
//		pSccpSession->pIupsGlbSession->ranap_session_count++;

		if(PCons::P_IUPSSM && PCons::DEBUG) printf("Start of a new RANAP session [%s]\n", pSctpPacket->iups_session_ranap_id);
		// TheLog_nc_v1(Log::Info, name(),"  Start of a new RANAP session [%s]", pSctpPacket->iups_session_ranap_id);

		//Create a new transactional session
		iupsTrxSession this_s_trx;

		//Populate this transactional session with values
		this_s_trx.SessionActive = true;		//session is available for writing
		this_s_trx.SessionStartDirUp = msgObj->dirUserNetwork;
		this_s_trx.StartTimeEpochMicroSec = msgObj->frTimeEpochNanoSec / 1000;
		this_s_trx.StartRanapProcedureId = pSctpPacket->iups_procedure_code;
		strcpy(this_s_trx.StartRanapProcedureDesc, pSctpPacket->iups_procedure_desc);
		this_s_trx.StartMMSMMessageId = pSctpPacket->iups_mmsm_id;
		strcpy(this_s_trx.StartMMSMMessageDesc, pSctpPacket->iups_mmsm_desc);
		strcpy(this_s_trx.PLMNFirstId, pSctpPacket->iups_PLMNIdHex);
		strcpy(this_s_trx.SACFirstId, pSctpPacket->iups_SACIdHex);
		strcpy(this_s_trx.LACFirstId, pSctpPacket->iups_LACIdHex);
		strcpy(this_s_trx.RACFirstId, pSctpPacket->iups_RACIdHex);
		strcpy(this_s_trx.RAIOld, pSctpPacket->iups_RAIOldDec);
		strcpy(this_s_trx.RAINew, pSctpPacket->iups_RAINewDec);
		this_s_trx.RABCauseId = pSctpPacket->iups_RABCauseId;
		strcpy(this_s_trx.RABCauseDesc, pSctpPacket->iups_RABCauseDesc);

		strcpy(this_s_trx.Mbrupl, pSctpPacket->iups_Mbrupl);
		strcpy(this_s_trx.Mbrdnl, pSctpPacket->iups_Mbrdnl);
		strcpy(this_s_trx.ExtendedMbr, pSctpPacket->iups_ExtendedMbr);

		//Pack it to the MAP
		pSccpSession->pIupsGlbSession->SRanap[std::string(pSctpPacket->iups_session_ranap_id)] = this_s_trx;

		if(PCons::P_IUPSSM && PCons::DEBUG) printf("Successfully created new RANAP session [%s]\n", pSctpPacket->iups_session_ranap_id);
		// TheLog_nc_v2(Log::Info, name(),"  Successfully created new RANAP session [%s] :: Size [%d]", pSctpPacket->iups_session_ranap_id,pSccpSession->pIupsGlbSession->SRanap.size());

	}

	//We will now update rest of the fields using pointer to the transactional object just created

	iupsTrxSession *strx;

	if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : sessiontype [%s] SGMmSm.size [%d] SRanap.size [%d]\n", pSctpPacket->iups_sessiontype == GMM_SESSION ? "GMM" : "RANAP", pSccpSession->pIupsGlbSession->SGMmSm.size(), pSccpSession->pIupsGlbSession->SRanap.size());
	// TheLog_nc_v3(Log::Info, name(),"  IUPS SM : sessiontype [%s] SGMmSm.size [%d] SRanap.size [%d]", pSctpPacket->iups_sessiontype == GMM_SESSION ? "GMM" : "RANAP", pSccpSession->pIupsGlbSession->SGMmSm.size(), pSccpSession->pIupsGlbSession->SRanap.size());

	if(pSctpPacket->iups_sessiontype == GMM_SESSION && pSccpSession->pIupsGlbSession->SGMmSm.size() > 0){
		//Get the session xdr from map
		if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : sessiontype == GMM_SESSION size > 0\n");
		std::map<int, iupsTrxSession>::iterator it_gx = pSccpSession->pIupsGlbSession->SGMmSm.find(pSctpPacket->iups_session_mmsm_id);
		if(it_gx != pSccpSession->pIupsGlbSession->SGMmSm.end())
		{
			strx = &it_gx->second;
			if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : SGMmSm FOUND [%d] [%s]\n",pSctpPacket->iups_session_mmsm_id, IUPSGlobal::MM_SM_Message_Id_Val_String[pSctpPacket->iups_session_mmsm_id]);
		}else{
			iupsTrxSession init_strx;
			strx = &init_strx;
			strx->SessionActive = false;
			if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : SGMmSm NOT FOUND [%d] [%s]\n",pSctpPacket->iups_session_mmsm_id, IUPSGlobal::MM_SM_Message_Id_Val_String[pSctpPacket->iups_session_mmsm_id]);
		}
	}else if(pSctpPacket->iups_sessiontype == RANAP_SESSION && pSccpSession->pIupsGlbSession->SRanap.size() > 0){
		if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : sessiontype == RANAP_SESSION size > 0\n");
		std::map<string, iupsTrxSession>::iterator it_rx = pSccpSession->pIupsGlbSession->SRanap.find(std::string(pSctpPacket->iups_session_ranap_id));
		if(it_rx != pSccpSession->pIupsGlbSession->SRanap.end())
		{
			strx = &it_rx->second;
			if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : SRanap FOUND [%s]\n",pSctpPacket->iups_session_ranap_id);
		}else{
			iupsTrxSession init_strx;
			strx = &init_strx;
			strx->SessionActive = false;
			if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : SRanap NOT FOUND [%s]\n",pSctpPacket->iups_session_ranap_id);
		}
	}
	else{
		if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : else case\n");
		//This case has no signifacance seems
		iupsTrxSession init_strx;
		strx = &init_strx;
		strx->SessionActive = false;
	}

	if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : strx->SessionActive [%d]\n",strx->SessionActive);

	//Write data in between sessions if the session is active
	if(strx->SessionActive)
	{
		if(PCons::P_IUPSSM && PCons::DEBUG) printf("Start populating data to an active TRX session\n");

		if(strlen(pSctpPacket->iups_RABId) > 0 && strlen(pSctpPacket->iups_RABId) > 3)
			strcpy(strx->RABId, pSctpPacket->iups_RABId);

		if(strlen(pSctpPacket->iups_TEId) > 0 && strlen(pSctpPacket->iups_TEId) > 3)
			strcpy(strx->TEId, pSctpPacket->iups_TEId);

//		if(msgObj->RAT >= 0){
//			strx->RATId = msgObj->RAT;
			//strx->RATDesc.assign(msgObj->iups_RATDesc);
//		}

		if(pSctpPacket->iups_RAUpdateId >= 0){
			strx->RAUpdateId = pSctpPacket->iups_RAUpdateId;
			//strx->RAUpdateDesc.assign(pSctpPacket->iups_RAUpdateDesc);
		}
		if(pSctpPacket->iups_EndCauseId >= 0){
			strx->EndCauseId = pSctpPacket->iups_EndCauseId;
			strcpy(strx->EndCauseDesc, pSctpPacket->iups_EndCauseDesc);
		}
		if(pSctpPacket->iups_AttachDetachId >= 0){
			strx->AttachDetachId = pSctpPacket->iups_AttachDetachId;
			strcpy(strx->AttachDetachDir, pSctpPacket->iups_AttachDetachDir);
			strcpy(strx->AttachDetachDesc, pSctpPacket->iups_AttachDetachDesc);
		}

		if(strlen(pSctpPacket->iups_PDPAddressAllocated) > 0 && strlen(pSctpPacket->iups_PDPAddressAllocated) > 3)
			strcpy(strx->PDPAddressAllocated, pSctpPacket->iups_PDPAddressAllocated);

		if(strlen(pSctpPacket->iups_APN) > 3)
			strcpy(strx->APN, pSctpPacket->iups_APN);

		if(pSctpPacket->iups_procedure_code >= 0){
			strx->EndRanapProcedureId = pSctpPacket->iups_procedure_code;
			strcpy(strx->EndRanapProcedureDesc, pSctpPacket->iups_procedure_desc);
		}

		if(msgObj->dirUserNetwork) {
			strx->ByteSizeUL+=pSctpPacket->iups_ranap_bytes;
		}else{
			strx->ByteSizeDL+=pSctpPacket->iups_ranap_bytes;
		}
		if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : Completed populating data to an active TRX session\n");


		if(pSctpPacket->iups_gmmsessionintmd){
			if(PCons::P_IUPSSM && PCons::TRACE) printf("                IUPS SM : GMM Intermediate session for %s\n", pSctpPacket->sccp_session_id);
			strx->IntmdSession = true;
			strx->IntmdTimeEpochMicroSec = msgObj->frTimeEpochNanoSec / 1000;
			strx->IntmdMMSMMessageId = pSctpPacket->iups_mmsm_id;
			strcpy(strx->IntmdMMSMMessageDesc, pSctpPacket->iups_mmsm_desc);
		}

		if(pSctpPacket->iups_mmsm_id == SM_Activate_PDP_context_accept)
		{
//			printf("************* SM_Activate_PDP_context_accept......\n");
			strx->rspPdp_Mbrupl = pSctpPacket->iups_pdp_Mbrupl;
			strx->rspPdp_Mbrdnl = pSctpPacket->iups_pdp_Mbrdnl;
			strx->rspPdp_ExtMbr = pSctpPacket->iups_pdp_ExtMbrdnl;
//			printf("[QOS] Uplink = %d kbps| Dnlink = %d kbps| Ext = %d kbps \n",
//					strx->rspPdp_Mbrupl, strx->rspPdp_Mbrdnl, strx->rspPdp_ExtMbr);

		}
	}

	if(pSctpPacket->iups_gmmsessionend || pSctpPacket->iups_rsessionend){
		if(PCons::P_IUPSSM && PCons::TRACE) printf("                IUPS SM : GMM [%d] / Ranap [%d] session end indication for session MMSMId [%d] / Ranap [%s]\n",pSctpPacket->iups_gmmsessionend, pSctpPacket->iups_rsessionend, pSctpPacket->iups_mmsm_id, pSctpPacket->iups_session_ranap_id);
		// TheLog_nc_v3(Log::Info, name(),"  GMM [%d] / Ranap [%d] session end indication for session %s",pSctpPacket->iups_gmmsessionend, pSctpPacket->iups_rsessionend, pSctpPacket->sccp_session_id);
		strx->EndTimeEpochMicroSec = msgObj->frTimeEpochNanoSec / 1000;
		strx->EndRanapProcedureId = pSctpPacket->iups_procedure_code;
		strcpy(strx->EndRanapProcedureDesc, pSctpPacket->iups_procedure_desc);
		strx->EndMMSMMessageId = pSctpPacket->iups_mmsm_id;
		strcpy(strx->EndMMSMMessageDesc, pSctpPacket->iups_mmsm_desc);
		strcpy(strx->PLMNLastId, pSctpPacket->iups_PLMNIdHex);
		strcpy(strx->SACLastId, pSctpPacket->iups_SACIdHex);
		strcpy(strx->LACLastId, pSctpPacket->iups_LACIdHex);
		strcpy(strx->RACLastId, pSctpPacket->iups_RACIdHex);
		strx->SessionActive = false;
		if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : GMM [%d] / Ranap [%d] session state set to FALSE for session %s\n",pSctpPacket->iups_gmmsessionend, pSctpPacket->iups_rsessionend, pSctpPacket->sccp_session_id);
		// TheLog_nc_v3(Log::Info, name(),"  GMM [%d] / Ranap [%d] session state set to FALSE for session %s",pSctpPacket->iups_gmmsessionend, pSctpPacket->iups_rsessionend, pSctpPacket->sccp_session_id);
	}

	//Check the flush conditions
	//Options are 	1. When SSCP release occur
	//				2. When either RANAP or GMM session ends but IMSI is also available
	bool flush_type_sccp = false;
	bool flush_type_gmm = false;
	bool flush_type_ranap = false;
	if(pSccpSession->sccp_session_end){
		flush_type_sccp = true;		//If this happens to need to check for GMM / RANAP session, anyway both will be flushed
		pSccpSession->EndTimeEpochMicroSec = msgObj->frTimeEpochNanoSec / 1000;
		pSccpSession->LastUpdateTimeEpcohMicroSec = msgObj->frTimeEpochNanoSec / 1000;
		processSCCPSessionFlush(pSccpSession);
	}else{
		//if(msgObj->iups_gmmsessionend && pSccpSession->pIupsGlbSession->imsi_available) flush_type_gmm = true;
		//if(msgObj->iups_rsessionend && pSccpSession->pIupsGlbSession->imsi_available) flush_type_ranap = true;
		if(pSctpPacket->iups_gmmsessionend) flush_type_gmm = true;
		if(pSctpPacket->iups_rsessionend) flush_type_ranap = true;
		pSccpSession->EndTimeEpochMicroSec = msgObj->frTimeEpochNanoSec / 1000;
		pSccpSession->LastUpdateTimeEpcohMicroSec = msgObj->frTimeEpochNanoSec / 1000;

//		if(strlen(pSccpSession->IMSI) > 0) printf("processIupsSessionFlush IMSI::%s\n", pSccpSession->IMSI);
		processIupsSessionFlush(pSccpSession, flush_type_gmm, flush_type_ranap);
	}
}

void IUPSSessionManager::flushSession(sccpSession *pSccpSession)
{
	processSCCPSessionFlush(pSccpSession);
}

void IUPSSessionManager::processIupsSessionFlush(sccpSession *pSccpSession, bool flush_type_gmm, bool flush_type_ranap)
{

		if(flush_type_gmm && pSccpSession->pIupsGlbSession->SGMmSm.size() > 0)
		{
			if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : flush_type_gmm Clear GMM sessions [%d]\n",pSccpSession->pIupsGlbSession->SGMmSm.size());

			int keys[100];
			int cnt = 0;
			for(auto elem : pSccpSession->pIupsGlbSession->SGMmSm)
			{
				iupsTrxSession *strx = &elem.second;
				if(!strx->SessionActive){
					if(strx->EndTimeEpochMicroSec <= 0){
						strx->EndTimeEpochMicroSec = pSccpSession->EndTimeEpochMicroSec;
					}
					if(strx->EndRanapProcedureId == -1){
						strx->EndRanapProcedureId = pSccpSession->pIupsGlbSession->LastKnownRanapProcedureId;
					}
					makeAndFlushSession(GMM_SESSION, pSccpSession, strx);
					keys[cnt] = elem.first;
					cnt++;
				}
			}
			if(cnt > 0)
			{
				for(int i=0; i<cnt; i++)
				{
					pSccpSession->pIupsGlbSession->SGMmSm.erase(keys[i]);
					keys[i] = 0;
				}
				cnt = 0;
			}
		}

		if(flush_type_ranap && pSccpSession->pIupsGlbSession->SRanap.size() > 0)
		{

			if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : flush_type_ranap Clear RANAP sessions [%d]\n",pSccpSession->pIupsGlbSession->SRanap.size());
			string keys[100];
			int cnt = 0;
			//for(int i=pSccpSession->pIupsGlbSession->last_ranap_session_flush_id; i<=pSccpSession->pIupsGlbSession->ranap_session_count; i++){
			for(auto elem : pSccpSession->pIupsGlbSession->SRanap)
			{
				//printf("SRanap Key [%s]\n", elem.first.c_str());
				iupsTrxSession *strx = &elem.second;
				if(!strx->SessionActive){
					if(strx->EndTimeEpochMicroSec <= 0){
						strx->EndTimeEpochMicroSec = pSccpSession->EndTimeEpochMicroSec;
					}
					if(strx->EndRanapProcedureId == -1){
						strx->EndRanapProcedureId = pSccpSession->pIupsGlbSession->LastKnownRanapProcedureId;
					}
					//printf("StartMMSMMessageId [%d]\n",strx->StartMMSMMessageId);
					makeAndFlushSession(RANAP_SESSION, pSccpSession, strx);
					keys[cnt] = elem.first;
					cnt++;
				}
			}
			if(cnt > 0)
			{
				for(int i=0; i<cnt; i++)
				{
					pSccpSession->pIupsGlbSession->SRanap.erase(keys[i]);
					keys[i] = "";
				}
				cnt = 0;
			}
	}
}

void IUPSSessionManager::processSCCPSessionFlush(sccpSession *pSccpSession)
{

	//flush all
	if(pSccpSession->pIupsGlbSession->SGMmSm.size() > 0 ||
		pSccpSession->pIupsGlbSession->SRanap.size() > 0)
	{

		if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : flush_type_sccp Clear all GMM sessions [%d]\n",pSccpSession->pIupsGlbSession->SGMmSm.size());
		//Clear all GMM sessions
		for(auto elem : pSccpSession->pIupsGlbSession->SGMmSm)
		{
			iupsTrxSession *strx = &elem.second;
			//At times disconnection happens from network w/o GMM messages
			//in such cases populate the end transaction data from XDR data
			if(strx->EndTimeEpochMicroSec <= 0){
				strx->EndTimeEpochMicroSec = pSccpSession->EndTimeEpochMicroSec;
			}
			if(strx->EndRanapProcedureId == -1){
				strx->EndRanapProcedureId = pSccpSession->pIupsGlbSession->LastKnownRanapProcedureId;
				//strcpy(strx->EndRanapProcedureDesc,sglb->LastKnownRanapProcedureDesc);
			}
			makeAndFlushSession(GMM_SESSION, pSccpSession, strx);
		}
		//Clear the Map
		pSccpSession->pIupsGlbSession->SGMmSm.clear();


		if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : flush_type_sccp Clear all RANAP sessions [%d]\n",pSccpSession->pIupsGlbSession->SRanap.size());
		//Now Clear all RANAP sessions
		for(auto elem : pSccpSession->pIupsGlbSession->SRanap)
		{
			iupsTrxSession *strx = &elem.second;
			//At times disconnection happens from network w/o GMM messages
			//in such cases populate the end transaction data from XDR data
			if(strx->EndTimeEpochMicroSec <= 0){
				strx->EndTimeEpochMicroSec = pSccpSession->EndTimeEpochMicroSec;
			}
			if(strx->EndRanapProcedureId == -1){
				strx->EndRanapProcedureId = pSccpSession->pIupsGlbSession->LastKnownRanapProcedureId;
			}
			makeAndFlushSession(RANAP_SESSION, pSccpSession, strx);
		}

		//Clear the Map
		pSccpSession->pIupsGlbSession->SRanap.clear();

	}
	else
	{
		if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : SGMmSm.size() < 0 [%d] || SRanap.size() < 0 [%d] Case\n",pSccpSession->pIupsGlbSession->SGMmSm.size(), pSccpSession->pIupsGlbSession->SRanap.size());
		iupsTrxSession *strx = new iupsTrxSession();
		strx->StartRanapProcedureId = strx->EndRanapProcedureId = pSccpSession->pIupsGlbSession->LastKnownRanapProcedureId;
		makeAndFlushSession(SCCP_SESSION, pSccpSession, strx);
		delete (strx);
	}
}

void IUPSSessionManager::makeAndFlushSession(int type, sccpSession *sglb, iupsTrxSession *strx)
{

//	if(strcmp(sglb->Slr, "0b8d17") == 0)
//		printf("makeAndFlushSession CC:%d| CR:%d|DT:%d|RL:%d\n",
//				sglb->sccp_cr, sglb->sccp_cc, sglb->sccp_dt, sglb->sccp_rlsd);

	if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : makeAndFlushSession of Type [%d] having IMSI [%s]\n",type, sglb->IMSI);
	// TheLog_nc_v2(Log::Info, name(),"  makeAndFlushSession of Type [%d] having IMSI [%s]",type, sglb->IMSI);

//	PCons::iups_flush_cnt++;

	iupsSession *pIupsSession = new iupsSession();
	sprintf(pIupsSession->SessionId, "%s_%u", sglb->SessionId, sglb->StartTimeEpochMicroSec);

	if(type == SCCP_SESSION) strcpy(pIupsSession->SessionType, "SCCP");
	else if(type == RANAP_SESSION) strcpy(pIupsSession->SessionType, "RANAP");
	else if(type == GMM_SESSION) strcpy(pIupsSession->SessionType, "GMM");

	pIupsSession->sccp_cr = sglb->sccp_cr;
	pIupsSession->CRTimeEpochMicroSec = sglb->CRTimeEpochMicroSec;
	pIupsSession->sccp_cc = sglb->sccp_cc;
	pIupsSession->CCTimeEpochMicroSec = sglb->CCTimeEpochMicroSec;
	pIupsSession->sccp_dt = sglb->sccp_dt;
	pIupsSession->DTTimeEpochMicroSec = sglb->DTTimeEpochMicroSec;
	pIupsSession->sccp_rlsd = sglb->sccp_rlsd;
	pIupsSession->RLSDTimeEpochMicroSec = sglb->RLSDTimeEpochMicroSec;
	pIupsSession->sccp_rlc = sglb->sccp_rlc;
	pIupsSession->RLCTimeEpochMicroSec = sglb->RLCTimeEpochMicroSec;

	pIupsSession->StartTimeEpochMicroSec = sglb->StartTimeEpochMicroSec;
	pIupsSession->EndTimeEpochMicroSec = sglb->EndTimeEpochMicroSec;
//	pIupsSession->RNC_SGSN = strx->SessionStartDirUp; //(strx->SessionStartDirUp? FLOW_DIR_RNC_SGSN:FLOW_DIR_SGSN_RNC);
	pIupsSession->RNC_SGSN = sglb->SessionStartDirUp; //(strx->SessionStartDirUp? FLOW_DIR_RNC_SGSN:FLOW_DIR_SGSN_RNC); // Debashis
	strcpy(pIupsSession->SourceMAC, sglb->sourceMacAddr);
	strcpy(pIupsSession->DestinationMAC, sglb->destMacAddr);
	pIupsSession->SourceIP = sglb->SourceIP;
	pIupsSession->DestinationIP = sglb->DestinationIP;
	pIupsSession->VLANId = sglb->VLANId;
	pIupsSession->OPC = sglb->OPC;
	pIupsSession->DPC = sglb->DPC;
	strcpy(pIupsSession->SCCPSessionId, sglb->SessionId);
	strcpy(pIupsSession->Slr, sglb->Slr);
	strcpy(pIupsSession->Dlr, sglb->Dlr);
	pIupsSession->SCCPMsgId = sglb->SCCPMsgId;
	strcpy(pIupsSession->SCCPMsgDesc, sglb->SCCPMsgDesc);

	strcpy(pIupsSession->IMSI, sglb->IMSI);
	strcpy(pIupsSession->IMEI, sglb->IMEI);

	pIupsSession->StartRanapProcedureId = strx->StartRanapProcedureId;
	strcpy(pIupsSession->StartRanapProcedureDesc, strx->StartRanapProcedureDesc);
	strcpy(pIupsSession->RNCId, sglb->pIupsGlbSession->GlobalRNCId);
	pIupsSession->StartMMSMMessageId = strx->StartMMSMMessageId;
	strcpy(pIupsSession->StartMMSMMessageDesc, strx->StartMMSMMessageDesc);
	pIupsSession->RATId = strx->RATId;
	pIupsSession->RABCauseId = strx->RABCauseId;
	strcpy(pIupsSession->RABCauseDesc, strx->RABCauseDesc);
	strcpy(pIupsSession->RABId, strx->RABId);
	strcpy(pIupsSession->TEId, strx->TEId);
	pIupsSession->AttachDetachId = strx->AttachDetachId;
	pIupsSession->PDPStaticAddressRequested = strx->PDPStaticAddressRequested;
	strcpy(pIupsSession->PDPAddressRequested, strx->PDPAddressRequested);
	strcpy(pIupsSession->PDPAddressAllocated, strx->PDPAddressAllocated);
	pIupsSession->RAUpdateId = strx->RAUpdateId;
	strcpy(pIupsSession->RAINew, strx->RAINew);
	strcpy(pIupsSession->RAIOld, strx->RAIOld);
	pIupsSession->EndRanapProcedureId = strx->EndRanapProcedureId;
	strcpy(pIupsSession->EndRanapProcedureDesc, strx->EndRanapProcedureDesc);

	if(strx->IntmdSession){
		pIupsSession->IntmdTimeEpochMicroSec = strx->IntmdTimeEpochMicroSec;
		pIupsSession->IntmdMMSMMessageId = strx->IntmdMMSMMessageId;
		strcpy(pIupsSession->IntmdMMSMMessageDesc, strx->IntmdMMSMMessageDesc);
	}
	pIupsSession->EndMMSMMessageId = strx->EndMMSMMessageId;
	strcpy(pIupsSession->EndMMSMMessageDesc, strx->EndMMSMMessageDesc);
	pIupsSession->EndCauseId = strx->EndCauseId;
	strcpy(pIupsSession->EndCauseDesc, strx->EndCauseDesc);
	strcpy(pIupsSession->PLMNFirstId, sglb->pIupsGlbSession->PLMNFirstId);
	strcpy(pIupsSession->LACFirstId, sglb->pIupsGlbSession->LACFirstId);
	strcpy(pIupsSession->SACFirstId, sglb->pIupsGlbSession->SACFirstId);
	strcpy(pIupsSession->RACFirstId, sglb->pIupsGlbSession->RACFirstId);
	strcpy(pIupsSession->APN, strx->APN);

	pIupsSession->ByteSizeUL = strx->ByteSizeUL;
	pIupsSession->ByteSizeDL = strx->ByteSizeDL;

	pIupsSession->frameByteSizeUL = sglb->frameSizeBytesUp;
	pIupsSession->frameByteSizeDL = sglb->frameSizeBytesDn;

	strcpy(pIupsSession->Mbrupl, strx->Mbrupl);
	strcpy(pIupsSession->Mbrdnl, strx->Mbrdnl);
	strcpy(pIupsSession->ExtendedMbr, strx->ExtendedMbr);

	pIupsSession->reqPdp_Mbrupl = strx->reqPdp_Mbrupl;
	pIupsSession->reqPdp_Mbrdnl = strx->reqPdp_Mbrdnl;
	pIupsSession->rspPdp_Mbrupl = strx->rspPdp_Mbrupl;
	pIupsSession->rspPdp_Mbrdnl = strx->rspPdp_Mbrdnl;
	pIupsSession->rspPdp_ExtMbr = strx->rspPdp_ExtMbr;

	if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : Flushing IUPS Session with Id [%s]\n", pIupsSession->SessionId);

	string tdr, csvXdr;

	if(GContainer::config->iupsConfig->IUPS_WRITE_TDR) {
		tdr = buildTDRData(pIupsSession);
		writeXdr(tdr);
	}

	if(GContainer::config->iupsConfig->IUPS_WRITE_XDR) {
		csvXdr = buildCSVData(pIupsSession);
		flushIupsSession(csvXdr);
	}

	delete(pIupsSession);

	// TheLog_nc_v2(Log::Info, name(),"  XDR for IUPS Session with Id [%s] ::  [%s]",pIupsSession->SessionId, tdr.c_str());
}

string IUPSSessionManager::buildCSVData(iupsSession *pIupsSession)
{
	pIupsSession->RATId = 1;

	string csvBuffer = "";

	csvBuffer = "50,142,IUPS,";

	csvBuffer.append(std::to_string(pIupsSession->sccp_cr)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->CRTimeEpochMicroSec)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->sccp_cc)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->CCTimeEpochMicroSec)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->sccp_dt)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->DTTimeEpochMicroSec)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->sccp_rlsd)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->RLSDTimeEpochMicroSec)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->sccp_rlc)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->RLCTimeEpochMicroSec)).append(",");

	csvBuffer.append(pIupsSession->SessionId).append(",");
	csvBuffer.append(pIupsSession->SessionType).append(",");
	csvBuffer.append(std::to_string(pIupsSession->StartTimeEpochMicroSec)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->EndTimeEpochMicroSec)).append(",");

	if(pIupsSession->RNC_SGSN)
		csvBuffer.append("RNC->SGSN");
	else
		csvBuffer.append("SGSN->RNC");

	csvBuffer.append(",");
	csvBuffer.append(pIupsSession->SourceMAC).append(",");
	csvBuffer.append(pIupsSession->DestinationMAC).append(",");
	csvBuffer.append(std::to_string(pIupsSession->SourceIP)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->DestinationIP)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->VLANId)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->OPC)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->DPC)).append(",");
	csvBuffer.append(pIupsSession->Slr).append(",");
	csvBuffer.append(pIupsSession->Dlr).append(",");
	csvBuffer.append(std::to_string(pIupsSession->SCCPMsgId)).append(",");
	csvBuffer.append(std::string(SCCPGlobal::SCCP_TYPE_Val_String[pIupsSession->SCCPMsgId])).append(",");

	if(strlen(pIupsSession->IMSI) < 10)
		csvBuffer.append("NA").append(",");
	else
		csvBuffer.append(pIupsSession->IMSI).append(",");

	if(strlen(pIupsSession->IMEI) < 10)
		csvBuffer.append("NA").append(",");
	else
		csvBuffer.append(pIupsSession->IMEI).append(",");


	if(pIupsSession->StartRanapProcedureId == -1){
		csvBuffer.append("-1,NA,");
	}
	else{
		csvBuffer.append(std::to_string(pIupsSession->StartRanapProcedureId)).append(",");
		if(strlen(pIupsSession->StartRanapProcedureDesc) <= 0)
			strcpy(pIupsSession->StartRanapProcedureDesc, IUPSGlobal::Procedure_Val_String[pIupsSession->StartRanapProcedureId]);
		csvBuffer.append(std::string(pIupsSession->StartRanapProcedureDesc)).append(",");

	}

	if(strlen(pIupsSession->RNCId) > 1){
		csvBuffer.append(std::to_string(strtol((const char*)pIupsSession->RNCId, NULL, 16))).append(",");
	}else{
		csvBuffer.append("-1").append(",");
	}

	if(pIupsSession->StartMMSMMessageId == -1){
		csvBuffer.append("-1,NA,");
	}
	else{
		csvBuffer.append(std::to_string(pIupsSession->StartMMSMMessageId)).append(",");
		csvBuffer.append(std::string(IUPSGlobal::MM_SM_Message_Id_Val_String[pIupsSession->StartMMSMMessageId])).append(",");
	}

	csvBuffer.append(std::to_string(pIupsSession->RATId)).append(",");
	csvBuffer.append("UTRAN").append(",");

	if(pIupsSession->RABCauseId == -1){
		csvBuffer.append("-1,NA,");
	}
	else{
		csvBuffer.append(std::to_string(pIupsSession->RABCauseId)).append(",");
		csvBuffer.append(pIupsSession->RABCauseDesc).append(",");
	}

	if(strlen(pIupsSession->RABId) < 1)
		csvBuffer.append("NA").append(",");
	else
		csvBuffer.append(pIupsSession->RABId).append(",");

	if(strlen(pIupsSession->TEId) < 1)
		csvBuffer.append("NA").append(",");
	else
		csvBuffer.append(pIupsSession->TEId).append(",");


	if(pIupsSession->AttachDetachId == -1){
		csvBuffer.append("-1,NA,NA,");
	}else{
		csvBuffer.append(std::to_string(pIupsSession->AttachDetachId)).append(",");
		csvBuffer.append(pIupsSession->AttachDetachDir).append(",");
		csvBuffer.append(pIupsSession->AttachDetachDesc).append(",");
	}

	if(pIupsSession->PDPStaticAddressRequested == -1){
		csvBuffer.append("-1,");
	}
	else{
		csvBuffer.append(std::to_string(pIupsSession->PDPStaticAddressRequested)).append(",");
	}


	if(strlen(pIupsSession->PDPAddressRequested) < 1)
		csvBuffer.append("NA").append(",");
	else
		csvBuffer.append(pIupsSession->PDPAddressRequested).append(",");

	if(strlen(pIupsSession->PDPAddressAllocated) < 1)
		csvBuffer.append("NA").append(",");
	else
		csvBuffer.append(pIupsSession->PDPAddressAllocated).append(",");


	if(pIupsSession->RAUpdateId == -1){
		csvBuffer.append("-1,NA,");
	}else{
		csvBuffer.append(std::to_string(pIupsSession->RAUpdateId)).append(",");
		csvBuffer.append(IUPSGlobal::RA_Update_Type_Val_String[pIupsSession->RAUpdateId]).append(",");
	}

	if(strlen(pIupsSession->RAINew) < 1)
		csvBuffer.append("NA").append(",");
	else
		csvBuffer.append(pIupsSession->RAINew).append(",");

	if(strlen(pIupsSession->RAIOld) < 1)
		csvBuffer.append("NA").append(",");
	else
		csvBuffer.append(pIupsSession->RAIOld).append(",");


	if(pIupsSession->EndRanapProcedureId == -1){
		csvBuffer.append("-1,NA,");
	}
	else{
		csvBuffer.append(std::to_string(pIupsSession->EndRanapProcedureId)).append(",");
		csvBuffer.append(IUPSGlobal::Procedure_Val_String[pIupsSession->EndRanapProcedureId]).append(",");
	}

	if(pIupsSession->IntmdMMSMMessageId == -1){
		csvBuffer.append("-1,NA,0,");
	}else{
		csvBuffer.append(std::to_string(pIupsSession->IntmdMMSMMessageId)).append(",");
		csvBuffer.append(std::string(IUPSGlobal::MM_SM_Message_Id_Val_String[pIupsSession->IntmdMMSMMessageId])).append(",");
		csvBuffer.append(std::to_string(pIupsSession->IntmdTimeEpochMicroSec)).append(",");
	}

	if(pIupsSession->EndMMSMMessageId == -1){
		csvBuffer.append("-1,NA,");
	}else{
		csvBuffer.append(std::to_string(pIupsSession->EndMMSMMessageId)).append(",");
		csvBuffer.append(std::string(IUPSGlobal::MM_SM_Message_Id_Val_String[pIupsSession->EndMMSMMessageId])).append(",");
	}
	if(pIupsSession->EndCauseId == -1){
		csvBuffer.append("-1,");
	}
	else{
		csvBuffer.append(std::to_string(pIupsSession->EndCauseId)).append(",");
	}


	if(strlen(pIupsSession->EndCauseDesc) < 1)
		csvBuffer.append("NA").append(",");
	else
		csvBuffer.append(pIupsSession->EndCauseDesc).append(",");

	if(strlen(pIupsSession->PLMNFirstId) < 1)
		csvBuffer.append("NA").append(",");
	else
		csvBuffer.append(pIupsSession->PLMNFirstId).append(",");

	if(strlen(pIupsSession->LACFirstId) < 1)
		csvBuffer.append("NA").append(",");
	else
		csvBuffer.append(pIupsSession->LACFirstId).append(",");

	if(strlen(pIupsSession->SACFirstId) < 1)
		csvBuffer.append("NA").append(",");
	else
		csvBuffer.append(pIupsSession->SACFirstId).append(",");

	if(strlen(pIupsSession->RACFirstId) < 1)
		csvBuffer.append("NA").append(",");
	else
		csvBuffer.append(pIupsSession->RACFirstId).append(",");

	if(strlen(pIupsSession->APN) < 1)
		csvBuffer.append("NA").append(",");
	else
		csvBuffer.append(pIupsSession->APN).append(",");

	csvBuffer.append(std::to_string(pIupsSession->ByteSizeUL)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->ByteSizeDL)).append(",");

	csvBuffer.append(std::to_string(pIupsSession->frameByteSizeUL)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->frameByteSizeDL)).append(",");

	csvBuffer.append(std::string(pIupsSession->Mbrupl)).append(",");
	csvBuffer.append(std::string(pIupsSession->ExtendedMbr)).append(",");

	csvBuffer.append(std::to_string(pIupsSession->reqPdp_Mbrupl)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->reqPdp_Mbrdnl)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->rspPdp_Mbrupl)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->rspPdp_Mbrdnl)).append(",");
	csvBuffer.append(std::to_string(pIupsSession->rspPdp_ExtMbr));

	if(PCons::P_IUPSSM && PCons::DEBUG) printf("                IUPS SM : csvBuffer [%s]\n", csvBuffer.c_str());

	return csvBuffer;
}

string IUPSSessionManager::buildTDRData(iupsSession *pIupsSession)
{

	string tdrdata;
	char buffer[5000];
	char csvBuffer[5000];
	char tmpData[1000];

	pIupsSession->RATId = 1;

//	if(strcmp(pIupsSession->Slr, "0b8d17") == 0)
//		printf("buildTDRData CC:%d| CR:%d|DT:%d|RL:%d\n",
//				pIupsSession->sccp_cr, pIupsSession->sccp_cc, pIupsSession->sccp_dt, pIupsSession->sccp_rlsd);

	char prefix[4] = "_p_";
	sprintf(buffer, "-- IuPS TDR -------------------------------------\n");
	tdrdata.assign(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sProbe_Id			: 50\n", prefix);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sProtocol_Id			: 142\n", prefix);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sProtocol_Desc		: RANAP\n", prefix);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sSCCP_CR			: %d [%lu]\n", prefix, pIupsSession->sccp_cr, pIupsSession->CRTimeEpochMicroSec);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sSCCP_CC			: %d [%lu]\n", prefix, pIupsSession->sccp_cc, pIupsSession->CCTimeEpochMicroSec);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sSCCP_DT1			: %d [%lu]\n", prefix, pIupsSession->sccp_dt, pIupsSession->DTTimeEpochMicroSec);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sSCCP_RLSD			: %d [%lu]\n", prefix, pIupsSession->sccp_rlsd, pIupsSession->RLSDTimeEpochMicroSec);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sSCCP_RLC			: %d [%lu]\n", prefix, pIupsSession->sccp_rlc, pIupsSession->RLCTimeEpochMicroSec);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sSession_Id			: %s\n", prefix, pIupsSession->SessionId);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sSession_Type			: %s\n", prefix, pIupsSession->SessionType);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sStart_Time_MS		: %lu\n", prefix, pIupsSession->StartTimeEpochMicroSec);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sEnd_Time_MS	 		: %lu\n", prefix,  pIupsSession->EndTimeEpochMicroSec);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	if(pIupsSession->RNC_SGSN)
		sprintf(buffer, "	%sInitiation_Dir		: RNC->SGSN\n", prefix);
	else
		sprintf(buffer, "	%sInitiation_Dir		: SGSN->RNC\n", prefix);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sSource_Mac_Addr		: %s\n", prefix, pIupsSession->SourceMAC);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sDestination_Mac_Addr		: %s\n", prefix, pIupsSession->DestinationMAC);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sSource_IP_Addr		: %u\n", prefix, pIupsSession->SourceIP);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sDestination_IP_Addr		: %u\n", prefix, pIupsSession->DestinationIP);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sOPC				: %d\n", prefix, pIupsSession->OPC);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sDPC				: %d\n", prefix, pIupsSession->DPC);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sSCCP SLR			: %s\n", prefix, pIupsSession->Slr);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sSCCP DLR			: %s\n", prefix, pIupsSession->Dlr);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sSCCP Message Desc		: %s\n", prefix, SCCPGlobal::SCCP_TYPE_Val_String[pIupsSession->SCCPMsgId]);
	tdrdata.append(buffer);
	buffer[0] = '\0';

	if(strlen(pIupsSession->IMSI) < 10){
		strcpy(tmpData,",");
		sprintf(buffer, "	%sIMSI				: not populated yet\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
	}
	else{
		sprintf(tmpData,"%s,",pIupsSession->IMSI);
		sprintf(buffer, "	%sIMSI				: %s\n", prefix, pIupsSession->IMSI);
		tdrdata.append(buffer);
		buffer[0] = '\0';
	}
	strcat(csvBuffer,tmpData);

	tmpData[0] = '\0';
	if(strlen(pIupsSession->IMEI) < 10){
		strcpy(tmpData,",");
		sprintf(buffer, "	%sIMEI				: not populated yet\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
	}
	else{
		sprintf(tmpData,"%s,",pIupsSession->IMEI);
		sprintf(buffer, "	%sIMEI				: %s\n", prefix, pIupsSession->IMEI);
		tdrdata.append(buffer);
		buffer[0] = '\0';
	}
	strcat(csvBuffer,tmpData);

	if(pIupsSession->StartRanapProcedureId == -1){
		sprintf(buffer, "	%sRANAP_Procedure_Id		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sRANAP_Procedure_Desc		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		strcat(csvBuffer,",,");
	}
	else{
		sprintf(buffer, "	%sRANAP_Procedure_Id		: %d\n", prefix, pIupsSession->StartRanapProcedureId);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		//sprintf(buffer, "	%sRANAP_Procedure_Desc		: %s\n", prefix, PCons::Procedure_Val_String[pIupsSession->StartRanapProcedureId]);
		sprintf(buffer, "	%sRANAP_Procedure_Desc		: %s\n", prefix, pIupsSession->StartRanapProcedureDesc);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		tmpData[0] = '\0';
		sprintf(tmpData,"%d,%s,",pIupsSession->StartRanapProcedureId,pIupsSession->StartRanapProcedureDesc);
		strcat(csvBuffer,tmpData);
	}

	if(strlen(pIupsSession->RNCId) > 1){
		sprintf(buffer, "	%sRNC_Id			: %d [0x%s]\n", prefix, (int)strtol(pIupsSession->RNCId, NULL, 16), pIupsSession->RNCId);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		tmpData[0] = '\0';
		sprintf(tmpData,"%d,",(int)strtol(pIupsSession->RNCId, NULL, 16));
		strcat(csvBuffer,tmpData);
	}else{
		sprintf(buffer, "	%sRNC_Id			:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		strcat(csvBuffer,",");
	}

	if(pIupsSession->StartMMSMMessageId == -1){
		sprintf(buffer, "	%sGMM_SM_Id			:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sGMM_SM_Desc			:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		strcat(csvBuffer,",,");
	}
	else{
		sprintf(buffer, "	%sGMM_SM_Id			: %d\n", prefix, pIupsSession->StartMMSMMessageId);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sGMM_SM_Desc			: %s\n", prefix, IUPSGlobal::MM_SM_Message_Id_Val_String[pIupsSession->StartMMSMMessageId]);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		tmpData[0] = '\0';
		sprintf(tmpData,"%d,%s,",pIupsSession->StartMMSMMessageId,IUPSGlobal::MM_SM_Message_Id_Val_String[pIupsSession->StartMMSMMessageId]);
		strcat(csvBuffer,tmpData);
	}


	sprintf(buffer, "	%sRAT_Id			: %d\n", prefix, pIupsSession->RATId);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sRAT_Desc			: UTRAN\n", prefix);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	tmpData[0] = '\0';
	sprintf(tmpData,"%d,UTRAN,",pIupsSession->RATId);
	strcat(csvBuffer,tmpData);

	if(pIupsSession->RABCauseId == -1){
		sprintf(buffer, "	%sRAB_Cause_Id			:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sRAB_Cause_Desc		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		strcat(csvBuffer,",,");
	}
	else{
		sprintf(buffer, "	%sRAB_Cause_Id			: %d\n", prefix, pIupsSession->RABCauseId);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sRAB_Cause_Desc		: %s\n", prefix, pIupsSession->RABCauseDesc);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		tmpData[0] = '\0';
		sprintf(tmpData,"%d,%s,",pIupsSession->RABCauseId,pIupsSession->RABCauseDesc);
		strcat(csvBuffer,tmpData);
	}


	sprintf(buffer, "	%sRAB_Id			: %s\n", prefix, pIupsSession->RABId);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sTunnel_Id			: %s\n", prefix, pIupsSession->TEId);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	tmpData[0] = '\0';
	sprintf(tmpData,"%s,%s,",pIupsSession->RABId,pIupsSession->TEId);
	strcat(csvBuffer,tmpData);

	if(pIupsSession->AttachDetachId == -1){
		sprintf(buffer, "	%sAttach_Detach_Id		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sAttach_Detach_Dir		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sAttach_Detach_Desc		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		strcat(csvBuffer,",,,");
	}else{
		sprintf(buffer, "	%sAttach_Detach_Id		: %d\n", prefix, pIupsSession->AttachDetachId);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sAttach_Detach_Dir		: %s\n", prefix, pIupsSession->AttachDetachDir);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sAttach_Detach_Desc		: %s\n", prefix, pIupsSession->AttachDetachDesc);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		tmpData[0] = '\0';
		sprintf(tmpData,"%d,%s,%s,",pIupsSession->AttachDetachId,pIupsSession->AttachDetachDir,pIupsSession->AttachDetachDesc);
		strcat(csvBuffer,tmpData);
	}

	if(pIupsSession->PDPStaticAddressRequested == -1){
		sprintf(buffer, "	%sPDP_Static_Addr_Requested	:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		strcat(csvBuffer,",");
	}
	else{
		sprintf(buffer, "	%sPDP_Static_Addr_Requested	: %d\n", prefix, pIupsSession->PDPStaticAddressRequested);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		tmpData[0] = '\0';
		sprintf(tmpData,"%d,",pIupsSession->PDPStaticAddressRequested);
		strcat(csvBuffer,tmpData);
	}

	sprintf(buffer, "	%sPDP_Addr_Requested		: %s\n", prefix, pIupsSession->PDPAddressRequested);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sPDP_Addr_Allocated		: %s\n", prefix, pIupsSession->PDPAddressAllocated);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	tmpData[0] = '\0';
	sprintf(tmpData,"%s,%s,",pIupsSession->PDPAddressRequested, pIupsSession->PDPAddressAllocated);
	strcat(csvBuffer,tmpData);

	if(pIupsSession->RAUpdateId == -1){
		sprintf(buffer, "	%sRA_Update_Id			:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sRA_Update_Desc		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		strcat(csvBuffer,",,");
	}else{
		sprintf(buffer, "	%sRA_Update_Id			: %d\n", prefix, pIupsSession->RAUpdateId);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sRA_Update_Desc		: %s\n", prefix, IUPSGlobal::RA_Update_Type_Val_String[pIupsSession->RAUpdateId]);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		tmpData[0] = '\0';
		sprintf(tmpData,"%d,%s,",pIupsSession->RAUpdateId, IUPSGlobal::RA_Update_Type_Val_String[pIupsSession->RAUpdateId]);
		strcat(csvBuffer,tmpData);
	}


	sprintf(buffer, "	%sRouting_Area_Id		: %s\n", prefix, pIupsSession->RAINew);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sOld_Routing_Area_Id		: %s\n", prefix, pIupsSession->RAIOld);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	tmpData[0] = '\0';
	sprintf(tmpData,"%s,%s,",pIupsSession->RAINew, pIupsSession->RAIOld);
	strcat(csvBuffer,tmpData);

	if(pIupsSession->IntmdMMSMMessageId == -1){
		sprintf(buffer, "	%sGMM_SM_Intmd_Id		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sGMM_SM_Intmd_Desc		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		strcat(csvBuffer,",,");
		sprintf(buffer, "	%sGMM_SM_Intmd_TimeMS		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sGMM_SM_Intmd_Time		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		strcat(csvBuffer,",,");
	}
	else{
		sprintf(buffer, "	%sGMM_SM_Intmd_Id		: %d\n", prefix, pIupsSession->IntmdMMSMMessageId);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sGMM_SM_Intmd_Desc		: %s\n", prefix, IUPSGlobal::MM_SM_Message_Id_Val_String[pIupsSession->IntmdMMSMMessageId]);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		tmpData[0] = '\0';
		sprintf(tmpData,"%d,%s,",pIupsSession->IntmdMMSMMessageId,IUPSGlobal::MM_SM_Message_Id_Val_String[pIupsSession->IntmdMMSMMessageId]);
		strcat(csvBuffer,tmpData);

		sprintf(buffer, "	%sGMM_SM_Intmd_TimeMS		: %lu\n", prefix, pIupsSession->IntmdTimeEpochMicroSec);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		strcat(csvBuffer,tmpData);
	}


	if(pIupsSession->EndRanapProcedureId == -1){
		sprintf(buffer, "	%sRANAP_End_Procedure_Id		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sRANAP_End_Procedure_Desc		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		strcat(csvBuffer,",,");
	}
	else{
		sprintf(buffer, "	%sRANAP_End_Procedure_Id	: %d\n", prefix, pIupsSession->EndRanapProcedureId);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sRANAP_End_Procedure_Desc	: %s\n", prefix, IUPSGlobal::Procedure_Val_String[pIupsSession->EndRanapProcedureId]);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		tmpData[0] = '\0';
		sprintf(tmpData,"%d,%s,",pIupsSession->EndRanapProcedureId, IUPSGlobal::Procedure_Val_String[pIupsSession->EndRanapProcedureId]);
		strcat(csvBuffer,tmpData);
	}

	if(pIupsSession->EndMMSMMessageId == -1){
		sprintf(buffer, "	%sGMM_SM_End_Id		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sGMM_SM_End_Desc		:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		strcat(csvBuffer,",,");
	}else{
		sprintf(buffer, "	%sGMM_SM_End_Id		: %d\n", prefix, pIupsSession->EndMMSMMessageId);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		sprintf(buffer, "	%sGMM_SM_End_Desc		: %s\n", prefix, IUPSGlobal::MM_SM_Message_Id_Val_String[pIupsSession->EndMMSMMessageId]);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		tmpData[0] = '\0';
		sprintf(tmpData,"%d,%s,",pIupsSession->EndMMSMMessageId, IUPSGlobal::MM_SM_Message_Id_Val_String[pIupsSession->EndMMSMMessageId]);
		strcat(csvBuffer,tmpData);
	}
	if(pIupsSession->EndCauseId == -1){
		strcat(csvBuffer,",");
		sprintf(buffer, "	%sEnd_Cause			:\n", prefix);
		tdrdata.append(buffer);
		buffer[0] = '\0';
	}
	else{
		sprintf(buffer, "	%sEnd_Cause			: %d\n", prefix, pIupsSession->EndCauseId);
		tdrdata.append(buffer);
		buffer[0] = '\0';
		tmpData[0] = '\0';
		sprintf(tmpData,"%d,",pIupsSession->EndCauseId);
		strcat(csvBuffer,tmpData);
	}

	sprintf(buffer, "	%sEnd_Cause_Desc		: %s\n", prefix, pIupsSession->EndCauseDesc);
	tdrdata.append(buffer);
	buffer[0] = '\0';

	sprintf(buffer, "	%sPLMN_Id			: 0x%s\n", prefix, pIupsSession->PLMNFirstId);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sLAC_Id			: 0x%s\n", prefix, pIupsSession->LACFirstId);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sSAC_Id			: 0x%s\n", prefix, pIupsSession->SACFirstId);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sRAC_Id			: 0x%s\n", prefix, pIupsSession->RACFirstId);
	tdrdata.append(buffer);
	buffer[0] = '\0';

	sprintf(buffer, "	%sAPN				: %s\n", prefix, pIupsSession->APN);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sBytes_Transfer_ul		: %d\n", prefix, pIupsSession->ByteSizeUL);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sBytes_Transfer_dl		: %d\n", prefix, pIupsSession->ByteSizeDL);
	tdrdata.append(buffer);
	buffer[0] = '\0';

	sprintf(buffer, "	%sTotal_Transfer_ul		: %d\n", prefix, pIupsSession->frameByteSizeUL);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sTotal_Transfer_dl		: %d\n", prefix, pIupsSession->frameByteSizeDL);
	tdrdata.append(buffer);
	buffer[0] = '\0';

	sprintf(buffer, "	%sMBR Up            		: %s\n", prefix, pIupsSession->Mbrdnl);
	tdrdata.append(buffer);
	buffer[0] = '\0';
	sprintf(buffer, "	%sExtended MBR         	: %s\n", prefix, pIupsSession->ExtendedMbr);
	tdrdata.append(buffer);
	buffer[0] = '\0';

	sprintf(buffer, "	%sReq_Pdp_MBR_Up          	: %d\n", prefix, pIupsSession->reqPdp_Mbrupl);
	tdrdata.append(buffer);
	buffer[0] = '\0';

	sprintf(buffer, "	%sReq_Pdp_MBR_Dn         	: %d\n", prefix, pIupsSession->reqPdp_Mbrdnl);
	tdrdata.append(buffer);
	buffer[0] = '\0';

	sprintf(buffer, "	%sRsp_Pdp_MBR_Up            	: %d\n", prefix, pIupsSession->rspPdp_Mbrupl);
	tdrdata.append(buffer);
	buffer[0] = '\0';

	sprintf(buffer, "	%sRsp_Pdp_MBR_Dn            	: %d\n", prefix, pIupsSession->rspPdp_Mbrupl);
	tdrdata.append(buffer);
	buffer[0] = '\0';

	sprintf(buffer, "	%sRsp_Pdp_ExtMBR Dn        	: %d\n", prefix, pIupsSession->rspPdp_ExtMbr);
	tdrdata.append(buffer);
	buffer[0] = '\0';

	sprintf(buffer, "-------------------------------------------------\n");
	tdrdata.append(buffer);
	buffer[0] = '\0';

	return tdrdata;
}

//void IUPSSessionManager::writeTraceTdr(string sccpSessionId, string str)
//{
//	char file_name[100] = "";
//	sprintf(file_name,"%s%s/%s",GContainer::config->TRACE_DIR.c_str(), GContainer::config->iupsConfig->IUPS_WRITE_TRACE_TDR_DIR_PREFIX.c_str(), sccpSessionId.c_str());
//	printf("File : %s\n",file_name);
//	FILE* file = fopen( file_name, "a" );
//	fprintf(file, "%s\n", str.c_str());
//	fclose(file);
//}

void IUPSSessionManager::writeXdr(string str)
{
	char file_name[100] = "";

	time_t ltime;
	struct tm *Tm;
	ltime=time(NULL);
	Tm=localtime(&ltime);ltime=time(NULL);

//	sprintf(timeStr, "%d-%d-%d", Tm->tm_hour, Tm->tm_mon, Tm->tm_year+1900);

	sprintf(file_name,"/data/xdr/SpectaProbe/iups/iups_%d-%d-%d.tdr", Tm->tm_year+1900, Tm->tm_mon+1, Tm->tm_hour);

	FILE* file = fopen( file_name, "a" );
	fprintf(file, "%s\n", str.c_str());
	fclose(file);
}

VOID IUPSSessionManager::flushIupsSession(string csvxdr)
{
//	long epochSecNow = getCurrentEpochSeconds();
//	int idx = (((epochSecNow % 100) /10)  % IPGlobal::FLUSHER_TIMEINDEX) + 1;
//	if(idx >= IPGlobal::FLUSHER_TIMEINDEX) idx = idx - IPGlobal::FLUSHER_TIMEINDEX;

//	gettimeofday(&curTime, NULL);
//	int index = FLUSHER_WRITE_TIME_INDEX(curTime.tv_sec);

	long epochSecNow = getCurrentEpochSeconds();
	int idx = WRITE_TIME_INDEX(epochSecNow);

	switch(idx)
	{
			case 0:
				IUPSFlushRepository::iupsFlushMap_sm_0_t_0[IUPSFlushRepository::iupsFlushMap_sm_0_t_0_cnt] = csvxdr;
				IUPSFlushRepository::iupsFlushMap_sm_0_t_0_cnt++;
				break;
			case 1:
				IUPSFlushRepository::iupsFlushMap_sm_0_t_1[IUPSFlushRepository::iupsFlushMap_sm_0_t_1_cnt] = csvxdr;
				IUPSFlushRepository::iupsFlushMap_sm_0_t_1_cnt++;
				break;
			case 2:
				IUPSFlushRepository::iupsFlushMap_sm_0_t_2[IUPSFlushRepository::iupsFlushMap_sm_0_t_2_cnt] = csvxdr;
				IUPSFlushRepository::iupsFlushMap_sm_0_t_2_cnt++;
				break;
			case 3:
				IUPSFlushRepository::iupsFlushMap_sm_0_t_3[IUPSFlushRepository::iupsFlushMap_sm_0_t_3_cnt] = csvxdr;
				IUPSFlushRepository::iupsFlushMap_sm_0_t_3_cnt++;
				break;
			case 4:
				IUPSFlushRepository::iupsFlushMap_sm_0_t_4[IUPSFlushRepository::iupsFlushMap_sm_0_t_4_cnt] = csvxdr;
				IUPSFlushRepository::iupsFlushMap_sm_0_t_4_cnt++;
				break;
			case 5:
				IUPSFlushRepository::iupsFlushMap_sm_0_t_5[IUPSFlushRepository::iupsFlushMap_sm_0_t_5_cnt] = csvxdr;
				IUPSFlushRepository::iupsFlushMap_sm_0_t_5_cnt++;
				break;
			case 6:
				IUPSFlushRepository::iupsFlushMap_sm_0_t_6[IUPSFlushRepository::iupsFlushMap_sm_0_t_6_cnt] = csvxdr;
				IUPSFlushRepository::iupsFlushMap_sm_0_t_6_cnt++;
				break;
			case 7:
				IUPSFlushRepository::iupsFlushMap_sm_0_t_7[IUPSFlushRepository::iupsFlushMap_sm_0_t_7_cnt] = csvxdr;
				IUPSFlushRepository::iupsFlushMap_sm_0_t_7_cnt++;
				break;
			case 8:
				IUPSFlushRepository::iupsFlushMap_sm_0_t_8[IUPSFlushRepository::iupsFlushMap_sm_0_t_8_cnt] = csvxdr;
				IUPSFlushRepository::iupsFlushMap_sm_0_t_8_cnt++;
				break;
			case 9:
				IUPSFlushRepository::iupsFlushMap_sm_0_t_9[IUPSFlushRepository::iupsFlushMap_sm_0_t_9_cnt] = csvxdr;
				IUPSFlushRepository::iupsFlushMap_sm_0_t_9_cnt++;
				break;
	}
}

VOID IUPSSessionManager::initializeIUPSFlushRepository()
{
//	printf("IPSessionManager  Initializing IUPS Flush    Repository with [%'07d] x 10 ...\n", IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//	TheLog_nc_v1(Log::Info, name(),"  [%d] Initializing IUPS Flush    Repository with [%'07d] x 10 ...", IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//	IUPSFlushRepository::iupsFlushMap_sm_0_t_0.reserve(100000);
//	IUPSFlushRepository::iupsFlushMap_sm_0_t_1.reserve(100000);
//	IUPSFlushRepository::iupsFlushMap_sm_0_t_2.reserve(100000);
//	IUPSFlushRepository::iupsFlushMap_sm_0_t_3.reserve(100000);
//	IUPSFlushRepository::iupsFlushMap_sm_0_t_4.reserve(100000);
//	IUPSFlushRepository::iupsFlushMap_sm_0_t_5.reserve(100000);
//	IUPSFlushRepository::iupsFlushMap_sm_0_t_6.reserve(100000);
//	IUPSFlushRepository::iupsFlushMap_sm_0_t_7.reserve(100000);
//	IUPSFlushRepository::iupsFlushMap_sm_0_t_8.reserve(100000);
//	IUPSFlushRepository::iupsFlushMap_sm_0_t_9.reserve(100000);
//	printf("IPSessionManager  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...Completed\n", IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
//	TheLog_nc_v1(Log::Info, name(),"  [%d] Initializing IP Flush    Repository with [%'07d] x 10 ...Completed", IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);

}
